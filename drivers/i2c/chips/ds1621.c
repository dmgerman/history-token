multiline_comment|/*&n;    ds1621.c - Part of lm_sensors, Linux kernel modules for hardware&n;             monitoring&n;    Christian W. Zuckschwerdt  &lt;zany@triq.net&gt;  2000-11-23&n;    based on lm75.c by Frodo Looijaard &lt;frodol@dds.nl&gt;&n;    Ported to Linux 2.6 by Aurelien Jarno &lt;aurelien@aurel32.net&gt; with &n;    the help of Jean Delvare &lt;khali@linux-fr.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-sensor.h&gt;
macro_line|#include &quot;lm75.h&quot;
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
l_int|0x48
comma
l_int|0x4f
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
DECL|variable|ds1621
id|SENSORS_INSMOD_1
c_func
(paren
id|ds1621
)paren
suffix:semicolon
DECL|variable|polarity
r_static
r_int
id|polarity
op_assign
op_minus
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|polarity
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|polarity
comma
l_string|&quot;Output&squot;s polarity: 0 = active high, 1 = active low&quot;
)paren
suffix:semicolon
multiline_comment|/* Many DS1621 constants specified below */
multiline_comment|/* Config register used for detection         */
multiline_comment|/*  7    6    5    4    3    2    1    0      */
multiline_comment|/* |Done|THF |TLF |NVB | 1  | 0  |POL |1SHOT| */
DECL|macro|DS1621_REG_CONFIG_MASK
mdefine_line|#define DS1621_REG_CONFIG_MASK&t;&t;0x0C
DECL|macro|DS1621_REG_CONFIG_VAL
mdefine_line|#define DS1621_REG_CONFIG_VAL&t;&t;0x08
DECL|macro|DS1621_REG_CONFIG_POLARITY
mdefine_line|#define DS1621_REG_CONFIG_POLARITY&t;0x02
DECL|macro|DS1621_REG_CONFIG_1SHOT
mdefine_line|#define DS1621_REG_CONFIG_1SHOT&t;&t;0x01
DECL|macro|DS1621_REG_CONFIG_DONE
mdefine_line|#define DS1621_REG_CONFIG_DONE&t;&t;0x80
multiline_comment|/* The DS1621 registers */
DECL|macro|DS1621_REG_TEMP
mdefine_line|#define DS1621_REG_TEMP&t;&t;&t;0xAA /* word, RO */
DECL|macro|DS1621_REG_TEMP_MIN
mdefine_line|#define DS1621_REG_TEMP_MIN&t;&t;0xA1 /* word, RW */
DECL|macro|DS1621_REG_TEMP_MAX
mdefine_line|#define DS1621_REG_TEMP_MAX&t;&t;0xA2 /* word, RW */
DECL|macro|DS1621_REG_CONF
mdefine_line|#define DS1621_REG_CONF&t;&t;&t;0xAC /* byte, RW */
DECL|macro|DS1621_COM_START
mdefine_line|#define DS1621_COM_START&t;&t;0xEE /* no data */
multiline_comment|/* The DS1621 configuration register */
DECL|macro|DS1621_ALARM_TEMP_HIGH
mdefine_line|#define DS1621_ALARM_TEMP_HIGH&t;&t;0x40
DECL|macro|DS1621_ALARM_TEMP_LOW
mdefine_line|#define DS1621_ALARM_TEMP_LOW&t;&t;0x20
multiline_comment|/* Conversions. Rounding and limit checking is only done on the TO_REG&n;   variants. Note that you should be a bit careful with which arguments&n;   these macros are called: arguments may be evaluated more than once.&n;   Fixing this is just not worth it. */
DECL|macro|ALARMS_FROM_REG
mdefine_line|#define ALARMS_FROM_REG(val) ((val) &amp; &bslash;&n;                              (DS1621_ALARM_TEMP_HIGH | DS1621_ALARM_TEMP_LOW))
multiline_comment|/* Each client has this additional data */
DECL|struct|ds1621_data
r_struct
id|ds1621_data
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
multiline_comment|/* !=0 if following fields are valid */
DECL|member|last_updated
r_int
r_int
id|last_updated
suffix:semicolon
multiline_comment|/* In jiffies */
DECL|member|temp
DECL|member|temp_min
DECL|member|temp_max
id|u16
id|temp
comma
id|temp_min
comma
id|temp_max
suffix:semicolon
multiline_comment|/* Register values, word */
DECL|member|conf
id|u8
id|conf
suffix:semicolon
multiline_comment|/* Register encoding, combined */
)brace
suffix:semicolon
r_static
r_int
id|ds1621_attach_adapter
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
id|ds1621_detect
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
id|ds1621_init_client
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
id|ds1621_detach_client
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
id|ds1621_data
op_star
id|ds1621_update_client
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* This is the driver that will be inserted */
DECL|variable|ds1621_driver
r_static
r_struct
id|i2c_driver
id|ds1621_driver
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
l_string|&quot;ds1621&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_DS1621
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|ds1621_attach_adapter
comma
dot
id|detach_client
op_assign
id|ds1621_detach_client
comma
)brace
suffix:semicolon
DECL|variable|ds1621_id
r_static
r_int
id|ds1621_id
suffix:semicolon
multiline_comment|/* All registers are word-sized, except for the configuration register.&n;   DS1621 uses a high-byte first convention, which is exactly opposite to&n;   the usual practice. */
DECL|function|ds1621_read_value
r_static
r_int
id|ds1621_read_value
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
id|DS1621_REG_CONF
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
multiline_comment|/* All registers are word-sized, except for the configuration register.&n;   DS1621 uses a high-byte first convention, which is exactly opposite to&n;   the usual practice. */
DECL|function|ds1621_write_value
r_static
r_int
id|ds1621_write_value
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
id|DS1621_REG_CONF
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
DECL|function|ds1621_init_client
r_static
r_void
id|ds1621_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
id|reg
op_assign
id|ds1621_read_value
c_func
(paren
id|client
comma
id|DS1621_REG_CONF
)paren
suffix:semicolon
multiline_comment|/* switch to continous conversion mode */
id|reg
op_and_assign
op_complement
id|DS1621_REG_CONFIG_1SHOT
suffix:semicolon
multiline_comment|/* setup output polarity */
r_if
c_cond
(paren
id|polarity
op_eq
l_int|0
)paren
id|reg
op_and_assign
op_complement
id|DS1621_REG_CONFIG_POLARITY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|polarity
op_eq
l_int|1
)paren
id|reg
op_or_assign
id|DS1621_REG_CONFIG_POLARITY
suffix:semicolon
id|ds1621_write_value
c_func
(paren
id|client
comma
id|DS1621_REG_CONF
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* start conversion */
id|i2c_smbus_write_byte
c_func
(paren
id|client
comma
id|DS1621_COM_START
)paren
suffix:semicolon
)brace
DECL|macro|show
mdefine_line|#define show(value)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t show_##value(struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct ds1621_data *data = ds1621_update_client(dev);&t;&t;&bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, LM75_TEMP_FROM_REG(data-&gt;value));&t;&bslash;&n;}
DECL|variable|temp
id|show
c_func
(paren
id|temp
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
DECL|macro|set_temp
mdefine_line|#define set_temp(suffix, value, reg)&t;&t;&t;&t;&t;&bslash;&n;static ssize_t set_temp_##suffix(struct device *dev, const char *buf,&t;&bslash;&n;&t;&t;&t;&t; size_t count)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev);&t;&t;&t;&bslash;&n;&t;struct ds1621_data *data = ds1621_update_client(dev);&t;&t;&bslash;&n;&t;data-&gt;value = LM75_TEMP_TO_REG(simple_strtoul(buf, NULL, 10));&t;&bslash;&n;&t;ds1621_write_value(client, reg, data-&gt;value);&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|set_temp
c_func
(paren
id|min
comma
id|temp_min
comma
id|DS1621_REG_TEMP_MIN
)paren
suffix:semicolon
id|set_temp
c_func
(paren
id|max
comma
id|temp_max
comma
id|DS1621_REG_TEMP_MAX
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
id|ds1621_data
op_star
id|data
op_assign
id|ds1621_update_client
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
id|ALARMS_FROM_REG
c_func
(paren
id|data-&gt;conf
)paren
)paren
suffix:semicolon
)brace
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
DECL|function|ds1621_attach_adapter
r_static
r_int
id|ds1621_attach_adapter
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
id|ds1621_detect
)paren
suffix:semicolon
)brace
multiline_comment|/* This function is called by i2c_detect */
DECL|function|ds1621_detect
r_int
id|ds1621_detect
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
id|conf
comma
id|temp
suffix:semicolon
r_struct
id|i2c_client
op_star
id|new_client
suffix:semicolon
r_struct
id|ds1621_data
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
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
op_or
id|I2C_FUNC_SMBUS_WRITE_BYTE
)paren
)paren
r_goto
m_exit
suffix:semicolon
multiline_comment|/* OK. For now, we presume we have a valid client. We now create the&n;&t;   client structure, even though we cannot fill it completely yet.&n;&t;   But it allows us to access ds1621_{read,write}_value. */
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
id|ds1621_data
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
id|ds1621_data
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
id|ds1621_driver
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
id|conf
op_assign
id|ds1621_read_value
c_func
(paren
id|new_client
comma
id|DS1621_REG_CONF
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|conf
op_amp
id|DS1621_REG_CONFIG_MASK
)paren
op_ne
id|DS1621_REG_CONFIG_VAL
)paren
r_goto
id|exit_free
suffix:semicolon
id|temp
op_assign
id|ds1621_read_value
c_func
(paren
id|new_client
comma
id|DS1621_REG_TEMP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x007f
)paren
r_goto
id|exit_free
suffix:semicolon
id|temp
op_assign
id|ds1621_read_value
c_func
(paren
id|new_client
comma
id|DS1621_REG_TEMP_MIN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x007f
)paren
r_goto
id|exit_free
suffix:semicolon
id|temp
op_assign
id|ds1621_read_value
c_func
(paren
id|new_client
comma
id|DS1621_REG_TEMP_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x007f
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
id|ds1621
suffix:semicolon
multiline_comment|/* Fill in remaining client fields and put it into the global list */
id|strlcpy
c_func
(paren
id|new_client-&gt;name
comma
l_string|&quot;ds1621&quot;
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
id|new_client-&gt;id
op_assign
id|ds1621_id
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
multiline_comment|/* Initialize the DS1621 chip */
id|ds1621_init_client
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
id|dev_attr_alarms
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/* OK, this is not exactly good programming practice, usually. But it is&n;   very code-efficient in this case. */
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
DECL|function|ds1621_detach_client
r_static
r_int
id|ds1621_detach_client
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
DECL|function|ds1621_update_client
r_static
r_struct
id|ds1621_data
op_star
id|ds1621_update_client
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
id|ds1621_data
op_star
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|u8
id|new_conf
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
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;Starting ds1621 update&bslash;n&quot;
)paren
suffix:semicolon
id|data-&gt;conf
op_assign
id|ds1621_read_value
c_func
(paren
id|client
comma
id|DS1621_REG_CONF
)paren
suffix:semicolon
id|data-&gt;temp
op_assign
id|ds1621_read_value
c_func
(paren
id|client
comma
id|DS1621_REG_TEMP
)paren
suffix:semicolon
id|data-&gt;temp_min
op_assign
id|ds1621_read_value
c_func
(paren
id|client
comma
id|DS1621_REG_TEMP_MIN
)paren
suffix:semicolon
id|data-&gt;temp_max
op_assign
id|ds1621_read_value
c_func
(paren
id|client
comma
id|DS1621_REG_TEMP_MAX
)paren
suffix:semicolon
multiline_comment|/* reset alarms if neccessary */
id|new_conf
op_assign
id|data-&gt;conf
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;temp
OL
id|data-&gt;temp_min
)paren
id|new_conf
op_and_assign
op_complement
id|DS1621_ALARM_TEMP_LOW
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;temp
OG
id|data-&gt;temp_max
)paren
id|new_conf
op_and_assign
op_complement
id|DS1621_ALARM_TEMP_HIGH
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;conf
op_ne
id|new_conf
)paren
id|ds1621_write_value
c_func
(paren
id|client
comma
id|DS1621_REG_CONF
comma
id|new_conf
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
DECL|function|ds1621_init
r_static
r_int
id|__init
id|ds1621_init
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
id|ds1621_driver
)paren
suffix:semicolon
)brace
DECL|function|ds1621_exit
r_static
r_void
id|__exit
id|ds1621_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|ds1621_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christian W. Zuckschwerdt &lt;zany@triq.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;DS1621 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ds1621_init
id|module_init
c_func
(paren
id|ds1621_init
)paren
suffix:semicolon
DECL|variable|ds1621_exit
id|module_exit
c_func
(paren
id|ds1621_exit
)paren
suffix:semicolon
eof
