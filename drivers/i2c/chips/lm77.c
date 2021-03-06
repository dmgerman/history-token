multiline_comment|/*&n;    lm77.c - Part of lm_sensors, Linux kernel modules for hardware&n;             monitoring&n;&n;    Copyright (c) 2004  Andras BALI &lt;drewie@freemail.hu&gt;&n;&n;    Heavily based on lm75.c by Frodo Looijaard &lt;frodol@dds.nl&gt;.  The LM77&n;    is a temperature sensor and thermal window comparator with 0.5 deg&n;    resolution made by National Semiconductor.  Complete datasheet can be&n;    obtained at their site:&n;       http://www.national.com/pf/LM/LM77.html&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
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
l_int|0x48
comma
l_int|0x49
comma
l_int|0x4a
comma
l_int|0x4b
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
multiline_comment|/* Insmod parameters */
DECL|variable|lm77
id|SENSORS_INSMOD_1
c_func
(paren
id|lm77
)paren
suffix:semicolon
multiline_comment|/* The LM77 registers */
DECL|macro|LM77_REG_TEMP
mdefine_line|#define LM77_REG_TEMP&t;&t;0x00
DECL|macro|LM77_REG_CONF
mdefine_line|#define LM77_REG_CONF&t;&t;0x01
DECL|macro|LM77_REG_TEMP_HYST
mdefine_line|#define LM77_REG_TEMP_HYST&t;0x02
DECL|macro|LM77_REG_TEMP_CRIT
mdefine_line|#define LM77_REG_TEMP_CRIT&t;0x03
DECL|macro|LM77_REG_TEMP_MIN
mdefine_line|#define LM77_REG_TEMP_MIN&t;0x04
DECL|macro|LM77_REG_TEMP_MAX
mdefine_line|#define LM77_REG_TEMP_MAX&t;0x05
multiline_comment|/* Each client has this additional data */
DECL|struct|lm77_data
r_struct
id|lm77_data
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
DECL|member|last_updated
r_int
r_int
id|last_updated
suffix:semicolon
multiline_comment|/* In jiffies */
DECL|member|temp_input
r_int
id|temp_input
suffix:semicolon
multiline_comment|/* Temperatures */
DECL|member|temp_crit
r_int
id|temp_crit
suffix:semicolon
DECL|member|temp_min
r_int
id|temp_min
suffix:semicolon
DECL|member|temp_max
r_int
id|temp_max
suffix:semicolon
DECL|member|temp_hyst
r_int
id|temp_hyst
suffix:semicolon
DECL|member|alarms
id|u8
id|alarms
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|lm77_attach_adapter
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
id|lm77_detect
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
id|lm77_init_client
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
id|lm77_detach_client
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
id|lm77_read_value
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
id|lm77_write_value
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
r_struct
id|lm77_data
op_star
id|lm77_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* This is the driver that will be inserted */
DECL|variable|lm77_driver
r_static
r_struct
id|i2c_driver
id|lm77_driver
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
l_string|&quot;lm77&quot;
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|lm77_attach_adapter
comma
dot
id|detach_client
op_assign
id|lm77_detach_client
comma
)brace
suffix:semicolon
multiline_comment|/* straight from the datasheet */
DECL|macro|LM77_TEMP_MIN
mdefine_line|#define LM77_TEMP_MIN (-55000)
DECL|macro|LM77_TEMP_MAX
mdefine_line|#define LM77_TEMP_MAX 125000
multiline_comment|/* In the temperature registers, the low 3 bits are not part of the&n;   temperature values; they are the status bits. */
DECL|function|LM77_TEMP_TO_REG
r_static
r_inline
id|u16
id|LM77_TEMP_TO_REG
c_func
(paren
r_int
id|temp
)paren
(brace
r_int
id|ntemp
op_assign
id|SENSORS_LIMIT
c_func
(paren
id|temp
comma
id|LM77_TEMP_MIN
comma
id|LM77_TEMP_MAX
)paren
suffix:semicolon
r_return
(paren
id|u16
)paren
(paren
(paren
id|ntemp
op_div
l_int|500
)paren
op_star
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|LM77_TEMP_FROM_REG
r_static
r_inline
r_int
id|LM77_TEMP_FROM_REG
c_func
(paren
id|u16
id|reg
)paren
(brace
r_return
(paren
(paren
r_int
)paren
id|reg
op_div
l_int|8
)paren
op_star
l_int|500
suffix:semicolon
)brace
multiline_comment|/* sysfs stuff */
multiline_comment|/* read routines for temperature limits */
DECL|macro|show
mdefine_line|#define show(value)&t;&bslash;&n;static ssize_t show_##value(struct device *dev, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct lm77_data *data = lm77_update_device(dev);&t;&bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, data-&gt;value);&t;&t;&bslash;&n;}
DECL|variable|temp_input
id|show
c_func
(paren
id|temp_input
)paren
suffix:semicolon
DECL|variable|temp_crit
id|show
c_func
(paren
id|temp_crit
)paren
suffix:semicolon
DECL|variable|temp_min
id|show
c_func
(paren
id|temp_min
)paren
suffix:semicolon
DECL|variable|temp_max
id|show
c_func
(paren
id|temp_max
)paren
suffix:semicolon
DECL|variable|alarms
id|show
c_func
(paren
id|alarms
)paren
suffix:semicolon
multiline_comment|/* read routines for hysteresis values */
DECL|function|show_temp_crit_hyst
r_static
id|ssize_t
id|show_temp_crit_hyst
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
id|lm77_data
op_star
id|data
op_assign
id|lm77_update_device
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
id|data-&gt;temp_crit
op_minus
id|data-&gt;temp_hyst
)paren
suffix:semicolon
)brace
DECL|function|show_temp_min_hyst
r_static
id|ssize_t
id|show_temp_min_hyst
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
id|lm77_data
op_star
id|data
op_assign
id|lm77_update_device
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
id|data-&gt;temp_min
op_plus
id|data-&gt;temp_hyst
)paren
suffix:semicolon
)brace
DECL|function|show_temp_max_hyst
r_static
id|ssize_t
id|show_temp_max_hyst
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
id|lm77_data
op_star
id|data
op_assign
id|lm77_update_device
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
id|data-&gt;temp_max
op_minus
id|data-&gt;temp_hyst
)paren
suffix:semicolon
)brace
multiline_comment|/* write routines */
DECL|macro|set
mdefine_line|#define set(value, reg)&t;&bslash;&n;static ssize_t set_##value(struct device *dev, const char *buf, size_t count)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev);&t;&t;&t;&t;&bslash;&n;&t;struct lm77_data *data = i2c_get_clientdata(client);&t;&t;&t;&bslash;&n;&t;long val = simple_strtoul(buf, NULL, 10);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;down(&amp;data-&gt;update_lock);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;data-&gt;value = val;&t;&t;&t;&t;&bslash;&n;&t;lm77_write_value(client, reg, LM77_TEMP_TO_REG(data-&gt;value));&t;&t;&bslash;&n;&t;up(&amp;data-&gt;update_lock);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|set
c_func
(paren
id|temp_min
comma
id|LM77_REG_TEMP_MIN
)paren
suffix:semicolon
id|set
c_func
(paren
id|temp_max
comma
id|LM77_REG_TEMP_MAX
)paren
suffix:semicolon
multiline_comment|/* hysteresis is stored as a relative value on the chip, so it has to be&n;   converted first */
DECL|function|set_temp_crit_hyst
r_static
id|ssize_t
id|set_temp_crit_hyst
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
id|lm77_data
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
id|data-&gt;temp_hyst
op_assign
id|data-&gt;temp_crit
op_minus
id|val
suffix:semicolon
id|lm77_write_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP_HYST
comma
id|LM77_TEMP_TO_REG
c_func
(paren
id|data-&gt;temp_hyst
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
multiline_comment|/* preserve hysteresis when setting T_crit */
DECL|function|set_temp_crit
r_static
id|ssize_t
id|set_temp_crit
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
id|lm77_data
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
r_int
id|oldcrithyst
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
id|oldcrithyst
op_assign
id|data-&gt;temp_crit
op_minus
id|data-&gt;temp_hyst
suffix:semicolon
id|data-&gt;temp_crit
op_assign
id|val
suffix:semicolon
id|data-&gt;temp_hyst
op_assign
id|data-&gt;temp_crit
op_minus
id|oldcrithyst
suffix:semicolon
id|lm77_write_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP_CRIT
comma
id|LM77_TEMP_TO_REG
c_func
(paren
id|data-&gt;temp_crit
)paren
)paren
suffix:semicolon
id|lm77_write_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP_HYST
comma
id|LM77_TEMP_TO_REG
c_func
(paren
id|data-&gt;temp_hyst
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
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_input
comma
id|S_IRUGO
comma
id|show_temp_input
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_crit
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
id|temp1_min
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_min
comma
id|set_temp_min
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
id|show_temp_max
comma
id|set_temp_max
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_crit_hyst
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_crit_hyst
comma
id|set_temp_crit_hyst
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_min_hyst
comma
id|S_IRUGO
comma
id|show_temp_min_hyst
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
id|temp1_max_hyst
comma
id|S_IRUGO
comma
id|show_temp_max_hyst
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
DECL|function|lm77_attach_adapter
r_static
r_int
id|lm77_attach_adapter
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
id|lm77_detect
)paren
suffix:semicolon
)brace
multiline_comment|/* This function is called by i2c_detect */
DECL|function|lm77_detect
r_static
r_int
id|lm77_detect
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
id|lm77_data
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
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
)paren
)paren
r_goto
m_exit
suffix:semicolon
multiline_comment|/* OK. For now, we presume we have a valid client. We now create the&n;&t;   client structure, even though we cannot fill it completely yet.&n;&t;   But it allows us to access lm77_{read,write}_value. */
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
id|lm77_data
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
id|lm77_data
)paren
)paren
suffix:semicolon
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
id|lm77_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Here comes the remaining detection.  Since the LM77 has no&n;&t;   register dedicated to identification, we have to rely on the&n;&t;   following tricks:&n;&n;&t;   1. the high 4 bits represent the sign and thus they should&n;&t;      always be the same&n;&t;   2. the high 3 bits are unused in the configuration register&n;&t;   3. addresses 0x06 and 0x07 return the last read value&n;&t;   4. registers cycling over 8-address boundaries&n;&n;&t;   Word-sized registers are high-byte first. */
r_if
c_cond
(paren
id|kind
OL
l_int|0
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
id|crit
comma
id|min
comma
id|max
suffix:semicolon
multiline_comment|/* addresses cycling */
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
id|crit
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|3
)paren
suffix:semicolon
id|min
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|4
)paren
suffix:semicolon
id|max
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|5
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|8
suffix:semicolon
id|i
op_le
l_int|0xff
suffix:semicolon
id|i
op_add_assign
l_int|8
)paren
r_if
c_cond
(paren
id|i2c_smbus_read_byte_data
c_func
(paren
id|new_client
comma
id|i
op_plus
l_int|1
)paren
op_ne
id|conf
op_logical_or
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
id|i
op_plus
l_int|2
)paren
op_ne
id|hyst
op_logical_or
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
id|i
op_plus
l_int|3
)paren
op_ne
id|crit
op_logical_or
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
id|i
op_plus
l_int|4
)paren
op_ne
id|min
op_logical_or
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
id|i
op_plus
l_int|5
)paren
op_ne
id|max
)paren
r_goto
id|exit_free
suffix:semicolon
multiline_comment|/* sign bits */
r_if
c_cond
(paren
(paren
(paren
id|cur
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0xf0
op_logical_and
(paren
id|cur
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0x0
)paren
op_logical_or
(paren
(paren
id|hyst
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0xf0
op_logical_and
(paren
id|hyst
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0x0
)paren
op_logical_or
(paren
(paren
id|crit
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0xf0
op_logical_and
(paren
id|crit
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0x0
)paren
op_logical_or
(paren
(paren
id|min
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0xf0
op_logical_and
(paren
id|min
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0x0
)paren
op_logical_or
(paren
(paren
id|max
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0xf0
op_logical_and
(paren
id|max
op_amp
l_int|0x00f0
)paren
op_ne
l_int|0x0
)paren
)paren
r_goto
id|exit_free
suffix:semicolon
multiline_comment|/* unused bits */
r_if
c_cond
(paren
id|conf
op_amp
l_int|0xe0
)paren
r_goto
id|exit_free
suffix:semicolon
multiline_comment|/* 0x06 and 0x07 return the last read value */
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
r_if
c_cond
(paren
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|6
)paren
op_ne
id|cur
op_logical_or
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|7
)paren
op_ne
id|cur
)paren
r_goto
id|exit_free
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
r_if
c_cond
(paren
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|6
)paren
op_ne
id|hyst
op_logical_or
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|7
)paren
op_ne
id|hyst
)paren
r_goto
id|exit_free
suffix:semicolon
id|min
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|6
)paren
op_ne
id|min
op_logical_or
id|i2c_smbus_read_word_data
c_func
(paren
id|new_client
comma
l_int|7
)paren
op_ne
id|min
)paren
r_goto
id|exit_free
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
id|lm77
suffix:semicolon
r_if
c_cond
(paren
id|kind
op_eq
id|lm77
)paren
(brace
id|name
op_assign
l_string|&quot;lm77&quot;
suffix:semicolon
)brace
multiline_comment|/* Fill in the remaining client fields and put it into the global list */
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
multiline_comment|/* Initialize the LM77 chip */
id|lm77_init_client
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
id|dev_attr_temp1_min
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
id|dev_attr_temp1_crit_hyst
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp1_min_hyst
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_temp1_max_hyst
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
DECL|function|lm77_detach_client
r_static
r_int
id|lm77_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
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
multiline_comment|/* All registers are word-sized, except for the configuration register.&n;   The LM77 uses the high-byte first convention. */
DECL|function|lm77_read_value
r_static
id|u16
id|lm77_read_value
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
id|LM77_REG_CONF
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
id|swab16
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
DECL|function|lm77_write_value
r_static
r_int
id|lm77_write_value
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
id|LM77_REG_CONF
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
id|swab16
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
DECL|function|lm77_init_client
r_static
r_void
id|lm77_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
multiline_comment|/* Initialize the LM77 chip - turn off shutdown mode */
r_int
id|conf
op_assign
id|lm77_read_value
c_func
(paren
id|client
comma
id|LM77_REG_CONF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conf
op_amp
l_int|1
)paren
id|lm77_write_value
c_func
(paren
id|client
comma
id|LM77_REG_CONF
comma
id|conf
op_amp
l_int|0xfe
)paren
suffix:semicolon
)brace
DECL|function|lm77_update_device
r_static
r_struct
id|lm77_data
op_star
id|lm77_update_device
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
id|lm77_data
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
op_plus
id|HZ
op_div
l_int|2
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
l_string|&quot;Starting lm77 update&bslash;n&quot;
)paren
suffix:semicolon
id|data-&gt;temp_input
op_assign
id|LM77_TEMP_FROM_REG
c_func
(paren
id|lm77_read_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP
)paren
)paren
suffix:semicolon
id|data-&gt;temp_hyst
op_assign
id|LM77_TEMP_FROM_REG
c_func
(paren
id|lm77_read_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP_HYST
)paren
)paren
suffix:semicolon
id|data-&gt;temp_crit
op_assign
id|LM77_TEMP_FROM_REG
c_func
(paren
id|lm77_read_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP_CRIT
)paren
)paren
suffix:semicolon
id|data-&gt;temp_min
op_assign
id|LM77_TEMP_FROM_REG
c_func
(paren
id|lm77_read_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP_MIN
)paren
)paren
suffix:semicolon
id|data-&gt;temp_max
op_assign
id|LM77_TEMP_FROM_REG
c_func
(paren
id|lm77_read_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP_MAX
)paren
)paren
suffix:semicolon
id|data-&gt;alarms
op_assign
id|lm77_read_value
c_func
(paren
id|client
comma
id|LM77_REG_TEMP
)paren
op_amp
l_int|0x0007
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
DECL|function|sensors_lm77_init
r_static
r_int
id|__init
id|sensors_lm77_init
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
id|lm77_driver
)paren
suffix:semicolon
)brace
DECL|function|sensors_lm77_exit
r_static
r_void
id|__exit
id|sensors_lm77_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|lm77_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andras BALI &lt;drewie@freemail.hu&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;LM77 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sensors_lm77_init
id|module_init
c_func
(paren
id|sensors_lm77_init
)paren
suffix:semicolon
DECL|variable|sensors_lm77_exit
id|module_exit
c_func
(paren
id|sensors_lm77_exit
)paren
suffix:semicolon
eof
