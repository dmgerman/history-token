multiline_comment|/*&n; * &lt;asm/smplock.h&gt;&n; *&n; * i386 SMP lock implementation&n; */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/current.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;spin_is_locked(&amp;kernel_flag)
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(task-&gt;lock_depth &gt;= 0)) {&t;&bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag);&t;&bslash;&n;&t;&t;if (global_irq_holder == (cpu))&t;&bslash;&n;&t;&t;&t;BUG();&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;} while (0)
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
macro_line|#if 1
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
macro_line|#else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;incl %1&bslash;n&bslash;t&quot;
l_string|&quot;jne 9f&quot;
id|spin_lock_string
l_string|&quot;&bslash;n9:&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
comma
l_string|&quot;=m&quot;
(paren
id|current-&gt;lock_depth
)paren
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
id|current-&gt;lock_depth
OL
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 1
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
macro_line|#else
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;jns 9f&bslash;n&bslash;t&quot;
id|spin_unlock_string
l_string|&quot;&bslash;n9:&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
comma
l_string|&quot;=m&quot;
(paren
id|current-&gt;lock_depth
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
