multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This implemenation of synchronization variables is heavily based on&n; * one done by Steve Lord &lt;lord@sgi.com&gt;&n; *&n; * Paul Cassella &lt;pwc@sgi.com&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/sn/sv.h&gt;
multiline_comment|/* Define this to have sv_test() run some simple tests.&n;   kernel_thread() must behave as expected when this is called.  */
DECL|macro|RUN_SV_TEST
macro_line|#undef RUN_SV_TEST
DECL|macro|DEBUG
mdefine_line|#define DEBUG
multiline_comment|/* Set up some macros so sv_wait(), sv_signal(), and sv_broadcast()&n;   can sanity check interrupt state on architectures where we know&n;   how. */
macro_line|#ifdef DEBUG
DECL|macro|SV_DEBUG_INTERRUPT_STATE
mdefine_line|#define SV_DEBUG_INTERRUPT_STATE
macro_line|#ifdef __mips64
DECL|macro|SV_TEST_INTERRUPTS_ENABLED
mdefine_line|#define SV_TEST_INTERRUPTS_ENABLED(flags) ((flags &amp; 0x1) != 0)
DECL|macro|SV_TEST_INTERRUPTS_DISABLED
mdefine_line|#define SV_TEST_INTERRUPTS_DISABLED(flags) ((flags &amp; 0x1) == 0)
DECL|macro|SV_INTERRUPT_TEST_WORKERS
mdefine_line|#define SV_INTERRUPT_TEST_WORKERS 31
macro_line|#elif defined(__ia64)
DECL|macro|SV_TEST_INTERRUPTS_ENABLED
mdefine_line|#define SV_TEST_INTERRUPTS_ENABLED(flags) ((flags &amp; 0x4000) != 0)
DECL|macro|SV_TEST_INTERRUPTS_DISABLED
mdefine_line|#define SV_TEST_INTERRUPTS_DISABLED(flags) ((flags &amp; 0x4000) == 0)
DECL|macro|SV_INTERRUPT_TEST_WORKERS
mdefine_line|#define SV_INTERRUPT_TEST_WORKERS 4 /* simulator&squot;s slow */
macro_line|#else
DECL|macro|SV_DEBUG_INTERRUPT_STATE
macro_line|#undef  SV_DEBUG_INTERRUPT_STATE
DECL|macro|SV_INTERRUPT_TEST_WORKERS
mdefine_line|#define SV_INTERRUPT_TEST_WORKERS 4 /* reasonable? default. */
macro_line|#endif /* __mips64 */
macro_line|#endif /* DEBUG */
multiline_comment|/* XXX FIXME hack hack hack.  Our mips64 tree is from before the&n;   switch to WQ_FLAG_EXCLUSIVE, and our ia64 tree is from after it. */
macro_line|#ifdef TASK_EXCLUSIVE
DECL|macro|EXCLUSIVE_IN_QUEUE
macro_line|#undef EXCLUSIVE_IN_QUEUE
macro_line|#else
DECL|macro|EXCLUSIVE_IN_QUEUE
mdefine_line|#define EXCLUSIVE_IN_QUEUE
DECL|macro|TASK_EXCLUSIVE
mdefine_line|#define TASK_EXCLUSIVE 0 /* for the set_current_state() in sv_wait() */
macro_line|#endif
DECL|function|sv_lock
r_static
r_inline
r_void
id|sv_lock
c_func
(paren
id|sv_t
op_star
id|sv
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sv-&gt;sv_lock
)paren
suffix:semicolon
)brace
DECL|function|sv_unlock
r_static
r_inline
r_void
id|sv_unlock
c_func
(paren
id|sv_t
op_star
id|sv
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|sv-&gt;sv_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* up() is &quot;extern inline&quot;, so we can&squot;t pass its address to sv_wait.&n;   Use this function&squot;s address instead. */
DECL|function|up_wrapper
r_static
r_void
id|up_wrapper
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/* spin_unlock() is sometimes a macro. */
DECL|function|spin_unlock_wrapper
r_static
r_void
id|spin_unlock_wrapper
c_func
(paren
id|spinlock_t
op_star
id|s
)paren
(brace
id|spin_unlock
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX Perhaps sv_wait() should do the switch() each time and avoid&n;   the extra indirection and the need for the _wrapper functions? */
DECL|function|sv_set_mon_type
r_static
r_inline
r_void
id|sv_set_mon_type
c_func
(paren
id|sv_t
op_star
id|sv
comma
r_int
id|type
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|SV_MON_SPIN
suffix:colon
id|sv-&gt;sv_mon_unlock_func
op_assign
(paren
id|sv_mon_unlock_func_t
)paren
id|spin_unlock_wrapper
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SV_MON_SEMA
suffix:colon
id|sv-&gt;sv_mon_unlock_func
op_assign
(paren
id|sv_mon_unlock_func_t
)paren
id|up_wrapper
suffix:semicolon
r_if
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_INTS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_set_mon_type: The monitor lock &quot;
l_string|&quot;cannot be shared with interrupts if it is a &quot;
l_string|&quot;semaphore!&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_BHS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_set_mon_type: The monitor lock &quot;
l_string|&quot;cannot be shared with bottom-halves if it is &quot;
l_string|&quot;a semaphore!&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#if 0 
multiline_comment|/*&n;&t; * If needed, and will need to think about interrupts.  This&n;&t; * may be needed, for example, if someone wants to use sv&squot;s&n;&t; * with something like dev_base; writers need to hold two&n;&t; * locks. &n;&t; */
r_case
id|SV_MON_CUSTOM
suffix:colon
(brace
r_struct
id|sv_mon_custom
op_star
id|c
op_assign
id|lock
suffix:semicolon
id|sv-&gt;sv_mon_unlock_func
op_assign
id|c-&gt;sv_mon_unlock_func
suffix:semicolon
id|sv-&gt;sv_mon_lock
op_assign
id|c-&gt;sv_mon_lock
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_set_mon_type: unknown type %d (0x%x)! &quot;
l_string|&quot;(flags 0x%x)&bslash;n&quot;
comma
id|type
comma
id|type
comma
id|sv-&gt;sv_flags
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sv-&gt;sv_flags
op_or_assign
id|type
suffix:semicolon
)brace
DECL|function|sv_set_ord
r_static
r_inline
r_void
id|sv_set_ord
c_func
(paren
id|sv_t
op_star
id|sv
comma
r_int
id|ord
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ord
)paren
id|ord
op_assign
id|SV_ORDER_DEFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ord
op_ne
id|SV_ORDER_FIFO
op_logical_and
id|ord
op_ne
id|SV_ORDER_LIFO
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;sv_set_ord: unknown order %d (0x%x)! &quot;
comma
id|ord
comma
id|ord
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|sv-&gt;sv_flags
op_or_assign
id|ord
suffix:semicolon
)brace
DECL|function|sv_init
r_void
id|sv_init
c_func
(paren
id|sv_t
op_star
id|sv
comma
id|sv_mon_lock_t
op_star
id|lock
comma
r_int
id|flags
)paren
(brace
r_int
id|ord
op_assign
id|flags
op_amp
id|SV_ORDER_MASK
suffix:semicolon
r_int
id|type
op_assign
id|flags
op_amp
id|SV_MON_MASK
suffix:semicolon
multiline_comment|/* Copy all non-order, non-type flags */
id|sv-&gt;sv_flags
op_assign
(paren
id|flags
op_amp
op_complement
(paren
id|SV_ORDER_MASK
op_or
id|SV_MON_MASK
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sv-&gt;sv_flags
op_amp
(paren
id|SV_INTS
op_or
id|SV_BHS
)paren
)paren
op_eq
(paren
id|SV_INTS
op_or
id|SV_BHS
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_init: do not set both SV_INTS and SV_BHS, only SV_INTS.&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|sv_set_ord
c_func
(paren
id|sv
comma
id|ord
)paren
suffix:semicolon
id|sv_set_mon_type
c_func
(paren
id|sv
comma
id|type
)paren
suffix:semicolon
multiline_comment|/* If lock is NULL, we&squot;ll get it from sv_wait_compat() (and&n;           ignore it in sv_signal() and sv_broadcast()). */
id|sv-&gt;sv_mon_lock
op_assign
id|lock
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|sv-&gt;sv_lock
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sv-&gt;sv_waiters
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The associated lock must be locked on entry.  It is unlocked on return.&n; *&n; * Return values:&n; *&n; * n &lt; 0 : interrupted,  -n jiffies remaining on timeout, or -1 if timeout == 0&n; * n = 0 : timeout expired&n; * n &gt; 0 : sv_signal()&squot;d, n jiffies remaining on timeout, or 1 if timeout == 0&n; */
DECL|function|sv_wait
r_int
r_int
id|sv_wait
c_func
(paren
id|sv_t
op_star
id|sv
comma
r_int
id|sv_wait_flags
comma
r_int
r_int
id|timeout
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef SV_DEBUG_INTERRUPT_STATE
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_INTS
)paren
(brace
r_if
c_cond
(paren
id|SV_TEST_INTERRUPTS_ENABLED
c_func
(paren
id|flags
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_wait: SV_INTS and interrupts &quot;
l_string|&quot;enabled (flags: 0x%lx)&bslash;n&quot;
comma
id|flags
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|SV_TEST_INTERRUPTS_DISABLED
c_func
(paren
id|flags
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sv_wait: !SV_INTS and interrupts &quot;
l_string|&quot;disabled! (flags: 0x%lx)&bslash;n&quot;
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif  /* SV_DEBUG_INTERRUPT_STATE */
id|sv_lock
c_func
(paren
id|sv
)paren
suffix:semicolon
id|sv
op_member_access_from_pointer
id|sv_mon_unlock_func
c_func
(paren
id|sv-&gt;sv_mon_lock
)paren
suffix:semicolon
multiline_comment|/* Add ourselves to the wait queue and set the state before&n;&t; * releasing the sv_lock so as to avoid racing with the&n;&t; * wake_up() in sv_signal() and sv_broadcast(). &n;&t; */
multiline_comment|/* don&squot;t need the _irqsave part, but there is no wq_write_lock() */
id|write_lock_irqsave
c_func
(paren
op_amp
id|sv-&gt;sv_waiters.lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef EXCLUSIVE_IN_QUEUE
id|wait.flags
op_or_assign
id|WQ_FLAG_EXCLUSIVE
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_ORDER_MASK
)paren
(brace
r_case
id|SV_ORDER_FIFO
suffix:colon
id|__add_wait_queue_tail
c_func
(paren
op_amp
id|sv-&gt;sv_waiters
comma
op_amp
id|wait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SV_ORDER_FILO
suffix:colon
id|__add_wait_queue
c_func
(paren
op_amp
id|sv-&gt;sv_waiters
comma
op_amp
id|wait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_wait: unknown order!  (sv: 0x%p, flags: 0x%x)&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|sv
comma
id|sv-&gt;sv_flags
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|sv-&gt;sv_waiters.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sv_wait_flags
op_amp
id|SV_WAIT_SIG
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_EXCLUSIVE
op_or
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
)brace
r_else
id|set_current_state
c_func
(paren
id|TASK_EXCLUSIVE
op_or
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sv-&gt;sv_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_INTS
)paren
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_BHS
)paren
(brace
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timeout
)paren
id|ret
op_assign
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
r_else
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;state
op_ne
id|TASK_RUNNING
)paren
multiline_comment|/* XXX Is this possible? */
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_wait: state not TASK_RUNNING after &quot;
l_string|&quot;schedule().&bslash;n&quot;
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|sv-&gt;sv_waiters
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* Return cases:&n;&t;   - woken by a sv_signal/sv_broadcast&n;&t;   - woken by a signal&n;&t;   - woken by timeout expiring&n;&t;*/
multiline_comment|/* XXX This isn&squot;t really accurate; we may have been woken&n;           before the signal anyway.... */
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
r_return
id|timeout
ques
c_cond
op_minus
id|ret
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|timeout
ques
c_cond
id|ret
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|sv_signal
r_void
id|sv_signal
c_func
(paren
id|sv_t
op_star
id|sv
)paren
(brace
multiline_comment|/* If interrupts can acquire this lock, they can also acquire the&n;&t;   sv_mon_lock, which we must already have to have called this, so&n;&t;   interrupts must be disabled already.  If interrupts cannot&n;&t;   contend for this lock, we don&squot;t have to worry about it. */
macro_line|#ifdef SV_DEBUG_INTERRUPT_STATE
r_if
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_INTS
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SV_TEST_INTERRUPTS_ENABLED
c_func
(paren
id|flags
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_signal: SV_INTS and &quot;
l_string|&quot;interrupts enabled! (flags: 0x%lx)&bslash;n&quot;
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* SV_DEBUG_INTERRUPT_STATE */
id|sv_lock
c_func
(paren
id|sv
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|sv-&gt;sv_waiters
)paren
suffix:semicolon
id|sv_unlock
c_func
(paren
id|sv
)paren
suffix:semicolon
)brace
DECL|function|sv_broadcast
r_void
id|sv_broadcast
c_func
(paren
id|sv_t
op_star
id|sv
)paren
(brace
macro_line|#ifdef SV_DEBUG_INTERRUPT_STATE
r_if
c_cond
(paren
id|sv-&gt;sv_flags
op_amp
id|SV_INTS
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SV_TEST_INTERRUPTS_ENABLED
c_func
(paren
id|flags
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_broadcast: SV_INTS and &quot;
l_string|&quot;interrupts enabled! (flags: 0x%lx)&bslash;n&quot;
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* SV_DEBUG_INTERRUPT_STATE */
id|sv_lock
c_func
(paren
id|sv
)paren
suffix:semicolon
id|wake_up_all
c_func
(paren
op_amp
id|sv-&gt;sv_waiters
)paren
suffix:semicolon
id|sv_unlock
c_func
(paren
id|sv
)paren
suffix:semicolon
)brace
DECL|function|sv_destroy
r_void
id|sv_destroy
c_func
(paren
id|sv_t
op_star
id|sv
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|sv-&gt;sv_lock
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sv_destroy: someone else has sv 0x%p locked!&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|sv
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX Check that the waitqueue is empty? &n;&t;       Mark the sv destroyed?&n;&t;*/
)brace
macro_line|#ifdef RUN_SV_TEST
r_static
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|talkback
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|sem
)paren
suffix:semicolon
DECL|variable|sv
id|sv_t
id|sv
suffix:semicolon
DECL|variable|sv_filo
id|sv_t
id|sv_filo
suffix:semicolon
DECL|function|sv_test_1_w
r_static
r_int
id|sv_test_1_w
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sv_test_1_w: acquiring spinlock 0x%p...&bslash;n&quot;
comma
id|arg
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
(paren
id|spinlock_t
op_star
)paren
id|arg
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_w: spinlock acquired, waking sv_test_1_s.&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_w: sv_spin_wait()&squot;ing.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_spin_wait
c_func
(paren
op_amp
id|sv
comma
id|arg
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_w: talkback.&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_w: exiting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sv_test_1_s
r_static
r_int
id|sv_test_1_s
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sv_test_1_s: waiting for semaphore.&bslash;n&quot;
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_s: semaphore acquired.  Acquiring spinlock.&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
(paren
id|spinlock_t
op_star
)paren
id|arg
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_s: spinlock acquired.  sv_signaling.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_signal
c_func
(paren
op_amp
id|sv
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_s: talkback.&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_1_s: exiting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|count
r_static
r_int
id|count
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|monitor
)paren
suffix:semicolon
DECL|function|sv_test_2_w
r_static
r_int
id|sv_test_2_w
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_int
id|dummy
op_assign
id|count
op_increment
suffix:semicolon
id|sv_t
op_star
id|sv
op_assign
(paren
id|sv_t
op_star
)paren
id|arg
suffix:semicolon
id|down
c_func
(paren
op_amp
id|monitor
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_2_w: thread %d started, sv_waiting.&bslash;n&quot;
comma
id|dummy
)paren
suffix:semicolon
id|sv_sema_wait
c_func
(paren
id|sv
comma
op_amp
id|monitor
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_2_w: thread %d woken, exiting.&bslash;n&quot;
comma
id|dummy
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sv_test_2_s_1
r_static
r_int
id|sv_test_2_s_1
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_int
id|i
suffix:semicolon
id|sv_t
op_star
id|sv
op_assign
(paren
id|sv_t
op_star
)paren
id|arg
suffix:semicolon
id|down
c_func
(paren
op_amp
id|monitor
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sv_test_2_s_1: waking one thread.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_signal
c_func
(paren
id|sv
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;sv_test_2_s_1: signaling and broadcasting again.  Nothing should happen.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_signal
c_func
(paren
id|sv
)paren
suffix:semicolon
id|sv_broadcast
c_func
(paren
id|sv
)paren
suffix:semicolon
id|sv_signal
c_func
(paren
id|sv
)paren
suffix:semicolon
id|sv_broadcast
c_func
(paren
id|sv
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_2_s_1: talkbacking.&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|monitor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sv_test_2_s
r_static
r_int
id|sv_test_2_s
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_int
id|i
suffix:semicolon
id|sv_t
op_star
id|sv
op_assign
(paren
id|sv_t
op_star
)paren
id|arg
suffix:semicolon
id|down
c_func
(paren
op_amp
id|monitor
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sv_test_2_s: waking one thread (should be %d.)&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|sv_signal
c_func
(paren
id|sv
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;sv_test_3_s: waking remaining threads with broadcast.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_broadcast
c_func
(paren
id|sv
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;sv_test_3_s: sending talkback.&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test_3_s: exiting.&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|monitor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|big_test
r_static
r_void
id|big_test
c_func
(paren
id|sv_t
op_star
id|sv
)paren
(brace
r_int
id|i
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;big_test: spawning thread %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|sv_test_2_w
comma
id|sv
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;big_test: spawning first wake-up thread.&bslash;n&quot;
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|sv_test_2_s_1
comma
id|sv
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;big_test: talkback happened.&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OL
l_int|13
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;big_test: spawning thread %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|sv_test_2_w
comma
id|sv
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;big_test: spawning wake-up thread.&bslash;n&quot;
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|sv_test_2_s
comma
id|sv
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
)brace
DECL|variable|int_test_sv
id|sv_t
id|int_test_sv
suffix:semicolon
DECL|variable|int_test_spin
id|spinlock_t
id|int_test_spin
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|int_test_ready
r_int
id|int_test_ready
suffix:semicolon
DECL|variable|irqtestcount
r_static
r_int
id|irqtestcount
suffix:semicolon
DECL|function|interrupt_test_worker
r_static
r_int
id|interrupt_test_worker
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|id
op_assign
op_increment
id|irqtestcount
suffix:semicolon
r_int
id|it
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
comma
id|flags2
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ITW: thread %d started.&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|local_save_flags
c_func
(paren
id|flags2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_mod
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ITW %2d %5d: irqsaving          (%lx)&bslash;n&quot;
comma
id|id
comma
id|it
comma
id|flags2
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|int_test_spin
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ITW %2d %5d: spin_lock_irqing   (%lx)&bslash;n&quot;
comma
id|id
comma
id|it
comma
id|flags2
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|int_test_spin
)paren
suffix:semicolon
)brace
id|local_save_flags
c_func
(paren
id|flags2
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ITW %2d %5d: locked, sv_waiting (%lx).&bslash;n&quot;
comma
id|id
comma
id|it
comma
id|flags2
)paren
suffix:semicolon
id|sv_wait
c_func
(paren
op_amp
id|int_test_sv
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags2
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ITW %2d %5d: wait finished      (%lx), pausing&bslash;n&quot;
comma
id|id
comma
id|it
comma
id|flags2
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|jiffies
op_amp
l_int|0xf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;state
op_ne
id|TASK_RUNNING
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ITW:  current-&gt;state isn&squot;t RUNNING after schedule!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|it
op_increment
suffix:semicolon
)brace
)brace
DECL|function|interrupt_test
r_static
r_void
id|interrupt_test
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;interrupt_test: initing sv.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_init
c_func
(paren
op_amp
id|int_test_sv
comma
op_amp
id|int_test_spin
comma
id|SV_MON_SPIN
op_or
id|SV_INTS
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SV_INTERRUPT_TEST_WORKERS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;interrupt_test: starting test thread %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|interrupt_test_worker
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;interrupt_test: done with init part.&bslash;n&quot;
)paren
suffix:semicolon
id|int_test_ready
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|sv_test
r_int
id|sv_test
c_func
(paren
r_void
)paren
(brace
id|spinlock_t
id|s
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|sv_init
c_func
(paren
op_amp
id|sv
comma
op_amp
id|s
comma
id|SV_MON_SPIN
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test: starting sv_test_1_w.&bslash;n&quot;
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|sv_test_1_w
comma
op_amp
id|s
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test: starting sv_test_1_s.&bslash;n&quot;
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|sv_test_1_s
comma
op_amp
id|s
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test: waiting for talkback.&bslash;n&quot;
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|talkback
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test: talkback happened, sv_destroying.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_destroy
c_func
(paren
op_amp
id|sv
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test: beginning big_test on sv.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_init
c_func
(paren
op_amp
id|sv
comma
op_amp
id|monitor
comma
id|SV_MON_SEMA
)paren
suffix:semicolon
id|big_test
c_func
(paren
op_amp
id|sv
)paren
suffix:semicolon
id|sv_destroy
c_func
(paren
op_amp
id|sv
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test: beginning big_test on sv_filo.&bslash;n&quot;
)paren
suffix:semicolon
id|sv_init
c_func
(paren
op_amp
id|sv_filo
comma
op_amp
id|monitor
comma
id|SV_MON_SEMA
op_or
id|SV_ORDER_FILO
)paren
suffix:semicolon
id|big_test
c_func
(paren
op_amp
id|sv_filo
)paren
suffix:semicolon
id|sv_destroy
c_func
(paren
op_amp
id|sv_filo
)paren
suffix:semicolon
id|interrupt_test
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sv_test: done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sv_test
id|__initcall
c_func
(paren
id|sv_test
)paren
suffix:semicolon
macro_line|#endif /* RUN_SV_TEST */
eof
