multiline_comment|/* net/sched/sch_dsmark.c - Differentiated Services field marker */
multiline_comment|/* Written 1998-2000 by Werner Almesberger, EPFL ICA */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt; /* for pkt_sched */
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;net/dsfield.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#if 1 /* control */
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
macro_line|#if 0 /* data */
mdefine_line|#define D2PRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|D2PRINTK
mdefine_line|#define D2PRINTK(format,args...)
macro_line|#endif
DECL|macro|PRIV
mdefine_line|#define PRIV(sch) qdisc_priv(sch)
multiline_comment|/*&n; * classid&t;class&t;&t;marking&n; * -------&t;-----&t;&t;-------&n; *   n/a&t;  0&t;&t;n/a&n; *   x:0&t;  1&t;&t;use entry [0]&n; *   ...&t; ...&t;&t;...&n; *   x:y y&gt;0&t; y+1&t;&t;use entry [y]&n; *   ...&t; ...&t;&t;...&n; * x:indices-1&t;indices&t;&t;use entry [indices-1]&n; *   ...&t; ...&t;&t;...&n; *   x:y&t; y+1&t;&t;use entry [y &amp; (indices-1)]&n; *   ...&t; ...&t;&t;...&n; * 0xffff&t;0x10000&t;&t;use entry [indices-1]&n; */
DECL|macro|NO_DEFAULT_INDEX
mdefine_line|#define NO_DEFAULT_INDEX&t;(1 &lt;&lt; 16)
DECL|struct|dsmark_qdisc_data
r_struct
id|dsmark_qdisc_data
(brace
DECL|member|q
r_struct
id|Qdisc
op_star
id|q
suffix:semicolon
DECL|member|filter_list
r_struct
id|tcf_proto
op_star
id|filter_list
suffix:semicolon
DECL|member|mask
id|__u8
op_star
id|mask
suffix:semicolon
multiline_comment|/* &quot;owns&quot; the array */
DECL|member|value
id|__u8
op_star
id|value
suffix:semicolon
DECL|member|indices
id|__u16
id|indices
suffix:semicolon
DECL|member|default_index
id|__u32
id|default_index
suffix:semicolon
multiline_comment|/* index range is 0...0xffff */
DECL|member|set_tc_index
r_int
id|set_tc_index
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ------------------------- Class/flow operations ------------------------- */
DECL|function|dsmark_graft
r_static
r_int
id|dsmark_graft
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_int
r_int
id|arg
comma
r_struct
id|Qdisc
op_star
r_new
comma
r_struct
id|Qdisc
op_star
op_star
id|old
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_graft(sch %p,[qdisc %p],new %p,old %p)&bslash;n&quot;
comma
id|sch
comma
id|p
comma
r_new
comma
id|old
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_new
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
id|sch_tree_lock
c_func
(paren
id|sch
)paren
suffix:semicolon
op_star
id|old
op_assign
id|xchg
c_func
(paren
op_amp
id|p-&gt;q
comma
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|old
)paren
id|qdisc_reset
c_func
(paren
op_star
id|old
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_assign
l_int|0
suffix:semicolon
id|sch_tree_unlock
c_func
(paren
id|sch
)paren
suffix:semicolon
multiline_comment|/* @@@ move up ? */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsmark_leaf
r_static
r_struct
id|Qdisc
op_star
id|dsmark_leaf
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|p-&gt;q
suffix:semicolon
)brace
DECL|function|dsmark_get
r_static
r_int
r_int
id|dsmark_get
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
id|u32
id|classid
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_get(sch %p,[qdisc %p],classid %x)&bslash;n&quot;
comma
id|sch
comma
id|p
comma
id|classid
)paren
suffix:semicolon
r_return
id|TC_H_MIN
c_func
(paren
id|classid
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|dsmark_bind_filter
r_static
r_int
r_int
id|dsmark_bind_filter
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_int
r_int
id|parent
comma
id|u32
id|classid
)paren
(brace
r_return
id|dsmark_get
c_func
(paren
id|sch
comma
id|classid
)paren
suffix:semicolon
)brace
DECL|function|dsmark_put
r_static
r_void
id|dsmark_put
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_int
r_int
id|cl
)paren
(brace
)brace
DECL|function|dsmark_change
r_static
r_int
id|dsmark_change
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
id|u32
id|classid
comma
id|u32
id|parent
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
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
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
id|TCA_DSMARK_MAX
)braket
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_change(sch %p,[qdisc %p],classid %x,parent %x),&quot;
l_string|&quot;arg 0x%lx&bslash;n&quot;
comma
id|sch
comma
id|p
comma
id|classid
comma
id|parent
comma
op_star
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
OG
id|p-&gt;indices
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
op_logical_or
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_DSMARK_MAX
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
id|TCA_DSMARK_MASK
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_DSMARK_MASK
op_minus
l_int|1
)braket
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;mask
(braket
op_star
id|arg
op_minus
l_int|1
)braket
op_assign
op_star
(paren
id|__u8
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_DSMARK_MASK
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tb
(braket
id|TCA_DSMARK_VALUE
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_DSMARK_VALUE
op_minus
l_int|1
)braket
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;value
(braket
op_star
id|arg
op_minus
l_int|1
)braket
op_assign
op_star
(paren
id|__u8
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_DSMARK_VALUE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsmark_delete
r_static
r_int
id|dsmark_delete
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
op_logical_or
id|arg
OG
id|p-&gt;indices
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;mask
(braket
id|arg
op_minus
l_int|1
)braket
op_assign
l_int|0xff
suffix:semicolon
id|p-&gt;value
(braket
id|arg
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsmark_walk
r_static
r_void
id|dsmark_walk
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_struct
id|qdisc_walker
op_star
id|walker
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_walk(sch %p,[qdisc %p],walker %p)&bslash;n&quot;
comma
id|sch
comma
id|p
comma
id|walker
)paren
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;stop
)paren
r_return
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
id|p-&gt;indices
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;mask
(braket
id|i
)braket
op_eq
l_int|0xff
op_logical_and
op_logical_neg
id|p-&gt;value
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;count
op_ge
id|walker-&gt;skip
)paren
(brace
r_if
c_cond
(paren
id|walker
op_member_access_from_pointer
id|fn
c_func
(paren
id|sch
comma
id|i
op_plus
l_int|1
comma
id|walker
)paren
OL
l_int|0
)paren
(brace
id|walker-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|walker-&gt;count
op_increment
suffix:semicolon
)brace
)brace
DECL|function|dsmark_find_tcf
r_static
r_struct
id|tcf_proto
op_star
op_star
id|dsmark_find_tcf
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_int
r_int
id|cl
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
op_amp
id|p-&gt;filter_list
suffix:semicolon
)brace
multiline_comment|/* --------------------------- Qdisc operations ---------------------------- */
DECL|function|dsmark_enqueue
r_static
r_int
id|dsmark_enqueue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|tcf_result
id|res
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|ret
op_assign
id|NET_XMIT_POLICED
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;dsmark_enqueue(skb %p,sch %p,[qdisc %p])&bslash;n&quot;
comma
id|skb
comma
id|sch
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;set_tc_index
)paren
(brace
multiline_comment|/* FIXME: Safe with non-linear skbs? --RR */
r_switch
c_cond
(paren
id|skb-&gt;protocol
)paren
(brace
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:colon
id|skb-&gt;tc_index
op_assign
id|ipv4_get_dsfield
c_func
(paren
id|skb-&gt;nh.iph
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IPV6
)paren
suffix:colon
id|skb-&gt;tc_index
op_assign
id|ipv6_get_dsfield
c_func
(paren
id|skb-&gt;nh.ipv6h
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|skb-&gt;tc_index
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
id|result
op_assign
id|TC_POLICE_OK
suffix:semicolon
multiline_comment|/* be nice to gcc */
r_if
c_cond
(paren
id|TC_H_MAJ
c_func
(paren
id|skb-&gt;priority
)paren
op_eq
id|sch-&gt;handle
)paren
(brace
id|skb-&gt;tc_index
op_assign
id|TC_H_MIN
c_func
(paren
id|skb-&gt;priority
)paren
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|tc_classify
c_func
(paren
id|skb
comma
id|p-&gt;filter_list
comma
op_amp
id|res
)paren
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;result %d class 0x%04x&bslash;n&quot;
comma
id|result
comma
id|res.classid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|result
)paren
(brace
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_case
id|TC_POLICE_SHOT
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
id|TC_POLICE_RECLASSIFY
suffix:colon
multiline_comment|/* FIXME: what to do here ??? */
macro_line|#endif
macro_line|#endif
r_case
id|TC_POLICE_OK
suffix:colon
id|skb-&gt;tc_index
op_assign
id|TC_H_MIN
c_func
(paren
id|res.classid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TC_POLICE_UNSPEC
suffix:colon
multiline_comment|/* fall through */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|p-&gt;default_index
op_ne
id|NO_DEFAULT_INDEX
)paren
id|skb-&gt;tc_index
op_assign
id|p-&gt;default_index
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
r_if
c_cond
(paren
macro_line|#ifdef CONFIG_NET_CLS_POLICE
id|result
op_eq
id|TC_POLICE_SHOT
op_logical_or
macro_line|#endif
(paren
(paren
id|ret
op_assign
id|p-&gt;q
op_member_access_from_pointer
id|enqueue
c_func
(paren
id|skb
comma
id|p-&gt;q
)paren
)paren
op_ne
l_int|0
)paren
)paren
(brace
id|sch-&gt;stats.drops
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|sch-&gt;stats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;stats.packets
op_increment
suffix:semicolon
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dsmark_dequeue
r_static
r_struct
id|sk_buff
op_star
id|dsmark_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|index
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;dsmark_dequeue(sch %p,[qdisc %p])&bslash;n&quot;
comma
id|sch
comma
id|p
)paren
suffix:semicolon
id|skb
op_assign
id|p-&gt;q-&gt;ops
op_member_access_from_pointer
id|dequeue
c_func
(paren
id|p-&gt;q
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
l_int|NULL
suffix:semicolon
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
id|index
op_assign
id|skb-&gt;tc_index
op_amp
(paren
id|p-&gt;indices
op_minus
l_int|1
)paren
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;index %d-&gt;%d&bslash;n&quot;
comma
id|skb-&gt;tc_index
comma
id|index
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;protocol
)paren
(brace
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:colon
id|ipv4_change_dsfield
c_func
(paren
id|skb-&gt;nh.iph
comma
id|p-&gt;mask
(braket
id|index
)braket
comma
id|p-&gt;value
(braket
id|index
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IPV6
)paren
suffix:colon
id|ipv6_change_dsfield
c_func
(paren
id|skb-&gt;nh.ipv6h
comma
id|p-&gt;mask
(braket
id|index
)braket
comma
id|p-&gt;value
(braket
id|index
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/*&n;&t;&t;&t; * Only complain if a change was actually attempted.&n;&t;&t;&t; * This way, we can send non-IP traffic through dsmark&n;&t;&t;&t; * and don&squot;t need yet another qdisc as a bypass.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;mask
(braket
id|index
)braket
op_ne
l_int|0xff
op_logical_or
id|p-&gt;value
(braket
id|index
)braket
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;dsmark_dequeue: &quot;
l_string|&quot;unsupported protocol %d&bslash;n&quot;
comma
id|htons
c_func
(paren
id|skb-&gt;protocol
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
DECL|function|dsmark_requeue
r_static
r_int
id|dsmark_requeue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
id|D2PRINTK
c_func
(paren
l_string|&quot;dsmark_requeue(skb %p,sch %p,[qdisc %p])&bslash;n&quot;
comma
id|skb
comma
id|sch
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|p-&gt;q-&gt;ops
op_member_access_from_pointer
id|requeue
c_func
(paren
id|skb
comma
id|p-&gt;q
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sch-&gt;stats.drops
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dsmark_drop
r_static
r_int
r_int
id|dsmark_drop
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_reset(sch %p,[qdisc %p])&bslash;n&quot;
comma
id|sch
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;q-&gt;ops-&gt;drop
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|len
op_assign
id|p-&gt;q-&gt;ops
op_member_access_from_pointer
id|drop
c_func
(paren
id|p-&gt;q
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|dsmark_init
r_int
id|dsmark_init
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_struct
id|rtattr
op_star
id|opt
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_DSMARK_MAX
)braket
suffix:semicolon
id|__u16
id|tmp
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_init(sch %p,[qdisc %p],opt %p)&bslash;n&quot;
comma
id|sch
comma
id|p
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
op_logical_or
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_DSMARK_MAX
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
op_logical_or
op_logical_neg
id|tb
(braket
id|TCA_DSMARK_INDICES
op_minus
l_int|1
)braket
op_logical_or
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_DSMARK_INDICES
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
id|__u16
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|p-&gt;filter_list
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;indices
op_assign
op_star
(paren
id|__u16
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_DSMARK_INDICES
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;indices
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|p-&gt;indices
suffix:semicolon
id|tmp
op_ne
l_int|1
suffix:semicolon
id|tmp
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|tmp
op_amp
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|p-&gt;default_index
op_assign
id|NO_DEFAULT_INDEX
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_DSMARK_DEFAULT_INDEX
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
id|TCA_DSMARK_DEFAULT_INDEX
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
id|__u16
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p-&gt;default_index
op_assign
op_star
(paren
id|__u16
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_DSMARK_DEFAULT_INDEX
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|p-&gt;set_tc_index
op_assign
op_logical_neg
op_logical_neg
id|tb
(braket
id|TCA_DSMARK_SET_TC_INDEX
op_minus
l_int|1
)braket
suffix:semicolon
id|p-&gt;mask
op_assign
id|kmalloc
c_func
(paren
id|p-&gt;indices
op_star
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mask
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|p-&gt;value
op_assign
id|p-&gt;mask
op_plus
id|p-&gt;indices
suffix:semicolon
id|memset
c_func
(paren
id|p-&gt;mask
comma
l_int|0xff
comma
id|p-&gt;indices
)paren
suffix:semicolon
id|memset
c_func
(paren
id|p-&gt;value
comma
l_int|0
comma
id|p-&gt;indices
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;q
op_assign
id|qdisc_create_dflt
c_func
(paren
id|sch-&gt;dev
comma
op_amp
id|pfifo_qdisc_ops
)paren
)paren
)paren
id|p-&gt;q
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_init: qdisc %p&bslash;n&quot;
comma
op_amp
id|p-&gt;q
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsmark_reset
r_static
r_void
id|dsmark_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_reset(sch %p,[qdisc %p])&bslash;n&quot;
comma
id|sch
comma
id|p
)paren
suffix:semicolon
id|qdisc_reset
c_func
(paren
id|p-&gt;q
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|dsmark_destroy
r_static
r_void
id|dsmark_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|tcf_proto
op_star
id|tp
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_destroy(sch %p,[qdisc %p])&bslash;n&quot;
comma
id|sch
comma
id|p
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;filter_list
)paren
(brace
id|tp
op_assign
id|p-&gt;filter_list
suffix:semicolon
id|p-&gt;filter_list
op_assign
id|tp-&gt;next
suffix:semicolon
id|tcf_destroy
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
id|qdisc_destroy
c_func
(paren
id|p-&gt;q
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p-&gt;mask
)paren
suffix:semicolon
)brace
DECL|function|dsmark_dump_class
r_static
r_int
id|dsmark_dump_class
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_int
r_int
id|cl
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcmsg
op_star
id|tcm
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
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
id|DPRINTK
c_func
(paren
l_string|&quot;dsmark_dump_class(sch %p,[qdisc %p],class %ld&bslash;n&quot;
comma
id|sch
comma
id|p
comma
id|cl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cl
op_logical_or
id|cl
OG
id|p-&gt;indices
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tcm-&gt;tcm_handle
op_assign
id|TC_H_MAKE
c_func
(paren
id|TC_H_MAJ
c_func
(paren
id|sch-&gt;handle
)paren
comma
id|cl
op_minus
l_int|1
)paren
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
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_DSMARK_MASK
comma
l_int|1
comma
op_amp
id|p-&gt;mask
(braket
id|cl
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_DSMARK_VALUE
comma
l_int|1
comma
op_amp
id|p-&gt;value
(braket
id|cl
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
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
DECL|function|dsmark_dump
r_static
r_int
id|dsmark_dump
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dsmark_qdisc_data
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|sch
)paren
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
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_DSMARK_INDICES
comma
r_sizeof
(paren
id|__u16
)paren
comma
op_amp
id|p-&gt;indices
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;default_index
op_ne
id|NO_DEFAULT_INDEX
)paren
(brace
id|__u16
id|tmp
op_assign
id|p-&gt;default_index
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_DSMARK_DEFAULT_INDEX
comma
r_sizeof
(paren
id|__u16
)paren
comma
op_amp
id|tmp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;set_tc_index
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_DSMARK_SET_TC_INDEX
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
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
DECL|variable|dsmark_class_ops
r_static
r_struct
id|Qdisc_class_ops
id|dsmark_class_ops
op_assign
(brace
dot
id|graft
op_assign
id|dsmark_graft
comma
dot
id|leaf
op_assign
id|dsmark_leaf
comma
dot
id|get
op_assign
id|dsmark_get
comma
dot
id|put
op_assign
id|dsmark_put
comma
dot
id|change
op_assign
id|dsmark_change
comma
dot
r_delete
op_assign
id|dsmark_delete
comma
dot
id|walk
op_assign
id|dsmark_walk
comma
dot
id|tcf_chain
op_assign
id|dsmark_find_tcf
comma
dot
id|bind_tcf
op_assign
id|dsmark_bind_filter
comma
dot
id|unbind_tcf
op_assign
id|dsmark_put
comma
dot
id|dump
op_assign
id|dsmark_dump_class
comma
)brace
suffix:semicolon
DECL|variable|dsmark_qdisc_ops
r_static
r_struct
id|Qdisc_ops
id|dsmark_qdisc_ops
op_assign
(brace
dot
id|next
op_assign
l_int|NULL
comma
dot
id|cl_ops
op_assign
op_amp
id|dsmark_class_ops
comma
dot
id|id
op_assign
l_string|&quot;dsmark&quot;
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|dsmark_qdisc_data
)paren
comma
dot
id|enqueue
op_assign
id|dsmark_enqueue
comma
dot
id|dequeue
op_assign
id|dsmark_dequeue
comma
dot
id|requeue
op_assign
id|dsmark_requeue
comma
dot
id|drop
op_assign
id|dsmark_drop
comma
dot
id|init
op_assign
id|dsmark_init
comma
dot
id|reset
op_assign
id|dsmark_reset
comma
dot
id|destroy
op_assign
id|dsmark_destroy
comma
dot
id|change
op_assign
l_int|NULL
comma
dot
id|dump
op_assign
id|dsmark_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|dsmark_module_init
r_static
r_int
id|__init
id|dsmark_module_init
c_func
(paren
r_void
)paren
(brace
r_return
id|register_qdisc
c_func
(paren
op_amp
id|dsmark_qdisc_ops
)paren
suffix:semicolon
)brace
DECL|function|dsmark_module_exit
r_static
r_void
id|__exit
id|dsmark_module_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_qdisc
c_func
(paren
op_amp
id|dsmark_qdisc_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|dsmark_module_init
)paren
id|module_exit
c_func
(paren
id|dsmark_module_exit
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
