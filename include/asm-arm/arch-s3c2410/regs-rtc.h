multiline_comment|/* linux/include/asm/arch-s3c2410/regs-rtc.h&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 Internal RTC register definition&n; *&n; *  Changelog:&n; *    19-06-2003     BJD     Created file&n; *    12-03-2004     BJD     Updated include protection&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_RTC_H
DECL|macro|__ASM_ARCH_REGS_RTC_H
mdefine_line|#define __ASM_ARCH_REGS_RTC_H __FILE__
DECL|macro|S3C2410_RTCREG
mdefine_line|#define S3C2410_RTCREG(x) ((x) + S3C2410_VA_RTC)
DECL|macro|S3C2410_RTCCON
mdefine_line|#define S3C2410_RTCCON&t;      S3C2410_RTCREG(0x40)
DECL|macro|S3C2410_RTCCON_RTCEN
mdefine_line|#define S3C2410_RTCCON_RTCEN  (1&lt;&lt;0)
DECL|macro|S3C2410_RTCCON_CLKSEL
mdefine_line|#define S3C2410_RTCCON_CLKSEL (1&lt;&lt;1)
DECL|macro|S3C2410_RTCCON_CNTSEL
mdefine_line|#define S3C2410_RTCCON_CNTSEL (1&lt;&lt;2)
DECL|macro|S3C2410_RTCCON_CLKRST
mdefine_line|#define S3C2410_RTCCON_CLKRST (1&lt;&lt;3)
DECL|macro|S3C2410_TICNT
mdefine_line|#define S3C2410_TICNT&t;      S3C2410_RTCREG(0x44)
DECL|macro|S3C2410_TICNT_ENABLE
mdefine_line|#define S3C2410_TICNT_ENABLE  (1&lt;&lt;7)
DECL|macro|S3C2410_RTCALM
mdefine_line|#define S3C2410_RTCALM&t;      S3C2410_RTCREG(0x50)
DECL|macro|S3C2410_RTCALM_ALMEN
mdefine_line|#define S3C2410_RTCALM_ALMEN  (1&lt;&lt;6)
DECL|macro|S3C2410_RTCALM_YEAREN
mdefine_line|#define S3C2410_RTCALM_YEAREN (1&lt;&lt;5)
DECL|macro|S3C2410_RTCALM_MONEN
mdefine_line|#define S3C2410_RTCALM_MONEN  (1&lt;&lt;4)
DECL|macro|S3C2410_RTCALM_DAYEN
mdefine_line|#define S3C2410_RTCALM_DAYEN  (1&lt;&lt;3)
DECL|macro|S3C2410_RTCALM_HOUREN
mdefine_line|#define S3C2410_RTCALM_HOUREN (1&lt;&lt;2)
DECL|macro|S3C2410_RTCALM_MINEN
mdefine_line|#define S3C2410_RTCALM_MINEN  (1&lt;&lt;1)
DECL|macro|S3C2410_RTCALM_SECEN
mdefine_line|#define S3C2410_RTCALM_SECEN  (1&lt;&lt;0)
DECL|macro|S3C2410_RTCALM_ALL
mdefine_line|#define S3C2410_RTCALM_ALL &bslash;&n;  S3C2410_RTCALM_ALMEN | S3C2410_RTCALM_YEAREN | S3C2410_RTCALM_MONEN |&bslash;&n;  S3C2410_RTCALM_DAYEN | S3C2410_RTCALM_HOUREN | S3C2410_RTCALM_MINEN |&bslash;&n;  S3C2410_RTCALM_SECEN
DECL|macro|S3C2410_ALMSEC
mdefine_line|#define S3C2410_ALMSEC&t;      S3C2410_RTCREG(0x54)
DECL|macro|S3C2410_ALMMIN
mdefine_line|#define S3C2410_ALMMIN&t;      S3C2410_RTCREG(0x58)
DECL|macro|S3C2410_ALMHOUR
mdefine_line|#define S3C2410_ALMHOUR&t;      S3C2410_RTCREG(0x5c)
DECL|macro|S3C2410_ALMDATE
mdefine_line|#define S3C2410_ALMDATE&t;      S3C2410_RTCREG(0x60)
DECL|macro|S3C2410_ALMMON
mdefine_line|#define S3C2410_ALMMON&t;      S3C2410_RTCREG(0x64)
DECL|macro|S3C2410_ALMYEAR
mdefine_line|#define S3C2410_ALMYEAR&t;      S3C2410_RTCREG(0x68)
DECL|macro|S3C2410_RTCRST
mdefine_line|#define S3C2410_RTCRST&t;      S3C2410_RTCREG(0x6c)
DECL|macro|S3C2410_RTCSEC
mdefine_line|#define S3C2410_RTCSEC&t;      S3C2410_RTCREG(0x70)
DECL|macro|S3C2410_RTCMIN
mdefine_line|#define S3C2410_RTCMIN&t;      S3C2410_RTCREG(0x74)
DECL|macro|S3C2410_RTCHOUR
mdefine_line|#define S3C2410_RTCHOUR&t;      S3C2410_RTCREG(0x78)
DECL|macro|S3C2410_RTCDATE
mdefine_line|#define S3C2410_RTCDATE&t;      S3C2410_RTCREG(0x7c)
DECL|macro|S3C2410_RTCDAY
mdefine_line|#define S3C2410_RTCDAY&t;      S3C2410_RTCREG(0x80)
DECL|macro|S3C2410_RTCMON
mdefine_line|#define S3C2410_RTCMON&t;      S3C2410_RTCREG(0x84)
DECL|macro|S3C2410_RTCYEAR
mdefine_line|#define S3C2410_RTCYEAR&t;      S3C2410_RTCREG(0x88)
macro_line|#endif /* __ASM_ARCH_REGS_RTC_H */
eof
