multiline_comment|/* linux/include/asm-arm/arch-s3c2410/timex.h&n; *&n; * (c) 2003-2005 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - time parameters&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  02-Sep-2003 BJD  Created file&n; *  05-Jan-2004 BJD  Updated for Linux 2.6.0&n; *  22-Nov-2004 BJD  Fixed CLOCK_TICK_RATE&n; *  10-Jan-2004 BJD  Removed s3c2410_clock_tick_rate&n;*/
macro_line|#ifndef __ASM_ARCH_TIMEX_H
DECL|macro|__ASM_ARCH_TIMEX_H
mdefine_line|#define __ASM_ARCH_TIMEX_H
multiline_comment|/* CLOCK_TICK_RATE needs to be evaluatable by the cpp, so making it&n; * a variable is useless. It seems as long as we make our timers an&n; * exact multiple of HZ, any value that makes a 1-&gt;1 correspondence&n; * for the time conversion functions to/from jiffies is acceptable.&n;*/
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 12000000
macro_line|#endif /* __ASM_ARCH_TIMEX_H */
eof
