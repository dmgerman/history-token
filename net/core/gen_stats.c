multiline_comment|/*&n; * net/core/gen_stats.c&n; *&n; *             This program is free software; you can redistribute it and/or&n; *             modify it under the terms of the GNU General Public License&n; *             as published by the Free Software Foundation; either version&n; *             2 of the License, or (at your option) any later version.&n; *&n; * Authors:  Thomas Graf &lt;tgraf@suug.ch&gt;&n; *           Jamal Hadi Salim&n; *           Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; * See Documentation/networking/gen_stats.txt&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/gen_stats.h&gt;
macro_line|#include &lt;net/gen_stats.h&gt;
r_static
r_inline
r_int
DECL|function|gnet_stats_copy
id|gnet_stats_copy
c_func
(paren
r_struct
id|gnet_dump
op_star
id|d
comma
r_int
id|type
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
(brace
id|RTA_PUT
c_func
(paren
id|d-&gt;skb
comma
id|type
comma
id|size
comma
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|rtattr_failure
suffix:colon
id|spin_unlock_bh
c_func
(paren
id|d-&gt;lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|gnet_stats_start_copy_compat
id|gnet_stats_start_copy_compat
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
comma
r_int
id|tc_stats_type
comma
r_int
id|xstats_type
comma
id|spinlock_t
op_star
id|lock
comma
r_struct
id|gnet_dump
op_star
id|d
)paren
(brace
id|spin_lock_bh
c_func
(paren
id|lock
)paren
suffix:semicolon
id|d-&gt;lock
op_assign
id|lock
suffix:semicolon
id|d-&gt;tail
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
id|d-&gt;skb
op_assign
id|skb
suffix:semicolon
id|d-&gt;compat_tc_stats
op_assign
id|tc_stats_type
suffix:semicolon
id|d-&gt;compat_xstats
op_assign
id|xstats_type
suffix:semicolon
id|d-&gt;xstats
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;compat_tc_stats
)paren
id|memset
c_func
(paren
op_amp
id|d-&gt;tc_stats
comma
l_int|0
comma
r_sizeof
(paren
id|d-&gt;tc_stats
)paren
)paren
suffix:semicolon
r_return
id|gnet_stats_copy
c_func
(paren
id|d
comma
id|type
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|gnet_stats_start_copy
id|gnet_stats_start_copy
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
comma
id|spinlock_t
op_star
id|lock
comma
r_struct
id|gnet_dump
op_star
id|d
)paren
(brace
r_return
id|gnet_stats_start_copy_compat
c_func
(paren
id|skb
comma
id|type
comma
l_int|0
comma
l_int|0
comma
id|lock
comma
id|d
)paren
suffix:semicolon
)brace
r_int
DECL|function|gnet_stats_copy_basic
id|gnet_stats_copy_basic
c_func
(paren
r_struct
id|gnet_dump
op_star
id|d
comma
r_struct
id|gnet_stats_basic
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|d-&gt;compat_tc_stats
)paren
(brace
id|d-&gt;tc_stats.bytes
op_assign
id|b-&gt;bytes
suffix:semicolon
id|d-&gt;tc_stats.packets
op_assign
id|b-&gt;packets
suffix:semicolon
)brace
r_return
id|gnet_stats_copy
c_func
(paren
id|d
comma
id|TCA_STATS_BASIC
comma
id|b
comma
r_sizeof
(paren
op_star
id|b
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|gnet_stats_copy_rate_est
id|gnet_stats_copy_rate_est
c_func
(paren
r_struct
id|gnet_dump
op_star
id|d
comma
r_struct
id|gnet_stats_rate_est
op_star
id|r
)paren
(brace
r_if
c_cond
(paren
id|d-&gt;compat_tc_stats
)paren
(brace
id|d-&gt;tc_stats.bps
op_assign
id|r-&gt;bps
suffix:semicolon
id|d-&gt;tc_stats.pps
op_assign
id|r-&gt;pps
suffix:semicolon
)brace
r_return
id|gnet_stats_copy
c_func
(paren
id|d
comma
id|TCA_STATS_RATE_EST
comma
id|r
comma
r_sizeof
(paren
op_star
id|r
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|gnet_stats_copy_queue
id|gnet_stats_copy_queue
c_func
(paren
r_struct
id|gnet_dump
op_star
id|d
comma
r_struct
id|gnet_stats_queue
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
id|d-&gt;compat_tc_stats
)paren
(brace
id|d-&gt;tc_stats.drops
op_assign
id|q-&gt;drops
suffix:semicolon
id|d-&gt;tc_stats.qlen
op_assign
id|q-&gt;qlen
suffix:semicolon
id|d-&gt;tc_stats.backlog
op_assign
id|q-&gt;backlog
suffix:semicolon
id|d-&gt;tc_stats.overlimits
op_assign
id|q-&gt;overlimits
suffix:semicolon
)brace
r_return
id|gnet_stats_copy
c_func
(paren
id|d
comma
id|TCA_STATS_QUEUE
comma
id|q
comma
r_sizeof
(paren
op_star
id|q
)paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|gnet_stats_copy_app
id|gnet_stats_copy_app
c_func
(paren
r_struct
id|gnet_dump
op_star
id|d
comma
r_void
op_star
id|st
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|d-&gt;compat_xstats
)paren
id|d-&gt;xstats
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|d-&gt;skb-&gt;tail
suffix:semicolon
r_return
id|gnet_stats_copy
c_func
(paren
id|d
comma
id|TCA_STATS_APP
comma
id|st
comma
id|len
)paren
suffix:semicolon
)brace
r_int
DECL|function|gnet_stats_finish_copy
id|gnet_stats_finish_copy
c_func
(paren
r_struct
id|gnet_dump
op_star
id|d
)paren
(brace
id|d-&gt;tail-&gt;rta_len
op_assign
id|d-&gt;skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|d-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;compat_tc_stats
)paren
r_if
c_cond
(paren
id|gnet_stats_copy
c_func
(paren
id|d
comma
id|d-&gt;compat_tc_stats
comma
op_amp
id|d-&gt;tc_stats
comma
r_sizeof
(paren
id|d-&gt;tc_stats
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;compat_xstats
op_logical_and
id|d-&gt;xstats
)paren
(brace
r_if
c_cond
(paren
id|gnet_stats_copy
c_func
(paren
id|d
comma
id|d-&gt;compat_xstats
comma
id|RTA_DATA
c_func
(paren
id|d-&gt;xstats
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|d-&gt;xstats
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
id|d-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|gnet_stats_start_copy
id|EXPORT_SYMBOL
c_func
(paren
id|gnet_stats_start_copy
)paren
suffix:semicolon
DECL|variable|gnet_stats_copy_basic
id|EXPORT_SYMBOL
c_func
(paren
id|gnet_stats_copy_basic
)paren
suffix:semicolon
DECL|variable|gnet_stats_copy_rate_est
id|EXPORT_SYMBOL
c_func
(paren
id|gnet_stats_copy_rate_est
)paren
suffix:semicolon
DECL|variable|gnet_stats_copy_queue
id|EXPORT_SYMBOL
c_func
(paren
id|gnet_stats_copy_queue
)paren
suffix:semicolon
DECL|variable|gnet_stats_copy_app
id|EXPORT_SYMBOL
c_func
(paren
id|gnet_stats_copy_app
)paren
suffix:semicolon
DECL|variable|gnet_stats_finish_copy
id|EXPORT_SYMBOL
c_func
(paren
id|gnet_stats_finish_copy
)paren
suffix:semicolon
eof
