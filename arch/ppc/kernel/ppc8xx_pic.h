multiline_comment|/*&n; * BK Id: SCCS/s.ppc8xx_pic.h 1.7 05/17/01 18:14:21 cort&n; */
macro_line|#ifndef _PPC_KERNEL_PPC8xx_H
DECL|macro|_PPC_KERNEL_PPC8xx_H
mdefine_line|#define _PPC_KERNEL_PPC8xx_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;local_irq.h&quot;
r_extern
r_struct
id|hw_interrupt_type
id|ppc8xx_pic
suffix:semicolon
r_void
id|m8xx_pic_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|m8xx_do_IRQ
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
id|m8xx_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MBX
macro_line|#include &quot;i8259.h&quot;
macro_line|#include &lt;asm/io.h&gt;
r_void
id|mbx_i8259_action
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _PPC_KERNEL_PPC8xx_H */
eof
