multiline_comment|/*&n;    smsc47m1.c - Part of lm_sensors, Linux kernel modules&n;                 for hardware monitoring&n;&n;    Supports the SMSC LPC47B27x, LPC47M10x, LPC47M13x and LPC47M14x&n;    Super-I/O chips.&n;&n;    Copyright (C) 2002 Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;    Copyright (C) 2004 Jean Delvare &lt;khali@linux-fr.org&gt;&n;    Ported to Linux 2.6 by Gabriele Gorla &lt;gorlik@yahoo.com&gt;&n;                        and Jean Delvare&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
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
DECL|enumerator|smsc47m1
r_enum
id|chips
(brace
id|any_chip
comma
id|smsc47m1
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
r_static
r_inline
r_void
DECL|function|superio_outb
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
r_static
r_inline
r_int
DECL|function|superio_inb
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
multiline_comment|/* logical device for fans is 0x0A */
DECL|macro|superio_select
mdefine_line|#define superio_select() superio_outb(0x07, 0x0A)
r_static
r_inline
r_void
DECL|function|superio_enter
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
r_static
r_inline
r_void
DECL|function|superio_exit
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
DECL|macro|SUPERIO_REG_ACT
mdefine_line|#define SUPERIO_REG_ACT&t;&t;0x30
DECL|macro|SUPERIO_REG_BASE
mdefine_line|#define SUPERIO_REG_BASE&t;0x60
DECL|macro|SUPERIO_REG_DEVID
mdefine_line|#define SUPERIO_REG_DEVID&t;0x20
multiline_comment|/* Logical device registers */
DECL|macro|SMSC_EXTENT
mdefine_line|#define SMSC_EXTENT&t;&t;0x80
multiline_comment|/* nr is 0 or 1 in the macros below */
DECL|macro|SMSC47M1_REG_ALARM
mdefine_line|#define SMSC47M1_REG_ALARM&t;&t;0x04
DECL|macro|SMSC47M1_REG_TPIN
mdefine_line|#define SMSC47M1_REG_TPIN(nr)&t;&t;(0x34 - (nr))
DECL|macro|SMSC47M1_REG_PPIN
mdefine_line|#define SMSC47M1_REG_PPIN(nr)&t;&t;(0x36 - (nr))
DECL|macro|SMSC47M1_REG_PWM
mdefine_line|#define SMSC47M1_REG_PWM(nr)&t;&t;(0x56 + (nr))
DECL|macro|SMSC47M1_REG_FANDIV
mdefine_line|#define SMSC47M1_REG_FANDIV&t;&t;0x58
DECL|macro|SMSC47M1_REG_FAN
mdefine_line|#define SMSC47M1_REG_FAN(nr)&t;&t;(0x59 + (nr))
DECL|macro|SMSC47M1_REG_FAN_PRELOAD
mdefine_line|#define SMSC47M1_REG_FAN_PRELOAD(nr)&t;(0x5B + (nr))
DECL|macro|MIN_FROM_REG
mdefine_line|#define MIN_FROM_REG(reg,div)&t;&t;((reg)&gt;=192 ? 0 : &bslash;&n;&t;&t;&t;&t;&t; 983040/((192-(reg))*(div)))
DECL|macro|FAN_FROM_REG
mdefine_line|#define FAN_FROM_REG(reg,div,preload)&t;((reg)&lt;=(preload) || (reg)==255 ? 0 : &bslash;&n;&t;&t;&t;&t;&t; 983040/(((reg)-(preload))*(div)))
DECL|macro|DIV_FROM_REG
mdefine_line|#define DIV_FROM_REG(reg)&t;&t;(1 &lt;&lt; (reg))
DECL|macro|PWM_FROM_REG
mdefine_line|#define PWM_FROM_REG(reg)&t;&t;(((reg) &amp; 0x7E) &lt;&lt; 1)
DECL|macro|PWM_EN_FROM_REG
mdefine_line|#define PWM_EN_FROM_REG(reg)&t;&t;((~(reg)) &amp; 0x01)
DECL|macro|PWM_TO_REG
mdefine_line|#define PWM_TO_REG(reg)&t;&t;&t;(((reg) &gt;&gt; 1) &amp; 0x7E)
DECL|struct|smsc47m1_data
r_struct
id|smsc47m1_data
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
multiline_comment|/* In jiffies */
DECL|member|fan
id|u8
id|fan
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Register value */
DECL|member|fan_preload
id|u8
id|fan_preload
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Register value */
DECL|member|fan_div
id|u8
id|fan_div
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Register encoding, shifted right */
DECL|member|alarms
id|u8
id|alarms
suffix:semicolon
multiline_comment|/* Register encoding */
DECL|member|pwm
id|u8
id|pwm
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Register value (bit 7 is enable) */
)brace
suffix:semicolon
r_static
r_int
id|smsc47m1_attach_adapter
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
id|smsc47m1_find
c_func
(paren
r_int
op_star
id|address
)paren
suffix:semicolon
r_static
r_int
id|smsc47m1_detect
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
id|smsc47m1_detach_client
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
id|smsc47m1_read_value
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
r_void
id|smsc47m1_write_value
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
id|value
)paren
suffix:semicolon
r_static
r_struct
id|smsc47m1_data
op_star
id|smsc47m1_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|init
)paren
suffix:semicolon
DECL|variable|smsc47m1_driver
r_static
r_struct
id|i2c_driver
id|smsc47m1_driver
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
l_string|&quot;smsc47m1&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_SMSC47M1
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|smsc47m1_attach_adapter
comma
dot
id|detach_client
op_assign
id|smsc47m1_detach_client
comma
)brace
suffix:semicolon
multiline_comment|/* nr is 0 or 1 in the callback functions below */
DECL|function|get_fan
r_static
id|ssize_t
id|get_fan
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
id|smsc47m1_data
op_star
id|data
op_assign
id|smsc47m1_update_device
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* This chip (stupidly) stops monitoring fan speed if PWM is&n;&t;   enabled and duty cycle is 0%. This is fine if the monitoring&n;&t;   and control concern the same fan, but troublesome if they are&n;&t;   not (which could as well happen). */
r_int
id|rpm
op_assign
(paren
id|data-&gt;pwm
(braket
id|nr
)braket
op_amp
l_int|0x7F
)paren
op_eq
l_int|0x00
ques
c_cond
l_int|0
suffix:colon
id|FAN_FROM_REG
c_func
(paren
id|data-&gt;fan
(braket
id|nr
)braket
comma
id|DIV_FROM_REG
c_func
(paren
id|data-&gt;fan_div
(braket
id|nr
)braket
)paren
comma
id|data-&gt;fan_preload
(braket
id|nr
)braket
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
id|rpm
)paren
suffix:semicolon
)brace
DECL|function|get_fan_min
r_static
id|ssize_t
id|get_fan_min
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
id|smsc47m1_data
op_star
id|data
op_assign
id|smsc47m1_update_device
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_int
id|rpm
op_assign
id|MIN_FROM_REG
c_func
(paren
id|data-&gt;fan_preload
(braket
id|nr
)braket
comma
id|DIV_FROM_REG
c_func
(paren
id|data-&gt;fan_div
(braket
id|nr
)braket
)paren
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
id|rpm
)paren
suffix:semicolon
)brace
DECL|function|get_fan_div
r_static
id|ssize_t
id|get_fan_div
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
id|smsc47m1_data
op_star
id|data
op_assign
id|smsc47m1_update_device
c_func
(paren
id|dev
comma
l_int|0
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
id|DIV_FROM_REG
c_func
(paren
id|data-&gt;fan_div
(braket
id|nr
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_pwm
r_static
id|ssize_t
id|get_pwm
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
id|smsc47m1_data
op_star
id|data
op_assign
id|smsc47m1_update_device
c_func
(paren
id|dev
comma
l_int|0
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
id|PWM_FROM_REG
c_func
(paren
id|data-&gt;pwm
(braket
id|nr
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_pwm_en
r_static
id|ssize_t
id|get_pwm_en
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
id|smsc47m1_data
op_star
id|data
op_assign
id|smsc47m1_update_device
c_func
(paren
id|dev
comma
l_int|0
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
id|PWM_EN_FROM_REG
c_func
(paren
id|data-&gt;pwm
(braket
id|nr
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_alarms
r_static
id|ssize_t
id|get_alarms
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
id|smsc47m1_data
op_star
id|data
op_assign
id|smsc47m1_update_device
c_func
(paren
id|dev
comma
l_int|0
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
DECL|function|set_fan_min
r_static
id|ssize_t
id|set_fan_min
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
comma
r_int
id|nr
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
id|smsc47m1_data
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
id|rpmdiv
comma
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
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
id|rpmdiv
op_assign
id|val
op_star
id|DIV_FROM_REG
c_func
(paren
id|data-&gt;fan_div
(braket
id|nr
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|983040
OG
l_int|192
op_star
id|rpmdiv
op_logical_or
l_int|2
op_star
id|rpmdiv
OG
l_int|983040
)paren
(brace
id|up
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|data-&gt;fan_preload
(braket
id|nr
)braket
op_assign
l_int|192
op_minus
(paren
(paren
l_int|983040
op_plus
id|rpmdiv
op_div
l_int|2
)paren
op_div
id|rpmdiv
)paren
suffix:semicolon
id|smsc47m1_write_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_FAN_PRELOAD
c_func
(paren
id|nr
)paren
comma
id|data-&gt;fan_preload
(braket
id|nr
)braket
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
multiline_comment|/* Note: we save and restore the fan minimum here, because its value is&n;   determined in part by the fan clock divider.  This follows the principle&n;   of least suprise; the user doesn&squot;t expect the fan minimum to change just&n;   because the divider changed. */
DECL|function|set_fan_div
r_static
id|ssize_t
id|set_fan_div
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
comma
r_int
id|nr
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
id|smsc47m1_data
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
id|new_div
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
comma
id|tmp
suffix:semicolon
id|u8
id|old_div
op_assign
id|DIV_FROM_REG
c_func
(paren
id|data-&gt;fan_div
(braket
id|nr
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_div
op_eq
id|old_div
)paren
multiline_comment|/* No change */
r_return
id|count
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|new_div
)paren
(brace
r_case
l_int|1
suffix:colon
id|data-&gt;fan_div
(braket
id|nr
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|data-&gt;fan_div
(braket
id|nr
)braket
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|data-&gt;fan_div
(braket
id|nr
)braket
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|data-&gt;fan_div
(braket
id|nr
)braket
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|up
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|tmp
op_assign
id|smsc47m1_read_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_FANDIV
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|tmp
op_or_assign
(paren
id|data-&gt;fan_div
(braket
l_int|0
)braket
op_lshift
l_int|4
)paren
op_or
(paren
id|data-&gt;fan_div
(braket
l_int|1
)braket
op_lshift
l_int|6
)paren
suffix:semicolon
id|smsc47m1_write_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_FANDIV
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Preserve fan min */
id|tmp
op_assign
l_int|192
op_minus
(paren
id|old_div
op_star
(paren
l_int|192
op_minus
id|data-&gt;fan_preload
(braket
id|nr
)braket
)paren
op_plus
id|new_div
op_div
l_int|2
)paren
op_div
id|new_div
suffix:semicolon
id|data-&gt;fan_preload
(braket
id|nr
)braket
op_assign
id|SENSORS_LIMIT
c_func
(paren
id|tmp
comma
l_int|0
comma
l_int|191
)paren
suffix:semicolon
id|smsc47m1_write_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_FAN_PRELOAD
c_func
(paren
id|nr
)paren
comma
id|data-&gt;fan_preload
(braket
id|nr
)braket
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
DECL|function|set_pwm
r_static
id|ssize_t
id|set_pwm
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
comma
r_int
id|nr
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
id|smsc47m1_data
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
r_if
c_cond
(paren
id|val
template_param
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
id|data-&gt;pwm
(braket
id|nr
)braket
op_and_assign
l_int|0x81
suffix:semicolon
multiline_comment|/* Preserve additional bits */
id|data-&gt;pwm
(braket
id|nr
)braket
op_or_assign
id|PWM_TO_REG
c_func
(paren
id|val
)paren
suffix:semicolon
id|smsc47m1_write_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_PWM
c_func
(paren
id|nr
)paren
comma
id|data-&gt;pwm
(braket
id|nr
)braket
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
DECL|function|set_pwm_en
r_static
id|ssize_t
id|set_pwm_en
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
comma
r_int
id|nr
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
id|smsc47m1_data
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
r_if
c_cond
(paren
id|val
op_ne
l_int|0
op_logical_and
id|val
op_ne
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;update_lock
)paren
suffix:semicolon
id|data-&gt;pwm
(braket
id|nr
)braket
op_and_assign
l_int|0xFE
suffix:semicolon
multiline_comment|/* preserve the other bits */
id|data-&gt;pwm
(braket
id|nr
)braket
op_or_assign
op_logical_neg
id|val
suffix:semicolon
id|smsc47m1_write_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_PWM
c_func
(paren
id|nr
)paren
comma
id|data-&gt;pwm
(braket
id|nr
)braket
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
DECL|macro|fan_present
mdefine_line|#define fan_present(offset)&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t get_fan##offset (struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return get_fan(dev, buf, offset - 1);&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t get_fan##offset##_min (struct device *dev, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return get_fan_min(dev, buf, offset - 1);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t set_fan##offset##_min (struct device *dev,&t;&t;&bslash;&n;&t;&t;const char *buf, size_t count)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return set_fan_min(dev, buf, count, offset - 1);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t get_fan##offset##_div (struct device *dev, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return get_fan_div(dev, buf, offset - 1);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t set_fan##offset##_div (struct device *dev,&t;&t;&bslash;&n;&t;&t;const char *buf, size_t count)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return set_fan_div(dev, buf, count, offset - 1);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t get_pwm##offset (struct device *dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return get_pwm(dev, buf, offset - 1);&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t set_pwm##offset (struct device *dev,&t;&t;&t;&bslash;&n;&t;&t;const char *buf, size_t count)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return set_pwm(dev, buf, count, offset - 1);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t get_pwm##offset##_en (struct device *dev, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return get_pwm_en(dev, buf, offset - 1);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t set_pwm##offset##_en (struct device *dev,&t;&t;&bslash;&n;&t;&t;const char *buf, size_t count)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return set_pwm_en(dev, buf, count, offset - 1);&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(fan##offset##_input, S_IRUGO, get_fan##offset,&t;&bslash;&n;&t;&t;NULL);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(fan##offset##_min, S_IRUGO | S_IWUSR,&t;&t;&bslash;&n;&t;&t;get_fan##offset##_min, set_fan##offset##_min);&t;&t;&bslash;&n;static DEVICE_ATTR(fan##offset##_div, S_IRUGO | S_IWUSR,&t;&t;&bslash;&n;&t;&t;get_fan##offset##_div, set_fan##offset##_div);&t;&t;&bslash;&n;static DEVICE_ATTR(pwm##offset, S_IRUGO | S_IWUSR,&t;&t;&t;&bslash;&n;&t;&t;get_pwm##offset, set_pwm##offset);&t;&t;&t;&bslash;&n;static DEVICE_ATTR(pwm##offset##_enable, S_IRUGO | S_IWUSR,&t;&t;&bslash;&n;&t;&t;get_pwm##offset##_en, set_pwm##offset##_en);
id|fan_present
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|fan_present
c_func
(paren
l_int|2
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
id|get_alarms
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|smsc47m1_attach_adapter
r_static
r_int
id|smsc47m1_attach_adapter
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
id|smsc47m1_detect
)paren
suffix:semicolon
)brace
DECL|function|smsc47m1_find
r_static
r_int
id|smsc47m1_find
c_func
(paren
r_int
op_star
id|address
)paren
(brace
id|u8
id|val
suffix:semicolon
id|superio_enter
c_func
(paren
)paren
suffix:semicolon
id|val
op_assign
id|superio_inb
c_func
(paren
id|SUPERIO_REG_DEVID
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SMSC LPC47M10x/LPC47M13x (device id 0x59), LPC47M14x (device id&n;&t; * 0x5F) and LPC47B27x (device id 0x51) have fan control.&n;&t; * The LPC47M15x and LPC47M192 chips &quot;with hardware monitoring block&quot;&n;&t; * can do much more besides (device id 0x60, unsupported).&n;&t; */
r_if
c_cond
(paren
id|val
op_eq
l_int|0x51
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smsc47m1: Found SMSC47B27x&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|val
op_eq
l_int|0x59
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smsc47m1: Found SMSC47M10x/SMSC47M13x&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|val
op_eq
l_int|0x5F
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smsc47m1: Found SMSC47M14x&bslash;n&quot;
)paren
suffix:semicolon
r_else
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
id|superio_select
c_func
(paren
)paren
suffix:semicolon
op_star
id|address
op_assign
(paren
id|superio_inb
c_func
(paren
id|SUPERIO_REG_BASE
)paren
op_lshift
l_int|8
)paren
op_or
id|superio_inb
c_func
(paren
id|SUPERIO_REG_BASE
op_plus
l_int|1
)paren
suffix:semicolon
id|val
op_assign
id|superio_inb
c_func
(paren
id|SUPERIO_REG_ACT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|address
op_eq
l_int|0
op_logical_or
(paren
id|val
op_amp
l_int|0x01
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smsc47m1: Device is disabled, will not use&bslash;n&quot;
)paren
suffix:semicolon
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
id|superio_exit
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smsc47m1_detect
r_static
r_int
id|smsc47m1_detect
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
id|smsc47m1_data
op_star
id|data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|fan1
comma
id|fan2
comma
id|pwm1
comma
id|pwm2
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
id|address
comma
id|SMSC_EXTENT
comma
id|smsc47m1_driver.name
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
id|address
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
id|smsc47m1_data
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
id|smsc47m1_data
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
id|smsc47m1_driver
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
l_string|&quot;smsc47m1&quot;
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
multiline_comment|/* If no function is properly configured, there&squot;s no point in&n;&t;   actually registering the chip. */
id|fan1
op_assign
(paren
id|smsc47m1_read_value
c_func
(paren
id|new_client
comma
id|SMSC47M1_REG_TPIN
c_func
(paren
l_int|0
)paren
)paren
op_amp
l_int|0x05
)paren
op_eq
l_int|0x05
suffix:semicolon
id|fan2
op_assign
(paren
id|smsc47m1_read_value
c_func
(paren
id|new_client
comma
id|SMSC47M1_REG_TPIN
c_func
(paren
l_int|1
)paren
)paren
op_amp
l_int|0x05
)paren
op_eq
l_int|0x05
suffix:semicolon
id|pwm1
op_assign
(paren
id|smsc47m1_read_value
c_func
(paren
id|new_client
comma
id|SMSC47M1_REG_PPIN
c_func
(paren
l_int|0
)paren
)paren
op_amp
l_int|0x05
)paren
op_eq
l_int|0x04
suffix:semicolon
id|pwm2
op_assign
(paren
id|smsc47m1_read_value
c_func
(paren
id|new_client
comma
id|SMSC47M1_REG_PPIN
c_func
(paren
l_int|1
)paren
)paren
op_amp
l_int|0x05
)paren
op_eq
l_int|0x04
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fan1
op_logical_or
id|fan2
op_logical_or
id|pwm1
op_logical_or
id|pwm2
)paren
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
l_string|&quot;Device is not configured, will not use&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|error_free
suffix:semicolon
)brace
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
multiline_comment|/* Some values (fan min, clock dividers, pwm registers) may be&n;&t;   needed before any update is triggered, so we better read them&n;&t;   at least once here. We don&squot;t usually do it that way, but in&n;&t;   this particular case, manually reading 5 registers out of 8&n;&t;   doesn&squot;t make much sense and we&squot;re better using the existing&n;&t;   function. */
id|smsc47m1_update_device
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fan1
)paren
(brace
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
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_fan1_div
)paren
suffix:semicolon
)brace
r_else
id|dev_dbg
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
l_string|&quot;Fan 1 not enabled by hardware, &quot;
l_string|&quot;skipping&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fan2
)paren
(brace
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_fan2_input
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_fan2_min
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_fan2_div
)paren
suffix:semicolon
)brace
r_else
id|dev_dbg
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
l_string|&quot;Fan 2 not enabled by hardware, &quot;
l_string|&quot;skipping&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pwm1
)paren
(brace
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
)brace
r_else
id|dev_dbg
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
l_string|&quot;PWM 1 not enabled by hardware, &quot;
l_string|&quot;skipping&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pwm2
)paren
(brace
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_pwm2
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
op_amp
id|dev_attr_pwm2_enable
)paren
suffix:semicolon
)brace
r_else
id|dev_dbg
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
l_string|&quot;PWM 2 not enabled by hardware, &quot;
l_string|&quot;skipping&bslash;n&quot;
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
id|address
comma
id|SMSC_EXTENT
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|smsc47m1_detach_client
r_static
r_int
id|smsc47m1_detach_client
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
DECL|function|smsc47m1_read_value
r_static
r_int
id|smsc47m1_read_value
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
r_int
id|res
suffix:semicolon
id|down
c_func
(paren
op_amp
(paren
(paren
r_struct
id|smsc47m1_data
op_star
)paren
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
)paren
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|res
op_assign
id|inb_p
c_func
(paren
id|client-&gt;addr
op_plus
id|reg
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
(paren
r_struct
id|smsc47m1_data
op_star
)paren
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
)paren
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|smsc47m1_write_value
r_static
r_void
id|smsc47m1_write_value
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
id|value
)paren
(brace
id|down
c_func
(paren
op_amp
(paren
(paren
r_struct
id|smsc47m1_data
op_star
)paren
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
)paren
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|value
comma
id|client-&gt;addr
op_plus
id|reg
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
(paren
r_struct
id|smsc47m1_data
op_star
)paren
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
)paren
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
)brace
DECL|function|smsc47m1_update_device
r_static
r_struct
id|smsc47m1_data
op_star
id|smsc47m1_update_device
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|init
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
id|smsc47m1_data
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
id|init
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data-&gt;fan
(braket
id|i
)braket
op_assign
id|smsc47m1_read_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_FAN
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|data-&gt;fan_preload
(braket
id|i
)braket
op_assign
id|smsc47m1_read_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_FAN_PRELOAD
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|data-&gt;pwm
(braket
id|i
)braket
op_assign
id|smsc47m1_read_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_PWM
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
)brace
id|i
op_assign
id|smsc47m1_read_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_FANDIV
)paren
suffix:semicolon
id|data-&gt;fan_div
(braket
l_int|0
)braket
op_assign
(paren
id|i
op_rshift
l_int|4
)paren
op_amp
l_int|0x03
suffix:semicolon
id|data-&gt;fan_div
(braket
l_int|1
)braket
op_assign
id|i
op_rshift
l_int|6
suffix:semicolon
id|data-&gt;alarms
op_assign
id|smsc47m1_read_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_ALARM
)paren
op_rshift
l_int|6
suffix:semicolon
multiline_comment|/* Clear alarms if needed */
r_if
c_cond
(paren
id|data-&gt;alarms
)paren
id|smsc47m1_write_value
c_func
(paren
id|client
comma
id|SMSC47M1_REG_ALARM
comma
l_int|0xC0
)paren
suffix:semicolon
id|data-&gt;last_updated
op_assign
id|jiffies
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
DECL|function|sm_smsc47m1_init
r_static
r_int
id|__init
id|sm_smsc47m1_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smsc47m1_find
c_func
(paren
id|normal_isa
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|smsc47m1_driver
)paren
suffix:semicolon
)brace
DECL|function|sm_smsc47m1_exit
r_static
r_void
id|__exit
id|sm_smsc47m1_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|smsc47m1_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SMSC LPC47M1xx fan sensors driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sm_smsc47m1_init
id|module_init
c_func
(paren
id|sm_smsc47m1_init
)paren
suffix:semicolon
DECL|variable|sm_smsc47m1_exit
id|module_exit
c_func
(paren
id|sm_smsc47m1_exit
)paren
suffix:semicolon
eof
