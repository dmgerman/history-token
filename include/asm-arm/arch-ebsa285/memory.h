multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/memory.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   20-Oct-1996 RMK&t;Created&n; *   31-Dec-1997 RMK&t;Fixed definitions to reduce warnings.&n; *   17-May-1998 DAG&t;Added __virt_to_bus and __bus_to_virt functions.&n; *   21-Nov-1998 RMK&t;Changed __virt_to_bus and __bus_to_virt to macros.&n; *   21-Mar-1999 RMK&t;Added PAGE_OFFSET for co285 architecture.&n; *&t;&t;&t;Renamed to memory.h&n; *&t;&t;&t;Moved PAGE_OFFSET and TASK_SIZE here&n; */
macro_line|#ifndef __ASM_ARCH_MMU_H
DECL|macro|__ASM_ARCH_MMU_H
mdefine_line|#define __ASM_ARCH_MMU_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_FOOTBRIDGE_ADDIN)
multiline_comment|/*&n; * If we may be using add-in footbridge mode, then we must&n; * use the out-of-line translation that makes use of the&n; * PCI BAR&n; */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|__virt_to_bus
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__bus_to_virt
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#elif defined(CONFIG_FOOTBRIDGE_HOST)
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;((x) - 0xe0000000)
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)&t;((x) + 0xe0000000)
macro_line|#else
macro_line|#error &quot;Undefined footbridge mode&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_ARCH_FOOTBRIDGE)
multiline_comment|/* Task size and page offset at 3GB */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(0xc0000000UL)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(0xc0000000UL)
macro_line|#elif defined(CONFIG_ARCH_CO285)
multiline_comment|/* Task size and page offset at 1.5GB */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(0x60000000UL)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;(0x60000000UL)
macro_line|#else
macro_line|#error &quot;Undefined footbridge architecture&quot;
macro_line|#endif
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;&t;(0x04000000UL)
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;&t;(0x00000000UL)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)
multiline_comment|/*&n; * The DRAM is always contiguous.&n; */
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(vpage) ((unsigned long)(vpage) - PAGE_OFFSET)
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(ppage) ((unsigned long)(ppage) + PAGE_OFFSET)
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(addr)&t;(0)
macro_line|#endif
eof
