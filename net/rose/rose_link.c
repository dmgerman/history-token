multiline_comment|/*&n; *&t;ROSE release 003&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;ROSE 001&t;Jonathan(G4KLX)&t;Cloned from rose_timer.c&n; *&t;ROSE 003&t;Jonathan(G4KLX)&t;New timer architecture.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
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
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/rose.h&gt;
r_static
r_void
id|rose_ftimer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|rose_t0timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|rose_start_ftimer
r_void
id|rose_start_ftimer
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|neigh-&gt;ftimer
)paren
suffix:semicolon
id|neigh-&gt;ftimer.data
op_assign
(paren
r_int
r_int
)paren
id|neigh
suffix:semicolon
id|neigh-&gt;ftimer.function
op_assign
op_amp
id|rose_ftimer_expiry
suffix:semicolon
id|neigh-&gt;ftimer.expires
op_assign
id|jiffies
op_plus
id|sysctl_rose_link_fail_timeout
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|neigh-&gt;ftimer
)paren
suffix:semicolon
)brace
DECL|function|rose_start_t0timer
r_void
id|rose_start_t0timer
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|neigh-&gt;t0timer
)paren
suffix:semicolon
id|neigh-&gt;t0timer.data
op_assign
(paren
r_int
r_int
)paren
id|neigh
suffix:semicolon
id|neigh-&gt;t0timer.function
op_assign
op_amp
id|rose_t0timer_expiry
suffix:semicolon
id|neigh-&gt;t0timer.expires
op_assign
id|jiffies
op_plus
id|sysctl_rose_restart_request_timeout
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|neigh-&gt;t0timer
)paren
suffix:semicolon
)brace
DECL|function|rose_stop_ftimer
r_void
id|rose_stop_ftimer
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|neigh-&gt;ftimer
)paren
suffix:semicolon
)brace
DECL|function|rose_stop_t0timer
r_void
id|rose_stop_t0timer
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|neigh-&gt;t0timer
)paren
suffix:semicolon
)brace
DECL|function|rose_ftimer_running
r_int
id|rose_ftimer_running
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
r_return
id|timer_pending
c_func
(paren
op_amp
id|neigh-&gt;ftimer
)paren
suffix:semicolon
)brace
DECL|function|rose_t0timer_running
r_int
id|rose_t0timer_running
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
r_return
id|timer_pending
c_func
(paren
op_amp
id|neigh-&gt;t0timer
)paren
suffix:semicolon
)brace
DECL|function|rose_ftimer_expiry
r_static
r_void
id|rose_ftimer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
)brace
DECL|function|rose_t0timer_expiry
r_static
r_void
id|rose_t0timer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
r_struct
id|rose_neigh
op_star
id|neigh
op_assign
(paren
r_struct
id|rose_neigh
op_star
)paren
id|param
suffix:semicolon
id|rose_transmit_restart_request
c_func
(paren
id|neigh
)paren
suffix:semicolon
id|neigh-&gt;dce_mode
op_assign
l_int|0
suffix:semicolon
id|rose_start_t0timer
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Interface to ax25_send_frame. Changes my level 2 callsign depending&n; *&t;on whether we have a global ROSE callsign or use the default port&n; *&t;callsign.&n; */
DECL|function|rose_send_frame
r_static
r_int
id|rose_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
id|ax25_address
op_star
id|rose_call
suffix:semicolon
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|rose_callsign
comma
op_amp
id|null_ax25_address
)paren
op_eq
l_int|0
)paren
id|rose_call
op_assign
(paren
id|ax25_address
op_star
)paren
id|neigh-&gt;dev-&gt;dev_addr
suffix:semicolon
r_else
id|rose_call
op_assign
op_amp
id|rose_callsign
suffix:semicolon
id|neigh-&gt;ax25
op_assign
id|ax25_send_frame
c_func
(paren
id|skb
comma
l_int|260
comma
id|rose_call
comma
op_amp
id|neigh-&gt;callsign
comma
id|neigh-&gt;digipeat
comma
id|neigh-&gt;dev
)paren
suffix:semicolon
r_return
(paren
id|neigh-&gt;ax25
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Interface to ax25_link_up. Changes my level 2 callsign depending&n; *&t;on whether we have a global ROSE callsign or use the default port&n; *&t;callsign.&n; */
DECL|function|rose_link_up
r_static
r_int
id|rose_link_up
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
id|ax25_address
op_star
id|rose_call
suffix:semicolon
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|rose_callsign
comma
op_amp
id|null_ax25_address
)paren
op_eq
l_int|0
)paren
id|rose_call
op_assign
(paren
id|ax25_address
op_star
)paren
id|neigh-&gt;dev-&gt;dev_addr
suffix:semicolon
r_else
id|rose_call
op_assign
op_amp
id|rose_callsign
suffix:semicolon
id|neigh-&gt;ax25
op_assign
id|ax25_find_cb
c_func
(paren
id|rose_call
comma
op_amp
id|neigh-&gt;callsign
comma
id|neigh-&gt;digipeat
comma
id|neigh-&gt;dev
)paren
suffix:semicolon
r_return
(paren
id|neigh-&gt;ax25
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This handles all restart and diagnostic frames.&n; */
DECL|function|rose_link_rx_restart
r_void
id|rose_link_rx_restart
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|rose_neigh
op_star
id|neigh
comma
r_int
r_int
id|frametype
)paren
(brace
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_switch
c_cond
(paren
id|frametype
)paren
(brace
r_case
id|ROSE_RESTART_REQUEST
suffix:colon
id|rose_stop_t0timer
c_func
(paren
id|neigh
)paren
suffix:semicolon
id|neigh-&gt;restarted
op_assign
l_int|1
suffix:semicolon
id|neigh-&gt;dce_mode
op_assign
(paren
id|skb-&gt;data
(braket
l_int|3
)braket
op_eq
id|ROSE_DTE_ORIGINATED
)paren
suffix:semicolon
id|rose_transmit_restart_confirmation
c_func
(paren
id|neigh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_RESTART_CONFIRMATION
suffix:colon
id|rose_stop_t0timer
c_func
(paren
id|neigh
)paren
suffix:semicolon
id|neigh-&gt;restarted
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_DIAGNOSTIC
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ROSE: received diagnostic #%d - %02X %02X %02X&bslash;n&quot;
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
comma
id|skb-&gt;data
(braket
l_int|6
)braket
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
l_string|&quot;ROSE: received unknown %02X with LCI 000&bslash;n&quot;
comma
id|frametype
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|neigh-&gt;restarted
)paren
(brace
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
id|neigh-&gt;queue
)paren
)paren
op_ne
l_int|NULL
)paren
r_if
c_cond
(paren
op_logical_neg
id|rose_send_frame
c_func
(paren
id|skbn
comma
id|neigh
)paren
)paren
id|kfree_skb
c_func
(paren
id|skbn
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;This routine is called when a Restart Request is needed&n; */
DECL|function|rose_transmit_restart_request
r_void
id|rose_transmit_restart_request
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
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
r_int
id|len
suffix:semicolon
id|len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|ROSE_MIN_LEN
op_plus
l_int|3
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
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|ROSE_MIN_LEN
op_plus
l_int|3
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|AX25_P_ROSE
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|ROSE_RESTART_REQUEST
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
r_if
c_cond
(paren
op_logical_neg
id|rose_send_frame
c_func
(paren
id|skb
comma
id|neigh
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called when a Restart Confirmation is needed&n; */
DECL|function|rose_transmit_restart_confirmation
r_void
id|rose_transmit_restart_confirmation
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
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
r_int
id|len
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
id|skb_reserve
c_func
(paren
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|ROSE_MIN_LEN
op_plus
l_int|1
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|AX25_P_ROSE
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|ROSE_RESTART_CONFIRMATION
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rose_send_frame
c_func
(paren
id|skb
comma
id|neigh
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called when a Diagnostic is required.&n; */
DECL|function|rose_transmit_diagnostic
r_void
id|rose_transmit_diagnostic
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
comma
r_int
r_char
id|diag
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
r_int
id|len
suffix:semicolon
id|len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|ROSE_MIN_LEN
op_plus
l_int|2
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
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|ROSE_MIN_LEN
op_plus
l_int|2
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|AX25_P_ROSE
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|ROSE_GFI
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|ROSE_DIAGNOSTIC
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|diag
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rose_send_frame
c_func
(paren
id|skb
comma
id|neigh
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called when a Clear Request is needed outside of the context&n; * of a connected socket.&n; */
DECL|function|rose_transmit_clear_request
r_void
id|rose_transmit_clear_request
c_func
(paren
r_struct
id|rose_neigh
op_star
id|neigh
comma
r_int
r_int
id|lci
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
suffix:semicolon
id|len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|ROSE_MIN_LEN
op_plus
l_int|3
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
id|skb
comma
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
)paren
suffix:semicolon
id|dptr
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|ROSE_MIN_LEN
op_plus
l_int|3
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|AX25_P_ROSE
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
(paren
(paren
id|lci
op_rshift
l_int|8
)paren
op_amp
l_int|0x0F
)paren
op_or
id|ROSE_GFI
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
(paren
(paren
id|lci
op_rshift
l_int|0
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|ROSE_CLEAR_REQUEST
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|cause
suffix:semicolon
op_star
id|dptr
op_increment
op_assign
id|diagnostic
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rose_send_frame
c_func
(paren
id|skb
comma
id|neigh
)paren
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|rose_transmit_link
r_void
id|rose_transmit_link
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|rose_neigh
op_star
id|neigh
)paren
(brace
r_int
r_char
op_star
id|dptr
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|call_fw_firewall
c_func
(paren
id|PF_ROSE
comma
id|skb-&gt;dev
comma
id|skb-&gt;data
comma
l_int|NULL
comma
op_amp
id|skb
)paren
op_ne
id|FW_ACCEPT
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|neigh-&gt;loopback
)paren
(brace
id|rose_loopback_queue
c_func
(paren
id|skb
comma
id|neigh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rose_link_up
c_func
(paren
id|neigh
)paren
)paren
id|neigh-&gt;restarted
op_assign
l_int|0
suffix:semicolon
id|dptr
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
id|dptr
op_increment
op_assign
id|AX25_P_ROSE
suffix:semicolon
r_if
c_cond
(paren
id|neigh-&gt;restarted
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rose_send_frame
c_func
(paren
id|skb
comma
id|neigh
)paren
)paren
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
id|neigh-&gt;queue
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rose_t0timer_running
c_func
(paren
id|neigh
)paren
)paren
(brace
id|rose_transmit_restart_request
c_func
(paren
id|neigh
)paren
suffix:semicolon
id|neigh-&gt;dce_mode
op_assign
l_int|0
suffix:semicolon
id|rose_start_t0timer
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
)brace
)brace
eof
