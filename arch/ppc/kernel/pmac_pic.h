macro_line|#ifndef _PPC_KERNEL_PMAC_PIC_H
DECL|macro|_PPC_KERNEL_PMAC_PIC_H
mdefine_line|#define _PPC_KERNEL_PMAC_PIC_H
macro_line|#include &quot;local_irq.h&quot;
r_extern
r_struct
id|hw_interrupt_type
id|pmac_pic
suffix:semicolon
r_void
id|pmac_pic_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pmac_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|pmac_post_irq
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_PMAC_PIC_H */
eof
