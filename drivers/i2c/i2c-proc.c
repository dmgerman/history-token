multiline_comment|/*&n;    i2c-proc.c - Part of lm_sensors, Linux kernel modules for hardware&n;                monitoring&n;    Copyright (c) 1998 - 2001 Frodo Looijaard &lt;frodol@dds.nl&gt; and&n;    Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    This driver puts entries in /proc/sys/dev/sensors for each I2C device&n;*/
multiline_comment|/* #define DEBUG 1 */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-proc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* Very inefficient for ISA detects, and won&squot;t work for 10-bit addresses! */
DECL|function|i2c_detect
r_int
id|i2c_detect
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_struct
id|i2c_address_data
op_star
id|address_data
comma
id|i2c_found_addr_proc
op_star
id|found_proc
)paren
(brace
r_int
id|addr
comma
id|i
comma
id|found
comma
id|j
comma
id|err
suffix:semicolon
r_struct
id|i2c_force_data
op_star
id|this_force
suffix:semicolon
r_int
id|is_isa
op_assign
id|i2c_is_isa_adapter
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_int
id|adapter_id
op_assign
id|is_isa
ques
c_cond
id|SENSORS_ISA_BUS
suffix:colon
id|i2c_adapter_id
c_func
(paren
id|adapter
)paren
suffix:semicolon
multiline_comment|/* Forget it if we can&squot;t probe using SMBUS_QUICK */
r_if
c_cond
(paren
(paren
op_logical_neg
id|is_isa
)paren
op_logical_and
op_logical_neg
id|i2c_check_functionality
c_func
(paren
id|adapter
comma
id|I2C_FUNC_SMBUS_QUICK
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
l_int|0x00
suffix:semicolon
id|addr
op_le
(paren
id|is_isa
ques
c_cond
l_int|0xffff
suffix:colon
l_int|0x7f
)paren
suffix:semicolon
id|addr
op_increment
)paren
(brace
multiline_comment|/* XXX: WTF is going on here??? */
r_if
c_cond
(paren
(paren
id|is_isa
op_logical_and
id|check_region
c_func
(paren
id|addr
comma
l_int|1
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|is_isa
op_logical_and
id|i2c_check_addr
c_func
(paren
id|adapter
comma
id|addr
)paren
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* If it is in one of the force entries, we don&squot;t do any&n;&t;&t;   detection at all */
id|found
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|this_force
op_assign
id|address_data-&gt;forces
op_plus
id|i
comma
id|this_force-&gt;force
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|this_force-&gt;force
(braket
id|j
)braket
op_ne
id|SENSORS_I2C_END
)paren
suffix:semicolon
id|j
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|adapter_id
op_eq
id|this_force-&gt;force
(braket
id|j
)braket
)paren
op_logical_or
(paren
(paren
id|this_force-&gt;force
(braket
id|j
)braket
op_eq
id|SENSORS_ANY_I2C_BUS
)paren
op_logical_and
op_logical_neg
id|is_isa
)paren
)paren
op_logical_and
(paren
id|addr
op_eq
id|this_force-&gt;force
(braket
id|j
op_plus
l_int|1
)braket
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found force parameter for adapter %d, addr %04x&bslash;n&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|found_proc
c_func
(paren
id|adapter
comma
id|addr
comma
id|this_force-&gt;kind
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|found
)paren
r_continue
suffix:semicolon
multiline_comment|/* If this address is in one of the ignores, we can forget about it&n;&t;&t;   right now */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;ignore
(braket
id|i
)braket
op_ne
id|SENSORS_I2C_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|adapter_id
op_eq
id|address_data-&gt;ignore
(braket
id|i
)braket
)paren
op_logical_or
(paren
(paren
id|address_data-&gt;ignore
(braket
id|i
)braket
op_eq
id|SENSORS_ANY_I2C_BUS
)paren
op_logical_and
op_logical_neg
id|is_isa
)paren
)paren
op_logical_and
(paren
id|addr
op_eq
id|address_data-&gt;ignore
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found ignore parameter for adapter %d, addr %04x&bslash;n&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;ignore_range
(braket
id|i
)braket
op_ne
id|SENSORS_I2C_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|3
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|adapter_id
op_eq
id|address_data-&gt;ignore_range
(braket
id|i
)braket
)paren
op_logical_or
(paren
(paren
id|address_data
op_member_access_from_pointer
id|ignore_range
(braket
id|i
)braket
op_eq
id|SENSORS_ANY_I2C_BUS
)paren
op_amp
op_logical_neg
id|is_isa
)paren
)paren
op_logical_and
(paren
id|addr
op_ge
id|address_data-&gt;ignore_range
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_logical_and
(paren
id|addr
op_le
id|address_data-&gt;ignore_range
(braket
id|i
op_plus
l_int|2
)braket
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found ignore_range parameter for adapter %d, addr %04x&bslash;n&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|found
)paren
r_continue
suffix:semicolon
multiline_comment|/* Now, we will do a detection, but only if it is in the normal or &n;&t;&t;   probe entries */
r_if
c_cond
(paren
id|is_isa
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;normal_isa
(braket
id|i
)braket
op_ne
id|SENSORS_ISA_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
id|address_data-&gt;normal_isa
(braket
id|i
)braket
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found normal isa entry for adapter %d, addr %04x&bslash;n&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;normal_isa_range
(braket
id|i
)braket
op_ne
id|SENSORS_ISA_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|3
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|address_data-&gt;normal_isa_range
(braket
id|i
)braket
)paren
op_logical_and
(paren
id|addr
op_le
id|address_data-&gt;normal_isa_range
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_logical_and
(paren
(paren
id|addr
op_minus
id|address_data-&gt;normal_isa_range
(braket
id|i
)braket
)paren
op_mod
id|address_data-&gt;normal_isa_range
(braket
id|i
op_plus
l_int|2
)braket
op_eq
l_int|0
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found normal isa_range entry for adapter %d, addr %04x&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;normal_i2c
(braket
id|i
)braket
op_ne
id|SENSORS_I2C_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
id|address_data-&gt;normal_i2c
(braket
id|i
)braket
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found normal i2c entry for adapter %d, addr %02x&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;normal_i2c_range
(braket
id|i
)braket
op_ne
id|SENSORS_I2C_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|address_data-&gt;normal_i2c_range
(braket
id|i
)braket
)paren
op_logical_and
(paren
id|addr
op_le
id|address_data-&gt;normal_i2c_range
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found normal i2c_range entry for adapter %d, addr %04x&bslash;n&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;probe
(braket
id|i
)braket
op_ne
id|SENSORS_I2C_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|adapter_id
op_eq
id|address_data-&gt;probe
(braket
id|i
)braket
)paren
op_logical_or
(paren
(paren
id|address_data
op_member_access_from_pointer
id|probe
(braket
id|i
)braket
op_eq
id|SENSORS_ANY_I2C_BUS
)paren
op_amp
op_logical_neg
id|is_isa
)paren
)paren
op_logical_and
(paren
id|addr
op_eq
id|address_data-&gt;probe
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found probe parameter for adapter %d, addr %04x&bslash;n&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found
op_logical_and
(paren
id|address_data-&gt;probe_range
(braket
id|i
)braket
op_ne
id|SENSORS_I2C_END
)paren
suffix:semicolon
id|i
op_add_assign
l_int|3
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|adapter_id
op_eq
id|address_data-&gt;probe_range
(braket
id|i
)braket
)paren
op_logical_or
(paren
(paren
id|address_data-&gt;probe_range
(braket
id|i
)braket
op_eq
id|SENSORS_ANY_I2C_BUS
)paren
op_amp
op_logical_neg
id|is_isa
)paren
)paren
op_logical_and
(paren
id|addr
op_ge
id|address_data-&gt;probe_range
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_logical_and
(paren
id|addr
op_le
id|address_data-&gt;probe_range
(braket
id|i
op_plus
l_int|2
)braket
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;found probe_range parameter for adapter %d, addr %04x&bslash;n&quot;
comma
id|adapter_id
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
r_continue
suffix:semicolon
multiline_comment|/* OK, so we really should examine this address. First check&n;&t;&t;   whether there is some client here at all! */
r_if
c_cond
(paren
id|is_isa
op_logical_or
(paren
id|i2c_smbus_xfer
(paren
id|adapter
comma
id|addr
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|I2C_SMBUS_QUICK
comma
l_int|NULL
)paren
op_ge
l_int|0
)paren
)paren
r_if
c_cond
(paren
(paren
id|err
op_assign
id|found_proc
c_func
(paren
id|adapter
comma
id|addr
comma
op_minus
l_int|1
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_proc_init
r_static
r_int
id|__init
id|i2c_proc_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_proc_exit
r_static
r_void
id|__exit
id|i2c_proc_exit
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|i2c_detect
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_detect
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;i2c-proc driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_proc_init
id|module_init
c_func
(paren
id|i2c_proc_init
)paren
suffix:semicolon
DECL|variable|i2c_proc_exit
id|module_exit
c_func
(paren
id|i2c_proc_exit
)paren
suffix:semicolon
eof
