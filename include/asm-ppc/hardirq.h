macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* The __last_jiffy_stamp field is needed to ensure that no decrementer&n; * interrupt is lost on SMP machines. Since on most CPUs it is in the same&n; * cache line as local_irq_count, it is cheap to access and is also used on UP&n; * for uniformity.&n; */
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
multiline_comment|/* set_bit is used on this */
DECL|member|__last_jiffy_stamp
r_int
r_int
id|__last_jiffy_stamp
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|last_jiffy_stamp
mdefine_line|#define last_jiffy_stamp(cpu) __IRQ_STAT((cpu), __last_jiffy_stamp)
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
macro_line|#endif /* __KERNEL__ */
eof
