macro_line|#ifndef _ASM_IO_H
DECL|macro|_ASM_IO_H
mdefine_line|#define _ASM_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/gsc.h&gt;
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(a) ((unsigned long)__pa(a))
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(a) __va(a)
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
DECL|macro|inb_p
mdefine_line|#define inb_p inb
DECL|macro|inw_p
mdefine_line|#define inw_p inw
DECL|macro|inl_p
mdefine_line|#define inl_p inl
DECL|macro|outb_p
mdefine_line|#define outb_p outb
DECL|macro|outw_p
mdefine_line|#define outw_p outw
DECL|macro|outl_p
mdefine_line|#define outl_p outl
DECL|macro|readb
mdefine_line|#define readb gsc_readb
DECL|macro|readw
mdefine_line|#define readw gsc_readw
DECL|macro|readl
mdefine_line|#define readl gsc_readl
DECL|macro|writeb
mdefine_line|#define writeb gsc_writeb
DECL|macro|writew
mdefine_line|#define writew gsc_writew
DECL|macro|writel
mdefine_line|#define writel gsc_writel
macro_line|#if defined(CONFIG_PCI) || defined(CONFIG_ISA)
multiline_comment|/*&n; *&t;So we get clear link errors &n; */
r_extern
id|u8
id|inb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
id|u16
id|inw
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
id|u32
id|inl
c_func
(paren
r_int
r_int
id|addr
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
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|outw
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
id|outl
c_func
(paren
id|u32
id|b
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|function|memcpy_toio
r_static
r_inline
r_void
id|memcpy_toio
c_func
(paren
r_void
op_star
id|dest
comma
r_void
op_star
id|src
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|writeb
c_func
(paren
op_star
(paren
(paren
r_char
op_star
)paren
id|src
)paren
op_increment
comma
(paren
r_char
op_star
)paren
id|dest
op_increment
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* IO Port space is :      BBiiii   where BB is HBA number. */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0x00ffffff
multiline_comment|/* Right now we don&squot;t support Dino-on-a-card and V class which do PCI MMIO&n; * through address/data registers. */
DECL|macro|ioremap
mdefine_line|#define ioremap(__offset, __size)&t;((void *)(__offset))
DECL|macro|iounmap
mdefine_line|#define iounmap(__addr)
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { flush_kernel_dcache_range(_start,_size); } while(0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { flush_kernel_dcache_range(_start,_size); } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { flush_kernel_dcache_range(_start,_size); } while (0)
macro_line|#endif
eof
