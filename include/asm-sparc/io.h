multiline_comment|/*&n; * $Id: io.h,v 1.30 2001/12/21 01:23:21 davem Exp $&n; */
macro_line|#ifndef __SPARC_IO_H
DECL|macro|__SPARC_IO_H
mdefine_line|#define __SPARC_IO_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;  /* struct resource */
macro_line|#include &lt;asm/page.h&gt;      /* IO address mapping routines need this */
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(((page) - mem_map) &lt;&lt; PAGE_SHIFT)
DECL|function|flip_dword
r_static
r_inline
id|u32
id|flip_dword
(paren
id|u32
id|l
)paren
(brace
r_return
(paren
(paren
id|l
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
(paren
id|l
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
(paren
id|l
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|l
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|flip_word
r_static
r_inline
id|u16
id|flip_word
(paren
id|u16
id|w
)paren
(brace
r_return
(paren
(paren
id|w
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|w
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|macro|mmiowb
mdefine_line|#define mmiowb()
multiline_comment|/*&n; * Memory mapped I/O to PCI&n; */
DECL|function|__raw_readb
r_static
r_inline
id|u8
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
id|__force
r_volatile
id|u8
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__raw_readw
r_static
r_inline
id|u16
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
id|__force
r_volatile
id|u16
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__raw_readl
r_static
r_inline
id|u32
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
id|__force
r_volatile
id|u32
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
id|u8
id|b
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
id|__force
r_volatile
id|u8
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|__raw_writew
r_static
r_inline
r_void
id|__raw_writew
c_func
(paren
id|u16
id|w
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
id|__force
r_volatile
id|u16
op_star
)paren
id|addr
op_assign
id|w
suffix:semicolon
)brace
DECL|function|__raw_writel
r_static
r_inline
r_void
id|__raw_writel
c_func
(paren
id|u32
id|l
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
id|__force
r_volatile
id|u32
op_star
)paren
id|addr
op_assign
id|l
suffix:semicolon
)brace
DECL|function|__readb
r_static
r_inline
id|u8
id|__readb
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
id|__force
r_volatile
id|u8
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|__readw
r_static
r_inline
id|u16
id|__readw
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
id|flip_word
c_func
(paren
op_star
(paren
id|__force
r_volatile
id|u16
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__readl
r_static
r_inline
id|u32
id|__readl
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
id|flip_dword
c_func
(paren
op_star
(paren
id|__force
r_volatile
id|u32
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__writeb
r_static
r_inline
r_void
id|__writeb
c_func
(paren
id|u8
id|b
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
id|__force
r_volatile
id|u8
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|__writew
r_static
r_inline
r_void
id|__writew
c_func
(paren
id|u16
id|w
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
id|__force
r_volatile
id|u16
op_star
)paren
id|addr
op_assign
id|flip_word
c_func
(paren
id|w
)paren
suffix:semicolon
)brace
DECL|function|__writel
r_static
r_inline
r_void
id|__writel
c_func
(paren
id|u32
id|l
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
id|__force
r_volatile
id|u32
op_star
)paren
id|addr
op_assign
id|flip_dword
c_func
(paren
id|l
)paren
suffix:semicolon
)brace
DECL|macro|readb
mdefine_line|#define readb(__addr)&t;&t;__readb(__addr)
DECL|macro|readw
mdefine_line|#define readw(__addr)&t;&t;__readw(__addr)
DECL|macro|readl
mdefine_line|#define readl(__addr)&t;&t;__readl(__addr)
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(__addr)&t;readb(__addr)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(__addr)&t;readw(__addr)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(__addr)&t;readl(__addr)
DECL|macro|writeb
mdefine_line|#define writeb(__b, __addr)&t;__writeb((__b),(__addr))
DECL|macro|writew
mdefine_line|#define writew(__w, __addr)&t;__writew((__w),(__addr))
DECL|macro|writel
mdefine_line|#define writel(__l, __addr)&t;__writel((__l),(__addr))
multiline_comment|/*&n; * I/O space operations&n; *&n; * Arrangement on a Sun is somewhat complicated.&n; *&n; * First of all, we want to use standard Linux drivers&n; * for keyboard, PC serial, etc. These drivers think&n; * they access I/O space and use inb/outb.&n; * On the other hand, EBus bridge accepts PCI *memory*&n; * cycles and converts them into ISA *I/O* cycles.&n; * Ergo, we want inb &amp; outb to generate PCI memory cycles.&n; *&n; * If we want to issue PCI *I/O* cycles, we do this&n; * with a low 64K fixed window in PCIC. This window gets&n; * mapped somewhere into virtual kernel space and we&n; * can use inb/outb again.&n; */
DECL|macro|inb_local
mdefine_line|#define inb_local(__addr)&t;__readb((void __iomem *)(unsigned long)(__addr))
DECL|macro|inb
mdefine_line|#define inb(__addr)&t;&t;__readb((void __iomem *)(unsigned long)(__addr))
DECL|macro|inw
mdefine_line|#define inw(__addr)&t;&t;__readw((void __iomem *)(unsigned long)(__addr))
DECL|macro|inl
mdefine_line|#define inl(__addr)&t;&t;__readl((void __iomem *)(unsigned long)(__addr))
DECL|macro|outb_local
mdefine_line|#define outb_local(__b, __addr)&t;__writeb(__b, (void __iomem *)(unsigned long)(__addr))
DECL|macro|outb
mdefine_line|#define outb(__b, __addr)&t;__writeb(__b, (void __iomem *)(unsigned long)(__addr))
DECL|macro|outw
mdefine_line|#define outw(__w, __addr)&t;__writew(__w, (void __iomem *)(unsigned long)(__addr))
DECL|macro|outl
mdefine_line|#define outl(__l, __addr)&t;__writel(__l, (void __iomem *)(unsigned long)(__addr))
DECL|macro|inb_p
mdefine_line|#define inb_p(__addr)&t;&t;inb(__addr)
DECL|macro|outb_p
mdefine_line|#define outb_p(__b, __addr)&t;outb(__b, __addr)
DECL|macro|inw_p
mdefine_line|#define inw_p(__addr)&t;&t;inw(__addr)
DECL|macro|outw_p
mdefine_line|#define outw_p(__w, __addr)&t;outw(__w, __addr)
DECL|macro|inl_p
mdefine_line|#define inl_p(__addr)&t;&t;inl(__addr)
DECL|macro|outl_p
mdefine_line|#define outl_p(__l, __addr)&t;outl(__l, __addr)
r_void
id|outsb
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|cnt
)paren
suffix:semicolon
r_void
id|outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|cnt
)paren
suffix:semicolon
r_void
id|outsl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|cnt
)paren
suffix:semicolon
r_void
id|insb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_void
id|insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_void
id|insl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * SBus accessors.&n; *&n; * SBus has only one, memory mapped, I/O space.&n; * We do not need to flip bytes for SBus of course.&n; */
DECL|function|_sbus_readb
r_static
r_inline
id|u8
id|_sbus_readb
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
id|__force
r_volatile
id|u8
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|_sbus_readw
r_static
r_inline
id|u16
id|_sbus_readw
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
id|__force
r_volatile
id|u16
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|_sbus_readl
r_static
r_inline
id|u32
id|_sbus_readl
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
id|__force
r_volatile
id|u32
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|_sbus_writeb
r_static
r_inline
r_void
id|_sbus_writeb
c_func
(paren
id|u8
id|b
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
id|__force
r_volatile
id|u8
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|_sbus_writew
r_static
r_inline
r_void
id|_sbus_writew
c_func
(paren
id|u16
id|w
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
id|__force
r_volatile
id|u16
op_star
)paren
id|addr
op_assign
id|w
suffix:semicolon
)brace
DECL|function|_sbus_writel
r_static
r_inline
r_void
id|_sbus_writel
c_func
(paren
id|u32
id|l
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
id|__force
r_volatile
id|u32
op_star
)paren
id|addr
op_assign
id|l
suffix:semicolon
)brace
multiline_comment|/*&n; * The only reason for #define&squot;s is to hide casts to unsigned long.&n; */
DECL|macro|sbus_readb
mdefine_line|#define sbus_readb(__addr)&t;&t;_sbus_readb(__addr)
DECL|macro|sbus_readw
mdefine_line|#define sbus_readw(__addr)&t;&t;_sbus_readw(__addr)
DECL|macro|sbus_readl
mdefine_line|#define sbus_readl(__addr)&t;&t;_sbus_readl(__addr)
DECL|macro|sbus_writeb
mdefine_line|#define sbus_writeb(__b, __addr)&t;_sbus_writeb(__b, __addr)
DECL|macro|sbus_writew
mdefine_line|#define sbus_writew(__w, __addr)&t;_sbus_writew(__w, __addr)
DECL|macro|sbus_writel
mdefine_line|#define sbus_writel(__l, __addr)&t;_sbus_writel(__l, __addr)
DECL|function|sbus_memset_io
r_static
r_inline
r_void
id|sbus_memset_io
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|__dst
comma
r_int
id|c
comma
id|__kernel_size_t
id|n
)paren
(brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|sbus_writeb
c_func
(paren
id|c
comma
id|__dst
)paren
suffix:semicolon
id|__dst
op_increment
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|_memset_io
id|_memset_io
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|dst
comma
r_int
id|c
comma
id|__kernel_size_t
id|n
)paren
(brace
r_volatile
r_void
id|__iomem
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|writeb
c_func
(paren
id|c
comma
id|d
)paren
suffix:semicolon
id|d
op_increment
suffix:semicolon
)brace
)brace
DECL|macro|memset_io
mdefine_line|#define memset_io(d,c,sz)&t;_memset_io(d,c,sz)
r_static
r_inline
r_void
DECL|function|_memcpy_fromio
id|_memcpy_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_volatile
r_void
id|__iomem
op_star
id|src
comma
id|__kernel_size_t
id|n
)paren
(brace
r_char
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
r_char
id|tmp
op_assign
id|readb
c_func
(paren
id|src
)paren
suffix:semicolon
op_star
id|d
op_increment
op_assign
id|tmp
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(d,s,sz)&t;_memcpy_fromio(d,s,sz)
r_static
r_inline
r_void
DECL|function|_memcpy_toio
id|_memcpy_toio
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
id|__kernel_size_t
id|n
)paren
(brace
r_const
r_char
op_star
id|s
op_assign
id|src
suffix:semicolon
r_volatile
r_void
id|__iomem
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
r_char
id|tmp
op_assign
op_star
id|s
op_increment
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
comma
id|d
)paren
suffix:semicolon
id|d
op_increment
suffix:semicolon
)brace
)brace
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(d,s,sz)&t;_memcpy_toio(d,s,sz)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Bus number may be embedded in the higher bits of the physical address.&n; * This is why we have no bus number argument to ioremap().&n; */
r_extern
r_void
id|__iomem
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
suffix:semicolon
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(X,Y)&t;ioremap((X),(Y))
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
multiline_comment|/*&n; * Bus number may be in res-&gt;flags... somewhere.&n; */
r_extern
r_void
id|__iomem
op_star
id|sbus_ioremap
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|sbus_iounmap
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|vaddr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n; * At the moment, we do not use CMOS_READ anywhere outside of rtc.c,&n; * so rtc_port is static in it. This should not change unless a new&n; * hardware pops up.&n; */
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)   (rtc_port + (x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD  0
multiline_comment|/* Nothing to do */
multiline_comment|/* P3: Only IDE DMA may need these. XXX Verify that it still does... */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif
macro_line|#endif /* !(__SPARC_IO_H) */
eof
