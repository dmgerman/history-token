macro_line|#ifndef _H8300_IO_H
DECL|macro|_H8300_IO_H
mdefine_line|#define _H8300_IO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/virtconvert.h&gt;
macro_line|#if defined(CONFIG_H83007) || defined(CONFIG_H83068)
macro_line|#include &lt;asm/regs306x.h&gt;
macro_line|#elif defined(CONFIG_H8S2678)
macro_line|#include &lt;asm/regs267x.h&gt;
macro_line|#else
macro_line|#error UNKNOWN CPU TYPE
macro_line|#endif
multiline_comment|/*&n; * These are for ISA/PCI shared memory _only_ and should never be used&n; * on any other type of memory, including Zorro memory. They are meant to&n; * access the bus in the bus byte order which is little-endian!.&n; *&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the m68k architecture, we just read/write the&n; * memory location directly.&n; */
multiline_comment|/* ++roman: The assignments to temp. vars avoid that gcc sometimes generates&n; * two accesses to memory, which may be undesireable for some devices.&n; */
multiline_comment|/*&n; * swap functions are sometimes needed to interface little-endian hardware&n; */
DECL|function|_swapw
r_static
r_inline
r_int
r_int
id|_swapw
c_func
(paren
r_volatile
r_int
r_int
id|v
)paren
(brace
macro_line|#ifndef H8300_IO_NOSWAP
r_int
r_int
id|r
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;xor.b %w0,%x0&bslash;n&bslash;t&quot;
l_string|&quot;xor.b %x0,%w0&bslash;n&bslash;t&quot;
l_string|&quot;xor.b %w0,%x0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|v
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
macro_line|#else
r_return
id|v
suffix:semicolon
macro_line|#endif
)brace
DECL|function|_swapl
r_static
r_inline
r_int
r_int
id|_swapl
c_func
(paren
r_volatile
r_int
r_int
id|v
)paren
(brace
macro_line|#ifndef H8300_IO_NOSWAP
r_int
r_int
id|r
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;xor.b %w0,%x0&bslash;n&bslash;t&quot;
l_string|&quot;xor.b %x0,%w0&bslash;n&bslash;t&quot;
l_string|&quot;xor.b %w0,%x0&bslash;n&bslash;t&quot;
l_string|&quot;xor.w %e0,%f0&bslash;n&bslash;t&quot;
l_string|&quot;xor.w %f0,%e0&bslash;n&bslash;t&quot;
l_string|&quot;xor.w %e0,%f0&bslash;n&bslash;t&quot;
l_string|&quot;xor.b %w0,%x0&bslash;n&bslash;t&quot;
l_string|&quot;xor.b %x0,%w0&bslash;n&bslash;t&quot;
l_string|&quot;xor.b %w0,%x0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|v
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
macro_line|#else
r_return
id|v
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|readb
mdefine_line|#define readb(addr) &bslash;&n;    ({ unsigned char __v = &bslash;&n;     *(volatile unsigned char *)((unsigned long)(addr) &amp; 0x00ffffff); &bslash;&n;     __v; })
DECL|macro|readw
mdefine_line|#define readw(addr) &bslash;&n;    ({ unsigned short __v = &bslash;&n;     *(volatile unsigned short *)((unsigned long)(addr) &amp; 0x00ffffff); &bslash;&n;     __v; })
DECL|macro|readl
mdefine_line|#define readl(addr) &bslash;&n;    ({ unsigned long __v = &bslash;&n;     *(volatile unsigned long *)((unsigned long)(addr) &amp; 0x00ffffff); &bslash;&n;     __v; })
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) (void)((*(volatile unsigned char *) &bslash;&n;                             ((unsigned long)(addr) &amp; 0x00ffffff)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) (void)((*(volatile unsigned short *) &bslash;&n;                             ((unsigned long)(addr) &amp; 0x00ffffff)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) (void)((*(volatile unsigned long *) &bslash;&n;                             ((unsigned long)(addr) &amp; 0x00ffffff)) = (b))
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
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb writeb
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew writew
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel writel
DECL|function|h8300_buswidth
r_static
r_inline
r_int
id|h8300_buswidth
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ABWCR
op_amp
(paren
l_int|1
op_lshift
(paren
(paren
id|addr
op_rshift
l_int|21
)paren
op_amp
l_int|7
)paren
)paren
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|io_outsb
r_static
r_inline
r_void
id|io_outsb
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_char
op_star
id|ap_b
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|ap_w
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_char
op_star
id|bp
op_assign
(paren
r_int
r_char
op_star
)paren
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|h8300_buswidth
c_func
(paren
id|addr
)paren
op_logical_and
(paren
id|addr
op_amp
l_int|1
)paren
)paren
(brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|ap_w
op_assign
op_star
id|bp
op_increment
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|ap_b
op_assign
op_star
id|bp
op_increment
suffix:semicolon
)brace
)brace
DECL|function|io_outsw
r_static
r_inline
r_void
id|io_outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|ap
op_assign
id|_swapw
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
)brace
DECL|function|io_outsl
r_static
r_inline
r_void
id|io_outsl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|ap
op_assign
id|_swapl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
)brace
DECL|function|io_outsw_noswap
r_static
r_inline
r_void
id|io_outsw_noswap
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|ap
op_assign
op_star
id|bp
op_increment
suffix:semicolon
)brace
DECL|function|io_outsl_noswap
r_static
r_inline
r_void
id|io_outsl_noswap
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|ap
op_assign
op_star
id|bp
op_increment
suffix:semicolon
)brace
DECL|function|io_insb
r_static
r_inline
r_void
id|io_insb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_char
op_star
id|ap_b
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|ap_w
suffix:semicolon
r_int
r_char
op_star
id|bp
op_assign
(paren
r_int
r_char
op_star
)paren
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|h8300_buswidth
c_func
(paren
id|addr
)paren
)paren
(brace
id|ap_w
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|addr
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|bp
op_increment
op_assign
op_star
id|ap_w
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
id|ap_b
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|bp
op_increment
op_assign
op_star
id|ap_b
suffix:semicolon
)brace
)brace
DECL|function|io_insw
r_static
r_inline
r_void
id|io_insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|bp
op_increment
op_assign
id|_swapw
c_func
(paren
op_star
id|ap
)paren
suffix:semicolon
)brace
DECL|function|io_insl
r_static
r_inline
r_void
id|io_insl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|bp
op_increment
op_assign
id|_swapl
c_func
(paren
op_star
id|ap
)paren
suffix:semicolon
)brace
DECL|function|io_insw_noswap
r_static
r_inline
r_void
id|io_insw_noswap
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|bp
op_increment
op_assign
op_star
id|ap
suffix:semicolon
)brace
DECL|function|io_insl_noswap
r_static
r_inline
r_void
id|io_insl_noswap
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ap
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|bp
op_assign
(paren
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
op_star
id|bp
op_increment
op_assign
op_star
id|ap
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;make the short names macros so specific devices&n; *&t;can override them as required&n; */
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
DECL|macro|mmiowb
mdefine_line|#define mmiowb()
DECL|macro|inb
mdefine_line|#define inb(addr)    ((h8300_buswidth(addr))?readw((addr) &amp; ~1) &amp; 0xff:readb(addr))
DECL|macro|inw
mdefine_line|#define inw(addr)    _swapw(readw(addr))
DECL|macro|inl
mdefine_line|#define inl(addr)    _swapl(readl(addr))
DECL|macro|outb
mdefine_line|#define outb(x,addr) ((void)((h8300_buswidth(addr) &amp;&amp; &bslash;&n;                      ((addr) &amp; 1))?writew(x,(addr) &amp; ~1):writeb(x,addr)))
DECL|macro|outw
mdefine_line|#define outw(x,addr) ((void) writew(_swapw(x),addr))
DECL|macro|outl
mdefine_line|#define outl(x,addr) ((void) writel(_swapl(x),addr))
DECL|macro|inb_p
mdefine_line|#define inb_p(addr)    inb(addr)
DECL|macro|inw_p
mdefine_line|#define inw_p(addr)    inw(addr)
DECL|macro|inl_p
mdefine_line|#define inl_p(addr)    inl(addr)
DECL|macro|outb_p
mdefine_line|#define outb_p(x,addr) outb(x,addr)
DECL|macro|outw_p
mdefine_line|#define outw_p(x,addr) outw(x,addr)
DECL|macro|outl_p
mdefine_line|#define outl_p(x,addr) outl(x,addr)
DECL|macro|outsb
mdefine_line|#define outsb(a,b,l) io_outsb(a,b,l)
DECL|macro|outsw
mdefine_line|#define outsw(a,b,l) io_outsw(a,b,l)
DECL|macro|outsl
mdefine_line|#define outsl(a,b,l) io_outsl(a,b,l)
DECL|macro|insb
mdefine_line|#define insb(a,b,l) io_insb(a,b,l)
DECL|macro|insw
mdefine_line|#define insw(a,b,l) io_insw(a,b,l)
DECL|macro|insl
mdefine_line|#define insl(a,b,l) io_insl(a,b,l)
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffff
multiline_comment|/* Values for nocacheflag and cmode */
DECL|macro|IOMAP_FULL_CACHING
mdefine_line|#define IOMAP_FULL_CACHING&t;&t;0
DECL|macro|IOMAP_NOCACHE_SER
mdefine_line|#define IOMAP_NOCACHE_SER&t;&t;1
DECL|macro|IOMAP_NOCACHE_NONSER
mdefine_line|#define IOMAP_NOCACHE_NONSER&t;&t;2
DECL|macro|IOMAP_WRITETHROUGH
mdefine_line|#define IOMAP_WRITETHROUGH&t;&t;3
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
comma
r_int
id|cacheflag
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
comma
r_int
r_int
id|size
)paren
suffix:semicolon
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
id|physaddr
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
id|physaddr
comma
id|size
comma
id|IOMAP_NOCACHE_SER
)paren
suffix:semicolon
)brace
DECL|function|ioremap_nocache
r_static
r_inline
r_void
op_star
id|ioremap_nocache
c_func
(paren
r_int
r_int
id|physaddr
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
id|physaddr
comma
id|size
comma
id|IOMAP_NOCACHE_SER
)paren
suffix:semicolon
)brace
DECL|function|ioremap_writethrough
r_static
r_inline
r_void
op_star
id|ioremap_writethrough
c_func
(paren
r_int
r_int
id|physaddr
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
id|physaddr
comma
id|size
comma
id|IOMAP_WRITETHROUGH
)paren
suffix:semicolon
)brace
DECL|function|ioremap_fullcache
r_static
r_inline
r_void
op_star
id|ioremap_fullcache
c_func
(paren
r_int
r_int
id|physaddr
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
id|physaddr
comma
id|size
comma
id|IOMAP_FULL_CACHING
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
multiline_comment|/* Nothing to do */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
multiline_comment|/* H8/300 internal I/O functions */
DECL|function|ctrl_inb
r_static
id|__inline__
r_int
r_char
id|ctrl_inb
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
DECL|function|ctrl_inw
r_static
id|__inline__
r_int
r_int
id|ctrl_inw
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
DECL|function|ctrl_inl
r_static
id|__inline__
r_int
r_int
id|ctrl_inl
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
DECL|function|ctrl_outb
r_static
id|__inline__
r_void
id|ctrl_outb
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
)brace
DECL|function|ctrl_outw
r_static
id|__inline__
r_void
id|ctrl_outw
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
)brace
DECL|function|ctrl_outl
r_static
id|__inline__
r_void
id|ctrl_outl
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
)brace
multiline_comment|/* Pages to physical address... */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)      ((page - mem_map) &lt;&lt; PAGE_SHIFT)
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus(page)       ((page - mem_map) &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * Macros used for converting between virtual and physical mappings.&n; */
DECL|macro|mm_ptov
mdefine_line|#define mm_ptov(vaddr)&t;&t;((void *) (vaddr))
DECL|macro|mm_vtop
mdefine_line|#define mm_vtop(vaddr)&t;&t;((unsigned long) (vaddr))
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(vaddr)&t;((void *) (vaddr))
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(vaddr)&t;((unsigned long) (vaddr))
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _H8300_IO_H */
eof
