multiline_comment|/*&n; * arch/arm/mach-imx/mx1ads.c&n; *&n; * Initially based on:&n; *&t;linux-2.6.7-imx/arch/arm/mach-imx/scb9328.c&n; *&t;Copyright (c) 2004 Sascha Hauer &lt;sascha@saschahauer.de&gt;&n; *&n; * 2004 (c) MontaVista Software, Inc.&n; *&n; * This file is licensed under the terms of the GNU General Public&n; * License version 2. This program is licensed &quot;as is&quot; without any&n; * warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;generic.h&quot;
macro_line|#include &lt;asm/serial.h&gt;
DECL|variable|mx1ads_resources
r_static
r_struct
id|resource
id|mx1ads_resources
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
id|IMX_CS4_VIRT
comma
dot
id|end
op_assign
id|IMX_CS4_VIRT
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
l_int|13
comma
dot
id|end
op_assign
l_int|13
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
DECL|variable|mx1ads_device
r_static
r_struct
id|platform_device
id|mx1ads_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mx1ads&quot;
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|mx1ads_resources
)paren
comma
dot
id|resource
op_assign
id|mx1ads_resources
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
id|mx1ads_device
comma
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|mx1ads_init
id|mx1ads_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_LEDS
id|imx_gpio_mode
c_func
(paren
id|GPIO_PORTA
op_or
id|GPIO_OUT
op_or
id|GPIO_GPIO
op_or
l_int|2
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|mx1ads_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
id|IMX_CS0_VIRT
comma
id|IMX_CS0_PHYS
comma
id|IMX_CS0_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|IMX_CS1_VIRT
comma
id|IMX_CS1_PHYS
comma
id|IMX_CS1_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|IMX_CS2_VIRT
comma
id|IMX_CS2_PHYS
comma
id|IMX_CS2_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|IMX_CS3_VIRT
comma
id|IMX_CS3_PHYS
comma
id|IMX_CS3_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|IMX_CS4_VIRT
comma
id|IMX_CS4_PHYS
comma
id|IMX_CS4_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|IMX_CS5_VIRT
comma
id|IMX_CS5_PHYS
comma
id|IMX_CS5_SIZE
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|mx1ads_map_io
id|mx1ads_map_io
c_func
(paren
r_void
)paren
(brace
id|imx_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|mx1ads_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|mx1ads_io_desc
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|MX1ADS
comma
l_string|&quot;Motorola MX1ADS&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Sascha Hauer, Pengutronix&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x08000000
comma
l_int|0x00200000
comma
l_int|0xe0200000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x08000100
)paren
id|MAPIO
c_func
(paren
id|mx1ads_map_io
)paren
id|INITIRQ
c_func
(paren
id|imx_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|imx_timer
comma
id|INIT_MACHINE
c_func
(paren
id|mx1ads_init
)paren
id|MACHINE_END
eof
