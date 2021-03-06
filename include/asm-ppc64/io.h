macro_line|#ifndef _PPC64_IO_H
DECL|macro|_PPC64_IO_H
mdefine_line|#define _PPC64_IO_H
multiline_comment|/* &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef CONFIG_PPC_ISERIES 
macro_line|#include &lt;asm/iSeries/iSeries_io.h&gt;
macro_line|#endif  
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm-generic/iomap.h&gt;
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw(p, a, c) _insw_ns((volatile u16 *)(p), (a), (c))
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl(p, a, c) _insl_ns((volatile u32 *)(p), (a), (c))
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw(p, a, c) _outsw_ns((volatile u16 *)(p), (a), (c))
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl(p, a, c) _outsl_ns((volatile u32 *)(p), (a), (c))
DECL|macro|SIO_CONFIG_RA
mdefine_line|#define SIO_CONFIG_RA&t;0x398
DECL|macro|SIO_CONFIG_RD
mdefine_line|#define SIO_CONFIG_RD&t;0x399
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO
r_extern
r_int
r_int
id|isa_io_base
suffix:semicolon
r_extern
r_int
r_int
id|pci_io_base
suffix:semicolon
r_extern
r_int
r_int
id|io_page_mask
suffix:semicolon
DECL|macro|MAX_ISA_PORT
mdefine_line|#define MAX_ISA_PORT 0x10000
DECL|macro|_IO_IS_VALID
mdefine_line|#define _IO_IS_VALID(port) ((port) &gt;= MAX_ISA_PORT || (1 &lt;&lt; (port&gt;&gt;PAGE_SHIFT)) &bslash;&n;&t;&t;&t;    &amp; io_page_mask)
macro_line|#ifdef CONFIG_PPC_ISERIES
multiline_comment|/* __raw_* accessors aren&squot;t supported on iSeries */
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(addr)&t;{ BUG(); 0; }
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(addr)       { BUG(); 0; }
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(addr)       { BUG(); 0; }
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(addr)       { BUG(); 0; }
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v, addr)   { BUG(); 0; }
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v, addr)   { BUG(); 0; }
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v, addr)   { BUG(); 0; }
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v, addr)   { BUG(); 0; }
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;iSeries_Read_Byte(addr)
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;iSeries_Read_Word(addr)
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;iSeries_Read_Long(addr)
DECL|macro|writeb
mdefine_line|#define writeb(data, addr)&t;iSeries_Write_Byte((data),(addr))
DECL|macro|writew
mdefine_line|#define writew(data, addr)&t;iSeries_Write_Word((data),(addr))
DECL|macro|writel
mdefine_line|#define writel(data, addr)&t;iSeries_Write_Long((data),(addr))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;iSeries_memset_io((a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;iSeries_memcpy_fromio((a), (b), (c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;iSeries_memcpy_toio((a), (b), (c))
DECL|macro|inb
mdefine_line|#define inb(addr)&t;&t;readb(((void __iomem *)(long)(addr)))
DECL|macro|inw
mdefine_line|#define inw(addr)&t;&t;readw(((void __iomem *)(long)(addr)))
DECL|macro|inl
mdefine_line|#define inl(addr)&t;&t;readl(((void __iomem *)(long)(addr)))
DECL|macro|outb
mdefine_line|#define outb(data,addr)&t;&t;writeb(data,((void __iomem *)(long)(addr)))
DECL|macro|outw
mdefine_line|#define outw(data,addr)&t;&t;writew(data,((void __iomem *)(long)(addr)))
DECL|macro|outl
mdefine_line|#define outl(data,addr)&t;&t;writel(data,((void __iomem *)(long)(addr)))
multiline_comment|/*&n; * The *_ns versions below don&squot;t do byte-swapping.&n; * Neither do the standard versions now, these are just here&n; * for older code.&n; */
DECL|macro|insw_ns
mdefine_line|#define insw_ns(port, buf, ns)&t;_insw_ns((u16 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|insl_ns
mdefine_line|#define insl_ns(port, buf, nl)&t;_insl_ns((u32 *)((port)+pci_io_base), (buf), (nl))
macro_line|#else
DECL|function|__raw_readb
r_static
r_inline
r_int
r_char
id|__raw_readb
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__raw_readw
r_static
r_inline
r_int
r_int
id|__raw_readw
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__raw_readl
r_static
r_inline
r_int
r_int
id|__raw_readl
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__raw_readq
r_static
r_inline
r_int
r_int
id|__raw_readq
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__raw_writeb
r_static
r_inline
r_void
id|__raw_writeb
c_func
(paren
r_int
r_char
id|v
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
id|__force
op_star
)paren
id|addr
op_assign
id|v
suffix:semicolon
)brace
DECL|function|__raw_writew
r_static
r_inline
r_void
id|__raw_writew
c_func
(paren
r_int
r_int
id|v
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|v
suffix:semicolon
)brace
DECL|function|__raw_writel
r_static
r_inline
r_void
id|__raw_writel
c_func
(paren
r_int
r_int
id|v
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|v
suffix:semicolon
)brace
DECL|function|__raw_writeq
r_static
r_inline
r_void
id|__raw_writeq
c_func
(paren
r_int
r_int
id|v
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|v
suffix:semicolon
)brace
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;eeh_readb(addr)
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;eeh_readw(addr)
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;eeh_readl(addr)
DECL|macro|readq
mdefine_line|#define readq(addr)&t;&t;eeh_readq(addr)
DECL|macro|writeb
mdefine_line|#define writeb(data, addr)&t;eeh_writeb((data), (addr))
DECL|macro|writew
mdefine_line|#define writew(data, addr)&t;eeh_writew((data), (addr))
DECL|macro|writel
mdefine_line|#define writel(data, addr)&t;eeh_writel((data), (addr))
DECL|macro|writeq
mdefine_line|#define writeq(data, addr)&t;eeh_writeq((data), (addr))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;eeh_memset_io((a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;eeh_memcpy_fromio((a),(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;eeh_memcpy_toio((a),(b),(c))
DECL|macro|inb
mdefine_line|#define inb(port)&t;&t;eeh_inb((unsigned long)port)
DECL|macro|outb
mdefine_line|#define outb(val, port)&t;&t;eeh_outb(val, (unsigned long)port)
DECL|macro|inw
mdefine_line|#define inw(port)&t;&t;eeh_inw((unsigned long)port)
DECL|macro|outw
mdefine_line|#define outw(val, port)&t;&t;eeh_outw(val, (unsigned long)port)
DECL|macro|inl
mdefine_line|#define inl(port)&t;&t;eeh_inl((unsigned long)port)
DECL|macro|outl
mdefine_line|#define outl(val, port)&t;&t;eeh_outl(val, (unsigned long)port)
multiline_comment|/*&n; * The insw/outsw/insl/outsl macros don&squot;t do byte-swapping.&n; * They are only used in practice for transferring buffers which&n; * are arrays of bytes, and byte-swapping is not appropriate in&n; * that case.  - paulus */
DECL|macro|insb
mdefine_line|#define insb(port, buf, ns)&t;eeh_insb((port), (buf), (ns))
DECL|macro|insw
mdefine_line|#define insw(port, buf, ns)&t;eeh_insw_ns((port), (buf), (ns))
DECL|macro|insl
mdefine_line|#define insl(port, buf, nl)&t;eeh_insl_ns((port), (buf), (nl))
DECL|macro|insw_ns
mdefine_line|#define insw_ns(port, buf, ns)&t;eeh_insw_ns((port), (buf), (ns))
DECL|macro|insl_ns
mdefine_line|#define insl_ns(port, buf, nl)&t;eeh_insl_ns((port), (buf), (nl))
DECL|macro|outsb
mdefine_line|#define outsb(port, buf, ns)  _outsb((u8 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, ns)  _outsw_ns((u16 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|outsl
mdefine_line|#define outsl(port, buf, nl)  _outsl_ns((u32 *)((port)+pci_io_base), (buf), (nl))
macro_line|#endif
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(addr) readb(addr)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(addr) readw(addr)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(addr) readl(addr)
DECL|macro|readq_relaxed
mdefine_line|#define readq_relaxed(addr) readq(addr)
r_extern
r_void
id|_insb
c_func
(paren
r_volatile
id|u8
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_outsb
c_func
(paren
r_volatile
id|u8
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_insw
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_outsw
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_insl
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_void
id|_outsl
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_void
id|_insw_ns
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_outsw_ns
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_insl_ns
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_void
id|_outsl_ns
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
DECL|macro|mmiowb
mdefine_line|#define mmiowb()
multiline_comment|/*&n; * output pause versions need a delay at least for the&n; * w83c105 ide controller in a p610.&n; */
DECL|macro|inb_p
mdefine_line|#define inb_p(port)             inb(port)
DECL|macro|outb_p
mdefine_line|#define outb_p(val, port)       (udelay(1), outb((val), (port)))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)             inw(port)
DECL|macro|outw_p
mdefine_line|#define outw_p(val, port)       (udelay(1), outw((val), (port)))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)             inl(port)
DECL|macro|outl_p
mdefine_line|#define outl_p(val, port)       (udelay(1), outl((val), (port)))
multiline_comment|/*&n; * The *_ns versions below don&squot;t do byte-swapping.&n; * Neither do the standard versions now, these are just here&n; * for older code.&n; */
DECL|macro|outsw_ns
mdefine_line|#define outsw_ns(port, buf, ns)&t;_outsw_ns((u16 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|outsl_ns
mdefine_line|#define outsl_ns(port, buf, nl)&t;_outsl_ns((u32 *)((port)+pci_io_base), (buf), (nl))
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT ~(0UL)
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|__ioremap_explicit
c_func
(paren
r_int
r_int
id|p_addr
comma
r_int
r_int
id|v_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|__iomem
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/**&n; * ioremap     -   map bus memory into CPU space&n; * @address:   bus address of the memory&n; * @size:      size of the resource to map&n; *&n; * ioremap performs a platform specific sequence of operations to&n; * make bus memory CPU accessible via the readb/readw/readl/writeb/&n; * writew/writel functions and the other mmio helpers. The returned&n; * address is not guaranteed to be usable directly as a virtual&n; * address.&n; */
r_extern
r_void
id|__iomem
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(addr, size)&t;ioremap((addr), (size))
r_extern
r_int
id|iounmap_explicit
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|iounmap
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|__iomem
op_star
id|reserve_phb_iospace
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;virt_to_phys&t;-&t;map virtual addresses to physical&n; *&t;@address: address to remap&n; *&n; *&t;The returned physical address is the physical (CPU) mapping for&n; *&t;the memory address given. It is only valid to use this function on&n; *&t;addresses directly mapped or allocated via kmalloc.&n; *&n; *&t;This function does not give bus mappings for DMA transfers. In&n; *&t;almost all conceivable cases a device driver should not be using&n; *&t;this function&n; */
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;phys_to_virt&t;-&t;map physical address to virtual&n; *&t;@address: address to remap&n; *&n; *&t;The returned virtual address is a current CPU mapping for&n; *&t;the memory address given. It is only valid to use this function on&n; *&t;addresses that have a kernel mapping&n; *&n; *&t;This function does not handle bus mappings for DMA transfers. In&n; *&t;almost all conceivable cases a device driver should not be using&n; *&t;this function&n; */
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Change &quot;struct page&quot; to physical address.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
multiline_comment|/* We do NOT want virtual merging, it would put too much pressure on&n; * our iommu allocator. Instead, we want drivers to be smart enough&n; * to coalesce sglists that happen to have been mapped in a contiguous&n; * way by the iommu&n; */
DECL|macro|BIO_VMERGE_BOUNDARY
mdefine_line|#define BIO_VMERGE_BOUNDARY&t;0
macro_line|#endif /* __KERNEL__ */
DECL|function|iosync
r_static
r_inline
r_void
id|iosync
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Enforce in-order execution of data I/O. &n; * No distinction between read/write on PPC; use eieio for all three.&n; */
DECL|macro|iobarrier_rw
mdefine_line|#define iobarrier_rw() eieio()
DECL|macro|iobarrier_r
mdefine_line|#define iobarrier_r()  eieio()
DECL|macro|iobarrier_w
mdefine_line|#define iobarrier_w()  eieio()
multiline_comment|/*&n; * 8, 16 and 32 bit, big and little endian I/O operations, with barrier.&n; * These routines do not perform EEH-related I/O address translation,&n; * and should not be used directly by device drivers.  Use inb/readb&n; * instead.&n; */
DECL|function|in_8
r_static
r_inline
r_int
id|in_8
c_func
(paren
r_const
r_volatile
r_int
r_char
id|__iomem
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lbz%U1%X1 %0,%1; twi 0,%0,0; isync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|out_8
r_static
r_inline
r_void
id|out_8
c_func
(paren
r_volatile
r_int
r_char
id|__iomem
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stb%U0%X0 %1,%0; sync&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|in_le16
r_static
r_inline
r_int
id|in_le16
c_func
(paren
r_const
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lhbrx %0,0,%1; twi 0,%0,0; isync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|in_be16
r_static
r_inline
r_int
id|in_be16
c_func
(paren
r_const
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lhz%U1%X1 %0,%1; twi 0,%0,0; isync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|out_le16
r_static
r_inline
r_void
id|out_le16
c_func
(paren
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sthbrx %1,0,%2; sync&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|out_be16
r_static
r_inline
r_void
id|out_be16
c_func
(paren
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sth%U0%X0 %1,%0; sync&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|in_le32
r_static
r_inline
r_int
id|in_le32
c_func
(paren
r_const
r_volatile
r_int
id|__iomem
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lwbrx %0,0,%1; twi 0,%0,0; isync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|in_be32
r_static
r_inline
r_int
id|in_be32
c_func
(paren
r_const
r_volatile
r_int
id|__iomem
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lwz%U1%X1 %0,%1; twi 0,%0,0; isync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|out_le32
r_static
r_inline
r_void
id|out_le32
c_func
(paren
r_volatile
r_int
id|__iomem
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwbrx %1,0,%2; sync&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|out_be32
r_static
r_inline
r_void
id|out_be32
c_func
(paren
r_volatile
r_int
id|__iomem
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stw%U0%X0 %1,%0; sync&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|in_le64
r_static
r_inline
r_int
r_int
id|in_le64
c_func
(paren
r_const
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
)paren
(brace
r_int
r_int
id|tmp
comma
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld %1,0(%2)&bslash;n&quot;
l_string|&quot;twi 0,%1,0&bslash;n&quot;
l_string|&quot;isync&bslash;n&quot;
l_string|&quot;rldimi %0,%1,5*8,1*8&bslash;n&quot;
l_string|&quot;rldimi %0,%1,3*8,2*8&bslash;n&quot;
l_string|&quot;rldimi %0,%1,1*8,3*8&bslash;n&quot;
l_string|&quot;rldimi %0,%1,7*8,4*8&bslash;n&quot;
l_string|&quot;rldicl %1,%1,32,0&bslash;n&quot;
l_string|&quot;rlwimi %0,%1,8,8,31&bslash;n&quot;
l_string|&quot;rlwimi %0,%1,24,16,23&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;b&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|in_be64
r_static
r_inline
r_int
r_int
id|in_be64
c_func
(paren
r_const
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld%U1%X1 %0,%1; twi 0,%0,0; isync&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|out_le64
r_static
r_inline
r_void
id|out_le64
c_func
(paren
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rldimi %0,%1,5*8,1*8&bslash;n&quot;
l_string|&quot;rldimi %0,%1,3*8,2*8&bslash;n&quot;
l_string|&quot;rldimi %0,%1,1*8,3*8&bslash;n&quot;
l_string|&quot;rldimi %0,%1,7*8,4*8&bslash;n&quot;
l_string|&quot;rldicl %1,%1,32,0&bslash;n&quot;
l_string|&quot;rlwimi %0,%1,8,8,31&bslash;n&quot;
l_string|&quot;rlwimi %0,%1,24,16,23&bslash;n&quot;
l_string|&quot;std %0,0(%3)&bslash;n&quot;
l_string|&quot;sync&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|val
)paren
comma
l_string|&quot;b&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|out_be64
r_static
r_inline
r_void
id|out_be64
c_func
(paren
r_volatile
r_int
r_int
id|__iomem
op_star
id|addr
comma
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;std%U0%X0 %1,%0; sync&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_PPC_ISERIES 
macro_line|#include &lt;asm/eeh.h&gt;
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/**&n; *&t;check_signature&t;&t;-&t;find BIOS signatures&n; *&t;@io_addr: mmio address to check&n; *&t;@signature:  signature block&n; *&t;@length: length of signature&n; *&n; *&t;Perform a signature comparison with the mmio address io_addr. This&n; *&t;address should have been obtained by ioremap.&n; *&t;Returns 1 on a match.&n; */
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|io_addr
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
macro_line|#ifndef CONFIG_PPC_ISERIES 
r_do
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|io_addr
)paren
op_ne
op_star
id|signature
)paren
r_goto
id|out
suffix:semicolon
id|io_addr
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
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Nothing to do */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
multiline_comment|/* Check of existence of legacy devices */
r_extern
r_int
id|check_legacy_ioport
c_func
(paren
r_int
r_int
id|base_port
)paren
suffix:semicolon
multiline_comment|/*&n; * Convert a physical pointer to a virtual kernel pointer for /dev/mem&n; * access&n; */
DECL|macro|xlate_dev_mem_ptr
mdefine_line|#define xlate_dev_mem_ptr(p)&t;__va(p)
multiline_comment|/*&n; * Convert a virtual cached pointer to an uncached pointer&n; */
DECL|macro|xlate_dev_kmem_ptr
mdefine_line|#define xlate_dev_kmem_ptr(p)&t;p
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC64_IO_H */
eof
