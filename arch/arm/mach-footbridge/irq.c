multiline_comment|/*&n; *  linux/arch/arm/mach-footbridge/irq.c&n; *&n; *  Copyright (C) 1996-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   22-Aug-1998 RMK&t;Restructured IRQ routines&n; *   03-Sep-1998 PJB&t;Merged CATS support&n; *   20-Jan-1998 RMK&t;Started merge of EBSA286, CATS and NetWinder&n; *   26-Jan-1999 PJB&t;Don&squot;t use IACK on CATS&n; *   16-Mar-1999 RMK&t;Added autodetect of ISA PICs&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
r_extern
r_void
id|__init
id|isa_init_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n; * Footbridge IRQ translation table&n; *  Converts from our IRQ numbers into FootBridge masks&n; */
DECL|variable|fb_irq_mask
r_static
r_const
r_int
id|fb_irq_mask
(braket
)braket
op_assign
(brace
id|IRQ_MASK_UART_RX
comma
multiline_comment|/*  0 */
id|IRQ_MASK_UART_TX
comma
multiline_comment|/*  1 */
id|IRQ_MASK_TIMER1
comma
multiline_comment|/*  2 */
id|IRQ_MASK_TIMER2
comma
multiline_comment|/*  3 */
id|IRQ_MASK_TIMER3
comma
multiline_comment|/*  4 */
id|IRQ_MASK_IN0
comma
multiline_comment|/*  5 */
id|IRQ_MASK_IN1
comma
multiline_comment|/*  6 */
id|IRQ_MASK_IN2
comma
multiline_comment|/*  7 */
id|IRQ_MASK_IN3
comma
multiline_comment|/*  8 */
id|IRQ_MASK_DOORBELLHOST
comma
multiline_comment|/*  9 */
id|IRQ_MASK_DMA1
comma
multiline_comment|/* 10 */
id|IRQ_MASK_DMA2
comma
multiline_comment|/* 11 */
id|IRQ_MASK_PCI
comma
multiline_comment|/* 12 */
id|IRQ_MASK_SDRAMPARITY
comma
multiline_comment|/* 13 */
id|IRQ_MASK_I2OINPOST
comma
multiline_comment|/* 14 */
id|IRQ_MASK_PCI_ABORT
comma
multiline_comment|/* 15 */
id|IRQ_MASK_PCI_SERR
comma
multiline_comment|/* 16 */
id|IRQ_MASK_DISCARD_TIMER
comma
multiline_comment|/* 17 */
id|IRQ_MASK_PCI_DPERR
comma
multiline_comment|/* 18 */
id|IRQ_MASK_PCI_PERR
comma
multiline_comment|/* 19 */
)brace
suffix:semicolon
DECL|function|fb_mask_irq
r_static
r_void
id|fb_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
op_star
id|CSR_IRQ_DISABLE
op_assign
id|fb_irq_mask
(braket
id|_DC21285_INR
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
)brace
DECL|function|fb_unmask_irq
r_static
r_void
id|fb_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
op_star
id|CSR_IRQ_ENABLE
op_assign
id|fb_irq_mask
(braket
id|_DC21285_INR
c_func
(paren
id|irq
)paren
)braket
suffix:semicolon
)brace
DECL|variable|fb_chip
r_static
r_struct
id|irqchip
id|fb_chip
op_assign
(brace
id|ack
suffix:colon
id|fb_mask_irq
comma
id|mask
suffix:colon
id|fb_mask_irq
comma
id|unmask
suffix:colon
id|fb_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|__fb_init_irq
r_static
r_void
id|__init
id|__fb_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * setup DC21285 IRQs&n;&t; */
op_star
id|CSR_IRQ_DISABLE
op_assign
op_minus
l_int|1
suffix:semicolon
op_star
id|CSR_FIQ_DISABLE
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|_DC21285_IRQ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|irq
OL
id|_DC21285_IRQ
c_func
(paren
l_int|20
)paren
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
id|fb_chip
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
DECL|function|footbridge_init_irq
r_void
id|__init
id|footbridge_init_irq
c_func
(paren
r_void
)paren
(brace
id|__fb_init_irq
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|footbridge_cfn_mode
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_ebsa285
c_func
(paren
)paren
)paren
multiline_comment|/* The following is dependent on which slot&n;&t;&t; * you plug the Southbridge card into.  We&n;&t;&t; * currently assume that you plug it into&n;&t;&t; * the right-hand most slot.&n;&t;&t; */
id|isa_init_irq
c_func
(paren
id|IRQ_PCI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_cats
c_func
(paren
)paren
)paren
id|isa_init_irq
c_func
(paren
id|IRQ_IN2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
id|isa_init_irq
c_func
(paren
id|IRQ_IN3
)paren
suffix:semicolon
)brace
eof
