multiline_comment|/*&n; * include/asm-mips/rtc.h &n; *&n; * (Really an interface for drivers/char/genrtc.c)&n; *&n; * Copyright (C) 2004 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * Please read the COPYING file for all license details.&n; */
macro_line|#ifndef _MIPS_RTC_H
DECL|macro|_MIPS_RTC_H
mdefine_line|#define _MIPS_RTC_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/rtc.h&gt;
DECL|macro|RTC_PIE
mdefine_line|#define RTC_PIE 0x40            /* periodic interrupt enable */
DECL|macro|RTC_AIE
mdefine_line|#define RTC_AIE 0x20            /* alarm interrupt enable */
DECL|macro|RTC_UIE
mdefine_line|#define RTC_UIE 0x10            /* update-finished interrupt enable */
multiline_comment|/* some dummy definitions */
DECL|macro|RTC_BATT_BAD
mdefine_line|#define RTC_BATT_BAD 0x100      /* battery bad */
DECL|macro|RTC_SQWE
mdefine_line|#define RTC_SQWE 0x08           /* enable square-wave output */
DECL|macro|RTC_DM_BINARY
mdefine_line|#define RTC_DM_BINARY 0x04      /* all time/date values are BCD if clear */
DECL|macro|RTC_24H
mdefine_line|#define RTC_24H 0x02            /* 24 hour mode - else hours bit 7 means pm */
DECL|macro|RTC_DST_EN
mdefine_line|#define RTC_DST_EN 0x01         /* auto switch DST - works f. USA only */
r_int
r_int
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|time
)paren
suffix:semicolon
r_int
id|set_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|time
)paren
suffix:semicolon
r_int
r_int
id|get_rtc_ss
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|get_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
suffix:semicolon
r_int
id|set_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
