multiline_comment|/*&n; * lm63.c - driver for the National Semiconductor LM63 temperature sensor&n; *          with integrated fan control&n; * Copyright (C) 2004  Jean Delvare &lt;khali@linux-fr.org&gt;&n; * Based on the lm90 driver.&n; *&n; * The LM63 is a sensor chip made by National Semiconductor. It measures&n; * two temperatures (its own and one external one) and the speed of one&n; * fan, those speed it can additionally control. Complete datasheet can be&n; * obtained from National&squot;s website at:&n; *   http://www.national.com/pf/LM/LM63.html&n; *&n; * The LM63 is basically an LM86 with fan speed monitoring and control&n; * capabilities added. It misses some of the LM86 features though:&n; *  - No low limit for local temperature.&n; *  - No critical limit for local temperature.&n; *  - Critical limit for remote temperature can be changed only once. We&n; *    will consider that the critical limit is read-only.&n; *&n; * The datasheet isn&squot;t very clear about what the tachometer reading is.&n; * I had a explanation from National Semiconductor though. The two lower&n; * bits of the read value have to be masked out. The value is still 16 bit&n; * in width.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
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
multiline_comment|/*&n; * Insmod parameters&n; */
DECL|variable|lm63
id|SENSORS_INSMOD_1
c_func
(paren
id|lm63
)paren
suffix:semicolon
multiline_comment|/*&n; * The LM63 registers&n; */
DECL|macro|LM63_REG_CONFIG1
mdefine_line|#define LM63_REG_CONFIG1&t;&t;0x03
DECL|macro|LM63_REG_CONFIG2
mdefine_line|#define LM63_REG_CONFIG2&t;&t;0xBF
DECL|macro|LM63_REG_CONFIG_FAN
mdefine_line|#define LM63_REG_CONFIG_FAN&t;&t;0x4A
DECL|macro|LM63_REG_TACH_COUNT_MSB
mdefine_line|#define LM63_REG_TACH_COUNT_MSB&t;&t;0x47
DECL|macro|LM63_REG_TACH_COUNT_LSB
mdefine_line|#define LM63_REG_TACH_COUNT_LSB&t;&t;0x46
DECL|macro|LM63_REG_TACH_LIMIT_MSB
mdefine_line|#define LM63_REG_TACH_LIMIT_MSB&t;&t;0x49
DECL|macro|LM63_REG_TACH_LIMIT_LSB
mdefine_line|#define LM63_REG_TACH_LIMIT_LSB&t;&t;0x48
DECL|macro|LM63_REG_PWM_VALUE
mdefine_line|#define LM63_REG_PWM_VALUE&t;&t;0x4C
DECL|macro|LM63_REG_PWM_FREQ
mdefine_line|#define LM63_REG_PWM_FREQ&t;&t;0x4D
DECL|macro|LM63_REG_LOCAL_TEMP
mdefine_line|#define LM63_REG_LOCAL_TEMP&t;&t;0x00
DECL|macro|LM63_REG_LOCAL_HIGH
mdefine_line|#define LM63_REG_LOCAL_HIGH&t;&t;0x05
DECL|macro|LM63_REG_REMOTE_TEMP_MSB
mdefine_line|#define LM63_REG_REMOTE_TEMP_MSB&t;0x01
DECL|macro|LM63_REG_REMOTE_TEMP_LSB
mdefine_line|#define LM63_REG_REMOTE_TEMP_LSB&t;0x10
DECL|macro|LM63_REG_REMOTE_OFFSET_MSB
mdefine_line|#define LM63_REG_REMOTE_OFFSET_MSB&t;0x11
DECL|macro|LM63_REG_REMOTE_OFFSET_LSB
mdefine_line|#define LM63_REG_REMOTE_OFFSET_LSB&t;0x12
DECL|macro|LM63_REG_REMOTE_HIGH_MSB
mdefine_line|#define LM63_REG_REMOTE_HIGH_MSB&t;0x07
DECL|macro|LM63_REG_REMOTE_HIGH_LSB
mdefine_line|#define LM63_REG_REMOTE_HIGH_LSB&t;0x13
DECL|macro|LM63_REG_REMOTE_LOW_MSB
mdefine_line|#define LM63_REG_REMOTE_LOW_MSB&t;&t;0x08
DECL|macro|LM63_REG_REMOTE_LOW_LSB
mdefine_line|#define LM63_REG_REMOTE_LOW_LSB&t;&t;0x14
DECL|macro|LM63_REG_REMOTE_TCRIT
mdefine_line|#define LM63_REG_REMOTE_TCRIT&t;&t;0x19
DECL|macro|LM63_REG_REMOTE_TCRIT_HYST
mdefine_line|#define LM63_REG_REMOTE_TCRIT_HYST&t;0x21
DECL|macro|LM63_REG_ALERT_STATUS
mdefine_line|#define LM63_REG_ALERT_STATUS&t;&t;0x02
DECL|macro|LM63_REG_ALERT_MASK
mdefine_line|#define LM63_REG_ALERT_MASK&t;&t;0x16
DECL|macro|LM63_REG_MAN_ID
mdefine_line|#define LM63_REG_MAN_ID&t;&t;&t;0xFE
DECL|macro|LM63_REG_CHIP_ID
mdefine_line|#define LM63_REG_CHIP_ID&t;&t;0xFF
multiline_comment|/*&n; * Conversions and various macros&n; * For tachometer counts, the LM63 uses 16-bit values.&n; * For local temperature and high limit, remote critical limit and hysteresis&n; * value, it uses signed 8-bit values with LSB = 1 degree Celcius.&n; * For remote temperature, low and high limits, it uses signed 11-bit values&n; * with LSB = 0.125 degree Celcius, left-justified in 16-bit registers.&n; */
DECL|macro|FAN_FROM_REG
mdefine_line|#define FAN_FROM_REG(reg)&t;((reg) == 0xFFFC || (reg) == 0 ? 0 : &bslash;&n;&t;&t;&t;&t; 5400000 / (reg))
DECL|macro|FAN_TO_REG
mdefine_line|#define FAN_TO_REG(val)&t;&t;((val) &lt;= 82 ? 0xFFFC : &bslash;&n;&t;&t;&t;&t; (5400000 / (val)) &amp; 0xFFFC)
DECL|macro|TEMP8_FROM_REG
mdefine_line|#define TEMP8_FROM_REG(reg)&t;((reg) * 1000)
DECL|macro|TEMP8_TO_REG
mdefine_line|#define TEMP8_TO_REG(val)&t;((val) &lt;= -128000 ? -128 : &bslash;&n;&t;&t;&t;&t; (val) &gt;= 127000 ? 127 : &bslash;&n;&t;&t;&t;&t; (val) &lt; 0 ? ((val) - 500) / 1000 : &bslash;&n;&t;&t;&t;&t; ((val) + 500) / 1000)
DECL|macro|TEMP11_FROM_REG
mdefine_line|#define TEMP11_FROM_REG(reg)&t;((reg) / 32 * 125)
DECL|macro|TEMP11_TO_REG
mdefine_line|#define TEMP11_TO_REG(val)&t;((val) &lt;= -128000 ? 0x8000 : &bslash;&n;&t;&t;&t;&t; (val) &gt;= 127875 ? 0x7FE0 : &bslash;&n;&t;&t;&t;&t; (val) &lt; 0 ? ((val) - 62) / 125 * 32 : &bslash;&n;&t;&t;&t;&t; ((val) + 62) / 125 * 32)
DECL|macro|HYST_TO_REG
mdefine_line|#define HYST_TO_REG(val)&t;((val) &lt;= 0 ? 0 : &bslash;&n;&t;&t;&t;&t; (val) &gt;= 127000 ? 127 : &bslash;&n;&t;&t;&t;&t; ((val) + 500) / 1000)
multiline_comment|/*&n; * Functions declaration&n; */
r_static
r_int
id|lm63_attach_adapter
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
id|lm63_detach_client
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
id|lm63_data
op_star
id|lm63_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|lm63_detect
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
id|lm63_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
multiline_comment|/*&n; * Driver data (common to all clients)&n; */
DECL|variable|lm63_driver
r_static
r_struct
id|i2c_driver
id|lm63_driver
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
l_string|&quot;lm63&quot;
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|lm63_attach_adapter
comma
dot
id|detach_client
op_assign
id|lm63_detach_client
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Client data (each client gets its own)&n; */
DECL|struct|lm63_data
r_struct
id|lm63_data
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
DECL|member|config
DECL|member|config_fan
id|u8
id|config
comma
id|config_fan
suffix:semicolon
DECL|member|fan1_input
id|u16
id|fan1_input
suffix:semicolon
DECL|member|fan1_low
id|u16
id|fan1_low
suffix:semicolon
DECL|member|pwm1_freq
id|u8
id|pwm1_freq
suffix:semicolon
DECL|member|pwm1_value
id|u8
id|pwm1_value
suffix:semicolon
DECL|member|temp1_input
id|s8
id|temp1_input
suffix:semicolon
DECL|member|temp1_high
id|s8
id|temp1_high
suffix:semicolon
DECL|member|temp2_input
id|s16
id|temp2_input
suffix:semicolon
DECL|member|temp2_high
id|s16
id|temp2_high
suffix:semicolon
DECL|member|temp2_low
id|s16
id|temp2_low
suffix:semicolon
DECL|member|temp2_crit
id|s8
id|temp2_crit
suffix:semicolon
DECL|member|temp2_crit_hyst
id|u8
id|temp2_crit_hyst
suffix:semicolon
DECL|member|alarms
id|u8
id|alarms
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Sysfs callback functions and files&n; */
DECL|macro|show_fan
mdefine_line|#define show_fan(value) &bslash;&n;static ssize_t show_##value(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;struct lm63_data *data = lm63_update_device(dev); &bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, FAN_FROM_REG(data-&gt;value)); &bslash;&n;}
DECL|variable|fan1_input
id|show_fan
c_func
(paren
id|fan1_input
)paren
suffix:semicolon
DECL|variable|fan1_low
id|show_fan
c_func
(paren
id|fan1_low
)paren
suffix:semicolon
DECL|function|set_fan1_low
r_static
id|ssize_t
id|set_fan1_low
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
id|lm63_data
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
r_int
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
id|data-&gt;fan1_low
op_assign
id|FAN_TO_REG
c_func
(paren
id|val
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_TACH_LIMIT_LSB
comma
id|data-&gt;fan1_low
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_TACH_LIMIT_MSB
comma
id|data-&gt;fan1_low
op_rshift
l_int|8
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|show_pwm1
r_static
id|ssize_t
id|show_pwm1
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
id|lm63_data
op_star
id|data
op_assign
id|lm63_update_device
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
id|data-&gt;pwm1_value
op_ge
l_int|2
op_star
id|data-&gt;pwm1_freq
ques
c_cond
l_int|255
suffix:colon
(paren
id|data-&gt;pwm1_value
op_star
l_int|255
op_plus
id|data-&gt;pwm1_freq
)paren
op_div
(paren
l_int|2
op_star
id|data-&gt;pwm1_freq
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_pwm1
r_static
id|ssize_t
id|set_pwm1
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
id|lm63_data
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
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data-&gt;config_fan
op_amp
l_int|0x20
)paren
)paren
multiline_comment|/* register is read-only */
r_return
op_minus
id|EPERM
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
id|data-&gt;pwm1_value
op_assign
id|val
op_le
l_int|0
ques
c_cond
l_int|0
suffix:colon
id|val
op_ge
l_int|255
ques
c_cond
l_int|2
op_star
id|data-&gt;pwm1_freq
suffix:colon
(paren
id|val
op_star
id|data-&gt;pwm1_freq
op_star
l_int|2
op_plus
l_int|127
)paren
op_div
l_int|255
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_PWM_VALUE
comma
id|data-&gt;pwm1_value
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|show_pwm1_enable
r_static
id|ssize_t
id|show_pwm1_enable
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
id|lm63_data
op_star
id|data
op_assign
id|lm63_update_device
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
id|data-&gt;config_fan
op_amp
l_int|0x20
ques
c_cond
l_int|1
suffix:colon
l_int|2
)paren
suffix:semicolon
)brace
DECL|macro|show_temp8
mdefine_line|#define show_temp8(value) &bslash;&n;static ssize_t show_##value(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;struct lm63_data *data = lm63_update_device(dev); &bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, TEMP8_FROM_REG(data-&gt;value)); &bslash;&n;}
DECL|macro|show_temp11
mdefine_line|#define show_temp11(value) &bslash;&n;static ssize_t show_##value(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;struct lm63_data *data = lm63_update_device(dev); &bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, TEMP11_FROM_REG(data-&gt;value)); &bslash;&n;}
DECL|variable|temp1_input
id|show_temp8
c_func
(paren
id|temp1_input
)paren
suffix:semicolon
DECL|variable|temp1_high
id|show_temp8
c_func
(paren
id|temp1_high
)paren
suffix:semicolon
DECL|variable|temp2_input
id|show_temp11
c_func
(paren
id|temp2_input
)paren
suffix:semicolon
DECL|variable|temp2_high
id|show_temp11
c_func
(paren
id|temp2_high
)paren
suffix:semicolon
DECL|variable|temp2_low
id|show_temp11
c_func
(paren
id|temp2_low
)paren
suffix:semicolon
DECL|variable|temp2_crit
id|show_temp8
c_func
(paren
id|temp2_crit
)paren
suffix:semicolon
DECL|macro|set_temp8
mdefine_line|#define set_temp8(value, reg) &bslash;&n;static ssize_t set_##value(struct device *dev, const char *buf, &bslash;&n;&t;size_t count) &bslash;&n;{ &bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev); &bslash;&n;&t;struct lm63_data *data = i2c_get_clientdata(client); &bslash;&n;&t;long val = simple_strtol(buf, NULL, 10); &bslash;&n; &bslash;&n;&t;down(&amp;data-&gt;update_lock); &bslash;&n;&t;data-&gt;value = TEMP8_TO_REG(val); &bslash;&n;&t;i2c_smbus_write_byte_data(client, reg, data-&gt;value); &bslash;&n;&t;up(&amp;data-&gt;update_lock); &bslash;&n;&t;return count; &bslash;&n;}
DECL|macro|set_temp11
mdefine_line|#define set_temp11(value, reg_msb, reg_lsb) &bslash;&n;static ssize_t set_##value(struct device *dev, const char *buf, &bslash;&n;&t;size_t count) &bslash;&n;{ &bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev); &bslash;&n;&t;struct lm63_data *data = i2c_get_clientdata(client); &bslash;&n;&t;long val = simple_strtol(buf, NULL, 10); &bslash;&n; &bslash;&n;&t;down(&amp;data-&gt;update_lock); &bslash;&n;&t;data-&gt;value = TEMP11_TO_REG(val); &bslash;&n;&t;i2c_smbus_write_byte_data(client, reg_msb, data-&gt;value &gt;&gt; 8); &bslash;&n;&t;i2c_smbus_write_byte_data(client, reg_lsb, data-&gt;value &amp; 0xff); &bslash;&n;&t;up(&amp;data-&gt;update_lock); &bslash;&n;&t;return count; &bslash;&n;}
id|set_temp8
c_func
(paren
id|temp1_high
comma
id|LM63_REG_LOCAL_HIGH
)paren
suffix:semicolon
id|set_temp11
c_func
(paren
id|temp2_high
comma
id|LM63_REG_REMOTE_HIGH_MSB
comma
id|LM63_REG_REMOTE_HIGH_LSB
)paren
suffix:semicolon
id|set_temp11
c_func
(paren
id|temp2_low
comma
id|LM63_REG_REMOTE_LOW_MSB
comma
id|LM63_REG_REMOTE_LOW_LSB
)paren
suffix:semicolon
multiline_comment|/* Hysteresis register holds a relative value, while we want to present&n;   an absolute to user-space */
DECL|function|show_temp2_crit_hyst
r_static
id|ssize_t
id|show_temp2_crit_hyst
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
id|lm63_data
op_star
id|data
op_assign
id|lm63_update_device
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
id|TEMP8_FROM_REG
c_func
(paren
id|data-&gt;temp2_crit
)paren
op_minus
id|TEMP8_FROM_REG
c_func
(paren
id|data-&gt;temp2_crit_hyst
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* And now the other way around, user-space provides an absolute&n;   hysteresis value and we have to store a relative one */
DECL|function|set_temp2_crit_hyst
r_static
id|ssize_t
id|set_temp2_crit_hyst
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
id|lm63_data
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
id|val
op_assign
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
r_int
id|hyst
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
id|hyst
op_assign
id|TEMP8_FROM_REG
c_func
(paren
id|data-&gt;temp2_crit
)paren
op_minus
id|val
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_TCRIT_HYST
comma
id|HYST_TO_REG
c_func
(paren
id|hyst
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|data-&gt;update_lock
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
id|lm63_data
op_star
id|data
op_assign
id|lm63_update_device
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
l_string|&quot;%u&bslash;n&quot;
comma
id|data-&gt;alarms
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|fan1_input
comma
id|S_IRUGO
comma
id|show_fan1_input
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|fan1_min
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_fan1_low
comma
id|set_fan1_low
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|pwm1
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_pwm1
comma
id|set_pwm1
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|pwm1_enable
comma
id|S_IRUGO
comma
id|show_pwm1_enable
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_input
comma
id|S_IRUGO
comma
id|show_temp1_input
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
id|show_temp1_high
comma
id|set_temp1_high
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
id|show_temp2_input
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp2_min
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp2_low
comma
id|set_temp2_low
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
id|show_temp2_high
comma
id|set_temp2_high
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
id|show_temp2_crit
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp2_crit_hyst
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp2_crit_hyst
comma
id|set_temp2_crit_hyst
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
DECL|function|lm63_attach_adapter
r_static
r_int
id|lm63_attach_adapter
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
id|lm63_detect
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following function does more than just detection. If detection&n; * succeeds, it also registers the new chip.&n; */
DECL|function|lm63_detect
r_static
r_int
id|lm63_detect
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
id|lm63_data
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
id|lm63_data
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
id|lm63_data
)paren
)paren
suffix:semicolon
multiline_comment|/* The common I2C client data is placed right before the&n;&t;   LM63-specific data. */
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
id|lm63_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default to an LM63 if forced */
r_if
c_cond
(paren
id|kind
op_eq
l_int|0
)paren
id|kind
op_assign
id|lm63
suffix:semicolon
r_if
c_cond
(paren
id|kind
OL
l_int|0
)paren
(brace
multiline_comment|/* must identify */
id|u8
id|man_id
comma
id|chip_id
comma
id|reg_config1
comma
id|reg_config2
suffix:semicolon
id|u8
id|reg_alert_status
comma
id|reg_alert_mask
suffix:semicolon
id|man_id
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM63_REG_MAN_ID
)paren
suffix:semicolon
id|chip_id
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM63_REG_CHIP_ID
)paren
suffix:semicolon
id|reg_config1
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM63_REG_CONFIG1
)paren
suffix:semicolon
id|reg_config2
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM63_REG_CONFIG2
)paren
suffix:semicolon
id|reg_alert_status
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM63_REG_ALERT_STATUS
)paren
suffix:semicolon
id|reg_alert_mask
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|LM63_REG_ALERT_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|man_id
op_eq
l_int|0x01
multiline_comment|/* National Semiconductor */
op_logical_and
id|chip_id
op_eq
l_int|0x41
multiline_comment|/* LM63 */
op_logical_and
(paren
id|reg_config1
op_amp
l_int|0x18
)paren
op_eq
l_int|0x00
op_logical_and
(paren
id|reg_config2
op_amp
l_int|0xF8
)paren
op_eq
l_int|0x00
op_logical_and
(paren
id|reg_alert_status
op_amp
l_int|0x20
)paren
op_eq
l_int|0x00
op_logical_and
(paren
id|reg_alert_mask
op_amp
l_int|0xA4
)paren
op_eq
l_int|0xA4
)paren
(brace
id|kind
op_assign
id|lm63
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* failed */
id|dev_dbg
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;Unsupported chip &quot;
l_string|&quot;(man_id=0x%02X, chip_id=0x%02X).&bslash;n&quot;
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
id|strlcpy
c_func
(paren
id|new_client-&gt;name
comma
l_string|&quot;lm63&quot;
comma
id|I2C_NAME_SIZE
)paren
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
multiline_comment|/* Initialize the LM63 chip */
id|lm63_init_client
c_func
(paren
id|new_client
)paren
suffix:semicolon
multiline_comment|/* Register sysfs hooks */
r_if
c_cond
(paren
id|data-&gt;config
op_amp
l_int|0x04
)paren
(brace
multiline_comment|/* tachometer enabled */
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_fan1_input
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_fan1_min
)paren
suffix:semicolon
)brace
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_pwm1
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_pwm1_enable
)paren
suffix:semicolon
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
id|dev_attr_temp2_min
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
id|dev_attr_temp2_crit_hyst
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
multiline_comment|/* Idealy we shouldn&squot;t have to initialize anything, since the BIOS&n;   should have taken care of everything */
DECL|function|lm63_init_client
r_static
r_void
id|lm63_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|lm63_data
op_star
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|data-&gt;config
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_CONFIG1
)paren
suffix:semicolon
id|data-&gt;config_fan
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_CONFIG_FAN
)paren
suffix:semicolon
multiline_comment|/* Start converting if needed */
r_if
c_cond
(paren
id|data-&gt;config
op_amp
l_int|0x40
)paren
(brace
multiline_comment|/* standby */
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Switching to operational mode&quot;
)paren
suffix:semicolon
id|data-&gt;config
op_and_assign
l_int|0xA7
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_CONFIG1
comma
id|data-&gt;config
)paren
suffix:semicolon
)brace
multiline_comment|/* We may need pwm1_freq before ever updating the client data */
id|data-&gt;pwm1_freq
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_PWM_FREQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;pwm1_freq
op_eq
l_int|0
)paren
id|data-&gt;pwm1_freq
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Show some debug info about the LM63 configuration */
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Alert/tach pin configured for %s&bslash;n&quot;
comma
(paren
id|data-&gt;config
op_amp
l_int|0x04
)paren
ques
c_cond
l_string|&quot;tachometer input&quot;
suffix:colon
l_string|&quot;alert output&quot;
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;PWM clock %s kHz, output frequency %u Hz&bslash;n&quot;
comma
(paren
id|data-&gt;config_fan
op_amp
l_int|0x08
)paren
ques
c_cond
l_string|&quot;1.4&quot;
suffix:colon
l_string|&quot;360&quot;
comma
(paren
(paren
id|data-&gt;config_fan
op_amp
l_int|0x08
)paren
ques
c_cond
l_int|700
suffix:colon
l_int|180000
)paren
op_div
id|data-&gt;pwm1_freq
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;PWM output active %s, %s mode&bslash;n&quot;
comma
(paren
id|data-&gt;config_fan
op_amp
l_int|0x10
)paren
ques
c_cond
l_string|&quot;low&quot;
suffix:colon
l_string|&quot;high&quot;
comma
(paren
id|data-&gt;config_fan
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;manual&quot;
suffix:colon
l_string|&quot;auto&quot;
)paren
suffix:semicolon
)brace
DECL|function|lm63_detach_client
r_static
r_int
id|lm63_detach_client
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
l_string|&quot;client not detached&bslash;n&quot;
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
DECL|function|lm63_update_device
r_static
r_struct
id|lm63_data
op_star
id|lm63_update_device
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
id|lm63_data
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
id|time_after
c_func
(paren
id|jiffies
comma
id|data-&gt;last_updated
op_plus
id|HZ
)paren
op_logical_or
op_logical_neg
id|data-&gt;valid
)paren
(brace
r_if
c_cond
(paren
id|data-&gt;config
op_amp
l_int|0x04
)paren
(brace
multiline_comment|/* tachometer enabled  */
multiline_comment|/* order matters for fan1_input */
id|data-&gt;fan1_input
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_TACH_COUNT_LSB
)paren
op_amp
l_int|0xFC
suffix:semicolon
id|data-&gt;fan1_input
op_or_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_TACH_COUNT_MSB
)paren
op_lshift
l_int|8
suffix:semicolon
id|data-&gt;fan1_low
op_assign
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_TACH_LIMIT_LSB
)paren
op_amp
l_int|0xFC
)paren
op_or
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_TACH_LIMIT_MSB
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
id|data-&gt;pwm1_freq
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_PWM_FREQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;pwm1_freq
op_eq
l_int|0
)paren
id|data-&gt;pwm1_freq
op_assign
l_int|1
suffix:semicolon
id|data-&gt;pwm1_value
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_PWM_VALUE
)paren
suffix:semicolon
id|data-&gt;temp1_input
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_LOCAL_TEMP
)paren
suffix:semicolon
id|data-&gt;temp1_high
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_LOCAL_HIGH
)paren
suffix:semicolon
multiline_comment|/* order matters for temp2_input */
id|data-&gt;temp2_input
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_TEMP_MSB
)paren
op_lshift
l_int|8
suffix:semicolon
id|data-&gt;temp2_input
op_or_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_TEMP_LSB
)paren
suffix:semicolon
id|data-&gt;temp2_high
op_assign
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_HIGH_MSB
)paren
op_lshift
l_int|8
)paren
op_or
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_HIGH_LSB
)paren
suffix:semicolon
id|data-&gt;temp2_low
op_assign
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_LOW_MSB
)paren
op_lshift
l_int|8
)paren
op_or
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_LOW_LSB
)paren
suffix:semicolon
id|data-&gt;temp2_crit
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_TCRIT
)paren
suffix:semicolon
id|data-&gt;temp2_crit_hyst
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_REMOTE_TCRIT_HYST
)paren
suffix:semicolon
id|data-&gt;alarms
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|LM63_REG_ALERT_STATUS
)paren
op_amp
l_int|0x7F
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
DECL|function|sensors_lm63_init
r_static
r_int
id|__init
id|sensors_lm63_init
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
id|lm63_driver
)paren
suffix:semicolon
)brace
DECL|function|sensors_lm63_exit
r_static
r_void
id|__exit
id|sensors_lm63_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|lm63_driver
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
l_string|&quot;LM63 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sensors_lm63_init
id|module_init
c_func
(paren
id|sensors_lm63_init
)paren
suffix:semicolon
DECL|variable|sensors_lm63_exit
id|module_exit
c_func
(paren
id|sensors_lm63_exit
)paren
suffix:semicolon
eof
