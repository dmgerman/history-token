multiline_comment|/* $Id: rtc.h,v 1.3 2001/03/21 09:56:31 magnusmn Exp $ */
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
DECL|macro|RTC_CONTROL
mdefine_line|#define RTC_CONTROL 7
multiline_comment|/* Bits in CONTROL register */
DECL|macro|RTC_CONTROL_WRITEPROTECT
mdefine_line|#define RTC_CONTROL_WRITEPROTECT 0x80
DECL|macro|RTC_TRICKLECHARGER
mdefine_line|#define RTC_TRICKLECHARGER 8
multiline_comment|/* Bits in TRICKLECHARGER register TCS TCS TCS TCS DS DS RS RS */
DECL|macro|RTC_TCR_PATTERN
mdefine_line|#define   RTC_TCR_PATTERN 0xA0 /* 1010xxxx */
DECL|macro|RTC_TCR_1DIOD
mdefine_line|#define   RTC_TCR_1DIOD 0x04 /* xxxx01xx */
DECL|macro|RTC_TCR_2DIOD
mdefine_line|#define   RTC_TCR_2DIOD 0x08 /* xxxx10xx */
DECL|macro|RTC_TCR_DISABLED
mdefine_line|#define   RTC_TCR_DISABLED 0x00 /* xxxxxx00 Disabled */
DECL|macro|RTC_TCR_2KOHM
mdefine_line|#define   RTC_TCR_2KOHM 0x01      /* xxxxxx01 2KOhm */
DECL|macro|RTC_TCR_4KOHM
mdefine_line|#define   RTC_TCR_4KOHM 0x02      /* xxxxxx10 4kOhm */
DECL|macro|RTC_TCR_8KOHM
mdefine_line|#define   RTC_TCR_8KOHM 0x03      /* xxxxxx11 8kOhm */
macro_line|#ifdef CONFIG_ETRAX_DS1302
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
DECL|macro|RTC_SET_CHARGE
mdefine_line|#define RTC_SET_CHARGE  _IOW(&squot;p&squot;, 0x0b, int) /* Set CHARGE mode    */
macro_line|#endif
eof
