multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|variable|ax25_frag_lock
r_static
id|spinlock_t
id|ax25_frag_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|ax25_send_frame
id|ax25_cb
op_star
id|ax25_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|paclen
comma
id|ax25_address
op_star
id|src
comma
id|ax25_address
op_star
id|dest
comma
id|ax25_digi
op_star
id|digi
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ax25_dev
op_star
id|ax25_dev
suffix:semicolon
id|ax25_cb
op_star
id|ax25
suffix:semicolon
multiline_comment|/*&n;&t; * Take the default packet length for the device if zero is&n;&t; * specified.&n;&t; */
r_if
c_cond
(paren
id|paclen
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|ax25_dev
op_assign
id|ax25_dev_ax25dev
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|paclen
op_assign
id|ax25_dev-&gt;values
(braket
id|AX25_VALUES_PACLEN
)braket
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Look for an existing connection.&n;&t; */
r_if
c_cond
(paren
(paren
id|ax25
op_assign
id|ax25_find_cb
c_func
(paren
id|src
comma
id|dest
comma
id|digi
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|ax25_output
c_func
(paren
id|ax25
comma
id|paclen
comma
id|skb
)paren
suffix:semicolon
r_return
id|ax25
suffix:semicolon
multiline_comment|/* It already existed */
)brace
r_if
c_cond
(paren
(paren
id|ax25_dev
op_assign
id|ax25_dev_ax25dev
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ax25
op_assign
id|ax25_create_cb
c_func
(paren
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|ax25_fillin_cb
c_func
(paren
id|ax25
comma
id|ax25_dev
)paren
suffix:semicolon
id|ax25-&gt;source_addr
op_assign
op_star
id|src
suffix:semicolon
id|ax25-&gt;dest_addr
op_assign
op_star
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|digi
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|ax25-&gt;digipeat
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ax25_digi
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ax25_cb_put
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|ax25-&gt;digipeat
comma
id|digi
comma
r_sizeof
(paren
id|ax25_digi
)paren
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_std_establish_data_link
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
id|ax25_dev-&gt;dama.slave
)paren
id|ax25_ds_establish_data_link
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_else
id|ax25_std_establish_data_link
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
id|ax25_cb_add
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_1
suffix:semicolon
id|ax25_start_heartbeat
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_output
c_func
(paren
id|ax25
comma
id|paclen
comma
id|skb
)paren
suffix:semicolon
r_return
id|ax25
suffix:semicolon
multiline_comment|/* We had to create it */
)brace
multiline_comment|/*&n; *&t;All outgoing AX.25 I frames pass via this routine. Therefore this is&n; *&t;where the fragmentation of frames takes place. If fragment is set to&n; *&t;zero then we are not allowed to do fragmentation, even if the frame&n; *&t;is too large.&n; */
DECL|function|ax25_output
r_void
id|ax25_output
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
id|paclen
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
op_star
id|p
suffix:semicolon
r_int
id|frontlen
comma
id|len
comma
id|fragno
comma
id|ka9qfrag
comma
id|first
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;len
op_minus
l_int|1
)paren
OG
id|paclen
)paren
(brace
r_if
c_cond
(paren
op_star
id|skb-&gt;data
op_eq
id|AX25_P_TEXT
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* skip PID */
id|ka9qfrag
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|paclen
op_sub_assign
l_int|2
suffix:semicolon
multiline_comment|/* Allow for fragment control info */
id|ka9qfrag
op_assign
l_int|1
suffix:semicolon
)brace
id|fragno
op_assign
id|skb-&gt;len
op_div
id|paclen
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_mod
id|paclen
op_eq
l_int|0
)paren
id|fragno
op_decrement
suffix:semicolon
id|frontlen
op_assign
id|skb_headroom
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* Address space + CTRL */
r_while
c_loop
(paren
id|skb-&gt;len
OG
l_int|0
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|ax25_frag_lock
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
id|paclen
op_plus
l_int|2
op_plus
id|frontlen
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|ax25_frag_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;AX.25: ax25_output - out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;sk
op_ne
l_int|NULL
)paren
id|skb_set_owner_w
c_func
(paren
id|skbn
comma
id|skb-&gt;sk
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|ax25_frag_lock
)paren
suffix:semicolon
id|len
op_assign
(paren
id|paclen
OG
id|skb-&gt;len
)paren
ques
c_cond
id|skb-&gt;len
suffix:colon
id|paclen
suffix:semicolon
r_if
c_cond
(paren
id|ka9qfrag
op_eq
l_int|1
)paren
(brace
id|skb_reserve
c_func
(paren
id|skbn
comma
id|frontlen
op_plus
l_int|2
)paren
suffix:semicolon
id|skbn-&gt;nh.raw
op_assign
id|skbn-&gt;data
op_plus
(paren
id|skb-&gt;nh.raw
op_minus
id|skb-&gt;data
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
id|len
)paren
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
id|p
op_assign
id|skb_push
c_func
(paren
id|skbn
comma
l_int|2
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|AX25_P_SEGMENT
suffix:semicolon
op_star
id|p
op_assign
id|fragno
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|first
)paren
(brace
op_star
id|p
op_or_assign
id|AX25_SEG_FIRST
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|skb_reserve
c_func
(paren
id|skbn
comma
id|frontlen
op_plus
l_int|1
)paren
suffix:semicolon
id|skbn-&gt;nh.raw
op_assign
id|skbn-&gt;data
op_plus
(paren
id|skb-&gt;nh.raw
op_minus
id|skb-&gt;data
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
id|len
)paren
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
id|p
op_assign
id|skb_push
c_func
(paren
id|skbn
comma
l_int|1
)paren
suffix:semicolon
op_star
id|p
op_assign
id|AX25_P_TEXT
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|ax25-&gt;write_queue
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
id|ax25-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Throw it on the queue */
)brace
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_kick
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
multiline_comment|/*&n;&t; * A DAMA slave is _required_ to work as normal AX.25L2V2&n;&t; * if no DAMA master is available.&n;&t; */
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|ax25-&gt;ax25_dev-&gt;dama.slave
)paren
id|ax25_kick
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/*&n; *  This procedure is passed a buffer descriptor for an iframe. It builds&n; *  the rest of the control part of the frame and then writes it out.&n; */
DECL|function|ax25_send_iframe
r_static
r_void
id|ax25_send_iframe
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|poll_bit
)paren
(brace
r_int
r_char
op_star
id|frame
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
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;modulus
op_eq
id|AX25_MODULUS
)paren
(brace
id|frame
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|frame
op_assign
id|AX25_I
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|AX25_PF
suffix:colon
l_int|0
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|ax25-&gt;vr
op_lshift
l_int|5
)paren
suffix:semicolon
op_star
id|frame
op_or_assign
(paren
id|ax25-&gt;vs
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|frame
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|frame
(braket
l_int|0
)braket
op_assign
id|AX25_I
suffix:semicolon
id|frame
(braket
l_int|0
)braket
op_or_assign
(paren
id|ax25-&gt;vs
op_lshift
l_int|1
)paren
suffix:semicolon
id|frame
(braket
l_int|1
)braket
op_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|AX25_EPF
suffix:colon
l_int|0
suffix:semicolon
id|frame
(braket
l_int|1
)braket
op_or_assign
(paren
id|ax25-&gt;vr
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
id|ax25_start_idletimer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_transmit_buffer
c_func
(paren
id|ax25
comma
id|skb
comma
id|AX25_COMMAND
)paren
suffix:semicolon
)brace
DECL|function|ax25_kick
r_void
id|ax25_kick
c_func
(paren
id|ax25_cb
op_star
id|ax25
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
r_int
id|last
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|start
comma
id|end
comma
id|next
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;state
op_ne
id|AX25_STATE_3
op_logical_and
id|ax25-&gt;state
op_ne
id|AX25_STATE_4
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;condition
op_amp
id|AX25_COND_PEER_RX_BUSY
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|skb_peek
c_func
(paren
op_amp
id|ax25-&gt;write_queue
)paren
op_eq
l_int|NULL
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
id|ax25-&gt;ack_queue
)paren
op_eq
l_int|NULL
)paren
ques
c_cond
id|ax25-&gt;va
suffix:colon
id|ax25-&gt;vs
suffix:semicolon
id|end
op_assign
(paren
id|ax25-&gt;va
op_plus
id|ax25-&gt;window
)paren
op_mod
id|ax25-&gt;modulus
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
id|ax25-&gt;vs
op_assign
id|start
suffix:semicolon
multiline_comment|/*&n;&t; * Transmit data until either we&squot;re out of data to send or&n;&t; * the window is full. Send a poll on the final I frame if&n;&t; * the window is filled.&n;&t; */
multiline_comment|/*&n;&t; * Dequeue the frame and copy it.&n;&t; */
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;write_queue
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
id|ax25-&gt;write_queue
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;sk
op_ne
l_int|NULL
)paren
id|skb_set_owner_w
c_func
(paren
id|skbn
comma
id|skb-&gt;sk
)paren
suffix:semicolon
id|next
op_assign
(paren
id|ax25-&gt;vs
op_plus
l_int|1
)paren
op_mod
id|ax25-&gt;modulus
suffix:semicolon
id|last
op_assign
(paren
id|next
op_eq
id|end
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Transmit the frame copy.&n;&t;&t; * bke 960114: do not set the Poll bit on the last frame&n;&t;&t; * in DAMA mode.&n;&t;&t; */
r_switch
c_cond
(paren
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_PROTOCOL
)braket
)paren
(brace
r_case
id|AX25_PROTO_STD_SIMPLEX
suffix:colon
r_case
id|AX25_PROTO_STD_DUPLEX
suffix:colon
id|ax25_send_iframe
c_func
(paren
id|ax25
comma
id|skbn
comma
(paren
id|last
)paren
ques
c_cond
id|AX25_POLLON
suffix:colon
id|AX25_POLLOFF
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AX25_DAMA_SLAVE
r_case
id|AX25_PROTO_DAMA_SLAVE
suffix:colon
id|ax25_send_iframe
c_func
(paren
id|ax25
comma
id|skbn
comma
id|AX25_POLLOFF
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
id|ax25-&gt;vs
op_assign
id|next
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Requeue the original data frame.&n;&t;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
comma
id|skb
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|last
op_logical_and
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|ax25-&gt;write_queue
)paren
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_ACK_PENDING
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ax25_t1timer_running
c_func
(paren
id|ax25
)paren
)paren
(brace
id|ax25_stop_t3timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_t1timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
)brace
DECL|function|ax25_transmit_buffer
r_void
id|ax25_transmit_buffer
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|type
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
id|ptr
suffix:semicolon
r_int
id|headroom
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;ax25_dev
op_eq
l_int|NULL
)paren
(brace
id|ax25_disconnect
c_func
(paren
id|ax25
comma
id|ENETUNREACH
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|headroom
op_assign
id|ax25_addr_size
c_func
(paren
id|ax25-&gt;digipeat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|headroom
)paren
(brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|headroom
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;AX.25: ax25_transmit_buffer - out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;sk
op_ne
l_int|NULL
)paren
id|skb_set_owner_w
c_func
(paren
id|skbn
comma
id|skb-&gt;sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skbn
suffix:semicolon
)brace
id|ptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|headroom
)paren
suffix:semicolon
id|ax25_addr_build
c_func
(paren
id|ptr
comma
op_amp
id|ax25-&gt;source_addr
comma
op_amp
id|ax25-&gt;dest_addr
comma
id|ax25-&gt;digipeat
comma
id|type
comma
id|ax25-&gt;modulus
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|ax25-&gt;ax25_dev-&gt;dev
suffix:semicolon
id|ax25_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A small shim to dev_queue_xmit to add the KISS control byte, and do&n; *&t;any packet forwarding in operation.&n; */
DECL|function|ax25_queue_xmit
r_void
id|ax25_queue_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_AX25
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|ax25_fwd_dev
c_func
(paren
id|skb-&gt;dev
)paren
suffix:semicolon
id|ptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|ptr
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* KISS */
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|ax25_check_iframes_acked
r_int
id|ax25_check_iframes_acked
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;vs
op_eq
id|nr
)paren
(brace
id|ax25_frames_acked
c_func
(paren
id|ax25
comma
id|nr
)paren
suffix:semicolon
id|ax25_calculate_rtt
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_stop_t1timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_t3timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ax25-&gt;va
op_ne
id|nr
)paren
(brace
id|ax25_frames_acked
c_func
(paren
id|ax25
comma
id|nr
)paren
suffix:semicolon
id|ax25_calculate_t1
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_start_t1timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
