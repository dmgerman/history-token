multiline_comment|/* linux/include/asm-arm/arch-s3c2410/timex.h&n; *&n; * (c) 2003,2004 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - time parameters&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  02-Sep-2003 BJD  Created file&n; *  05-Jan-2004 BJD  Updated for Linux 2.6.0&n; *  22-Nov-2004 BJD  Fixed CLOCK_TICK_RATE&n;*/
macro_line|#ifndef __ASM_ARCH_TIMEX_H
DECL|macro|__ASM_ARCH_TIMEX_H
mdefine_line|#define __ASM_ARCH_TIMEX_H
macro_line|#if 0
multiline_comment|/* todo - this does not seem to work with 2.6.0 -&gt; division by zero&n; * in header files&n; */
r_extern
r_int
id|s3c2410_clock_tick_rate
suffix:semicolon
mdefine_line|#define CLOCK_TICK_RATE (s3c2410_clock_tick_rate)
macro_line|#endif
multiline_comment|/* currently, the BAST uses 12MHz as a base clock rate */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 12000000
macro_line|#endif /* __ASM_ARCH_TIMEX_H */
eof
