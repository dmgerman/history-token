multiline_comment|/*&n; * Copied from linux/include/asm-arm/arch-sa1100/system.h&n; * Copyright (c) 1999 Nicolas Pitre &lt;nico@cam.org&gt;&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
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
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|ARM_RSTCT1
)paren
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof
