multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Waldorf GMBH, written by Ralf Baechle&n; * Copyright (C) 1995, 96, 97, 98, 99, 2000, 01, 02, 03 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;irq.h&gt;
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
r_struct
id|pt_regs
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
r_extern
id|asmlinkage
r_int
r_int
id|do_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n; * do_IRQ handles all normal device IRQ&squot;s (the special&n; * SMP cross-CPU interrupts have their own specific&n; * handlers).&n; *&n; * Ideally there should be away to get this into kernel/irq/handle.c to&n; * avoid the overhead of a call for just a tiny function ...&n; */
DECL|macro|do_IRQ
mdefine_line|#define do_IRQ(irq, regs)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;irq_enter();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__do_IRQ((irq), (regs));&t;&t;&t;&t;&t;&bslash;&n;&t;irq_exit();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
r_extern
r_void
id|arch_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|irqaction
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
eof
