multiline_comment|/*&n; *  linux/include/asm-parisc/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the PARISC architecture specific IDE code.&n; */
macro_line|#ifndef __ASM_PARISC_IDE_H
DECL|macro|__ASM_PARISC_IDE_H
mdefine_line|#define __ASM_PARISC_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;2
macro_line|#endif
DECL|macro|ide_default_irq
mdefine_line|#define ide_default_irq(base) (0)
DECL|macro|ide_default_io_base
mdefine_line|#define ide_default_io_base(index) (0)
DECL|function|ide_init_hwif_ports
r_static
r_inline
r_void
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
r_int
r_int
id|data_port
comma
r_int
r_int
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
r_int
r_int
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
id|hw-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_plus
l_int|0x206
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
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;(0)
DECL|macro|ide_request_irq
mdefine_line|#define ide_request_irq(irq,hand,flg,dev,id)&t;request_irq((irq),(hand),(flg),(dev),(id))
DECL|macro|ide_free_irq
mdefine_line|#define ide_free_irq(irq,dev_id)&t;&t;free_irq((irq), (dev_id))
DECL|macro|ide_check_region
mdefine_line|#define ide_check_region(from,extent)&t;&t;check_region((from), (extent))
DECL|macro|ide_request_region
mdefine_line|#define ide_request_region(from,extent,name)&t;request_region((from), (extent), (name))
DECL|macro|ide_release_region
mdefine_line|#define ide_release_region(from,extent)&t;&t;release_region((from), (extent))
multiline_comment|/* Generic I/O and MEMIO string operations.  */
DECL|macro|__ide_insw
mdefine_line|#define __ide_insw&t;insw
DECL|macro|__ide_insl
mdefine_line|#define __ide_insl&t;insl
DECL|macro|__ide_outsw
mdefine_line|#define __ide_outsw&t;outsw
DECL|macro|__ide_outsl
mdefine_line|#define __ide_outsl&t;outsl
DECL|function|__ide_mm_insw
r_static
id|__inline__
r_void
id|__ide_mm_insw
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
id|u32
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
op_star
(paren
id|u16
op_star
)paren
id|addr
op_assign
id|__raw_readw
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
DECL|function|__ide_mm_insl
r_static
id|__inline__
r_void
id|__ide_mm_insl
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
id|u32
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
op_star
(paren
id|u32
op_star
)paren
id|addr
op_assign
id|__raw_readl
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
DECL|function|__ide_mm_outsw
r_static
id|__inline__
r_void
id|__ide_mm_outsw
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
id|u32
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
id|__raw_writew
c_func
(paren
op_star
(paren
id|u16
op_star
)paren
id|addr
comma
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
DECL|function|__ide_mm_outsl
r_static
id|__inline__
r_void
id|__ide_mm_outsl
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
id|u32
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
id|__raw_writel
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|addr
comma
id|port
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_PARISC_IDE_H */
eof
