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
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu) &bslash;&n;do { &bslash;&n;&t;if (task-&gt;lock_depth &gt;= 0) &bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag); &bslash;&n;&t;release_irqlock(cpu); &bslash;&n;&t;__sti(); &bslash;&n;} while (0)
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task) &bslash;&n;do { &bslash;&n;&t;if (task-&gt;lock_depth &gt;= 0) &bslash;&n;&t;&t;spin_lock(&amp;kernel_flag); &bslash;&n;} while (0)
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously,&n; * so we only need to worry about other&n; * CPU&squot;s.&n; */
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel() &bslash;&n;do { &bslash;&n;&t;if (!++current-&gt;lock_depth) &bslash;&n;&t;&t;spin_lock(&amp;kernel_flag); &bslash;&n;} while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel() &bslash;&n;do { &bslash;&n;&t;if (--current-&gt;lock_depth &lt; 0) &bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag); &bslash;&n;} while(0)
eof
