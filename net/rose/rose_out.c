multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; */
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/rose.h&gt;
multiline_comment|/*&n; *&t;This procedure is passed a buffer descriptor for an iframe. It builds&n; *&t;the rest of the control part of the frame and then writes it out.&n; */
DECL|function|rose_send_iframe
r_static
r_void
id|rose_send_iframe
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
id|rose_cb
op_star
id|rose
op_assign
id|rose_sk
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
op_or_assign
(paren
id|rose-&gt;vr
op_lshift
l_int|5
)paren
op_amp
l_int|0xE0
suffix:semicolon
id|skb-&gt;data
(braket
l_int|2
)braket
op_or_assign
(paren
id|rose-&gt;vs
op_lshift
l_int|1
)paren
op_amp
l_int|0x0E
suffix:semicolon
id|rose_start_idletimer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_transmit_link
c_func
(paren
id|skb
comma
id|rose-&gt;neighbour
)paren
suffix:semicolon
)brace
DECL|function|rose_kick
r_void
id|rose_kick
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|rose_cb
op_star
id|rose
op_assign
id|rose_sk
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
id|rose-&gt;state
op_ne
id|ROSE_STATE_3
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rose-&gt;condition
op_amp
id|ROSE_COND_PEER_RX_BUSY
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
id|rose-&gt;ack_queue
)paren
op_eq
l_int|NULL
)paren
ques
c_cond
id|rose-&gt;va
suffix:colon
id|rose-&gt;vs
suffix:semicolon
id|end
op_assign
(paren
id|rose-&gt;va
op_plus
id|sysctl_rose_window_size
)paren
op_mod
id|ROSE_MODULUS
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
id|rose-&gt;vs
op_assign
id|start
suffix:semicolon
multiline_comment|/*&n;&t; * Transmit data until either we&squot;re out of data to send or&n;&t; * the window is full.&n;&t; */
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
id|rose_send_iframe
c_func
(paren
id|sk
comma
id|skbn
)paren
suffix:semicolon
id|rose-&gt;vs
op_assign
(paren
id|rose-&gt;vs
op_plus
l_int|1
)paren
op_mod
id|ROSE_MODULUS
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Requeue the original data frame.&n;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|rose-&gt;ack_queue
comma
id|skb
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rose-&gt;vs
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
id|rose-&gt;vl
op_assign
id|rose-&gt;vr
suffix:semicolon
id|rose-&gt;condition
op_and_assign
op_complement
id|ROSE_COND_ACK_PENDING
suffix:semicolon
id|rose_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following routines are taken from page 170 of the 7th ARRL Computer&n; * Networking Conference paper, as is the whole state machine.&n; */
DECL|function|rose_enquiry_response
r_void
id|rose_enquiry_response
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|rose_cb
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rose-&gt;condition
op_amp
id|ROSE_COND_OWN_RX_BUSY
)paren
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RNR
)paren
suffix:semicolon
r_else
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RR
)paren
suffix:semicolon
id|rose-&gt;vl
op_assign
id|rose-&gt;vr
suffix:semicolon
id|rose-&gt;condition
op_and_assign
op_complement
id|ROSE_COND_ACK_PENDING
suffix:semicolon
id|rose_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
eof
