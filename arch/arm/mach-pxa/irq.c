multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/irq.c&n; *&n; *  Generic PXA IRQ handling, GPIO IRQ demultiplexing, etc.&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/*&n; * This is for IRQs known as PXA_IRQ([8...31]).&n; */
DECL|function|pxa_mask_irq
r_static
r_void
id|pxa_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ICMR
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_plus
id|PXA_IRQ_SKIP
)paren
)paren
suffix:semicolon
)brace
DECL|function|pxa_unmask_irq
r_static
r_void
id|pxa_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ICMR
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_plus
id|PXA_IRQ_SKIP
)paren
)paren
suffix:semicolon
)brace
DECL|variable|pxa_internal_chip
r_static
r_struct
id|irqchip
id|pxa_internal_chip
op_assign
(brace
dot
id|ack
op_assign
id|pxa_mask_irq
comma
dot
id|mask
op_assign
id|pxa_mask_irq
comma
dot
id|unmask
op_assign
id|pxa_unmask_irq
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * PXA GPIO edge detection for IRQs:&n; * IRQs are generated on Falling-Edge, Rising-Edge, or both.&n; * Use this instead of directly setting GRER/GFER.&n; */
DECL|variable|GPIO_IRQ_rising_edge
r_static
r_int
id|GPIO_IRQ_rising_edge
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|GPIO_IRQ_falling_edge
r_static
r_int
id|GPIO_IRQ_falling_edge
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|GPIO_IRQ_mask
r_static
r_int
id|GPIO_IRQ_mask
(braket
l_int|3
)braket
suffix:semicolon
DECL|function|pxa_gpio_irq_type
r_static
r_int
id|pxa_gpio_irq_type
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|type
)paren
(brace
r_int
id|gpio
comma
id|idx
suffix:semicolon
id|gpio
op_assign
id|irq
op_minus
(paren
(paren
id|irq
op_ge
id|IRQ_GPIO
c_func
(paren
l_int|2
)paren
)paren
ques
c_cond
id|IRQ_GPIO
c_func
(paren
l_int|2
)paren
op_plus
l_int|2
suffix:colon
id|IRQ_GPIO
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;IRQ%d (GPIO%d): &quot;
comma
id|irq
comma
id|gpio
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|gpio
op_or
id|GPIO_IN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|__IRQT_RISEDGE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rising &quot;
)paren
suffix:semicolon
id|__set_bit
(paren
id|gpio
comma
id|GPIO_IRQ_rising_edge
)paren
suffix:semicolon
)brace
r_else
id|__clear_bit
(paren
id|gpio
comma
id|GPIO_IRQ_rising_edge
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|__IRQT_FALEDGE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;falling &quot;
)paren
suffix:semicolon
id|__set_bit
(paren
id|gpio
comma
id|GPIO_IRQ_falling_edge
)paren
suffix:semicolon
)brace
r_else
id|__clear_bit
(paren
id|gpio
comma
id|GPIO_IRQ_falling_edge
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;edges&bslash;n&quot;
)paren
suffix:semicolon
id|idx
op_assign
id|gpio
op_rshift
l_int|5
suffix:semicolon
id|GRER
c_func
(paren
id|gpio
)paren
op_assign
id|GPIO_IRQ_rising_edge
(braket
id|idx
)braket
op_amp
id|GPIO_IRQ_mask
(braket
id|idx
)braket
suffix:semicolon
id|GFER
c_func
(paren
id|gpio
)paren
op_assign
id|GPIO_IRQ_falling_edge
(braket
id|idx
)braket
op_amp
id|GPIO_IRQ_mask
(braket
id|idx
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * GPIO IRQs must be acknowledged.  This is for GPIO 0 and 1.&n; */
DECL|function|pxa_ack_low_gpio
r_static
r_void
id|pxa_ack_low_gpio
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|GEDR0
op_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IRQ_GPIO0
)paren
)paren
suffix:semicolon
)brace
DECL|variable|pxa_low_gpio_chip
r_static
r_struct
id|irqchip
id|pxa_low_gpio_chip
op_assign
(brace
dot
id|ack
op_assign
id|pxa_ack_low_gpio
comma
dot
id|mask
op_assign
id|pxa_mask_irq
comma
dot
id|unmask
op_assign
id|pxa_unmask_irq
comma
dot
id|type
op_assign
id|pxa_gpio_irq_type
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Demux handler for GPIO 2-80 edge detect interrupts&n; */
DECL|function|pxa_gpio_demux_handler
r_static
r_void
id|pxa_gpio_demux_handler
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
id|loop
suffix:semicolon
r_do
(brace
id|loop
op_assign
l_int|0
suffix:semicolon
id|mask
op_assign
id|GEDR0
op_amp
op_complement
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|mask
)paren
(brace
id|GEDR0
op_assign
id|mask
suffix:semicolon
id|irq
op_assign
id|IRQ_GPIO
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|mask
op_rshift_assign
l_int|2
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
id|irq
op_increment
suffix:semicolon
id|desc
op_increment
suffix:semicolon
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mask
)paren
suffix:semicolon
id|loop
op_assign
l_int|1
suffix:semicolon
)brace
id|mask
op_assign
id|GEDR1
suffix:semicolon
r_if
c_cond
(paren
id|mask
)paren
(brace
id|GEDR1
op_assign
id|mask
suffix:semicolon
id|irq
op_assign
id|IRQ_GPIO
c_func
(paren
l_int|32
)paren
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
id|irq
op_increment
suffix:semicolon
id|desc
op_increment
suffix:semicolon
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mask
)paren
suffix:semicolon
id|loop
op_assign
l_int|1
suffix:semicolon
)brace
id|mask
op_assign
id|GEDR2
suffix:semicolon
r_if
c_cond
(paren
id|mask
)paren
(brace
id|GEDR2
op_assign
id|mask
suffix:semicolon
id|irq
op_assign
id|IRQ_GPIO
c_func
(paren
l_int|64
)paren
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
id|irq
op_increment
suffix:semicolon
id|desc
op_increment
suffix:semicolon
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mask
)paren
suffix:semicolon
id|loop
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|loop
)paren
suffix:semicolon
)brace
DECL|function|pxa_ack_muxed_gpio
r_static
r_void
id|pxa_ack_muxed_gpio
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|gpio
op_assign
id|irq
op_minus
id|IRQ_GPIO
c_func
(paren
l_int|2
)paren
op_plus
l_int|2
suffix:semicolon
id|GEDR
c_func
(paren
id|gpio
)paren
op_assign
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
)brace
DECL|function|pxa_mask_muxed_gpio
r_static
r_void
id|pxa_mask_muxed_gpio
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|gpio
op_assign
id|irq
op_minus
id|IRQ_GPIO
c_func
(paren
l_int|2
)paren
op_plus
l_int|2
suffix:semicolon
id|__clear_bit
c_func
(paren
id|gpio
comma
id|GPIO_IRQ_mask
)paren
suffix:semicolon
id|GRER
c_func
(paren
id|gpio
)paren
op_and_assign
op_complement
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
id|GFER
c_func
(paren
id|gpio
)paren
op_and_assign
op_complement
id|GPIO_bit
c_func
(paren
id|gpio
)paren
suffix:semicolon
)brace
DECL|function|pxa_unmask_muxed_gpio
r_static
r_void
id|pxa_unmask_muxed_gpio
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|gpio
op_assign
id|irq
op_minus
id|IRQ_GPIO
c_func
(paren
l_int|2
)paren
op_plus
l_int|2
suffix:semicolon
r_int
id|idx
op_assign
id|gpio
op_rshift
l_int|5
suffix:semicolon
id|__set_bit
c_func
(paren
id|gpio
comma
id|GPIO_IRQ_mask
)paren
suffix:semicolon
id|GRER
c_func
(paren
id|gpio
)paren
op_assign
id|GPIO_IRQ_rising_edge
(braket
id|idx
)braket
op_amp
id|GPIO_IRQ_mask
(braket
id|idx
)braket
suffix:semicolon
id|GFER
c_func
(paren
id|gpio
)paren
op_assign
id|GPIO_IRQ_falling_edge
(braket
id|idx
)braket
op_amp
id|GPIO_IRQ_mask
(braket
id|idx
)braket
suffix:semicolon
)brace
DECL|variable|pxa_muxed_gpio_chip
r_static
r_struct
id|irqchip
id|pxa_muxed_gpio_chip
op_assign
(brace
dot
id|ack
op_assign
id|pxa_ack_muxed_gpio
comma
dot
id|mask
op_assign
id|pxa_mask_muxed_gpio
comma
dot
id|unmask
op_assign
id|pxa_unmask_muxed_gpio
comma
dot
id|rerun
op_assign
id|pxa_manual_rerun
comma
dot
id|type
op_assign
id|pxa_gpio_irq_type
comma
)brace
suffix:semicolon
DECL|function|pxa_init_irq
r_void
id|__init
id|pxa_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
multiline_comment|/* disable all IRQs */
id|ICMR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* all IRQs are IRQ, not FIQ */
id|ICLR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* clear all GPIO edge detects */
id|GFER0
op_assign
id|GFER1
op_assign
id|GFER2
op_assign
l_int|0
suffix:semicolon
id|GRER0
op_assign
id|GRER1
op_assign
id|GRER2
op_assign
l_int|0
suffix:semicolon
id|GEDR0
op_assign
id|GEDR0
suffix:semicolon
id|GEDR1
op_assign
id|GEDR1
suffix:semicolon
id|GEDR2
op_assign
id|GEDR2
suffix:semicolon
multiline_comment|/* only unmasked interrupts kick us out of idle */
id|ICCR
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* GPIO 0 and 1 must have their mask bit always set */
id|GPIO_IRQ_mask
(braket
l_int|0
)braket
op_assign
l_int|3
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_GPIO0
suffix:semicolon
id|irq
op_le
id|IRQ_GPIO1
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
id|pxa_low_gpio_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_edge_IRQ
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
r_for
c_loop
(paren
id|irq
op_assign
id|PXA_IRQ
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|irq
op_le
id|PXA_IRQ
c_func
(paren
l_int|31
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
id|pxa_internal_chip
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
)paren
suffix:semicolon
)brace
multiline_comment|/* Those are reserved */
id|set_irq_flags
c_func
(paren
id|PXA_IRQ
c_func
(paren
l_int|15
)paren
comma
l_int|0
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|PXA_IRQ
c_func
(paren
l_int|16
)paren
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_GPIO
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|irq
op_le
id|IRQ_GPIO
c_func
(paren
l_int|80
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
id|pxa_muxed_gpio_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_edge_IRQ
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
multiline_comment|/* Install handler for GPIO 2-80 edge detect interrupts */
id|set_irq_chip
c_func
(paren
id|IRQ_GPIO_2_80
comma
op_amp
id|pxa_internal_chip
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIO_2_80
comma
id|pxa_gpio_demux_handler
)paren
suffix:semicolon
)brace
eof
