multiline_comment|/* linux/drivers/i2c/scx200_i2c.c &n;&n;   Copyright (c) 2001,2002 Christer Weinigel &lt;wingel@nano-system.com&gt;&n;&n;   National Semiconductor SCx200 I2C bus on GPIO pins&n;&n;   Based on i2c-velleman.c Copyright (C) 1995-96, 2000 Simon G. Vogl&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;   &n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;   &n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     &n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/scx200_gpio.h&gt;
DECL|macro|NAME
mdefine_line|#define NAME &quot;scx200_i2c&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christer Weinigel &lt;wingel@nano-system.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NatSemi SCx200 I2C Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|scl
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|scl
comma
l_string|&quot;GPIO line for SCL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|sda
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|sda
comma
l_string|&quot;GPIO line for SDA&quot;
)paren
suffix:semicolon
DECL|variable|scl
r_static
r_int
id|scl
op_assign
id|CONFIG_SCx200_I2C_SCL
suffix:semicolon
DECL|variable|sda
r_static
r_int
id|sda
op_assign
id|CONFIG_SCx200_I2C_SDA
suffix:semicolon
DECL|function|scx200_i2c_setscl
r_static
r_void
id|scx200_i2c_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
id|scx200_gpio_set
c_func
(paren
id|scl
comma
id|state
)paren
suffix:semicolon
)brace
DECL|function|scx200_i2c_setsda
r_static
r_void
id|scx200_i2c_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
id|scx200_gpio_set
c_func
(paren
id|sda
comma
id|state
)paren
suffix:semicolon
)brace
DECL|function|scx200_i2c_getscl
r_static
r_int
id|scx200_i2c_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|scx200_gpio_get
c_func
(paren
id|scl
)paren
suffix:semicolon
)brace
DECL|function|scx200_i2c_getsda
r_static
r_int
id|scx200_i2c_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|scx200_gpio_get
c_func
(paren
id|sda
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------&n; * Encapsulate the above functions in the correct operations structure.&n; * This is only done when more than one hardware adapter is supported.&n; */
DECL|variable|scx200_i2c_data
r_static
r_struct
id|i2c_algo_bit_data
id|scx200_i2c_data
op_assign
(brace
l_int|NULL
comma
id|scx200_i2c_setsda
comma
id|scx200_i2c_setscl
comma
id|scx200_i2c_getsda
comma
id|scx200_i2c_getscl
comma
l_int|10
comma
l_int|10
comma
l_int|100
comma
multiline_comment|/* waits, timeout */
)brace
suffix:semicolon
DECL|variable|scx200_i2c_ops
r_static
r_struct
id|i2c_adapter
id|scx200_i2c_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;NatSemi SCx200 I2C&quot;
comma
dot
id|id
op_assign
id|I2C_HW_B_VELLE
comma
dot
id|algo_data
op_assign
op_amp
id|scx200_i2c_data
comma
)brace
suffix:semicolon
DECL|function|scx200_i2c_init
r_int
id|scx200_i2c_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: NatSemi SCx200 I2C Driver&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scx200_gpio_present
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: no SCx200 gpio pins available&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: SCL=GPIO%02u, SDA=GPIO%02u&bslash;n&quot;
comma
id|scl
comma
id|sda
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scl
op_eq
op_minus
l_int|1
op_logical_or
id|sda
op_eq
op_minus
l_int|1
op_logical_or
id|scl
op_eq
id|sda
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: scl and sda must be specified&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Configure GPIOs as open collector outputs */
id|scx200_gpio_configure
c_func
(paren
id|scl
comma
op_complement
l_int|2
comma
l_int|5
)paren
suffix:semicolon
id|scx200_gpio_configure
c_func
(paren
id|sda
comma
op_complement
l_int|2
comma
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|scx200_i2c_ops
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: adapter %s registration failed&bslash;n&quot;
comma
id|scx200_i2c_ops.name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_i2c_cleanup
r_void
id|scx200_i2c_cleanup
c_func
(paren
r_void
)paren
(brace
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|scx200_i2c_ops
)paren
suffix:semicolon
)brace
DECL|variable|scx200_i2c_init
id|module_init
c_func
(paren
id|scx200_i2c_init
)paren
suffix:semicolon
DECL|variable|scx200_i2c_cleanup
id|module_exit
c_func
(paren
id|scx200_i2c_cleanup
)paren
suffix:semicolon
multiline_comment|/*&n;    Local variables:&n;        compile-command: &quot;make -k -C ../.. SUBDIRS=drivers/i2c modules&quot;&n;        c-basic-offset: 8&n;    End:&n;*/
eof
