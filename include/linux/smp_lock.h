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
r_void
id|__lockfunc
id|get_kernel_lock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__lockfunc
id|put_kernel_lock
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Release/re-acquire global kernel lock for the scheduler&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(tsk) do { &t;&t;&bslash;&n;&t;if (unlikely((tsk)-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;put_kernel_lock();&t;&t;&bslash;&n;} while (0)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(tsk) do {&t;&bslash;&n;&t;if (unlikely((tsk)-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;get_kernel_lock();&t;&t;&bslash;&n;} while (0)
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
mdefine_line|#define reacquire_kernel_lock(task)&t;&t;do { } while(0)
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;&t;&t;1
macro_line|#endif /* CONFIG_LOCK_KERNEL */
macro_line|#endif /* __LINUX_SMPLOCK_H */
eof
