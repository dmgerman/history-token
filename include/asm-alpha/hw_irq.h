macro_line|#ifndef _ALPHA_HW_IRQ_H
DECL|macro|_ALPHA_HW_IRQ_H
mdefine_line|#define _ALPHA_HW_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|ACTUAL_NR_IRQS
mdefine_line|#define ACTUAL_NR_IRQS&t;alpha_mv.nr_irqs
macro_line|#else
DECL|macro|ACTUAL_NR_IRQS
mdefine_line|#define ACTUAL_NR_IRQS&t;NR_IRQS
macro_line|#endif
macro_line|#endif
eof
