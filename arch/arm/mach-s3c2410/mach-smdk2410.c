multiline_comment|/***********************************************************************&n; *&n; * linux/arch/arm/mach-s3c2410/mach-smdk2410.c&n; *&n; * Copyright (C) 2004 by FS Forth-Systeme GmbH&n; * All rights reserved.&n; *&n; * $Id: mach-smdk2410.c,v 1.1 2004/05/11 14:15:38 mpietrek Exp $&n; * @Author: Jonas Dietsche&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of&n; * the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston,&n; * MA 02111-1307 USA&n; *&n; * @History:&n; * derived from linux/arch/arm/mach-s3c2410/mach-bast.c, written by&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * 10-Mar-2005 LCVR  Changed S3C2410_VA to S3C24XX_VA&n; *&n; ***********************************************************************/
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
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/regs-serial.h&gt;
macro_line|#include &quot;devs.h&quot;
macro_line|#include &quot;cpu.h&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|smdk2410_iodesc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* nothing here yet */
)brace
suffix:semicolon
DECL|macro|UCON
mdefine_line|#define UCON S3C2410_UCON_DEFAULT
DECL|macro|ULCON
mdefine_line|#define ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
DECL|macro|UFCON
mdefine_line|#define UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE
DECL|variable|smdk2410_uartcfgs
r_static
r_struct
id|s3c2410_uartcfg
id|smdk2410_uartcfgs
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
)brace
comma
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
)brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|smdk2410_devices
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
id|smdk2410_board
id|__initdata
op_assign
(brace
dot
id|devices
op_assign
id|smdk2410_devices
comma
dot
id|devices_count
op_assign
id|ARRAY_SIZE
c_func
(paren
id|smdk2410_devices
)paren
)brace
suffix:semicolon
DECL|function|smdk2410_map_io
r_void
id|__init
id|smdk2410_map_io
c_func
(paren
r_void
)paren
(brace
id|s3c24xx_init_io
c_func
(paren
id|smdk2410_iodesc
comma
id|ARRAY_SIZE
c_func
(paren
id|smdk2410_iodesc
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
id|smdk2410_uartcfgs
comma
id|ARRAY_SIZE
c_func
(paren
id|smdk2410_uartcfgs
)paren
)paren
suffix:semicolon
id|s3c24xx_set_board
c_func
(paren
op_amp
id|smdk2410_board
)paren
suffix:semicolon
)brace
DECL|function|smdk2410_init_irq
r_void
id|__init
id|smdk2410_init_irq
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
id|SMDK2410
comma
l_string|&quot;SMDK2410&quot;
)paren
multiline_comment|/* @TODO: request a new identifier and switch&n;&t;&t;&t;&t;    * to SMDK2410 */
id|MAINTAINER
c_func
(paren
l_string|&quot;Jonas Dietsche&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|S3C2410_SDRAM_PA
comma
id|S3C2410_PA_UART
comma
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
id|smdk2410_map_io
)paren
id|INITIRQ
c_func
(paren
id|smdk2410_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|s3c24xx_timer
comma
id|MACHINE_END
eof
