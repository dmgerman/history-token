multiline_comment|/*&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; *&n; * Use inline IRQs where possible - Anton Blanchard &lt;anton@au.ibm.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC64_HW_IRQ_H
DECL|macro|_PPC64_HW_IRQ_H
mdefine_line|#define _PPC64_HW_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
r_int
id|timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ppc_irq_dispatch_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
r_extern
r_int
r_int
id|local_get_flags
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|local_irq_disable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|local_irq_restore
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;local_irq_restore(1)
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;((flags) = local_get_flags())
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)&t;((flags) = local_irq_disable())
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;(local_get_flags() == 0)
macro_line|#else
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;((flags) = mfmsr())
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags) do { &bslash;&n;&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;); &bslash;&n;&t;__mtmsrd((flags), 1); &bslash;&n;} while(0)
DECL|function|local_irq_disable
r_static
r_inline
r_void
id|local_irq_disable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|msr
suffix:semicolon
id|msr
op_assign
id|mfmsr
c_func
(paren
)paren
suffix:semicolon
id|__mtmsrd
c_func
(paren
id|msr
op_amp
op_complement
id|MSR_EE
comma
l_int|1
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|local_irq_enable
r_static
r_inline
r_void
id|local_irq_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|msr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|msr
op_assign
id|mfmsr
c_func
(paren
)paren
suffix:semicolon
id|__mtmsrd
c_func
(paren
id|msr
op_or
id|MSR_EE
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|__do_save_and_cli
r_static
r_inline
r_void
id|__do_save_and_cli
c_func
(paren
r_int
r_int
op_star
id|flags
)paren
(brace
r_int
r_int
id|msr
suffix:semicolon
id|msr
op_assign
id|mfmsr
c_func
(paren
)paren
suffix:semicolon
op_star
id|flags
op_assign
id|msr
suffix:semicolon
id|__mtmsrd
c_func
(paren
id|msr
op_amp
op_complement
id|MSR_EE
comma
l_int|1
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)          __do_save_and_cli(&amp;flags)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&t;&bslash;&n;&t;!(flags &amp; MSR_EE);&t;&t;&t;&bslash;&n;})
macro_line|#endif /* CONFIG_PPC_ISERIES */
DECL|macro|mask_irq
mdefine_line|#define mask_irq(irq) ({if (irq_desc[irq].handler &amp;&amp; irq_desc[irq].handler-&gt;disable) irq_desc[irq].handler-&gt;disable(irq);})
DECL|macro|unmask_irq
mdefine_line|#define unmask_irq(irq) ({if (irq_desc[irq].handler &amp;&amp; irq_desc[irq].handler-&gt;enable) irq_desc[irq].handler-&gt;enable(irq);})
DECL|macro|ack_irq
mdefine_line|#define ack_irq(irq) ({if (irq_desc[irq].handler &amp;&amp; irq_desc[irq].handler-&gt;ack) irq_desc[irq].handler-&gt;ack(irq);})
multiline_comment|/* Should we handle this via lost interrupts and IPIs or should we don&squot;t care like&n; * we do now ? --BenH.&n; */
r_struct
id|hw_interrupt_type
suffix:semicolon
DECL|function|hw_resend_irq
r_static
r_inline
r_void
id|hw_resend_irq
c_func
(paren
r_struct
id|hw_interrupt_type
op_star
id|h
comma
r_int
r_int
id|i
)paren
(brace
)brace
macro_line|#endif /* _PPC64_HW_IRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
