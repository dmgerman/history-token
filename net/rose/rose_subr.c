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
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/rose.h&gt;
multiline_comment|/*&n; *&t;This routine purges all of the queues of frames.&n; */
DECL|function|rose_clear_queues
r_void
id|rose_clear_queues
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|skb_queue_purge
c_func
(paren
op_amp
id|sk-&gt;write_queue
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|rose_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|ack_queue
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine purges the input queue of those frames that have been&n; * acknowledged. This replaces the boxes labelled &quot;V(a) &lt;- N(r)&quot; on the&n; * SDL diagram.&n; */
DECL|function|rose_frames_acked
r_void
id|rose_frames_acked
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
multiline_comment|/*&n;&t; * Remove all the ack-ed frames from the ack queue.&n;&t; */
r_if
c_cond
(paren
id|rose-&gt;va
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
id|rose-&gt;ack_queue
)paren
op_ne
l_int|NULL
op_logical_and
id|rose-&gt;va
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
id|rose-&gt;ack_queue
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|rose-&gt;va
op_assign
(paren
id|rose-&gt;va
op_plus
l_int|1
)paren
op_mod
id|ROSE_MODULUS
suffix:semicolon
)brace
)brace
)brace
DECL|function|rose_requeue_frames
r_void
id|rose_requeue_frames
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
multiline_comment|/*&n;&t; * Requeue all the un-ack-ed frames on the output queue to be picked&n;&t; * up by rose_kick. This arrangement handles the possibility of an&n;&t; * empty output queue.&n;&t; */
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
id|rose_sk
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
id|sk-&gt;write_queue
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
DECL|function|rose_validate_nr
r_int
id|rose_validate_nr
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
r_int
r_int
id|vc
op_assign
id|rose-&gt;va
suffix:semicolon
r_while
c_loop
(paren
id|vc
op_ne
id|rose-&gt;vs
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
id|ROSE_MODULUS
suffix:semicolon
)brace
r_return
id|nr
op_eq
id|rose-&gt;vs
suffix:semicolon
)brace
multiline_comment|/*&n; *  This routine is called when the packet layer internally generates a&n; *  control frame.&n; */
DECL|function|rose_write_internal
r_void
id|rose_write_internal
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
suffix:semicolon
r_int
r_char
op_star
id|dptr
suffix:semicolon
r_int
r_char
id|lci1
comma
id|lci2
suffix:semicolon
r_char
id|buffer
(braket
l_int|100
)braket
suffix:semicolon
r_int
id|len
comma
id|faclen
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|ROSE_MIN_LEN
op_plus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|ROSE_CALL_REQUEST
suffix:colon
id|len
op_add_assign
l_int|1
op_plus
id|ROSE_ADDR_LEN
op_plus
id|ROSE_ADDR_LEN
suffix:semicolon
id|faclen
op_assign
id|rose_create_facilities
c_func
(paren
id|buffer
comma
id|rose
)paren
suffix:semicolon
id|len
op_add_assign
id|faclen
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_CALL_ACCEPTED
suffix:colon
r_case
id|ROSE_CLEAR_REQUEST
suffix:colon
r_case
id|ROSE_RESET_REQUEST
suffix:colon
id|len
op_add_assign
l_int|2
suffix:semicolon
r_break
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
multiline_comment|/*&n;&t; *&t;Space for AX.25 header and PID.&n;&t; */
id|skb_reserve
c_func
(paren
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
l_int|1
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
id|lci1
op_assign
(paren
id|rose-&gt;lci
op_rshift
l_int|8
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|lci2
op_assign
(paren
id|rose-&gt;lci
op_rshift
l_int|0
)paren
op_amp
l_int|0xFF
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|ROSE_CALL_REQUEST
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
op_or
id|lci1
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
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
l_int|0xAA
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|rose-&gt;dest_addr
comma
id|ROSE_ADDR_LEN
)paren
suffix:semicolon
id|dptr
op_add_assign
id|ROSE_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
op_amp
id|rose-&gt;source_addr
comma
id|ROSE_ADDR_LEN
)paren
suffix:semicolon
id|dptr
op_add_assign
id|ROSE_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|dptr
comma
id|buffer
comma
id|faclen
)paren
suffix:semicolon
id|dptr
op_add_assign
id|faclen
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_CALL_ACCEPTED
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
op_or
id|lci1
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
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
multiline_comment|/* Address length */
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Facilities length */
r_break
suffix:semicolon
r_case
id|ROSE_CLEAR_REQUEST
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
op_or
id|lci1
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
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
id|rose-&gt;cause
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|rose-&gt;diagnostic
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_RESET_REQUEST
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
op_or
id|lci1
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
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
id|ROSE_DTE_ORIGINATED
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_RR
suffix:colon
r_case
id|ROSE_RNR
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
op_or
id|lci1
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
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
id|rose-&gt;vr
op_lshift
l_int|5
)paren
op_amp
l_int|0xE0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_CLEAR_CONFIRMATION
suffix:colon
r_case
id|ROSE_RESET_CONFIRMATION
suffix:colon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
op_or
id|lci1
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|lci2
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|frametype
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ROSE: rose_write_internal - invalid frametype %02X&bslash;n&quot;
comma
id|frametype
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
id|rose_transmit_link
c_func
(paren
id|skb
comma
id|rose-&gt;neighbour
)paren
suffix:semicolon
)brace
DECL|function|rose_decode
r_int
id|rose_decode
c_func
(paren
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
r_int
r_char
op_star
id|frame
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
id|ROSE_CALL_REQUEST
suffix:colon
r_case
id|ROSE_CALL_ACCEPTED
suffix:colon
r_case
id|ROSE_CLEAR_REQUEST
suffix:colon
r_case
id|ROSE_CLEAR_CONFIRMATION
suffix:colon
r_case
id|ROSE_RESET_REQUEST
suffix:colon
r_case
id|ROSE_RESET_CONFIRMATION
suffix:colon
r_return
id|frame
(braket
l_int|2
)braket
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
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
id|ROSE_RR
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
id|ROSE_RNR
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
id|ROSE_DATA
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
id|ROSE_Q_BIT
)paren
op_eq
id|ROSE_Q_BIT
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
id|ROSE_D_BIT
)paren
op_eq
id|ROSE_D_BIT
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
id|ROSE_M_BIT
)paren
op_eq
id|ROSE_M_BIT
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
id|ROSE_DATA
suffix:semicolon
)brace
r_return
id|ROSE_ILLEGAL
suffix:semicolon
)brace
DECL|function|rose_parse_national
r_static
r_int
id|rose_parse_national
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_struct
id|rose_facilities_struct
op_star
id|facilities
comma
r_int
id|len
)paren
(brace
r_int
r_char
op_star
id|pt
suffix:semicolon
r_int
r_char
id|l
comma
id|lg
comma
id|n
op_assign
l_int|0
suffix:semicolon
r_int
id|fac_national_digis_received
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_switch
c_cond
(paren
op_star
id|p
op_amp
l_int|0xC0
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|p
op_add_assign
l_int|2
suffix:semicolon
id|n
op_add_assign
l_int|2
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_NATIONAL_RAND
)paren
id|facilities-&gt;rand
op_assign
(paren
(paren
id|p
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_amp
l_int|0xFF00
)paren
op_plus
(paren
(paren
id|p
(braket
l_int|2
)braket
op_lshift
l_int|0
)paren
op_amp
l_int|0x00FF
)paren
suffix:semicolon
id|p
op_add_assign
l_int|3
suffix:semicolon
id|n
op_add_assign
l_int|3
suffix:semicolon
id|len
op_sub_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80
suffix:colon
id|p
op_add_assign
l_int|4
suffix:semicolon
id|n
op_add_assign
l_int|4
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xC0
suffix:colon
id|l
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_NATIONAL_DEST_DIGI
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fac_national_digis_received
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;source_digis
(braket
l_int|0
)braket
comma
id|p
op_plus
l_int|2
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|facilities-&gt;source_ndigis
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_NATIONAL_SRC_DIGI
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fac_national_digis_received
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;dest_digis
(braket
l_int|0
)braket
comma
id|p
op_plus
l_int|2
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|facilities-&gt;dest_ndigis
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_NATIONAL_FAIL_CALL
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;fail_call
comma
id|p
op_plus
l_int|2
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_NATIONAL_FAIL_ADD
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;fail_addr
comma
id|p
op_plus
l_int|3
comma
id|ROSE_ADDR_LEN
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_NATIONAL_DIGIS
)paren
(brace
id|fac_national_digis_received
op_assign
l_int|1
suffix:semicolon
id|facilities-&gt;source_ndigis
op_assign
l_int|0
suffix:semicolon
id|facilities-&gt;dest_ndigis
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|pt
op_assign
id|p
op_plus
l_int|2
comma
id|lg
op_assign
l_int|0
suffix:semicolon
id|lg
OL
id|l
suffix:semicolon
id|pt
op_add_assign
id|AX25_ADDR_LEN
comma
id|lg
op_add_assign
id|AX25_ADDR_LEN
)paren
(brace
r_if
c_cond
(paren
id|pt
(braket
l_int|6
)braket
op_amp
id|AX25_HBIT
)paren
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;dest_digis
(braket
id|facilities-&gt;dest_ndigis
op_increment
)braket
comma
id|pt
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;source_digis
(braket
id|facilities-&gt;source_ndigis
op_increment
)braket
comma
id|pt
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
)brace
)brace
id|p
op_add_assign
id|l
op_plus
l_int|2
suffix:semicolon
id|n
op_add_assign
id|l
op_plus
l_int|2
suffix:semicolon
id|len
op_sub_assign
id|l
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
id|p
op_ne
l_int|0x00
op_logical_and
id|len
OG
l_int|0
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|rose_parse_ccitt
r_static
r_int
id|rose_parse_ccitt
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_struct
id|rose_facilities_struct
op_star
id|facilities
comma
r_int
id|len
)paren
(brace
r_int
r_char
id|l
comma
id|n
op_assign
l_int|0
suffix:semicolon
r_char
id|callsign
(braket
l_int|11
)braket
suffix:semicolon
r_do
(brace
r_switch
c_cond
(paren
op_star
id|p
op_amp
l_int|0xC0
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|p
op_add_assign
l_int|2
suffix:semicolon
id|n
op_add_assign
l_int|2
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
id|p
op_add_assign
l_int|3
suffix:semicolon
id|n
op_add_assign
l_int|3
suffix:semicolon
id|len
op_sub_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80
suffix:colon
id|p
op_add_assign
l_int|4
suffix:semicolon
id|n
op_add_assign
l_int|4
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xC0
suffix:colon
id|l
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_CCITT_DEST_NSAP
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;source_addr
comma
id|p
op_plus
l_int|7
comma
id|ROSE_ADDR_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|callsign
comma
id|p
op_plus
l_int|12
comma
id|l
op_minus
l_int|10
)paren
suffix:semicolon
id|callsign
(braket
id|l
op_minus
l_int|10
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|facilities-&gt;source_call
op_assign
op_star
id|asc2ax
c_func
(paren
id|callsign
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
op_eq
id|FAC_CCITT_SRC_NSAP
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|facilities-&gt;dest_addr
comma
id|p
op_plus
l_int|7
comma
id|ROSE_ADDR_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|callsign
comma
id|p
op_plus
l_int|12
comma
id|l
op_minus
l_int|10
)paren
suffix:semicolon
id|callsign
(braket
id|l
op_minus
l_int|10
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|facilities-&gt;dest_call
op_assign
op_star
id|asc2ax
c_func
(paren
id|callsign
)paren
suffix:semicolon
)brace
id|p
op_add_assign
id|l
op_plus
l_int|2
suffix:semicolon
id|n
op_add_assign
id|l
op_plus
l_int|2
suffix:semicolon
id|len
op_sub_assign
id|l
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
id|p
op_ne
l_int|0x00
op_logical_and
id|len
OG
l_int|0
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|rose_parse_facilities
r_int
id|rose_parse_facilities
c_func
(paren
r_int
r_char
op_star
id|p
comma
r_struct
id|rose_facilities_struct
op_star
id|facilities
)paren
(brace
r_int
id|facilities_len
comma
id|len
suffix:semicolon
id|facilities_len
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|facilities_len
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|facilities_len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_int|0x00
)paren
(brace
id|facilities_len
op_decrement
suffix:semicolon
id|p
op_increment
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|p
)paren
(brace
r_case
id|FAC_NATIONAL
suffix:colon
multiline_comment|/* National */
id|len
op_assign
id|rose_parse_national
c_func
(paren
id|p
op_plus
l_int|1
comma
id|facilities
comma
id|facilities_len
op_minus
l_int|1
)paren
suffix:semicolon
id|facilities_len
op_sub_assign
id|len
op_plus
l_int|1
suffix:semicolon
id|p
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FAC_CCITT
suffix:colon
multiline_comment|/* CCITT */
id|len
op_assign
id|rose_parse_ccitt
c_func
(paren
id|p
op_plus
l_int|1
comma
id|facilities
comma
id|facilities_len
op_minus
l_int|1
)paren
suffix:semicolon
id|facilities_len
op_sub_assign
id|len
op_plus
l_int|1
suffix:semicolon
id|p
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ROSE: rose_parse_facilities - unknown facilities family %02X&bslash;n&quot;
comma
op_star
id|p
)paren
suffix:semicolon
id|facilities_len
op_decrement
suffix:semicolon
id|p
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_break
suffix:semicolon
multiline_comment|/* Error in facilities format */
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|rose_create_facilities
r_int
id|rose_create_facilities
c_func
(paren
r_int
r_char
op_star
id|buffer
comma
id|rose_cb
op_star
id|rose
)paren
(brace
r_int
r_char
op_star
id|p
op_assign
id|buffer
op_plus
l_int|1
suffix:semicolon
r_char
op_star
id|callsign
suffix:semicolon
r_int
id|len
comma
id|nb
suffix:semicolon
multiline_comment|/* National Facilities */
r_if
c_cond
(paren
id|rose-&gt;rand
op_ne
l_int|0
op_logical_or
id|rose-&gt;source_ndigis
op_eq
l_int|1
op_logical_or
id|rose-&gt;dest_ndigis
op_eq
l_int|1
)paren
(brace
op_star
id|p
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|FAC_NATIONAL
suffix:semicolon
r_if
c_cond
(paren
id|rose-&gt;rand
op_ne
l_int|0
)paren
(brace
op_star
id|p
op_increment
op_assign
id|FAC_NATIONAL_RAND
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|rose-&gt;rand
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|rose-&gt;rand
op_rshift
l_int|0
)paren
op_amp
l_int|0xFF
suffix:semicolon
)brace
multiline_comment|/* Sent before older facilities */
r_if
c_cond
(paren
(paren
id|rose-&gt;source_ndigis
OG
l_int|0
)paren
op_logical_or
(paren
id|rose-&gt;dest_ndigis
OG
l_int|0
)paren
)paren
(brace
r_int
id|maxdigi
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|FAC_NATIONAL_DIGIS
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|AX25_ADDR_LEN
op_star
(paren
id|rose-&gt;source_ndigis
op_plus
id|rose-&gt;dest_ndigis
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nb
op_assign
l_int|0
suffix:semicolon
id|nb
OL
id|rose-&gt;source_ndigis
suffix:semicolon
id|nb
op_increment
)paren
(brace
r_if
c_cond
(paren
op_increment
id|maxdigi
op_ge
id|ROSE_MAX_DIGIS
)paren
r_break
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|rose-&gt;source_digis
(braket
id|nb
)braket
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|p
(braket
l_int|6
)braket
op_or_assign
id|AX25_HBIT
suffix:semicolon
id|p
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
)brace
r_for
c_loop
(paren
id|nb
op_assign
l_int|0
suffix:semicolon
id|nb
OL
id|rose-&gt;dest_ndigis
suffix:semicolon
id|nb
op_increment
)paren
(brace
r_if
c_cond
(paren
op_increment
id|maxdigi
op_ge
id|ROSE_MAX_DIGIS
)paren
r_break
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|rose-&gt;dest_digis
(braket
id|nb
)braket
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|p
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_HBIT
suffix:semicolon
id|p
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
)brace
)brace
multiline_comment|/* For compatibility */
r_if
c_cond
(paren
id|rose-&gt;source_ndigis
OG
l_int|0
)paren
(brace
op_star
id|p
op_increment
op_assign
id|FAC_NATIONAL_SRC_DIGI
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|rose-&gt;source_digis
(braket
l_int|0
)braket
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|p
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
)brace
multiline_comment|/* For compatibility */
r_if
c_cond
(paren
id|rose-&gt;dest_ndigis
OG
l_int|0
)paren
(brace
op_star
id|p
op_increment
op_assign
id|FAC_NATIONAL_DEST_DIGI
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|rose-&gt;dest_digis
(braket
l_int|0
)braket
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|p
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
)brace
)brace
op_star
id|p
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|FAC_CCITT
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|FAC_CCITT_DEST_NSAP
suffix:semicolon
id|callsign
op_assign
id|ax2asc
c_func
(paren
op_amp
id|rose-&gt;dest_call
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|strlen
c_func
(paren
id|callsign
)paren
op_plus
l_int|10
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|strlen
c_func
(paren
id|callsign
)paren
op_plus
l_int|9
)paren
op_star
l_int|2
suffix:semicolon
multiline_comment|/* ??? */
op_star
id|p
op_increment
op_assign
l_int|0x47
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0x11
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|ROSE_ADDR_LEN
op_star
l_int|2
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|rose-&gt;dest_addr
comma
id|ROSE_ADDR_LEN
)paren
suffix:semicolon
id|p
op_add_assign
id|ROSE_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|callsign
comma
id|strlen
c_func
(paren
id|callsign
)paren
)paren
suffix:semicolon
id|p
op_add_assign
id|strlen
c_func
(paren
id|callsign
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|FAC_CCITT_SRC_NSAP
suffix:semicolon
id|callsign
op_assign
id|ax2asc
c_func
(paren
op_amp
id|rose-&gt;source_call
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|strlen
c_func
(paren
id|callsign
)paren
op_plus
l_int|10
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
id|strlen
c_func
(paren
id|callsign
)paren
op_plus
l_int|9
)paren
op_star
l_int|2
suffix:semicolon
multiline_comment|/* ??? */
op_star
id|p
op_increment
op_assign
l_int|0x47
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0x11
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|ROSE_ADDR_LEN
op_star
l_int|2
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|rose-&gt;source_addr
comma
id|ROSE_ADDR_LEN
)paren
suffix:semicolon
id|p
op_add_assign
id|ROSE_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|callsign
comma
id|strlen
c_func
(paren
id|callsign
)paren
)paren
suffix:semicolon
id|p
op_add_assign
id|strlen
c_func
(paren
id|callsign
)paren
suffix:semicolon
id|len
op_assign
id|p
op_minus
id|buffer
suffix:semicolon
id|buffer
(braket
l_int|0
)braket
op_assign
id|len
op_minus
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|rose_disconnect
r_void
id|rose_disconnect
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
id|cause
comma
r_int
id|diagnostic
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
id|rose_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_stop_idletimer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose-&gt;lci
op_assign
l_int|0
suffix:semicolon
id|rose-&gt;state
op_assign
id|ROSE_STATE_0
suffix:semicolon
r_if
c_cond
(paren
id|cause
op_ne
op_minus
l_int|1
)paren
id|rose-&gt;cause
op_assign
id|cause
suffix:semicolon
r_if
c_cond
(paren
id|diagnostic
op_ne
op_minus
l_int|1
)paren
id|rose-&gt;diagnostic
op_assign
id|diagnostic
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
id|reason
suffix:semicolon
id|sk-&gt;shutdown
op_or_assign
id|SEND_SHUTDOWN
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
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
)brace
eof
