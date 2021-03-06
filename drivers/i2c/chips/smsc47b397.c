multiline_comment|/*&n;    smsc47b397.c - Part of lm_sensors, Linux kernel modules&n;&t;&t;&t;for hardware monitoring&n;&n;    Supports the SMSC LPC47B397-NC Super-I/O chip.&n;&n;    Author/Maintainer: Mark M. Hoffman &lt;mhoffman@lightlink.com&gt;&n;&t;Copyright (C) 2004 Utilitek Systems, Inc.&n;&n;    derived in part from smsc47m1.c:&n;&t;Copyright (C) 2002 Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;&t;Copyright (C) 2004 Jean Delvare &lt;khali@linux-fr.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-sensor.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
multiline_comment|/* Address is autodetected, there is no default value */
DECL|variable|normal_isa
r_static
r_int
r_int
id|normal_isa
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
id|I2C_CLIENT_ISA_END
)brace
suffix:semicolon
DECL|variable|forces
r_static
r_struct
id|i2c_force_data
id|forces
(braket
)braket
op_assign
(brace
(brace
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|enum|chips
DECL|enumerator|any_chip
DECL|enumerator|smsc47b397
r_enum
id|chips
(brace
id|any_chip
comma
id|smsc47b397
)brace
suffix:semicolon
DECL|variable|addr_data
r_static
r_struct
id|i2c_address_data
id|addr_data
op_assign
(brace
dot
id|normal_i2c
op_assign
id|normal_i2c
comma
dot
id|normal_isa
op_assign
id|normal_isa
comma
dot
id|probe
op_assign
id|normal_i2c
comma
multiline_comment|/* cheat */
dot
id|ignore
op_assign
id|normal_i2c
comma
multiline_comment|/* cheat */
dot
id|forces
op_assign
id|forces
comma
)brace
suffix:semicolon
multiline_comment|/* Super-I/0 registers and commands */
DECL|macro|REG
mdefine_line|#define&t;REG&t;0x2e&t;/* The register to read/write */
DECL|macro|VAL
mdefine_line|#define&t;VAL&t;0x2f&t;/* The value to read/write */
DECL|function|superio_outb
r_static
r_inline
r_void
id|superio_outb
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|outb
c_func
(paren
id|reg
comma
id|REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|VAL
)paren
suffix:semicolon
)brace
DECL|function|superio_inb
r_static
r_inline
r_int
id|superio_inb
c_func
(paren
r_int
id|reg
)paren
(brace
id|outb
c_func
(paren
id|reg
comma
id|REG
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|VAL
)paren
suffix:semicolon
)brace
multiline_comment|/* select superio logical device */
DECL|function|superio_select
r_static
r_inline
r_void
id|superio_select
c_func
(paren
r_int
id|ld
)paren
(brace
id|superio_outb
c_func
(paren
l_int|0x07
comma
id|ld
)paren
suffix:semicolon
)brace
DECL|function|superio_enter
r_static
r_inline
r_void
id|superio_enter
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0x55
comma
id|REG
)paren
suffix:semicolon
)brace
DECL|function|superio_exit
r_static
r_inline
r_void
id|superio_exit
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0xAA
comma
id|REG
)paren
suffix:semicolon
)brace
DECL|macro|SUPERIO_REG_DEVID
mdefine_line|#define SUPERIO_REG_DEVID&t;0x20
DECL|macro|SUPERIO_REG_DEVREV
mdefine_line|#define SUPERIO_REG_DEVREV&t;0x21
DECL|macro|SUPERIO_REG_BASE_MSB
mdefine_line|#define SUPERIO_REG_BASE_MSB&t;0x60
DECL|macro|SUPERIO_REG_BASE_LSB
mdefine_line|#define SUPERIO_REG_BASE_LSB&t;0x61
DECL|macro|SUPERIO_REG_LD8
mdefine_line|#define SUPERIO_REG_LD8&t;&t;0x08
DECL|macro|SMSC_EXTENT
mdefine_line|#define SMSC_EXTENT&t;&t;0x02
multiline_comment|/* 0 &lt;= nr &lt;= 3 */
DECL|variable|smsc47b397_reg_temp
r_static
id|u8
id|smsc47b397_reg_temp
(braket
)braket
op_assign
(brace
l_int|0x25
comma
l_int|0x26
comma
l_int|0x27
comma
l_int|0x80
)brace
suffix:semicolon
DECL|macro|SMSC47B397_REG_TEMP
mdefine_line|#define SMSC47B397_REG_TEMP(nr)&t;(smsc47b397_reg_temp[(nr)])
multiline_comment|/* 0 &lt;= nr &lt;= 3 */
DECL|macro|SMSC47B397_REG_FAN_LSB
mdefine_line|#define SMSC47B397_REG_FAN_LSB(nr) (0x28 + 2 * (nr))
DECL|macro|SMSC47B397_REG_FAN_MSB
mdefine_line|#define SMSC47B397_REG_FAN_MSB(nr) (0x29 + 2 * (nr))
DECL|struct|smsc47b397_data
r_struct
id|smsc47b397_data
(brace
DECL|member|client
r_struct
id|i2c_client
id|client
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|update_lock
r_struct
id|semaphore
id|update_lock
suffix:semicolon
DECL|member|last_updated
r_int
r_int
id|last_updated
suffix:semicolon
multiline_comment|/* in jiffies */
DECL|member|valid
r_int
id|valid
suffix:semicolon
multiline_comment|/* register values */
DECL|member|fan
id|u16
id|fan
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|temp
id|u8
id|temp
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|smsc47b397_read_value
r_static
r_int
id|smsc47b397_read_value
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
r_struct
id|smsc47b397_data
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
id|res
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|client-&gt;addr
)paren
suffix:semicolon
id|res
op_assign
id|inb_p
c_func
(paren
id|client-&gt;addr
op_plus
l_int|1
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|smsc47b397_update_device
r_static
r_struct
id|smsc47b397_data
op_star
id|smsc47b397_update_device
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
id|smsc47b397_data
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
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;starting device update...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* 4 temperature inputs, 4 fan inputs */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data-&gt;temp
(braket
id|i
)braket
op_assign
id|smsc47b397_read_value
c_func
(paren
id|client
comma
id|SMSC47B397_REG_TEMP
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/* must read LSB first */
id|data-&gt;fan
(braket
id|i
)braket
op_assign
id|smsc47b397_read_value
c_func
(paren
id|client
comma
id|SMSC47B397_REG_FAN_LSB
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|data-&gt;fan
(braket
id|i
)braket
op_or_assign
id|smsc47b397_read_value
c_func
(paren
id|client
comma
id|SMSC47B397_REG_FAN_MSB
c_func
(paren
id|i
)paren
)paren
op_lshift
l_int|8
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
id|dev_dbg
c_func
(paren
op_amp
id|client-&gt;dev
comma
l_string|&quot;... device update complete&bslash;n&quot;
)paren
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
multiline_comment|/* TEMP: 0.001C/bit (-128C to +127C)&n;   REG: 1C/bit, two&squot;s complement */
DECL|function|temp_from_reg
r_static
r_int
id|temp_from_reg
c_func
(paren
id|u8
id|reg
)paren
(brace
r_return
(paren
id|s8
)paren
id|reg
op_star
l_int|1000
suffix:semicolon
)brace
multiline_comment|/* 0 &lt;= nr &lt;= 3 */
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
comma
r_int
id|nr
)paren
(brace
r_struct
id|smsc47b397_data
op_star
id|data
op_assign
id|smsc47b397_update_device
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
id|temp_from_reg
c_func
(paren
id|data-&gt;temp
(braket
id|nr
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|macro|sysfs_temp
mdefine_line|#define sysfs_temp(num) &bslash;&n;static ssize_t show_temp##num(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;return show_temp(dev, buf, num-1); &bslash;&n;} &bslash;&n;static DEVICE_ATTR(temp##num##_input, S_IRUGO, show_temp##num, NULL)
id|sysfs_temp
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|sysfs_temp
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|sysfs_temp
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|sysfs_temp
c_func
(paren
l_int|4
)paren
suffix:semicolon
DECL|macro|device_create_file_temp
mdefine_line|#define device_create_file_temp(client, num) &bslash;&n;&t;device_create_file(&amp;client-&gt;dev, &amp;dev_attr_temp##num##_input)
multiline_comment|/* FAN: 1 RPM/bit&n;   REG: count of 90kHz pulses / revolution */
DECL|function|fan_from_reg
r_static
r_int
id|fan_from_reg
c_func
(paren
id|u16
id|reg
)paren
(brace
r_return
l_int|90000
op_star
l_int|60
op_div
id|reg
suffix:semicolon
)brace
multiline_comment|/* 0 &lt;= nr &lt;= 3 */
DECL|function|show_fan
r_static
id|ssize_t
id|show_fan
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
comma
r_int
id|nr
)paren
(brace
r_struct
id|smsc47b397_data
op_star
id|data
op_assign
id|smsc47b397_update_device
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
id|fan_from_reg
c_func
(paren
id|data-&gt;fan
(braket
id|nr
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|macro|sysfs_fan
mdefine_line|#define sysfs_fan(num) &bslash;&n;static ssize_t show_fan##num(struct device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;return show_fan(dev, buf, num-1); &bslash;&n;} &bslash;&n;static DEVICE_ATTR(fan##num##_input, S_IRUGO, show_fan##num, NULL)
id|sysfs_fan
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|sysfs_fan
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|sysfs_fan
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|sysfs_fan
c_func
(paren
l_int|4
)paren
suffix:semicolon
DECL|macro|device_create_file_fan
mdefine_line|#define device_create_file_fan(client, num) &bslash;&n;&t;device_create_file(&amp;client-&gt;dev, &amp;dev_attr_fan##num##_input)
r_static
r_int
id|smsc47b397_detect
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|addr
comma
r_int
id|kind
)paren
suffix:semicolon
DECL|function|smsc47b397_attach_adapter
r_static
r_int
id|smsc47b397_attach_adapter
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
id|smsc47b397_detect
)paren
suffix:semicolon
)brace
DECL|function|smsc47b397_detach_client
r_static
r_int
id|smsc47b397_detach_client
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
id|release_region
c_func
(paren
id|client-&gt;addr
comma
id|SMSC_EXTENT
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
DECL|variable|smsc47b397_driver
r_static
r_struct
id|i2c_driver
id|smsc47b397_driver
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
l_string|&quot;smsc47b397&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_SMSC47B397
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|smsc47b397_attach_adapter
comma
dot
id|detach_client
op_assign
id|smsc47b397_detach_client
comma
)brace
suffix:semicolon
DECL|function|smsc47b397_detect
r_static
r_int
id|smsc47b397_detect
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|addr
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
id|smsc47b397_data
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
id|i2c_is_isa_adapter
c_func
(paren
id|adapter
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|addr
comma
id|SMSC_EXTENT
comma
id|smsc47b397_driver.name
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;Region 0x%x already in use!&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
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
id|smsc47b397_data
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
id|error_release
suffix:semicolon
)brace
id|memset
c_func
(paren
id|data
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|smsc47b397_data
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
id|addr
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|data-&gt;lock
)paren
suffix:semicolon
id|new_client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|new_client-&gt;driver
op_assign
op_amp
id|smsc47b397_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|strlcpy
c_func
(paren
id|new_client-&gt;name
comma
l_string|&quot;smsc47b397&quot;
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
id|init_MUTEX
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
id|error_free
suffix:semicolon
id|device_create_file_temp
c_func
(paren
id|new_client
comma
l_int|1
)paren
suffix:semicolon
id|device_create_file_temp
c_func
(paren
id|new_client
comma
l_int|2
)paren
suffix:semicolon
id|device_create_file_temp
c_func
(paren
id|new_client
comma
l_int|3
)paren
suffix:semicolon
id|device_create_file_temp
c_func
(paren
id|new_client
comma
l_int|4
)paren
suffix:semicolon
id|device_create_file_fan
c_func
(paren
id|new_client
comma
l_int|1
)paren
suffix:semicolon
id|device_create_file_fan
c_func
(paren
id|new_client
comma
l_int|2
)paren
suffix:semicolon
id|device_create_file_fan
c_func
(paren
id|new_client
comma
l_int|3
)paren
suffix:semicolon
id|device_create_file_fan
c_func
(paren
id|new_client
comma
l_int|4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_free
suffix:colon
id|kfree
c_func
(paren
id|new_client
)paren
suffix:semicolon
id|error_release
suffix:colon
id|release_region
c_func
(paren
id|addr
comma
id|SMSC_EXTENT
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|smsc47b397_find
r_static
r_int
id|__init
id|smsc47b397_find
c_func
(paren
r_int
r_int
op_star
id|addr
)paren
(brace
id|u8
id|id
comma
id|rev
suffix:semicolon
id|superio_enter
c_func
(paren
)paren
suffix:semicolon
id|id
op_assign
id|superio_inb
c_func
(paren
id|SUPERIO_REG_DEVID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_ne
l_int|0x6f
)paren
(brace
id|superio_exit
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|rev
op_assign
id|superio_inb
c_func
(paren
id|SUPERIO_REG_DEVREV
)paren
suffix:semicolon
id|superio_select
c_func
(paren
id|SUPERIO_REG_LD8
)paren
suffix:semicolon
op_star
id|addr
op_assign
(paren
id|superio_inb
c_func
(paren
id|SUPERIO_REG_BASE_MSB
)paren
op_lshift
l_int|8
)paren
op_or
id|superio_inb
c_func
(paren
id|SUPERIO_REG_BASE_LSB
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smsc47b397: found SMSC LPC47B397-NC &quot;
l_string|&quot;(base address 0x%04x, revision %u)&bslash;n&quot;
comma
op_star
id|addr
comma
id|rev
)paren
suffix:semicolon
id|superio_exit
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smsc47b397_init
r_static
r_int
id|__init
id|smsc47b397_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|smsc47b397_find
c_func
(paren
id|normal_isa
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|smsc47b397_driver
)paren
suffix:semicolon
)brace
DECL|function|smsc47b397_exit
r_static
r_void
id|__exit
id|smsc47b397_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|smsc47b397_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mark M. Hoffman &lt;mhoffman@lightlink.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SMSC LPC47B397 driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|smsc47b397_init
id|module_init
c_func
(paren
id|smsc47b397_init
)paren
suffix:semicolon
DECL|variable|smsc47b397_exit
id|module_exit
c_func
(paren
id|smsc47b397_exit
)paren
suffix:semicolon
eof
