macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
DECL|macro|__ARCH_IRQ_STAT
mdefine_line|#define __ARCH_IRQ_STAT 1
multiline_comment|/* Generate a lvalue for a pda member. Should fix softirq.c instead to use&n;   special access macros. This would generate better code. */
DECL|macro|__IRQ_STAT
mdefine_line|#define __IRQ_STAT(cpu,member) (read_pda(me)-&gt;member)
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
multiline_comment|/*&n; * &squot;what should we do if we get a hw irq event on an illegal vector&squot;.&n; * each architecture has to answer this themselves.&n; */
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
l_string|&quot;unexpected IRQ trap at vector %02x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
multiline_comment|/*&n;&t; * Currently unexpected vectors happen only on SMP and APIC.&n;&t; * We _must_ ack these because every local APIC has only N&n;&t; * irq slots per priority level, and a &squot;hanging, unacked&squot; IRQ&n;&t; * holds up an irq slot - in excessive cases (when multiple&n;&t; * unexpected vectors occur) that might lock up the APIC&n;&t; * completely.&n;&t; */
id|ack_APIC_irq
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
