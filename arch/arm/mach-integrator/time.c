multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/time.c&n; *&n; *  Copyright (C) 2000-2001 Deep Blue Solutions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|RTC_DR
mdefine_line|#define RTC_DR&t;&t;(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 0)
DECL|macro|RTC_MR
mdefine_line|#define RTC_MR&t;&t;(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 4)
DECL|macro|RTC_STAT
mdefine_line|#define RTC_STAT&t;(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 8)
DECL|macro|RTC_EOI
mdefine_line|#define RTC_EOI&t;&t;(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 8)
DECL|macro|RTC_LR
mdefine_line|#define RTC_LR&t;&t;(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 12)
DECL|macro|RTC_CR
mdefine_line|#define RTC_CR&t;&t;(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 16)
DECL|macro|RTC_CR_MIE
mdefine_line|#define RTC_CR_MIE&t;0x00000001
r_extern
r_int
(paren
op_star
id|set_rtc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|integrator_set_rtc
r_static
r_int
id|integrator_set_rtc
c_func
(paren
r_void
)paren
(brace
id|__raw_writel
c_func
(paren
id|xtime.tv_sec
comma
id|RTC_LR
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|integrator_rtc_init
r_static
r_int
id|integrator_rtc_init
c_func
(paren
r_void
)paren
(brace
id|__raw_writel
c_func
(paren
l_int|0
comma
id|RTC_CR
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0
comma
id|RTC_EOI
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|__raw_readl
c_func
(paren
id|RTC_DR
)paren
suffix:semicolon
id|set_rtc
op_assign
id|integrator_set_rtc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|integrator_rtc_init
id|__initcall
c_func
(paren
id|integrator_rtc_init
)paren
suffix:semicolon
eof
