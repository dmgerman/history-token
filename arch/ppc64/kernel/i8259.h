multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC_KERNEL_i8259_H
DECL|macro|_PPC_KERNEL_i8259_H
mdefine_line|#define _PPC_KERNEL_i8259_H
macro_line|#include &quot;local_irq.h&quot;
r_extern
r_struct
id|hw_interrupt_type
id|i8259_pic
suffix:semicolon
r_void
id|i8259_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|i8259_irq
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_i8259_H */
eof
