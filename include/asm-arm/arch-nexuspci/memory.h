multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/memory.h&n; *&n; * Copyright (c) 1997, 1998, 2000 FutureTV Labs Ltd.&n; * Copyright (c) 1999 Russell King&n; *&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
multiline_comment|/*&n; * Task size: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;(0x04000000UL)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)
multiline_comment|/*&n; * Page offset: 3GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;(0xc0000000UL)
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x40000000UL)
DECL|macro|BUS_OFFSET
mdefine_line|#define BUS_OFFSET&t;(0xe0000000UL)
multiline_comment|/*&n; * DRAM is contiguous&n; */
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((unsigned long)(vpage) - PAGE_OFFSET + PHYS_OFFSET)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((unsigned long)(ppage) + PAGE_OFFSET - PHYS_OFFSET)
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
multiline_comment|/*&n; * On the PCI bus the DRAM appears at address 0xe0000000&n; */
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x) ((unsigned long)(x) - PAGE_OFFSET + BUS_OFFSET)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x) ((unsigned long)(x) + PAGE_OFFSET - BUS_OFFSET)
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#endif
eof
