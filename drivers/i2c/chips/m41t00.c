multiline_comment|/*&n; * drivers/i2c/chips/m41t00.c&n; *&n; * I2C client/driver for the ST M41T00 Real-Time Clock chip.&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2005 (c) MontaVista Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * This i2c client/driver wedges between the drivers/char/genrtc.c RTC&n; * interface and the SMBus interface of the i2c subsystem.&n; * It would be more efficient to use i2c msgs/i2c_transfer directly but, as&n; * recommened in .../Documentation/i2c/writing-clients section&n; * &quot;Sending and receiving&quot;, using SMBus level communication is preferred.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
DECL|macro|M41T00_DRV_NAME
mdefine_line|#define&t;M41T00_DRV_NAME&t;&t;&quot;m41t00&quot;
r_static
id|DECLARE_MUTEX
c_func
(paren
id|m41t00_mutex
)paren
suffix:semicolon
DECL|variable|m41t00_driver
r_static
r_struct
id|i2c_driver
id|m41t00_driver
suffix:semicolon
DECL|variable|save_client
r_static
r_struct
id|i2c_client
op_star
id|save_client
suffix:semicolon
DECL|variable|ignore
r_static
r_int
r_int
id|ignore
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|normal_addr
r_static
r_int
r_int
id|normal_addr
(braket
)braket
op_assign
(brace
l_int|0x68
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|addr_data
r_static
r_struct
id|i2c_client_address_data
id|addr_data
op_assign
(brace
dot
id|normal_i2c
op_assign
id|normal_addr
comma
dot
id|normal_i2c_range
op_assign
id|ignore
comma
dot
id|probe
op_assign
id|ignore
comma
dot
id|probe_range
op_assign
id|ignore
comma
dot
id|ignore
op_assign
id|ignore
comma
dot
id|ignore_range
op_assign
id|ignore
comma
dot
id|force
op_assign
id|ignore
comma
)brace
suffix:semicolon
id|ulong
DECL|function|m41t00_get_rtc_time
id|m41t00_get_rtc_time
c_func
(paren
r_void
)paren
(brace
id|s32
id|sec
comma
id|min
comma
id|hour
comma
id|day
comma
id|mon
comma
id|year
suffix:semicolon
id|s32
id|sec1
comma
id|min1
comma
id|hour1
comma
id|day1
comma
id|mon1
comma
id|year1
suffix:semicolon
id|ulong
id|limit
op_assign
l_int|10
suffix:semicolon
id|sec
op_assign
id|min
op_assign
id|hour
op_assign
id|day
op_assign
id|mon
op_assign
id|year
op_assign
l_int|0
suffix:semicolon
id|sec1
op_assign
id|min1
op_assign
id|hour1
op_assign
id|day1
op_assign
id|mon1
op_assign
id|year1
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|m41t00_mutex
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
(paren
id|sec
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|save_client
comma
l_int|0
)paren
)paren
op_ge
l_int|0
)paren
op_logical_and
(paren
(paren
id|min
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|save_client
comma
l_int|1
)paren
)paren
op_ge
l_int|0
)paren
op_logical_and
(paren
(paren
id|hour
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|save_client
comma
l_int|2
)paren
)paren
op_ge
l_int|0
)paren
op_logical_and
(paren
(paren
id|day
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|save_client
comma
l_int|4
)paren
)paren
op_ge
l_int|0
)paren
op_logical_and
(paren
(paren
id|mon
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|save_client
comma
l_int|5
)paren
)paren
op_ge
l_int|0
)paren
op_logical_and
(paren
(paren
id|year
op_assign
id|i2c_smbus_read_byte_data
c_func
(paren
id|save_client
comma
l_int|6
)paren
)paren
op_ge
l_int|0
)paren
op_logical_and
(paren
(paren
id|sec
op_eq
id|sec1
)paren
op_logical_and
(paren
id|min
op_eq
id|min1
)paren
op_logical_and
(paren
id|hour
op_eq
id|hour1
)paren
op_logical_and
(paren
id|day
op_eq
id|day1
)paren
op_logical_and
(paren
id|mon
op_eq
id|mon1
)paren
op_logical_and
(paren
id|year
op_eq
id|year1
)paren
)paren
)paren
r_break
suffix:semicolon
id|sec1
op_assign
id|sec
suffix:semicolon
id|min1
op_assign
id|min
suffix:semicolon
id|hour1
op_assign
id|hour
suffix:semicolon
id|day1
op_assign
id|day
suffix:semicolon
id|mon1
op_assign
id|mon
suffix:semicolon
id|year1
op_assign
id|year
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|limit
OG
l_int|0
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|m41t00_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|limit
op_eq
l_int|0
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|save_client-&gt;dev
comma
l_string|&quot;m41t00: can&squot;t read rtc chip&bslash;n&quot;
)paren
suffix:semicolon
id|sec
op_assign
id|min
op_assign
id|hour
op_assign
id|day
op_assign
id|mon
op_assign
id|year
op_assign
l_int|0
suffix:semicolon
)brace
id|sec
op_and_assign
l_int|0x7f
suffix:semicolon
id|min
op_and_assign
l_int|0x7f
suffix:semicolon
id|hour
op_and_assign
l_int|0x3f
suffix:semicolon
id|day
op_and_assign
l_int|0x3f
suffix:semicolon
id|mon
op_and_assign
l_int|0x1f
suffix:semicolon
id|year
op_and_assign
l_int|0xff
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|year
)paren
suffix:semicolon
id|year
op_add_assign
l_int|1900
suffix:semicolon
r_if
c_cond
(paren
id|year
OL
l_int|1970
)paren
id|year
op_add_assign
l_int|100
suffix:semicolon
r_return
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|m41t00_set_tlet
id|m41t00_set_tlet
c_func
(paren
id|ulong
id|arg
)paren
(brace
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|ulong
id|nowtime
op_assign
op_star
(paren
id|ulong
op_star
)paren
id|arg
suffix:semicolon
id|to_tm
c_func
(paren
id|nowtime
comma
op_amp
id|tm
)paren
suffix:semicolon
id|tm.tm_year
op_assign
(paren
id|tm.tm_year
op_minus
l_int|1900
)paren
op_mod
l_int|100
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mon
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mday
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_year
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|m41t00_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|save_client
comma
l_int|0
comma
id|tm.tm_sec
op_amp
l_int|0x7f
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|save_client
comma
l_int|1
comma
id|tm.tm_min
op_amp
l_int|0x7f
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|save_client
comma
l_int|2
comma
id|tm.tm_hour
op_amp
l_int|0x7f
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|save_client
comma
l_int|4
comma
id|tm.tm_mday
op_amp
l_int|0x7f
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|save_client
comma
l_int|5
comma
id|tm.tm_mon
op_amp
l_int|0x7f
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|save_client
comma
l_int|6
comma
id|tm.tm_year
op_amp
l_int|0x7f
)paren
OL
l_int|0
)paren
)paren
id|dev_warn
c_func
(paren
op_amp
id|save_client-&gt;dev
comma
l_string|&quot;m41t00: can&squot;t write to rtc chip&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|m41t00_mutex
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|new_time
id|ulong
id|new_time
suffix:semicolon
id|DECLARE_TASKLET_DISABLED
c_func
(paren
id|m41t00_tasklet
comma
id|m41t00_set_tlet
comma
(paren
id|ulong
)paren
op_amp
id|new_time
)paren
suffix:semicolon
r_int
DECL|function|m41t00_set_rtc_time
id|m41t00_set_rtc_time
c_func
(paren
id|ulong
id|nowtime
)paren
(brace
id|new_time
op_assign
id|nowtime
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|tasklet_schedule
c_func
(paren
op_amp
id|m41t00_tasklet
)paren
suffix:semicolon
r_else
id|m41t00_set_tlet
c_func
(paren
(paren
id|ulong
)paren
op_amp
id|new_time
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Driver Interface&n; *&n; *****************************************************************************&n; */
r_static
r_int
DECL|function|m41t00_probe
id|m41t00_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
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
id|client
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_client
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|client
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|client
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|client-&gt;name
comma
id|M41T00_DRV_NAME
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
id|client-&gt;id
op_assign
id|m41t00_driver.id
suffix:semicolon
id|client-&gt;flags
op_assign
id|I2C_DF_NOTIFY
suffix:semicolon
id|client-&gt;addr
op_assign
id|addr
suffix:semicolon
id|client-&gt;adapter
op_assign
id|adap
suffix:semicolon
id|client-&gt;driver
op_assign
op_amp
id|m41t00_driver
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i2c_attach_client
c_func
(paren
id|client
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|save_client
op_assign
id|client
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|m41t00_attach
id|m41t00_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|m41t00_probe
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|m41t00_detach
id|m41t00_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i2c_detach_client
c_func
(paren
id|client
)paren
)paren
op_eq
l_int|0
)paren
(brace
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
id|tasklet_kill
c_func
(paren
op_amp
id|m41t00_tasklet
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|m41t00_driver
r_static
r_struct
id|i2c_driver
id|m41t00_driver
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
id|M41T00_DRV_NAME
comma
dot
id|id
op_assign
id|I2C_DRIVERID_STM41T00
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|m41t00_attach
comma
dot
id|detach_client
op_assign
id|m41t00_detach
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|m41t00_init
id|m41t00_init
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
id|m41t00_driver
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|m41t00_exit
id|m41t00_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|m41t00_driver
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|m41t00_init
id|module_init
c_func
(paren
id|m41t00_init
)paren
suffix:semicolon
DECL|variable|m41t00_exit
id|module_exit
c_func
(paren
id|m41t00_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mark A. Greer &lt;mgreer@mvista.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ST Microelectronics M41T00 RTC I2C Client Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
