multiline_comment|/*&n; * net/sched/sch_prio.c&t;Simple 3-band priority &quot;scheduler&quot;.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; * Fixes:       19990609: J Hadi Salim &lt;hadi@nortelnetworks.com&gt;: &n; *              Init --  EINVAL when opt undefined&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
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
DECL|struct|prio_sched_data
r_struct
id|prio_sched_data
(brace
DECL|member|bands
r_int
id|bands
suffix:semicolon
DECL|member|filter_list
r_struct
id|tcf_proto
op_star
id|filter_list
suffix:semicolon
DECL|member|prio2band
id|u8
id|prio2band
(braket
id|TC_PRIO_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|queues
r_struct
id|Qdisc
op_star
id|queues
(braket
id|TCQ_PRIO_BANDS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_struct
id|Qdisc
op_star
DECL|function|prio_classify
id|prio_classify
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
comma
r_int
op_star
id|qerr
)paren
(brace
r_struct
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|u32
id|band
op_assign
id|skb-&gt;priority
suffix:semicolon
r_struct
id|tcf_result
id|res
suffix:semicolon
op_star
id|qerr
op_assign
id|NET_XMIT_DROP
suffix:semicolon
r_if
c_cond
(paren
id|TC_H_MAJ
c_func
(paren
id|skb-&gt;priority
)paren
op_ne
id|sch-&gt;handle
)paren
(brace
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_switch
c_cond
(paren
id|tc_classify
c_func
(paren
id|skb
comma
id|q-&gt;filter_list
comma
op_amp
id|res
)paren
)paren
(brace
r_case
id|TC_ACT_STOLEN
suffix:colon
r_case
id|TC_ACT_QUEUED
suffix:colon
op_star
id|qerr
op_assign
id|NET_XMIT_SUCCESS
suffix:semicolon
r_case
id|TC_ACT_SHOT
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;filter_list
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;filter_list
op_logical_or
id|tc_classify
c_func
(paren
id|skb
comma
id|q-&gt;filter_list
comma
op_amp
id|res
)paren
)paren
(brace
macro_line|#endif
r_if
c_cond
(paren
id|TC_H_MAJ
c_func
(paren
id|band
)paren
)paren
id|band
op_assign
l_int|0
suffix:semicolon
r_return
id|q-&gt;queues
(braket
id|q-&gt;prio2band
(braket
id|band
op_amp
id|TC_PRIO_MAX
)braket
)braket
suffix:semicolon
)brace
id|band
op_assign
id|res.classid
suffix:semicolon
)brace
id|band
op_assign
id|TC_H_MIN
c_func
(paren
id|band
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|band
OG
id|q-&gt;bands
)paren
r_return
id|q-&gt;queues
(braket
id|q-&gt;prio2band
(braket
l_int|0
)braket
)braket
suffix:semicolon
r_return
id|q-&gt;queues
(braket
id|band
)braket
suffix:semicolon
)brace
r_static
r_int
DECL|function|prio_enqueue
id|prio_enqueue
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
id|Qdisc
op_star
id|qdisc
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|qdisc
op_assign
id|prio_classify
c_func
(paren
id|skb
comma
id|sch
comma
op_amp
id|ret
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|qdisc
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ret
op_eq
id|NET_XMIT_DROP
)paren
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|qdisc
op_member_access_from_pointer
id|enqueue
c_func
(paren
id|skb
comma
id|qdisc
)paren
)paren
op_eq
id|NET_XMIT_SUCCESS
)paren
(brace
id|sch-&gt;bstats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;bstats.packets
op_increment
suffix:semicolon
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
r_return
id|NET_XMIT_SUCCESS
suffix:semicolon
)brace
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|prio_requeue
id|prio_requeue
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
id|Qdisc
op_star
id|qdisc
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|qdisc
op_assign
id|prio_classify
c_func
(paren
id|skb
comma
id|sch
comma
op_amp
id|ret
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|qdisc
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ret
op_eq
id|NET_XMIT_DROP
)paren
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|qdisc-&gt;ops
op_member_access_from_pointer
id|requeue
c_func
(paren
id|skb
comma
id|qdisc
)paren
)paren
op_eq
id|NET_XMIT_SUCCESS
)paren
(brace
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
id|sch-&gt;qstats.requeues
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
r_return
id|NET_XMIT_DROP
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|prio_dequeue
id|prio_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|prio
suffix:semicolon
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
id|q-&gt;bands
suffix:semicolon
id|prio
op_increment
)paren
(brace
id|qdisc
op_assign
id|q-&gt;queues
(braket
id|prio
)braket
suffix:semicolon
id|skb
op_assign
id|qdisc
op_member_access_from_pointer
id|dequeue
c_func
(paren
id|qdisc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|prio_drop
r_static
r_int
r_int
id|prio_drop
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|prio
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
id|q-&gt;bands
op_minus
l_int|1
suffix:semicolon
id|prio
op_ge
l_int|0
suffix:semicolon
id|prio
op_decrement
)paren
(brace
id|qdisc
op_assign
id|q-&gt;queues
(braket
id|prio
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|qdisc-&gt;ops
op_member_access_from_pointer
id|drop
c_func
(paren
id|qdisc
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|prio_reset
id|prio_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_int
id|prio
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
id|q-&gt;bands
suffix:semicolon
id|prio
op_increment
)paren
id|qdisc_reset
c_func
(paren
id|q-&gt;queues
(braket
id|prio
)braket
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|prio_destroy
id|prio_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_int
id|prio
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
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
r_while
c_loop
(paren
(paren
id|tp
op_assign
id|q-&gt;filter_list
)paren
op_ne
l_int|NULL
)paren
(brace
id|q-&gt;filter_list
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
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
id|q-&gt;bands
suffix:semicolon
id|prio
op_increment
)paren
id|qdisc_destroy
c_func
(paren
id|q-&gt;queues
(braket
id|prio
)braket
)paren
suffix:semicolon
)brace
DECL|function|prio_tune
r_static
r_int
id|prio_tune
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|tc_prio_qopt
op_star
id|qopt
op_assign
id|RTA_DATA
c_func
(paren
id|opt
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;rta_len
OL
id|RTA_LENGTH
c_func
(paren
r_sizeof
(paren
op_star
id|qopt
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
id|qopt-&gt;bands
OG
id|TCQ_PRIO_BANDS
op_logical_or
id|qopt-&gt;bands
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|TC_PRIO_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|qopt-&gt;priomap
(braket
id|i
)braket
op_ge
id|qopt-&gt;bands
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|sch_tree_lock
c_func
(paren
id|sch
)paren
suffix:semicolon
id|q-&gt;bands
op_assign
id|qopt-&gt;bands
suffix:semicolon
id|memcpy
c_func
(paren
id|q-&gt;prio2band
comma
id|qopt-&gt;priomap
comma
id|TC_PRIO_MAX
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|q-&gt;bands
suffix:semicolon
id|i
OL
id|TCQ_PRIO_BANDS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|Qdisc
op_star
id|child
op_assign
id|xchg
c_func
(paren
op_amp
id|q-&gt;queues
(braket
id|i
)braket
comma
op_amp
id|noop_qdisc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
op_ne
op_amp
id|noop_qdisc
)paren
id|qdisc_destroy
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
id|sch_tree_unlock
c_func
(paren
id|sch
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
op_le
id|TC_PRIO_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|band
op_assign
id|q-&gt;prio2band
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;queues
(braket
id|band
)braket
op_eq
op_amp
id|noop_qdisc
)paren
(brace
r_struct
id|Qdisc
op_star
id|child
suffix:semicolon
id|child
op_assign
id|qdisc_create_dflt
c_func
(paren
id|sch-&gt;dev
comma
op_amp
id|pfifo_qdisc_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
(brace
id|sch_tree_lock
c_func
(paren
id|sch
)paren
suffix:semicolon
id|child
op_assign
id|xchg
c_func
(paren
op_amp
id|q-&gt;queues
(braket
id|band
)braket
comma
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
op_ne
op_amp
id|noop_qdisc
)paren
id|qdisc_destroy
c_func
(paren
id|child
)paren
suffix:semicolon
id|sch_tree_unlock
c_func
(paren
id|sch
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prio_init
r_static
r_int
id|prio_init
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|i
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
id|TCQ_PRIO_BANDS
suffix:semicolon
id|i
op_increment
)paren
id|q-&gt;queues
(braket
id|i
)braket
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|prio_tune
c_func
(paren
id|sch
comma
id|opt
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prio_dump
r_static
r_int
id|prio_dump
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
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
id|tc_prio_qopt
id|opt
suffix:semicolon
id|opt.bands
op_assign
id|q-&gt;bands
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|opt.priomap
comma
id|q-&gt;prio2band
comma
id|TC_PRIO_MAX
op_plus
l_int|1
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_OPTIONS
comma
r_sizeof
(paren
id|opt
)paren
comma
op_amp
id|opt
)paren
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
DECL|function|prio_graft
r_static
r_int
id|prio_graft
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
r_int
id|band
op_assign
id|arg
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|band
op_ge
id|q-&gt;bands
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
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
id|q-&gt;queues
(braket
id|band
)braket
suffix:semicolon
id|q-&gt;queues
(braket
id|band
)braket
op_assign
r_new
suffix:semicolon
id|sch-&gt;q.qlen
op_sub_assign
(paren
op_star
id|old
)paren
op_member_access_from_pointer
id|q.qlen
suffix:semicolon
id|qdisc_reset
c_func
(paren
op_star
id|old
)paren
suffix:semicolon
id|sch_tree_unlock
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|Qdisc
op_star
DECL|function|prio_leaf
id|prio_leaf
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
r_int
id|band
op_assign
id|arg
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|band
op_ge
id|q-&gt;bands
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|q-&gt;queues
(braket
id|band
)braket
suffix:semicolon
)brace
DECL|function|prio_get
r_static
r_int
r_int
id|prio_get
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
r_int
id|band
op_assign
id|TC_H_MIN
c_func
(paren
id|classid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|band
op_minus
l_int|1
op_ge
id|q-&gt;bands
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|band
suffix:semicolon
)brace
DECL|function|prio_bind
r_static
r_int
r_int
id|prio_bind
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
id|prio_get
c_func
(paren
id|sch
comma
id|classid
)paren
suffix:semicolon
)brace
DECL|function|prio_put
r_static
r_void
id|prio_put
c_func
(paren
r_struct
id|Qdisc
op_star
id|q
comma
r_int
r_int
id|cl
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|prio_change
r_static
r_int
id|prio_change
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
id|u32
id|handle
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
r_int
r_int
id|cl
op_assign
op_star
id|arg
suffix:semicolon
r_struct
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
op_minus
l_int|1
OG
id|q-&gt;bands
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prio_delete
r_static
r_int
id|prio_delete
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
op_minus
l_int|1
OG
id|q-&gt;bands
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prio_dump_class
r_static
r_int
id|prio_dump_class
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
op_minus
l_int|1
OG
id|q-&gt;bands
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|tcm-&gt;tcm_handle
op_or_assign
id|TC_H_MIN
c_func
(paren
id|cl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;queues
(braket
id|cl
op_minus
l_int|1
)braket
)paren
id|tcm-&gt;tcm_info
op_assign
id|q-&gt;queues
(braket
id|cl
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|handle
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prio_walk
r_static
r_void
id|prio_walk
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
id|arg
)paren
(brace
r_struct
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|prio
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
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
id|q-&gt;bands
suffix:semicolon
id|prio
op_increment
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
id|sch
comma
id|prio
op_plus
l_int|1
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
DECL|function|prio_find_tcf
r_static
r_struct
id|tcf_proto
op_star
op_star
id|prio_find_tcf
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
id|prio_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|q-&gt;filter_list
suffix:semicolon
)brace
DECL|variable|prio_class_ops
r_static
r_struct
id|Qdisc_class_ops
id|prio_class_ops
op_assign
(brace
dot
id|graft
op_assign
id|prio_graft
comma
dot
id|leaf
op_assign
id|prio_leaf
comma
dot
id|get
op_assign
id|prio_get
comma
dot
id|put
op_assign
id|prio_put
comma
dot
id|change
op_assign
id|prio_change
comma
dot
r_delete
op_assign
id|prio_delete
comma
dot
id|walk
op_assign
id|prio_walk
comma
dot
id|tcf_chain
op_assign
id|prio_find_tcf
comma
dot
id|bind_tcf
op_assign
id|prio_bind
comma
dot
id|unbind_tcf
op_assign
id|prio_put
comma
dot
id|dump
op_assign
id|prio_dump_class
comma
)brace
suffix:semicolon
DECL|variable|prio_qdisc_ops
r_static
r_struct
id|Qdisc_ops
id|prio_qdisc_ops
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
id|prio_class_ops
comma
dot
id|id
op_assign
l_string|&quot;prio&quot;
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|prio_sched_data
)paren
comma
dot
id|enqueue
op_assign
id|prio_enqueue
comma
dot
id|dequeue
op_assign
id|prio_dequeue
comma
dot
id|requeue
op_assign
id|prio_requeue
comma
dot
id|drop
op_assign
id|prio_drop
comma
dot
id|init
op_assign
id|prio_init
comma
dot
id|reset
op_assign
id|prio_reset
comma
dot
id|destroy
op_assign
id|prio_destroy
comma
dot
id|change
op_assign
id|prio_tune
comma
dot
id|dump
op_assign
id|prio_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|prio_module_init
r_static
r_int
id|__init
id|prio_module_init
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
id|prio_qdisc_ops
)paren
suffix:semicolon
)brace
DECL|function|prio_module_exit
r_static
r_void
id|__exit
id|prio_module_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_qdisc
c_func
(paren
op_amp
id|prio_qdisc_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|prio_module_init
)paren
id|module_exit
c_func
(paren
id|prio_module_exit
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
