multiline_comment|/*&n; * Implement the default iomap interfaces&n; *&n; * (C) Copyright 2004 Linus Torvalds&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Read/write from/to an (offsettable) iomem cookie. It might be a PIO&n; * access or a MMIO access, these functions don&squot;t care. The info is&n; * encoded in the hardware mapping set up by the mapping functions&n; * (or the cookie itself, depending on implementation and hw).&n; *&n; * The generic routines don&squot;t assume any hardware mappings, and just&n; * encode the PIO/MMIO as part of the cookie. They coldly assume that&n; * the MMIO IO mappings are not in the low address range.&n; *&n; * Architectures for which this is not true can&squot;t use this generic&n; * implementation and should do their own copy.&n; */
macro_line|#ifndef HAVE_ARCH_PIO_SIZE
multiline_comment|/*&n; * We encode the physical PIO addresses (0-0xffff) into the&n; * pointer by offsetting them with a constant (0x10000) and&n; * assuming that all the low addresses are always PIO. That means&n; * we can do some sanity checks on the low bits, and don&squot;t&n; * need to just take things for granted.&n; */
DECL|macro|PIO_OFFSET
mdefine_line|#define PIO_OFFSET&t;0x10000UL
DECL|macro|PIO_MASK
mdefine_line|#define PIO_MASK&t;0x0ffffUL
DECL|macro|PIO_RESERVED
mdefine_line|#define PIO_RESERVED&t;0x40000UL
macro_line|#endif
multiline_comment|/*&n; * Ugly macros are a way of life.&n; */
DECL|macro|VERIFY_PIO
mdefine_line|#define VERIFY_PIO(port) BUG_ON((port &amp; ~PIO_MASK) != PIO_OFFSET)
DECL|macro|IO_COND
mdefine_line|#define IO_COND(addr, is_pio, is_mmio) do {&t;&t;&t;&bslash;&n;&t;unsigned long port = (unsigned long __force)addr;&t;&bslash;&n;&t;if (port &lt; PIO_RESERVED) {&t;&t;&t;&t;&bslash;&n;&t;&t;VERIFY_PIO(port);&t;&t;&t;&t;&bslash;&n;&t;&t;port &amp;= PIO_MASK;&t;&t;&t;&t;&bslash;&n;&t;&t;is_pio;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;is_mmio;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|function|ioread8
r_int
r_int
id|fastcall
id|ioread8
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|IO_COND
c_func
(paren
id|addr
comma
r_return
id|inb
c_func
(paren
id|port
)paren
comma
r_return
id|readb
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|ioread16
r_int
r_int
id|fastcall
id|ioread16
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|IO_COND
c_func
(paren
id|addr
comma
r_return
id|inw
c_func
(paren
id|port
)paren
comma
r_return
id|readw
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|ioread32
r_int
r_int
id|fastcall
id|ioread32
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|IO_COND
c_func
(paren
id|addr
comma
r_return
id|inl
c_func
(paren
id|port
)paren
comma
r_return
id|readl
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ioread8
id|EXPORT_SYMBOL
c_func
(paren
id|ioread8
)paren
suffix:semicolon
DECL|variable|ioread16
id|EXPORT_SYMBOL
c_func
(paren
id|ioread16
)paren
suffix:semicolon
DECL|variable|ioread32
id|EXPORT_SYMBOL
c_func
(paren
id|ioread32
)paren
suffix:semicolon
DECL|function|iowrite8
r_void
id|fastcall
id|iowrite8
c_func
(paren
id|u8
id|val
comma
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|IO_COND
c_func
(paren
id|addr
comma
id|outb
c_func
(paren
id|val
comma
id|port
)paren
comma
id|writeb
c_func
(paren
id|val
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|iowrite16
r_void
id|fastcall
id|iowrite16
c_func
(paren
id|u16
id|val
comma
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|IO_COND
c_func
(paren
id|addr
comma
id|outw
c_func
(paren
id|val
comma
id|port
)paren
comma
id|writew
c_func
(paren
id|val
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|iowrite32
r_void
id|fastcall
id|iowrite32
c_func
(paren
id|u32
id|val
comma
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|IO_COND
c_func
(paren
id|addr
comma
id|outl
c_func
(paren
id|val
comma
id|port
)paren
comma
id|writel
c_func
(paren
id|val
comma
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|variable|iowrite8
id|EXPORT_SYMBOL
c_func
(paren
id|iowrite8
)paren
suffix:semicolon
DECL|variable|iowrite16
id|EXPORT_SYMBOL
c_func
(paren
id|iowrite16
)paren
suffix:semicolon
DECL|variable|iowrite32
id|EXPORT_SYMBOL
c_func
(paren
id|iowrite32
)paren
suffix:semicolon
multiline_comment|/*&n; * These are the &quot;repeat MMIO read/write&quot; functions.&n; * Note the &quot;__raw&quot; accesses, since we don&squot;t want to&n; * convert to CPU byte order. We write in &quot;IO byte&n; * order&quot; (we also don&squot;t have IO barriers).&n; */
DECL|function|mmio_insb
r_static
r_inline
r_void
id|mmio_insb
c_func
(paren
r_void
id|__iomem
op_star
id|addr
comma
id|u8
op_star
id|dst
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|count
op_ge
l_int|0
)paren
(brace
id|u8
id|data
op_assign
id|__raw_readb
c_func
(paren
id|addr
)paren
suffix:semicolon
op_star
id|dst
op_assign
id|data
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
)brace
DECL|function|mmio_insw
r_static
r_inline
r_void
id|mmio_insw
c_func
(paren
r_void
id|__iomem
op_star
id|addr
comma
id|u16
op_star
id|dst
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|count
op_ge
l_int|0
)paren
(brace
id|u16
id|data
op_assign
id|__raw_readw
c_func
(paren
id|addr
)paren
suffix:semicolon
op_star
id|dst
op_assign
id|data
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
)brace
DECL|function|mmio_insl
r_static
r_inline
r_void
id|mmio_insl
c_func
(paren
r_void
id|__iomem
op_star
id|addr
comma
id|u32
op_star
id|dst
comma
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|count
op_ge
l_int|0
)paren
(brace
id|u32
id|data
op_assign
id|__raw_readl
c_func
(paren
id|addr
)paren
suffix:semicolon
op_star
id|dst
op_assign
id|data
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
)brace
DECL|function|mmio_outsb
r_static
r_inline
r_void
id|mmio_outsb
c_func
(paren
r_void
id|__iomem
op_star
id|addr
comma
r_const
id|u8
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
op_decrement
id|count
op_ge
l_int|0
)paren
(brace
id|__raw_writeb
c_func
(paren
op_star
id|src
comma
id|addr
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
DECL|function|mmio_outsw
r_static
r_inline
r_void
id|mmio_outsw
c_func
(paren
r_void
id|__iomem
op_star
id|addr
comma
r_const
id|u16
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
op_decrement
id|count
op_ge
l_int|0
)paren
(brace
id|__raw_writew
c_func
(paren
op_star
id|src
comma
id|addr
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
DECL|function|mmio_outsl
r_static
r_inline
r_void
id|mmio_outsl
c_func
(paren
r_void
id|__iomem
op_star
id|addr
comma
r_const
id|u32
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
op_decrement
id|count
op_ge
l_int|0
)paren
(brace
id|__raw_writel
c_func
(paren
op_star
id|src
comma
id|addr
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
DECL|function|ioread8_rep
r_void
id|fastcall
id|ioread8_rep
c_func
(paren
r_void
id|__iomem
op_star
id|addr
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
id|IO_COND
c_func
(paren
id|addr
comma
id|insb
c_func
(paren
id|port
comma
id|dst
comma
id|count
)paren
comma
id|mmio_insb
c_func
(paren
id|addr
comma
id|dst
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|function|ioread16_rep
r_void
id|fastcall
id|ioread16_rep
c_func
(paren
r_void
id|__iomem
op_star
id|addr
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
id|IO_COND
c_func
(paren
id|addr
comma
id|insw
c_func
(paren
id|port
comma
id|dst
comma
id|count
)paren
comma
id|mmio_insw
c_func
(paren
id|addr
comma
id|dst
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|function|ioread32_rep
r_void
id|fastcall
id|ioread32_rep
c_func
(paren
r_void
id|__iomem
op_star
id|addr
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
id|IO_COND
c_func
(paren
id|addr
comma
id|insl
c_func
(paren
id|port
comma
id|dst
comma
id|count
)paren
comma
id|mmio_insl
c_func
(paren
id|addr
comma
id|dst
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ioread8_rep
id|EXPORT_SYMBOL
c_func
(paren
id|ioread8_rep
)paren
suffix:semicolon
DECL|variable|ioread16_rep
id|EXPORT_SYMBOL
c_func
(paren
id|ioread16_rep
)paren
suffix:semicolon
DECL|variable|ioread32_rep
id|EXPORT_SYMBOL
c_func
(paren
id|ioread32_rep
)paren
suffix:semicolon
DECL|function|iowrite8_rep
r_void
id|fastcall
id|iowrite8_rep
c_func
(paren
r_void
id|__iomem
op_star
id|addr
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
id|IO_COND
c_func
(paren
id|addr
comma
id|outsb
c_func
(paren
id|port
comma
id|src
comma
id|count
)paren
comma
id|mmio_outsb
c_func
(paren
id|addr
comma
id|src
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|function|iowrite16_rep
r_void
id|fastcall
id|iowrite16_rep
c_func
(paren
r_void
id|__iomem
op_star
id|addr
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
id|IO_COND
c_func
(paren
id|addr
comma
id|outsw
c_func
(paren
id|port
comma
id|src
comma
id|count
)paren
comma
id|mmio_outsw
c_func
(paren
id|addr
comma
id|src
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|function|iowrite32_rep
r_void
id|fastcall
id|iowrite32_rep
c_func
(paren
r_void
id|__iomem
op_star
id|addr
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
id|IO_COND
c_func
(paren
id|addr
comma
id|outsl
c_func
(paren
id|port
comma
id|src
comma
id|count
)paren
comma
id|mmio_outsl
c_func
(paren
id|addr
comma
id|src
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|variable|iowrite8_rep
id|EXPORT_SYMBOL
c_func
(paren
id|iowrite8_rep
)paren
suffix:semicolon
DECL|variable|iowrite16_rep
id|EXPORT_SYMBOL
c_func
(paren
id|iowrite16_rep
)paren
suffix:semicolon
DECL|variable|iowrite32_rep
id|EXPORT_SYMBOL
c_func
(paren
id|iowrite32_rep
)paren
suffix:semicolon
multiline_comment|/* Create a virtual mapping cookie for an IO port range */
DECL|function|ioport_map
r_void
id|__iomem
op_star
id|ioport_map
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|port
OG
id|PIO_MASK
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
r_int
r_int
)paren
(paren
id|port
op_plus
id|PIO_OFFSET
)paren
suffix:semicolon
)brace
DECL|function|ioport_unmap
r_void
id|ioport_unmap
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
multiline_comment|/* Nothing to do */
)brace
DECL|variable|ioport_map
id|EXPORT_SYMBOL
c_func
(paren
id|ioport_map
)paren
suffix:semicolon
DECL|variable|ioport_unmap
id|EXPORT_SYMBOL
c_func
(paren
id|ioport_unmap
)paren
suffix:semicolon
multiline_comment|/* Create a virtual mapping cookie for a PCI BAR (memory or IO) */
DECL|function|pci_iomap
r_void
id|__iomem
op_star
id|pci_iomap
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|bar
comma
r_int
r_int
id|maxlen
)paren
(brace
r_int
r_int
id|start
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
id|bar
)paren
suffix:semicolon
r_int
r_int
id|len
op_assign
id|pci_resource_len
c_func
(paren
id|dev
comma
id|bar
)paren
suffix:semicolon
r_int
r_int
id|flags
op_assign
id|pci_resource_flags
c_func
(paren
id|dev
comma
id|bar
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
op_logical_neg
id|start
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|maxlen
op_logical_and
id|len
OG
id|maxlen
)paren
id|len
op_assign
id|maxlen
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IORESOURCE_IO
)paren
r_return
id|ioport_map
c_func
(paren
id|start
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|IORESOURCE_CACHEABLE
)paren
r_return
id|ioremap
c_func
(paren
id|start
comma
id|len
)paren
suffix:semicolon
r_return
id|ioremap_nocache
c_func
(paren
id|start
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* What? */
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_iounmap
r_void
id|pci_iounmap
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|IO_COND
c_func
(paren
id|addr
comma
multiline_comment|/* nothing */
comma
id|iounmap
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|variable|pci_iomap
id|EXPORT_SYMBOL
c_func
(paren
id|pci_iomap
)paren
suffix:semicolon
DECL|variable|pci_iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|pci_iounmap
)paren
suffix:semicolon
eof
