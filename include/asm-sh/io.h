macro_line|#ifndef __ASM_SH_IO_H
DECL|macro|__ASM_SH_IO_H
mdefine_line|#define __ASM_SH_IO_H
multiline_comment|/*&n; * Convention:&n; *    read{b,w,l}/write{b,w,l} are for PCI,&n; *    while in{b,w,l}/out{b,w,l} are for ISA&n; * These may (will) be platform specific function.&n; * In addition we have &squot;pausing&squot; versions: in{b,w,l}_p/out{b,w,l}_p&n; * and &squot;string&squot; versions: ins{b,w,l}/outs{b,w,l}&n; * For read{b,w,l} and write{b,w,l} there are also __raw versions, which&n; * do not have a memory barrier after them.&n; *&n; * In addition, we have &n; *   ctrl_in{b,w,l}/ctrl_out{b,w,l} for SuperH specific I/O.&n; *   which are processor specific.&n; */
multiline_comment|/*&n; * We follow the Alpha convention here:&n; *  __inb expands to an inline function call (which calls via the mv)&n; *  _inb  is a real function call (note ___raw fns are _ version of __raw)&n; *  inb   by default expands to _inb, but the machine specific code may&n; *        define it to __inb if it chooses.&n; */
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Depending on which platform we are running on, we need different&n; * I/O functions.&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Since boards are able to define their own set of I/O routines through&n; * their respective machine vector, we always wrap through the mv.&n; *&n; * Also, in the event that a board hasn&squot;t provided its own definition for&n; * a given routine, it will be wrapped to generic code at run-time.&n; */
DECL|macro|__inb
macro_line|# define __inb(p)&t;sh_mv.mv_inb((p))
DECL|macro|__inw
macro_line|# define __inw(p)&t;sh_mv.mv_inw((p))
DECL|macro|__inl
macro_line|# define __inl(p)&t;sh_mv.mv_inl((p))
DECL|macro|__outb
macro_line|# define __outb(x,p)&t;sh_mv.mv_outb((x),(p))
DECL|macro|__outw
macro_line|# define __outw(x,p)&t;sh_mv.mv_outw((x),(p))
DECL|macro|__outl
macro_line|# define __outl(x,p)&t;sh_mv.mv_outl((x),(p))
DECL|macro|__inb_p
macro_line|# define __inb_p(p)&t;sh_mv.mv_inb_p((p))
DECL|macro|__inw_p
macro_line|# define __inw_p(p)&t;sh_mv.mv_inw_p((p))
DECL|macro|__inl_p
macro_line|# define __inl_p(p)&t;sh_mv.mv_inl_p((p))
DECL|macro|__outb_p
macro_line|# define __outb_p(x,p)&t;sh_mv.mv_outb_p((x),(p))
DECL|macro|__outw_p
macro_line|# define __outw_p(x,p)&t;sh_mv.mv_outw_p((x),(p))
DECL|macro|__outl_p
macro_line|# define __outl_p(x,p)&t;sh_mv.mv_outl_p((x),(p))
DECL|macro|__insb
macro_line|# define __insb(p,b,c)&t;sh_mv.mv_insb((p), (b), (c))
DECL|macro|__insw
macro_line|# define __insw(p,b,c)&t;sh_mv.mv_insw((p), (b), (c))
DECL|macro|__insl
macro_line|# define __insl(p,b,c)&t;sh_mv.mv_insl((p), (b), (c))
DECL|macro|__outsb
macro_line|# define __outsb(p,b,c)&t;sh_mv.mv_outsb((p), (b), (c))
DECL|macro|__outsw
macro_line|# define __outsw(p,b,c)&t;sh_mv.mv_outsw((p), (b), (c))
DECL|macro|__outsl
macro_line|# define __outsl(p,b,c)&t;sh_mv.mv_outsl((p), (b), (c))
DECL|macro|__readb
macro_line|# define __readb(a)&t;sh_mv.mv_readb((a))
DECL|macro|__readw
macro_line|# define __readw(a)&t;sh_mv.mv_readw((a))
DECL|macro|__readl
macro_line|# define __readl(a)&t;sh_mv.mv_readl((a))
DECL|macro|__writeb
macro_line|# define __writeb(v,a)&t;sh_mv.mv_writeb((v),(a))
DECL|macro|__writew
macro_line|# define __writew(v,a)&t;sh_mv.mv_writew((v),(a))
DECL|macro|__writel
macro_line|# define __writel(v,a)&t;sh_mv.mv_writel((v),(a))
DECL|macro|__ioremap
macro_line|# define __ioremap(a,s)&t;sh_mv.mv_ioremap((a), (s))
DECL|macro|__iounmap
macro_line|# define __iounmap(a)&t;sh_mv.mv_iounmap((a))
DECL|macro|__isa_port2addr
macro_line|# define __isa_port2addr(a)&t;sh_mv.mv_isa_port2addr(a)
DECL|macro|inb
macro_line|# define inb&t;&t;__inb
DECL|macro|inw
macro_line|# define inw&t;&t;__inw
DECL|macro|inl
macro_line|# define inl&t;&t;__inl
DECL|macro|outb
macro_line|# define outb&t;&t;__outb
DECL|macro|outw
macro_line|# define outw&t;&t;__outw
DECL|macro|outl
macro_line|# define outl&t;&t;__outl
DECL|macro|inb_p
macro_line|# define inb_p&t;&t;__inb_p
DECL|macro|inw_p
macro_line|# define inw_p&t;&t;__inw_p
DECL|macro|inl_p
macro_line|# define inl_p&t;&t;__inl_p
DECL|macro|outb_p
macro_line|# define outb_p&t;&t;__outb_p
DECL|macro|outw_p
macro_line|# define outw_p&t;&t;__outw_p
DECL|macro|outl_p
macro_line|# define outl_p&t;&t;__outl_p
DECL|macro|insb
macro_line|# define insb&t;&t;__insb
DECL|macro|insw
macro_line|# define insw&t;&t;__insw
DECL|macro|insl
macro_line|# define insl&t;&t;__insl
DECL|macro|outsb
macro_line|# define outsb&t;&t;__outsb
DECL|macro|outsw
macro_line|# define outsw&t;&t;__outsw
DECL|macro|outsl
macro_line|# define outsl&t;&t;__outsl
DECL|macro|__raw_readb
macro_line|# define __raw_readb&t;__readb
DECL|macro|__raw_readw
macro_line|# define __raw_readw&t;__readw
DECL|macro|__raw_readl
macro_line|# define __raw_readl&t;__readl
DECL|macro|__raw_writeb
macro_line|# define __raw_writeb&t;__writeb
DECL|macro|__raw_writew
macro_line|# define __raw_writew&t;__writew
DECL|macro|__raw_writel
macro_line|# define __raw_writel&t;__writel
multiline_comment|/*&n; * The platform header files may define some of these macros to use&n; * the inlined versions where appropriate.  These macros may also be&n; * redefined by userlevel programs.&n; */
macro_line|#ifdef __raw_readb
DECL|macro|readb
macro_line|# define readb(a)&t;({ unsigned long r_ = __raw_readb((unsigned long)a); mb(); r_; })
macro_line|#endif
macro_line|#ifdef __raw_readw
DECL|macro|readw
macro_line|# define readw(a)&t;({ unsigned long r_ = __raw_readw((unsigned long)a); mb(); r_; })
macro_line|#endif
macro_line|#ifdef __raw_readl
DECL|macro|readl
macro_line|# define readl(a)&t;({ unsigned long r_ = __raw_readl((unsigned long)a); mb(); r_; })
macro_line|#endif
macro_line|#ifdef __raw_writeb
DECL|macro|writeb
macro_line|# define writeb(v,a)&t;({ __raw_writeb((v),(unsigned long)(a)); mb(); })
macro_line|#endif
macro_line|#ifdef __raw_writew
DECL|macro|writew
macro_line|# define writew(v,a)&t;({ __raw_writew((v),(unsigned long)(a)); mb(); })
macro_line|#endif
macro_line|#ifdef __raw_writel
DECL|macro|writel
macro_line|# define writel(v,a)&t;({ __raw_writel((v),(unsigned long)(a)); mb(); })
macro_line|#endif
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(a) readb(a)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(a) readw(a)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(a) readl(a)
DECL|macro|mmiowb
mdefine_line|#define mmiowb()
multiline_comment|/*&n; * If the platform has PC-like I/O, this function converts the offset into&n; * an address.&n; */
DECL|function|isa_port2addr
r_static
id|__inline__
r_int
r_int
id|isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_return
id|__isa_port2addr
c_func
(paren
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function provides a method for the generic case where a board-specific&n; * isa_port2addr simply needs to return the port + some arbitrary port base.&n; *&n; * We use this at board setup time to implicitly set the port base, and&n; * as a result, we can use the generic isa_port2addr.&n; */
DECL|function|__set_io_port_base
r_static
r_inline
r_void
id|__set_io_port_base
c_func
(paren
r_int
r_int
id|pbase
)paren
(brace
r_extern
r_int
r_int
id|generic_io_base
suffix:semicolon
id|generic_io_base
op_assign
id|pbase
suffix:semicolon
)brace
DECL|macro|isa_readb
mdefine_line|#define isa_readb(a) readb(isa_port2addr(a))
DECL|macro|isa_readw
mdefine_line|#define isa_readw(a) readw(isa_port2addr(a))
DECL|macro|isa_readl
mdefine_line|#define isa_readl(a) readl(isa_port2addr(a))
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(b,a) writeb(b,isa_port2addr(a))
DECL|macro|isa_writew
mdefine_line|#define isa_writew(w,a) writew(w,isa_port2addr(a))
DECL|macro|isa_writel
mdefine_line|#define isa_writel(l,a) writel(l,isa_port2addr(a))
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c) &bslash;&n;  memset((void *)(isa_port2addr((unsigned long)a)),(b),(c))
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c) &bslash;&n;  memcpy((a),(void *)(isa_port2addr((unsigned long)(b))),(c))
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c) &bslash;&n;  memcpy((void *)(isa_port2addr((unsigned long)(a))),(b),(c))
multiline_comment|/* We really want to try and get these to memcpy etc */
r_extern
r_void
id|memcpy_fromio
c_func
(paren
r_void
op_star
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
id|memcpy_toio
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
r_int
)paren
suffix:semicolon
r_extern
r_void
id|memset_io
c_func
(paren
r_int
r_int
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* SuperH on-chip I/O functions */
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
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are trivial on the 1:1 Linux/SuperH mapping&n; */
DECL|function|virt_to_phys
r_static
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
id|PHYSADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_static
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
(paren
r_void
op_star
)paren
id|P1SEGADDR
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus page_to_phys
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the x86 architecture, we just read/write the&n; * memory location directly.&n; *&n; * On SH, we have the whole physical address space mapped at all times&n; * (as MIPS does), so &quot;ioremap()&quot; and &quot;iounmap()&quot; do not need to do&n; * anything.  (This isn&squot;t true for all machines but we still handle&n; * these cases with wired TLB entries anyway ...)&n; *&n; * We cheat a bit and always return uncachable areas until we&squot;ve fixed&n; * the drivers to handle caching properly.  &n; */
DECL|function|ioremap
r_static
id|__inline__
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
id|__ioremap
c_func
(paren
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|iounmap
r_static
id|__inline__
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|__iounmap
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(off,size) ioremap(off,size)
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
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size) &bslash;&n;    __flush_purge_region(_start,_size)
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size) &bslash;&n;    __flush_invalidate_region(_start,_size)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size) &bslash;&n;    __flush_wback_region(_start,_size)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_IO_H */
eof
