multiline_comment|/*&n; *  linux/include/asm-ppc/ide.h&n; *&n; *  Copyright (C) 1994-1996 Linus Torvalds &amp; authors */
multiline_comment|/*&n; *  This file contains the ppc architecture specific IDE code.&n; */
macro_line|#ifndef __ASMPPC_IDE_H
DECL|macro|__ASMPPC_IDE_H
mdefine_line|#define __ASMPPC_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;8
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
DECL|struct|ide_machdep_calls
r_struct
id|ide_machdep_calls
(brace
DECL|member|default_irq
r_int
(paren
op_star
id|default_irq
)paren
(paren
r_int
r_int
id|base
)paren
suffix:semicolon
DECL|member|default_io_base
r_int
r_int
(paren
op_star
id|default_io_base
)paren
(paren
r_int
id|index
)paren
suffix:semicolon
DECL|member|ide_init_hwif
r_void
(paren
op_star
id|ide_init_hwif
)paren
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
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ide_machdep_calls
id|ppc_ide_md
suffix:semicolon
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef&t;SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define&t;SUPPORT_SLOW_DATA_PORTS&t;0
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.default_irq
)paren
r_return
id|ppc_ide_md
dot
id|default_irq
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
r_int
r_int
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|ppc_ide_md.default_io_base
)paren
r_return
id|ppc_ide_md
dot
id|default_io_base
c_func
(paren
id|index
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is only used for PC-style IDE controllers (e.g. as on PReP)&n; * or for PCI IDE devices, not for other types of IDE interface such&n; * as the pmac IDE interfaces.&n; */
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
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
op_increment
suffix:semicolon
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
r_if
c_cond
(paren
id|ppc_ide_md.ide_init_hwif
op_ne
l_int|NULL
)paren
id|ppc_ide_md
dot
id|ide_init_hwif
c_func
(paren
id|hw
comma
id|data_port
comma
id|ctrl_port
comma
id|irq
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;(0)
macro_line|#else
DECL|macro|ide_init_default_irq
mdefine_line|#define ide_init_default_irq(base)&t;ide_default_irq(base)
macro_line|#endif
macro_line|#if (defined CONFIG_APUS || defined CONFIG_BLK_DEV_MPC8xx_IDE )
DECL|macro|IDE_ARCH_ACK_INTR
mdefine_line|#define IDE_ARCH_ACK_INTR  1
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(hwif) (hwif-&gt;hw.ack_intr ? hwif-&gt;hw.ack_intr(hwif) : 1)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMPPC_IDE_H */
eof
