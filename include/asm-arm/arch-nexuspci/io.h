multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/io.h&n; *&n; * Copyright (C) 1997-1999 Russell King&n; * Copyright (C) 2000 FutureTV Labs Ltd.&n; */
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
multiline_comment|/* PCI addresses must have been ioremapped */
r_if
c_cond
(paren
id|a
op_le
l_int|0xc0000000
op_logical_or
id|a
op_ge
l_int|0xe0000000
)paren
op_star
(paren
(paren
r_int
op_star
)paren
l_int|0
)paren
op_assign
l_int|0
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
r_if
c_cond
(paren
id|a
op_ge
l_int|16
op_star
l_int|1048576
)paren
id|BUG
c_func
(paren
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
multiline_comment|/*&n; * Generic virtual read/write&n; */
DECL|macro|__arch_getw
mdefine_line|#define __arch_getw(a)&t;&t;(*(volatile unsigned short *)(a))
DECL|macro|__arch_putw
mdefine_line|#define __arch_putw(v,a)&t;(*(volatile unsigned short *)(a) = (v))
multiline_comment|/*&n; * ioremap support - validate a PCI memory address,&n; * and convert a PCI memory address to a physical&n; * address for the page tables.&n; */
DECL|macro|iomem_valid_addr
mdefine_line|#define iomem_valid_addr(iomem,sz)&t;&bslash;&n;&t;((iomem) &lt; 0x80000000 &amp;&amp; (iomem) + (sz) &lt;= 0x80000000)
DECL|macro|iomem_to_phys
mdefine_line|#define iomem_to_phys(iomem)&t;((iomem) + PLX_MEM_START)
macro_line|#endif
eof
