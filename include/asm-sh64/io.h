macro_line|#ifndef __ASM_SH64_IO_H
DECL|macro|__ASM_SH64_IO_H
mdefine_line|#define __ASM_SH64_IO_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/io.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; *&n; */
multiline_comment|/*&n; * Convention:&n; *    read{b,w,l}/write{b,w,l} are for PCI,&n; *    while in{b,w,l}/out{b,w,l} are for ISA&n; * These may (will) be platform specific function.&n; *&n; * In addition, we have&n; *   ctrl_in{b,w,l}/ctrl_out{b,w,l} for SuperH specific I/O.&n; * which are processor specific. Address should be the result of&n; * onchip_remap();&n; */
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus page_to_phys
multiline_comment|/*&n; * Nothing overly special here.. instead of doing the same thing&n; * over and over again, we just define a set of sh64_in/out functions&n; * with an implicit size. The traditional read{b,w,l}/write{b,w,l}&n; * mess is wrapped to this, as are the SH-specific ctrl_in/out routines.&n; */
DECL|function|sh64_in8
r_static
r_inline
r_int
r_char
id|sh64_in8
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|sh64_in16
r_static
r_inline
r_int
r_int
id|sh64_in16
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|sh64_in32
r_static
r_inline
r_int
r_int
id|sh64_in32
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|sh64_in64
r_static
r_inline
r_int
r_int
r_int
id|sh64_in64
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
DECL|function|sh64_out8
r_static
r_inline
r_void
id|sh64_out8
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sh64_out16
r_static
r_inline
r_void
id|sh64_out16
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sh64_out32
r_static
r_inline
r_void
id|sh64_out32
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sh64_out64
r_static
r_inline
r_void
id|sh64_out64
c_func
(paren
r_int
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
r_int
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|readb
mdefine_line|#define readb(addr)&t;&t;sh64_in8(addr)
DECL|macro|readw
mdefine_line|#define readw(addr)&t;&t;sh64_in16(addr)
DECL|macro|readl
mdefine_line|#define readl(addr)&t;&t;sh64_in32(addr)
DECL|macro|writeb
mdefine_line|#define writeb(b, addr)&t;&t;sh64_out8(b, addr)
DECL|macro|writew
mdefine_line|#define writew(b, addr)&t;&t;sh64_out16(b, addr)
DECL|macro|writel
mdefine_line|#define writel(b, addr)&t;&t;sh64_out32(b, addr)
DECL|macro|ctrl_inb
mdefine_line|#define ctrl_inb(addr)&t;&t;sh64_in8(addr)
DECL|macro|ctrl_inw
mdefine_line|#define ctrl_inw(addr)&t;&t;sh64_in16(addr)
DECL|macro|ctrl_inl
mdefine_line|#define ctrl_inl(addr)&t;&t;sh64_in32(addr)
DECL|macro|ctrl_outb
mdefine_line|#define ctrl_outb(b, addr)&t;sh64_out8(b, addr)
DECL|macro|ctrl_outw
mdefine_line|#define ctrl_outw(b, addr)&t;sh64_out16(b, addr)
DECL|macro|ctrl_outl
mdefine_line|#define ctrl_outl(b, addr)&t;sh64_out32(b, addr)
r_int
r_int
id|inb
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_int
r_int
id|inw
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_int
r_int
id|inl
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_void
id|outb
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_void
id|outw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_void
id|outl
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_SH_CAYMAN
r_extern
r_int
r_int
id|smsc_superio_virt
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
r_int
id|pciio_virt
suffix:semicolon
macro_line|#endif
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are trivial on the 1:1 Linux/SuperH mapping&n; */
DECL|function|virt_to_phys
r_extern
id|__inline__
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
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_extern
id|__inline__
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
id|__va
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|phys_addr
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
DECL|function|ioremap
r_extern
id|__inline__
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|phys_addr
comma
id|size
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ioremap_nocache
r_extern
id|__inline__
r_void
op_star
id|ioremap_nocache
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|phys_addr
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|onchip_remap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|onchip_unmap
c_func
(paren
r_int
r_int
id|vaddr
)paren
suffix:semicolon
DECL|function|check_signature
r_static
id|__inline__
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
multiline_comment|/*&n; * The caches on some architectures aren&squot;t dma-coherent and have need to&n; * handle this in software.  There are three types of operations that&n; * can be applied to dma buffers.&n; *&n; *  - dma_cache_wback_inv(start, size) makes caches and RAM coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_inv(start, size) invalidates the affected parts of the&n; *    caches.  Dirty lines of the caches may be written back or simply&n; *    be discarded.  This operation is necessary before dma operations&n; *    to the memory.&n; *  - dma_cache_wback(start, size) writes back any dirty lines but does&n; *    not invalidate the cache.  This can be used before DMA reads from&n; *    memory,&n; */
DECL|function|dma_cache_wback_inv
r_static
id|__inline__
r_void
id|dma_cache_wback_inv
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|s
op_assign
id|start
op_amp
id|L1_CACHE_ALIGN_MASK
suffix:semicolon
r_int
r_int
id|e
op_assign
(paren
id|start
op_plus
id|size
)paren
op_amp
id|L1_CACHE_ALIGN_MASK
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|s
op_le
id|e
suffix:semicolon
id|s
op_add_assign
id|L1_CACHE_BYTES
)paren
id|asm
r_volatile
(paren
l_string|&quot;ocbp&t;%0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
)paren
suffix:semicolon
)brace
DECL|function|dma_cache_inv
r_static
id|__inline__
r_void
id|dma_cache_inv
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
singleline_comment|// Note that caller has to be careful with overzealous
singleline_comment|// invalidation should there be partial cache lines at the extremities
singleline_comment|// of the specified range
r_int
r_int
id|s
op_assign
id|start
op_amp
id|L1_CACHE_ALIGN_MASK
suffix:semicolon
r_int
r_int
id|e
op_assign
(paren
id|start
op_plus
id|size
)paren
op_amp
id|L1_CACHE_ALIGN_MASK
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|s
op_le
id|e
suffix:semicolon
id|s
op_add_assign
id|L1_CACHE_BYTES
)paren
id|asm
r_volatile
(paren
l_string|&quot;ocbi&t;%0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
)paren
suffix:semicolon
)brace
DECL|function|dma_cache_wback
r_static
id|__inline__
r_void
id|dma_cache_wback
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|s
op_assign
id|start
op_amp
id|L1_CACHE_ALIGN_MASK
suffix:semicolon
r_int
r_int
id|e
op_assign
(paren
id|start
op_plus
id|size
)paren
op_amp
id|L1_CACHE_ALIGN_MASK
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|s
op_le
id|e
suffix:semicolon
id|s
op_add_assign
id|L1_CACHE_BYTES
)paren
id|asm
r_volatile
(paren
l_string|&quot;ocbwb&t;%0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|s
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH64_IO_H */
eof
