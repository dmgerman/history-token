multiline_comment|/* $Id: rtc.h,v 1.1.1.1 2004/03/25 04:29:22 hitoshiy Exp $ */
macro_line|#ifndef __RTC_H__
DECL|macro|__RTC_H__
mdefine_line|#define __RTC_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Dallas DS1302 clock/calendar register numbers. */
DECL|macro|RTC_SECONDS
macro_line|#  define RTC_SECONDS      0
DECL|macro|RTC_MINUTES
macro_line|#  define RTC_MINUTES      1
DECL|macro|RTC_HOURS
macro_line|#  define RTC_HOURS        2
DECL|macro|RTC_DAY_OF_MONTH
macro_line|#  define RTC_DAY_OF_MONTH 3
DECL|macro|RTC_MONTH
macro_line|#  define RTC_MONTH        4
DECL|macro|RTC_WEEKDAY
macro_line|#  define RTC_WEEKDAY      5
DECL|macro|RTC_YEAR
macro_line|#  define RTC_YEAR         6
DECL|macro|RTC_CONTROL
macro_line|#  define RTC_CONTROL      7
multiline_comment|/* Bits in CONTROL register. */
DECL|macro|RTC_CONTROL_WRITEPROTECT
macro_line|#  define RTC_CONTROL_WRITEPROTECT &t;0x80
DECL|macro|RTC_TRICKLECHARGER
macro_line|#  define RTC_TRICKLECHARGER &t;&t;8
multiline_comment|/* Bits in TRICKLECHARGER register TCS TCS TCS TCS DS DS RS RS. */
DECL|macro|RTC_TCR_PATTERN
macro_line|#  define RTC_TCR_PATTERN &t;0xA0&t;/* 1010xxxx */
DECL|macro|RTC_TCR_1DIOD
macro_line|#  define RTC_TCR_1DIOD &t;0x04&t;/* xxxx01xx */
DECL|macro|RTC_TCR_2DIOD
macro_line|#  define RTC_TCR_2DIOD &t;0x08&t;/* xxxx10xx */
DECL|macro|RTC_TCR_DISABLED
macro_line|#  define RTC_TCR_DISABLED &t;0x00&t;/* xxxxxx00 Disabled */
DECL|macro|RTC_TCR_2KOHM
macro_line|#  define RTC_TCR_2KOHM &t;0x01&t;/* xxxxxx01 2KOhm */
DECL|macro|RTC_TCR_4KOHM
macro_line|#  define RTC_TCR_4KOHM &t;0x02&t;/* xxxxxx10 4kOhm */
DECL|macro|RTC_TCR_8KOHM
macro_line|#  define RTC_TCR_8KOHM &t;0x03&t;/* xxxxxx11 8kOhm */
macro_line|#ifdef CONFIG_M32700UT_DS1302
r_extern
r_int
r_char
id|ds1302_readreg
c_func
(paren
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|ds1302_writereg
c_func
(paren
r_int
id|reg
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
id|ds1302_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|CMOS_READ
macro_line|#  define CMOS_READ(x) ds1302_readreg(x)
DECL|macro|CMOS_WRITE
macro_line|#  define CMOS_WRITE(val,reg) ds1302_writereg(reg,val)
DECL|macro|RTC_INIT
macro_line|#  define RTC_INIT() ds1302_init()
macro_line|#else
multiline_comment|/* No RTC configured so we shouldn&squot;t try to access any. */
DECL|macro|CMOS_READ
macro_line|#  define CMOS_READ(x) 42
DECL|macro|CMOS_WRITE
macro_line|#  define CMOS_WRITE(x,y)
DECL|macro|RTC_INIT
macro_line|#  define RTC_INIT() (-1)
macro_line|#endif
multiline_comment|/*&n; * The struct used to pass data via the following ioctl. Similar to the&n; * struct tm in &lt;time.h&gt;, but it needs to be here so that the kernel&n; * source is self contained, allowing cross-compiles, etc. etc.&n; */
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
multiline_comment|/* ioctl() calls that are permitted to the /dev/rtc interface. */
DECL|macro|RTC_MAGIC
mdefine_line|#define RTC_MAGIC &squot;p&squot;
DECL|macro|RTC_RD_TIME
mdefine_line|#define RTC_RD_TIME&t;&t;_IOR(RTC_MAGIC, 0x09, struct rtc_time)&t;/* Read RTC time. */
DECL|macro|RTC_SET_TIME
mdefine_line|#define RTC_SET_TIME&t;&t;_IOW(RTC_MAGIC, 0x0a, struct rtc_time)&t;/* Set RTC time. */
DECL|macro|RTC_SET_CHARGE
mdefine_line|#define RTC_SET_CHARGE  &t;_IOW(RTC_MAGIC, 0x0b, int)
DECL|macro|RTC_MAX_IOCTL
mdefine_line|#define RTC_MAX_IOCTL 0x0b
macro_line|#endif /* __RTC_H__ */
eof
