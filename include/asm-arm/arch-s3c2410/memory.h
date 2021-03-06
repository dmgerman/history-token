multiline_comment|/*&n; *  linux/include/asm-arm/arch-s3c2410/memory.h&n; *&n; *  from linux/include/asm-arm/arch-rpc/memory.h&n; *&n; *  Copyright (C) 1996,1997,1998 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   20-Oct-1996 RMK&t;Created&n; *   31-Dec-1997 RMK&t;Fixed definitions to reduce warnings&n; *   11-Jan-1998 RMK&t;Uninlined to reduce hits on cache&n; *   08-Feb-1998 RMK&t;Added __virt_to_bus and __bus_to_virt&n; *   21-Mar-1999 RMK&t;Renamed to memory.h&n; *&t;&t; RMK&t;Added TASK_SIZE and PAGE_OFFSET&n; *   05-Apr-2004 BJD    Copied and altered for arch-s3c2410&n; *   17-Mar-2005 LCVR   Modified for S3C2400&n;*/
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * DRAM starts at 0x30000000 for S3C2410/S3C2440&n; * and at 0x0C000000 for S3C2400&n; */
macro_line|#ifdef CONFIG_CPU_S3C2400
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x0C000000UL)
macro_line|#else
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0x30000000UL)
macro_line|#endif
multiline_comment|/*&n; * These are exactly the same on the S3C2410 as the&n; * physical memory view.&n;*/
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x) __virt_to_phys(x)
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x) __phys_to_virt(x)
macro_line|#endif
eof
