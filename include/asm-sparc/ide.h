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
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
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
multiline_comment|/*&n; * The following is not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif)&t;&t;(1)
multiline_comment|/* XXX Known to be broken.  Axboe will fix the problems this&n; * XXX has by making separate IN/OUT macros for IDE_DATA&n; * XXX register and rest of IDE regs and also using&n; * XXX ide_ioreg_t instead of u32 for ports. -DaveM&n; */
DECL|macro|HAVE_ARCH_IN_BYTE
mdefine_line|#define HAVE_ARCH_IN_BYTE
DECL|macro|IN_BYTE
mdefine_line|#define IN_BYTE(p)&t;&t;(*((volatile u8 *)(p)))
DECL|macro|IN_WORD
mdefine_line|#define IN_WORD(p)&t;&t;(*((volatile u16 *)(p)))
DECL|macro|IN_LONG
mdefine_line|#define IN_LONG(p)&t;&t;(*((volatile u32 *)(p)))
DECL|macro|IN_BYTE_P
mdefine_line|#define IN_BYTE_P&t;&t;IN_BYTE
DECL|macro|IN_WORD_P
mdefine_line|#define IN_WORD_P&t;&t;IN_WORD
DECL|macro|IN_LONG_P
mdefine_line|#define IN_LONG_P&t;&t;IN_LONG
DECL|macro|HAVE_ARCH_OUT_BYTE
mdefine_line|#define HAVE_ARCH_OUT_BYTE
DECL|macro|OUT_BYTE
mdefine_line|#define OUT_BYTE(b,p)&t;&t;((*((volatile u8 *)(p))) = (b))
DECL|macro|OUT_WORD
mdefine_line|#define OUT_WORD(w,p)&t;&t;((*((volatile u16 *)(p))) = (w))
DECL|macro|OUT_LONG
mdefine_line|#define OUT_LONG(l,p)&t;&t;((*((volatile u32 *)(p))) = (l))
DECL|macro|OUT_BYTE_P
mdefine_line|#define OUT_BYTE_P&t;&t;OUT_BYTE
DECL|macro|OUT_WORD_P
mdefine_line|#define OUT_WORD_P&t;&t;OUT_WORD
DECL|macro|OUT_LONG_P
mdefine_line|#define OUT_LONG_P&t;&t;OUT_LONG
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC_IDE_H */
eof
