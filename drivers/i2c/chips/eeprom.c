multiline_comment|/*&n;    eeprom.c - Part of lm_sensors, Linux kernel modules for hardware&n;               monitoring&n;    Copyright (C) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt; and&n;&t;&t;&t;       Philip Edelbrock &lt;phil@netroedge.com&gt;&n;    Copyright (C) 2003 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n;    Copyright (C) 2003 IBM Corp.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* #define DEBUG */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-sensor.h&gt;
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
l_int|0x50
comma
l_int|0x57
comma
id|I2C_CLIENT_END
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
id|I2C_CLIENT_ISA_END
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
id|I2C_CLIENT_ISA_END
)brace
suffix:semicolon
multiline_comment|/* Insmod parameters */
DECL|variable|eeprom
id|SENSORS_INSMOD_1
c_func
(paren
id|eeprom
)paren
suffix:semicolon
DECL|variable|checksum
r_static
r_int
id|checksum
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|checksum
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|checksum
comma
l_string|&quot;Only accept eeproms whose checksum is correct&quot;
)paren
suffix:semicolon
multiline_comment|/* EEPROM registers */
DECL|macro|EEPROM_REG_CHECKSUM
mdefine_line|#define EEPROM_REG_CHECKSUM&t;0x3f
multiline_comment|/* Size of EEPROM in bytes */
DECL|macro|EEPROM_SIZE
mdefine_line|#define EEPROM_SIZE&t;&t;256
multiline_comment|/* possible types of eeprom devices */
DECL|enum|eeprom_nature
r_enum
id|eeprom_nature
(brace
DECL|enumerator|UNKNOWN
id|UNKNOWN
comma
DECL|enumerator|VAIO
id|VAIO
comma
)brace
suffix:semicolon
multiline_comment|/* Each client has this additional data */
DECL|struct|eeprom_data
r_struct
id|eeprom_data
(brace
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
DECL|member|data
id|u8
id|data
(braket
id|EEPROM_SIZE
)braket
suffix:semicolon
multiline_comment|/* Register values */
DECL|member|nature
r_enum
id|eeprom_nature
id|nature
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|eeprom_attach_adapter
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
id|eeprom_detect
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
id|kind
)paren
suffix:semicolon
r_static
r_int
id|eeprom_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
multiline_comment|/* This is the driver that will be inserted */
DECL|variable|eeprom_driver
r_static
r_struct
id|i2c_driver
id|eeprom_driver
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
l_string|&quot;eeprom&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_EEPROM
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|eeprom_attach_adapter
comma
dot
id|detach_client
op_assign
id|eeprom_detach_client
comma
)brace
suffix:semicolon
DECL|variable|eeprom_id
r_static
r_int
id|eeprom_id
op_assign
l_int|0
suffix:semicolon
DECL|function|eeprom_update_client
r_static
r_void
id|eeprom_update_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|eeprom_data
op_star
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_int
id|i
comma
id|j
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
l_int|300
op_star
id|HZ
)paren
op_or
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
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Starting eeprom update&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_check_functionality
c_func
(paren
id|client-&gt;adapter
comma
id|I2C_FUNC_SMBUS_READ_I2C_BLOCK
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EEPROM_SIZE
suffix:semicolon
id|i
op_add_assign
id|I2C_SMBUS_I2C_BLOCK_MAX
)paren
r_if
c_cond
(paren
id|i2c_smbus_read_i2c_block_data
c_func
(paren
id|client
comma
id|i
comma
id|data-&gt;data
op_plus
id|i
)paren
op_ne
id|I2C_SMBUS_I2C_BLOCK_MAX
)paren
r_goto
m_exit
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|i2c_smbus_write_byte
c_func
(paren
id|client
comma
l_int|0
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;eeprom read start has failed!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EEPROM_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|i2c_smbus_read_byte
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|0
)paren
r_goto
m_exit
suffix:semicolon
id|data-&gt;data
(braket
id|i
)braket
op_assign
(paren
id|u8
)paren
id|j
suffix:semicolon
)brace
)brace
id|data-&gt;last_updated
op_assign
id|jiffies
suffix:semicolon
id|data-&gt;valid
op_assign
l_int|1
suffix:semicolon
)brace
m_exit
suffix:colon
id|up
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
)brace
DECL|function|eeprom_read
r_static
id|ssize_t
id|eeprom_read
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|i2c_client
op_star
id|client
op_assign
id|to_i2c_client
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_struct
id|eeprom_data
op_star
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|eeprom_update_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
OG
id|EEPROM_SIZE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
OG
id|EEPROM_SIZE
)paren
id|count
op_assign
id|EEPROM_SIZE
op_minus
id|off
suffix:semicolon
multiline_comment|/* Hide Vaio security settings to regular users (16 first bytes) */
r_if
c_cond
(paren
id|data-&gt;nature
op_eq
id|VAIO
op_logical_and
id|off
OL
l_int|16
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_int
id|in_row1
op_assign
l_int|16
op_minus
id|off
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|in_row1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_minus
id|in_row1
OG
l_int|0
)paren
id|memcpy
c_func
(paren
id|buf
op_plus
id|in_row1
comma
op_amp
id|data-&gt;data
(braket
l_int|16
)braket
comma
id|count
op_minus
id|in_row1
)paren
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|buf
comma
op_amp
id|data-&gt;data
(braket
id|off
)braket
comma
id|count
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|eeprom_attr
r_static
r_struct
id|bin_attribute
id|eeprom_attr
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;eeprom&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
comma
)brace
comma
dot
id|size
op_assign
id|EEPROM_SIZE
comma
dot
id|read
op_assign
id|eeprom_read
comma
)brace
suffix:semicolon
DECL|function|eeprom_attach_adapter
r_static
r_int
id|eeprom_attach_adapter
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
id|eeprom_detect
)paren
suffix:semicolon
)brace
multiline_comment|/* This function is called by i2c_detect */
DECL|function|eeprom_detect
r_int
id|eeprom_detect
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
id|kind
)paren
(brace
r_int
id|i
comma
id|cs
suffix:semicolon
r_struct
id|i2c_client
op_star
id|new_client
suffix:semicolon
r_struct
id|eeprom_data
op_star
id|data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
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
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot; eeprom_detect called for an ISA bus adapter?!?&bslash;n&quot;
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
)paren
)paren
r_goto
m_exit
suffix:semicolon
multiline_comment|/* OK. For now, we presume we have a valid client. We now create the&n;&t;   client structure, even though we cannot fill it completely yet.&n;&t;   But it allows us to access eeprom_{read,write}_value. */
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
id|eeprom_data
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
m_exit
suffix:semicolon
)brace
id|memset
c_func
(paren
id|new_client
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
op_plus
r_sizeof
(paren
r_struct
id|eeprom_data
)paren
)paren
suffix:semicolon
id|data
op_assign
(paren
r_struct
id|eeprom_data
op_star
)paren
(paren
id|new_client
op_plus
l_int|1
)paren
suffix:semicolon
id|memset
c_func
(paren
id|data
comma
l_int|0xff
comma
id|EEPROM_SIZE
)paren
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
id|new_client
comma
id|data
)paren
suffix:semicolon
id|new_client-&gt;addr
op_assign
id|address
suffix:semicolon
id|new_client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|new_client-&gt;driver
op_assign
op_amp
id|eeprom_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now, we do the remaining detection. It is not there, unless you force&n;&t;   the checksum to work out. */
r_if
c_cond
(paren
id|checksum
)paren
(brace
multiline_comment|/* prevent 24RF08 corruption */
id|i2c_smbus_write_quick
c_func
(paren
id|new_client
comma
l_int|0
)paren
suffix:semicolon
id|cs
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
id|i
op_le
l_int|0x3e
suffix:semicolon
id|i
op_increment
)paren
id|cs
op_add_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|i
)paren
suffix:semicolon
id|cs
op_and_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_read_byte_data
(paren
id|new_client
comma
id|EEPROM_REG_CHECKSUM
)paren
op_ne
id|cs
)paren
r_goto
id|exit_kfree
suffix:semicolon
)brace
id|data-&gt;nature
op_assign
id|UNKNOWN
suffix:semicolon
multiline_comment|/* Detect the Vaio nature of EEPROMs.&n;&t;   We use the &quot;PCG-&quot; prefix as the signature. */
r_if
c_cond
(paren
id|address
op_eq
l_int|0x57
)paren
(brace
r_if
c_cond
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
l_int|0x80
)paren
op_eq
l_char|&squot;P&squot;
op_logical_and
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
l_int|0x81
)paren
op_eq
l_char|&squot;C&squot;
op_logical_and
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
l_int|0x82
)paren
op_eq
l_char|&squot;G&squot;
op_logical_and
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
l_int|0x83
)paren
op_eq
l_char|&squot;-&squot;
)paren
id|data-&gt;nature
op_assign
id|VAIO
suffix:semicolon
)brace
multiline_comment|/* Fill in the remaining client fields */
id|strncpy
c_func
(paren
id|new_client-&gt;name
comma
l_string|&quot;eeprom&quot;
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
id|new_client-&gt;id
op_assign
id|eeprom_id
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
id|exit_kfree
suffix:semicolon
multiline_comment|/* create the sysfs eeprom file */
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|new_client-&gt;dev.kobj
comma
op_amp
id|eeprom_attr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|exit_kfree
suffix:colon
id|kfree
c_func
(paren
id|new_client
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|eeprom_detach_client
r_static
r_int
id|eeprom_detach_client
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
suffix:semicolon
id|err
op_assign
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Client deregistration failed, client not detached.&bslash;n&quot;
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
DECL|function|eeprom_init
r_static
r_int
id|__init
id|eeprom_init
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
id|eeprom_driver
)paren
suffix:semicolon
)brace
DECL|function|eeprom_exit
r_static
r_void
id|__exit
id|eeprom_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|eeprom_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt; and &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt; and &quot;
l_string|&quot;Greg Kroah-Hartman &lt;greg@kroah.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C EEPROM driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|eeprom_init
id|module_init
c_func
(paren
id|eeprom_init
)paren
suffix:semicolon
DECL|variable|eeprom_exit
id|module_exit
c_func
(paren
id|eeprom_exit
)paren
suffix:semicolon
eof
