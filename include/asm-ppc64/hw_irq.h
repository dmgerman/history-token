multiline_comment|/*&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; *&n; * Use inline IRQs where possible - Anton Blanchard &lt;anton@au.ibm.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC64_HW_IRQ_H
DECL|macro|_PPC64_HW_IRQ_H
mdefine_line|#define _PPC64_HW_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#ifdef CONFIG_PPC_ISERIES
r_extern
r_void
id|__no_use_sti
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__no_use_cli
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__no_use_restore_flags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__no_use_save_flags
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__no_use_set_lost
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__no_lpq_restore_flags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;&t;&t;__no_use_cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;&t;&t;__no_use_sti()
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;((flags) = __no_use_save_flags())
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;__no_use_restore_flags((unsigned long)flags)
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)&t;({local_save_flags(flags);local_irq_disable();})
macro_line|#else
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;((flags) = mfmsr())
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;__mtmsrd((flags), 1)
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
