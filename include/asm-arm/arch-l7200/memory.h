multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/memory.h&n; *&n; * Copyright (c) 2000 Steve Hill (sjhill@cotw.com)&n; * Copyright (c) 2000 Rob Scott (rscott@mtrob.fdns.net)&n; *&n; * Changelog:&n; *  03-13-2000&t;SJH&t;Created&n; *  04-13-2000  RS      Changed bus macros for new addr&n; *  05-03-2000  SJH     Removed bus macros and fixed virt_to_phys macro&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset on the L7200 SDB.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET     (0xf0000000UL)
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x) __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x) __phys_to_virt(x)
macro_line|#endif
eof
