multiline_comment|/* linux/arch/arm/mach-s3c2410/mach-smdk2440.c&n; *&n; * Copyright (c) 2004,2005 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * http://www.fluff.org/ben/smdk2440/&n; *&n; * Thanks to Dimity Andric and TomTom for the loan of an SMDK2440.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *&t;01-Nov-2004 BJD Initial version&n; *&t;12-Nov-2004 BJD Updated for release&n; *&t;04-Jan-2005 BJD Fixes for pre-release&n; *&t;22-Feb-2005 BJD Updated for 2.6.11-rc5 relesa&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
singleline_comment|//#include &lt;asm/debug-ll.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &lt;asm/arch/regs-gpio.h&gt;
macro_line|#include &lt;asm/arch/idle.h&gt;
macro_line|#include &quot;s3c2410.h&quot;
macro_line|#include &quot;s3c2440.h&quot;
macro_line|#include &quot;clock.h&quot;
macro_line|#include &quot;devs.h&quot;
macro_line|#include &quot;cpu.h&quot;
macro_line|#include &quot;pm.h&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|smdk2440_iodesc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* ISA IO Space map (memory space selected by A24) */
(brace
id|S3C2410_VA_ISA_WORD
comma
id|S3C2410_CS2
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|S3C2410_VA_ISA_BYTE
comma
id|S3C2410_CS2
comma
id|SZ_16M
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
DECL|variable|smdk2440_uartcfgs
r_static
r_struct
id|s3c2410_uartcfg
id|smdk2440_uartcfgs
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
l_int|0x3c5
comma
dot
id|ulcon
op_assign
l_int|0x03
comma
dot
id|ufcon
op_assign
l_int|0x51
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
l_int|0x3c5
comma
dot
id|ulcon
op_assign
l_int|0x03
comma
dot
id|ufcon
op_assign
l_int|0x51
comma
)brace
comma
multiline_comment|/* IR port */
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
l_int|0x3c5
comma
dot
id|ulcon
op_assign
l_int|0x43
comma
dot
id|ufcon
op_assign
l_int|0x51
comma
)brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|smdk2440_devices
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
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|s3c24xx_board
id|smdk2440_board
id|__initdata
op_assign
(brace
dot
id|devices
op_assign
id|smdk2440_devices
comma
dot
id|devices_count
op_assign
id|ARRAY_SIZE
c_func
(paren
id|smdk2440_devices
)paren
)brace
suffix:semicolon
DECL|function|smdk2440_map_io
r_void
id|__init
id|smdk2440_map_io
c_func
(paren
r_void
)paren
(brace
id|s3c24xx_init_io
c_func
(paren
id|smdk2440_iodesc
comma
id|ARRAY_SIZE
c_func
(paren
id|smdk2440_iodesc
)paren
)paren
suffix:semicolon
id|s3c24xx_init_clocks
c_func
(paren
l_int|16934400
)paren
suffix:semicolon
id|s3c24xx_init_uarts
c_func
(paren
id|smdk2440_uartcfgs
comma
id|ARRAY_SIZE
c_func
(paren
id|smdk2440_uartcfgs
)paren
)paren
suffix:semicolon
id|s3c24xx_set_board
c_func
(paren
op_amp
id|smdk2440_board
)paren
suffix:semicolon
)brace
DECL|function|smdk2440_machine_init
r_void
id|__init
id|smdk2440_machine_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Configure the LEDs (even if we have no LED support)*/
id|s3c2410_gpio_cfgpin
c_func
(paren
id|S3C2410_GPF4
comma
id|S3C2410_GPF4_OUTP
)paren
suffix:semicolon
id|s3c2410_gpio_cfgpin
c_func
(paren
id|S3C2410_GPF5
comma
id|S3C2410_GPF5_OUTP
)paren
suffix:semicolon
id|s3c2410_gpio_cfgpin
c_func
(paren
id|S3C2410_GPF6
comma
id|S3C2410_GPF6_OUTP
)paren
suffix:semicolon
id|s3c2410_gpio_cfgpin
c_func
(paren
id|S3C2410_GPF7
comma
id|S3C2410_GPF7_OUTP
)paren
suffix:semicolon
id|s3c2410_gpio_setpin
c_func
(paren
id|S3C2410_GPF4
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_gpio_setpin
c_func
(paren
id|S3C2410_GPF5
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_gpio_setpin
c_func
(paren
id|S3C2410_GPF6
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_gpio_setpin
c_func
(paren
id|S3C2410_GPF7
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_pm_init
c_func
(paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|S3C2440
comma
l_string|&quot;SMDK2440&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Ben Dooks &lt;ben@fluff.org&gt;&quot;
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
dot
id|init_irq
op_assign
id|s3c24xx_init_irq
comma
dot
id|map_io
op_assign
id|smdk2440_map_io
comma
dot
id|init_machine
op_assign
id|smdk2440_machine_init
comma
dot
id|timer
op_assign
op_amp
id|s3c24xx_timer
comma
id|MACHINE_END
eof
