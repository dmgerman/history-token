multiline_comment|/*&n; * net/sched/sch_netem.c&t;Network emulator&n; *&n; * &t;&t;This program is free software; you can redistribute it and/or&n; * &t;&t;modify it under the terms of the GNU General Public License&n; * &t;&t;as published by the Free Software Foundation; either version&n; * &t;&t;2 of the License, or (at your option) any later version.&n; *&n; *  &t;&t;Many of the algorithms and ideas for this came from&n; *&t;&t;NIST Net which is not copyrighted. &n; *&n; * Authors:&t;Stephen Hemminger &lt;shemminger@osdl.org&gt;&n; *&t;&t;Catalin(ux aka Dino) BOIE &lt;catab at umbrella dot ro&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/*&t;Network Emulation Queuing algorithm.&n;&t;====================================&n;&n;&t;Sources: [1] Mark Carson, Darrin Santay, &quot;NIST Net - A Linux-based&n;&t;&t; Network Emulation Tool&n;&t;&t; [2] Luigi Rizzo, DummyNet for FreeBSD&n;&n;&t; ----------------------------------------------------------------&n;&n;&t; This started out as a simple way to delay outgoing packets to&n;&t; test TCP but has grown to include most of the functionality&n;&t; of a full blown network emulator like NISTnet. It can delay&n;&t; packets and add random jitter (and correlation). The random&n;&t; distribution can be loaded from a table as well to provide&n;&t; normal, Pareto, or experimental curves. Packet loss,&n;&t; duplication, and reordering can also be emulated.&n;&n;&t; This qdisc does not do classification that can be handled in&n;&t; layering other disciplines.  It does not need to do bandwidth&n;&t; control either since that can be handled by using token&n;&t; bucket or other rate control.&n;&n;&t; The simulator is limited by the Linux timer resolution&n;&t; and will create packet bursts on the HZ boundary (1ms).&n;*/
DECL|struct|netem_sched_data
r_struct
id|netem_sched_data
(brace
DECL|member|qdisc
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
DECL|member|delayed
r_struct
id|sk_buff_head
id|delayed
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|latency
id|u32
id|latency
suffix:semicolon
DECL|member|loss
id|u32
id|loss
suffix:semicolon
DECL|member|limit
id|u32
id|limit
suffix:semicolon
DECL|member|counter
id|u32
id|counter
suffix:semicolon
DECL|member|gap
id|u32
id|gap
suffix:semicolon
DECL|member|jitter
id|u32
id|jitter
suffix:semicolon
DECL|member|duplicate
id|u32
id|duplicate
suffix:semicolon
DECL|struct|crndstate
r_struct
id|crndstate
(brace
DECL|member|last
r_int
r_int
id|last
suffix:semicolon
DECL|member|rho
r_int
r_int
id|rho
suffix:semicolon
DECL|member|delay_cor
DECL|member|loss_cor
DECL|member|dup_cor
)brace
id|delay_cor
comma
id|loss_cor
comma
id|dup_cor
suffix:semicolon
DECL|struct|disttable
r_struct
id|disttable
(brace
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|table
id|s16
id|table
(braket
l_int|0
)braket
suffix:semicolon
DECL|member|delay_dist
)brace
op_star
id|delay_dist
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Time stamp put into socket buffer control block */
DECL|struct|netem_skb_cb
r_struct
id|netem_skb_cb
(brace
DECL|member|time_to_send
id|psched_time_t
id|time_to_send
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* init_crandom - initialize correlated random number generator&n; * Use entropy source for initial seed.&n; */
DECL|function|init_crandom
r_static
r_void
id|init_crandom
c_func
(paren
r_struct
id|crndstate
op_star
id|state
comma
r_int
r_int
id|rho
)paren
(brace
id|state-&gt;rho
op_assign
id|rho
suffix:semicolon
id|state-&gt;last
op_assign
id|net_random
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* get_crandom - correlated random number generator&n; * Next number depends on last value.&n; * rho is scaled to avoid floating point.&n; */
DECL|function|get_crandom
r_static
r_int
r_int
id|get_crandom
c_func
(paren
r_struct
id|crndstate
op_star
id|state
)paren
(brace
id|u64
id|value
comma
id|rho
suffix:semicolon
r_int
r_int
id|answer
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;rho
op_eq
l_int|0
)paren
multiline_comment|/* no correllation */
r_return
id|net_random
c_func
(paren
)paren
suffix:semicolon
id|value
op_assign
id|net_random
c_func
(paren
)paren
suffix:semicolon
id|rho
op_assign
(paren
id|u64
)paren
id|state-&gt;rho
op_plus
l_int|1
suffix:semicolon
id|answer
op_assign
(paren
id|value
op_star
(paren
(paren
l_int|1ull
op_lshift
l_int|32
)paren
op_minus
id|rho
)paren
op_plus
id|state-&gt;last
op_star
id|rho
)paren
op_rshift
l_int|32
suffix:semicolon
id|state-&gt;last
op_assign
id|answer
suffix:semicolon
r_return
id|answer
suffix:semicolon
)brace
multiline_comment|/* tabledist - return a pseudo-randomly distributed value with mean mu and&n; * std deviation sigma.  Uses table lookup to approximate the desired&n; * distribution, and a uniformly-distributed pseudo-random source.&n; */
DECL|function|tabledist
r_static
r_int
id|tabledist
c_func
(paren
r_int
r_int
id|mu
comma
r_int
id|sigma
comma
r_struct
id|crndstate
op_star
id|state
comma
r_const
r_struct
id|disttable
op_star
id|dist
)paren
(brace
r_int
id|t
comma
id|x
suffix:semicolon
r_int
r_int
id|rnd
suffix:semicolon
r_if
c_cond
(paren
id|sigma
op_eq
l_int|0
)paren
r_return
id|mu
suffix:semicolon
id|rnd
op_assign
id|get_crandom
c_func
(paren
id|state
)paren
suffix:semicolon
multiline_comment|/* default uniform distribution */
r_if
c_cond
(paren
id|dist
op_eq
l_int|NULL
)paren
r_return
(paren
id|rnd
op_mod
(paren
l_int|2
op_star
id|sigma
)paren
)paren
op_minus
id|sigma
op_plus
id|mu
suffix:semicolon
id|t
op_assign
id|dist-&gt;table
(braket
id|rnd
op_mod
id|dist-&gt;size
)braket
suffix:semicolon
id|x
op_assign
(paren
id|sigma
op_mod
id|NETEM_DIST_SCALE
)paren
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|x
op_ge
l_int|0
)paren
id|x
op_add_assign
id|NETEM_DIST_SCALE
op_div
l_int|2
suffix:semicolon
r_else
id|x
op_sub_assign
id|NETEM_DIST_SCALE
op_div
l_int|2
suffix:semicolon
r_return
id|x
op_div
id|NETEM_DIST_SCALE
op_plus
(paren
id|sigma
op_div
id|NETEM_DIST_SCALE
)paren
op_star
id|t
op_plus
id|mu
suffix:semicolon
)brace
multiline_comment|/* Put skb in the private delayed queue. */
DECL|function|delay_skb
r_static
r_int
id|delay_skb
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
id|netem_sched_data
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
id|netem_skb_cb
op_star
id|cb
op_assign
(paren
r_struct
id|netem_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|psched_tdiff_t
id|td
suffix:semicolon
id|psched_time_t
id|now
suffix:semicolon
id|PSCHED_GET_TIME
c_func
(paren
id|now
)paren
suffix:semicolon
id|td
op_assign
id|tabledist
c_func
(paren
id|q-&gt;latency
comma
id|q-&gt;jitter
comma
op_amp
id|q-&gt;delay_cor
comma
id|q-&gt;delay_dist
)paren
suffix:semicolon
id|PSCHED_TADD2
c_func
(paren
id|now
comma
id|td
comma
id|cb-&gt;time_to_send
)paren
suffix:semicolon
multiline_comment|/* Always queue at tail to keep packets in order */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|q-&gt;delayed.qlen
OL
id|q-&gt;limit
)paren
)paren
(brace
id|__skb_queue_tail
c_func
(paren
op_amp
id|q-&gt;delayed
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timer_pending
c_func
(paren
op_amp
id|q-&gt;timer
)paren
)paren
(brace
id|q-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|PSCHED_US2JIFFIE
c_func
(paren
id|td
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|q-&gt;timer
)paren
suffix:semicolon
)brace
r_return
id|NET_XMIT_SUCCESS
suffix:semicolon
)brace
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
DECL|function|netem_enqueue
r_static
r_int
id|netem_enqueue
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
id|netem_sched_data
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
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;netem_enqueue skb=%p @%lu&bslash;n&quot;
comma
id|skb
comma
id|jiffies
)paren
suffix:semicolon
multiline_comment|/* Random packet drop 0 =&gt; none, ~0 =&gt; all */
r_if
c_cond
(paren
id|q-&gt;loss
op_logical_and
id|q-&gt;loss
op_ge
id|get_crandom
c_func
(paren
op_amp
id|q-&gt;loss_cor
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;netem_enqueue: random loss&bslash;n&quot;
)paren
suffix:semicolon
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
l_int|0
suffix:semicolon
multiline_comment|/* lie about loss so TCP doesn&squot;t know */
)brace
multiline_comment|/* Random duplication */
r_if
c_cond
(paren
id|q-&gt;duplicate
op_logical_and
id|q-&gt;duplicate
op_ge
id|get_crandom
c_func
(paren
op_amp
id|q-&gt;dup_cor
)paren
op_logical_and
(paren
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;netem_enqueue: dup %p&bslash;n&quot;
comma
id|skb2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delay_skb
c_func
(paren
id|sch
comma
id|skb2
)paren
)paren
(brace
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
id|sch-&gt;bstats.bytes
op_add_assign
id|skb2-&gt;len
suffix:semicolon
id|sch-&gt;bstats.packets
op_increment
suffix:semicolon
)brace
r_else
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
)brace
multiline_comment|/* If doing simple delay then gap == 0 so all packets&n;&t; * go into the delayed holding queue&n;&t; * otherwise if doing out of order only &quot;1 out of gap&quot;&n;&t; * packets will be delayed.&n;&t; */
r_if
c_cond
(paren
id|q-&gt;counter
OL
id|q-&gt;gap
)paren
(brace
op_increment
id|q-&gt;counter
suffix:semicolon
id|ret
op_assign
id|q-&gt;qdisc
op_member_access_from_pointer
id|enqueue
c_func
(paren
id|skb
comma
id|q-&gt;qdisc
)paren
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|delay_skb
c_func
(paren
id|sch
comma
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|ret
op_eq
id|NET_XMIT_SUCCESS
)paren
)paren
(brace
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
id|sch-&gt;bstats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;bstats.packets
op_increment
suffix:semicolon
)brace
r_else
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Requeue packets but don&squot;t change time stamp */
DECL|function|netem_requeue
r_static
r_int
id|netem_requeue
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
id|netem_sched_data
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
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|q-&gt;qdisc-&gt;ops
op_member_access_from_pointer
id|requeue
c_func
(paren
id|skb
comma
id|q-&gt;qdisc
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|sch-&gt;q.qlen
op_increment
suffix:semicolon
id|sch-&gt;qstats.requeues
op_increment
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|netem_drop
r_static
r_int
r_int
id|netem_drop
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|netem_sched_data
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
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|q-&gt;qdisc-&gt;ops
op_member_access_from_pointer
id|drop
c_func
(paren
id|q-&gt;qdisc
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* Dequeue packet.&n; *  Move all packets that are ready to send from the delay holding&n; *  list to the underlying qdisc, then just call dequeue&n; */
DECL|function|netem_dequeue
r_static
r_struct
id|sk_buff
op_star
id|netem_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|netem_sched_data
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
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|q-&gt;qdisc
op_member_access_from_pointer
id|dequeue
c_func
(paren
id|q-&gt;qdisc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
DECL|function|netem_watchdog
r_static
r_void
id|netem_watchdog
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|Qdisc
op_star
id|sch
op_assign
(paren
r_struct
id|Qdisc
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|netem_sched_data
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
id|net_device
op_star
id|dev
op_assign
id|sch-&gt;dev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|psched_time_t
id|now
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;netem_watchdog: fired @%lu&bslash;n&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|PSCHED_GET_TIME
c_func
(paren
id|now
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|q-&gt;delayed
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_const
r_struct
id|netem_skb_cb
op_star
id|cb
op_assign
(paren
r_const
r_struct
id|netem_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_int
id|delay
op_assign
id|PSCHED_US2JIFFIE
c_func
(paren
id|PSCHED_TDIFF
c_func
(paren
id|cb-&gt;time_to_send
comma
id|now
)paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;netem_watchdog: skb %p@%lu %ld&bslash;n&quot;
comma
id|skb
comma
id|jiffies
comma
id|delay
)paren
suffix:semicolon
multiline_comment|/* if more time remaining? */
r_if
c_cond
(paren
id|delay
OG
l_int|0
)paren
(brace
id|mod_timer
c_func
(paren
op_amp
id|q-&gt;timer
comma
id|jiffies
op_plus
id|delay
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|__skb_unlink
c_func
(paren
id|skb
comma
op_amp
id|q-&gt;delayed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;qdisc
op_member_access_from_pointer
id|enqueue
c_func
(paren
id|skb
comma
id|q-&gt;qdisc
)paren
)paren
(brace
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
)brace
)brace
id|qdisc_run
c_func
(paren
id|dev
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
DECL|function|netem_reset
r_static
r_void
id|netem_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|netem_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|qdisc_reset
c_func
(paren
id|q-&gt;qdisc
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|q-&gt;delayed
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_assign
l_int|0
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|q-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|set_fifo_limit
r_static
r_int
id|set_fifo_limit
c_func
(paren
r_struct
id|Qdisc
op_star
id|q
comma
r_int
id|limit
)paren
(brace
r_struct
id|rtattr
op_star
id|rta
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|rta
op_assign
id|kmalloc
c_func
(paren
id|RTA_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|tc_fifo_qopt
)paren
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rta
)paren
(brace
id|rta-&gt;rta_type
op_assign
id|RTM_NEWQDISC
suffix:semicolon
id|rta-&gt;rta_len
op_assign
id|RTA_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|tc_fifo_qopt
)paren
)paren
suffix:semicolon
(paren
(paren
r_struct
id|tc_fifo_qopt
op_star
)paren
id|RTA_DATA
c_func
(paren
id|rta
)paren
)paren
op_member_access_from_pointer
id|limit
op_assign
id|limit
suffix:semicolon
id|ret
op_assign
id|q-&gt;ops
op_member_access_from_pointer
id|change
c_func
(paren
id|q
comma
id|rta
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rta
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Distribution data is a variable size payload containing&n; * signed 16 bit values.&n; */
DECL|function|get_dist_table
r_static
r_int
id|get_dist_table
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_const
r_struct
id|rtattr
op_star
id|attr
)paren
(brace
r_struct
id|netem_sched_data
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
id|n
op_assign
id|RTA_PAYLOAD
c_func
(paren
id|attr
)paren
op_div
r_sizeof
(paren
id|__s16
)paren
suffix:semicolon
r_const
id|__s16
op_star
id|data
op_assign
id|RTA_DATA
c_func
(paren
id|attr
)paren
suffix:semicolon
r_struct
id|disttable
op_star
id|d
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|65536
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|d
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|d
)paren
op_plus
id|n
op_star
r_sizeof
(paren
id|d-&gt;table
(braket
l_int|0
)braket
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|d-&gt;size
op_assign
id|n
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
id|n
suffix:semicolon
id|i
op_increment
)paren
id|d-&gt;table
(braket
id|i
)braket
op_assign
id|data
(braket
id|i
)braket
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|sch-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
id|d
op_assign
id|xchg
c_func
(paren
op_amp
id|q-&gt;delay_dist
comma
id|d
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|sch-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|d
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_correlation
r_static
r_int
id|get_correlation
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_const
r_struct
id|rtattr
op_star
id|attr
)paren
(brace
r_struct
id|netem_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_const
r_struct
id|tc_netem_corr
op_star
id|c
op_assign
id|RTA_DATA
c_func
(paren
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|attr
)paren
op_ne
r_sizeof
(paren
op_star
id|c
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|init_crandom
c_func
(paren
op_amp
id|q-&gt;delay_cor
comma
id|c-&gt;delay_corr
)paren
suffix:semicolon
id|init_crandom
c_func
(paren
op_amp
id|q-&gt;loss_cor
comma
id|c-&gt;loss_corr
)paren
suffix:semicolon
id|init_crandom
c_func
(paren
op_amp
id|q-&gt;dup_cor
comma
id|c-&gt;dup_corr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netem_change
r_static
r_int
id|netem_change
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
id|netem_sched_data
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
id|tc_netem_qopt
op_star
id|qopt
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
op_logical_or
id|RTA_PAYLOAD
c_func
(paren
id|opt
)paren
OL
r_sizeof
(paren
op_star
id|qopt
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|qopt
op_assign
id|RTA_DATA
c_func
(paren
id|opt
)paren
suffix:semicolon
id|ret
op_assign
id|set_fifo_limit
c_func
(paren
id|q-&gt;qdisc
comma
id|qopt-&gt;limit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;netem: can&squot;t set fifo limit&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|q-&gt;latency
op_assign
id|qopt-&gt;latency
suffix:semicolon
id|q-&gt;jitter
op_assign
id|qopt-&gt;jitter
suffix:semicolon
id|q-&gt;limit
op_assign
id|qopt-&gt;limit
suffix:semicolon
id|q-&gt;gap
op_assign
id|qopt-&gt;gap
suffix:semicolon
id|q-&gt;loss
op_assign
id|qopt-&gt;loss
suffix:semicolon
id|q-&gt;duplicate
op_assign
id|qopt-&gt;duplicate
suffix:semicolon
multiline_comment|/* Handle nested options after initial queue options.&n;&t; * Should have put all options in nested format but too late now.&n;&t; */
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|opt
)paren
OG
r_sizeof
(paren
op_star
id|qopt
)paren
)paren
(brace
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_NETEM_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_NETEM_MAX
comma
id|RTA_DATA
c_func
(paren
id|opt
)paren
op_plus
r_sizeof
(paren
op_star
id|qopt
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|opt
)paren
op_minus
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
id|tb
(braket
id|TCA_NETEM_CORR
op_minus
l_int|1
)braket
)paren
(brace
id|ret
op_assign
id|get_correlation
c_func
(paren
id|sch
comma
id|tb
(braket
id|TCA_NETEM_CORR
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tb
(braket
id|TCA_NETEM_DELAY_DIST
op_minus
l_int|1
)braket
)paren
(brace
id|ret
op_assign
id|get_dist_table
c_func
(paren
id|sch
comma
id|tb
(braket
id|TCA_NETEM_DELAY_DIST
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netem_init
r_static
r_int
id|netem_init
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
id|netem_sched_data
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
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|q-&gt;delayed
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|q-&gt;timer
)paren
suffix:semicolon
id|q-&gt;timer.function
op_assign
id|netem_watchdog
suffix:semicolon
id|q-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sch
suffix:semicolon
id|q-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|q-&gt;qdisc
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
op_logical_neg
id|q-&gt;qdisc
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;netem: qdisc create failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ret
op_assign
id|netem_change
c_func
(paren
id|sch
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;netem: change failed&bslash;n&quot;
)paren
suffix:semicolon
id|qdisc_destroy
c_func
(paren
id|q-&gt;qdisc
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|netem_destroy
r_static
r_void
id|netem_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|netem_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|q-&gt;timer
)paren
suffix:semicolon
id|qdisc_destroy
c_func
(paren
id|q-&gt;qdisc
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|q-&gt;delay_dist
)paren
suffix:semicolon
)brace
DECL|function|netem_dump
r_static
r_int
id|netem_dump
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
r_const
r_struct
id|netem_sched_data
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
id|rtattr
op_star
id|rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|b
suffix:semicolon
r_struct
id|tc_netem_qopt
id|qopt
suffix:semicolon
r_struct
id|tc_netem_corr
id|cor
suffix:semicolon
id|qopt.latency
op_assign
id|q-&gt;latency
suffix:semicolon
id|qopt.jitter
op_assign
id|q-&gt;jitter
suffix:semicolon
id|qopt.limit
op_assign
id|q-&gt;limit
suffix:semicolon
id|qopt.loss
op_assign
id|q-&gt;loss
suffix:semicolon
id|qopt.gap
op_assign
id|q-&gt;gap
suffix:semicolon
id|qopt.duplicate
op_assign
id|q-&gt;duplicate
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
id|qopt
)paren
comma
op_amp
id|qopt
)paren
suffix:semicolon
id|cor.delay_corr
op_assign
id|q-&gt;delay_cor.rho
suffix:semicolon
id|cor.loss_corr
op_assign
id|q-&gt;loss_cor.rho
suffix:semicolon
id|cor.dup_corr
op_assign
id|q-&gt;dup_cor.rho
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_NETEM_CORR
comma
r_sizeof
(paren
id|cor
)paren
comma
op_amp
id|cor
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
DECL|function|netem_dump_class
r_static
r_int
id|netem_dump_class
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
id|netem_sched_data
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
op_ne
l_int|1
)paren
multiline_comment|/* only one class */
r_return
op_minus
id|ENOENT
suffix:semicolon
id|tcm-&gt;tcm_handle
op_or_assign
id|TC_H_MIN
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|tcm-&gt;tcm_info
op_assign
id|q-&gt;qdisc-&gt;handle
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netem_graft
r_static
r_int
id|netem_graft
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
id|netem_sched_data
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
id|xchg
c_func
(paren
op_amp
id|q-&gt;qdisc
comma
r_new
)paren
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netem_leaf
r_static
r_struct
id|Qdisc
op_star
id|netem_leaf
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
id|netem_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|q-&gt;qdisc
suffix:semicolon
)brace
DECL|function|netem_get
r_static
r_int
r_int
id|netem_get
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
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|netem_put
r_static
r_void
id|netem_put
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
)brace
DECL|function|netem_change_class
r_static
r_int
id|netem_change_class
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
id|parentid
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
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|netem_delete
r_static
r_int
id|netem_delete
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
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|netem_walk
r_static
r_void
id|netem_walk
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
r_if
c_cond
(paren
op_logical_neg
id|walker-&gt;stop
)paren
(brace
r_if
c_cond
(paren
id|walker-&gt;count
op_ge
id|walker-&gt;skip
)paren
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
r_return
suffix:semicolon
)brace
id|walker-&gt;count
op_increment
suffix:semicolon
)brace
)brace
DECL|function|netem_find_tcf
r_static
r_struct
id|tcf_proto
op_star
op_star
id|netem_find_tcf
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
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|netem_class_ops
r_static
r_struct
id|Qdisc_class_ops
id|netem_class_ops
op_assign
(brace
dot
id|graft
op_assign
id|netem_graft
comma
dot
id|leaf
op_assign
id|netem_leaf
comma
dot
id|get
op_assign
id|netem_get
comma
dot
id|put
op_assign
id|netem_put
comma
dot
id|change
op_assign
id|netem_change_class
comma
dot
r_delete
op_assign
id|netem_delete
comma
dot
id|walk
op_assign
id|netem_walk
comma
dot
id|tcf_chain
op_assign
id|netem_find_tcf
comma
dot
id|dump
op_assign
id|netem_dump_class
comma
)brace
suffix:semicolon
DECL|variable|netem_qdisc_ops
r_static
r_struct
id|Qdisc_ops
id|netem_qdisc_ops
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;netem&quot;
comma
dot
id|cl_ops
op_assign
op_amp
id|netem_class_ops
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|netem_sched_data
)paren
comma
dot
id|enqueue
op_assign
id|netem_enqueue
comma
dot
id|dequeue
op_assign
id|netem_dequeue
comma
dot
id|requeue
op_assign
id|netem_requeue
comma
dot
id|drop
op_assign
id|netem_drop
comma
dot
id|init
op_assign
id|netem_init
comma
dot
id|reset
op_assign
id|netem_reset
comma
dot
id|destroy
op_assign
id|netem_destroy
comma
dot
id|change
op_assign
id|netem_change
comma
dot
id|dump
op_assign
id|netem_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|netem_module_init
r_static
r_int
id|__init
id|netem_module_init
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
id|netem_qdisc_ops
)paren
suffix:semicolon
)brace
DECL|function|netem_module_exit
r_static
r_void
id|__exit
id|netem_module_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_qdisc
c_func
(paren
op_amp
id|netem_qdisc_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|netem_module_init
)paren
id|module_exit
c_func
(paren
id|netem_module_exit
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
