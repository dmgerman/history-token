multiline_comment|/*&n; *  linux/drivers/acorn/char/pcf8583.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|struct|rtc_tm
r_struct
id|rtc_tm
(brace
DECL|member|cs
r_int
r_char
id|cs
suffix:semicolon
DECL|member|secs
r_int
r_char
id|secs
suffix:semicolon
DECL|member|mins
r_int
r_char
id|mins
suffix:semicolon
DECL|member|hours
r_int
r_char
id|hours
suffix:semicolon
DECL|member|mday
r_int
r_char
id|mday
suffix:semicolon
DECL|member|mon
r_int
r_char
id|mon
suffix:semicolon
DECL|member|year_off
r_int
r_char
id|year_off
suffix:semicolon
DECL|member|wday
r_int
r_char
id|wday
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mem
r_struct
id|mem
(brace
DECL|member|loc
r_int
r_int
id|loc
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RTC_GETDATETIME
mdefine_line|#define RTC_GETDATETIME&t;0
DECL|macro|RTC_SETTIME
mdefine_line|#define RTC_SETTIME&t;1
DECL|macro|RTC_SETDATETIME
mdefine_line|#define RTC_SETDATETIME&t;2
DECL|macro|RTC_GETCTRL
mdefine_line|#define RTC_GETCTRL&t;3
DECL|macro|RTC_SETCTRL
mdefine_line|#define RTC_SETCTRL&t;4
DECL|macro|MEM_READ
mdefine_line|#define MEM_READ&t;5
DECL|macro|MEM_WRITE
mdefine_line|#define MEM_WRITE&t;6
DECL|macro|CTRL_STOP
mdefine_line|#define CTRL_STOP&t;0x80
DECL|macro|CTRL_HOLD
mdefine_line|#define CTRL_HOLD&t;0x40
DECL|macro|CTRL_32KHZ
mdefine_line|#define CTRL_32KHZ&t;0x00
DECL|macro|CTRL_MASK
mdefine_line|#define CTRL_MASK&t;0x08
DECL|macro|CTRL_ALARMEN
mdefine_line|#define CTRL_ALARMEN&t;0x04
DECL|macro|CTRL_ALARM
mdefine_line|#define CTRL_ALARM&t;0x02
DECL|macro|CTRL_TIMER
mdefine_line|#define CTRL_TIMER&t;0x01
eof
