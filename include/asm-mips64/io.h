multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 Waldorf GmbH&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef CONFIG_DECSTATION
macro_line|#include &lt;asm/dec/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_ATLAS
macro_line|#include &lt;asm/mips-boards/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_MALTA
macro_line|#include &lt;asm/mips-boards/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_SEAD
macro_line|#include &lt;asm/mips-boards/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP22
macro_line|#include &lt;asm/sgi/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP27
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP32
macro_line|#include &lt;asm/ip32/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SIBYTE_SB1xxx_SOC
macro_line|#include &lt;asm/sibyte/io.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SNI_RM200_PCI
macro_line|#include &lt;asm/sni.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP27
r_extern
r_int
r_int
id|bus_to_baddr
(braket
l_int|256
)braket
suffix:semicolon
DECL|macro|bus_to_baddr
mdefine_line|#define bus_to_baddr(bus, addr)&t;(bus_to_baddr[(bus)-&gt;number] + (addr))
DECL|macro|baddr_to_bus
mdefine_line|#define baddr_to_bus(bus, addr)&t;((addr) - bus_to_baddr[(bus)-&gt;number])
macro_line|#else
DECL|macro|bus_to_baddr
mdefine_line|#define bus_to_baddr(bus, addr)&t;(addr)
DECL|macro|baddr_to_bus
mdefine_line|#define baddr_to_bus(bus, addr)&t;(addr)
macro_line|#endif
multiline_comment|/*&n; * Slowdown I/O port space accesses for antique hardware.&n; */
DECL|macro|CONF_SLOWDOWN_IO
macro_line|#undef CONF_SLOWDOWN_IO
multiline_comment|/*&n; * Sane hardware offers swapping of I/O space accesses in hardware; less&n; * sane hardware forces software to fiddle with this ...&n; */
macro_line|#if defined(CONFIG_SWAP_IO_SPACE) &amp;&amp; defined(__MIPSEB__)
DECL|macro|__ioswab8
mdefine_line|#define __ioswab8(x) (x)
macro_line|#ifdef CONFIG_SGI_IP22
multiline_comment|/*&n; * IP22 seems braindead enough to swap 16bits values in hardware, but&n; * not 32bits.  Go figure... Can&squot;t tell without documentation.&n; */
DECL|macro|__ioswab16
mdefine_line|#define __ioswab16(x) (x)
macro_line|#else
DECL|macro|__ioswab16
mdefine_line|#define __ioswab16(x) swab16(x)
macro_line|#endif
DECL|macro|__ioswab32
mdefine_line|#define __ioswab32(x) swab32(x)
macro_line|#else
DECL|macro|__ioswab8
mdefine_line|#define __ioswab8(x) (x)
DECL|macro|__ioswab16
mdefine_line|#define __ioswab16(x) (x)
DECL|macro|__ioswab32
mdefine_line|#define __ioswab32(x) (x)
macro_line|#endif
multiline_comment|/*&n; * Change &quot;struct page&quot; to physical address.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;((dma_addr_t)page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * ioremap     -   map bus memory into CPU space&n; * @offset:    bus address of the memory&n; * @size:      size of the resource to map&n; *&n; * ioremap performs a platform specific sequence of operations to&n; * make bus memory CPU accessible via the readb/readw/readl/writeb/&n; * writew/writel functions and the other mmio helpers. The returned&n; * address is not guaranteed to be usable directly as a virtual&n; * address.&n; */
DECL|function|ioremap
r_static
r_inline
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|IO_SPACE_BASE
op_or
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ioremap_nocache     -   map bus memory into CPU space&n; * @offset:    bus address of the memory&n; * @size:      size of the resource to map&n; *&n; * ioremap_nocache performs a platform specific sequence of operations to&n; * make bus memory CPU accessible via the readb/readw/readl/writeb/&n; * writew/writel functions and the other mmio helpers. The returned&n; * address is not guaranteed to be usable directly as a virtual&n; * address.&n; *&n; * This version of ioremap ensures that the memory is marked uncachable&n; * on the CPU as well as honouring existing caching rules from things like&n; * the PCI bus. Note that there are other caches and buffers on many&n; * busses. In paticular driver authors should read up on PCI writes&n; *&n; * It&squot;s useful if some control registers are in such an area and&n; * write combining or read caching is not desirable:&n; */
DECL|function|ioremap_nocache
r_static
r_inline
r_void
op_star
id|ioremap_nocache
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|IO_SPACE_BASE
op_or
id|offset
)paren
suffix:semicolon
)brace
DECL|function|iounmap
r_static
r_inline
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
)brace
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;(*(volatile unsigned char *)(addr))
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;__ioswab16((*(volatile unsigned short *)(addr)))
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;__ioswab32((*(volatile unsigned int *)(addr)))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(addr)&t;(*(volatile unsigned char *)(addr))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(addr)&t;(*(volatile unsigned short *)(addr))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(addr)&t;(*(volatile unsigned int *)(addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) ((*(volatile unsigned char *)(addr)) = (__ioswab8(b)))
DECL|macro|writew
mdefine_line|#define writew(b,addr) ((*(volatile unsigned short *)(addr)) = (__ioswab16(b)))
DECL|macro|writel
mdefine_line|#define writel(b,addr) ((*(volatile unsigned int *)(addr)) = (__ioswab32(b)))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(b,addr)&t;((*(volatile unsigned char *)(addr)) = (b))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(w,addr)&t;((*(volatile unsigned short *)(addr)) = (w))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(l,addr)&t;((*(volatile unsigned int *)(addr)) = (l))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
multiline_comment|/* The ISA versions are supplied by system specific code */
multiline_comment|/*&n; * On MIPS I/O ports are memory mapped, so we access them using normal&n; * load/store instructions. mips_io_port_base is the virtual address to&n; * which all ports are being mapped.  For sake of efficiency some code&n; * assumes that this is an address that can be loaded with a single lui&n; * instruction, so the lower 16 bits must be zero.  Should be true on&n; * on any sane architecture; generic code does not use this assumption.&n; */
r_extern
r_const
r_int
r_int
id|mips_io_port_base
suffix:semicolon
DECL|macro|set_io_port_base
mdefine_line|#define set_io_port_base(base)  &bslash;&n;&t;do { * (unsigned long *) &amp;mips_io_port_base = (base); } while (0)
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;sb&bslash;t$0,0x80(%0)&quot; &bslash;&n;&t;&t;: : &quot;r&quot; (mips_io_port_base));
macro_line|#ifdef CONF_SLOWDOWN_IO
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO { __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; }
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#endif
macro_line|#else
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO
macro_line|#endif
multiline_comment|/*&n; *     virt_to_phys    -       map virtual addresses to physical&n; *     @address: address to remap&n; *&n; *     The returned physical address is the physical (CPU) mapping for&n; *     the memory address given. It is only valid to use this function on&n; *     addresses directly mapped or allocated via kmalloc.&n; *&n; *     This function does not give bus mappings for DMA transfers. In&n; *     almost all conceivable cases a device driver should not be using&n; *     this function&n; */
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
(paren
r_int
r_int
)paren
id|address
op_minus
id|PAGE_OFFSET
suffix:semicolon
)brace
multiline_comment|/*&n; *     phys_to_virt    -       map physical address to virtual&n; *     @address: address to remap&n; *&n; *     The returned virtual address is a current CPU mapping for&n; *     the memory address given. It is only valid to use this function on&n; *     addresses that have a kernel mapping&n; *&n; *     This function does not handle bus mappings for DMA transfers. In&n; *     almost all conceivable cases a device driver should not be using&n; *     this function&n; */
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
(paren
id|address
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ISA I/O bus memory addresses are 1:1 with the physical address.&n; */
DECL|function|isa_virt_to_bus
r_static
r_inline
r_int
r_int
id|isa_virt_to_bus
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|PHYSADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|isa_bus_to_virt
r_static
r_inline
r_void
op_star
id|isa_bus_to_virt
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
id|KSEG0ADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * However PCI ones are not necessarily 1:1 and therefore these interfaces&n; * are forbidden in portable PCI drivers.&n; *&n; * Allow them for x86 for legacy drivers, though.&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
multiline_comment|/* This is too simpleminded for more sophisticated than dumb hardware ...  */
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus page_to_phys
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is mapped&n; * for the processor.  This implies the assumption that there is only&n; * one of these busses.&n; */
r_extern
r_int
r_int
id|isa_slot_offset
suffix:semicolon
multiline_comment|/*&n; * ISA space is &squot;always mapped&squot; on currently supported MIPS systems, no need&n; * to explicitly ioremap() it. The fact that the ISA IO space is mapped&n; * to PAGE_OFFSET is pure coincidence - it does not mean ISA values&n; * are physical addresses. The following constant pointer can be&n; * used as the IO-area pointer (it can be iounmapped as well, so the&n; * analogy with PCI is quite large):&n; */
DECL|macro|__ISA_IO_base
mdefine_line|#define __ISA_IO_base ((char *)(isa_slot_offset))
DECL|macro|isa_readb
mdefine_line|#define isa_readb(a) readb(__ISA_IO_base + (a))
DECL|macro|isa_readw
mdefine_line|#define isa_readw(a) readw(__ISA_IO_base + (a))
DECL|macro|isa_readl
mdefine_line|#define isa_readl(a) readl(__ISA_IO_base + (a))
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(b,a) writeb(b,__ISA_IO_base + (a))
DECL|macro|isa_writew
mdefine_line|#define isa_writew(w,a) writew(w,__ISA_IO_base + (a))
DECL|macro|isa_writel
mdefine_line|#define isa_writel(l,a) writel(l,__ISA_IO_base + (a))
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c)&t;&t;memset_io(__ISA_IO_base + (a),(b),(c))
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c)&t;memcpy_fromio((a),__ISA_IO_base + (b),(c))
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c)&t;&t;memcpy_toio(__ISA_IO_base + (a),(b),(c))
multiline_comment|/*&n; * We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and&n; * just copy it. The net code will then do the checksum later.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused) memcpy_fromio((skb)-&gt;data,(src),(len))
multiline_comment|/**&n; *     check_signature         -       find BIOS signatures&n; *     @io_addr: mmio address to check&n; *     @signature:  signature block&n; *     @length: length of signature&n; *&n; *     Perform a signature comparison with the mmio address io_addr. This&n; *     address should have been obtained by ioremap.&n; *     Returns 1 on a match.&n; */
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
multiline_comment|/*&n; *     isa_check_signature             -       find BIOS signatures&n; *     @io_addr: mmio address to check&n; *     @signature:  signature block&n; *     @length: length of signature&n; *&n; *     Perform a signature comparison with the ISA mmio address io_addr.&n; *     Returns 1 on a match.&n; *&n; *     This function is deprecated. New drivers should use ioremap and&n; *     check_signature.&n; */
DECL|macro|isa_check_signature
mdefine_line|#define isa_check_signature(io, s, l)&t;check_signature(i,s,l)
DECL|macro|outb
mdefine_line|#define outb(val,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u8 *)(mips_io_port_base + (port)) = __ioswab8(val);&t;&bslash;&n;} while(0)
DECL|macro|outw
mdefine_line|#define outw(val,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u16 *)(mips_io_port_base + (port)) = __ioswab16(val);&bslash;&n;} while(0)
DECL|macro|outl
mdefine_line|#define outl(val,port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u32 *)(mips_io_port_base + (port)) = __ioswab32(val);&bslash;&n;} while(0)
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u8 *)(mips_io_port_base + (port)) = __ioswab8(val);&t;&bslash;&n;&t;SLOW_DOWN_IO;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|outw_p
mdefine_line|#define outw_p(val,port)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u16 *)(mips_io_port_base + (port)) = __ioswab16(val);&bslash;&n;&t;SLOW_DOWN_IO;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|outl_p
mdefine_line|#define outl_p(val,port)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile u32 *)(mips_io_port_base + (port)) = __ioswab32(val);&bslash;&n;&t;SLOW_DOWN_IO;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|function|inb
r_static
r_inline
r_int
r_char
id|inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|__ioswab8
c_func
(paren
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|mips_io_port_base
op_plus
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|inw
r_static
r_inline
r_int
r_int
id|inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|__ioswab16
c_func
(paren
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|mips_io_port_base
op_plus
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|inl
r_static
r_inline
r_int
r_int
id|inl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|__ioswab32
c_func
(paren
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|mips_io_port_base
op_plus
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|inb_p
r_static
r_inline
r_int
r_char
id|inb_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
id|u8
id|__val
suffix:semicolon
id|__val
op_assign
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|mips_io_port_base
op_plus
id|port
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
r_return
id|__ioswab8
c_func
(paren
id|__val
)paren
suffix:semicolon
)brace
DECL|function|inw_p
r_static
r_inline
r_int
r_int
id|inw_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
id|u16
id|__val
suffix:semicolon
id|__val
op_assign
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|mips_io_port_base
op_plus
id|port
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
r_return
id|__ioswab16
c_func
(paren
id|__val
)paren
suffix:semicolon
)brace
DECL|function|inl_p
r_static
r_inline
r_int
r_int
id|inl_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
id|u32
id|__val
suffix:semicolon
id|__val
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|mips_io_port_base
op_plus
id|port
)paren
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
r_return
id|__ioswab32
c_func
(paren
id|__val
)paren
suffix:semicolon
)brace
DECL|function|outsb
r_static
r_inline
r_void
id|outsb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
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
(brace
id|outb
c_func
(paren
op_star
(paren
id|u8
op_star
)paren
id|addr
comma
id|port
)paren
suffix:semicolon
id|addr
op_increment
suffix:semicolon
)brace
)brace
DECL|function|insb
r_static
r_inline
r_void
id|insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
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
(brace
op_star
(paren
id|u8
op_star
)paren
id|addr
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr
op_increment
suffix:semicolon
)brace
)brace
DECL|function|outsw
r_static
r_inline
r_void
id|outsw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
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
(brace
id|outw
c_func
(paren
op_star
(paren
id|u16
op_star
)paren
id|addr
comma
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
DECL|function|insw
r_static
r_inline
r_void
id|insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
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
(brace
op_star
(paren
id|u16
op_star
)paren
id|addr
op_assign
id|inw
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
DECL|function|outsl
r_static
r_inline
r_void
id|outsl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
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
(brace
id|outl
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|addr
comma
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
DECL|function|insl
r_static
r_inline
r_void
id|insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
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
(brace
op_star
(paren
id|u32
op_star
)paren
id|addr
op_assign
id|inl
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The caches on some architectures aren&squot;t dma-coherent and have need to&n; * handle this in software.  There are three types of operations that&n; * can be applied to dma buffers.&n; *&n; *  - dma_cache_wback_inv(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_wback(start, size) makes caches and coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_inv(start, size) invalidates the affected parts of the&n; *    caches.  Dirty lines of the caches may be written back or simply&n; *    be discarded.  This operation is necessary before dma operations&n; *    to the memory.&n; */
macro_line|#ifdef CONFIG_NONCOHERENT_IO
r_extern
r_void
(paren
op_star
id|_dma_cache_wback_inv
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_dma_cache_wback
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_dma_cache_inv
)paren
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(start,size)&t;_dma_cache_wback_inv(start,size)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(start,size)&t;_dma_cache_wback(start,size)
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(start,size)&t;_dma_cache_inv(start,size)
macro_line|#else /* Sane hardware */
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(start,size)&t;&bslash;&n;&t;do { (void) (start); (void) (size); } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(start,size)&t;&bslash;&n;&t;do { (void) (start); (void) (size); } while (0)
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(start,size)&t;&bslash;&n;&t;do { (void) (start); (void) (size); } while (0)
macro_line|#endif /* CONFIG_NONCOHERENT_IO */
macro_line|#endif /* _ASM_IO_H */
eof
