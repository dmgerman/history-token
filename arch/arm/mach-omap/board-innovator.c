multiline_comment|/*&n; * linux/arch/arm/mach-omap/board-innovator.c&n; *&n; * Board specific inits for OMAP-1510 and OMAP-1610 Innovator&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; * Author: Greg Lonnon &lt;glonnon@ridgerun.com&gt;&n; *&n; * Copyright (C) 2002 MontaVista Software, Inc.&n; *&n; * Separated FPGA interrupts from innovator1510.c and cleaned up for 2.6&n; * Copyright (C) 2004 Nokia Corporation by Tony Lindrgen &lt;tony@atomide.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/clocks.h&gt;
macro_line|#include &lt;asm/arch/gpio.h&gt;
macro_line|#include &lt;asm/arch/fpga.h&gt;
macro_line|#include &quot;common.h&quot;
macro_line|#ifdef CONFIG_ARCH_OMAP1510
r_extern
r_int
id|omap_gpio_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Only FPGA needs to be mapped here. All others are done with ioremap */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|innovator1510_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OMAP1510P1_FPGA_BASE
comma
id|OMAP1510P1_FPGA_START
comma
id|OMAP1510P1_FPGA_SIZE
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
DECL|variable|innovator1510_smc91x_resources
r_static
r_struct
id|resource
id|innovator1510_smc91x_resources
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
id|OMAP1510P1_FPGA_ETHR_START
comma
multiline_comment|/* Physical */
dot
id|end
op_assign
id|OMAP1510P1_FPGA_ETHR_START
op_plus
l_int|16
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
id|INT_ETHER
comma
dot
id|end
op_assign
id|INT_ETHER
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
DECL|variable|innovator1510_smc91x_device
r_static
r_struct
id|platform_device
id|innovator1510_smc91x_device
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
id|innovator1510_smc91x_resources
)paren
comma
dot
id|resource
op_assign
id|innovator1510_smc91x_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|innovator1510_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|innovator1510_smc91x_device
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_OMAP1510 */
macro_line|#ifdef CONFIG_ARCH_OMAP1610
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|innovator1610_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OMAP1610_ETHR_BASE
comma
id|OMAP1610_ETHR_START
comma
id|OMAP1610_ETHR_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|OMAP1610_NOR_FLASH_BASE
comma
id|OMAP1610_NOR_FLASH_START
comma
id|OMAP1610_NOR_FLASH_SIZE
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
DECL|variable|innovator1610_smc91x_resources
r_static
r_struct
id|resource
id|innovator1610_smc91x_resources
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
id|OMAP1610_ETHR_START
comma
multiline_comment|/* Physical */
dot
id|end
op_assign
id|OMAP1610_ETHR_START
op_plus
id|SZ_4K
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
l_int|0
comma
multiline_comment|/* Really GPIO 0 */
dot
id|end
op_assign
l_int|0
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
DECL|variable|innovator1610_smc91x_device
r_static
r_struct
id|platform_device
id|innovator1610_smc91x_device
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
id|innovator1610_smc91x_resources
)paren
comma
dot
id|resource
op_assign
id|innovator1610_smc91x_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|innovator1610_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|innovator1610_smc91x_device
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_OMAP1610 */
DECL|function|innovator_init_irq
r_void
id|innovator_init_irq
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
macro_line|#ifdef CONFIG_ARCH_OMAP1510
r_if
c_cond
(paren
id|cpu_is_omap1510
c_func
(paren
)paren
)paren
(brace
id|omap_gpio_init
c_func
(paren
)paren
suffix:semicolon
id|fpga_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|innovator_init
r_static
r_void
id|__init
id|innovator_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ARCH_OMAP1510
r_if
c_cond
(paren
id|cpu_is_omap1510
c_func
(paren
)paren
)paren
(brace
id|platform_add_devices
c_func
(paren
id|innovator1510_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|innovator1510_devices
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1610
r_if
c_cond
(paren
id|cpu_is_omap1610
c_func
(paren
)paren
)paren
(brace
id|platform_add_devices
c_func
(paren
id|innovator1610_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|innovator1610_devices
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|innovator_map_io
r_static
r_void
id|__init
id|innovator_map_io
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
macro_line|#ifdef CONFIG_ARCH_OMAP1510
r_if
c_cond
(paren
id|cpu_is_omap1510
c_func
(paren
)paren
)paren
(brace
id|iotable_init
c_func
(paren
id|innovator1510_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|innovator1510_io_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Dump the Innovator FPGA rev early - useful info for support. */
id|printk
c_func
(paren
l_string|&quot;Innovator FPGA Rev %d.%d Board Rev %d&bslash;n&quot;
comma
id|fpga_read
c_func
(paren
id|OMAP1510P1_FPGA_REV_HIGH
)paren
comma
id|fpga_read
c_func
(paren
id|OMAP1510P1_FPGA_REV_LOW
)paren
comma
id|fpga_read
c_func
(paren
id|OMAP1510P1_FPGA_BOARD_REV
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1610
r_if
c_cond
(paren
id|cpu_is_omap1610
c_func
(paren
)paren
)paren
(brace
id|iotable_init
c_func
(paren
id|innovator1610_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|innovator1610_io_desc
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
id|MACHINE_START
c_func
(paren
id|OMAP_INNOVATOR
comma
l_string|&quot;TI-Innovator&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software, Inc.&quot;
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
id|innovator_map_io
)paren
id|INITIRQ
c_func
(paren
id|innovator_init_irq
)paren
id|INIT_MACHINE
c_func
(paren
id|innovator_init
)paren
id|MACHINE_END
eof
