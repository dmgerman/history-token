multiline_comment|/*&n; *&t;include/asm-mips/dec/rtc-dec.h&n; *&n; *&t;RTC definitions for DECstation style attached Dallas DS1287 chip.&n; *&n; *&t;Copyright (C) 2002  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
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
r_extern
r_struct
id|rtc_ops
id|dec_rtc_ops
suffix:semicolon
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;CPHYSADDR(dec_rtc_base)
DECL|macro|RTC_IO_EXTENT
mdefine_line|#define RTC_IO_EXTENT&t;dec_kn_slot_size
DECL|macro|RTC_IOMAPPED
mdefine_line|#define RTC_IOMAPPED&t;0
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;0
DECL|macro|RTC_DEC_YEAR
mdefine_line|#define RTC_DEC_YEAR&t;0x3f&t;/* Where we store the real year on DECs.  */
macro_line|#endif /* __ASM_MIPS_DEC_RTC_DEC_H */
eof
