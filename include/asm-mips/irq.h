multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Waldorf GMBH, written by Ralf Baechle&n; * Copyright (C) 1995, 96, 97, 98, 99, 2000, 01, 02 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2001 Kanoj Sarcar&n; */
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 128&t;&t;/* Largest number of ints of all machines.  */
macro_line|#ifdef CONFIG_I8259
DECL|function|irq_canonicalize
r_static
r_inline
r_int
id|irq_canonicalize
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
DECL|macro|irq_canonicalize
mdefine_line|#define irq_canonicalize(irq) (irq)&t;/* Sane hardware, sane code ... */
macro_line|#endif
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
r_struct
id|pt_regs
suffix:semicolon
r_extern
id|asmlinkage
r_int
r_int
id|do_IRQ
c_func
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
r_extern
r_void
id|init_generic_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H */
eof
