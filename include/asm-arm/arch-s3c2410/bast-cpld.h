multiline_comment|/* linux/include/asm-arm/arch-s3c2410/bast-cpld.h&n; *&n; * (c) 2003 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * BAST - CPLD control constants&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  25-May-2003 BJD  Created file, added CTRL1 registers&n;*/
macro_line|#ifndef __ASM_ARCH_BASTCPLD_H
DECL|macro|__ASM_ARCH_BASTCPLD_H
mdefine_line|#define __ASM_ARCH_BASTCPLD_H
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
macro_line|#endif /* __ASM_ARCH_BASTCPLD_H */
eof
