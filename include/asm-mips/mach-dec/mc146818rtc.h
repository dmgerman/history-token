multiline_comment|/*&n; * RTC definitions for DECstation style attached Dallas DS1287 chip.&n; *&n; * Copyright (C) 1998, 2001 by Ralf Baechle&n; * Copyright (C) 1998 by Harald Koerfgen&n; * Copyright (C) 2002  Maciej W. Rozycki&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_RTC_DEC_H
DECL|macro|__ASM_MIPS_DEC_RTC_DEC_H
mdefine_line|#define __ASM_MIPS_DEC_RTC_DEC_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
r_extern
r_volatile
id|u8
op_star
id|dec_rtc_base
suffix:semicolon
r_extern
r_int
r_int
id|dec_kn_slot_size
suffix:semicolon
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;CPHYSADDR(dec_rtc_base)
DECL|macro|RTC_IO_EXTENT
mdefine_line|#define RTC_IO_EXTENT&t;dec_kn_slot_size
DECL|macro|RTC_IOMAPPED
mdefine_line|#define RTC_IOMAPPED&t;0
DECL|macro|RTC_IRQ
macro_line|#undef RTC_IRQ
DECL|macro|RTC_DEC_YEAR
mdefine_line|#define RTC_DEC_YEAR&t;0x3f&t;/* Where we store the real year on DECs.  */
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
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
r_return
id|dec_rtc_base
(braket
id|addr
op_star
l_int|4
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
id|dec_rtc_base
(braket
id|addr
op_star
l_int|4
)braket
op_assign
id|data
suffix:semicolon
)brace
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
macro_line|#endif /* __ASM_MIPS_DEC_RTC_DEC_H */
eof
