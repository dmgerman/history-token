macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
multiline_comment|/*&n; * This file contains the definitions for the x86 IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated&n; * to (a) handle it all in a way that makes gcc able to optimize it&n; * as well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; */
multiline_comment|/*&n; * Thanks to James van Artsdalen for a better timing-fix than&n; * the two short jumps: using outb&squot;s to a nonexistent port seems&n; * to guarantee better timings even on fast machines.&n; *&n; * On the other hand, I&squot;d like to be sure of a non-existent port:&n; * I feel a bit unsafe about using 0x80 (should be safe, though)&n; *&n; *&t;&t;Linus&n; */
multiline_comment|/*&n;  *  Bit simplified and optimized by Jan Hubicka&n;  *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999.&n;  *&n;  *  isa_memset_io, isa_memcpy_fromio, isa_memcpy_toio added,&n;  *  isa_read[wl] and isa_write[wl] fixed&n;  *  - Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;  */
macro_line|#ifdef SLOW_IO_BY_JUMPING
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &quot;&bslash;njmp 1f&bslash;n1:&bslash;tjmp 1f&bslash;n1:&quot;
macro_line|#else
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO &quot;&bslash;noutb %%al,$0x80&quot;
macro_line|#endif
macro_line|#ifdef REALLY_SLOW_IO
DECL|macro|__FULL_SLOW_DOWN_IO
mdefine_line|#define __FULL_SLOW_DOWN_IO __SLOW_DOWN_IO __SLOW_DOWN_IO __SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#else
DECL|macro|__FULL_SLOW_DOWN_IO
mdefine_line|#define __FULL_SLOW_DOWN_IO __SLOW_DOWN_IO
macro_line|#endif
multiline_comment|/*&n; * Talk about misusing macros..&n; */
DECL|macro|__OUT1
mdefine_line|#define __OUT1(s,x) &bslash;&n;static inline void out##s(unsigned x value, unsigned short port) {
DECL|macro|__OUT2
mdefine_line|#define __OUT2(s,s1,s2) &bslash;&n;__asm__ __volatile__ (&quot;out&quot; #s &quot; %&quot; s1 &quot;0,%&quot; s2 &quot;1&quot;
DECL|macro|__OUT
mdefine_line|#define __OUT(s,s1,x) &bslash;&n;__OUT1(s,x) __OUT2(s,s1,&quot;w&quot;) : : &quot;a&quot; (value), &quot;Nd&quot; (port)); } &bslash;&n;__OUT1(s##_p,x) __OUT2(s,s1,&quot;w&quot;) __FULL_SLOW_DOWN_IO : : &quot;a&quot; (value), &quot;Nd&quot; (port));} &bslash;&n;
DECL|macro|__IN1
mdefine_line|#define __IN1(s) &bslash;&n;static inline RETURN_TYPE in##s(unsigned short port) { RETURN_TYPE _v;
DECL|macro|__IN2
mdefine_line|#define __IN2(s,s1,s2) &bslash;&n;__asm__ __volatile__ (&quot;in&quot; #s &quot; %&quot; s2 &quot;1,%&quot; s1 &quot;0&quot;
DECL|macro|__IN
mdefine_line|#define __IN(s,s1,i...) &bslash;&n;__IN1(s) __IN2(s,s1,&quot;w&quot;) : &quot;=a&quot; (_v) : &quot;Nd&quot; (port) ,##i ); return _v; } &bslash;&n;__IN1(s##_p) __IN2(s,s1,&quot;w&quot;) __FULL_SLOW_DOWN_IO : &quot;=a&quot; (_v) : &quot;Nd&quot; (port) ,##i ); return _v; } &bslash;&n;
DECL|macro|__INS
mdefine_line|#define __INS(s) &bslash;&n;static inline void ins##s(unsigned short port, void * addr, unsigned long count) &bslash;&n;{ __asm__ __volatile__ (&quot;rep ; ins&quot; #s &bslash;&n;: &quot;=D&quot; (addr), &quot;=c&quot; (count) : &quot;d&quot; (port),&quot;0&quot; (addr),&quot;1&quot; (count)); }
DECL|macro|__OUTS
mdefine_line|#define __OUTS(s) &bslash;&n;static inline void outs##s(unsigned short port, const void * addr, unsigned long count) &bslash;&n;{ __asm__ __volatile__ (&quot;rep ; outs&quot; #s &bslash;&n;: &quot;=S&quot; (addr), &quot;=c&quot; (count) : &quot;d&quot; (port),&quot;0&quot; (addr),&quot;1&quot; (count)); }
DECL|macro|RETURN_TYPE
mdefine_line|#define RETURN_TYPE unsigned char
id|__IN
c_func
(paren
id|b
comma
l_string|&quot;&quot;
)paren
DECL|macro|RETURN_TYPE
macro_line|#undef RETURN_TYPE
DECL|macro|RETURN_TYPE
mdefine_line|#define RETURN_TYPE unsigned short
id|__IN
c_func
(paren
id|w
comma
l_string|&quot;&quot;
)paren
DECL|macro|RETURN_TYPE
macro_line|#undef RETURN_TYPE
DECL|macro|RETURN_TYPE
mdefine_line|#define RETURN_TYPE unsigned int
id|__IN
c_func
(paren
id|l
comma
l_string|&quot;&quot;
)paren
DECL|macro|RETURN_TYPE
macro_line|#undef RETURN_TYPE
id|__OUT
c_func
(paren
id|b
comma
l_string|&quot;b&quot;
comma
r_char
)paren
id|__OUT
c_func
(paren
id|w
comma
l_string|&quot;w&quot;
comma
r_int
)paren
id|__OUT
c_func
(paren
id|l
comma
comma
r_int
)paren
id|__INS
c_func
(paren
id|b
)paren
id|__INS
c_func
(paren
id|w
)paren
id|__INS
c_func
(paren
id|l
)paren
id|__OUTS
c_func
(paren
id|b
)paren
id|__OUTS
c_func
(paren
id|w
)paren
id|__OUTS
c_func
(paren
id|l
)paren
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/vmalloc.h&gt;
multiline_comment|/*&n; * Temporary debugging check to catch old code using&n; * unmapped ISA addresses. Will be removed in 2.4.&n; */
macro_line|#if 0
r_extern
r_void
op_star
id|__io_virt_debug
c_func
(paren
r_int
r_int
id|x
comma
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__io_phys_debug
c_func
(paren
r_int
r_int
id|x
comma
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
mdefine_line|#define __io_virt(x) __io_virt_debug((unsigned long)(x), __FILE__, __LINE__)
singleline_comment|//#define __io_phys(x) __io_phys_debug((unsigned long)(x), __FILE__, __LINE__)
macro_line|#else
DECL|macro|__io_virt
mdefine_line|#define __io_virt(x) ((void *)(x))
singleline_comment|//#define __io_phys(x) __pa(x)
macro_line|#endif
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are pretty trivial&n; */
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
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|function|ioremap
r_static
r_inline
r_void
op_star
id|ioremap
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
multiline_comment|/*&n; * This one maps high address device memory and turns off caching for that area.&n; * it&squot;s useful if some control registers are in such an area and write combining&n; * or read caching is not desirable:&n; */
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
id|__ioremap
c_func
(paren
id|offset
comma
id|size
comma
id|_PAGE_PCD
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
multiline_comment|/*&n; * IO bus memory addresses are also 1:1 with the physical address&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the x86 architecture, we just read/write the&n; * memory location directly.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) __io_virt(addr))
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile unsigned short *) __io_virt(addr))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile unsigned int *) __io_virt(addr))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb readb
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw readw
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl readl
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) (*(volatile unsigned char *) __io_virt(addr) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) (*(volatile unsigned short *) __io_virt(addr) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) (*(volatile unsigned int *) __io_virt(addr) = (b))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb writeb
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew writew
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel writel
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset(__io_virt(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),__io_virt(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy(__io_virt(a),(b),(c))
multiline_comment|/*&n; * ISA space is &squot;always mapped&squot; on a typical x86 system, no need to&n; * explicitly ioremap() it. The fact that the ISA IO space is mapped&n; * to PAGE_OFFSET is pure coincidence - it does not mean ISA values&n; * are physical addresses. The following constant pointer can be&n; * used as the IO-area pointer (it can be iounmapped as well, so the&n; * analogy with PCI is quite large):&n; */
DECL|macro|__ISA_IO_base
mdefine_line|#define __ISA_IO_base ((char *)(PAGE_OFFSET))
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
mdefine_line|#define eth_io_copy_and_sum(a,b,c,d)&t;&t;eth_copy_and_sum((a),__io_virt(b),(c),(d))
DECL|macro|isa_eth_io_copy_and_sum
mdefine_line|#define isa_eth_io_copy_and_sum(a,b,c,d)&t;eth_copy_and_sum((a),__io_virt(__ISA_IO_base + (b)),(c),(d))
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
DECL|function|isa_check_signature
r_static
r_inline
r_int
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
multiline_comment|/* Nothing to do */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
