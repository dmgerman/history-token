multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/system.h&n; *&n; * Copyright (c) 1999 Nexus Electronics Ltd.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_SUSMODE
)paren
suffix:semicolon
)brace
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;iomd_writeb(0, IOMD_ROMCR0);&t;&bslash;&n;&t;&t;cpu_reset(0);&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif
eof
