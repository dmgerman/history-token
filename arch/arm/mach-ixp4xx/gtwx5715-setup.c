multiline_comment|/*&n; * arch/arm/mach-ixp4xx/gtwx5715-setup.c&n; *&n; * Gemtek GTWX5715 (Linksys WRV54G) board settup&n; *&n; * Copyright (C) 2004 George T. Joseph&n; * Derived from Coyote&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_8250.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#include &lt;asm/arch/gtwx5715.h&gt;
multiline_comment|/*&n; * Xscale UART registers are 32 bits wide with only the least&n; * significant 8 bits having any meaning.  From a configuration&n; * perspective, this means 2 things...&n; *&n; *   Setting .regshift = 2 so that the standard 16550 registers&n; *   line up on every 4th byte.&n; *&n; *   Shifting the register start virtual address +3 bytes when&n; *   compiled big-endian.  Since register writes are done on a&n; *   single byte basis, if the shift isn&squot;t done the driver will&n; *   write the value into the most significant byte of the register,&n; *   which is ignored, instead of the least significant.&n; */
macro_line|#ifdef&t;__ARMEB__
DECL|macro|REG_OFFSET
mdefine_line|#define&t;REG_OFFSET&t;3
macro_line|#else
DECL|macro|REG_OFFSET
mdefine_line|#define&t;REG_OFFSET&t;0
macro_line|#endif
multiline_comment|/*&n; * Only the second or &quot;console&quot; uart is connected on the gtwx5715.&n; */
DECL|variable|gtwx5715_uart_resources
r_static
r_struct
id|resource
id|gtwx5715_uart_resources
(braket
)braket
op_assign
(brace
(brace
dot
id|start
op_assign
id|IXP4XX_UART2_BASE_PHYS
comma
dot
id|end
op_assign
id|IXP4XX_UART2_BASE_PHYS
op_plus
l_int|0x0fff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(brace
dot
id|start
op_assign
id|IRQ_IXP4XX_UART2
comma
dot
id|end
op_assign
id|IRQ_IXP4XX_UART2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|gtwx5715_uart_platform_data
r_static
r_struct
id|plat_serial8250_port
id|gtwx5715_uart_platform_data
(braket
)braket
op_assign
(brace
(brace
dot
id|mapbase
op_assign
id|IXP4XX_UART2_BASE_PHYS
comma
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
id|IXP4XX_UART2_BASE_VIRT
op_plus
id|REG_OFFSET
comma
dot
id|irq
op_assign
id|IRQ_IXP4XX_UART2
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|regshift
op_assign
l_int|2
comma
dot
id|uartclk
op_assign
id|IXP4XX_UART_XTAL
comma
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|gtwx5715_uart_device
r_static
r_struct
id|platform_device
id|gtwx5715_uart_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial8250&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
id|gtwx5715_uart_platform_data
comma
)brace
comma
dot
id|num_resources
op_assign
l_int|2
comma
dot
id|resource
op_assign
id|gtwx5715_uart_resources
comma
)brace
suffix:semicolon
DECL|function|gtwx5715_map_io
r_void
id|__init
id|gtwx5715_map_io
c_func
(paren
r_void
)paren
(brace
id|ixp4xx_map_io
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|gtwx5715_flash_data
r_static
r_struct
id|flash_platform_data
id|gtwx5715_flash_data
op_assign
(brace
dot
id|map_name
op_assign
l_string|&quot;cfi_probe&quot;
comma
dot
id|width
op_assign
l_int|2
comma
)brace
suffix:semicolon
DECL|variable|gtwx5715_flash_resource
r_static
r_struct
id|resource
id|gtwx5715_flash_resource
op_assign
(brace
dot
id|start
op_assign
id|GTWX5715_FLASH_BASE
comma
dot
id|end
op_assign
id|GTWX5715_FLASH_BASE
op_plus
id|GTWX5715_FLASH_SIZE
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|gtwx5715_flash
r_static
r_struct
id|platform_device
id|gtwx5715_flash
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IXP4XX-Flash&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
op_amp
id|gtwx5715_flash_data
comma
)brace
comma
dot
id|num_resources
op_assign
l_int|1
comma
dot
id|resource
op_assign
op_amp
id|gtwx5715_flash_resource
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|gtwx5715_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|gtwx5715_uart_device
comma
op_amp
id|gtwx5715_flash
comma
)brace
suffix:semicolon
DECL|function|gtwx5715_init
r_static
r_void
id|__init
id|gtwx5715_init
c_func
(paren
r_void
)paren
(brace
id|platform_add_devices
c_func
(paren
id|gtwx5715_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|gtwx5715_devices
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|GTWX5715
comma
l_string|&quot;Gemtek GTWX5715 (Linksys WRV54G)&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;George Joseph&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IXP4XX_UART2_BASE_PHYS
comma
id|IXP4XX_UART2_BASE_VIRT
)paren
id|MAPIO
c_func
(paren
id|gtwx5715_map_io
)paren
id|INITIRQ
c_func
(paren
id|ixp4xx_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|ixp4xx_timer
comma
id|BOOT_PARAMS
c_func
(paren
l_int|0x0100
)paren
id|INIT_MACHINE
c_func
(paren
id|gtwx5715_init
)paren
id|MACHINE_END
eof
