multiline_comment|/* iptables match extension to limit the number of packets per second&n; * seperately for each hashbucket (sourceip/sourceport/dstip/dstport)&n; *&n; * (C) 2003-2004 by Harald Welte &lt;laforge@netfilter.org&gt;&n; *&n; * $Id: ipt_hashlimit.c 3244 2004-10-20 16:24:29Z laforge@netfilter.org $&n; *&n; * Development of this code was funded by Astaro AG, http://www.astaro.com/&n; *&n; * based on ipt_limit.c by:&n; * J&#xfffd;r&#xfffd;me de Vivie&t;&lt;devivie@info.enserb.u-bordeaux.fr&gt;&n; * Herv&#xfffd; Eychenne&t;&lt;eychenne@info.enserb.u-bordeaux.fr&gt;&n; * Rusty Russell&t;&lt;rusty@rustcorp.com.au&gt;&n; *&n; * The general idea is to create a hash table for every dstip and have a&n; * seperate limit counter per tuple.  This way you can do something like &squot;limit&n; * the number of syn packets for each of my internal addresses.&n; *&n; * Ideally this would just be implemented as a general &squot;hash&squot; match, which would&n; * allow us to attach any iptables target to it&squot;s hash buckets.  But this is&n; * not possible in the current iptables architecture.  As always, pkttables for&n; * 2.7.x will help ;)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/jhash.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/sctp.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) 
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) 
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_hashlimit.h&gt;
multiline_comment|/* FIXME: this is just for IP_NF_ASSERRT */
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
DECL|macro|MS2JIFFIES
mdefine_line|#define MS2JIFFIES(x) ((x*HZ)/1000)
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Harald Welte &lt;laforge@netfilter.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iptables match for limiting per hash-bucket&quot;
)paren
suffix:semicolon
multiline_comment|/* need to declare this at the top */
DECL|variable|hashlimit_procdir
r_static
r_struct
id|proc_dir_entry
op_star
id|hashlimit_procdir
suffix:semicolon
DECL|variable|dl_file_ops
r_static
r_struct
id|file_operations
id|dl_file_ops
suffix:semicolon
multiline_comment|/* hash table crap */
DECL|struct|dsthash_dst
r_struct
id|dsthash_dst
(brace
DECL|member|src_ip
id|u_int32_t
id|src_ip
suffix:semicolon
DECL|member|dst_ip
id|u_int32_t
id|dst_ip
suffix:semicolon
multiline_comment|/* ports have to be consecutive !!! */
DECL|member|src_port
id|u_int16_t
id|src_port
suffix:semicolon
DECL|member|dst_port
id|u_int16_t
id|dst_port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dsthash_ent
r_struct
id|dsthash_ent
(brace
multiline_comment|/* static / read-only parts in the beginning */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|dst
r_struct
id|dsthash_dst
id|dst
suffix:semicolon
multiline_comment|/* modified structure members in the end */
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
multiline_comment|/* precalculated expiry time */
r_struct
(brace
DECL|member|prev
r_int
r_int
id|prev
suffix:semicolon
multiline_comment|/* last modification */
DECL|member|credit
id|u_int32_t
id|credit
suffix:semicolon
DECL|member|credit_cap
DECL|member|cost
id|u_int32_t
id|credit_cap
comma
id|cost
suffix:semicolon
DECL|member|rateinfo
)brace
id|rateinfo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipt_hashlimit_htable
r_struct
id|ipt_hashlimit_htable
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* global list of all htables */
DECL|member|use
id|atomic_t
id|use
suffix:semicolon
DECL|member|cfg
r_struct
id|hashlimit_cfg
id|cfg
suffix:semicolon
multiline_comment|/* config */
multiline_comment|/* used internally */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* lock for list_head */
DECL|member|rnd
id|u_int32_t
id|rnd
suffix:semicolon
multiline_comment|/* random seed for hash */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* timer for gc */
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
multiline_comment|/* number entries in table */
multiline_comment|/* seq_file stuff */
DECL|member|pde
r_struct
id|proc_dir_entry
op_star
id|pde
suffix:semicolon
DECL|member|hash
r_struct
id|list_head
id|hash
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* hashtable itself */
)brace
suffix:semicolon
r_static
id|DECLARE_RWLOCK
c_func
(paren
id|hashlimit_lock
)paren
suffix:semicolon
multiline_comment|/* protects htables list */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|hlimit_mutex
)paren
suffix:semicolon
multiline_comment|/* additional checkentry protection */
r_static
id|LIST_HEAD
c_func
(paren
id|hashlimit_htables
)paren
suffix:semicolon
DECL|variable|hashlimit_cachep
r_static
id|kmem_cache_t
op_star
id|hashlimit_cachep
suffix:semicolon
DECL|function|dst_cmp
r_static
r_inline
r_int
id|dst_cmp
c_func
(paren
r_const
r_struct
id|dsthash_ent
op_star
id|ent
comma
r_struct
id|dsthash_dst
op_star
id|b
)paren
(brace
r_return
(paren
id|ent-&gt;dst.dst_ip
op_eq
id|b-&gt;dst_ip
op_logical_and
id|ent-&gt;dst.dst_port
op_eq
id|b-&gt;dst_port
op_logical_and
id|ent-&gt;dst.src_port
op_eq
id|b-&gt;src_port
op_logical_and
id|ent-&gt;dst.src_ip
op_eq
id|b-&gt;src_ip
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u_int32_t
DECL|function|hash_dst
id|hash_dst
c_func
(paren
r_const
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_const
r_struct
id|dsthash_dst
op_star
id|dst
)paren
(brace
r_return
(paren
id|jhash_3words
c_func
(paren
id|dst-&gt;dst_ip
comma
(paren
id|dst-&gt;dst_port
op_lshift
l_int|16
op_amp
id|dst-&gt;src_port
)paren
comma
id|dst-&gt;src_ip
comma
id|ht-&gt;rnd
)paren
op_mod
id|ht-&gt;cfg.size
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|dsthash_ent
op_star
DECL|function|__dsthash_find
id|__dsthash_find
c_func
(paren
r_const
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_struct
id|dsthash_dst
op_star
id|dst
)paren
(brace
r_struct
id|dsthash_ent
op_star
id|ent
suffix:semicolon
id|u_int32_t
id|hash
op_assign
id|hash_dst
c_func
(paren
id|ht
comma
id|dst
)paren
suffix:semicolon
id|ent
op_assign
id|LIST_FIND
c_func
(paren
op_amp
id|ht-&gt;hash
(braket
id|hash
)braket
comma
id|dst_cmp
comma
r_struct
id|dsthash_ent
op_star
comma
id|dst
)paren
suffix:semicolon
r_return
id|ent
suffix:semicolon
)brace
multiline_comment|/* allocate dsthash_ent, initialize dst, put in htable and lock it */
r_static
r_struct
id|dsthash_ent
op_star
DECL|function|__dsthash_alloc_init
id|__dsthash_alloc_init
c_func
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_struct
id|dsthash_dst
op_star
id|dst
)paren
(brace
r_struct
id|dsthash_ent
op_star
id|ent
suffix:semicolon
multiline_comment|/* initialize hash with random val at the time we allocate&n;&t; * the first hashtable entry */
r_if
c_cond
(paren
op_logical_neg
id|ht-&gt;rnd
)paren
id|get_random_bytes
c_func
(paren
op_amp
id|ht-&gt;rnd
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ht-&gt;cfg.max
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|ht-&gt;count
)paren
op_ge
id|ht-&gt;cfg.max
)paren
(brace
multiline_comment|/* FIXME: do something. question is what.. */
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ipt_hashlimit: max count of %u reached&bslash;n&quot;
comma
id|ht-&gt;cfg.max
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ent
op_assign
id|kmem_cache_alloc
c_func
(paren
id|hashlimit_cachep
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipt_hashlimit: can&squot;t allocate dsthash_ent&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|ht-&gt;count
)paren
suffix:semicolon
id|ent-&gt;dst.dst_ip
op_assign
id|dst-&gt;dst_ip
suffix:semicolon
id|ent-&gt;dst.dst_port
op_assign
id|dst-&gt;dst_port
suffix:semicolon
id|ent-&gt;dst.src_ip
op_assign
id|dst-&gt;src_ip
suffix:semicolon
id|ent-&gt;dst.src_port
op_assign
id|dst-&gt;src_port
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|ent-&gt;list
comma
op_amp
id|ht-&gt;hash
(braket
id|hash_dst
c_func
(paren
id|ht
comma
id|dst
)paren
)braket
)paren
suffix:semicolon
r_return
id|ent
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__dsthash_free
id|__dsthash_free
c_func
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_struct
id|dsthash_ent
op_star
id|ent
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|ent-&gt;list
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|hashlimit_cachep
comma
id|ent
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|ht-&gt;count
)paren
suffix:semicolon
)brace
r_static
r_void
id|htable_gc
c_func
(paren
r_int
r_int
id|htlong
)paren
suffix:semicolon
DECL|function|htable_create
r_static
r_int
id|htable_create
c_func
(paren
r_struct
id|ipt_hashlimit_info
op_star
id|minfo
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|ipt_hashlimit_htable
op_star
id|hinfo
suffix:semicolon
r_if
c_cond
(paren
id|minfo-&gt;cfg.size
)paren
id|size
op_assign
id|minfo-&gt;cfg.size
suffix:semicolon
r_else
(brace
id|size
op_assign
(paren
(paren
(paren
id|num_physpages
op_lshift
id|PAGE_SHIFT
)paren
op_div
l_int|16384
)paren
op_div
r_sizeof
(paren
r_struct
id|list_head
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_physpages
OG
(paren
l_int|1024
op_star
l_int|1024
op_star
l_int|1024
op_div
id|PAGE_SIZE
)paren
)paren
id|size
op_assign
l_int|8192
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|16
)paren
id|size
op_assign
l_int|16
suffix:semicolon
)brace
multiline_comment|/* FIXME: don&squot;t use vmalloc() here or anywhere else -HW */
id|hinfo
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_hashlimit_htable
)paren
op_plus
(paren
r_sizeof
(paren
r_struct
id|list_head
)paren
op_star
id|size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hinfo
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipt_hashlimit: Unable to create hashtable&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|minfo-&gt;hinfo
op_assign
id|hinfo
suffix:semicolon
multiline_comment|/* copy match config into hashtable config */
id|memcpy
c_func
(paren
op_amp
id|hinfo-&gt;cfg
comma
op_amp
id|minfo-&gt;cfg
comma
r_sizeof
(paren
id|hinfo-&gt;cfg
)paren
)paren
suffix:semicolon
id|hinfo-&gt;cfg.size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hinfo-&gt;cfg.max
)paren
id|hinfo-&gt;cfg.max
op_assign
l_int|8
op_star
id|hinfo-&gt;cfg.size
suffix:semicolon
r_else
r_if
c_cond
(paren
id|hinfo-&gt;cfg.max
OL
id|hinfo-&gt;cfg.size
)paren
id|hinfo-&gt;cfg.max
op_assign
id|hinfo-&gt;cfg.size
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
id|hinfo-&gt;cfg.size
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hinfo-&gt;hash
(braket
id|i
)braket
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|hinfo-&gt;count
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|hinfo-&gt;use
comma
l_int|1
)paren
suffix:semicolon
id|hinfo-&gt;rnd
op_assign
l_int|0
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|hinfo-&gt;lock
)paren
suffix:semicolon
id|hinfo-&gt;pde
op_assign
id|create_proc_entry
c_func
(paren
id|minfo-&gt;name
comma
l_int|0
comma
id|hashlimit_procdir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hinfo-&gt;pde
)paren
(brace
id|vfree
c_func
(paren
id|hinfo
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|hinfo-&gt;pde-&gt;proc_fops
op_assign
op_amp
id|dl_file_ops
suffix:semicolon
id|hinfo-&gt;pde-&gt;data
op_assign
id|hinfo
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|hinfo-&gt;timer
)paren
suffix:semicolon
id|hinfo-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|MS2JIFFIES
c_func
(paren
id|hinfo-&gt;cfg.gc_interval
)paren
suffix:semicolon
id|hinfo-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|hinfo
suffix:semicolon
id|hinfo-&gt;timer.function
op_assign
id|htable_gc
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|hinfo-&gt;timer
)paren
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|hashlimit_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|hinfo-&gt;list
comma
op_amp
id|hashlimit_htables
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|hashlimit_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|select_all
r_static
r_int
id|select_all
c_func
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_struct
id|dsthash_ent
op_star
id|he
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|select_gc
r_static
r_int
id|select_gc
c_func
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_struct
id|dsthash_ent
op_star
id|he
)paren
(brace
r_return
(paren
id|jiffies
op_ge
id|he-&gt;expires
)paren
suffix:semicolon
)brace
DECL|function|htable_selective_cleanup
r_static
r_void
id|htable_selective_cleanup
c_func
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_int
(paren
op_star
id|select
)paren
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
comma
r_struct
id|dsthash_ent
op_star
id|he
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|ht-&gt;cfg.size
op_logical_and
id|ht-&gt;cfg.max
)paren
suffix:semicolon
multiline_comment|/* lock hash table and iterate over it */
id|spin_lock_bh
c_func
(paren
op_amp
id|ht-&gt;lock
)paren
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
id|ht-&gt;cfg.size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dsthash_ent
op_star
id|dh
comma
op_star
id|n
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|dh
comma
id|n
comma
op_amp
id|ht-&gt;hash
(braket
id|i
)braket
comma
id|list
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|select
)paren
(paren
id|ht
comma
id|dh
)paren
)paren
id|__dsthash_free
c_func
(paren
id|ht
comma
id|dh
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|ht-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* hash table garbage collector, run by timer */
DECL|function|htable_gc
r_static
r_void
id|htable_gc
c_func
(paren
r_int
r_int
id|htlong
)paren
(brace
r_struct
id|ipt_hashlimit_htable
op_star
id|ht
op_assign
(paren
r_struct
id|ipt_hashlimit_htable
op_star
)paren
id|htlong
suffix:semicolon
id|htable_selective_cleanup
c_func
(paren
id|ht
comma
id|select_gc
)paren
suffix:semicolon
multiline_comment|/* re-add the timer accordingly */
id|ht-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|MS2JIFFIES
c_func
(paren
id|ht-&gt;cfg.gc_interval
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ht-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|htable_destroy
r_static
r_void
id|htable_destroy
c_func
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|hinfo
)paren
(brace
multiline_comment|/* remove timer, if it is pending */
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|hinfo-&gt;timer
)paren
)paren
id|del_timer
c_func
(paren
op_amp
id|hinfo-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* remove proc entry */
id|remove_proc_entry
c_func
(paren
id|hinfo-&gt;pde-&gt;name
comma
id|hashlimit_procdir
)paren
suffix:semicolon
id|htable_selective_cleanup
c_func
(paren
id|hinfo
comma
id|select_all
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|hinfo
)paren
suffix:semicolon
)brace
DECL|function|htable_find_get
r_static
r_struct
id|ipt_hashlimit_htable
op_star
id|htable_find_get
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|ipt_hashlimit_htable
op_star
id|hinfo
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|hashlimit_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|hinfo
comma
op_amp
id|hashlimit_htables
comma
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|hinfo-&gt;pde-&gt;name
)paren
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|hinfo-&gt;use
)paren
suffix:semicolon
id|READ_UNLOCK
c_func
(paren
op_amp
id|hashlimit_lock
)paren
suffix:semicolon
r_return
id|hinfo
suffix:semicolon
)brace
)brace
id|READ_UNLOCK
c_func
(paren
op_amp
id|hashlimit_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|htable_put
r_static
r_void
id|htable_put
c_func
(paren
r_struct
id|ipt_hashlimit_htable
op_star
id|hinfo
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|hinfo-&gt;use
)paren
)paren
(brace
id|WRITE_LOCK
c_func
(paren
op_amp
id|hashlimit_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|hinfo-&gt;list
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|hashlimit_lock
)paren
suffix:semicolon
id|htable_destroy
c_func
(paren
id|hinfo
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* The algorithm used is the Simple Token Bucket Filter (TBF)&n; * see net/sched/sch_tbf.c in the linux source tree&n; */
multiline_comment|/* Rusty: This is my (non-mathematically-inclined) understanding of&n;   this algorithm.  The `average rate&squot; in jiffies becomes your initial&n;   amount of credit `credit&squot; and the most credit you can ever have&n;   `credit_cap&squot;.  The `peak rate&squot; becomes the cost of passing the&n;   test, `cost&squot;.&n;&n;   `prev&squot; tracks the last packet hit: you gain one credit per jiffy.&n;   If you get credit balance more than this, the extra credit is&n;   discarded.  Every time the match passes, you lose `cost&squot; credits;&n;   if you don&squot;t have that many, the test fails.&n;&n;   See Alexey&squot;s formal explanation in net/sched/sch_tbf.c.&n;&n;   To get the maximum range, we multiply by this factor (ie. you get N&n;   credits per jiffy).  We want to allow a rate as low as 1 per day&n;   (slowest userspace tool allows), which means&n;   CREDITS_PER_JIFFY*HZ*60*60*24 &lt; 2^32 ie.&n;*/
DECL|macro|MAX_CPJ
mdefine_line|#define MAX_CPJ (0xFFFFFFFF / (HZ*60*60*24))
multiline_comment|/* Repeated shift and or gives us all 1s, final shift and add 1 gives&n; * us the power of 2 below the theoretical max, so GCC simply does a&n; * shift. */
DECL|macro|_POW2_BELOW2
mdefine_line|#define _POW2_BELOW2(x) ((x)|((x)&gt;&gt;1))
DECL|macro|_POW2_BELOW4
mdefine_line|#define _POW2_BELOW4(x) (_POW2_BELOW2(x)|_POW2_BELOW2((x)&gt;&gt;2))
DECL|macro|_POW2_BELOW8
mdefine_line|#define _POW2_BELOW8(x) (_POW2_BELOW4(x)|_POW2_BELOW4((x)&gt;&gt;4))
DECL|macro|_POW2_BELOW16
mdefine_line|#define _POW2_BELOW16(x) (_POW2_BELOW8(x)|_POW2_BELOW8((x)&gt;&gt;8))
DECL|macro|_POW2_BELOW32
mdefine_line|#define _POW2_BELOW32(x) (_POW2_BELOW16(x)|_POW2_BELOW16((x)&gt;&gt;16))
DECL|macro|POW2_BELOW32
mdefine_line|#define POW2_BELOW32(x) ((_POW2_BELOW32(x)&gt;&gt;1) + 1)
DECL|macro|CREDITS_PER_JIFFY
mdefine_line|#define CREDITS_PER_JIFFY POW2_BELOW32(MAX_CPJ)
multiline_comment|/* Precision saver. */
r_static
r_inline
id|u_int32_t
DECL|function|user2credits
id|user2credits
c_func
(paren
id|u_int32_t
id|user
)paren
(brace
multiline_comment|/* If multiplying would overflow... */
r_if
c_cond
(paren
id|user
OG
l_int|0xFFFFFFFF
op_div
(paren
id|HZ
op_star
id|CREDITS_PER_JIFFY
)paren
)paren
multiline_comment|/* Divide first. */
r_return
(paren
id|user
op_div
id|IPT_HASHLIMIT_SCALE
)paren
op_star
id|HZ
op_star
id|CREDITS_PER_JIFFY
suffix:semicolon
r_return
(paren
id|user
op_star
id|HZ
op_star
id|CREDITS_PER_JIFFY
)paren
op_div
id|IPT_HASHLIMIT_SCALE
suffix:semicolon
)brace
DECL|function|rateinfo_recalc
r_static
r_inline
r_void
id|rateinfo_recalc
c_func
(paren
r_struct
id|dsthash_ent
op_star
id|dh
comma
r_int
r_int
id|now
)paren
(brace
id|dh-&gt;rateinfo.credit
op_add_assign
(paren
id|now
op_minus
id|xchg
c_func
(paren
op_amp
id|dh-&gt;rateinfo.prev
comma
id|now
)paren
)paren
op_star
id|CREDITS_PER_JIFFY
suffix:semicolon
r_if
c_cond
(paren
id|dh-&gt;rateinfo.credit
OG
id|dh-&gt;rateinfo.credit_cap
)paren
id|dh-&gt;rateinfo.credit
op_assign
id|dh-&gt;rateinfo.credit_cap
suffix:semicolon
)brace
DECL|function|get_ports
r_static
r_inline
r_int
id|get_ports
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|offset
comma
id|u16
id|ports
(braket
l_int|2
)braket
)paren
(brace
r_union
(brace
r_struct
id|tcphdr
id|th
suffix:semicolon
r_struct
id|udphdr
id|uh
suffix:semicolon
id|sctp_sctphdr_t
id|sctph
suffix:semicolon
)brace
id|hdr_u
comma
op_star
id|ptr_u
suffix:semicolon
multiline_comment|/* Must not be a fragment. */
r_if
c_cond
(paren
id|offset
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Must be big enough to read ports (both UDP and TCP have&n;&t;   them at the start). */
id|ptr_u
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
comma
l_int|8
comma
op_amp
id|hdr_u
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr_u
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;nh.iph-&gt;protocol
)paren
(brace
r_case
id|IPPROTO_TCP
suffix:colon
id|ports
(braket
l_int|0
)braket
op_assign
id|ptr_u-&gt;th.source
suffix:semicolon
id|ports
(braket
l_int|1
)braket
op_assign
id|ptr_u-&gt;th.dest
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_UDP
suffix:colon
id|ports
(braket
l_int|0
)braket
op_assign
id|ptr_u-&gt;uh.source
suffix:semicolon
id|ports
(braket
l_int|1
)braket
op_assign
id|ptr_u-&gt;uh.dest
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_SCTP
suffix:colon
id|ports
(braket
l_int|0
)braket
op_assign
id|ptr_u-&gt;sctph.source
suffix:semicolon
id|ports
(braket
l_int|1
)braket
op_assign
id|ptr_u-&gt;sctph.dest
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* all other protocols don&squot;t supprot per-port hash&n;&t;&t;&t; * buckets */
id|ports
(braket
l_int|0
)braket
op_assign
id|ports
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|hashlimit_match
id|hashlimit_match
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|matchinfo
comma
r_int
id|offset
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_struct
id|ipt_hashlimit_info
op_star
id|r
op_assign
(paren
(paren
r_struct
id|ipt_hashlimit_info
op_star
)paren
id|matchinfo
)paren
op_member_access_from_pointer
id|u.master
suffix:semicolon
r_struct
id|ipt_hashlimit_htable
op_star
id|hinfo
op_assign
id|r-&gt;hinfo
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_struct
id|dsthash_ent
op_star
id|dh
suffix:semicolon
r_struct
id|dsthash_dst
id|dst
suffix:semicolon
multiline_comment|/* build &squot;dst&squot; according to hinfo-&gt;cfg and current packet */
id|memset
c_func
(paren
op_amp
id|dst
comma
l_int|0
comma
r_sizeof
(paren
id|dst
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hinfo-&gt;cfg.mode
op_amp
id|IPT_HASHLIMIT_HASH_DIP
)paren
id|dst.dst_ip
op_assign
id|skb-&gt;nh.iph-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
id|hinfo-&gt;cfg.mode
op_amp
id|IPT_HASHLIMIT_HASH_SIP
)paren
id|dst.src_ip
op_assign
id|skb-&gt;nh.iph-&gt;saddr
suffix:semicolon
r_if
c_cond
(paren
id|hinfo-&gt;cfg.mode
op_amp
id|IPT_HASHLIMIT_HASH_DPT
op_logical_or
id|hinfo-&gt;cfg.mode
op_amp
id|IPT_HASHLIMIT_HASH_SPT
)paren
(brace
id|u_int16_t
id|ports
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_ports
c_func
(paren
id|skb
comma
id|offset
comma
id|ports
)paren
)paren
(brace
multiline_comment|/* We&squot;ve been asked to examine this packet, and we&n;&t;&t; &t;  can&squot;t.  Hence, no choice but to drop. */
op_star
id|hotdrop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hinfo-&gt;cfg.mode
op_amp
id|IPT_HASHLIMIT_HASH_SPT
)paren
id|dst.src_port
op_assign
id|ports
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hinfo-&gt;cfg.mode
op_amp
id|IPT_HASHLIMIT_HASH_DPT
)paren
id|dst.dst_port
op_assign
id|ports
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|spin_lock_bh
c_func
(paren
op_amp
id|hinfo-&gt;lock
)paren
suffix:semicolon
id|dh
op_assign
id|__dsthash_find
c_func
(paren
id|hinfo
comma
op_amp
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dh
)paren
(brace
id|dh
op_assign
id|__dsthash_alloc_init
c_func
(paren
id|hinfo
comma
op_amp
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dh
)paren
(brace
multiline_comment|/* enomem... don&squot;t match == DROP */
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ENOMEM&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|hinfo-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dh-&gt;expires
op_assign
id|jiffies
op_plus
id|MS2JIFFIES
c_func
(paren
id|hinfo-&gt;cfg.expire
)paren
suffix:semicolon
id|dh-&gt;rateinfo.prev
op_assign
id|jiffies
suffix:semicolon
id|dh-&gt;rateinfo.credit
op_assign
id|user2credits
c_func
(paren
id|hinfo-&gt;cfg.avg
op_star
id|hinfo-&gt;cfg.burst
)paren
suffix:semicolon
id|dh-&gt;rateinfo.credit_cap
op_assign
id|user2credits
c_func
(paren
id|hinfo-&gt;cfg.avg
op_star
id|hinfo-&gt;cfg.burst
)paren
suffix:semicolon
id|dh-&gt;rateinfo.cost
op_assign
id|user2credits
c_func
(paren
id|hinfo-&gt;cfg.avg
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|hinfo-&gt;lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* update expiration timeout */
id|dh-&gt;expires
op_assign
id|now
op_plus
id|MS2JIFFIES
c_func
(paren
id|hinfo-&gt;cfg.expire
)paren
suffix:semicolon
id|rateinfo_recalc
c_func
(paren
id|dh
comma
id|now
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dh-&gt;rateinfo.credit
op_ge
id|dh-&gt;rateinfo.cost
)paren
(brace
multiline_comment|/* We&squot;re underlimit. */
id|dh-&gt;rateinfo.credit
op_sub_assign
id|dh-&gt;rateinfo.cost
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|hinfo-&gt;lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|hinfo-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* default case: we&squot;re overlimit, thus don&squot;t match */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|hashlimit_checkentry
id|hashlimit_checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_ip
op_star
id|ip
comma
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchsize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_struct
id|ipt_hashlimit_info
op_star
id|r
op_assign
id|matchinfo
suffix:semicolon
r_if
c_cond
(paren
id|matchsize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_hashlimit_info
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Check for overflow. */
r_if
c_cond
(paren
id|r-&gt;cfg.burst
op_eq
l_int|0
op_logical_or
id|user2credits
c_func
(paren
id|r-&gt;cfg.avg
op_star
id|r-&gt;cfg.burst
)paren
OL
id|user2credits
c_func
(paren
id|r-&gt;cfg.avg
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ipt_hashlimit: Overflow, try lower: %u/%u&bslash;n&quot;
comma
id|r-&gt;cfg.avg
comma
id|r-&gt;cfg.burst
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;cfg.mode
op_eq
l_int|0
op_logical_or
id|r-&gt;cfg.mode
OG
(paren
id|IPT_HASHLIMIT_HASH_DPT
op_or
id|IPT_HASHLIMIT_HASH_DIP
op_or
id|IPT_HASHLIMIT_HASH_SIP
op_or
id|IPT_HASHLIMIT_HASH_SPT
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;cfg.gc_interval
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;cfg.expire
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* This is the best we&squot;ve got: We cannot release and re-grab lock,&n;&t; * since checkentry() is called before ip_tables.c grabs ipt_mutex.  &n;&t; * We also cannot grab the hashtable spinlock, since htable_create will &n;&t; * call vmalloc, and that can sleep.  And we cannot just re-search&n;&t; * the list of htable&squot;s in htable_create(), since then we would&n;&t; * create duplicate proc files. -HW */
id|down
c_func
(paren
op_amp
id|hlimit_mutex
)paren
suffix:semicolon
id|r-&gt;hinfo
op_assign
id|htable_find_get
c_func
(paren
id|r-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;hinfo
op_logical_and
(paren
id|htable_create
c_func
(paren
id|r
)paren
op_ne
l_int|0
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|hlimit_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|hlimit_mutex
)paren
suffix:semicolon
multiline_comment|/* Ugly hack: For SMP, we only want to use one set */
id|r-&gt;u.master
op_assign
id|r
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_void
DECL|function|hashlimit_destroy
id|hashlimit_destroy
c_func
(paren
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchsize
)paren
(brace
r_struct
id|ipt_hashlimit_info
op_star
id|r
op_assign
(paren
r_struct
id|ipt_hashlimit_info
op_star
)paren
id|matchinfo
suffix:semicolon
id|htable_put
c_func
(paren
id|r-&gt;hinfo
)paren
suffix:semicolon
)brace
DECL|variable|ipt_hashlimit
r_static
r_struct
id|ipt_match
id|ipt_hashlimit
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;hashlimit&quot;
comma
dot
id|match
op_assign
id|hashlimit_match
comma
dot
id|checkentry
op_assign
id|hashlimit_checkentry
comma
dot
id|destroy
op_assign
id|hashlimit_destroy
comma
dot
id|me
op_assign
id|THIS_MODULE
)brace
suffix:semicolon
multiline_comment|/* PROC stuff */
DECL|function|dl_seq_start
r_static
r_void
op_star
id|dl_seq_start
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|pde
op_assign
id|s
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|ipt_hashlimit_htable
op_star
id|htable
op_assign
id|pde-&gt;data
suffix:semicolon
r_int
r_int
op_star
id|bucket
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|htable-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
op_ge
id|htable-&gt;cfg.size
)paren
r_return
l_int|NULL
suffix:semicolon
id|bucket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_int
r_int
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bucket
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
op_star
id|bucket
op_assign
op_star
id|pos
suffix:semicolon
r_return
id|bucket
suffix:semicolon
)brace
DECL|function|dl_seq_next
r_static
r_void
op_star
id|dl_seq_next
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|pde
op_assign
id|s
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|ipt_hashlimit_htable
op_star
id|htable
op_assign
id|pde-&gt;data
suffix:semicolon
r_int
r_int
op_star
id|bucket
op_assign
(paren
r_int
r_int
op_star
)paren
id|v
suffix:semicolon
op_star
id|pos
op_assign
op_increment
(paren
op_star
id|bucket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
op_ge
id|htable-&gt;cfg.size
)paren
(brace
id|kfree
c_func
(paren
id|v
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|bucket
suffix:semicolon
)brace
DECL|function|dl_seq_stop
r_static
r_void
id|dl_seq_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|pde
op_assign
id|s
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|ipt_hashlimit_htable
op_star
id|htable
op_assign
id|pde-&gt;data
suffix:semicolon
r_int
r_int
op_star
id|bucket
op_assign
(paren
r_int
r_int
op_star
)paren
id|v
suffix:semicolon
id|kfree
c_func
(paren
id|bucket
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|htable-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|dl_seq_real_show
r_static
r_inline
r_int
id|dl_seq_real_show
c_func
(paren
r_struct
id|dsthash_ent
op_star
id|ent
comma
r_struct
id|seq_file
op_star
id|s
)paren
(brace
multiline_comment|/* recalculate to show accurate numbers */
id|rateinfo_recalc
c_func
(paren
id|ent
comma
id|jiffies
)paren
suffix:semicolon
r_return
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;%ld %u.%u.%u.%u:%u-&gt;%u.%u.%u.%u:%u %u %u %u&bslash;n&quot;
comma
(paren
id|ent-&gt;expires
op_minus
id|jiffies
)paren
op_div
id|HZ
comma
id|NIPQUAD
c_func
(paren
id|ent-&gt;dst.src_ip
)paren
comma
id|ntohs
c_func
(paren
id|ent-&gt;dst.src_port
)paren
comma
id|NIPQUAD
c_func
(paren
id|ent-&gt;dst.dst_ip
)paren
comma
id|ntohs
c_func
(paren
id|ent-&gt;dst.dst_port
)paren
comma
id|ent-&gt;rateinfo.credit
comma
id|ent-&gt;rateinfo.credit_cap
comma
id|ent-&gt;rateinfo.cost
)paren
suffix:semicolon
)brace
DECL|function|dl_seq_show
r_static
r_int
id|dl_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|pde
op_assign
id|s
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|ipt_hashlimit_htable
op_star
id|htable
op_assign
id|pde-&gt;data
suffix:semicolon
r_int
r_int
op_star
id|bucket
op_assign
(paren
r_int
r_int
op_star
)paren
id|v
suffix:semicolon
r_if
c_cond
(paren
id|LIST_FIND_W
c_func
(paren
op_amp
id|htable-&gt;hash
(braket
op_star
id|bucket
)braket
comma
id|dl_seq_real_show
comma
r_struct
id|dsthash_ent
op_star
comma
id|s
)paren
)paren
(brace
multiline_comment|/* buffer was filled and unable to print that tuple */
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dl_seq_ops
r_static
r_struct
id|seq_operations
id|dl_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|dl_seq_start
comma
dot
id|next
op_assign
id|dl_seq_next
comma
dot
id|stop
op_assign
id|dl_seq_stop
comma
dot
id|show
op_assign
id|dl_seq_show
)brace
suffix:semicolon
DECL|function|dl_proc_open
r_static
r_int
id|dl_proc_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|ret
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|dl_seq_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
r_struct
id|seq_file
op_star
id|sf
op_assign
id|file-&gt;private_data
suffix:semicolon
id|sf
op_member_access_from_pointer
r_private
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|dl_file_ops
r_static
r_struct
id|file_operations
id|dl_file_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|dl_proc_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
)brace
suffix:semicolon
DECL|function|init_or_fini
r_static
r_int
id|init_or_fini
c_func
(paren
r_int
id|fini
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fini
)paren
r_goto
id|cleanup
suffix:semicolon
r_if
c_cond
(paren
id|ipt_register_match
c_func
(paren
op_amp
id|ipt_hashlimit
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|cleanup_nothing
suffix:semicolon
)brace
id|hashlimit_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;ipt_hashlimit&quot;
comma
r_sizeof
(paren
r_struct
id|dsthash_ent
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashlimit_cachep
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to create ipt_hashlimit slab cache&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup_unreg_match
suffix:semicolon
)brace
id|hashlimit_procdir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;ipt_hashlimit&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashlimit_procdir
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to create proc dir entry&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup_free_slab
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
id|cleanup
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;ipt_hashlimit&quot;
comma
id|proc_net
)paren
suffix:semicolon
id|cleanup_free_slab
suffix:colon
id|kmem_cache_destroy
c_func
(paren
id|hashlimit_cachep
)paren
suffix:semicolon
id|cleanup_unreg_match
suffix:colon
id|ipt_unregister_match
c_func
(paren
op_amp
id|ipt_hashlimit
)paren
suffix:semicolon
id|cleanup_nothing
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_return
id|init_or_fini
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|init_or_fini
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
eof
