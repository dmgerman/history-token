multiline_comment|/* linux/include/asm-arm/arch-s3c2410/idle.h&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 CPU Idle controls&n; *&n; *  Changelog:&n; *&t;28-Oct-2004  BJD  Initial version&n; *&n;*/
macro_line|#ifndef __ASM_ARCH_IDLE_H
DECL|macro|__ASM_ARCH_IDLE_H
mdefine_line|#define __ASM_ARCH_IDLE_H __FILE__
multiline_comment|/* This allows the over-ride of the default idle code, in case there&n; * is any other things to be done over idle (like DVS)&n;*/
r_extern
r_void
(paren
op_star
id|s3c24xx_idle
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|s3c24xx_default_idle
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_ARCH_IDLE_H */
eof
