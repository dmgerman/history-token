multiline_comment|/*&n; * drivers/i2c/busses/i2c-ixp2000.c&n; *&n; * I2C adapter for IXP2000 systems using GPIOs for I2C bus&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; * Based on IXDP2400 code by: Naeem M. Afzal &lt;naeem.m.afzal@intel.com&gt;&n; * Made generic by: Jeff Daly &lt;jeffrey.daly@intel.com&gt;&n; *&n; * Copyright (c) 2003-2004 MontaVista Software Inc.&n; *&n; * This file is licensed under  the terms of the GNU General Public &n; * License version 2. This program is licensed &quot;as is&quot; without any &n; * warranty of any kind, whether express or implied.&n; *&n; * From Jeff Daly:&n; *&n; * I2C adapter driver for Intel IXDP2xxx platforms. This should work for any&n; * IXP2000 platform if it uses the HW GPIO in the same manner.  Basically, &n; * SDA and SCL GPIOs have external pullups.  Setting the respective GPIO to &n; * an input will make the signal a &squot;1&squot; via the pullup.  Setting them to &n; * outputs will pull them down. &n; *&n; * The GPIOs are open drain signals and are used as configuration strap inputs&n; * during power-up so there&squot;s generally a buffer on the board that needs to be &n; * &squot;enabled&squot; to drive the GPIOs.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_I2C_DEBUG_BUS
DECL|macro|DEBUG
mdefine_line|#define DEBUG&t;1
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;&t;/* Pick up IXP42000-specific bits */
DECL|function|ixp2000_scl_pin
r_static
r_inline
r_int
id|ixp2000_scl_pin
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
(paren
r_struct
id|ixp2000_i2c_pins
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|scl_pin
suffix:semicolon
)brace
DECL|function|ixp2000_sda_pin
r_static
r_inline
r_int
id|ixp2000_sda_pin
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
(paren
r_struct
id|ixp2000_i2c_pins
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|sda_pin
suffix:semicolon
)brace
DECL|function|ixp2000_bit_setscl
r_static
r_void
id|ixp2000_bit_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|val
)paren
(brace
r_int
id|i
op_assign
l_int|5000
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|gpio_line_config
c_func
(paren
id|ixp2000_scl_pin
c_func
(paren
id|data
)paren
comma
id|GPIO_IN
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|gpio_line_get
c_func
(paren
id|ixp2000_scl_pin
c_func
(paren
id|data
)paren
)paren
op_logical_and
id|i
op_decrement
)paren
(brace
suffix:semicolon
)brace
)brace
r_else
(brace
id|gpio_line_config
c_func
(paren
id|ixp2000_scl_pin
c_func
(paren
id|data
)paren
comma
id|GPIO_OUT
)paren
suffix:semicolon
)brace
)brace
DECL|function|ixp2000_bit_setsda
r_static
r_void
id|ixp2000_bit_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
)paren
(brace
id|gpio_line_config
c_func
(paren
id|ixp2000_sda_pin
c_func
(paren
id|data
)paren
comma
id|GPIO_IN
)paren
suffix:semicolon
)brace
r_else
(brace
id|gpio_line_config
c_func
(paren
id|ixp2000_sda_pin
c_func
(paren
id|data
)paren
comma
id|GPIO_OUT
)paren
suffix:semicolon
)brace
)brace
DECL|function|ixp2000_bit_getscl
r_static
r_int
id|ixp2000_bit_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|gpio_line_get
c_func
(paren
id|ixp2000_scl_pin
c_func
(paren
id|data
)paren
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_bit_getsda
r_static
r_int
id|ixp2000_bit_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|gpio_line_get
c_func
(paren
id|ixp2000_sda_pin
c_func
(paren
id|data
)paren
)paren
suffix:semicolon
)brace
DECL|struct|ixp2000_i2c_data
r_struct
id|ixp2000_i2c_data
(brace
DECL|member|gpio_pins
r_struct
id|ixp2000_i2c_pins
op_star
id|gpio_pins
suffix:semicolon
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|algo_data
r_struct
id|i2c_algo_bit_data
id|algo_data
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ixp2000_i2c_remove
r_static
r_int
id|ixp2000_i2c_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|platform_device
op_star
id|plat_dev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ixp2000_i2c_data
op_star
id|drv_data
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|plat_dev-&gt;dev
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|plat_dev-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|drv_data-&gt;adapter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|drv_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ixp2000_i2c_probe
r_static
r_int
id|ixp2000_i2c_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|platform_device
op_star
id|plat_dev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ixp2000_i2c_pins
op_star
id|gpio
op_assign
id|plat_dev-&gt;dev.platform_data
suffix:semicolon
r_struct
id|ixp2000_i2c_data
op_star
id|drv_data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ixp2000_i2c_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv_data
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memzero
c_func
(paren
id|drv_data
comma
r_sizeof
(paren
op_star
id|drv_data
)paren
)paren
suffix:semicolon
id|drv_data-&gt;gpio_pins
op_assign
id|gpio
suffix:semicolon
id|drv_data-&gt;algo_data.data
op_assign
id|gpio
suffix:semicolon
id|drv_data-&gt;algo_data.setsda
op_assign
id|ixp2000_bit_setsda
suffix:semicolon
id|drv_data-&gt;algo_data.setscl
op_assign
id|ixp2000_bit_setscl
suffix:semicolon
id|drv_data-&gt;algo_data.getsda
op_assign
id|ixp2000_bit_getsda
suffix:semicolon
id|drv_data-&gt;algo_data.getscl
op_assign
id|ixp2000_bit_getscl
suffix:semicolon
id|drv_data-&gt;algo_data.udelay
op_assign
l_int|6
suffix:semicolon
id|drv_data-&gt;algo_data.mdelay
op_assign
l_int|6
suffix:semicolon
id|drv_data-&gt;algo_data.timeout
op_assign
l_int|100
suffix:semicolon
id|drv_data-&gt;adapter.id
op_assign
id|I2C_HW_B_IXP2000
comma
id|drv_data-&gt;adapter.algo_data
op_assign
op_amp
id|drv_data-&gt;algo_data
comma
id|drv_data-&gt;adapter.dev.parent
op_assign
op_amp
id|plat_dev-&gt;dev
suffix:semicolon
id|gpio_line_config
c_func
(paren
id|gpio-&gt;sda_pin
comma
id|GPIO_IN
)paren
suffix:semicolon
id|gpio_line_config
c_func
(paren
id|gpio-&gt;scl_pin
comma
id|GPIO_IN
)paren
suffix:semicolon
id|gpio_line_set
c_func
(paren
id|gpio-&gt;scl_pin
comma
l_int|0
)paren
suffix:semicolon
id|gpio_line_set
c_func
(paren
id|gpio-&gt;sda_pin
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|drv_data-&gt;adapter
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
id|dev
comma
l_string|&quot;Could not install, error %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|drv_data
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|plat_dev-&gt;dev
comma
id|drv_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ixp2000_i2c_driver
r_static
r_struct
id|device_driver
id|ixp2000_i2c_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IXP2000-I2C&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|ixp2000_i2c_probe
comma
dot
id|remove
op_assign
id|ixp2000_i2c_remove
comma
)brace
suffix:semicolon
DECL|function|ixp2000_i2c_init
r_static
r_int
id|__init
id|ixp2000_i2c_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driver_register
c_func
(paren
op_amp
id|ixp2000_i2c_driver
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_i2c_exit
r_static
r_void
id|__exit
id|ixp2000_i2c_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|ixp2000_i2c_driver
)paren
suffix:semicolon
)brace
DECL|variable|ixp2000_i2c_init
id|module_init
c_func
(paren
id|ixp2000_i2c_init
)paren
suffix:semicolon
DECL|variable|ixp2000_i2c_exit
id|module_exit
c_func
(paren
id|ixp2000_i2c_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Deepak Saxena &lt;dsaxena@plexity.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IXP2000 GPIO-based I2C bus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
