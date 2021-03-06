multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; */
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
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
multiline_comment|/*&n; *&t;This routine purges all of the queues of frames.&n; */
DECL|function|nr_clear_queues
r_void
id|nr_clear_queues
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
id|nr-&gt;ack_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|nr-&gt;reseq_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|nr-&gt;frag_queue
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine purges the input queue of those frames that have been&n; * acknowledged. This replaces the boxes labelled &quot;V(a) &lt;- N(r)&quot; on the&n; * SDL diagram.&n; */
DECL|function|nr_frames_acked
r_void
id|nr_frames_acked
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
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/*&n;&t; * Remove all the ack-ed frames from the ack queue.&n;&t; */
r_if
c_cond
(paren
id|nrom-&gt;va
op_ne
id|nr
)paren
(brace
r_while
c_loop
(paren
id|skb_peek
c_func
(paren
op_amp
id|nrom-&gt;ack_queue
)paren
op_ne
l_int|NULL
op_logical_and
id|nrom-&gt;va
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
id|nrom-&gt;ack_queue
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|nrom-&gt;va
op_assign
(paren
id|nrom-&gt;va
op_plus
l_int|1
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Requeue all the un-ack-ed frames on the output queue to be picked&n; * up by nr_kick called from the timer. This arrangement handles the&n; * possibility of an empty output queue.&n; */
DECL|function|nr_requeue_frames
r_void
id|nr_requeue_frames
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
id|nr_sk
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
id|skb_prev
op_eq
l_int|NULL
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
DECL|function|nr_validate_nr
r_int
id|nr_validate_nr
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
r_int
r_int
id|vc
op_assign
id|nrom-&gt;va
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|nrom-&gt;vs
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
id|NR_MODULUS
suffix:semicolon
)brace
r_return
id|nr
op_eq
id|nrom-&gt;vs
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Check that ns is within the receive window.&n; */
DECL|function|nr_in_rx_window
r_int
id|nr_in_rx_window
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|ns
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
r_int
id|vc
op_assign
id|nr-&gt;vr
suffix:semicolon
r_int
r_int
id|vt
op_assign
(paren
id|nr-&gt;vl
op_plus
id|nr-&gt;window
)paren
op_mod
id|NR_MODULUS
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|vt
)paren
(brace
r_if
c_cond
(paren
id|ns
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
id|NR_MODULUS
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  This routine is called when the HDLC layer internally generates a&n; *  control frame.&n; */
DECL|function|nr_write_internal
r_void
id|nr_write_internal
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
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_int
id|len
comma
id|timeout
suffix:semicolon
id|len
op_assign
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
op_amp
l_int|0x0F
)paren
(brace
r_case
id|NR_CONNREQ
suffix:colon
id|len
op_add_assign
l_int|17
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_CONNACK
suffix:colon
id|len
op_add_assign
(paren
id|nr-&gt;bpqext
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_DISCREQ
suffix:colon
r_case
id|NR_DISCACK
suffix:colon
r_case
id|NR_INFOACK
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NET/ROM: nr_write_internal - invalid frame type %d&bslash;n&quot;
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
multiline_comment|/*&n;&t; *&t;Space for AX.25 and NET/ROM network header&n;&t; */
id|skb_reserve
c_func
(paren
id|skb
comma
id|NR_NETWORK_LEN
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
op_amp
l_int|0x0F
)paren
(brace
r_case
id|NR_CONNREQ
suffix:colon
id|timeout
op_assign
id|nr-&gt;t1
op_div
id|HZ
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;my_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;my_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
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
id|nr-&gt;window
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|nr-&gt;user_addr
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
op_star
id|dptr
op_increment
op_assign
id|timeout
op_mod
l_int|256
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|timeout
op_div
l_int|256
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_CONNACK
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;your_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;your_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;my_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;my_id
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
id|nr-&gt;window
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;bpqext
)paren
op_star
id|dptr
op_increment
op_assign
id|sysctl_netrom_network_ttl_initialiser
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_DISCREQ
suffix:colon
r_case
id|NR_DISCACK
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;your_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;your_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_INFOACK
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;your_index
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;your_id
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|nr-&gt;vr
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
r_break
suffix:semicolon
)brace
id|nr_transmit_buffer
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called when a Connect Acknowledge with the Choke Flag&n; * set is needed to refuse a connection.&n; */
DECL|function|nr_transmit_refusal
r_void
id|nr_transmit_refusal
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|mine
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
op_plus
l_int|1
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
r_return
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skbn
comma
l_int|0
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skbn
comma
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|skb-&gt;data
op_plus
l_int|7
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
id|skb-&gt;data
op_plus
l_int|0
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
id|mine
)paren
(brace
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|skb-&gt;data
(braket
l_int|15
)braket
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|skb-&gt;data
(braket
l_int|16
)braket
suffix:semicolon
)brace
r_else
(brace
op_star
id|dptr
op_increment
op_assign
id|skb-&gt;data
(braket
l_int|15
)braket
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|skb-&gt;data
(braket
l_int|16
)braket
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
op_star
id|dptr
op_increment
op_assign
id|NR_CONNACK
op_or
id|NR_CHOKE_FLAG
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_route_frame
c_func
(paren
id|skbn
comma
l_int|NULL
)paren
)paren
id|kfree_skb
c_func
(paren
id|skbn
)paren
suffix:semicolon
)brace
DECL|function|nr_disconnect
r_void
id|nr_disconnect
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|reason
)paren
(brace
id|nr_stop_t1timer
c_func
(paren
id|sk
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
id|nr_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|nr_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|state
op_assign
id|NR_STATE_0
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
eof
