multiline_comment|/* linux/include/asm/arch-s3c2410/regs-irq.h&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *&n; *&n; *  Changelog:&n; *    19-06-2003     BJD     Created file&n; *    12-03-2004     BJD     Updated include protection&n; */
macro_line|#ifndef ___ASM_ARCH_REGS_IRQ_H
DECL|macro|___ASM_ARCH_REGS_IRQ_H
mdefine_line|#define ___ASM_ARCH_REGS_IRQ_H &quot;$Id: irq.h,v 1.3 2003/03/25 21:29:06 ben Exp $&quot;
multiline_comment|/* interrupt controller */
DECL|macro|S3C2410_IRQREG
mdefine_line|#define S3C2410_IRQREG(x)   ((x) + S3C2410_VA_IRQ)
DECL|macro|S3C2410_EINTREG
mdefine_line|#define S3C2410_EINTREG(x)  ((x) + S3C2410_VA_GPIO)
DECL|macro|S3C2410_SRCPND
mdefine_line|#define S3C2410_SRCPND&t;       S3C2410_IRQREG(0x000)
DECL|macro|S3C2410_INTMOD
mdefine_line|#define S3C2410_INTMOD&t;       S3C2410_IRQREG(0x004)
DECL|macro|S3C2410_INTMSK
mdefine_line|#define S3C2410_INTMSK&t;       S3C2410_IRQREG(0x008)
DECL|macro|S3C2410_PRIORITY
mdefine_line|#define S3C2410_PRIORITY       S3C2410_IRQREG(0x00C)
DECL|macro|S3C2410_INTPND
mdefine_line|#define S3C2410_INTPND&t;       S3C2410_IRQREG(0x010)
DECL|macro|S3C2410_INTOFFSET
mdefine_line|#define S3C2410_INTOFFSET      S3C2410_IRQREG(0x014)
DECL|macro|S3C2410_SUBSRCPND
mdefine_line|#define S3C2410_SUBSRCPND      S3C2410_IRQREG(0x018)
DECL|macro|S3C2410_INTSUBMSK
mdefine_line|#define S3C2410_INTSUBMSK      S3C2410_IRQREG(0x01C)
DECL|macro|S3C2410_EINTMASK
mdefine_line|#define S3C2410_EINTMASK       S3C2410_EINTREG(0x0A4)
DECL|macro|S3C2410_EINTPEND
mdefine_line|#define S3C2410_EINTPEND       S3C2410_EINTREG(0X0A8)
macro_line|#endif /* ___ASM_ARCH_REGS_IRQ_H */
eof
