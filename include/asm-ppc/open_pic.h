multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; *  arch/ppc/kernel/open_pic.h -- OpenPIC Interrupt Handling&n; *&n; *  Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; *  &n; */
macro_line|#ifndef _PPC_KERNEL_OPEN_PIC_H
DECL|macro|_PPC_KERNEL_OPEN_PIC_H
mdefine_line|#define _PPC_KERNEL_OPEN_PIC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
DECL|macro|OPENPIC_SIZE
mdefine_line|#define OPENPIC_SIZE&t;0x40000
multiline_comment|/*&n; *  Non-offset&squot;ed vector numbers&n; */
DECL|macro|OPENPIC_VEC_TIMER
mdefine_line|#define OPENPIC_VEC_TIMER&t;64&t;/* and up */
DECL|macro|OPENPIC_VEC_IPI
mdefine_line|#define OPENPIC_VEC_IPI&t;&t;72&t;/* and up */
DECL|macro|OPENPIC_VEC_SPURIOUS
mdefine_line|#define OPENPIC_VEC_SPURIOUS&t;127
multiline_comment|/*&n; * For the OpenPIC_InitSenses table, we include both the sense&n; * and polarity in one number and mask out the value we want&n; * later on. -- Tom&n; */
DECL|macro|IRQ_SENSE_MASK
mdefine_line|#define IRQ_SENSE_MASK&t;&t;0x1
DECL|macro|IRQ_SENSE_LEVEL
mdefine_line|#define IRQ_SENSE_LEVEL&t;&t;0x1
DECL|macro|IRQ_SENSE_EDGE
mdefine_line|#define IRQ_SENSE_EDGE&t;&t;0x0
DECL|macro|IRQ_POLARITY_MASK
mdefine_line|#define IRQ_POLARITY_MASK&t;0x2
DECL|macro|IRQ_POLARITY_POSITIVE
mdefine_line|#define IRQ_POLARITY_POSITIVE&t;0x2
DECL|macro|IRQ_POLARITY_NEGATIVE
mdefine_line|#define IRQ_POLARITY_NEGATIVE&t;0x0
multiline_comment|/* OpenPIC IRQ controller structure */
r_extern
r_struct
id|hw_interrupt_type
id|open_pic
suffix:semicolon
multiline_comment|/* OpenPIC IPI controller structure */
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|hw_interrupt_type
id|open_pic_ipi
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
r_extern
id|u_int
id|OpenPIC_NumInitSenses
suffix:semicolon
r_extern
id|u_char
op_star
id|OpenPIC_InitSenses
suffix:semicolon
r_extern
r_void
op_star
id|OpenPIC_Addr
suffix:semicolon
multiline_comment|/* Exported functions */
r_extern
r_void
id|openpic_set_sources
c_func
(paren
r_int
id|first_irq
comma
r_int
id|num_irqs
comma
r_void
op_star
id|isr
)paren
suffix:semicolon
r_extern
r_void
id|openpic_init
c_func
(paren
r_int
id|linux_irq_offset
)paren
suffix:semicolon
r_extern
r_void
id|openpic_init_nmi_irq
c_func
(paren
id|u_int
id|irq
)paren
suffix:semicolon
r_extern
id|u_int
id|openpic_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|openpic_eoi
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|openpic_request_IPIs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|do_openpic_setup_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|openpic_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|openpic_reset_processor_phys
c_func
(paren
id|u_int
id|cpumask
)paren
suffix:semicolon
r_extern
r_void
id|openpic_setup_ISU
c_func
(paren
r_int
id|isu_num
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|openpic_cause_IPI
c_func
(paren
id|u_int
id|ipi
comma
id|u_int
id|cpumask
)paren
suffix:semicolon
r_extern
r_void
id|smp_openpic_message_pass
c_func
(paren
r_int
id|target
comma
r_int
id|msg
comma
r_int
r_int
id|data
comma
r_int
id|wait
)paren
suffix:semicolon
DECL|function|openpic_to_irq
r_extern
r_inline
r_int
id|openpic_to_irq
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* IRQ 0 usually means &squot;disabled&squot;.. don&squot;t mess with it &n;&t; * exceptions to this (sandpoint maybe?) &n;&t; * shouldn&squot;t use openpic_to_irq &n;&t; */
r_if
c_cond
(paren
id|irq
op_ne
l_int|0
)paren
(brace
r_return
id|irq
op_add_assign
id|NUM_8259_INTERRUPTS
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*extern int open_pic_irq_offset;*/
macro_line|#endif /* _PPC_KERNEL_OPEN_PIC_H */
eof
