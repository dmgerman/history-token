multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Machine dependent access functions for RTC registers.&n; *&n; * Copyright (C) 1996, 1997, 1998, 2000 Ralf Baechle&n; */
macro_line|#ifndef _ASM_MC146818RTC_H
DECL|macro|_ASM_MC146818RTC_H
mdefine_line|#define _ASM_MC146818RTC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef RTC_PORT
macro_line|#if defined(CONFIG_MIPS_ITE8172) || defined(CONFIG_MIPS_IVR)
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x14014800 + (x))
macro_line|#else
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * The yet supported machines all access the RTC index register via&n; * an ISA port access but the way to access the date register differs ...&n; */
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr) ({ &bslash;&n;rtc_ops-&gt;rtc_read_data(addr); &bslash;&n;})
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val, addr) ({ &bslash;&n;rtc_ops-&gt;rtc_write_data(val, addr); &bslash;&n;})
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD &bslash;&n;rtc_ops-&gt;rtc_bcd_mode()
multiline_comment|/*&n; * This structure defines how to access various features of&n; * different machine types and how to access them.&n; */
DECL|struct|rtc_ops
r_struct
id|rtc_ops
(brace
multiline_comment|/* How to access the RTC register in a DS1287.  */
DECL|member|rtc_read_data
r_int
r_char
(paren
op_star
id|rtc_read_data
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|member|rtc_write_data
r_void
(paren
op_star
id|rtc_write_data
)paren
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|member|rtc_bcd_mode
r_int
(paren
op_star
id|rtc_bcd_mode
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|rtc_ops
op_star
id|rtc_ops
suffix:semicolon
macro_line|#ifdef CONFIG_DECSTATION
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ 0
macro_line|#elif defined(CONFIG_MIPS_ITE8172) || defined(CONFIG_MIPS_IVR)
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;IT8172_RTC_IRQ
macro_line|#else
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;8
macro_line|#endif
DECL|macro|RTC_DEC_YEAR
mdefine_line|#define RTC_DEC_YEAR&t;0x3f&t;/* Where we store the real year on DECs.  */
macro_line|#endif /* _ASM_MC146818RTC_H */
eof
