multiline_comment|/*&n; * linux/arch/arm/mach-iop310/iop310-irq.c&n; *&n; * Generic IOP310 IRQ handling functionality&n; *&n; * Author:  Nicolas Pitre&n; * Copyright:   (C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Added IOP310 chipset and IQ80310 board demuxing, masking code. - DS&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
r_extern
r_void
id|xs80200_irq_mask
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xs80200_irq_unmask
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xs80200_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|do_IRQ
c_func
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|iop310_mask
id|u32
id|iop310_mask
op_assign
l_int|0
suffix:semicolon
r_static
r_void
DECL|function|iop310_irq_mask
id|iop310_irq_mask
(paren
r_int
r_int
id|irq
)paren
(brace
id|iop310_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IOP310_IRQ_OFS
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * No mask bits on the 80312, so we have to&n;&t; * mask everything from the outside!&n;&t; */
id|xs80200_irq_mask
c_func
(paren
id|IRQ_XS80200_EXTIRQ
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|iop310_irq_unmask
id|iop310_irq_unmask
(paren
r_int
r_int
id|irq
)paren
(brace
id|iop310_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IOP310_IRQ_OFS
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if all 80312 sources are unmasked now&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|iop310_mask
)paren
(brace
id|xs80200_irq_unmask
c_func
(paren
id|IRQ_XS80200_EXTIRQ
)paren
suffix:semicolon
)brace
)brace
DECL|function|iop310_irq_demux
r_void
id|iop310_irq_demux
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|fiq1isr
op_assign
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
id|IOP310_FIQ1ISR
)paren
suffix:semicolon
id|u32
id|fiq2isr
op_assign
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
id|IOP310_FIQ2ISR
)paren
suffix:semicolon
r_int
r_int
id|irqno
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fiq1isr
)paren
(brace
r_if
c_cond
(paren
id|fiq1isr
op_amp
l_int|0x1
)paren
(brace
id|irqno
op_assign
id|IRQ_IOP310_DMA0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fiq1isr
op_amp
l_int|0x2
)paren
(brace
id|irqno
op_assign
id|IRQ_IOP310_DMA1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fiq1isr
op_amp
l_int|0x4
)paren
(brace
id|irqno
op_assign
id|IRQ_IOP310_DMA2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fiq1isr
op_amp
l_int|0x10
)paren
(brace
id|irqno
op_assign
id|IRQ_IOP310_PMON
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fiq1isr
op_amp
l_int|0x20
)paren
(brace
id|irqno
op_assign
id|IRQ_IOP310_AAU
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|fiq2isr
op_amp
l_int|0x2
)paren
(brace
id|irqno
op_assign
id|IRQ_IOP310_I2C
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fiq2isr
op_amp
l_int|0x4
)paren
(brace
id|irqno
op_assign
id|IRQ_IOP310_MU
suffix:semicolon
)brace
)brace
id|do_IRQ
c_func
(paren
id|irqno
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|iop310_init_irq
r_void
id|__init
id|iop310_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IOP310_IRQ_OFS
suffix:semicolon
id|i
OL
id|NR_IOP310_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask_ack
op_assign
id|iop310_irq_mask
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask
op_assign
id|iop310_irq_mask
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|unmask
op_assign
id|iop310_irq_unmask
suffix:semicolon
)brace
id|xs80200_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
eof
