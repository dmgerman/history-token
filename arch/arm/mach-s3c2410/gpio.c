multiline_comment|/* linux/arch/arm/mach-s3c2410/gpio.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 GPIO support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Changelog&n; *&t;13-Sep-2004  BJD  Implemented change of MISCCR&n; *&t;14-Sep-2004  BJD  Added getpin call&n; *&t;14-Sep-2004  BJD  Fixed bug in setpin() call&n; *&t;30-Sep-2004  BJD  Fixed cfgpin() mask bug&n; *&t;01-Oct-2004  BJD  Added getcfg() to get pin configuration&n; *&t;01-Oct-2004  BJD  Fixed mask bug in pullup() call&n; *&t;01-Oct-2004  BJD  Added getoirq() to turn pin into irqno&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/regs-gpio.h&gt;
DECL|function|s3c2410_gpio_cfgpin
r_void
id|s3c2410_gpio_cfgpin
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|function
)paren
(brace
r_int
r_int
id|base
op_assign
id|S3C2410_GPIO_BASE
c_func
(paren
id|pin
)paren
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
id|con
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|pin
OL
id|S3C2410_GPIO_BANKB
)paren
(brace
id|mask
op_assign
l_int|1
op_lshift
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
suffix:semicolon
)brace
r_else
(brace
id|mask
op_assign
l_int|3
op_lshift
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
op_star
l_int|2
suffix:semicolon
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|con
op_assign
id|__raw_readl
c_func
(paren
id|base
op_plus
l_int|0x00
)paren
suffix:semicolon
id|con
op_and_assign
op_complement
id|mask
suffix:semicolon
id|con
op_or_assign
id|function
suffix:semicolon
id|__raw_writel
c_func
(paren
id|con
comma
id|base
op_plus
l_int|0x00
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_gpio_getcfg
r_int
r_int
id|s3c2410_gpio_getcfg
c_func
(paren
r_int
r_int
id|pin
)paren
(brace
r_int
r_int
id|base
op_assign
id|S3C2410_GPIO_BASE
c_func
(paren
id|pin
)paren
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|pin
OL
id|S3C2410_GPIO_BANKB
)paren
(brace
id|mask
op_assign
l_int|1
op_lshift
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
suffix:semicolon
)brace
r_else
(brace
id|mask
op_assign
l_int|3
op_lshift
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
op_star
l_int|2
suffix:semicolon
)brace
r_return
id|__raw_readl
c_func
(paren
id|base
)paren
op_amp
id|mask
suffix:semicolon
)brace
DECL|function|s3c2410_gpio_pullup
r_void
id|s3c2410_gpio_pullup
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|to
)paren
(brace
r_int
r_int
id|base
op_assign
id|S3C2410_GPIO_BASE
c_func
(paren
id|pin
)paren
suffix:semicolon
r_int
r_int
id|offs
op_assign
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|up
suffix:semicolon
r_if
c_cond
(paren
id|pin
OL
id|S3C2410_GPIO_BANKB
)paren
r_return
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|up
op_assign
id|__raw_readl
c_func
(paren
id|base
op_plus
l_int|0x08
)paren
suffix:semicolon
id|up
op_and_assign
op_complement
(paren
l_int|1L
op_lshift
id|offs
)paren
suffix:semicolon
id|up
op_or_assign
id|to
op_lshift
id|offs
suffix:semicolon
id|__raw_writel
c_func
(paren
id|up
comma
id|base
op_plus
l_int|0x08
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_gpio_setpin
r_void
id|s3c2410_gpio_setpin
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|to
)paren
(brace
r_int
r_int
id|base
op_assign
id|S3C2410_GPIO_BASE
c_func
(paren
id|pin
)paren
suffix:semicolon
r_int
r_int
id|offs
op_assign
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|dat
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dat
op_assign
id|__raw_readl
c_func
(paren
id|base
op_plus
l_int|0x04
)paren
suffix:semicolon
id|dat
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|offs
)paren
suffix:semicolon
id|dat
op_or_assign
id|to
op_lshift
id|offs
suffix:semicolon
id|__raw_writel
c_func
(paren
id|dat
comma
id|base
op_plus
l_int|0x04
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_gpio_getpin
r_int
r_int
id|s3c2410_gpio_getpin
c_func
(paren
r_int
r_int
id|pin
)paren
(brace
r_int
r_int
id|base
op_assign
id|S3C2410_GPIO_BASE
c_func
(paren
id|pin
)paren
suffix:semicolon
r_int
r_int
id|offs
op_assign
id|S3C2410_GPIO_OFFSET
c_func
(paren
id|pin
)paren
suffix:semicolon
r_return
id|__raw_readl
c_func
(paren
id|base
op_plus
l_int|0x04
)paren
op_amp
(paren
l_int|1
op_lshift
id|offs
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_modify_misccr
r_int
r_int
id|s3c2410_modify_misccr
c_func
(paren
r_int
r_int
id|clear
comma
r_int
r_int
id|change
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|misccr
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|misccr
op_assign
id|__raw_readl
c_func
(paren
id|S3C2410_MISCCR
)paren
suffix:semicolon
id|misccr
op_and_assign
op_complement
id|clear
suffix:semicolon
id|misccr
op_xor_assign
id|change
suffix:semicolon
id|__raw_writel
c_func
(paren
id|misccr
comma
id|S3C2410_MISCCR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|misccr
suffix:semicolon
)brace
DECL|function|s3c2410_gpio_getirq
r_int
id|s3c2410_gpio_getirq
c_func
(paren
r_int
r_int
id|pin
)paren
(brace
r_if
c_cond
(paren
id|pin
template_param
id|S3C2410_GPG15_EINT23
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* not valid interrupts */
r_if
c_cond
(paren
id|pin
template_param
id|S3C2410_GPF7
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* not valid pin */
r_if
c_cond
(paren
id|pin
OL
id|S3C2410_GPF4
)paren
r_return
(paren
id|pin
op_minus
id|S3C2410_GPF0
)paren
op_plus
id|IRQ_EINT0
suffix:semicolon
r_if
c_cond
(paren
id|pin
OL
id|S3C2410_GPG0
)paren
r_return
(paren
id|pin
op_minus
id|S3C2410_GPF4
)paren
op_plus
id|IRQ_EINT4
suffix:semicolon
r_return
(paren
id|pin
op_minus
id|S3C2410_GPG0
)paren
op_plus
id|IRQ_EINT8
suffix:semicolon
)brace
eof
