multiline_comment|/*&n; * linux/arch/sh/kernel/rtc.c -- SH3 / SH4 on-chip RTC support&n; *&n; *  Copyright (C) 2000  Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *  Copyright (C) 1999  Tetsuya Okada &amp; Niibe Yutaka&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
DECL|function|sh_rtc_gettimeofday
r_void
id|sh_rtc_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_int
r_int
id|sec128
comma
id|sec
comma
id|min
comma
id|hr
comma
id|wk
comma
id|day
comma
id|mon
comma
id|yr
comma
id|yr100
suffix:semicolon
id|again
suffix:colon
r_do
(brace
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RCR1
)paren
suffix:semicolon
multiline_comment|/* Clear CF-bit */
id|sec128
op_assign
id|ctrl_inb
c_func
(paren
id|R64CNT
)paren
suffix:semicolon
id|sec
op_assign
id|ctrl_inb
c_func
(paren
id|RSECCNT
)paren
suffix:semicolon
id|min
op_assign
id|ctrl_inb
c_func
(paren
id|RMINCNT
)paren
suffix:semicolon
id|hr
op_assign
id|ctrl_inb
c_func
(paren
id|RHRCNT
)paren
suffix:semicolon
id|wk
op_assign
id|ctrl_inb
c_func
(paren
id|RWKCNT
)paren
suffix:semicolon
id|day
op_assign
id|ctrl_inb
c_func
(paren
id|RDAYCNT
)paren
suffix:semicolon
id|mon
op_assign
id|ctrl_inb
c_func
(paren
id|RMONCNT
)paren
suffix:semicolon
macro_line|#if defined(__SH4__)
id|yr
op_assign
id|ctrl_inw
c_func
(paren
id|RYRCNT
)paren
suffix:semicolon
id|yr100
op_assign
(paren
id|yr
op_rshift
l_int|8
)paren
suffix:semicolon
id|yr
op_and_assign
l_int|0xff
suffix:semicolon
macro_line|#else
id|yr
op_assign
id|ctrl_inb
c_func
(paren
id|RYRCNT
)paren
suffix:semicolon
id|yr100
op_assign
(paren
id|yr
op_eq
l_int|0x99
)paren
ques
c_cond
l_int|0x19
suffix:colon
l_int|0x20
suffix:semicolon
macro_line|#endif
)brace
r_while
c_loop
(paren
(paren
id|ctrl_inb
c_func
(paren
id|RCR1
)paren
op_amp
id|RCR1_CF
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#if RTC_BIT_INVERTED != 0
multiline_comment|/* Work around to avoid reading incorrect value. */
r_if
c_cond
(paren
id|sec128
op_eq
id|RTC_BIT_INVERTED
)paren
(brace
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
macro_line|#endif
id|BCD_TO_BIN
c_func
(paren
id|yr100
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|yr
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
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hr
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
id|sec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|yr
OG
l_int|99
op_logical_or
id|mon
template_param
l_int|12
op_logical_or
id|day
OG
l_int|31
op_logical_or
id|day
template_param
l_int|23
op_logical_or
id|min
OG
l_int|59
op_logical_or
id|sec
OG
l_int|59
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SH RTC: invalid value, resetting to 1 Jan 2000&bslash;n&quot;
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|RCR2_RESET
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Reset &amp; Stop */
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RSECCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RMINCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RHRCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|6
comma
id|RWKCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|RDAYCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|RMONCNT
)paren
suffix:semicolon
macro_line|#if defined(__SH4__)
id|ctrl_outw
c_func
(paren
l_int|0x2000
comma
id|RYRCNT
)paren
suffix:semicolon
macro_line|#else
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RYRCNT
)paren
suffix:semicolon
macro_line|#endif
id|ctrl_outb
c_func
(paren
id|RCR2_RTCEN
op_or
id|RCR2_START
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Start */
r_goto
id|again
suffix:semicolon
)brace
macro_line|#if RTC_BIT_INVERTED != 0
r_if
c_cond
(paren
(paren
id|sec128
op_amp
id|RTC_BIT_INVERTED
)paren
)paren
id|sec
op_decrement
suffix:semicolon
macro_line|#endif
id|tv-&gt;tv_sec
op_assign
id|mktime
c_func
(paren
id|yr100
op_star
l_int|100
op_plus
id|yr
comma
id|mon
comma
id|day
comma
id|hr
comma
id|min
comma
id|sec
)paren
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
(paren
id|sec128
op_star
l_int|1000000
)paren
op_div
l_int|128
suffix:semicolon
)brace
DECL|function|sh_rtc_settimeofday
r_int
id|sh_rtc_settimeofday
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_int
r_int
id|nowtime
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|real_seconds
comma
id|real_minutes
comma
id|cmos_minutes
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|RCR2_RESET
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Reset pre-scaler &amp; stop RTC */
id|cmos_minutes
op_assign
id|ctrl_inb
c_func
(paren
id|RMINCNT
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|cmos_minutes
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * since we&squot;re only adjusting minutes and seconds,&n;&t; * don&squot;t interfere with hour overflow. This avoids&n;&t; * messing with unknown time zones but requires your&n;&t; * RTC not to be off by more than 15 minutes&n;&t; */
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
OL
l_int|30
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|real_seconds
comma
id|RSECCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|real_minutes
comma
id|RMINCNT
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;set_rtc_time: can&squot;t update from %d to %d&bslash;n&quot;
comma
id|cmos_minutes
comma
id|real_minutes
)paren
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|ctrl_outb
c_func
(paren
id|RCR2_RTCEN
op_or
id|RCR2_START
comma
id|RCR2
)paren
suffix:semicolon
multiline_comment|/* Start RTC */
r_return
id|retval
suffix:semicolon
)brace
eof
