multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/cerf.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Apr-2003 : Removed some old PDA crud [FB]&n; * Oct-2003 : Added uart2 resource [FB]&n; * Jan-2004 : Removed io map for flash [FB]&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;asm/arch/cerf.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|cerfuart2_resources
r_static
r_struct
id|resource
id|cerfuart2_resources
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
l_int|0x80030000
comma
dot
id|end
op_assign
l_int|0x8003ffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|cerfuart2_device
r_static
r_struct
id|platform_device
id|cerfuart2_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa11x0-uart&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|cerfuart2_resources
)paren
comma
dot
id|resource
op_assign
id|cerfuart2_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|cerf_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|cerfuart2_device
comma
)brace
suffix:semicolon
DECL|function|cerf_init_irq
r_static
r_void
id|__init
id|cerf_init_irq
c_func
(paren
r_void
)paren
(brace
id|sa1100_init_irq
c_func
(paren
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|CERF_ETH_IRQ
comma
id|IRQT_RISING
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|cerf_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual&t; physical    length&t; type */
(brace
l_int|0xf0000000
comma
l_int|0x08000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
multiline_comment|/* Crystal Ethernet Chip */
)brace
suffix:semicolon
DECL|function|cerf_map_io
r_static
r_void
id|__init
id|cerf_map_io
c_func
(paren
r_void
)paren
(brace
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|cerf_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|cerf_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* disable this and the uart2 device for sa1100_fir */
id|sa1100_register_uart
c_func
(paren
l_int|2
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* set some GPDR bits here while it&squot;s safe */
id|GPDR
op_or_assign
id|CERF_GPIO_CF_RESET
suffix:semicolon
)brace
DECL|function|cerf_init
r_static
r_int
id|__init
id|cerf_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_cerf
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ret
op_assign
id|platform_add_devices
c_func
(paren
id|cerf_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|cerf_devices
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cerf_init
id|arch_initcall
c_func
(paren
id|cerf_init
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|CERF
comma
l_string|&quot;Intrinsyc CerfBoard/CerfCube&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;support@intrinsyc.com&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xf8000000
)paren
id|MAPIO
c_func
(paren
id|cerf_map_io
)paren
id|INITIRQ
c_func
(paren
id|cerf_init_irq
)paren
id|MACHINE_END
eof
