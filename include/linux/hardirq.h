macro_line|#ifndef LINUX_HARDIRQ_H
DECL|macro|LINUX_HARDIRQ_H
mdefine_line|#define LINUX_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PREEPT
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|__IRQ_MASK
mdefine_line|#define __IRQ_MASK(x)&t;((1UL &lt;&lt; (x))-1)
DECL|macro|PREEMPT_MASK
mdefine_line|#define PREEMPT_MASK&t;(__IRQ_MASK(PREEMPT_BITS) &lt;&lt; PREEMPT_SHIFT)
DECL|macro|HARDIRQ_MASK
mdefine_line|#define HARDIRQ_MASK&t;(__IRQ_MASK(HARDIRQ_BITS) &lt;&lt; HARDIRQ_SHIFT)
DECL|macro|SOFTIRQ_MASK
mdefine_line|#define SOFTIRQ_MASK&t;(__IRQ_MASK(SOFTIRQ_BITS) &lt;&lt; SOFTIRQ_SHIFT)
DECL|macro|PREEMPT_OFFSET
mdefine_line|#define PREEMPT_OFFSET&t;(1UL &lt;&lt; PREEMPT_SHIFT)
DECL|macro|SOFTIRQ_OFFSET
mdefine_line|#define SOFTIRQ_OFFSET&t;(1UL &lt;&lt; SOFTIRQ_SHIFT)
DECL|macro|HARDIRQ_OFFSET
mdefine_line|#define HARDIRQ_OFFSET&t;(1UL &lt;&lt; HARDIRQ_SHIFT)
DECL|macro|hardirq_count
mdefine_line|#define hardirq_count()&t;(preempt_count() &amp; HARDIRQ_MASK)
DECL|macro|softirq_count
mdefine_line|#define softirq_count()&t;(preempt_count() &amp; SOFTIRQ_MASK)
DECL|macro|irq_count
mdefine_line|#define irq_count()&t;(preempt_count() &amp; (HARDIRQ_MASK | SOFTIRQ_MASK))
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
macro_line|#ifdef CONFIG_PREEMPT
DECL|macro|in_atomic
macro_line|# define in_atomic()&t;((preempt_count() &amp; ~PREEMPT_ACTIVE) != kernel_locked())
DECL|macro|preemptible
macro_line|# define preemptible()&t;(preempt_count() == 0 &amp;&amp; !irqs_disabled())
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET (HARDIRQ_OFFSET-1)
macro_line|#else
DECL|macro|in_atomic
macro_line|# define in_atomic()&t;(preempt_count() != 0)
DECL|macro|preemptible
macro_line|# define preemptible()&t;0
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET HARDIRQ_OFFSET
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
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
macro_line|#else
DECL|macro|synchronize_irq
macro_line|# define synchronize_irq(irq)&t;barrier()
macro_line|#endif
macro_line|#endif /* LINUX_HARDIRQ_H */
eof
