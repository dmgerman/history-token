multiline_comment|/*&n; * &lt;asm/smplock.h&gt;&n; *&n; * Default SMP lock implementation&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_extern
id|spinlock_t
id|kernel_flag
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;&t;&bslash;&n;&t;(spin_is_locked(&amp;kernel_flag) &amp;&amp;&bslash;&n;&t; (current-&gt;lock_depth &gt;= 0))
macro_line|#else
macro_line|#ifdef CONFIG_PREEMPT
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;&t;preempt_get_count()
macro_line|#else
DECL|macro|kernel_locked
mdefine_line|#define kernel_locked()&t;&t;&t;1
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Release global kernel lock and global interrupt lock&n; */
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(task-&gt;lock_depth &gt;= 0)) {&t;&bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag);&t;&bslash;&n;&t;&t;release_irqlock(cpu);&t;&t;&bslash;&n;&t;&t;__sti();&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Re-acquire the kernel lock&n; */
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(task-&gt;lock_depth &gt;= 0))&t;&bslash;&n;&t;&t;spin_lock(&amp;kernel_flag);&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Getting the big kernel lock.&n; *&n; * This cannot happen asynchronously,&n; * so we only need to worry about other&n; * CPU&squot;s.&n; */
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!++current-&gt;lock_depth)&t;&t;&bslash;&n;&t;&t;spin_lock(&amp;kernel_flag);&t;&bslash;&n;} while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (--current-&gt;lock_depth &lt; 0)&t;&t;&bslash;&n;&t;&t;spin_unlock(&amp;kernel_flag);&t;&bslash;&n;} while(0)
eof
