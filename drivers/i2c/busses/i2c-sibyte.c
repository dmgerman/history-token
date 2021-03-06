multiline_comment|/*&n; * Copyright (C) 2004 Steven J. Hill&n; * Copyright (C) 2001,2002,2003 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/i2c-algo-sibyte.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_smbus.h&gt;
DECL|variable|sibyte_board_data
r_static
r_struct
id|i2c_algo_sibyte_data
id|sibyte_board_data
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|0
comma
(paren
r_void
op_star
)paren
(paren
id|KSEG1
op_plus
id|A_SMB_BASE
c_func
(paren
l_int|0
)paren
)paren
)brace
comma
(brace
l_int|NULL
comma
l_int|1
comma
(paren
r_void
op_star
)paren
(paren
id|KSEG1
op_plus
id|A_SMB_BASE
c_func
(paren
l_int|1
)paren
)paren
)brace
)brace
suffix:semicolon
DECL|variable|sibyte_board_adapter
r_static
r_struct
id|i2c_adapter
id|sibyte_board_adapter
(braket
l_int|2
)braket
op_assign
(brace
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|id
op_assign
id|I2C_HW_SIBYTE
comma
dot
r_class
op_assign
id|I2C_CLASS_HWMON
comma
dot
id|algo
op_assign
l_int|NULL
comma
dot
id|algo_data
op_assign
op_amp
id|sibyte_board_data
(braket
l_int|0
)braket
comma
dot
id|name
op_assign
l_string|&quot;SiByte SMBus 0&quot;
comma
)brace
comma
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|id
op_assign
id|I2C_HW_SIBYTE
comma
dot
r_class
op_assign
id|I2C_CLASS_HWMON
comma
dot
id|algo
op_assign
l_int|NULL
comma
dot
id|algo_data
op_assign
op_amp
id|sibyte_board_data
(braket
l_int|1
)braket
comma
dot
id|name
op_assign
l_string|&quot;SiByte SMBus 1&quot;
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|i2c_sibyte_init
r_static
r_int
id|__init
id|i2c_sibyte_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i2c-swarm.o: i2c SMBus adapter module for SiByte board&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_sibyte_add_bus
c_func
(paren
op_amp
id|sibyte_board_adapter
(braket
l_int|0
)braket
comma
id|K_SMB_FREQ_100KHZ
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|i2c_sibyte_add_bus
c_func
(paren
op_amp
id|sibyte_board_adapter
(braket
l_int|1
)braket
comma
id|K_SMB_FREQ_400KHZ
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_sibyte_exit
r_static
r_void
id|__exit
id|i2c_sibyte_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_sibyte_del_bus
c_func
(paren
op_amp
id|sibyte_board_adapter
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i2c_sibyte_del_bus
c_func
(paren
op_amp
id|sibyte_board_adapter
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|variable|i2c_sibyte_init
id|module_init
c_func
(paren
id|i2c_sibyte_init
)paren
suffix:semicolon
DECL|variable|i2c_sibyte_exit
id|module_exit
c_func
(paren
id|i2c_sibyte_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Kip Walker &lt;kwalker@broadcom.com&gt;, Steven J. Hill &lt;sjhill@realitydiluted.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SMBus adapter routines for SiByte boards&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
