multiline_comment|/*&n; *  include/asm-s390/io.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/io.h&quot;&n; */
macro_line|#ifndef _S390_IO_H
DECL|macro|_S390_IO_H
mdefine_line|#define _S390_IO_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
DECL|macro|__io_virt
mdefine_line|#define __io_virt(x)            ((void *)(PAGE_OFFSET | (unsigned long)(x)))
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; * These are pretty trivial&n; */
DECL|function|virt_to_phys
r_extern
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
r_int
r_int
id|real_address
suffix:semicolon
id|__asm__
(paren
l_string|&quot;   lra    %0,0(%1)&bslash;n&quot;
l_string|&quot;   jz     0f&bslash;n&quot;
l_string|&quot;   sr     %0,%0&bslash;n&quot;
l_string|&quot;0:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|real_address
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|address
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|real_address
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_extern
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
id|__io_virt
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Change &quot;struct page&quot; to physical address.&n; */
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;((page - mem_map) &lt;&lt; PAGE_SHIFT)
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
r_extern
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
r_extern
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
multiline_comment|/*&n; * IO bus memory addresses are also 1:1 with the physical address&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) __io_virt(addr))
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile unsigned short *) __io_virt(addr))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile unsigned int *) __io_virt(addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) (*(volatile unsigned char *) __io_virt(addr) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) (*(volatile unsigned short *) __io_virt(addr) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) (*(volatile unsigned int *) __io_virt(addr) = (b))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)        memset(__io_virt(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)    memcpy((a),__io_virt(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)      memcpy(__io_virt(a),(b),(c))
DECL|macro|inb_p
mdefine_line|#define inb_p(addr) readb(addr)
DECL|macro|inb
mdefine_line|#define inb(addr) readb(addr)
DECL|macro|outb
mdefine_line|#define outb(x,addr) ((void) writeb(x,addr))
DECL|macro|outb_p
mdefine_line|#define outb_p(x,addr) outb(x,addr)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
