multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Machine dependent access functions for RTC registers.&n; */
macro_line|#ifndef __ASM_MC146818_TIME_H
DECL|macro|__ASM_MC146818_TIME_H
mdefine_line|#define __ASM_MC146818_TIME_H
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/time.h&gt;
multiline_comment|/*&n; * For check timing call set_rtc_mmss() 500ms; used in timer interrupt.&n; */
DECL|macro|USEC_AFTER
mdefine_line|#define USEC_AFTER&t;500000
DECL|macro|USEC_BEFORE
mdefine_line|#define USEC_BEFORE&t;500000
multiline_comment|/*&n; * In order to set the CMOS clock precisely, set_rtc_mmss has to be&n; * called 500 ms after the second nowtime has started, because when&n; * nowtime is written into the registers of the CMOS clock, it will&n; * jump to the next second precisely 500 ms later. Check the Motorola&n; * MC146818A or Dallas DS12887 data sheet for details.&n; *&n; * BUG: This routine does not handle hour overflow properly; it just&n; *      sets the minutes. Usually you&squot;ll only notice that after reboot!&n; */
DECL|function|mc146818_set_rtc_mmss
r_static
r_inline
r_int
id|mc146818_set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
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
id|retval
op_assign
l_int|0
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
DECL|function|mc146818_get_cmos_time
r_static
r_inline
r_int
r_int
id|mc146818_get_cmos_time
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
multiline_comment|/*&n;&t; * The Linux interpretation of the CMOS clock register contents:&n;&t; * When the Update-In-Progress (UIP) flag goes from 1 to 0, the&n;&t; * RTC registers show the second which has precisely just started.&n;&t; * Let&squot;s hope other operating systems interpret the RTC the same way.&n;&t; */
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
macro_line|#endif /* __ASM_MC146818_TIME_H */
eof
