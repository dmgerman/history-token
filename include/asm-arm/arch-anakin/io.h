multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/io.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   10-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT&t;&t;0xffffffff
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;(a)
multiline_comment|/*&n; * We don&squot;t support ins[lb]/outs[lb].  Make them fault.&n; */
DECL|macro|__raw_readsb
mdefine_line|#define __raw_readsb(p,d,l)&t;do { *(int *)0 = 0; } while (0)
DECL|macro|__raw_readsl
mdefine_line|#define __raw_readsl(p,d,l)&t;do { *(int *)0 = 0; } while (0)
DECL|macro|__raw_writesb
mdefine_line|#define __raw_writesb(p,d,l)&t;do { *(int *)0 = 0; } while (0)
DECL|macro|__raw_writesl
mdefine_line|#define __raw_writesl(p,d,l)&t;do { *(int *)0 = 0; } while (0)
macro_line|#endif
eof
