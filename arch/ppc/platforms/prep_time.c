multiline_comment|/*&n; *  arch/ppc/platforms/prep_time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *&n; * Adapted for PowerPC (PReP) by Gary Thomas&n; * Modified by Cort Dougan (cort@cs.nmt.edu).&n; * Copied and modified from arch/i386/kernel/time.c&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/prep_nvram.h&gt;
macro_line|#include &lt;asm/mk48t59.h&gt;
macro_line|#include &lt;asm/time.h&gt;
r_extern
id|spinlock_t
id|rtc_lock
suffix:semicolon
multiline_comment|/*&n; * The motorola uses the m48t18 rtc (includes DS1643) whose registers&n; * are at a higher end of nvram (1ff8-1fff) than the ibm mc146818&n; * rtc (ds1386) which has regs at addr 0-d).  The intel gets&n; * past this because the bios emulates the mc146818.&n; *&n; * Why in the world did they have to use different clocks?&n; *&n; * Right now things are hacked to check which machine we&squot;re on then&n; * use the appropriate macro.  This is very very ugly and I should&n; * probably have a function that checks which machine we&squot;re on then&n; * does things correctly transparently or a function pointer which&n; * is setup at boot time to use the correct addresses.&n; * -- Cort&n; */
multiline_comment|/*&n; * Set the hardware clock. -- Cort&n; */
id|__prep
DECL|function|mc146818_set_rtc_time
r_int
id|mc146818_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
r_char
id|save_control
comma
id|save_freq_select
suffix:semicolon
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|to_tm
c_func
(paren
id|nowtime
comma
op_amp
id|tm
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being set */
id|save_control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
(paren
id|save_control
op_or
id|RTC_SET
)paren
comma
id|RTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* stop and reset prescaler */
id|save_freq_select
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
(paren
id|save_freq_select
op_or
id|RTC_DIV_RESET2
)paren
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|tm.tm_year
op_assign
(paren
id|tm.tm_year
op_minus
l_int|1900
)paren
op_mod
l_int|100
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mon
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mday
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_year
)paren
suffix:semicolon
)brace
id|CMOS_WRITE
c_func
(paren
id|tm.tm_sec
comma
id|RTC_SECONDS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|tm.tm_min
comma
id|RTC_MINUTES
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|tm.tm_hour
comma
id|RTC_HOURS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|tm.tm_mon
comma
id|RTC_MONTH
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|tm.tm_mday
comma
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|tm.tm_year
comma
id|RTC_YEAR
)paren
suffix:semicolon
multiline_comment|/* The following flags have to be released exactly in this order,&n;&t; * otherwise the DS12887 (popular MC146818A clone with integrated&n;&t; * battery and quartz) will not reset the oscillator and will not&n;&t; * update precisely 500 ms later. You won&squot;t find this mentioned in&n;&t; * the Dallas Semiconductor data sheets, but who believes data&n;&t; * sheets anyway ...                           -- Markus Kuhn&n;&t; */
id|CMOS_WRITE
c_func
(paren
id|save_control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|save_freq_select
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__prep
DECL|function|mc146818_get_rtc_time
r_int
r_int
id|mc146818_get_rtc_time
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
r_int
id|uip
comma
id|i
suffix:semicolon
multiline_comment|/* The Linux interpretation of the CMOS clock register contents:&n;&t; * When the Update-In-Progress (UIP) flag goes from 1 to 0, the&n;&t; * RTC registers show the second which has precisely just started.&n;&t; * Let&squot;s hope other operating systems interpret the RTC the same way.&n;&t; */
multiline_comment|/* Since the UIP flag is set for about 2.2 ms and the clock&n;&t; * is typically written with a precision of 1 jiffy, trying&n;&t; * to obtain a precision better than a few milliseconds is &n;&t; * an illusion. Only consistency is interesting, this also&n;&t; * allows to use the routine for /dev/rtc without a potential&n;&t; * 1 second kernel busy loop triggered by any reader of /dev/rtc. &n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|uip
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|sec
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mon
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
id|uip
op_or_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|uip
op_amp
id|RTC_UIP
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|year
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|year
op_add_assign
l_int|1900
)paren
OL
l_int|1970
)paren
id|year
op_add_assign
l_int|100
suffix:semicolon
r_return
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
id|__prep
DECL|function|mk48t59_set_rtc_time
r_int
id|mk48t59_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
r_char
id|save_control
suffix:semicolon
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|to_tm
c_func
(paren
id|nowtime
comma
op_amp
id|tm
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being written */
id|save_control
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_CONTROLA
)paren
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_CONTROLA
comma
(paren
id|save_control
op_or
id|MK48T59_RTC_CA_WRITE
)paren
)paren
suffix:semicolon
id|tm.tm_year
op_assign
(paren
id|tm.tm_year
op_minus
l_int|1900
)paren
op_mod
l_int|100
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mon
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mday
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_year
)paren
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_SECONDS
comma
id|tm.tm_sec
)paren
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_MINUTES
comma
id|tm.tm_min
)paren
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_HOURS
comma
id|tm.tm_hour
)paren
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_MONTH
comma
id|tm.tm_mon
)paren
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_DAY_OF_MONTH
comma
id|tm.tm_mday
)paren
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_YEAR
comma
id|tm.tm_year
)paren
suffix:semicolon
multiline_comment|/* Turn off the write bit. */
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_CONTROLA
comma
id|save_control
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__prep
DECL|function|mk48t59_get_rtc_time
r_int
r_int
id|mk48t59_get_rtc_time
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|save_control
suffix:semicolon
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
multiline_comment|/* Simple: freeze the clock, read it and allow updates again */
id|save_control
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_CONTROLA
)paren
suffix:semicolon
id|save_control
op_and_assign
op_complement
id|MK48T59_RTC_CA_READ
suffix:semicolon
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_CONTROLA
comma
id|save_control
)paren
suffix:semicolon
multiline_comment|/* Set the register to read the value. */
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_CONTROLA
comma
(paren
id|save_control
op_or
id|MK48T59_RTC_CA_READ
)paren
)paren
suffix:semicolon
id|sec
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mon
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|MK48T59_RTC_YEAR
)paren
suffix:semicolon
multiline_comment|/* Let the time values change again. */
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|MK48T59_RTC_CONTROLA
comma
id|save_control
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|year
)paren
suffix:semicolon
id|year
op_assign
id|year
op_plus
l_int|1900
suffix:semicolon
r_if
c_cond
(paren
id|year
OL
l_int|1970
)paren
(brace
id|year
op_add_assign
l_int|100
suffix:semicolon
)brace
r_return
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
eof
