multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 2001, 03 by Ralf Baechle&n; *&n; * RTC routines for PC style attached Dallas chip.&n; */
macro_line|#ifndef __ASM_MACH_AU1XX_MC146818RTC_H
DECL|macro|__ASM_MACH_AU1XX_MC146818RTC_H
mdefine_line|#define __ASM_MACH_AU1XX_MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x0c000000 + (x))
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;8
DECL|macro|PB1500_RTC_ADDR
mdefine_line|#define PB1500_RTC_ADDR 0x0c000000
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
id|offset
)paren
(brace
id|offset
op_lshift_assign
l_int|2
suffix:semicolon
r_return
(paren
id|u8
)paren
(paren
id|au_readl
c_func
(paren
id|offset
op_plus
id|PB1500_RTC_ADDR
)paren
op_amp
l_int|0xff
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
id|offset
)paren
(brace
id|offset
op_lshift_assign
l_int|2
suffix:semicolon
id|au_writel
c_func
(paren
id|data
comma
id|offset
op_plus
id|PB1500_RTC_ADDR
)paren
suffix:semicolon
)brace
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;1
macro_line|#endif /* __ASM_MACH_AU1XX_MC146818RTC_H */
eof
