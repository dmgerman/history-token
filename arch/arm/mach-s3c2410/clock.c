multiline_comment|/* linux/arch/arm/mach-s3c2410/clock.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 Clock control support&n; *&n; * Based on, and code from linux/arch/arm/mach-versatile/clock.c&n; **&n; **  Copyright (C) 2004 ARM Limited.&n; **  Written by Deep Blue Solutions Limited.&n; *&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware/clock.h&gt;
macro_line|#include &lt;asm/arch/regs-clock.h&gt;
macro_line|#include &quot;clock.h&quot;
multiline_comment|/* clock information */
DECL|variable|s3c24xx_xtal
r_int
r_int
id|s3c24xx_xtal
op_assign
l_int|12
op_star
l_int|1000
op_star
l_int|1000
suffix:semicolon
multiline_comment|/* default 12MHz */
DECL|variable|s3c24xx_fclk
r_int
r_int
id|s3c24xx_fclk
suffix:semicolon
DECL|variable|s3c24xx_hclk
r_int
r_int
id|s3c24xx_hclk
suffix:semicolon
DECL|variable|s3c24xx_pclk
r_int
r_int
id|s3c24xx_pclk
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|clocks
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|clocks_sem
)paren
suffix:semicolon
multiline_comment|/* old functions */
DECL|function|s3c2410_clk_enable
r_void
r_inline
id|s3c2410_clk_enable
c_func
(paren
r_int
r_int
id|clocks
comma
r_int
r_int
id|enable
)paren
(brace
r_int
r_int
id|clkcon
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|clkcon
op_assign
id|__raw_readl
c_func
(paren
id|S3C2410_CLKCON
)paren
suffix:semicolon
id|clkcon
op_and_assign
op_complement
id|clocks
suffix:semicolon
r_if
c_cond
(paren
id|enable
)paren
id|clkcon
op_or_assign
id|clocks
suffix:semicolon
multiline_comment|/* ensure none of the special function bits set */
id|clkcon
op_and_assign
op_complement
(paren
id|S3C2410_CLKCON_IDLE
op_or
id|S3C2410_CLKCON_POWER
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|clkcon
comma
id|S3C2410_CLKCON
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* enable and disable calls for use with the clk struct */
DECL|function|clk_null_enable
r_static
r_int
id|clk_null_enable
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_int
id|enable
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410_clkcon_enable
r_int
id|s3c2410_clkcon_enable
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_int
id|enable
)paren
(brace
id|s3c2410_clk_enable
c_func
(paren
id|clk-&gt;ctrlbit
comma
id|enable
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clock API calls */
DECL|function|clk_get
r_struct
id|clk
op_star
id|clk_get
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|id
)paren
(brace
r_struct
id|clk
op_star
id|p
suffix:semicolon
r_struct
id|clk
op_star
id|clk
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
r_int
id|idno
suffix:semicolon
id|idno
op_assign
(paren
id|dev
op_eq
l_int|NULL
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
id|to_platform_device
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|id
suffix:semicolon
id|down
c_func
(paren
op_amp
id|clocks_sem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|p
comma
op_amp
id|clocks
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;id
op_eq
id|idno
op_logical_and
id|strcmp
c_func
(paren
id|id
comma
id|p-&gt;name
)paren
op_eq
l_int|0
op_logical_and
id|try_module_get
c_func
(paren
id|p-&gt;owner
)paren
)paren
(brace
id|clk
op_assign
id|p
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* check for the case where a device was supplied, but the&n;&t; * clock that was being searched for is not device specific */
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|clk
)paren
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|p
comma
op_amp
id|clocks
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;id
op_eq
op_minus
l_int|1
op_logical_and
id|strcmp
c_func
(paren
id|id
comma
id|p-&gt;name
)paren
op_eq
l_int|0
op_logical_and
id|try_module_get
c_func
(paren
id|p-&gt;owner
)paren
)paren
(brace
id|clk
op_assign
id|p
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|up
c_func
(paren
op_amp
id|clocks_sem
)paren
suffix:semicolon
r_return
id|clk
suffix:semicolon
)brace
DECL|function|clk_put
r_void
id|clk_put
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
id|module_put
c_func
(paren
id|clk-&gt;owner
)paren
suffix:semicolon
)brace
DECL|function|clk_enable
r_int
id|clk_enable
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|clk
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
(paren
id|clk-&gt;enable
)paren
(paren
id|clk
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|clk_disable
r_void
id|clk_disable
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|clk
)paren
)paren
(paren
id|clk-&gt;enable
)paren
(paren
id|clk
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|clk_use
r_int
id|clk_use
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|clk-&gt;used
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|clk_unuse
r_void
id|clk_unuse
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|clk-&gt;used
)paren
suffix:semicolon
)brace
DECL|function|clk_get_rate
r_int
r_int
id|clk_get_rate
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|clk
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|clk-&gt;rate
op_ne
l_int|0
)paren
r_return
id|clk-&gt;rate
suffix:semicolon
r_while
c_loop
(paren
id|clk-&gt;parent
op_ne
l_int|NULL
op_logical_and
id|clk-&gt;rate
op_eq
l_int|0
)paren
id|clk
op_assign
id|clk-&gt;parent
suffix:semicolon
r_return
id|clk-&gt;rate
suffix:semicolon
)brace
DECL|function|clk_round_rate
r_int
id|clk_round_rate
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_int
r_int
id|rate
)paren
(brace
r_return
id|rate
suffix:semicolon
)brace
DECL|function|clk_set_rate
r_int
id|clk_set_rate
c_func
(paren
r_struct
id|clk
op_star
id|clk
comma
r_int
r_int
id|rate
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|clk_get_parent
r_struct
id|clk
op_star
id|clk_get_parent
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
r_return
id|clk-&gt;parent
suffix:semicolon
)brace
DECL|variable|clk_get
id|EXPORT_SYMBOL
c_func
(paren
id|clk_get
)paren
suffix:semicolon
DECL|variable|clk_put
id|EXPORT_SYMBOL
c_func
(paren
id|clk_put
)paren
suffix:semicolon
DECL|variable|clk_enable
id|EXPORT_SYMBOL
c_func
(paren
id|clk_enable
)paren
suffix:semicolon
DECL|variable|clk_disable
id|EXPORT_SYMBOL
c_func
(paren
id|clk_disable
)paren
suffix:semicolon
DECL|variable|clk_use
id|EXPORT_SYMBOL
c_func
(paren
id|clk_use
)paren
suffix:semicolon
DECL|variable|clk_unuse
id|EXPORT_SYMBOL
c_func
(paren
id|clk_unuse
)paren
suffix:semicolon
DECL|variable|clk_get_rate
id|EXPORT_SYMBOL
c_func
(paren
id|clk_get_rate
)paren
suffix:semicolon
DECL|variable|clk_round_rate
id|EXPORT_SYMBOL
c_func
(paren
id|clk_round_rate
)paren
suffix:semicolon
DECL|variable|clk_set_rate
id|EXPORT_SYMBOL
c_func
(paren
id|clk_set_rate
)paren
suffix:semicolon
DECL|variable|clk_get_parent
id|EXPORT_SYMBOL
c_func
(paren
id|clk_get_parent
)paren
suffix:semicolon
multiline_comment|/* base clocks */
DECL|variable|clk_f
r_static
r_struct
id|clk
id|clk_f
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fclk&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|rate
op_assign
l_int|0
comma
dot
id|parent
op_assign
l_int|NULL
comma
dot
id|ctrlbit
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|clk_h
r_static
r_struct
id|clk
id|clk_h
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;hclk&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|rate
op_assign
l_int|0
comma
dot
id|parent
op_assign
l_int|NULL
comma
dot
id|ctrlbit
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|clk_p
r_static
r_struct
id|clk
id|clk_p
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pclk&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|rate
op_assign
l_int|0
comma
dot
id|parent
op_assign
l_int|NULL
comma
dot
id|ctrlbit
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* clocks that could be registered by external code */
DECL|variable|s3c24xx_dclk0
r_struct
id|clk
id|s3c24xx_dclk0
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dclk0&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|s3c24xx_dclk1
r_struct
id|clk
id|s3c24xx_dclk1
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dclk1&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|s3c24xx_clkout0
r_struct
id|clk
id|s3c24xx_clkout0
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;clkout1&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|s3c24xx_clkout1
r_struct
id|clk
id|s3c24xx_clkout1
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;clkout1&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|s3c24xx_uclk
r_struct
id|clk
id|s3c24xx_uclk
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;uclk&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* clock definitions */
DECL|variable|init_clocks
r_static
r_struct
id|clk
id|init_clocks
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;nand&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_h
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_NAND
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;lcd&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_h
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_LCDC
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;usb-host&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_h
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_USBH
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;usb-device&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_h
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_USBD
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;timers&quot;
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_PWMT
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;sdi&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_SDI
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;uart&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_UART0
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;uart&quot;
comma
dot
id|id
op_assign
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_UART1
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;uart&quot;
comma
dot
id|id
op_assign
l_int|2
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_UART2
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;gpio&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_GPIO
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;rtc&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_RTC
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;adc&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_ADC
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;i2c&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_IIC
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;iis&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_IIS
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;spi&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|enable
op_assign
id|s3c2410_clkcon_enable
comma
dot
id|ctrlbit
op_assign
id|S3C2410_CLKCON_SPI
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;watchdog&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|parent
op_assign
op_amp
id|clk_p
comma
dot
id|ctrlbit
op_assign
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* initialise the clock system */
DECL|function|s3c2410_register_clock
r_int
id|s3c2410_register_clock
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
(brace
id|clk-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|clk-&gt;used
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clk-&gt;enable
op_eq
l_int|NULL
)paren
id|clk-&gt;enable
op_assign
id|clk_null_enable
suffix:semicolon
multiline_comment|/* add to the list of available clocks */
id|down
c_func
(paren
op_amp
id|clocks_sem
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|clk-&gt;list
comma
op_amp
id|clocks
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|clocks_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* initalise all the clocks */
DECL|function|s3c2410_init_clocks
r_int
id|__init
id|s3c2410_init_clocks
c_func
(paren
r_void
)paren
(brace
r_struct
id|clk
op_star
id|clkp
op_assign
id|init_clocks
suffix:semicolon
r_int
id|ptr
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;S3C2410 Clock control, (c) 2004 Simtec Electronics&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* initialise the main system clocks */
id|clk_h.rate
op_assign
id|s3c24xx_hclk
suffix:semicolon
id|clk_p.rate
op_assign
id|s3c24xx_pclk
suffix:semicolon
id|clk_f.rate
op_assign
id|s3c24xx_fclk
suffix:semicolon
multiline_comment|/* it looks like just setting the register here is not good&n;&t; * enough, and causes the odd hang at initial boot time, so&n;&t; * do all of them indivdually.&n;&t; *&n;&t; * I think disabling the LCD clock if the LCD is active is&n;&t; * very dangerous, and therefore the bootloader should be&n;&t; * careful to not enable the LCD clock if it is not needed.&n;&t; *&n;&t; * and of course, this looks neater&n;&t; */
id|s3c2410_clk_enable
c_func
(paren
id|S3C2410_CLKCON_NAND
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_clk_enable
c_func
(paren
id|S3C2410_CLKCON_USBH
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_clk_enable
c_func
(paren
id|S3C2410_CLKCON_USBD
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_clk_enable
c_func
(paren
id|S3C2410_CLKCON_ADC
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_clk_enable
c_func
(paren
id|S3C2410_CLKCON_IIC
comma
l_int|0
)paren
suffix:semicolon
id|s3c2410_clk_enable
c_func
(paren
id|S3C2410_CLKCON_SPI
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* assume uart clocks are correctly setup */
multiline_comment|/* register our clocks */
r_if
c_cond
(paren
id|s3c2410_register_clock
c_func
(paren
op_amp
id|clk_f
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;failed to register cpu fclk&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_register_clock
c_func
(paren
op_amp
id|clk_h
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;failed to register cpu hclk&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_register_clock
c_func
(paren
op_amp
id|clk_p
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;failed to register cpu pclk&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
l_int|0
suffix:semicolon
id|ptr
OL
id|ARRAY_SIZE
c_func
(paren
id|init_clocks
)paren
suffix:semicolon
id|ptr
op_increment
comma
id|clkp
op_increment
)paren
(brace
id|ret
op_assign
id|s3c2410_register_clock
c_func
(paren
id|clkp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to register clock %s (%d)&bslash;n&quot;
comma
id|clkp-&gt;name
comma
id|ret
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
