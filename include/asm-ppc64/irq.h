macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * Maximum number of interrupt sources that we can handle.&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;512
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* this number is used when no interrupt has been assigned */
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ&t;&t;&t;(-1)
DECL|macro|get_irq_desc
mdefine_line|#define get_irq_desc(irq) (&amp;irq_desc[(irq)])
multiline_comment|/* Define a way to iterate across irqs. */
DECL|macro|for_each_irq
mdefine_line|#define for_each_irq(i) &bslash;&n;&t;for ((i) = 0; (i) &lt; NR_IRQS; ++(i))
multiline_comment|/* Interrupt numbers are virtual in case they are sparsely&n; * distributed by the hardware.&n; */
r_extern
r_int
r_int
id|virt_irq_to_real_map
(braket
id|NR_IRQS
)braket
suffix:semicolon
multiline_comment|/* Create a mapping for a real_irq if it doesn&squot;t already exist.&n; * Return the virtual irq as a convenience.&n; */
r_int
id|virt_irq_create_mapping
c_func
(paren
r_int
r_int
id|real_irq
)paren
suffix:semicolon
r_void
id|virt_irq_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|virt_irq_to_real
r_static
r_inline
r_int
r_int
id|virt_irq_to_real
c_func
(paren
r_int
r_int
id|virt_irq
)paren
(brace
r_return
id|virt_irq_to_real_map
(braket
id|virt_irq
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Because many systems have two overlapping names spaces for&n; * interrupts (ISA and XICS for example), and the ISA interrupts&n; * have historically not been easy to renumber, we allow ISA&n; * interrupts to take values 0 - 15, and shift up the remaining&n; * interrupts by 0x10.&n; */
DECL|macro|NUM_ISA_INTERRUPTS
mdefine_line|#define NUM_ISA_INTERRUPTS&t;0x10
r_extern
r_int
id|__irq_offset_value
suffix:semicolon
DECL|function|irq_offset_up
r_static
r_inline
r_int
id|irq_offset_up
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
op_plus
id|__irq_offset_value
suffix:semicolon
)brace
DECL|function|irq_offset_down
r_static
r_inline
r_int
id|irq_offset_down
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
op_minus
id|__irq_offset_value
suffix:semicolon
)brace
DECL|function|irq_offset_value
r_static
r_inline
r_int
id|irq_offset_value
c_func
(paren
r_void
)paren
(brace
r_return
id|__irq_offset_value
suffix:semicolon
)brace
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
r_struct
id|irqaction
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_int
id|handle_IRQ_event
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
