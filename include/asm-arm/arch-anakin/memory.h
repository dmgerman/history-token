multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/memory.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   09-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(3u * 1024 * 1024 * 1024)
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;&t;(64u * 1024 * 1024)
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(1u * 1024 * 1024 * 1024)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0xc0000000
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;&t;0x20000000
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(a)&t;((a) - PAGE_OFFSET + PHYS_OFFSET)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(a)&t;((a) + PAGE_OFFSET - PHYS_OFFSET)
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(a)&t;__virt_to_phys(a)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(a)&t;__phys_to_virt(a)
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#endif
eof
