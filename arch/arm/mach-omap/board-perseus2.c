multiline_comment|/*&n; * linux/arch/arm/mach-omap/board-perseus2.c&n; *&n; * Modified from board-generic.c&n; *&n; * Original OMAP730 support by Jean Pihet &lt;j-pihet@ti.com&gt;&n; * Updated for 2.6 by Kevin Hilman &lt;kjh@hilman.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/clocks.h&gt;
macro_line|#include &lt;asm/arch/gpio.h&gt;
macro_line|#include &lt;asm/arch/mux.h&gt;
macro_line|#include &lt;asm/arch/fpga.h&gt;
macro_line|#include &lt;asm/arch/serial.h&gt;
macro_line|#include &quot;common.h&quot;
DECL|function|omap_perseus2_init_irq
r_void
id|omap_perseus2_init_irq
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
)brace
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
id|H2P2_DBG_FPGA_ETHR_START
comma
multiline_comment|/* Physical */
dot
id|end
op_assign
id|H2P2_DBG_FPGA_ETHR_START
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
id|INT_730_MPU_EXT_NIRQ
comma
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
DECL|variable|p2_serial_ports
r_static
r_int
id|__initdata
id|p2_serial_ports
(braket
id|OMAP_MAX_NR_PORTS
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|0
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
DECL|function|omap_perseus2_init
r_static
r_void
id|__init
id|omap_perseus2_init
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
multiline_comment|/* Only FPGA needs to be mapped here. All others are done with ioremap */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|omap_perseus2_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|H2P2_DBG_FPGA_BASE
comma
id|H2P2_DBG_FPGA_START
comma
id|H2P2_DBG_FPGA_SIZE
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
DECL|function|omap_perseus2_map_io
r_static
r_void
id|__init
id|omap_perseus2_map_io
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
id|iotable_init
c_func
(paren
id|omap_perseus2_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|omap_perseus2_io_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Early, board-dependent init */
multiline_comment|/*&n;&t; * Hold GSM Reset until needed&n;&t; */
id|omap_writew
c_func
(paren
id|omap_readw
c_func
(paren
id|OMAP730_DSP_M_CTL
)paren
op_amp
op_complement
l_int|1
comma
id|OMAP730_DSP_M_CTL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * UARTs -&gt; done automagically by 8250 driver&n;&t; */
multiline_comment|/*&n;&t; * CSx timings, GPIO Mux ... setup&n;&t; */
multiline_comment|/* Flash: CS0 timings setup */
id|omap_writel
c_func
(paren
l_int|0x0000fff3
comma
id|OMAP730_FLASH_CFG_0
)paren
suffix:semicolon
id|omap_writel
c_func
(paren
l_int|0x00000088
comma
id|OMAP730_FLASH_ACFG_0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ethernet support trough the debug board&n;&t; * CS1 timings setup&n;&t; */
id|omap_writel
c_func
(paren
l_int|0x0000fff3
comma
id|OMAP730_FLASH_CFG_1
)paren
suffix:semicolon
id|omap_writel
c_func
(paren
l_int|0x00000000
comma
id|OMAP730_FLASH_ACFG_1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Configure MPU_EXT_NIRQ IO in IO_CONF9 register,&n;&t; * It is used as the Ethernet controller interrupt&n;&t; */
id|omap_writel
c_func
(paren
id|omap_readl
c_func
(paren
id|OMAP730_IO_CONF_9
)paren
op_amp
l_int|0x1FFFFFFF
comma
id|OMAP730_IO_CONF_9
)paren
suffix:semicolon
id|omap_serial_init
c_func
(paren
id|p2_serial_ports
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|OMAP_PERSEUS2
comma
l_string|&quot;OMAP730 Perseus2&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Kevin Hilman &lt;kjh@hilman.org&gt;&quot;
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
id|omap_perseus2_map_io
)paren
id|INITIRQ
c_func
(paren
id|omap_perseus2_init_irq
)paren
id|INIT_MACHINE
c_func
(paren
id|omap_perseus2_init
)paren
dot
id|timer
op_assign
op_amp
id|omap_timer
comma
id|MACHINE_END
eof
