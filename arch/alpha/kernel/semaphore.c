multiline_comment|/*&n; * Alpha semaphore implementation.&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; * (C) Copyright 1999, 2000 Richard Henderson&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; * This is basically the PPC semaphore scheme ported to use&n; * the Alpha ll/sc sequences, so see the PPC code for&n; * credits.&n; */
multiline_comment|/*&n; * Atomically update sem-&gt;count.&n; * This does the equivalent of the following:&n; *&n; *&t;old_count = sem-&gt;count;&n; *&t;tmp = MAX(old_count, 0) + incr;&n; *&t;sem-&gt;count = tmp;&n; *&t;return old_count;&n; */
DECL|function|__sem_update_count
r_static
r_inline
r_int
id|__sem_update_count
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_int
id|incr
)paren
(brace
r_int
id|old_count
comma
id|tmp
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%0,%2&bslash;n&quot;
l_string|&quot;&t;cmovgt&t;%0,%0,%1&bslash;n&quot;
l_string|&quot;&t;addl&t;%1,%3,%1&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%1,%2&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old_count
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|incr
)paren
comma
l_string|&quot;1&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
)paren
suffix:semicolon
r_return
id|old_count
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform the &quot;down&quot; function.  Return zero for semaphore acquired,&n; * return negative for signalled out of the function.&n; *&n; * If called from down, the return is ignored and the wait loop is&n; * not interruptible.  This means that a task waiting on a semaphore&n; * using &quot;down()&quot; cannot be killed until someone does an &quot;up()&quot; on&n; * the semaphore.&n; *&n; * If called from down_interruptible, the return value gets checked&n; * upon return.  If the return value is negative then the task continues&n; * with the negative value in the return register (it can be tested by&n; * the caller).&n; *&n; * Either form may be used in conjunction with &quot;up()&quot;.&n; */
r_void
DECL|function|__down_failed
id|__down_failed
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down failed(%p)&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Try to get the semaphore.  If the count is &gt; 0, then we&squot;ve&n;&t; * got the semaphore; we decrement count and exit the loop.&n;&t; * If the count is 0 or negative, we set it to -1, indicating&n;&t; * that we are asleep, and then sleep.&n;&t; */
r_while
c_loop
(paren
id|__sem_update_count
c_func
(paren
id|sem
comma
op_minus
l_int|1
)paren
op_le
l_int|0
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
multiline_comment|/*&n;&t; * If there are any more sleepers, wake one of them up so&n;&t; * that it can either get the semaphore, or set count to -1&n;&t; * indicating that there are still processes sleeping.&n;&t; */
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down acquired(%p)&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
)brace
r_int
DECL|function|__down_failed_interruptible
id|__down_failed_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down failed(%p)&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue_exclusive
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|__sem_update_count
c_func
(paren
id|sem
comma
op_minus
l_int|1
)paren
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * A signal is pending - give up trying.&n;&t;&t;&t; * Set sem-&gt;count to 0 if it is negative,&n;&t;&t;&t; * since we are no longer sleeping.&n;&t;&t;&t; */
id|__sem_update_count
c_func
(paren
id|sem
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|tsk
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down %s(%p)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
(paren
id|ret
OL
l_int|0
ques
c_cond
l_string|&quot;interrupted&quot;
suffix:colon
l_string|&quot;acquired&quot;
)paren
comma
id|sem
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_void
DECL|function|__up_wakeup
id|__up_wakeup
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
multiline_comment|/*&n;&t; * Note that we incremented count in up() before we came here,&n;&t; * but that was ineffective since the result was &lt;= 0, and&n;&t; * any negative value of count is equivalent to 0.&n;&t; * This ends up setting count to 1, unless count is now &gt; 0&n;&t; * (i.e. because some other cpu has called up() in the meantime),&n;&t; * in which case we just increment count.&n;&t; */
id|__sem_update_count
c_func
(paren
id|sem
comma
l_int|1
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
r_void
DECL|function|down
id|down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down(%p) &lt;count=%d&gt; from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
comma
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
id|__down
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_int
DECL|function|down_interruptible
id|down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down(%p) &lt;count=%d&gt; from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
comma
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|__down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_int
DECL|function|down_trylock
id|down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|ret
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|ret
op_assign
id|__down_trylock
c_func
(paren
id|sem
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): down_trylock %s from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|ret
ques
c_cond
l_string|&quot;failed&quot;
suffix:colon
l_string|&quot;acquired&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_void
DECL|function|up
id|up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_SEMAPHORE
id|printk
c_func
(paren
l_string|&quot;%s(%d): up(%p) &lt;count=%d&gt; from %p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sem
comma
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
id|__up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
eof
