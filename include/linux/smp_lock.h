macro_line|#ifndef __LINUX_SMPLOCK_H
DECL|macro|__LINUX_SMPLOCK_H
mdefine_line|#define __LINUX_SMPLOCK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifdef CONFIG_LOCK_KERNEL
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;(current-&gt;lock_depth &gt;= 0)
r_extern
r_int
id|__lockfunc
id|__reacquire_kernel_lock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__lockfunc
id|__release_kernel_lock
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Release/re-acquire global kernel lock for the scheduler&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(tsk) do { &t;&t;&bslash;&n;&t;if (unlikely((tsk)-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;__release_kernel_lock();&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Non-SMP kernels will never block on the kernel lock,&n; * so we are better off returning a constant zero from&n; * reacquire_kernel_lock() so that the compiler can see&n; * it at compile-time.&n; */
macro_line|#if defined(CONFIG_SMP) &amp;&amp; !defined(CONFIG_PREEMPT_BKL)
DECL|macro|return_value_on_smp
macro_line|# define return_value_on_smp return
macro_line|#else
DECL|macro|return_value_on_smp
macro_line|# define return_value_on_smp
macro_line|#endif
DECL|function|reacquire_kernel_lock
r_static
r_inline
r_int
id|reacquire_kernel_lock
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|task-&gt;lock_depth
op_ge
l_int|0
)paren
)paren
id|return_value_on_smp
id|__reacquire_kernel_lock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kernel_lock
r_extern
r_void
id|__lockfunc
id|lock_kernel
c_func
(paren
r_void
)paren
id|__acquires
c_func
(paren
id|kernel_lock
)paren
suffix:semicolon
DECL|variable|kernel_lock
r_extern
r_void
id|__lockfunc
id|unlock_kernel
c_func
(paren
r_void
)paren
id|__releases
c_func
(paren
id|kernel_lock
)paren
suffix:semicolon
macro_line|#else
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task)&t;&t;do { } while(0)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task)&t;&t;0
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;&t;&t;1
macro_line|#endif /* CONFIG_LOCK_KERNEL */
macro_line|#endif /* __LINUX_SMPLOCK_H */
eof
