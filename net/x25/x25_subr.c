multiline_comment|/*&n; *&t;X.25 Packet Layer release 002&n; *&n; *&t;This is ALPHA test software. This code may break your machine,&n; *&t;randomly fail to work with new releases, misbehave and/or generally&n; *&t;screw up. It might even work.&n; *&n; *&t;This code REQUIRES 2.1.15 or higher&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;X.25 001&t;Jonathan Naylor&t;  Started coding.&n; *&t;X.25 002&t;Jonathan Naylor&t;  Centralised disconnection processing.&n; *&t;mar/20/00&t;Daniela Squassoni Disabling/enabling of facilities&n; *&t;&t;&t;&t;&t;  negotiation.&n; *&t;jun/24/01&t;Arnaldo C. Melo&t;  use skb_queue_purge, cleanups&n; */
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
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/x25.h&gt;
multiline_comment|/*&n; *&t;This routine purges all of the queues of frames.&n; */
DECL|function|x25_clear_queues
r_void
id|x25_clear_queues
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;sk_write_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|x25-&gt;ack_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|x25-&gt;interrupt_in_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|x25-&gt;interrupt_out_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|x25-&gt;fragment_queue
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine purges the input queue of those frames that have been&n; * acknowledged. This replaces the boxes labelled &quot;V(a) &lt;- N(r)&quot; on the&n; * SDL diagram.&n;*/
DECL|function|x25_frames_acked
r_void
id|x25_frames_acked
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_int
id|modulus
op_assign
id|x25-&gt;neighbour-&gt;extended
ques
c_cond
id|X25_EMODULUS
suffix:colon
id|X25_SMODULUS
suffix:semicolon
multiline_comment|/*&n;&t; * Remove all the ack-ed frames from the ack queue.&n;&t; */
r_if
c_cond
(paren
id|x25-&gt;va
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
id|x25-&gt;ack_queue
)paren
op_logical_and
id|x25-&gt;va
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
id|x25-&gt;ack_queue
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|x25-&gt;va
op_assign
(paren
id|x25-&gt;va
op_plus
l_int|1
)paren
op_mod
id|modulus
suffix:semicolon
)brace
)brace
DECL|function|x25_requeue_frames
r_void
id|x25_requeue_frames
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
multiline_comment|/*&n;&t; * Requeue all the un-ack-ed frames on the output queue to be picked&n;&t; * up by x25_kick. This arrangement handles the possibility of an empty&n;&t; * output queue.&n;&t; */
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
id|x25_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|ack_queue
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
id|sk-&gt;sk_write_queue
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
DECL|function|x25_validate_nr
r_int
id|x25_validate_nr
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|nr
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_int
r_int
id|vc
op_assign
id|x25-&gt;va
suffix:semicolon
r_int
id|modulus
op_assign
id|x25-&gt;neighbour-&gt;extended
ques
c_cond
id|X25_EMODULUS
suffix:colon
id|X25_SMODULUS
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|x25-&gt;vs
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
id|x25-&gt;vs
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  This routine is called when the packet layer internally generates a&n; *  control frame.&n; */
DECL|function|x25_write_internal
r_void
id|x25_write_internal
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|frametype
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
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
r_int
r_char
id|facilities
(braket
id|X25_MAX_FAC_LEN
)braket
suffix:semicolon
r_int
r_char
id|addresses
(braket
l_int|1
op_plus
id|X25_ADDR_LEN
)braket
suffix:semicolon
r_int
r_char
id|lci1
comma
id|lci2
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Default safe frame size.&n;&t; */
r_int
id|len
op_assign
id|X25_MAX_L2_LEN
op_plus
id|X25_EXT_MIN_LEN
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Adjust frame size.&n;&t; */
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|X25_CALL_REQUEST
suffix:colon
id|len
op_add_assign
l_int|1
op_plus
id|X25_ADDR_LEN
op_plus
id|X25_MAX_FAC_LEN
op_plus
id|X25_MAX_CUD_LEN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_CALL_ACCEPTED
suffix:colon
id|len
op_add_assign
l_int|1
op_plus
id|X25_MAX_FAC_LEN
op_plus
id|X25_MAX_CUD_LEN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_CLEAR_REQUEST
suffix:colon
r_case
id|X25_RESET_REQUEST
suffix:colon
id|len
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_RR
suffix:colon
r_case
id|X25_RNR
suffix:colon
r_case
id|X25_REJ
suffix:colon
r_case
id|X25_CLEAR_CONFIRMATION
suffix:colon
r_case
id|X25_INTERRUPT_CONFIRMATION
suffix:colon
r_case
id|X25_RESET_CONFIRMATION
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;X.25: invalid frame type %02X&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Space for Ethernet and 802.2 LLC headers.&n;&t; */
id|skb_reserve
c_func
(paren
id|skb
comma
id|X25_MAX_L2_LEN
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Make space for the GFI and LCI, and fill them in.&n;&t; */
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
id|lci1
op_assign
(paren
id|x25-&gt;lci
op_rshift
l_int|8
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|lci2
op_assign
(paren
id|x25-&gt;lci
op_rshift
l_int|0
)paren
op_amp
l_int|0xFF
suffix:semicolon
r_if
c_cond
(paren
id|x25-&gt;neighbour-&gt;extended
)paren
(brace
op_star
id|dptr
op_increment
op_assign
id|lci1
op_or
id|X25_GFI_EXTSEQ
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
suffix:semicolon
)brace
r_else
(brace
op_star
id|dptr
op_increment
op_assign
id|lci1
op_or
id|X25_GFI_STDSEQ
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Now fill in the frame type specific information.&n;&t; */
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|X25_CALL_REQUEST
suffix:colon
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
op_increment
op_assign
id|X25_CALL_REQUEST
suffix:semicolon
id|len
op_assign
id|x25_addr_aton
c_func
(paren
id|addresses
comma
op_amp
id|x25-&gt;dest_addr
comma
op_amp
id|x25-&gt;source_addr
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|addresses
comma
id|len
)paren
suffix:semicolon
id|len
op_assign
id|x25_create_facilities
c_func
(paren
id|facilities
comma
op_amp
id|x25-&gt;facilities
comma
id|x25-&gt;neighbour-&gt;global_facil_mask
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|facilities
comma
id|len
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|x25-&gt;calluserdata.cudlength
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|x25-&gt;calluserdata.cuddata
comma
id|x25-&gt;calluserdata.cudlength
)paren
suffix:semicolon
id|x25-&gt;calluserdata.cudlength
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_CALL_ACCEPTED
suffix:colon
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
op_star
id|dptr
op_increment
op_assign
id|X25_CALL_ACCEPTED
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Address lengths */
id|len
op_assign
id|x25_create_facilities
c_func
(paren
id|facilities
comma
op_amp
id|x25-&gt;facilities
comma
id|x25-&gt;vc_facil_mask
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|facilities
comma
id|len
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|x25-&gt;calluserdata.cudlength
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|x25-&gt;calluserdata.cuddata
comma
id|x25-&gt;calluserdata.cudlength
)paren
suffix:semicolon
id|x25-&gt;calluserdata.cudlength
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_CLEAR_REQUEST
suffix:colon
r_case
id|X25_RESET_REQUEST
suffix:colon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
l_int|3
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* XXX */
op_star
id|dptr
op_increment
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* XXX */
r_break
suffix:semicolon
r_case
id|X25_RR
suffix:colon
r_case
id|X25_RNR
suffix:colon
r_case
id|X25_REJ
suffix:colon
r_if
c_cond
(paren
id|x25-&gt;neighbour-&gt;extended
)paren
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
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
(paren
id|x25-&gt;vr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
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
op_increment
op_or_assign
(paren
id|x25-&gt;vr
op_lshift
l_int|5
)paren
op_amp
l_int|0xE0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X25_CLEAR_CONFIRMATION
suffix:colon
r_case
id|X25_INTERRUPT_CONFIRMATION
suffix:colon
r_case
id|X25_RESET_CONFIRMATION
suffix:colon
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
r_break
suffix:semicolon
)brace
id|x25_transmit_link
c_func
(paren
id|skb
comma
id|x25-&gt;neighbour
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Unpick the contents of the passed X.25 Packet Layer frame.&n; */
DECL|function|x25_decode
r_int
id|x25_decode
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
op_star
id|ns
comma
r_int
op_star
id|nr
comma
r_int
op_star
id|q
comma
r_int
op_star
id|d
comma
r_int
op_star
id|m
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_int
r_char
op_star
id|frame
op_assign
id|skb-&gt;data
suffix:semicolon
op_star
id|ns
op_assign
op_star
id|nr
op_assign
op_star
id|q
op_assign
op_star
id|d
op_assign
op_star
id|m
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|frame
(braket
l_int|2
)braket
)paren
(brace
r_case
id|X25_CALL_REQUEST
suffix:colon
r_case
id|X25_CALL_ACCEPTED
suffix:colon
r_case
id|X25_CLEAR_REQUEST
suffix:colon
r_case
id|X25_CLEAR_CONFIRMATION
suffix:colon
r_case
id|X25_INTERRUPT
suffix:colon
r_case
id|X25_INTERRUPT_CONFIRMATION
suffix:colon
r_case
id|X25_RESET_REQUEST
suffix:colon
r_case
id|X25_RESET_CONFIRMATION
suffix:colon
r_case
id|X25_RESTART_REQUEST
suffix:colon
r_case
id|X25_RESTART_CONFIRMATION
suffix:colon
r_case
id|X25_REGISTRATION_REQUEST
suffix:colon
r_case
id|X25_REGISTRATION_CONFIRMATION
suffix:colon
r_case
id|X25_DIAGNOSTIC
suffix:colon
r_return
id|frame
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x25-&gt;neighbour-&gt;extended
)paren
(brace
r_if
c_cond
(paren
id|frame
(braket
l_int|2
)braket
op_eq
id|X25_RR
op_logical_or
id|frame
(braket
l_int|2
)braket
op_eq
id|X25_RNR
op_logical_or
id|frame
(braket
l_int|2
)braket
op_eq
id|X25_REJ
)paren
(brace
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|3
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
r_return
id|frame
(braket
l_int|2
)braket
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|2
)braket
op_amp
l_int|0x1F
)paren
op_eq
id|X25_RR
op_logical_or
(paren
id|frame
(braket
l_int|2
)braket
op_amp
l_int|0x1F
)paren
op_eq
id|X25_RNR
op_logical_or
(paren
id|frame
(braket
l_int|2
)braket
op_amp
l_int|0x1F
)paren
op_eq
id|X25_REJ
)paren
(brace
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|2
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
r_return
id|frame
(braket
l_int|2
)braket
op_amp
l_int|0x1F
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|x25-&gt;neighbour-&gt;extended
)paren
(brace
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|2
)braket
op_amp
l_int|0x01
)paren
op_eq
id|X25_DATA
)paren
(brace
op_star
id|q
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|X25_Q_BIT
)paren
op_eq
id|X25_Q_BIT
suffix:semicolon
op_star
id|d
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|X25_D_BIT
)paren
op_eq
id|X25_D_BIT
suffix:semicolon
op_star
id|m
op_assign
(paren
id|frame
(braket
l_int|3
)braket
op_amp
id|X25_EXT_M_BIT
)paren
op_eq
id|X25_EXT_M_BIT
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|3
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
op_star
id|ns
op_assign
(paren
id|frame
(braket
l_int|2
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
r_return
id|X25_DATA
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|2
)braket
op_amp
l_int|0x01
)paren
op_eq
id|X25_DATA
)paren
(brace
op_star
id|q
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|X25_Q_BIT
)paren
op_eq
id|X25_Q_BIT
suffix:semicolon
op_star
id|d
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|X25_D_BIT
)paren
op_eq
id|X25_D_BIT
suffix:semicolon
op_star
id|m
op_assign
(paren
id|frame
(braket
l_int|2
)braket
op_amp
id|X25_STD_M_BIT
)paren
op_eq
id|X25_STD_M_BIT
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|2
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
op_star
id|ns
op_assign
(paren
id|frame
(braket
l_int|2
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x07
suffix:semicolon
r_return
id|X25_DATA
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;X.25: invalid PLP frame %02X %02X %02X&bslash;n&quot;
comma
id|frame
(braket
l_int|0
)braket
comma
id|frame
(braket
l_int|1
)braket
comma
id|frame
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_return
id|X25_ILLEGAL
suffix:semicolon
)brace
DECL|function|x25_disconnect
r_void
id|x25_disconnect
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|reason
comma
r_int
r_char
id|cause
comma
r_int
r_char
id|diagnostic
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25-&gt;lci
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;state
op_assign
id|X25_STATE_0
suffix:semicolon
id|x25-&gt;causediag.cause
op_assign
id|cause
suffix:semicolon
id|x25-&gt;causediag.diagnostic
op_assign
id|diagnostic
suffix:semicolon
id|sk-&gt;sk_state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;sk_err
op_assign
id|reason
suffix:semicolon
id|sk-&gt;sk_shutdown
op_or_assign
id|SEND_SHUTDOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock_flag
c_func
(paren
id|sk
comma
id|SOCK_DEAD
)paren
)paren
(brace
id|sk
op_member_access_from_pointer
id|sk_state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_set_flag
c_func
(paren
id|sk
comma
id|SOCK_DEAD
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Clear an own-rx-busy condition and tell the peer about this, provided&n; * that there is a significant amount of free receive buffer space available.&n; */
DECL|function|x25_check_rbuf
r_void
id|x25_check_rbuf
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;sk_rmem_alloc
)paren
OL
(paren
id|sk-&gt;sk_rcvbuf
op_div
l_int|2
)paren
op_logical_and
(paren
id|x25-&gt;condition
op_amp
id|X25_COND_OWN_RX_BUSY
)paren
)paren
(brace
id|x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_OWN_RX_BUSY
suffix:semicolon
id|x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_ACK_PENDING
suffix:semicolon
id|x25-&gt;vl
op_assign
id|x25-&gt;vr
suffix:semicolon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_RR
)paren
suffix:semicolon
id|x25_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
eof
