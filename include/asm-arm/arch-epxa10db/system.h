multiline_comment|/*&n; *  linux/include/asm-arm/arch-epxa10db/system.h&n; *&n; *  Copyright (C) 1999 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;asm/arch/platform.h&gt;
DECL|function|arch_idle
r_static
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * This should do all the clock switching&n;&t; * and wait for interrupt tricks&n;&t; */
id|cpu_do_idle
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|arch_reset
r_extern
id|__inline__
r_void
id|arch_reset
c_func
(paren
r_char
id|mode
)paren
(brace
multiline_comment|/* Hmm... We can probably do something with the watchdog... */
)brace
macro_line|#endif
eof
