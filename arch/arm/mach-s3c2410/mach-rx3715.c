multiline_comment|/* linux/arch/arm/mach-s3c2410/mach-rx3715.c&n; *&n; * Copyright (c) 2003,2004 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * http://www.handhelds.org/projects/rx3715.html&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *&t;16-Sep-2004 BJD Copied from mach-h1940.c&n; *&t;25-Oct-2004 BJD Updates for 2.6.10-rc1&n; *&t;10-Jan-2005 BJD Removed include of s3c2410.h s3c2440.h&n; *&t;14-Jan-2005 BJD Added new clock init&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &lt;asm/arch/regs-gpio.h&gt;
macro_line|#include &quot;clock.h&quot;
macro_line|#include &quot;devs.h&quot;
macro_line|#include &quot;cpu.h&quot;
macro_line|#include &quot;pm.h&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|rx3715_iodesc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* dump ISA space somewhere unused */
(brace
id|S3C2410_VA_ISA_WORD
comma
id|S3C2410_CS3
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
(brace
id|S3C2410_VA_ISA_BYTE
comma
id|S3C2410_CS3
comma
id|SZ_16M
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
DECL|variable|rx3715_uartcfgs
r_static
r_struct
id|s3c2410_uartcfg
id|rx3715_uartcfgs
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
l_int|0x00
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
id|uart_flags
op_assign
id|UPF_CONS_FLOW
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
id|rx3715_devices
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
id|rx3715_board
id|__initdata
op_assign
(brace
dot
id|devices
op_assign
id|rx3715_devices
comma
dot
id|devices_count
op_assign
id|ARRAY_SIZE
c_func
(paren
id|rx3715_devices
)paren
)brace
suffix:semicolon
DECL|function|rx3715_map_io
r_void
id|__init
id|rx3715_map_io
c_func
(paren
r_void
)paren
(brace
id|s3c24xx_init_io
c_func
(paren
id|rx3715_iodesc
comma
id|ARRAY_SIZE
c_func
(paren
id|rx3715_iodesc
)paren
)paren
suffix:semicolon
id|s3c24xx_init_clocks
c_func
(paren
l_int|16934000
)paren
suffix:semicolon
id|s3c24xx_init_uarts
c_func
(paren
id|rx3715_uartcfgs
comma
id|ARRAY_SIZE
c_func
(paren
id|rx3715_uartcfgs
)paren
)paren
suffix:semicolon
id|s3c24xx_set_board
c_func
(paren
op_amp
id|rx3715_board
)paren
suffix:semicolon
)brace
DECL|function|rx3715_init_irq
r_void
id|__init
id|rx3715_init_irq
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
macro_line|#ifdef CONFIG_PM
DECL|function|rx3715_init_machine
r_static
r_void
id|__init
id|rx3715_init_machine
c_func
(paren
r_void
)paren
(brace
id|s3c2410_pm_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|rx3715_init_machine
mdefine_line|#define rx3715_init_machine NULL
macro_line|#endif
id|MACHINE_START
c_func
(paren
id|RX3715
comma
l_string|&quot;IPAQ-RX3715&quot;
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
id|MAPIO
c_func
(paren
id|rx3715_map_io
)paren
id|INITIRQ
c_func
(paren
id|rx3715_init_irq
)paren
id|INIT_MACHINE
c_func
(paren
id|rx3715_init_machine
)paren
dot
id|timer
op_assign
op_amp
id|s3c24xx_timer
comma
id|MACHINE_END
eof
