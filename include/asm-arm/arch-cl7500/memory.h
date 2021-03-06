multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/memory.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * Changelog:&n; *  20-Oct-1996&t;RMK&t;Created&n; *  31-Dec-1997&t;RMK&t;Fixed definitions to reduce warnings&n; *  11-Jan-1998&t;RMK&t;Uninlined to reduce hits on cache&n; *  08-Feb-1998&t;RMK&t;Added __virt_to_bus and __bus_to_virt&n; *  21-Mar-1999&t;RMK&t;Renamed to memory.h&n; *&t;&t;RMK&t;Added TASK_SIZE and PAGE_OFFSET&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x10000000UL)
multiline_comment|/*&n; * These are exactly the same on the RiscPC as the&n; * physical memory view.&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x) __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x) __phys_to_virt(x)
macro_line|#endif
eof
