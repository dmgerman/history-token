multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_HW_IRQ_H
DECL|macro|_PPC_HW_IRQ_H
mdefine_line|#define _PPC_HW_IRQ_H
r_extern
r_int
r_int
id|timer_interrupt_intercept
suffix:semicolon
r_extern
r_int
r_int
id|do_IRQ_intercept
suffix:semicolon
r_extern
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
DECL|macro|INLINE_IRQS
mdefine_line|#define INLINE_IRQS
macro_line|#ifdef INLINE_IRQS
DECL|macro|mfmsr
mdefine_line|#define mfmsr()&t;&t;({unsigned int rval; &bslash;&n;&t;&t;&t;asm volatile(&quot;mfmsr %0&quot; : &quot;=r&quot; (rval)); rval;})
DECL|macro|mtmsr
mdefine_line|#define mtmsr(v)&t;asm volatile(&quot;mtmsr %0&quot; : : &quot;r&quot; (v))
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;((flags) = mfmsr())
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;mtmsr(flags)
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
id|mtmsr
c_func
(paren
id|msr
op_amp
op_complement
id|MSR_EE
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
id|mtmsr
c_func
(paren
id|msr
op_or
id|MSR_EE
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
id|mtmsr
c_func
(paren
id|msr
op_amp
op_complement
id|MSR_EE
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
macro_line|#else
r_extern
r_void
id|local_irq_enable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
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
r_extern
r_void
id|local_save_flags_ptr
c_func
(paren
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|local_irq_enable_end
comma
id|local_irq_disable_end
comma
id|local_irq_restore_end
comma
id|local_save_flags_ptr_end
suffix:semicolon
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags) local_save_flags_ptr((unsigned long *)&amp;flags)
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags) ({local_save_flags(flags);local_irq_disable();})
macro_line|#endif
r_extern
r_void
id|do_lost_interrupts
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
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
macro_line|#endif /* _PPC_HW_IRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
