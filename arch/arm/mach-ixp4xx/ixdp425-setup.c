multiline_comment|/*&n; * arch/arm/mach-ixp4xx/ixdp425-setup.c&n; *&n; * IXDP425/IXCDP1100 board-setup &n; *&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#ifdef&t;__ARMEB__
DECL|macro|REG_OFFSET
mdefine_line|#define&t;REG_OFFSET&t;3
macro_line|#else
DECL|macro|REG_OFFSET
mdefine_line|#define&t;REG_OFFSET&t;0
macro_line|#endif
multiline_comment|/*&n; * IXDP425 uses both chipset serial ports&n; */
DECL|variable|ixdp425_serial_ports
r_static
r_struct
id|uart_port
id|ixdp425_serial_ports
(braket
)braket
op_assign
(brace
(brace
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
(paren
id|IXP4XX_UART1_BASE_VIRT
op_plus
id|REG_OFFSET
)paren
comma
dot
id|mapbase
op_assign
(paren
id|IXP4XX_UART1_BASE_PHYS
)paren
comma
dot
id|irq
op_assign
id|IRQ_IXP4XX_UART1
comma
dot
id|flags
op_assign
id|UPF_SKIP_TEST
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
dot
id|line
op_assign
l_int|0
comma
dot
id|type
op_assign
id|PORT_XSCALE
comma
dot
id|fifosize
op_assign
l_int|32
)brace
comma
(brace
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
(paren
id|IXP4XX_UART2_BASE_VIRT
op_plus
id|REG_OFFSET
)paren
comma
dot
id|mapbase
op_assign
(paren
id|IXP4XX_UART2_BASE_PHYS
)paren
comma
dot
id|irq
op_assign
id|IRQ_IXP4XX_UART2
comma
dot
id|flags
op_assign
id|UPF_SKIP_TEST
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
dot
id|line
op_assign
l_int|1
comma
dot
id|type
op_assign
id|PORT_XSCALE
comma
dot
id|fifosize
op_assign
l_int|32
)brace
)brace
suffix:semicolon
DECL|function|ixdp425_map_io
r_void
id|__init
id|ixdp425_map_io
c_func
(paren
r_void
)paren
(brace
id|early_serial_setup
c_func
(paren
op_amp
id|ixdp425_serial_ports
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|ixdp425_serial_ports
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|ixp4xx_map_io
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|ixdp425_flash_data
r_static
r_struct
id|flash_platform_data
id|ixdp425_flash_data
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
DECL|variable|ixdp425_flash_resource
r_static
r_struct
id|resource
id|ixdp425_flash_resource
op_assign
(brace
dot
id|start
op_assign
id|IXDP425_FLASH_BASE
comma
dot
id|end
op_assign
id|IXDP425_FLASH_BASE
op_plus
id|IXDP425_FLASH_SIZE
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|ixdp425_flash
r_static
r_struct
id|platform_device
id|ixdp425_flash
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
id|ixdp425_flash_data
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
id|ixdp425_flash_resource
comma
)brace
suffix:semicolon
DECL|variable|ixdp425_i2c_gpio_pins
r_static
r_struct
id|ixp4xx_i2c_pins
id|ixdp425_i2c_gpio_pins
op_assign
(brace
dot
id|sda_pin
op_assign
id|IXDP425_SDA_PIN
comma
dot
id|scl_pin
op_assign
id|IXDP425_SCL_PIN
comma
)brace
suffix:semicolon
DECL|variable|ixdp425_i2c_controller
r_static
r_struct
id|platform_device
id|ixdp425_i2c_controller
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IXP4XX-I2C&quot;
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
id|ixdp425_i2c_gpio_pins
comma
)brace
comma
dot
id|num_resources
op_assign
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|ixdp425_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|ixdp425_i2c_controller
comma
op_amp
id|ixdp425_flash
)brace
suffix:semicolon
DECL|function|ixdp425_init
r_static
r_void
id|__init
id|ixdp425_init
c_func
(paren
r_void
)paren
(brace
id|ixp4xx_sys_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * IXP465 has 32MB window&n;&t; */
r_if
c_cond
(paren
id|machine_is_ixdp465
c_func
(paren
)paren
)paren
(brace
id|ixdp425_flash_resource.end
op_add_assign
id|IXDP425_FLASH_SIZE
suffix:semicolon
)brace
id|platform_add_devices
c_func
(paren
id|ixdp425_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|ixdp425_devices
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|IXDP425
comma
l_string|&quot;Intel IXDP425 Development Platform&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software, Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IXP4XX_PERIPHERAL_BASE_PHYS
comma
id|IXP4XX_PERIPHERAL_BASE_VIRT
)paren
id|MAPIO
c_func
(paren
id|ixdp425_map_io
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
id|ixdp425_init
)paren
id|MACHINE_END
id|MACHINE_START
c_func
(paren
id|IXDP465
comma
l_string|&quot;Intel IXDP465 Development Platform&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software, Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IXP4XX_PERIPHERAL_BASE_PHYS
comma
id|IXP4XX_PERIPHERAL_BASE_VIRT
)paren
id|MAPIO
c_func
(paren
id|ixdp425_map_io
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
id|ixdp425_init
)paren
id|MACHINE_END
id|MACHINE_START
c_func
(paren
id|IXCDP1100
comma
l_string|&quot;Intel IXCDP1100 Development Platform&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software, Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IXP4XX_PERIPHERAL_BASE_PHYS
comma
id|IXP4XX_PERIPHERAL_BASE_VIRT
)paren
id|MAPIO
c_func
(paren
id|ixdp425_map_io
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
id|ixdp425_init
)paren
id|MACHINE_END
multiline_comment|/*&n; * Avila is functionally equivalent to IXDP425 except that it adds&n; * a CF IDE slot hanging off the expansion bus. When we have a &n; * driver for IXP4xx CF IDE with driver model support we&squot;ll move&n; * Avila to it&squot;s own setup file.&n; */
macro_line|#ifdef CONFIG_ARCH_AVILA
id|MACHINE_START
c_func
(paren
id|AVILA
comma
l_string|&quot;Gateworks Avila Network Platform&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Deepak Saxena &lt;dsaxena@plexity.net&gt;&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IXP4XX_PERIPHERAL_BASE_PHYS
comma
id|IXP4XX_PERIPHERAL_BASE_VIRT
)paren
id|MAPIO
c_func
(paren
id|ixdp425_map_io
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
id|ixdp425_init
)paren
id|MACHINE_END
macro_line|#endif
eof
