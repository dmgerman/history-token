macro_line|#ifndef __ALPHA_IO_H
DECL|macro|__ALPHA_IO_H
mdefine_line|#define __ALPHA_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* We don&squot;t use IO slowdowns on the Alpha, but.. */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO&t;do { } while (0)
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO&t;do { } while (0)
multiline_comment|/*&n; * Virtual -&gt; physical identity mapping starts at this offset&n; */
macro_line|#ifdef USE_48_BIT_KSEG
DECL|macro|IDENT_ADDR
mdefine_line|#define IDENT_ADDR     0xffff800000000000
macro_line|#else
DECL|macro|IDENT_ADDR
mdefine_line|#define IDENT_ADDR     0xfffffc0000000000
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/*&n; * We try to avoid hae updates (thus the cache), but when we&n; * do need to update the hae, we need to do it atomically, so&n; * that any interrupts wouldn&squot;t get confused with the hae&n; * register not being up-to-date with respect to the hardware&n; * value.&n; */
DECL|function|__set_hae
r_static
r_inline
r_void
id|__set_hae
c_func
(paren
r_int
r_int
id|new_hae
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|alpha_mv.hae_cache
op_assign
id|new_hae
suffix:semicolon
op_star
id|alpha_mv.hae_register
op_assign
id|new_hae
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Re-read to make sure it was written.  */
id|new_hae
op_assign
op_star
id|alpha_mv.hae_register
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|set_hae
r_static
r_inline
r_void
id|set_hae
c_func
(paren
r_int
r_int
id|new_hae
)paren
(brace
r_if
c_cond
(paren
id|new_hae
op_ne
id|alpha_mv.hae_cache
)paren
id|__set_hae
c_func
(paren
id|new_hae
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
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
id|IDENT_ADDR
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
(paren
r_void
op_star
)paren
(paren
id|address
op_plus
id|IDENT_ADDR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Change addresses as seen by the kernel (virtual) to addresses as&n; * seen by a device (bus), and vice versa.&n; *&n; * Note that this only works for a limited range of kernel addresses,&n; * and very well may not span all memory.  Consider this interface &n; * deprecated in favour of the mapping functions in &lt;asm/pci.h&gt;.&n; */
r_extern
r_int
r_int
id|__direct_map_base
suffix:semicolon
r_extern
r_int
r_int
id|__direct_map_size
suffix:semicolon
DECL|function|virt_to_bus
r_static
r_inline
r_int
r_int
id|virt_to_bus
c_func
(paren
r_void
op_star
id|address
)paren
(brace
r_int
r_int
id|phys
op_assign
id|virt_to_phys
c_func
(paren
id|address
)paren
suffix:semicolon
r_int
r_int
id|bus
op_assign
id|phys
op_plus
id|__direct_map_base
suffix:semicolon
r_return
id|phys
op_le
id|__direct_map_size
ques
c_cond
id|bus
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|bus_to_virt
r_static
r_inline
r_void
op_star
id|bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_void
op_star
id|virt
suffix:semicolon
multiline_comment|/* This check is a sanity check but also ensures that bus address 0&n;&t;   maps to virtual address 0 which is useful to detect null pointers&n;&t;   (the NCR driver is much simpler if NULL pointers are preserved).  */
id|address
op_sub_assign
id|__direct_map_base
suffix:semicolon
id|virt
op_assign
id|phys_to_virt
c_func
(paren
id|address
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|address
op_le
l_int|0
ques
c_cond
l_int|NULL
suffix:colon
id|virt
suffix:semicolon
)brace
macro_line|#else /* !__KERNEL__ */
multiline_comment|/*&n; * Define actual functions in private name-space so it&squot;s easier to&n; * accommodate things like XFree or svgalib that like to define their&n; * own versions of inb etc.&n; */
r_extern
r_void
id|__sethae
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* syscall */
r_extern
r_void
id|_sethae
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* cached version */
macro_line|#endif /* !__KERNEL__ */
multiline_comment|/*&n; * There are different chipsets to interface the Alpha CPUs to the world.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_ALPHA_GENERIC
multiline_comment|/* In a generic kernel, we always go through the machine vector.  */
DECL|macro|__inb
macro_line|# define __inb(p)&t;alpha_mv.mv_inb((unsigned long)(p))
DECL|macro|__inw
macro_line|# define __inw(p)&t;alpha_mv.mv_inw((unsigned long)(p))
DECL|macro|__inl
macro_line|# define __inl(p)&t;alpha_mv.mv_inl((unsigned long)(p))
DECL|macro|__outb
macro_line|# define __outb(x,p)&t;alpha_mv.mv_outb((x),(unsigned long)(p))
DECL|macro|__outw
macro_line|# define __outw(x,p)&t;alpha_mv.mv_outw((x),(unsigned long)(p))
DECL|macro|__outl
macro_line|# define __outl(x,p)&t;alpha_mv.mv_outl((x),(unsigned long)(p))
DECL|macro|__readb
macro_line|# define __readb(a)&t;alpha_mv.mv_readb((unsigned long)(a))
DECL|macro|__readw
macro_line|# define __readw(a)&t;alpha_mv.mv_readw((unsigned long)(a))
DECL|macro|__readl
macro_line|# define __readl(a)&t;alpha_mv.mv_readl((unsigned long)(a))
DECL|macro|__readq
macro_line|# define __readq(a)&t;alpha_mv.mv_readq((unsigned long)(a))
DECL|macro|__writeb
macro_line|# define __writeb(v,a)&t;alpha_mv.mv_writeb((v),(unsigned long)(a))
DECL|macro|__writew
macro_line|# define __writew(v,a)&t;alpha_mv.mv_writew((v),(unsigned long)(a))
DECL|macro|__writel
macro_line|# define __writel(v,a)&t;alpha_mv.mv_writel((v),(unsigned long)(a))
DECL|macro|__writeq
macro_line|# define __writeq(v,a)&t;alpha_mv.mv_writeq((v),(unsigned long)(a))
DECL|macro|__ioremap
macro_line|# define __ioremap(a)&t;alpha_mv.mv_ioremap((unsigned long)(a))
DECL|macro|__is_ioaddr
macro_line|# define __is_ioaddr(a)&t;alpha_mv.mv_is_ioaddr((unsigned long)(a))
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
DECL|macro|__raw_readb
macro_line|# define __raw_readb&t;__readb
DECL|macro|__raw_readw
macro_line|# define __raw_readw&t;__readw
DECL|macro|__raw_readl
macro_line|# define __raw_readl&t;__readl
DECL|macro|__raw_readq
macro_line|# define __raw_readq&t;__readq
DECL|macro|__raw_writeb
macro_line|# define __raw_writeb&t;__writeb
DECL|macro|__raw_writew
macro_line|# define __raw_writew&t;__writew
DECL|macro|__raw_writel
macro_line|# define __raw_writel&t;__writel
DECL|macro|__raw_writeq
macro_line|# define __raw_writeq&t;__writeq
macro_line|#else
multiline_comment|/* Control how and what gets defined within the core logic headers.  */
DECL|macro|__WANT_IO_DEF
mdefine_line|#define __WANT_IO_DEF
macro_line|#if defined(CONFIG_ALPHA_APECS)
macro_line|# include &lt;asm/core_apecs.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_CIA)
macro_line|# include &lt;asm/core_cia.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_IRONGATE)
macro_line|# include &lt;asm/core_irongate.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_JENSEN)
macro_line|# include &lt;asm/jensen.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_LCA)
macro_line|# include &lt;asm/core_lca.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_MCPCIA)
macro_line|# include &lt;asm/core_mcpcia.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_POLARIS)
macro_line|# include &lt;asm/core_polaris.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_T2)
macro_line|# include &lt;asm/core_t2.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_TSUNAMI)
macro_line|# include &lt;asm/core_tsunami.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_TITAN)
macro_line|# include &lt;asm/core_titan.h&gt;
macro_line|#elif defined(CONFIG_ALPHA_WILDFIRE)
macro_line|# include &lt;asm/core_wildfire.h&gt;
macro_line|#else
macro_line|#error &quot;What system is this?&quot;
macro_line|#endif
DECL|macro|__WANT_IO_DEF
macro_line|#undef __WANT_IO_DEF
macro_line|#endif /* GENERIC */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * The convention used for inb/outb etc. is that names starting with&n; * two underscores are the inline versions, names starting with a&n; * single underscore are proper functions, and names starting with a&n; * letter are macros that map in some way to inline or proper function&n; * versions.  Not all that pretty, but before you change it, be sure&n; * to convince yourself that it won&squot;t break anything (in particular&n; * module support).&n; */
r_extern
r_int
r_int
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
r_int
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
r_int
r_int
id|_readq
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
r_extern
r_void
id|_writeq
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
macro_line|# define inb_p&t;&t;inb
macro_line|#endif
macro_line|#ifndef inw_p
DECL|macro|inw_p
macro_line|# define inw_p&t;&t;inw
macro_line|#endif
macro_line|#ifndef inl_p
DECL|macro|inl_p
macro_line|# define inl_p&t;&t;inl
macro_line|#endif
macro_line|#ifndef outb_p
DECL|macro|outb_p
macro_line|# define outb_p&t;&t;outb
macro_line|#endif
macro_line|#ifndef outw_p
DECL|macro|outw_p
macro_line|# define outw_p&t;&t;outw
macro_line|#endif
macro_line|#ifndef outl_p
DECL|macro|outl_p
macro_line|# define outl_p&t;&t;outl
macro_line|#endif
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
macro_line|#else 
multiline_comment|/* Userspace declarations.  */
r_extern
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
r_int
r_int
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
multiline_comment|/*&n; * On Alpha, we have the whole of I/O space mapped at all times, but&n; * at odd and sometimes discontinuous addresses.  Note that the &n; * discontinuities are all across busses, so we need not care for that&n; * for any one device.&n; *&n; * Map the I/O space address into the kernel&squot;s virtual address space.&n; */
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
id|__ioremap
c_func
(paren
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
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|ioremap
c_func
(paren
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/* Indirect back to the macros provided.  */
r_extern
r_int
r_int
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
r_int
r_int
id|___raw_readq
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
r_extern
r_void
id|___raw_writeq
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
macro_line|#ifdef __raw_readq
DECL|macro|readq
macro_line|# define readq(a)&t;({ unsigned long r_ = __raw_readq(a); mb(); r_; })
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
macro_line|#ifdef __raw_writeq
DECL|macro|writeq
macro_line|# define writeq(v,a)&t;({ __raw_writeq((v),(a)); mb(); })
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
macro_line|#ifndef __raw_readq
DECL|macro|__raw_readq
macro_line|# define __raw_readq(a)&t;___raw_readq((unsigned long)(a))
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
macro_line|#ifndef __raw_writeq
DECL|macro|__raw_writeq
macro_line|# define __raw_writeq(v,a)  ___raw_writeq((v),(unsigned long)(a))
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
macro_line|#ifndef readq
DECL|macro|readq
macro_line|# define readq(a)&t;_readq((unsigned long)(a))
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
macro_line|#ifndef writeq
DECL|macro|writeq
macro_line|# define writeq(v,a)&t;_writeq((v),(unsigned long)(a))
macro_line|#endif
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
id|_memset_c_io
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(to,from,len) &bslash;&n;  _memcpy_fromio((to),(unsigned long)(from),(len))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(to,from,len) &bslash;&n;  _memcpy_toio((unsigned long)(to),(from),(len))
DECL|macro|memset_io
mdefine_line|#define memset_io(addr,c,len) &bslash;&n;  _memset_c_io((unsigned long)(addr),0x0101010101010101UL*(u8)(c),(len))
DECL|macro|__HAVE_ARCH_MEMSETW_IO
mdefine_line|#define __HAVE_ARCH_MEMSETW_IO
DECL|macro|memsetw_io
mdefine_line|#define memsetw_io(addr,c,len) &bslash;&n;  _memset_c_io((unsigned long)(addr),0x0001000100010001UL*(u16)(c),(len))
multiline_comment|/*&n; * String versions of in/out ops:&n; */
r_extern
r_void
id|insb
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
multiline_comment|/*&n; * XXX - We don&squot;t have csum_partial_copy_fromio() yet, so we cheat here and &n; * just copy it. The net code will then do the checksum later. Presently &n; * only used by some shared memory 8390 Ethernet cards anyway.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(skb,src,len,unused) &bslash;&n;  memcpy_fromio((skb)-&gt;data,(src),(len))
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
multiline_comment|/*&n; * ISA space is mapped to some machine-specific location on Alpha.&n; * Call into the existing hooks to get the address translated.&n; */
DECL|macro|isa_readb
mdefine_line|#define isa_readb(a)&t;&t;&t;readb(__ioremap(a))
DECL|macro|isa_readw
mdefine_line|#define isa_readw(a)&t;&t;&t;readw(__ioremap(a))
DECL|macro|isa_readl
mdefine_line|#define isa_readl(a)&t;&t;&t;readl(__ioremap(a))
DECL|macro|isa_writeb
mdefine_line|#define isa_writeb(b,a)&t;&t;&t;writeb((b),__ioremap(a))
DECL|macro|isa_writew
mdefine_line|#define isa_writew(w,a)&t;&t;&t;writew((w),__ioremap(a))
DECL|macro|isa_writel
mdefine_line|#define isa_writel(l,a)&t;&t;&t;writel((l),__ioremap(a))
DECL|macro|isa_memset_io
mdefine_line|#define isa_memset_io(a,b,c)&t;&t;memset_io(__ioremap(a),(b),(c))
DECL|macro|isa_memcpy_fromio
mdefine_line|#define isa_memcpy_fromio(a,b,c)&t;memcpy_fromio((a),__ioremap(b),(c))
DECL|macro|isa_memcpy_toio
mdefine_line|#define isa_memcpy_toio(a,b,c)&t;&t;memcpy_toio(__ioremap(a),(b),(c))
multiline_comment|/*&n; * The Alpha Jensen hardware for some rather strange reason puts&n; * the RTC clock at 0x170 instead of 0x70. Probably due to some&n; * misguided idea about using 0x70 for NMI stuff.&n; *&n; * These defines will override the defaults when doing RTC queries&n; */
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|RTC_PORT
macro_line|# define RTC_PORT(x)&t;((x) + alpha_mv.rtc_port)
macro_line|#else
macro_line|# ifdef CONFIG_ALPHA_JENSEN
DECL|macro|RTC_PORT
macro_line|#  define RTC_PORT(x)&t;(0x170+(x))
macro_line|# else
DECL|macro|RTC_PORT
macro_line|#  define RTC_PORT(x)&t;(0x70 + (x))
macro_line|# endif
macro_line|#endif
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
multiline_comment|/* Nothing to do */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_IO_H */
eof
