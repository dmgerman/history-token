macro_line|#ifndef LINUX_HARDIRQ_H
DECL|macro|LINUX_HARDIRQ_H
mdefine_line|#define LINUX_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption&n; * counter. The bitmask has the following meaning:&n; *&n; * - bits 0-7 are the preemption count (max preemption depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; *&n; * The hardirq count can be overridden per architecture, the default is:&n; *&n; * - bits 16-27 are the hardirq count (max # of hardirqs: 4096)&n; * - ( bit 28 is the PREEMPT_ACTIVE flag. )&n; *&n; * PREEMPT_MASK: 0x000000ff&n; * SOFTIRQ_MASK: 0x0000ff00&n; * HARDIRQ_MASK: 0x0fff0000&n; */
DECL|macro|PREEMPT_BITS
mdefine_line|#define PREEMPT_BITS&t;8
DECL|macro|SOFTIRQ_BITS
mdefine_line|#define SOFTIRQ_BITS&t;8
macro_line|#ifndef HARDIRQ_BITS
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;12
multiline_comment|/*&n; * The hardirq mask has to be large enough to have space for potentially&n; * all IRQ sources in the system nesting on a single CPU.&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
macro_line|#endif
DECL|macro|PREEMPT_SHIFT
mdefine_line|#define PREEMPT_SHIFT&t;0
DECL|macro|SOFTIRQ_SHIFT
mdefine_line|#define SOFTIRQ_SHIFT&t;(PREEMPT_SHIFT + PREEMPT_BITS)
DECL|macro|HARDIRQ_SHIFT
mdefine_line|#define HARDIRQ_SHIFT&t;(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
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
macro_line|#if defined(CONFIG_PREEMPT) &amp;&amp; !defined(CONFIG_PREEMPT_BKL)
DECL|macro|in_atomic
macro_line|# define in_atomic()&t;((preempt_count() &amp; ~PREEMPT_ACTIVE) != kernel_locked())
macro_line|#else
DECL|macro|in_atomic
macro_line|# define in_atomic()&t;((preempt_count() &amp; ~PREEMPT_ACTIVE) != 0)
macro_line|#endif
macro_line|#ifdef CONFIG_PREEMPT
DECL|macro|preemptible
macro_line|# define preemptible()&t;(preempt_count() == 0 &amp;&amp; !irqs_disabled())
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET (HARDIRQ_OFFSET-1)
macro_line|#else
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
DECL|macro|nmi_enter
mdefine_line|#define nmi_enter()&t;&t;irq_enter()
DECL|macro|nmi_exit
mdefine_line|#define nmi_exit()&t;&t;sub_preempt_count(HARDIRQ_OFFSET)
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;add_preempt_count(HARDIRQ_OFFSET)
r_extern
r_void
id|irq_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* LINUX_HARDIRQ_H */
eof
