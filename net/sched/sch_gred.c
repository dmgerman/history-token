multiline_comment|/*&n; * net/sched/sch_gred.c&t;Generic Random Early Detection queue.&n; *&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Authors:    J Hadi Salim (hadi@cyberus.ca) 1998-2002&n; *&n; *             991129: -  Bug fix with grio mode&n; *&t;&t;       - a better sing. AvgQ mode with Grio(WRED)&n; *&t;&t;       - A finer grained VQ dequeue based on sugestion&n; *&t;&t;         from Ren Liu&n; *&t;&t;       - More error checks&n; *&n; *&n; *&n; *  For all the glorious comments look at Alexey&squot;s sch_red.c&n; */
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
r_struct
id|gred_sched_data
suffix:semicolon
r_struct
id|gred_sched
suffix:semicolon
DECL|struct|gred_sched_data
r_struct
id|gred_sched_data
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
DECL|member|DP
id|u32
id|DP
suffix:semicolon
multiline_comment|/* the drop pramaters */
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
DECL|member|Scell_max
id|u32
id|Scell_max
suffix:semicolon
DECL|member|Rmask
id|u32
id|Rmask
suffix:semicolon
DECL|member|bytesin
id|u32
id|bytesin
suffix:semicolon
multiline_comment|/* bytes seen on virtualQ so far*/
DECL|member|packetsin
id|u32
id|packetsin
suffix:semicolon
multiline_comment|/* packets seen on virtualQ so far*/
DECL|member|backlog
id|u32
id|backlog
suffix:semicolon
multiline_comment|/* bytes on the virtualQ */
DECL|member|forced
id|u32
id|forced
suffix:semicolon
multiline_comment|/* packets dropped for exceeding limits */
DECL|member|early
id|u32
id|early
suffix:semicolon
multiline_comment|/* packets dropped as a warning */
DECL|member|other
id|u32
id|other
suffix:semicolon
multiline_comment|/* packets dropped by invoking drop() */
DECL|member|pdrop
id|u32
id|pdrop
suffix:semicolon
multiline_comment|/* packets dropped because we exceeded physical queue limits */
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
DECL|member|prio
id|u8
id|prio
suffix:semicolon
multiline_comment|/* the prio of this vq */
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
multiline_comment|/* Start of idle period&t;*/
)brace
suffix:semicolon
DECL|struct|gred_sched
r_struct
id|gred_sched
(brace
DECL|member|tab
r_struct
id|gred_sched_data
op_star
id|tab
(braket
id|MAX_DPs
)braket
suffix:semicolon
DECL|member|DPs
id|u32
id|DPs
suffix:semicolon
DECL|member|def
id|u32
id|def
suffix:semicolon
DECL|member|initd
id|u8
id|initd
suffix:semicolon
DECL|member|grio
id|u8
id|grio
suffix:semicolon
DECL|member|eqp
id|u8
id|eqp
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|gred_enqueue
id|gred_enqueue
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
id|psched_time_t
id|now
suffix:semicolon
r_struct
id|gred_sched_data
op_star
id|q
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|gred_sched
op_star
id|t
op_assign
(paren
r_struct
id|gred_sched
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_int
r_int
id|qave
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;initd
op_logical_and
id|skb_queue_len
c_func
(paren
op_amp
id|sch-&gt;q
)paren
op_le
id|sch-&gt;dev-&gt;tx_queue_len
)paren
(brace
id|D2PRINTK
c_func
(paren
l_string|&quot;NO GRED Queues setup yet! Enqueued anyway&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|do_enqueue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|skb-&gt;tc_index
op_amp
l_int|0xf
)paren
OG
(paren
id|t-&gt;DPs
op_minus
l_int|1
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|q
op_assign
id|t-&gt;tab
(braket
id|skb-&gt;tc_index
op_amp
l_int|0xf
)braket
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;GRED: setting to default (%d)&bslash;n &quot;
comma
id|t-&gt;def
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|q
op_assign
id|t-&gt;tab
(braket
id|t-&gt;def
)braket
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;GRED: setting to default FAILED! dropping!! &quot;
l_string|&quot;(%d)&bslash;n &quot;
comma
id|t-&gt;def
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
multiline_comment|/* fix tc_index? --could be controvesial but needed for&n;&t;&t;   requeueing */
id|skb-&gt;tc_index
op_assign
(paren
id|skb-&gt;tc_index
op_amp
l_int|0xfffffff0
)paren
op_or
id|t-&gt;def
suffix:semicolon
)brace
id|D2PRINTK
c_func
(paren
l_string|&quot;gred_enqueue virtualQ 0x%x classid %x backlog %d &quot;
l_string|&quot;general backlog %d&bslash;n&quot;
comma
id|skb-&gt;tc_index
op_amp
l_int|0xf
comma
id|sch-&gt;handle
comma
id|q-&gt;backlog
comma
id|sch-&gt;stats.backlog
)paren
suffix:semicolon
multiline_comment|/* sum up all the qaves of prios &lt;= to ours to get the new qave*/
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;eqp
op_logical_and
id|t-&gt;grio
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|t-&gt;DPs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|t-&gt;tab
(braket
id|i
)braket
)paren
op_logical_or
(paren
id|i
op_eq
id|q-&gt;DP
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t-&gt;tab
(braket
id|i
)braket
op_member_access_from_pointer
id|prio
OL
id|q-&gt;prio
)paren
op_logical_and
(paren
id|PSCHED_IS_PASTPERFECT
c_func
(paren
id|t-&gt;tab
(braket
id|i
)braket
op_member_access_from_pointer
id|qidlestart
)paren
)paren
)paren
id|qave
op_add_assign
id|t-&gt;tab
(braket
id|i
)braket
op_member_access_from_pointer
id|qave
suffix:semicolon
)brace
)brace
id|q-&gt;packetsin
op_increment
suffix:semicolon
id|q-&gt;bytesin
op_add_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;eqp
op_logical_and
id|t-&gt;grio
)paren
(brace
id|qave
op_assign
l_int|0
suffix:semicolon
id|q-&gt;qave
op_assign
id|t-&gt;tab
(braket
id|t-&gt;def
)braket
op_member_access_from_pointer
id|qave
suffix:semicolon
id|q-&gt;qidlestart
op_assign
id|t-&gt;tab
(braket
id|t-&gt;def
)braket
op_member_access_from_pointer
id|qidlestart
suffix:semicolon
)brace
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
id|q-&gt;qave
op_rshift_assign
id|q-&gt;Stab
(braket
(paren
id|us_idle
op_rshift
id|q-&gt;Scell_log
)paren
op_amp
l_int|0xFF
)braket
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|t-&gt;eqp
)paren
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
)brace
r_else
(brace
id|q-&gt;qave
op_add_assign
id|q-&gt;backlog
op_minus
(paren
id|q-&gt;qave
op_rshift
id|q-&gt;Wlog
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|t-&gt;eqp
op_logical_and
id|t-&gt;grio
)paren
id|t-&gt;tab
(braket
id|t-&gt;def
)braket
op_member_access_from_pointer
id|qave
op_assign
id|q-&gt;qave
suffix:semicolon
r_if
c_cond
(paren
(paren
id|q-&gt;qave
op_plus
id|qave
)paren
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
id|q-&gt;backlog
op_le
id|q-&gt;limit
)paren
(brace
id|q-&gt;backlog
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|do_enqueue
suffix:colon
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
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;pdrop
op_increment
suffix:semicolon
)brace
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
id|NET_XMIT_DROP
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|q-&gt;qave
op_plus
id|qave
)paren
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
id|q-&gt;forced
op_increment
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|q-&gt;qcount
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
(paren
id|qave
op_plus
id|q-&gt;qave
)paren
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
id|q-&gt;early
op_increment
suffix:semicolon
r_goto
id|drop
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
)brace
r_static
r_int
DECL|function|gred_requeue
id|gred_requeue
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
id|gred_sched_data
op_star
id|q
suffix:semicolon
r_struct
id|gred_sched
op_star
id|t
op_assign
(paren
r_struct
id|gred_sched
op_star
)paren
id|sch-&gt;data
suffix:semicolon
id|q
op_assign
id|t-&gt;tab
(braket
(paren
id|skb-&gt;tc_index
op_amp
l_int|0xf
)paren
)braket
suffix:semicolon
multiline_comment|/* error checking here -- probably unnecessary */
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
id|q-&gt;backlog
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
DECL|function|gred_dequeue
id|gred_dequeue
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
id|gred_sched_data
op_star
id|q
suffix:semicolon
r_struct
id|gred_sched
op_star
id|t
op_assign
(paren
r_struct
id|gred_sched
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
id|q
op_assign
id|t-&gt;tab
(braket
(paren
id|skb-&gt;tc_index
op_amp
l_int|0xf
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
id|q-&gt;backlog
op_sub_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;backlog
op_logical_and
op_logical_neg
id|t-&gt;eqp
)paren
id|PSCHED_GET_TIME
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
)brace
r_else
(brace
id|D2PRINTK
c_func
(paren
l_string|&quot;gred_dequeue: skb has bad tcindex %x&bslash;n&quot;
comma
id|skb-&gt;tc_index
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t-&gt;eqp
)paren
(brace
id|q
op_assign
id|t-&gt;tab
(braket
id|t-&gt;def
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
id|D2PRINTK
c_func
(paren
l_string|&quot;no default VQ set: Results will be &quot;
l_string|&quot;screwed up&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|PSCHED_GET_TIME
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|gred_drop
id|gred_drop
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
id|gred_sched_data
op_star
id|q
suffix:semicolon
r_struct
id|gred_sched
op_star
id|t
op_assign
(paren
r_struct
id|gred_sched
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
id|sch-&gt;stats.backlog
op_sub_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;stats.drops
op_increment
suffix:semicolon
id|q
op_assign
id|t-&gt;tab
(braket
(paren
id|skb-&gt;tc_index
op_amp
l_int|0xf
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
id|q-&gt;backlog
op_sub_assign
id|skb-&gt;len
suffix:semicolon
id|q-&gt;other
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;backlog
op_logical_and
op_logical_neg
id|t-&gt;eqp
)paren
id|PSCHED_GET_TIME
c_func
(paren
id|q-&gt;qidlestart
)paren
suffix:semicolon
)brace
r_else
(brace
id|D2PRINTK
c_func
(paren
l_string|&quot;gred_dequeue: skb has bad tcindex %x&bslash;n&quot;
comma
id|skb-&gt;tc_index
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|q
op_assign
id|t-&gt;tab
(braket
id|t-&gt;def
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
(brace
id|D2PRINTK
c_func
(paren
l_string|&quot;no default VQ set: Results might be screwed up&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
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
DECL|function|gred_reset
r_static
r_void
id|gred_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|gred_sched_data
op_star
id|q
suffix:semicolon
r_struct
id|gred_sched
op_star
id|t
op_assign
(paren
r_struct
id|gred_sched
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|t-&gt;DPs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|q
op_assign
id|t-&gt;tab
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
r_continue
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
id|q-&gt;backlog
op_assign
l_int|0
suffix:semicolon
id|q-&gt;other
op_assign
l_int|0
suffix:semicolon
id|q-&gt;forced
op_assign
l_int|0
suffix:semicolon
id|q-&gt;pdrop
op_assign
l_int|0
suffix:semicolon
id|q-&gt;early
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|gred_change
r_static
r_int
id|gred_change
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
id|gred_sched
op_star
id|table
op_assign
(paren
r_struct
id|gred_sched
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_struct
id|gred_sched_data
op_star
id|q
suffix:semicolon
r_struct
id|tc_gred_qopt
op_star
id|ctl
suffix:semicolon
r_struct
id|tc_gred_sopt
op_star
id|sopt
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_GRED_STAB
)braket
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb2
(braket
id|TCA_GRED_DPS
)braket
suffix:semicolon
r_int
id|i
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
id|TCA_GRED_STAB
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
id|TCA_GRED_PARMS
op_minus
l_int|1
)braket
op_eq
l_int|0
op_logical_and
id|tb
(braket
id|TCA_GRED_STAB
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
(brace
id|rtattr_parse
c_func
(paren
id|tb2
comma
id|TCA_GRED_DPS
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
suffix:semicolon
r_if
c_cond
(paren
id|tb2
(braket
id|TCA_GRED_DPS
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sopt
op_assign
id|RTA_DATA
c_func
(paren
id|tb2
(braket
id|TCA_GRED_DPS
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|table-&gt;DPs
op_assign
id|sopt-&gt;DPs
suffix:semicolon
id|table-&gt;def
op_assign
id|sopt-&gt;def_DP
suffix:semicolon
id|table-&gt;grio
op_assign
id|sopt-&gt;grio
suffix:semicolon
id|table-&gt;initd
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* probably need to clear all the table DP entries as well */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|table-&gt;DPs
op_logical_or
id|tb
(braket
id|TCA_GRED_PARMS
op_minus
l_int|1
)braket
op_eq
l_int|0
op_logical_or
id|tb
(braket
id|TCA_GRED_STAB
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
id|TCA_GRED_PARMS
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
id|TCA_GRED_STAB
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
id|TCA_GRED_PARMS
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctl-&gt;DP
OG
id|MAX_DPs
op_minus
l_int|1
)paren
(brace
multiline_comment|/* misbehaving is punished! Put in the default drop probability */
id|DPRINTK
c_func
(paren
l_string|&quot;&bslash;nGRED: DP %u not in  the proper range fixed. New DP &quot;
l_string|&quot;set to default at %d&bslash;n&quot;
comma
id|ctl-&gt;DP
comma
id|table-&gt;def
)paren
suffix:semicolon
id|ctl-&gt;DP
op_assign
id|table-&gt;def
suffix:semicolon
)brace
r_if
c_cond
(paren
id|table-&gt;tab
(braket
id|ctl-&gt;DP
)braket
op_eq
l_int|NULL
)paren
(brace
id|table-&gt;tab
(braket
id|ctl-&gt;DP
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|gred_sched_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|table-&gt;tab
(braket
id|ctl-&gt;DP
)braket
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|table-&gt;tab
(braket
id|ctl-&gt;DP
)braket
comma
l_int|0
comma
(paren
r_sizeof
(paren
r_struct
id|gred_sched_data
)paren
)paren
)paren
suffix:semicolon
)brace
id|q
op_assign
id|table-&gt;tab
(braket
id|ctl-&gt;DP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|table-&gt;grio
)paren
(brace
r_if
c_cond
(paren
id|ctl-&gt;prio
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|table-&gt;def
op_logical_and
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;&bslash;nGRED: DP %u does not have a prio&quot;
l_string|&quot;setting default to %d&bslash;n&quot;
comma
id|ctl-&gt;DP
comma
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
op_member_access_from_pointer
id|prio
)paren
suffix:semicolon
id|q-&gt;prio
op_assign
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
op_member_access_from_pointer
id|prio
suffix:semicolon
)brace
r_else
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;&bslash;nGRED: DP %u does not have a prio&quot;
l_string|&quot; setting default to 8&bslash;n&quot;
comma
id|ctl-&gt;DP
)paren
suffix:semicolon
id|q-&gt;prio
op_assign
l_int|8
suffix:semicolon
)brace
)brace
r_else
(brace
id|q-&gt;prio
op_assign
id|ctl-&gt;prio
suffix:semicolon
)brace
)brace
r_else
(brace
id|q-&gt;prio
op_assign
l_int|8
suffix:semicolon
)brace
id|q-&gt;DP
op_assign
id|ctl-&gt;DP
suffix:semicolon
id|q-&gt;Wlog
op_assign
id|ctl-&gt;Wlog
suffix:semicolon
id|q-&gt;Plog
op_assign
id|ctl-&gt;Plog
suffix:semicolon
id|q-&gt;limit
op_assign
id|ctl-&gt;limit
suffix:semicolon
id|q-&gt;Scell_log
op_assign
id|ctl-&gt;Scell_log
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
id|q-&gt;qave
op_assign
l_int|0
suffix:semicolon
id|q-&gt;backlog
op_assign
l_int|0
suffix:semicolon
id|q-&gt;qcount
op_assign
op_minus
l_int|1
suffix:semicolon
id|q-&gt;other
op_assign
l_int|0
suffix:semicolon
id|q-&gt;forced
op_assign
l_int|0
suffix:semicolon
id|q-&gt;pdrop
op_assign
l_int|0
suffix:semicolon
id|q-&gt;early
op_assign
l_int|0
suffix:semicolon
id|PSCHED_SET_PASTPERFECT
c_func
(paren
id|q-&gt;qidlestart
)paren
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
id|TCA_GRED_STAB
op_minus
l_int|1
)braket
)paren
comma
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
id|table-&gt;initd
op_logical_and
id|table-&gt;grio
)paren
(brace
multiline_comment|/* this looks ugly but it&squot;s not in the fast path */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|table-&gt;DPs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|table-&gt;tab
(braket
id|i
)braket
)paren
op_logical_or
(paren
id|i
op_eq
id|q-&gt;DP
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|table-&gt;tab
(braket
id|i
)braket
op_member_access_from_pointer
id|prio
op_eq
id|q-&gt;prio
)paren
(brace
multiline_comment|/* WRED mode detected */
id|table-&gt;eqp
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|table-&gt;initd
)paren
(brace
id|table-&gt;initd
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* &n;        &t;the first entry also goes into the default until&n;        &t;over-written &n;&t;&t;*/
r_if
c_cond
(paren
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
op_eq
l_int|NULL
)paren
(brace
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|gred_sched_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
comma
l_int|0
comma
(paren
r_sizeof
(paren
r_struct
id|gred_sched_data
)paren
)paren
)paren
suffix:semicolon
)brace
id|q
op_assign
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
suffix:semicolon
id|q-&gt;DP
op_assign
id|table-&gt;def
suffix:semicolon
id|q-&gt;Wlog
op_assign
id|ctl-&gt;Wlog
suffix:semicolon
id|q-&gt;Plog
op_assign
id|ctl-&gt;Plog
suffix:semicolon
id|q-&gt;limit
op_assign
id|ctl-&gt;limit
suffix:semicolon
id|q-&gt;Scell_log
op_assign
id|ctl-&gt;Scell_log
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
r_if
c_cond
(paren
id|table-&gt;grio
)paren
id|q-&gt;prio
op_assign
id|table-&gt;tab
(braket
id|ctl-&gt;DP
)braket
op_member_access_from_pointer
id|prio
suffix:semicolon
r_else
id|q-&gt;prio
op_assign
l_int|8
suffix:semicolon
id|q-&gt;qcount
op_assign
op_minus
l_int|1
suffix:semicolon
id|PSCHED_SET_PASTPERFECT
c_func
(paren
id|q-&gt;qidlestart
)paren
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
id|TCA_GRED_STAB
op_minus
l_int|1
)braket
)paren
comma
l_int|256
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gred_init
r_static
r_int
id|gred_init
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
id|gred_sched
op_star
id|table
op_assign
(paren
r_struct
id|gred_sched
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_struct
id|tc_gred_sopt
op_star
id|sopt
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_GRED_STAB
)braket
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb2
(braket
id|TCA_GRED_DPS
)braket
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
id|TCA_GRED_STAB
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
id|TCA_GRED_PARMS
op_minus
l_int|1
)braket
op_eq
l_int|0
op_logical_and
id|tb
(braket
id|TCA_GRED_STAB
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
(brace
id|rtattr_parse
c_func
(paren
id|tb2
comma
id|TCA_GRED_DPS
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
suffix:semicolon
r_if
c_cond
(paren
id|tb2
(braket
id|TCA_GRED_DPS
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sopt
op_assign
id|RTA_DATA
c_func
(paren
id|tb2
(braket
id|TCA_GRED_DPS
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|table-&gt;DPs
op_assign
id|sopt-&gt;DPs
suffix:semicolon
id|table-&gt;def
op_assign
id|sopt-&gt;def_DP
suffix:semicolon
id|table-&gt;grio
op_assign
id|sopt-&gt;grio
suffix:semicolon
id|table-&gt;initd
op_assign
l_int|0
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;&bslash;n GRED_INIT error!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|gred_dump
r_static
r_int
id|gred_dump
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
r_int
r_int
id|qave
suffix:semicolon
r_struct
id|rtattr
op_star
id|rta
suffix:semicolon
r_struct
id|tc_gred_qopt
op_star
id|opt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|tc_gred_qopt
op_star
id|dst
suffix:semicolon
r_struct
id|gred_sched
op_star
id|table
op_assign
(paren
r_struct
id|gred_sched
op_star
)paren
id|sch-&gt;data
suffix:semicolon
r_struct
id|gred_sched_data
op_star
id|q
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
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
id|opt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tc_gred_qopt
)paren
op_star
id|MAX_DPs
comma
id|GFP_KERNEL
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
id|DPRINTK
c_func
(paren
l_string|&quot;gred_dump:failed to malloc for %Zd&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|tc_gred_qopt
)paren
op_star
id|MAX_DPs
)paren
suffix:semicolon
r_goto
id|rtattr_failure
suffix:semicolon
)brace
id|memset
c_func
(paren
id|opt
comma
l_int|0
comma
(paren
r_sizeof
(paren
r_struct
id|tc_gred_qopt
)paren
)paren
op_star
id|table-&gt;DPs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table-&gt;initd
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;NO GRED Queues setup!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DPs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dst
op_assign
op_amp
id|opt
(braket
id|i
)braket
suffix:semicolon
id|q
op_assign
id|table-&gt;tab
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
(brace
multiline_comment|/* hack -- fix at some point with proper message&n;&t;&t;&t;   This is how we indicate to tc that there is no VQ&n;&t;&t;&t;   at this DP */
id|dst-&gt;DP
op_assign
id|MAX_DPs
op_plus
id|i
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dst-&gt;limit
op_assign
id|q-&gt;limit
suffix:semicolon
id|dst-&gt;qth_min
op_assign
id|q-&gt;qth_min
op_rshift
id|q-&gt;Wlog
suffix:semicolon
id|dst-&gt;qth_max
op_assign
id|q-&gt;qth_max
op_rshift
id|q-&gt;Wlog
suffix:semicolon
id|dst-&gt;DP
op_assign
id|q-&gt;DP
suffix:semicolon
id|dst-&gt;backlog
op_assign
id|q-&gt;backlog
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;qave
)paren
(brace
r_if
c_cond
(paren
id|table-&gt;eqp
op_logical_and
id|table-&gt;grio
)paren
(brace
id|q-&gt;qidlestart
op_assign
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
op_member_access_from_pointer
id|qidlestart
suffix:semicolon
id|q-&gt;qave
op_assign
id|table-&gt;tab
(braket
id|table-&gt;def
)braket
op_member_access_from_pointer
id|qave
suffix:semicolon
)brace
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
id|idle
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
id|idle
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
id|qave
op_assign
id|q-&gt;qave
op_rshift
id|q-&gt;Stab
(braket
(paren
id|idle
op_rshift
id|q-&gt;Scell_log
)paren
op_amp
l_int|0xFF
)braket
suffix:semicolon
id|dst-&gt;qave
op_assign
id|qave
op_rshift
id|q-&gt;Wlog
suffix:semicolon
)brace
r_else
(brace
id|dst-&gt;qave
op_assign
id|q-&gt;qave
op_rshift
id|q-&gt;Wlog
suffix:semicolon
)brace
)brace
r_else
(brace
id|dst-&gt;qave
op_assign
l_int|0
suffix:semicolon
)brace
id|dst-&gt;Wlog
op_assign
id|q-&gt;Wlog
suffix:semicolon
id|dst-&gt;Plog
op_assign
id|q-&gt;Plog
suffix:semicolon
id|dst-&gt;Scell_log
op_assign
id|q-&gt;Scell_log
suffix:semicolon
id|dst-&gt;other
op_assign
id|q-&gt;other
suffix:semicolon
id|dst-&gt;forced
op_assign
id|q-&gt;forced
suffix:semicolon
id|dst-&gt;early
op_assign
id|q-&gt;early
suffix:semicolon
id|dst-&gt;pdrop
op_assign
id|q-&gt;pdrop
suffix:semicolon
id|dst-&gt;prio
op_assign
id|q-&gt;prio
suffix:semicolon
id|dst-&gt;packets
op_assign
id|q-&gt;packetsin
suffix:semicolon
id|dst-&gt;bytesin
op_assign
id|q-&gt;bytesin
suffix:semicolon
)brace
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_GRED_PARMS
comma
r_sizeof
(paren
r_struct
id|tc_gred_qopt
)paren
op_star
id|MAX_DPs
comma
id|opt
)paren
suffix:semicolon
id|rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
id|kfree
c_func
(paren
id|opt
)paren
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|rtattr_failure
suffix:colon
r_if
c_cond
(paren
id|opt
)paren
id|kfree
c_func
(paren
id|opt
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;gred_dump: FAILURE!!!!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* also free the opt struct here */
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
DECL|function|gred_destroy
r_static
r_void
id|gred_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|gred_sched
op_star
id|table
op_assign
(paren
r_struct
id|gred_sched
op_star
)paren
id|sch-&gt;data
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
id|table-&gt;DPs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|table-&gt;tab
(braket
id|i
)braket
)paren
id|kfree
c_func
(paren
id|table-&gt;tab
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|gred_qdisc_ops
r_struct
id|Qdisc_ops
id|gred_qdisc_ops
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
l_string|&quot;gred&quot;
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|gred_sched
)paren
comma
dot
id|enqueue
op_assign
id|gred_enqueue
comma
dot
id|dequeue
op_assign
id|gred_dequeue
comma
dot
id|requeue
op_assign
id|gred_requeue
comma
dot
id|drop
op_assign
id|gred_drop
comma
dot
id|init
op_assign
id|gred_init
comma
dot
id|reset
op_assign
id|gred_reset
comma
dot
id|destroy
op_assign
id|gred_destroy
comma
dot
id|change
op_assign
id|gred_change
comma
dot
id|dump
op_assign
id|gred_dump
comma
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
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
id|gred_qdisc_ops
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_qdisc
c_func
(paren
op_amp
id|gred_qdisc_ops
)paren
suffix:semicolon
)brace
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
