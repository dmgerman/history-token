multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/* The __last_jiffy_stamp field is needed to ensure that no decrementer &n; * interrupt is lost on SMP machines. Since on most CPUs it is in the same &n; * cache line as local_irq_count, it is cheap to access and is also used on UP &n; * for uniformity.&n; */
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
multiline_comment|/* set_bit is used on this */
DECL|member|__syscall_count
r_int
r_int
id|__syscall_count
suffix:semicolon
DECL|member|__ksoftirqd_task
r_struct
id|task_struct
op_star
id|__ksoftirqd_task
suffix:semicolon
DECL|member|__last_jiffy_stamp
r_int
r_int
id|__last_jiffy_stamp
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|last_jiffy_stamp
mdefine_line|#define last_jiffy_stamp(cpu) __IRQ_STAT((cpu), __last_jiffy_stamp)
DECL|macro|IRQ_OFFSET
mdefine_line|#define IRQ_OFFSET&t;64
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()&t;((preempt_count() &amp; ~PREEMPT_ACTIVE) &gt;= IRQ_OFFSET)
DECL|macro|in_irq
mdefine_line|#define in_irq&t;&t;in_interrupt
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;(preempt_count() += IRQ_OFFSET)
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;(preempt_count() -= IRQ_OFFSET)
macro_line|#ifndef CONFIG_SMP
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq(irq)&t;barrier()
macro_line|#else /* CONFIG_SMP */
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_HARDIRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
