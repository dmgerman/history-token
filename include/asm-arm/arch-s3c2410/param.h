multiline_comment|/* linux/include/asm-arm/arch-s3c2410/param.h&n; *&n; * (c) 2003 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - Machine parameters&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  02-Sep-2003 BJD  Created file&n; *  12-Mar-2004 BJD  Added include protection&n;*/
macro_line|#ifndef __ASM_ARCH_PARAM_H
DECL|macro|__ASM_ARCH_PARAM_H
mdefine_line|#define __ASM_ARCH_PARAM_H
multiline_comment|/* we cannot get our timer down to 100Hz with the setup as is, but we can&n; * manage 200 clock ticks per second... if this is a problem, we can always&n; * add a software pre-scaler to the evil timer systems.&n;*/
DECL|macro|HZ
mdefine_line|#define HZ   200
macro_line|#endif /* __ASM_ARCH_PARAM_H */
eof
