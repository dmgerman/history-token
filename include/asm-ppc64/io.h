macro_line|#ifndef _PPC64_IO_H
DECL|macro|_PPC64_IO_H
mdefine_line|#define _PPC64_IO_H
multiline_comment|/* &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef CONFIG_PPC_ISERIES 
macro_line|#include &lt;asm/iSeries/iSeries_io.h&gt;
macro_line|#endif  
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
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
multiline_comment|/* Define this if you want to see virt_to_* messages */
DECL|macro|__IO_DEBUG
macro_line|#undef __IO_DEBUG
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
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;iSeries_Read_Byte((void*)(addr))  
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;iSeries_Read_Word((void*)(addr))  
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;iSeries_Read_Long((void*)(addr))
DECL|macro|writeb
mdefine_line|#define writeb(data, addr)&t;iSeries_Write_Byte(data,((void*)(addr)))
DECL|macro|writew
mdefine_line|#define writew(data, addr)&t;iSeries_Write_Word(data,((void*)(addr)))
DECL|macro|writel
mdefine_line|#define writel(data, addr)&t;iSeries_Write_Long(data,((void*)(addr)))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;iSeries_memset_io((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;iSeries_memcpy_fromio((void *)(a), (void *)(b), (c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;iSeries_memcpy_toio((void *)(a), (void *)(b), (c))
DECL|macro|inb
mdefine_line|#define inb(addr)&t;&t;readb(((unsigned long)(addr)))  
DECL|macro|inw
mdefine_line|#define inw(addr)&t;&t;readw(((unsigned long)(addr)))  
DECL|macro|inl
mdefine_line|#define inl(addr)&t;&t;readl(((unsigned long)(addr)))
DECL|macro|outb
mdefine_line|#define outb(data,addr)&t;&t;writeb(data,((unsigned long)(addr)))  
DECL|macro|outw
mdefine_line|#define outw(data,addr)&t;&t;writew(data,((unsigned long)(addr)))  
DECL|macro|outl
mdefine_line|#define outl(data,addr)&t;&t;writel(data,((unsigned long)(addr)))
macro_line|#else
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;eeh_readb((void*)(addr))  
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;eeh_readw((void*)(addr))  
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;eeh_readl((void*)(addr))
DECL|macro|writeb
mdefine_line|#define writeb(data, addr)&t;eeh_writeb((data), ((void*)(addr)))
DECL|macro|writew
mdefine_line|#define writew(data, addr)&t;eeh_writew((data), ((void*)(addr)))
DECL|macro|writel
mdefine_line|#define writel(data, addr)&t;eeh_writel((data), ((void*)(addr)))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;eeh_memset_io((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;eeh_memcpy_fromio((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;eeh_memcpy_toio((void *)(a),(b),(c))
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
mdefine_line|#define insb(port, buf, ns)&t;_insb((u8 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|outsb
mdefine_line|#define outsb(port, buf, ns)&t;_outsb((u8 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|insw
mdefine_line|#define insw(port, buf, ns)&t;_insw_ns((u16 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, ns)&t;_outsw_ns((u16 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|insl
mdefine_line|#define insl(port, buf, nl)&t;_insl_ns((u32 *)((port)+pci_io_base), (buf), (nl))
DECL|macro|outsl
mdefine_line|#define outsl(port, buf, nl)&t;_outsl_ns((u32 *)((port)+pci_io_base), (buf), (nl))
macro_line|#endif
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(addr) readb(addr)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(addr) readw(addr)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(addr) readl(addr)
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
DECL|macro|insw_ns
mdefine_line|#define insw_ns(port, buf, ns)&t;_insw_ns((u16 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|outsw_ns
mdefine_line|#define outsw_ns(port, buf, ns)&t;_outsw_ns((u16 *)((port)+pci_io_base), (buf), (ns))
DECL|macro|insl_ns
mdefine_line|#define insl_ns(port, buf, nl)&t;_insl_ns((u32 *)((port)+pci_io_base), (buf), (nl))
DECL|macro|outsl_ns
mdefine_line|#define outsl_ns(port, buf, nl)&t;_outsl_ns((u32 *)((port)+pci_io_base), (buf), (nl))
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT ~(0UL)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Map in an area of physical address space, for accessing&n; * I/O devices etc.&n; */
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
r_extern
r_void
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
r_void
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
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
op_star
id|reserve_phb_iospace
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv, for&n; * addresses in the area where the kernel has the RAM mapped.&n; */
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
macro_line|#ifdef __IO_DEBUG
id|printk
c_func
(paren
l_string|&quot;virt_to_phys: 0x%08lx -&gt; 0x%08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|address
comma
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|address
)paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef __IO_DEBUG
id|printk
c_func
(paren
l_string|&quot;phys_to_virt: 0x%08lx -&gt; 0x%08lx&bslash;n&quot;
comma
id|address
comma
id|__va
c_func
(paren
id|address
)paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#if 0
mdefine_line|#define BIO_VMERGE_BOUNDARY&t;4096
macro_line|#endif
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
multiline_comment|/*&n; * 8, 16 and 32 bit, big and little endian I/O operations, with barrier.&n; */
DECL|function|in_8
r_static
r_inline
r_int
id|in_8
c_func
(paren
r_volatile
r_int
r_char
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
l_string|&quot;eieio; lbz%U1%X1 %0,%1&quot;
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
l_string|&quot;stb%U0%X0 %1,%0&quot;
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
r_volatile
r_int
r_int
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
l_string|&quot;eieio; lhbrx %0,0,%1&quot;
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
r_volatile
r_int
r_int
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
l_string|&quot;eieio; lhz%U1%X1 %0,%1&quot;
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
l_string|&quot;sthbrx %1,0,%2&quot;
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
l_string|&quot;sth%U0%X0 %1,%0&quot;
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
r_volatile
r_int
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
l_string|&quot;eieio; lwbrx %0,0,%1&quot;
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
r_volatile
r_int
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
l_string|&quot;eieio; lwz%U1%X1 %0,%1&quot;
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
l_string|&quot;stwbrx %1,0,%2&quot;
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
l_string|&quot;stw%U0%X0 %1,%0&quot;
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
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
r_int
r_int
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC64_IO_H */
eof
