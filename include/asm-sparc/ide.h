multiline_comment|/* $Id: ide.h,v 1.7 2002/01/16 20:58:40 davem Exp $&n; * ide.h: SPARC PCI specific IDE glue.&n; *&n; * Copyright (C) 1997  David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998  Eddie C. Dost   (ecd@skynet.be)&n; * Adaptation from sparc64 version to sparc by Pete Zaitcev.&n; */
macro_line|#ifndef _SPARC_IDE_H
DECL|macro|_SPARC_IDE_H
mdefine_line|#define _SPARC_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hdreg.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
DECL|macro|MAX_HWIFS
macro_line|#undef  MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;2
DECL|macro|ide__sti
mdefine_line|#define&t;ide__sti()&t;__sti()
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
id|ide_ioreg_t
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Doing any sort of ioremap() here does not work&n; * because this function may be called with null aguments.&n; */
DECL|function|ide_init_hwif_ports
r_static
id|__inline__
r_void
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|reg
op_assign
id|data_port
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
suffix:semicolon
id|reg
op_add_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctrl_port
)paren
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctrl_port
suffix:semicolon
)brace
r_else
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
id|hw-&gt;io_ports
(braket
id|IDE_IRQ_OFFSET
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This registers the standard ports for this architecture with the IDE&n; * driver.&n; */
DECL|function|ide_init_default_hwifs
r_static
id|__inline__
r_void
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_PCI
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|index
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MAX_HWIFS
suffix:semicolon
id|index
op_increment
)paren
(brace
id|ide_init_hwif_ports
c_func
(paren
op_amp
id|hw
comma
id|ide_default_io_base
c_func
(paren
id|index
)paren
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|hw.irq
op_assign
id|ide_default_irq
c_func
(paren
id|ide_default_io_base
c_func
(paren
id|index
)paren
)paren
suffix:semicolon
id|ide_register_hw
c_func
(paren
op_amp
id|hw
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef  SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS 0
DECL|macro|HD_DATA
macro_line|#undef  HD_DATA
DECL|macro|HD_DATA
mdefine_line|#define HD_DATA ((ide_ioreg_t)0)
multiline_comment|/* From m68k code... */
macro_line|#ifdef insl
DECL|macro|insl
macro_line|#undef insl
macro_line|#endif
macro_line|#ifdef outsl
DECL|macro|outsl
macro_line|#undef outsl
macro_line|#endif
macro_line|#ifdef insw
DECL|macro|insw
macro_line|#undef insw
macro_line|#endif
macro_line|#ifdef outsw
DECL|macro|outsw
macro_line|#undef outsw
macro_line|#endif
DECL|macro|insl
mdefine_line|#define insl(data_reg, buffer, wcount) insw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|outsl
mdefine_line|#define outsl(data_reg, buffer, wcount) outsw(data_reg, buffer, (wcount)&lt;&lt;1)
DECL|macro|insw
mdefine_line|#define insw(port, buf, nr) ide_insw((port), (buf), (nr))
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, nr) ide_outsw((port), (buf), (nr))
DECL|function|ide_insw
r_static
id|__inline__
r_void
id|ide_insw
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
(brace
r_volatile
r_int
r_int
op_star
id|data_port
suffix:semicolon
multiline_comment|/* unsigned long end = (unsigned long)dst + (count &lt;&lt; 1); */
multiline_comment|/* P3 */
id|u16
op_star
id|ps
op_assign
id|dst
suffix:semicolon
id|u32
op_star
id|pi
suffix:semicolon
id|data_port
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|ps
)paren
op_amp
l_int|0x2
)paren
(brace
op_star
id|ps
op_increment
op_assign
op_star
id|data_port
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|pi
op_assign
(paren
id|u32
op_star
)paren
id|ps
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
l_int|2
)paren
(brace
id|u32
id|w
suffix:semicolon
id|w
op_assign
(paren
op_star
id|data_port
)paren
op_lshift
l_int|16
suffix:semicolon
id|w
op_or_assign
(paren
op_star
id|data_port
)paren
suffix:semicolon
op_star
id|pi
op_increment
op_assign
id|w
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|ps
op_assign
(paren
id|u16
op_star
)paren
id|pi
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
op_star
id|ps
op_increment
op_assign
op_star
id|data_port
suffix:semicolon
)brace
multiline_comment|/* __flush_dcache_range((unsigned long)dst, end); */
multiline_comment|/* P3 see hme */
)brace
DECL|function|ide_outsw
r_static
id|__inline__
r_void
id|ide_outsw
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
(brace
r_volatile
r_int
r_int
op_star
id|data_port
suffix:semicolon
multiline_comment|/* unsigned long end = (unsigned long)src + (count &lt;&lt; 1); */
r_const
id|u16
op_star
id|ps
op_assign
id|src
suffix:semicolon
r_const
id|u32
op_star
id|pi
suffix:semicolon
id|data_port
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|port
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|src
)paren
op_amp
l_int|0x2
)paren
(brace
op_star
id|data_port
op_assign
op_star
id|ps
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|pi
op_assign
(paren
r_const
id|u32
op_star
)paren
id|ps
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
l_int|2
)paren
(brace
id|u32
id|w
suffix:semicolon
id|w
op_assign
op_star
id|pi
op_increment
suffix:semicolon
op_star
id|data_port
op_assign
(paren
id|w
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|data_port
op_assign
id|w
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|ps
op_assign
(paren
r_const
id|u16
op_star
)paren
id|pi
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
op_star
id|data_port
op_assign
op_star
id|ps
suffix:semicolon
)brace
multiline_comment|/* __flush_dcache_range((unsigned long)src, end); */
multiline_comment|/* P3 see hme */
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC_IDE_H */
eof
