multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/memory.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   20-Oct-1996 RMK&t;Created&n; *   31-Dec-1997 RMK&t;Fixed definitions to reduce warnings&n; *   21-Mar-1999 RMK&t;Renamed to memory.h&n; *&t;&t; RMK&t;Moved TASK_SIZE and PAGE_OFFSET here&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x00000000UL)
multiline_comment|/*&n; * We keep this 1:1 so that we don&squot;t interfere&n; * with the PCMCIA memory regions&n; */
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;(x)
macro_line|#endif
eof
