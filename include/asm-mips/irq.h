multiline_comment|/* $Id: irq.h,v 1.6 2000/01/26 00:07:45 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Waldorf GMBH, written by Ralf Baechle&n; * Copyright (C) 1995, 1996, 1997, 1998 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 64
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
r_extern
r_int
(paren
op_star
id|irq_cannonicalize
)paren
(paren
r_int
id|irq
)paren
suffix:semicolon
r_struct
id|irqaction
suffix:semicolon
r_extern
r_int
id|i8259_setup_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync&t;disable_irq
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Machine specific interrupt initialization  */
r_extern
r_void
(paren
op_star
id|irq_setup
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H */
eof
