multiline_comment|/*&n; *&t;include/asm-mips/irq_cpu.h&n; *&n; *&t;MIPS CPU interrupt definitions.&n; *&n; *&t;Copyright (C) 2002  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_IRQ_CPU_H
DECL|macro|_ASM_IRQ_CPU_H
mdefine_line|#define _ASM_IRQ_CPU_H
r_extern
r_void
id|mips_cpu_irq_init
c_func
(paren
r_int
id|irq_base
)paren
suffix:semicolon
r_extern
r_void
id|rm7k_cpu_irq_init
c_func
(paren
r_int
id|irq_base
)paren
suffix:semicolon
r_extern
r_void
id|rm9k_cpu_irq_init
c_func
(paren
r_int
id|irq_base
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_CPU_H */
eof
