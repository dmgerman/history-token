multiline_comment|/*&n; * BK Id: SCCS/s.hw_irq.h 1.10 05/17/01 18:14:24 cort&n; */
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
id|__sti
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cli
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__restore_flags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__save_flags_ptr
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
id|__sti_end
comma
id|__cli_end
comma
id|__restore_flags_end
comma
id|__save_flags_ptr_end
suffix:semicolon
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags) __save_flags_ptr((unsigned long *)&amp;flags)
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(flags) ({__save_flags(flags);__cli();})
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
