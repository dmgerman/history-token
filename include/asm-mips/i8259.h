multiline_comment|/*&n; *&t;include/asm-mips/i8259.h&n; *&n; *&t;i8259A interrupt definitions.&n; *&n; *&t;Copyright (C) 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_MIPS_I8259_H
DECL|macro|__ASM_MIPS_I8259_H
mdefine_line|#define __ASM_MIPS_I8259_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_void
id|init_i8259_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_I8259_H */
eof
