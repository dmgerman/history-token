multiline_comment|/*&n; *&t;include/asm-mips/i8259.h&n; *&n; *&t;i8259A interrupt definitions.&n; *&n; *&t;Copyright (C) 2003  Maciej W. Rozycki&n; *&t;Copyright (C) 2003  Ralf Baechle &lt;ralf@linux-mips.org&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_I8259_H
DECL|macro|_ASM_I8259_H
mdefine_line|#define _ASM_I8259_H
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
id|spinlock_t
id|i8259A_lock
suffix:semicolon
r_extern
r_void
id|init_i8259_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Do the traditional i8259 interrupt polling thing.  This is for the few&n; * cases where no better interrupt acknowledge method is available and we&n; * absolutely must touch the i8259.&n; */
DECL|function|i8259_irq
r_static
r_inline
r_int
id|i8259_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i8259A_lock
)paren
suffix:semicolon
multiline_comment|/* Perform an interrupt acknowledge cycle on controller 1. */
id|outb
c_func
(paren
l_int|0x0C
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* prepare for poll */
id|irq
op_assign
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
(brace
multiline_comment|/*&n;&t;&t; * Interrupt is cascaded so perform interrupt&n;&t;&t; * acknowledge on controller 2.&n;&t;&t; */
id|outb
c_func
(paren
l_int|0x0C
comma
l_int|0xA0
)paren
suffix:semicolon
multiline_comment|/* prepare for poll */
id|irq
op_assign
(paren
id|inb
c_func
(paren
l_int|0xA0
)paren
op_amp
l_int|7
)paren
op_plus
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|irq
op_eq
l_int|7
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This may be a spurious interrupt.&n;&t;&t; *&n;&t;&t; * Read the interrupt status register (ISR). If the most&n;&t;&t; * significant bit is not set then there is no valid&n;&t;&t; * interrupt.&n;&t;&t; */
id|outb
c_func
(paren
l_int|0x0B
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* ISR register */
r_if
c_cond
(paren
op_complement
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|0x80
)paren
(brace
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|i8259A_lock
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
macro_line|#endif /* _ASM_I8259_H */
eof
