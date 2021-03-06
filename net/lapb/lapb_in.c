multiline_comment|/*&n; *&t;LAPB release 002&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;LAPB 001&t;Jonathan Naulor&t;Started Coding&n; *&t;LAPB 002&t;Jonathan Naylor&t;New timer architecture.&n; *&t;2000-10-29&t;Henner Eisen&t;lapb_data_indication() return status.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/lapb.h&gt;
multiline_comment|/*&n; *&t;State machine for state 0, Disconnected State.&n; *&t;The handling of the timer(s) is in file lapb_timer.c.&n; */
DECL|function|lapb_state0_machine
r_static
r_void
id|lapb_state0_machine
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|lapb_frame
op_star
id|frame
)paren
(brace
r_switch
c_cond
(paren
id|frame-&gt;type
)paren
(brace
r_case
id|LAPB_SABM
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 RX SABM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 -&gt; S3&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_3
suffix:semicolon
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;va
op_assign
l_int|0
suffix:semicolon
id|lapb_connect_indication
c_func
(paren
id|lapb
comma
id|LAPB_OK
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_SABME
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 RX SABME(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 -&gt; S3&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_3
suffix:semicolon
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;va
op_assign
l_int|0
suffix:semicolon
id|lapb_connect_indication
c_func
(paren
id|lapb
comma
id|LAPB_OK
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_DISC
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 RX DISC(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S0 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;State machine for state 1, Awaiting Connection State.&n; *&t;The handling of the timer(s) is in file lapb_timer.c.&n; */
DECL|function|lapb_state1_machine
r_static
r_void
id|lapb_state1_machine
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|lapb_frame
op_star
id|frame
)paren
(brace
r_switch
c_cond
(paren
id|frame-&gt;type
)paren
(brace
r_case
id|LAPB_SABM
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 RX SABM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_SABME
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 RX SABME(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_DISC
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 RX DISC(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_UA
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 RX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|frame-&gt;pf
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 -&gt; S3&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_3
suffix:semicolon
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;va
op_assign
l_int|0
suffix:semicolon
id|lapb_connect_confirmation
c_func
(paren
id|lapb
comma
id|LAPB_OK
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_DM
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 RX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|frame-&gt;pf
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S1 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_clear_queues
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_disconnect_indication
c_func
(paren
id|lapb
comma
id|LAPB_REFUSED
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;State machine for state 2, Awaiting Release State.&n; *&t;The handling of the timer(s) is in file lapb_timer.c&n; */
DECL|function|lapb_state2_machine
r_static
r_void
id|lapb_state2_machine
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|lapb_frame
op_star
id|frame
)paren
(brace
r_switch
c_cond
(paren
id|frame-&gt;type
)paren
(brace
r_case
id|LAPB_SABM
suffix:colon
r_case
id|LAPB_SABME
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 RX {SABM,SABME}(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_DISC
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 RX DISC(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_UA
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 RX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|frame-&gt;pf
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_disconnect_confirmation
c_func
(paren
id|lapb
comma
id|LAPB_OK
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_DM
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 RX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|frame-&gt;pf
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_disconnect_confirmation
c_func
(paren
id|lapb
comma
id|LAPB_NOTCONNECTED
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_I
suffix:colon
r_case
id|LAPB_REJ
suffix:colon
r_case
id|LAPB_RNR
suffix:colon
r_case
id|LAPB_RR
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 RX {I,REJ,RNR,RR}&quot;
l_string|&quot;(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S2 RX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|frame-&gt;pf
)paren
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;State machine for state 3, Connected State.&n; *&t;The handling of the timer(s) is in file lapb_timer.c&n; */
DECL|function|lapb_state3_machine
r_static
r_void
id|lapb_state3_machine
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|lapb_frame
op_star
id|frame
)paren
(brace
r_int
id|queued
op_assign
l_int|0
suffix:semicolon
r_int
id|modulus
op_assign
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
ques
c_cond
id|LAPB_EMODULUS
suffix:colon
id|LAPB_SMODULUS
suffix:semicolon
r_switch
c_cond
(paren
id|frame-&gt;type
)paren
(brace
r_case
id|LAPB_SABM
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX SABM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;va
op_assign
l_int|0
suffix:semicolon
id|lapb_requeue_frames
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_SABME
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX SABME(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;va
op_assign
l_int|0
suffix:semicolon
id|lapb_requeue_frames
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_DISC
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX DISC(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_clear_queues
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_disconnect_indication
c_func
(paren
id|lapb
comma
id|LAPB_OK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_DM
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S0&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_clear_queues
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_0
suffix:semicolon
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_disconnect_indication
c_func
(paren
id|lapb
comma
id|LAPB_NOTCONNECTED
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_RNR
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX RNR(%d) R%d&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
comma
id|frame-&gt;nr
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;condition
op_or_assign
id|LAPB_PEER_RX_BUSY_CONDITION
suffix:semicolon
id|lapb_check_need_response
c_func
(paren
id|lapb
comma
id|frame-&gt;cr
comma
id|frame-&gt;pf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb_validate_nr
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
)paren
(brace
id|lapb_check_iframes_acked
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
suffix:semicolon
)brace
r_else
(brace
id|lapb-&gt;frmr_data
op_assign
op_star
id|frame
suffix:semicolon
id|lapb-&gt;frmr_type
op_assign
id|LAPB_FRMR_Z
suffix:semicolon
id|lapb_transmit_frmr
c_func
(paren
id|lapb
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S4&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_4
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_RR
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX RR(%d) R%d&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
comma
id|frame-&gt;nr
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_PEER_RX_BUSY_CONDITION
suffix:semicolon
id|lapb_check_need_response
c_func
(paren
id|lapb
comma
id|frame-&gt;cr
comma
id|frame-&gt;pf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb_validate_nr
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
)paren
(brace
id|lapb_check_iframes_acked
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
suffix:semicolon
)brace
r_else
(brace
id|lapb-&gt;frmr_data
op_assign
op_star
id|frame
suffix:semicolon
id|lapb-&gt;frmr_type
op_assign
id|LAPB_FRMR_Z
suffix:semicolon
id|lapb_transmit_frmr
c_func
(paren
id|lapb
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S4&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_4
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_REJ
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX REJ(%d) R%d&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
comma
id|frame-&gt;nr
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_PEER_RX_BUSY_CONDITION
suffix:semicolon
id|lapb_check_need_response
c_func
(paren
id|lapb
comma
id|frame-&gt;cr
comma
id|frame-&gt;pf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb_validate_nr
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
)paren
(brace
id|lapb_frames_acked
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
suffix:semicolon
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb_requeue_frames
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
r_else
(brace
id|lapb-&gt;frmr_data
op_assign
op_star
id|frame
suffix:semicolon
id|lapb-&gt;frmr_type
op_assign
id|LAPB_FRMR_Z
suffix:semicolon
id|lapb_transmit_frmr
c_func
(paren
id|lapb
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S4&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_4
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_I
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX I(%d) S%d R%d&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
comma
id|frame-&gt;ns
comma
id|frame-&gt;nr
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|lapb_validate_nr
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
)paren
(brace
id|lapb-&gt;frmr_data
op_assign
op_star
id|frame
suffix:semicolon
id|lapb-&gt;frmr_type
op_assign
id|LAPB_FRMR_Z
suffix:semicolon
id|lapb_transmit_frmr
c_func
(paren
id|lapb
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S4&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_4
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lapb-&gt;condition
op_amp
id|LAPB_PEER_RX_BUSY_CONDITION
)paren
id|lapb_frames_acked
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
suffix:semicolon
r_else
id|lapb_check_iframes_acked
c_func
(paren
id|lapb
comma
id|frame-&gt;nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;ns
op_eq
id|lapb-&gt;vr
)paren
(brace
r_int
id|cn
suffix:semicolon
id|cn
op_assign
id|lapb_data_indication
c_func
(paren
id|lapb
comma
id|skb
)paren
suffix:semicolon
id|queued
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * If upper layer has dropped the frame, we&n;&t;&t;&t;&t; * basically ignore any further protocol&n;&t;&t;&t;&t; * processing. This will cause the peer&n;&t;&t;&t;&t; * to re-transmit the frame later like&n;&t;&t;&t;&t; * a frame lost on the wire.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|cn
op_eq
id|NET_RX_DROP
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;LAPB: rx congestion&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|lapb-&gt;vr
op_assign
(paren
id|lapb-&gt;vr
op_plus
l_int|1
)paren
op_mod
id|modulus
suffix:semicolon
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_REJECT_CONDITION
suffix:semicolon
r_if
c_cond
(paren
id|frame-&gt;pf
)paren
id|lapb_enquiry_response
c_func
(paren
id|lapb
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|lapb-&gt;condition
op_amp
id|LAPB_ACK_PENDING_CONDITION
)paren
)paren
(brace
id|lapb-&gt;condition
op_or_assign
id|LAPB_ACK_PENDING_CONDITION
suffix:semicolon
id|lapb_start_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|lapb-&gt;condition
op_amp
id|LAPB_REJECT_CONDITION
)paren
(brace
r_if
c_cond
(paren
id|frame-&gt;pf
)paren
id|lapb_enquiry_response
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 TX REJ(%d) R%d&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
comma
id|lapb-&gt;vr
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;condition
op_or_assign
id|LAPB_REJECT_CONDITION
suffix:semicolon
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_REJ
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb-&gt;condition
op_and_assign
op_complement
id|LAPB_ACK_PENDING_CONDITION
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|LAPB_FRMR
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX FRMR(%d) %02X &quot;
l_string|&quot;%02X %02X %02X %02X&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
comma
id|skb-&gt;data
(braket
l_int|0
)braket
comma
id|skb-&gt;data
(braket
l_int|1
)braket
comma
id|skb-&gt;data
(braket
l_int|2
)braket
comma
id|skb-&gt;data
(braket
l_int|3
)braket
comma
id|skb-&gt;data
(braket
l_int|4
)braket
)paren
suffix:semicolon
macro_line|#endif
id|lapb_establish_data_link
c_func
(paren
id|lapb
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S1&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_requeue_frames
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_ILLEGAL
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 RX ILLEGAL(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb-&gt;frmr_data
op_assign
op_star
id|frame
suffix:semicolon
id|lapb-&gt;frmr_type
op_assign
id|LAPB_FRMR_W
suffix:semicolon
id|lapb_transmit_frmr
c_func
(paren
id|lapb
)paren
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S3 -&gt; S4&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_start_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_4
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|queued
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;State machine for state 4, Frame Reject State.&n; *&t;The handling of the timer(s) is in file lapb_timer.c.&n; */
DECL|function|lapb_state4_machine
r_static
r_void
id|lapb_state4_machine
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|lapb_frame
op_star
id|frame
)paren
(brace
r_switch
c_cond
(paren
id|frame-&gt;type
)paren
(brace
r_case
id|LAPB_SABM
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 RX SABM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 -&gt; S3&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_3
suffix:semicolon
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;va
op_assign
l_int|0
suffix:semicolon
id|lapb_connect_indication
c_func
(paren
id|lapb
comma
id|LAPB_OK
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LAPB_SABME
suffix:colon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 RX SABME(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 TX UA(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LAPB_DEBUG &gt; 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 -&gt; S3&bslash;n&quot;
comma
id|lapb-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_UA
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
id|lapb_stop_t1timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb_stop_t2timer
c_func
(paren
id|lapb
)paren
suffix:semicolon
id|lapb-&gt;state
op_assign
id|LAPB_STATE_3
suffix:semicolon
id|lapb-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|lapb-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|lapb-&gt;va
op_assign
l_int|0
suffix:semicolon
id|lapb_connect_indication
c_func
(paren
id|lapb
comma
id|LAPB_OK
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S4 TX DM(%d)&bslash;n&quot;
comma
id|lapb-&gt;dev
comma
id|frame-&gt;pf
)paren
suffix:semicolon
macro_line|#endif
id|lapb_send_control
c_func
(paren
id|lapb
comma
id|LAPB_DM
comma
id|frame-&gt;pf
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Process an incoming LAPB frame&n; */
DECL|function|lapb_data_input
r_void
id|lapb_data_input
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|lapb_frame
id|frame
suffix:semicolon
r_if
c_cond
(paren
id|lapb_decode
c_func
(paren
id|lapb
comma
id|skb
comma
op_amp
id|frame
)paren
OL
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|lapb-&gt;state
)paren
(brace
r_case
id|LAPB_STATE_0
suffix:colon
id|lapb_state0_machine
c_func
(paren
id|lapb
comma
id|skb
comma
op_amp
id|frame
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_STATE_1
suffix:colon
id|lapb_state1_machine
c_func
(paren
id|lapb
comma
id|skb
comma
op_amp
id|frame
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_STATE_2
suffix:colon
id|lapb_state2_machine
c_func
(paren
id|lapb
comma
id|skb
comma
op_amp
id|frame
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_STATE_3
suffix:colon
id|lapb_state3_machine
c_func
(paren
id|lapb
comma
id|skb
comma
op_amp
id|frame
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LAPB_STATE_4
suffix:colon
id|lapb_state4_machine
c_func
(paren
id|lapb
comma
id|skb
comma
op_amp
id|frame
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|lapb_kick
c_func
(paren
id|lapb
)paren
suffix:semicolon
)brace
eof
