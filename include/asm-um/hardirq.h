multiline_comment|/* (c) 2004 cw@f00f.org, GPLv2 blah blah */
macro_line|#ifndef __ASM_UM_HARDIRQ_H
DECL|macro|__ASM_UM_HARDIRQ_H
mdefine_line|#define __ASM_UM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/* NOTE: When SMP works again we might want to make this&n; * ____cacheline_aligned or maybe use per_cpu state? --cw */
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
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;
multiline_comment|/* As this would be very strange for UML to get we BUG() after the&n; * printk. */
DECL|function|ack_bad_irq
r_static
r_inline
r_void
id|ack_bad_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unexpected IRQ %02x&bslash;n&quot;
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
macro_line|#endif /* __ASM_UM_HARDIRQ_H */
eof
