multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/memory.h&n; *&n; * Copyright (c) 1996-1999 Russell King.&n; * Copyright (c) 1998-1999 Phil Blundell&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;&t;(0x80000000UL)
multiline_comment|/*&n; * Bus view is the same as physical view&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;__virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;__phys_to_virt(x)
macro_line|#endif
eof
