multiline_comment|/*&n;    adm1021.c - Part of lm_sensors, Linux kernel modules for hardware&n;             monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt; and&n;    Philip Edelbrock &lt;phil@netroedge.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-sensor.h&gt;
multiline_comment|/* Registers */
DECL|macro|ADM1021_SYSCTL_TEMP
mdefine_line|#define ADM1021_SYSCTL_TEMP&t;&t;1200
DECL|macro|ADM1021_SYSCTL_REMOTE_TEMP
mdefine_line|#define ADM1021_SYSCTL_REMOTE_TEMP&t;1201
DECL|macro|ADM1021_SYSCTL_DIE_CODE
mdefine_line|#define ADM1021_SYSCTL_DIE_CODE&t;&t;1202
DECL|macro|ADM1021_SYSCTL_ALARMS
mdefine_line|#define ADM1021_SYSCTL_ALARMS&t;&t;1203
DECL|macro|ADM1021_ALARM_TEMP_HIGH
mdefine_line|#define ADM1021_ALARM_TEMP_HIGH&t;&t;0x40
DECL|macro|ADM1021_ALARM_TEMP_LOW
mdefine_line|#define ADM1021_ALARM_TEMP_LOW&t;&t;0x20
DECL|macro|ADM1021_ALARM_RTEMP_HIGH
mdefine_line|#define ADM1021_ALARM_RTEMP_HIGH&t;0x10
DECL|macro|ADM1021_ALARM_RTEMP_LOW
mdefine_line|#define ADM1021_ALARM_RTEMP_LOW&t;&t;0x08
DECL|macro|ADM1021_ALARM_RTEMP_NA
mdefine_line|#define ADM1021_ALARM_RTEMP_NA&t;&t;0x04
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
multiline_comment|/* Insmod parameters */
id|SENSORS_INSMOD_8
c_func
(paren
id|adm1021
comma
id|adm1023
comma
id|max1617
comma
id|max1617a
comma
id|thmc10
comma
id|lm84
comma
id|gl523sm
comma
id|mc1066
)paren
suffix:semicolon
multiline_comment|/* adm1021 constants specified below */
multiline_comment|/* The adm1021 registers */
multiline_comment|/* Read-only */
DECL|macro|ADM1021_REG_TEMP
mdefine_line|#define ADM1021_REG_TEMP&t;&t;0x00
DECL|macro|ADM1021_REG_REMOTE_TEMP
mdefine_line|#define ADM1021_REG_REMOTE_TEMP&t;&t;0x01
DECL|macro|ADM1021_REG_STATUS
mdefine_line|#define ADM1021_REG_STATUS&t;&t;0x02
DECL|macro|ADM1021_REG_MAN_ID
mdefine_line|#define ADM1021_REG_MAN_ID&t;&t;0x0FE&t;/* 0x41 = AMD, 0x49 = TI, 0x4D = Maxim, 0x23 = Genesys , 0x54 = Onsemi*/
DECL|macro|ADM1021_REG_DEV_ID
mdefine_line|#define ADM1021_REG_DEV_ID&t;&t;0x0FF&t;/* ADM1021 = 0x0X, ADM1023 = 0x3X */
DECL|macro|ADM1021_REG_DIE_CODE
mdefine_line|#define ADM1021_REG_DIE_CODE&t;&t;0x0FF&t;/* MAX1617A */
multiline_comment|/* These use different addresses for reading/writing */
DECL|macro|ADM1021_REG_CONFIG_R
mdefine_line|#define ADM1021_REG_CONFIG_R&t;&t;0x03
DECL|macro|ADM1021_REG_CONFIG_W
mdefine_line|#define ADM1021_REG_CONFIG_W&t;&t;0x09
DECL|macro|ADM1021_REG_CONV_RATE_R
mdefine_line|#define ADM1021_REG_CONV_RATE_R&t;&t;0x04
DECL|macro|ADM1021_REG_CONV_RATE_W
mdefine_line|#define ADM1021_REG_CONV_RATE_W&t;&t;0x0A
multiline_comment|/* These are for the ADM1023&squot;s additional precision on the remote temp sensor */
DECL|macro|ADM1021_REG_REM_TEMP_PREC
mdefine_line|#define ADM1021_REG_REM_TEMP_PREC&t;0x010
DECL|macro|ADM1021_REG_REM_OFFSET
mdefine_line|#define ADM1021_REG_REM_OFFSET&t;&t;0x011
DECL|macro|ADM1021_REG_REM_OFFSET_PREC
mdefine_line|#define ADM1021_REG_REM_OFFSET_PREC&t;0x012
DECL|macro|ADM1021_REG_REM_TOS_PREC
mdefine_line|#define ADM1021_REG_REM_TOS_PREC&t;0x013
DECL|macro|ADM1021_REG_REM_THYST_PREC
mdefine_line|#define ADM1021_REG_REM_THYST_PREC&t;0x014
multiline_comment|/* limits */
DECL|macro|ADM1021_REG_TOS_R
mdefine_line|#define ADM1021_REG_TOS_R&t;&t;0x05
DECL|macro|ADM1021_REG_TOS_W
mdefine_line|#define ADM1021_REG_TOS_W&t;&t;0x0B
DECL|macro|ADM1021_REG_REMOTE_TOS_R
mdefine_line|#define ADM1021_REG_REMOTE_TOS_R&t;0x07
DECL|macro|ADM1021_REG_REMOTE_TOS_W
mdefine_line|#define ADM1021_REG_REMOTE_TOS_W&t;0x0D
DECL|macro|ADM1021_REG_THYST_R
mdefine_line|#define ADM1021_REG_THYST_R&t;&t;0x06
DECL|macro|ADM1021_REG_THYST_W
mdefine_line|#define ADM1021_REG_THYST_W&t;&t;0x0C
DECL|macro|ADM1021_REG_REMOTE_THYST_R
mdefine_line|#define ADM1021_REG_REMOTE_THYST_R&t;0x08
DECL|macro|ADM1021_REG_REMOTE_THYST_W
mdefine_line|#define ADM1021_REG_REMOTE_THYST_W&t;0x0E
multiline_comment|/* write-only */
DECL|macro|ADM1021_REG_ONESHOT
mdefine_line|#define ADM1021_REG_ONESHOT&t;&t;0x0F
multiline_comment|/* Conversions. Rounding and limit checking is only done on the TO_REG&n;   variants. Note that you should be a bit careful with which arguments&n;   these macros are called: arguments may be evaluated more than once.&n;   Fixing this is just not worth it. */
multiline_comment|/* Conversions  note: 1021 uses normal integer signed-byte format*/
DECL|macro|TEMP_FROM_REG
mdefine_line|#define TEMP_FROM_REG(val)&t;(val &gt; 127 ? (val-256)*1000 : val*1000)
DECL|macro|TEMP_TO_REG
mdefine_line|#define TEMP_TO_REG(val)&t;(SENSORS_LIMIT((val &lt; 0 ? (val/1000)+256 : val/1000),0,255))
multiline_comment|/* Initial values */
multiline_comment|/* Note: Even though I left the low and high limits named os and hyst, &n;they don&squot;t quite work like a thermostat the way the LM75 does.  I.e., &n;a lower temp than THYST actually triggers an alarm instead of &n;clearing it.  Weird, ey?   --Phil  */
multiline_comment|/* Each client has this additional data */
DECL|struct|adm1021_data
r_struct
id|adm1021_data
(brace
DECL|member|client
r_struct
id|i2c_client
id|client
suffix:semicolon
DECL|member|type
r_enum
id|chips
id|type
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
DECL|member|temp_max
id|u8
id|temp_max
suffix:semicolon
multiline_comment|/* Register values */
DECL|member|temp_hyst
id|u8
id|temp_hyst
suffix:semicolon
DECL|member|temp_input
id|u8
id|temp_input
suffix:semicolon
DECL|member|remote_temp_max
id|u8
id|remote_temp_max
suffix:semicolon
DECL|member|remote_temp_hyst
id|u8
id|remote_temp_hyst
suffix:semicolon
DECL|member|remote_temp_input
id|u8
id|remote_temp_input
suffix:semicolon
DECL|member|alarms
id|u8
id|alarms
suffix:semicolon
multiline_comment|/* special values for ADM1021 only */
DECL|member|die_code
id|u8
id|die_code
suffix:semicolon
multiline_comment|/* Special values for ADM1023 only */
DECL|member|remote_temp_prec
id|u8
id|remote_temp_prec
suffix:semicolon
DECL|member|remote_temp_os_prec
id|u8
id|remote_temp_os_prec
suffix:semicolon
DECL|member|remote_temp_hyst_prec
id|u8
id|remote_temp_hyst_prec
suffix:semicolon
DECL|member|remote_temp_offset
id|u8
id|remote_temp_offset
suffix:semicolon
DECL|member|remote_temp_offset_prec
id|u8
id|remote_temp_offset_prec
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|adm1021_attach_adapter
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
id|adm1021_detect
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
id|adm1021_init_client
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
id|adm1021_detach_client
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
id|adm1021_read_value
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
id|adm1021_write_value
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
id|adm1021_data
op_star
id|adm1021_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* (amalysh) read only mode, otherwise any limit&squot;s writing confuse BIOS */
DECL|variable|read_only
r_static
r_int
id|read_only
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This is the driver that will be inserted */
DECL|variable|adm1021_driver
r_static
r_struct
id|i2c_driver
id|adm1021_driver
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
l_string|&quot;adm1021&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_ADM1021
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|adm1021_attach_adapter
comma
dot
id|detach_client
op_assign
id|adm1021_detach_client
comma
)brace
suffix:semicolon
DECL|variable|adm1021_id
r_static
r_int
id|adm1021_id
suffix:semicolon
DECL|macro|show
mdefine_line|#define show(value)&t;&bslash;&n;static ssize_t show_##value(struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct adm1021_data *data = adm1021_update_device(dev);&t;&t;&bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, TEMP_FROM_REG(data-&gt;value));&t;&bslash;&n;}
DECL|variable|temp_max
id|show
c_func
(paren
id|temp_max
)paren
suffix:semicolon
DECL|variable|temp_hyst
id|show
c_func
(paren
id|temp_hyst
)paren
suffix:semicolon
DECL|variable|temp_input
id|show
c_func
(paren
id|temp_input
)paren
suffix:semicolon
DECL|variable|remote_temp_max
id|show
c_func
(paren
id|remote_temp_max
)paren
suffix:semicolon
DECL|variable|remote_temp_hyst
id|show
c_func
(paren
id|remote_temp_hyst
)paren
suffix:semicolon
DECL|variable|remote_temp_input
id|show
c_func
(paren
id|remote_temp_input
)paren
suffix:semicolon
DECL|macro|show2
mdefine_line|#define show2(value)&t;&bslash;&n;static ssize_t show_##value(struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct adm1021_data *data = adm1021_update_device(dev);&t;&t;&bslash;&n;&t;return sprintf(buf, &quot;%d&bslash;n&quot;, data-&gt;value);&t;&t;&t;&bslash;&n;}
DECL|variable|alarms
id|show2
c_func
(paren
id|alarms
)paren
suffix:semicolon
DECL|variable|die_code
id|show2
c_func
(paren
id|die_code
)paren
suffix:semicolon
DECL|macro|set
mdefine_line|#define set(value, reg)&t;&bslash;&n;static ssize_t set_##value(struct device *dev, const char *buf, size_t count)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct i2c_client *client = to_i2c_client(dev);&t;&t;&bslash;&n;&t;struct adm1021_data *data = i2c_get_clientdata(client);&t;&bslash;&n;&t;int temp = simple_strtoul(buf, NULL, 10);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;data-&gt;value = TEMP_TO_REG(temp);&t;&t;&t;&bslash;&n;&t;adm1021_write_value(client, reg, data-&gt;value);&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|set
c_func
(paren
id|temp_max
comma
id|ADM1021_REG_TOS_W
)paren
suffix:semicolon
id|set
c_func
(paren
id|temp_hyst
comma
id|ADM1021_REG_THYST_W
)paren
suffix:semicolon
id|set
c_func
(paren
id|remote_temp_max
comma
id|ADM1021_REG_REMOTE_TOS_W
)paren
suffix:semicolon
id|set
c_func
(paren
id|remote_temp_hyst
comma
id|ADM1021_REG_REMOTE_THYST_W
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
id|temp1_min
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|show_temp_hyst
comma
id|set_temp_hyst
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
id|show_temp_input
comma
l_int|NULL
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
id|show_remote_temp_max
comma
id|set_remote_temp_max
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
id|show_remote_temp_hyst
comma
id|set_remote_temp_hyst
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
id|show_remote_temp_input
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
r_static
id|DEVICE_ATTR
c_func
(paren
id|die_code
comma
id|S_IRUGO
comma
id|show_die_code
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|adm1021_attach_adapter
r_static
r_int
id|adm1021_attach_adapter
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
id|adm1021_detect
)paren
suffix:semicolon
)brace
DECL|function|adm1021_detect
r_static
r_int
id|adm1021_detect
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
suffix:semicolon
r_struct
id|i2c_client
op_star
id|new_client
suffix:semicolon
r_struct
id|adm1021_data
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
op_assign
l_string|&quot;&quot;
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
l_string|&quot;adm1021_detect called for an ISA bus adapter?!?&bslash;n&quot;
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
id|error0
suffix:semicolon
multiline_comment|/* OK. For now, we presume we have a valid client. We now create the&n;&t;   client structure, even though we cannot fill it completely yet.&n;&t;   But it allows us to access adm1021_{read,write}_value. */
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
id|adm1021_data
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
id|adm1021_data
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
id|adm1021_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now, we do the remaining detection. */
r_if
c_cond
(paren
id|kind
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_STATUS
)paren
op_amp
l_int|0x03
)paren
op_ne
l_int|0x00
op_logical_or
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_CONFIG_R
)paren
op_amp
l_int|0x3F
)paren
op_ne
l_int|0x00
op_logical_or
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_CONV_RATE_R
)paren
op_amp
l_int|0xF8
)paren
op_ne
l_int|0x00
)paren
(brace
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|error1
suffix:semicolon
)brace
)brace
multiline_comment|/* Determine the chip type. */
r_if
c_cond
(paren
id|kind
op_le
l_int|0
)paren
(brace
id|i
op_assign
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_MAN_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0x41
)paren
r_if
c_cond
(paren
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_DEV_ID
)paren
op_amp
l_int|0x0F0
)paren
op_eq
l_int|0x030
)paren
id|kind
op_assign
id|adm1023
suffix:semicolon
r_else
id|kind
op_assign
id|adm1021
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
op_eq
l_int|0x49
)paren
id|kind
op_assign
id|thmc10
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
op_eq
l_int|0x23
)paren
id|kind
op_assign
id|gl523sm
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|0x4d
)paren
op_logical_and
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_DEV_ID
)paren
op_eq
l_int|0x01
)paren
)paren
id|kind
op_assign
id|max1617a
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
op_eq
l_int|0x54
)paren
id|kind
op_assign
id|mc1066
suffix:semicolon
multiline_comment|/* LM84 Mfr ID in a different place, and it has more unused bits */
r_else
r_if
c_cond
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_CONV_RATE_R
)paren
op_eq
l_int|0x00
op_logical_and
(paren
id|kind
op_eq
l_int|0
multiline_comment|/* skip extra detection */
op_logical_or
(paren
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_CONFIG_R
)paren
op_amp
l_int|0x7F
)paren
op_eq
l_int|0x00
op_logical_and
(paren
id|adm1021_read_value
c_func
(paren
id|new_client
comma
id|ADM1021_REG_STATUS
)paren
op_amp
l_int|0xAB
)paren
op_eq
l_int|0x00
)paren
)paren
)paren
id|kind
op_assign
id|lm84
suffix:semicolon
r_else
id|kind
op_assign
id|max1617
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kind
op_eq
id|max1617
)paren
(brace
id|type_name
op_assign
l_string|&quot;max1617&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|max1617a
)paren
(brace
id|type_name
op_assign
l_string|&quot;max1617a&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|adm1021
)paren
(brace
id|type_name
op_assign
l_string|&quot;adm1021&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|adm1023
)paren
(brace
id|type_name
op_assign
l_string|&quot;adm1023&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|thmc10
)paren
(brace
id|type_name
op_assign
l_string|&quot;thmc10&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|lm84
)paren
(brace
id|type_name
op_assign
l_string|&quot;lm84&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|gl523sm
)paren
(brace
id|type_name
op_assign
l_string|&quot;gl523sm&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|kind
op_eq
id|mc1066
)paren
(brace
id|type_name
op_assign
l_string|&quot;mc1066&quot;
suffix:semicolon
)brace
multiline_comment|/* Fill in the remaining client fields and put it into the global list */
id|strlcpy
c_func
(paren
id|new_client-&gt;name
comma
id|type_name
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
id|data-&gt;type
op_assign
id|kind
suffix:semicolon
id|new_client-&gt;id
op_assign
id|adm1021_id
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
id|error1
suffix:semicolon
multiline_comment|/* Initialize the ADM1021 chip */
r_if
c_cond
(paren
id|kind
op_ne
id|lm84
)paren
id|adm1021_init_client
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
id|dev_attr_alarms
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;type
op_eq
id|adm1021
)paren
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_die_code
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error1
suffix:colon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
id|error0
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|adm1021_init_client
r_static
r_void
id|adm1021_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
multiline_comment|/* Enable ADC and disable suspend mode */
id|adm1021_write_value
c_func
(paren
id|client
comma
id|ADM1021_REG_CONFIG_W
comma
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_CONFIG_R
)paren
op_amp
l_int|0xBF
)paren
suffix:semicolon
multiline_comment|/* Set Conversion rate to 1/sec (this can be tinkered with) */
id|adm1021_write_value
c_func
(paren
id|client
comma
id|ADM1021_REG_CONV_RATE_W
comma
l_int|0x04
)paren
suffix:semicolon
)brace
DECL|function|adm1021_detach_client
r_static
r_int
id|adm1021_detach_client
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
multiline_comment|/* All registers are byte-sized */
DECL|function|adm1021_read_value
r_static
r_int
id|adm1021_read_value
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
r_return
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|function|adm1021_write_value
r_static
r_int
id|adm1021_write_value
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
op_logical_neg
id|read_only
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adm1021_update_device
r_static
r_struct
id|adm1021_data
op_star
id|adm1021_update_device
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
id|adm1021_data
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
l_string|&quot;Starting adm1021 update&bslash;n&quot;
)paren
suffix:semicolon
id|data-&gt;temp_input
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_TEMP
)paren
suffix:semicolon
id|data-&gt;temp_max
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_TOS_R
)paren
suffix:semicolon
id|data-&gt;temp_hyst
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_THYST_R
)paren
suffix:semicolon
id|data-&gt;remote_temp_input
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REMOTE_TEMP
)paren
suffix:semicolon
id|data-&gt;remote_temp_max
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REMOTE_TOS_R
)paren
suffix:semicolon
id|data-&gt;remote_temp_hyst
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REMOTE_THYST_R
)paren
suffix:semicolon
id|data-&gt;alarms
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_STATUS
)paren
op_amp
l_int|0xec
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;type
op_eq
id|adm1021
)paren
id|data-&gt;die_code
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_DIE_CODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;type
op_eq
id|adm1023
)paren
(brace
id|data-&gt;remote_temp_prec
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REM_TEMP_PREC
)paren
suffix:semicolon
id|data-&gt;remote_temp_os_prec
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REM_TOS_PREC
)paren
suffix:semicolon
id|data-&gt;remote_temp_hyst_prec
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REM_THYST_PREC
)paren
suffix:semicolon
id|data-&gt;remote_temp_offset
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REM_OFFSET
)paren
suffix:semicolon
id|data-&gt;remote_temp_offset_prec
op_assign
id|adm1021_read_value
c_func
(paren
id|client
comma
id|ADM1021_REG_REM_OFFSET_PREC
)paren
suffix:semicolon
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
DECL|function|sensors_adm1021_init
r_static
r_int
id|__init
id|sensors_adm1021_init
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
id|adm1021_driver
)paren
suffix:semicolon
)brace
DECL|function|sensors_adm1021_exit
r_static
r_void
id|__exit
id|sensors_adm1021_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|adm1021_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt; and &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;adm1021 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|read_only
comma
r_bool
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|read_only
comma
l_string|&quot;Don&squot;t set any values, read only mode&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|sensors_adm1021_init
)paren
id|module_exit
c_func
(paren
id|sensors_adm1021_exit
)paren
eof
