multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; */
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
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
r_static
r_void
id|nr_heartbeat_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|nr_t1timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|nr_t2timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|nr_t4timer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|nr_idletimer_expiry
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|nr_start_t1timer
r_void
id|nr_start_t1timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|nr-&gt;t1timer
)paren
suffix:semicolon
id|nr-&gt;t1timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|nr-&gt;t1timer.function
op_assign
op_amp
id|nr_t1timer_expiry
suffix:semicolon
id|nr-&gt;t1timer.expires
op_assign
id|jiffies
op_plus
id|nr-&gt;t1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|nr-&gt;t1timer
)paren
suffix:semicolon
)brace
DECL|function|nr_start_t2timer
r_void
id|nr_start_t2timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|nr-&gt;t2timer
)paren
suffix:semicolon
id|nr-&gt;t2timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|nr-&gt;t2timer.function
op_assign
op_amp
id|nr_t2timer_expiry
suffix:semicolon
id|nr-&gt;t2timer.expires
op_assign
id|jiffies
op_plus
id|nr-&gt;t2
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|nr-&gt;t2timer
)paren
suffix:semicolon
)brace
DECL|function|nr_start_t4timer
r_void
id|nr_start_t4timer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|nr-&gt;t4timer
)paren
suffix:semicolon
id|nr-&gt;t4timer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|nr-&gt;t4timer.function
op_assign
op_amp
id|nr_t4timer_expiry
suffix:semicolon
id|nr-&gt;t4timer.expires
op_assign
id|jiffies
op_plus
id|nr-&gt;t4
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|nr-&gt;t4timer
)paren
suffix:semicolon
)brace
DECL|function|nr_start_idletimer
r_void
id|nr_start_idletimer
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|nr-&gt;idletimer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;idle
OG
l_int|0
)paren
(brace
id|nr-&gt;idletimer.data
op_assign
(paren
r_int
r_int
)paren
id|sk
suffix:semicolon
id|nr-&gt;idletimer.function
op_assign
op_amp
id|nr_idletimer_expiry
suffix:semicolon
id|nr-&gt;idletimer.expires
op_assign
id|jiffies
op_plus
id|nr-&gt;idle
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|nr-&gt;idletimer
)paren
suffix:semicolon
)brace
)brace
DECL|function|nr_start_heartbeat
r_void
id|nr_start_heartbeat
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
id|nr_heartbeat_expiry
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
DECL|function|nr_stop_t1timer
r_void
id|nr_stop_t1timer
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
id|nr_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|t1timer
)paren
suffix:semicolon
)brace
DECL|function|nr_stop_t2timer
r_void
id|nr_stop_t2timer
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
id|nr_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|t2timer
)paren
suffix:semicolon
)brace
DECL|function|nr_stop_t4timer
r_void
id|nr_stop_t4timer
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
id|nr_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|t4timer
)paren
suffix:semicolon
)brace
DECL|function|nr_stop_idletimer
r_void
id|nr_stop_idletimer
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
id|nr_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|idletimer
)paren
suffix:semicolon
)brace
DECL|function|nr_stop_heartbeat
r_void
id|nr_stop_heartbeat
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
DECL|function|nr_t1timer_running
r_int
id|nr_t1timer_running
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
id|timer_pending
c_func
(paren
op_amp
id|nr_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|t1timer
)paren
suffix:semicolon
)brace
DECL|function|nr_heartbeat_expiry
r_static
r_void
id|nr_heartbeat_expiry
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
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nr-&gt;state
)paren
(brace
r_case
id|NR_STATE_0
suffix:colon
multiline_comment|/* Magic here: If we listen() and a new link dies before it&n;&t;&t;&t;   is accepted() it isn&squot;t &squot;dead&squot; so doesn&squot;t get removed. */
r_if
c_cond
(paren
id|sk-&gt;destroy
op_logical_or
(paren
id|sk-&gt;state
op_eq
id|TCP_LISTEN
op_logical_and
id|sk-&gt;dead
)paren
)paren
(brace
id|nr_destroy_socket
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
id|NR_STATE_3
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Check for the state of the receive buffer.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;rmem_alloc
)paren
OL
(paren
id|sk-&gt;rcvbuf
op_div
l_int|2
)paren
op_logical_and
(paren
id|nr-&gt;condition
op_amp
id|NR_COND_OWN_RX_BUSY
)paren
)paren
(brace
id|nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_OWN_RX_BUSY
suffix:semicolon
id|nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_ACK_PENDING
suffix:semicolon
id|nr-&gt;vl
op_assign
id|nr-&gt;vr
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_INFOACK
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|nr_start_heartbeat
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
DECL|function|nr_t2timer_expiry
r_static
r_void
id|nr_t2timer_expiry
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
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr-&gt;condition
op_amp
id|NR_COND_ACK_PENDING
)paren
(brace
id|nr-&gt;condition
op_and_assign
op_complement
id|NR_COND_ACK_PENDING
suffix:semicolon
id|nr_enquiry_response
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
)brace
DECL|function|nr_t4timer_expiry
r_static
r_void
id|nr_t4timer_expiry
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
id|nr_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|condition
op_and_assign
op_complement
id|NR_COND_PEER_RX_BUSY
suffix:semicolon
)brace
DECL|function|nr_idletimer_expiry
r_static
r_void
id|nr_idletimer_expiry
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
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
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
id|nr-&gt;n2count
op_assign
l_int|0
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_DISCREQ
)paren
suffix:semicolon
id|nr-&gt;state
op_assign
id|NR_STATE_2
suffix:semicolon
id|nr_start_t1timer
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
id|sk-&gt;state
op_assign
id|TCP_CLOSE
suffix:semicolon
id|sk-&gt;err
op_assign
l_int|0
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
DECL|function|nr_t1timer_expiry
r_static
r_void
id|nr_t1timer_expiry
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
id|nr_cb
op_star
id|nr
op_assign
id|nr_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nr-&gt;state
)paren
(brace
r_case
id|NR_STATE_1
suffix:colon
r_if
c_cond
(paren
id|nr-&gt;n2count
op_eq
id|nr-&gt;n2
)paren
(brace
id|nr_disconnect
c_func
(paren
id|sk
comma
id|ETIMEDOUT
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|nr-&gt;n2count
op_increment
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_CONNREQ
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NR_STATE_2
suffix:colon
r_if
c_cond
(paren
id|nr-&gt;n2count
op_eq
id|nr-&gt;n2
)paren
(brace
id|nr_disconnect
c_func
(paren
id|sk
comma
id|ETIMEDOUT
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|nr-&gt;n2count
op_increment
suffix:semicolon
id|nr_write_internal
c_func
(paren
id|sk
comma
id|NR_DISCREQ
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NR_STATE_3
suffix:colon
r_if
c_cond
(paren
id|nr-&gt;n2count
op_eq
id|nr-&gt;n2
)paren
(brace
id|nr_disconnect
c_func
(paren
id|sk
comma
id|ETIMEDOUT
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|nr-&gt;n2count
op_increment
suffix:semicolon
id|nr_requeue_frames
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|nr_start_t1timer
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
eof
