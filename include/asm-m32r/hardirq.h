macro_line|#ifdef __KERNEL__
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
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
macro_line|#if NR_IRQS &gt; 256
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;9
macro_line|#else
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;8
macro_line|#endif
multiline_comment|/*&n; * The hardirq mask has to be large enough to have&n; * space for potentially all IRQ sources in the system&n; * nesting on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
DECL|function|ack_bad_irq
r_static
r_inline
r_void
id|ack_bad_irq
c_func
(paren
r_int
id|irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;unexpected IRQ trap at vector %02x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_HARDIRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
