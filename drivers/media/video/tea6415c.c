multiline_comment|/*&n;    tea6415c.h - i2c-driver for the tea6415c by SGS Thomson   &n;&n;    Copyright (C) 1998-2003 Michael Hunold &lt;michael@mihu.de&gt;&n;&n;    The tea6415c is a bus controlled video-matrix-switch&n;    with 8 inputs and 6 outputs.&n;    It is cascadable, i.e. it can be found at the addresses&n;    0x86 and 0x06 on the i2c-bus.&n;    &n;    For detailed informations download the specifications directly&n;    from SGS Thomson at http://www.st.com&n;        &n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License vs published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mvss Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;tea6415c.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* insmod parameter */
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk&t;if (debug) printk
DECL|macro|TEA6415C_NUM_INPUTS
mdefine_line|#define TEA6415C_NUM_INPUTS&t;8
DECL|macro|TEA6415C_NUM_OUTPUTS
mdefine_line|#define TEA6415C_NUM_OUTPUTS&t;6
multiline_comment|/* addresses to scan, found only at 0x03 and/or 0x43 (7-bit) */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
id|I2C_TEA6415C_1
comma
id|I2C_TEA6415C_2
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|normal_i2c_range
r_static
r_int
r_int
id|normal_i2c_range
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
)brace
suffix:semicolon
multiline_comment|/* magic definition of all other variables and things */
id|I2C_CLIENT_INSMOD
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
suffix:semicolon
multiline_comment|/* unique ID allocation */
DECL|variable|tea6415c_id
r_static
r_int
id|tea6415c_id
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* this function is called by i2c_probe */
DECL|function|tea6415c_detect
r_static
r_int
id|tea6415c_detect
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|address
comma
r_int
r_int
id|flags
comma
r_int
id|kind
)paren
(brace
r_struct
id|i2c_client
op_star
id|client
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* let&squot;s see whether this adapter can support what we need */
r_if
c_cond
(paren
l_int|0
op_eq
id|i2c_check_functionality
c_func
(paren
id|adapter
comma
id|I2C_FUNC_SMBUS_WRITE_BYTE
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* allocate memory for client structure */
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_client
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|client
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* fill client structure */
id|sprintf
c_func
(paren
id|client-&gt;dev.name
comma
l_string|&quot;tea6415c (0x%02x)&quot;
comma
id|address
)paren
suffix:semicolon
id|client-&gt;id
op_assign
id|tea6415c_id
op_increment
suffix:semicolon
id|client-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|client-&gt;addr
op_assign
id|address
suffix:semicolon
id|client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|client-&gt;driver
op_assign
op_amp
id|driver
suffix:semicolon
multiline_comment|/* tell the i2c layer a new client has arrived */
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|err
op_assign
id|i2c_attach_client
c_func
(paren
id|client
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;tea6415c.o: detected @ 0x%02x on adapter %s&bslash;n&quot;
comma
l_int|2
op_star
id|address
comma
op_amp
id|client-&gt;adapter-&gt;dev.name
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tea6415c_attach
r_static
r_int
id|tea6415c_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
multiline_comment|/* let&squot;s see whether this is a know adapter we can attach to */
r_if
c_cond
(paren
id|adapter-&gt;id
op_ne
id|I2C_ALGO_SAA7146
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tea6415c.o: refusing to probe on unknown adapter [name=&squot;%s&squot;,id=0x%x]&bslash;n&quot;
comma
id|adapter-&gt;dev.name
comma
id|adapter-&gt;id
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|i2c_probe
c_func
(paren
id|adapter
comma
op_amp
id|addr_data
comma
op_amp
id|tea6415c_detect
)paren
suffix:semicolon
)brace
DECL|function|tea6415c_detach
r_static
r_int
id|tea6415c_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|err
op_assign
id|i2c_detach_client
c_func
(paren
id|client
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tea6415c.o: Client deregistration failed, client not detached.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* makes a connection between the input-pin &squot;i&squot; and the output-pin &squot;o&squot;&n;   for the tea6415c-client &squot;client&squot; */
DECL|function|tea6415c_switch
r_static
r_int
id|tea6415c_switch
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
id|i
comma
r_int
id|o
)paren
(brace
id|u8
id|byte
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tea6415c.o: tea6415c_switch: adr:0x%02x, i:%d, o:%d&bslash;n&quot;
comma
id|client-&gt;addr
comma
id|i
comma
id|o
)paren
suffix:semicolon
multiline_comment|/* check if the pins are valid */
r_if
c_cond
(paren
l_int|0
op_eq
(paren
(paren
l_int|1
op_eq
id|i
op_logical_or
l_int|3
op_eq
id|i
op_logical_or
l_int|5
op_eq
id|i
op_logical_or
l_int|6
op_eq
id|i
op_logical_or
l_int|8
op_eq
id|i
op_logical_or
l_int|10
op_eq
id|i
op_logical_or
l_int|20
op_eq
id|i
op_logical_or
l_int|11
op_eq
id|i
)paren
op_logical_and
(paren
l_int|18
op_eq
id|o
op_logical_or
l_int|17
op_eq
id|o
op_logical_or
l_int|16
op_eq
id|o
op_logical_or
l_int|15
op_eq
id|o
op_logical_or
l_int|14
op_eq
id|o
op_logical_or
l_int|13
op_eq
id|o
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* to understand this, have a look at the tea6415c-specs (p.5) */
r_switch
c_cond
(paren
id|o
)paren
(brace
r_case
l_int|18
suffix:colon
id|byte
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
id|byte
op_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|byte
op_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|17
suffix:colon
id|byte
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|byte
op_assign
l_int|0x18
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
id|byte
op_assign
l_int|0x28
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|5
suffix:colon
id|byte
op_or_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|byte
op_or_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|byte
op_or_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|20
suffix:colon
id|byte
op_or_assign
l_int|0x06
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|byte
op_or_assign
l_int|0x01
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|byte
op_or_assign
l_int|0x05
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|byte
op_or_assign
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|byte
op_or_assign
l_int|0x07
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|i2c_smbus_write_byte
c_func
(paren
id|client
comma
id|byte
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tea6415c.o: tea6415c_switch: could not write to tea6415c&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tea6415c_command
r_static
r_int
id|tea6415c_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|tea6415c_multiplex
op_star
id|v
op_assign
(paren
r_struct
id|tea6415c_multiplex
op_star
)paren
id|arg
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TEA6415C_SWITCH
suffix:colon
(brace
id|result
op_assign
id|tea6415c_switch
c_func
(paren
id|client
comma
id|v-&gt;in
comma
id|v-&gt;out
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
(brace
)brace
(brace
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|0
op_ne
id|result
)paren
r_return
id|result
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
op_assign
(brace
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,54)
dot
id|owner
op_assign
id|THIS_MODULE
comma
macro_line|#endif
dot
id|name
op_assign
l_string|&quot;tea6415c driver&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_TEA6415C
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|tea6415c_attach
comma
dot
id|detach_client
op_assign
id|tea6415c_detach
comma
dot
id|command
op_assign
id|tea6415c_command
comma
)brace
suffix:semicolon
DECL|function|tea6415c_init_module
r_static
r_int
id|tea6415c_init_module
c_func
(paren
r_void
)paren
(brace
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tea6415c_cleanup_module
r_static
r_void
id|tea6415c_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|tea6415c_init_module
id|module_init
c_func
(paren
id|tea6415c_init_module
)paren
suffix:semicolon
DECL|variable|tea6415c_cleanup_module
id|module_exit
c_func
(paren
id|tea6415c_cleanup_module
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Michael Hunold &lt;michael@mihu.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;tea6415c driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
