macro_line|#ifndef _LINUX_WAIT_H
DECL|macro|_LINUX_WAIT_H
mdefine_line|#define _LINUX_WAIT_H
DECL|macro|WNOHANG
mdefine_line|#define WNOHANG&t;&t;0x00000001
DECL|macro|WUNTRACED
mdefine_line|#define WUNTRACED&t;0x00000002
DECL|macro|__WNOTHREAD
mdefine_line|#define __WNOTHREAD&t;0x20000000&t;/* Don&squot;t wait on children of other threads in this group */
DECL|macro|__WALL
mdefine_line|#define __WALL&t;&t;0x40000000&t;/* Wait on all children, regardless of type */
DECL|macro|__WCLONE
mdefine_line|#define __WCLONE&t;0x80000000&t;/* Wait only on non-SIGCHLD children */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|typedef|wait_queue_t
r_typedef
r_struct
id|__wait_queue
id|wait_queue_t
suffix:semicolon
DECL|typedef|wait_queue_func_t
r_typedef
r_int
(paren
op_star
id|wait_queue_func_t
)paren
(paren
id|wait_queue_t
op_star
id|wait
comma
r_int
id|mode
comma
r_int
id|sync
)paren
suffix:semicolon
r_extern
r_int
id|default_wake_function
c_func
(paren
id|wait_queue_t
op_star
id|wait
comma
r_int
id|mode
comma
r_int
id|sync
)paren
suffix:semicolon
DECL|struct|__wait_queue
r_struct
id|__wait_queue
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|WQ_FLAG_EXCLUSIVE
mdefine_line|#define WQ_FLAG_EXCLUSIVE&t;0x01
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|func
id|wait_queue_func_t
id|func
suffix:semicolon
DECL|member|task_list
r_struct
id|list_head
id|task_list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|__wait_queue_head
r_struct
id|__wait_queue_head
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|task_list
r_struct
id|list_head
id|task_list
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|wait_queue_head_t
r_typedef
r_struct
id|__wait_queue_head
id|wait_queue_head_t
suffix:semicolon
multiline_comment|/*&n; * Macros for declaration and initialisaton of the datatypes&n; */
DECL|macro|__WAITQUEUE_INITIALIZER
mdefine_line|#define __WAITQUEUE_INITIALIZER(name, tsk) {&t;&t;&t;&t;&bslash;&n;&t;.task&t;&t;= tsk,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.func&t;&t;= default_wake_function,&t;&t;&t;&bslash;&n;&t;.task_list&t;= { NULL, NULL } }
DECL|macro|DECLARE_WAITQUEUE
mdefine_line|#define DECLARE_WAITQUEUE(name, tsk)&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t name = __WAITQUEUE_INITIALIZER(name, tsk)
DECL|macro|__WAIT_QUEUE_HEAD_INITIALIZER
mdefine_line|#define __WAIT_QUEUE_HEAD_INITIALIZER(name) {&t;&t;&t;&t;&bslash;&n;&t;.lock&t;&t;= SPIN_LOCK_UNLOCKED,&t;&t;&t;&t;&bslash;&n;&t;.task_list&t;= { &amp;(name).task_list, &amp;(name).task_list } }
DECL|macro|DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define DECLARE_WAIT_QUEUE_HEAD(name) &bslash;&n;&t;wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name)
DECL|function|init_waitqueue_head
r_static
r_inline
r_void
id|init_waitqueue_head
c_func
(paren
id|wait_queue_head_t
op_star
id|q
)paren
(brace
id|q-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|q-&gt;task_list
)paren
suffix:semicolon
)brace
DECL|function|init_waitqueue_entry
r_static
r_inline
r_void
id|init_waitqueue_entry
c_func
(paren
id|wait_queue_t
op_star
id|q
comma
r_struct
id|task_struct
op_star
id|p
)paren
(brace
id|q-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|q-&gt;task
op_assign
id|p
suffix:semicolon
id|q-&gt;func
op_assign
id|default_wake_function
suffix:semicolon
)brace
DECL|function|init_waitqueue_func_entry
r_static
r_inline
r_void
id|init_waitqueue_func_entry
c_func
(paren
id|wait_queue_t
op_star
id|q
comma
id|wait_queue_func_t
id|func
)paren
(brace
id|q-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|q-&gt;task
op_assign
l_int|NULL
suffix:semicolon
id|q-&gt;func
op_assign
id|func
suffix:semicolon
)brace
DECL|function|waitqueue_active
r_static
r_inline
r_int
id|waitqueue_active
c_func
(paren
id|wait_queue_head_t
op_star
id|q
)paren
(brace
r_return
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;task_list
)paren
suffix:semicolon
)brace
r_extern
r_void
id|FASTCALL
c_func
(paren
id|add_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|add_wait_queue_exclusive
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|remove_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
)paren
suffix:semicolon
DECL|function|__add_wait_queue
r_static
r_inline
r_void
id|__add_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|head
comma
id|wait_queue_t
op_star
r_new
)paren
(brace
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|task_list
comma
op_amp
id|head-&gt;task_list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Used for wake-one threads:&n; */
DECL|function|__add_wait_queue_tail
r_static
r_inline
r_void
id|__add_wait_queue_tail
c_func
(paren
id|wait_queue_head_t
op_star
id|head
comma
id|wait_queue_t
op_star
r_new
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|task_list
comma
op_amp
id|head-&gt;task_list
)paren
suffix:semicolon
)brace
DECL|function|__remove_wait_queue
r_static
r_inline
r_void
id|__remove_wait_queue
c_func
(paren
id|wait_queue_head_t
op_star
id|head
comma
id|wait_queue_t
op_star
id|old
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|old-&gt;task_list
)paren
suffix:semicolon
)brace
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__wake_up
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
r_int
r_int
id|mode
comma
r_int
id|nr
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__wake_up_locked
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
r_int
r_int
id|mode
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__wake_up_sync
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
r_int
r_int
id|mode
comma
r_int
id|nr
)paren
)paren
suffix:semicolon
DECL|macro|wake_up
mdefine_line|#define wake_up(x)&t;&t;&t;__wake_up((x),TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, 1)
DECL|macro|wake_up_nr
mdefine_line|#define wake_up_nr(x, nr)&t;&t;__wake_up((x),TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, nr)
DECL|macro|wake_up_all
mdefine_line|#define wake_up_all(x)&t;&t;&t;__wake_up((x),TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, 0)
DECL|macro|wake_up_all_sync
mdefine_line|#define wake_up_all_sync(x)&t;&t;&t;__wake_up_sync((x),TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, 0)
DECL|macro|wake_up_interruptible
mdefine_line|#define wake_up_interruptible(x)&t;__wake_up((x),TASK_INTERRUPTIBLE, 1)
DECL|macro|wake_up_interruptible_nr
mdefine_line|#define wake_up_interruptible_nr(x, nr)&t;__wake_up((x),TASK_INTERRUPTIBLE, nr)
DECL|macro|wake_up_interruptible_all
mdefine_line|#define wake_up_interruptible_all(x)&t;__wake_up((x),TASK_INTERRUPTIBLE, 0)
DECL|macro|wake_up_locked
mdefine_line|#define&t;wake_up_locked(x)&t;&t;__wake_up_locked((x), TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE)
DECL|macro|wake_up_interruptible_sync
mdefine_line|#define wake_up_interruptible_sync(x)   __wake_up_sync((x),TASK_INTERRUPTIBLE, 1)
DECL|macro|__wait_event
mdefine_line|#define __wait_event(wq, condition) &t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t __wait;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;init_waitqueue_entry(&amp;__wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE);&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event
mdefine_line|#define wait_event(wq, condition) &t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (condition)&t; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__wait_event(wq, condition);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__wait_event_interruptible
mdefine_line|#define __wait_event_interruptible(wq, condition, ret)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t __wait;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;init_waitqueue_entry(&amp;__wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_INTERRUPTIBLE);&t;&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!signal_pending(current)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;schedule();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;continue;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = -ERESTARTSYS;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_interruptible
mdefine_line|#define wait_event_interruptible(wq, condition)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __ret = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(condition))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__wait_event_interruptible(wq, condition, __ret);&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__wait_event_interruptible_timeout
mdefine_line|#define __wait_event_interruptible_timeout(wq, condition, ret)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t __wait;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;init_waitqueue_entry(&amp;__wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_current_state(TASK_INTERRUPTIBLE);&t;&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!signal_pending(current)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ret = schedule_timeout(ret);&t;&t;&t;&bslash;&n;&t;&t;&t;if (!ret)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;continue;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = -ERESTARTSYS;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;wq, &amp;__wait);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_interruptible_timeout
mdefine_line|#define wait_event_interruptible_timeout(wq, condition, timeout)&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __ret = timeout;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(condition))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__wait_event_interruptible_timeout(wq, condition, __ret); &bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * Must be called with the spinlock in the wait_queue_head_t held.&n; */
DECL|function|add_wait_queue_exclusive_locked
r_static
r_inline
r_void
id|add_wait_queue_exclusive_locked
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
(brace
id|wait-&gt;flags
op_or_assign
id|WQ_FLAG_EXCLUSIVE
suffix:semicolon
id|__add_wait_queue_tail
c_func
(paren
id|q
comma
id|wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Must be called with the spinlock in the wait_queue_head_t held.&n; */
DECL|function|remove_wait_queue_locked
r_static
r_inline
r_void
id|remove_wait_queue_locked
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
(brace
id|__remove_wait_queue
c_func
(paren
id|q
comma
id|wait
)paren
suffix:semicolon
)brace
DECL|macro|add_wait_queue_cond
mdefine_line|#define add_wait_queue_cond(q, wait, cond) &bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;&t;int _raced = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock_irqsave(&amp;(q)-&gt;lock, flags);&t;&bslash;&n;&t;&t;(wait)-&gt;flags = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;__add_wait_queue((q), (wait));&t;&t;&t;&bslash;&n;&t;&t;rmb();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!(cond)) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;_raced = 1;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;__remove_wait_queue((q), (wait));&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock_irqrestore(&amp;(q)-&gt;lock, flags);&t;&bslash;&n;&t;&t;_raced;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * These are the old interfaces to sleep waiting for an event.&n; * They are racy.  DO NOT use them, use the wait_event* interfaces above.  &n; * We plan to remove these interfaces during 2.7.&n; */
r_extern
r_void
id|FASTCALL
c_func
(paren
id|sleep_on
c_func
(paren
id|wait_queue_head_t
op_star
id|q
)paren
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
id|sleep_on_timeout
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
r_int
r_int
id|timeout
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|interruptible_sleep_on
c_func
(paren
id|wait_queue_head_t
op_star
id|q
)paren
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
id|interruptible_sleep_on_timeout
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
r_int
r_int
id|timeout
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Waitqueues which are removed from the waitqueue_head at wakeup time&n; */
r_void
id|FASTCALL
c_func
(paren
id|prepare_to_wait
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
comma
r_int
id|state
)paren
)paren
suffix:semicolon
r_void
id|FASTCALL
c_func
(paren
id|prepare_to_wait_exclusive
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
comma
r_int
id|state
)paren
)paren
suffix:semicolon
r_void
id|FASTCALL
c_func
(paren
id|finish_wait
c_func
(paren
id|wait_queue_head_t
op_star
id|q
comma
id|wait_queue_t
op_star
id|wait
)paren
)paren
suffix:semicolon
r_int
id|autoremove_wake_function
c_func
(paren
id|wait_queue_t
op_star
id|wait
comma
r_int
id|mode
comma
r_int
id|sync
)paren
suffix:semicolon
DECL|macro|DEFINE_WAIT
mdefine_line|#define DEFINE_WAIT(name)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t name = {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.task&t;&t;= current,&t;&t;&t;&t;&bslash;&n;&t;&t;.func&t;&t;= autoremove_wake_function,&t;&t;&bslash;&n;&t;&t;.task_list&t;= {&t;.next = &amp;name.task_list,&t;&bslash;&n;&t;&t;&t;&t;&t;.prev = &amp;name.task_list,&t;&bslash;&n;&t;&t;&t;&t;},&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|init_wait
mdefine_line|#define init_wait(wait)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;wait-&gt;task = current;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;wait-&gt;func = autoremove_wake_function;&t;&t;&t;&bslash;&n;&t;&t;INIT_LIST_HEAD(&amp;wait-&gt;task_list);&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
