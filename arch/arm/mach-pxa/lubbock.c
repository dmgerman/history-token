multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/lubbock.c&n; *&n; *  Support for the Intel DBPXA250 Development Platform.&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/arch/irq.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|lubbock_irq_enabled
r_static
r_int
r_int
id|lubbock_irq_enabled
suffix:semicolon
DECL|function|lubbock_mask_irq
r_static
r_void
id|lubbock_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|lubbock_irq
op_assign
(paren
id|irq
op_minus
id|LUBBOCK_IRQ
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|LUB_IRQ_MASK_EN
op_assign
(paren
id|lubbock_irq_enabled
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|lubbock_irq
)paren
)paren
suffix:semicolon
)brace
DECL|function|lubbock_unmask_irq
r_static
r_void
id|lubbock_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|lubbock_irq
op_assign
(paren
id|irq
op_minus
id|LUBBOCK_IRQ
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* the irq can be acknowledged only if deasserted, so it&squot;s done here */
id|LUB_IRQ_SET_CLR
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|lubbock_irq
)paren
suffix:semicolon
id|LUB_IRQ_MASK_EN
op_assign
(paren
id|lubbock_irq_enabled
op_or_assign
(paren
l_int|1
op_lshift
id|lubbock_irq
)paren
)paren
suffix:semicolon
)brace
DECL|variable|lubbock_irq_chip
r_static
r_struct
id|irqchip
id|lubbock_irq_chip
op_assign
(brace
dot
id|ack
op_assign
id|lubbock_mask_irq
comma
dot
id|mask
op_assign
id|lubbock_mask_irq
comma
dot
id|unmask
op_assign
id|lubbock_unmask_irq
comma
)brace
suffix:semicolon
DECL|function|lubbock_irq_handler
r_static
r_void
id|lubbock_irq_handler
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
id|pending
op_assign
id|LUB_IRQ_SET_CLR
op_amp
id|lubbock_irq_enabled
suffix:semicolon
r_do
(brace
id|GEDR
c_func
(paren
l_int|0
)paren
op_assign
id|GPIO_bit
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* clear our parent irq */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|pending
)paren
)paren
(brace
id|irq
op_assign
id|LUBBOCK_IRQ
c_func
(paren
l_int|0
)paren
op_plus
id|__ffs
c_func
(paren
id|pending
)paren
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
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
)brace
id|pending
op_assign
id|LUB_IRQ_SET_CLR
op_amp
id|lubbock_irq_enabled
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pending
)paren
suffix:semicolon
)brace
DECL|function|lubbock_init_irq
r_static
r_void
id|__init
id|lubbock_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
id|pxa_init_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* setup extra lubbock irqs */
r_for
c_loop
(paren
id|irq
op_assign
id|LUBBOCK_IRQ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|irq
op_le
id|LUBBOCK_IRQ
c_func
(paren
l_int|5
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
id|lubbock_irq_chip
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
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIO
c_func
(paren
l_int|0
)paren
comma
id|lubbock_irq_handler
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO
c_func
(paren
l_int|0
)paren
comma
id|IRQT_FALLING
)paren
suffix:semicolon
)brace
DECL|variable|sa1111_resources
r_static
r_struct
id|resource
id|sa1111_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x10000000
comma
dot
id|end
op_assign
l_int|0x10001fff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
id|LUBBOCK_SA1111_IRQ
comma
dot
id|end
op_assign
id|LUBBOCK_SA1111_IRQ
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|sa1111_device
r_static
r_struct
id|platform_device
id|sa1111_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa1111&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sa1111_resources
)paren
comma
dot
id|resource
op_assign
id|sa1111_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|sa1111_device
comma
)brace
suffix:semicolon
DECL|function|lubbock_init
r_static
r_int
id|__init
id|lubbock_init
c_func
(paren
r_void
)paren
(brace
r_return
id|platform_add_devices
c_func
(paren
id|devices
comma
id|ARRAY_SIZE
c_func
(paren
id|devices
)paren
)paren
suffix:semicolon
)brace
DECL|variable|lubbock_init
id|subsys_initcall
c_func
(paren
id|lubbock_init
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|lubbock_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf0000000
comma
l_int|0x08000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* CPLD */
(brace
l_int|0xf1000000
comma
l_int|0x0c000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* LAN91C96 IO */
(brace
l_int|0xf1100000
comma
l_int|0x0e000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* LAN91C96 Attr */
)brace
suffix:semicolon
DECL|function|lubbock_map_io
r_static
r_void
id|__init
id|lubbock_map_io
c_func
(paren
r_void
)paren
(brace
id|pxa_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|lubbock_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|lubbock_io_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* This enables the BTUART */
id|CKEN
op_or_assign
id|CKEN7_BTUART
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO42_BTRXD_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO43_BTTXD_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO44_BTCTS_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO45_BTRTS_MD
)paren
suffix:semicolon
multiline_comment|/* This is for the SMC chip select */
id|pxa_gpio_mode
c_func
(paren
id|GPIO79_nCS_3_MD
)paren
suffix:semicolon
multiline_comment|/* setup sleep mode values */
id|PWER
op_assign
l_int|0x00000002
suffix:semicolon
id|PFER
op_assign
l_int|0x00000000
suffix:semicolon
id|PRER
op_assign
l_int|0x00000002
suffix:semicolon
id|PGSR0
op_assign
l_int|0x00008000
suffix:semicolon
id|PGSR1
op_assign
l_int|0x003F0202
suffix:semicolon
id|PGSR2
op_assign
l_int|0x0001C000
suffix:semicolon
id|PCFR
op_or_assign
id|PCFR_OPDE
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|LUBBOCK
comma
l_string|&quot;Intel DBPXA250 Development Platform&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xa0000000
comma
l_int|0x40000000
comma
id|io_p2v
c_func
(paren
l_int|0x40000000
)paren
)paren
id|MAPIO
c_func
(paren
id|lubbock_map_io
)paren
id|INITIRQ
c_func
(paren
id|lubbock_init_irq
)paren
id|MACHINE_END
eof
