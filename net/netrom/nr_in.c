multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; * Copyright Darryl Miles G7LED (dlm@g7led.demon.co.uk)&n; */
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
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ip.h&gt;&t;&t;&t;/* For ip_rcv */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
DECL|function|nr_queue_rx_frame
r_static
r_int
id|nr_queue_rx_frame
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
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|nr_start_idletimer
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
id|nr-&gt;fraglen
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|nr-&gt;frag_queue
comma
id|skb
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
id|nr-&gt;fraglen
OG
l_int|0
)paren
(brace
multiline_comment|/* End of fragment */
id|nr-&gt;fraglen
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|nr-&gt;frag_queue
comma
id|skb
)paren
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
id|nr-&gt;fraglen
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
id|skbn-&gt;h.raw
op_assign
id|skbn-&gt;data
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
id|nr-&gt;frag_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
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
id|nr-&gt;fraglen
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|sock_queue_rcv_skb
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * State machine for state 1, Awaiting Connection State.&n; * The handling of the timer(s) is in file nr_timer.c.&n; * Handling of state 0 and connection release is in netrom.c.&n; */
DECL|function|nr_state1_machine
r_static
r_int
id|nr_state1_machine
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
id|NR_CONNACK
suffix:colon
(brace
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr_stop_t1timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr_start_idletimer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr-&gt;your_index
op_assign
id|skb-&gt;data
(braket
l_int|17
)braket
suffix:semicolon
id|nr-&gt;your_id
op_assign
id|skb-&gt;data
(braket
l_int|18
)braket
suffix:semicolon
id|nr-&gt;vs
op_assign
l_int|0
suffix:semicolon
id|nr-&gt;va
op_assign
l_int|0
suffix:semicolon
id|nr-&gt;vr
op_assign
l_int|0
suffix:semicolon
id|nr-&gt;vl
op_assign
l_int|0
suffix:semicolon
id|nr-&gt;state
op_assign
id|NR_STATE_3
suffix:semicolon
id|nr-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|nr-&gt;window
op_assign
id|skb-&gt;data
(braket
l_int|20
)braket
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_ESTABLISHED
suffix:semicolon
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
id|NR_CONNACK
op_or
id|NR_CHOKE_FLAG
suffix:colon
id|nr_disconnect
c_func
(paren
id|sk
comma
id|ECONNREFUSED
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
multiline_comment|/*&n; * State machine for state 2, Awaiting Release State.&n; * The handling of the timer(s) is in file nr_timer.c&n; * Handling of state 0 and connection release is in netrom.c.&n; */
DECL|function|nr_state2_machine
r_static
r_int
id|nr_state2_machine
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
id|NR_CONNACK
op_or
id|NR_CHOKE_FLAG
suffix:colon
id|nr_disconnect
c_func
(paren
id|sk
comma
id|ECONNRESET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_DISCREQ
suffix:colon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_DISCACK
)paren
suffix:semicolon
r_case
id|NR_DISCACK
suffix:colon
id|nr_disconnect
c_func
(paren
id|sk
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
multiline_comment|/*&n; * State machine for state 3, Connected State.&n; * The handling of the timer(s) is in file nr_timer.c&n; * Handling of state 0 and connection release is in netrom.c.&n; */
DECL|function|nr_state3_machine
r_static
r_int
id|nr_state3_machine
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
id|nr_cb
op_star
id|nrom
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|sk_buff_head
id|temp_queue
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_int
id|save_vr
suffix:semicolon
r_int
r_int
id|nr
comma
id|ns
suffix:semicolon
r_int
id|queued
op_assign
l_int|0
suffix:semicolon
id|nr
op_assign
id|skb-&gt;data
(braket
l_int|18
)braket
suffix:semicolon
id|ns
op_assign
id|skb-&gt;data
(braket
l_int|17
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|NR_CONNREQ
suffix:colon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_CONNACK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_DISCREQ
suffix:colon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_DISCACK
)paren
suffix:semicolon
id|nr_disconnect
c_func
(paren
id|sk
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_CONNACK
op_or
id|NR_CHOKE_FLAG
suffix:colon
r_case
id|NR_DISCACK
suffix:colon
id|nr_disconnect
c_func
(paren
id|sk
comma
id|ECONNRESET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_INFOACK
suffix:colon
r_case
id|NR_INFOACK
op_or
id|NR_CHOKE_FLAG
suffix:colon
r_case
id|NR_INFOACK
op_or
id|NR_NAK_FLAG
suffix:colon
r_case
id|NR_INFOACK
op_or
id|NR_NAK_FLAG
op_or
id|NR_CHOKE_FLAG
suffix:colon
r_if
c_cond
(paren
id|frametype
op_amp
id|NR_CHOKE_FLAG
)paren
(brace
id|nrom-&gt;condition
op_or_assign
id|NR_COND_PEER_RX_BUSY
suffix:semicolon
id|nr_start_t4timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|nrom-&gt;condition
op_and_assign
op_complement
id|NR_COND_PEER_RX_BUSY
suffix:semicolon
id|nr_stop_t4timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|nr_validate_nr
c_func
(paren
id|sk
comma
id|nr
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|frametype
op_amp
id|NR_NAK_FLAG
)paren
(brace
id|nr_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
id|nr_send_nak_frame
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|nrom-&gt;condition
op_amp
id|NR_COND_PEER_RX_BUSY
)paren
(brace
id|nr_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
r_else
(brace
id|nr_check_iframes_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|NR_INFO
suffix:colon
r_case
id|NR_INFO
op_or
id|NR_NAK_FLAG
suffix:colon
r_case
id|NR_INFO
op_or
id|NR_CHOKE_FLAG
suffix:colon
r_case
id|NR_INFO
op_or
id|NR_MORE_FLAG
suffix:colon
r_case
id|NR_INFO
op_or
id|NR_NAK_FLAG
op_or
id|NR_CHOKE_FLAG
suffix:colon
r_case
id|NR_INFO
op_or
id|NR_CHOKE_FLAG
op_or
id|NR_MORE_FLAG
suffix:colon
r_case
id|NR_INFO
op_or
id|NR_NAK_FLAG
op_or
id|NR_MORE_FLAG
suffix:colon
r_case
id|NR_INFO
op_or
id|NR_NAK_FLAG
op_or
id|NR_CHOKE_FLAG
op_or
id|NR_MORE_FLAG
suffix:colon
r_if
c_cond
(paren
id|frametype
op_amp
id|NR_CHOKE_FLAG
)paren
(brace
id|nrom-&gt;condition
op_or_assign
id|NR_COND_PEER_RX_BUSY
suffix:semicolon
id|nr_start_t4timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
id|nrom-&gt;condition
op_and_assign
op_complement
id|NR_COND_PEER_RX_BUSY
suffix:semicolon
id|nr_stop_t4timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr_validate_nr
c_func
(paren
id|sk
comma
id|nr
)paren
)paren
(brace
r_if
c_cond
(paren
id|frametype
op_amp
id|NR_NAK_FLAG
)paren
(brace
id|nr_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
id|nr_send_nak_frame
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|nrom-&gt;condition
op_amp
id|NR_COND_PEER_RX_BUSY
)paren
(brace
id|nr_frames_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
r_else
(brace
id|nr_check_iframes_acked
c_func
(paren
id|sk
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
)brace
id|queued
op_assign
l_int|1
suffix:semicolon
id|skb_queue_head
c_func
(paren
op_amp
id|nrom-&gt;reseq_queue
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nrom-&gt;condition
op_amp
id|NR_COND_OWN_RX_BUSY
)paren
r_break
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|temp_queue
)paren
suffix:semicolon
r_do
(brace
id|save_vr
op_assign
id|nrom-&gt;vr
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skbn
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|nrom-&gt;reseq_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|ns
op_assign
id|skbn-&gt;data
(braket
l_int|17
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ns
op_eq
id|nrom-&gt;vr
)paren
(brace
r_if
c_cond
(paren
id|nr_queue_rx_frame
c_func
(paren
id|sk
comma
id|skbn
comma
id|frametype
op_amp
id|NR_MORE_FLAG
)paren
op_eq
l_int|0
)paren
(brace
id|nrom-&gt;vr
op_assign
(paren
id|nrom-&gt;vr
op_plus
l_int|1
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
)brace
r_else
(brace
id|nrom-&gt;condition
op_or_assign
id|NR_COND_OWN_RX_BUSY
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|temp_queue
comma
id|skbn
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|nr_in_rx_window
c_func
(paren
id|sk
comma
id|ns
)paren
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|temp_queue
comma
id|skbn
)paren
suffix:semicolon
)brace
r_else
(brace
id|kfree_skb
c_func
(paren
id|skbn
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|skbn
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|temp_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|nrom-&gt;reseq_queue
comma
id|skbn
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|save_vr
op_ne
id|nrom-&gt;vr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Window is full, ack it immediately.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|nrom-&gt;vl
op_plus
id|nrom-&gt;window
)paren
op_mod
id|NR_MODULUS
)paren
op_eq
id|nrom-&gt;vr
)paren
(brace
id|nr_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|nrom-&gt;condition
op_amp
id|NR_COND_ACK_PENDING
)paren
)paren
(brace
id|nrom-&gt;condition
op_or_assign
id|NR_COND_ACK_PENDING
suffix:semicolon
id|nr_start_t2timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|queued
suffix:semicolon
)brace
multiline_comment|/* Higher level upcall for a LAPB frame */
DECL|function|nr_process_rx_frame
r_int
id|nr_process_rx_frame
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
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
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
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;state
op_eq
id|NR_STATE_0
)paren
r_return
l_int|0
suffix:semicolon
id|frametype
op_assign
id|skb-&gt;data
(braket
l_int|19
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|nr-&gt;state
)paren
(brace
r_case
id|NR_STATE_1
suffix:colon
id|queued
op_assign
id|nr_state1_machine
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
id|NR_STATE_2
suffix:colon
id|queued
op_assign
id|nr_state2_machine
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
id|NR_STATE_3
suffix:colon
id|queued
op_assign
id|nr_state3_machine
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
id|nr_kick
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|queued
suffix:semicolon
)brace
eof
