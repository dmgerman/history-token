multiline_comment|/* linux/include/asm-arm/arch-s3c2410/bast-cpld.h&n; *&n; * (c) 2003,2004 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * BAST - CPLD control constants&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  25-May-2003 BJD  Created file, added CTRL1 registers&n; *  30-Aug-2004 BJD  Updated definitions from 2.4.26 port&n; *  30-Aug-2004 BJD  Added CTRL3 and CTRL4 definitions&n;*/
macro_line|#ifndef __ASM_ARCH_BASTCPLD_H
DECL|macro|__ASM_ARCH_BASTCPLD_H
mdefine_line|#define __ASM_ARCH_BASTCPLD_H
multiline_comment|/* CTRL1 - Audio LR routing */
DECL|macro|BAST_CPLD_CTRL1_LRCOFF
mdefine_line|#define BAST_CPLD_CTRL1_LRCOFF&t;    (0x00)
DECL|macro|BAST_CPLD_CTRL1_LRCADC
mdefine_line|#define BAST_CPLD_CTRL1_LRCADC&t;    (0x01)
DECL|macro|BAST_CPLD_CTRL1_LRCDAC
mdefine_line|#define BAST_CPLD_CTRL1_LRCDAC&t;    (0x02)
DECL|macro|BAST_CPLD_CTRL1_LRCARM
mdefine_line|#define BAST_CPLD_CTRL1_LRCARM&t;    (0x03)
DECL|macro|BAST_CPLD_CTRL1_LRMASK
mdefine_line|#define BAST_CPLD_CTRL1_LRMASK&t;    (0x03)
multiline_comment|/* CTRL2 - NAND WP control, IDE Reset assert/check */
DECL|macro|BAST_CPLD_CTRL2_WNAND
mdefine_line|#define BAST_CPLD_CTRL2_WNAND       (0x04)
DECL|macro|BAST_CPLD_CTLR2_IDERST
mdefine_line|#define BAST_CPLD_CTLR2_IDERST      (0x08)
multiline_comment|/* CTRL3 - rom write control, CPLD identity */
DECL|macro|BAST_CPLD_CTRL3_IDMASK
mdefine_line|#define BAST_CPLD_CTRL3_IDMASK      (0x0e)
DECL|macro|BAST_CPLD_CTRL3_ROMWEN
mdefine_line|#define BAST_CPLD_CTRL3_ROMWEN      (0x01)
multiline_comment|/* CTRL4 - 8bit LCD interface control/status */
DECL|macro|BAST_CPLD_CTRL4_LLAT
mdefine_line|#define BAST_CPLD_CTRL4_LLAT&t;    (0x01)
DECL|macro|BAST_CPLD_CTRL4_LCDRW
mdefine_line|#define BAST_CPLD_CTRL4_LCDRW&t;    (0x02)
DECL|macro|BAST_CPLD_CTRL4_LCDCMD
mdefine_line|#define BAST_CPLD_CTRL4_LCDCMD&t;    (0x04)
DECL|macro|BAST_CPLD_CTRL4_LCDE2
mdefine_line|#define BAST_CPLD_CTRL4_LCDE2&t;    (0x01)
multiline_comment|/* CTRL5 - DMA routing */
DECL|macro|BAST_CPLD_DMA0_PRIIDE
mdefine_line|#define BAST_CPLD_DMA0_PRIIDE      (0&lt;&lt;0)
DECL|macro|BAST_CPLD_DMA0_SECIDE
mdefine_line|#define BAST_CPLD_DMA0_SECIDE      (1&lt;&lt;0)
DECL|macro|BAST_CPLD_DMA0_ISA15
mdefine_line|#define BAST_CPLD_DMA0_ISA15       (2&lt;&lt;0)
DECL|macro|BAST_CPLD_DMA0_ISA36
mdefine_line|#define BAST_CPLD_DMA0_ISA36       (3&lt;&lt;0)
DECL|macro|BAST_CPLD_DMA1_PRIIDE
mdefine_line|#define BAST_CPLD_DMA1_PRIIDE      (0&lt;&lt;2)
DECL|macro|BAST_CPLD_DMA1_SECIDE
mdefine_line|#define BAST_CPLD_DMA1_SECIDE      (1&lt;&lt;2)
DECL|macro|BAST_CPLD_DMA1_ISA15
mdefine_line|#define BAST_CPLD_DMA1_ISA15       (2&lt;&lt;2)
DECL|macro|BAST_CPLD_DMA1_ISA36
mdefine_line|#define BAST_CPLD_DMA1_ISA36       (3&lt;&lt;2)
macro_line|#endif /* __ASM_ARCH_BASTCPLD_H */
eof
