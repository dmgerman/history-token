multiline_comment|/*&n;    lm75.c - Part of lm_sensors, Linux kernel modules for hardware&n;             monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-proc.h&gt;
DECL|macro|LM75_SYSCTL_TEMP
mdefine_line|#define LM75_SYSCTL_TEMP 1200&t;/* Degrees Celcius * 10 */
multiline_comment|/* Addresses to scan */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
id|SENSORS_I2C_END
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
l_int|0x48
comma
l_int|0x4f
comma
id|SENSORS_I2C_END
)brace
suffix:semicolon
DECL|variable|normal_isa
r_static
r_int
r_int
id|normal_isa
(braket
)braket
op_assign
(brace
id|SENSORS_ISA_END
)brace
suffix:semicolon
DECL|variable|normal_isa_range
r_static
r_int
r_int
id|normal_isa_range
(braket
)braket
op_assign
(brace
id|SENSORS_ISA_END
)brace
suffix:semicolon
multiline_comment|/* Insmod parameters */
DECL|variable|lm75
id|SENSORS_INSMOD_1
c_func
(paren
id|lm75
)paren
suffix:semicolon
multiline_comment|/* Many LM75 constants specified below */
multiline_comment|/* The LM75 registers */
DECL|macro|LM75_REG_TEMP
mdefine_line|#define LM75_REG_TEMP 0x00
DECL|macro|LM75_REG_CONF
mdefine_line|#define LM75_REG_CONF 0x01
DECL|macro|LM75_REG_TEMP_HYST
mdefine_line|#define LM75_REG_TEMP_HYST 0x02
DECL|macro|LM75_REG_TEMP_OS
mdefine_line|#define LM75_REG_TEMP_OS 0x03
multiline_comment|/* Conversions. Rounding and limit checking is only done on the TO_REG&n;   variants. Note that you should be a bit careful with which arguments&n;   these macros are called: arguments may be evaluated more than once.&n;   Fixing this is just not worth it. */
DECL|macro|TEMP_FROM_REG
mdefine_line|#define TEMP_FROM_REG(val) ((((val &amp; 0x7fff) &gt;&gt; 7) * 5) | ((val &amp; 0x8000)?-256:0))
DECL|macro|TEMP_TO_REG
mdefine_line|#define TEMP_TO_REG(val)   (SENSORS_LIMIT((val&lt;0?(0x200+((val)/5))&lt;&lt;7:(((val) + 2) / 5) &lt;&lt; 7),0,0xffff))
multiline_comment|/* Initial values */
DECL|macro|LM75_INIT_TEMP_OS
mdefine_line|#define LM75_INIT_TEMP_OS 600
DECL|macro|LM75_INIT_TEMP_HYST
mdefine_line|#define LM75_INIT_TEMP_HYST 500
multiline_comment|/* Each client has this additional data */
DECL|struct|lm75_data
r_struct
id|lm75_data
(brace
DECL|member|sysctl_id
r_int
id|sysctl_id
suffix:semicolon
DECL|member|update_lock
r_struct
id|semaphore
id|update_lock
suffix:semicolon
DECL|member|valid
r_char
id|valid
suffix:semicolon
multiline_comment|/* !=0 if following fields are valid */
DECL|member|last_updated
r_int
r_int
id|last_updated
suffix:semicolon
multiline_comment|/* In jiffies */
DECL|member|temp
DECL|member|temp_os
DECL|member|temp_hyst
id|u16
id|temp
comma
id|temp_os
comma
id|temp_hyst
suffix:semicolon
multiline_comment|/* Register values */
)brace
suffix:semicolon
r_static
r_int
id|lm75_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_int
id|lm75_detect
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
suffix:semicolon
r_static
r_void
id|lm75_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
r_static
r_int
id|lm75_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
r_static
id|u16
id|swap_bytes
c_func
(paren
id|u16
id|val
)paren
suffix:semicolon
r_static
r_int
id|lm75_read_value
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|reg
)paren
suffix:semicolon
r_static
r_int
id|lm75_write_value
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|reg
comma
id|u16
id|value
)paren
suffix:semicolon
r_static
r_void
id|lm75_temp
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
id|operation
comma
r_int
id|ctl_name
comma
r_int
op_star
id|nrels_mag
comma
r_int
op_star
id|results
)paren
suffix:semicolon
r_static
r_void
id|lm75_update_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
multiline_comment|/* This is the driver that will be inserted */
DECL|variable|lm75_driver
r_static
r_struct
id|i2c_driver
id|lm75_driver
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
l_string|&quot;LM75 sensor chip driver&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_LM75
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|lm75_attach_adapter
comma
dot
id|detach_client
op_assign
id|lm75_detach_client
comma
)brace
suffix:semicolon
multiline_comment|/* These files are created for each detected LM75. This is just a template;&n;   though at first sight, you might think we could use a statically&n;   allocated list, we need some way to get back to the parent - which&n;   is done through one of the &squot;extra&squot; fields which are initialized&n;   when a new copy is allocated. */
DECL|variable|lm75_dir_table_template
r_static
id|ctl_table
id|lm75_dir_table_template
(braket
)braket
op_assign
(brace
(brace
id|LM75_SYSCTL_TEMP
comma
l_string|&quot;temp&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|i2c_proc_real
comma
op_amp
id|i2c_sysctl_real
comma
l_int|NULL
comma
op_amp
id|lm75_temp
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|lm75_id
r_static
r_int
id|lm75_id
op_assign
l_int|0
suffix:semicolon
DECL|function|lm75_attach_adapter
r_static
r_int
id|lm75_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_return
id|i2c_detect
c_func
(paren
id|adapter
comma
op_amp
id|addr_data
comma
id|lm75_detect
)paren
suffix:semicolon
)brace
multiline_comment|/* This function is called by i2c_detect */
DECL|function|lm75_detect
r_static
r_int
id|lm75_detect
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
r_int
id|i
comma
id|cur
comma
id|conf
comma
id|hyst
comma
id|os
suffix:semicolon
r_struct
id|i2c_client
op_star
id|new_client
suffix:semicolon
r_struct
id|lm75_data
op_star
id|data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|type_name
comma
op_star
id|client_name
suffix:semicolon
multiline_comment|/* Make sure we aren&squot;t probing the ISA bus!! This is just a safety check&n;&t;   at this moment; i2c_detect really won&squot;t call us. */
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|i2c_is_isa_adapter
c_func
(paren
id|adapter
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;lm75.o: lm75_detect called for an ISA bus adapter?!?&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|i2c_check_functionality
c_func
(paren
id|adapter
comma
id|I2C_FUNC_SMBUS_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
)paren
)paren
r_goto
id|error0
suffix:semicolon
multiline_comment|/* OK. For now, we presume we have a valid client. We now create the&n;&t;   client structure, even though we cannot fill it completely yet.&n;&t;   But it allows us to access lm75_{read,write}_value. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_client
)paren
op_plus
r_sizeof
(paren
r_struct
id|lm75_data
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error0
suffix:semicolon
)brace
id|data
op_assign
(paren
r_struct
id|lm75_data
op_star
)paren
(paren
id|new_client
op_plus
l_int|1
)paren
suffix:semicolon
id|new_client-&gt;addr
op_assign
id|address
suffix:semicolon
id|new_client-&gt;data
op_assign
id|data
suffix:semicolon
id|new_client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|new_client-&gt;driver
op_assign
op_amp
id|lm75_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now, we do the remaining detection. It is lousy. */
r_if
c_cond
(paren
id|kind
OL
l_int|0
)paren
(brace
id|cur
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|0
)paren
suffix:semicolon
id|conf
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
l_int|1
)paren
suffix:semicolon
id|hyst
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|2
)paren
suffix:semicolon
id|os
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|3
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|0x1f
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|i2c_smbus_read_byte_data
(paren
id|new_client
comma
id|i
op_star
l_int|8
op_plus
l_int|1
)paren
op_ne
id|conf
)paren
op_logical_or
(paren
id|i2c_smbus_read_word_data
(paren
id|new_client
comma
id|i
op_star
l_int|8
op_plus
l_int|2
)paren
op_ne
id|hyst
)paren
op_logical_or
(paren
id|i2c_smbus_read_word_data
(paren
id|new_client
comma
id|i
op_star
l_int|8
op_plus
l_int|3
)paren
op_ne
id|os
)paren
)paren
r_goto
id|error1
suffix:semicolon
)brace
multiline_comment|/* Determine the chip type - only one kind supported! */
r_if
c_cond
(paren
id|kind
op_le
l_int|0
)paren
id|kind
op_assign
id|lm75
suffix:semicolon
r_if
c_cond
(paren
id|kind
op_eq
id|lm75
)paren
(brace
id|type_name
op_assign
l_string|&quot;lm75&quot;
suffix:semicolon
id|client_name
op_assign
l_string|&quot;LM75 chip&quot;
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;lm75.o: Internal error: unknown kind (%d)?!?&quot;
comma
id|kind
)paren
suffix:semicolon
r_goto
id|error1
suffix:semicolon
)brace
multiline_comment|/* Fill in the remaining client fields and put it into the global list */
id|strcpy
c_func
(paren
id|new_client-&gt;name
comma
id|client_name
)paren
suffix:semicolon
id|new_client-&gt;id
op_assign
id|lm75_id
op_increment
suffix:semicolon
id|data-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
multiline_comment|/* Tell the I2C layer a new client has arrived */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c_attach_client
c_func
(paren
id|new_client
)paren
)paren
)paren
r_goto
id|error3
suffix:semicolon
multiline_comment|/* Register a new directory entry with module sensors */
id|i
op_assign
id|i2c_register_entry
c_func
(paren
id|new_client
comma
id|type_name
comma
id|lm75_dir_table_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|err
op_assign
id|i
suffix:semicolon
r_goto
id|error4
suffix:semicolon
)brace
id|data-&gt;sysctl_id
op_assign
id|i
suffix:semicolon
id|lm75_init_client
c_func
(paren
id|new_client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* OK, this is not exactly good programming practice, usually. But it is&n;   very code-efficient in this case. */
id|error4
suffix:colon
id|i2c_detach_client
c_func
(paren
id|new_client
)paren
suffix:semicolon
id|error3
suffix:colon
id|error1
suffix:colon
id|kfree
c_func
(paren
id|new_client
)paren
suffix:semicolon
id|error0
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|lm75_detach_client
r_static
r_int
id|lm75_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|lm75_data
op_star
id|data
op_assign
id|client-&gt;data
suffix:semicolon
id|i2c_deregister_entry
c_func
(paren
id|data-&gt;sysctl_id
)paren
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
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
DECL|function|swap_bytes
r_static
id|u16
id|swap_bytes
c_func
(paren
id|u16
id|val
)paren
(brace
r_return
(paren
id|val
op_rshift
l_int|8
)paren
op_or
(paren
id|val
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/* All registers are word-sized, except for the configuration register.&n;   LM75 uses a high-byte first convention, which is exactly opposite to&n;   the usual practice. */
DECL|function|lm75_read_value
r_static
r_int
id|lm75_read_value
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|reg
)paren
(brace
r_if
c_cond
(paren
id|reg
op_eq
id|LM75_REG_CONF
)paren
r_return
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|reg
)paren
suffix:semicolon
r_else
r_return
id|swap_bytes
c_func
(paren
id|i2c_smbus_read_word_data
c_func
(paren
id|client
comma
id|reg
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* All registers are word-sized, except for the configuration register.&n;   LM75 uses a high-byte first convention, which is exactly opposite to&n;   the usual practice. */
DECL|function|lm75_write_value
r_static
r_int
id|lm75_write_value
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|reg
comma
id|u16
id|value
)paren
(brace
r_if
c_cond
(paren
id|reg
op_eq
id|LM75_REG_CONF
)paren
r_return
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|reg
comma
id|value
)paren
suffix:semicolon
r_else
r_return
id|i2c_smbus_write_word_data
c_func
(paren
id|client
comma
id|reg
comma
id|swap_bytes
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
DECL|function|lm75_init_client
r_static
r_void
id|lm75_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
multiline_comment|/* Initialize the LM75 chip */
id|lm75_write_value
c_func
(paren
id|client
comma
id|LM75_REG_TEMP_OS
comma
id|TEMP_TO_REG
c_func
(paren
id|LM75_INIT_TEMP_OS
)paren
)paren
suffix:semicolon
id|lm75_write_value
c_func
(paren
id|client
comma
id|LM75_REG_TEMP_HYST
comma
id|TEMP_TO_REG
c_func
(paren
id|LM75_INIT_TEMP_HYST
)paren
)paren
suffix:semicolon
id|lm75_write_value
c_func
(paren
id|client
comma
id|LM75_REG_CONF
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|lm75_update_client
r_static
r_void
id|lm75_update_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|lm75_data
op_star
id|data
op_assign
id|client-&gt;data
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|jiffies
op_minus
id|data-&gt;last_updated
OG
id|HZ
op_plus
id|HZ
op_div
l_int|2
)paren
op_logical_or
(paren
id|jiffies
OL
id|data-&gt;last_updated
)paren
op_logical_or
op_logical_neg
id|data-&gt;valid
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Starting lm75 update&bslash;n&quot;
)paren
suffix:semicolon
id|data-&gt;temp
op_assign
id|lm75_read_value
c_func
(paren
id|client
comma
id|LM75_REG_TEMP
)paren
suffix:semicolon
id|data-&gt;temp_os
op_assign
id|lm75_read_value
c_func
(paren
id|client
comma
id|LM75_REG_TEMP_OS
)paren
suffix:semicolon
id|data-&gt;temp_hyst
op_assign
id|lm75_read_value
c_func
(paren
id|client
comma
id|LM75_REG_TEMP_HYST
)paren
suffix:semicolon
id|data-&gt;last_updated
op_assign
id|jiffies
suffix:semicolon
id|data-&gt;valid
op_assign
l_int|1
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
)brace
DECL|function|lm75_temp
r_static
r_void
id|lm75_temp
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
id|operation
comma
r_int
id|ctl_name
comma
r_int
op_star
id|nrels_mag
comma
r_int
op_star
id|results
)paren
(brace
r_struct
id|lm75_data
op_star
id|data
op_assign
id|client-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|operation
op_eq
id|SENSORS_PROC_REAL_INFO
)paren
op_star
id|nrels_mag
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|operation
op_eq
id|SENSORS_PROC_REAL_READ
)paren
(brace
id|lm75_update_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|results
(braket
l_int|0
)braket
op_assign
id|TEMP_FROM_REG
c_func
(paren
id|data-&gt;temp_os
)paren
suffix:semicolon
id|results
(braket
l_int|1
)braket
op_assign
id|TEMP_FROM_REG
c_func
(paren
id|data-&gt;temp_hyst
)paren
suffix:semicolon
id|results
(braket
l_int|2
)braket
op_assign
id|TEMP_FROM_REG
c_func
(paren
id|data-&gt;temp
)paren
suffix:semicolon
op_star
id|nrels_mag
op_assign
l_int|3
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|operation
op_eq
id|SENSORS_PROC_REAL_WRITE
)paren
(brace
r_if
c_cond
(paren
op_star
id|nrels_mag
op_ge
l_int|1
)paren
(brace
id|data-&gt;temp_os
op_assign
id|TEMP_TO_REG
c_func
(paren
id|results
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|lm75_write_value
c_func
(paren
id|client
comma
id|LM75_REG_TEMP_OS
comma
id|data-&gt;temp_os
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|nrels_mag
op_ge
l_int|2
)paren
(brace
id|data-&gt;temp_hyst
op_assign
id|TEMP_TO_REG
c_func
(paren
id|results
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|lm75_write_value
c_func
(paren
id|client
comma
id|LM75_REG_TEMP_HYST
comma
id|data-&gt;temp_hyst
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|sensors_lm75_init
r_static
r_int
id|__init
id|sensors_lm75_init
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|lm75_driver
)paren
suffix:semicolon
)brace
DECL|function|sensors_lm75_exit
r_static
r_void
id|__exit
id|sensors_lm75_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|lm75_driver
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
l_string|&quot;LM75 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sensors_lm75_init
id|module_init
c_func
(paren
id|sensors_lm75_init
)paren
suffix:semicolon
DECL|variable|sensors_lm75_exit
id|module_exit
c_func
(paren
id|sensors_lm75_exit
)paren
suffix:semicolon
eof
