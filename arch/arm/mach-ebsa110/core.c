multiline_comment|/*&n; *  linux/arch/arm/mach-ebsa110/core.c&n; *&n; *  Copyright (C) 1998-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Extra MM routines for the EBSA-110 architecture&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;&t;0xfe000000&t;/* read */
DECL|macro|IRQ_MSET
mdefine_line|#define IRQ_MSET&t;&t;0xfe000000&t;/* write */
DECL|macro|IRQ_STAT
mdefine_line|#define IRQ_STAT&t;&t;0xff000000&t;/* read */
DECL|macro|IRQ_MCLR
mdefine_line|#define IRQ_MCLR&t;&t;0xff000000&t;/* write */
DECL|function|ebsa110_mask_irq
r_static
r_void
id|ebsa110_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|__raw_writeb
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|IRQ_MCLR
)paren
suffix:semicolon
)brace
DECL|function|ebsa110_unmask_irq
r_static
r_void
id|ebsa110_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|__raw_writeb
c_func
(paren
l_int|1
op_lshift
id|irq
comma
id|IRQ_MSET
)paren
suffix:semicolon
)brace
DECL|variable|ebsa110_irq_chip
r_static
r_struct
id|irqchip
id|ebsa110_irq_chip
op_assign
(brace
dot
id|ack
op_assign
id|ebsa110_mask_irq
comma
dot
id|mask
op_assign
id|ebsa110_mask_irq
comma
dot
id|unmask
op_assign
id|ebsa110_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|ebsa110_init_irq
r_static
r_void
id|__init
id|ebsa110_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0xff
comma
id|IRQ_MCLR
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0x55
comma
id|IRQ_MSET
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0x00
comma
id|IRQ_MSET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__raw_readb
c_func
(paren
id|IRQ_MASK
)paren
op_ne
l_int|0x55
)paren
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0xff
comma
id|IRQ_MCLR
)paren
suffix:semicolon
multiline_comment|/* clear all interrupt enables */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|ebsa110_irq_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ebsa110_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*&n;&t; * sparse external-decode ISAIO space&n;&t; */
(brace
id|IRQ_STAT
comma
id|TRICK4_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* IRQ_STAT/IRQ_MCLR */
(brace
id|IRQ_MASK
comma
id|TRICK3_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* IRQ_MASK/IRQ_MSET */
(brace
id|SOFT_BASE
comma
id|TRICK1_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* SOFT_BASE */
(brace
id|PIT_BASE
comma
id|TRICK0_PHYS
comma
id|PGDIR_SIZE
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* PIT_BASE */
multiline_comment|/*&n;&t; * self-decode ISAIO space&n;&t; */
(brace
id|ISAIO_BASE
comma
id|ISAIO_PHYS
comma
id|ISAIO_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|ISAMEM_BASE
comma
id|ISAMEM_PHYS
comma
id|ISAMEM_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|ebsa110_map_io
r_static
r_void
id|__init
id|ebsa110_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|ebsa110_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|ebsa110_io_desc
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|EBSA110
comma
l_string|&quot;EBSA110&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
l_int|0xe0000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000400
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|0
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|2
)paren
id|SOFT_REBOOT
id|MAPIO
c_func
(paren
id|ebsa110_map_io
)paren
id|INITIRQ
c_func
(paren
id|ebsa110_init_irq
)paren
id|MACHINE_END
eof
