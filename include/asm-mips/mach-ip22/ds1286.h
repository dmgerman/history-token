multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 2001, 03 by Ralf Baechle&n; *&n; * RTC routines for PC style attached Dallas chip.&n; */
macro_line|#ifndef __ASM_MACH_IP22_DS1286_H
DECL|macro|__ASM_MACH_IP22_DS1286_H
mdefine_line|#define __ASM_MACH_IP22_DS1286_H
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
DECL|macro|rtc_read
mdefine_line|#define rtc_read(reg)&t;&t;(hpc3c0-&gt;rtcregs[(reg)] &amp; 0xff)
DECL|macro|rtc_write
mdefine_line|#define rtc_write(data, reg)&t;do { hpc3c0-&gt;rtcregs[(reg)] = (data); } while(0)
macro_line|#endif /* __ASM_MACH_IP22_DS1286_H */
eof
