multiline_comment|/*&n; * net/sched/sch_red.c&t;Random Early Detection queue.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; * Changes:&n; * J Hadi Salim &lt;hadi@nortel.com&gt; 980914:&t;computation fixes&n; * Alexey Makarenko &lt;makar@phoenix.kharkov.ua&gt; 990814: qave on idle link was calculated incorrectly.&n; * J Hadi Salim &lt;hadi@nortelnetworks.com&gt; 980816:  ECN support&t;&n; */
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
macro_line|#include &lt;net/inet_ecn.h&gt;
multiline_comment|/*&t;Random Early Detection (RED) algorithm.&n;&t;=======================================&n;&n;&t;Source: Sally Floyd and Van Jacobson, &quot;Random Early Detection Gateways&n;&t;for Congestion Avoidance&quot;, 1993, IEEE/ACM Transactions on Networking.&n;&n;&t;This file codes a &quot;divisionless&quot; version of RED algorithm&n;&t;as written down in Fig.17 of the paper.&n;&n;Short description.&n;------------------&n;&n;&t;When a new packet arrives we calculate the average queue length:&n;&n;&t;avg = (1-W)*avg + W*current_queue_len,&n;&n;&t;W is the filter time constant (chosen as 2^(-Wlog)), it controls&n;&t;the inertia of the algorithm. To allow larger bursts, W should be&n;&t;decreased.&n;&n;&t;if (avg &gt; th_max) -&gt; packet marked (dropped).&n;&t;if (avg &lt; th_min) -&gt; packet passes.&n;&t;if (th_min &lt; avg &lt; th_max) we calculate probability:&n;&n;&t;Pb = max_P * (avg - th_min)/(th_max-th_min)&n;&n;&t;and mark (drop) packet with this probability.&n;&t;Pb changes from 0 (at avg==th_min) to max_P (avg==th_max).&n;&t;max_P should be small (not 1), usually 0.01..0.02 is good value.&n;&n;&t;max_P is chosen as a number, so that max_P/(th_max-th_min)&n;&t;is a negative power of two in order arithmetics to contain&n;&t;only shifts.&n;&n;&n;&t;Parameters, settable by user:&n;&t;-----------------------------&n;&n;&t;limit&t;&t;- bytes (must be &gt; qth_max + burst)&n;&n;&t;Hard limit on queue length, should be chosen &gt;qth_max&n;&t;to allow packet bursts. This parameter does not&n;&t;affect the algorithms behaviour and can be chosen&n;&t;arbitrarily high (well, less than ram size)&n;&t;Really, this limit will never be reached&n;&t;if RED works correctly.&n;&n;&t;qth_min&t;&t;- bytes (should be &lt; qth_max/2)&n;&t;qth_max&t;&t;- bytes (should be at least 2*qth_min and less limit)&n;&t;Wlog&t;       &t;- bits (&lt;32) log(1/W).&n;&t;Plog&t;       &t;- bits (&lt;32)&n;&n;&t;Plog is related to max_P by formula:&n;&n;&t;max_P = (qth_max-qth_min)/2^Plog;&n;&n;&t;F.e. if qth_max=128K and qth_min=32K, then Plog=22&n;&t;corresponds to max_P=0.02&n;&n;&t;Scell_log&n;&t;Stab&n;&n;&t;Lookup table for log((1-W)^(t/t_ave).&n;&n;&n;NOTES:&n;&n;Upper bound on W.&n;-----------------&n;&n;&t;If you want to allow bursts of L packets of size S,&n;&t;you should choose W:&n;&n;&t;L + 1 - th_min/S &lt; (1-(1-W)^L)/W&n;&n;&t;th_min/S = 32         th_min/S = 4&n;&t;&t;&t;                       &n;&t;log(W)&t;L&n;&t;-1&t;33&n;&t;-2&t;35&n;&t;-3&t;39&n;&t;-4&t;46&n;&t;-5&t;57&n;&t;-6&t;75&n;&t;-7&t;101&n;&t;-8&t;135&n;&t;-9&t;190&n;&t;etc.&n; */
DECL|struct|red_sched_data
r_struct
id|red_sched_data
(brace
multiline_comment|/* Parameters */
DECL|member|limit
id|u32
id|limit
suffix:semicolon
multiline_comment|/* HARD maximal queue length&t;*/
DECL|member|qth_min
id|u32
id|qth_min
suffix:semicolon
multiline_comment|/* Min average length threshold: A scaled */
DECL|member|qth_max
id|u32
id|qth_max
suffix:semicolon
multiline_comment|/* Max average length threshold: A scaled */
DECL|member|Rmask
id|u32
id|Rmask
suffix:semicolon
DECL|member|Scell_max
id|u32
id|Scell_max
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|Wlog
r_char
id|Wlog
suffix:semicolon
multiline_comment|/* log(W)&t;&t;*/
DECL|member|Plog
r_char
id|Plog
suffix:semicolon
multiline_comment|/* random number bits&t;*/
DECL|member|Scell_log
r_char
id|Scell_log
suffix:semicolon
DECL|member|Stab
id|u8
id|Stab
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Variables */
DECL|member|qave
r_int
r_int
id|qave
suffix:semicolon
multiline_comment|/* Average queue length: A scaled */
DECL|member|qcount
r_int
id|qcount
suffix:semicolon
multiline_comment|/* Packets since last random number generation */
DECL|member|qR
id|u32
id|qR
suffix:semicolon
multiline_comment|/* Cached random number */
DECL|member|qidlestart
id|psched_time_t
id|qidlestart
suffix:semicolon
multiline_comment|/* Start of idle period&t;&t;*/
DECL|member|st
r_struct
id|tc_red_xstats
id|st
suffix:semicolon
)brace
suffix:semicolon
DECL|function|red_ecn_mark
r_static
r_int
id|red_ecn_mark
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nh.raw
op_plus
l_int|20
OG
id|skb-&gt;tail
)paren
r_return
l_int|0
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
r_if
c_cond
(paren
op_logical_neg
id|INET_ECN_is_capable
c_func
(paren
id|skb-&gt;nh.iph-&gt;tos
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|INET_ECN_is_not_ce
c_func
(paren
id|skb-&gt;nh.iph-&gt;tos
)paren
)paren
id|IP_ECN_set_ce
c_func
(paren
id|skb-&gt;nh.iph
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IPV6
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|INET_ECN_is_capable
c_func
(paren
id|ip6_get_dsfield
c_func
(paren
id|skb-&gt;nh.ipv6h
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|IP6_ECN_set_ce
c_func
(paren
id|skb-&gt;nh.ipv6h
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|red_enqueue
id|red_enqueue
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
id|red_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|red_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
id|psched_time_t
id|now
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PSCHED_IS_PASTPERFECT
c_func
(paren
id|q-&gt;qidlestart
)paren
)paren
(brace
r_int
id|us_idle
suffix:semicolon
r_int
id|shift
suffix:semicolon
id|PSCHED_GET_TIME
c_func
(paren
id|now
)paren
suffix:semicolon
id|us_idle
op_assign
id|PSCHED_TDIFF_SAFE
c_func
(paren
id|now
comma
id|q-&gt;qidlestart
comma
id|q-&gt;Scell_max
comma
l_int|0
)paren
suffix:semicolon
id|PSCHED_SET_PASTPERFECT
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
multiline_comment|/*&n;   The problem: ideally, average length queue recalcultion should&n;   be done over constant clock intervals. This is too expensive, so that&n;   the calculation is driven by outgoing packets.&n;   When the queue is idle we have to model this clock by hand.&n;&n;   SF+VJ proposed to &quot;generate&quot; m = idletime/(average_pkt_size/bandwidth)&n;   dummy packets as a burst after idle time, i.e.&n;&n;          q-&gt;qave *= (1-W)^m&n;&n;   This is an apparently overcomplicated solution (f.e. we have to precompute&n;   a table to make this calculation in reasonable time)&n;   I believe that a simpler model may be used here,&n;   but it is field for experiments.&n;*/
id|shift
op_assign
id|q-&gt;Stab
(braket
id|us_idle
op_rshift
id|q-&gt;Scell_log
)braket
suffix:semicolon
r_if
c_cond
(paren
id|shift
)paren
(brace
id|q-&gt;qave
op_rshift_assign
id|shift
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Approximate initial part of exponent&n;&t;&t;&t;   with linear function:&n;&t;&t;&t;   (1-W)^m ~= 1-mW + ...&n;&n;&t;&t;&t;   Seems, it is the best solution to&n;&t;&t;&t;   problem of too coarce exponent tabulation.&n;&t;&t;&t; */
id|us_idle
op_assign
(paren
id|q-&gt;qave
op_star
id|us_idle
)paren
op_rshift
id|q-&gt;Scell_log
suffix:semicolon
r_if
c_cond
(paren
id|us_idle
OL
id|q-&gt;qave
op_div
l_int|2
)paren
id|q-&gt;qave
op_sub_assign
id|us_idle
suffix:semicolon
r_else
id|q-&gt;qave
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|q-&gt;qave
op_add_assign
id|sch-&gt;stats.backlog
op_minus
(paren
id|q-&gt;qave
op_rshift
id|q-&gt;Wlog
)paren
suffix:semicolon
multiline_comment|/* NOTE:&n;&t;&t;   q-&gt;qave is fixed point number with point at Wlog.&n;&t;&t;   The formulae above is equvalent to floating point&n;&t;&t;   version:&n;&n;&t;&t;   qave = qave*(1-W) + sch-&gt;stats.backlog*W;&n;&t;&t;                                           --ANK (980924)&n;&t;&t; */
)brace
r_if
c_cond
(paren
id|q-&gt;qave
OL
id|q-&gt;qth_min
)paren
(brace
id|q-&gt;qcount
op_assign
op_minus
l_int|1
suffix:semicolon
id|enqueue
suffix:colon
r_if
c_cond
(paren
id|sch-&gt;stats.backlog
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
id|sch-&gt;stats.backlog
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;stats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;stats.packets
op_increment
suffix:semicolon
r_return
id|NET_XMIT_SUCCESS
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;st.pdrop
op_increment
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sch-&gt;stats.drops
op_increment
suffix:semicolon
r_return
id|NET_XMIT_DROP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|q-&gt;qave
op_ge
id|q-&gt;qth_max
)paren
(brace
id|q-&gt;qcount
op_assign
op_minus
l_int|1
suffix:semicolon
id|sch-&gt;stats.overlimits
op_increment
suffix:semicolon
id|mark
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|q-&gt;flags
op_amp
id|TC_RED_ECN
)paren
op_logical_or
op_logical_neg
id|red_ecn_mark
c_func
(paren
id|skb
)paren
)paren
(brace
id|q-&gt;st.early
op_increment
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|q-&gt;st.marked
op_increment
suffix:semicolon
r_goto
id|enqueue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|q-&gt;qcount
)paren
(brace
multiline_comment|/* The formula used below causes questions.&n;&n;&t;&t;   OK. qR is random number in the interval 0..Rmask&n;&t;&t;   i.e. 0..(2^Plog). If we used floating point&n;&t;&t;   arithmetics, it would be: (2^Plog)*rnd_num,&n;&t;&t;   where rnd_num is less 1.&n;&n;&t;&t;   Taking into account, that qave have fixed&n;&t;&t;   point at Wlog, and Plog is related to max_P by&n;&t;&t;   max_P = (qth_max-qth_min)/2^Plog; two lines&n;&t;&t;   below have the following floating point equivalent:&n;&t;&t;   &n;&t;&t;   max_P*(qave - qth_min)/(qth_max-qth_min) &lt; rnd/qcount&n;&n;&t;&t;   Any questions? --ANK (980924)&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|q-&gt;qave
op_minus
id|q-&gt;qth_min
)paren
op_rshift
id|q-&gt;Wlog
)paren
op_star
id|q-&gt;qcount
OL
id|q-&gt;qR
)paren
r_goto
id|enqueue
suffix:semicolon
id|q-&gt;qcount
op_assign
l_int|0
suffix:semicolon
id|q-&gt;qR
op_assign
id|net_random
c_func
(paren
)paren
op_amp
id|q-&gt;Rmask
suffix:semicolon
id|sch-&gt;stats.overlimits
op_increment
suffix:semicolon
r_goto
id|mark
suffix:semicolon
)brace
id|q-&gt;qR
op_assign
id|net_random
c_func
(paren
)paren
op_amp
id|q-&gt;Rmask
suffix:semicolon
r_goto
id|enqueue
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sch-&gt;stats.drops
op_increment
suffix:semicolon
r_return
id|NET_XMIT_CN
suffix:semicolon
)brace
r_static
r_int
DECL|function|red_requeue
id|red_requeue
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
id|red_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|red_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
id|PSCHED_SET_PASTPERFECT
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
id|__skb_queue_head
c_func
(paren
op_amp
id|sch-&gt;q
comma
id|skb
)paren
suffix:semicolon
id|sch-&gt;stats.backlog
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
DECL|function|red_dequeue
id|red_dequeue
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
id|red_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|red_sched_data
op_star
)paren
id|sch-&gt;data
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
(brace
id|sch-&gt;stats.backlog
op_sub_assign
id|skb-&gt;len
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
id|PSCHED_GET_TIME
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|red_drop
r_static
r_int
r_int
id|red_drop
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
id|red_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|red_sched_data
op_star
)paren
id|sch-&gt;data
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
id|sch-&gt;stats.backlog
op_sub_assign
id|len
suffix:semicolon
id|sch-&gt;stats.drops
op_increment
suffix:semicolon
id|q-&gt;st.other
op_increment
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
id|PSCHED_GET_TIME
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|red_reset
r_static
r_void
id|red_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|red_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|red_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
id|__skb_queue_purge
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
id|sch-&gt;stats.backlog
op_assign
l_int|0
suffix:semicolon
id|PSCHED_SET_PASTPERFECT
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
id|q-&gt;qave
op_assign
l_int|0
suffix:semicolon
id|q-&gt;qcount
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|red_change
r_static
r_int
id|red_change
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
id|red_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|red_sched_data
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_RED_STAB
)braket
suffix:semicolon
r_struct
id|tc_red_qopt
op_star
id|ctl
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
op_logical_or
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_RED_STAB
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
op_logical_or
id|tb
(braket
id|TCA_RED_PARMS
op_minus
l_int|1
)braket
op_eq
l_int|0
op_logical_or
id|tb
(braket
id|TCA_RED_STAB
op_minus
l_int|1
)braket
op_eq
l_int|0
op_logical_or
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_RED_PARMS
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
op_star
id|ctl
)paren
op_logical_or
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_RED_STAB
op_minus
l_int|1
)braket
)paren
OL
l_int|256
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ctl
op_assign
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_RED_PARMS
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|sch_tree_lock
c_func
(paren
id|sch
)paren
suffix:semicolon
id|q-&gt;flags
op_assign
id|ctl-&gt;flags
suffix:semicolon
id|q-&gt;Wlog
op_assign
id|ctl-&gt;Wlog
suffix:semicolon
id|q-&gt;Plog
op_assign
id|ctl-&gt;Plog
suffix:semicolon
id|q-&gt;Rmask
op_assign
id|ctl-&gt;Plog
OL
l_int|32
ques
c_cond
(paren
(paren
l_int|1
op_lshift
id|ctl-&gt;Plog
)paren
op_minus
l_int|1
)paren
suffix:colon
op_complement
l_int|0UL
suffix:semicolon
id|q-&gt;Scell_log
op_assign
id|ctl-&gt;Scell_log
suffix:semicolon
id|q-&gt;Scell_max
op_assign
(paren
l_int|255
op_lshift
id|q-&gt;Scell_log
)paren
suffix:semicolon
id|q-&gt;qth_min
op_assign
id|ctl-&gt;qth_min
op_lshift
id|ctl-&gt;Wlog
suffix:semicolon
id|q-&gt;qth_max
op_assign
id|ctl-&gt;qth_max
op_lshift
id|ctl-&gt;Wlog
suffix:semicolon
id|q-&gt;limit
op_assign
id|ctl-&gt;limit
suffix:semicolon
id|memcpy
c_func
(paren
id|q-&gt;Stab
comma
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_RED_STAB
op_minus
l_int|1
)braket
)paren
comma
l_int|256
)paren
suffix:semicolon
id|q-&gt;qcount
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|sch-&gt;q
)paren
op_eq
l_int|0
)paren
id|PSCHED_SET_PASTPERFECT
c_func
(paren
id|q-&gt;qidlestart
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
DECL|function|red_init
r_static
r_int
id|red_init
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
r_return
id|red_change
c_func
(paren
id|sch
comma
id|opt
)paren
suffix:semicolon
)brace
DECL|function|red_copy_xstats
r_int
id|red_copy_xstats
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_red_xstats
op_star
id|st
)paren
(brace
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_XSTATS
comma
r_sizeof
(paren
op_star
id|st
)paren
comma
id|st
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|rtattr_failure
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|red_dump
r_static
r_int
id|red_dump
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
id|red_sched_data
op_star
id|q
op_assign
(paren
r_struct
id|red_sched_data
op_star
)paren
id|sch-&gt;data
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
r_struct
id|tc_red_qopt
id|opt
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
id|opt.limit
op_assign
id|q-&gt;limit
suffix:semicolon
id|opt.qth_min
op_assign
id|q-&gt;qth_min
op_rshift
id|q-&gt;Wlog
suffix:semicolon
id|opt.qth_max
op_assign
id|q-&gt;qth_max
op_rshift
id|q-&gt;Wlog
suffix:semicolon
id|opt.Wlog
op_assign
id|q-&gt;Wlog
suffix:semicolon
id|opt.Plog
op_assign
id|q-&gt;Plog
suffix:semicolon
id|opt.Scell_log
op_assign
id|q-&gt;Scell_log
suffix:semicolon
id|opt.flags
op_assign
id|q-&gt;flags
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_RED_PARMS
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
id|rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
r_if
c_cond
(paren
id|red_copy_xstats
c_func
(paren
id|skb
comma
op_amp
id|q-&gt;st
)paren
)paren
r_goto
id|rtattr_failure
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
DECL|function|red_destroy
r_static
r_void
id|red_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
)brace
DECL|variable|red_qdisc_ops
r_static
r_struct
id|Qdisc_ops
id|red_qdisc_ops
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
l_string|&quot;red&quot;
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|red_sched_data
)paren
comma
dot
id|enqueue
op_assign
id|red_enqueue
comma
dot
id|dequeue
op_assign
id|red_dequeue
comma
dot
id|requeue
op_assign
id|red_requeue
comma
dot
id|drop
op_assign
id|red_drop
comma
dot
id|init
op_assign
id|red_init
comma
dot
id|reset
op_assign
id|red_reset
comma
dot
id|destroy
op_assign
id|red_destroy
comma
dot
id|change
op_assign
id|red_change
comma
dot
id|dump
op_assign
id|red_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|red_module_init
r_static
r_int
id|__init
id|red_module_init
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
id|red_qdisc_ops
)paren
suffix:semicolon
)brace
DECL|function|red_module_exit
r_static
r_void
id|__exit
id|red_module_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_qdisc
c_func
(paren
op_amp
id|red_qdisc_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|red_module_init
)paren
id|module_exit
c_func
(paren
id|red_module_exit
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
