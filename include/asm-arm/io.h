multiline_comment|/*&n; *  linux/include/asm-arm/io.h&n; *&n; *  Copyright (C) 1996-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *  16-Sep-1996&t;RMK&t;Inlined the inx/outx functions &amp; optimised for both&n; *&t;&t;&t;constant addresses and variable addresses.&n; *  04-Dec-1997&t;RMK&t;Moved a lot of this stuff to the new architecture&n; *&t;&t;&t;specific IO header files.&n; *  27-Mar-1999&t;PJB&t;Second parameter of memcpy_toio is const..&n; *  04-Apr-1999&t;PJB&t;Added check_signature.&n; *  12-Dec-1999&t;RMK&t;More cleanups&n; *  18-Jun-2000 RMK&t;Removed virt_to_* and friends definitions&n; */
macro_line|#ifndef __ASM_ARM_IO_H
DECL|macro|__ASM_ARM_IO_H
mdefine_line|#define __ASM_ARM_IO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
multiline_comment|/*&n; * Generic virtual read/write.  Note that we don&squot;t support half-word&n; * read/writes.  We define __arch_*[bl] here, and leave __arch_*w&n; * to the architecture specific code.&n; */
DECL|macro|__arch_getb
mdefine_line|#define __arch_getb(a)&t;&t;&t;(*(volatile unsigned char *)(a))
DECL|macro|__arch_getl
mdefine_line|#define __arch_getl(a)&t;&t;&t;(*(volatile unsigned int  *)(a))
DECL|macro|__arch_putb
mdefine_line|#define __arch_putb(v,a)&t;&t;(*(volatile unsigned char *)(a) = (v))
DECL|macro|__arch_putl
mdefine_line|#define __arch_putl(v,a)&t;&t;(*(volatile unsigned int  *)(a) = (v))
r_extern
r_void
id|__raw_writesb
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
id|__raw_writesw
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
id|__raw_writesl
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
mdefine_line|#define __raw_writeb(v,a)&t;&t;__arch_putb(v,a)
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)&t;&t;__arch_putw(v,a)
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;&t;__arch_putl(v,a)
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)&t;&t;&t;__arch_getb(a)
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)&t;&t;&t;__arch_getw(a)
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;&t;__arch_getl(a)
multiline_comment|/*&n; * The compiler seems to be incapable of optimising constants&n; * properly.  Spell it out to the compiler in some cases.&n; * These are only valid for small values of &quot;off&quot; (&lt; 1&lt;&lt;12)&n; */
DECL|macro|__raw_base_writeb
mdefine_line|#define __raw_base_writeb(val,base,off)&t;__arch_base_putb(val,base,off)
DECL|macro|__raw_base_writew
mdefine_line|#define __raw_base_writew(val,base,off)&t;__arch_base_putw(val,base,off)
DECL|macro|__raw_base_writel
mdefine_line|#define __raw_base_writel(val,base,off)&t;__arch_base_putl(val,base,off)
DECL|macro|__raw_base_readb
mdefine_line|#define __raw_base_readb(base,off)&t;__arch_base_getb(base,off)
DECL|macro|__raw_base_readw
mdefine_line|#define __raw_base_readw(base,off)&t;__arch_base_getw(base,off)
DECL|macro|__raw_base_readl
mdefine_line|#define __raw_base_readl(base,off)&t;__arch_base_getl(base,off)
multiline_comment|/*&n; * Now, pick up the machine-defined IO definitions&n; */
macro_line|#include &lt;asm/arch/io.h&gt;
multiline_comment|/*&n; * IO definitions.  We define {out,in,outs,ins}[bwl] if __io is&n; * defined by the machine.  Otherwise, these definitions are left&n; * for the machine specific header files to pick up.&n; */
macro_line|#ifdef __io
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;&t;&t;__raw_writeb(v,__io(p))
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;&t;&t;__raw_writew(v,__io(p))
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;&t;&t;__raw_writel(v,__io(p))
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;&t;&t;__raw_readb(__io(p))
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&t;&t;__raw_readw(__io(p))
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&t;&t;__raw_readl(__io(p))
DECL|macro|outsb
mdefine_line|#define outsb(p,d,l)&t;&t;&t;__raw_writesb(__io(p),d,l)
DECL|macro|outsw
mdefine_line|#define outsw(p,d,l)&t;&t;&t;__raw_writesw(__io(p),d,l)
DECL|macro|outsl
mdefine_line|#define outsl(p,d,l)&t;&t;&t;__raw_writesl(__io(p),d,l)
DECL|macro|insb
mdefine_line|#define insb(p,d,l)&t;&t;&t;__raw_readsb(__io(p),d,l)
DECL|macro|insw
mdefine_line|#define insw(p,d,l)&t;&t;&t;__raw_readsw(__io(p),d,l)
DECL|macro|insl
mdefine_line|#define insl(p,d,l)&t;&t;&t;__raw_readsl(__io(p),d,l)
macro_line|#endif
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port)&t;&t;outb((val),(port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port)&t;&t;outw((val),(port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val,port)&t;&t;outl((val),(port))
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;&t;&t;inb((port))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)&t;&t;&t;inw((port))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)&t;&t;&t;inl((port))
DECL|macro|outsb_p
mdefine_line|#define outsb_p(port,from,len)&t;&t;outsb(port,from,len)
DECL|macro|outsw_p
mdefine_line|#define outsw_p(port,from,len)&t;&t;outsw(port,from,len)
DECL|macro|outsl_p
mdefine_line|#define outsl_p(port,from,len)&t;&t;outsl(port,from,len)
DECL|macro|insb_p
mdefine_line|#define insb_p(port,to,len)&t;&t;insb(port,to,len)
DECL|macro|insw_p
mdefine_line|#define insw_p(port,to,len)&t;&t;insw(port,to,len)
DECL|macro|insl_p
mdefine_line|#define insl_p(port,to,len)&t;&t;insl(port,to,len)
multiline_comment|/*&n; * ioremap and friends.&n; *&n; * ioremap takes a PCI memory address, as specified in&n; * linux/Documentation/IO-mapping.txt.  If you want a&n; * physical address, use __ioremap instead.&n; */
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|offset
comma
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
id|__iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; * Generic ioremap support.&n; *&n; * Define:&n; *  iomem_valid_addr(off,size)&n; *  iomem_to_phys(off)&n; */
macro_line|#ifdef iomem_valid_addr
DECL|macro|__arch_ioremap
mdefine_line|#define __arch_ioremap(off,sz,nocache)&t;&t;&t;&t;&bslash;&n; ({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _off = (off), _size = (sz);&t;&t;&bslash;&n;&t;void *_ret = (void *)0;&t;&t;&t;&t;&t;&bslash;&n;&t;if (iomem_valid_addr(_off, _size))&t;&t;&t;&bslash;&n;&t;&t;_ret = __ioremap(iomem_to_phys(_off),_size,0);&t;&bslash;&n;&t;_ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; })
DECL|macro|__arch_iounmap
mdefine_line|#define __arch_iounmap __iounmap
macro_line|#endif
DECL|macro|ioremap
mdefine_line|#define ioremap(off,sz)&t;&t;&t;__arch_ioremap((off),(sz),0)
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(off,sz)&t;&t;__arch_ioremap((off),(sz),1)
DECL|macro|iounmap
mdefine_line|#define iounmap(_addr)&t;&t;&t;__arch_iounmap(_addr)
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
multiline_comment|/*&n; * If this architecture has PCI memory IO, then define the read/write&n; * macros.  These should only be used with the cookie passed from&n; * ioremap.&n; */
macro_line|#ifdef __mem_pci
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;&t;__raw_readb(__mem_pci(addr))
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;&t;__raw_readw(__mem_pci(addr))
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;&t;__raw_readl(__mem_pci(addr))
DECL|macro|writeb
mdefine_line|#define writeb(val,addr)&t;&t;__raw_writeb(val,__mem_pci(addr))
DECL|macro|writew
mdefine_line|#define writew(val,addr)&t;&t;__raw_writew(val,__mem_pci(addr))
DECL|macro|writel
mdefine_line|#define writel(val,addr)&t;&t;__raw_writel(val,__mem_pci(addr))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;&t;_memset_io(__mem_pci(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;&t;_memcpy_fromio((a),__mem_pci(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;&t;_memcpy_toio(__mem_pci(a),(b),(c))
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(a,b,c,d) &bslash;&n;&t;&t;&t;&t;eth_copy_and_sum((a),__mem_pci(b),(c),(d))
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
mdefine_line|#define readb(addr)&t;&t;&t;(__readwrite_bug(&quot;readb&quot;),0)
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;&t;(__readwrite_bug(&quot;readw&quot;),0)
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;&t;(__readwrite_bug(&quot;readl&quot;),0)
DECL|macro|writeb
mdefine_line|#define writeb(v,addr)&t;&t;&t;__readwrite_bug(&quot;writeb&quot;)
DECL|macro|writew
mdefine_line|#define writew(v,addr)&t;&t;&t;__readwrite_bug(&quot;writew&quot;)
DECL|macro|writel
mdefine_line|#define writel(v,addr)&t;&t;&t;__readwrite_bug(&quot;writel&quot;)
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(a,b,c,d)&t;__readwrite_bug(&quot;eth_io_copy_and_sum&quot;)
DECL|macro|check_signature
mdefine_line|#define check_signature(io,sig,len)&t;(0)
macro_line|#endif&t;/* __mem_pci */
multiline_comment|/*&n; * remap a physical address `phys&squot; of size `size&squot; with page protection `prot&squot;&n; * into virtual address `from&squot;&n; */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(from,phys,size,prot) &bslash;&n;&t;&t;remap_page_range(from,phys,size,prot)
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
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __ASM_ARM_IO_H */
eof
