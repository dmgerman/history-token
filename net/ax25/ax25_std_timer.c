multiline_comment|/*&n; *&t;AX.25 release 037&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;AX.25 028a&t;Jonathan(G4KLX)&t;New state machine based on SDL diagrams.&n; *&t;AX.25 028b&t;Jonathan(G4KLX)&t;Extracted AX25 control block from the&n; *&t;&t;&t;&t;&t;sock structure.&n; *&t;AX.25 029&t;Alan(GW4PTS)&t;Switched to KA9Q constant names.&n; *&t;AX.25 031&t;Joerg(DL1BKE)&t;Added DAMA support&n; *&t;AX.25 032&t;Joerg(DL1BKE)&t;Fixed DAMA timeout bug&n; *&t;AX.25 033&t;Jonathan(G4KLX)&t;Modularisation functions.&n; *&t;AX.25 035&t;Frederic(F1OAT)&t;Support for pseudo-digipeating.&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Split from ax25_timer.c.&n; *&t;AX.25 037&t;Jonathan(G4KLX)&t;New timer architecture.&n; */
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
r_switch
c_cond
(paren
id|ax25-&gt;state
)paren
(brace
r_case
id|AX25_STATE_0
suffix:colon
multiline_comment|/* Magic here: If we listen() and a new link dies before it&n;&t;&t;&t;   is accepted() it isn&squot;t &squot;dead&squot; so doesn&squot;t get removed. */
r_if
c_cond
(paren
id|ax25-&gt;sk
op_eq
l_int|NULL
op_logical_or
id|ax25-&gt;sk-&gt;destroy
op_logical_or
(paren
id|ax25-&gt;sk-&gt;state
op_eq
id|TCP_LISTEN
op_logical_and
id|ax25-&gt;sk-&gt;dead
)paren
)paren
(brace
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
multiline_comment|/*&n;&t;&t;&t; * Check the state of the receive buffer.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ax25-&gt;sk
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
id|ax25-&gt;sk-&gt;rmem_alloc
)paren
OL
(paren
id|ax25-&gt;sk-&gt;rcvbuf
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
id|ax25-&gt;sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|ax25-&gt;sk-&gt;err
op_assign
l_int|0
suffix:semicolon
id|ax25-&gt;sk-&gt;shutdown
op_or_assign
id|SEND_SHUTDOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ax25-&gt;sk-&gt;dead
)paren
id|ax25-&gt;sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|ax25-&gt;sk
)paren
suffix:semicolon
id|ax25-&gt;sk-&gt;dead
op_assign
l_int|1
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
