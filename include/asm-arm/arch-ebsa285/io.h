multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/io.h&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Modifications:&n; *   06-12-1997&t;RMK&t;Created.&n; *   07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
multiline_comment|/*&n; * Translation of various region addresses to virtual addresses&n; */
DECL|macro|__io_pci
mdefine_line|#define __io_pci(a)&t;&t;(PCIO_BASE + (a))
macro_line|#if 1
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;((unsigned long)(a))
DECL|macro|__mem_isa
mdefine_line|#define __mem_isa(a)&t;&t;(PCIMEM_BASE + (unsigned long)(a))
macro_line|#else
DECL|function|___mem_pci
r_extern
id|__inline__
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
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
DECL|function|___mem_isa
r_extern
id|__inline__
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
multiline_comment|/* the following macro is depreciated */
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)&t;&t;__io_pci(p)
multiline_comment|/*&n; * Generic virtual read/write&n; */
DECL|macro|__arch_getb
mdefine_line|#define __arch_getb(a)&t;&t;(*(volatile unsigned char *)(a))
DECL|macro|__arch_getl
mdefine_line|#define __arch_getl(a)&t;&t;(*(volatile unsigned int  *)(a))
DECL|function|__arch_getw
r_extern
id|__inline__
r_int
r_int
id|__arch_getw
c_func
(paren
r_int
r_int
id|a
)paren
(brace
r_int
r_int
id|value
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldr%?h&t;%0, [%1, #0]&t;@ getw&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|a
)paren
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|macro|__arch_putb
mdefine_line|#define __arch_putb(v,a)&t;(*(volatile unsigned char *)(a) = (v))
DECL|macro|__arch_putl
mdefine_line|#define __arch_putl(v,a)&t;(*(volatile unsigned int  *)(a) = (v))
DECL|function|__arch_putw
r_extern
id|__inline__
r_void
id|__arch_putw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|a
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;str%?h&t;%0, [%1, #0]&t;@ putw&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|a
)paren
)paren
suffix:semicolon
)brace
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;&t;__arch_getb(__io_pci(p))
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&t;__arch_getw(__io_pci(p))
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&t;__arch_getl(__io_pci(p))
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;&t;__arch_putb(v,__io_pci(p))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;&t;__arch_putw(v,__io_pci(p))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;&t;__arch_putl(v,__io_pci(p))
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
multiline_comment|/*&n; * ioremap support - validate a PCI memory address,&n; * and convert a PCI memory address to a physical&n; * address for the page tables.&n; */
DECL|macro|valid_ioaddr
mdefine_line|#define valid_ioaddr(off,sz)&t;((off) &lt; 0x80000000 &amp;&amp; (off) + (sz) &lt;= 0x80000000)
DECL|macro|io_to_phys
mdefine_line|#define io_to_phys(off)&t;&t;((off) + DC21285_PCI_MEM)
multiline_comment|/*&n; * ioremap takes a PCI memory address, as specified in&n; * linux/Documentation/IO-mapping.txt&n; */
DECL|macro|__arch_ioremap
mdefine_line|#define __arch_ioremap(off,size,nocache)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _off = (off), _size = (size);&t;&t;&bslash;&n;&t;void *_ret = (void *)0;&t;&t;&t;&t;&t;&bslash;&n;&t;if (valid_ioaddr(_off, _size))&t;&t;&t;&t;&bslash;&n;&t;&t;_ret = __ioremap(io_to_phys(_off), _size, 0);&t;&bslash;&n;&t;_ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
eof
