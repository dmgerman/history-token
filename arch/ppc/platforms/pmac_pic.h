multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#ifndef __PPC_PLATFORMS_PMAC_PIC_H
DECL|macro|__PPC_PLATFORMS_PMAC_PIC_H
mdefine_line|#define __PPC_PLATFORMS_PMAC_PIC_H
macro_line|#include &lt;linux/irq.h&gt;
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
macro_line|#endif /* __PPC_PLATFORMS_PMAC_PIC_H */
eof
