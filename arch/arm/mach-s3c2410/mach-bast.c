multiline_comment|/* linux/arch/arm/mach-s3c2410/mach-bast.c&n; *&n; * Copyright (c) 2003,2004 Simtec Electronics&n; *   Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * http://www.simtec.co.uk/products/EB2410ITX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     14-Sep-2004 BJD  USB power control&n; *     20-Aug-2004 BJD  Added s3c2410_board struct&n; *     18-Aug-2004 BJD  Added platform devices from default set&n; *     16-May-2003 BJD  Created initial version&n; *     16-Aug-2003 BJD  Fixed header files and copyright, added URL&n; *     05-Sep-2003 BJD  Moved to v2.6 kernel&n; *     06-Jan-2003 BJD  Updates for &lt;arch/map.h&gt;&n; *     18-Jan-2003 BJD  Added serial port configuration&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/arch/bast-map.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
singleline_comment|//#include &lt;asm/debug-ll.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &quot;s3c2410.h&quot;
macro_line|#include &quot;devs.h&quot;
macro_line|#include &quot;cpu.h&quot;
macro_line|#include &quot;usb-simtec.h&quot;
multiline_comment|/* macros for virtual address mods for the io space entries */
DECL|macro|VA_C5
mdefine_line|#define VA_C5(item) ((item) + BAST_VAM_CS5)
DECL|macro|VA_C4
mdefine_line|#define VA_C4(item) ((item) + BAST_VAM_CS4)
DECL|macro|VA_C3
mdefine_line|#define VA_C3(item) ((item) + BAST_VAM_CS3)
DECL|macro|VA_C2
mdefine_line|#define VA_C2(item) ((item) + BAST_VAM_CS2)
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
id|bast_iodesc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* ISA IO areas */
(brace
id|S3C2410_VA_ISA_BYTE
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
id|S3C2410_VA_ISA_WORD
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
id|BAST_VA_CTRL1
comma
id|BAST_PA_CTRL1
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_CTRL2
comma
id|BAST_PA_CTRL2
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_CTRL3
comma
id|BAST_PA_CTRL3
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_CTRL4
comma
id|BAST_PA_CTRL4
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* PC104 IRQ mux */
(brace
id|BAST_VA_PC104_IRQREQ
comma
id|BAST_PA_PC104_IRQREQ
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_PC104_IRQRAW
comma
id|BAST_PA_PC104_IRQRAW
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_PC104_IRQMASK
comma
id|BAST_PA_PC104_IRQMASK
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* onboard 8bit lcd port */
(brace
id|BAST_VA_LCD_RCMD1
comma
id|BAST_PA_LCD_RCMD1
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_LCD_WCMD1
comma
id|BAST_PA_LCD_WCMD1
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_LCD_RDATA1
comma
id|BAST_PA_LCD_RDATA1
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_LCD_WDATA1
comma
id|BAST_PA_LCD_WDATA1
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_LCD_RCMD2
comma
id|BAST_PA_LCD_RCMD2
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_LCD_WCMD2
comma
id|BAST_PA_LCD_WCMD2
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_LCD_RDATA2
comma
id|BAST_PA_LCD_RDATA2
comma
id|SZ_1M
comma
id|MT_DEVICE
)brace
comma
(brace
id|BAST_VA_LCD_WDATA2
comma
id|BAST_PA_LCD_WDATA2
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
id|BAST_VA_ISAIO
)paren
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
id|VA_C2
c_func
(paren
id|BAST_VA_ISAMEM
)paren
comma
id|PA_CS2
c_func
(paren
id|BAST_PA_ISAMEM
)paren
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C2
c_func
(paren
id|BAST_VA_ASIXNET
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_ASIXNET
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
id|BAST_VA_SUPERIO
)paren
comma
id|PA_CS2
c_func
(paren
id|BAST_PA_SUPERIO
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
id|BAST_VA_DM9000
)paren
comma
id|PA_CS2
c_func
(paren
id|BAST_PA_DM9000
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
id|BAST_VA_IDEPRI
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDEPRI
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
id|BAST_VA_IDESEC
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDESEC
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
id|BAST_VA_IDEPRIAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDEPRIAUX
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
id|BAST_VA_IDESECAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDESECAUX
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
id|BAST_VA_ISAIO
)paren
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
(brace
id|VA_C3
c_func
(paren
id|BAST_VA_ISAMEM
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_ISAMEM
)paren
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C3
c_func
(paren
id|BAST_VA_ASIXNET
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_ASIXNET
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
id|BAST_VA_SUPERIO
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_SUPERIO
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
id|BAST_VA_DM9000
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_DM9000
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
id|BAST_VA_IDEPRI
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDEPRI
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
id|BAST_VA_IDESEC
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDESEC
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
id|BAST_VA_IDEPRIAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDEPRIAUX
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
id|BAST_VA_IDESECAUX
)paren
comma
id|PA_CS3
c_func
(paren
id|BAST_PA_IDESECAUX
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
id|BAST_VA_ISAIO
)paren
comma
id|PA_CS4
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
id|VA_C4
c_func
(paren
id|BAST_VA_ISAMEM
)paren
comma
id|PA_CS4
c_func
(paren
id|BAST_PA_ISAMEM
)paren
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C4
c_func
(paren
id|BAST_VA_ASIXNET
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_ASIXNET
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
id|BAST_VA_SUPERIO
)paren
comma
id|PA_CS4
c_func
(paren
id|BAST_PA_SUPERIO
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
id|BAST_VA_DM9000
)paren
comma
id|PA_CS4
c_func
(paren
id|BAST_PA_DM9000
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
id|BAST_VA_IDEPRI
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDEPRI
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
id|BAST_VA_IDESEC
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDESEC
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
id|BAST_VA_IDEPRIAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDEPRIAUX
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
id|BAST_VA_IDESECAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDESECAUX
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
id|BAST_VA_ISAIO
)paren
comma
id|PA_CS5
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
id|VA_C5
c_func
(paren
id|BAST_VA_ISAMEM
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_ISAMEM
)paren
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|VA_C5
c_func
(paren
id|BAST_VA_ASIXNET
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_ASIXNET
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
id|BAST_VA_SUPERIO
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_SUPERIO
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
id|BAST_VA_DM9000
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_DM9000
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
id|BAST_VA_IDEPRI
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDEPRI
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
id|BAST_VA_IDESEC
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDESEC
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
id|BAST_VA_IDEPRIAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDEPRIAUX
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
id|BAST_VA_IDESECAUX
)paren
comma
id|PA_CS5
c_func
(paren
id|BAST_PA_IDESECAUX
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
multiline_comment|/* base baud rate for all our UARTs */
DECL|variable|bast_serial_clock
r_static
r_int
r_int
id|bast_serial_clock
op_assign
l_int|24
op_star
l_int|1000
op_star
l_int|1000
suffix:semicolon
DECL|variable|bast_uartcfgs
r_static
r_struct
id|s3c2410_uartcfg
id|bast_uartcfgs
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
id|clock
op_assign
op_amp
id|bast_serial_clock
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
id|clock
op_assign
op_amp
id|bast_serial_clock
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
id|clock
op_assign
op_amp
id|bast_serial_clock
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
)brace
)brace
suffix:semicolon
multiline_comment|/* NOR Flash on BAST board */
DECL|variable|bast_nor_resource
r_static
r_struct
id|resource
id|bast_nor_resource
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
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
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
DECL|variable|bast_device_nor
r_static
r_struct
id|platform_device
id|bast_device_nor
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
id|bast_nor_resource
)paren
comma
dot
id|resource
op_assign
id|bast_nor_resource
comma
)brace
suffix:semicolon
multiline_comment|/* Standard BAST devices */
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|bast_devices
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
id|s3c_device_rtc
comma
op_amp
id|bast_device_nor
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|s3c2410_board
id|bast_board
id|__initdata
op_assign
(brace
dot
id|devices
op_assign
id|bast_devices
comma
dot
id|devices_count
op_assign
id|ARRAY_SIZE
c_func
(paren
id|bast_devices
)paren
)brace
suffix:semicolon
DECL|function|bast_map_io
r_void
id|__init
id|bast_map_io
c_func
(paren
r_void
)paren
(brace
id|s3c24xx_init_io
c_func
(paren
id|bast_iodesc
comma
id|ARRAY_SIZE
c_func
(paren
id|bast_iodesc
)paren
)paren
suffix:semicolon
id|s3c2410_init_uarts
c_func
(paren
id|bast_uartcfgs
comma
id|ARRAY_SIZE
c_func
(paren
id|bast_uartcfgs
)paren
)paren
suffix:semicolon
id|s3c2410_set_board
c_func
(paren
op_amp
id|bast_board
)paren
suffix:semicolon
id|usb_simtec_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|bast_init_irq
r_void
id|__init
id|bast_init_irq
c_func
(paren
r_void
)paren
(brace
id|s3c2410_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|BAST
comma
l_string|&quot;Simtec-BAST&quot;
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
id|S3C2410_VA_UART
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
id|bast_map_io
)paren
id|INITIRQ
c_func
(paren
id|bast_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|s3c2410_timer
comma
id|MACHINE_END
eof
