macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|member|idle_timestamp
r_int
r_int
id|idle_timestamp
suffix:semicolon
DECL|member|__nmi_count
r_int
r_int
id|__nmi_count
suffix:semicolon
multiline_comment|/* arch dependent */
DECL|member|apic_timer_irqs
r_int
r_int
id|apic_timer_irqs
suffix:semicolon
multiline_comment|/* arch dependent */
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
r_void
id|ack_bad_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
