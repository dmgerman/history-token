multiline_comment|/*&n; * net/sched/police.c&t;Input police filter.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
DECL|macro|L2T
mdefine_line|#define L2T(p,L)   ((p)-&gt;R_tab-&gt;data[(L)&gt;&gt;(p)-&gt;R_tab-&gt;rate.cell_log])
DECL|macro|L2T_P
mdefine_line|#define L2T_P(p,L) ((p)-&gt;P_tab-&gt;data[(L)&gt;&gt;(p)-&gt;P_tab-&gt;rate.cell_log])
DECL|variable|idx_gen
r_static
id|u32
id|idx_gen
suffix:semicolon
DECL|variable|tcf_police_ht
r_static
r_struct
id|tcf_police
op_star
id|tcf_police_ht
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Policer hash table lock */
DECL|variable|police_lock
r_static
id|rwlock_t
id|police_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Each policer is serialized by its individual spinlock */
DECL|function|tcf_police_hash
r_static
id|__inline__
r_int
id|tcf_police_hash
c_func
(paren
id|u32
id|index
)paren
(brace
r_return
id|index
op_amp
l_int|0xF
suffix:semicolon
)brace
DECL|function|tcf_police_lookup
r_static
id|__inline__
r_struct
id|tcf_police
op_star
id|tcf_police_lookup
c_func
(paren
id|u32
id|index
)paren
(brace
r_struct
id|tcf_police
op_star
id|p
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|police_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|tcf_police_ht
(braket
id|tcf_police_hash
c_func
(paren
id|index
)paren
)braket
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;index
op_eq
id|index
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|police_lock
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|tcf_police_new_index
r_static
id|__inline__
id|u32
id|tcf_police_new_index
c_func
(paren
r_void
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
op_increment
id|idx_gen
op_eq
l_int|0
)paren
id|idx_gen
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tcf_police_lookup
c_func
(paren
id|idx_gen
)paren
)paren
suffix:semicolon
r_return
id|idx_gen
suffix:semicolon
)brace
DECL|function|tcf_police_destroy
r_void
id|tcf_police_destroy
c_func
(paren
r_struct
id|tcf_police
op_star
id|p
)paren
(brace
r_int
id|h
op_assign
id|tcf_police_hash
c_func
(paren
id|p-&gt;index
)paren
suffix:semicolon
r_struct
id|tcf_police
op_star
op_star
id|p1p
suffix:semicolon
r_for
c_loop
(paren
id|p1p
op_assign
op_amp
id|tcf_police_ht
(braket
id|h
)braket
suffix:semicolon
op_star
id|p1p
suffix:semicolon
id|p1p
op_assign
op_amp
(paren
op_star
id|p1p
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
op_star
id|p1p
op_eq
id|p
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|police_lock
)paren
suffix:semicolon
op_star
id|p1p
op_assign
id|p-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|police_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
id|qdisc_kill_estimator
c_func
(paren
op_amp
id|p-&gt;stats
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|p-&gt;R_tab
)paren
id|qdisc_put_rtab
c_func
(paren
id|p-&gt;R_tab
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;P_tab
)paren
id|qdisc_put_rtab
c_func
(paren
id|p-&gt;P_tab
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|BUG_TRAP
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|tcf_police_locate
r_struct
id|tcf_police
op_star
id|tcf_police_locate
c_func
(paren
r_struct
id|rtattr
op_star
id|rta
comma
r_struct
id|rtattr
op_star
id|est
)paren
(brace
r_int
id|h
suffix:semicolon
r_struct
id|tcf_police
op_star
id|p
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_POLICE_MAX
)braket
suffix:semicolon
r_struct
id|tc_police
op_star
id|parm
suffix:semicolon
r_if
c_cond
(paren
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_POLICE_MAX
comma
id|RTA_DATA
c_func
(paren
id|rta
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|rta
)paren
)paren
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_POLICE_TBF
op_minus
l_int|1
)braket
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|parm
op_assign
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_POLICE_TBF
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parm-&gt;index
op_logical_and
(paren
id|p
op_assign
id|tcf_police_lookup
c_func
(paren
id|parm-&gt;index
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|p-&gt;refcnt
op_increment
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
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
id|p-&gt;refcnt
op_assign
l_int|1
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
id|p-&gt;stats.lock
op_assign
op_amp
id|p-&gt;lock
suffix:semicolon
r_if
c_cond
(paren
id|parm-&gt;rate.rate
)paren
(brace
r_if
c_cond
(paren
(paren
id|p-&gt;R_tab
op_assign
id|qdisc_get_rtab
c_func
(paren
op_amp
id|parm-&gt;rate
comma
id|tb
(braket
id|TCA_POLICE_RATE
op_minus
l_int|1
)braket
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|failure
suffix:semicolon
r_if
c_cond
(paren
id|parm-&gt;peakrate.rate
op_logical_and
(paren
id|p-&gt;P_tab
op_assign
id|qdisc_get_rtab
c_func
(paren
op_amp
id|parm-&gt;peakrate
comma
id|tb
(braket
id|TCA_POLICE_PEAKRATE
op_minus
l_int|1
)braket
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|failure
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tb
(braket
id|TCA_POLICE_RESULT
op_minus
l_int|1
)braket
)paren
id|p-&gt;result
op_assign
op_star
(paren
r_int
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_POLICE_RESULT
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
r_if
c_cond
(paren
id|tb
(braket
id|TCA_POLICE_AVRATE
op_minus
l_int|1
)braket
)paren
id|p-&gt;ewma_rate
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
id|TCA_POLICE_AVRATE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
id|p-&gt;toks
op_assign
id|p-&gt;burst
op_assign
id|parm-&gt;burst
suffix:semicolon
id|p-&gt;mtu
op_assign
id|parm-&gt;mtu
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;mtu
op_eq
l_int|0
)paren
(brace
id|p-&gt;mtu
op_assign
op_complement
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;R_tab
)paren
id|p-&gt;mtu
op_assign
l_int|255
op_lshift
id|p-&gt;R_tab-&gt;rate.cell_log
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;P_tab
)paren
id|p-&gt;ptoks
op_assign
id|L2T_P
c_func
(paren
id|p
comma
id|p-&gt;mtu
)paren
suffix:semicolon
id|PSCHED_GET_TIME
c_func
(paren
id|p-&gt;t_c
)paren
suffix:semicolon
id|p-&gt;index
op_assign
id|parm-&gt;index
ques
c_cond
suffix:colon
id|tcf_police_new_index
c_func
(paren
)paren
suffix:semicolon
id|p-&gt;action
op_assign
id|parm-&gt;action
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
r_if
c_cond
(paren
id|est
)paren
id|qdisc_new_estimator
c_func
(paren
op_amp
id|p-&gt;stats
comma
id|est
)paren
suffix:semicolon
macro_line|#endif
id|h
op_assign
id|tcf_police_hash
c_func
(paren
id|p-&gt;index
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|police_lock
)paren
suffix:semicolon
id|p-&gt;next
op_assign
id|tcf_police_ht
(braket
id|h
)braket
suffix:semicolon
id|tcf_police_ht
(braket
id|h
)braket
op_assign
id|p
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|police_lock
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
id|failure
suffix:colon
r_if
c_cond
(paren
id|p-&gt;R_tab
)paren
id|qdisc_put_rtab
c_func
(paren
id|p-&gt;R_tab
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|tcf_police
r_int
id|tcf_police
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_police
op_star
id|p
)paren
(brace
id|psched_time_t
id|now
suffix:semicolon
r_int
id|toks
suffix:semicolon
r_int
id|ptoks
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
id|p-&gt;stats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|p-&gt;stats.packets
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
r_if
c_cond
(paren
id|p-&gt;ewma_rate
op_logical_and
id|p-&gt;stats.bps
op_ge
id|p-&gt;ewma_rate
)paren
(brace
id|p-&gt;stats.overlimits
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_return
id|p-&gt;action
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|skb-&gt;len
op_le
id|p-&gt;mtu
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;R_tab
op_eq
l_int|NULL
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_return
id|p-&gt;result
suffix:semicolon
)brace
id|PSCHED_GET_TIME
c_func
(paren
id|now
)paren
suffix:semicolon
id|toks
op_assign
id|PSCHED_TDIFF_SAFE
c_func
(paren
id|now
comma
id|p-&gt;t_c
comma
id|p-&gt;burst
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;P_tab
)paren
(brace
id|ptoks
op_assign
id|toks
op_plus
id|p-&gt;ptoks
suffix:semicolon
r_if
c_cond
(paren
id|ptoks
OG
(paren
r_int
)paren
id|L2T_P
c_func
(paren
id|p
comma
id|p-&gt;mtu
)paren
)paren
id|ptoks
op_assign
(paren
r_int
)paren
id|L2T_P
c_func
(paren
id|p
comma
id|p-&gt;mtu
)paren
suffix:semicolon
id|ptoks
op_sub_assign
id|L2T_P
c_func
(paren
id|p
comma
id|skb-&gt;len
)paren
suffix:semicolon
)brace
id|toks
op_add_assign
id|p-&gt;toks
suffix:semicolon
r_if
c_cond
(paren
id|toks
OG
(paren
r_int
)paren
id|p-&gt;burst
)paren
id|toks
op_assign
id|p-&gt;burst
suffix:semicolon
id|toks
op_sub_assign
id|L2T
c_func
(paren
id|p
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|toks
op_or
id|ptoks
)paren
op_ge
l_int|0
)paren
(brace
id|p-&gt;t_c
op_assign
id|now
suffix:semicolon
id|p-&gt;toks
op_assign
id|toks
suffix:semicolon
id|p-&gt;ptoks
op_assign
id|ptoks
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_return
id|p-&gt;result
suffix:semicolon
)brace
)brace
id|p-&gt;stats.overlimits
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_return
id|p-&gt;action
suffix:semicolon
)brace
DECL|function|tcf_police_dump
r_int
id|tcf_police_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_police
op_star
id|p
)paren
(brace
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|tc_police
id|opt
suffix:semicolon
id|opt.index
op_assign
id|p-&gt;index
suffix:semicolon
id|opt.action
op_assign
id|p-&gt;action
suffix:semicolon
id|opt.mtu
op_assign
id|p-&gt;mtu
suffix:semicolon
id|opt.burst
op_assign
id|p-&gt;burst
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;R_tab
)paren
id|opt.rate
op_assign
id|p-&gt;R_tab-&gt;rate
suffix:semicolon
r_else
id|memset
c_func
(paren
op_amp
id|opt.rate
comma
l_int|0
comma
r_sizeof
(paren
id|opt.rate
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;P_tab
)paren
id|opt.peakrate
op_assign
id|p-&gt;P_tab-&gt;rate
suffix:semicolon
r_else
id|memset
c_func
(paren
op_amp
id|opt.peakrate
comma
l_int|0
comma
r_sizeof
(paren
id|opt.peakrate
)paren
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_POLICE_TBF
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
r_if
c_cond
(paren
id|p-&gt;result
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_POLICE_RESULT
comma
r_sizeof
(paren
r_int
)paren
comma
op_amp
id|p-&gt;result
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
r_if
c_cond
(paren
id|p-&gt;ewma_rate
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_POLICE_AVRATE
comma
l_int|4
comma
op_amp
id|p-&gt;ewma_rate
)paren
suffix:semicolon
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
DECL|variable|tcf_police
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police
)paren
suffix:semicolon
DECL|variable|tcf_police_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_destroy
)paren
suffix:semicolon
DECL|variable|tcf_police_dump
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_dump
)paren
suffix:semicolon
DECL|variable|tcf_police_hash
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_hash
)paren
suffix:semicolon
DECL|variable|tcf_police_ht
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_ht
)paren
suffix:semicolon
DECL|variable|tcf_police_locate
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_locate
)paren
suffix:semicolon
DECL|variable|tcf_police_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_lookup
)paren
suffix:semicolon
DECL|variable|tcf_police_new_index
id|EXPORT_SYMBOL
c_func
(paren
id|tcf_police_new_index
)paren
suffix:semicolon
eof
