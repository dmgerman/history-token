multiline_comment|/*&n; * &lt;asm/smplock.h&gt;&n; *&n; * Default SMP lock implementation&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;spin_is_locked(&amp;kernel_flag)
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|function|release_kernel_lock
r_static
id|__inline__
r_void
id|release_kernel_lock
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
id|spin_unlock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|function|reacquire_kernel_lock
r_static
id|__inline__
r_void
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
id|spin_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
)brace
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
macro_line|#endif
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
eof
