multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/time.c&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
DECL|macro|RTC_DR
mdefine_line|#define RTC_DR&t;&t;(*(unsigned long *)(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 0))
DECL|macro|RTC_MR
mdefine_line|#define RTC_MR&t;&t;(*(unsigned long *)(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 4))
DECL|macro|RTC_STAT
mdefine_line|#define RTC_STAT&t;(*(unsigned long *)(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 8))
DECL|macro|RTC_EOI
mdefine_line|#define RTC_EOI&t;&t;(*(unsigned long *)(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 8))
DECL|macro|RTC_LR
mdefine_line|#define RTC_LR&t;&t;(*(unsigned long *)(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 12))
DECL|macro|RTC_CR
mdefine_line|#define RTC_CR&t;&t;(*(unsigned long *)(IO_ADDRESS(INTEGRATOR_RTC_BASE) + 16))
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
id|RTC_LR
op_assign
id|xtime.tv_sec
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
id|RTC_CR
op_assign
l_int|0
suffix:semicolon
id|RTC_EOI
op_assign
l_int|0
suffix:semicolon
id|xtime.tv_sec
op_assign
id|RTC_DR
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
