multiline_comment|/*&n; * ds1742rtc.h - register definitions for the Real-Time-Clock / CMOS RAM&n; *&n; *   Based on include/asm-mips/ds1643rtc.h.&n; *&n; * Copyright (C) 1999-2001 Toshiba Corporation&n; * It was written to be part of the Linux operating system.&n; */
multiline_comment|/* permission is hereby granted to copy, modify and redistribute this code&n; * in terms of the GNU Library General Public License, Version 2 or later,&n; * at your option.&n; */
macro_line|#ifndef _DS1742RTC_H
DECL|macro|_DS1742RTC_H
mdefine_line|#define _DS1742RTC_H
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;&t;/* bad name... */
DECL|macro|RTC_BRAM_SIZE
mdefine_line|#define RTC_BRAM_SIZE&t;&t;0x800
DECL|macro|RTC_OFFSET
mdefine_line|#define RTC_OFFSET&t;&t;0x7f8
multiline_comment|/**********************************************************************&n; * register summary&n; **********************************************************************/
DECL|macro|RTC_CONTROL
mdefine_line|#define RTC_CONTROL&t;&t;(RTC_OFFSET + 0)
DECL|macro|RTC_CENTURY
mdefine_line|#define RTC_CENTURY&t;&t;(RTC_OFFSET + 0)
DECL|macro|RTC_SECONDS
mdefine_line|#define RTC_SECONDS&t;&t;(RTC_OFFSET + 1)
DECL|macro|RTC_MINUTES
mdefine_line|#define RTC_MINUTES&t;&t;(RTC_OFFSET + 2)
DECL|macro|RTC_HOURS
mdefine_line|#define RTC_HOURS&t;&t;(RTC_OFFSET + 3)
DECL|macro|RTC_DAY
mdefine_line|#define RTC_DAY&t;&t;&t;(RTC_OFFSET + 4)
DECL|macro|RTC_DATE
mdefine_line|#define RTC_DATE&t;&t;(RTC_OFFSET + 5)
DECL|macro|RTC_MONTH
mdefine_line|#define RTC_MONTH&t;&t;(RTC_OFFSET + 6)
DECL|macro|RTC_YEAR
mdefine_line|#define RTC_YEAR&t;&t;(RTC_OFFSET + 7)
DECL|macro|RTC_CENTURY_MASK
mdefine_line|#define RTC_CENTURY_MASK&t;0x3f
DECL|macro|RTC_SECONDS_MASK
mdefine_line|#define RTC_SECONDS_MASK&t;0x7f
DECL|macro|RTC_DAY_MASK
mdefine_line|#define RTC_DAY_MASK&t;&t;0x07
multiline_comment|/*&n; * Bits in the Control/Century register&n; */
DECL|macro|RTC_WRITE
mdefine_line|#define RTC_WRITE&t;&t;0x80
DECL|macro|RTC_READ
mdefine_line|#define RTC_READ&t;&t;0x40
multiline_comment|/*&n; * Bits in the Seconds register&n; */
DECL|macro|RTC_STOP
mdefine_line|#define RTC_STOP&t;&t;0x80
multiline_comment|/*&n; * Bits in the Day register&n; */
DECL|macro|RTC_BATT_FLAG
mdefine_line|#define RTC_BATT_FLAG&t;&t;0x80
DECL|macro|RTC_FREQ_TEST
mdefine_line|#define RTC_FREQ_TEST&t;&t;0x40
multiline_comment|/*&n; * Conversion between binary and BCD.&n; */
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
macro_line|#endif /* _DS1742RTC_H */
eof
