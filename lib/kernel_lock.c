multiline_comment|/*&n; * lib/kernel_lock.c&n; *&n; * This is the traditional BKL - big kernel lock. Largely&n; * relegated to obsolescense, but used by various less&n; * important (or lazy) subsystems.&n; */
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#if defined(CONFIG_PREEMPT) &amp;&amp; defined(__smp_processor_id) &amp;&amp; &bslash;&n;&t;&t;defined(CONFIG_DEBUG_PREEMPT)
multiline_comment|/*&n; * Debugging check.&n; */
DECL|function|smp_processor_id
r_int
r_int
id|smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|preempt_count
op_assign
id|preempt_count
c_func
(paren
)paren
suffix:semicolon
r_int
id|this_cpu
op_assign
id|__smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|cpumask_t
id|this_mask
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|preempt_count
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|irqs_disabled
c_func
(paren
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Kernel threads bound to a single CPU can safely use&n;&t; * smp_processor_id():&n;&t; */
id|this_mask
op_assign
id|cpumask_of_cpu
c_func
(paren
id|this_cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_equal
c_func
(paren
id|current-&gt;cpus_allowed
comma
id|this_mask
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * It is valid to assume CPU-locality during early bootup:&n;&t; */
r_if
c_cond
(paren
id|system_state
op_ne
id|SYSTEM_RUNNING
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Avoid recursion:&n;&t; */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|printk_ratelimit
c_func
(paren
)paren
)paren
r_goto
id|out_enable
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BUG: using smp_processor_id() in preemptible [%08x] code: %s/%d&bslash;n&quot;
comma
id|preempt_count
c_func
(paren
)paren
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;caller is %s&bslash;n&quot;
comma
(paren
r_int
)paren
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
id|out_enable
suffix:colon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|this_cpu
suffix:semicolon
)brace
DECL|variable|smp_processor_id
id|EXPORT_SYMBOL
c_func
(paren
id|smp_processor_id
)paren
suffix:semicolon
macro_line|#endif /* PREEMPT &amp;&amp; __smp_processor_id &amp;&amp; DEBUG_PREEMPT */
macro_line|#ifdef CONFIG_PREEMPT_BKL
multiline_comment|/*&n; * The &squot;big kernel semaphore&squot;&n; *&n; * This mutex is taken and released recursively by lock_kernel()&n; * and unlock_kernel().  It is transparently dropped and reaquired&n; * over schedule().  It is used to protect legacy code that hasn&squot;t&n; * been migrated to a proper locking design yet.&n; *&n; * Note: code locked by this semaphore will only be serialized against&n; * other code using the same locking facility. The code guarantees that&n; * the task remains on the same CPU.&n; *&n; * Don&squot;t use in new code.&n; */
DECL|variable|kernel_sem
id|DECLARE_MUTEX
c_func
(paren
id|kernel_sem
)paren
suffix:semicolon
multiline_comment|/*&n; * Re-acquire the kernel semaphore.&n; *&n; * This function is called with preemption off.&n; *&n; * We are executing in schedule() so the code must be extremely careful&n; * about recursion, both due to the down() and due to the enabling of&n; * preemption. schedule() will re-check the preemption flag after&n; * reacquiring the semaphore.&n; */
DECL|function|__reacquire_kernel_lock
r_int
id|__lockfunc
id|__reacquire_kernel_lock
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|current
suffix:semicolon
r_int
id|saved_lock_depth
op_assign
id|task-&gt;lock_depth
suffix:semicolon
id|BUG_ON
c_func
(paren
id|saved_lock_depth
OL
l_int|0
)paren
suffix:semicolon
id|task-&gt;lock_depth
op_assign
op_minus
l_int|1
suffix:semicolon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|kernel_sem
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|task-&gt;lock_depth
op_assign
id|saved_lock_depth
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__release_kernel_lock
r_void
id|__lockfunc
id|__release_kernel_lock
c_func
(paren
r_void
)paren
(brace
id|up
c_func
(paren
op_amp
id|kernel_sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Getting the big kernel semaphore.&n; */
DECL|function|lock_kernel
r_void
id|__lockfunc
id|lock_kernel
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|current
suffix:semicolon
r_int
id|depth
op_assign
id|task-&gt;lock_depth
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|depth
)paren
)paren
multiline_comment|/*&n;&t;&t; * No recursion worries - we set up lock_depth _after_&n;&t;&t; */
id|down
c_func
(paren
op_amp
id|kernel_sem
)paren
suffix:semicolon
id|task-&gt;lock_depth
op_assign
id|depth
suffix:semicolon
)brace
DECL|function|unlock_kernel
r_void
id|__lockfunc
id|unlock_kernel
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|current
suffix:semicolon
id|BUG_ON
c_func
(paren
id|task-&gt;lock_depth
OL
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_decrement
id|task-&gt;lock_depth
OL
l_int|0
)paren
)paren
id|up
c_func
(paren
op_amp
id|kernel_sem
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * The &squot;big kernel lock&squot;&n; *&n; * This spinlock is taken and released recursively by lock_kernel()&n; * and unlock_kernel().  It is transparently dropped and reaquired&n; * over schedule().  It is used to protect legacy code that hasn&squot;t&n; * been migrated to a proper locking design yet.&n; *&n; * Don&squot;t use in new code.&n; */
r_static
id|__cacheline_aligned_in_smp
id|DEFINE_SPINLOCK
c_func
(paren
id|kernel_flag
)paren
suffix:semicolon
multiline_comment|/*&n; * Acquire/release the underlying lock from the scheduler.&n; *&n; * This is called with preemption disabled, and should&n; * return an error value if it cannot get the lock and&n; * TIF_NEED_RESCHED gets set.&n; *&n; * If it successfully gets the lock, it should increment&n; * the preemption count like any spinlock does.&n; *&n; * (This works on UP too - _raw_spin_trylock will never&n; * return false in that case)&n; */
DECL|function|__reacquire_kernel_lock
r_int
id|__lockfunc
id|__reacquire_kernel_lock
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|_raw_spin_trylock
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
(brace
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
)brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__release_kernel_lock
r_void
id|__lockfunc
id|__release_kernel_lock
c_func
(paren
r_void
)paren
(brace
id|_raw_spin_unlock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the BKL spinlocks - we try to be polite about preemption. &n; * If SMP is not on (ie UP preemption), this all goes away because the&n; * _raw_spin_trylock() will always succeed.&n; */
macro_line|#ifdef CONFIG_PREEMPT
DECL|function|__lock_kernel
r_static
r_inline
r_void
id|__lock_kernel
c_func
(paren
r_void
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|_raw_spin_trylock
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * If preemption was disabled even before this&n;&t;&t; * was called, there&squot;s nothing we can be polite&n;&t;&t; * about - just spin.&n;&t;&t; */
r_if
c_cond
(paren
id|preempt_count
c_func
(paren
)paren
OG
l_int|1
)paren
(brace
id|_raw_spin_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Otherwise, let&squot;s wait for the kernel lock&n;&t;&t; * with preemption enabled..&n;&t;&t; */
r_do
(brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|spin_is_locked
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|_raw_spin_trylock
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
multiline_comment|/*&n; * Non-preemption case - just get the spinlock&n; */
DECL|function|__lock_kernel
r_static
r_inline
r_void
id|__lock_kernel
c_func
(paren
r_void
)paren
(brace
id|_raw_spin_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|__unlock_kernel
r_static
r_inline
r_void
id|__unlock_kernel
c_func
(paren
r_void
)paren
(brace
id|_raw_spin_unlock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously, so we only need to&n; * worry about other CPU&squot;s.&n; */
DECL|function|lock_kernel
r_void
id|__lockfunc
id|lock_kernel
c_func
(paren
r_void
)paren
(brace
r_int
id|depth
op_assign
id|current-&gt;lock_depth
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|depth
)paren
)paren
id|__lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;lock_depth
op_assign
id|depth
suffix:semicolon
)brace
DECL|function|unlock_kernel
r_void
id|__lockfunc
id|unlock_kernel
c_func
(paren
r_void
)paren
(brace
id|BUG_ON
c_func
(paren
id|current-&gt;lock_depth
OL
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_decrement
id|current-&gt;lock_depth
OL
l_int|0
)paren
)paren
id|__unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|lock_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|lock_kernel
)paren
suffix:semicolon
DECL|variable|unlock_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|unlock_kernel
)paren
suffix:semicolon
eof
