multiline_comment|/*&n; * w83l785ts.c - Part of lm_sensors, Linux kernel modules for hardware&n; *               monitoring&n; * Copyright (C) 2003-2004  Jean Delvare &lt;khali@linux-fr.org&gt;&n; *&n; * Inspired from the lm83 driver. The W83L785TS-S is a sensor chip made&n; * by Winbond. It reports a single external temperature with a 1 deg&n; * resolution and a 3 deg accuracy. Datasheet can be obtained from&n; * Winbond&squot;s website at:&n; *   http://www.winbond-usa.com/products/winbond_products/pdfs/PCIC/W83L785TS-S.pdf&n; *&n; * Ported to Linux 2.6 by Wolfgang Ziegler &lt;nuppla@gmx.at&gt; and Jean Delvare&n; * &lt;khali@linux-fr.org&gt;.&n; *&n; * Thanks to James Bolt &lt;james@evilpenguin.com&gt; for benchmarking the read&n; * error handling mechanism.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-sensor.h&gt;
multiline_comment|/* How many retries on register read error */
DECL|macro|MAX_RETRIES
mdefine_line|#define MAX_RETRIES&t;5
multiline_comment|/*&n; * Address to scan&n; * Address is fully defined internally and cannot be changed.&n; */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
l_int|0x2e
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
multiline_comment|/*&n; * Insmod parameters&n; */
DECL|variable|w83l785ts
id|SENSORS_INSMOD_1
c_func
(paren
id|w83l785ts
)paren
suffix:semicolon
multiline_comment|/*&n; * The W83L785TS-S registers&n; * Manufacturer ID is 0x5CA3 for Winbond.&n; */
DECL|macro|W83L785TS_REG_MAN_ID1
mdefine_line|#define W83L785TS_REG_MAN_ID1&t;&t;0x4D
DECL|macro|W83L785TS_REG_MAN_ID2
mdefine_line|#define W83L785TS_REG_MAN_ID2&t;&t;0x4C
DECL|macro|W83L785TS_REG_CHIP_ID
mdefine_line|#define W83L785TS_REG_CHIP_ID&t;&t;0x4E
DECL|macro|W83L785TS_REG_CONFIG
mdefine_line|#define W83L785TS_REG_CONFIG&t;&t;0x40
DECL|macro|W83L785TS_REG_TYPE
mdefine_line|#define W83L785TS_REG_TYPE&t;&t;0x52
DECL|macro|W83L785TS_REG_TEMP
mdefine_line|#define W83L785TS_REG_TEMP&t;&t;0x27
DECL|macro|W83L785TS_REG_TEMP_OVER
mdefine_line|#define W83L785TS_REG_TEMP_OVER&t;&t;0x53 /* not sure about this one */
multiline_comment|/*&n; * Conversions&n; * The W83L785TS-S uses signed 8-bit values.&n; */
DECL|macro|TEMP_FROM_REG
mdefine_line|#define TEMP_FROM_REG(val)&t;((val &amp; 0x80 ? val-0x100 : val) * 1000)
multiline_comment|/*&n; * Functions declaration&n; */
r_static
r_int
id|w83l785ts_attach_adapter
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
id|w83l785ts_detect
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
id|w83l785ts_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
r_static
id|u8
id|w83l785ts_read_value
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
id|u8
id|defval
)paren
suffix:semicolon
r_static
r_struct
id|w83l785ts_data
op_star
id|w83l785ts_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Driver data (common to all clients)&n; */
DECL|variable|w83l785ts_driver
r_static
r_struct
id|i2c_driver
id|w83l785ts_driver
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
l_string|&quot;w83l785ts&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_W83L785TS
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|w83l785ts_attach_adapter
comma
dot
id|detach_client
op_assign
id|w83l785ts_detach_client
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Client data (each client gets its own)&n; */
DECL|struct|w83l785ts_data
r_struct
id|w83l785ts_data
(brace
DECL|member|client
r_struct
id|i2c_client
id|client
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
multiline_comment|/* zero until following fields are valid */
DECL|member|last_updated
r_int
r_int
id|last_updated
suffix:semicolon
multiline_comment|/* in jiffies */
multiline_comment|/* registers values */
DECL|member|temp
DECL|member|temp_over
id|u8
id|temp
comma
id|temp_over
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Internal variables&n; */
DECL|variable|w83l785ts_id
r_static
r_int
id|w83l785ts_id
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Sysfs stuff&n; */
DECL|function|show_temp
r_static
id|ssize_t
id|show_temp
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|w83l785ts_data
op_star
id|data
op_assign
id|w83l785ts_update_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|TEMP_FROM_REG
c_func
(paren
id|data-&gt;temp
)paren
)paren
suffix:semicolon
)brace
DECL|function|show_temp_over
r_static
id|ssize_t
id|show_temp_over
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|w83l785ts_data
op_star
id|data
op_assign
id|w83l785ts_update_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|TEMP_FROM_REG
c_func
(paren
id|data-&gt;temp_over
)paren
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_input
comma
id|S_IRUGO
comma
id|show_temp
comma
l_int|NULL
)paren
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_max
comma
id|S_IRUGO
comma
id|show_temp_over
comma
l_int|NULL
)paren
multiline_comment|/*&n; * Real code&n; */
DECL|function|w83l785ts_attach_adapter
r_static
r_int
id|w83l785ts_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|adapter
op_member_access_from_pointer
r_class
op_amp
id|I2C_CLASS_HWMON
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|i2c_detect
c_func
(paren
id|adapter
comma
op_amp
id|addr_data
comma
id|w83l785ts_detect
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following function does more than just detection. If detection&n; * succeeds, it also registers the new chip.&n; */
DECL|function|w83l785ts_detect
r_static
r_int
id|w83l785ts_detect
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
r_struct
id|i2c_client
op_star
id|new_client
suffix:semicolon
r_struct
id|w83l785ts_data
op_star
id|data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|w83l785ts_data
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
id|data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|w83l785ts_data
)paren
)paren
suffix:semicolon
multiline_comment|/* The common I2C client data is placed right before the&n;&t; * W83L785TS-specific data. */
id|new_client
op_assign
op_amp
id|data-&gt;client
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
id|w83l785ts_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Now we do the remaining detection. A negative kind means that&n;&t; * the driver was loaded with no force parameter (default), so we&n;&t; * must both detect and identify the chip (actually there is only&n;&t; * one possible kind of chip for now, W83L785TS-S). A zero kind means&n;&t; * that the driver was loaded with the force parameter, the detection&n;&t; * step shall be skipped. A positive kind means that the driver&n;&t; * was loaded with the force parameter and a given kind of chip is&n;&t; * requested, so both the detection and the identification steps&n;&t; * are skipped.&n;&t; */
r_if
c_cond
(paren
id|kind
OL
l_int|0
)paren
(brace
multiline_comment|/* detection */
r_if
c_cond
(paren
(paren
(paren
id|w83l785ts_read_value
c_func
(paren
id|new_client
comma
id|W83L785TS_REG_CONFIG
comma
l_int|0
)paren
op_amp
l_int|0x80
)paren
op_ne
l_int|0x00
)paren
op_logical_or
(paren
(paren
id|w83l785ts_read_value
c_func
(paren
id|new_client
comma
id|W83L785TS_REG_TYPE
comma
l_int|0
)paren
op_amp
l_int|0xFC
)paren
op_ne
l_int|0x00
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;W83L785TS-S detection failed at 0x%02x.&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
r_goto
id|exit_free
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|kind
op_le
l_int|0
)paren
(brace
multiline_comment|/* identification */
id|u16
id|man_id
suffix:semicolon
id|u8
id|chip_id
suffix:semicolon
id|man_id
op_assign
(paren
id|w83l785ts_read_value
c_func
(paren
id|new_client
comma
id|W83L785TS_REG_MAN_ID1
comma
l_int|0
)paren
op_lshift
l_int|8
)paren
op_plus
id|w83l785ts_read_value
c_func
(paren
id|new_client
comma
id|W83L785TS_REG_MAN_ID2
comma
l_int|0
)paren
suffix:semicolon
id|chip_id
op_assign
id|w83l785ts_read_value
c_func
(paren
id|new_client
comma
id|W83L785TS_REG_CHIP_ID
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|man_id
op_eq
l_int|0x5CA3
)paren
(brace
multiline_comment|/* Winbond */
r_if
c_cond
(paren
id|chip_id
op_eq
l_int|0x70
)paren
(brace
multiline_comment|/* W83L785TS-S */
id|kind
op_assign
id|w83l785ts
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|kind
op_le
l_int|0
)paren
(brace
multiline_comment|/* identification failed */
id|dev_info
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;Unsupported chip (man_id=0x%04X, &quot;
l_string|&quot;chip_id=0x%02X).&bslash;n&quot;
comma
id|man_id
comma
id|chip_id
)paren
suffix:semicolon
r_goto
id|exit_free
suffix:semicolon
)brace
)brace
multiline_comment|/* We can fill in the remaining client fields. */
id|strlcpy
c_func
(paren
id|new_client-&gt;name
comma
l_string|&quot;w83l785ts&quot;
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
id|new_client-&gt;id
op_assign
id|w83l785ts_id
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
multiline_comment|/* Default values in case the first read fails (unlikely). */
id|data-&gt;temp_over
op_assign
id|data-&gt;temp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Tell the I2C layer a new client has arrived. */
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
id|exit_free
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the W83L785TS chip&n;&t; * Nothing yet, assume it is already started.&n;&t; */
multiline_comment|/* Register sysfs hooks */
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp1_input
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp1_max
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|exit_free
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|w83l785ts_detach_client
r_static
r_int
id|w83l785ts_detach_client
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
r_if
c_cond
(paren
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
id|dev_err
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Client deregistration failed, &quot;
l_string|&quot;client not detached.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|w83l785ts_read_value
r_static
id|u8
id|w83l785ts_read_value
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
id|u8
id|defval
)paren
(brace
r_int
id|value
comma
id|i
suffix:semicolon
multiline_comment|/* Frequent read errors have been reported on Asus boards, so we&n;&t; * retry on read errors. If it still fails (unlikely), return the&n;&t; * default value requested by the caller. */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|MAX_RETRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|value
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_ge
l_int|0
)paren
r_return
id|value
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Read failed, will retry in %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|dev_err
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Couldn&squot;t read value from register. &quot;
l_string|&quot;Please report.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|defval
suffix:semicolon
)brace
DECL|function|w83l785ts_update_device
r_static
r_struct
id|w83l785ts_data
op_star
id|w83l785ts_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
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
id|dev
)paren
suffix:semicolon
r_struct
id|w83l785ts_data
op_star
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
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
op_logical_neg
id|data-&gt;valid
op_logical_or
(paren
id|jiffies
op_minus
id|data-&gt;last_updated
OG
id|HZ
op_star
l_int|2
)paren
op_logical_or
(paren
id|jiffies
OL
id|data-&gt;last_updated
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Updating w83l785ts data.&bslash;n&quot;
)paren
suffix:semicolon
id|data-&gt;temp
op_assign
id|w83l785ts_read_value
c_func
(paren
id|client
comma
id|W83L785TS_REG_TEMP
comma
id|data-&gt;temp
)paren
suffix:semicolon
id|data-&gt;temp_over
op_assign
id|w83l785ts_read_value
c_func
(paren
id|client
comma
id|W83L785TS_REG_TEMP_OVER
comma
id|data-&gt;temp_over
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
r_return
id|data
suffix:semicolon
)brace
DECL|function|sensors_w83l785ts_init
r_static
r_int
id|__init
id|sensors_w83l785ts_init
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
id|w83l785ts_driver
)paren
suffix:semicolon
)brace
DECL|function|sensors_w83l785ts_exit
r_static
r_void
id|__exit
id|sensors_w83l785ts_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|w83l785ts_driver
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
l_string|&quot;W83L785TS-S driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sensors_w83l785ts_init
id|module_init
c_func
(paren
id|sensors_w83l785ts_init
)paren
suffix:semicolon
DECL|variable|sensors_w83l785ts_exit
id|module_exit
c_func
(paren
id|sensors_w83l785ts_exit
)paren
suffix:semicolon
eof
