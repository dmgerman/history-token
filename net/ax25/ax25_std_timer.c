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
DECL|function|ax25_std_heartbeat_expiry
r_void
id|ax25_std_heartbeat_expiry
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|ax25-&gt;sk
suffix:semicolon
r_if
c_cond
(paren
id|sk
)paren
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ax25-&gt;state
)paren
(brace
r_case
id|AX25_STATE_0
suffix:colon
multiline_comment|/* Magic here: If we listen() and a new link dies before it&n;&t;&t;   is accepted() it isn&squot;t &squot;dead&squot; so doesn&squot;t get removed. */
r_if
c_cond
(paren
op_logical_neg
id|sk
op_logical_or
id|sock_flag
c_func
(paren
id|sk
comma
id|SOCK_DESTROY
)paren
op_logical_or
(paren
id|sk-&gt;sk_state
op_eq
id|TCP_LISTEN
op_logical_and
id|sock_flag
c_func
(paren
id|sk
comma
id|SOCK_DEAD
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|sk
)paren
(brace
id|sock_hold
c_func
(paren
id|sk
)paren
suffix:semicolon
id|ax25_destroy_socket
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
id|ax25_destroy_socket
c_func
(paren
id|ax25
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AX25_STATE_3
suffix:colon
r_case
id|AX25_STATE_4
suffix:colon
multiline_comment|/*&n;&t;&t; * Check the state of the receive buffer.&n;&t;&t; */
r_if
c_cond
(paren
id|sk
op_ne
l_int|NULL
)paren
(brace
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
id|ax25-&gt;condition
op_amp
id|AX25_COND_OWN_RX_BUSY
)paren
)paren
(brace
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_OWN_RX_BUSY
suffix:semicolon
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_ACK_PENDING
suffix:semicolon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_RR
comma
id|AX25_POLLOFF
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|sk
)paren
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|ax25_start_heartbeat
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
DECL|function|ax25_std_t2timer_expiry
r_void
id|ax25_std_t2timer_expiry
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
id|ax25-&gt;condition
op_amp
id|AX25_COND_ACK_PENDING
)paren
(brace
id|ax25-&gt;condition
op_and_assign
op_complement
id|AX25_COND_ACK_PENDING
suffix:semicolon
id|ax25_std_timeout_response
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
)brace
DECL|function|ax25_std_t3timer_expiry
r_void
id|ax25_std_t3timer_expiry
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|ax25_std_transmit_enquiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_4
suffix:semicolon
)brace
DECL|function|ax25_std_idletimer_expiry
r_void
id|ax25_std_idletimer_expiry
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
id|ax25_clear_queues
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_DISC
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_2
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
l_int|0
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
DECL|function|ax25_std_t1timer_expiry
r_void
id|ax25_std_t1timer_expiry
c_func
(paren
id|ax25_cb
op_star
id|ax25
)paren
(brace
r_switch
c_cond
(paren
id|ax25-&gt;state
)paren
(brace
r_case
id|AX25_STATE_1
suffix:colon
r_if
c_cond
(paren
id|ax25-&gt;n2count
op_eq
id|ax25-&gt;n2
)paren
(brace
r_if
c_cond
(paren
id|ax25-&gt;modulus
op_eq
id|AX25_MODULUS
)paren
(brace
id|ax25_disconnect
c_func
(paren
id|ax25
comma
id|ETIMEDOUT
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|ax25-&gt;modulus
op_assign
id|AX25_MODULUS
suffix:semicolon
id|ax25-&gt;window
op_assign
id|ax25-&gt;ax25_dev-&gt;values
(braket
id|AX25_VALUES_WINDOW
)braket
suffix:semicolon
id|ax25-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_SABM
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ax25-&gt;n2count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ax25-&gt;modulus
op_eq
id|AX25_MODULUS
)paren
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_SABM
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
r_else
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_SABME
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AX25_STATE_2
suffix:colon
r_if
c_cond
(paren
id|ax25-&gt;n2count
op_eq
id|ax25-&gt;n2
)paren
(brace
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_DISC
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
id|ax25_disconnect
c_func
(paren
id|ax25
comma
id|ETIMEDOUT
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|ax25-&gt;n2count
op_increment
suffix:semicolon
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_DISC
comma
id|AX25_POLLON
comma
id|AX25_COMMAND
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AX25_STATE_3
suffix:colon
id|ax25-&gt;n2count
op_assign
l_int|1
suffix:semicolon
id|ax25_std_transmit_enquiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
id|ax25-&gt;state
op_assign
id|AX25_STATE_4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AX25_STATE_4
suffix:colon
r_if
c_cond
(paren
id|ax25-&gt;n2count
op_eq
id|ax25-&gt;n2
)paren
(brace
id|ax25_send_control
c_func
(paren
id|ax25
comma
id|AX25_DM
comma
id|AX25_POLLON
comma
id|AX25_RESPONSE
)paren
suffix:semicolon
id|ax25_disconnect
c_func
(paren
id|ax25
comma
id|ETIMEDOUT
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|ax25-&gt;n2count
op_increment
suffix:semicolon
id|ax25_std_transmit_enquiry
c_func
(paren
id|ax25
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
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
eof
