multiline_comment|/*&n; * Various ISA level dependant constants.&n; * Most of the following constants reflect the different layout&n; * of Coprocessor 0 registers.&n; *&n; * Copyright (c) 1998 Harald Koerfgen&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASM_ISADEP_H
DECL|macro|__ASM_ISADEP_H
mdefine_line|#define __ASM_ISADEP_H
macro_line|#if defined(CONFIG_CPU_R3000)
multiline_comment|/*&n; * R2000 or R3000&n; */
multiline_comment|/*&n; * kernel or user mode? (CP0_STATUS)&n; */
DECL|macro|KU_MASK
mdefine_line|#define KU_MASK 0x08
DECL|macro|KU_USER
mdefine_line|#define&t;KU_USER 0x08
DECL|macro|KU_KERN
mdefine_line|#define KU_KERN 0x00
macro_line|#else
multiline_comment|/*&n; * kernel or user mode?&n; */
DECL|macro|KU_MASK
mdefine_line|#define KU_MASK 0x18
DECL|macro|KU_USER
mdefine_line|#define&t;KU_USER 0x10
DECL|macro|KU_KERN
mdefine_line|#define KU_KERN 0x00
macro_line|#endif
macro_line|#endif /* __ASM_ISADEP_H */
eof
