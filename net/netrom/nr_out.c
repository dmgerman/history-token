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
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
multiline_comment|/*&n; *&t;This is where all NET/ROM frames pass, except for IP-over-NET/ROM which&n; *&t;cannot be fragmented in this manner.&n; */
DECL|function|nr_output
r_void
id|nr_output
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
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
id|transport
(braket
id|NR_TRANSPORT_LEN
)braket
suffix:semicolon
r_int
id|err
comma
id|frontlen
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_minus
id|NR_TRANSPORT_LEN
OG
id|NR_MAX_PACKET_SIZE
)paren
(brace
multiline_comment|/* Save a copy of the Transport Header */
id|memcpy
c_func
(paren
id|transport
comma
id|skb-&gt;data
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|frontlen
op_assign
id|skb_headroom
c_func
(paren
id|skb
)paren
suffix:semicolon
r_while
c_loop
(paren
id|skb-&gt;len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|sock_alloc_send_skb
c_func
(paren
id|sk
comma
id|frontlen
op_plus
id|NR_MAX_PACKET_SIZE
comma
l_int|0
comma
op_amp
id|err
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
id|skbn
comma
id|frontlen
)paren
suffix:semicolon
id|len
op_assign
(paren
id|NR_MAX_PACKET_SIZE
OG
id|skb-&gt;len
)paren
ques
c_cond
id|skb-&gt;len
suffix:colon
id|NR_MAX_PACKET_SIZE
suffix:semicolon
multiline_comment|/* Copy the user data */
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skbn
comma
id|len
)paren
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Duplicate the Transport Header */
id|skb_push
c_func
(paren
id|skbn
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skbn-&gt;data
comma
id|transport
comma
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
l_int|0
)paren
id|skbn-&gt;data
(braket
l_int|4
)braket
op_or_assign
id|NR_MORE_FLAG
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;sk_write_queue
comma
id|skbn
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;sk_write_queue
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
id|nr_kick
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This procedure is passed a buffer descriptor for an iframe. It builds&n; *&t;the rest of the control part of the frame and then writes it out.&n; */
DECL|function|nr_send_iframe
r_static
r_void
id|nr_send_iframe
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
id|nr_sock
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb-&gt;data
(braket
l_int|2
)braket
op_assign
id|nr-&gt;vs
suffix:semicolon
id|skb-&gt;data
(braket
l_int|3
)braket
op_assign
id|nr-&gt;vr
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;condition
op_amp
id|NR_COND_OWN_RX_BUSY
)paren
id|skb-&gt;data
(braket
l_int|4
)braket
op_or_assign
id|NR_CHOKE_FLAG
suffix:semicolon
id|nr_start_idletimer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr_transmit_buffer
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|nr_send_nak_frame
r_void
id|nr_send_nak_frame
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
id|skbn
suffix:semicolon
r_struct
id|nr_sock
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|nr-&gt;ack_queue
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skbn-&gt;data
(braket
l_int|2
)braket
op_assign
id|nr-&gt;va
suffix:semicolon
id|skbn-&gt;data
(braket
l_int|3
)braket
op_assign
id|nr-&gt;vr
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;condition
op_amp
id|NR_COND_OWN_RX_BUSY
)paren
id|skbn-&gt;data
(braket
l_int|4
)braket
op_or_assign
id|NR_CHOKE_FLAG
suffix:semicolon
id|nr_transmit_buffer
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
id|nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_ACK_PENDING
suffix:semicolon
id|nr-&gt;vl
op_assign
id|nr-&gt;vr
suffix:semicolon
id|nr_stop_t1timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|nr_kick
r_void
id|nr_kick
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|nr_sock
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|skbn
suffix:semicolon
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;state
op_ne
id|NR_STATE_3
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;condition
op_amp
id|NR_COND_PEER_RX_BUSY
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;sk_write_queue
)paren
)paren
r_return
suffix:semicolon
id|start
op_assign
(paren
id|skb_peek
c_func
(paren
op_amp
id|nr-&gt;ack_queue
)paren
op_eq
l_int|NULL
)paren
ques
c_cond
id|nr-&gt;va
suffix:colon
id|nr-&gt;vs
suffix:semicolon
id|end
op_assign
(paren
id|nr-&gt;va
op_plus
id|nr-&gt;window
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
r_if
c_cond
(paren
id|start
op_eq
id|end
)paren
r_return
suffix:semicolon
id|nr-&gt;vs
op_assign
id|start
suffix:semicolon
multiline_comment|/*&n;&t; * Transmit data until either we&squot;re out of data to send or&n;&t; * the window is full.&n;&t; */
multiline_comment|/*&n;&t; * Dequeue the frame and copy it.&n;&t; */
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;sk_write_queue
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|sk-&gt;sk_write_queue
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb_set_owner_w
c_func
(paren
id|skbn
comma
id|sk
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Transmit the frame copy.&n;&t;&t; */
id|nr_send_iframe
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
id|nr-&gt;vs
op_assign
(paren
id|nr-&gt;vs
op_plus
l_int|1
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Requeue the original data frame.&n;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|nr-&gt;ack_queue
comma
id|skb
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|nr-&gt;vs
op_ne
id|end
op_logical_and
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;sk_write_queue
)paren
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
id|nr-&gt;vl
op_assign
id|nr-&gt;vr
suffix:semicolon
id|nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_ACK_PENDING
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_t1timer_running
c_func
(paren
id|sk
)paren
)paren
id|nr_start_t1timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|nr_transmit_buffer
r_void
id|nr_transmit_buffer
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
id|nr_sock
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
r_char
op_star
id|dptr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Add the protocol byte and network header.&n;&t; */
id|dptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|NR_NETWORK_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|nr-&gt;source_addr
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_EBIT
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|dptr
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|nr-&gt;dest_addr
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|AX25_EBIT
suffix:semicolon
id|dptr
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|dptr
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|sysctl_netrom_network_ttl_initialiser
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_route_frame
c_func
(paren
id|skb
comma
l_int|NULL
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|nr_disconnect
c_func
(paren
id|sk
comma
id|ENETUNREACH
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The following routines are taken from page 170 of the 7th ARRL Computer&n; * Networking Conference paper, as is the whole state machine.&n; */
DECL|function|nr_establish_data_link
r_void
id|nr_establish_data_link
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|nr_sock
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr-&gt;condition
op_assign
l_int|0x00
suffix:semicolon
id|nr-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_CONNREQ
)paren
suffix:semicolon
id|nr_stop_t2timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr_stop_t4timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr_stop_idletimer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr_start_t1timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Never send a NAK when we are CHOKEd.&n; */
DECL|function|nr_enquiry_response
r_void
id|nr_enquiry_response
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|nr_sock
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
id|frametype
op_assign
id|NR_INFOACK
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;condition
op_amp
id|NR_COND_OWN_RX_BUSY
)paren
(brace
id|frametype
op_or_assign
id|NR_CHOKE_FLAG
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|skb_peek
c_func
(paren
op_amp
id|nr-&gt;reseq_queue
)paren
op_ne
l_int|NULL
)paren
id|frametype
op_or_assign
id|NR_NAK_FLAG
suffix:semicolon
)brace
id|nr_write_internal
c_func
(paren
id|sk
comma
id|frametype
)paren
suffix:semicolon
id|nr-&gt;vl
op_assign
id|nr-&gt;vr
suffix:semicolon
id|nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_ACK_PENDING
suffix:semicolon
)brace
DECL|function|nr_check_iframes_acked
r_void
id|nr_check_iframes_acked
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
id|nr_sock
op_star
id|nrom
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nrom-&gt;vs
op_eq
id|nr
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
id|nr_stop_t1timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nrom-&gt;n2count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|nrom-&gt;va
op_ne
id|nr
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
id|nr_start_t1timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
)brace
eof
