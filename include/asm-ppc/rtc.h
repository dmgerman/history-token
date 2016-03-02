multiline_comment|/* &n; * inclue/asm-ppc/rtc.h&n; *&n; * Author: Tom Rini &lt;trini@mvista.com&gt;&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; *&n; * Based on:&n; * include/asm-m68k/rtc.h&n; *&n; * Copyright Richard Zidlicky&n; * implementation details for genrtc/q40rtc driver&n; *&n; * And the old drivers/macintosh/rtc.c which was heavily based on:&n; * Linux/SPARC Real Time Clock Driver&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; *&n; * With additional work by Paul Mackerras and Franz Sirl.&n; */
macro_line|#ifndef __ASM_RTC_H__
DECL|macro|__ASM_RTC_H__
mdefine_line|#define __ASM_RTC_H__
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
DECL|macro|RTC_PIE
mdefine_line|#define RTC_PIE 0x40&t;&t;/* periodic interrupt enable */
DECL|macro|RTC_AIE
mdefine_line|#define RTC_AIE 0x20&t;&t;/* alarm interrupt enable */
DECL|macro|RTC_UIE
mdefine_line|#define RTC_UIE 0x10&t;&t;/* update-finished interrupt enable */
multiline_comment|/* some dummy definitions */
DECL|macro|RTC_BATT_BAD
mdefine_line|#define RTC_BATT_BAD 0x100&t;/* battery bad */
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
(brace
r_if
c_cond
(paren
id|ppc_md.get_rtc_time
)paren
(brace
r_int
r_int
id|nowtime
suffix:semicolon
id|nowtime
op_assign
(paren
id|ppc_md.get_rtc_time
)paren
(paren
)paren
suffix:semicolon
id|to_tm
c_func
(paren
id|nowtime
comma
id|time
)paren
suffix:semicolon
id|time-&gt;tm_year
op_sub_assign
l_int|1900
suffix:semicolon
id|time-&gt;tm_mon
op_sub_assign
l_int|1
suffix:semicolon
multiline_comment|/* Make sure userland has a 0-based month */
)brace
r_return
id|RTC_24H
suffix:semicolon
)brace
multiline_comment|/* Set the current date and time in the real time clock. */
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
r_if
c_cond
(paren
id|ppc_md.get_rtc_time
)paren
(brace
r_int
r_int
id|nowtime
suffix:semicolon
id|nowtime
op_assign
id|mktime
c_func
(paren
id|time-&gt;tm_year
op_plus
l_int|1900
comma
id|time-&gt;tm_mon
op_plus
l_int|1
comma
id|time-&gt;tm_mday
comma
id|time-&gt;tm_hour
comma
id|time-&gt;tm_min
comma
id|time-&gt;tm_sec
)paren
suffix:semicolon
(paren
id|ppc_md.set_rtc_time
)paren
(paren
id|nowtime
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|get_rtc_ss
r_static
r_inline
r_int
r_int
id|get_rtc_ss
c_func
(paren
r_void
)paren
(brace
r_struct
id|rtc_time
id|h
suffix:semicolon
id|get_rtc_time
c_func
(paren
op_amp
id|h
)paren
suffix:semicolon
r_return
id|h.tm_sec
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_RTC_H__ */
eof
