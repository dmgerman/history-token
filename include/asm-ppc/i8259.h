macro_line|#ifndef _PPC_KERNEL_i8259_H
DECL|macro|_PPC_KERNEL_i8259_H
mdefine_line|#define _PPC_KERNEL_i8259_H
macro_line|#include &lt;linux/irq.h&gt;
r_extern
r_struct
id|hw_interrupt_type
id|i8259_pic
suffix:semicolon
r_extern
r_void
id|i8259_init
c_func
(paren
r_int
id|intack_addr
)paren
suffix:semicolon
r_extern
r_int
id|i8259_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_i8259_H */
eof
