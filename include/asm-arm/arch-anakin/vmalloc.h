multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/vmalloc.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   09-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_VMALLOC_H
DECL|macro|__ASM_ARCH_VMALLOC_H
mdefine_line|#define __ASM_ARCH_VMALLOC_H
multiline_comment|/*&n; * VMALLOC_ARCH_OFFSET must be set to VMALLOC_OFFSET (check&n; * linux/arch/arm/kernel/traps.c)&n; */
DECL|macro|VMALLOC_ARCH_OFFSET
mdefine_line|#define VMALLOC_ARCH_OFFSET&t;(8 * 1024 * 1024)
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(a)&t;((unsigned int) (a))
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;((VMALLOC_VMADDR(high_memory) + VMALLOC_ARCH_OFFSET) &amp; ~(VMALLOC_ARCH_OFFSET - 1))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;(PAGE_OFFSET + 0x10000000)
macro_line|#endif
eof
