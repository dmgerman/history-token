multiline_comment|/*&n; *&t;X.25 Packet Layer release 002&n; *&n; *&t;This is ALPHA test software. This code may break your machine,&n; *&t;randomly fail to work with new releases, misbehave and/or generally&n; *&t;screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;X.25 001&t;Jonathan Naylor&t;  Started coding.&n; *&t;X.25 002&t;Jonathan Naylor&t;  Centralised disconnection code.&n; *&t;&t;&t;&t;&t;  New timer architecture.&n; *&t;2000-03-20&t;Daniela Squassoni Disabling/enabling of facilities &n; *&t;&t;&t;&t;&t;  negotiation.&n; *&t;2000-11-10&t;Henner Eisen&t;  Check and reset for out-of-sequence&n; *&t;&t;&t;&t;&t;  i-frames.&n; */
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
macro_line|#include &lt;net/ip.h&gt;&t;&t;&t;/* For ip_rcv */
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/x25.h&gt;
DECL|function|x25_queue_rx_frame
r_static
r_int
id|x25_queue_rx_frame
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
id|more
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbo
comma
op_star
id|skbn
op_assign
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
r_if
c_cond
(paren
id|more
)paren
(brace
id|x25-&gt;fraglen
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|x25-&gt;fragment_queue
comma
id|skb
)paren
suffix:semicolon
id|skb_set_owner_r
c_func
(paren
id|skb
comma
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|more
op_logical_and
id|x25-&gt;fraglen
OG
l_int|0
)paren
(brace
multiline_comment|/* End of fragment */
r_int
id|len
op_assign
id|x25-&gt;fraglen
op_plus
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skbn
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
(brace
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
id|skb_queue_tail
c_func
(paren
op_amp
id|x25-&gt;fragment_queue
comma
id|skb
)paren
suffix:semicolon
id|skbn-&gt;h.raw
op_assign
id|skbn-&gt;data
suffix:semicolon
id|skbo
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|x25-&gt;fragment_queue
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skbn
comma
id|skbo-&gt;len
)paren
comma
id|skbo-&gt;data
comma
id|skbo-&gt;len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skbo
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skbo
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|x25-&gt;fragment_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb_pull
c_func
(paren
id|skbo
comma
(paren
id|x25-&gt;neighbour-&gt;extended
)paren
ques
c_cond
id|X25_EXT_MIN_LEN
suffix:colon
id|X25_STD_MIN_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skbn
comma
id|skbo-&gt;len
)paren
comma
id|skbo-&gt;data
comma
id|skbo-&gt;len
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skbo
)paren
suffix:semicolon
)brace
id|x25-&gt;fraglen
op_assign
l_int|0
suffix:semicolon
)brace
id|skb_set_owner_r
c_func
(paren
id|skbn
comma
id|sk
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;receive_queue
comma
id|skbn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|data_ready
c_func
(paren
id|sk
comma
id|skbn-&gt;len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 1, Awaiting Call Accepted State.&n; * The handling of the timer(s) is in file x25_timer.c.&n; * Handling of state 0 and connection release is in af_x25.c.&n; */
DECL|function|x25_state1_machine
r_static
r_int
id|x25_state1_machine
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
id|frametype
)paren
(brace
r_struct
id|x25_address
id|source_addr
comma
id|dest_addr
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|X25_CALL_ACCEPTED
suffix:colon
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
id|x25_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|x25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;state
op_assign
id|X25_STATE_3
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_ESTABLISHED
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Parse the data in the frame.&n;&t;&t;&t; */
id|skb_pull
c_func
(paren
id|skb
comma
id|X25_STD_MIN_LEN
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|x25_addr_ntoa
c_func
(paren
id|skb-&gt;data
comma
op_amp
id|source_addr
comma
op_amp
id|dest_addr
)paren
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|x25_parse_facilities
c_func
(paren
id|skb
comma
op_amp
id|x25-&gt;facilities
comma
op_amp
id|x25-&gt;vc_facil_mask
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Copy any Call User Data.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|skb-&gt;len
op_ge
l_int|0
)paren
(brace
id|memcpy
c_func
(paren
id|x25-&gt;calluserdata.cuddata
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|x25-&gt;calluserdata.cudlength
op_assign
id|skb-&gt;len
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|X25_CLEAR_REQUEST
suffix:colon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_CLEAR_CONFIRMATION
)paren
suffix:semicolon
id|x25_disconnect
c_func
(paren
id|sk
comma
id|ECONNREFUSED
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
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 2, Awaiting Clear Confirmation State.&n; * The handling of the timer(s) is in file x25_timer.c&n; * Handling of state 0 and connection release is in af_x25.c.&n; */
DECL|function|x25_state2_machine
r_static
r_int
id|x25_state2_machine
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
id|frametype
)paren
(brace
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|X25_CLEAR_REQUEST
suffix:colon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_CLEAR_CONFIRMATION
)paren
suffix:semicolon
id|x25_disconnect
c_func
(paren
id|sk
comma
l_int|0
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
r_break
suffix:semicolon
r_case
id|X25_CLEAR_CONFIRMATION
suffix:colon
id|x25_disconnect
c_func
(paren
id|sk
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 3, Connected State.&n; * The handling of the timer(s) is in file x25_timer.c&n; * Handling of state 0 and connection release is in af_x25.c.&n; */
DECL|function|x25_state3_machine
r_static
r_int
id|x25_state3_machine
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
id|frametype
comma
r_int
id|ns
comma
r_int
id|nr
comma
r_int
id|q
comma
r_int
id|d
comma
r_int
id|m
)paren
(brace
r_int
id|queued
op_assign
l_int|0
suffix:semicolon
r_int
id|modulus
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
id|modulus
op_assign
(paren
id|x25-&gt;neighbour-&gt;extended
)paren
ques
c_cond
id|X25_EMODULUS
suffix:colon
id|X25_SMODULUS
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|X25_RESET_REQUEST
suffix:colon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_RESET_CONFIRMATION
)paren
suffix:semicolon
id|x25_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|x25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|x25_requeue_frames
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_CLEAR_REQUEST
suffix:colon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_CLEAR_CONFIRMATION
)paren
suffix:semicolon
id|x25_disconnect
c_func
(paren
id|sk
comma
l_int|0
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
r_break
suffix:semicolon
r_case
id|X25_RR
suffix:colon
r_case
id|X25_RNR
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|x25_validate_nr
c_func
(paren
id|sk
comma
id|nr
)paren
)paren
(brace
id|x25_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_RESET_REQUEST
)paren
suffix:semicolon
id|x25_start_t22timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|x25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;state
op_assign
id|X25_STATE_4
suffix:semicolon
)brace
r_else
(brace
id|x25_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frametype
op_eq
id|X25_RNR
)paren
(brace
id|x25-&gt;condition
op_or_assign
id|X25_COND_PEER_RX_BUSY
suffix:semicolon
)brace
r_else
(brace
id|x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_PEER_RX_BUSY
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|X25_DATA
suffix:colon
multiline_comment|/* XXX */
id|x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_PEER_RX_BUSY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ns
op_ne
id|x25-&gt;vr
)paren
op_logical_or
op_logical_neg
id|x25_validate_nr
c_func
(paren
id|sk
comma
id|nr
)paren
)paren
(brace
id|x25_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_RESET_REQUEST
)paren
suffix:semicolon
id|x25_start_t22timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|x25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;state
op_assign
id|X25_STATE_4
suffix:semicolon
r_break
suffix:semicolon
)brace
id|x25_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ns
op_eq
id|x25-&gt;vr
)paren
(brace
r_if
c_cond
(paren
id|x25_queue_rx_frame
c_func
(paren
id|sk
comma
id|skb
comma
id|m
)paren
op_eq
l_int|0
)paren
(brace
id|x25-&gt;vr
op_assign
(paren
id|x25-&gt;vr
op_plus
l_int|1
)paren
op_mod
id|modulus
suffix:semicolon
id|queued
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Should never happen */
id|x25_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_RESET_REQUEST
)paren
suffix:semicolon
id|x25_start_t22timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|x25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;state
op_assign
id|X25_STATE_4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;rmem_alloc
)paren
OG
(paren
id|sk-&gt;rcvbuf
op_div
l_int|2
)paren
)paren
id|x25-&gt;condition
op_or_assign
id|X25_COND_OWN_RX_BUSY
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *&t;If the window is full Ack it immediately, else&n;&t;&t;&t; *&t;start the holdback timer.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|x25-&gt;vl
op_plus
id|x25-&gt;facilities.winsize_in
)paren
op_mod
id|modulus
)paren
op_eq
id|x25-&gt;vr
)paren
(brace
id|x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_ACK_PENDING
suffix:semicolon
id|x25_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|x25-&gt;condition
op_or_assign
id|X25_COND_ACK_PENDING
suffix:semicolon
id|x25_start_t2timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X25_INTERRUPT_CONFIRMATION
suffix:colon
id|x25-&gt;intflag
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_INTERRUPT
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;urginline
)paren
(brace
id|queued
op_assign
(paren
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skb
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb_set_owner_r
c_func
(paren
id|skb
comma
id|sk
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|x25-&gt;interrupt_in_queue
comma
id|skb
)paren
suffix:semicolon
id|queued
op_assign
l_int|1
suffix:semicolon
)brace
id|sk_send_sigurg
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_INTERRUPT_CONFIRMATION
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;x25: unknown %02X in state 3&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|queued
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 4, Awaiting Reset Confirmation State.&n; * The handling of the timer(s) is in file x25_timer.c&n; * Handling of state 0 and connection release is in af_x25.c.&n; */
DECL|function|x25_state4_machine
r_static
r_int
id|x25_state4_machine
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
id|frametype
)paren
(brace
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|X25_RESET_REQUEST
suffix:colon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_RESET_CONFIRMATION
)paren
suffix:semicolon
r_case
id|X25_RESET_CONFIRMATION
suffix:colon
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
id|x25_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|x25-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|x25-&gt;va
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|x25-&gt;state
op_assign
id|X25_STATE_3
suffix:semicolon
id|x25_requeue_frames
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|X25_CLEAR_REQUEST
suffix:colon
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_CLEAR_CONFIRMATION
)paren
suffix:semicolon
id|x25_disconnect
c_func
(paren
id|sk
comma
l_int|0
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
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Higher level upcall for a LAPB frame */
DECL|function|x25_process_rx_frame
r_int
id|x25_process_rx_frame
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
id|queued
op_assign
l_int|0
comma
id|frametype
comma
id|ns
comma
id|nr
comma
id|q
comma
id|d
comma
id|m
suffix:semicolon
r_if
c_cond
(paren
id|x25-&gt;state
op_eq
id|X25_STATE_0
)paren
r_return
l_int|0
suffix:semicolon
id|frametype
op_assign
id|x25_decode
c_func
(paren
id|sk
comma
id|skb
comma
op_amp
id|ns
comma
op_amp
id|nr
comma
op_amp
id|q
comma
op_amp
id|d
comma
op_amp
id|m
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|x25-&gt;state
)paren
(brace
r_case
id|X25_STATE_1
suffix:colon
id|queued
op_assign
id|x25_state1_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_STATE_2
suffix:colon
id|queued
op_assign
id|x25_state2_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_STATE_3
suffix:colon
id|queued
op_assign
id|x25_state3_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
comma
id|ns
comma
id|nr
comma
id|q
comma
id|d
comma
id|m
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_STATE_4
suffix:colon
id|queued
op_assign
id|x25_state4_machine
c_func
(paren
id|sk
comma
id|skb
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|x25_kick
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|queued
suffix:semicolon
)brace
DECL|function|x25_backlog_rcv
r_int
id|x25_backlog_rcv
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
)paren
(brace
r_int
id|queued
op_assign
id|x25_process_rx_frame
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
eof
