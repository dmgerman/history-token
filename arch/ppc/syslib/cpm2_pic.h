macro_line|#ifndef _PPC_KERNEL_CPM2_H
DECL|macro|_PPC_KERNEL_CPM2_H
mdefine_line|#define _PPC_KERNEL_CPM2_H
macro_line|#include &lt;linux/irq.h&gt;
r_extern
r_struct
id|hw_interrupt_type
id|cpm2_pic
suffix:semicolon
r_void
id|cpm2_pic_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cpm2_do_IRQ
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|cpu
)paren
suffix:semicolon
r_int
id|cpm2_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_CPM2_H */
eof
