multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/system.h&n; *&n; * Copyright (c) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog&n; *  03-21-2000  SJH&t;Created&n; *  04-26-2000  SJH&t;Fixed functions&n; *  05-03-2000  SJH&t;Removed usage of obsolete &squot;iomd.h&squot;&n; *  05-31-2000  SJH&t;Properly implemented &squot;arch_idle&squot;&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|function|arch_idle
r_static
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* fixme: this needs to be cleaned up (converted from ASM code) --rmk */
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|IO_BASE
op_plus
l_int|0x50004
)paren
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* idle mode */
)brace
DECL|function|arch_reset
r_static
r_inline
r_void
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
l_char|&squot;s&squot;
)paren
(brace
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
