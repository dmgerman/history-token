multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/io.h&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Modifications:&n; *   06-12-1997&t;RMK&t;Created.&n; *   07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
multiline_comment|/*&n; * Translation of various region addresses to virtual addresses&n; */
DECL|macro|__io
mdefine_line|#define __io(a)&t;&t;&t;(PCIO_BASE + (a))
macro_line|#if 1
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;((unsigned long)(a))
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;(PCIMEM_BASE + (unsigned long)(a))
macro_line|#else
DECL|function|___mem_pci
r_static
r_inline
r_int
r_int
id|___mem_pci
c_func
(paren
r_int
r_int
id|a
)paren
(brace
id|BUG_ON
c_func
(paren
id|a
op_le
l_int|0xc0000000
op_logical_or
id|a
op_ge
l_int|0xe0000000
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
DECL|function|___mem_isa
r_static
r_inline
r_int
r_int
id|___mem_isa
c_func
(paren
r_int
r_int
id|a
)paren
(brace
id|BUG_ON
c_func
(paren
id|a
op_ge
l_int|16
op_star
l_int|1048576
)paren
suffix:semicolon
r_return
id|PCIMEM_BASE
op_plus
id|a
suffix:semicolon
)brace
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;___mem_pci((unsigned long)(a))
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;___mem_isa((unsigned long)(a))
macro_line|#endif
macro_line|#endif
eof
