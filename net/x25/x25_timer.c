multiline_comment|/*&n; *&t;X.25 Packet Layer release 002&n; *&n; *&t;This is ALPHA test software. This code may break your machine,&n; *&t;randomly fail to work with new releases, misbehave and/or generally&n; *&t;screw up. It might even work. &n; *&n; *&t;This code REQUIRES 2.1.15 or higher&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;History&n; *&t;X.25 001&t;Jonathan Naylor&t;Started coding.&n; *&t;X.25 002&t;Jonathan Naylor&t;New timer architecture.&n; *&t;&t;&t;&t;&t;Centralised disconnection processing.&n; */
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
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/x25.h&gt;
r_static
r_void
id|x25_heartbeat_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|x25_timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|x25_start_heartbeat
r_void
id|x25_start_heartbeat
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
id|sk-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|sk-&gt;timer.function
op_assign
op_amp
id|x25_heartbeat_expiry
suffix:semicolon
id|sk-&gt;timer.expires
op_assign
id|jiffies
op_plus
l_int|5
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|x25_stop_heartbeat
r_void
id|x25_stop_heartbeat
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|sk-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|x25_start_t2timer
r_void
id|x25_start_t2timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
id|x25-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|x25-&gt;timer.function
op_assign
op_amp
id|x25_timer_expiry
suffix:semicolon
id|x25-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|x25-&gt;t2
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|x25_start_t21timer
r_void
id|x25_start_t21timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
id|x25-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|x25-&gt;timer.function
op_assign
op_amp
id|x25_timer_expiry
suffix:semicolon
id|x25-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|x25-&gt;t21
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|x25_start_t22timer
r_void
id|x25_start_t22timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
id|x25-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|x25-&gt;timer.function
op_assign
op_amp
id|x25_timer_expiry
suffix:semicolon
id|x25-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|x25-&gt;t22
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|x25_start_t23timer
r_void
id|x25_start_t23timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
id|x25-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|x25-&gt;timer.function
op_assign
op_amp
id|x25_timer_expiry
suffix:semicolon
id|x25-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|x25-&gt;t23
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|x25_stop_timer
r_void
id|x25_stop_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|x25_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|timer
)paren
suffix:semicolon
)brace
DECL|function|x25_display_timer
r_int
r_int
id|x25_display_timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timer_pending
c_func
(paren
op_amp
id|x25-&gt;timer
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|x25-&gt;timer.expires
op_minus
id|jiffies
suffix:semicolon
)brace
DECL|function|x25_heartbeat_expiry
r_static
r_void
id|x25_heartbeat_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|param
suffix:semicolon
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_owned_by_user
c_func
(paren
id|sk
)paren
)paren
multiline_comment|/* can currently only occur in state 3 */
r_goto
id|restart_heartbeat
suffix:semicolon
r_switch
c_cond
(paren
id|x25_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|state
)paren
(brace
r_case
id|X25_STATE_0
suffix:colon
multiline_comment|/* Magic here: If we listen() and a new link dies before it&n;&t;&t;&t;   is accepted() it isn&squot;t &squot;dead&squot; so doesn&squot;t get removed. */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|SOCK_DESTROY
comma
op_amp
id|sk-&gt;flags
)paren
op_logical_or
(paren
id|sk-&gt;state
op_eq
id|TCP_LISTEN
op_logical_and
id|test_bit
c_func
(paren
id|SOCK_DEAD
comma
op_amp
id|sk-&gt;flags
)paren
)paren
)paren
(brace
id|x25_destroy_socket
c_func
(paren
id|sk
)paren
suffix:semicolon
r_goto
id|unlock
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X25_STATE_3
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Check for the state of the receive buffer.&n;&t;&t;&t; */
id|x25_check_rbuf
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|restart_heartbeat
suffix:colon
id|x25_start_heartbeat
c_func
(paren
id|sk
)paren
suffix:semicolon
id|unlock
suffix:colon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Timer has expired, it may have been T2, T21, T22, or T23. We can tell&n; *&t;by the state machine state.&n; */
DECL|function|x25_do_timer_expiry
r_static
r_inline
r_void
id|x25_do_timer_expiry
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|x25_opt
op_star
id|x25
op_assign
id|x25_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|x25-&gt;state
)paren
(brace
r_case
id|X25_STATE_3
suffix:colon
multiline_comment|/* T2 */
r_if
c_cond
(paren
id|x25-&gt;condition
op_amp
id|X25_COND_ACK_PENDING
)paren
(brace
id|x25-&gt;condition
op_and_assign
op_complement
id|X25_COND_ACK_PENDING
suffix:semicolon
id|x25_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X25_STATE_1
suffix:colon
multiline_comment|/* T21 */
r_case
id|X25_STATE_4
suffix:colon
multiline_comment|/* T22 */
id|x25_write_internal
c_func
(paren
id|sk
comma
id|X25_CLEAR_REQUEST
)paren
suffix:semicolon
id|x25-&gt;state
op_assign
id|X25_STATE_2
suffix:semicolon
id|x25_start_t23timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X25_STATE_2
suffix:colon
multiline_comment|/* T23 */
id|x25_disconnect
c_func
(paren
id|sk
comma
id|ETIMEDOUT
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|x25_timer_expiry
r_static
r_void
id|x25_timer_expiry
c_func
(paren
r_int
r_int
id|param
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
(paren
r_struct
id|sock
op_star
)paren
id|param
suffix:semicolon
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_owned_by_user
c_func
(paren
id|sk
)paren
)paren
(brace
multiline_comment|/* can currently only occur in state 3 */
r_if
c_cond
(paren
id|x25_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|state
op_eq
id|X25_STATE_3
)paren
id|x25_start_t2timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_else
id|x25_do_timer_expiry
c_func
(paren
id|sk
)paren
suffix:semicolon
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
eof
