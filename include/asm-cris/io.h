macro_line|#ifndef _ASM_CRIS_IO_H
DECL|macro|_ASM_CRIS_IO_H
mdefine_line|#define _ASM_CRIS_IO_H
macro_line|#include &lt;asm/page.h&gt;   /* for __va, __pa */
macro_line|#include &lt;asm/arch/io.h&gt;
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
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
r_return
id|__pa
c_func
(paren
id|address
)paren
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
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the CRIS architecture, we just read/write the&n; * memory location directly.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) (addr))
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile unsigned short *) (addr))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile unsigned int *) (addr))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb readb
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw readw
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl readl
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) ((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) ((*(volatile unsigned short *) (addr)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) ((*(volatile unsigned int *) (addr)) = (b))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb writeb
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew writew
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel writel
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
multiline_comment|/*&n; * Again, CRIS does not require mem IO specific function.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(a,b,c,d)&t;eth_copy_and_sum((a),(void *)(b),(c),(d))
multiline_comment|/* The following is junk needed for the arch-independent code but which&n; * we never use in the CRIS port&n; */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
DECL|macro|inb
mdefine_line|#define inb(x) (0)
DECL|macro|outb
mdefine_line|#define outb(x,y)
DECL|macro|outw
mdefine_line|#define outw(x,y)
DECL|macro|outl
mdefine_line|#define outl(x,y)
DECL|macro|insb
mdefine_line|#define insb(x,y,z)
DECL|macro|insw
mdefine_line|#define insw(x,y,z)
DECL|macro|insl
mdefine_line|#define insl(x,y,z)
DECL|macro|outsb
mdefine_line|#define outsb(x,y,z)
DECL|macro|outsw
mdefine_line|#define outsw(x,y,z)
DECL|macro|outsl
mdefine_line|#define outsl(x,y,z)
macro_line|#endif
eof
