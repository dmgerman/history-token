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
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;12
multiline_comment|/*&n; * The hardirq mask has to be large enough to have&n; * space for potentially nestable IRQ sources in the system&n; * to nest on a single CPU. On Alpha, interrupts are masked at the CPU&n; * by IPL as well as at the system level. We only have 8 IPLs (UNIX PALcode)&n; * so we really only have 8 nestable IRQs, but allow some overhead&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; 16
macro_line|#error HARDIRQ_BITS is too low!
macro_line|#endif
macro_line|#endif /* _ALPHA_HARDIRQ_H */
eof
