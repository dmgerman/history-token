multiline_comment|/*&n; * Semaphore implementation Copyright (c) 2001 Matthew Wilcox, Hewlett-Packard&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * Semaphores are complex as we wish to avoid using two variables.&n; * `count&squot; has multiple roles, depending on its value.  If it is positive&n; * or zero, there are no waiters.  The functions here will never be&n; * called; see &lt;asm/semaphore.h&gt;&n; *&n; * When count is -1 it indicates there is at least one task waiting&n; * for the semaphore.&n; *&n; * When count is less than that, there are &squot;- count - 1&squot; wakeups&n; * pending.  ie if it has value -3, there are 2 wakeups pending.&n; *&n; * Note that these functions are only called when there is contention&n; * on the lock, and as such all this is the &quot;non-critical&quot; part of the&n; * whole semaphore business. The critical part is the inline stuff in&n; * &lt;asm/semaphore.h&gt; where we want to avoid any extra jumps and calls.&n; */
DECL|function|__up
r_void
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|sem-&gt;count
op_decrement
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
DECL|macro|wakers
mdefine_line|#define wakers(count) (-1 - count)
DECL|macro|DOWN_HEAD
mdefine_line|#define DOWN_HEAD&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DECLARE_WAITQUEUE(wait, current);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Note that someone is waiting */&t;&t;&t;&t;&bslash;&n;&t;if (sem-&gt;count == 0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sem-&gt;count = -1;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* protected by the sentry still -- use unlocked version */&t;&bslash;&n;&t;wait.flags = WQ_FLAG_EXCLUSIVE;&t;&t;&t;&t;&t;&bslash;&n;&t;__add_wait_queue_tail(&amp;sem-&gt;wait, &amp;wait);&t;&t;&t;&bslash;&n; lost_race:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irq(&amp;sem-&gt;sentry);&t;&t;&t;&t;&t;&bslash;&n;
DECL|macro|DOWN_TAIL
mdefine_line|#define DOWN_TAIL&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_irq(&amp;sem-&gt;sentry);&t;&t;&t;&t;&t;&bslash;&n;&t;if (wakers(sem-&gt;count) == 0 &amp;&amp; ret == 0)&t;&t;&t;&bslash;&n;&t;&t;goto lost_race;&t;/* Someone stole our wakeup */&t;&t;&bslash;&n;&t;__remove_wait_queue(&amp;sem-&gt;wait, &amp;wait);&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!waitqueue_active(&amp;sem-&gt;wait) &amp;&amp; (sem-&gt;count &lt; 0))&t;&t;&bslash;&n;&t;&t;sem-&gt;count = wakers(sem-&gt;count);
DECL|macro|UPDATE_COUNT
mdefine_line|#define UPDATE_COUNT&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sem-&gt;count += (sem-&gt;count &lt; 0) ? 1 : - 1;
DECL|function|__down
r_void
id|__sched
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|DOWN_HEAD
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* we can _read_ this without the sentry */
r_if
c_cond
(paren
id|sem-&gt;count
op_ne
op_minus
l_int|1
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|DOWN_TAIL
id|UPDATE_COUNT
)brace
DECL|function|__down_interruptible
r_int
id|__sched
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|DOWN_HEAD
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* we can _read_ this without the sentry */
r_if
c_cond
(paren
id|sem-&gt;count
op_ne
op_minus
l_int|1
)paren
r_break
suffix:semicolon
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
)brace
id|DOWN_TAIL
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|UPDATE_COUNT
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
