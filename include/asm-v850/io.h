multiline_comment|/*&n; * include/asm-v850/io.h -- Misc I/O operations&n; *&n; *  Copyright (C) 2001,02,03,04  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03,04  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_IO_H__
DECL|macro|__V850_IO_H__
mdefine_line|#define __V850_IO_H__
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xFFFFFFFF
DECL|macro|readb
mdefine_line|#define readb(addr) &bslash;&n;  ({ unsigned char __v = (*(volatile unsigned char *) (addr)); __v; })
DECL|macro|readw
mdefine_line|#define readw(addr) &bslash;&n;  ({ unsigned short __v = (*(volatile unsigned short *) (addr)); __v; })
DECL|macro|readl
mdefine_line|#define readl(addr) &bslash;&n;  ({ unsigned long __v = (*(volatile unsigned long *) (addr)); __v; })
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(a) readb(a)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(a) readw(a)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(a) readl(a)
DECL|macro|writeb
mdefine_line|#define writeb(b, addr) &bslash;&n;  (void)((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b, addr) &bslash;&n;  (void)((*(volatile unsigned short *) (addr)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b, addr) &bslash;&n;  (void)((*(volatile unsigned int *) (addr)) = (b))
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
DECL|macro|inb
mdefine_line|#define inb(addr)&t;readb (addr)
DECL|macro|inw
mdefine_line|#define inw(addr)&t;readw (addr)
DECL|macro|inl
mdefine_line|#define inl(addr)&t;readl (addr)
DECL|macro|outb
mdefine_line|#define outb(x, addr)&t;((void) writeb (x, addr))
DECL|macro|outw
mdefine_line|#define outw(x, addr)&t;((void) writew (x, addr))
DECL|macro|outl
mdefine_line|#define outl(x, addr)&t;((void) writel (x, addr))
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;&t;inb((port))
DECL|macro|outb_p
mdefine_line|#define outb_p(val, port)&t;outb((val), (port))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)&t;&t;inw((port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val, port)&t;outw((val), (port))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)&t;&t;inl((port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val, port)&t;outl((val), (port))
DECL|function|insb
r_static
r_inline
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
(brace
r_int
r_char
op_star
id|p
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|p
op_increment
op_assign
id|inb
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|insw
r_static
r_inline
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
(brace
r_int
r_int
op_star
id|p
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|p
op_increment
op_assign
id|inw
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|insl
r_static
r_inline
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
(brace
r_int
r_int
op_star
id|p
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|p
op_increment
op_assign
id|inl
(paren
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|outsb
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
(brace
r_const
r_int
r_char
op_star
id|p
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|outb
(paren
op_star
id|p
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|outsw
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
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|outw
(paren
op_star
id|p
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|outsl
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
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|outl
(paren
op_star
id|p
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
DECL|macro|iounmap
mdefine_line|#define iounmap(addr)&t;&t;&t;&t;((void)0)
DECL|macro|ioremap
mdefine_line|#define ioremap(physaddr, size)&t;&t;&t;(physaddr)
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(physaddr, size)&t;&t;(physaddr)
DECL|macro|ioremap_writethrough
mdefine_line|#define ioremap_writethrough(physaddr, size)&t;(physaddr)
DECL|macro|ioremap_fullcache
mdefine_line|#define ioremap_fullcache(physaddr, size)&t;(physaddr)
DECL|macro|mmiowb
mdefine_line|#define mmiowb()
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)      ((page - mem_map) &lt;&lt; PAGE_SHIFT)
macro_line|#if 0
multiline_comment|/* This is really stupid; don&squot;t define it.  */
mdefine_line|#define page_to_bus(page)       page_to_phys (page)
macro_line|#endif
multiline_comment|/* Conversion between virtual and physical mappings.  */
DECL|macro|mm_ptov
mdefine_line|#define mm_ptov(addr)&t;&t;((void *)__phys_to_virt (addr))
DECL|macro|mm_vtop
mdefine_line|#define mm_vtop(addr)&t;&t;((unsigned long)__virt_to_phys (addr))
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(addr)&t;((void *)__phys_to_virt (addr))
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(addr)&t;((unsigned long)__virt_to_phys (addr))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(dst, src, len) memcpy (dst, (void *)src, len)
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(dst, src, len) memcpy ((void *)dst, src, len)
macro_line|#endif /* __V850_IO_H__ */
eof
