multiline_comment|/*&n; * lm83.c - Part of lm_sensors, Linux kernel modules for hardware&n; *          monitoring&n; * Copyright (C) 2003  Jean Delvare &lt;khali@linux-fr.org&gt;&n; *&n; * Heavily inspired from the lm78, lm75 and adm1021 drivers. The LM83 is&n; * a sensor chip made by National Semiconductor. It reports up to four&n; * temperatures (its own plus up to three external ones) with a 1 deg&n; * resolution and a 3-4 deg accuracy. Complete datasheet can be obtained&n; * from National&squot;s website at:&n; *   http://www.national.com/pf/LM/LM83.html&n; * Since the datasheet omits to give the chip stepping code, I give it&n; * here: 0x03 (at register 0xff).&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-sensor.h&gt;
multiline_comment|/*&n; * Addresses to scan&n; * Address is selected using 2 three-level pins, resulting in 9 possible&n; * addresses.&n; */
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
l_int|0x18
comma
l_int|0x1a
comma
l_int|0x29
comma
l_int|0x2b
comma
l_int|0x4c
comma
l_int|0x4e
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
multiline_comment|/*&n; * Insmod parameters&n; */
DECL|variable|lm83
id|SENSORS_INSMOD_1
c_func
(paren
id|lm83
)paren
suffix:semicolon
multiline_comment|/*&n; * The LM83 registers&n; * Manufacturer ID is 0x01 for National Semiconductor.&n; */
DECL|macro|LM83_REG_R_MAN_ID
mdefine_line|#define LM83_REG_R_MAN_ID&t;&t;0xFE
DECL|macro|LM83_REG_R_CHIP_ID
mdefine_line|#define LM83_REG_R_CHIP_ID&t;&t;0xFF
DECL|macro|LM83_REG_R_CONFIG
mdefine_line|#define LM83_REG_R_CONFIG&t;&t;0x03
DECL|macro|LM83_REG_W_CONFIG
mdefine_line|#define LM83_REG_W_CONFIG&t;&t;0x09
DECL|macro|LM83_REG_R_STATUS1
mdefine_line|#define LM83_REG_R_STATUS1&t;&t;0x02
DECL|macro|LM83_REG_R_STATUS2
mdefine_line|#define LM83_REG_R_STATUS2&t;&t;0x35
DECL|macro|LM83_REG_R_LOCAL_TEMP
mdefine_line|#define LM83_REG_R_LOCAL_TEMP&t;&t;0x00
DECL|macro|LM83_REG_R_LOCAL_HIGH
mdefine_line|#define LM83_REG_R_LOCAL_HIGH&t;&t;0x05
DECL|macro|LM83_REG_W_LOCAL_HIGH
mdefine_line|#define LM83_REG_W_LOCAL_HIGH&t;&t;0x0B
DECL|macro|LM83_REG_R_REMOTE1_TEMP
mdefine_line|#define LM83_REG_R_REMOTE1_TEMP&t;&t;0x30
DECL|macro|LM83_REG_R_REMOTE1_HIGH
mdefine_line|#define LM83_REG_R_REMOTE1_HIGH&t;&t;0x38
DECL|macro|LM83_REG_W_REMOTE1_HIGH
mdefine_line|#define LM83_REG_W_REMOTE1_HIGH&t;&t;0x50
DECL|macro|LM83_REG_R_REMOTE2_TEMP
mdefine_line|#define LM83_REG_R_REMOTE2_TEMP&t;&t;0x01
DECL|macro|LM83_REG_R_REMOTE2_HIGH
mdefine_line|#define LM83_REG_R_REMOTE2_HIGH&t;&t;0x07
DECL|macro|LM83_REG_W_REMOTE2_HIGH
mdefine_line|#define LM83_REG_W_REMOTE2_HIGH&t;&t;0x0D
DECL|macro|LM83_REG_R_REMOTE3_TEMP
mdefine_line|#define LM83_REG_R_REMOTE3_TEMP&t;&t;0x31
DECL|macro|LM83_REG_R_REMOTE3_HIGH
mdefine_line|#define LM83_REG_R_REMOTE3_HIGH&t;&t;0x3A
DECL|macro|LM83_REG_W_REMOTE3_HIGH
mdefine_line|#define LM83_REG_W_REMOTE3_HIGH&t;&t;0x52
DECL|macro|LM83_REG_R_TCRIT
mdefine_line|#define LM83_REG_R_TCRIT&t;&t;0x42
DECL|macro|LM83_REG_W_TCRIT
mdefine_line|#define LM83_REG_W_TCRIT&t;&t;0x5A
multiline_comment|/*&n; * Conversions and various macros&n; * The LM83 uses signed 8-bit values with LSB = 1 degree Celcius.&n; */
DECL|macro|TEMP_FROM_REG
mdefine_line|#define TEMP_FROM_REG(val)&t;((val) * 1000)
DECL|macro|TEMP_TO_REG
mdefine_line|#define TEMP_TO_REG(val)&t;((val) &lt;= -128000 ? -128 : &bslash;&n;&t;&t;&t;&t; (val) &gt;= 127000 ? 127 : &bslash;&n;&t;&t;&t;&t; (val) &lt; 0 ? ((val) - 500) / 1000 : &bslash;&n;&t;&t;&t;&t; ((val) + 500) / 1000)
DECL|variable|LM83_REG_R_TEMP
r_static
r_const
id|u8
id|LM83_REG_R_TEMP
(braket
)braket
op_assign
(brace
id|LM83_REG_R_LOCAL_TEMP
comma
id|LM83_REG_R_REMOTE1_TEMP
comma
id|LM83_REG_R_REMOTE2_TEMP
comma
id|LM83_REG_R_REMOTE3_TEMP
)brace
suffix:semicolon
DECL|variable|LM83_REG_R_HIGH
r_static
r_const
id|u8
id|LM83_REG_R_HIGH
(braket
)braket
op_assign
(brace
id|LM83_REG_R_LOCAL_HIGH
comma
id|LM83_REG_R_REMOTE1_HIGH
comma
id|LM83_REG_R_REMOTE2_HIGH
comma
id|LM83_REG_R_REMOTE3_HIGH
)brace
suffix:semicolon
DECL|variable|LM83_REG_W_HIGH
r_static
r_const
id|u8
id|LM83_REG_W_HIGH
(braket
)braket
op_assign
(brace
id|LM83_REG_W_LOCAL_HIGH
comma
id|LM83_REG_W_REMOTE1_HIGH
comma
id|LM83_REG_W_REMOTE2_HIGH
comma
id|LM83_REG_W_REMOTE3_HIGH
)brace
suffix:semicolon
multiline_comment|/*&n; * Functions declaration&n; */
r_static
r_int
id|lm83_attach_adapter
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
id|lm83_detect
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
id|lm83_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
r_static
r_struct
id|lm83_data
op_star
id|lm83_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Driver data (common to all clients)&n; */
DECL|variable|lm83_driver
r_static
r_struct
id|i2c_driver
id|lm83_driver
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
l_string|&quot;lm83&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_LM83
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|lm83_attach_adapter
comma
dot
id|detach_client
op_assign
id|lm83_detach_client
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Client data (each client gets its own)&n; */
DECL|struct|lm83_data
r_struct
id|lm83_data
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
DECL|member|temp_input
id|s8
id|temp_input
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|temp_high
id|s8
id|temp_high
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|temp_crit
id|s8
id|temp_crit
suffix:semicolon
DECL|member|alarms
id|u16
id|alarms
suffix:semicolon
multiline_comment|/* bitvector, combined */
)brace
suffix:semicolon
multiline_comment|/*&n; * Internal variables&n; */
DECL|variable|lm83_id
r_static
r_int
id|lm83_id
suffix:semicolon
multiline_comment|/*&n; * Sysfs stuff&n; */
DECL|macro|show_temp
mdefine_line|#define show_temp(suffix, value) &bslash;&n;static ssize_t show_temp_##suffix(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;struct lm83_data *data = lm83_update_device(dev); &bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, TEMP_FROM_REG(data-&gt;value)); &bslash;&n;}
id|show_temp
c_func
(paren
id|input1
comma
id|temp_input
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|input2
comma
id|temp_input
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|input3
comma
id|temp_input
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|input4
comma
id|temp_input
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|high1
comma
id|temp_high
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|high2
comma
id|temp_high
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|high3
comma
id|temp_high
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|high4
comma
id|temp_high
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|crit
comma
id|temp_crit
)paren
suffix:semicolon
DECL|macro|set_temp
mdefine_line|#define set_temp(suffix, value, reg) &bslash;&n;static ssize_t set_temp_##suffix(struct device *dev, const char *buf, &bslash;&n;&t;size_t count) &bslash;&n;{ &bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev); &bslash;&n;&t;struct lm83_data *data = i2c_get_clientdata(client); &bslash;&n;&t;long val = simple_strtol(buf, NULL, 10); &bslash;&n;&t;data-&gt;value = TEMP_TO_REG(val); &bslash;&n;&t;i2c_smbus_write_byte_data(client, reg, data-&gt;value); &bslash;&n;&t;return count; &bslash;&n;}
id|set_temp
c_func
(paren
id|high1
comma
id|temp_high
(braket
l_int|0
)braket
comma
id|LM83_REG_W_LOCAL_HIGH
)paren
suffix:semicolon
id|set_temp
c_func
(paren
id|high2
comma
id|temp_high
(braket
l_int|1
)braket
comma
id|LM83_REG_W_REMOTE1_HIGH
)paren
suffix:semicolon
id|set_temp
c_func
(paren
id|high3
comma
id|temp_high
(braket
l_int|2
)braket
comma
id|LM83_REG_W_REMOTE2_HIGH
)paren
suffix:semicolon
id|set_temp
c_func
(paren
id|high4
comma
id|temp_high
(braket
l_int|3
)braket
comma
id|LM83_REG_W_REMOTE3_HIGH
)paren
suffix:semicolon
id|set_temp
c_func
(paren
id|crit
comma
id|temp_crit
comma
id|LM83_REG_W_TCRIT
)paren
suffix:semicolon
DECL|function|show_alarms
r_static
id|ssize_t
id|show_alarms
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
id|lm83_data
op_star
id|data
op_assign
id|lm83_update_device
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
id|data-&gt;alarms
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
id|show_temp_input1
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp2_input
comma
id|S_IRUGO
comma
id|show_temp_input2
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp3_input
comma
id|S_IRUGO
comma
id|show_temp_input3
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp4_input
comma
id|S_IRUGO
comma
id|show_temp_input4
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_max
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_high1
comma
id|set_temp_high1
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp2_max
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_high2
comma
id|set_temp_high2
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp3_max
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_high3
comma
id|set_temp_high3
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp4_max
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_high4
comma
id|set_temp_high4
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_crit
comma
id|S_IRUGO
comma
id|show_temp_crit
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp2_crit
comma
id|S_IRUGO
comma
id|show_temp_crit
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp3_crit
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_crit
comma
id|set_temp_crit
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp4_crit
comma
id|S_IRUGO
comma
id|show_temp_crit
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|alarms
comma
id|S_IRUGO
comma
id|show_alarms
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n; * Real code&n; */
DECL|function|lm83_attach_adapter
r_static
r_int
id|lm83_attach_adapter
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
id|lm83_detect
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following function does more than just detection. If detection&n; * succeeds, it also registers the new chip.&n; */
DECL|function|lm83_detect
r_static
r_int
id|lm83_detect
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
id|lm83_data
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
id|name
op_assign
l_string|&quot;&quot;
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
id|lm83_data
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
id|lm83_data
)paren
)paren
suffix:semicolon
multiline_comment|/* The common I2C client data is placed right after the&n;&t; * LM83-specific data. */
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
id|lm83_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now we do the detection and identification. A negative kind&n;&t; * means that the driver was loaded with no force parameter&n;&t; * (default), so we must both detect and identify the chip&n;&t; * (actually there is only one possible kind of chip for now, LM83).&n;&t; * A zero kind means that the driver was loaded with the force&n;&t; * parameter, the detection step shall be skipped. A positive kind&n;&t; * means that the driver was loaded with the force parameter and a&n;&t; * given kind of chip is requested, so both the detection and the&n;&t; * identification steps are skipped. */
multiline_comment|/* Default to an LM83 if forced */
r_if
c_cond
(paren
id|kind
op_eq
l_int|0
)paren
id|kind
op_assign
id|lm83
suffix:semicolon
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
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM83_REG_R_STATUS1
)paren
op_amp
l_int|0xA8
)paren
op_ne
l_int|0x00
)paren
op_logical_or
(paren
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM83_REG_R_STATUS2
)paren
op_amp
l_int|0x48
)paren
op_ne
l_int|0x00
)paren
op_logical_or
(paren
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM83_REG_R_CONFIG
)paren
op_amp
l_int|0x41
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
l_string|&quot;LM83 detection failed at 0x%02x.&bslash;n&quot;
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
id|u8
id|man_id
comma
id|chip_id
suffix:semicolon
id|man_id
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM83_REG_R_MAN_ID
)paren
suffix:semicolon
id|chip_id
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM83_REG_R_CHIP_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|man_id
op_eq
l_int|0x01
)paren
(brace
multiline_comment|/* National Semiconductor */
r_if
c_cond
(paren
id|chip_id
op_eq
l_int|0x03
)paren
(brace
id|kind
op_assign
id|lm83
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
l_string|&quot;Unsupported chip (man_id=0x%02X, &quot;
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
r_if
c_cond
(paren
id|kind
op_eq
id|lm83
)paren
(brace
id|name
op_assign
l_string|&quot;lm83&quot;
suffix:semicolon
)brace
multiline_comment|/* We can fill in the remaining client fields */
id|strlcpy
c_func
(paren
id|new_client-&gt;name
comma
id|name
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
id|new_client-&gt;id
op_assign
id|lm83_id
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
id|exit_free
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the LM83 chip&n;&t; * (Nothing to do for this one.)&n;&t; */
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
id|dev_attr_temp2_input
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp3_input
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp4_input
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
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp2_max
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp3_max
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp4_max
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp1_crit
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp2_crit
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp3_crit
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp4_crit
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_alarms
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
DECL|function|lm83_detach_client
r_static
r_int
id|lm83_detach_client
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
DECL|function|lm83_update_device
r_static
r_struct
id|lm83_data
op_star
id|lm83_update_device
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
id|lm83_data
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
op_logical_or
op_logical_neg
id|data-&gt;valid
)paren
(brace
r_int
id|nr
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Updating lm83 data.&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
l_int|0
suffix:semicolon
id|nr
OL
l_int|4
suffix:semicolon
id|nr
op_increment
)paren
(brace
id|data-&gt;temp_input
(braket
id|nr
)braket
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM83_REG_R_TEMP
(braket
id|nr
)braket
)paren
suffix:semicolon
id|data-&gt;temp_high
(braket
id|nr
)braket
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM83_REG_R_HIGH
(braket
id|nr
)braket
)paren
suffix:semicolon
)brace
id|data-&gt;temp_crit
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM83_REG_R_TCRIT
)paren
suffix:semicolon
id|data-&gt;alarms
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM83_REG_R_STATUS1
)paren
op_plus
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM83_REG_R_STATUS2
)paren
op_lshift
l_int|8
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
DECL|function|sensors_lm83_init
r_static
r_int
id|__init
id|sensors_lm83_init
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
id|lm83_driver
)paren
suffix:semicolon
)brace
DECL|function|sensors_lm83_exit
r_static
r_void
id|__exit
id|sensors_lm83_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|lm83_driver
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
l_string|&quot;LM83 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sensors_lm83_init
id|module_init
c_func
(paren
id|sensors_lm83_init
)paren
suffix:semicolon
DECL|variable|sensors_lm83_exit
id|module_exit
c_func
(paren
id|sensors_lm83_exit
)paren
suffix:semicolon
eof
