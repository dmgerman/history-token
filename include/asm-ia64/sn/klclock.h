multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 2001 Silicon Graphics, Inc. All rights reserved.&n; * Copyright (C) 2001 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_IA64_SN_KLCLOCK_H
DECL|macro|_ASM_IA64_SN_KLCLOCK_H
mdefine_line|#define _ASM_IA64_SN_KLCLOCK_H
macro_line|#include &lt;asm/sn/ioc3.h&gt;
DECL|macro|RTC_BASE_ADDR
mdefine_line|#define RTC_BASE_ADDR&t;&t;(unsigned char *)(nvram_base)
multiline_comment|/* Defines for the SGS-Thomson M48T35 clock */
DECL|macro|RTC_SGS_WRITE_ENABLE
mdefine_line|#define RTC_SGS_WRITE_ENABLE    0x80
DECL|macro|RTC_SGS_READ_PROTECT
mdefine_line|#define RTC_SGS_READ_PROTECT    0x40
DECL|macro|RTC_SGS_YEAR_ADDR
mdefine_line|#define RTC_SGS_YEAR_ADDR       (RTC_BASE_ADDR + 0x7fffL)
DECL|macro|RTC_SGS_MONTH_ADDR
mdefine_line|#define RTC_SGS_MONTH_ADDR      (RTC_BASE_ADDR + 0x7ffeL)
DECL|macro|RTC_SGS_DATE_ADDR
mdefine_line|#define RTC_SGS_DATE_ADDR       (RTC_BASE_ADDR + 0x7ffdL)
DECL|macro|RTC_SGS_DAY_ADDR
mdefine_line|#define RTC_SGS_DAY_ADDR        (RTC_BASE_ADDR + 0x7ffcL)
DECL|macro|RTC_SGS_HOUR_ADDR
mdefine_line|#define RTC_SGS_HOUR_ADDR       (RTC_BASE_ADDR + 0x7ffbL)
DECL|macro|RTC_SGS_MIN_ADDR
mdefine_line|#define RTC_SGS_MIN_ADDR        (RTC_BASE_ADDR + 0x7ffaL)
DECL|macro|RTC_SGS_SEC_ADDR
mdefine_line|#define RTC_SGS_SEC_ADDR        (RTC_BASE_ADDR + 0x7ff9L)
DECL|macro|RTC_SGS_CONTROL_ADDR
mdefine_line|#define RTC_SGS_CONTROL_ADDR    (RTC_BASE_ADDR + 0x7ff8L)
multiline_comment|/* Defines for the Dallas DS1386 */
DECL|macro|RTC_DAL_UPDATE_ENABLE
mdefine_line|#define RTC_DAL_UPDATE_ENABLE   0x80
DECL|macro|RTC_DAL_UPDATE_DISABLE
mdefine_line|#define RTC_DAL_UPDATE_DISABLE  0x00
DECL|macro|RTC_DAL_YEAR_ADDR
mdefine_line|#define RTC_DAL_YEAR_ADDR       (RTC_BASE_ADDR + 0xaL)
DECL|macro|RTC_DAL_MONTH_ADDR
mdefine_line|#define RTC_DAL_MONTH_ADDR      (RTC_BASE_ADDR + 0x9L)
DECL|macro|RTC_DAL_DATE_ADDR
mdefine_line|#define RTC_DAL_DATE_ADDR       (RTC_BASE_ADDR + 0x8L)
DECL|macro|RTC_DAL_DAY_ADDR
mdefine_line|#define RTC_DAL_DAY_ADDR        (RTC_BASE_ADDR + 0x6L)
DECL|macro|RTC_DAL_HOUR_ADDR
mdefine_line|#define RTC_DAL_HOUR_ADDR       (RTC_BASE_ADDR + 0x4L)
DECL|macro|RTC_DAL_MIN_ADDR
mdefine_line|#define RTC_DAL_MIN_ADDR        (RTC_BASE_ADDR + 0x2L)
DECL|macro|RTC_DAL_SEC_ADDR
mdefine_line|#define RTC_DAL_SEC_ADDR        (RTC_BASE_ADDR + 0x1L)
DECL|macro|RTC_DAL_CONTROL_ADDR
mdefine_line|#define RTC_DAL_CONTROL_ADDR    (RTC_BASE_ADDR + 0xbL)
DECL|macro|RTC_DAL_USER_ADDR
mdefine_line|#define RTC_DAL_USER_ADDR       (RTC_BASE_ADDR + 0xeL)
multiline_comment|/* Defines for the Dallas DS1742 */
DECL|macro|RTC_DS1742_WRITE_ENABLE
mdefine_line|#define RTC_DS1742_WRITE_ENABLE    0x80
DECL|macro|RTC_DS1742_READ_ENABLE
mdefine_line|#define RTC_DS1742_READ_ENABLE     0x40
DECL|macro|RTC_DS1742_UPDATE_DISABLE
mdefine_line|#define RTC_DS1742_UPDATE_DISABLE  0x00
DECL|macro|RTC_DS1742_YEAR_ADDR
mdefine_line|#define RTC_DS1742_YEAR_ADDR       (RTC_BASE_ADDR + 0x7ffL)
DECL|macro|RTC_DS1742_MONTH_ADDR
mdefine_line|#define RTC_DS1742_MONTH_ADDR      (RTC_BASE_ADDR + 0x7feL)
DECL|macro|RTC_DS1742_DATE_ADDR
mdefine_line|#define RTC_DS1742_DATE_ADDR       (RTC_BASE_ADDR + 0x7fdL)
DECL|macro|RTC_DS1742_DAY_ADDR
mdefine_line|#define RTC_DS1742_DAY_ADDR        (RTC_BASE_ADDR + 0x7fcL)
DECL|macro|RTC_DS1742_HOUR_ADDR
mdefine_line|#define RTC_DS1742_HOUR_ADDR       (RTC_BASE_ADDR + 0x7fbL)
DECL|macro|RTC_DS1742_MIN_ADDR
mdefine_line|#define RTC_DS1742_MIN_ADDR        (RTC_BASE_ADDR + 0x7faL)
DECL|macro|RTC_DS1742_SEC_ADDR
mdefine_line|#define RTC_DS1742_SEC_ADDR        (RTC_BASE_ADDR + 0x7f9L)
DECL|macro|RTC_DS1742_CONTROL_ADDR
mdefine_line|#define RTC_DS1742_CONTROL_ADDR    (RTC_BASE_ADDR + 0x7f8L)
DECL|macro|RTC_DS1742_USER_ADDR
mdefine_line|#define RTC_DS1742_USER_ADDR       (RTC_BASE_ADDR + 0x0L)
DECL|macro|BCD_TO_INT
mdefine_line|#define BCD_TO_INT(x) (((x&gt;&gt;4) * 10) + (x &amp; 0xf))
DECL|macro|INT_TO_BCD
mdefine_line|#define INT_TO_BCD(x) (((x / 10)&lt;&lt;4) + (x % 10))
DECL|macro|YRREF
mdefine_line|#define YRREF&t;1970 
macro_line|#endif /* _ASM_IA64_SN_KLCLOCK_H  */
eof
