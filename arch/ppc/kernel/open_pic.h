multiline_comment|/*&n; * BK Id: SCCS/s.open_pic.h 1.8 05/17/01 18:14:21 cort&n; */
multiline_comment|/*&n; *  arch/ppc/kernel/open_pic.h -- OpenPIC Interrupt Handling&n; *&n; *  Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; *  &n; */
macro_line|#ifndef _PPC_KERNEL_OPEN_PIC_H
DECL|macro|_PPC_KERNEL_OPEN_PIC_H
mdefine_line|#define _PPC_KERNEL_OPEN_PIC_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|OPENPIC_SIZE
mdefine_line|#define OPENPIC_SIZE&t;0x40000
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
id|openpic_init
c_func
(paren
r_int
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
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
id|openpic_init_processor
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
r_return
id|irq
op_add_assign
id|NUM_8259_INTERRUPTS
suffix:semicolon
)brace
multiline_comment|/*extern int open_pic_irq_offset;*/
macro_line|#endif /* _PPC_KERNEL_OPEN_PIC_H */
eof
