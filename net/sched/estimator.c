multiline_comment|/*&n; * net/sched/estimator.c&t;Simple rate estimator.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/*&n;   This code is NOT intended to be used for statistics collection,&n;   its purpose is to provide a base for statistical multiplexing&n;   for controlled load service.&n;   If you need only statistics, run a user level daemon which&n;   periodically reads byte counters.&n;&n;   Unfortunately, rate estimation is not a very easy task.&n;   F.e. I did not find a simple way to estimate the current peak rate&n;   and even failed to formulate the problem 8)8)&n;&n;   So I preferred not to built an estimator into the scheduler,&n;   but run this task separately.&n;   Ideally, it should be kernel thread(s), but for now it runs&n;   from timers, which puts apparent top bounds on the number of rated&n;   flows, has minimal overhead on small, but is enough&n;   to handle controlled load service, sets of aggregates.&n;&n;   We measure rate over A=(1&lt;&lt;interval) seconds and evaluate EWMA:&n;&n;   avrate = avrate*(1-W) + rate*W&n;&n;   where W is chosen as negative power of 2: W = 2^(-ewma_log)&n;&n;   The resulting time constant is:&n;&n;   T = A/(-ln(1-W))&n;&n;&n;   NOTES.&n;&n;   * The stored value for avbps is scaled by 2^5, so that maximal&n;     rate is ~1Gbit, avpps is scaled by 2^10.&n;&n;   * Minimal interval is HZ/4=250msec (it is the greatest common divisor&n;     for HZ=100 and HZ=1024 8)), maximal interval&n;     is (HZ/4)*2^EST_MAX_INTERVAL = 8sec. Shorter intervals&n;     are too expensive, longer ones can be implemented&n;     at user level painlessly.&n; */
macro_line|#if (HZ%4) != 0
macro_line|#error Bad HZ value.
macro_line|#endif
DECL|macro|EST_MAX_INTERVAL
mdefine_line|#define EST_MAX_INTERVAL&t;5
DECL|struct|qdisc_estimator
r_struct
id|qdisc_estimator
(brace
DECL|member|next
r_struct
id|qdisc_estimator
op_star
id|next
suffix:semicolon
DECL|member|stats
r_struct
id|tc_stats
op_star
id|stats
suffix:semicolon
DECL|member|interval
r_int
id|interval
suffix:semicolon
DECL|member|ewma_log
r_int
id|ewma_log
suffix:semicolon
DECL|member|last_bytes
id|u64
id|last_bytes
suffix:semicolon
DECL|member|last_packets
id|u32
id|last_packets
suffix:semicolon
DECL|member|avpps
id|u32
id|avpps
suffix:semicolon
DECL|member|avbps
id|u32
id|avbps
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qdisc_estimator_head
r_struct
id|qdisc_estimator_head
(brace
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|list
r_struct
id|qdisc_estimator
op_star
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|elist
r_static
r_struct
id|qdisc_estimator_head
id|elist
(braket
id|EST_MAX_INTERVAL
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Estimator array lock */
DECL|variable|est_lock
r_static
id|rwlock_t
id|est_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|est_timer
r_static
r_void
id|est_timer
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_int
id|idx
op_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
r_struct
id|qdisc_estimator
op_star
id|e
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|est_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
id|elist
(braket
id|idx
)braket
dot
id|list
suffix:semicolon
id|e
suffix:semicolon
id|e
op_assign
id|e-&gt;next
)paren
(brace
r_struct
id|tc_stats
op_star
id|st
op_assign
id|e-&gt;stats
suffix:semicolon
id|u64
id|nbytes
suffix:semicolon
id|u32
id|npackets
suffix:semicolon
id|u32
id|rate
suffix:semicolon
id|spin_lock
c_func
(paren
id|st-&gt;lock
)paren
suffix:semicolon
id|nbytes
op_assign
id|st-&gt;bytes
suffix:semicolon
id|npackets
op_assign
id|st-&gt;packets
suffix:semicolon
id|rate
op_assign
(paren
id|nbytes
op_minus
id|e-&gt;last_bytes
)paren
op_lshift
(paren
l_int|7
op_minus
id|idx
)paren
suffix:semicolon
id|e-&gt;last_bytes
op_assign
id|nbytes
suffix:semicolon
id|e-&gt;avbps
op_add_assign
(paren
(paren
r_int
)paren
id|rate
op_minus
(paren
r_int
)paren
id|e-&gt;avbps
)paren
op_rshift
id|e-&gt;ewma_log
suffix:semicolon
id|st-&gt;bps
op_assign
(paren
id|e-&gt;avbps
op_plus
l_int|0xF
)paren
op_rshift
l_int|5
suffix:semicolon
id|rate
op_assign
(paren
id|npackets
op_minus
id|e-&gt;last_packets
)paren
op_lshift
(paren
l_int|12
op_minus
id|idx
)paren
suffix:semicolon
id|e-&gt;last_packets
op_assign
id|npackets
suffix:semicolon
id|e-&gt;avpps
op_add_assign
(paren
(paren
r_int
)paren
id|rate
op_minus
(paren
r_int
)paren
id|e-&gt;avpps
)paren
op_rshift
id|e-&gt;ewma_log
suffix:semicolon
id|e-&gt;stats-&gt;pps
op_assign
(paren
id|e-&gt;avpps
op_plus
l_int|0x1FF
)paren
op_rshift
l_int|10
suffix:semicolon
id|spin_unlock
c_func
(paren
id|st-&gt;lock
)paren
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|elist
(braket
id|idx
)braket
dot
id|timer
comma
id|jiffies
op_plus
(paren
(paren
id|HZ
op_div
l_int|4
)paren
op_lshift
id|idx
)paren
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|est_lock
)paren
suffix:semicolon
)brace
DECL|function|qdisc_new_estimator
r_int
id|qdisc_new_estimator
c_func
(paren
r_struct
id|tc_stats
op_star
id|stats
comma
r_struct
id|rtattr
op_star
id|opt
)paren
(brace
r_struct
id|qdisc_estimator
op_star
id|est
suffix:semicolon
r_struct
id|tc_estimator
op_star
id|parm
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
id|RTA_PAYLOAD
c_func
(paren
id|opt
)paren
OL
r_sizeof
(paren
op_star
id|parm
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|parm-&gt;interval
template_param
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|est
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|est
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|est
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
id|est
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|est
)paren
)paren
suffix:semicolon
id|est-&gt;interval
op_assign
id|parm-&gt;interval
op_plus
l_int|2
suffix:semicolon
id|est-&gt;stats
op_assign
id|stats
suffix:semicolon
id|est-&gt;ewma_log
op_assign
id|parm-&gt;ewma_log
suffix:semicolon
id|est-&gt;last_bytes
op_assign
id|stats-&gt;bytes
suffix:semicolon
id|est-&gt;avbps
op_assign
id|stats-&gt;bps
op_lshift
l_int|5
suffix:semicolon
id|est-&gt;last_packets
op_assign
id|stats-&gt;packets
suffix:semicolon
id|est-&gt;avpps
op_assign
id|stats-&gt;pps
op_lshift
l_int|10
suffix:semicolon
id|est-&gt;next
op_assign
id|elist
(braket
id|est-&gt;interval
)braket
dot
id|list
suffix:semicolon
r_if
c_cond
(paren
id|est-&gt;next
op_eq
l_int|NULL
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|elist
(braket
id|est-&gt;interval
)braket
dot
id|timer
)paren
suffix:semicolon
id|elist
(braket
id|est-&gt;interval
)braket
dot
id|timer.data
op_assign
id|est-&gt;interval
suffix:semicolon
id|elist
(braket
id|est-&gt;interval
)braket
dot
id|timer.expires
op_assign
id|jiffies
op_plus
(paren
(paren
id|HZ
op_div
l_int|4
)paren
op_lshift
id|est-&gt;interval
)paren
suffix:semicolon
id|elist
(braket
id|est-&gt;interval
)braket
dot
id|timer.function
op_assign
id|est_timer
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|elist
(braket
id|est-&gt;interval
)braket
dot
id|timer
)paren
suffix:semicolon
)brace
id|write_lock_bh
c_func
(paren
op_amp
id|est_lock
)paren
suffix:semicolon
id|elist
(braket
id|est-&gt;interval
)braket
dot
id|list
op_assign
id|est
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|est_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|qdisc_kill_estimator
r_void
id|qdisc_kill_estimator
c_func
(paren
r_struct
id|tc_stats
op_star
id|stats
)paren
(brace
r_int
id|idx
suffix:semicolon
r_struct
id|qdisc_estimator
op_star
id|est
comma
op_star
op_star
id|pest
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
op_le
id|EST_MAX_INTERVAL
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_int
id|killed
op_assign
l_int|0
suffix:semicolon
id|pest
op_assign
op_amp
id|elist
(braket
id|idx
)braket
dot
id|list
suffix:semicolon
r_while
c_loop
(paren
(paren
id|est
op_assign
op_star
id|pest
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|est-&gt;stats
op_ne
id|stats
)paren
(brace
id|pest
op_assign
op_amp
id|est-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|write_lock_bh
c_func
(paren
op_amp
id|est_lock
)paren
suffix:semicolon
op_star
id|pest
op_assign
id|est-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|est_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|est
)paren
suffix:semicolon
id|killed
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|killed
op_logical_and
id|elist
(braket
id|idx
)braket
dot
id|list
op_eq
l_int|NULL
)paren
id|del_timer
c_func
(paren
op_amp
id|elist
(braket
id|idx
)braket
dot
id|timer
)paren
suffix:semicolon
)brace
)brace
DECL|variable|qdisc_kill_estimator
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_kill_estimator
)paren
suffix:semicolon
DECL|variable|qdisc_new_estimator
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_new_estimator
)paren
suffix:semicolon
eof
