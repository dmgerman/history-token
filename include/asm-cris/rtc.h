multiline_comment|/* $Id: rtc.h,v 1.1 2000/07/10 16:32:31 bjornw Exp $ */
macro_line|#ifndef RTC_H
DECL|macro|RTC_H
mdefine_line|#define RTC_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Dallas DS1302 clock/calendar register numbers */
DECL|macro|RTC_SECONDS
mdefine_line|#define RTC_SECONDS 0
DECL|macro|RTC_MINUTES
mdefine_line|#define RTC_MINUTES 1
DECL|macro|RTC_HOURS
mdefine_line|#define RTC_HOURS 2
DECL|macro|RTC_DAY_OF_MONTH
mdefine_line|#define RTC_DAY_OF_MONTH 3
DECL|macro|RTC_MONTH
mdefine_line|#define RTC_MONTH 4
DECL|macro|RTC_WEEKDAY
mdefine_line|#define RTC_WEEKDAY 5
DECL|macro|RTC_YEAR
mdefine_line|#define RTC_YEAR 6
macro_line|#ifdef CONFIG_DS1302
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(x) ds1302_readreg(x)
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val,reg) ds1302_writereg(reg,val)
DECL|macro|RTC_INIT
mdefine_line|#define RTC_INIT() ds1302_init()
macro_line|#else
multiline_comment|/* no RTC configured so we shouldn&squot;t try to access any */
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(x) 42
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(x,y)
DECL|macro|RTC_INIT
mdefine_line|#define RTC_INIT() (-1)
macro_line|#endif
multiline_comment|/* conversions to and from the stupid RTC internal format */
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(x) x = (((x &amp; 0xf0) &gt;&gt; 3) * 5 + (x &amp; 0xf))
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(x) x = (x % 10) | ((x / 10) &lt;&lt; 4) 
multiline_comment|/*&n; * The struct used to pass data via the following ioctl. Similar to the&n; * struct tm in &lt;time.h&gt;, but it needs to be here so that the kernel &n; * source is self contained, allowing cross-compiles, etc. etc.&n; */
DECL|struct|rtc_time
r_struct
id|rtc_time
(brace
DECL|member|tm_sec
r_int
id|tm_sec
suffix:semicolon
DECL|member|tm_min
r_int
id|tm_min
suffix:semicolon
DECL|member|tm_hour
r_int
id|tm_hour
suffix:semicolon
DECL|member|tm_mday
r_int
id|tm_mday
suffix:semicolon
DECL|member|tm_mon
r_int
id|tm_mon
suffix:semicolon
DECL|member|tm_year
r_int
id|tm_year
suffix:semicolon
DECL|member|tm_wday
r_int
id|tm_wday
suffix:semicolon
DECL|member|tm_yday
r_int
id|tm_yday
suffix:semicolon
DECL|member|tm_isdst
r_int
id|tm_isdst
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ioctl calls that are permitted to the /dev/rtc interface&n; */
DECL|macro|RTC_RD_TIME
mdefine_line|#define RTC_RD_TIME&t;_IOR(&squot;p&squot;, 0x09, struct rtc_time) /* Read RTC time   */
DECL|macro|RTC_SET_TIME
mdefine_line|#define RTC_SET_TIME&t;_IOW(&squot;p&squot;, 0x0a, struct rtc_time) /* Set RTC time    */
macro_line|#endif
eof
