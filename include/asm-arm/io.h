multiline_comment|/*&n; *  linux/include/asm-arm/io.h&n; *&n; *  Copyright (C) 1996-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *  16-Sep-1996&t;RMK&t;Inlined the inx/outx functions &amp; optimised for both&n; *&t;&t;&t;constant addresses and variable addresses.&n; *  04-Dec-1997&t;RMK&t;Moved a lot of this stuff to the new architecture&n; *&t;&t;&t;specific IO header files.&n; *  27-Mar-1999&t;PJB&t;Second parameter of memcpy_toio is const..&n; *  04-Apr-1999&t;PJB&t;Added check_signature.&n; *  12-Dec-1999&t;RMK&t;More cleanups&n; *  18-Jun-2000 RMK&t;Removed virt_to_* and friends definitions&n; */
macro_line|#ifndef __ASM_ARM_IO_H
DECL|macro|__ASM_ARM_IO_H
mdefine_line|#define __ASM_ARM_IO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
multiline_comment|/*&n; * Generic IO read/write.  These perform native-endian accesses.  Note&n; * that some architectures will want to re-define __raw_{read,write}w.&n; */
r_extern
r_void
id|__raw_writesb
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|data
comma
r_int
id|bytelen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_writesw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|data
comma
r_int
id|wordlen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_writesl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|data
comma
r_int
id|longlen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_readsb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|data
comma
r_int
id|bytelen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_readsw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|data
comma
r_int
id|wordlen
)paren
suffix:semicolon
r_extern
r_void
id|__raw_readsl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|data
comma
r_int
id|longlen
)paren
suffix:semicolon
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v,a)&t;(*(volatile unsigned char  *)(a) = (v))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)&t;(*(volatile unsigned short *)(a) = (v))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;(*(volatile unsigned int   *)(a) = (v))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)&t;&t;(*(volatile unsigned char  *)(a))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)&t;&t;(*(volatile unsigned short *)(a))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;(*(volatile unsigned int   *)(a))
multiline_comment|/*&n; * Bad read/write accesses...&n; */
r_extern
r_void
id|__readwrite_bug
c_func
(paren
r_const
r_char
op_star
id|fn
)paren
suffix:semicolon
multiline_comment|/*&n; * Now, pick up the machine-defined IO definitions&n; */
macro_line|#include &lt;asm/arch/io.h&gt;
macro_line|#ifdef __io_pci
macro_line|#warning machine class uses buggy __io_pci
macro_line|#endif
macro_line|#if defined(__arch_putb) || defined(__arch_putw) || defined(__arch_putl) || &bslash;&n;    defined(__arch_getb) || defined(__arch_getw) || defined(__arch_getl)
macro_line|#warning machine class uses old __arch_putw or __arch_getw
macro_line|#endif
multiline_comment|/*&n; *  IO port access primitives&n; *  -------------------------&n; *&n; * The ARM doesn&squot;t have special IO access instructions; all IO is memory&n; * mapped.  Note that these are defined to perform little endian accesses&n; * only.  Their primary purpose is to access PCI and ISA peripherals.&n; *&n; * Note that for a big endian machine, this implies that the following&n; * big endian mode connectivity is in place, as described by numerious&n; * ARM documents:&n; *&n; *    PCI:  D0-D7   D8-D15 D16-D23 D24-D31&n; *    ARM: D24-D31 D16-D23  D8-D15  D0-D7&n; *&n; * The machine specific io.h include defines __io to translate an &quot;IO&quot;&n; * address to a memory address.&n; *&n; * Note that we prevent GCC re-ordering or caching values in expressions&n; * by introducing sequence points into the in*() definitions.  Note that&n; * __raw_* do not guarantee this behaviour.&n; */
macro_line|#ifdef __io
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;&t;__raw_writeb(v,__io(p))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;&t;__raw_writew(cpu_to_le16(v),__io(p))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;&t;__raw_writel(cpu_to_le32(v),__io(p))
DECL|macro|inb
mdefine_line|#define inb(p)&t;({ unsigned int __v = __raw_readb(__io(p)); __v; })
DECL|macro|inw
mdefine_line|#define inw(p)&t;({ unsigned int __v = le16_to_cpu(__raw_readw(__io(p))); __v; })
DECL|macro|inl
mdefine_line|#define inl(p)&t;({ unsigned int __v = le32_to_cpu(__raw_readl(__io(p))); __v; })
DECL|macro|outsb
mdefine_line|#define outsb(p,d,l)&t;&t;__raw_writesb(__io(p),d,l)
DECL|macro|outsw
mdefine_line|#define outsw(p,d,l)&t;&t;__raw_writesw(__io(p),d,l)
DECL|macro|outsl
mdefine_line|#define outsl(p,d,l)&t;&t;__raw_writesl(__io(p),d,l)
DECL|macro|insb
mdefine_line|#define insb(p,d,l)&t;&t;__raw_readsb(__io(p),d,l)
DECL|macro|insw
mdefine_line|#define insw(p,d,l)&t;&t;__raw_readsw(__io(p),d,l)
DECL|macro|insl
mdefine_line|#define insl(p,d,l)&t;&t;__raw_readsl(__io(p),d,l)
macro_line|#endif
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port)&t;outb((val),(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port)&t;outw((val),(port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val,port)&t;outl((val),(port))
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;&t;inb((port))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)&t;&t;inw((port))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)&t;&t;inl((port))
DECL|macro|outsb_p
mdefine_line|#define outsb_p(port,from,len)&t;outsb(port,from,len)
DECL|macro|outsw_p
mdefine_line|#define outsw_p(port,from,len)&t;outsw(port,from,len)
DECL|macro|outsl_p
mdefine_line|#define outsl_p(port,from,len)&t;outsl(port,from,len)
DECL|macro|insb_p
mdefine_line|#define insb_p(port,to,len)&t;insb(port,to,len)
DECL|macro|insw_p
mdefine_line|#define insw_p(port,to,len)&t;insw(port,to,len)
DECL|macro|insl_p
mdefine_line|#define insl_p(port,to,len)&t;insl(port,to,len)
multiline_comment|/*&n; * String version of IO memory access ops:&n; */
r_extern
r_void
id|_memcpy_fromio
c_func
(paren
r_void
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|_memcpy_toio
c_func
(paren
r_int
r_int
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|_memset_io
c_func
(paren
r_int
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *  Memory access primitives&n; *  ------------------------&n; *&n; * These perform PCI memory accesses via an ioremap region.  They don&squot;t&n; * take an address as such, but a cookie.&n; *&n; * Again, this are defined to perform little endian accesses.  See the&n; * IO port primitives for more information.&n; */
macro_line|#ifdef __mem_pci
DECL|macro|readb
mdefine_line|#define readb(c) ({ unsigned int __v = __raw_readb(__mem_pci(c)); __v; })
DECL|macro|readw
mdefine_line|#define readw(c) ({ unsigned int __v = le16_to_cpu(__raw_readw(__mem_pci(c))); __v; })
DECL|macro|readl
mdefine_line|#define readl(c) ({ unsigned int __v = le32_to_cpu(__raw_readl(__mem_pci(c))); __v; })
DECL|macro|writeb
mdefine_line|#define writeb(v,c)&t;&t;__raw_writeb(v,__mem_pci(c))
DECL|macro|writew
mdefine_line|#define writew(v,c)&t;&t;__raw_writew(cpu_to_le16(v),__mem_pci(c))
DECL|macro|writel
mdefine_line|#define writel(v,c)&t;&t;__raw_writel(cpu_to_le32(v),__mem_pci(c))
DECL|macro|memset_io
mdefine_line|#define memset_io(c,v,l)&t;_memset_io(__mem_pci(c),(v),(l))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,c,l)&t;_memcpy_fromio((a),__mem_pci(c),(l))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(c,a,l)&t;_memcpy_toio(__mem_pci(c),(a),(l))
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
r_return
id|retval
suffix:semicolon
)brace
macro_line|#elif !defined(readb)
DECL|macro|readb
mdefine_line|#define readb(c)&t;&t;&t;(__readwrite_bug(&quot;readb&quot;),0)
DECL|macro|readw
mdefine_line|#define readw(c)&t;&t;&t;(__readwrite_bug(&quot;readw&quot;),0)
DECL|macro|readl
mdefine_line|#define readl(c)&t;&t;&t;(__readwrite_bug(&quot;readl&quot;),0)
DECL|macro|writeb
mdefine_line|#define writeb(v,c)&t;&t;&t;__readwrite_bug(&quot;writeb&quot;)
DECL|macro|writew
mdefine_line|#define writew(v,c)&t;&t;&t;__readwrite_bug(&quot;writew&quot;)
DECL|macro|writel
mdefine_line|#define writel(v,c)&t;&t;&t;__readwrite_bug(&quot;writel&quot;)
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(s,c,l,b)&t;__readwrite_bug(&quot;eth_io_copy_and_sum&quot;)
DECL|macro|check_signature
mdefine_line|#define check_signature(io,sig,len)&t;(0)
macro_line|#endif&t;/* __mem_pci */
multiline_comment|/*&n; * If this architecture has ISA IO, then define the isa_read/isa_write&n; * macros.&n; */
macro_line|#ifdef __mem_isa
DECL|macro|isa_readb
mdefine_line|#define isa_readb(addr)&t;&t;&t;__raw_readb(__mem_isa(addr))
DECL|macro|isa_readw
mdefine_line|#define isa_readw(addr)&t;&t;&t;__raw_readw(__mem_isa(addr))
DECL|macro|isa_readl
mdefine_line|#define isa_readl(addr)&t;&t;&t;__raw_readl(__mem_isa(addr))
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(val,addr)&t;&t;__raw_writeb(val,__mem_isa(addr))
DECL|macro|isa_writew
mdefine_line|#define isa_writew(val,addr)&t;&t;__raw_writew(val,__mem_isa(addr))
DECL|macro|isa_writel
mdefine_line|#define isa_writel(val,addr)&t;&t;__raw_writel(val,__mem_isa(addr))
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c)&t;&t;_memset_io(__mem_isa(a),(b),(c))
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c)&t;_memcpy_fromio((a),__mem_isa(b),(c))
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c)&t;&t;_memcpy_toio(__mem_isa((a)),(b),(c))
DECL|macro|isa_eth_io_copy_and_sum
mdefine_line|#define isa_eth_io_copy_and_sum(a,b,c,d) &bslash;&n;&t;&t;&t;&t;eth_copy_and_sum((a),__mem_isa(b),(c),(d))
r_static
r_inline
r_int
DECL|function|isa_check_signature
id|isa_check_signature
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
r_do
(brace
r_if
c_cond
(paren
id|isa_readb
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
r_return
id|retval
suffix:semicolon
)brace
macro_line|#else&t;/* __mem_isa */
DECL|macro|isa_readb
mdefine_line|#define isa_readb(addr)&t;&t;&t;(__readwrite_bug(&quot;isa_readb&quot;),0)
DECL|macro|isa_readw
mdefine_line|#define isa_readw(addr)&t;&t;&t;(__readwrite_bug(&quot;isa_readw&quot;),0)
DECL|macro|isa_readl
mdefine_line|#define isa_readl(addr)&t;&t;&t;(__readwrite_bug(&quot;isa_readl&quot;),0)
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(val,addr)&t;&t;__readwrite_bug(&quot;isa_writeb&quot;)
DECL|macro|isa_writew
mdefine_line|#define isa_writew(val,addr)&t;&t;__readwrite_bug(&quot;isa_writew&quot;)
DECL|macro|isa_writel
mdefine_line|#define isa_writel(val,addr)&t;&t;__readwrite_bug(&quot;isa_writel&quot;)
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c)&t;&t;__readwrite_bug(&quot;isa_memset_io&quot;)
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c)&t;__readwrite_bug(&quot;isa_memcpy_fromio&quot;)
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c)&t;&t;__readwrite_bug(&quot;isa_memcpy_toio&quot;)
DECL|macro|isa_eth_io_copy_and_sum
mdefine_line|#define isa_eth_io_copy_and_sum(a,b,c,d) &bslash;&n;&t;&t;&t;&t;__readwrite_bug(&quot;isa_eth_io_copy_and_sum&quot;)
DECL|macro|isa_check_signature
mdefine_line|#define isa_check_signature(io,sig,len)&t;(0)
macro_line|#endif&t;/* __mem_isa */
multiline_comment|/*&n; * ioremap and friends.&n; *&n; * ioremap takes a PCI memory address, as specified in&n; * linux/Documentation/IO-mapping.txt.&n; */
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
macro_line|#ifndef __arch_ioremap
DECL|macro|ioremap
mdefine_line|#define ioremap(cookie,size)&t;&t;__ioremap(cookie,size,0,1)
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(cookie,size)&t;__ioremap(cookie,size,0,1)
DECL|macro|iounmap
mdefine_line|#define iounmap(cookie)&t;&t;&t;__iounmap(cookie)
macro_line|#else
DECL|macro|ioremap
mdefine_line|#define ioremap(cookie,size)&t;&t;__arch_ioremap((cookie),(size),0,1)
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(cookie,size)&t;__arch_ioremap((cookie),(size),0,1)
DECL|macro|iounmap
mdefine_line|#define iounmap(cookie)&t;&t;&t;__arch_iounmap(cookie)
macro_line|#endif
multiline_comment|/*&n; * DMA-consistent mapping functions.  These allocate/free a region of&n; * uncached, unwrite-buffered mapped memory space for use with DMA&n; * devices.  This is the &quot;generic&quot; version.  The PCI specific version&n; * is in pci.h&n; */
r_extern
r_void
op_star
id|consistent_alloc
c_func
(paren
r_int
id|gfp
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|handle
)paren
suffix:semicolon
r_extern
r_void
id|consistent_free
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
id|dma_addr_t
id|handle
)paren
suffix:semicolon
r_extern
r_void
id|consistent_sync
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|rw
)paren
suffix:semicolon
multiline_comment|/*&n; * Change &quot;struct page&quot; to physical address.&n; */
macro_line|#ifdef CONFIG_DISCONTIG
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;&t;&t;&t;&t;  &bslash;&n;&t;((((page) - page_zone(page)-&gt;zone_mem_map) &lt;&lt; PAGE_SHIFT) &bslash;&n;&t;&t;  + page_zone(page)-&gt;zone_start_paddr)
macro_line|#else
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;&t;&t;&t;&t;  &bslash;&n;&t;(PHYS_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
macro_line|#endif
multiline_comment|/*&n; * We should really eliminate virt_to_bus() here - it&squot;s depreciated.&n; */
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus(page)&t;&t;&t;&t;&t;  &bslash;&n;&t;(virt_to_bus(page_address(page)))
multiline_comment|/*&n; * can the hardware map this into one segment or not, given no other&n; * constraints.&n; */
DECL|macro|BIOVEC_MERGEABLE
mdefine_line|#define BIOVEC_MERGEABLE(vec1, vec2)&t;&bslash;&n;&t;((bvec_to_phys((vec1)) + (vec1)-&gt;bv_len) == bvec_to_phys((vec2)))
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __ASM_ARM_IO_H */
eof
