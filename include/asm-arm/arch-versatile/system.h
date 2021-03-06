multiline_comment|/*&n; *  linux/include/asm-arm/arch-versatile/system.h&n; *&n; *  Copyright (C) 2003 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/platform.h&gt;
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
multiline_comment|/*&n;&t; * This should do all the clock switching&n;&t; * and wait for interrupt tricks&n;&t; */
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
r_int
r_int
id|hdr_ctrl
op_assign
(paren
id|IO_ADDRESS
c_func
(paren
id|VERSATILE_SYS_BASE
)paren
op_plus
id|VERSATILE_SYS_RESETCTL_OFFSET
)paren
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/*&n;&t; * To reset, we hit the on-board reset register&n;&t; * in the system FPGA&n;&t; */
id|val
op_assign
id|__raw_readl
c_func
(paren
id|hdr_ctrl
)paren
suffix:semicolon
id|val
op_or_assign
id|VERSATILE_SYS_CTRL_RESET_CONFIGCLR
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
comma
id|hdr_ctrl
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
