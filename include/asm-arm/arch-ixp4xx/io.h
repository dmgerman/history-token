multiline_comment|/*&n; * linux/include/asm-arm/arch-ixp4xx/io.h&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002-2004  MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
macro_line|#include &lt;asm/hardware.h&gt;
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff0000
DECL|macro|BIT
mdefine_line|#define&t;BIT(x)&t;((1)&lt;&lt;(x))
r_extern
r_int
(paren
op_star
id|ixp4xx_pci_read
)paren
(paren
id|u32
id|addr
comma
id|u32
id|cmd
comma
id|u32
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|ixp4xx_pci_write
c_func
(paren
id|u32
id|addr
comma
id|u32
id|cmd
comma
id|u32
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * IXP4xx provides two methods of accessing PCI memory space:&n; *&n; * 1) A direct mapped window from 0x48000000 to 0x4bffffff (64MB).&n; *    To access PCI via this space, we simply ioremap() the BAR&n; *    into the kernel and we can use the standard read[bwl]/write[bwl]&n; *    macros. This is the preffered method due to speed but it&n; *    limits the system to just 64MB of PCI memory. This can be &n; *    problamatic if using video cards and other memory-heavy&n; *    targets.&n; *&n; * 2) If &gt; 64MB of memory space is required, the IXP4xx can be configured&n; *    to use indirect registers to access PCI (as we do below for I/O&n; *    transactions). This allows for up to 128MB (0x48000000 to 0x4fffffff)&n; *    of memory on the bus. The disadvantadge of this is that every &n; *    PCI access requires three local register accesses plus a spinlock,&n; *    but in some cases the performance hit is acceptable. In addition,&n; *    you cannot mmap() PCI devices in this case.&n; *&n; */
macro_line|#ifndef&t;CONFIG_IXP4XX_INDIRECT_PCI
DECL|macro|__mem_pci
mdefine_line|#define __mem_pci(a)&t;&t;((unsigned long)(a))
macro_line|#else
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * In the case of using indirect PCI, we simply return the actual PCI&n; * address and our read/write implementation use that to drive the &n; * access registers. If something outside of PCI is ioremap&squot;d, we&n; * fallback to the default.&n; */
r_static
r_inline
r_void
op_star
DECL|function|__ixp4xx_ioremap
id|__ixp4xx_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|size
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|align
)paren
(brace
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
OL
l_int|0x48000000
)paren
op_logical_or
(paren
id|addr
OG
l_int|0x4fffffff
)paren
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|addr
comma
id|size
comma
id|flags
comma
id|align
)paren
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_iounmap
id|__ixp4xx_iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_extern
r_void
id|__iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u32
)paren
id|addr
op_ge
id|VMALLOC_START
)paren
id|__iounmap
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|__arch_ioremap
mdefine_line|#define __arch_ioremap(a, s, f, x)&t;__ixp4xx_ioremap(a, s, f, x)
DECL|macro|__arch_iounmap
mdefine_line|#define&t;__arch_iounmap(a)&t;&t;__ixp4xx_iounmap(a)
DECL|macro|writeb
mdefine_line|#define&t;writeb(p, v)&t;&t;&t;__ixp4xx_writeb(p, v)
DECL|macro|writew
mdefine_line|#define&t;writew(p, v)&t;&t;&t;__ixp4xx_writew(p, v)
DECL|macro|writel
mdefine_line|#define&t;writel(p, v)&t;&t;&t;__ixp4xx_writel(p, v)
DECL|macro|writesb
mdefine_line|#define&t;writesb(p, v, l)&t;&t;__ixp4xx_writesb(p, v, l)
DECL|macro|writesw
mdefine_line|#define&t;writesw(p, v, l)&t;&t;__ixp4xx_writesw(p, v, l)
DECL|macro|writesl
mdefine_line|#define&t;writesl(p, v, l)&t;&t;__ixp4xx_writesl(p, v, l)
DECL|macro|readb
mdefine_line|#define&t;readb(p)&t;&t;&t;__ixp4xx_readb(p)
DECL|macro|readw
mdefine_line|#define&t;readw(p)&t;&t;&t;__ixp4xx_readw(p)
DECL|macro|readl
mdefine_line|#define&t;readl(p)&t;&t;&t;__ixp4xx_readl(p)
DECL|macro|readsb
mdefine_line|#define&t;readsb(p, v, l)&t;&t;&t;__ixp4xx_readsb(p, v, l)
DECL|macro|readsw
mdefine_line|#define&t;readsw(p, v, l)&t;&t;&t;__ixp4xx_readsw(p, v, l)
DECL|macro|readsl
mdefine_line|#define&t;readsl(p, v, l)&t;&t;&t;__ixp4xx_readsl(p, v, l)
r_static
r_inline
r_void
DECL|function|__ixp4xx_writeb
id|__ixp4xx_writeb
c_func
(paren
id|u8
id|value
comma
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|VMALLOC_START
)paren
(brace
id|__raw_writeb
c_func
(paren
id|value
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
id|BIT
c_func
(paren
id|n
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
id|data
op_assign
id|value
op_lshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
id|ixp4xx_pci_write
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_MEMWRITE
comma
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_writesb
id|__ixp4xx_writesb
c_func
(paren
id|u32
id|bus_addr
comma
id|u8
op_star
id|vaddr
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|writeb
c_func
(paren
op_star
id|vaddr
op_increment
comma
id|bus_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_writew
id|__ixp4xx_writew
c_func
(paren
id|u16
id|value
comma
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|VMALLOC_START
)paren
(brace
id|__raw_writew
c_func
(paren
id|value
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
(paren
id|BIT
c_func
(paren
id|n
)paren
op_or
id|BIT
c_func
(paren
id|n
op_plus
l_int|1
)paren
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
id|data
op_assign
id|value
op_lshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
id|ixp4xx_pci_write
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_MEMWRITE
comma
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_writesw
id|__ixp4xx_writesw
c_func
(paren
id|u32
id|bus_addr
comma
id|u16
op_star
id|vaddr
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|writew
c_func
(paren
op_star
id|vaddr
op_increment
comma
id|bus_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_writel
id|__ixp4xx_writel
c_func
(paren
id|u32
id|value
comma
id|u32
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_ge
id|VMALLOC_START
)paren
(brace
id|__raw_writel
c_func
(paren
id|value
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ixp4xx_pci_write
c_func
(paren
id|addr
comma
id|NP_CMD_MEMWRITE
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_writesl
id|__ixp4xx_writesl
c_func
(paren
id|u32
id|bus_addr
comma
id|u32
op_star
id|vaddr
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|writel
c_func
(paren
op_star
id|vaddr
op_increment
comma
id|bus_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_char
DECL|function|__ixp4xx_readb
id|__ixp4xx_readb
c_func
(paren
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|VMALLOC_START
)paren
r_return
id|__raw_readb
c_func
(paren
id|addr
)paren
suffix:semicolon
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
id|BIT
c_func
(paren
id|n
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_read
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_MEMREAD
comma
op_amp
id|data
)paren
)paren
r_return
l_int|0xff
suffix:semicolon
r_return
id|data
op_rshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_readsb
id|__ixp4xx_readsb
c_func
(paren
id|u32
id|bus_addr
comma
id|u8
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|vaddr
op_increment
op_assign
id|readb
c_func
(paren
id|bus_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__ixp4xx_readw
id|__ixp4xx_readw
c_func
(paren
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|VMALLOC_START
)paren
r_return
id|__raw_readw
c_func
(paren
id|addr
)paren
suffix:semicolon
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
(paren
id|BIT
c_func
(paren
id|n
)paren
op_or
id|BIT
c_func
(paren
id|n
op_plus
l_int|1
)paren
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_read
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_MEMREAD
comma
op_amp
id|data
)paren
)paren
r_return
l_int|0xffff
suffix:semicolon
r_return
id|data
op_rshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_readsw
id|__ixp4xx_readsw
c_func
(paren
id|u32
id|bus_addr
comma
id|u16
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|vaddr
op_increment
op_assign
id|readw
c_func
(paren
id|bus_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__ixp4xx_readl
id|__ixp4xx_readl
c_func
(paren
id|u32
id|addr
)paren
(brace
id|u32
id|data
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|VMALLOC_START
)paren
r_return
id|__raw_readl
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_read
c_func
(paren
id|addr
comma
id|NP_CMD_MEMREAD
comma
op_amp
id|data
)paren
)paren
r_return
l_int|0xffffffff
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_readsl
id|__ixp4xx_readsl
c_func
(paren
id|u32
id|bus_addr
comma
id|u32
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|vaddr
op_increment
op_assign
id|readl
c_func
(paren
id|bus_addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We can use the built-in functions b/c they end up calling writeb/readb&n; */
DECL|macro|memset_io
mdefine_line|#define memset_io(c,v,l)&t;&t;_memset_io((c),(v),(l))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,c,l)&t;&t;_memcpy_fromio((a),(c),(l))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(c,a,l)&t;&t;_memcpy_toio((c),(a),(l))
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(s,c,l,b) &bslash;&n;&t;&t;&t;&t;eth_copy_and_sum((s),__mem_pci(c),(l),(b))
r_static
r_inline
r_int
DECL|function|check_signature
id|check_signature
c_func
(paren
r_int
r_int
id|bus_addr
comma
r_const
r_int
r_char
op_star
id|signature
comma
r_int
id|length
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|bus_addr
)paren
op_ne
op_star
id|signature
)paren
r_goto
id|out
suffix:semicolon
id|bus_addr
op_increment
suffix:semicolon
id|signature
op_increment
suffix:semicolon
id|length
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * IXP4xx does not have a transparent cpu -&gt; PCI I/O translation&n; * window.  Instead, it has a set of registers that must be tweaked&n; * with the proper byte lanes, command types, and address for the&n; * transaction.  This means that we need to override the default&n; * I/O functions.&n; */
DECL|macro|outb
mdefine_line|#define&t;outb(p, v)&t;&t;&t;__ixp4xx_outb(p, v)
DECL|macro|outw
mdefine_line|#define&t;outw(p, v)&t;&t;&t;__ixp4xx_outw(p, v)
DECL|macro|outl
mdefine_line|#define&t;outl(p, v)&t;&t;&t;__ixp4xx_outl(p, v)
DECL|macro|outsb
mdefine_line|#define&t;outsb(p, v, l)&t;&t;&t;__ixp4xx_outsb(p, v, l)
DECL|macro|outsw
mdefine_line|#define&t;outsw(p, v, l)&t;&t;&t;__ixp4xx_outsw(p, v, l)
DECL|macro|outsl
mdefine_line|#define&t;outsl(p, v, l)&t;&t;&t;__ixp4xx_outsl(p, v, l)
DECL|macro|inb
mdefine_line|#define&t;inb(p)&t;&t;&t;&t;__ixp4xx_inb(p)
DECL|macro|inw
mdefine_line|#define&t;inw(p)&t;&t;&t;&t;__ixp4xx_inw(p)
DECL|macro|inl
mdefine_line|#define&t;inl(p)&t;&t;&t;&t;__ixp4xx_inl(p)
DECL|macro|insb
mdefine_line|#define&t;insb(p, v, l)&t;&t;&t;__ixp4xx_insb(p, v, l)
DECL|macro|insw
mdefine_line|#define&t;insw(p, v, l)&t;&t;&t;__ixp4xx_insw(p, v, l)
DECL|macro|insl
mdefine_line|#define&t;insl(p, v, l)&t;&t;&t;__ixp4xx_insl(p, v, l)
r_static
r_inline
r_void
DECL|function|__ixp4xx_outb
id|__ixp4xx_outb
c_func
(paren
id|u8
id|value
comma
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
id|BIT
c_func
(paren
id|n
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
id|data
op_assign
id|value
op_lshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
id|ixp4xx_pci_write
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_IOWRITE
comma
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_outsb
id|__ixp4xx_outsb
c_func
(paren
id|u32
id|io_addr
comma
id|u8
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|outb
c_func
(paren
op_star
id|vaddr
op_increment
comma
id|io_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_outw
id|__ixp4xx_outw
c_func
(paren
id|u16
id|value
comma
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
(paren
id|BIT
c_func
(paren
id|n
)paren
op_or
id|BIT
c_func
(paren
id|n
op_plus
l_int|1
)paren
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
id|data
op_assign
id|value
op_lshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
id|ixp4xx_pci_write
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_IOWRITE
comma
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_outsw
id|__ixp4xx_outsw
c_func
(paren
id|u32
id|io_addr
comma
id|u16
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|outw
c_func
(paren
id|cpu_to_le16
c_func
(paren
op_star
id|vaddr
op_increment
)paren
comma
id|io_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_outl
id|__ixp4xx_outl
c_func
(paren
id|u32
id|value
comma
id|u32
id|addr
)paren
(brace
id|ixp4xx_pci_write
c_func
(paren
id|addr
comma
id|NP_CMD_IOWRITE
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_outsl
id|__ixp4xx_outsl
c_func
(paren
id|u32
id|io_addr
comma
id|u32
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|outl
c_func
(paren
op_star
id|vaddr
op_increment
comma
id|io_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u8
DECL|function|__ixp4xx_inb
id|__ixp4xx_inb
c_func
(paren
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
id|BIT
c_func
(paren
id|n
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_read
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_IOREAD
comma
op_amp
id|data
)paren
)paren
r_return
l_int|0xff
suffix:semicolon
r_return
id|data
op_rshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_insb
id|__ixp4xx_insb
c_func
(paren
id|u32
id|io_addr
comma
id|u8
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|vaddr
op_increment
op_assign
id|inb
c_func
(paren
id|io_addr
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u16
DECL|function|__ixp4xx_inw
id|__ixp4xx_inw
c_func
(paren
id|u32
id|addr
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
id|n
op_assign
id|addr
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
(paren
l_int|0xf
op_amp
op_complement
(paren
id|BIT
c_func
(paren
id|n
)paren
op_or
id|BIT
c_func
(paren
id|n
op_plus
l_int|1
)paren
)paren
)paren
op_lshift
id|IXP4XX_PCI_NP_CBE_BESL
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_read
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_IOREAD
comma
op_amp
id|data
)paren
)paren
r_return
l_int|0xffff
suffix:semicolon
r_return
id|data
op_rshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_insw
id|__ixp4xx_insw
c_func
(paren
id|u32
id|io_addr
comma
id|u16
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|vaddr
op_increment
op_assign
id|le16_to_cpu
c_func
(paren
id|inw
c_func
(paren
id|io_addr
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|__ixp4xx_inl
id|__ixp4xx_inl
c_func
(paren
id|u32
id|addr
)paren
(brace
id|u32
id|data
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_read
c_func
(paren
id|addr
comma
id|NP_CMD_IOREAD
comma
op_amp
id|data
)paren
)paren
r_return
l_int|0xffffffff
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__ixp4xx_insl
id|__ixp4xx_insl
c_func
(paren
id|u32
id|io_addr
comma
id|u32
op_star
id|vaddr
comma
id|u32
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|vaddr
op_increment
op_assign
id|inl
c_func
(paren
id|io_addr
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
singleline_comment|//  __ASM_ARM_ARCH_IO_H
eof
