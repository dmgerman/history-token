macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * This file contains the definitions for the x86 IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated&n; * to (a) handle it all in a way that makes gcc able to optimize it&n; * as well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; */
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe about using 0x80 (should be safe, though)&n; *&n; *&t;&t;Linus&n; */
multiline_comment|/*&n;  *  Bit simplified and optimized by Jan Hubicka&n;  *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999.&n;  *&n;  *  isa_memset_io, isa_memcpy_fromio, isa_memcpy_toio added,&n;  *  isa_read[wl] and isa_write[wl] fixed&n;  *  - Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;  */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
DECL|macro|XQUAD_PORTIO_BASE
mdefine_line|#define XQUAD_PORTIO_BASE 0xfe400000
DECL|macro|XQUAD_PORTIO_QUAD
mdefine_line|#define XQUAD_PORTIO_QUAD 0x40000  /* 256k per quad. */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm-generic/iomap.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
multiline_comment|/**&n; *&t;virt_to_phys&t;-&t;map virtual addresses to physical&n; *&t;@address: address to remap&n; *&n; *&t;The returned physical address is the physical (CPU) mapping for&n; *&t;the memory address given. It is only valid to use this function on&n; *&t;addresses directly mapped or allocated via kmalloc. &n; *&n; *&t;This function does not give bus mappings for DMA transfers. In&n; *&t;almost all conceivable cases a device driver should not be using&n; *&t;this function&n; */
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
id|__va
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Change &quot;struct page&quot; to physical address.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)    ((dma_addr_t)page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
r_extern
r_void
id|__iomem
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|offset
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
multiline_comment|/**&n; * ioremap     -   map bus memory into CPU space&n; * @offset:    bus address of the memory&n; * @size:      size of the resource to map&n; *&n; * ioremap performs a platform specific sequence of operations to&n; * make bus memory CPU accessible via the readb/readw/readl/writeb/&n; * writew/writel functions and the other mmio helpers. The returned&n; * address is not guaranteed to be usable directly as a virtual&n; * address. &n; */
DECL|function|ioremap
r_static
r_inline
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
(brace
r_return
id|__ioremap
c_func
(paren
id|offset
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__iomem
op_star
id|ioremap_nocache
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
multiline_comment|/*&n; * bt_ioremap() and bt_iounmap() are for temporary early boot-time&n; * mappings, before the real ioremap() is functional.&n; * A boot-time mapping is currently limited to at most 16 pages.&n; */
r_extern
r_void
op_star
id|bt_ioremap
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
r_extern
r_void
id|bt_iounmap
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
multiline_comment|/*&n; * ISA I/O bus memory addresses are 1:1 with the physical address.&n; */
DECL|macro|isa_virt_to_bus
mdefine_line|#define isa_virt_to_bus virt_to_phys
DECL|macro|isa_page_to_bus
mdefine_line|#define isa_page_to_bus page_to_phys
DECL|macro|isa_bus_to_virt
mdefine_line|#define isa_bus_to_virt phys_to_virt
multiline_comment|/*&n; * However PCI ones are not necessarily 1:1 and therefore these interfaces&n; * are forbidden in portable PCI drivers.&n; *&n; * Allow them on x86 for legacy drivers, though.&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the x86 architecture, we just read/write the&n; * memory location directly.&n; */
DECL|function|readb
r_static
r_inline
r_int
r_char
id|readb
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
DECL|function|readw
r_static
r_inline
r_int
r_int
id|readw
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
DECL|function|readl
r_static
r_inline
r_int
r_int
id|readl
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
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(addr) readb(addr)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(addr) readw(addr)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(addr) readl(addr)
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb readb
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw readw
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl readl
DECL|function|writeb
r_static
r_inline
r_void
id|writeb
c_func
(paren
r_int
r_char
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
r_volatile
r_int
r_char
id|__force
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|writew
r_static
r_inline
r_void
id|writew
c_func
(paren
r_int
r_int
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
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|writel
r_static
r_inline
r_void
id|writel
c_func
(paren
r_int
r_int
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
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb writeb
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew writew
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel writel
DECL|macro|mmiowb
mdefine_line|#define mmiowb()
DECL|function|memset_io
r_static
r_inline
r_void
id|memset_io
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
comma
r_int
r_char
id|val
comma
r_int
id|count
)paren
(brace
id|memset
c_func
(paren
(paren
r_void
id|__force
op_star
)paren
id|addr
comma
id|val
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|memcpy_fromio
r_static
r_inline
r_void
id|memcpy_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_volatile
r_void
id|__iomem
op_star
id|src
comma
r_int
id|count
)paren
(brace
id|__memcpy
c_func
(paren
id|dst
comma
(paren
r_void
id|__force
op_star
)paren
id|src
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|memcpy_toio
r_static
r_inline
r_void
id|memcpy_toio
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
r_int
id|count
)paren
(brace
id|__memcpy
c_func
(paren
(paren
r_void
id|__force
op_star
)paren
id|dst
comma
id|src
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ISA space is &squot;always mapped&squot; on a typical x86 system, no need to&n; * explicitly ioremap() it. The fact that the ISA IO space is mapped&n; * to PAGE_OFFSET is pure coincidence - it does not mean ISA values&n; * are physical addresses. The following constant pointer can be&n; * used as the IO-area pointer (it can be iounmapped as well, so the&n; * analogy with PCI is quite large):&n; */
DECL|macro|__ISA_IO_base
mdefine_line|#define __ISA_IO_base ((char __iomem *)(PAGE_OFFSET))
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
multiline_comment|/*&n; * Again, i386 does not require mem IO specific function.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(a,b,c,d)&t;&t;eth_copy_and_sum((a),(void __force *)(b),(c),(d))
DECL|macro|isa_eth_io_copy_and_sum
mdefine_line|#define isa_eth_io_copy_and_sum(a,b,c,d)&t;eth_copy_and_sum((a),(void __force *)(__ISA_IO_base + (b)),(c),(d))
multiline_comment|/**&n; *&t;check_signature&t;&t;-&t;find BIOS signatures&n; *&t;@io_addr: mmio address to check &n; *&t;@signature:  signature block&n; *&t;@length: length of signature&n; *&n; *&t;Perform a signature comparison with the mmio address io_addr. This&n; *&t;address should have been obtained by ioremap.&n; *&t;Returns 1 on a match.&n; */
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
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
multiline_comment|/*&n; *&t;Cache management&n; *&n; *&t;This needed for two cases&n; *&t;1. Out of order aware processors&n; *&t;2. Accidentally out of order processors (PPro errata #51)&n; */
macro_line|#if defined(CONFIG_X86_OOSTORE) || defined(CONFIG_X86_PPRO_FENCE)
DECL|function|flush_write_buffers
r_static
r_inline
r_void
id|flush_write_buffers
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;lock; addl $0,0(%%esp)&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;flush_write_buffers()
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;flush_write_buffers()
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;flush_write_buffers()
macro_line|#else
multiline_comment|/* Nothing to do */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
DECL|macro|flush_write_buffers
mdefine_line|#define flush_write_buffers()
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#ifdef SLOW_IO_BY_JUMPING
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &quot;jmp 1f; 1: jmp 1f; 1:&quot;
macro_line|#else
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &quot;outb %%al,$0x80;&quot;
macro_line|#endif
DECL|function|slow_down_io
r_static
r_inline
r_void
id|slow_down_io
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
id|__SLOW_DOWN_IO
macro_line|#ifdef REALLY_SLOW_IO
id|__SLOW_DOWN_IO
id|__SLOW_DOWN_IO
id|__SLOW_DOWN_IO
macro_line|#endif
suffix:colon
suffix:colon
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_NUMAQ
r_extern
r_void
op_star
id|xquad_portio
suffix:semicolon
multiline_comment|/* Where the IO area was mapped */
DECL|macro|XQUAD_PORT_ADDR
mdefine_line|#define XQUAD_PORT_ADDR(port, quad) (xquad_portio + (XQUAD_PORTIO_QUAD*quad) + port)
DECL|macro|__BUILDIO
mdefine_line|#define __BUILDIO(bwl,bw,type) &bslash;&n;static inline void out##bwl##_quad(unsigned type value, int port, int quad) { &bslash;&n;&t;if (xquad_portio) &bslash;&n;&t;&t;write##bwl(value, XQUAD_PORT_ADDR(port, quad)); &bslash;&n;&t;else &bslash;&n;&t;&t;out##bwl##_local(value, port); &bslash;&n;} &bslash;&n;static inline void out##bwl(unsigned type value, int port) { &bslash;&n;&t;out##bwl##_quad(value, port, 0); &bslash;&n;} &bslash;&n;static inline unsigned type in##bwl##_quad(int port, int quad) { &bslash;&n;&t;if (xquad_portio) &bslash;&n;&t;&t;return read##bwl(XQUAD_PORT_ADDR(port, quad)); &bslash;&n;&t;else &bslash;&n;&t;&t;return in##bwl##_local(port); &bslash;&n;} &bslash;&n;static inline unsigned type in##bwl(int port) { &bslash;&n;&t;return in##bwl##_quad(port, 0); &bslash;&n;}
macro_line|#else
DECL|macro|__BUILDIO
mdefine_line|#define __BUILDIO(bwl,bw,type) &bslash;&n;static inline void out##bwl(unsigned type value, int port) { &bslash;&n;&t;out##bwl##_local(value, port); &bslash;&n;} &bslash;&n;static inline unsigned type in##bwl(int port) { &bslash;&n;&t;return in##bwl##_local(port); &bslash;&n;}
macro_line|#endif
DECL|macro|BUILDIO
mdefine_line|#define BUILDIO(bwl,bw,type) &bslash;&n;static inline void out##bwl##_local(unsigned type value, int port) { &bslash;&n;&t;__asm__ __volatile__(&quot;out&quot; #bwl &quot; %&quot; #bw &quot;0, %w1&quot; : : &quot;a&quot;(value), &quot;Nd&quot;(port)); &bslash;&n;} &bslash;&n;static inline unsigned type in##bwl##_local(int port) { &bslash;&n;&t;unsigned type value; &bslash;&n;&t;__asm__ __volatile__(&quot;in&quot; #bwl &quot; %w1, %&quot; #bw &quot;0&quot; : &quot;=a&quot;(value) : &quot;Nd&quot;(port)); &bslash;&n;&t;return value; &bslash;&n;} &bslash;&n;static inline void out##bwl##_local_p(unsigned type value, int port) { &bslash;&n;&t;out##bwl##_local(value, port); &bslash;&n;&t;slow_down_io(); &bslash;&n;} &bslash;&n;static inline unsigned type in##bwl##_local_p(int port) { &bslash;&n;&t;unsigned type value = in##bwl##_local(port); &bslash;&n;&t;slow_down_io(); &bslash;&n;&t;return value; &bslash;&n;} &bslash;&n;__BUILDIO(bwl,bw,type) &bslash;&n;static inline void out##bwl##_p(unsigned type value, int port) { &bslash;&n;&t;out##bwl(value, port); &bslash;&n;&t;slow_down_io(); &bslash;&n;} &bslash;&n;static inline unsigned type in##bwl##_p(int port) { &bslash;&n;&t;unsigned type value = in##bwl(port); &bslash;&n;&t;slow_down_io(); &bslash;&n;&t;return value; &bslash;&n;} &bslash;&n;static inline void outs##bwl(int port, const void *addr, unsigned long count) { &bslash;&n;&t;__asm__ __volatile__(&quot;rep; outs&quot; #bwl : &quot;+S&quot;(addr), &quot;+c&quot;(count) : &quot;d&quot;(port)); &bslash;&n;} &bslash;&n;static inline void ins##bwl(int port, void *addr, unsigned long count) { &bslash;&n;&t;__asm__ __volatile__(&quot;rep; ins&quot; #bwl : &quot;+D&quot;(addr), &quot;+c&quot;(count) : &quot;d&quot;(port)); &bslash;&n;}
id|BUILDIO
c_func
(paren
id|b
comma
id|b
comma
r_char
)paren
id|BUILDIO
c_func
(paren
id|w
comma
id|w
comma
r_int
)paren
id|BUILDIO
c_func
(paren
id|l
comma
comma
r_int
)paren
macro_line|#endif
eof
