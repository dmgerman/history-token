multiline_comment|/*&n; * linux/arch/sh/kernel/io_rts7751r2d.c&n; *&n; * Copyright (C) 2001  Ian da Silva, Jeremy Siegel&n; * Based largely on io_se.c.&n; *&n; * I/O routine for Renesas Technology sales RTS7751R2D.&n; *&n; * Initial version only to support LAN access; some&n; * placeholder code from io_rts7751r2d.c left in with the&n; * expectation of later SuperIO and PCMCIA access.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rts7751r2d/rts7751r2d.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;../../../drivers/pci/pci-sh7751.h&quot;
multiline_comment|/*&n; * The 7751R RTS7751R2D uses the built-in PCI controller (PCIC)&n; * of the 7751R processor, and has a SuperIO accessible via the PCI.&n; * The board also includes a PCMCIA controller on its memory bus,&n; * like the other Solution Engine boards.&n; */
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
DECL|function|port2adr
r_static
r_inline
r_int
r_int
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
(paren
l_int|0x1f0
op_le
id|port
op_logical_and
id|port
OL
l_int|0x1f8
)paren
op_logical_or
id|port
op_eq
l_int|0x3f6
)paren
r_if
c_cond
(paren
id|port
op_eq
l_int|0x3f6
)paren
r_return
(paren
id|PA_AREA5_IO
op_plus
l_int|0x80c
)paren
suffix:semicolon
r_else
r_return
(paren
id|PA_AREA5_IO
op_plus
l_int|0x1000
op_plus
(paren
(paren
id|port
op_minus
l_int|0x1f0
)paren
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_else
id|maybebadio
c_func
(paren
id|port2adr
comma
(paren
r_int
r_int
)paren
id|port
)paren
suffix:semicolon
r_return
id|port
suffix:semicolon
)brace
DECL|function|port88796l
r_static
r_inline
r_int
r_int
id|port88796l
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|flag
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
id|addr
op_assign
id|PA_AX88796L
op_plus
(paren
(paren
id|port
op_minus
id|AX88796L_IO_BASE
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
r_else
id|addr
op_assign
id|PA_AX88796L
op_plus
(paren
(paren
id|port
op_minus
id|AX88796L_IO_BASE
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|0x1000
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/* The 7751R RTS7751R2D seems to have everything hooked */
multiline_comment|/* up pretty normally (nothing on high-bytes only...) so this */
multiline_comment|/* shouldn&squot;t be needed */
DECL|function|shifted_port
r_static
r_inline
r_int
id|shifted_port
c_func
(paren
r_int
r_int
id|port
)paren
(brace
multiline_comment|/* For IDE registers, value is not shifted */
r_if
c_cond
(paren
(paren
l_int|0x1f0
op_le
id|port
op_logical_and
id|port
OL
l_int|0x1f8
)paren
op_logical_or
id|port
op_eq
l_int|0x3f6
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
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
macro_line|#if defined(CONFIG_NE2000) || defined(CONFIG_NE2000_MODULE)
DECL|macro|CHECK_AX88796L_PORT
mdefine_line|#define CHECK_AX88796L_PORT(port) &bslash;&n;  ((port &gt;= AX88796L_IO_BASE) &amp;&amp; (port &lt; (AX88796L_IO_BASE+0x20)))
macro_line|#else
DECL|macro|CHECK_AX88796L_PORT
mdefine_line|#define CHECK_AX88796L_PORT(port) (0)
macro_line|#endif
multiline_comment|/*&n; * General outline: remap really low stuff [eventually] to SuperIO,&n; * stuff in PCI IO space (at or above window at pci.h:PCIBIOS_MIN_IO)&n; * is mapped through the PCI IO window.  Stuff with high bits (PXSEG)&n; * should be way beyond the window, and is used  w/o translation for&n; * compatibility.&n; */
DECL|function|rts7751r2d_inb
r_int
r_char
id|rts7751r2d_inb
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
r_return
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|0
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
r_return
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|rts7751r2d_inb_p
r_int
r_char
id|rts7751r2d_inb_p
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|v
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|0
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
id|v
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
)paren
op_amp
l_int|0xff
)paren
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
DECL|function|rts7751r2d_inw
r_int
r_int
id|rts7751r2d_inw
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|maybebadio
c_func
(paren
id|inw
comma
id|port
)paren
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
DECL|function|rts7751r2d_inl
r_int
r_int
id|rts7751r2d_inl
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|maybebadio
c_func
(paren
id|inl
comma
id|port
)paren
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
DECL|function|rts7751r2d_outb
r_void
id|rts7751r2d_outb
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|0
)paren
)paren
op_assign
id|value
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
id|PCI_IOMAP
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
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
)paren
op_assign
id|value
suffix:semicolon
)brace
DECL|function|rts7751r2d_outb_p
r_void
id|rts7751r2d_outb_p
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|0
)paren
)paren
op_assign
id|value
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
id|PCI_IOMAP
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
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
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
DECL|function|rts7751r2d_outw
r_void
id|rts7751r2d_outw
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|maybebadio
c_func
(paren
id|outw
comma
id|port
)paren
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
id|PCI_IOMAP
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
DECL|function|rts7751r2d_outl
r_void
id|rts7751r2d_outl
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
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|maybebadio
c_func
(paren
id|outl
comma
id|port
)paren
suffix:semicolon
r_else
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
op_logical_or
id|shifted_port
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
id|PCI_IOMAP
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
id|outl
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|rts7751r2d_insb
r_void
id|rts7751r2d_insb
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
r_volatile
id|__u8
op_star
id|bp
suffix:semicolon
r_volatile
id|__u16
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
(brace
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
op_assign
op_star
id|p
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
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
op_logical_or
id|shifted_port
c_func
(paren
id|port
)paren
)paren
(brace
id|bp
op_assign
(paren
id|__u8
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
op_assign
op_star
id|bp
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
op_assign
op_star
id|p
op_amp
l_int|0xff
suffix:semicolon
)brace
)brace
DECL|function|rts7751r2d_insw
r_void
id|rts7751r2d_insw
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
r_volatile
id|__u16
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
id|p
op_assign
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
op_logical_or
id|shifted_port
c_func
(paren
id|port
)paren
)paren
id|p
op_assign
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
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|addr
)paren
op_increment
op_assign
op_star
id|p
suffix:semicolon
)brace
DECL|function|rts7751r2d_insl
r_void
id|rts7751r2d_insl
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
r_if
c_cond
(paren
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|maybebadio
c_func
(paren
id|insl
comma
id|port
)paren
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
op_logical_or
id|shifted_port
c_func
(paren
id|port
)paren
)paren
(brace
r_volatile
id|__u32
op_star
id|p
op_assign
(paren
id|__u32
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
(paren
(paren
id|__u32
op_star
)paren
id|addr
)paren
op_increment
op_assign
op_star
id|p
suffix:semicolon
)brace
r_else
id|maybebadio
c_func
(paren
id|insl
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|rts7751r2d_outsb
r_void
id|rts7751r2d_outsb
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
r_volatile
id|__u8
op_star
id|bp
suffix:semicolon
r_volatile
id|__u16
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
(brace
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|p
op_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
r_while
c_loop
(paren
id|count
op_decrement
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
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
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
op_logical_or
id|shifted_port
c_func
(paren
id|port
)paren
)paren
(brace
id|bp
op_assign
(paren
id|__u8
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|bp
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|p
op_assign
op_star
(paren
(paren
r_int
r_char
op_star
)paren
id|addr
)paren
op_increment
suffix:semicolon
)brace
)brace
DECL|function|rts7751r2d_outsw
r_void
id|rts7751r2d_outsw
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
r_volatile
id|__u16
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port88796l
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PXSEG
c_func
(paren
id|port
)paren
)paren
id|p
op_assign
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
op_logical_or
id|shifted_port
c_func
(paren
id|port
)paren
)paren
id|p
op_assign
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
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port2adr
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|p
op_assign
op_star
(paren
(paren
id|__u16
op_star
)paren
id|addr
)paren
op_increment
suffix:semicolon
)brace
DECL|function|rts7751r2d_outsl
r_void
id|rts7751r2d_outsl
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
r_if
c_cond
(paren
id|CHECK_AX88796L_PORT
c_func
(paren
id|port
)paren
)paren
id|maybebadio
c_func
(paren
id|outsl
comma
id|port
)paren
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
op_logical_or
id|shifted_port
c_func
(paren
id|port
)paren
)paren
(brace
r_volatile
id|__u32
op_star
id|p
op_assign
(paren
id|__u32
op_star
)paren
id|PCI_IOMAP
c_func
(paren
id|port
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|p
op_assign
op_star
(paren
(paren
id|__u32
op_star
)paren
id|addr
)paren
op_increment
suffix:semicolon
)brace
r_else
id|maybebadio
c_func
(paren
id|outsl
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|rts7751r2d_ioremap
r_void
op_star
id|rts7751r2d_ioremap
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
r_if
c_cond
(paren
id|offset
op_ge
l_int|0xfd000000
)paren
r_return
(paren
r_void
op_star
)paren
id|offset
suffix:semicolon
r_else
r_return
(paren
r_void
op_star
)paren
id|P2SEGADDR
c_func
(paren
id|offset
)paren
suffix:semicolon
)brace
DECL|variable|rts7751r2d_ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|rts7751r2d_ioremap
)paren
suffix:semicolon
DECL|function|rts7751r2d_isa_port2addr
r_int
r_int
id|rts7751r2d_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_return
id|port2adr
c_func
(paren
id|offset
)paren
suffix:semicolon
)brace
eof
