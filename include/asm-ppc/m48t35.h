multiline_comment|/*&n; * BK Id: SCCS/s.m48t35.h 1.5 05/17/01 18:14:25 cort&n; */
multiline_comment|/*&n; *  Registers for the SGS-Thomson M48T35 Timekeeper RAM chip&n; */
macro_line|#ifndef __PPC_M48T35_H
DECL|macro|__PPC_M48T35_H
mdefine_line|#define __PPC_M48T35_H
multiline_comment|/* RTC offsets */
DECL|macro|M48T35_RTC_CONTROL
mdefine_line|#define M48T35_RTC_CONTROL  0
DECL|macro|M48T35_RTC_SECONDS
mdefine_line|#define M48T35_RTC_SECONDS  1
DECL|macro|M48T35_RTC_MINUTES
mdefine_line|#define M48T35_RTC_MINUTES  2
DECL|macro|M48T35_RTC_HOURS
mdefine_line|#define M48T35_RTC_HOURS    3
DECL|macro|M48T35_RTC_DAY
mdefine_line|#define M48T35_RTC_DAY      4
DECL|macro|M48T35_RTC_DOM
mdefine_line|#define M48T35_RTC_DOM      5
DECL|macro|M48T35_RTC_MONTH
mdefine_line|#define M48T35_RTC_MONTH    6
DECL|macro|M48T35_RTC_YEAR
mdefine_line|#define M48T35_RTC_YEAR     7
DECL|macro|M48T35_RTC_SET
mdefine_line|#define M48T35_RTC_SET      0x80
DECL|macro|M48T35_RTC_STOPPED
mdefine_line|#define M48T35_RTC_STOPPED  0x80
DECL|macro|M48T35_RTC_READ
mdefine_line|#define M48T35_RTC_READ     0x40
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(x)   ((x)=((x)&amp;15) + ((x)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(x)   ((x)=(((x)/10)&lt;&lt;4) + (x)%10)
macro_line|#endif
macro_line|#endif
eof
