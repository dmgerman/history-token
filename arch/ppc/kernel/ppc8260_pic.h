macro_line|#ifndef _PPC_KERNEL_PPC8260_H
DECL|macro|_PPC_KERNEL_PPC8260_H
mdefine_line|#define _PPC_KERNEL_PPC8260_H
macro_line|#include &quot;local_irq.h&quot;
r_extern
r_struct
id|hw_interrupt_type
id|ppc8260_pic
suffix:semicolon
r_void
id|m8260_pic_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|m8260_do_IRQ
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
id|m8260_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_PPC8260_H */
eof
