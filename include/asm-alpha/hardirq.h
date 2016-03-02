macro_line|#ifndef _ALPHA_HARDIRQ_H
DECL|macro|_ALPHA_HARDIRQ_H
mdefine_line|#define _ALPHA_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
multiline_comment|/* entry.S is sensitive to the offsets of these fields */
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|member|__syscall_count
r_int
r_int
id|__syscall_count
suffix:semicolon
DECL|member|idle_timestamp
r_int
r_int
id|idle_timestamp
suffix:semicolon
DECL|member|__ksoftirqd_task
r_struct
id|task_struct
op_star
id|__ksoftirqd_task
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption&n; * counter. The bitmask has the following meaning:&n; *&n; * - bits 0-7 are the preemption count (max preemption depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; * - bits 16-27 are the hardirq count (max # of hardirqs: 4096)&n; *&n; * - ( bit 30 is the PREEMPT_ACTIVE flag. )&n; *&n; * PREEMPT_MASK: 0x000000ff&n; * SOFTIRQ_MASK: 0x0000ff00&n; * HARDIRQ_MASK: 0x0fff0000&n; */
DECL|macro|PREEMPT_BITS
mdefine_line|#define PREEMPT_BITS&t;8
DECL|macro|SOFTIRQ_BITS
mdefine_line|#define SOFTIRQ_BITS&t;8
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;12
DECL|macro|PREEMPT_SHIFT
mdefine_line|#define PREEMPT_SHIFT&t;0
DECL|macro|SOFTIRQ_SHIFT
mdefine_line|#define SOFTIRQ_SHIFT&t;(PREEMPT_SHIFT + PREEMPT_BITS)
DECL|macro|HARDIRQ_SHIFT
mdefine_line|#define HARDIRQ_SHIFT&t;(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
multiline_comment|/*&n; * The hardirq mask has to be large enough to have&n; * space for potentially nestable IRQ sources in the system&n; * to nest on a single CPU. On Alpha, interrupts are masked at the CPU&n; * by IPL as well as at the system level. We only have 8 IPLs (UNIX PALcode)&n; * so we really only have 8 nestable IRQs, but allow some overhead&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; 16
macro_line|#error HARDIRQ_BITS is too low!
macro_line|#endif
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;(preempt_count() += HARDIRQ_OFFSET)
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_count() -= IRQ_EXIT_OFFSET;&t;&t;&bslash;&n;&t;&t;if (!in_interrupt() &amp;&amp;&t;&t;&t;&t;&bslash;&n;&t;&t;    softirq_pending(smp_processor_id()))&t;&bslash;&n;&t;&t;&t;do_softirq();&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_enable_no_resched();&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* _ALPHA_HARDIRQ_H */
eof
