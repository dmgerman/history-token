macro_line|#ifndef _ASM_IA64_HARDIRQ_H
DECL|macro|_ASM_IA64_HARDIRQ_H
mdefine_line|#define _ASM_IA64_HARDIRQ_H
multiline_comment|/*&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * No irq_cpustat_t for IA-64.  The data is held in the per-CPU data structure.&n; */
DECL|macro|__ARCH_IRQ_STAT
mdefine_line|#define __ARCH_IRQ_STAT&t;1
DECL|macro|softirq_pending
mdefine_line|#define softirq_pending(cpu)&t;&t;(cpu_data(cpu)-&gt;softirq_pending)
DECL|macro|syscall_count
mdefine_line|#define syscall_count(cpu)&t;&t;/* unused on IA-64 */
DECL|macro|ksoftirqd_task
mdefine_line|#define ksoftirqd_task(cpu)&t;&t;(cpu_data(cpu)-&gt;ksoftirqd)
DECL|macro|nmi_count
mdefine_line|#define nmi_count(cpu)&t;&t;&t;0
DECL|macro|local_softirq_pending
mdefine_line|#define local_softirq_pending()&t;&t;(local_cpu_data-&gt;softirq_pending)
DECL|macro|local_syscall_count
mdefine_line|#define local_syscall_count()&t;&t;/* unused on IA-64 */
DECL|macro|local_ksoftirqd_task
mdefine_line|#define local_ksoftirqd_task()&t;&t;(local_cpu_data-&gt;ksoftirqd)
DECL|macro|local_nmi_count
mdefine_line|#define local_nmi_count()&t;&t;0
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption counter. The bitmask has the&n; * following meaning:&n; *&n; * - bits 0-7 are the preemption count (max preemption depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; * - bits 16-29 are the hardirq count (max # of hardirqs: 16384)&n; *&n; * - (bit 63 is the PREEMPT_ACTIVE flag---not currently implemented.)&n; *&n; * PREEMPT_MASK: 0x000000ff&n; * SOFTIRQ_MASK: 0x0000ff00&n; * HARDIRQ_MASK: 0x3fff0000&n; */
DECL|macro|PREEMPT_BITS
mdefine_line|#define PREEMPT_BITS&t;8
DECL|macro|SOFTIRQ_BITS
mdefine_line|#define SOFTIRQ_BITS&t;8
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;14
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
mdefine_line|#define irq_count()&t;(preempt_count() &amp; (HARDIRQ_MASK | SOFTIRQ_MASK))
DECL|macro|PREEMPT_OFFSET
mdefine_line|#define PREEMPT_OFFSET&t;(1UL &lt;&lt; PREEMPT_SHIFT)
DECL|macro|SOFTIRQ_OFFSET
mdefine_line|#define SOFTIRQ_OFFSET&t;(1UL &lt;&lt; SOFTIRQ_SHIFT)
DECL|macro|HARDIRQ_OFFSET
mdefine_line|#define HARDIRQ_OFFSET&t;(1UL &lt;&lt; HARDIRQ_SHIFT)
multiline_comment|/*&n; * The hardirq mask has to be large enough to have space for potentially all IRQ sources&n; * in the system nesting on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
multiline_comment|/*&n; * Are we doing bottom half or hardware interrupt processing?&n; * Are we in a softirq context?&n; * Interrupt context?&n; */
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
macro_line|# define in_atomic()&t;&t;((preempt_count() &amp; ~PREEMPT_ACTIVE) != kernel_locked())
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET (HARDIRQ_OFFSET-1)
macro_line|#else
DECL|macro|in_atomic
macro_line|# define in_atomic()&t;&t;(preempt_count() != 0)
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET HARDIRQ_OFFSET
macro_line|#endif
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_count() -= IRQ_EXIT_OFFSET;&t;&t;&bslash;&n;&t;&t;if (!in_interrupt() &amp;&amp; local_softirq_pending())&t;&bslash;&n;&t;&t;&t;do_softirq();&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_enable_no_resched();&t;&t;&t;&bslash;&n;} while (0)
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|synchronize_irq
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#else
DECL|macro|synchronize_irq
macro_line|# define synchronize_irq(irq)&t;barrier()
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* _ASM_IA64_HARDIRQ_H */
eof
