multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/io.h&n; *&n; *  Copyright (C) 1997,1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *  06-Dec-1997&t;RMK&t;Created.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * Generic virtual read/write&n; */
DECL|macro|__arch_getw
mdefine_line|#define __arch_getw(a)&t;&t;(*(volatile unsigned short *)(a))
DECL|macro|__arch_putw
mdefine_line|#define __arch_putw(v,a)&t;(*(volatile unsigned short *)(a) = (v))
DECL|macro|__io
mdefine_line|#define __io(p)&t;&t;(ISAIO_BASE + ((p) &lt;&lt; 2))
macro_line|#endif
eof
