multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/irq.c&n; *&n; * Copyright (C) 1999-2001 Nicolas Pitre&n; *&n; * Generic IRQ handling for the SA11x0, GPIO 11-27 IRQ demultiplexing.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/*&n; * SA1100 GPIO edge detection for IRQs:&n; * IRQs are generated on Falling-Edge, Rising-Edge, or both.&n; * Use this instead of directly setting GRER/GFER.&n; */
DECL|variable|GPIO_IRQ_rising_edge
r_static
r_int
id|GPIO_IRQ_rising_edge
suffix:semicolon
DECL|variable|GPIO_IRQ_falling_edge
r_static
r_int
id|GPIO_IRQ_falling_edge
suffix:semicolon
DECL|variable|GPIO_IRQ_mask
r_static
r_int
id|GPIO_IRQ_mask
op_assign
(paren
l_int|1
op_lshift
l_int|11
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * To get the GPIO number from an IRQ number&n; */
DECL|macro|GPIO_11_27_IRQ
mdefine_line|#define GPIO_11_27_IRQ(i)&t;((i) - 21)
DECL|macro|GPIO11_27_MASK
mdefine_line|#define GPIO11_27_MASK(irq)&t;(1 &lt;&lt; GPIO_11_27_IRQ(irq))
DECL|function|sa1100_gpio_type
r_static
r_int
id|sa1100_gpio_type
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
r_int
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_le
l_int|10
)paren
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
r_else
id|mask
op_assign
id|GPIO11_27_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|IRQT_PROBE
)paren
(brace
r_if
c_cond
(paren
(paren
id|GPIO_IRQ_rising_edge
op_or
id|GPIO_IRQ_falling_edge
)paren
op_amp
id|mask
)paren
r_return
l_int|0
suffix:semicolon
id|type
op_assign
id|__IRQT_RISEDGE
op_or
id|__IRQT_FALEDGE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_amp
id|__IRQT_RISEDGE
)paren
(brace
id|GPIO_IRQ_rising_edge
op_or_assign
id|mask
suffix:semicolon
)brace
r_else
id|GPIO_IRQ_rising_edge
op_and_assign
op_complement
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|__IRQT_FALEDGE
)paren
(brace
id|GPIO_IRQ_falling_edge
op_or_assign
id|mask
suffix:semicolon
)brace
r_else
id|GPIO_IRQ_falling_edge
op_and_assign
op_complement
id|mask
suffix:semicolon
id|GRER
op_assign
id|GPIO_IRQ_rising_edge
op_amp
id|GPIO_IRQ_mask
suffix:semicolon
id|GFER
op_assign
id|GPIO_IRQ_falling_edge
op_amp
id|GPIO_IRQ_mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * GPIO IRQs must be acknowledged.  This is for IRQs from 0 to 10.&n; */
DECL|function|sa1100_low_gpio_ack
r_static
r_void
id|sa1100_low_gpio_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|GEDR
op_assign
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1100_low_gpio_mask
r_static
r_void
id|sa1100_low_gpio_mask
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
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1100_low_gpio_unmask
r_static
r_void
id|sa1100_low_gpio_unmask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ICMR
op_or_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
)brace
DECL|function|sa1100_low_gpio_wake
r_static
r_int
id|sa1100_low_gpio_wake
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
id|PWER
op_or_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
r_else
id|PWER
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1100_low_gpio_chip
r_static
r_struct
id|irqchip
id|sa1100_low_gpio_chip
op_assign
(brace
dot
id|ack
op_assign
id|sa1100_low_gpio_ack
comma
dot
id|mask
op_assign
id|sa1100_low_gpio_mask
comma
dot
id|unmask
op_assign
id|sa1100_low_gpio_unmask
comma
dot
id|type
op_assign
id|sa1100_gpio_type
comma
dot
id|wake
op_assign
id|sa1100_low_gpio_wake
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * IRQ11 (GPIO11 through 27) handler.  We enter here with the&n; * irq_controller_lock held, and IRQs disabled.  Decode the IRQ&n; * and call the handler.&n; */
r_static
r_void
DECL|function|sa1100_high_gpio_handler
id|sa1100_high_gpio_handler
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
id|mask
op_assign
id|GEDR
op_amp
l_int|0xfffff800
suffix:semicolon
r_do
(brace
multiline_comment|/*&n;&t;&t; * clear down all currently active IRQ sources.&n;&t;&t; * We will be processing them all.&n;&t;&t; */
id|GEDR
op_assign
id|mask
suffix:semicolon
id|irq
op_assign
id|IRQ_GPIO11
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|mask
op_rshift_assign
l_int|11
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
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
id|irq
op_increment
suffix:semicolon
id|desc
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mask
)paren
suffix:semicolon
id|mask
op_assign
id|GEDR
op_amp
l_int|0xfffff800
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Like GPIO0 to 10, GPIO11-27 IRQs need to be handled specially.&n; * In addition, the IRQs are all collected up into one bit in the&n; * interrupt controller registers.&n; */
DECL|function|sa1100_high_gpio_ack
r_static
r_void
id|sa1100_high_gpio_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
id|GPIO11_27_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
id|GEDR
op_assign
id|mask
suffix:semicolon
)brace
DECL|function|sa1100_high_gpio_mask
r_static
r_void
id|sa1100_high_gpio_mask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
id|GPIO11_27_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
id|GPIO_IRQ_mask
op_and_assign
op_complement
id|mask
suffix:semicolon
id|GRER
op_and_assign
op_complement
id|mask
suffix:semicolon
id|GFER
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
DECL|function|sa1100_high_gpio_unmask
r_static
r_void
id|sa1100_high_gpio_unmask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
id|GPIO11_27_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
id|GPIO_IRQ_mask
op_or_assign
id|mask
suffix:semicolon
id|GRER
op_assign
id|GPIO_IRQ_rising_edge
op_amp
id|GPIO_IRQ_mask
suffix:semicolon
id|GFER
op_assign
id|GPIO_IRQ_falling_edge
op_amp
id|GPIO_IRQ_mask
suffix:semicolon
)brace
DECL|function|sa1100_high_gpio_wake
r_static
r_int
id|sa1100_high_gpio_wake
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
id|PWER
op_or_assign
id|GPIO11_27_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
r_else
id|PWER
op_and_assign
op_complement
id|GPIO11_27_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1100_high_gpio_chip
r_static
r_struct
id|irqchip
id|sa1100_high_gpio_chip
op_assign
(brace
dot
id|ack
op_assign
id|sa1100_high_gpio_ack
comma
dot
id|mask
op_assign
id|sa1100_high_gpio_mask
comma
dot
id|unmask
op_assign
id|sa1100_high_gpio_unmask
comma
dot
id|type
op_assign
id|sa1100_gpio_type
comma
dot
id|wake
op_assign
id|sa1100_high_gpio_wake
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * We don&squot;t need to ACK IRQs on the SA1100 unless they&squot;re GPIOs&n; * this is for internal IRQs i.e. from 11 to 31.&n; */
DECL|function|sa1100_mask_irq
r_static
r_void
id|sa1100_mask_irq
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
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1100_unmask_irq
r_static
r_void
id|sa1100_unmask_irq
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
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|sa1100_normal_chip
r_static
r_struct
id|irqchip
id|sa1100_normal_chip
op_assign
(brace
dot
id|ack
op_assign
id|sa1100_mask_irq
comma
dot
id|mask
op_assign
id|sa1100_mask_irq
comma
dot
id|unmask
op_assign
id|sa1100_unmask_irq
comma
)brace
suffix:semicolon
DECL|variable|irq_resource
r_static
r_struct
id|resource
id|irq_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;irqs&quot;
comma
dot
id|start
op_assign
l_int|0x90050000
comma
dot
id|end
op_assign
l_int|0x9005ffff
comma
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|saved
r_int
r_int
id|saved
suffix:semicolon
DECL|member|icmr
r_int
r_int
id|icmr
suffix:semicolon
DECL|member|iclr
r_int
r_int
id|iclr
suffix:semicolon
DECL|member|iccr
r_int
r_int
id|iccr
suffix:semicolon
DECL|variable|sa1100irq_state
)brace
id|sa1100irq_state
suffix:semicolon
DECL|function|sa1100irq_suspend
r_static
r_int
id|sa1100irq_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_struct
id|sa1100irq_state
op_star
id|st
op_assign
op_amp
id|sa1100irq_state
suffix:semicolon
id|st-&gt;saved
op_assign
l_int|1
suffix:semicolon
id|st-&gt;icmr
op_assign
id|ICMR
suffix:semicolon
id|st-&gt;iclr
op_assign
id|ICLR
suffix:semicolon
id|st-&gt;iccr
op_assign
id|ICCR
suffix:semicolon
multiline_comment|/*&n;&t; * Disable all GPIO-based interrupts.&n;&t; */
id|ICMR
op_and_assign
op_complement
(paren
id|IC_GPIO11_27
op_or
id|IC_GPIO10
op_or
id|IC_GPIO9
op_or
id|IC_GPIO8
op_or
id|IC_GPIO7
op_or
id|IC_GPIO6
op_or
id|IC_GPIO5
op_or
id|IC_GPIO4
op_or
id|IC_GPIO3
op_or
id|IC_GPIO2
op_or
id|IC_GPIO1
op_or
id|IC_GPIO0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the appropriate edges for wakeup.&n;&t; */
id|GRER
op_assign
id|PWER
op_amp
id|GPIO_IRQ_rising_edge
suffix:semicolon
id|GFER
op_assign
id|PWER
op_amp
id|GPIO_IRQ_falling_edge
suffix:semicolon
multiline_comment|/*&n;&t; * Clear any pending GPIO interrupts.&n;&t; */
id|GEDR
op_assign
id|GEDR
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100irq_resume
r_static
r_int
id|sa1100irq_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
)paren
(brace
r_struct
id|sa1100irq_state
op_star
id|st
op_assign
op_amp
id|sa1100irq_state
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;saved
)paren
(brace
id|ICCR
op_assign
id|st-&gt;iccr
suffix:semicolon
id|ICLR
op_assign
id|st-&gt;iclr
suffix:semicolon
id|GRER
op_assign
id|GPIO_IRQ_rising_edge
op_amp
id|GPIO_IRQ_mask
suffix:semicolon
id|GFER
op_assign
id|GPIO_IRQ_falling_edge
op_amp
id|GPIO_IRQ_mask
suffix:semicolon
id|ICMR
op_assign
id|st-&gt;icmr
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1100irq_sysclass
r_static
r_struct
id|sysdev_class
id|sa1100irq_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;sa11x0-irq&quot;
)paren
comma
dot
id|suspend
op_assign
id|sa1100irq_suspend
comma
dot
id|resume
op_assign
id|sa1100irq_resume
comma
)brace
suffix:semicolon
DECL|variable|sa1100irq_device
r_static
r_struct
id|sys_device
id|sa1100irq_device
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|sa1100irq_sysclass
comma
)brace
suffix:semicolon
DECL|function|sa1100irq_init_devicefs
r_static
r_int
id|__init
id|sa1100irq_init_devicefs
c_func
(paren
r_void
)paren
(brace
id|sysdev_class_register
c_func
(paren
op_amp
id|sa1100irq_sysclass
)paren
suffix:semicolon
r_return
id|sys_device_register
c_func
(paren
op_amp
id|sa1100irq_device
)paren
suffix:semicolon
)brace
DECL|variable|sa1100irq_init_devicefs
id|device_initcall
c_func
(paren
id|sa1100irq_init_devicefs
)paren
suffix:semicolon
DECL|function|sa1100_init_irq
r_void
id|__init
id|sa1100_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|irq_resource
)paren
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
id|GFER
op_assign
l_int|0
suffix:semicolon
id|GRER
op_assign
l_int|0
suffix:semicolon
id|GEDR
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Whatever the doc says, this has to be set for the wait-on-irq&n;&t; * instruction to work... on a SA1100 rev 9 at least.&n;&t; */
id|ICCR
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
op_le
l_int|10
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
id|sa1100_low_gpio_chip
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
l_int|12
suffix:semicolon
id|irq
op_le
l_int|31
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
id|sa1100_normal_chip
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
r_for
c_loop
(paren
id|irq
op_assign
l_int|32
suffix:semicolon
id|irq
op_le
l_int|48
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
id|sa1100_high_gpio_chip
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
multiline_comment|/*&n;&t; * Install handler for GPIO 11-27 edge detect interrupts&n;&t; */
id|set_irq_chip
c_func
(paren
id|IRQ_GPIO11_27
comma
op_amp
id|sa1100_normal_chip
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIO11_27
comma
id|sa1100_high_gpio_handler
)paren
suffix:semicolon
)brace
eof
