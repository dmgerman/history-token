multiline_comment|/*&n;    i2c-isa.c - Part of lm_sensors, Linux kernel modules for hardware&n;            monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt; &n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* This implements an i2c algorithm/adapter for ISA bus. Not that this is&n;   on first sight very useful; almost no functionality is preserved.&n;   Except that it makes writing drivers for chips which can be on both&n;   the SMBus and the ISA bus very much easier. See lm78.c for an example&n;   of this. */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
multiline_comment|/* This is the actual algorithm we define */
DECL|variable|isa_algorithm
r_static
r_struct
id|i2c_algorithm
id|isa_algorithm
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ISA bus algorithm&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_ISA
comma
)brace
suffix:semicolon
multiline_comment|/* There can only be one... */
DECL|variable|isa_adapter
r_static
r_struct
id|i2c_adapter
id|isa_adapter
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|id
op_assign
id|I2C_ALGO_ISA
op_or
id|I2C_HW_ISA
comma
dot
r_class
op_assign
id|I2C_ADAP_CLASS_SMBUS
comma
dot
id|algo
op_assign
op_amp
id|isa_algorithm
comma
dot
id|name
op_assign
l_string|&quot;ISA main adapter&quot;
comma
)brace
suffix:semicolon
DECL|function|i2c_isa_init
r_static
r_int
id|__init
id|i2c_isa_init
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_add_adapter
c_func
(paren
op_amp
id|isa_adapter
)paren
suffix:semicolon
)brace
DECL|function|i2c_isa_exit
r_static
r_void
id|__exit
id|i2c_isa_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|isa_adapter
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ISA bus access through i2c&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_isa_init
id|module_init
c_func
(paren
id|i2c_isa_init
)paren
suffix:semicolon
DECL|variable|i2c_isa_exit
id|module_exit
c_func
(paren
id|i2c_isa_exit
)paren
suffix:semicolon
eof
