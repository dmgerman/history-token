multiline_comment|/*&n;    i2c-stub.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;&n;    Copyright (c) 2004 Mark M. Hoffman &lt;mhoffman@lightlink.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
DECL|macro|DEBUG
mdefine_line|#define DEBUG 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
DECL|variable|stub_bytes
r_static
id|u8
id|stub_bytes
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|stub_words
r_static
id|u16
id|stub_words
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Return -1 on error. */
DECL|function|stub_xfer
r_static
id|s32
id|stub_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
id|u16
id|addr
comma
r_int
r_int
id|flags
comma
r_char
id|read_write
comma
id|u8
id|command
comma
r_int
id|size
comma
r_union
id|i2c_smbus_data
op_star
id|data
)paren
(brace
id|s32
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;smbus quick - addr 0x%02x&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|stub_bytes
(braket
id|command
)braket
op_assign
id|data-&gt;byte
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;smbus byte data - addr 0x%02x, &quot;
l_string|&quot;wrote 0x%02x at 0x%02x.&bslash;n&quot;
comma
id|addr
comma
id|data-&gt;byte
comma
id|command
)paren
suffix:semicolon
)brace
r_else
(brace
id|data-&gt;byte
op_assign
id|stub_bytes
(braket
id|command
)braket
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;smbus byte data - addr 0x%02x, &quot;
l_string|&quot;read  0x%02x at 0x%02x.&bslash;n&quot;
comma
id|addr
comma
id|data-&gt;byte
comma
id|command
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|stub_words
(braket
id|command
)braket
op_assign
id|data-&gt;word
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;smbus word data - addr 0x%02x, &quot;
l_string|&quot;wrote 0x%04x at 0x%02x.&bslash;n&quot;
comma
id|addr
comma
id|data-&gt;word
comma
id|command
)paren
suffix:semicolon
)brace
r_else
(brace
id|data-&gt;word
op_assign
id|stub_words
(braket
id|command
)braket
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;smbus word data - addr 0x%02x, &quot;
l_string|&quot;read  0x%04x at 0x%02x.&bslash;n&quot;
comma
id|addr
comma
id|data-&gt;word
comma
id|command
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Unsupported I2C/SMBus command&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* switch (size) */
r_return
id|ret
suffix:semicolon
)brace
DECL|function|stub_func
r_static
id|u32
id|stub_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_return
id|I2C_FUNC_SMBUS_QUICK
op_or
id|I2C_FUNC_SMBUS_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
suffix:semicolon
)brace
DECL|variable|smbus_algorithm
r_static
r_struct
id|i2c_algorithm
id|smbus_algorithm
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Non-I2C SMBus adapter&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SMBUS
comma
dot
id|functionality
op_assign
id|stub_func
comma
dot
id|smbus_xfer
op_assign
id|stub_xfer
comma
)brace
suffix:semicolon
DECL|variable|stub_adapter
r_static
r_struct
id|i2c_adapter
id|stub_adapter
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
r_class
op_assign
id|I2C_CLASS_HWMON
comma
dot
id|algo
op_assign
op_amp
id|smbus_algorithm
comma
dot
id|name
op_assign
l_string|&quot;SMBus stub driver&quot;
comma
)brace
suffix:semicolon
DECL|function|i2c_stub_init
r_static
r_int
id|__init
id|i2c_stub_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-stub loaded&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|i2c_add_adapter
c_func
(paren
op_amp
id|stub_adapter
)paren
suffix:semicolon
)brace
DECL|function|i2c_stub_exit
r_static
r_void
id|__exit
id|i2c_stub_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|stub_adapter
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mark M. Hoffman &lt;mhoffman@lightlink.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C stub driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_stub_init
id|module_init
c_func
(paren
id|i2c_stub_init
)paren
suffix:semicolon
DECL|variable|i2c_stub_exit
id|module_exit
c_func
(paren
id|i2c_stub_exit
)paren
suffix:semicolon
eof
