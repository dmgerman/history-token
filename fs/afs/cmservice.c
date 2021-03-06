multiline_comment|/* cmservice.c: AFS Cache Manager Service&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &quot;server.h&quot;
macro_line|#include &quot;cell.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &quot;cmservice.h&quot;
macro_line|#include &quot;internal.h&quot;
DECL|variable|afscm_usage
r_static
r_int
id|afscm_usage
suffix:semicolon
multiline_comment|/* AFS cache manager usage count */
DECL|variable|afscm_sem
r_static
r_struct
id|rw_semaphore
id|afscm_sem
suffix:semicolon
multiline_comment|/* AFS cache manager start/stop semaphore */
r_static
r_int
id|afscm_new_call
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_static
r_void
id|afscm_attention
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_static
r_void
id|afscm_error
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_static
r_void
id|afscm_aemap
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_static
r_void
id|_SRXAFSCM_CallBack
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_static
r_void
id|_SRXAFSCM_InitCallBackState
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_static
r_void
id|_SRXAFSCM_Probe
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
DECL|typedef|_SRXAFSCM_xxxx_t
r_typedef
r_void
(paren
op_star
id|_SRXAFSCM_xxxx_t
)paren
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
DECL|variable|AFSCM_ops
r_static
r_const
r_struct
id|rxrpc_operation
id|AFSCM_ops
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
l_int|204
comma
dot
id|asize
op_assign
id|RXRPC_APP_MARK_EOF
comma
dot
id|name
op_assign
l_string|&quot;CallBack&quot;
comma
dot
id|user
op_assign
id|_SRXAFSCM_CallBack
comma
)brace
comma
(brace
dot
id|id
op_assign
l_int|205
comma
dot
id|asize
op_assign
id|RXRPC_APP_MARK_EOF
comma
dot
id|name
op_assign
l_string|&quot;InitCallBackState&quot;
comma
dot
id|user
op_assign
id|_SRXAFSCM_InitCallBackState
comma
)brace
comma
(brace
dot
id|id
op_assign
l_int|206
comma
dot
id|asize
op_assign
id|RXRPC_APP_MARK_EOF
comma
dot
id|name
op_assign
l_string|&quot;Probe&quot;
comma
dot
id|user
op_assign
id|_SRXAFSCM_Probe
comma
)brace
comma
macro_line|#if 0
(brace
dot
id|id
op_assign
l_int|207
comma
dot
id|asize
op_assign
id|RXRPC_APP_MARK_EOF
comma
dot
id|name
op_assign
l_string|&quot;GetLock&quot;
comma
dot
id|user
op_assign
id|_SRXAFSCM_GetLock
comma
)brace
comma
(brace
dot
id|id
op_assign
l_int|208
comma
dot
id|asize
op_assign
id|RXRPC_APP_MARK_EOF
comma
dot
id|name
op_assign
l_string|&quot;GetCE&quot;
comma
dot
id|user
op_assign
id|_SRXAFSCM_GetCE
comma
)brace
comma
(brace
dot
id|id
op_assign
l_int|209
comma
dot
id|asize
op_assign
id|RXRPC_APP_MARK_EOF
comma
dot
id|name
op_assign
l_string|&quot;GetXStatsVersion&quot;
comma
dot
id|user
op_assign
id|_SRXAFSCM_GetXStatsVersion
comma
)brace
comma
(brace
dot
id|id
op_assign
l_int|210
comma
dot
id|asize
op_assign
id|RXRPC_APP_MARK_EOF
comma
dot
id|name
op_assign
l_string|&quot;GetXStats&quot;
comma
dot
id|user
op_assign
id|_SRXAFSCM_GetXStats
comma
)brace
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|AFSCM_service
r_static
r_struct
id|rxrpc_service
id|AFSCM_service
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;AFS/CM&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|link
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|AFSCM_service.link
)paren
comma
dot
id|new_call
op_assign
id|afscm_new_call
comma
dot
id|service_id
op_assign
l_int|1
comma
dot
id|attn_func
op_assign
id|afscm_attention
comma
dot
id|error_func
op_assign
id|afscm_error
comma
dot
id|aemap_func
op_assign
id|afscm_aemap
comma
dot
id|ops_begin
op_assign
op_amp
id|AFSCM_ops
(braket
l_int|0
)braket
comma
dot
id|ops_end
op_assign
op_amp
id|AFSCM_ops
(braket
r_sizeof
(paren
id|AFSCM_ops
)paren
op_div
r_sizeof
(paren
id|AFSCM_ops
(braket
l_int|0
)braket
)paren
)braket
comma
)brace
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|kafscmd_alive
)paren
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|kafscmd_dead
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|kafscmd_sleepq
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|kafscmd_attention_list
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|afscm_calls
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|afscm_calls_lock
)paren
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|kafscmd_attention_lock
)paren
suffix:semicolon
DECL|variable|kafscmd_die
r_static
r_int
id|kafscmd_die
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS Cache Manager kernel thread&n; */
DECL|function|kafscmd
r_static
r_int
id|kafscmd
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
id|myself
comma
id|current
)paren
suffix:semicolon
r_struct
id|rxrpc_call
op_star
id|call
suffix:semicolon
id|_SRXAFSCM_xxxx_t
id|func
suffix:semicolon
r_int
id|die
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kAFS: Started kafscmd %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kafscmd&quot;
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|kafscmd_alive
)paren
suffix:semicolon
multiline_comment|/* loop around looking for things to attend to */
r_do
(brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|kafscmd_attention_list
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
id|kafscmd_sleepq
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
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
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
id|kafscmd_attention_list
)paren
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
op_logical_or
id|kafscmd_die
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
id|kafscmd_sleepq
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
)brace
id|die
op_assign
id|kafscmd_die
suffix:semicolon
multiline_comment|/* dequeue the next call requiring attention */
id|call
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafscmd_attention_lock
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
id|kafscmd_attention_list
)paren
)paren
(brace
id|call
op_assign
id|list_entry
c_func
(paren
id|kafscmd_attention_list.next
comma
r_struct
id|rxrpc_call
comma
id|app_attn_link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;app_attn_link
)paren
suffix:semicolon
id|die
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call
)paren
(brace
multiline_comment|/* act upon it */
id|_debug
c_func
(paren
l_string|&quot;@@@ Begin Attend Call %p&quot;
comma
id|call
)paren
suffix:semicolon
id|func
op_assign
id|call-&gt;app_user
suffix:semicolon
r_if
c_cond
(paren
id|func
)paren
id|func
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
l_string|&quot;@@@ End Attend Call %p&quot;
comma
id|call
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
multiline_comment|/* and that&squot;s all */
id|complete_and_exit
c_func
(paren
op_amp
id|kafscmd_dead
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* end kafscmd() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle a call coming in to the cache manager&n; * - if I want to keep the call, I must increment its usage count&n; * - the return value will be negated and passed back in an abort packet if&n; *   non-zero&n; * - serialised by virtue of there only being one krxiod&n; */
DECL|function|afscm_new_call
r_static
r_int
id|afscm_new_call
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;%p{cid=%u u=%d}&quot;
comma
id|call
comma
id|ntohl
c_func
(paren
id|call-&gt;call_id
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|call-&gt;usage
)paren
)paren
suffix:semicolon
id|rxrpc_get_call
c_func
(paren
id|call
)paren
suffix:semicolon
multiline_comment|/* add to my current call list */
id|spin_lock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|call-&gt;app_link
comma
op_amp
id|afscm_calls
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afscm_new_call() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * queue on the kafscmd queue for attention&n; */
DECL|function|afscm_attention
r_static
r_void
id|afscm_attention
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;%p{cid=%u u=%d}&quot;
comma
id|call
comma
id|ntohl
c_func
(paren
id|call-&gt;call_id
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|call-&gt;usage
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|call-&gt;app_attn_link
)paren
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|call-&gt;app_attn_link
comma
op_amp
id|kafscmd_attention_list
)paren
suffix:semicolon
id|rxrpc_get_call
c_func
(paren
id|call
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafscmd_sleepq
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; {u=%d}&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|call-&gt;usage
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* end afscm_attention() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle my call being aborted&n; * - clean up, dequeue and put my ref to the call&n; */
DECL|function|afscm_error
r_static
r_void
id|afscm_error
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_int
id|removed
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{est=%s ac=%u er=%d}&quot;
comma
id|call
comma
id|rxrpc_call_error_states
(braket
id|call-&gt;app_err_state
)braket
comma
id|call-&gt;app_abort_code
comma
id|call-&gt;app_errno
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|call-&gt;app_attn_link
)paren
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|call-&gt;app_attn_link
comma
op_amp
id|kafscmd_attention_list
)paren
suffix:semicolon
id|rxrpc_get_call
c_func
(paren
id|call
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
id|removed
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|afscm_calls_lock
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
id|call-&gt;app_link
)paren
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;app_link
)paren
suffix:semicolon
id|removed
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|removed
)paren
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafscmd_sleepq
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afscm_error() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * map afs abort codes to/from Linux error codes&n; * - called with call-&gt;lock held&n; */
DECL|function|afscm_aemap
r_static
r_void
id|afscm_aemap
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_switch
c_cond
(paren
id|call-&gt;app_err_state
)paren
(brace
r_case
id|RXRPC_ESTATE_LOCAL_ABORT
suffix:colon
id|call-&gt;app_abort_code
op_assign
op_minus
id|call-&gt;app_errno
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RXRPC_ESTATE_PEER_ABORT
suffix:colon
id|call-&gt;app_errno
op_assign
op_minus
id|ECONNABORTED
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* end afscm_aemap() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * start the cache manager service if not already started&n; */
DECL|function|afscm_start
r_int
id|afscm_start
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|afscm_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|afscm_usage
)paren
(brace
id|ret
op_assign
id|kernel_thread
c_func
(paren
id|kafscmd
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
r_goto
id|out
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|kafscmd_alive
)paren
suffix:semicolon
id|ret
op_assign
id|rxrpc_add_service
c_func
(paren
id|afs_transport
comma
op_amp
id|AFSCM_service
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
id|kill
suffix:semicolon
id|afs_kafstimod_add_timer
c_func
(paren
op_amp
id|afs_mntpt_expiry_timer
comma
id|afs_mntpt_expiry_timeout
op_star
id|HZ
)paren
suffix:semicolon
)brace
id|afscm_usage
op_increment
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|afscm_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|kill
suffix:colon
id|kafscmd_die
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafscmd_sleepq
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|kafscmd_dead
)paren
suffix:semicolon
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|afscm_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afscm_start() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * stop the cache manager service&n; */
DECL|function|afscm_stop
r_void
id|afscm_stop
c_func
(paren
r_void
)paren
(brace
r_struct
id|rxrpc_call
op_star
id|call
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|afscm_sem
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|afscm_usage
op_eq
l_int|0
)paren
suffix:semicolon
id|afscm_usage
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|afscm_usage
op_eq
l_int|0
)paren
(brace
multiline_comment|/* don&squot;t want more incoming calls */
id|rxrpc_del_service
c_func
(paren
id|afs_transport
comma
op_amp
id|AFSCM_service
)paren
suffix:semicolon
multiline_comment|/* abort any calls I&squot;ve still got open (the afscm_error() will&n;&t;&t; * dequeue them) */
id|spin_lock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|afscm_calls
)paren
)paren
(brace
id|call
op_assign
id|list_entry
c_func
(paren
id|afscm_calls.next
comma
r_struct
id|rxrpc_call
comma
id|app_link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;app_link
)paren
suffix:semicolon
id|rxrpc_get_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
id|rxrpc_call_abort
c_func
(paren
id|call
comma
op_minus
id|ESRCH
)paren
suffix:semicolon
multiline_comment|/* abort, dequeue and&n;&t;&t;&t;&t;&t;&t;&t; * put */
id|_debug
c_func
(paren
l_string|&quot;nuking active call %08x.%d&quot;
comma
id|ntohl
c_func
(paren
id|call-&gt;conn-&gt;conn_id
)paren
comma
id|ntohl
c_func
(paren
id|call-&gt;call_id
)paren
)paren
suffix:semicolon
id|rxrpc_put_call
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
id|spin_lock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
multiline_comment|/* get rid of my daemon */
id|kafscmd_die
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafscmd_sleepq
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|kafscmd_dead
)paren
suffix:semicolon
multiline_comment|/* dispose of any calls waiting for attention */
id|spin_lock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|kafscmd_attention_list
)paren
)paren
(brace
id|call
op_assign
id|list_entry
c_func
(paren
id|kafscmd_attention_list.next
comma
r_struct
id|rxrpc_call
comma
id|app_attn_link
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;app_attn_link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafscmd_attention_lock
)paren
suffix:semicolon
id|afs_kafstimod_del_timer
c_func
(paren
op_amp
id|afs_mntpt_expiry_timer
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|afscm_sem
)paren
suffix:semicolon
)brace
multiline_comment|/* end afscm_stop() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle the fileserver breaking a set of callbacks&n; */
DECL|function|_SRXAFSCM_CallBack
r_static
r_void
id|_SRXAFSCM_CallBack
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
r_int
id|count
comma
id|qty
comma
id|tmp
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|removed
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{acs=%s}&quot;
comma
id|call
comma
id|rxrpc_call_states
(braket
id|call-&gt;app_call_state
)braket
)paren
suffix:semicolon
id|server
op_assign
id|afs_server_get_from_peer
c_func
(paren
id|call-&gt;conn-&gt;peer
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|call-&gt;app_call_state
)paren
(brace
multiline_comment|/* we&squot;ve received the last packet&n;&t;&t; * - drain all the data from the call and send the reply&n;&t;&t; */
r_case
id|RXRPC_CSTATE_SRVR_GOT_ARGS
suffix:colon
id|ret
op_assign
op_minus
id|EBADMSG
suffix:semicolon
id|qty
op_assign
id|call-&gt;app_ready_qty
suffix:semicolon
r_if
c_cond
(paren
id|qty
template_param
l_int|50
op_star
(paren
l_int|6
op_star
l_int|4
)paren
op_plus
l_int|8
)paren
r_break
suffix:semicolon
(brace
r_struct
id|afs_callback
op_star
id|cb
comma
op_star
id|pcb
suffix:semicolon
r_int
id|loop
suffix:semicolon
id|__be32
op_star
id|fp
comma
op_star
id|bp
suffix:semicolon
id|fp
op_assign
id|rxrpc_call_alloc_scratch
c_func
(paren
id|call
comma
id|qty
)paren
suffix:semicolon
multiline_comment|/* drag the entire argument block out to the scratch&n;&t;&t;&t; * space */
id|ret
op_assign
id|rxrpc_call_read_data
c_func
(paren
id|call
comma
id|fp
comma
id|qty
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
r_break
suffix:semicolon
multiline_comment|/* and unmarshall the parameter block */
id|ret
op_assign
op_minus
id|EBADMSG
suffix:semicolon
id|count
op_assign
id|ntohl
c_func
(paren
op_star
id|fp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|AFSCBMAX
op_logical_or
(paren
id|count
op_star
(paren
l_int|3
op_star
l_int|4
)paren
op_plus
l_int|8
op_ne
id|qty
op_logical_and
id|count
op_star
(paren
l_int|6
op_star
l_int|4
)paren
op_plus
l_int|8
op_ne
id|qty
)paren
)paren
r_break
suffix:semicolon
id|bp
op_assign
id|fp
op_plus
id|count
op_star
l_int|3
suffix:semicolon
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
l_int|0
op_logical_and
id|tmp
op_ne
id|count
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|0
)paren
id|bp
op_assign
l_int|NULL
suffix:semicolon
id|pcb
op_assign
id|cb
op_assign
id|rxrpc_call_alloc_scratch_s
c_func
(paren
id|call
comma
r_struct
id|afs_callback
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
id|count
op_minus
l_int|1
suffix:semicolon
id|loop
op_ge
l_int|0
suffix:semicolon
id|loop
op_decrement
)paren
(brace
id|pcb-&gt;fid.vid
op_assign
id|ntohl
c_func
(paren
op_star
id|fp
op_increment
)paren
suffix:semicolon
id|pcb-&gt;fid.vnode
op_assign
id|ntohl
c_func
(paren
op_star
id|fp
op_increment
)paren
suffix:semicolon
id|pcb-&gt;fid.unique
op_assign
id|ntohl
c_func
(paren
op_star
id|fp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp
)paren
(brace
id|pcb-&gt;version
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|pcb-&gt;expiry
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|pcb-&gt;type
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
id|pcb-&gt;version
op_assign
l_int|0
suffix:semicolon
id|pcb-&gt;expiry
op_assign
l_int|0
suffix:semicolon
id|pcb-&gt;type
op_assign
id|AFSCM_CB_UNTYPED
suffix:semicolon
)brace
id|pcb
op_increment
suffix:semicolon
)brace
multiline_comment|/* invoke the actual service routine */
id|ret
op_assign
id|SRXAFSCM_CallBack
c_func
(paren
id|server
comma
id|count
comma
id|cb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* send the reply */
id|ret
op_assign
id|rxrpc_call_write_data
c_func
(paren
id|call
comma
l_int|0
comma
l_int|NULL
comma
id|RXRPC_LAST_PACKET
comma
id|GFP_KERNEL
comma
l_int|0
comma
op_amp
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* operation complete */
r_case
id|RXRPC_CSTATE_COMPLETE
suffix:colon
id|call-&gt;app_user
op_assign
l_int|NULL
suffix:semicolon
id|removed
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|afscm_calls_lock
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
id|call-&gt;app_link
)paren
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;app_link
)paren
suffix:semicolon
id|removed
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|removed
)paren
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* operation terminated on error */
r_case
id|RXRPC_CSTATE_ERROR
suffix:colon
id|call-&gt;app_user
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
id|afs_put_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* end _SRXAFSCM_CallBack() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle the fileserver asking us to initialise our callback state&n; */
DECL|function|_SRXAFSCM_InitCallBackState
r_static
r_void
id|_SRXAFSCM_InitCallBackState
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|removed
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{acs=%s}&quot;
comma
id|call
comma
id|rxrpc_call_states
(braket
id|call-&gt;app_call_state
)braket
)paren
suffix:semicolon
id|server
op_assign
id|afs_server_get_from_peer
c_func
(paren
id|call-&gt;conn-&gt;peer
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|call-&gt;app_call_state
)paren
(brace
multiline_comment|/* we&squot;ve received the last packet - drain all the data from the&n;&t;&t; * call */
r_case
id|RXRPC_CSTATE_SRVR_GOT_ARGS
suffix:colon
multiline_comment|/* shouldn&squot;t be any args */
id|ret
op_assign
op_minus
id|EBADMSG
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* send the reply when asked for it */
r_case
id|RXRPC_CSTATE_SRVR_SND_REPLY
suffix:colon
multiline_comment|/* invoke the actual service routine */
id|ret
op_assign
id|SRXAFSCM_InitCallBackState
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
id|ret
op_assign
id|rxrpc_call_write_data
c_func
(paren
id|call
comma
l_int|0
comma
l_int|NULL
comma
id|RXRPC_LAST_PACKET
comma
id|GFP_KERNEL
comma
l_int|0
comma
op_amp
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* operation complete */
r_case
id|RXRPC_CSTATE_COMPLETE
suffix:colon
id|call-&gt;app_user
op_assign
l_int|NULL
suffix:semicolon
id|removed
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|afscm_calls_lock
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
id|call-&gt;app_link
)paren
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;app_link
)paren
suffix:semicolon
id|removed
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|removed
)paren
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* operation terminated on error */
r_case
id|RXRPC_CSTATE_ERROR
suffix:colon
id|call-&gt;app_user
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
id|afs_put_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* end _SRXAFSCM_InitCallBackState() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle a probe from a fileserver&n; */
DECL|function|_SRXAFSCM_Probe
r_static
r_void
id|_SRXAFSCM_Probe
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|removed
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p{acs=%s}&quot;
comma
id|call
comma
id|rxrpc_call_states
(braket
id|call-&gt;app_call_state
)braket
)paren
suffix:semicolon
id|server
op_assign
id|afs_server_get_from_peer
c_func
(paren
id|call-&gt;conn-&gt;peer
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|call-&gt;app_call_state
)paren
(brace
multiline_comment|/* we&squot;ve received the last packet - drain all the data from the&n;&t;&t; * call */
r_case
id|RXRPC_CSTATE_SRVR_GOT_ARGS
suffix:colon
multiline_comment|/* shouldn&squot;t be any args */
id|ret
op_assign
op_minus
id|EBADMSG
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* send the reply when asked for it */
r_case
id|RXRPC_CSTATE_SRVR_SND_REPLY
suffix:colon
multiline_comment|/* invoke the actual service routine */
id|ret
op_assign
id|SRXAFSCM_Probe
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
id|ret
op_assign
id|rxrpc_call_write_data
c_func
(paren
id|call
comma
l_int|0
comma
l_int|NULL
comma
id|RXRPC_LAST_PACKET
comma
id|GFP_KERNEL
comma
l_int|0
comma
op_amp
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* operation complete */
r_case
id|RXRPC_CSTATE_COMPLETE
suffix:colon
id|call-&gt;app_user
op_assign
l_int|NULL
suffix:semicolon
id|removed
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|afscm_calls_lock
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
id|call-&gt;app_link
)paren
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|call-&gt;app_link
)paren
suffix:semicolon
id|removed
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|afscm_calls_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|removed
)paren
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* operation terminated on error */
r_case
id|RXRPC_CSTATE_ERROR
suffix:colon
id|call-&gt;app_user
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
id|afs_put_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* end _SRXAFSCM_Probe() */
eof
