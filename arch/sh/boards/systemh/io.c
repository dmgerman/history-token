multiline_comment|/* &n; * linux/arch/sh/boards/systemh/io.c&n; *&n; * Copyright (C) 2001  Ian da Silva, Jeremy Siegel&n; * Based largely on io_se.c.&n; *&n; * I/O routine for Hitachi 7751 Systemh.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/systemh/7751systemh.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;../../drivers/pci/pci-sh7751.h&quot;
multiline_comment|/*&n; * The 7751 SystemH Engine uses the built-in PCI controller (PCIC)&n; * of the 7751 processor, and has a SuperIO accessible on its memory &n; * bus.&n; */
DECL|macro|PCIIOBR
mdefine_line|#define PCIIOBR&t;&t;(volatile long *)PCI_REG(SH7751_PCIIOBR)
DECL|macro|PCIMBR
mdefine_line|#define PCIMBR          (volatile long *)PCI_REG(SH7751_PCIMBR)
DECL|macro|PCI_IO_AREA
mdefine_line|#define PCI_IO_AREA&t;SH7751_PCI_IO_BASE
DECL|macro|PCI_MEM_AREA
mdefine_line|#define PCI_MEM_AREA&t;SH7751_PCI_CONFIG_BASE
DECL|macro|PCI_IOMAP
mdefine_line|#define PCI_IOMAP(adr)&t;(PCI_IO_AREA + (adr &amp; ~SH7751_PCIIOBR_MASK))
DECL|macro|ETHER_IOMAP
mdefine_line|#define ETHER_IOMAP(adr) (0xB3000000 + (adr)) /*map to 16bits access area&n;                                                of smc lan chip*/ 
DECL|macro|maybebadio
mdefine_line|#define maybebadio(name,port) &bslash;&n;  printk(&quot;bad PC-like io %s for port 0x%lx at 0x%08x&bslash;n&quot;, &bslash;&n;&t; #name, (port), (__u32) __builtin_return_address(0))
DECL|function|delay
r_static
r_inline
r_void
id|delay
c_func
(paren
r_void
)paren
(brace
id|ctrl_inw
c_func
(paren
l_int|0xa0000000
)paren
suffix:semicolon
)brace
r_static
r_inline
r_volatile
id|__u16
op_star
DECL|function|port2adr
id|port2adr
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_ge
l_int|0x2000
)paren
r_return
(paren
r_volatile
id|__u16
op_star
)paren
(paren
id|PA_MRSHPC
op_plus
(paren
id|port
op_minus
l_int|0x2000
)paren
)paren
suffix:semicolon
macro_line|#if 0
r_else
r_return
(paren
r_volatile
id|__u16
op_star
)paren
(paren
id|PA_SUPERIO
op_plus
(paren
id|port
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif
id|maybebadio
c_func
(paren
id|name
comma
(paren
r_int
r_int
)paren
id|port
)paren
suffix:semicolon
r_return
(paren
r_volatile
id|__u16
op_star
)paren
id|port
suffix:semicolon
)brace
multiline_comment|/* In case someone configures the kernel w/o PCI support: in that */
multiline_comment|/* scenario, don&squot;t ever bother to check for PCI-window addresses */
multiline_comment|/* NOTE: WINDOW CHECK MAY BE A BIT OFF, HIGH PCIBIOS_MIN_IO WRAPS? */
macro_line|#if defined(CONFIG_PCI)
DECL|macro|CHECK_SH7751_PCIIO
mdefine_line|#define CHECK_SH7751_PCIIO(port) &bslash;&n;  ((port &gt;= PCIBIOS_MIN_IO) &amp;&amp; (port &lt; (PCIBIOS_MIN_IO + SH7751_PCI_IO_SIZE)))
macro_line|#else
DECL|macro|CHECK_SH7751_PCIIO
mdefine_line|#define CHECK_SH7751_PCIIO(port) (0)
macro_line|#endif
multiline_comment|/*&n; * General outline: remap really low stuff [eventually] to SuperIO,&n; * stuff in PCI IO space (at or above window at pci.h:PCIBIOS_MIN_IO)&n; * is mapped through the PCI IO window.  Stuff with high bits (PXSEG)&n; * should be way beyond the window, and is used  w/o translation for&n; * compatibility.&n; */
DECL|function|sh7751systemh_inb
r_int
r_char
id|sh7751systemh_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|port
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_le
l_int|0x3F1
)paren
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ETHER_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
r_return
(paren
op_star
id|port2adr
c_func
(paren
id|port
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
DECL|function|sh7751systemh_inb_p
r_int
r_char
id|sh7751systemh_inb_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_char
id|v
suffix:semicolon
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|port
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_le
l_int|0x3F1
)paren
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ETHER_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
id|v
op_assign
(paren
op_star
id|port2adr
c_func
(paren
id|port
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|sh7751systemh_inw
r_int
r_int
id|sh7751systemh_inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_ge
l_int|0x2000
)paren
r_return
op_star
id|port2adr
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_le
l_int|0x3F1
)paren
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ETHER_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
id|maybebadio
c_func
(paren
id|inw
comma
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sh7751systemh_inl
r_int
r_int
id|sh7751systemh_inl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_ge
l_int|0x2000
)paren
r_return
op_star
id|port2adr
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_le
l_int|0x3F1
)paren
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ETHER_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
id|maybebadio
c_func
(paren
id|inl
comma
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sh7751systemh_outb
r_void
id|sh7751systemh_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|port
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
)paren
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_le
l_int|0x3F1
)paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ETHER_IOMAP
c_func
(paren
id|port
)paren
op_assign
id|value
suffix:semicolon
r_else
op_star
(paren
id|port2adr
c_func
(paren
id|port
)paren
)paren
op_assign
id|value
suffix:semicolon
)brace
DECL|function|sh7751systemh_outb_p
r_void
id|sh7751systemh_outb_p
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|port
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
)paren
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_le
l_int|0x3F1
)paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ETHER_IOMAP
c_func
(paren
id|port
)paren
op_assign
id|value
suffix:semicolon
r_else
op_star
(paren
id|port2adr
c_func
(paren
id|port
)paren
)paren
op_assign
id|value
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_outw
r_void
id|sh7751systemh_outw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
)paren
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_ge
l_int|0x2000
)paren
op_star
id|port2adr
c_func
(paren
id|port
)paren
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|port
op_le
l_int|0x3F1
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ETHER_IOMAP
c_func
(paren
id|port
)paren
op_assign
id|value
suffix:semicolon
r_else
id|maybebadio
c_func
(paren
id|outw
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_outl
r_void
id|sh7751systemh_outl
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port
op_assign
id|value
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CHECK_SH7751_PCIIO
c_func
(paren
id|port
)paren
)paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
)paren
op_assign
id|value
suffix:semicolon
r_else
id|maybebadio
c_func
(paren
id|outl
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_insb
r_void
id|sh7751systemh_insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
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
id|addr
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
id|sh7751systemh_inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_insw
r_void
id|sh7751systemh_insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
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
id|addr
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
id|sh7751systemh_inw
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_insl
r_void
id|sh7751systemh_insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
id|maybebadio
c_func
(paren
id|insl
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_outsb
r_void
id|sh7751systemh_outsb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
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
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|sh7751systemh_outb
c_func
(paren
op_star
id|p
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_outsw
r_void
id|sh7751systemh_outsw
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
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
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|sh7751systemh_outw
c_func
(paren
op_star
id|p
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|sh7751systemh_outsl
r_void
id|sh7751systemh_outsl
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
id|maybebadio
c_func
(paren
id|outsw
comma
id|port
)paren
suffix:semicolon
)brace
multiline_comment|/* For read/write calls, just copy generic (pass-thru); PCIMBR is  */
multiline_comment|/* already set up.  For a larger memory space, these would need to */
multiline_comment|/* reset PCIMBR as needed on a per-call basis...                   */
DECL|function|sh7751systemh_readb
r_int
r_char
id|sh7751systemh_readb
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
DECL|function|sh7751systemh_readw
r_int
r_int
id|sh7751systemh_readw
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
DECL|function|sh7751systemh_readl
r_int
r_int
id|sh7751systemh_readl
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
DECL|function|sh7751systemh_writeb
r_void
id|sh7751systemh_writeb
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
DECL|function|sh7751systemh_writew
r_void
id|sh7751systemh_writew
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
DECL|function|sh7751systemh_writel
r_void
id|sh7751systemh_writel
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
"&f;"
multiline_comment|/* Map ISA bus address to the real address. Only for PCMCIA.  */
multiline_comment|/* ISA page descriptor.  */
DECL|variable|sh_isa_memmap
r_static
id|__u32
id|sh_isa_memmap
(braket
l_int|256
)braket
suffix:semicolon
macro_line|#if 0
r_static
r_int
id|sh_isa_mmap
c_func
(paren
id|__u32
id|start
comma
id|__u32
id|length
comma
id|__u32
id|offset
)paren
(brace
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
l_int|0x100000
op_logical_or
(paren
id|start
op_amp
l_int|0xfff
)paren
op_logical_or
(paren
id|length
op_ne
l_int|0x1000
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|idx
op_assign
id|start
op_rshift
l_int|12
suffix:semicolon
id|sh_isa_memmap
(braket
id|idx
)braket
op_assign
l_int|0xb8000000
op_plus
(paren
id|offset
op_amp
op_complement
l_int|0xfff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sh_isa_mmap: start %x len %x offset %x (idx %x paddr %x)&bslash;n&quot;
comma
id|start
comma
id|length
comma
id|offset
comma
id|idx
comma
id|sh_isa_memmap
(braket
id|idx
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_int
r_int
DECL|function|sh7751systemh_isa_port2addr
id|sh7751systemh_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_int
id|idx
suffix:semicolon
id|idx
op_assign
(paren
id|offset
op_rshift
l_int|12
)paren
op_amp
l_int|0xff
suffix:semicolon
id|offset
op_and_assign
l_int|0xfff
suffix:semicolon
r_return
id|sh_isa_memmap
(braket
id|idx
)braket
op_plus
id|offset
suffix:semicolon
)brace
eof
