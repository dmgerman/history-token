multiline_comment|/*&n; * arch/v850/kernel/semaphore.c -- Semaphore support&n; *&n; *  Copyright (C) 1998-2000  IBM Corporation&n; *  Copyright (C) 1999  Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * This file is a copy of the s390 version, arch/s390/kernel/semaphore.c&n; *    Author(s): Martin Schwidefsky&n; * which was derived from the i386 version, linux/arch/i386/kernel/semaphore.c&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/*&n; * Semaphores are implemented using a two-way counter:&n; * The &quot;count&quot; variable is decremented for each process&n; * that tries to acquire the semaphore, while the &quot;sleeping&quot;&n; * variable is a count of such acquires.&n; *&n; * Notably, the inline &quot;up()&quot; and &quot;down()&quot; functions can&n; * efficiently test if they need to do any extra work (up&n; * needs to do something only if count was negative before&n; * the increment operation.&n; *&n; * &quot;sleeping&quot; and the contention routine ordering is&n; * protected by the semaphore spinlock.&n; *&n; * Note that these functions are only called when there is&n; * contention on the lock, and as such all this is the&n; * &quot;non-critical&quot; part of the whole semaphore business. The&n; * critical part is the inline stuff in &lt;asm/semaphore.h&gt;&n; * where we want to avoid any extra jumps and calls.&n; */
multiline_comment|/*&n; * Logic:&n; *  - only on a boundary condition do we need to care. When we go&n; *    from a negative count to a non-negative, we wake people up.&n; *  - when we go from a non-negative count to a negative do we&n; *    (a) synchronize with the &quot;sleeper&quot; count and (b) make sure&n; *    that we&squot;re on the wakeup list before we synchronize so that&n; *    we cannot lose wakeup events.&n; */
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
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
DECL|variable|semaphore_lock
r_static
id|spinlock_t
id|semaphore_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
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
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
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
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|sleepers
op_assign
id|sem-&gt;sleepers
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Add &quot;everybody else&quot; into it. They aren&squot;t&n;&t;&t; * playing, because we own the spinlock.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
op_minus
l_int|1
comma
op_amp
id|sem-&gt;count
)paren
)paren
(brace
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sem-&gt;sleepers
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* us - see -1 above */
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
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
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
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
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
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
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|sleepers
op_assign
id|sem-&gt;sleepers
suffix:semicolon
multiline_comment|/*&n;&t;&t; * With signals pending, this turns into&n;&t;&t; * the trylock failure case - we won&squot;t be&n;&t;&t; * sleeping, and we* can&squot;t get the lock as&n;&t;&t; * it has contention. Just correct the count&n;&t;&t; * and exit.&n;&t;&t; */
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
id|retval
op_assign
op_minus
id|EINTR
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
id|atomic_add
c_func
(paren
id|sleepers
comma
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Add &quot;everybody else&quot; into it. They aren&squot;t&n;&t;&t; * playing, because we own the spinlock. The&n;&t;&t; * &quot;-1&quot; is because we&squot;re still hoping to get&n;&t;&t; * the lock.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
op_minus
l_int|1
comma
op_amp
id|sem-&gt;count
)paren
)paren
(brace
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sem-&gt;sleepers
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* us - see -1 above */
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|semaphore_lock
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
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
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Trylock failed - make sure we correct for&n; * having decremented the count.&n; */
DECL|function|__down_trylock
r_int
id|__down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|sleepers
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|semaphore_lock
comma
id|flags
)paren
suffix:semicolon
id|sleepers
op_assign
id|sem-&gt;sleepers
op_plus
l_int|1
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Add &quot;everybody else&quot; and us into it. They aren&squot;t&n;&t; * playing, because we own the spinlock.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
comma
op_amp
id|sem-&gt;count
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|semaphore_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
