macro_line|#ifndef __LINUX_SMPLOCK_H
DECL|macro|__LINUX_SMPLOCK_H
mdefine_line|#define __LINUX_SMPLOCK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if !defined(CONFIG_SMP) &amp;&amp; !defined(CONFIG_PREEMPT)
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task)&t;&t;do { } while(0)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task)&t;&t;do { } while(0)
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked() 1
macro_line|#else
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/current.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;(current-&gt;lock_depth &gt;= 0)
DECL|macro|get_kernel_lock
mdefine_line|#define get_kernel_lock()&t;spin_lock(&amp;kernel_flag)
DECL|macro|put_kernel_lock
mdefine_line|#define put_kernel_lock()&t;spin_unlock(&amp;kernel_flag)
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(task-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;put_kernel_lock();&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(task-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;get_kernel_lock();&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously,&n; * so we only need to worry about other&n; * CPU&squot;s.&n; */
DECL|function|lock_kernel
r_static
id|__inline__
r_void
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
op_logical_neg
id|depth
)paren
id|get_kernel_lock
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
r_static
id|__inline__
r_void
id|unlock_kernel
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;lock_depth
OL
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|current-&gt;lock_depth
OL
l_int|0
)paren
id|put_kernel_lock
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif
eof
