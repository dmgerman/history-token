macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|member|__local_irq_count
r_int
r_int
id|__local_irq_count
suffix:semicolon
DECL|member|__local_bh_count
r_int
r_int
id|__local_bh_count
suffix:semicolon
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
multiline_comment|/* waitqueue is too large */
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption&n; * counter.  The bitmask has the following meaning:&n; *&n; * - bits 0-7 are the preemption count (max depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; * - bits 16-24 are the hardirq count (max # of hardirqs: 512)&n; * - bit 26 is the PREEMPT_ACTIVE flag&n; *&n; * We optimize HARDIRQ_BITS for immediate constant, and only&n; * increase it if really needed.&n; */
DECL|macro|PREEMPT_BITS
mdefine_line|#define PREEMPT_BITS&t;8
DECL|macro|SOFTIRQ_BITS
mdefine_line|#define SOFTIRQ_BITS&t;8
macro_line|#if NR_IRQS &gt; 256
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;9
macro_line|#else
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;8
macro_line|#endif
DECL|macro|PREEMPT_SHIFT
mdefine_line|#define PREEMPT_SHIFT&t;0
DECL|macro|SOFTIRQ_SHIFT
mdefine_line|#define SOFTIRQ_SHIFT&t;(PREEMPT_SHIFT + PREEMPT_BITS)
DECL|macro|HARDIRQ_SHIFT
mdefine_line|#define HARDIRQ_SHIFT&t;(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
DECL|macro|__MASK
mdefine_line|#define __MASK(x)&t;((1UL &lt;&lt; (x))-1)
DECL|macro|PREEMPT_MASK
mdefine_line|#define PREEMPT_MASK&t;(__MASK(PREEMPT_BITS) &lt;&lt; PREEMPT_SHIFT)
DECL|macro|HARDIRQ_MASK
mdefine_line|#define HARDIRQ_MASK&t;(__MASK(HARDIRQ_BITS) &lt;&lt; HARDIRQ_SHIFT)
DECL|macro|SOFTIRQ_MASK
mdefine_line|#define SOFTIRQ_MASK&t;(__MASK(SOFTIRQ_BITS) &lt;&lt; SOFTIRQ_SHIFT)
DECL|macro|hardirq_count
mdefine_line|#define hardirq_count()&t;(preempt_count() &amp; HARDIRQ_MASK)
DECL|macro|softirq_count
mdefine_line|#define softirq_count()&t;(preempt_count() &amp; SOFTIRQ_MASK)
DECL|macro|irq_count
mdefine_line|#define irq_count()&t;(preempt_count() &amp; (HARDIRQ_MASK|SOFTIRQ_MASK))
DECL|macro|PREEMPT_OFFSET
mdefine_line|#define PREEMPT_OFFSET&t;(1UL &lt;&lt; PREEMPT_SHIFT)
DECL|macro|SOFTIRQ_OFFSET
mdefine_line|#define SOFTIRQ_OFFSET&t;(1UL &lt;&lt; SOFTIRQ_SHIFT)
DECL|macro|HARDIRQ_OFFSET
mdefine_line|#define HARDIRQ_OFFSET&t;(1UL &lt;&lt; HARDIRQ_SHIFT)
multiline_comment|/*&n; * The hardirq mask has to be large enough to have space&n; * for potentially all IRQ sources in the system nesting&n; * on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
multiline_comment|/*&n; * Are we doing bottom half or hardware interrupt processing?&n; * Are we in a softirq context? Interrupt context?&n; */
DECL|macro|in_irq
mdefine_line|#define in_irq()&t;&t;(hardirq_count())
DECL|macro|in_softirq
mdefine_line|#define in_softirq()&t;&t;(softirq_count())
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()&t;&t;(irq_count())
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock()&t;(!in_interrupt())
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock()&t;do { } while (0)
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;(preempt_count() += HARDIRQ_OFFSET)
macro_line|#ifdef CONFIG_PREEMPT
DECL|macro|in_atomic
macro_line|# define in_atomic()&t;((preempt_count() &amp; ~PREEMPT_ACTIVE) != kernel_locked())
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET (HARDIRQ_OFFSET-1)
macro_line|#else
DECL|macro|in_atomic
macro_line|# define in_atomic()&t;(preempt_count() != 0)
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET HARDIRQ_OFFSET
macro_line|#endif
macro_line|#ifndef CONFIG_SMP
r_extern
id|asmlinkage
r_void
id|__do_softirq
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_count() -= IRQ_EXIT_OFFSET;&t;&t;&t;&bslash;&n;&t;&t;if (!in_interrupt() &amp;&amp; local_softirq_pending())&t;&t;&bslash;&n;&t;&t;&t;__do_softirq();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_enable_no_resched();&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq(irq)&t;barrier()
macro_line|#else
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
macro_line|#endif
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
