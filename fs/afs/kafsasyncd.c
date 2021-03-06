multiline_comment|/* kafsasyncd.c: AFS asynchronous operation daemon&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; *&n; * The AFS async daemon is used to the following:&n; * - probe &quot;dead&quot; servers to see whether they&squot;ve come back to life yet.&n; * - probe &quot;live&quot; servers that we haven&squot;t talked to for a while to see if they are better&n; *   candidates for serving than what we&squot;re currently using&n; * - poll volume location servers to keep up to date volume location lists&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &quot;cell.h&quot;
macro_line|#include &quot;server.h&quot;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;kafsasyncd.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &quot;internal.h&quot;
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|kafsasyncd_alive
)paren
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|kafsasyncd_dead
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|kafsasyncd_sleepq
)paren
suffix:semicolon
DECL|variable|kafsasyncd_task
r_static
r_struct
id|task_struct
op_star
id|kafsasyncd_task
suffix:semicolon
DECL|variable|kafsasyncd_die
r_static
r_int
id|kafsasyncd_die
suffix:semicolon
r_static
r_int
id|kafsasyncd
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|kafsasyncd_async_attnq
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|kafsasyncd_async_busyq
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|kafsasyncd_async_lock
)paren
suffix:semicolon
DECL|function|kafsasyncd_null_call_attn_func
r_static
r_void
id|kafsasyncd_null_call_attn_func
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
)brace
DECL|function|kafsasyncd_null_call_error_func
r_static
r_void
id|kafsasyncd_null_call_error_func
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * start the async daemon&n; */
DECL|function|afs_kafsasyncd_start
r_int
id|afs_kafsasyncd_start
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|kernel_thread
c_func
(paren
id|kafsasyncd
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|kafsasyncd_alive
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_kafsasyncd_start() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * stop the async daemon&n; */
DECL|function|afs_kafsasyncd_stop
r_void
id|afs_kafsasyncd_stop
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* get rid of my daemon */
id|kafsasyncd_die
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafsasyncd_sleepq
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|kafsasyncd_dead
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_kafsasyncd_stop() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * probing daemon&n; */
DECL|function|kafsasyncd
r_static
r_int
id|kafsasyncd
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|afs_async_op
op_star
id|op
suffix:semicolon
r_int
id|die
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|myself
comma
id|current
)paren
suffix:semicolon
id|kafsasyncd_task
op_assign
id|current
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kAFS: Started kafsasyncd %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kafsasyncd&quot;
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|kafsasyncd_alive
)paren
suffix:semicolon
multiline_comment|/* loop around looking for things to attend to */
r_do
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
id|kafsasyncd_sleepq
comma
op_amp
id|myself
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|kafsasyncd_async_attnq
)paren
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
op_logical_or
id|kafsasyncd_die
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|kafsasyncd_sleepq
comma
op_amp
id|myself
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|try_to_freeze
c_func
(paren
id|PF_FREEZE
)paren
suffix:semicolon
multiline_comment|/* discard pending signals */
id|afs_discard_my_signals
c_func
(paren
)paren
suffix:semicolon
id|die
op_assign
id|kafsasyncd_die
suffix:semicolon
multiline_comment|/* deal with the next asynchronous operation requiring&n;&t;&t; * attention */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|kafsasyncd_async_attnq
)paren
)paren
(brace
r_struct
id|afs_async_op
op_star
id|op
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;@@@ Begin Asynchronous Operation&quot;
)paren
suffix:semicolon
id|op
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
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
id|kafsasyncd_async_attnq
)paren
)paren
(brace
id|op
op_assign
id|list_entry
c_func
(paren
id|kafsasyncd_async_attnq.next
comma
r_struct
id|afs_async_op
comma
id|link
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|op-&gt;link
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|op-&gt;link
comma
op_amp
id|kafsasyncd_async_busyq
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;@@@ Operation %p {%p}&bslash;n&quot;
comma
id|op
comma
id|op
ques
c_cond
id|op-&gt;ops
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op
)paren
id|op-&gt;ops
op_member_access_from_pointer
id|attend
c_func
(paren
id|op
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;@@@ End Asynchronous Operation&quot;
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|die
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* need to kill all outstanding asynchronous operations before&n;&t; * exiting */
id|kafsasyncd_task
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
multiline_comment|/* fold the busy and attention queues together */
id|list_splice_init
c_func
(paren
op_amp
id|kafsasyncd_async_busyq
comma
op_amp
id|kafsasyncd_async_attnq
)paren
suffix:semicolon
multiline_comment|/* dequeue kafsasyncd from all their wait queues */
id|list_for_each_entry
c_func
(paren
id|op
comma
op_amp
id|kafsasyncd_async_attnq
comma
id|link
)paren
(brace
id|op-&gt;call-&gt;app_attn_func
op_assign
id|kafsasyncd_null_call_attn_func
suffix:semicolon
id|op-&gt;call-&gt;app_error_func
op_assign
id|kafsasyncd_null_call_error_func
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|op-&gt;call-&gt;waitq
comma
op_amp
id|op-&gt;waiter
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
multiline_comment|/* abort all the operations */
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|kafsasyncd_async_attnq
)paren
)paren
(brace
id|op
op_assign
id|list_entry
c_func
(paren
id|kafsasyncd_async_attnq.next
comma
r_struct
id|afs_async_op
comma
id|link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|op-&gt;link
)paren
suffix:semicolon
id|rxrpc_call_abort
c_func
(paren
id|op-&gt;call
comma
op_minus
id|EIO
)paren
suffix:semicolon
id|rxrpc_put_call
c_func
(paren
id|op-&gt;call
)paren
suffix:semicolon
id|op-&gt;call
op_assign
l_int|NULL
suffix:semicolon
id|op-&gt;ops
op_member_access_from_pointer
id|discard
c_func
(paren
id|op
)paren
suffix:semicolon
)brace
multiline_comment|/* and that&squot;s all */
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|complete_and_exit
c_func
(paren
op_amp
id|kafsasyncd_dead
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* end kafsasyncd() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * begin an operation&n; * - place operation on busy queue&n; */
DECL|function|afs_kafsasyncd_begin_op
r_void
id|afs_kafsasyncd_begin_op
c_func
(paren
r_struct
id|afs_async_op
op_star
id|op
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|op-&gt;waiter
comma
id|kafsasyncd_task
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|op-&gt;call-&gt;waitq
comma
op_amp
id|op-&gt;waiter
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|op-&gt;link
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|op-&gt;link
comma
op_amp
id|kafsasyncd_async_busyq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_kafsasyncd_begin_op() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * request attention for an operation&n; * - move to attention queue&n; */
DECL|function|afs_kafsasyncd_attend_op
r_void
id|afs_kafsasyncd_attend_op
c_func
(paren
r_struct
id|afs_async_op
op_star
id|op
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|op-&gt;link
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|op-&gt;link
comma
op_amp
id|kafsasyncd_async_attnq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafsasyncd_sleepq
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_kafsasyncd_attend_op() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * terminate an operation&n; * - remove from either queue&n; */
DECL|function|afs_kafsasyncd_terminate_op
r_void
id|afs_kafsasyncd_terminate_op
c_func
(paren
r_struct
id|afs_async_op
op_star
id|op
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
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
id|op-&gt;link
)paren
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|op-&gt;link
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|op-&gt;call-&gt;waitq
comma
op_amp
id|op-&gt;waiter
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafsasyncd_async_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafsasyncd_sleepq
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_kafsasyncd_terminate_op() */
eof
