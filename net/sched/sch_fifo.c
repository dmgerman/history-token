multiline_comment|/*&n; * net/sched/sch_fifo.c&t;The simplest FIFO queue.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
multiline_comment|/* 1 band FIFO pseudo-&quot;scheduler&quot; */
DECL|struct|fifo_sched_data
r_struct
id|fifo_sched_data
(brace
DECL|member|limit
r_int
id|limit
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|bfifo_enqueue
id|bfifo_enqueue
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
id|fifo_sched_data
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
id|sch-&gt;qstats.backlog
op_plus
id|skb-&gt;len
op_le
id|q-&gt;limit
)paren
(brace
id|__skb_queue_tail
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
id|sch-&gt;qstats.backlog
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;bstats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;bstats.packets
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|sch-&gt;reshape_fail
op_eq
l_int|NULL
op_logical_or
id|sch
op_member_access_from_pointer
id|reshape_fail
c_func
(paren
id|skb
comma
id|sch
)paren
)paren
macro_line|#endif
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_XMIT_DROP
suffix:semicolon
)brace
r_static
r_int
DECL|function|bfifo_requeue
id|bfifo_requeue
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
id|__skb_queue_head
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
id|sch-&gt;qstats.backlog
op_add_assign
id|skb-&gt;len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|bfifo_dequeue
id|bfifo_dequeue
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
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|sch-&gt;qstats.backlog
op_sub_assign
id|skb-&gt;len
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|fifo_drop
id|fifo_drop
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
id|skb
op_assign
id|__skb_dequeue_tail
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_int
r_int
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;qstats.backlog
op_sub_assign
id|len
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|fifo_reset
id|fifo_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
id|skb_queue_purge
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
id|sch-&gt;qstats.backlog
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pfifo_enqueue
id|pfifo_enqueue
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
id|fifo_sched_data
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
id|sch-&gt;q.qlen
OL
id|q-&gt;limit
)paren
(brace
id|__skb_queue_tail
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
id|sch-&gt;bstats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;bstats.packets
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|sch-&gt;reshape_fail
op_eq
l_int|NULL
op_logical_or
id|sch
op_member_access_from_pointer
id|reshape_fail
c_func
(paren
id|skb
comma
id|sch
)paren
)paren
macro_line|#endif
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_XMIT_DROP
suffix:semicolon
)brace
r_static
r_int
DECL|function|pfifo_requeue
id|pfifo_requeue
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
id|__skb_queue_head
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|pfifo_dequeue
id|pfifo_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_return
id|__skb_dequeue
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
)brace
DECL|function|fifo_init
r_static
r_int
id|fifo_init
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
id|fifo_sched_data
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
id|opt
op_eq
l_int|NULL
)paren
(brace
r_int
r_int
id|limit
op_assign
id|sch-&gt;dev-&gt;tx_queue_len
ques
c_cond
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;ops
op_eq
op_amp
id|bfifo_qdisc_ops
)paren
id|q-&gt;limit
op_assign
id|limit
op_star
id|sch-&gt;dev-&gt;mtu
suffix:semicolon
r_else
id|q-&gt;limit
op_assign
id|limit
suffix:semicolon
)brace
r_else
(brace
r_struct
id|tc_fifo_qopt
op_star
id|ctl
op_assign
id|RTA_DATA
c_func
(paren
id|opt
)paren
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
id|ctl
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|q-&gt;limit
op_assign
id|ctl-&gt;limit
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fifo_dump
r_static
r_int
id|fifo_dump
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
id|fifo_sched_data
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
id|tc_fifo_qopt
id|opt
suffix:semicolon
id|opt.limit
op_assign
id|q-&gt;limit
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
DECL|variable|pfifo_qdisc_ops
r_struct
id|Qdisc_ops
id|pfifo_qdisc_ops
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
l_int|NULL
comma
dot
id|id
op_assign
l_string|&quot;pfifo&quot;
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|fifo_sched_data
)paren
comma
dot
id|enqueue
op_assign
id|pfifo_enqueue
comma
dot
id|dequeue
op_assign
id|pfifo_dequeue
comma
dot
id|requeue
op_assign
id|pfifo_requeue
comma
dot
id|drop
op_assign
id|fifo_drop
comma
dot
id|init
op_assign
id|fifo_init
comma
dot
id|reset
op_assign
id|fifo_reset
comma
dot
id|destroy
op_assign
l_int|NULL
comma
dot
id|change
op_assign
id|fifo_init
comma
dot
id|dump
op_assign
id|fifo_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|bfifo_qdisc_ops
r_struct
id|Qdisc_ops
id|bfifo_qdisc_ops
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
l_int|NULL
comma
dot
id|id
op_assign
l_string|&quot;bfifo&quot;
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|fifo_sched_data
)paren
comma
dot
id|enqueue
op_assign
id|bfifo_enqueue
comma
dot
id|dequeue
op_assign
id|bfifo_dequeue
comma
dot
id|requeue
op_assign
id|bfifo_requeue
comma
dot
id|drop
op_assign
id|fifo_drop
comma
dot
id|init
op_assign
id|fifo_init
comma
dot
id|reset
op_assign
id|fifo_reset
comma
dot
id|destroy
op_assign
l_int|NULL
comma
dot
id|change
op_assign
id|fifo_init
comma
dot
id|dump
op_assign
id|fifo_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|bfifo_qdisc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|bfifo_qdisc_ops
)paren
suffix:semicolon
DECL|variable|pfifo_qdisc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|pfifo_qdisc_ops
)paren
suffix:semicolon
eof
