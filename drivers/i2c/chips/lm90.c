multiline_comment|/*&n; * lm90.c - Part of lm_sensors, Linux kernel modules for hardware&n; *          monitoring&n; * Copyright (C) 2003  Jean Delvare &lt;khali@linux-fr.org&gt;&n; *&n; * Based on the lm83 driver. The LM90 is a sensor chip made by National&n; * Semiconductor. It reports up to two temperatures (its own plus up to&n; * one external one) with a 0.125 deg resolution (1 deg for local&n; * temperature) and a 3-4 deg accuracy. Complete datasheet can be&n; * obtained from National&squot;s website at:&n; *   http://www.national.com/pf/LM/LM90.html&n; *&n; * This driver also supports the ADM1032, a sensor chip made by Analog&n; * Devices. That chip is similar to the LM90, with a few differences&n; * that are not handled by this driver. Complete datasheet can be&n; * obtained from Analog&squot;s website at:&n; *   http://products.analog.com/products/info.asp?product=ADM1032&n; *&n; * Since the LM90 was the first chipset supported by this driver, most&n; * comments will refer to this chipset, but are actually general and&n; * concern all supported chipsets, unless mentioned otherwise.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_I2C_DEBUG_CHIP
DECL|macro|DEBUG
mdefine_line|#define DEBUG&t;1
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-sensor.h&gt;
multiline_comment|/*&n; * Addresses to scan&n; * Address is fully defined internally and cannot be changed.&n; */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
l_int|0x4c
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
id|SENSORS_INSMOD_2
c_func
(paren
id|lm90
comma
id|adm1032
)paren
suffix:semicolon
multiline_comment|/*&n; * The LM90 registers&n; */
DECL|macro|LM90_REG_R_MAN_ID
mdefine_line|#define LM90_REG_R_MAN_ID&t;&t;0xFE
DECL|macro|LM90_REG_R_CHIP_ID
mdefine_line|#define LM90_REG_R_CHIP_ID&t;&t;0xFF
DECL|macro|LM90_REG_R_CONFIG1
mdefine_line|#define LM90_REG_R_CONFIG1&t;&t;0x03
DECL|macro|LM90_REG_W_CONFIG1
mdefine_line|#define LM90_REG_W_CONFIG1&t;&t;0x09
DECL|macro|LM90_REG_R_CONFIG2
mdefine_line|#define LM90_REG_R_CONFIG2&t;&t;0xBF
DECL|macro|LM90_REG_W_CONFIG2
mdefine_line|#define LM90_REG_W_CONFIG2&t;&t;0xBF
DECL|macro|LM90_REG_R_CONVRATE
mdefine_line|#define LM90_REG_R_CONVRATE&t;&t;0x04
DECL|macro|LM90_REG_W_CONVRATE
mdefine_line|#define LM90_REG_W_CONVRATE&t;&t;0x0A
DECL|macro|LM90_REG_R_STATUS
mdefine_line|#define LM90_REG_R_STATUS&t;&t;0x02
DECL|macro|LM90_REG_R_LOCAL_TEMP
mdefine_line|#define LM90_REG_R_LOCAL_TEMP&t;&t;0x00
DECL|macro|LM90_REG_R_LOCAL_HIGH
mdefine_line|#define LM90_REG_R_LOCAL_HIGH&t;&t;0x05
DECL|macro|LM90_REG_W_LOCAL_HIGH
mdefine_line|#define LM90_REG_W_LOCAL_HIGH&t;&t;0x0B
DECL|macro|LM90_REG_R_LOCAL_LOW
mdefine_line|#define LM90_REG_R_LOCAL_LOW&t;&t;0x06
DECL|macro|LM90_REG_W_LOCAL_LOW
mdefine_line|#define LM90_REG_W_LOCAL_LOW&t;&t;0x0C
DECL|macro|LM90_REG_R_LOCAL_CRIT
mdefine_line|#define LM90_REG_R_LOCAL_CRIT&t;&t;0x20
DECL|macro|LM90_REG_W_LOCAL_CRIT
mdefine_line|#define LM90_REG_W_LOCAL_CRIT&t;&t;0x20
DECL|macro|LM90_REG_R_REMOTE_TEMPH
mdefine_line|#define LM90_REG_R_REMOTE_TEMPH&t;&t;0x01
DECL|macro|LM90_REG_R_REMOTE_TEMPL
mdefine_line|#define LM90_REG_R_REMOTE_TEMPL&t;&t;0x10
DECL|macro|LM90_REG_R_REMOTE_OFFSH
mdefine_line|#define LM90_REG_R_REMOTE_OFFSH&t;&t;0x11
DECL|macro|LM90_REG_W_REMOTE_OFFSH
mdefine_line|#define LM90_REG_W_REMOTE_OFFSH&t;&t;0x11
DECL|macro|LM90_REG_R_REMOTE_OFFSL
mdefine_line|#define LM90_REG_R_REMOTE_OFFSL&t;&t;0x12
DECL|macro|LM90_REG_W_REMOTE_OFFSL
mdefine_line|#define LM90_REG_W_REMOTE_OFFSL&t;&t;0x12
DECL|macro|LM90_REG_R_REMOTE_HIGHH
mdefine_line|#define LM90_REG_R_REMOTE_HIGHH&t;&t;0x07
DECL|macro|LM90_REG_W_REMOTE_HIGHH
mdefine_line|#define LM90_REG_W_REMOTE_HIGHH&t;&t;0x0D
DECL|macro|LM90_REG_R_REMOTE_HIGHL
mdefine_line|#define LM90_REG_R_REMOTE_HIGHL&t;&t;0x13
DECL|macro|LM90_REG_W_REMOTE_HIGHL
mdefine_line|#define LM90_REG_W_REMOTE_HIGHL&t;&t;0x13
DECL|macro|LM90_REG_R_REMOTE_LOWH
mdefine_line|#define LM90_REG_R_REMOTE_LOWH&t;&t;0x08
DECL|macro|LM90_REG_W_REMOTE_LOWH
mdefine_line|#define LM90_REG_W_REMOTE_LOWH&t;&t;0x0E
DECL|macro|LM90_REG_R_REMOTE_LOWL
mdefine_line|#define LM90_REG_R_REMOTE_LOWL&t;&t;0x14
DECL|macro|LM90_REG_W_REMOTE_LOWL
mdefine_line|#define LM90_REG_W_REMOTE_LOWL&t;&t;0x14
DECL|macro|LM90_REG_R_REMOTE_CRIT
mdefine_line|#define LM90_REG_R_REMOTE_CRIT&t;&t;0x19
DECL|macro|LM90_REG_W_REMOTE_CRIT
mdefine_line|#define LM90_REG_W_REMOTE_CRIT&t;&t;0x19
DECL|macro|LM90_REG_R_TCRIT_HYST
mdefine_line|#define LM90_REG_R_TCRIT_HYST&t;&t;0x21
DECL|macro|LM90_REG_W_TCRIT_HYST
mdefine_line|#define LM90_REG_W_TCRIT_HYST&t;&t;0x21
multiline_comment|/*&n; * Conversions and various macros&n; * The LM90 uses signed 8-bit values for the local temperatures,&n; * and signed 11-bit values for the remote temperatures (except&n; * T_CRIT). Note that TEMP2_TO_REG does not round values, but&n; * stick to the nearest lower value instead. Fixing it is just&n; * not worth it.&n; */
DECL|macro|TEMP1_FROM_REG
mdefine_line|#define TEMP1_FROM_REG(val)&t;((val &amp; 0x80 ? val-0x100 : val) * 1000)
DECL|macro|TEMP1_TO_REG
mdefine_line|#define TEMP1_TO_REG(val)&t;((val &lt; 0 ? val+0x100*1000 : val) / 1000)
DECL|macro|TEMP2_FROM_REG
mdefine_line|#define TEMP2_FROM_REG(val)&t;(((val &amp; 0x8000 ? val-0x10000 : val) &gt;&gt; 5) * 125)
DECL|macro|TEMP2_TO_REG
mdefine_line|#define TEMP2_TO_REG(val)&t;((((val / 125) &lt;&lt; 5) + (val &lt; 0 ? 0x10000 : 0)) &amp; 0xFFE0)
DECL|macro|HYST_FROM_REG
mdefine_line|#define HYST_FROM_REG(val)&t;(val * 1000)
DECL|macro|HYST_TO_REG
mdefine_line|#define HYST_TO_REG(val)&t;(val &lt;= 0 ? 0 : val &gt;= 31000 ? 31 : val / 1000)
multiline_comment|/*&n; * Functions declaration&n; */
r_static
r_int
id|lm90_attach_adapter
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
id|lm90_detect
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
r_void
id|lm90_init_client
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
id|lm90_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
r_static
r_void
id|lm90_update_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
multiline_comment|/*&n; * Driver data (common to all clients)&n; */
DECL|variable|lm90_driver
r_static
r_struct
id|i2c_driver
id|lm90_driver
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
l_string|&quot;lm90&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_LM90
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|lm90_attach_adapter
comma
dot
id|detach_client
op_assign
id|lm90_detach_client
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Client data (each client gets its own)&n; */
DECL|struct|lm90_data
r_struct
id|lm90_data
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
multiline_comment|/* zero until following fields are valid */
DECL|member|last_updated
r_int
r_int
id|last_updated
suffix:semicolon
multiline_comment|/* in jiffies */
multiline_comment|/* registers values */
DECL|member|temp_input1
DECL|member|temp_low1
DECL|member|temp_high1
id|u8
id|temp_input1
comma
id|temp_low1
comma
id|temp_high1
suffix:semicolon
multiline_comment|/* local */
DECL|member|temp_input2
DECL|member|temp_low2
DECL|member|temp_high2
id|u16
id|temp_input2
comma
id|temp_low2
comma
id|temp_high2
suffix:semicolon
multiline_comment|/* remote, combined */
DECL|member|temp_crit1
DECL|member|temp_crit2
id|u8
id|temp_crit1
comma
id|temp_crit2
suffix:semicolon
DECL|member|temp_hyst
id|u8
id|temp_hyst
suffix:semicolon
DECL|member|alarms
id|u16
id|alarms
suffix:semicolon
multiline_comment|/* bitvector, combined */
)brace
suffix:semicolon
multiline_comment|/*&n; * Internal variables&n; */
DECL|variable|lm90_id
r_static
r_int
id|lm90_id
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Sysfs stuff&n; */
DECL|macro|show_temp
mdefine_line|#define show_temp(value, converter) &bslash;&n;static ssize_t show_##value(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev); &bslash;&n;&t;struct lm90_data *data = i2c_get_clientdata(client); &bslash;&n;&t;lm90_update_client(client); &bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, converter(data-&gt;value)); &bslash;&n;}
id|show_temp
c_func
(paren
id|temp_input1
comma
id|TEMP1_FROM_REG
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|temp_input2
comma
id|TEMP2_FROM_REG
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|temp_low1
comma
id|TEMP1_FROM_REG
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|temp_low2
comma
id|TEMP2_FROM_REG
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|temp_high1
comma
id|TEMP1_FROM_REG
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|temp_high2
comma
id|TEMP2_FROM_REG
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|temp_crit1
comma
id|TEMP1_FROM_REG
)paren
suffix:semicolon
id|show_temp
c_func
(paren
id|temp_crit2
comma
id|TEMP1_FROM_REG
)paren
suffix:semicolon
DECL|macro|set_temp1
mdefine_line|#define set_temp1(value, reg) &bslash;&n;static ssize_t set_##value(struct device *dev, const char *buf, &bslash;&n;&t;size_t count) &bslash;&n;{ &bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev); &bslash;&n;&t;struct lm90_data *data = i2c_get_clientdata(client); &bslash;&n;&t;data-&gt;value = TEMP1_TO_REG(simple_strtol(buf, NULL, 10)); &bslash;&n;&t;i2c_smbus_write_byte_data(client, reg, data-&gt;value); &bslash;&n;&t;return count; &bslash;&n;}
DECL|macro|set_temp2
mdefine_line|#define set_temp2(value, regh, regl) &bslash;&n;static ssize_t set_##value(struct device *dev, const char *buf, &bslash;&n;&t;size_t count) &bslash;&n;{ &bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev); &bslash;&n;&t;struct lm90_data *data = i2c_get_clientdata(client); &bslash;&n;&t;data-&gt;value = TEMP2_TO_REG(simple_strtol(buf, NULL, 10)); &bslash;&n;&t;i2c_smbus_write_byte_data(client, regh, data-&gt;value &gt;&gt; 8); &bslash;&n;&t;i2c_smbus_write_byte_data(client, regl, data-&gt;value &amp; 0xff); &bslash;&n;&t;return count; &bslash;&n;}
id|set_temp1
c_func
(paren
id|temp_low1
comma
id|LM90_REG_W_LOCAL_LOW
)paren
suffix:semicolon
id|set_temp2
c_func
(paren
id|temp_low2
comma
id|LM90_REG_W_REMOTE_LOWH
comma
id|LM90_REG_W_REMOTE_LOWL
)paren
suffix:semicolon
id|set_temp1
c_func
(paren
id|temp_high1
comma
id|LM90_REG_W_LOCAL_HIGH
)paren
suffix:semicolon
id|set_temp2
c_func
(paren
id|temp_high2
comma
id|LM90_REG_W_REMOTE_HIGHH
comma
id|LM90_REG_W_REMOTE_HIGHL
)paren
suffix:semicolon
id|set_temp1
c_func
(paren
id|temp_crit1
comma
id|LM90_REG_W_LOCAL_CRIT
)paren
suffix:semicolon
id|set_temp1
c_func
(paren
id|temp_crit2
comma
id|LM90_REG_W_REMOTE_CRIT
)paren
suffix:semicolon
DECL|macro|show_temp_hyst
mdefine_line|#define show_temp_hyst(value, basereg) &bslash;&n;static ssize_t show_##value(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev); &bslash;&n;&t;struct lm90_data *data = i2c_get_clientdata(client); &bslash;&n;&t;lm90_update_client(client); &bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, TEMP1_FROM_REG(data-&gt;basereg) &bslash;&n;&t;&t;       - HYST_FROM_REG(data-&gt;temp_hyst)); &bslash;&n;}
id|show_temp_hyst
c_func
(paren
id|temp_hyst1
comma
id|temp_crit1
)paren
suffix:semicolon
id|show_temp_hyst
c_func
(paren
id|temp_hyst2
comma
id|temp_crit2
)paren
suffix:semicolon
DECL|function|set_temp_hyst1
r_static
id|ssize_t
id|set_temp_hyst1
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
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
id|dev
)paren
suffix:semicolon
r_struct
id|lm90_data
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
id|hyst
op_assign
id|TEMP1_FROM_REG
c_func
(paren
id|data-&gt;temp_crit1
)paren
op_minus
id|simple_strtol
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_W_TCRIT_HYST
comma
id|HYST_TO_REG
c_func
(paren
id|hyst
)paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
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
id|lm90_data
op_star
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|lm90_update_client
c_func
(paren
id|client
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
id|temp_input1
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
id|temp_input2
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
id|temp_min1
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_low1
comma
id|set_temp_low1
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp_min2
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_low2
comma
id|set_temp_low2
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp_max1
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
id|temp_max2
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
id|temp_crit1
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_crit1
comma
id|set_temp_crit1
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp_crit2
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_crit2
comma
id|set_temp_crit2
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp_hyst1
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_hyst1
comma
id|set_temp_hyst1
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp_hyst2
comma
id|S_IRUGO
comma
id|show_temp_hyst2
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
DECL|function|lm90_attach_adapter
r_static
r_int
id|lm90_attach_adapter
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
id|I2C_ADAP_CLASS_SMBUS
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
id|lm90_detect
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following function does more than just detection. If detection&n; * succeeds, it also registers the new chip.&n; */
DECL|function|lm90_detect
r_static
r_int
id|lm90_detect
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
id|lm90_data
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
id|u8
id|reg_config1
op_assign
l_int|0
comma
id|reg_convrate
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
id|lm90_data
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
id|lm90_data
)paren
)paren
suffix:semicolon
multiline_comment|/* The LM90-specific data is placed right after the common I2C&n;&t; * client data. */
id|data
op_assign
(paren
r_struct
id|lm90_data
op_star
)paren
(paren
id|new_client
op_plus
l_int|1
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
id|lm90_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Now we do the remaining detection. A negative kind means that&n;&t; * the driver was loaded with no force parameter (default), so we&n;&t; * must both detect and identify the chip. A zero kind means that&n;&t; * the driver was loaded with the force parameter, the detection&n;&t; * step shall be skipped. A positive kind means that the driver&n;&t; * was loaded with the force parameter and a given kind of chip is&n;&t; * requested, so both the detection and the identification steps&n;&t; * are skipped.&n;&t; */
r_if
c_cond
(paren
id|kind
OL
l_int|0
)paren
(brace
multiline_comment|/* detection */
id|reg_config1
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM90_REG_R_CONFIG1
)paren
suffix:semicolon
id|reg_convrate
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM90_REG_R_CONVRATE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reg_config1
op_amp
l_int|0x2A
)paren
op_ne
l_int|0x00
op_logical_or
id|reg_convrate
OG
l_int|0x0A
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;LM90 detection failed at 0x%02x.&bslash;n&quot;
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
id|LM90_REG_R_MAN_ID
)paren
suffix:semicolon
id|chip_id
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM90_REG_R_CHIP_ID
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
op_ge
l_int|0x21
op_logical_and
id|chip_id
OL
l_int|0x30
multiline_comment|/* LM90 */
op_logical_and
(paren
id|kind
op_eq
l_int|0
multiline_comment|/* skip detection */
op_logical_or
(paren
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM90_REG_R_CONFIG2
)paren
op_amp
l_int|0xF8
)paren
op_eq
l_int|0x00
op_logical_and
id|reg_convrate
op_le
l_int|0x09
)paren
)paren
)paren
(brace
id|kind
op_assign
id|lm90
suffix:semicolon
id|name
op_assign
l_string|&quot;lm90&quot;
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|man_id
op_eq
l_int|0x41
)paren
(brace
multiline_comment|/* Analog Devices */
r_if
c_cond
(paren
(paren
id|chip_id
op_amp
l_int|0xF0
)paren
op_eq
l_int|0x40
multiline_comment|/* ADM1032 */
op_logical_and
(paren
id|kind
op_eq
l_int|0
multiline_comment|/* skip detection */
op_logical_or
(paren
id|reg_config1
op_amp
l_int|0x3F
)paren
op_eq
l_int|0x00
)paren
)paren
(brace
id|kind
op_assign
id|adm1032
suffix:semicolon
id|name
op_assign
l_string|&quot;adm1032&quot;
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
id|lm90_id
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
multiline_comment|/* Initialize the LM90 chip */
id|lm90_init_client
c_func
(paren
id|new_client
)paren
suffix:semicolon
multiline_comment|/* Register sysfs hooks */
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_input1
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_input2
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_min1
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_min2
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_max1
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_max2
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_crit1
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_crit2
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_hyst1
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp_hyst2
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
id|new_client
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|lm90_init_client
r_static
r_void
id|lm90_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
id|u8
id|config
suffix:semicolon
multiline_comment|/*&n;&t; * Start the conversions.&n;&t; */
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_W_CONVRATE
comma
l_int|5
)paren
suffix:semicolon
multiline_comment|/* 2 Hz */
id|config
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_CONFIG1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config
op_amp
l_int|0x40
)paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_W_CONFIG1
comma
id|config
op_amp
l_int|0xBF
)paren
suffix:semicolon
multiline_comment|/* run */
)brace
DECL|function|lm90_detach_client
r_static
r_int
id|lm90_detach_client
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
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lm90_update_client
r_static
r_void
id|lm90_update_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|lm90_data
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
id|u8
id|oldh
comma
id|newh
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Updating lm90 data.&bslash;n&quot;
)paren
suffix:semicolon
id|data-&gt;temp_input1
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_LOCAL_TEMP
)paren
suffix:semicolon
id|data-&gt;temp_high1
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_LOCAL_HIGH
)paren
suffix:semicolon
id|data-&gt;temp_low1
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_LOCAL_LOW
)paren
suffix:semicolon
id|data-&gt;temp_crit1
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_LOCAL_CRIT
)paren
suffix:semicolon
id|data-&gt;temp_crit2
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_CRIT
)paren
suffix:semicolon
id|data-&gt;temp_hyst
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_TCRIT_HYST
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * There is a trick here. We have to read two registers to&n;&t;&t; * have the remote sensor temperature, but we have to beware&n;&t;&t; * a conversion could occur inbetween the readings. The&n;&t;&t; * datasheet says we should either use the one-shot&n;&t;&t; * conversion register, which we don&squot;t want to do (disables&n;&t;&t; * hardware monitoring) or monitor the busy bit, which is&n;&t;&t; * impossible (we can&squot;t read the values and monitor that bit&n;&t;&t; * at the exact same time). So the solution used here is to&n;&t;&t; * read the high byte once, then the low byte, then the high&n;&t;&t; * byte again. If the new high byte matches the old one,&n;&t;&t; * then we have a valid reading. Else we have to read the low&n;&t;&t; * byte again, and now we believe we have a correct reading.&n;&t;&t; */
id|oldh
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_TEMPH
)paren
suffix:semicolon
id|data-&gt;temp_input2
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_TEMPL
)paren
suffix:semicolon
id|newh
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_TEMPH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newh
op_ne
id|oldh
)paren
(brace
id|data-&gt;temp_input2
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_TEMPL
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|oldh
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_TEMPH
)paren
suffix:semicolon
multiline_comment|/* oldh is actually newer */
r_if
c_cond
(paren
id|newh
op_ne
id|oldh
)paren
id|dev_warn
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Remote temperature may be &quot;
l_string|&quot;wrong.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
id|data-&gt;temp_input2
op_or_assign
(paren
id|newh
op_lshift
l_int|8
)paren
suffix:semicolon
id|data-&gt;temp_high2
op_assign
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_HIGHH
)paren
op_lshift
l_int|8
)paren
op_plus
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_HIGHL
)paren
suffix:semicolon
id|data-&gt;temp_low2
op_assign
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_LOWH
)paren
op_lshift
l_int|8
)paren
op_plus
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_REMOTE_LOWL
)paren
suffix:semicolon
id|data-&gt;alarms
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM90_REG_R_STATUS
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
DECL|function|sensors_lm90_init
r_static
r_int
id|__init
id|sensors_lm90_init
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
id|lm90_driver
)paren
suffix:semicolon
)brace
DECL|function|sensors_lm90_exit
r_static
r_void
id|__exit
id|sensors_lm90_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|lm90_driver
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
l_string|&quot;LM90/ADM1032 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sensors_lm90_init
id|module_init
c_func
(paren
id|sensors_lm90_init
)paren
suffix:semicolon
DECL|variable|sensors_lm90_exit
id|module_exit
c_func
(paren
id|sensors_lm90_exit
)paren
suffix:semicolon
eof
