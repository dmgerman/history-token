multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 2001, 03 by Ralf Baechle&n; * Copyright (C) 2000 Harald Koerfgen&n; *&n; * RTC routines for IP32 style attached Dallas chip.&n; */
macro_line|#ifndef __ASM_MACH_IP32_MC146818RTC_H
DECL|macro|__ASM_MACH_IP32_MC146818RTC_H
mdefine_line|#define __ASM_MACH_IP32_MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ip32/mace.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
DECL|function|CMOS_READ
r_static
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
r_return
id|mace-&gt;isa.rtc
(braket
id|addr
op_lshift
l_int|8
)braket
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
id|mace-&gt;isa.rtc
(braket
id|addr
op_lshift
l_int|8
)braket
op_assign
id|data
suffix:semicolon
)brace
multiline_comment|/* FIXME: Do it right. For now just assume that noone lives in 20th century&n; * and no O2 user in 22th century ;-) */
DECL|macro|mc146818_decode_year
mdefine_line|#define mc146818_decode_year(year) ((year) + 2000)
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
macro_line|#endif /* __ASM_MACH_IP32_MC146818RTC_H */
eof
