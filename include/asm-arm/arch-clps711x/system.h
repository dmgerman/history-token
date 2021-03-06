multiline_comment|/*&n; *  linux/include/asm-arm/arch-clps711x/system.h&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
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
id|clps_writel
c_func
(paren
l_int|1
comma
id|HALT
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;r0, r0&bslash;n&bslash;&n;&t;mov&t;r0, r0&quot;
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
id|cpu_reset
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
