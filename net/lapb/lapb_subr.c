multiline_comment|/*&n; *&t;LAPB release 002&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;LAPB 001&t;Jonathan Naylor&t;Started Coding&n; */
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
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/lapb.h&gt;
multiline_comment|/*&n; *&t;This routine purges all the queues of frames.&n; */
DECL|function|lapb_clear_queues
r_void
id|lapb_clear_queues
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
(brace
id|skb_queue_purge
c_func
(paren
op_amp
id|lapb-&gt;write_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|lapb-&gt;ack_queue
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine purges the input queue of those frames that have been&n; * acknowledged. This replaces the boxes labelled &quot;V(a) &lt;- N(r)&quot; on the&n; * SDL diagram.&n; */
DECL|function|lapb_frames_acked
r_void
id|lapb_frames_acked
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
r_int
id|nr
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|modulus
suffix:semicolon
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
multiline_comment|/*&n;&t; * Remove all the ack-ed frames from the ack queue.&n;&t; */
r_if
c_cond
(paren
id|lapb-&gt;va
op_ne
id|nr
)paren
r_while
c_loop
(paren
id|skb_peek
c_func
(paren
op_amp
id|lapb-&gt;ack_queue
)paren
op_logical_and
id|lapb-&gt;va
op_ne
id|nr
)paren
(brace
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|lapb-&gt;ack_queue
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|lapb-&gt;va
op_assign
(paren
id|lapb-&gt;va
op_plus
l_int|1
)paren
op_mod
id|modulus
suffix:semicolon
)brace
)brace
DECL|function|lapb_requeue_frames
r_void
id|lapb_requeue_frames
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|skb_prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Requeue all the un-ack-ed frames on the output queue to be picked&n;&t; * up by lapb_kick called from the timer. This arrangement handles the&n;&t; * possibility of an empty output queue.&n;&t; */
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|lapb-&gt;ack_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|skb_prev
)paren
id|skb_queue_head
c_func
(paren
op_amp
id|lapb-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
r_else
id|skb_append
c_func
(paren
id|skb_prev
comma
id|skb
)paren
suffix:semicolon
id|skb_prev
op_assign
id|skb
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Validate that the value of nr is between va and vs. Return true or&n; *&t;false for testing.&n; */
DECL|function|lapb_validate_nr
r_int
id|lapb_validate_nr
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
r_int
id|nr
)paren
(brace
r_int
r_int
id|vc
op_assign
id|lapb-&gt;va
suffix:semicolon
r_int
id|modulus
suffix:semicolon
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
r_while
c_loop
(paren
id|vc
op_ne
id|lapb-&gt;vs
)paren
(brace
r_if
c_cond
(paren
id|nr
op_eq
id|vc
)paren
r_return
l_int|1
suffix:semicolon
id|vc
op_assign
(paren
id|vc
op_plus
l_int|1
)paren
op_mod
id|modulus
suffix:semicolon
)brace
r_return
id|nr
op_eq
id|lapb-&gt;vs
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This routine is the centralised routine for parsing the control&n; *&t;information for the different frame formats.&n; */
DECL|function|lapb_decode
r_int
id|lapb_decode
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
id|frame-&gt;type
op_assign
id|LAPB_ILLEGAL
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 2
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d RX %02X %02X %02X&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
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
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* We always need to look at 2 bytes, sometimes we need&n;&t; * to look at 3 and those cases are handled below.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_MLP
)paren
(brace
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_DCE
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_D
)paren
id|frame-&gt;cr
op_assign
id|LAPB_COMMAND
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_C
)paren
id|frame-&gt;cr
op_assign
id|LAPB_RESPONSE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_C
)paren
id|frame-&gt;cr
op_assign
id|LAPB_COMMAND
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_D
)paren
id|frame-&gt;cr
op_assign
id|LAPB_RESPONSE
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_DCE
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_B
)paren
id|frame-&gt;cr
op_assign
id|LAPB_COMMAND
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_A
)paren
id|frame-&gt;cr
op_assign
id|LAPB_RESPONSE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_A
)paren
id|frame-&gt;cr
op_assign
id|LAPB_COMMAND
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|LAPB_ADDR_B
)paren
id|frame-&gt;cr
op_assign
id|LAPB_RESPONSE
suffix:semicolon
)brace
)brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_S
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * I frame - carries NR/NS/PF&n;&t;&t;&t; */
id|frame-&gt;type
op_assign
id|LAPB_I
suffix:semicolon
id|frame-&gt;ns
op_assign
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
id|frame-&gt;nr
op_assign
(paren
id|skb-&gt;data
(braket
l_int|1
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
id|frame-&gt;pf
op_assign
id|skb-&gt;data
(braket
l_int|1
)braket
op_amp
id|LAPB_EPF
suffix:semicolon
id|frame-&gt;control
(braket
l_int|0
)braket
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
id|frame-&gt;control
(braket
l_int|1
)braket
op_assign
id|skb-&gt;data
(braket
l_int|1
)braket
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_U
)paren
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * S frame - take out PF/NR&n;&t;&t;&t; */
id|frame-&gt;type
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
l_int|0x0F
suffix:semicolon
id|frame-&gt;nr
op_assign
(paren
id|skb-&gt;data
(braket
l_int|1
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
id|frame-&gt;pf
op_assign
id|skb-&gt;data
(braket
l_int|1
)braket
op_amp
id|LAPB_EPF
suffix:semicolon
id|frame-&gt;control
(braket
l_int|0
)braket
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
id|frame-&gt;control
(braket
l_int|1
)braket
op_assign
id|skb-&gt;data
(braket
l_int|1
)braket
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_U
)paren
op_eq
l_int|3
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * U frame - take out PF&n;&t;&t;&t; */
id|frame-&gt;type
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
op_complement
id|LAPB_SPF
suffix:semicolon
id|frame-&gt;pf
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_SPF
suffix:semicolon
id|frame-&gt;control
(braket
l_int|0
)braket
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
id|frame-&gt;control
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_S
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * I frame - carries NR/NS/PF&n;&t;&t;&t; */
id|frame-&gt;type
op_assign
id|LAPB_I
suffix:semicolon
id|frame-&gt;ns
op_assign
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x07
suffix:semicolon
id|frame-&gt;nr
op_assign
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
id|frame-&gt;pf
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_SPF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_U
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * S frame - take out PF/NR&n;&t;&t;&t; */
id|frame-&gt;type
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
l_int|0x0F
suffix:semicolon
id|frame-&gt;nr
op_assign
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
id|frame-&gt;pf
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_SPF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_U
)paren
op_eq
l_int|3
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * U frame - take out PF&n;&t;&t;&t; */
id|frame-&gt;type
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
op_complement
id|LAPB_SPF
suffix:semicolon
id|frame-&gt;pf
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_amp
id|LAPB_SPF
suffix:semicolon
)brace
id|frame-&gt;control
(braket
l_int|0
)braket
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;This routine is called when the HDLC layer internally  generates a&n; *&t;command or  response  for  the remote machine ( eg. RR, UA etc. ). &n; *&t;Only supervisory or unnumbered frames are processed, FRMRs are handled&n; *&t;by lapb_transmit_frmr below.&n; */
DECL|function|lapb_send_control
r_void
id|lapb_send_control
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
comma
r_int
id|frametype
comma
r_int
id|poll_bit
comma
r_int
id|type
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|LAPB_HEADER_LEN
op_plus
l_int|3
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
id|LAPB_HEADER_LEN
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
r_if
c_cond
(paren
(paren
id|frametype
op_amp
id|LAPB_U
)paren
op_eq
id|LAPB_U
)paren
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|dptr
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_or_assign
id|poll_bit
ques
c_cond
id|LAPB_SPF
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|dptr
(braket
l_int|0
)braket
op_assign
id|frametype
suffix:semicolon
id|dptr
(braket
l_int|1
)braket
op_assign
(paren
id|lapb-&gt;vr
op_lshift
l_int|1
)paren
suffix:semicolon
id|dptr
(braket
l_int|1
)braket
op_or_assign
id|poll_bit
ques
c_cond
id|LAPB_EPF
suffix:colon
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|dptr
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_or_assign
id|poll_bit
ques
c_cond
id|LAPB_SPF
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|frametype
op_amp
id|LAPB_U
)paren
op_eq
id|LAPB_S
)paren
multiline_comment|/* S frames carry NR */
op_star
id|dptr
op_or_assign
(paren
id|lapb-&gt;vr
op_lshift
l_int|5
)paren
suffix:semicolon
)brace
id|lapb_transmit_buffer
c_func
(paren
id|lapb
comma
id|skb
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;This routine generates FRMRs based on information previously stored in&n; *&t;the LAPB control block.&n; */
DECL|function|lapb_transmit_frmr
r_void
id|lapb_transmit_frmr
c_func
(paren
r_struct
id|lapb_cb
op_star
id|lapb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|LAPB_HEADER_LEN
op_plus
l_int|7
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
id|LAPB_HEADER_LEN
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;mode
op_amp
id|LAPB_EXTENDED
)paren
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|LAPB_FRMR
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lapb-&gt;frmr_data.control
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lapb-&gt;frmr_data.control
(braket
l_int|1
)braket
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
(paren
id|lapb-&gt;vs
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
op_star
id|dptr
op_assign
(paren
id|lapb-&gt;vr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;frmr_data.cr
op_eq
id|LAPB_RESPONSE
)paren
op_star
id|dptr
op_or_assign
l_int|0x01
suffix:semicolon
id|dptr
op_increment
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lapb-&gt;frmr_type
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX FRMR %02X %02X %02X %02X %02X&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
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
comma
id|skb-&gt;data
(braket
l_int|5
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|LAPB_FRMR
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lapb-&gt;frmr_data.control
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|dptr
op_assign
(paren
id|lapb-&gt;vs
op_lshift
l_int|1
)paren
op_amp
l_int|0x0E
suffix:semicolon
op_star
id|dptr
op_or_assign
(paren
id|lapb-&gt;vr
op_lshift
l_int|5
)paren
op_amp
l_int|0xE0
suffix:semicolon
r_if
c_cond
(paren
id|lapb-&gt;frmr_data.cr
op_eq
id|LAPB_RESPONSE
)paren
op_star
id|dptr
op_or_assign
l_int|0x10
suffix:semicolon
id|dptr
op_increment
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lapb-&gt;frmr_type
suffix:semicolon
macro_line|#if LAPB_DEBUG &gt; 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;lapb: (%p) S%d TX FRMR %02X %02X %02X&bslash;n&quot;
comma
id|lapb-&gt;token
comma
id|lapb-&gt;state
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
)paren
suffix:semicolon
macro_line|#endif
)brace
id|lapb_transmit_buffer
c_func
(paren
id|lapb
comma
id|skb
comma
id|LAPB_RESPONSE
)paren
suffix:semicolon
)brace
eof
