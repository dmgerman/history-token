multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; * Copyright (C) 2003 by Ralf Baechle&n; *&n; * This program is free software; you can distribute it and/or modify it&n; * under the terms of the GNU General Public License (Version 2) as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * RTC routines for Malta style attached PIIX4 device, which contains a&n; * Motorola MC146818A-compatible Real Time Clock.&n; */
macro_line|#ifndef __ASM_MACH_MALTA_MC146818RTC_H
DECL|macro|__ASM_MACH_MALTA_MC146818RTC_H
mdefine_line|#define __ASM_MACH_MALTA_MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mips-boards/generic.h&gt;
macro_line|#include &lt;asm/mips-boards/malta.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;8
DECL|function|CMOS_READ
r_static
r_inline
r_int
r_char
id|CMOS_READ
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|outb
c_func
(paren
id|addr
comma
id|MALTA_RTC_ADR_REG
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|MALTA_RTC_DAT_REG
)paren
suffix:semicolon
)brace
DECL|function|CMOS_WRITE
r_static
r_inline
r_void
id|CMOS_WRITE
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
id|outb
c_func
(paren
id|addr
comma
id|MALTA_RTC_ADR_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|MALTA_RTC_DAT_REG
)paren
suffix:semicolon
)brace
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
DECL|macro|mc146818_decode_year
mdefine_line|#define mc146818_decode_year(year) ((year) &lt; 70 ? (year) + 2000 : (year) + 1970)
macro_line|#endif /* __ASM_MACH_MALTA_MC146818RTC_H */
eof
