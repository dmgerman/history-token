multiline_comment|/* krxsecd.c: Rx security daemon&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * This daemon deals with:&n; * - consulting the application as to whether inbound peers and calls should be authorised&n; * - generating security challenges for inbound connections&n; * - responding to security challenges on outbound connections&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;rxrpc/krxsecd.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &lt;rxrpc/message.h&gt;
macro_line|#include &lt;rxrpc/peer.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &quot;internal.h&quot;
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|rxrpc_krxsecd_sleepq
)paren
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|rxrpc_krxsecd_dead
)paren
suffix:semicolon
DECL|variable|rxrpc_krxsecd_die
r_static
r_volatile
r_int
id|rxrpc_krxsecd_die
suffix:semicolon
DECL|variable|rxrpc_krxsecd_qcount
r_static
id|atomic_t
id|rxrpc_krxsecd_qcount
suffix:semicolon
multiline_comment|/* queue of unprocessed inbound messages with seqno #1 and&n; * RXRPC_CLIENT_INITIATED flag set */
r_static
id|LIST_HEAD
c_func
(paren
id|rxrpc_krxsecd_initmsgq
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|rxrpc_krxsecd_initmsgq_lock
)paren
suffix:semicolon
r_static
r_void
id|rxrpc_krxsecd_process_incoming_call
c_func
(paren
r_struct
id|rxrpc_message
op_star
id|msg
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx security daemon&n; */
DECL|function|rxrpc_krxsecd
r_static
r_int
id|rxrpc_krxsecd
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|krxsecd
comma
id|current
)paren
suffix:semicolon
r_int
id|die
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Started krxsecd %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;krxsecd&quot;
)paren
suffix:semicolon
multiline_comment|/* loop around waiting for work to do */
r_do
(brace
multiline_comment|/* wait for work or to be told to exit */
id|_debug
c_func
(paren
l_string|&quot;### Begin Wait&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_krxsecd_qcount
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|rxrpc_krxsecd_sleepq
comma
op_amp
id|krxsecd
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_krxsecd_qcount
)paren
op_logical_or
id|rxrpc_krxsecd_die
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|rxrpc_krxsecd_sleepq
comma
op_amp
id|krxsecd
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
)brace
id|die
op_assign
id|rxrpc_krxsecd_die
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;### End Wait&quot;
)paren
suffix:semicolon
multiline_comment|/* see if there&squot;re incoming calls in need of authenticating */
id|_debug
c_func
(paren
l_string|&quot;### Begin Inbound Calls&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq
)paren
)paren
(brace
r_struct
id|rxrpc_message
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq
)paren
)paren
(brace
id|msg
op_assign
id|list_entry
c_func
(paren
id|rxrpc_krxsecd_initmsgq.next
comma
r_struct
id|rxrpc_message
comma
id|link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|msg-&gt;link
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_krxsecd_qcount
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
(brace
id|rxrpc_krxsecd_process_incoming_call
c_func
(paren
id|msg
)paren
suffix:semicolon
id|rxrpc_put_message
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
)brace
id|_debug
c_func
(paren
l_string|&quot;### End Inbound Calls&quot;
)paren
suffix:semicolon
id|try_to_freeze
c_func
(paren
id|PF_FREEZE
)paren
suffix:semicolon
multiline_comment|/* discard pending signals */
id|rxrpc_discard_my_signals
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|die
)paren
suffix:semicolon
multiline_comment|/* and that&squot;s all */
id|complete_and_exit
c_func
(paren
op_amp
id|rxrpc_krxsecd_dead
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxsecd() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * start up a krxsecd daemon&n; */
DECL|function|rxrpc_krxsecd_init
r_int
id|__init
id|rxrpc_krxsecd_init
c_func
(paren
r_void
)paren
(brace
r_return
id|kernel_thread
c_func
(paren
id|rxrpc_krxsecd
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxsecd_init() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * kill the krxsecd daemon and wait for it to complete&n; */
DECL|function|rxrpc_krxsecd_kill
r_void
id|rxrpc_krxsecd_kill
c_func
(paren
r_void
)paren
(brace
id|rxrpc_krxsecd_die
op_assign
l_int|1
suffix:semicolon
id|wake_up_all
c_func
(paren
op_amp
id|rxrpc_krxsecd_sleepq
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|rxrpc_krxsecd_dead
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxsecd_kill() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clear all pending incoming calls for the specified transport&n; */
DECL|function|rxrpc_krxsecd_clear_transport
r_void
id|rxrpc_krxsecd_clear_transport
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_struct
id|rxrpc_message
op_star
id|msg
suffix:semicolon
r_struct
id|list_head
op_star
id|_p
comma
op_star
id|_n
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p&quot;
comma
id|trans
)paren
suffix:semicolon
multiline_comment|/* move all the messages for this transport onto a temp list */
id|spin_lock
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|_p
comma
id|_n
comma
op_amp
id|rxrpc_krxsecd_initmsgq
)paren
(brace
id|msg
op_assign
id|list_entry
c_func
(paren
id|_p
comma
r_struct
id|rxrpc_message
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;trans
op_eq
id|trans
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|msg-&gt;link
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|msg-&gt;link
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_krxsecd_qcount
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq_lock
)paren
suffix:semicolon
multiline_comment|/* zap all messages on the temp list */
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|tmp
)paren
)paren
(brace
id|msg
op_assign
id|list_entry
c_func
(paren
id|tmp.next
comma
r_struct
id|rxrpc_message
comma
id|link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|msg-&gt;link
)paren
suffix:semicolon
id|rxrpc_put_message
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxsecd_clear_transport() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * queue a message on the incoming calls list&n; */
DECL|function|rxrpc_krxsecd_queue_incoming_call
r_void
id|rxrpc_krxsecd_queue_incoming_call
c_func
(paren
r_struct
id|rxrpc_message
op_star
id|msg
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;%p&quot;
comma
id|msg
)paren
suffix:semicolon
multiline_comment|/* queue for processing by krxsecd */
id|spin_lock
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rxrpc_krxsecd_die
)paren
(brace
id|rxrpc_get_message
c_func
(paren
id|msg
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|msg-&gt;link
comma
op_amp
id|rxrpc_krxsecd_initmsgq
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|rxrpc_krxsecd_qcount
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|rxrpc_krxsecd_initmsgq_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|rxrpc_krxsecd_sleepq
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxsecd_queue_incoming_call() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * process the initial message of an incoming call&n; */
DECL|function|rxrpc_krxsecd_process_incoming_call
r_void
id|rxrpc_krxsecd_process_incoming_call
c_func
(paren
r_struct
id|rxrpc_message
op_star
id|msg
)paren
(brace
r_struct
id|rxrpc_transport
op_star
id|trans
op_assign
id|msg-&gt;trans
suffix:semicolon
r_struct
id|rxrpc_service
op_star
id|srv
suffix:semicolon
r_struct
id|rxrpc_call
op_star
id|call
suffix:semicolon
r_struct
id|list_head
op_star
id|_p
suffix:semicolon
r_int
r_int
id|sid
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{tr=%p}&quot;
comma
id|msg
comma
id|trans
)paren
suffix:semicolon
id|ret
op_assign
id|rxrpc_incoming_call
c_func
(paren
id|msg-&gt;conn
comma
id|msg
comma
op_amp
id|call
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* find the matching service on the transport */
id|sid
op_assign
id|ntohs
c_func
(paren
id|msg-&gt;hdr.serviceId
)paren
suffix:semicolon
id|srv
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|trans-&gt;lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|trans-&gt;services
)paren
(brace
id|srv
op_assign
id|list_entry
c_func
(paren
id|_p
comma
r_struct
id|rxrpc_service
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srv-&gt;service_id
op_eq
id|sid
op_logical_and
id|try_module_get
c_func
(paren
id|srv-&gt;owner
)paren
)paren
(brace
multiline_comment|/* found a match (made sure it won&squot;t vanish) */
id|_debug
c_func
(paren
l_string|&quot;found service &squot;%s&squot;&quot;
comma
id|srv-&gt;name
)paren
suffix:semicolon
id|call-&gt;owner
op_assign
id|srv-&gt;owner
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|trans-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* report the new connection&n;&t; * - the func must inc the call&squot;s usage count to keep it&n;&t; */
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|_p
op_ne
op_amp
id|trans-&gt;services
)paren
(brace
multiline_comment|/* attempt to accept the call */
id|call-&gt;conn-&gt;service
op_assign
id|srv
suffix:semicolon
id|call-&gt;app_attn_func
op_assign
id|srv-&gt;attn_func
suffix:semicolon
id|call-&gt;app_error_func
op_assign
id|srv-&gt;error_func
suffix:semicolon
id|call-&gt;app_aemap_func
op_assign
id|srv-&gt;aemap_func
suffix:semicolon
id|ret
op_assign
id|srv
op_member_access_from_pointer
id|new_call
c_func
(paren
id|call
)paren
suffix:semicolon
multiline_comment|/* send an abort if an error occurred */
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* formally receive and ACK the new packet */
id|ret
op_assign
id|rxrpc_conn_receive_call_packet
c_func
(paren
id|call-&gt;conn
comma
id|call
comma
id|msg
)paren
suffix:semicolon
)brace
)brace
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|rxrpc_trans_immediate_abort
c_func
(paren
id|trans
comma
id|msg
comma
id|ret
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; (%d)&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxsecd_process_incoming_call() */
eof
