macro_line|#ifndef __ASM_SH_IO_H
DECL|macro|__ASM_SH_IO_H
mdefine_line|#define __ASM_SH_IO_H
multiline_comment|/*&n; * Convention:&n; *    read{b,w,l}/write{b,w,l} are for PCI,&n; *    while in{b,w,l}/out{b,w,l} are for ISA&n; * These may (will) be platform specific function.&n; * In addition we have &squot;pausing&squot; versions: in{b,w,l}_p/out{b,w,l}_p&n; * and &squot;string&squot; versions: ins{b,w,l}/outs{b,w,l}&n; * For read{b,w,l} and write{b,w,l} there are also __raw versions, which&n; * do not have a memory barrier after them.&n; *&n; * In addition, we have &n; *   ctrl_in{b,w,l}/ctrl_out{b,w,l} for SuperH specific I/O.&n; *   which are processor specific.&n; */
multiline_comment|/*&n; * We follow the Alpha convention here:&n; *  __inb expands to an inline function call (which either calls via the&n; *        mach_vec if generic, or a machine specific implementation)&n; *  _inb  is a real function call (note ___raw fns are _ version of __raw)&n; *  inb   by default expands to _inb, but the machine specif code may&n; *        define it to __inb if it chooses.&n; */
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Depending on which platform we are running on, we need different&n; * I/O functions.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#if defined(CONFIG_SH_GENERIC) || defined(CONFIG_SH_CQREEK) || defined(CONFIG_SH_UNKNOWN)
multiline_comment|/* In a generic kernel, we always go through the machine vector.  */
macro_line|#include &lt;asm/machvec.h&gt;
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
mdefine_line|#define __insb(p,b,c)&t;sh_mv.mv_insb((p), (b), (c))
DECL|macro|__insw
mdefine_line|#define __insw(p,b,c)&t;sh_mv.mv_insw((p), (b), (c))
DECL|macro|__insl
mdefine_line|#define __insl(p,b,c)&t;sh_mv.mv_insl((p), (b), (c))
DECL|macro|__outsb
mdefine_line|#define __outsb(p,b,c)&t;sh_mv.mv_outsb((p), (b), (c))
DECL|macro|__outsw
mdefine_line|#define __outsw(p,b,c)&t;sh_mv.mv_outsw((p), (b), (c))
DECL|macro|__outsl
mdefine_line|#define __outsl(p,b,c)&t;sh_mv.mv_outsl((p), (b), (c))
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
macro_line|#else
multiline_comment|/* Control operations through platform specific headers */
DECL|macro|__WANT_IO_DEF
macro_line|# define __WANT_IO_DEF
macro_line|# if defined(CONFIG_SH_HP600)
macro_line|#  include &lt;asm/io_hd64461.h&gt;
macro_line|# elif defined(CONFIG_SH_7750_OVERDRIVE)
macro_line|#  include &lt;asm/io_od.h&gt;
macro_line|# elif defined(CONFIG_SH_SOLUTION_ENGINE)
macro_line|#  include &lt;asm/io_se.h&gt;
macro_line|# elif defined(CONFIG_SH_DMIDA) || &bslash;&n;       defined(CONFIG_SH_STB1_HARP) || &bslash;&n;       defined(CONFIG_SH_STB1_OVERDRIVE)
macro_line|#  include &lt;asm/io_hd64465.h&gt;
macro_line|# elif defined(CONFIG_SH_EC3104)
macro_line|#  include &lt;asm/io_ec3104.h&gt;
macro_line|# elif defined(CONFIG_SH_DREAMCAST)
macro_line|#  include &lt;asm/io_dc.h&gt;
macro_line|# elif defined(CONFIG_SH_CAT68701)
macro_line|#  include &lt;asm/io_cat68701.h&gt;
macro_line|# elif defined(CONFIG_SH_UNKNOWN)
macro_line|#  include &lt;asm/io_unknown.h&gt;
macro_line|# else
macro_line|#  error &quot;What system is this?&quot;
macro_line|#endif
DECL|macro|__WANT_IO_DEF
macro_line|#undef __WANT_IO_DEF
macro_line|#endif /* GENERIC */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* These are always function calls, in both kernel and user space */
r_extern
r_int
r_char
id|_inb
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_inw
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_inl
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outb
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outw
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outl
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_char
id|_inb_p
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_inw_p
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_inl_p
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outb_p
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outw_p
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_outl_p
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|_insb
(paren
r_int
r_int
id|port
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
r_extern
r_void
id|_insw
(paren
r_int
r_int
id|port
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
r_extern
r_void
id|_insl
(paren
r_int
r_int
id|port
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
r_extern
r_void
id|_outsb
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|_outsw
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|_outsl
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
r_char
id|_readb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_readw
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_readl
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|_writeb
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
suffix:semicolon
r_extern
r_void
id|_writew
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
suffix:semicolon
r_extern
r_void
id|_writel
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
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_int
r_char
id|___raw_readb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|___raw_readw
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|___raw_readl
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|___raw_writeb
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
suffix:semicolon
r_extern
r_void
id|___raw_writew
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
suffix:semicolon
r_extern
r_void
id|___raw_writel
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
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * The platform header files may define some of these macros to use&n; * the inlined versions where appropriate.  These macros may also be&n; * redefined by userlevel programs.&n; */
macro_line|#ifndef inb
DECL|macro|inb
macro_line|# define inb(p)&t;&t;_inb(p)
macro_line|#endif
macro_line|#ifndef inw
DECL|macro|inw
macro_line|# define inw(p)&t;&t;_inw(p)
macro_line|#endif
macro_line|#ifndef inl
DECL|macro|inl
macro_line|# define inl(p)&t;&t;_inl(p)
macro_line|#endif
macro_line|#ifndef outb
DECL|macro|outb
macro_line|# define outb(b,p)&t;_outb((b),(p))
macro_line|#endif
macro_line|#ifndef outw
DECL|macro|outw
macro_line|# define outw(w,p)&t;_outw((w),(p))
macro_line|#endif
macro_line|#ifndef outl
DECL|macro|outl
macro_line|# define outl(l,p)&t;_outl((l),(p))
macro_line|#endif
macro_line|#ifndef inb_p
DECL|macro|inb_p
macro_line|# define inb_p&t;&t;_inb_p
macro_line|#endif
macro_line|#ifndef inw_p
DECL|macro|inw_p
macro_line|# define inw_p&t;&t;_inw_p
macro_line|#endif
macro_line|#ifndef inl_p
DECL|macro|inl_p
macro_line|# define inl_p&t;&t;_inl_p
macro_line|#endif
macro_line|#ifndef outb_p
DECL|macro|outb_p
macro_line|# define outb_p&t;&t;_outb_p
macro_line|#endif
macro_line|#ifndef outw_p
DECL|macro|outw_p
macro_line|# define outw_p&t;&t;_outw_p
macro_line|#endif
macro_line|#ifndef outl_p
DECL|macro|outl_p
macro_line|# define outl_p&t;&t;_outl_p
macro_line|#endif
macro_line|#ifndef insb
DECL|macro|insb
macro_line|# define insb(p,d,c)&t;_insb((p),(d),(c))
macro_line|#endif
macro_line|#ifndef insw
DECL|macro|insw
macro_line|# define insw(p,d,c)&t;_insw((p),(d),(c))
macro_line|#endif
macro_line|#ifndef insl
DECL|macro|insl
macro_line|# define insl(p,d,c)&t;_insl((p),(d),(c))
macro_line|#endif
macro_line|#ifndef outsb
DECL|macro|outsb
macro_line|# define outsb(p,s,c)&t;_outsb((p),(s),(c))
macro_line|#endif
macro_line|#ifndef outsw
DECL|macro|outsw
macro_line|# define outsw(p,s,c)&t;_outsw((p),(s),(c))
macro_line|#endif
macro_line|#ifndef outsl
DECL|macro|outsl
macro_line|# define outsl(p,s,c)&t;_outsl((p),(s),(c))
macro_line|#endif
macro_line|#ifdef __raw_readb
DECL|macro|readb
macro_line|# define readb(a)&t;({ unsigned long r_ = __raw_readb(a); mb(); r_; })
macro_line|#endif
macro_line|#ifdef __raw_readw
DECL|macro|readw
macro_line|# define readw(a)&t;({ unsigned long r_ = __raw_readw(a); mb(); r_; })
macro_line|#endif
macro_line|#ifdef __raw_readl
DECL|macro|readl
macro_line|# define readl(a)&t;({ unsigned long r_ = __raw_readl(a); mb(); r_; })
macro_line|#endif
macro_line|#ifdef __raw_writeb
DECL|macro|writeb
macro_line|# define writeb(v,a)&t;({ __raw_writeb((v),(a)); mb(); })
macro_line|#endif
macro_line|#ifdef __raw_writew
DECL|macro|writew
macro_line|# define writew(v,a)&t;({ __raw_writew((v),(a)); mb(); })
macro_line|#endif
macro_line|#ifdef __raw_writel
DECL|macro|writel
macro_line|# define writel(v,a)&t;({ __raw_writel((v),(a)); mb(); })
macro_line|#endif
macro_line|#ifndef __raw_readb
DECL|macro|__raw_readb
macro_line|# define __raw_readb(a)&t;___raw_readb((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef __raw_readw
DECL|macro|__raw_readw
macro_line|# define __raw_readw(a)&t;___raw_readw((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef __raw_readl
DECL|macro|__raw_readl
macro_line|# define __raw_readl(a)&t;___raw_readl((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef __raw_writeb
DECL|macro|__raw_writeb
macro_line|# define __raw_writeb(v,a)  ___raw_writeb((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifndef __raw_writew
DECL|macro|__raw_writew
macro_line|# define __raw_writew(v,a)  ___raw_writew((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifndef __raw_writel
DECL|macro|__raw_writel
macro_line|# define __raw_writel(v,a)  ___raw_writel((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifndef readb
DECL|macro|readb
macro_line|# define readb(a)&t;_readb((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef readw
DECL|macro|readw
macro_line|# define readw(a)&t;_readw((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef readl
DECL|macro|readl
macro_line|# define readl(a)&t;_readl((unsigned long)(a))
macro_line|#endif
macro_line|#ifndef writeb
DECL|macro|writeb
macro_line|# define writeb(v,a)&t;_writeb((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifndef writew
DECL|macro|writew
macro_line|# define writew(v,a)&t;_writew((v),(unsigned long)(a))
macro_line|#endif
macro_line|#ifndef writel
DECL|macro|writel
macro_line|# define writel(v,a)&t;_writel((v),(unsigned long)(a))
macro_line|#endif
macro_line|#else 
multiline_comment|/* Userspace declarations.  */
r_extern
r_int
r_char
id|inb
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
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
r_extern
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
r_extern
r_void
id|outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|outw
c_func
(paren
r_int
r_int
id|w
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|outl
c_func
(paren
r_int
r_int
id|l
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
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
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
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
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
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
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsw
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsl
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
r_char
id|readb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|readw
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|readl
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|writeb
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
suffix:semicolon
r_extern
r_void
id|writew
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
suffix:semicolon
r_extern
r_void
id|writel
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
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * If the platform has PC-like I/O, this function converts the offset into&n; * an address.&n; */
DECL|function|isa_port2addr
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
r_extern
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
macro_line|#include &lt;asm/addrspace.h&gt;
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
id|PHYSADDR
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
mdefine_line|#define dma_cache_wback_inv(_start,_size) &bslash;&n;    cache_flush_area((unsigned long)(_start),((unsigned long)(_start)+(_size)))
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size) &bslash;&n;    cache_purge_area((unsigned long)(_start),((unsigned long)(_start)+(_size)))
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size) &bslash;&n;    cache_wback_area((unsigned long)(_start),((unsigned long)(_start)+(_size)))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_IO_H */
eof
