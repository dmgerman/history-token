multiline_comment|/*&n; * BK Id: SCCS/s.ppc4xx_pic.h 1.5 05/17/01 18:14:21 cort&n; */
multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: ppc4xx_pic.h&n; *&n; *    Description:&n; *      Interrupt controller driver for PowerPC 4xx-based processors.&n; */
macro_line|#ifndef&t;__PPC4XX_PIC_H__
DECL|macro|__PPC4XX_PIC_H__
mdefine_line|#define&t;__PPC4XX_PIC_H__
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/* External Global Variables */
r_extern
r_struct
id|hw_interrupt_type
op_star
id|ppc4xx_pic
suffix:semicolon
multiline_comment|/* Function Prototypes */
r_extern
r_void
id|ppc4xx_pic_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_pic_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __PPC4XX_PIC_H__ */
eof
