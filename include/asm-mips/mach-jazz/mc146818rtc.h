multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 2001, 03 by Ralf Baechle&n; *&n; * RTC routines for Jazz style attached Dallas chip.&n; */
macro_line|#ifndef __ASM_MACH_JAZZ_MC146818RTC_H
DECL|macro|__ASM_MACH_JAZZ_MC146818RTC_H
mdefine_line|#define __ASM_MACH_JAZZ_MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
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
id|outb_p
c_func
(paren
id|addr
comma
id|RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
op_star
(paren
r_char
op_star
)paren
id|JAZZ_RTC_BASE
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
id|outb_p
c_func
(paren
id|addr
comma
id|RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|JAZZ_RTC_BASE
op_assign
id|data
suffix:semicolon
)brace
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
macro_line|#endif /* __ASM_MACH_JAZZ_MC146818RTC_H */
eof
