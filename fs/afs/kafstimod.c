multiline_comment|/* kafstimod.c: AFS timeout daemon&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &quot;cell.h&quot;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &quot;internal.h&quot;
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|kafstimod_alive
)paren
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|kafstimod_dead
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|kafstimod_sleepq
)paren
suffix:semicolon
DECL|variable|kafstimod_die
r_static
r_int
id|kafstimod_die
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|kafstimod_list
)paren
suffix:semicolon
DECL|variable|kafstimod_lock
r_static
id|spinlock_t
id|kafstimod_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
r_int
id|kafstimod
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * start the timeout daemon&n; */
DECL|function|afs_kafstimod_start
r_int
id|afs_kafstimod_start
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
id|kafstimod
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
id|kafstimod_alive
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_kafstimod_start() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * stop the timeout daemon&n; */
DECL|function|afs_kafstimod_stop
r_void
id|afs_kafstimod_stop
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* get rid of my daemon */
id|kafstimod_die
op_assign
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafstimod_sleepq
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|kafstimod_dead
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_kafstimod_stop() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * timeout processing daemon&n; */
DECL|function|kafstimod
r_static
r_int
id|kafstimod
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
id|afs_timer_t
op_star
id|timer
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kAFS: Started kafstimod %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;kafstimod&quot;
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|kafstimod_alive
)paren
suffix:semicolon
multiline_comment|/* loop around looking for things to attend to */
id|loop
suffix:colon
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
id|kafstimod_sleepq
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
r_int
r_int
id|jif
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* deal with the server being asked to die */
r_if
c_cond
(paren
id|kafstimod_die
)paren
(brace
id|remove_wait_queue
c_func
(paren
op_amp
id|kafstimod_sleepq
comma
op_amp
id|myself
)paren
suffix:semicolon
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
id|kafstimod_dead
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* discard pending signals */
id|afs_discard_my_signals
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* work out the time to elapse before the next event */
id|spin_lock
c_func
(paren
op_amp
id|kafstimod_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|kafstimod_list
)paren
)paren
(brace
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
)brace
r_else
(brace
id|timer
op_assign
id|list_entry
c_func
(paren
id|kafstimod_list.next
comma
id|afs_timer_t
comma
id|link
)paren
suffix:semicolon
id|timeout
op_assign
id|timer-&gt;timo_jif
suffix:semicolon
id|jif
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|time_before_eq
c_func
(paren
(paren
r_int
r_int
)paren
id|timeout
comma
id|jif
)paren
)paren
r_goto
id|immediate
suffix:semicolon
r_else
(brace
id|timeout
op_assign
(paren
r_int
)paren
id|timeout
op_minus
(paren
r_int
)paren
id|jiffies
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|kafstimod_lock
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
multiline_comment|/* the thing on the front of the queue needs processing&n;&t; * - we come here with the lock held and timer pointing to the expired entry&n;&t; */
id|immediate
suffix:colon
id|remove_wait_queue
c_func
(paren
op_amp
id|kafstimod_sleepq
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
id|_debug
c_func
(paren
l_string|&quot;@@@ Begin Timeout of %p&quot;
comma
id|timer
)paren
suffix:semicolon
multiline_comment|/* dequeue the timer */
id|list_del_init
c_func
(paren
op_amp
id|timer-&gt;link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kafstimod_lock
)paren
suffix:semicolon
multiline_comment|/* call the timeout function */
id|timer-&gt;ops
op_member_access_from_pointer
id|timed_out
c_func
(paren
id|timer
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;@@@ End Timeout&quot;
)paren
suffix:semicolon
r_goto
id|loop
suffix:semicolon
)brace
multiline_comment|/* end kafstimod() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * (re-)queue a timer&n; */
DECL|function|afs_kafstimod_add_timer
r_void
id|afs_kafstimod_add_timer
c_func
(paren
id|afs_timer_t
op_star
id|timer
comma
r_int
r_int
id|timeout
)paren
(brace
r_struct
id|list_head
op_star
id|_p
suffix:semicolon
id|afs_timer_t
op_star
id|ptimer
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p,%lu&quot;
comma
id|timer
comma
id|timeout
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafstimod_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|timer-&gt;link
)paren
suffix:semicolon
multiline_comment|/* the timer was deferred or reset - put it back in the queue at the right place */
id|timer-&gt;timo_jif
op_assign
id|jiffies
op_plus
id|timeout
suffix:semicolon
id|list_for_each
c_func
(paren
id|_p
comma
op_amp
id|kafstimod_list
)paren
(brace
id|ptimer
op_assign
id|list_entry
c_func
(paren
id|_p
comma
id|afs_timer_t
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|timer-&gt;timo_jif
comma
id|ptimer-&gt;timo_jif
)paren
)paren
r_break
suffix:semicolon
)brace
id|list_add_tail
c_func
(paren
op_amp
id|timer-&gt;link
comma
id|_p
)paren
suffix:semicolon
multiline_comment|/* insert before stopping point */
id|spin_unlock
c_func
(paren
op_amp
id|kafstimod_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafstimod_sleepq
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_kafstimod_add_timer() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * dequeue a timer&n; * - returns 0 if the timer was deleted or -ENOENT if it wasn&squot;t queued&n; */
DECL|function|afs_kafstimod_del_timer
r_int
id|afs_kafstimod_del_timer
c_func
(paren
id|afs_timer_t
op_star
id|timer
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%p&quot;
comma
id|timer
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|kafstimod_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|timer-&gt;link
)paren
)paren
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_else
id|list_del_init
c_func
(paren
op_amp
id|timer-&gt;link
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kafstimod_lock
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|kafstimod_sleepq
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
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_kafstimod_del_timer() */
eof
