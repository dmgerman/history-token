multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/memory.h&n; *&n; * by Alexander Schulz&n; *&n; * derived from:&n; * linux/include/asm-arm/arch-ebsa110/memory.h&n; * Copyright (c) 1996-1999 Russell King.&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET     (0x08000000UL)
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;__virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;__phys_to_virt(x)
macro_line|#endif
eof
