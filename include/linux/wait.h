macro_line|#ifndef _LINUX_WAIT_H
DECL|macro|_LINUX_WAIT_H
mdefine_line|#define _LINUX_WAIT_H
DECL|macro|WNOHANG
mdefine_line|#define WNOHANG&t;&t;0x00000001
DECL|macro|WUNTRACED
mdefine_line|#define WUNTRACED&t;0x00000002
DECL|macro|WSTOPPED
mdefine_line|#define WSTOPPED&t;WUNTRACED
DECL|macro|WEXITED
mdefine_line|#define WEXITED&t;&t;0x00000004
DECL|macro|WCONTINUED
mdefine_line|#define WCONTINUED&t;0x00000008
DECL|macro|WNOWAIT
mdefine_line|#define WNOWAIT&t;&t;0x01000000&t;/* Don&squot;t reap, just poll status.  */
DECL|macro|__WNOTHREAD
mdefine_line|#define __WNOTHREAD&t;0x20000000&t;/* Don&squot;t wait on children of other threads in this group */
DECL|macro|__WALL
mdefine_line|#define __WALL&t;&t;0x40000000&t;/* Wait on all children, regardless of type */
DECL|macro|__WCLONE
mdefine_line|#define __WCLONE&t;0x80000000&t;/* Wait only on non-SIGCHLD children */
multiline_comment|/* First argument to waitid: */
DECL|macro|P_ALL
mdefine_line|#define P_ALL&t;&t;0
DECL|macro|P_PID
mdefine_line|#define P_PID&t;&t;1
DECL|macro|P_PGID
mdefine_line|#define P_PGID&t;&t;2
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/current.h&gt;
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
comma
r_void
op_star
id|key
)paren
suffix:semicolon
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
comma
r_void
op_star
id|key
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
DECL|struct|wait_bit_key
r_struct
id|wait_bit_key
(brace
DECL|member|flags
r_void
op_star
id|flags
suffix:semicolon
DECL|member|bit_nr
r_int
id|bit_nr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wait_bit_queue
r_struct
id|wait_bit_queue
(brace
DECL|member|key
r_struct
id|wait_bit_key
id|key
suffix:semicolon
DECL|member|wait
id|wait_queue_t
id|wait
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
DECL|macro|__WAIT_BIT_KEY_INITIALIZER
mdefine_line|#define __WAIT_BIT_KEY_INITIALIZER(word, bit)&t;&t;&t;&t;&bslash;&n;&t;{ .flags = word, .bit_nr = bit, }
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
multiline_comment|/*&n; * Used to distinguish between sync and async io wait context:&n; * sync i/o typically specifies a NULL wait queue entry or a wait&n; * queue entry bound to a task (current task) to wake up.&n; * aio specifies a wait queue entry with an async notification&n; * callback routine, not associated with any task.&n; */
DECL|macro|is_sync_wait
mdefine_line|#define is_sync_wait(wait)&t;(!(wait) || ((wait)-&gt;task))
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
comma
r_void
op_star
id|key
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
r_void
id|FASTCALL
c_func
(paren
id|__wake_up_bit
c_func
(paren
id|wait_queue_head_t
op_star
comma
r_void
op_star
comma
r_int
)paren
)paren
suffix:semicolon
r_int
id|FASTCALL
c_func
(paren
id|__wait_on_bit
c_func
(paren
id|wait_queue_head_t
op_star
comma
r_struct
id|wait_bit_queue
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
comma
r_int
)paren
)paren
suffix:semicolon
r_int
id|FASTCALL
c_func
(paren
id|__wait_on_bit_lock
c_func
(paren
id|wait_queue_head_t
op_star
comma
r_struct
id|wait_bit_queue
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
comma
r_int
)paren
)paren
suffix:semicolon
id|wait_queue_head_t
op_star
id|FASTCALL
c_func
(paren
id|bit_waitqueue
c_func
(paren
r_void
op_star
comma
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/**&n; * wake_up_bit - wake up a waiter on a bit&n; * @word: the word being waited on, a kernel virtual address&n; * @bit: the bit of the word being waited on&n; *&n; * There is a standard hashed waitqueue table for generic use. This&n; * is the part of the hashtable&squot;s accessor API that wakes up waiters&n; * on a bit. For instance, if one were to have waiters on a bitflag,&n; * one would call wake_up_bit() after clearing the bit.&n; */
DECL|function|wake_up_bit
r_static
r_inline
r_void
id|wake_up_bit
c_func
(paren
r_void
op_star
id|word
comma
r_int
id|bit
)paren
(brace
id|__wake_up_bit
c_func
(paren
id|bit_waitqueue
c_func
(paren
id|word
comma
id|bit
)paren
comma
id|word
comma
id|bit
)paren
suffix:semicolon
)brace
DECL|macro|wake_up
mdefine_line|#define wake_up(x)&t;&t;&t;__wake_up(x, TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, 1, NULL)
DECL|macro|wake_up_nr
mdefine_line|#define wake_up_nr(x, nr)&t;&t;__wake_up(x, TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, nr, NULL)
DECL|macro|wake_up_all
mdefine_line|#define wake_up_all(x)&t;&t;&t;__wake_up(x, TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, 0, NULL)
DECL|macro|wake_up_all_sync
mdefine_line|#define wake_up_all_sync(x)&t;&t;&t;__wake_up_sync((x),TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE, 0)
DECL|macro|wake_up_interruptible
mdefine_line|#define wake_up_interruptible(x)&t;__wake_up(x, TASK_INTERRUPTIBLE, 1, NULL)
DECL|macro|wake_up_interruptible_nr
mdefine_line|#define wake_up_interruptible_nr(x, nr)&t;__wake_up(x, TASK_INTERRUPTIBLE, nr, NULL)
DECL|macro|wake_up_interruptible_all
mdefine_line|#define wake_up_interruptible_all(x)&t;__wake_up(x, TASK_INTERRUPTIBLE, 0, NULL)
DECL|macro|wake_up_locked
mdefine_line|#define&t;wake_up_locked(x)&t;&t;__wake_up_locked((x), TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE)
DECL|macro|wake_up_interruptible_sync
mdefine_line|#define wake_up_interruptible_sync(x)   __wake_up_sync((x),TASK_INTERRUPTIBLE, 1)
DECL|macro|__wait_event
mdefine_line|#define __wait_event(wq, condition) &t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DEFINE_WAIT(__wait);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;prepare_to_wait(&amp;wq, &amp;__wait, TASK_UNINTERRUPTIBLE);&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;schedule();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;finish_wait(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event
mdefine_line|#define wait_event(wq, condition) &t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (condition)&t; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__wait_event(wq, condition);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__wait_event_timeout
mdefine_line|#define __wait_event_timeout(wq, condition, ret)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DEFINE_WAIT(__wait);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;prepare_to_wait(&amp;wq, &amp;__wait, TASK_UNINTERRUPTIBLE);&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = schedule_timeout(ret);&t;&t;&t;&t;&bslash;&n;&t;&t;if (!ret)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;finish_wait(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_timeout
mdefine_line|#define wait_event_timeout(wq, condition, timeout)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __ret = timeout;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(condition)) &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__wait_event_timeout(wq, condition, __ret);&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__wait_event_interruptible
mdefine_line|#define __wait_event_interruptible(wq, condition, ret)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DEFINE_WAIT(__wait);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;prepare_to_wait(&amp;wq, &amp;__wait, TASK_INTERRUPTIBLE);&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!signal_pending(current)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;schedule();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;continue;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = -ERESTARTSYS;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;finish_wait(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_interruptible
mdefine_line|#define wait_event_interruptible(wq, condition)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __ret = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(condition))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__wait_event_interruptible(wq, condition, __ret);&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__wait_event_interruptible_timeout
mdefine_line|#define __wait_event_interruptible_timeout(wq, condition, ret)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DEFINE_WAIT(__wait);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;prepare_to_wait(&amp;wq, &amp;__wait, TASK_INTERRUPTIBLE);&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!signal_pending(current)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ret = schedule_timeout(ret);&t;&t;&t;&bslash;&n;&t;&t;&t;if (!ret)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;continue;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = -ERESTARTSYS;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;finish_wait(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_interruptible_timeout
mdefine_line|#define wait_event_interruptible_timeout(wq, condition, timeout)&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __ret = timeout;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(condition))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__wait_event_interruptible_timeout(wq, condition, __ret); &bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__wait_event_interruptible_exclusive
mdefine_line|#define __wait_event_interruptible_exclusive(wq, condition, ret)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DEFINE_WAIT(__wait);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;prepare_to_wait_exclusive(&amp;wq, &amp;__wait,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;TASK_INTERRUPTIBLE);&t;&t;&bslash;&n;&t;&t;if (condition)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!signal_pending(current)) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;schedule();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;continue;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = -ERESTARTSYS;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;finish_wait(&amp;wq, &amp;__wait);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|wait_event_interruptible_exclusive
mdefine_line|#define wait_event_interruptible_exclusive(wq, condition)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __ret = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(condition))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__wait_event_interruptible_exclusive(wq, condition, __ret);&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
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
comma
r_void
op_star
id|key
)paren
suffix:semicolon
r_int
id|wake_bit_function
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
comma
r_void
op_star
id|key
)paren
suffix:semicolon
DECL|macro|DEFINE_WAIT
mdefine_line|#define DEFINE_WAIT(name)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wait_queue_t name = {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.task&t;&t;= current,&t;&t;&t;&t;&bslash;&n;&t;&t;.func&t;&t;= autoremove_wake_function,&t;&t;&bslash;&n;&t;&t;.task_list&t;= {&t;.next = &amp;name.task_list,&t;&bslash;&n;&t;&t;&t;&t;&t;.prev = &amp;name.task_list,&t;&bslash;&n;&t;&t;&t;&t;},&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|DEFINE_WAIT_BIT
mdefine_line|#define DEFINE_WAIT_BIT(name, word, bit)&t;&t;&t;&t;&bslash;&n;&t;struct wait_bit_queue name = {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.key = __WAIT_BIT_KEY_INITIALIZER(word, bit),&t;&t;&bslash;&n;&t;&t;.wait&t;= {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;.task&t;&t;= current,&t;&t;&t;&bslash;&n;&t;&t;&t;.func&t;&t;= wake_bit_function,&t;&t;&bslash;&n;&t;&t;&t;.task_list&t;=&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;LIST_HEAD_INIT(name.wait.task_list),&t;&bslash;&n;&t;&t;},&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|init_wait
mdefine_line|#define init_wait(wait)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;wait-&gt;task = current;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;wait-&gt;func = autoremove_wake_function;&t;&t;&t;&bslash;&n;&t;&t;INIT_LIST_HEAD(&amp;wait-&gt;task_list);&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/**&n; * wait_on_bit - wait for a bit to be cleared&n; * @word: the word being waited on, a kernel virtual address&n; * @bit: the bit of the word being waited on&n; * @action: the function used to sleep, which may take special actions&n; * @mode: the task state to sleep in&n; *&n; * There is a standard hashed waitqueue table for generic use. This&n; * is the part of the hashtable&squot;s accessor API that waits on a bit.&n; * For instance, if one were to have waiters on a bitflag, one would&n; * call wait_on_bit() in threads waiting for the bit to clear.&n; * One uses wait_on_bit() where one is waiting for the bit to clear,&n; * but has no intention of setting it.&n; */
DECL|function|wait_on_bit
r_static
r_inline
r_int
id|wait_on_bit
c_func
(paren
r_void
op_star
id|word
comma
r_int
id|bit
comma
r_int
(paren
op_star
id|action
)paren
(paren
r_void
op_star
)paren
comma
r_int
id|mode
)paren
(brace
id|DEFINE_WAIT_BIT
c_func
(paren
id|q
comma
id|word
comma
id|bit
)paren
suffix:semicolon
id|wait_queue_head_t
op_star
id|wqh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|bit
comma
id|word
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|wqh
op_assign
id|bit_waitqueue
c_func
(paren
id|word
comma
id|bit
)paren
suffix:semicolon
r_return
id|__wait_on_bit
c_func
(paren
id|wqh
comma
op_amp
id|q
comma
id|word
comma
id|bit
comma
id|action
comma
id|mode
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * wait_on_bit_lock - wait for a bit to be cleared, when wanting to set it&n; * @word: the word being waited on, a kernel virtual address&n; * @bit: the bit of the word being waited on&n; * @action: the function used to sleep, which may take special actions&n; * @mode: the task state to sleep in&n; *&n; * There is a standard hashed waitqueue table for generic use. This&n; * is the part of the hashtable&squot;s accessor API that waits on a bit&n; * when one intends to set it, for instance, trying to lock bitflags.&n; * For instance, if one were to have waiters trying to set bitflag&n; * and waiting for it to clear before setting it, one would call&n; * wait_on_bit() in threads waiting to be able to set the bit.&n; * One uses wait_on_bit_lock() where one is waiting for the bit to&n; * clear with the intention of setting it, and when done, clearing it.&n; */
DECL|function|wait_on_bit_lock
r_static
r_inline
r_int
id|wait_on_bit_lock
c_func
(paren
r_void
op_star
id|word
comma
r_int
id|bit
comma
r_int
(paren
op_star
id|action
)paren
(paren
r_void
op_star
)paren
comma
r_int
id|mode
)paren
(brace
id|DEFINE_WAIT_BIT
c_func
(paren
id|q
comma
id|word
comma
id|bit
)paren
suffix:semicolon
id|wait_queue_head_t
op_star
id|wqh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|bit
comma
id|word
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|wqh
op_assign
id|bit_waitqueue
c_func
(paren
id|word
comma
id|bit
)paren
suffix:semicolon
r_return
id|__wait_on_bit_lock
c_func
(paren
id|wqh
comma
op_amp
id|q
comma
id|word
comma
id|bit
comma
id|action
comma
id|mode
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
