multiline_comment|/* linux/arch/arm/mach-s3c2410/mach-vr1000.c&n; *&n; * Copyright (c) 2003-2005 Simtec Electronics&n; *   Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Machine support for Thorcom VR1000 board. Designed for Thorcom by&n; * Simtec Electronics, http://www.simtec.co.uk/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     14-Sep-2004 BJD  USB Power control&n; *     04-Sep-2004 BJD  Added new uart init, and io init&n; *     21-Aug-2004 BJD  Added struct s3c2410_board&n; *     06-Aug-2004 BJD  Fixed call to time initialisation&n; *     05-Apr-2004 BJD  Copied to make mach-vr1000.c&n; *     18-Oct-2004 BJD  Updated board struct&n; *     04-Nov-2004 BJD  Clock and serial configuration update&n; *&n; *     04-Jan-2005 BJD  Updated uart init call&n; *     10-Jan-2005 BJD  Removed include of s3c2410.h&n; *     14-Jan-2005 BJD  Added clock init&n; *     15-Jan-2005 BJD  Add serial port device definition&n; *     20-Jan-2005 BJD  Use UPF_IOREMAP for ports&n; *     10-Feb-2005 BJD  Added power-off capability&n; *     10-Mar-2005 LCVR Changed S3C2410_VA to S3C24XX_VA&n; *     14-Mar-2006 BJD  void __iomem fixes&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_8250.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/arch/bast-map.h&gt;
macro_line|#include &lt;asm/arch/vr1000-map.h&gt;
macro_line|#include &lt;asm/arch/vr1000-irq.h&gt;
macro_line|#include &lt;asm/arch/vr1000-cpld.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &lt;asm/arch/regs-gpio.h&gt;
macro_line|#include &quot;clock.h&quot;
macro_line|#include &quot;devs.h&quot;
macro_line|#include &quot;cpu.h&quot;
macro_line|#include &quot;usb-simtec.h&quot;
multiline_comment|/* macros for virtual address mods for the io space entries */
DECL|macro|VA_C5
mdefine_line|#define VA_C5(item) ((unsigned long)(item) + BAST_VAM_CS5)
DECL|macro|VA_C4
mdefine_line|#define VA_C4(item) ((unsigned long)(item) + BAST_VAM_CS4)
DECL|macro|VA_C3
mdefine_line|#define VA_C3(item) ((unsigned long)(item) + BAST_VAM_CS3)
DECL|macro|VA_C2
mdefine_line|#define VA_C2(item) ((unsigned long)(item) + BAST_VAM_CS2)
multiline_comment|/* macros to modify the physical addresses for io space */
DECL|macro|PA_CS2
mdefine_line|#define PA_CS2(item) ((item) + S3C2410_CS2)
DECL|macro|PA_CS3
mdefine_line|#define PA_CS3(item) ((item) + S3C2410_CS3)
DECL|macro|PA_CS4
mdefine_line|#define PA_CS4(item) ((item) + S3C2410_CS4)
DECL|macro|PA_CS5
mdefine_line|#define PA_CS5(item) ((item) + S3C2410_CS5)
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|vr1000_iodesc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* ISA IO areas */
(brace
(paren
id|u32
)paren
id|S3C24XX_VA_ISA_BYTE
comma
id|PA_CS2
c_func
(paren
id|BAST_PA_ISAIO
)paren
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
(paren
id|u32
)paren
id|S3C24XX_VA_ISA_WORD
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_ISAIO
)paren
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* we could possibly compress the next set down into a set of smaller tables&n;   * pagetables, but that would mean using an L2 section, and it still means&n;   * we cannot actually feed the same register to an LDR due to 16K spacing&n;   */
multiline_comment|/* bast CPLD control registers, and external interrupt controls */
(brace
(paren
id|u32
)paren
id|VR1000_VA_CTRL1
comma
id|VR1000_PA_CTRL1
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
(paren
id|u32
)paren
id|VR1000_VA_CTRL2
comma
id|VR1000_PA_CTRL2
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
(paren
id|u32
)paren
id|VR1000_VA_CTRL3
comma
id|VR1000_PA_CTRL3
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
(paren
id|u32
)paren
id|VR1000_VA_CTRL4
comma
id|VR1000_PA_CTRL4
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* peripheral space... one for each of fast/slow/byte/16bit */
multiline_comment|/* note, ide is only decoded in word space, even though some registers&n;   * are only 8bit */
multiline_comment|/* slow, byte */
(brace
id|VA_C2
c_func
(paren
id|VR1000_VA_DM9000
)paren
comma
id|PA_CS2
c_func
(paren
id|VR1000_PA_DM9000
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C2
c_func
(paren
id|VR1000_VA_IDEPRI
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDEPRI
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C2
c_func
(paren
id|VR1000_VA_IDESEC
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDESEC
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C2
c_func
(paren
id|VR1000_VA_IDEPRIAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDEPRIAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C2
c_func
(paren
id|VR1000_VA_IDESECAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDESECAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* slow, word */
(brace
id|VA_C3
c_func
(paren
id|VR1000_VA_DM9000
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_DM9000
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C3
c_func
(paren
id|VR1000_VA_IDEPRI
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDEPRI
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C3
c_func
(paren
id|VR1000_VA_IDESEC
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDESEC
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C3
c_func
(paren
id|VR1000_VA_IDEPRIAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDEPRIAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C3
c_func
(paren
id|VR1000_VA_IDESECAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|VR1000_PA_IDESECAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* fast, byte */
(brace
id|VA_C4
c_func
(paren
id|VR1000_VA_DM9000
)paren
comma
id|PA_CS4
c_func
(paren
id|VR1000_PA_DM9000
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C4
c_func
(paren
id|VR1000_VA_IDEPRI
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDEPRI
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C4
c_func
(paren
id|VR1000_VA_IDESEC
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDESEC
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C4
c_func
(paren
id|VR1000_VA_IDEPRIAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDEPRIAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C4
c_func
(paren
id|VR1000_VA_IDESECAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDESECAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* fast, word */
(brace
id|VA_C5
c_func
(paren
id|VR1000_VA_DM9000
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_DM9000
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C5
c_func
(paren
id|VR1000_VA_IDEPRI
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDEPRI
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C5
c_func
(paren
id|VR1000_VA_IDESEC
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDESEC
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C5
c_func
(paren
id|VR1000_VA_IDEPRIAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDEPRIAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C5
c_func
(paren
id|VR1000_VA_IDESECAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|VR1000_PA_IDESECAUX
)paren
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
DECL|macro|UCON
mdefine_line|#define UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
DECL|macro|ULCON
mdefine_line|#define ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
DECL|macro|UFCON
mdefine_line|#define UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE
multiline_comment|/* uart clock source(s) */
DECL|variable|vr1000_serial_clocks
r_static
r_struct
id|s3c24xx_uart_clksrc
id|vr1000_serial_clocks
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
id|name
op_assign
l_string|&quot;uclk&quot;
comma
dot
id|divisor
op_assign
l_int|1
comma
dot
id|min_baud
op_assign
l_int|0
comma
dot
id|max_baud
op_assign
l_int|0
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pclk&quot;
comma
dot
id|divisor
op_assign
l_int|1
comma
dot
id|min_baud
op_assign
l_int|0
comma
dot
id|max_baud
op_assign
l_float|0.
)brace
)brace
suffix:semicolon
DECL|variable|vr1000_uartcfgs
r_static
r_struct
id|s3c2410_uartcfg
id|vr1000_uartcfgs
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
id|hwport
op_assign
l_int|0
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|ucon
op_assign
id|UCON
comma
dot
id|ulcon
op_assign
id|ULCON
comma
dot
id|ufcon
op_assign
id|UFCON
comma
dot
id|clocks
op_assign
id|vr1000_serial_clocks
comma
dot
id|clocks_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|vr1000_serial_clocks
)paren
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|hwport
op_assign
l_int|1
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|ucon
op_assign
id|UCON
comma
dot
id|ulcon
op_assign
id|ULCON
comma
dot
id|ufcon
op_assign
id|UFCON
comma
dot
id|clocks
op_assign
id|vr1000_serial_clocks
comma
dot
id|clocks_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|vr1000_serial_clocks
)paren
comma
)brace
comma
multiline_comment|/* port 2 is not actually used */
(braket
l_int|2
)braket
op_assign
(brace
dot
id|hwport
op_assign
l_int|2
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|ucon
op_assign
id|UCON
comma
dot
id|ulcon
op_assign
id|ULCON
comma
dot
id|ufcon
op_assign
id|UFCON
comma
dot
id|clocks
op_assign
id|vr1000_serial_clocks
comma
dot
id|clocks_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|vr1000_serial_clocks
)paren
comma
)brace
)brace
suffix:semicolon
multiline_comment|/* definitions for the vr1000 extra 16550 serial ports */
DECL|macro|VR1000_BAUDBASE
mdefine_line|#define VR1000_BAUDBASE (3692307)
DECL|macro|VR1000_SERIAL_MAPBASE
mdefine_line|#define VR1000_SERIAL_MAPBASE(x) (VR1000_PA_SERIAL + 0x80 + ((x) &lt;&lt; 5))
DECL|variable|serial_platform_data
r_static
r_struct
id|plat_serial8250_port
id|serial_platform_data
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
id|mapbase
op_assign
id|VR1000_SERIAL_MAPBASE
c_func
(paren
l_int|0
)paren
comma
dot
id|irq
op_assign
id|IRQ_VR1000_SERIAL
op_plus
l_int|0
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_IOREMAP
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|regshift
op_assign
l_int|0
comma
dot
id|uartclk
op_assign
id|VR1000_BAUDBASE
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|mapbase
op_assign
id|VR1000_SERIAL_MAPBASE
c_func
(paren
l_int|1
)paren
comma
dot
id|irq
op_assign
id|IRQ_VR1000_SERIAL
op_plus
l_int|1
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_IOREMAP
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|regshift
op_assign
l_int|0
comma
dot
id|uartclk
op_assign
id|VR1000_BAUDBASE
comma
)brace
comma
(braket
l_int|2
)braket
op_assign
(brace
dot
id|mapbase
op_assign
id|VR1000_SERIAL_MAPBASE
c_func
(paren
l_int|2
)paren
comma
dot
id|irq
op_assign
id|IRQ_VR1000_SERIAL
op_plus
l_int|2
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_IOREMAP
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|regshift
op_assign
l_int|0
comma
dot
id|uartclk
op_assign
id|VR1000_BAUDBASE
comma
)brace
comma
(braket
l_int|3
)braket
op_assign
(brace
dot
id|mapbase
op_assign
id|VR1000_SERIAL_MAPBASE
c_func
(paren
l_int|3
)paren
comma
dot
id|irq
op_assign
id|IRQ_VR1000_SERIAL
op_plus
l_int|3
comma
dot
id|flags
op_assign
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_IOREMAP
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|regshift
op_assign
l_int|0
comma
dot
id|uartclk
op_assign
id|VR1000_BAUDBASE
comma
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|serial_device
r_static
r_struct
id|platform_device
id|serial_device
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
id|serial_platform_data
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* MTD NOR Flash */
DECL|variable|vr1000_nor_resource
r_static
r_struct
id|resource
id|vr1000_nor_resource
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
id|S3C2410_CS1
op_plus
l_int|0x4000000
comma
dot
id|end
op_assign
id|S3C2410_CS1
op_plus
l_int|0x4000000
op_plus
id|SZ_16M
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
)brace
suffix:semicolon
DECL|variable|vr1000_nor
r_static
r_struct
id|platform_device
id|vr1000_nor
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;bast-nor&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|vr1000_nor_resource
)paren
comma
dot
id|resource
op_assign
id|vr1000_nor_resource
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|vr1000_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|s3c_device_usb
comma
op_amp
id|s3c_device_lcd
comma
op_amp
id|s3c_device_wdt
comma
op_amp
id|s3c_device_i2c
comma
op_amp
id|s3c_device_iis
comma
op_amp
id|serial_device
comma
op_amp
id|vr1000_nor
comma
)brace
suffix:semicolon
DECL|variable|vr1000_clocks
r_static
r_struct
id|clk
op_star
id|vr1000_clocks
(braket
)braket
op_assign
(brace
op_amp
id|s3c24xx_dclk0
comma
op_amp
id|s3c24xx_dclk1
comma
op_amp
id|s3c24xx_clkout0
comma
op_amp
id|s3c24xx_clkout1
comma
op_amp
id|s3c24xx_uclk
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|s3c24xx_board
id|vr1000_board
id|__initdata
op_assign
(brace
dot
id|devices
op_assign
id|vr1000_devices
comma
dot
id|devices_count
op_assign
id|ARRAY_SIZE
c_func
(paren
id|vr1000_devices
)paren
comma
dot
id|clocks
op_assign
id|vr1000_clocks
comma
dot
id|clocks_count
op_assign
id|ARRAY_SIZE
c_func
(paren
id|vr1000_clocks
)paren
comma
)brace
suffix:semicolon
DECL|function|vr1000_power_off
r_static
r_void
id|vr1000_power_off
c_func
(paren
r_void
)paren
(brace
id|s3c2410_gpio_cfgpin
c_func
(paren
id|S3C2410_GPB9
comma
id|S3C2410_GPB9_OUTP
)paren
suffix:semicolon
id|s3c2410_gpio_setpin
c_func
(paren
id|S3C2410_GPB9
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|vr1000_map_io
r_void
id|__init
id|vr1000_map_io
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* initialise clock sources */
id|s3c24xx_dclk0.parent
op_assign
l_int|NULL
suffix:semicolon
id|s3c24xx_dclk0.rate
op_assign
l_int|12
op_star
l_int|1000
op_star
l_int|1000
suffix:semicolon
id|s3c24xx_dclk1.parent
op_assign
l_int|NULL
suffix:semicolon
id|s3c24xx_dclk1.rate
op_assign
l_int|3692307
suffix:semicolon
id|s3c24xx_clkout0.parent
op_assign
op_amp
id|s3c24xx_dclk0
suffix:semicolon
id|s3c24xx_clkout1.parent
op_assign
op_amp
id|s3c24xx_dclk1
suffix:semicolon
id|s3c24xx_uclk.parent
op_assign
op_amp
id|s3c24xx_clkout1
suffix:semicolon
id|pm_power_off
op_assign
id|vr1000_power_off
suffix:semicolon
id|s3c24xx_init_io
c_func
(paren
id|vr1000_iodesc
comma
id|ARRAY_SIZE
c_func
(paren
id|vr1000_iodesc
)paren
)paren
suffix:semicolon
id|s3c24xx_init_clocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|s3c24xx_init_uarts
c_func
(paren
id|vr1000_uartcfgs
comma
id|ARRAY_SIZE
c_func
(paren
id|vr1000_uartcfgs
)paren
)paren
suffix:semicolon
id|s3c24xx_set_board
c_func
(paren
op_amp
id|vr1000_board
)paren
suffix:semicolon
id|usb_simtec_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|vr1000_init_irq
r_void
id|__init
id|vr1000_init_irq
c_func
(paren
r_void
)paren
(brace
id|s3c24xx_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|VR1000
comma
l_string|&quot;Thorcom-VR1000&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Ben Dooks &lt;ben@simtec.co.uk&gt;&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|S3C2410_SDRAM_PA
comma
id|S3C2410_PA_UART
comma
(paren
id|u32
)paren
id|S3C24XX_VA_UART
)paren
id|BOOT_PARAMS
c_func
(paren
id|S3C2410_SDRAM_PA
op_plus
l_int|0x100
)paren
id|MAPIO
c_func
(paren
id|vr1000_map_io
)paren
id|INITIRQ
c_func
(paren
id|vr1000_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|s3c24xx_timer
comma
id|MACHINE_END
eof
