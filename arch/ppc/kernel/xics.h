multiline_comment|/*&n; * arch/ppc/kernel/xics.h&n; *&n; * Copyright 2000 IBM Corporation.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC_KERNEL_XICS_H
DECL|macro|_PPC_KERNEL_XICS_H
mdefine_line|#define _PPC_KERNEL_XICS_H
macro_line|#include &quot;local_irq.h&quot;
r_extern
r_struct
id|hw_interrupt_type
id|xics_pic
suffix:semicolon
r_extern
r_struct
id|hw_interrupt_type
id|xics_8259_pic
suffix:semicolon
r_void
id|xics_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|xics_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_XICS_H */
eof
