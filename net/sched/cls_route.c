multiline_comment|/*&n; * net/sched/cls_route.c&t;ROUTE4 classifier.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/*&n;   1. For now we assume that route tags &lt; 256.&n;      It allows to use direct table lookups, instead of hash tables.&n;   2. For now we assume that &quot;from TAG&quot; and &quot;fromdev DEV&quot; statements&n;      are mutually  exclusive.&n;   3. &quot;to TAG from ANY&quot; has higher priority, than &quot;to ANY from XXX&quot;&n; */
DECL|struct|route4_fastmap
r_struct
id|route4_fastmap
(brace
DECL|member|filter
r_struct
id|route4_filter
op_star
id|filter
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|iif
r_int
id|iif
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|route4_head
r_struct
id|route4_head
(brace
DECL|member|fastmap
r_struct
id|route4_fastmap
id|fastmap
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|table
r_struct
id|route4_bucket
op_star
id|table
(braket
l_int|256
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|route4_bucket
r_struct
id|route4_bucket
(brace
DECL|member|ht
r_struct
id|route4_filter
op_star
id|ht
(braket
l_int|16
op_plus
l_int|16
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|route4_filter
r_struct
id|route4_filter
(brace
DECL|member|next
r_struct
id|route4_filter
op_star
id|next
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|iif
r_int
id|iif
suffix:semicolon
DECL|member|res
r_struct
id|tcf_result
id|res
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
DECL|member|police
r_struct
id|tcf_police
op_star
id|police
suffix:semicolon
macro_line|#endif
DECL|member|handle
id|u32
id|handle
suffix:semicolon
DECL|member|bkt
r_struct
id|route4_bucket
op_star
id|bkt
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ROUTE4_FAILURE
mdefine_line|#define ROUTE4_FAILURE ((struct route4_filter*)(-1L))
DECL|function|route4_fastmap_hash
r_static
id|__inline__
r_int
id|route4_fastmap_hash
c_func
(paren
id|u32
id|id
comma
r_int
id|iif
)paren
(brace
r_return
id|id
op_amp
l_int|0xF
suffix:semicolon
)brace
DECL|function|route4_reset_fastmap
r_static
r_void
id|route4_reset_fastmap
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|route4_head
op_star
id|head
comma
id|u32
id|id
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|memset
c_func
(paren
id|head-&gt;fastmap
comma
l_int|0
comma
r_sizeof
(paren
id|head-&gt;fastmap
)paren
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
)brace
r_static
r_void
id|__inline__
DECL|function|route4_set_fastmap
id|route4_set_fastmap
c_func
(paren
r_struct
id|route4_head
op_star
id|head
comma
id|u32
id|id
comma
r_int
id|iif
comma
r_struct
id|route4_filter
op_star
id|f
)paren
(brace
r_int
id|h
op_assign
id|route4_fastmap_hash
c_func
(paren
id|id
comma
id|iif
)paren
suffix:semicolon
id|head-&gt;fastmap
(braket
id|h
)braket
dot
id|id
op_assign
id|id
suffix:semicolon
id|head-&gt;fastmap
(braket
id|h
)braket
dot
id|iif
op_assign
id|iif
suffix:semicolon
id|head-&gt;fastmap
(braket
id|h
)braket
dot
id|filter
op_assign
id|f
suffix:semicolon
)brace
DECL|function|route4_hash_to
r_static
id|__inline__
r_int
id|route4_hash_to
c_func
(paren
id|u32
id|id
)paren
(brace
r_return
id|id
op_amp
l_int|0xFF
suffix:semicolon
)brace
DECL|function|route4_hash_from
r_static
id|__inline__
r_int
id|route4_hash_from
c_func
(paren
id|u32
id|id
)paren
(brace
r_return
(paren
id|id
op_rshift
l_int|16
)paren
op_amp
l_int|0xF
suffix:semicolon
)brace
DECL|function|route4_hash_iif
r_static
id|__inline__
r_int
id|route4_hash_iif
c_func
(paren
r_int
id|iif
)paren
(brace
r_return
l_int|16
op_plus
(paren
(paren
id|iif
op_rshift
l_int|16
)paren
op_amp
l_int|0xF
)paren
suffix:semicolon
)brace
DECL|function|route4_hash_wild
r_static
id|__inline__
r_int
id|route4_hash_wild
c_func
(paren
r_void
)paren
(brace
r_return
l_int|32
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_POLICE
DECL|macro|IF_ROUTE_POLICE
mdefine_line|#define IF_ROUTE_POLICE &bslash;&n;if (f-&gt;police) { &bslash;&n;&t;int pol_res = tcf_police(skb, f-&gt;police); &bslash;&n;&t;if (pol_res &gt;= 0) return pol_res; &bslash;&n;&t;dont_cache = 1; &bslash;&n;&t;continue; &bslash;&n;} &bslash;&n;if (!dont_cache)
macro_line|#else
DECL|macro|IF_ROUTE_POLICE
mdefine_line|#define IF_ROUTE_POLICE
macro_line|#endif
DECL|function|route4_classify
r_static
r_int
id|route4_classify
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_result
op_star
id|res
)paren
(brace
r_struct
id|route4_head
op_star
id|head
op_assign
(paren
r_struct
id|route4_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
r_struct
id|route4_bucket
op_star
id|b
suffix:semicolon
r_struct
id|route4_filter
op_star
id|f
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_int
id|dont_cache
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|u32
id|id
comma
id|h
suffix:semicolon
r_int
id|iif
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dst
op_assign
id|skb-&gt;dst
)paren
op_eq
l_int|NULL
)paren
r_goto
id|failure
suffix:semicolon
id|id
op_assign
id|dst-&gt;tclassid
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
r_goto
id|old_method
suffix:semicolon
id|iif
op_assign
(paren
(paren
r_struct
id|rtable
op_star
)paren
id|dst
)paren
op_member_access_from_pointer
id|fl.iif
suffix:semicolon
id|h
op_assign
id|route4_fastmap_hash
c_func
(paren
id|id
comma
id|iif
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
id|head-&gt;fastmap
(braket
id|h
)braket
dot
id|id
op_logical_and
id|iif
op_eq
id|head-&gt;fastmap
(braket
id|h
)braket
dot
id|iif
op_logical_and
(paren
id|f
op_assign
id|head-&gt;fastmap
(braket
id|h
)braket
dot
id|filter
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|f
op_eq
id|ROUTE4_FAILURE
)paren
r_goto
id|failure
suffix:semicolon
op_star
id|res
op_assign
id|f-&gt;res
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|h
op_assign
id|route4_hash_to
c_func
(paren
id|id
)paren
suffix:semicolon
id|restart
suffix:colon
r_if
c_cond
(paren
(paren
id|b
op_assign
id|head-&gt;table
(braket
id|h
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|f
op_assign
id|b-&gt;ht
(braket
id|route4_hash_from
c_func
(paren
id|id
)paren
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;id
op_eq
id|id
)paren
(brace
op_star
id|res
op_assign
id|f-&gt;res
suffix:semicolon
id|IF_ROUTE_POLICE
id|route4_set_fastmap
c_func
(paren
id|head
comma
id|id
comma
id|iif
comma
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|f
op_assign
id|b-&gt;ht
(braket
id|route4_hash_iif
c_func
(paren
id|iif
)paren
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;iif
op_eq
id|iif
)paren
(brace
op_star
id|res
op_assign
id|f-&gt;res
suffix:semicolon
id|IF_ROUTE_POLICE
id|route4_set_fastmap
c_func
(paren
id|head
comma
id|id
comma
id|iif
comma
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|f
op_assign
id|b-&gt;ht
(braket
id|route4_hash_wild
c_func
(paren
)paren
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
op_star
id|res
op_assign
id|f-&gt;res
suffix:semicolon
id|IF_ROUTE_POLICE
id|route4_set_fastmap
c_func
(paren
id|head
comma
id|id
comma
id|iif
comma
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|h
OL
l_int|256
)paren
(brace
id|h
op_assign
l_int|256
suffix:semicolon
id|id
op_and_assign
op_complement
l_int|0xFFFF
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
op_logical_neg
id|dont_cache
)paren
macro_line|#endif
id|route4_set_fastmap
c_func
(paren
id|head
comma
id|id
comma
id|iif
comma
id|ROUTE4_FAILURE
)paren
suffix:semicolon
id|failure
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
id|old_method
suffix:colon
r_if
c_cond
(paren
id|id
op_logical_and
(paren
id|TC_H_MAJ
c_func
(paren
id|id
)paren
op_eq
l_int|0
op_logical_or
op_logical_neg
(paren
id|TC_H_MAJ
c_func
(paren
id|id
op_xor
id|tp-&gt;q-&gt;handle
)paren
)paren
)paren
)paren
(brace
id|res-&gt;classid
op_assign
id|id
suffix:semicolon
id|res
op_member_access_from_pointer
r_class
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|to_hash
r_static
id|u32
id|to_hash
c_func
(paren
id|u32
id|id
)paren
(brace
id|u32
id|h
op_assign
id|id
op_amp
l_int|0xFF
suffix:semicolon
r_if
c_cond
(paren
id|id
op_amp
l_int|0x8000
)paren
id|h
op_add_assign
l_int|256
suffix:semicolon
r_return
id|h
suffix:semicolon
)brace
DECL|function|from_hash
r_static
id|u32
id|from_hash
c_func
(paren
id|u32
id|id
)paren
(brace
id|id
op_and_assign
l_int|0xFFFF
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
l_int|0xFFFF
)paren
r_return
l_int|32
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|id
op_amp
l_int|0x8000
)paren
)paren
(brace
r_if
c_cond
(paren
id|id
OG
l_int|255
)paren
r_return
l_int|256
suffix:semicolon
r_return
id|id
op_amp
l_int|0xF
suffix:semicolon
)brace
r_return
l_int|16
op_plus
(paren
id|id
op_amp
l_int|0xF
)paren
suffix:semicolon
)brace
DECL|function|route4_get
r_static
r_int
r_int
id|route4_get
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
id|u32
id|handle
)paren
(brace
r_struct
id|route4_head
op_star
id|head
op_assign
(paren
r_struct
id|route4_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_struct
id|route4_bucket
op_star
id|b
suffix:semicolon
r_struct
id|route4_filter
op_star
id|f
suffix:semicolon
r_int
id|h1
comma
id|h2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head
)paren
r_return
l_int|0
suffix:semicolon
id|h1
op_assign
id|to_hash
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h1
OG
l_int|256
)paren
r_return
l_int|0
suffix:semicolon
id|h2
op_assign
id|from_hash
c_func
(paren
id|handle
op_rshift
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h2
OG
l_int|32
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|b
op_assign
id|head-&gt;table
(braket
id|h1
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|f
op_assign
id|b-&gt;ht
(braket
id|h2
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
r_if
c_cond
(paren
id|f-&gt;handle
op_eq
id|handle
)paren
r_return
(paren
r_int
r_int
)paren
id|f
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|route4_put
r_static
r_void
id|route4_put
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|f
)paren
(brace
)brace
DECL|function|route4_init
r_static
r_int
id|route4_init
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|route4_destroy
r_static
r_void
id|route4_destroy
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
r_struct
id|route4_head
op_star
id|head
op_assign
id|xchg
c_func
(paren
op_amp
id|tp-&gt;root
comma
l_int|NULL
)paren
suffix:semicolon
r_int
id|h1
comma
id|h2
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|h1
op_assign
l_int|0
suffix:semicolon
id|h1
op_le
l_int|256
suffix:semicolon
id|h1
op_increment
)paren
(brace
r_struct
id|route4_bucket
op_star
id|b
suffix:semicolon
r_if
c_cond
(paren
(paren
id|b
op_assign
id|head-&gt;table
(braket
id|h1
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|h2
op_assign
l_int|0
suffix:semicolon
id|h2
op_le
l_int|32
suffix:semicolon
id|h2
op_increment
)paren
(brace
r_struct
id|route4_filter
op_star
id|f
suffix:semicolon
r_while
c_loop
(paren
(paren
id|f
op_assign
id|b-&gt;ht
(braket
id|h2
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|cl
suffix:semicolon
id|b-&gt;ht
(braket
id|h2
)braket
op_assign
id|f-&gt;next
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cl
op_assign
id|__cls_set_class
c_func
(paren
op_amp
id|f-&gt;res
dot
r_class
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|unbind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|cl
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
id|tcf_police_release
c_func
(paren
id|f-&gt;police
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
macro_line|#endif
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|head
)paren
suffix:semicolon
)brace
DECL|function|route4_delete
r_static
r_int
id|route4_delete
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|route4_head
op_star
id|head
op_assign
(paren
r_struct
id|route4_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_struct
id|route4_filter
op_star
op_star
id|fp
comma
op_star
id|f
op_assign
(paren
r_struct
id|route4_filter
op_star
)paren
id|arg
suffix:semicolon
r_int
id|h
op_assign
l_int|0
suffix:semicolon
r_struct
id|route4_bucket
op_star
id|b
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head
op_logical_or
op_logical_neg
id|f
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|h
op_assign
id|f-&gt;handle
suffix:semicolon
id|b
op_assign
id|f-&gt;bkt
suffix:semicolon
r_for
c_loop
(paren
id|fp
op_assign
op_amp
id|b-&gt;ht
(braket
id|from_hash
c_func
(paren
id|h
op_rshift
l_int|16
)paren
)braket
suffix:semicolon
op_star
id|fp
suffix:semicolon
id|fp
op_assign
op_amp
(paren
op_star
id|fp
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
op_star
id|fp
op_eq
id|f
)paren
(brace
r_int
r_int
id|cl
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
op_star
id|fp
op_assign
id|f-&gt;next
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|route4_reset_fastmap
c_func
(paren
id|tp-&gt;q-&gt;dev
comma
id|head
comma
id|f-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cl
op_assign
id|cls_set_class
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;res
dot
r_class
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|unbind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|cl
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
id|tcf_police_release
c_func
(paren
id|f-&gt;police
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
macro_line|#endif
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
multiline_comment|/* Strip tree */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|32
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|b-&gt;ht
(braket
id|i
)braket
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* OK, session has no flows */
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|head-&gt;table
(braket
id|to_hash
c_func
(paren
id|h
)paren
)braket
op_assign
l_int|NULL
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|b
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|route4_change
r_static
r_int
id|route4_change
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|base
comma
id|u32
id|handle
comma
r_struct
id|rtattr
op_star
op_star
id|tca
comma
r_int
r_int
op_star
id|arg
)paren
(brace
r_struct
id|route4_head
op_star
id|head
op_assign
id|tp-&gt;root
suffix:semicolon
r_struct
id|route4_filter
op_star
id|f
comma
op_star
id|f1
comma
op_star
op_star
id|ins_f
suffix:semicolon
r_struct
id|route4_bucket
op_star
id|b
suffix:semicolon
r_struct
id|rtattr
op_star
id|opt
op_assign
id|tca
(braket
id|TCA_OPTIONS
op_minus
l_int|1
)braket
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_ROUTE4_MAX
)braket
suffix:semicolon
r_int
id|h1
comma
id|h2
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
)paren
r_return
id|handle
ques
c_cond
op_minus
id|EINVAL
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_ROUTE4_MAX
comma
id|RTA_DATA
c_func
(paren
id|opt
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|opt
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|f
op_assign
(paren
r_struct
id|route4_filter
op_star
)paren
op_star
id|arg
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Node exists: adjust only classid */
r_if
c_cond
(paren
id|f-&gt;handle
op_ne
id|handle
op_logical_and
id|handle
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_CLASSID
op_minus
l_int|1
)braket
)paren
(brace
r_int
r_int
id|cl
suffix:semicolon
id|f-&gt;res.classid
op_assign
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_CLASSID
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|cl
op_assign
id|cls_set_class
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;res
dot
r_class
comma
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|bind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|base
comma
id|f-&gt;res.classid
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
)paren
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|unbind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|cl
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_POLICE
op_minus
l_int|1
)braket
)paren
(brace
r_struct
id|tcf_police
op_star
id|police
op_assign
id|tcf_police_locate
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_POLICE
op_minus
l_int|1
)braket
comma
id|tca
(braket
id|TCA_RATE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|police
op_assign
id|xchg
c_func
(paren
op_amp
id|f-&gt;police
comma
id|police
)paren
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tcf_police_release
c_func
(paren
id|police
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Now more serious part... */
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
(brace
id|head
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|route4_head
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
id|memset
c_func
(paren
id|head
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|route4_head
)paren
)paren
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tp-&gt;root
op_assign
id|head
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
id|f
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|route4_filter
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|f-&gt;handle
op_assign
l_int|0x8000
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_TO
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
id|handle
op_amp
l_int|0x8000
)paren
r_goto
id|errout
suffix:semicolon
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_TO
op_minus
l_int|1
)braket
)paren
OL
l_int|4
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;id
op_assign
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_TO
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;id
OG
l_int|0xFF
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;handle
op_assign
id|f-&gt;id
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_FROM
op_minus
l_int|1
)braket
)paren
(brace
id|u32
id|sid
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_IIF
op_minus
l_int|1
)braket
)paren
r_goto
id|errout
suffix:semicolon
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_FROM
op_minus
l_int|1
)braket
)paren
OL
l_int|4
)paren
r_goto
id|errout
suffix:semicolon
id|sid
op_assign
(paren
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_FROM
op_minus
l_int|1
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sid
OG
l_int|0xFF
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;handle
op_or_assign
id|sid
op_lshift
l_int|16
suffix:semicolon
id|f-&gt;id
op_or_assign
id|sid
op_lshift
l_int|16
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_IIF
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_IIF
op_minus
l_int|1
)braket
)paren
OL
l_int|4
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;iif
op_assign
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_IIF
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;iif
OG
l_int|0x7FFF
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;handle
op_or_assign
(paren
id|f-&gt;iif
op_or
l_int|0x8000
)paren
op_lshift
l_int|16
suffix:semicolon
)brace
r_else
id|f-&gt;handle
op_or_assign
l_int|0xFFFF
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|handle
)paren
(brace
id|f-&gt;handle
op_or_assign
id|handle
op_amp
l_int|0x7F00
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;handle
op_ne
id|handle
)paren
r_goto
id|errout
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_CLASSID
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_CLASSID
op_minus
l_int|1
)braket
)paren
OL
l_int|4
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;res.classid
op_assign
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_CLASSID
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|h1
op_assign
id|to_hash
c_func
(paren
id|f-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|b
op_assign
id|head-&gt;table
(braket
id|h1
)braket
)paren
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|ENOBUFS
suffix:semicolon
id|b
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|route4_bucket
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_eq
l_int|NULL
)paren
r_goto
id|errout
suffix:semicolon
id|memset
c_func
(paren
id|b
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|b
)paren
)paren
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|head-&gt;table
(braket
id|h1
)braket
op_assign
id|b
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
id|f-&gt;bkt
op_assign
id|b
suffix:semicolon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
id|h2
op_assign
id|from_hash
c_func
(paren
id|f-&gt;handle
op_rshift
l_int|16
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ins_f
op_assign
op_amp
id|b-&gt;ht
(braket
id|h2
)braket
suffix:semicolon
(paren
id|f1
op_assign
op_star
id|ins_f
)paren
op_ne
l_int|NULL
suffix:semicolon
id|ins_f
op_assign
op_amp
id|f1-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;handle
OL
id|f1-&gt;handle
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|f1-&gt;handle
op_eq
id|f-&gt;handle
)paren
r_goto
id|errout
suffix:semicolon
)brace
id|cls_set_class
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;res
dot
r_class
comma
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|bind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|base
comma
id|f-&gt;res.classid
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|tb
(braket
id|TCA_ROUTE4_POLICE
op_minus
l_int|1
)braket
)paren
id|f-&gt;police
op_assign
id|tcf_police_locate
c_func
(paren
id|tb
(braket
id|TCA_ROUTE4_POLICE
op_minus
l_int|1
)braket
comma
id|tca
(braket
id|TCA_RATE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
id|f-&gt;next
op_assign
id|f1
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
op_star
id|ins_f
op_assign
id|f
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|route4_reset_fastmap
c_func
(paren
id|tp-&gt;q-&gt;dev
comma
id|head
comma
id|f-&gt;id
)paren
suffix:semicolon
op_star
id|arg
op_assign
(paren
r_int
r_int
)paren
id|f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|errout
suffix:colon
r_if
c_cond
(paren
id|f
)paren
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|route4_walk
r_static
r_void
id|route4_walk
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_walker
op_star
id|arg
)paren
(brace
r_struct
id|route4_head
op_star
id|head
op_assign
id|tp-&gt;root
suffix:semicolon
r_int
id|h
comma
id|h1
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
id|arg-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|arg-&gt;stop
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
op_le
l_int|256
suffix:semicolon
id|h
op_increment
)paren
(brace
r_struct
id|route4_bucket
op_star
id|b
op_assign
id|head-&gt;table
(braket
id|h
)braket
suffix:semicolon
r_if
c_cond
(paren
id|b
)paren
(brace
r_for
c_loop
(paren
id|h1
op_assign
l_int|0
suffix:semicolon
id|h1
op_le
l_int|32
suffix:semicolon
id|h1
op_increment
)paren
(brace
r_struct
id|route4_filter
op_star
id|f
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|b-&gt;ht
(braket
id|h1
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|arg-&gt;count
OL
id|arg-&gt;skip
)paren
(brace
id|arg-&gt;count
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
op_member_access_from_pointer
id|fn
c_func
(paren
id|tp
comma
(paren
r_int
r_int
)paren
id|f
comma
id|arg
)paren
OL
l_int|0
)paren
(brace
id|arg-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|arg-&gt;count
op_increment
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
DECL|function|route4_dump
r_static
r_int
id|route4_dump
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|fh
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcmsg
op_star
id|t
)paren
(brace
r_struct
id|route4_filter
op_star
id|f
op_assign
(paren
r_struct
id|route4_filter
op_star
)paren
id|fh
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|rtattr
op_star
id|rta
suffix:semicolon
id|u32
id|id
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
r_return
id|skb-&gt;len
suffix:semicolon
id|t-&gt;tcm_handle
op_assign
id|f-&gt;handle
suffix:semicolon
id|rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|b
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_OPTIONS
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|f-&gt;handle
op_amp
l_int|0x8000
)paren
)paren
(brace
id|id
op_assign
id|f-&gt;id
op_amp
l_int|0xFF
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_ROUTE4_TO
comma
r_sizeof
(paren
id|id
)paren
comma
op_amp
id|id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|f-&gt;handle
op_amp
l_int|0x80000000
)paren
(brace
r_if
c_cond
(paren
(paren
id|f-&gt;handle
op_rshift
l_int|16
)paren
op_ne
l_int|0xFFFF
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_ROUTE4_IIF
comma
r_sizeof
(paren
id|f-&gt;iif
)paren
comma
op_amp
id|f-&gt;iif
)paren
suffix:semicolon
)brace
r_else
(brace
id|id
op_assign
id|f-&gt;id
op_rshift
l_int|16
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_ROUTE4_FROM
comma
r_sizeof
(paren
id|id
)paren
comma
op_amp
id|id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|f-&gt;res.classid
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_ROUTE4_CLASSID
comma
l_int|4
comma
op_amp
id|f-&gt;res.classid
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|f-&gt;police
)paren
(brace
r_struct
id|rtattr
op_star
id|p_rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_ROUTE4_POLICE
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcf_police_dump
c_func
(paren
id|skb
comma
id|f-&gt;police
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
id|p_rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|p_rta
suffix:semicolon
)brace
macro_line|#endif
id|rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|f-&gt;police
)paren
(brace
r_if
c_cond
(paren
id|qdisc_copy_stats
c_func
(paren
id|skb
comma
op_amp
id|f-&gt;police-&gt;stats
)paren
)paren
r_goto
id|rtattr_failure
suffix:semicolon
)brace
macro_line|#endif
r_return
id|skb-&gt;len
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
id|b
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|cls_route4_ops
r_static
r_struct
id|tcf_proto_ops
id|cls_route4_ops
op_assign
(brace
dot
id|next
op_assign
l_int|NULL
comma
dot
id|kind
op_assign
l_string|&quot;route&quot;
comma
dot
id|classify
op_assign
id|route4_classify
comma
dot
id|init
op_assign
id|route4_init
comma
dot
id|destroy
op_assign
id|route4_destroy
comma
dot
id|get
op_assign
id|route4_get
comma
dot
id|put
op_assign
id|route4_put
comma
dot
id|change
op_assign
id|route4_change
comma
dot
r_delete
op_assign
id|route4_delete
comma
dot
id|walk
op_assign
id|route4_walk
comma
dot
id|dump
op_assign
id|route4_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init_route4
r_static
r_int
id|__init
id|init_route4
c_func
(paren
r_void
)paren
(brace
r_return
id|register_tcf_proto_ops
c_func
(paren
op_amp
id|cls_route4_ops
)paren
suffix:semicolon
)brace
DECL|function|exit_route4
r_static
r_void
id|__exit
id|exit_route4
c_func
(paren
r_void
)paren
(brace
id|unregister_tcf_proto_ops
c_func
(paren
op_amp
id|cls_route4_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_route4
)paren
id|module_exit
c_func
(paren
id|exit_route4
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
