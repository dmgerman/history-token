multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 by Ralf Baechle&n; *&n; * RTC routines for PC style attached Dallas chip with ARC epoch.&n; */
macro_line|#ifndef __ASM_MACH_RM200_MC146818RTC_H
DECL|macro|__ASM_MACH_RM200_MC146818RTC_H
mdefine_line|#define __ASM_MACH_RM200_MC146818RTC_H
DECL|macro|mc146818_decode_year
mdefine_line|#define mc146818_decode_year(year) ((year) + 1980)
macro_line|#include_next &lt;mc146818rtc.h&gt;
macro_line|#endif /* __ASM_MACH_RM200_MC146818RTC_H */
eof
