multiline_comment|/* linux/include/asm-arm/arch-s3c2410/hardware.h&n; *&n; * (c) 2003 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - hardware&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  21-May-2003 BJD  Created file&n; *  06-Jun-2003 BJD  Added CPU frequency settings&n; *  03-Sep-2003 BJD  Linux v2.6 support&n; *  12-Mar-2004 BJD  Fixed include protection, fixed type of clock vars&n;*/
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* processor clock settings, in Hz */
r_extern
r_int
r_int
id|s3c2410_pclk
suffix:semicolon
r_extern
r_int
r_int
id|s3c2410_hclk
suffix:semicolon
r_extern
r_int
r_int
id|s3c2410_fclk
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/arch/map.h&gt;
multiline_comment|/* machine specific includes, such as the BAST */
macro_line|#if defined(CONFIG_ARCH_BAST)
macro_line|#include &lt;asm/arch/bast-cpld.h&gt;
macro_line|#endif
multiline_comment|/* currently here until moved into config (todo) */
DECL|macro|CONFIG_NO_MULTIWORD_IO
mdefine_line|#define CONFIG_NO_MULTIWORD_IO
macro_line|#endif /* __ASM_ARCH_HARDWARE_H */
eof
