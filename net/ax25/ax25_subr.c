multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)&n; * Copyright (C) Frederic Rible F1OAT (frible@teaser.fr)&n; */
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
multiline_comment|/*&n; *&t;This routine purges all the queues of frames.&n; */
DECL|function|ax25_clear_queues
r_void
id|ax25_clear_queues
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|skb_queue_purge
c_func
(paren
op_amp
id|ax25-&gt;write_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|ax25-&gt;ack_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|ax25-&gt;reseq_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|ax25-&gt;frag_queue
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine purges the input queue of those frames that have been&n; * acknowledged. This replaces the boxes labelled &quot;V(a) &lt;- N(r)&quot; on the&n; * SDL diagram.&n; */
DECL|function|ax25_frames_acked
r_void
id|ax25_frames_acked
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
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/*&n;&t; * Remove all the ack-ed frames from the ack queue.&n;&t; */
r_if
c_cond
(paren
id|ax25-&gt;va
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
id|ax25-&gt;ack_queue
)paren
op_ne
l_int|NULL
op_logical_and
id|ax25-&gt;va
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
id|ax25-&gt;ack_queue
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|ax25-&gt;va
op_assign
(paren
id|ax25-&gt;va
op_plus
l_int|1
)paren
op_mod
id|ax25-&gt;modulus
suffix:semicolon
)brace
)brace
)brace
DECL|function|ax25_requeue_frames
r_void
id|ax25_requeue_frames
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
id|skb_prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Requeue all the un-ack-ed frames on the output queue to be picked&n;&t; * up by ax25_kick called from the timer. This arrangement handles the&n;&t; * possibility of an empty output queue.&n;&t; */
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
id|ax25-&gt;ack_queue
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
id|ax25-&gt;write_queue
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
DECL|function|ax25_validate_nr
r_int
id|ax25_validate_nr
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
r_int
r_int
id|vc
op_assign
id|ax25-&gt;va
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|ax25-&gt;vs
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
id|ax25-&gt;modulus
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_eq
id|ax25-&gt;vs
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This routine is the centralised routine for parsing the control&n; *&t;information for the different frame formats.&n; */
DECL|function|ax25_decode
r_int
id|ax25_decode
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
op_star
id|ns
comma
r_int
op_star
id|nr
comma
r_int
op_star
id|pf
)paren
(brace
r_int
r_char
op_star
id|frame
suffix:semicolon
r_int
id|frametype
op_assign
id|AX25_ILLEGAL
suffix:semicolon
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
id|pf
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;modulus
op_eq
id|AX25_MODULUS
)paren
(brace
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_S
)paren
op_eq
l_int|0
)paren
(brace
id|frametype
op_assign
id|AX25_I
suffix:semicolon
multiline_comment|/* I frame - carries NR/NS/PF */
op_star
id|ns
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x07
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_PF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_U
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* S frame - take out PF/NR */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
l_int|0x0F
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_PF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_U
)paren
op_eq
l_int|3
)paren
(brace
multiline_comment|/* U frame - take out PF */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
op_complement
id|AX25_PF
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_PF
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_S
)paren
op_eq
l_int|0
)paren
(brace
id|frametype
op_assign
id|AX25_I
suffix:semicolon
multiline_comment|/* I frame - carries NR/NS/PF */
op_star
id|ns
op_assign
(paren
id|frame
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|1
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|1
)braket
op_amp
id|AX25_EPF
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
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_U
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* S frame - take out PF/NR */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
l_int|0x0F
suffix:semicolon
op_star
id|nr
op_assign
(paren
id|frame
(braket
l_int|1
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|1
)braket
op_amp
id|AX25_EPF
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
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_U
)paren
op_eq
l_int|3
)paren
(brace
multiline_comment|/* U frame - take out PF */
id|frametype
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
op_complement
id|AX25_PF
suffix:semicolon
op_star
id|pf
op_assign
id|frame
(braket
l_int|0
)braket
op_amp
id|AX25_PF
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
r_return
id|frametype
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This routine is called when the HDLC layer internally  generates a&n; *&t;command or  response  for  the remote machine ( eg. RR, UA etc. ).&n; *&t;Only supervisory or unnumbered frames are processed.&n; */
DECL|function|ax25_send_control
r_void
id|ax25_send_control
c_func
(paren
id|ax25_cb
op_star
id|ax25
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
id|ax25-&gt;ax25_dev-&gt;dev-&gt;hard_header_len
op_plus
l_int|2
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
id|ax25-&gt;ax25_dev-&gt;dev-&gt;hard_header_len
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* Assume a response - address structure for DTE */
r_if
c_cond
(paren
id|ax25-&gt;modulus
op_eq
id|AX25_MODULUS
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
(paren
id|poll_bit
)paren
ques
c_cond
id|AX25_PF
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|frametype
op_amp
id|AX25_U
)paren
op_eq
id|AX25_S
)paren
multiline_comment|/* S frames carry NR */
op_star
id|dptr
op_or_assign
(paren
id|ax25-&gt;vr
op_lshift
l_int|5
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|frametype
op_amp
id|AX25_U
)paren
op_eq
id|AX25_U
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
(paren
id|poll_bit
)paren
ques
c_cond
id|AX25_PF
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
id|ax25-&gt;vr
op_lshift
l_int|1
)paren
suffix:semicolon
id|dptr
(braket
l_int|1
)braket
op_or_assign
(paren
id|poll_bit
)paren
ques
c_cond
id|AX25_EPF
suffix:colon
l_int|0
suffix:semicolon
)brace
)brace
id|ax25_transmit_buffer
c_func
(paren
id|ax25
comma
id|skb
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Send a &squot;DM&squot; to an unknown connection attempt, or an invalid caller.&n; *&n; *&t;Note: src here is the sender, thus it&squot;s the target of the DM&n; */
DECL|function|ax25_return_dm
r_void
id|ax25_return_dm
c_func
(paren
r_struct
id|net_device
op_star
id|dev
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
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_char
op_star
id|dptr
suffix:semicolon
id|ax25_digi
id|retdigi
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
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
id|dev-&gt;hard_header_len
op_plus
l_int|1
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Next SABM will get DM&squot;d */
id|skb_reserve
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|ax25_digi_invert
c_func
(paren
id|digi
comma
op_amp
id|retdigi
)paren
suffix:semicolon
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
id|AX25_DM
op_or
id|AX25_PF
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Do the address ourselves&n;&t; */
id|dptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|ax25_addr_size
c_func
(paren
id|digi
)paren
)paren
suffix:semicolon
id|dptr
op_add_assign
id|ax25_addr_build
c_func
(paren
id|dptr
comma
id|dest
comma
id|src
comma
op_amp
id|retdigi
comma
id|AX25_RESPONSE
comma
id|AX25_MODULUS
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|ax25_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Exponential backoff for AX.25&n; */
DECL|function|ax25_calculate_t1
r_void
id|ax25_calculate_t1
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_int
id|n
comma
id|t
op_assign
l_int|2
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;backoff
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|t
op_add_assign
l_int|2
op_star
id|ax25-&gt;n2count
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|ax25-&gt;n2count
suffix:semicolon
id|n
op_increment
)paren
id|t
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
l_int|8
)paren
id|t
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ax25-&gt;t1
op_assign
id|t
op_star
id|ax25-&gt;rtt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Calculate the Round Trip Time&n; */
DECL|function|ax25_calculate_rtt
r_void
id|ax25_calculate_rtt
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;backoff
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ax25_t1timer_running
c_func
(paren
id|ax25
)paren
op_logical_and
id|ax25-&gt;n2count
op_eq
l_int|0
)paren
id|ax25-&gt;rtt
op_assign
(paren
l_int|9
op_star
id|ax25-&gt;rtt
op_plus
id|ax25-&gt;t1
op_minus
id|ax25_display_timer
c_func
(paren
op_amp
id|ax25-&gt;t1timer
)paren
)paren
op_div
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;rtt
OL
id|AX25_T1CLAMPLO
)paren
id|ax25-&gt;rtt
op_assign
id|AX25_T1CLAMPLO
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;rtt
OG
id|AX25_T1CLAMPHI
)paren
id|ax25-&gt;rtt
op_assign
id|AX25_T1CLAMPHI
suffix:semicolon
)brace
DECL|function|ax25_disconnect
r_void
id|ax25_disconnect
c_func
(paren
id|ax25_cb
op_star
id|ax25
comma
r_int
id|reason
)paren
(brace
id|ax25_clear_queues
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
id|ax25_stop_t2timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_stop_t3timer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25_stop_idletimer
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_0
suffix:semicolon
id|ax25_link_failed
c_func
(paren
id|ax25
comma
id|reason
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;sk
op_ne
l_int|NULL
)paren
(brace
id|bh_lock_sock
c_func
(paren
id|ax25-&gt;sk
)paren
suffix:semicolon
id|ax25-&gt;sk-&gt;sk_state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|ax25-&gt;sk-&gt;sk_err
op_assign
id|reason
suffix:semicolon
id|ax25-&gt;sk-&gt;sk_shutdown
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
id|ax25-&gt;sk
comma
id|SOCK_DEAD
)paren
)paren
(brace
id|ax25-&gt;sk
op_member_access_from_pointer
id|sk_state_change
c_func
(paren
id|ax25-&gt;sk
)paren
suffix:semicolon
id|sock_set_flag
c_func
(paren
id|ax25-&gt;sk
comma
id|SOCK_DEAD
)paren
suffix:semicolon
)brace
id|bh_unlock_sock
c_func
(paren
id|ax25-&gt;sk
)paren
suffix:semicolon
)brace
)brace
eof
