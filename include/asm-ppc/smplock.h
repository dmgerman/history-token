multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * &lt;asm/smplock.h&gt;&n; *&n; * Default SMP lock implementation&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_SMPLOCK_H__
DECL|macro|__ASM_SMPLOCK_H__
mdefine_line|#define __ASM_SMPLOCK_H__
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;spin_is_locked(&amp;kernel_flag)
macro_line|#elif defined(CONFIG_PREEMPT)
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;preempt_get_count()
macro_line|#endif
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(task-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag);&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(task-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;spin_lock(&amp;kernel_flag);&t;&bslash;&n;} while (0)
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
macro_line|#ifdef CONFIG_PREEMPT
r_if
c_cond
(paren
id|current-&gt;lock_depth
op_eq
op_minus
l_int|1
)paren
id|spin_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
op_increment
id|current-&gt;lock_depth
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
op_increment
id|current-&gt;lock_depth
)paren
id|spin_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PREEMPT */
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
op_decrement
id|current-&gt;lock_depth
OL
l_int|0
)paren
id|spin_unlock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SMPLOCK_H__ */
macro_line|#endif /* __KERNEL__ */
eof
