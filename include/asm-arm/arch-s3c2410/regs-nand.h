multiline_comment|/* linux/include/asm-arm/arch-s3c2410/regs-nand.h&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 clock register definitions&n; *&n; *  Changelog:&n; *    18-Aug-2004    BJD     Copied file from 2.4 and updated&n;*/
macro_line|#ifndef __ASM_ARM_REGS_NAND
DECL|macro|__ASM_ARM_REGS_NAND
mdefine_line|#define __ASM_ARM_REGS_NAND &quot;$Id: nand.h,v 1.3 2003/12/09 11:36:29 ben Exp $&quot;
DECL|macro|S3C2410_NFREG
mdefine_line|#define S3C2410_NFREG(x) (x)
DECL|macro|S3C2410_NFCONF
mdefine_line|#define S3C2410_NFCONF  S3C2410_NFREG(0x00)
DECL|macro|S3C2410_NFCMD
mdefine_line|#define S3C2410_NFCMD   S3C2410_NFREG(0x04)
DECL|macro|S3C2410_NFADDR
mdefine_line|#define S3C2410_NFADDR  S3C2410_NFREG(0x08)
DECL|macro|S3C2410_NFDATA
mdefine_line|#define S3C2410_NFDATA  S3C2410_NFREG(0x0C)
DECL|macro|S3C2410_NFSTAT
mdefine_line|#define S3C2410_NFSTAT  S3C2410_NFREG(0x10)
DECL|macro|S3C2410_NFECC
mdefine_line|#define S3C2410_NFECC   S3C2410_NFREG(0x14)
DECL|macro|S3C2410_NFCONF_EN
mdefine_line|#define S3C2410_NFCONF_EN          (1&lt;&lt;15)
DECL|macro|S3C2410_NFCONF_512BYTE
mdefine_line|#define S3C2410_NFCONF_512BYTE     (1&lt;&lt;14)
DECL|macro|S3C2410_NFCONF_4STEP
mdefine_line|#define S3C2410_NFCONF_4STEP       (1&lt;&lt;13)
DECL|macro|S3C2410_NFCONF_INITECC
mdefine_line|#define S3C2410_NFCONF_INITECC     (1&lt;&lt;12)
DECL|macro|S3C2410_NFCONF_nFCE
mdefine_line|#define S3C2410_NFCONF_nFCE        (1&lt;&lt;11)
DECL|macro|S3C2410_NFCONF_TACLS
mdefine_line|#define S3C2410_NFCONF_TACLS(x)    ((x)&lt;&lt;8)
DECL|macro|S3C2410_NFCONF_TWRPH0
mdefine_line|#define S3C2410_NFCONF_TWRPH0(x)   ((x)&lt;&lt;4)
DECL|macro|S3C2410_NFCONF_TWRPH1
mdefine_line|#define S3C2410_NFCONF_TWRPH1(x)   ((x)&lt;&lt;0)
DECL|macro|S3C2410_NFSTAT_BUSY
mdefine_line|#define S3C2410_NFSTAT_BUSY        (1&lt;&lt;0)
multiline_comment|/* think ECC can only be 8bit read? */
macro_line|#endif /* __ASM_ARM_REGS_NAND */
eof
