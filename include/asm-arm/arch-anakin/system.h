multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/system.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   11-Apr-2001 TTC&t;Created&n; *   04-May-2001 W/PB&t;Removed cpu_do_idle()&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
r_static
r_inline
r_void
DECL|function|arch_idle
id|arch_idle
c_func
(paren
r_void
)paren
(brace
)brace
r_static
r_inline
r_void
DECL|function|arch_reset
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
