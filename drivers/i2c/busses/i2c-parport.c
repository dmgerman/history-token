multiline_comment|/* ------------------------------------------------------------------------ *&n; * i2c-parport.c I2C bus over parallel port                                 *&n; * ------------------------------------------------------------------------ *&n;   Copyright (C) 2003-2004 Jean Delvare &lt;khali@linux-fr.org&gt;&n;   &n;   Based on older i2c-philips-par.c driver&n;   Copyright (C) 1995-2000 Simon G. Vogl&n;   With some changes from:&n;   Frodo Looijaard &lt;frodol@dds.nl&gt;&n;   Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt;&n;   &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; * ------------------------------------------------------------------------ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;i2c-parport.h&quot;
multiline_comment|/* ----- Device list ------------------------------------------------------ */
DECL|struct|i2c_par
r_struct
id|i2c_par
(brace
DECL|member|pdev
r_struct
id|pardevice
op_star
id|pdev
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
DECL|member|next
r_struct
id|i2c_par
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|adapter_list
r_static
r_struct
id|i2c_par
op_star
id|adapter_list
suffix:semicolon
multiline_comment|/* ----- Low-level parallel port access ----------------------------------- */
DECL|function|port_write_data
r_static
r_void
id|port_write_data
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|d
)paren
(brace
id|parport_write_data
c_func
(paren
id|p
comma
id|d
)paren
suffix:semicolon
)brace
DECL|function|port_write_control
r_static
r_void
id|port_write_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|d
)paren
(brace
id|parport_write_control
c_func
(paren
id|p
comma
id|d
)paren
suffix:semicolon
)brace
DECL|function|port_read_data
r_static
r_int
r_char
id|port_read_data
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_return
id|parport_read_data
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|port_read_status
r_static
r_int
r_char
id|port_read_status
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_return
id|parport_read_status
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|port_read_control
r_static
r_int
r_char
id|port_read_control
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_return
id|parport_read_control
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|variable|port_write
r_static
r_void
(paren
op_star
id|port_write
(braket
)braket
)paren
(paren
r_struct
id|parport
op_star
comma
r_int
r_char
)paren
op_assign
(brace
id|port_write_data
comma
l_int|NULL
comma
id|port_write_control
comma
)brace
suffix:semicolon
DECL|variable|port_read
r_static
r_int
r_char
(paren
op_star
id|port_read
(braket
)braket
)paren
(paren
r_struct
id|parport
op_star
)paren
op_assign
(brace
id|port_read_data
comma
id|port_read_status
comma
id|port_read_control
comma
)brace
suffix:semicolon
multiline_comment|/* ----- Unified line operation functions --------------------------------- */
DECL|function|line_set
r_static
r_inline
r_void
id|line_set
c_func
(paren
r_struct
id|parport
op_star
id|data
comma
r_int
id|state
comma
r_const
r_struct
id|lineop
op_star
id|op
)paren
(brace
id|u8
id|oldval
op_assign
id|port_read
(braket
id|op-&gt;port
)braket
(paren
id|data
)paren
suffix:semicolon
multiline_comment|/* Touch only the bit(s) needed */
r_if
c_cond
(paren
(paren
id|op-&gt;inverted
op_logical_and
op_logical_neg
id|state
)paren
op_logical_or
(paren
op_logical_neg
id|op-&gt;inverted
op_logical_and
id|state
)paren
)paren
id|port_write
(braket
id|op-&gt;port
)braket
(paren
id|data
comma
id|oldval
op_or
id|op-&gt;val
)paren
suffix:semicolon
r_else
id|port_write
(braket
id|op-&gt;port
)braket
(paren
id|data
comma
id|oldval
op_amp
op_complement
id|op-&gt;val
)paren
suffix:semicolon
)brace
DECL|function|line_get
r_static
r_inline
r_int
id|line_get
c_func
(paren
r_struct
id|parport
op_star
id|data
comma
r_const
r_struct
id|lineop
op_star
id|op
)paren
(brace
id|u8
id|oldval
op_assign
id|port_read
(braket
id|op-&gt;port
)braket
(paren
id|data
)paren
suffix:semicolon
r_return
(paren
(paren
id|op-&gt;inverted
op_logical_and
(paren
id|oldval
op_amp
id|op-&gt;val
)paren
op_ne
id|op-&gt;val
)paren
op_logical_or
(paren
op_logical_neg
id|op-&gt;inverted
op_logical_and
(paren
id|oldval
op_amp
id|op-&gt;val
)paren
op_eq
id|op-&gt;val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* ----- I2C algorithm call-back functions and structures ----------------- */
DECL|function|parport_setscl
r_static
r_void
id|parport_setscl
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
id|line_set
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|state
comma
op_amp
id|adapter_parm
(braket
id|type
)braket
dot
id|setscl
)paren
suffix:semicolon
)brace
DECL|function|parport_setsda
r_static
r_void
id|parport_setsda
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
id|line_set
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|state
comma
op_amp
id|adapter_parm
(braket
id|type
)braket
dot
id|setsda
)paren
suffix:semicolon
)brace
DECL|function|parport_getscl
r_static
r_int
id|parport_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|line_get
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
op_amp
id|adapter_parm
(braket
id|type
)braket
dot
id|getscl
)paren
suffix:semicolon
)brace
DECL|function|parport_getsda
r_static
r_int
id|parport_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|line_get
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
op_amp
id|adapter_parm
(braket
id|type
)braket
dot
id|getsda
)paren
suffix:semicolon
)brace
multiline_comment|/* Encapsulate the functions above in the correct structure.&n;   Note that this is only a template, from which the real structures are&n;   copied. The attaching code will set getscl to NULL for adapters that&n;   cannot read SCL back, and will also make the the data field point to&n;   the parallel port structure. */
DECL|variable|parport_algo_data
r_static
r_struct
id|i2c_algo_bit_data
id|parport_algo_data
op_assign
(brace
dot
id|setsda
op_assign
id|parport_setsda
comma
dot
id|setscl
op_assign
id|parport_setscl
comma
dot
id|getsda
op_assign
id|parport_getsda
comma
dot
id|getscl
op_assign
id|parport_getscl
comma
dot
id|udelay
op_assign
l_int|60
comma
dot
id|mdelay
op_assign
l_int|60
comma
dot
id|timeout
op_assign
id|HZ
comma
)brace
suffix:semicolon
multiline_comment|/* ----- I2c and parallel port call-back functions and structures --------- */
DECL|variable|parport_adapter
r_static
r_struct
id|i2c_adapter
id|parport_adapter
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
id|I2C_CLASS_SMBUS
comma
dot
id|id
op_assign
id|I2C_HW_B_LP
comma
dot
id|name
op_assign
l_string|&quot;Parallel port adapter&quot;
comma
)brace
suffix:semicolon
DECL|function|i2c_parport_attach
r_static
r_void
id|i2c_parport_attach
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|i2c_par
op_star
id|adapter
suffix:semicolon
id|adapter
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_par
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adapter
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-parport: Failed to kmalloc&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|adapter
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|i2c_par
)paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;i2c-parport: attaching to %s&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
id|adapter-&gt;pdev
op_assign
id|parport_register_device
c_func
(paren
id|port
comma
l_string|&quot;i2c-parport&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|PARPORT_FLAG_EXCL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adapter-&gt;pdev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-parport: Unable to register with parport&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|ERROR0
suffix:semicolon
)brace
multiline_comment|/* Fill the rest of the structure */
id|adapter-&gt;adapter
op_assign
id|parport_adapter
suffix:semicolon
id|adapter-&gt;algo_data
op_assign
id|parport_algo_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adapter_parm
(braket
id|type
)braket
dot
id|getscl.val
)paren
id|adapter-&gt;algo_data.getscl
op_assign
l_int|NULL
suffix:semicolon
id|adapter-&gt;algo_data.data
op_assign
id|port
suffix:semicolon
id|adapter-&gt;adapter.algo_data
op_assign
op_amp
id|adapter-&gt;algo_data
suffix:semicolon
r_if
c_cond
(paren
id|parport_claim_or_block
c_func
(paren
id|adapter-&gt;pdev
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-parport: Could not claim parallel port&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|ERROR1
suffix:semicolon
)brace
multiline_comment|/* Reset hardware to a sane state (SCL and SDA high) */
id|parport_setsda
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
id|parport_setscl
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Other init if needed (power on...) */
r_if
c_cond
(paren
id|adapter_parm
(braket
id|type
)braket
dot
id|init.val
)paren
id|line_set
c_func
(paren
id|port
comma
l_int|1
comma
op_amp
id|adapter_parm
(braket
id|type
)braket
dot
id|init
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|adapter-&gt;pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|adapter-&gt;adapter
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-parport: Unable to register with I2C&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|ERROR1
suffix:semicolon
)brace
multiline_comment|/* Add the new adapter to the list */
id|adapter-&gt;next
op_assign
id|adapter_list
suffix:semicolon
id|adapter_list
op_assign
id|adapter
suffix:semicolon
r_return
suffix:semicolon
id|ERROR1
suffix:colon
id|parport_unregister_device
c_func
(paren
id|adapter-&gt;pdev
)paren
suffix:semicolon
id|ERROR0
suffix:colon
id|kfree
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
DECL|function|i2c_parport_detach
r_static
r_void
id|i2c_parport_detach
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|i2c_par
op_star
id|adapter
comma
op_star
id|prev
suffix:semicolon
multiline_comment|/* Walk the list */
r_for
c_loop
(paren
id|prev
op_assign
l_int|NULL
comma
id|adapter
op_assign
id|adapter_list
suffix:semicolon
id|adapter
suffix:semicolon
id|prev
op_assign
id|adapter
comma
id|adapter
op_assign
id|adapter-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|adapter-&gt;pdev-&gt;port
op_eq
id|port
)paren
(brace
multiline_comment|/* Un-init if needed (power off...) */
r_if
c_cond
(paren
id|adapter_parm
(braket
id|type
)braket
dot
id|init.val
)paren
id|line_set
c_func
(paren
id|port
comma
l_int|0
comma
op_amp
id|adapter_parm
(braket
id|type
)braket
dot
id|init
)paren
suffix:semicolon
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|adapter-&gt;adapter
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|adapter-&gt;pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|adapter-&gt;next
suffix:semicolon
r_else
id|adapter_list
op_assign
id|adapter-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
DECL|variable|i2c_driver
r_static
r_struct
id|parport_driver
id|i2c_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i2c-parport&quot;
comma
dot
id|attach
op_assign
id|i2c_parport_attach
comma
dot
id|detach
op_assign
id|i2c_parport_detach
comma
)brace
suffix:semicolon
multiline_comment|/* ----- Module loading, unloading and information ------------------------ */
DECL|function|i2c_parport_init
r_static
r_int
id|__init
id|i2c_parport_init
c_func
(paren
r_void
)paren
(brace
r_int
id|type_count
suffix:semicolon
id|type_count
op_assign
r_sizeof
(paren
id|adapter_parm
)paren
op_div
r_sizeof
(paren
r_struct
id|adapter_parm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
op_logical_or
id|type
op_ge
id|type_count
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-parport: invalid type (%d)&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
id|type
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|parport_register_driver
c_func
(paren
op_amp
id|i2c_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_parport_exit
r_static
r_void
id|__exit
id|i2c_parport_exit
c_func
(paren
r_void
)paren
(brace
id|parport_unregister_driver
c_func
(paren
op_amp
id|i2c_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jean Delvare &lt;khali@linux-fr.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C bus over parallel port&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_parport_init
id|module_init
c_func
(paren
id|i2c_parport_init
)paren
suffix:semicolon
DECL|variable|i2c_parport_exit
id|module_exit
c_func
(paren
id|i2c_parport_exit
)paren
suffix:semicolon
eof
