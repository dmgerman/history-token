multiline_comment|/*&n; *  include/asm-s390/smplock.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/smplock.h&quot;&n; */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()                spin_is_locked(&amp;kernel_flag)
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu)     &bslash;&n;do {                                       &bslash;&n;&t;if (task-&gt;lock_depth &gt;= 0)         &bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag); &bslash;&n;&t;release_irqlock(cpu);              &bslash;&n;&t;__sti();                           &bslash;&n;} while (0)
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task)        &bslash;&n;do {                                       &bslash;&n;&t;if (task-&gt;lock_depth &gt;= 0)         &bslash;&n;&t;&t;spin_lock(&amp;kernel_flag);   &bslash;&n;} while (0)
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously,&n; * so we only need to worry about other&n; * CPU&squot;s.&n; */
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously,&n; * so we only need to worry about other&n; * CPU&squot;s.&n; */
DECL|function|lock_kernel
r_extern
id|__inline__
r_void
id|lock_kernel
c_func
(paren
r_void
)paren
(brace
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
)brace
DECL|function|unlock_kernel
r_extern
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
