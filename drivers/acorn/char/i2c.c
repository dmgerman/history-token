multiline_comment|/*&n; *  linux/drivers/acorn/char/i2c.c&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  ARM IOC/IOMD i2c driver.&n; *&n; *  On Acorn machines, the following i2c devices are on the bus:&n; *&t;- PCF8583 real time clock &amp; static RAM&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware/ioc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;pcf8583.h&quot;
r_extern
r_int
(paren
op_star
id|set_rtc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|rtc_client
r_static
r_struct
id|i2c_client
op_star
id|rtc_client
suffix:semicolon
DECL|variable|days_in_mon
r_static
r_const
r_int
r_char
id|days_in_mon
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|28
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
DECL|variable|rtc_epoch
r_static
r_int
r_int
id|rtc_epoch
op_assign
l_int|1900
suffix:semicolon
DECL|macro|CMOS_CHECKSUM
mdefine_line|#define CMOS_CHECKSUM&t;(63)
DECL|macro|CMOS_YEAR
mdefine_line|#define CMOS_YEAR&t;(64 + 128)
DECL|function|rtc_command
r_static
r_inline
r_int
id|rtc_command
c_func
(paren
r_int
id|cmd
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|rtc_client
)paren
id|ret
op_assign
id|rtc_client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|rtc_client
comma
id|cmd
comma
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the current RTC time and date, and update xtime.&n; */
DECL|function|get_rtc_time
r_static
r_void
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_tm
op_star
id|rtctm
comma
r_int
r_int
op_star
id|year
)paren
(brace
r_int
r_char
id|ctrl
comma
id|yr
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|mem
id|rtcmem
op_assign
(brace
id|CMOS_YEAR
comma
r_sizeof
(paren
id|yr
)paren
comma
id|yr
)brace
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the RTC is running.&n;&t; */
id|rtc_command
c_func
(paren
id|RTC_GETCTRL
comma
op_amp
id|ctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctrl
op_amp
l_int|0xc0
)paren
(brace
r_int
r_char
id|new_ctrl
suffix:semicolon
id|new_ctrl
op_assign
id|ctrl
op_amp
op_complement
l_int|0xc0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RTC: resetting control %02X -&gt; %02X&bslash;n&quot;
comma
id|ctrl
comma
id|new_ctrl
)paren
suffix:semicolon
id|rtc_command
c_func
(paren
id|RTC_SETCTRL
comma
op_amp
id|new_ctrl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Acorn machines store the year in&n;&t; * the static RAM at location 192.&n;&t; */
r_if
c_cond
(paren
id|rtc_command
c_func
(paren
id|MEM_READ
comma
op_amp
id|rtcmem
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rtc_command
c_func
(paren
id|RTC_GETDATETIME
comma
id|rtctm
)paren
)paren
r_return
suffix:semicolon
op_star
id|year
op_assign
id|yr
(braket
l_int|1
)braket
op_star
l_int|100
op_plus
id|yr
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|set_rtc_time
r_static
r_int
id|set_rtc_time
c_func
(paren
r_struct
id|rtc_tm
op_star
id|rtctm
comma
r_int
r_int
id|year
)paren
(brace
r_int
r_char
id|yr
(braket
l_int|2
)braket
comma
id|leap
comma
id|chk
suffix:semicolon
r_struct
id|mem
id|cmos_year
op_assign
(brace
id|CMOS_YEAR
comma
r_sizeof
(paren
id|yr
)paren
comma
id|yr
)brace
suffix:semicolon
r_struct
id|mem
id|cmos_check
op_assign
(brace
id|CMOS_CHECKSUM
comma
l_int|1
comma
op_amp
id|chk
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|leap
op_assign
(paren
op_logical_neg
(paren
id|year
op_mod
l_int|4
)paren
op_logical_and
(paren
id|year
op_mod
l_int|100
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|year
op_mod
l_int|400
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtctm-&gt;mon
OG
l_int|12
op_logical_or
id|rtctm-&gt;mday
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rtctm-&gt;mday
OG
(paren
id|days_in_mon
(braket
id|rtctm-&gt;mon
)braket
op_plus
(paren
id|rtctm-&gt;mon
op_eq
l_int|2
op_logical_and
id|leap
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rtctm-&gt;hours
op_ge
l_int|24
op_logical_or
id|rtctm-&gt;mins
op_ge
l_int|60
op_logical_or
id|rtctm-&gt;secs
op_ge
l_int|60
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ret
op_assign
id|rtc_command
c_func
(paren
id|RTC_SETDATETIME
comma
id|rtctm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|rtc_command
c_func
(paren
id|MEM_READ
comma
op_amp
id|cmos_check
)paren
suffix:semicolon
id|rtc_command
c_func
(paren
id|MEM_READ
comma
op_amp
id|cmos_year
)paren
suffix:semicolon
id|chk
op_sub_assign
id|yr
(braket
l_int|1
)braket
op_plus
id|yr
(braket
l_int|0
)braket
suffix:semicolon
id|yr
(braket
l_int|1
)braket
op_assign
id|year
op_div
l_int|100
suffix:semicolon
id|yr
(braket
l_int|0
)braket
op_assign
id|year
op_mod
l_int|100
suffix:semicolon
id|chk
op_add_assign
id|yr
(braket
l_int|1
)braket
op_plus
id|yr
(braket
l_int|0
)braket
suffix:semicolon
id|rtc_command
c_func
(paren
id|MEM_WRITE
comma
op_amp
id|cmos_year
)paren
suffix:semicolon
id|rtc_command
c_func
(paren
id|MEM_WRITE
comma
op_amp
id|cmos_check
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the RTC time only.  Note that&n; * we do not touch the date.&n; */
DECL|function|k_set_rtc_time
r_static
r_int
id|k_set_rtc_time
c_func
(paren
r_void
)paren
(brace
r_struct
id|rtc_tm
id|new_rtctm
comma
id|old_rtctm
suffix:semicolon
r_int
r_int
id|nowtime
op_assign
id|xtime.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|rtc_command
c_func
(paren
id|RTC_GETDATETIME
comma
op_amp
id|old_rtctm
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|new_rtctm.cs
op_assign
id|xtime.tv_usec
op_div
l_int|10000
suffix:semicolon
id|new_rtctm.secs
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|nowtime
op_div_assign
l_int|60
suffix:semicolon
id|new_rtctm.mins
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|nowtime
op_div_assign
l_int|60
suffix:semicolon
id|new_rtctm.hours
op_assign
id|nowtime
op_mod
l_int|24
suffix:semicolon
multiline_comment|/*&n;&t; * avoid writing when we&squot;re going to change the day&n;&t; * of the month.  We will retry in the next minute.&n;&t; * This basically means that if the RTC must not drift&n;&t; * by more than 1 minute in 11 minutes.&n;&t; *&n;&t; * [ rtc: 1/1/2000 23:58:00, real 2/1/2000 00:01:00,&n;&t; *   rtc gets set to 1/1/2000 00:01:00 ]&n;&t; */
r_if
c_cond
(paren
(paren
id|old_rtctm.hours
op_eq
l_int|23
op_logical_and
id|old_rtctm.mins
op_eq
l_int|59
)paren
op_logical_or
(paren
id|new_rtctm.hours
op_eq
l_int|23
op_logical_and
id|new_rtctm.mins
op_eq
l_int|59
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|rtc_command
c_func
(paren
id|RTC_SETTIME
comma
op_amp
id|new_rtctm
)paren
suffix:semicolon
)brace
DECL|function|rtc_ioctl
r_static
r_int
id|rtc_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|year
suffix:semicolon
r_struct
id|rtc_time
id|rtctm
suffix:semicolon
r_struct
id|rtc_tm
id|rtc_raw
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_ALM_READ
suffix:colon
r_case
id|RTC_ALM_SET
suffix:colon
r_break
suffix:semicolon
r_case
id|RTC_RD_TIME
suffix:colon
id|get_rtc_time
c_func
(paren
op_amp
id|rtc_raw
comma
op_amp
id|year
)paren
suffix:semicolon
id|rtctm.tm_sec
op_assign
id|rtc_raw.secs
suffix:semicolon
id|rtctm.tm_min
op_assign
id|rtc_raw.mins
suffix:semicolon
id|rtctm.tm_hour
op_assign
id|rtc_raw.hours
suffix:semicolon
id|rtctm.tm_mday
op_assign
id|rtc_raw.mday
suffix:semicolon
id|rtctm.tm_mon
op_assign
id|rtc_raw.mon
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* month starts at 0 */
id|rtctm.tm_year
op_assign
id|year
op_minus
l_int|1900
suffix:semicolon
multiline_comment|/* starts at 1900 */
r_return
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|rtctm
comma
r_sizeof
(paren
id|rtctm
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|RTC_SET_TIME
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rtctm
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|rtctm
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|rtc_raw.secs
op_assign
id|rtctm.tm_sec
suffix:semicolon
id|rtc_raw.mins
op_assign
id|rtctm.tm_min
suffix:semicolon
id|rtc_raw.hours
op_assign
id|rtctm.tm_hour
suffix:semicolon
id|rtc_raw.mday
op_assign
id|rtctm.tm_mday
suffix:semicolon
id|rtc_raw.mon
op_assign
id|rtctm.tm_mon
op_plus
l_int|1
suffix:semicolon
id|rtc_raw.year_off
op_assign
l_int|2
suffix:semicolon
id|year
op_assign
id|rtctm.tm_year
op_plus
l_int|1900
suffix:semicolon
r_return
id|set_rtc_time
c_func
(paren
op_amp
id|rtc_raw
comma
id|year
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RTC_EPOCH_READ
suffix:colon
r_return
id|put_user
c_func
(paren
id|rtc_epoch
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|rtc_fops
r_static
r_struct
id|file_operations
id|rtc_fops
op_assign
(brace
dot
id|ioctl
op_assign
id|rtc_ioctl
comma
)brace
suffix:semicolon
DECL|variable|rtc_dev
r_static
r_struct
id|miscdevice
id|rtc_dev
op_assign
(brace
dot
id|minor
op_assign
id|RTC_MINOR
comma
dot
id|name
op_assign
l_string|&quot;rtc&quot;
comma
dot
id|fops
op_assign
op_amp
id|rtc_fops
comma
)brace
suffix:semicolon
multiline_comment|/* IOC / IOMD i2c driver */
DECL|macro|FORCE_ONES
mdefine_line|#define FORCE_ONES&t;0xdc
DECL|macro|SCL
mdefine_line|#define SCL&t;&t;0x02
DECL|macro|SDA
mdefine_line|#define SDA&t;&t;0x01
multiline_comment|/*&n; * We must preserve all non-i2c output bits in IOC_CONTROL.&n; * Note also that we need to preserve the value of SCL and&n; * SDA outputs as well (which may be different from the&n; * values read back from IOC_CONTROL).&n; */
DECL|variable|force_ones
r_static
id|u_int
id|force_ones
suffix:semicolon
DECL|function|ioc_setscl
r_static
r_void
id|ioc_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
id|u_int
id|ioc_control
op_assign
id|ioc_readb
c_func
(paren
id|IOC_CONTROL
)paren
op_amp
op_complement
(paren
id|SCL
op_or
id|SDA
)paren
suffix:semicolon
id|u_int
id|ones
op_assign
id|force_ones
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
id|ones
op_or_assign
id|SCL
suffix:semicolon
r_else
id|ones
op_and_assign
op_complement
id|SCL
suffix:semicolon
id|force_ones
op_assign
id|ones
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|ioc_control
op_or
id|ones
comma
id|IOC_CONTROL
)paren
suffix:semicolon
)brace
DECL|function|ioc_setsda
r_static
r_void
id|ioc_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
id|u_int
id|ioc_control
op_assign
id|ioc_readb
c_func
(paren
id|IOC_CONTROL
)paren
op_amp
op_complement
(paren
id|SCL
op_or
id|SDA
)paren
suffix:semicolon
id|u_int
id|ones
op_assign
id|force_ones
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
id|ones
op_or_assign
id|SDA
suffix:semicolon
r_else
id|ones
op_and_assign
op_complement
id|SDA
suffix:semicolon
id|force_ones
op_assign
id|ones
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|ioc_control
op_or
id|ones
comma
id|IOC_CONTROL
)paren
suffix:semicolon
)brace
DECL|function|ioc_getscl
r_static
r_int
id|ioc_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|ioc_readb
c_func
(paren
id|IOC_CONTROL
)paren
op_amp
id|SCL
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|ioc_getsda
r_static
r_int
id|ioc_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|ioc_readb
c_func
(paren
id|IOC_CONTROL
)paren
op_amp
id|SDA
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|variable|ioc_data
r_static
r_struct
id|i2c_algo_bit_data
id|ioc_data
op_assign
(brace
dot
id|setsda
op_assign
id|ioc_setsda
comma
dot
id|setscl
op_assign
id|ioc_setscl
comma
dot
id|getsda
op_assign
id|ioc_getsda
comma
dot
id|getscl
op_assign
id|ioc_getscl
comma
dot
id|udelay
op_assign
l_int|80
comma
dot
id|mdelay
op_assign
l_int|80
comma
dot
id|timeout
op_assign
l_int|100
)brace
suffix:semicolon
DECL|function|ioc_client_reg
r_static
r_int
id|ioc_client_reg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_if
c_cond
(paren
id|client-&gt;id
op_eq
id|I2C_DRIVERID_PCF8583
op_logical_and
id|client-&gt;addr
op_eq
l_int|0x50
)paren
(brace
r_struct
id|rtc_tm
id|rtctm
suffix:semicolon
r_int
r_int
id|year
suffix:semicolon
id|rtc_client
op_assign
id|client
suffix:semicolon
id|get_rtc_time
c_func
(paren
op_amp
id|rtctm
comma
op_amp
id|year
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
id|rtctm.cs
op_star
l_int|10000
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|year
comma
id|rtctm.mon
comma
id|rtctm.mday
comma
id|rtctm.hours
comma
id|rtctm.mins
comma
id|rtctm.secs
)paren
suffix:semicolon
id|set_rtc
op_assign
id|k_set_rtc_time
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ioc_client_unreg
r_static
r_int
id|ioc_client_unreg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_if
c_cond
(paren
id|client
op_eq
id|rtc_client
)paren
(brace
id|set_rtc
op_assign
l_int|NULL
suffix:semicolon
id|rtc_client
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ioc_ops
r_static
r_struct
id|i2c_adapter
id|ioc_ops
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IOC/IOMD&quot;
comma
dot
id|id
op_assign
id|I2C_HW_B_IOC
comma
dot
id|algo_data
op_assign
op_amp
id|ioc_data
comma
dot
id|client_register
op_assign
id|ioc_client_reg
comma
dot
id|client_unregister
op_assign
id|ioc_client_unreg
)brace
suffix:semicolon
DECL|function|i2c_ioc_init
r_static
r_int
id|__init
id|i2c_ioc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|force_ones
op_assign
id|FORCE_ONES
op_or
id|SCL
op_or
id|SDA
suffix:semicolon
id|ret
op_assign
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|ioc_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
id|misc_register
c_func
(paren
op_amp
id|rtc_dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|i2c_ioc_init
id|__initcall
c_func
(paren
id|i2c_ioc_init
)paren
suffix:semicolon
eof
