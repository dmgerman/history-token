macro_line|#ifndef __ALPHA_POLARIS__H__
DECL|macro|__ALPHA_POLARIS__H__
mdefine_line|#define __ALPHA_POLARIS__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * POLARIS is the internal name for a core logic chipset which provides&n; * memory controller and PCI access for the 21164PC chip based systems.&n; *&n; * This file is based on:&n; *&n; * Polaris System Controller&n; * Device Functional Specification&n; * 22-Jan-98&n; * Rev. 4.2&n; *&n; */
multiline_comment|/* Polaris memory regions */
DECL|macro|POLARIS_SPARSE_MEM_BASE
mdefine_line|#define POLARIS_SPARSE_MEM_BASE&t;&t;(IDENT_ADDR + 0xf800000000)
DECL|macro|POLARIS_DENSE_MEM_BASE
mdefine_line|#define POLARIS_DENSE_MEM_BASE&t;&t;(IDENT_ADDR + 0xf900000000)
DECL|macro|POLARIS_SPARSE_IO_BASE
mdefine_line|#define POLARIS_SPARSE_IO_BASE&t;&t;(IDENT_ADDR + 0xf980000000)
DECL|macro|POLARIS_SPARSE_CONFIG_BASE
mdefine_line|#define POLARIS_SPARSE_CONFIG_BASE&t;(IDENT_ADDR + 0xf9c0000000)
DECL|macro|POLARIS_IACK_BASE
mdefine_line|#define POLARIS_IACK_BASE&t;&t;(IDENT_ADDR + 0xf9f8000000)
DECL|macro|POLARIS_DENSE_IO_BASE
mdefine_line|#define POLARIS_DENSE_IO_BASE&t;&t;(IDENT_ADDR + 0xf9fc000000)
DECL|macro|POLARIS_DENSE_CONFIG_BASE
mdefine_line|#define POLARIS_DENSE_CONFIG_BASE&t;(IDENT_ADDR + 0xf9fe000000)
DECL|macro|POLARIS_IACK_SC
mdefine_line|#define POLARIS_IACK_SC&t;&t;&t;POLARIS_IACK_BASE
multiline_comment|/* The Polaris command/status registers live in PCI Config space for&n; * bus 0/device 0.  As such, they may be bytes, words, or doublewords.&n; */
DECL|macro|POLARIS_W_VENID
mdefine_line|#define POLARIS_W_VENID&t;&t;(POLARIS_DENSE_CONFIG_BASE)
DECL|macro|POLARIS_W_DEVID
mdefine_line|#define POLARIS_W_DEVID&t;&t;(POLARIS_DENSE_CONFIG_BASE+2)
DECL|macro|POLARIS_W_CMD
mdefine_line|#define POLARIS_W_CMD&t;&t;(POLARIS_DENSE_CONFIG_BASE+4)
DECL|macro|POLARIS_W_STATUS
mdefine_line|#define POLARIS_W_STATUS&t;(POLARIS_DENSE_CONFIG_BASE+6)
multiline_comment|/*&n; * Data structure for handling POLARIS machine checks:&n; */
DECL|struct|el_POLARIS_sysdata_mcheck
r_struct
id|el_POLARIS_sysdata_mcheck
(brace
DECL|member|psc_status
id|u_long
id|psc_status
suffix:semicolon
DECL|member|psc_pcictl0
id|u_long
id|psc_pcictl0
suffix:semicolon
DECL|member|psc_pcictl1
id|u_long
id|psc_pcictl1
suffix:semicolon
DECL|member|psc_pcictl2
id|u_long
id|psc_pcictl2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * POLARIS, the PCI/memory support chipset for the PCA56 (21164PC)&n; * processors, can use either a sparse address  mapping scheme, or the &n; * so-called byte-word PCI address space, to get at PCI memory and I/O.&n; *&n; * However, we will support only the BWX form.&n; */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int  *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long  *
DECL|function|polaris_inb
id|__EXTERN_INLINE
r_int
r_int
id|polaris_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* ??? I wish I could get rid of this.  But there&squot;s no ioremap&n;&t;   equivalent for I/O space.  PCI I/O can be forced into the&n;&t;   POLARIS I/O region, but that doesn&squot;t take care of legacy&n;&t;   ISA crap.  */
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_outb
id|__EXTERN_INLINE
r_void
id|polaris_outb
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
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_inw
id|__EXTERN_INLINE
r_int
r_int
id|polaris_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_outw
id|__EXTERN_INLINE
r_void
id|polaris_outw
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
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_inl
id|__EXTERN_INLINE
r_int
r_int
id|polaris_inl
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
id|vuip
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
suffix:semicolon
)brace
DECL|function|polaris_outl
id|__EXTERN_INLINE
r_void
id|polaris_outl
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
id|vuip
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.  Polaris allows all accesses (byte/word&n; * as well as long/quad) to be done through dense space.&n; *&n; * We will only support DENSE access via BWX insns.&n; */
DECL|function|polaris_readb
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|polaris_readw
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|polaris_readl
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readl
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
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|polaris_readq
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readq
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
id|vulp
)paren
id|addr
suffix:semicolon
)brace
DECL|function|polaris_writeb
id|__EXTERN_INLINE
r_void
id|polaris_writeb
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
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|polaris_writew
id|__EXTERN_INLINE
r_void
id|polaris_writew
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
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|polaris_writel
id|__EXTERN_INLINE
r_void
id|polaris_writel
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
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|polaris_writeq
id|__EXTERN_INLINE
r_void
id|polaris_writeq
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
id|vulp
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|polaris_ioremap
id|__EXTERN_INLINE
r_int
r_int
id|polaris_ioremap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
suffix:semicolon
)brace
DECL|function|polaris_is_ioaddr
id|__EXTERN_INLINE
r_int
id|polaris_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|POLARIS_SPARSE_MEM_BASE
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
mdefine_line|#define __inb(p)&t;&t;polaris_inb((unsigned long)(p))
DECL|macro|__inw
mdefine_line|#define __inw(p)&t;&t;polaris_inw((unsigned long)(p))
DECL|macro|__inl
mdefine_line|#define __inl(p)&t;&t;polaris_inl((unsigned long)(p))
DECL|macro|__outb
mdefine_line|#define __outb(x,p)&t;&t;polaris_outb((x),(unsigned long)(p))
DECL|macro|__outw
mdefine_line|#define __outw(x,p)&t;&t;polaris_outw((x),(unsigned long)(p))
DECL|macro|__outl
mdefine_line|#define __outl(x,p)&t;&t;polaris_outl((x),(unsigned long)(p))
DECL|macro|__readb
mdefine_line|#define __readb(a)&t;&t;polaris_readb((unsigned long)(a))
DECL|macro|__readw
mdefine_line|#define __readw(a)&t;&t;polaris_readw((unsigned long)(a))
DECL|macro|__readl
mdefine_line|#define __readl(a)&t;&t;polaris_readl((unsigned long)(a))
DECL|macro|__readq
mdefine_line|#define __readq(a)&t;&t;polaris_readq((unsigned long)(a))
DECL|macro|__writeb
mdefine_line|#define __writeb(x,a)&t;&t;polaris_writeb((x),(unsigned long)(a))
DECL|macro|__writew
mdefine_line|#define __writew(x,a)&t;&t;polaris_writew((x),(unsigned long)(a))
DECL|macro|__writel
mdefine_line|#define __writel(x,a)&t;&t;polaris_writel((x),(unsigned long)(a))
DECL|macro|__writeq
mdefine_line|#define __writeq(x,a)&t;&t;polaris_writeq((x),(unsigned long)(a))
DECL|macro|__ioremap
mdefine_line|#define __ioremap(a)&t;&t;polaris_ioremap((unsigned long)(a))
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr(a)&t;&t;polaris_is_ioaddr((unsigned long)(a))
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;&t;__inb(p)
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;&t;__inw(p)
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;&t;__inl(p)
DECL|macro|outb
mdefine_line|#define outb(x,p)&t;&t;__outb((x),(p))
DECL|macro|outw
mdefine_line|#define outw(x,p)&t;&t;__outw((x),(p))
DECL|macro|outl
mdefine_line|#define outl(x,p)&t;&t;__outl((x),(p))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)&t;&t;__readb(a)
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)&t;&t;__readw(a)
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;__readl(a)
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a)&t;&t;__readq(a)
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v,a)&t;__writeb((v),(a))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)&t;__writew((v),(a))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;__writel((v),(a))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v,a)&t;__writeq((v),(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_POLARIS__H__ */
eof
