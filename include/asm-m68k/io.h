multiline_comment|/*&n; * linux/include/asm-m68k/io.h &n; *&n; * 4/1/00 RZ: - rewritten to avoid clashes between ISA/PCI and other&n; *              IO access&n; *            - added Q40 support&n; *            - added skeleton for GG-II and Amiga PCMCIA&n; * 2/3/01 RZ: - moved a few more defs into raw_io.h&n; *&n; * inX/outX/readX/writeX should not be used by any driver unless it does&n; * ISA or PCI access. Other drivers should use function defined in raw_io.h&n; * or define its own macros on top of these.&n; *&n; *    inX(),outX()              are for PCI and ISA I/O&n; *    readX(),writeX()          are for PCI memory&n; *    isa_readX(),isa_writeX()  are for ISA memory&n; *&n; * moved mem{cpy,set}_*io inside CONFIG_PCI&n; */
macro_line|#ifndef _IO_H
DECL|macro|_IO_H
mdefine_line|#define _IO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/raw_io.h&gt;
macro_line|#include &lt;asm/virtconvert.h&gt;
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#endif
multiline_comment|/*&n; * IO/MEM definitions for various ISA bridges&n; */
macro_line|#ifdef CONFIG_Q40
DECL|macro|q40_isa_io_base
mdefine_line|#define q40_isa_io_base  0xff400000
DECL|macro|q40_isa_mem_base
mdefine_line|#define q40_isa_mem_base 0xff800000
DECL|macro|Q40_ISA_IO_B
mdefine_line|#define Q40_ISA_IO_B(ioaddr) (q40_isa_io_base+1+4*((unsigned long)(ioaddr)))
DECL|macro|Q40_ISA_IO_W
mdefine_line|#define Q40_ISA_IO_W(ioaddr) (q40_isa_io_base+  4*((unsigned long)(ioaddr)))
DECL|macro|Q40_ISA_MEM_B
mdefine_line|#define Q40_ISA_MEM_B(madr)  (q40_isa_mem_base+1+4*((unsigned long)(madr)))
DECL|macro|Q40_ISA_MEM_W
mdefine_line|#define Q40_ISA_MEM_W(madr)  (q40_isa_mem_base+  4*((unsigned long)(madr)))
DECL|macro|MACH_HAS_ISA
mdefine_line|#define MACH_HAS_ISA 1
macro_line|#endif /* Q40 */
multiline_comment|/* GG-II Zorro to ISA bridge */
macro_line|#ifdef CONFIG_GG2
r_extern
r_int
r_int
id|gg2_isa_base
suffix:semicolon
DECL|macro|GG2_ISA_IO_B
mdefine_line|#define GG2_ISA_IO_B(ioaddr) (gg2_isa_base+1+((unsigned long)(ioaddr)*4))
DECL|macro|GG2_ISA_IO_W
mdefine_line|#define GG2_ISA_IO_W(ioaddr) (gg2_isa_base+  ((unsigned long)(ioaddr)*4))
DECL|macro|GG2_ISA_MEM_B
mdefine_line|#define GG2_ISA_MEM_B(madr)  (gg2_isa_base+1+(((unsigned long)(madr)*4) &amp; 0xfffff))
DECL|macro|GG2_ISA_MEM_W
mdefine_line|#define GG2_ISA_MEM_W(madr)  (gg2_isa_base+  (((unsigned long)(madr)*4) &amp; 0xfffff))
macro_line|#ifndef MACH_HAS_ISA
DECL|macro|MACH_HAS_ISA
mdefine_line|#define MACH_HAS_ISA 1
macro_line|#else 
DECL|macro|MACH_HAS_ISA
macro_line|#undef MACH_HAS_ISA
DECL|macro|MACH_HAS_ISA
mdefine_line|#define MACH_HAS_ISA m
macro_line|#endif
macro_line|#endif /* GG2 */
macro_line|#ifdef CONFIG_AMIGA_PCMCIA
macro_line|#include &lt;asm/amigayle.h&gt;
DECL|macro|AG_ISA_IO_B
mdefine_line|#define AG_ISA_IO_B(ioaddr) ( GAYLE_IO+(ioaddr)+(((ioaddr)&amp;1)*GAYLE_ODD) )
DECL|macro|AG_ISA_IO_W
mdefine_line|#define AG_ISA_IO_W(ioaddr) ( GAYLE_IO+(ioaddr) )
macro_line|#ifndef MACH_HAS_ISA
DECL|macro|MACH_HAS_ISA
mdefine_line|#define MACH_HAS_ISA 1
macro_line|#else 
DECL|macro|MACH_HAS_ISA
macro_line|#undef MACH_HAS_ISA
DECL|macro|MACH_HAS_ISA
mdefine_line|#define MACH_HAS_ISA m
macro_line|#endif
macro_line|#endif /* AMIGA_PCMCIA */
macro_line|#ifdef MACH_HAS_ISA
DECL|macro|Q40_ISA
mdefine_line|#define Q40_ISA (1)
DECL|macro|GG2_ISA
mdefine_line|#define GG2_ISA (2)
DECL|macro|AG_ISA
mdefine_line|#define AG_ISA  (3)
macro_line|#if defined(CONFIG_Q40) &amp;&amp; MACH_HAS_ISA==1
DECL|macro|ISA_TYPE
mdefine_line|#define ISA_TYPE Q40_ISA
DECL|macro|ISA_SEX
mdefine_line|#define ISA_SEX  0
macro_line|#endif
macro_line|#if defined(CONFIG_AMIGA_PCMCIA) &amp;&amp; MACH_HAS_ISA==1
DECL|macro|ISA_TYPE
mdefine_line|#define ISA_TYPE AG_ISA
DECL|macro|ISA_SEX
mdefine_line|#define ISA_SEX  1
macro_line|#endif 
macro_line|#if defined(CONFIG_GG2) &amp;&amp; MACH_HAS_ISA==1
DECL|macro|ISA_TYPE
mdefine_line|#define ISA_TYPE GG2_ISA
DECL|macro|ISA_SEX
mdefine_line|#define ISA_SEX  0
macro_line|#endif
macro_line|#ifdef CONFIG_ISA
r_extern
r_int
id|isa_type
suffix:semicolon
r_extern
r_int
id|isa_sex
suffix:semicolon
DECL|macro|ISA_TYPE
mdefine_line|#define ISA_TYPE isa_type
DECL|macro|ISA_SEX
mdefine_line|#define ISA_SEX  isa_sex
macro_line|#endif
multiline_comment|/*&n; * define inline addr translation functions. Normally only one variant will&n; * be compiled in so the case statement will be optimised away&n; */
DECL|function|isa_itb
r_static
r_inline
r_int
r_int
id|isa_itb
c_func
(paren
r_int
id|addr
)paren
(brace
r_switch
c_cond
(paren
id|ISA_TYPE
)paren
(brace
macro_line|#ifdef CONFIG_Q40
r_case
id|Q40_ISA
suffix:colon
r_return
id|Q40_ISA_IO_B
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_GG2
r_case
id|GG2_ISA
suffix:colon
r_return
id|GG2_ISA_IO_B
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGA_PCMCIA
r_case
id|AG_ISA
suffix:colon
r_return
id|AG_ISA_IO_B
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* avoid warnings, just in case */
)brace
)brace
DECL|function|isa_itw
r_static
r_inline
r_int
r_int
id|isa_itw
c_func
(paren
r_int
id|addr
)paren
(brace
r_switch
c_cond
(paren
id|ISA_TYPE
)paren
(brace
macro_line|#ifdef CONFIG_Q40
r_case
id|Q40_ISA
suffix:colon
r_return
id|Q40_ISA_IO_W
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_GG2
r_case
id|GG2_ISA
suffix:colon
r_return
id|GG2_ISA_IO_W
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGA_PCMCIA
r_case
id|AG_ISA
suffix:colon
r_return
id|AG_ISA_IO_W
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* avoid warnings, just in case */
)brace
)brace
DECL|function|isa_mtb
r_static
r_inline
r_int
r_int
id|isa_mtb
c_func
(paren
r_int
id|addr
)paren
(brace
r_switch
c_cond
(paren
id|ISA_TYPE
)paren
(brace
macro_line|#ifdef CONFIG_Q40
r_case
id|Q40_ISA
suffix:colon
r_return
id|Q40_ISA_MEM_B
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_GG2
r_case
id|GG2_ISA
suffix:colon
r_return
id|GG2_ISA_MEM_B
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* FIXME: any ISA mem mapping for PCMCIA? */
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* avoid warnings, just in case */
)brace
)brace
DECL|function|isa_mtw
r_static
r_inline
r_int
r_int
id|isa_mtw
c_func
(paren
r_int
id|addr
)paren
(brace
r_switch
c_cond
(paren
id|ISA_TYPE
)paren
(brace
macro_line|#ifdef CONFIG_Q40
r_case
id|Q40_ISA
suffix:colon
r_return
id|Q40_ISA_MEM_W
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_GG2
r_case
id|GG2_ISA
suffix:colon
r_return
id|GG2_ISA_MEM_W
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* avoid warnings, just in case */
)brace
)brace
DECL|macro|isa_inb
mdefine_line|#define isa_inb(port)      in_8(isa_itb(port))
DECL|macro|isa_inw
mdefine_line|#define isa_inw(port)      (ISA_SEX ? in_be16(isa_itw(port)) : in_le16(isa_itw(port)))
DECL|macro|isa_outb
mdefine_line|#define isa_outb(val,port) out_8(isa_itb(port),(val))
DECL|macro|isa_outw
mdefine_line|#define isa_outw(val,port) (ISA_SEX ? out_be16(isa_itw(port),(val)) : out_le16(isa_itw(port),(val)))
DECL|macro|isa_readb
mdefine_line|#define isa_readb(p)       in_8(isa_mtb(p))
DECL|macro|isa_readw
mdefine_line|#define isa_readw(p)       in_le16(isa_mtw(p))
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(val,p)  out_8(isa_mtb(p),(val))
DECL|macro|isa_writew
mdefine_line|#define isa_writew(val,p)  out_le16(isa_mtw(p),(val))
DECL|macro|isa_inb_p
mdefine_line|#define isa_inb_p(p)      ({unsigned char v=isa_inb(p);isa_outb(0,0x80);v;})
DECL|macro|isa_outb_p
mdefine_line|#define isa_outb_p(v,p)   ({isa_outb((v),(p));isa_outb(0,0x80);})
DECL|macro|isa_insb
mdefine_line|#define isa_insb(port, buf, nr) raw_insb(isa_itb(port), (buf), (nr))
DECL|macro|isa_outsb
mdefine_line|#define isa_outsb(port, buf, nr) raw_outsb(isa_itb(port), (buf), (nr))
DECL|macro|isa_insw
mdefine_line|#define isa_insw(port, buf, nr)     &bslash;&n;       (ISA_SEX ? raw_insw(isa_itw(port), (buf), (nr)) :    &bslash;&n;                  raw_insw_swapw(isa_itw(port), (buf), (nr)))
DECL|macro|isa_outsw
mdefine_line|#define isa_outsw(port, buf, nr)    &bslash;&n;       (ISA_SEX ? raw_outsw(isa_itw(port), (buf), (nr)) :  &bslash;&n;                  raw_outsw_swapw(isa_itw(port), (buf), (nr)))
macro_line|#endif  /* MACH_HAS_ISA */
macro_line|#if defined(CONFIG_ISA) &amp;&amp; !defined(CONFIG_PCI) 
DECL|macro|inb
mdefine_line|#define inb     isa_inb
DECL|macro|inb_p
mdefine_line|#define inb_p   isa_inb_p
DECL|macro|outb
mdefine_line|#define outb    isa_outb
DECL|macro|outb_p
mdefine_line|#define outb_p  isa_outb_p
DECL|macro|inw
mdefine_line|#define inw     isa_inw
DECL|macro|outw
mdefine_line|#define outw    isa_outw
DECL|macro|inl
mdefine_line|#define inl     isa_inw
DECL|macro|outl
mdefine_line|#define outl    isa_outw
DECL|macro|insb
mdefine_line|#define insb    isa_insb
DECL|macro|insw
mdefine_line|#define insw    isa_insw
DECL|macro|outsb
mdefine_line|#define outsb   isa_outsb
DECL|macro|outsw
mdefine_line|#define outsw   isa_outsw
macro_line|#endif /* MACH_HAS_ISA */
macro_line|#if defined(CONFIG_PCI)
DECL|macro|inl
mdefine_line|#define inl(port)       in_le32(port)
DECL|macro|outl
mdefine_line|#define outl(val,port)  out_le32((port),(val))
DECL|macro|readb
mdefine_line|#define readb(addr)  in_8(addr)
DECL|macro|readw
mdefine_line|#define readw(addr)  in_le16(addr)
DECL|macro|readl
mdefine_line|#define readl(addr)  in_le32(addr)
DECL|macro|writeb
mdefine_line|#define writeb(val,addr)  out_8((addr),(val))
DECL|macro|writew
mdefine_line|#define writew(val,addr)  out_le16((addr),(val))
DECL|macro|writel
mdefine_line|#define writel(val,addr)  out_le32((addr),(val))
macro_line|#ifndef CONFIG_ISA
DECL|macro|inb
mdefine_line|#define inb(port)      in_8(port)
DECL|macro|outb
mdefine_line|#define outb(val,port) out_8((port),(val))
DECL|macro|inw
mdefine_line|#define inw(port)      in_le16(port)
DECL|macro|outw
mdefine_line|#define outw(val,port) out_le16((port),(val))
macro_line|#else
multiline_comment|/*&n; * kernel with both ISA and PCI compiled in, those have &n; * conflicting defs for in/out. Simply consider port &lt; 1024 &n; * ISA and everything else PCI&n; */
DECL|macro|inb
mdefine_line|#define inb(port) ((port)&lt;1024 ? isa_inb(port) : in_8(port))
DECL|macro|inb_p
mdefine_line|#define inb_p(port) ((port)&lt;1024 ? isa_inb_p(port) : in_8(port))
DECL|macro|inw
mdefine_line|#define inw(port) ((port)&lt;1024 ? isa_inw(port) : in_le16(port))
DECL|macro|outb
mdefine_line|#define outb(val,port) ((port)&lt;1024 ? isa_outb((val),(port)) : out_8((port),(val)))
DECL|macro|outb_p
mdefine_line|#define outb_p(val,port) ((port)&lt;1024 ? isa_outb_p((val),(port)) : out_8((port),(val)))
DECL|macro|outw
mdefine_line|#define outw(val,port) ((port)&lt;1024 ? isa_outw((val),(port)) : out_le16((port),(val)))
macro_line|#endif
macro_line|#endif /* CONFIG_PCI */
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
macro_line|#ifndef CONFIG_SUN3
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
macro_line|#else
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0x0fffffff
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _IO_H */
eof
