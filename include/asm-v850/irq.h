multiline_comment|/*&n; * include/asm-v850/irq.h -- Machine interrupt handling&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_IRQ_H__
DECL|macro|__V850_IRQ_H__
mdefine_line|#define __V850_IRQ_H__
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* Default NUM_MACH_IRQS.  */
macro_line|#ifndef NUM_MACH_IRQS
DECL|macro|NUM_MACH_IRQS
mdefine_line|#define NUM_MACH_IRQS&t;NUM_CPU_IRQS
macro_line|#endif
multiline_comment|/* NMIs have IRQ numbers from FIRST_NMI to FIRST_NMI+NUM_NMIS-1.  */
DECL|macro|FIRST_NMI
mdefine_line|#define FIRST_NMI&t;NUM_MACH_IRQS
DECL|macro|IRQ_NMI
mdefine_line|#define IRQ_NMI(n)&t;(FIRST_NMI + (n))
multiline_comment|/* v850 processors have 3 non-maskable interrupts.  */
DECL|macro|NUM_NMIS
mdefine_line|#define NUM_NMIS&t;3
multiline_comment|/* Includes both maskable and non-maskable irqs.  */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;(NUM_MACH_IRQS + NUM_NMIS)
macro_line|#ifndef __ASSEMBLY__
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|hw_interrupt_type
suffix:semicolon
r_struct
id|irqaction
suffix:semicolon
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(irq)&t;(irq)
multiline_comment|/* Initialize irq handling for IRQs.&n;   BASE_IRQ, BASE_IRQ+INTERVAL, ..., BASE_IRQ+NUM*INTERVAL&n;   to IRQ_TYPE.  An IRQ_TYPE of 0 means to use a generic interrupt type.  */
r_extern
r_void
id|init_irq_handlers
(paren
r_int
id|base_irq
comma
r_int
id|num
comma
r_int
id|interval
comma
r_struct
id|hw_interrupt_type
op_star
id|irq_type
)paren
suffix:semicolon
DECL|typedef|irq_handler_t
r_typedef
r_void
(paren
op_star
id|irq_handler_t
)paren
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/* Handle interrupt IRQ.  REGS are the registers at the time of ther&n;   interrupt.  */
r_extern
r_int
r_int
id|handle_irq
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_IRQ_H__ */
eof
