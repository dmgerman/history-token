multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: ppc4xx_pic.h&n; *&n; *    Description:&n; *      Interrupt controller driver for PowerPC 4xx-based processors.&n; */
macro_line|#ifndef&t;__PPC4XX_PIC_H__
DECL|macro|__PPC4XX_PIC_H__
mdefine_line|#define&t;__PPC4XX_PIC_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/* External Global Variables */
r_extern
r_struct
id|hw_interrupt_type
op_star
id|ppc4xx_pic
suffix:semicolon
r_extern
r_int
r_int
id|ibm4xxPIC_NumInitSenses
suffix:semicolon
r_extern
r_int
r_char
op_star
id|ibm4xxPIC_InitSenses
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
macro_line|#endif&t;&t;&t;&t;/* __PPC4XX_PIC_H__ */
eof
