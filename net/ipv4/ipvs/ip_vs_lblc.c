multiline_comment|/*&n; * IPVS:        Locality-Based Least-Connection scheduling module&n; *&n; * Version:     $Id: ip_vs_lblc.c,v 1.10 2002/09/15 08:14:08 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@gnuchina.org&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *     Martin Hamilton         :    fixed the terrible locking bugs&n; *                                   *lock(tbl-&gt;lock) ==&gt; *lock(&amp;tbl-&gt;lock)&n; *     Wensong Zhang           :    fixed the uninitilized tbl-&gt;lock bug&n; *     Wensong Zhang           :    added doing full expiration check to&n; *                                   collect stale entries of 24+ hours when&n; *                                   no partial expire check in a half hour&n; *     Julian Anastasov        :    replaced del_timer call with del_timer_sync&n; *                                   to avoid the possible race between timer&n; *                                   handler and del_timer thread in SMP&n; *&n; */
multiline_comment|/*&n; * The lblc algorithm is as follows (pseudo code):&n; *&n; *       if cachenode[dest_ip] is null then&n; *               n, cachenode[dest_ip] &lt;- {weighted least-conn node};&n; *       else&n; *               n &lt;- cachenode[dest_ip];&n; *               if (n is dead) OR&n; *                  (n.conns&gt;n.weight AND&n; *                   there is a node m with m.conns&lt;m.weight/2) then&n; *                 n, cachenode[dest_ip] &lt;- {weighted least-conn node};&n; *&n; *       return n;&n; *&n; * Thanks must go to Wenzhuo Zhang for talking WCCP to me and pushing&n; * me to write this module.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* for systcl */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
multiline_comment|/*&n; *    It is for garbage collection of stale IPVS lblc entries,&n; *    when the table is full.&n; */
DECL|macro|CHECK_EXPIRE_INTERVAL
mdefine_line|#define CHECK_EXPIRE_INTERVAL   (60*HZ)
DECL|macro|ENTRY_TIMEOUT
mdefine_line|#define ENTRY_TIMEOUT           (6*60*HZ)
multiline_comment|/*&n; *    It is for full expiration check.&n; *    When there is no partial expiration check (garbage collection)&n; *    in a half hour, do a full expiration check to collect stale&n; *    entries that haven&squot;t been touched for a day.&n; */
DECL|macro|COUNT_FOR_FULL_EXPIRATION
mdefine_line|#define COUNT_FOR_FULL_EXPIRATION   30
DECL|variable|sysctl_ip_vs_lblc_expiration
r_int
id|sysctl_ip_vs_lblc_expiration
op_assign
l_int|24
op_star
l_int|60
op_star
l_int|60
op_star
id|HZ
suffix:semicolon
multiline_comment|/*&n; *     for IPVS lblc entry hash table&n; */
macro_line|#ifndef CONFIG_IP_VS_LBLC_TAB_BITS
DECL|macro|CONFIG_IP_VS_LBLC_TAB_BITS
mdefine_line|#define CONFIG_IP_VS_LBLC_TAB_BITS      10
macro_line|#endif
DECL|macro|IP_VS_LBLC_TAB_BITS
mdefine_line|#define IP_VS_LBLC_TAB_BITS     CONFIG_IP_VS_LBLC_TAB_BITS
DECL|macro|IP_VS_LBLC_TAB_SIZE
mdefine_line|#define IP_VS_LBLC_TAB_SIZE     (1 &lt;&lt; IP_VS_LBLC_TAB_BITS)
DECL|macro|IP_VS_LBLC_TAB_MASK
mdefine_line|#define IP_VS_LBLC_TAB_MASK     (IP_VS_LBLC_TAB_SIZE - 1)
multiline_comment|/*&n; *      IPVS lblc entry represents an association between destination&n; *      IP address and its destination server&n; */
DECL|struct|ip_vs_lblc_entry
r_struct
id|ip_vs_lblc_entry
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|addr
id|__u32
id|addr
suffix:semicolon
multiline_comment|/* destination IP address */
DECL|member|dest
r_struct
id|ip_vs_dest
op_star
id|dest
suffix:semicolon
multiline_comment|/* real server (cache) */
DECL|member|lastuse
r_int
r_int
id|lastuse
suffix:semicolon
multiline_comment|/* last used time */
)brace
suffix:semicolon
multiline_comment|/*&n; *      IPVS lblc hash table&n; */
DECL|struct|ip_vs_lblc_table
r_struct
id|ip_vs_lblc_table
(brace
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
multiline_comment|/* lock for this table */
DECL|member|bucket
r_struct
id|list_head
id|bucket
(braket
id|IP_VS_LBLC_TAB_SIZE
)braket
suffix:semicolon
multiline_comment|/* hash bucket */
DECL|member|entries
id|atomic_t
id|entries
suffix:semicolon
multiline_comment|/* number of entries */
DECL|member|max_size
r_int
id|max_size
suffix:semicolon
multiline_comment|/* maximum size of entries */
DECL|member|periodic_timer
r_struct
id|timer_list
id|periodic_timer
suffix:semicolon
multiline_comment|/* collect stale entries */
DECL|member|rover
r_int
id|rover
suffix:semicolon
multiline_comment|/* rover for expire check */
DECL|member|counter
r_int
id|counter
suffix:semicolon
multiline_comment|/* counter for no expire */
)brace
suffix:semicolon
multiline_comment|/*&n; *      IPVS LBLC sysctl table&n; */
DECL|struct|ip_vs_lblc_sysctl_table
r_struct
id|ip_vs_lblc_sysctl_table
(brace
DECL|member|sysctl_header
r_struct
id|ctl_table_header
op_star
id|sysctl_header
suffix:semicolon
DECL|member|vs_vars
id|ctl_table
id|vs_vars
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|vs_dir
id|ctl_table
id|vs_dir
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ipv4_dir
id|ctl_table
id|ipv4_dir
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|root_dir
id|ctl_table
id|root_dir
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|lblc_sysctl_table
r_static
r_struct
id|ip_vs_lblc_sysctl_table
id|lblc_sysctl_table
op_assign
(brace
l_int|NULL
comma
(brace
(brace
id|NET_IPV4_VS_LBLC_EXPIRE
comma
l_string|&quot;lblc_expiration&quot;
comma
op_amp
id|sysctl_ip_vs_lblc_expiration
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_jiffies
)brace
comma
(brace
l_int|0
)brace
)brace
comma
(brace
(brace
id|NET_IPV4_VS
comma
l_string|&quot;vs&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|lblc_sysctl_table.vs_vars
)brace
comma
(brace
l_int|0
)brace
)brace
comma
(brace
(brace
id|NET_IPV4
comma
l_string|&quot;ipv4&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|lblc_sysctl_table.vs_dir
)brace
comma
(brace
l_int|0
)brace
)brace
comma
(brace
(brace
id|CTL_NET
comma
l_string|&quot;net&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|lblc_sysctl_table.ipv4_dir
)brace
comma
(brace
l_int|0
)brace
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; *      new/free a ip_vs_lblc_entry, which is a mapping of a destionation&n; *      IP address to a server.&n; */
r_static
r_inline
r_struct
id|ip_vs_lblc_entry
op_star
DECL|function|ip_vs_lblc_new
id|ip_vs_lblc_new
c_func
(paren
id|__u32
id|daddr
comma
r_struct
id|ip_vs_dest
op_star
id|dest
)paren
(brace
r_struct
id|ip_vs_lblc_entry
op_star
id|en
suffix:semicolon
id|en
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ip_vs_lblc_entry
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|en
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_lblc_new(): no memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|en-&gt;list
)paren
suffix:semicolon
id|en-&gt;addr
op_assign
id|daddr
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dest-&gt;refcnt
)paren
suffix:semicolon
id|en-&gt;dest
op_assign
id|dest
suffix:semicolon
r_return
id|en
suffix:semicolon
)brace
DECL|function|ip_vs_lblc_free
r_static
r_inline
r_void
id|ip_vs_lblc_free
c_func
(paren
r_struct
id|ip_vs_lblc_entry
op_star
id|en
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|en-&gt;list
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t kfree dest because it is refered either by its service&n;&t; * or the trash dest list.&n;&t; */
id|atomic_dec
c_func
(paren
op_amp
id|en-&gt;dest-&gt;refcnt
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|en
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Returns hash value for IPVS LBLC entry&n; */
DECL|function|ip_vs_lblc_hashkey
r_static
r_inline
r_int
id|ip_vs_lblc_hashkey
c_func
(paren
id|__u32
id|addr
)paren
(brace
r_return
(paren
id|ntohl
c_func
(paren
id|addr
)paren
op_star
l_int|2654435761UL
)paren
op_amp
id|IP_VS_LBLC_TAB_MASK
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Hash an entry in the ip_vs_lblc_table.&n; *&t;returns bool success.&n; */
r_static
r_int
DECL|function|ip_vs_lblc_hash
id|ip_vs_lblc_hash
c_func
(paren
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
comma
r_struct
id|ip_vs_lblc_entry
op_star
id|en
)paren
(brace
r_int
id|hash
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|en-&gt;list
)paren
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_lblc_hash(): request for already hashed, &quot;
l_string|&quot;called from %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Hash by destination IP address&n;&t; */
id|hash
op_assign
id|ip_vs_lblc_hashkey
c_func
(paren
id|en-&gt;addr
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|en-&gt;list
comma
op_amp
id|tbl-&gt;bucket
(braket
id|hash
)braket
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|tbl-&gt;entries
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#if 0000
multiline_comment|/*&n; *&t;Unhash ip_vs_lblc_entry from ip_vs_lblc_table.&n; *&t;returns bool success.&n; */
r_static
r_int
id|ip_vs_lblc_unhash
c_func
(paren
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
comma
r_struct
id|ip_vs_lblc_entry
op_star
id|en
)paren
(brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|en-&gt;list
)paren
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_lblc_unhash(): request for not hashed entry, &quot;
l_string|&quot;called from %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Remove it from the table&n;&t; */
id|write_lock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|en-&gt;list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|en-&gt;list
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *  Get ip_vs_lblc_entry associated with supplied parameters.&n; */
r_static
r_inline
r_struct
id|ip_vs_lblc_entry
op_star
DECL|function|ip_vs_lblc_get
id|ip_vs_lblc_get
c_func
(paren
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
comma
id|__u32
id|addr
)paren
(brace
r_int
id|hash
suffix:semicolon
r_struct
id|ip_vs_lblc_entry
op_star
id|en
suffix:semicolon
id|hash
op_assign
id|ip_vs_lblc_hashkey
c_func
(paren
id|addr
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|en
comma
op_amp
id|tbl-&gt;bucket
(braket
id|hash
)braket
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|en-&gt;addr
op_eq
id|addr
)paren
(brace
multiline_comment|/* HIT */
id|read_unlock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
id|en
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *      Flush all the entries of the specified table.&n; */
DECL|function|ip_vs_lblc_flush
r_static
r_void
id|ip_vs_lblc_flush
c_func
(paren
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ip_vs_lblc_entry
op_star
id|en
comma
op_star
id|nxt
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IP_VS_LBLC_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|en
comma
id|nxt
comma
op_amp
id|tbl-&gt;bucket
(braket
id|i
)braket
comma
id|list
)paren
(brace
id|ip_vs_lblc_free
c_func
(paren
id|en
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|tbl-&gt;entries
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|ip_vs_lblc_full_check
r_static
r_inline
r_void
id|ip_vs_lblc_full_check
c_func
(paren
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
)paren
(brace
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|ip_vs_lblc_entry
op_star
id|en
comma
op_star
id|nxt
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
id|tbl-&gt;rover
suffix:semicolon
id|i
OL
id|IP_VS_LBLC_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
(paren
id|j
op_plus
l_int|1
)paren
op_amp
id|IP_VS_LBLC_TAB_MASK
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|en
comma
id|nxt
comma
op_amp
id|tbl-&gt;bucket
(braket
id|j
)braket
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|now
comma
id|en-&gt;lastuse
op_plus
id|sysctl_ip_vs_lblc_expiration
)paren
)paren
r_continue
suffix:semicolon
id|ip_vs_lblc_free
c_func
(paren
id|en
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|tbl-&gt;entries
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
)brace
id|tbl-&gt;rover
op_assign
id|j
suffix:semicolon
)brace
multiline_comment|/*&n; *      Periodical timer handler for IPVS lblc table&n; *      It is used to collect stale entries when the number of entries&n; *      exceeds the maximum size of the table.&n; *&n; *      Fixme: we probably need more complicated algorithm to collect&n; *             entries that have not been used for a long time even&n; *             if the number of entries doesn&squot;t exceed the maximum size&n; *             of the table.&n; *      The full expiration check is for this purpose now.&n; */
DECL|function|ip_vs_lblc_check_expire
r_static
r_void
id|ip_vs_lblc_check_expire
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_int
id|goal
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|ip_vs_lblc_entry
op_star
id|en
comma
op_star
id|nxt
suffix:semicolon
id|tbl
op_assign
(paren
r_struct
id|ip_vs_lblc_table
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tbl-&gt;counter
op_mod
id|COUNT_FOR_FULL_EXPIRATION
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* do full expiration check */
id|ip_vs_lblc_full_check
c_func
(paren
id|tbl
)paren
suffix:semicolon
id|tbl-&gt;counter
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|tbl-&gt;entries
)paren
op_le
id|tbl-&gt;max_size
)paren
(brace
id|tbl-&gt;counter
op_increment
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|goal
op_assign
(paren
id|atomic_read
c_func
(paren
op_amp
id|tbl-&gt;entries
)paren
op_minus
id|tbl-&gt;max_size
)paren
op_star
l_int|4
op_div
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|goal
OG
id|tbl-&gt;max_size
op_div
l_int|2
)paren
id|goal
op_assign
id|tbl-&gt;max_size
op_div
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
id|tbl-&gt;rover
suffix:semicolon
id|i
OL
id|IP_VS_LBLC_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
(paren
id|j
op_plus
l_int|1
)paren
op_amp
id|IP_VS_LBLC_TAB_MASK
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|en
comma
id|nxt
comma
op_amp
id|tbl-&gt;bucket
(braket
id|j
)braket
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|now
comma
id|en-&gt;lastuse
op_plus
id|ENTRY_TIMEOUT
)paren
)paren
r_continue
suffix:semicolon
id|ip_vs_lblc_free
c_func
(paren
id|en
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|tbl-&gt;entries
)paren
suffix:semicolon
id|goal
op_decrement
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|goal
op_le
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|tbl-&gt;rover
op_assign
id|j
suffix:semicolon
id|out
suffix:colon
id|mod_timer
c_func
(paren
op_amp
id|tbl-&gt;periodic_timer
comma
id|jiffies
op_plus
id|CHECK_EXPIRE_INTERVAL
)paren
suffix:semicolon
)brace
DECL|function|ip_vs_lblc_init_svc
r_static
r_int
id|ip_vs_lblc_init_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
suffix:semicolon
multiline_comment|/*&n;&t; *    Allocate the ip_vs_lblc_table for this service&n;&t; */
id|tbl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ip_vs_lblc_table
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tbl
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_lblc_init_svc(): no memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|svc-&gt;sched_data
op_assign
id|tbl
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;LBLC hash table (memory=%Zdbytes) allocated for &quot;
l_string|&quot;current service&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|ip_vs_lblc_table
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *    Initialize the hash buckets&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IP_VS_LBLC_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|tbl-&gt;bucket
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|tbl-&gt;lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|tbl-&gt;max_size
op_assign
id|IP_VS_LBLC_TAB_SIZE
op_star
l_int|16
suffix:semicolon
id|tbl-&gt;rover
op_assign
l_int|0
suffix:semicolon
id|tbl-&gt;counter
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *    Hook periodic timer for garbage collection&n;&t; */
id|init_timer
c_func
(paren
op_amp
id|tbl-&gt;periodic_timer
)paren
suffix:semicolon
id|tbl-&gt;periodic_timer.data
op_assign
(paren
r_int
r_int
)paren
id|tbl
suffix:semicolon
id|tbl-&gt;periodic_timer.function
op_assign
id|ip_vs_lblc_check_expire
suffix:semicolon
id|tbl-&gt;periodic_timer.expires
op_assign
id|jiffies
op_plus
id|CHECK_EXPIRE_INTERVAL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tbl-&gt;periodic_timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_vs_lblc_done_svc
r_static
r_int
id|ip_vs_lblc_done_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
op_assign
id|svc-&gt;sched_data
suffix:semicolon
multiline_comment|/* remove periodic timer */
id|del_timer_sync
c_func
(paren
op_amp
id|tbl-&gt;periodic_timer
)paren
suffix:semicolon
multiline_comment|/* got to clean up table entries here */
id|ip_vs_lblc_flush
c_func
(paren
id|tbl
)paren
suffix:semicolon
multiline_comment|/* release the table itself */
id|kfree
c_func
(paren
id|svc-&gt;sched_data
)paren
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;LBLC hash table (memory=%Zdbytes) released&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|ip_vs_lblc_table
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_vs_lblc_update_svc
r_static
r_int
id|ip_vs_lblc_update_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|ip_vs_dest
op_star
DECL|function|__ip_vs_wlc_schedule
id|__ip_vs_wlc_schedule
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
comma
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
r_struct
id|ip_vs_dest
op_star
id|dest
comma
op_star
id|least
suffix:semicolon
r_int
id|loh
comma
id|doh
suffix:semicolon
multiline_comment|/*&n;&t; * We think the overhead of processing active connections is fifty&n;&t; * times higher than that of inactive connections in average. (This&n;&t; * fifty times might not be accurate, we will change it later.) We&n;&t; * use the following formula to estimate the overhead:&n;&t; *                dest-&gt;activeconns*50 + dest-&gt;inactconns&n;&t; * and the load:&n;&t; *                (dest overhead) / dest-&gt;weight&n;&t; *&n;&t; * Remember -- no floats in kernel mode!!!&n;&t; * The comparison of h1*w2 &gt; h2*w1 is equivalent to that of&n;&t; *                h1/w1 &gt; h2/w2&n;&t; * if every weight is larger than zero.&n;&t; *&n;&t; * The server with weight=0 is quiesced and will not receive any&n;&t; * new connection.&n;&t; */
id|list_for_each_entry
c_func
(paren
id|least
comma
op_amp
id|svc-&gt;destinations
comma
id|n_list
)paren
(brace
r_if
c_cond
(paren
id|least-&gt;flags
op_amp
id|IP_VS_DEST_F_OVERLOAD
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;weight
)paren
OG
l_int|0
)paren
(brace
id|loh
op_assign
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;activeconns
)paren
op_star
l_int|50
op_plus
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;inactconns
)paren
suffix:semicolon
r_goto
id|nextstage
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *    Find the destination with the least load.&n;&t; */
id|nextstage
suffix:colon
id|list_for_each_entry
c_func
(paren
id|dest
comma
op_amp
id|svc-&gt;destinations
comma
id|n_list
)paren
(brace
r_if
c_cond
(paren
id|dest-&gt;flags
op_amp
id|IP_VS_DEST_F_OVERLOAD
)paren
r_continue
suffix:semicolon
id|doh
op_assign
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;activeconns
)paren
op_star
l_int|50
op_plus
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;inactconns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loh
op_star
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
OG
id|doh
op_star
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;weight
)paren
)paren
(brace
id|least
op_assign
id|dest
suffix:semicolon
id|loh
op_assign
id|doh
suffix:semicolon
)brace
)brace
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;LBLC: server %d.%d.%d.%d:%d &quot;
l_string|&quot;activeconns %d refcnt %d weight %d overhead %d&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|least-&gt;addr
)paren
comma
id|ntohs
c_func
(paren
id|least-&gt;port
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;activeconns
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;refcnt
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;weight
)paren
comma
id|loh
)paren
suffix:semicolon
r_return
id|least
suffix:semicolon
)brace
multiline_comment|/*&n; *   If this destination server is overloaded and there is a less loaded&n; *   server, then return true.&n; */
r_static
r_inline
r_int
DECL|function|is_overloaded
id|is_overloaded
c_func
(paren
r_struct
id|ip_vs_dest
op_star
id|dest
comma
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;activeconns
)paren
OG
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
)paren
(brace
r_struct
id|ip_vs_dest
op_star
id|d
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|d
comma
op_amp
id|svc-&gt;destinations
comma
id|n_list
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|d-&gt;activeconns
)paren
op_star
l_int|2
OL
id|atomic_read
c_func
(paren
op_amp
id|d-&gt;weight
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *    Locality-Based (weighted) Least-Connection scheduling&n; */
r_static
r_struct
id|ip_vs_dest
op_star
DECL|function|ip_vs_lblc_schedule
id|ip_vs_lblc_schedule
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
comma
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
r_struct
id|ip_vs_dest
op_star
id|dest
suffix:semicolon
r_struct
id|ip_vs_lblc_table
op_star
id|tbl
suffix:semicolon
r_struct
id|ip_vs_lblc_entry
op_star
id|en
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;ip_vs_lblc_schedule(): Scheduling...&bslash;n&quot;
)paren
suffix:semicolon
id|tbl
op_assign
(paren
r_struct
id|ip_vs_lblc_table
op_star
)paren
id|svc-&gt;sched_data
suffix:semicolon
id|en
op_assign
id|ip_vs_lblc_get
c_func
(paren
id|tbl
comma
id|iph-&gt;daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|en
op_eq
l_int|NULL
)paren
(brace
id|dest
op_assign
id|__ip_vs_wlc_schedule
c_func
(paren
id|svc
comma
id|iph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_DBG
c_func
(paren
l_int|1
comma
l_string|&quot;no destination available&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|en
op_assign
id|ip_vs_lblc_new
c_func
(paren
id|iph-&gt;daddr
comma
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|en
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|ip_vs_lblc_hash
c_func
(paren
id|tbl
comma
id|en
)paren
suffix:semicolon
)brace
r_else
(brace
id|dest
op_assign
id|en-&gt;dest
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dest-&gt;flags
op_amp
id|IP_VS_DEST_F_AVAILABLE
)paren
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
op_le
l_int|0
op_logical_or
id|is_overloaded
c_func
(paren
id|dest
comma
id|svc
)paren
)paren
(brace
id|dest
op_assign
id|__ip_vs_wlc_schedule
c_func
(paren
id|svc
comma
id|iph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_DBG
c_func
(paren
l_int|1
comma
l_string|&quot;no destination available&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|en-&gt;dest-&gt;refcnt
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dest-&gt;refcnt
)paren
suffix:semicolon
id|en-&gt;dest
op_assign
id|dest
suffix:semicolon
)brace
)brace
id|en-&gt;lastuse
op_assign
id|jiffies
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;LBLC: destination IP address %u.%u.%u.%u &quot;
l_string|&quot;--&gt; server %u.%u.%u.%u:%d&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|en-&gt;addr
)paren
comma
id|NIPQUAD
c_func
(paren
id|dest-&gt;addr
)paren
comma
id|ntohs
c_func
(paren
id|dest-&gt;port
)paren
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
multiline_comment|/*&n; *      IPVS LBLC Scheduler structure&n; */
DECL|variable|ip_vs_lblc_scheduler
r_static
r_struct
id|ip_vs_scheduler
id|ip_vs_lblc_scheduler
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lblc&quot;
comma
dot
id|refcnt
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|init_service
op_assign
id|ip_vs_lblc_init_svc
comma
dot
id|done_service
op_assign
id|ip_vs_lblc_done_svc
comma
dot
id|update_service
op_assign
id|ip_vs_lblc_update_svc
comma
dot
id|schedule
op_assign
id|ip_vs_lblc_schedule
comma
)brace
suffix:semicolon
DECL|function|ip_vs_lblc_init
r_static
r_int
id|__init
id|ip_vs_lblc_init
c_func
(paren
r_void
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ip_vs_lblc_scheduler.n_list
)paren
suffix:semicolon
id|lblc_sysctl_table.sysctl_header
op_assign
id|register_sysctl_table
c_func
(paren
id|lblc_sysctl_table.root_dir
comma
l_int|0
)paren
suffix:semicolon
r_return
id|register_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_lblc_scheduler
)paren
suffix:semicolon
)brace
DECL|function|ip_vs_lblc_cleanup
r_static
r_void
id|__exit
id|ip_vs_lblc_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|lblc_sysctl_table.sysctl_header
)paren
suffix:semicolon
id|unregister_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_lblc_scheduler
)paren
suffix:semicolon
)brace
DECL|variable|ip_vs_lblc_init
id|module_init
c_func
(paren
id|ip_vs_lblc_init
)paren
suffix:semicolon
DECL|variable|ip_vs_lblc_cleanup
id|module_exit
c_func
(paren
id|ip_vs_lblc_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
