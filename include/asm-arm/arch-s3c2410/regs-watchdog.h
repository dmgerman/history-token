multiline_comment|/* linux/include/asm/arch-s3c2410/regs0watchdog.h&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 Watchdog timer control&n; *&n; *  Changelog:&n; *    21-06-2003     BJD     Created file&n; *    12-03-2004     BJD     Updated include protection&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_WATCHDOG_H
DECL|macro|__ASM_ARCH_REGS_WATCHDOG_H
mdefine_line|#define __ASM_ARCH_REGS_WATCHDOG_H &quot;$Id: watchdog.h,v 1.2 2003/04/29 13:31:09 ben Exp $&quot;
DECL|macro|S3C2410_WDOGREG
mdefine_line|#define S3C2410_WDOGREG(x) ((x) + S3C2410_VA_WATCHDOG)
DECL|macro|S3C2410_WTCON
mdefine_line|#define S3C2410_WTCON&t;   S3C2410_WDOGREG(0x00)
DECL|macro|S3C2410_WTDAT
mdefine_line|#define S3C2410_WTDAT&t;   S3C2410_WDOGREG(0x04)
DECL|macro|S3C2410_WTCNT
mdefine_line|#define S3C2410_WTCNT&t;   S3C2410_WDOGREG(0x08)
multiline_comment|/* the watchdog can either generate a reset pulse, or an&n; * interrupt.&n; */
DECL|macro|S3C2410_WTCON_RSTEN
mdefine_line|#define S3C2410_WTCON_RSTEN   (0x01)
DECL|macro|S3C2410_WTCON_INTEN
mdefine_line|#define S3C2410_WTCON_INTEN   (1&lt;&lt;2)
DECL|macro|S3C2410_WTCON_ENABLE
mdefine_line|#define S3C2410_WTCON_ENABLE  (1&lt;&lt;5)
DECL|macro|S3C2410_WTCON_DIV16
mdefine_line|#define S3C2410_WTCON_DIV16   (0&lt;&lt;3)
DECL|macro|S3C2410_WTCON_DIV32
mdefine_line|#define S3C2410_WTCON_DIV32   (1&lt;&lt;3)
DECL|macro|S3C2410_WTCON_DIV64
mdefine_line|#define S3C2410_WTCON_DIV64   (2&lt;&lt;3)
DECL|macro|S3C2410_WTCON_DIV128
mdefine_line|#define S3C2410_WTCON_DIV128  (3&lt;&lt;3)
DECL|macro|S3C2410_WTCON_PRESCALE
mdefine_line|#define S3C2410_WTCON_PRESCALE(x) ((x) &lt;&lt; 8)
DECL|macro|S3C2410_WTCON_PRESCALE_MASK
mdefine_line|#define S3C2410_WTCON_PRESCALE_MASK (0xff00)
macro_line|#endif /* __ASM_ARCH_REGS_WATCHDOG_H */
eof
