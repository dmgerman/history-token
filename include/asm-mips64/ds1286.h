multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * mc146818rtc.h - register definitions for the Real-Time-Clock / CMOS RAM&n; * Copyright Torsten Duwe &lt;duwe@informatik.uni-erlangen.de&gt; 1993&n; * derived from Data Sheet, Copyright Motorola 1984 (!).&n; * It was written to be part of the Linux operating system.&n; *&n; * Copyright (C) 1998, 1999 Ralf Baechle&n; */
macro_line|#ifndef _ASM_DS1286_h
DECL|macro|_ASM_DS1286_h
mdefine_line|#define _ASM_DS1286_h
macro_line|#include &lt;asm/mc146818rtc.h&gt;
multiline_comment|/**********************************************************************&n; * register summary&n; **********************************************************************/
DECL|macro|RTC_HUNDREDTH_SECOND
mdefine_line|#define RTC_HUNDREDTH_SECOND&t;0
DECL|macro|RTC_SECONDS
mdefine_line|#define RTC_SECONDS&t;&t;1
DECL|macro|RTC_MINUTES
mdefine_line|#define RTC_MINUTES&t;&t;2
DECL|macro|RTC_MINUTES_ALARM
mdefine_line|#define RTC_MINUTES_ALARM&t;3
DECL|macro|RTC_HOURS
mdefine_line|#define RTC_HOURS&t;&t;4
DECL|macro|RTC_HOURS_ALARM
mdefine_line|#define RTC_HOURS_ALARM&t;&t;5
DECL|macro|RTC_DAY
mdefine_line|#define RTC_DAY&t;&t;&t;6
DECL|macro|RTC_DAY_ALARM
mdefine_line|#define RTC_DAY_ALARM&t;&t;7
DECL|macro|RTC_DATE
mdefine_line|#define RTC_DATE&t;&t;8
DECL|macro|RTC_MONTH
mdefine_line|#define RTC_MONTH&t;&t;9
DECL|macro|RTC_YEAR
mdefine_line|#define RTC_YEAR&t;&t;10
DECL|macro|RTC_CMD
mdefine_line|#define RTC_CMD&t;&t;&t;11
DECL|macro|RTC_WHSEC
mdefine_line|#define RTC_WHSEC&t;&t;12
DECL|macro|RTC_WSEC
mdefine_line|#define RTC_WSEC&t;&t;13
DECL|macro|RTC_UNUSED
mdefine_line|#define RTC_UNUSED&t;&t;14
multiline_comment|/* RTC_*_alarm is always true if 2 MSBs are set */
DECL|macro|RTC_ALARM_DONT_CARE
macro_line|# define RTC_ALARM_DONT_CARE &t;0xC0
multiline_comment|/*&n; * Bits in the month register&n; */
DECL|macro|RTC_EOSC
mdefine_line|#define RTC_EOSC&t;&t;0x80
DECL|macro|RTC_ESQW
mdefine_line|#define RTC_ESQW&t;&t;0x40
multiline_comment|/*&n; * Bits in the Command register&n; */
DECL|macro|RTC_TDF
mdefine_line|#define RTC_TDF&t;&t;&t;0x01
DECL|macro|RTC_WAF
mdefine_line|#define RTC_WAF&t;&t;&t;0x02
DECL|macro|RTC_TDM
mdefine_line|#define RTC_TDM&t;&t;&t;0x04
DECL|macro|RTC_WAM
mdefine_line|#define RTC_WAM&t;&t;&t;0x08
DECL|macro|RTC_PU_LVL
mdefine_line|#define RTC_PU_LVL&t;&t;0x10
DECL|macro|RTC_IBH_LO
mdefine_line|#define RTC_IBH_LO&t;&t;0x20
DECL|macro|RTC_IPSW
mdefine_line|#define RTC_IPSW&t;&t;0x40
DECL|macro|RTC_TE
mdefine_line|#define RTC_TE&t;&t;&t;0x80
multiline_comment|/*&n; * Conversion between binary and BCD.&n; */
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
macro_line|#endif /* _ASM_DS1286_h */
eof
