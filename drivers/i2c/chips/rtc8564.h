multiline_comment|/*&n; *  linux/drivers/i2c/chips/rtc8564.h&n; *&n; *  Copyright (C) 2002-2004 Stefan Eletzhofer&n; *&n; *&t;based on linux/drivers/acron/char/pcf8583.h&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|struct|rtc_tm
r_struct
id|rtc_tm
(brace
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
DECL|member|year
r_int
r_int
id|year
suffix:semicolon
multiline_comment|/* xxxx 4 digits :) */
DECL|member|wday
r_int
r_char
id|wday
suffix:semicolon
DECL|member|vl
r_int
r_char
id|vl
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
DECL|macro|RTC8564_REG_CTRL1
mdefine_line|#define RTC8564_REG_CTRL1&t;&t;0x0 /* T  0 S 0 | T 0 0 0 */
DECL|macro|RTC8564_REG_CTRL2
mdefine_line|#define RTC8564_REG_CTRL2&t;&t;0x1 /* 0  0 0 TI/TP | AF TF AIE TIE */
DECL|macro|RTC8564_REG_SEC
mdefine_line|#define RTC8564_REG_SEC&t;&t;&t;0x2 /* VL 4 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_MIN
mdefine_line|#define RTC8564_REG_MIN&t;&t;&t;0x3 /* x  4 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_HR
mdefine_line|#define RTC8564_REG_HR&t;&t;&t;0x4 /* x  x 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_DAY
mdefine_line|#define RTC8564_REG_DAY&t;&t;&t;0x5 /* x  x 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_WDAY
mdefine_line|#define RTC8564_REG_WDAY&t;&t;0x6 /* x  x x x | x 4 2 1 */
DECL|macro|RTC8564_REG_MON_CENT
mdefine_line|#define RTC8564_REG_MON_CENT&t;0x7 /* C  x x 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_YEAR
mdefine_line|#define RTC8564_REG_YEAR&t;&t;0x8 /* 8  4 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_AL_MIN
mdefine_line|#define RTC8564_REG_AL_MIN&t;&t;0x9 /* AE 4 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_AL_HR
mdefine_line|#define RTC8564_REG_AL_HR&t;&t;0xa /* AE 4 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_AL_DAY
mdefine_line|#define RTC8564_REG_AL_DAY&t;&t;0xb /* AE x 2 1 | 8 4 2 1 */
DECL|macro|RTC8564_REG_AL_WDAY
mdefine_line|#define RTC8564_REG_AL_WDAY&t;&t;0xc /* AE x x x | x 4 2 1 */
DECL|macro|RTC8564_REG_CLKOUT
mdefine_line|#define RTC8564_REG_CLKOUT&t;&t;0xd /* FE x x x | x x FD1 FD0 */
DECL|macro|RTC8564_REG_TCTL
mdefine_line|#define RTC8564_REG_TCTL&t;&t;0xe /* TE x x x | x x FD1 FD0 */
DECL|macro|RTC8564_REG_TIMER
mdefine_line|#define RTC8564_REG_TIMER&t;&t;0xf /* 8 bit binary */
multiline_comment|/* Control reg */
DECL|macro|RTC8564_CTRL1_TEST1
mdefine_line|#define RTC8564_CTRL1_TEST1&t;&t;(1&lt;&lt;3)
DECL|macro|RTC8564_CTRL1_STOP
mdefine_line|#define RTC8564_CTRL1_STOP&t;&t;(1&lt;&lt;5)
DECL|macro|RTC8564_CTRL1_TEST2
mdefine_line|#define RTC8564_CTRL1_TEST2&t;&t;(1&lt;&lt;7)
DECL|macro|RTC8564_CTRL2_TIE
mdefine_line|#define RTC8564_CTRL2_TIE&t;&t;(1&lt;&lt;0)
DECL|macro|RTC8564_CTRL2_AIE
mdefine_line|#define RTC8564_CTRL2_AIE&t;&t;(1&lt;&lt;1)
DECL|macro|RTC8564_CTRL2_TF
mdefine_line|#define RTC8564_CTRL2_TF&t;&t;(1&lt;&lt;2)
DECL|macro|RTC8564_CTRL2_AF
mdefine_line|#define RTC8564_CTRL2_AF&t;&t;(1&lt;&lt;3)
DECL|macro|RTC8564_CTRL2_TI_TP
mdefine_line|#define RTC8564_CTRL2_TI_TP&t;&t;(1&lt;&lt;4)
multiline_comment|/* CLKOUT frequencies */
DECL|macro|RTC8564_FD_32768HZ
mdefine_line|#define RTC8564_FD_32768HZ&t;&t;(0x0)
DECL|macro|RTC8564_FD_1024HZ
mdefine_line|#define RTC8564_FD_1024HZ&t;&t;(0x1)
DECL|macro|RTC8564_FD_32
mdefine_line|#define RTC8564_FD_32&t;&t;&t;(0x2)
DECL|macro|RTC8564_FD_1HZ
mdefine_line|#define RTC8564_FD_1HZ&t;&t;&t;(0x3)
multiline_comment|/* Timer CTRL */
DECL|macro|RTC8564_TD_4096HZ
mdefine_line|#define RTC8564_TD_4096HZ&t;&t;(0x0)
DECL|macro|RTC8564_TD_64HZ
mdefine_line|#define RTC8564_TD_64HZ&t;&t;&t;(0x1)
DECL|macro|RTC8564_TD_1HZ
mdefine_line|#define RTC8564_TD_1HZ&t;&t;&t;(0x2)
DECL|macro|RTC8564_TD_1_60HZ
mdefine_line|#define RTC8564_TD_1_60HZ&t;&t;(0x3)
DECL|macro|I2C_DRIVERID_RTC8564
mdefine_line|#define I2C_DRIVERID_RTC8564 0xf000
eof
