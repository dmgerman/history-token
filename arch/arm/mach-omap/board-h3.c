multiline_comment|/*&n; * linux/arch/arm/mach-omap/board-h3.c&n; *&n; * This file contains OMAP1710 H3 specific code.&n; *&n; * Copyright (C) 2004 Texas Instruments, Inc.&n; * Copyright (C) 2002 MontaVista Software, Inc.&n; * Copyright (C) 2001 RidgeRun, Inc.&n; * Author: RidgeRun, Inc.&n; *         Greg Lonnon (glonnon@ridgerun.com) or info@ridgerun.com&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &lt;asm/arch/mux.h&gt;
macro_line|#include &lt;asm/arch/gpio.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;common.h&quot;
r_extern
r_int
id|omap_gpio_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|h3_serial_ports
r_static
r_int
id|__initdata
id|h3_serial_ports
(braket
id|OMAP_MAX_NR_PORTS
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|smc91x_resources
r_static
r_struct
id|resource
id|smc91x_resources
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
id|OMAP1710_ETHR_START
comma
multiline_comment|/* Physical */
dot
id|end
op_assign
id|OMAP1710_ETHR_START
op_plus
id|OMAP1710_ETHR_SIZE
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
id|OMAP_GPIO_IRQ
c_func
(paren
l_int|40
)paren
comma
dot
id|end
op_assign
id|OMAP_GPIO_IRQ
c_func
(paren
l_int|40
)paren
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
DECL|variable|smc91x_device
r_static
r_struct
id|platform_device
id|smc91x_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;smc91x&quot;
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
id|smc91x_resources
)paren
comma
dot
id|resource
op_assign
id|smc91x_resources
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
id|smc91x_device
comma
)brace
suffix:semicolon
DECL|function|h3_init
r_static
r_void
id|__init
id|h3_init
c_func
(paren
r_void
)paren
(brace
(paren
r_void
)paren
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
DECL|function|h3_init_smc91x
r_static
r_void
id|__init
id|h3_init_smc91x
c_func
(paren
r_void
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|W15_1710_GPIO40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|omap_request_gpio
c_func
(paren
l_int|40
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Error requesting gpio 40 for smc91x irq&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|omap_set_gpio_edge_ctrl
c_func
(paren
l_int|40
comma
id|OMAP_GPIO_FALLING_EDGE
)paren
suffix:semicolon
)brace
DECL|function|h3_init_irq
r_void
id|h3_init_irq
c_func
(paren
r_void
)paren
(brace
id|omap_init_irq
c_func
(paren
)paren
suffix:semicolon
id|omap_gpio_init
c_func
(paren
)paren
suffix:semicolon
id|h3_init_smc91x
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|h3_map_io
r_static
r_void
id|__init
id|h3_map_io
c_func
(paren
r_void
)paren
(brace
id|omap_map_io
c_func
(paren
)paren
suffix:semicolon
id|omap_serial_init
c_func
(paren
id|h3_serial_ports
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|OMAP_H3
comma
l_string|&quot;TI OMAP1710 H3 board&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Texas Instruments, Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x10000000
comma
l_int|0xfff00000
comma
l_int|0xfef00000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x10000100
)paren
id|MAPIO
c_func
(paren
id|h3_map_io
)paren
id|INITIRQ
c_func
(paren
id|h3_init_irq
)paren
id|INIT_MACHINE
c_func
(paren
id|h3_init
)paren
dot
id|timer
op_assign
op_amp
id|omap_timer
comma
id|MACHINE_END
eof
