multiline_comment|/*&n; * net/dst.h&t;Protocol independent destination cache definitions.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; */
macro_line|#ifndef _NET_DST_H
DECL|macro|_NET_DST_H
mdefine_line|#define _NET_DST_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;net/neighbour.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * 0 - no debugging messages&n; * 1 - rare events and bugs (default)&n; * 2 - trace mode.&n; */
DECL|macro|RT_CACHE_DEBUG
mdefine_line|#define RT_CACHE_DEBUG&t;&t;0
DECL|macro|DST_GC_MIN
mdefine_line|#define DST_GC_MIN&t;(HZ/10)
DECL|macro|DST_GC_INC
mdefine_line|#define DST_GC_INC&t;(HZ/2)
DECL|macro|DST_GC_MAX
mdefine_line|#define DST_GC_MAX&t;(120*HZ)
multiline_comment|/* Each dst_entry has reference count and sits in some parent list(s).&n; * When it is removed from parent list, it is &quot;freed&quot; (dst_free).&n; * After this it enters dead state (dst-&gt;obsolete &gt; 0) and if its refcnt&n; * is zero, it can be destroyed immediately, otherwise it is added&n; * to gc list and garbage collector periodically checks the refcnt.&n; */
r_struct
id|sk_buff
suffix:semicolon
DECL|struct|dst_entry
r_struct
id|dst_entry
(brace
DECL|member|next
r_struct
id|dst_entry
op_star
id|next
suffix:semicolon
DECL|member|__refcnt
id|atomic_t
id|__refcnt
suffix:semicolon
multiline_comment|/* client references&t;*/
DECL|member|__use
r_int
id|__use
suffix:semicolon
DECL|member|child
r_struct
id|dst_entry
op_star
id|child
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|obsolete
r_int
id|obsolete
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|macro|DST_HOST
mdefine_line|#define DST_HOST&t;&t;1
DECL|macro|DST_NOXFRM
mdefine_line|#define DST_NOXFRM&t;&t;2
DECL|macro|DST_NOPOLICY
mdefine_line|#define DST_NOPOLICY&t;&t;4
DECL|macro|DST_NOHASH
mdefine_line|#define DST_NOHASH&t;&t;8
DECL|member|lastuse
r_int
r_int
id|lastuse
suffix:semicolon
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
DECL|member|header_len
r_int
r_int
id|header_len
suffix:semicolon
multiline_comment|/* more space at head required */
DECL|member|trailer_len
r_int
r_int
id|trailer_len
suffix:semicolon
multiline_comment|/* space to reserve at tail */
DECL|member|metrics
id|u32
id|metrics
(braket
id|RTAX_MAX
)braket
suffix:semicolon
DECL|member|path
r_struct
id|dst_entry
op_star
id|path
suffix:semicolon
DECL|member|rate_last
r_int
r_int
id|rate_last
suffix:semicolon
multiline_comment|/* rate limiting for ICMP */
DECL|member|rate_tokens
r_int
r_int
id|rate_tokens
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|neighbour
r_struct
id|neighbour
op_star
id|neighbour
suffix:semicolon
DECL|member|hh
r_struct
id|hh_cache
op_star
id|hh
suffix:semicolon
DECL|member|xfrm
r_struct
id|xfrm_state
op_star
id|xfrm
suffix:semicolon
DECL|member|input
r_int
(paren
op_star
id|input
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|output
r_int
(paren
op_star
id|output
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
DECL|member|tclassid
id|__u32
id|tclassid
suffix:semicolon
macro_line|#endif
DECL|member|ops
r_struct
id|dst_ops
op_star
id|ops
suffix:semicolon
DECL|member|rcu_head
r_struct
id|rcu_head
id|rcu_head
suffix:semicolon
DECL|member|info
r_char
id|info
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dst_ops
r_struct
id|dst_ops
(brace
DECL|member|family
r_int
r_int
id|family
suffix:semicolon
DECL|member|protocol
r_int
r_int
id|protocol
suffix:semicolon
DECL|member|gc_thresh
r_int
id|gc_thresh
suffix:semicolon
DECL|member|gc
r_int
(paren
op_star
id|gc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|check
r_struct
id|dst_entry
op_star
(paren
op_star
id|check
)paren
(paren
r_struct
id|dst_entry
op_star
comma
id|__u32
id|cookie
)paren
suffix:semicolon
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|dst_entry
op_star
)paren
suffix:semicolon
DECL|member|ifdown
r_void
(paren
op_star
id|ifdown
)paren
(paren
r_struct
id|dst_entry
op_star
comma
r_int
id|how
)paren
suffix:semicolon
DECL|member|negative_advice
r_struct
id|dst_entry
op_star
(paren
op_star
id|negative_advice
)paren
(paren
r_struct
id|dst_entry
op_star
)paren
suffix:semicolon
DECL|member|link_failure
r_void
(paren
op_star
id|link_failure
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|update_pmtu
r_void
(paren
op_star
id|update_pmtu
)paren
(paren
r_struct
id|dst_entry
op_star
id|dst
comma
id|u32
id|mtu
)paren
suffix:semicolon
DECL|member|get_mss
r_int
(paren
op_star
id|get_mss
)paren
(paren
r_struct
id|dst_entry
op_star
id|dst
comma
id|u32
id|mtu
)paren
suffix:semicolon
DECL|member|entry_size
r_int
id|entry_size
suffix:semicolon
DECL|member|entries
id|atomic_t
id|entries
suffix:semicolon
DECL|member|kmem_cachep
id|kmem_cache_t
op_star
id|kmem_cachep
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_static
r_inline
id|u32
DECL|function|dst_metric
id|dst_metric
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
comma
r_int
id|metric
)paren
(brace
r_return
id|dst-&gt;metrics
(braket
id|metric
op_minus
l_int|1
)braket
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|dst_path_metric
id|dst_path_metric
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
comma
r_int
id|metric
)paren
(brace
r_return
id|dst-&gt;path-&gt;metrics
(braket
id|metric
op_minus
l_int|1
)braket
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|dst_pmtu
id|dst_pmtu
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
id|u32
id|mtu
op_assign
id|dst_path_metric
c_func
(paren
id|dst
comma
id|RTAX_MTU
)paren
suffix:semicolon
multiline_comment|/* Yes, _exactly_. This is paranoia. */
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_return
id|mtu
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dst_metric_locked
id|dst_metric_locked
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
comma
r_int
id|metric
)paren
(brace
r_return
id|dst_metric
c_func
(paren
id|dst
comma
id|RTAX_LOCK
)paren
op_amp
(paren
l_int|1
op_lshift
id|metric
)paren
suffix:semicolon
)brace
DECL|function|dst_hold
r_static
r_inline
r_void
id|dst_hold
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|dst_clone
r_struct
id|dst_entry
op_star
id|dst_clone
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|dst
)paren
id|atomic_inc
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
r_static
r_inline
DECL|function|dst_release
r_void
id|dst_release
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|dst
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;BUG: dst underflow %d: %p&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
comma
id|current_text_addr
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Children define the path of the packet through the&n; * Linux networking.  Thus, destinations are stackable.&n; */
DECL|function|dst_pop
r_static
r_inline
r_struct
id|dst_entry
op_star
id|dst_pop
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_struct
id|dst_entry
op_star
id|child
op_assign
id|dst_clone
c_func
(paren
id|dst-&gt;child
)paren
suffix:semicolon
id|dst_release
c_func
(paren
id|dst
)paren
suffix:semicolon
r_return
id|child
suffix:semicolon
)brace
r_extern
r_void
op_star
id|dst_alloc
c_func
(paren
r_struct
id|dst_ops
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_void
id|__dst_free
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
suffix:semicolon
r_extern
r_struct
id|dst_entry
op_star
id|dst_destroy
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
suffix:semicolon
DECL|function|dst_free
r_static
r_inline
r_void
id|dst_free
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|dst-&gt;obsolete
OG
l_int|1
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|dst-&gt;__refcnt
)paren
)paren
(brace
id|dst
op_assign
id|dst_destroy
c_func
(paren
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst
)paren
r_return
suffix:semicolon
)brace
id|__dst_free
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
DECL|function|dst_confirm
r_static
r_inline
r_void
id|dst_confirm
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|dst
)paren
id|neigh_confirm
c_func
(paren
id|dst-&gt;neighbour
)paren
suffix:semicolon
)brace
DECL|function|dst_negative_advice
r_static
r_inline
r_void
id|dst_negative_advice
c_func
(paren
r_struct
id|dst_entry
op_star
op_star
id|dst_p
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
op_star
id|dst_p
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_logical_and
id|dst-&gt;ops-&gt;negative_advice
)paren
op_star
id|dst_p
op_assign
id|dst-&gt;ops
op_member_access_from_pointer
id|negative_advice
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
DECL|function|dst_link_failure
r_static
r_inline
r_void
id|dst_link_failure
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_logical_and
id|dst-&gt;ops
op_logical_and
id|dst-&gt;ops-&gt;link_failure
)paren
id|dst-&gt;ops
op_member_access_from_pointer
id|link_failure
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dst_set_expires
r_static
r_inline
r_void
id|dst_set_expires
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
comma
r_int
id|timeout
)paren
(brace
r_int
r_int
id|expires
op_assign
id|jiffies
op_plus
id|timeout
suffix:semicolon
r_if
c_cond
(paren
id|expires
op_eq
l_int|0
)paren
id|expires
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;expires
op_eq
l_int|0
op_logical_or
id|time_before
c_func
(paren
id|expires
comma
id|dst-&gt;expires
)paren
)paren
id|dst-&gt;expires
op_assign
id|expires
suffix:semicolon
)brace
multiline_comment|/* Output packet to network from transport.  */
DECL|function|dst_output
r_static
r_inline
r_int
id|dst_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|err
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|err
op_assign
id|skb-&gt;dst
op_member_access_from_pointer
id|output
c_func
(paren
op_amp
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|err
op_eq
l_int|0
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
op_ne
id|NET_XMIT_BYPASS
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
)brace
multiline_comment|/* Input packet from network to transport.  */
DECL|function|dst_input
r_static
r_inline
r_int
id|dst_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|err
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|err
op_assign
id|skb-&gt;dst
op_member_access_from_pointer
id|input
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|err
op_eq
l_int|0
)paren
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* Oh, Jamal... Seems, I will not forgive you this mess. :-) */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
op_ne
id|NET_XMIT_BYPASS
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
)brace
r_extern
r_void
id|dst_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|flowi
suffix:semicolon
macro_line|#ifndef CONFIG_XFRM
DECL|function|xfrm_lookup
r_static
r_inline
r_int
id|xfrm_lookup
c_func
(paren
r_struct
id|dst_entry
op_star
op_star
id|dst_p
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
r_extern
r_int
id|xfrm_lookup
c_func
(paren
r_struct
id|dst_entry
op_star
op_star
id|dst_p
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif /* _NET_DST_H */
eof
