multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/memory.h&n; *&n; * by Alexander Schulz&n; *&n; * derived from:&n; * linux/include/asm-arm/arch-ebsa110/memory.h&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Task size: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;(0x04000000UL)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)
multiline_comment|/*&n; * Page offset: = 3GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;(0xC0000000UL)
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET     (0x08000000UL)
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) (vpage - PAGE_OFFSET + PHYS_OFFSET)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) (ppage - PHYS_OFFSET + PAGE_OFFSET)
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;__virt_to_phys(x)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;__phys_to_virt(x)
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#endif
eof
