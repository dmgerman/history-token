macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;8
multiline_comment|/*&n; * The hardirq mask has to be large enough to have space&n; * for potentially all IRQ sources in the system nesting&n; * on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;(preempt_count() += HARDIRQ_OFFSET)
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
mdefine_line|#define irq_exit()                                                      &bslash;&n;        do {                                                            &bslash;&n;                preempt_count() -= IRQ_EXIT_OFFSET;                     &bslash;&n;                if (!in_interrupt() &amp;&amp; local_softirq_pending())         &bslash;&n;                        __do_softirq();                                 &bslash;&n;                preempt_enable_no_resched();                            &bslash;&n;        } while (0)
macro_line|#endif
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
