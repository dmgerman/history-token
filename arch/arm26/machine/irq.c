multiline_comment|/*&n; *  linux/arch/arm/mach-arc/irq.c&n; *&n; *  Copyright (C) 1996 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   24-09-1996&t;RMK&t;Created&n; *   10-10-1996&t;RMK&t;Brought up to date with arch-sa110eval&n; *   22-10-1996&t;RMK&t;Changed interrupt numbers &amp; uses new inb/outb macros&n; *   11-01-1998&t;RMK&t;Added mask_and_ack_irq&n; *   22-08-1998&t;RMK&t;Restructured IRQ routines&n; *   08-09-2002 IM&t;Brought up to date for 2.5&n; *   01-06-2003 JMA     Removed arc_fiq_chip&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/irqchip.h&gt;
macro_line|#include &lt;asm/ioc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_void
id|init_FIQ
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|a_clf
mdefine_line|#define a_clf()&t;clf()
DECL|macro|a_stf
mdefine_line|#define a_stf()&t;stf()
DECL|function|arc_ack_irq_a
r_static
r_void
id|arc_ack_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|a_clf
c_func
(paren
)paren
suffix:semicolon
id|val
op_assign
id|ioc_readb
c_func
(paren
id|IOC_IRQMASKA
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOC_IRQMASKA
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|mask
comma
id|IOC_IRQCLRA
)paren
suffix:semicolon
id|a_stf
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|arc_mask_irq_a
r_static
r_void
id|arc_mask_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|a_clf
c_func
(paren
)paren
suffix:semicolon
id|val
op_assign
id|ioc_readb
c_func
(paren
id|IOC_IRQMASKA
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOC_IRQMASKA
)paren
suffix:semicolon
id|a_stf
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|arc_unmask_irq_a
r_static
r_void
id|arc_unmask_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|a_clf
c_func
(paren
)paren
suffix:semicolon
id|val
op_assign
id|ioc_readb
c_func
(paren
id|IOC_IRQMASKA
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOC_IRQMASKA
)paren
suffix:semicolon
id|a_stf
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|arc_a_chip
r_static
r_struct
id|irqchip
id|arc_a_chip
op_assign
(brace
dot
id|ack
op_assign
id|arc_ack_irq_a
comma
dot
id|mask
op_assign
id|arc_mask_irq_a
comma
dot
id|unmask
op_assign
id|arc_unmask_irq_a
comma
)brace
suffix:semicolon
DECL|function|arc_mask_irq_b
r_static
r_void
id|arc_mask_irq_b
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|ioc_readb
c_func
(paren
id|IOC_IRQMASKB
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOC_IRQMASKB
)paren
suffix:semicolon
)brace
DECL|function|arc_unmask_irq_b
r_static
r_void
id|arc_unmask_irq_b
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|ioc_readb
c_func
(paren
id|IOC_IRQMASKB
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOC_IRQMASKB
)paren
suffix:semicolon
)brace
DECL|variable|arc_b_chip
r_static
r_struct
id|irqchip
id|arc_b_chip
op_assign
(brace
dot
id|ack
op_assign
id|arc_mask_irq_b
comma
dot
id|mask
op_assign
id|arc_mask_irq_b
comma
dot
id|unmask
op_assign
id|arc_unmask_irq_b
comma
)brace
suffix:semicolon
multiline_comment|/* FIXME - JMA none of these functions are used in arm26 currently&n;static void arc_mask_irq_fiq(unsigned int irq)&n;{&n;&t;unsigned int val, mask;&n;&n;&t;mask = 1 &lt;&lt; (irq &amp; 7);&n;&t;val = ioc_readb(IOC_FIQMASK);&n;&t;ioc_writeb(val &amp; ~mask, IOC_FIQMASK);&n;}&n;&n;static void arc_unmask_irq_fiq(unsigned int irq)&n;{&n;&t;unsigned int val, mask;&n;&n;&t;mask = 1 &lt;&lt; (irq &amp; 7);&n;&t;val = ioc_readb(IOC_FIQMASK);&n;&t;ioc_writeb(val | mask, IOC_FIQMASK);&n;}&n;&n;static struct irqchip arc_fiq_chip = {&n;        .ack    = arc_mask_irq_fiq,&n;        .mask   = arc_mask_irq_fiq,&n;        .unmask = arc_unmask_irq_fiq,&n;};&n;*/
DECL|function|arc_init_irq
r_void
id|__init
id|arc_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
comma
id|flags
suffix:semicolon
multiline_comment|/* Disable all IOC interrupt sources */
id|ioc_writeb
c_func
(paren
l_int|0
comma
id|IOC_IRQMASKA
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
l_int|0
comma
id|IOC_IRQMASKB
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
l_int|0
comma
id|IOC_FIQMASK
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
id|flags
op_assign
id|IRQF_VALID
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_le
l_int|6
op_logical_or
(paren
id|irq
op_ge
l_int|9
op_logical_and
id|irq
op_le
l_int|15
)paren
)paren
id|flags
op_or_assign
id|IRQF_PROBE
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|IRQ_KEYBOARDTX
)paren
id|flags
op_or_assign
id|IRQF_NOAUTOEN
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|7
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|arc_a_chip
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
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
dot
dot
dot
l_int|15
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|arc_b_chip
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
id|flags
)paren
suffix:semicolon
multiline_comment|/*&t;&t;case 64 ... 72:&n;&t;&t;&t;set_irq_chip(irq, &amp;arc_fiq_chip);&n;                        set_irq_flags(irq, flags);&n;&t;&t;&t;break;&n;*/
)brace
)brace
id|irq_desc
(braket
id|IRQ_KEYBOARDTX
)braket
dot
id|noautoenable
op_assign
l_int|1
suffix:semicolon
id|init_FIQ
c_func
(paren
)paren
suffix:semicolon
)brace
eof
