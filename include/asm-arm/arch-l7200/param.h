multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/param.h&n; *&n; * Copyright (C) 2000 Rob Scott (rscott@mtrob.fdns.net)&n; *                    Steve Hill (sjhill@cotw.com)&n; *&n; * This file contains the hardware definitions for the&n; * LinkUp Systems L7200 SOC development board.&n; *&n; * Changelog:&n; *   04-21-2000 RS      Created L7200 version&n; *   04-25-2000 SJH     Cleaned up file&n; *   05-03-2000 SJH     Change comments and rate&n; */
macro_line|#ifndef __ASM_ARCH_PARAM_H
DECL|macro|__ASM_ARCH_PARAM_H
mdefine_line|#define __ASM_ARCH_PARAM_H
multiline_comment|/*&n; * See &squot;time.h&squot; for how the RTC HZ rate is set&n; */
DECL|macro|HZ
mdefine_line|#define HZ 128
multiline_comment|/*&n; * Define hz_to_std, since we have a non 100Hz define&n; * (see include/asm-arm/param.h)&n; */
macro_line|#if defined(__KERNEL__)
DECL|macro|hz_to_std
mdefine_line|#define hz_to_std(a) ((a * HZ)/100)
macro_line|#endif
macro_line|#endif
eof
