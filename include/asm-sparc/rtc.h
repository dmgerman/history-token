multiline_comment|/* $Id: rtc.h,v 1.2 1996/08/21 23:17:39 ecd Exp $&n; *&n; * rtc.h: Definitions for access to the Mostek real time clock&n; *&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; */
macro_line|#ifndef _RTC_H
DECL|macro|_RTC_H
mdefine_line|#define _RTC_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|struct|rtc_time
r_struct
id|rtc_time
(brace
DECL|member|sec
r_int
id|sec
suffix:semicolon
multiline_comment|/* Seconds (0-59) */
DECL|member|min
r_int
id|min
suffix:semicolon
multiline_comment|/* Minutes (0-59) */
DECL|member|hour
r_int
id|hour
suffix:semicolon
multiline_comment|/* Hour (0-23) */
DECL|member|dow
r_int
id|dow
suffix:semicolon
multiline_comment|/* Day of the week (1-7) */
DECL|member|dom
r_int
id|dom
suffix:semicolon
multiline_comment|/* Day of the month (1-31) */
DECL|member|month
r_int
id|month
suffix:semicolon
multiline_comment|/* Month of year (1-12) */
DECL|member|year
r_int
id|year
suffix:semicolon
multiline_comment|/* Year (0-99) */
)brace
suffix:semicolon
DECL|macro|RTCGET
mdefine_line|#define RTCGET _IOR(&squot;p&squot;, 20, struct rtc_time)
DECL|macro|RTCSET
mdefine_line|#define RTCSET _IOW(&squot;p&squot;, 21, struct rtc_time)
macro_line|#endif
eof
