multiline_comment|/* linux/include/asm/arch-s3c2410/regs-adc.h&n; *&n; * Copyright (c) 2004 Shannon Holland &lt;holland@loser.net&gt;&n; *&n; * This program is free software; yosu can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 ADC registers&n; *&n; *  Changelog:&n; *    27-09-2004     SAH     Created file&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_ADC_H
DECL|macro|__ASM_ARCH_REGS_ADC_H
mdefine_line|#define __ASM_ARCH_REGS_ADC_H &quot;regs-adc.h&quot;
DECL|macro|S3C2410_ADCREG
mdefine_line|#define S3C2410_ADCREG(x) (x)
DECL|macro|S3C2410_ADCCON
mdefine_line|#define S3C2410_ADCCON&t;   S3C2410_ADCREG(0x00)
DECL|macro|S3C2410_ADCTSC
mdefine_line|#define S3C2410_ADCTSC&t;   S3C2410_ADCREG(0x04)
DECL|macro|S3C2410_ADCDLY
mdefine_line|#define S3C2410_ADCDLY&t;   S3C2410_ADCREG(0x08)
DECL|macro|S3C2410_ADCDAT0
mdefine_line|#define S3C2410_ADCDAT0&t;   S3C2410_ADCREG(0x0C)
DECL|macro|S3C2410_ADCDAT1
mdefine_line|#define S3C2410_ADCDAT1&t;   S3C2410_ADCREG(0x10)
multiline_comment|/* ADCCON Register Bits */
DECL|macro|S3C2410_ADCCON_ECFLG
mdefine_line|#define S3C2410_ADCCON_ECFLG&t;&t;(1&lt;&lt;15)
DECL|macro|S3C2410_ADCCON_PRSCEN
mdefine_line|#define S3C2410_ADCCON_PRSCEN&t;&t;(1&lt;&lt;14)
DECL|macro|S3C2410_ADCCON_PRSCVL
mdefine_line|#define S3C2410_ADCCON_PRSCVL(x)&t;(((x)&amp;0xFF)&lt;&lt;6)
DECL|macro|S3C2410_ADCCON_PRSCVLMASK
mdefine_line|#define S3C2410_ADCCON_PRSCVLMASK&t;(0xFF&lt;&lt;6)
DECL|macro|S3C2410_ADCCON_SELMUX
mdefine_line|#define S3C2410_ADCCON_SELMUX(x)&t;(((x)&amp;0x7)&lt;&lt;3)
DECL|macro|S3C2410_ADCCON_MUXMASK
mdefine_line|#define S3C2410_ADCCON_MUXMASK&t;&t;(0x7&lt;&lt;3)
DECL|macro|S3C2410_ADCCON_STDBM
mdefine_line|#define S3C2410_ADCCON_STDBM&t;&t;(1&lt;&lt;2)
DECL|macro|S3C2410_ADCCON_READ_START
mdefine_line|#define S3C2410_ADCCON_READ_START&t;(1&lt;&lt;1)
DECL|macro|S3C2410_ADCCON_ENABLE_START
mdefine_line|#define S3C2410_ADCCON_ENABLE_START&t;(1&lt;&lt;0)
DECL|macro|S3C2410_ADCCON_STARTMASK
mdefine_line|#define S3C2410_ADCCON_STARTMASK&t;(0x3&lt;&lt;0)
multiline_comment|/* ADCTSC Register Bits */
DECL|macro|S3C2410_ADCTSC_YM_SEN
mdefine_line|#define S3C2410_ADCTSC_YM_SEN&t;&t;(1&lt;&lt;7)
DECL|macro|S3C2410_ADCTSC_YP_SEN
mdefine_line|#define S3C2410_ADCTSC_YP_SEN&t;&t;(1&lt;&lt;6)
DECL|macro|S3C2410_ADCTSC_XM_SEN
mdefine_line|#define S3C2410_ADCTSC_XM_SEN&t;&t;(1&lt;&lt;5)
DECL|macro|S3C2410_ADCTSC_XP_SEN
mdefine_line|#define S3C2410_ADCTSC_XP_SEN&t;&t;(1&lt;&lt;4)
DECL|macro|S3C2410_ADCTSC_PULL_UP_DISABLE
mdefine_line|#define S3C2410_ADCTSC_PULL_UP_DISABLE&t;(1&lt;&lt;3)
DECL|macro|S3C2410_ADCTSC_AUTO_PST
mdefine_line|#define S3C2410_ADCTSC_AUTO_PST&t;&t;(1&lt;&lt;2)
DECL|macro|S3C2410_ADCTSC_XY_PST
mdefine_line|#define S3C2410_ADCTSC_XY_PST&t;&t;(0x3&lt;&lt;0)
multiline_comment|/* ADCDAT0 Bits */
DECL|macro|S3C2410_ADCDAT0_UPDOWN
mdefine_line|#define S3C2410_ADCDAT0_UPDOWN&t;&t;(1&lt;&lt;15)
DECL|macro|S3C2410_ADCDAT0_AUTO_PST
mdefine_line|#define S3C2410_ADCDAT0_AUTO_PST&t;(1&lt;&lt;14)
DECL|macro|S3C2410_ADCDAT0_XY_PST
mdefine_line|#define S3C2410_ADCDAT0_XY_PST&t;&t;(0x3&lt;&lt;12)
DECL|macro|S3C2410_ADCDAT0_XPDATA_MASK
mdefine_line|#define S3C2410_ADCDAT0_XPDATA_MASK&t;(0x03FF)
multiline_comment|/* ADCDAT1 Bits */
DECL|macro|S3C2410_ADCDAT1_UPDOWN
mdefine_line|#define S3C2410_ADCDAT1_UPDOWN&t;&t;(1&lt;&lt;15)
DECL|macro|S3C2410_ADCDAT1_AUTO_PST
mdefine_line|#define S3C2410_ADCDAT1_AUTO_PST&t;(1&lt;&lt;14)
DECL|macro|S3C2410_ADCDAT1_XY_PST
mdefine_line|#define S3C2410_ADCDAT1_XY_PST&t;&t;(0x3&lt;&lt;12)
DECL|macro|S3C2410_ADCDAT1_YPDATA_MASK
mdefine_line|#define S3C2410_ADCDAT1_YPDATA_MASK&t;(0x03FF)
macro_line|#endif /* __ASM_ARCH_REGS_ADC_H */
eof
