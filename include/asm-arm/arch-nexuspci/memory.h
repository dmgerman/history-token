multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/memory.h&n; *&n; * Copyright (c) 1997, 1998, 2000 FutureTV Labs Ltd.&n; * Copyright (c) 1999 Russell King&n; *&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x40000000UL)
DECL|macro|BUS_OFFSET
mdefine_line|#define BUS_OFFSET&t;(0xe0000000UL)
multiline_comment|/*&n; * On the PCI bus the DRAM appears at address 0xe0000000&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x) ((unsigned long)(x) - PAGE_OFFSET + BUS_OFFSET)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x) ((unsigned long)(x) + PAGE_OFFSET - BUS_OFFSET)
macro_line|#endif
eof
