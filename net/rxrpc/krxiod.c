multiline_comment|/* krxiod.c: Rx I/O daemon&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;rxrpc/krxiod.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/peer.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &quot;internal.h&quot;
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|rxrpc_krxiod_sleepq
)paren
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|rxrpc_krxiod_dead
)paren
suffix:semicolon
DECL|variable|rxrpc_krxiod_qcount
r_static
id|atomic_t
id|rxrpc_krxiod_qcount
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|rxrpc_krxiod_transportq
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|rxrpc_krxiod_transportq_lock
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|rxrpc_krxiod_callq
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|rxrpc_krxiod_callq_lock
)paren
suffix:semicolon
DECL|variable|rxrpc_krxiod_die
r_static
r_volatile
r_int
id|rxrpc_krxiod_die
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx I/O daemon&n; */
DECL|function|rxrpc_krxiod
r_static
r_int
id|rxrpc_krxiod
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
id|krxiod
comma
id|current
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Started krxiod %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;krxiod&quot;
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
id|rxrpc_krxiod_qcount
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
id|rxrpc_krxiod_sleepq
comma
op_amp
id|krxiod
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
id|rxrpc_krxiod_qcount
)paren
op_logical_or
id|rxrpc_krxiod_die
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
id|rxrpc_krxiod_sleepq
comma
op_amp
id|krxiod
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
)brace
id|_debug
c_func
(paren
l_string|&quot;### End Wait&quot;
)paren
suffix:semicolon
multiline_comment|/* do work if been given some to do */
id|_debug
c_func
(paren
l_string|&quot;### Begin Work&quot;
)paren
suffix:semicolon
multiline_comment|/* see if there&squot;s a transport in need of attention */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|rxrpc_krxiod_transportq
)paren
)paren
(brace
r_struct
id|rxrpc_transport
op_star
id|trans
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rxrpc_krxiod_transportq_lock
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
id|rxrpc_krxiod_transportq
)paren
)paren
(brace
id|trans
op_assign
id|list_entry
c_func
(paren
id|rxrpc_krxiod_transportq.next
comma
r_struct
id|rxrpc_transport
comma
id|krxiodq_link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|trans-&gt;krxiodq_link
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_krxiod_qcount
)paren
suffix:semicolon
multiline_comment|/* make sure it hasn&squot;t gone away and doesn&squot;t go&n;&t;&t;&t;&t; * away */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|trans-&gt;usage
)paren
OG
l_int|0
)paren
id|rxrpc_get_transport
c_func
(paren
id|trans
)paren
suffix:semicolon
r_else
id|trans
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|rxrpc_krxiod_transportq_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trans
)paren
(brace
id|rxrpc_trans_receive_packet
c_func
(paren
id|trans
)paren
suffix:semicolon
id|rxrpc_put_transport
c_func
(paren
id|trans
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* see if there&squot;s a call in need of attention */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|rxrpc_krxiod_callq
)paren
)paren
(brace
r_struct
id|rxrpc_call
op_star
id|call
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rxrpc_krxiod_callq_lock
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
id|rxrpc_krxiod_callq
)paren
)paren
(brace
id|call
op_assign
id|list_entry
c_func
(paren
id|rxrpc_krxiod_callq.next
comma
r_struct
id|rxrpc_call
comma
id|rcv_krxiodq_lk
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;rcv_krxiodq_lk
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_krxiod_qcount
)paren
suffix:semicolon
multiline_comment|/* make sure it hasn&squot;t gone away and doesn&squot;t go&n;&t;&t;&t;&t; * away */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|call-&gt;usage
)paren
OG
l_int|0
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;@@@ KRXIOD&quot;
l_string|&quot; Begin Attend Call %p&quot;
comma
id|call
)paren
suffix:semicolon
id|rxrpc_get_call
c_func
(paren
id|call
)paren
suffix:semicolon
)brace
r_else
(brace
id|call
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|rxrpc_krxiod_callq_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call
)paren
(brace
id|rxrpc_call_do_stuff
c_func
(paren
id|call
)paren
suffix:semicolon
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;@@@ KRXIOD End Attend Call %p&quot;
comma
id|call
)paren
suffix:semicolon
)brace
)brace
id|_debug
c_func
(paren
l_string|&quot;### End Work&quot;
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
id|rxrpc_krxiod_die
)paren
suffix:semicolon
multiline_comment|/* and that&squot;s all */
id|complete_and_exit
c_func
(paren
op_amp
id|rxrpc_krxiod_dead
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxiod() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * start up a krxiod daemon&n; */
DECL|function|rxrpc_krxiod_init
r_int
id|__init
id|rxrpc_krxiod_init
c_func
(paren
r_void
)paren
(brace
r_return
id|kernel_thread
c_func
(paren
id|rxrpc_krxiod
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxiod_init() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * kill the krxiod daemon and wait for it to complete&n; */
DECL|function|rxrpc_krxiod_kill
r_void
id|rxrpc_krxiod_kill
c_func
(paren
r_void
)paren
(brace
id|rxrpc_krxiod_die
op_assign
l_int|1
suffix:semicolon
id|wake_up_all
c_func
(paren
op_amp
id|rxrpc_krxiod_sleepq
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|rxrpc_krxiod_dead
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxiod_kill() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * queue a transport for attention by krxiod&n; */
DECL|function|rxrpc_krxiod_queue_transport
r_void
id|rxrpc_krxiod_queue_transport
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|trans-&gt;krxiodq_link
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rxrpc_krxiod_transportq_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|trans-&gt;krxiodq_link
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|trans-&gt;usage
)paren
OG
l_int|0
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|trans-&gt;krxiodq_link
comma
op_amp
id|rxrpc_krxiod_transportq
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|rxrpc_krxiod_qcount
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rxrpc_krxiod_transportq_lock
comma
id|flags
)paren
suffix:semicolon
id|wake_up_all
c_func
(paren
op_amp
id|rxrpc_krxiod_sleepq
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
multiline_comment|/* end rxrpc_krxiod_queue_transport() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * dequeue a transport from krxiod&squot;s attention queue&n; */
DECL|function|rxrpc_krxiod_dequeue_transport
r_void
id|rxrpc_krxiod_dequeue_transport
c_func
(paren
r_struct
id|rxrpc_transport
op_star
id|trans
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rxrpc_krxiod_transportq_lock
comma
id|flags
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
id|trans-&gt;krxiodq_link
)paren
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|trans-&gt;krxiodq_link
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_krxiod_qcount
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rxrpc_krxiod_transportq_lock
comma
id|flags
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxiod_dequeue_transport() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * queue a call for attention by krxiod&n; */
DECL|function|rxrpc_krxiod_queue_call
r_void
id|rxrpc_krxiod_queue_call
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|call-&gt;rcv_krxiodq_lk
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rxrpc_krxiod_callq_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|call-&gt;usage
)paren
OG
l_int|0
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|call-&gt;rcv_krxiodq_lk
comma
op_amp
id|rxrpc_krxiod_callq
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|rxrpc_krxiod_qcount
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rxrpc_krxiod_callq_lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|wake_up_all
c_func
(paren
op_amp
id|rxrpc_krxiod_sleepq
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxiod_queue_call() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * dequeue a call from krxiod&squot;s attention queue&n; */
DECL|function|rxrpc_krxiod_dequeue_call
r_void
id|rxrpc_krxiod_dequeue_call
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rxrpc_krxiod_callq_lock
comma
id|flags
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
id|call-&gt;rcv_krxiodq_lk
)paren
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;rcv_krxiodq_lk
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|rxrpc_krxiod_qcount
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rxrpc_krxiod_callq_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_krxiod_dequeue_call() */
eof
