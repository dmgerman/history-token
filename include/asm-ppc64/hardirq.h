macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
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
l_string|&quot;illegal vector %d received!&bslash;n&quot;
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
eof
