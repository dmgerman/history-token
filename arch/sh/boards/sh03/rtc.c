multiline_comment|/*&n; * linux/arch/sh/boards/sh03/rtc.c -- CTP/PCI-SH03 on-chip RTC support&n; *&n; *  Copyright (C) 2004  Saito.K &amp; Jeanne(ksaito@interface.co.jp)&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|RTC_BASE
mdefine_line|#define RTC_BASE&t;0xb0000000
DECL|macro|RTC_SEC1
mdefine_line|#define RTC_SEC1&t;(RTC_BASE + 0)
DECL|macro|RTC_SEC10
mdefine_line|#define RTC_SEC10&t;(RTC_BASE + 1)
DECL|macro|RTC_MIN1
mdefine_line|#define RTC_MIN1&t;(RTC_BASE + 2)
DECL|macro|RTC_MIN10
mdefine_line|#define RTC_MIN10&t;(RTC_BASE + 3)
DECL|macro|RTC_HOU1
mdefine_line|#define RTC_HOU1&t;(RTC_BASE + 4)
DECL|macro|RTC_HOU10
mdefine_line|#define RTC_HOU10&t;(RTC_BASE + 5)
DECL|macro|RTC_WEE1
mdefine_line|#define RTC_WEE1&t;(RTC_BASE + 6)
DECL|macro|RTC_DAY1
mdefine_line|#define RTC_DAY1&t;(RTC_BASE + 7)
DECL|macro|RTC_DAY10
mdefine_line|#define RTC_DAY10&t;(RTC_BASE + 8)
DECL|macro|RTC_MON1
mdefine_line|#define RTC_MON1&t;(RTC_BASE + 9)
DECL|macro|RTC_MON10
mdefine_line|#define RTC_MON10&t;(RTC_BASE + 10)
DECL|macro|RTC_YEA1
mdefine_line|#define RTC_YEA1&t;(RTC_BASE + 11)
DECL|macro|RTC_YEA10
mdefine_line|#define RTC_YEA10&t;(RTC_BASE + 12)
DECL|macro|RTC_YEA100
mdefine_line|#define RTC_YEA100&t;(RTC_BASE + 13)
DECL|macro|RTC_YEA1000
mdefine_line|#define RTC_YEA1000&t;(RTC_BASE + 14)
DECL|macro|RTC_CTL
mdefine_line|#define RTC_CTL&t;&t;(RTC_BASE + 15)
DECL|macro|RTC_BUSY
mdefine_line|#define RTC_BUSY&t;1
DECL|macro|RTC_STOP
mdefine_line|#define RTC_STOP&t;2
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val)&t;((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
r_extern
r_void
(paren
op_star
id|rtc_get_time
)paren
(paren
r_struct
id|timespec
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|rtc_set_time
)paren
(paren
r_const
id|time_t
)paren
suffix:semicolon
r_extern
id|spinlock_t
id|rtc_lock
suffix:semicolon
DECL|function|get_cmos_time
r_int
r_int
id|get_cmos_time
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
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|again
suffix:colon
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
multiline_comment|/* may take up to 1 second... */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctrl_inb
c_func
(paren
id|RTC_CTL
)paren
op_amp
id|RTC_BUSY
)paren
)paren
r_break
suffix:semicolon
r_do
(brace
id|sec
op_assign
(paren
id|ctrl_inb
c_func
(paren
id|RTC_SEC1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_SEC10
)paren
op_amp
l_int|0x7
)paren
op_star
l_int|10
suffix:semicolon
id|min
op_assign
(paren
id|ctrl_inb
c_func
(paren
id|RTC_MIN1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_MIN10
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|10
suffix:semicolon
id|hour
op_assign
(paren
id|ctrl_inb
c_func
(paren
id|RTC_HOU1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_HOU10
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|10
suffix:semicolon
id|day
op_assign
(paren
id|ctrl_inb
c_func
(paren
id|RTC_DAY1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_DAY10
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|10
suffix:semicolon
id|mon
op_assign
(paren
id|ctrl_inb
c_func
(paren
id|RTC_MON1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_MON10
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|10
suffix:semicolon
id|year
op_assign
(paren
id|ctrl_inb
c_func
(paren
id|RTC_YEA1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_YEA10
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|10
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_YEA100
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|100
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_YEA1000
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|1000
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sec
op_ne
(paren
id|ctrl_inb
c_func
(paren
id|RTC_SEC1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_SEC10
)paren
op_amp
l_int|0x7
)paren
op_star
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|year
op_eq
l_int|0
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
l_string|&quot;SH-03 RTC: invalid value, resetting to 1 Jan 2000&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;year=%d, mon=%d, day=%d, hour=%d, min=%d, sec=%d&bslash;n&quot;
comma
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
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_SEC1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_SEC10
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_MIN1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_MIN10
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_HOU1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_HOU10
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|6
comma
id|RTC_WEE1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|RTC_DAY1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_DAY10
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|RTC_MON1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_MON10
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_YEA1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_YEA10
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_YEA100
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|2
comma
id|RTC_YEA1000
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|RTC_CTL
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
)paren
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
DECL|function|sh03_rtc_gettimeofday
r_void
id|sh03_rtc_gettimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
id|tv-&gt;tv_sec
op_assign
id|get_cmos_time
c_func
(paren
)paren
suffix:semicolon
id|tv-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|set_rtc_mmss
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
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
r_int
id|i
suffix:semicolon
multiline_comment|/* gets recalled with irq locally disabled */
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
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
multiline_comment|/* may take up to 1 second... */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctrl_inb
c_func
(paren
id|RTC_CTL
)paren
op_amp
id|RTC_BUSY
)paren
)paren
r_break
suffix:semicolon
id|cmos_minutes
op_assign
(paren
id|ctrl_inb
c_func
(paren
id|RTC_MIN1
)paren
op_amp
l_int|0xf
)paren
op_plus
(paren
id|ctrl_inb
c_func
(paren
id|RTC_MIN10
)paren
op_amp
l_int|0xf
)paren
op_star
l_int|10
suffix:semicolon
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
op_mod
l_int|10
comma
id|RTC_SEC1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|real_seconds
op_div
l_int|10
comma
id|RTC_SEC10
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|real_minutes
op_mod
l_int|10
comma
id|RTC_MIN1
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|real_minutes
op_div
l_int|10
comma
id|RTC_MIN10
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;set_rtc_mmss: can&squot;t update from %d to %d&bslash;n&quot;
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
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sh03_rtc_settimeofday
r_int
id|sh03_rtc_settimeofday
c_func
(paren
r_const
id|time_t
id|secs
)paren
(brace
r_int
r_int
id|nowtime
op_assign
id|secs
suffix:semicolon
r_return
id|set_rtc_mmss
c_func
(paren
id|nowtime
)paren
suffix:semicolon
)brace
DECL|function|sh03_time_init
r_void
id|sh03_time_init
c_func
(paren
r_void
)paren
(brace
id|rtc_get_time
op_assign
id|sh03_rtc_gettimeofday
suffix:semicolon
id|rtc_set_time
op_assign
id|sh03_rtc_settimeofday
suffix:semicolon
)brace
eof
