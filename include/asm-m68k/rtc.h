multiline_comment|/* asm-m68k/rtc.h&n; *&n; * Copyright Richard Zidlicky&n; * implementation details for genrtc/q40rtc driver&n; */
multiline_comment|/* permission is hereby granted to copy, modify and redistribute this code&n; * in terms of the GNU Library General Public License, Version 2 or later,&n; * at your option.&n; */
macro_line|#ifndef _ASM_RTC_H
DECL|macro|_ASM_RTC_H
mdefine_line|#define _ASM_RTC_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* a few implementation details for the emulation : */
r_extern
r_int
id|gen_rtc_irq_flags
suffix:semicolon
multiline_comment|/* which sort(s) of interrupts caused int */
r_extern
r_int
id|gen_rtc_irq_ctrl
suffix:semicolon
multiline_comment|/*                             are enabled */
r_extern
r_int
id|q40rtc_oldsecs
suffix:semicolon
DECL|macro|RTC_PIE
mdefine_line|#define RTC_PIE 0x40&t;&t;/* periodic interrupt enable */
DECL|macro|RTC_AIE
mdefine_line|#define RTC_AIE 0x20&t;&t;/* alarm interrupt enable */
DECL|macro|RTC_UIE
mdefine_line|#define RTC_UIE 0x10&t;&t;/* update-finished interrupt enable */
r_extern
r_void
id|gen_rtc_interrupt
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* some dummy definitions */
DECL|macro|RTC_SQWE
mdefine_line|#define RTC_SQWE 0x08&t;&t;/* enable square-wave output */
DECL|macro|RTC_DM_BINARY
mdefine_line|#define RTC_DM_BINARY 0x04&t;/* all time/date values are BCD if clear */
DECL|macro|RTC_24H
mdefine_line|#define RTC_24H 0x02&t;&t;/* 24 hour mode - else hours bit 7 means pm */
DECL|macro|RTC_DST_EN
mdefine_line|#define RTC_DST_EN 0x01&t;        /* auto switch DST - works f. USA only */
DECL|function|get_rtc_time
r_static
r_inline
r_void
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|time
)paren
(brace
multiline_comment|/*&n;&t; * Only the values that we read from the RTC are set. We leave&n;&t; * tm_wday, tm_yday and tm_isdst untouched. Even though the&n;&t; * RTC has RTC_DAY_OF_WEEK, we ignore it, as it is only updated&n;&t; * by the RTC when initially set to a non-zero value.&n;&t; */
id|mach_hwclk
c_func
(paren
l_int|0
comma
id|time
)paren
suffix:semicolon
)brace
DECL|function|set_rtc_time
r_static
r_inline
r_int
id|set_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|time
)paren
(brace
r_return
id|mach_hwclk
c_func
(paren
l_int|1
comma
id|time
)paren
suffix:semicolon
)brace
DECL|function|get_rtc_pll
r_static
r_inline
r_int
id|get_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
(brace
r_if
c_cond
(paren
id|mach_get_rtc_pll
)paren
r_return
id|mach_get_rtc_pll
c_func
(paren
id|pll
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|set_rtc_pll
r_static
r_inline
r_int
id|set_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
(brace
r_if
c_cond
(paren
id|mach_set_rtc_pll
)paren
r_return
id|mach_set_rtc_pll
c_func
(paren
id|pll
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM__RTC_H */
eof
