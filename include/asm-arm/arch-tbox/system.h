multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/system.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|function|arch_idle
r_static
r_inline
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
id|cpu_do_idle
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode)&t;do { } while (0)
macro_line|#endif
eof
