multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/time.h&n; *&n; *  Copyright (C) 1998 Russell King.&n; *  Copyright (C) 1998 Phil Blundell&n; *&n; * CATS has a real-time clock, though the evaluation board doesn&squot;t.&n; *&n; * Changelog:&n; *  21-Mar-1998&t;RMK&t;Created&n; *  27-Aug-1998&t;PJB&t;CATS support&n; *  28-Dec-1998&t;APH&t;Made leds optional&n; *  20-Jan-1999&t;RMK&t;Started merge of EBSA285, CATS and NetWinder&n; *  16-Mar-1999&t;RMK&t;More support for EBSA285-like machines with RTCs in&n; */
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;&t;(rtc_base+(x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;&t;0
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &quot;common.h&quot;
DECL|variable|rtc_base
r_static
r_int
id|rtc_base
suffix:semicolon
DECL|function|get_isa_cmos_time
r_static
r_int
r_int
id|__init
id|get_isa_cmos_time
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
singleline_comment|// check to see if the RTC makes sense.....
r_if
c_cond
(paren
(paren
id|CMOS_READ
c_func
(paren
id|RTC_VALID
)paren
op_amp
id|RTC_VRT
)paren
op_eq
l_int|0
)paren
r_return
id|mktime
c_func
(paren
l_int|1970
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* The Linux interpretation of the CMOS clock register contents:&n;&t; * When the Update-In-Progress (UIP) flag goes from 1 to 0, the&n;&t; * RTC registers show the second which has precisely just started.&n;&t; * Let&squot;s hope other operating systems interpret the RTC the same way.&n;&t; */
multiline_comment|/* read RTC exactly on falling edge of update flag */
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
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
r_break
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
multiline_comment|/* must try at least 2.228 ms */
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
)paren
r_break
suffix:semicolon
r_do
(brace
multiline_comment|/* Isn&squot;t this overkill ? UIP above should guarantee consistency */
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
)brace
r_while
c_loop
(paren
id|sec
op_ne
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
)paren
suffix:semicolon
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
DECL|function|set_isa_cmos_time
r_static
r_int
id|set_isa_cmos_time
c_func
(paren
r_void
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
r_char
id|save_control
comma
id|save_freq_select
suffix:semicolon
r_int
r_int
id|nowtime
op_assign
id|xtime.tv_sec
suffix:semicolon
id|save_control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being set */
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
id|save_freq_select
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
multiline_comment|/* stop and reset prescaler */
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
id|cmos_minutes
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
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
id|real_seconds
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
)brace
id|CMOS_WRITE
c_func
(paren
id|real_seconds
comma
id|RTC_SECONDS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|real_minutes
comma
id|RTC_MINUTES
)paren
suffix:semicolon
)brace
r_else
id|retval
op_assign
op_minus
l_int|1
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
r_return
id|retval
suffix:semicolon
)brace
DECL|function|isa_rtc_init
r_void
id|__init
id|isa_rtc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_co285
c_func
(paren
)paren
op_logical_or
id|machine_is_personal_server
c_func
(paren
)paren
)paren
multiline_comment|/*&n;&t;&t; * Add-in 21285s shouldn&squot;t access the RTC&n;&t;&t; */
id|rtc_base
op_assign
l_int|0
suffix:semicolon
r_else
id|rtc_base
op_assign
l_int|0x70
suffix:semicolon
r_if
c_cond
(paren
id|rtc_base
)paren
(brace
r_int
id|reg_d
comma
id|reg_b
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Probe for the RTC.&n;&t;&t; */
id|reg_d
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_REG_D
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * make sure the divider is set&n;&t;&t; */
id|CMOS_WRITE
c_func
(paren
id|RTC_REF_CLCK_32KHZ
comma
id|RTC_REG_A
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set control reg B&n;&t;&t; *   (24 hour mode, update enabled)&n;&t;&t; */
id|reg_b
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_REG_B
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|reg_b
op_or_assign
l_int|2
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|reg_b
comma
id|RTC_REG_B
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|CMOS_READ
c_func
(paren
id|RTC_REG_A
)paren
op_amp
l_int|0x7f
)paren
op_eq
id|RTC_REF_CLCK_32KHZ
op_logical_and
id|CMOS_READ
c_func
(paren
id|RTC_REG_B
)paren
op_eq
id|reg_b
)paren
(brace
r_struct
id|timespec
id|tv
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We have a RTC.  Check the battery&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|reg_d
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;RTC: *** warning: CMOS battery bad&bslash;n&quot;
)paren
suffix:semicolon
id|tv.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|tv.tv_sec
op_assign
id|get_isa_cmos_time
c_func
(paren
)paren
suffix:semicolon
id|do_settimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|set_rtc
op_assign
id|set_isa_cmos_time
suffix:semicolon
)brace
r_else
id|rtc_base
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
