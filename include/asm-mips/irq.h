multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Waldorf GMBH, written by Ralf Baechle&n; * Copyright (C) 1995, 96, 97, 98, 99, 2000, 2001 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 64&t;&t;/* Largest number of ints of all machines.  */
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
macro_line|#ifdef CONFIG_I8259
DECL|function|irq_cannonicalize
r_static
r_inline
r_int
id|irq_cannonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
(paren
id|irq
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
id|irq
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(irq) (irq)&t;/* Sane hardware, sane code ... */
macro_line|#endif
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
macro_line|#ifdef CONFIG_ROTTEN_IRQ
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync&t;disable_irq
macro_line|#else
r_extern
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
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
