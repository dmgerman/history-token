multiline_comment|/*&n; * linux/include/asm-arm/arch-pxa/irq.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Created:&t;Jun 15, 2001&n; * Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|fixup_irq
mdefine_line|#define fixup_irq(x)&t;(x)
multiline_comment|/*&n; * This prototype is required for cascading of multiplexed interrupts.&n; * Since it doesn&squot;t exist elsewhere, we&squot;ll put it here for now.&n; */
r_extern
r_void
id|do_IRQ
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
eof
