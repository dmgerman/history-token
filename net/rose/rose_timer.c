multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; * Copyright (C) 2002 Ralf Baechle DO1GRB (ralf@gnu.org)&n; */
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
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/rose.h&gt;
r_static
r_void
id|rose_heartbeat_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|rose_timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|rose_idletimer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|rose_start_heartbeat
r_void
id|rose_start_heartbeat
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
id|sk-&gt;sk_timer
)paren
suffix:semicolon
id|sk-&gt;sk_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|sk-&gt;sk_timer.function
op_assign
op_amp
id|rose_heartbeat_expiry
suffix:semicolon
id|sk-&gt;sk_timer.expires
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
id|sk-&gt;sk_timer
)paren
suffix:semicolon
)brace
DECL|function|rose_start_t1timer
r_void
id|rose_start_t1timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|rose_sock
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
id|rose-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|rose-&gt;timer.function
op_assign
op_amp
id|rose_timer_expiry
suffix:semicolon
id|rose-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|rose-&gt;t1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|rose_start_t2timer
r_void
id|rose_start_t2timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|rose_sock
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
id|rose-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|rose-&gt;timer.function
op_assign
op_amp
id|rose_timer_expiry
suffix:semicolon
id|rose-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|rose-&gt;t2
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|rose_start_t3timer
r_void
id|rose_start_t3timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|rose_sock
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
id|rose-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|rose-&gt;timer.function
op_assign
op_amp
id|rose_timer_expiry
suffix:semicolon
id|rose-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|rose-&gt;t3
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|rose_start_hbtimer
r_void
id|rose_start_hbtimer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|rose_sock
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
id|rose-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|rose-&gt;timer.function
op_assign
op_amp
id|rose_timer_expiry
suffix:semicolon
id|rose-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|rose-&gt;hb
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rose-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|rose_start_idletimer
r_void
id|rose_start_idletimer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|rose_sock
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|rose-&gt;idletimer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rose-&gt;idle
OG
l_int|0
)paren
(brace
id|rose-&gt;idletimer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|rose-&gt;idletimer.function
op_assign
op_amp
id|rose_idletimer_expiry
suffix:semicolon
id|rose-&gt;idletimer.expires
op_assign
id|jiffies
op_plus
id|rose-&gt;idle
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rose-&gt;idletimer
)paren
suffix:semicolon
)brace
)brace
DECL|function|rose_stop_heartbeat
r_void
id|rose_stop_heartbeat
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
id|sk-&gt;sk_timer
)paren
suffix:semicolon
)brace
DECL|function|rose_stop_timer
r_void
id|rose_stop_timer
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
id|rose_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|timer
)paren
suffix:semicolon
)brace
DECL|function|rose_stop_idletimer
r_void
id|rose_stop_idletimer
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
id|rose_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|idletimer
)paren
suffix:semicolon
)brace
DECL|function|rose_heartbeat_expiry
r_static
r_void
id|rose_heartbeat_expiry
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
r_struct
id|rose_sock
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|rose-&gt;state
)paren
(brace
r_case
id|ROSE_STATE_0
suffix:colon
multiline_comment|/* Magic here: If we listen() and a new link dies before it&n;&t;&t;   is accepted() it isn&squot;t &squot;dead&squot; so doesn&squot;t get removed. */
r_if
c_cond
(paren
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
id|rose_destroy_socket
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ROSE_STATE_3
suffix:colon
multiline_comment|/*&n;&t;&t; * Check for the state of the receive buffer.&n;&t;&t; */
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
id|rose-&gt;condition
op_amp
id|ROSE_COND_OWN_RX_BUSY
)paren
)paren
(brace
id|rose-&gt;condition
op_and_assign
op_complement
id|ROSE_COND_OWN_RX_BUSY
suffix:semicolon
id|rose-&gt;condition
op_and_assign
op_complement
id|ROSE_COND_ACK_PENDING
suffix:semicolon
id|rose-&gt;vl
op_assign
id|rose-&gt;vr
suffix:semicolon
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_RR
)paren
suffix:semicolon
id|rose_stop_timer
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/* HB */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|rose_start_heartbeat
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
DECL|function|rose_timer_expiry
r_static
r_void
id|rose_timer_expiry
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
r_struct
id|rose_sock
op_star
id|rose
op_assign
id|rose_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|rose-&gt;state
)paren
(brace
r_case
id|ROSE_STATE_1
suffix:colon
multiline_comment|/* T1 */
r_case
id|ROSE_STATE_4
suffix:colon
multiline_comment|/* T2 */
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_CLEAR_REQUEST
)paren
suffix:semicolon
id|rose-&gt;state
op_assign
id|ROSE_STATE_2
suffix:semicolon
id|rose_start_t3timer
c_func
(paren
id|sk
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_STATE_2
suffix:colon
multiline_comment|/* T3 */
id|rose-&gt;neighbour-&gt;use
op_decrement
suffix:semicolon
id|rose_disconnect
c_func
(paren
id|sk
comma
id|ETIMEDOUT
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROSE_STATE_3
suffix:colon
multiline_comment|/* HB */
r_if
c_cond
(paren
id|rose-&gt;condition
op_amp
id|ROSE_COND_ACK_PENDING
)paren
(brace
id|rose-&gt;condition
op_and_assign
op_complement
id|ROSE_COND_ACK_PENDING
suffix:semicolon
id|rose_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|rose_idletimer_expiry
r_static
r_void
id|rose_idletimer_expiry
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
id|rose_clear_queues
c_func
(paren
id|sk
)paren
suffix:semicolon
id|rose_write_internal
c_func
(paren
id|sk
comma
id|ROSE_CLEAR_REQUEST
)paren
suffix:semicolon
id|rose_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|state
op_assign
id|ROSE_STATE_2
suffix:semicolon
id|rose_start_t3timer
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;sk_state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;sk_err
op_assign
l_int|0
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
id|bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
eof
