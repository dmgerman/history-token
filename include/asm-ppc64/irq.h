macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/*&n; * Maximum number of interrupt sources that we can handle.&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;512
multiline_comment|/* this number is used when no interrupt has been assigned */
DECL|macro|NO_IRQ
mdefine_line|#define NO_IRQ&t;&t;&t;(-1)
multiline_comment|/*&n; * These constants are used for passing information about interrupt&n; * signal polarity and level/edge sensing to the low-level PIC chip&n; * drivers.&n; */
DECL|macro|IRQ_SENSE_MASK
mdefine_line|#define IRQ_SENSE_MASK&t;&t;0x1
DECL|macro|IRQ_SENSE_LEVEL
mdefine_line|#define IRQ_SENSE_LEVEL&t;&t;0x1&t;/* interrupt on active level */
DECL|macro|IRQ_SENSE_EDGE
mdefine_line|#define IRQ_SENSE_EDGE&t;&t;0x0&t;/* interrupt triggered by edge */
DECL|macro|IRQ_POLARITY_MASK
mdefine_line|#define IRQ_POLARITY_MASK&t;0x2
DECL|macro|IRQ_POLARITY_POSITIVE
mdefine_line|#define IRQ_POLARITY_POSITIVE&t;0x2&t;/* high level or low-&gt;high edge */
DECL|macro|IRQ_POLARITY_NEGATIVE
mdefine_line|#define IRQ_POLARITY_NEGATIVE&t;0x0&t;/* low level or high-&gt;low edge */
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
r_extern
r_int
r_int
id|real_irq_to_virt_slowpath
c_func
(paren
r_int
r_int
id|real_irq
)paren
suffix:semicolon
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
r_extern
r_int
id|distribute_irqs
suffix:semicolon
r_struct
id|irqaction
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
macro_line|#ifdef CONFIG_IRQSTACKS
multiline_comment|/*&n; * Per-cpu stacks for handling hard and soft interrupts.&n; */
r_extern
r_struct
id|thread_info
op_star
id|hardirq_ctx
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_struct
id|thread_info
op_star
id|softirq_ctx
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_void
id|irq_ctx_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|call_do_softirq
c_func
(paren
r_struct
id|thread_info
op_star
id|tp
)paren
suffix:semicolon
r_extern
r_int
id|call_handle_IRQ_event
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|irqaction
op_star
id|action
comma
r_struct
id|thread_info
op_star
id|tp
)paren
suffix:semicolon
DECL|macro|__ARCH_HAS_DO_SOFTIRQ
mdefine_line|#define __ARCH_HAS_DO_SOFTIRQ
macro_line|#else
DECL|macro|irq_ctx_init
mdefine_line|#define irq_ctx_init()
macro_line|#endif /* CONFIG_IRQSTACKS */
macro_line|#endif /* _ASM_IRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
