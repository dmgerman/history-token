multiline_comment|/*&n; * IPVS:        Destination Hashing scheduling module&n; *&n; * Version:     $Id: ip_vs_dh.c,v 1.5 2002/09/15 08:14:08 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@gnuchina.org&gt;&n; *&n; *              Inspired by the consistent hashing scheduler patch from&n; *              Thomas Proell &lt;proellt@gmx.de&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *&n; */
multiline_comment|/*&n; * The dh algorithm is to select server by the hash key of destination IP&n; * address. The pseudo code is as follows:&n; *&n; *       n &lt;- servernode[dest_ip];&n; *       if (n is dead) OR&n; *          (n is overloaded) OR (n.weight &lt;= 0) then&n; *                 return NULL;&n; *&n; *       return n;&n; *&n; * Notes that servernode is a 256-bucket hash table that maps the hash&n; * index derived from packet destination IP address to the current server&n; * array. If the dh scheduler is used in cache cluster, it is good to&n; * combine it with cache_bypass feature. When the statically assigned&n; * server is dead or overloaded, the load balancer can bypass the cache&n; * server and send requests to the original server directly.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
multiline_comment|/*&n; *      IPVS DH bucket&n; */
DECL|struct|ip_vs_dh_bucket
r_struct
id|ip_vs_dh_bucket
(brace
DECL|member|dest
r_struct
id|ip_vs_dest
op_star
id|dest
suffix:semicolon
multiline_comment|/* real server (cache) */
)brace
suffix:semicolon
multiline_comment|/*&n; *     for IPVS DH entry hash table&n; */
macro_line|#ifndef CONFIG_IP_VS_DH_TAB_BITS
DECL|macro|CONFIG_IP_VS_DH_TAB_BITS
mdefine_line|#define CONFIG_IP_VS_DH_TAB_BITS        8
macro_line|#endif
DECL|macro|IP_VS_DH_TAB_BITS
mdefine_line|#define IP_VS_DH_TAB_BITS               CONFIG_IP_VS_DH_TAB_BITS
DECL|macro|IP_VS_DH_TAB_SIZE
mdefine_line|#define IP_VS_DH_TAB_SIZE               (1 &lt;&lt; IP_VS_DH_TAB_BITS)
DECL|macro|IP_VS_DH_TAB_MASK
mdefine_line|#define IP_VS_DH_TAB_MASK               (IP_VS_DH_TAB_SIZE - 1)
multiline_comment|/*&n; *&t;Returns hash value for IPVS DH entry&n; */
DECL|function|ip_vs_dh_hashkey
r_static
r_inline
r_int
id|ip_vs_dh_hashkey
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
id|IP_VS_DH_TAB_MASK
suffix:semicolon
)brace
multiline_comment|/*&n; *      Get ip_vs_dest associated with supplied parameters.&n; */
r_static
r_inline
r_struct
id|ip_vs_dest
op_star
DECL|function|ip_vs_dh_get
id|ip_vs_dh_get
c_func
(paren
r_struct
id|ip_vs_dh_bucket
op_star
id|tbl
comma
id|__u32
id|addr
)paren
(brace
r_return
(paren
id|tbl
(braket
id|ip_vs_dh_hashkey
c_func
(paren
id|addr
)paren
)braket
)paren
dot
id|dest
suffix:semicolon
)brace
multiline_comment|/*&n; *      Assign all the hash buckets of the specified table with the service.&n; */
r_static
r_int
DECL|function|ip_vs_dh_assign
id|ip_vs_dh_assign
c_func
(paren
r_struct
id|ip_vs_dh_bucket
op_star
id|tbl
comma
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
id|ip_vs_dh_bucket
op_star
id|b
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|ip_vs_dest
op_star
id|dest
suffix:semicolon
id|b
op_assign
id|tbl
suffix:semicolon
id|p
op_assign
op_amp
id|svc-&gt;destinations
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
id|IP_VS_DH_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
id|p
)paren
)paren
(brace
id|b-&gt;dest
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|p
op_eq
op_amp
id|svc-&gt;destinations
)paren
id|p
op_assign
id|p-&gt;next
suffix:semicolon
id|dest
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|ip_vs_dest
comma
id|n_list
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dest-&gt;refcnt
)paren
suffix:semicolon
id|b-&gt;dest
op_assign
id|dest
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|b
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *      Flush all the hash buckets of the specified table.&n; */
DECL|function|ip_vs_dh_flush
r_static
r_void
id|ip_vs_dh_flush
c_func
(paren
r_struct
id|ip_vs_dh_bucket
op_star
id|tbl
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ip_vs_dh_bucket
op_star
id|b
suffix:semicolon
id|b
op_assign
id|tbl
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
id|IP_VS_DH_TAB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|b-&gt;dest
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|b-&gt;dest-&gt;refcnt
)paren
suffix:semicolon
id|b-&gt;dest
op_assign
l_int|NULL
suffix:semicolon
)brace
id|b
op_increment
suffix:semicolon
)brace
)brace
DECL|function|ip_vs_dh_init_svc
r_static
r_int
id|ip_vs_dh_init_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_dh_bucket
op_star
id|tbl
suffix:semicolon
multiline_comment|/* allocate the DH table for this service */
id|tbl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ip_vs_dh_bucket
)paren
op_star
id|IP_VS_DH_TAB_SIZE
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
l_string|&quot;ip_vs_dh_init_svc(): no memory&bslash;n&quot;
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
l_string|&quot;DH hash table (memory=%dbytes) allocated for &quot;
l_string|&quot;current service&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|ip_vs_dh_bucket
)paren
op_star
id|IP_VS_DH_TAB_SIZE
)paren
suffix:semicolon
multiline_comment|/* assign the hash buckets with the updated service */
id|ip_vs_dh_assign
c_func
(paren
id|tbl
comma
id|svc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_vs_dh_done_svc
r_static
r_int
id|ip_vs_dh_done_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_dh_bucket
op_star
id|tbl
op_assign
id|svc-&gt;sched_data
suffix:semicolon
multiline_comment|/* got to clean up hash buckets here */
id|ip_vs_dh_flush
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
l_string|&quot;DH hash table (memory=%dbytes) released&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|ip_vs_dh_bucket
)paren
op_star
id|IP_VS_DH_TAB_SIZE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_vs_dh_update_svc
r_static
r_int
id|ip_vs_dh_update_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_dh_bucket
op_star
id|tbl
op_assign
id|svc-&gt;sched_data
suffix:semicolon
multiline_comment|/* got to clean up hash buckets here */
id|ip_vs_dh_flush
c_func
(paren
id|tbl
)paren
suffix:semicolon
multiline_comment|/* assign the hash buckets with the updated service */
id|ip_vs_dh_assign
c_func
(paren
id|tbl
comma
id|svc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *      If the dest flags is set with IP_VS_DEST_F_OVERLOAD,&n; *      consider that the server is overloaded here.&n; */
DECL|function|is_overloaded
r_static
r_inline
r_int
id|is_overloaded
c_func
(paren
r_struct
id|ip_vs_dest
op_star
id|dest
)paren
(brace
r_return
id|dest-&gt;flags
op_amp
id|IP_VS_DEST_F_OVERLOAD
suffix:semicolon
)brace
multiline_comment|/*&n; *      Destination hashing scheduling&n; */
r_static
r_struct
id|ip_vs_dest
op_star
DECL|function|ip_vs_dh_schedule
id|ip_vs_dh_schedule
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
id|ip_vs_dh_bucket
op_star
id|tbl
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;ip_vs_dh_schedule(): Scheduling...&bslash;n&quot;
)paren
suffix:semicolon
id|tbl
op_assign
(paren
r_struct
id|ip_vs_dh_bucket
op_star
)paren
id|svc-&gt;sched_data
suffix:semicolon
id|dest
op_assign
id|ip_vs_dh_get
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
op_logical_neg
id|dest
op_logical_or
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
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;DH: destination IP address %u.%u.%u.%u &quot;
l_string|&quot;--&gt; server %u.%u.%u.%u:%d&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
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
multiline_comment|/*&n; *      IPVS DH Scheduler structure&n; */
DECL|variable|ip_vs_dh_scheduler
r_static
r_struct
id|ip_vs_scheduler
id|ip_vs_dh_scheduler
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dh&quot;
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
id|ip_vs_dh_init_svc
comma
dot
id|done_service
op_assign
id|ip_vs_dh_done_svc
comma
dot
id|update_service
op_assign
id|ip_vs_dh_update_svc
comma
dot
id|schedule
op_assign
id|ip_vs_dh_schedule
comma
)brace
suffix:semicolon
DECL|function|ip_vs_dh_init
r_static
r_int
id|__init
id|ip_vs_dh_init
c_func
(paren
r_void
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ip_vs_dh_scheduler.n_list
)paren
suffix:semicolon
r_return
id|register_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_dh_scheduler
)paren
suffix:semicolon
)brace
DECL|function|ip_vs_dh_cleanup
r_static
r_void
id|__exit
id|ip_vs_dh_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_dh_scheduler
)paren
suffix:semicolon
)brace
DECL|variable|ip_vs_dh_init
id|module_init
c_func
(paren
id|ip_vs_dh_init
)paren
suffix:semicolon
DECL|variable|ip_vs_dh_cleanup
id|module_exit
c_func
(paren
id|ip_vs_dh_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
