multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; * Copyright (C) 2003 by Ralf Baechle&n; *&n; * This program is free software; you can distribute it and/or modify it&n; * under the terms of the GNU General Public License (Version 2) as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; */
macro_line|#ifndef __ASM_MACH_ATLAS_MC146818RTC_H
DECL|macro|__ASM_MACH_ATLAS_MC146818RTC_H
mdefine_line|#define __ASM_MACH_ATLAS_MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mips-boards/atlas.h&gt;
macro_line|#include &lt;asm/mips-boards/atlasint.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(ATLAS_RTC_ADR_REG + (x)*8)
DECL|macro|RTC_IOMAPPED
mdefine_line|#define RTC_IOMAPPED&t;1
DECL|macro|RTC_EXTENT
mdefine_line|#define RTC_EXTENT&t;16
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;ATLASINT_RTC
macro_line|#ifdef CONFIG_CPU_LITTLE_ENDIAN
DECL|macro|ATLAS_RTC_PORT
mdefine_line|#define ATLAS_RTC_PORT(x) (RTC_PORT(x) + 0)
macro_line|#else
DECL|macro|ATLAS_RTC_PORT
mdefine_line|#define ATLAS_RTC_PORT(x) (RTC_PORT(x) + 3)
macro_line|#endif
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
id|ATLAS_RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|ATLAS_RTC_PORT
c_func
(paren
l_int|1
)paren
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
id|ATLAS_RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|ATLAS_RTC_PORT
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
DECL|macro|mc146818_decode_year
mdefine_line|#define mc146818_decode_year(year) ((year) &lt; 70 ? (year) + 2000 : (year) + 1970)
macro_line|#endif /* __ASM_MACH_ATLAS_MC146818RTC_H */
eof
