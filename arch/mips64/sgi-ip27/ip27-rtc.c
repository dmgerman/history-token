multiline_comment|/*&n; *&t;Driver for the SGS-Thomson M48T35 Timekeeper RAM chip&n; *&n; *&t;Real Time Clock interface for Linux&t;&n; *&n; *&t;TODO: Implement periodic interrupts.&n; *&n; *&t;Copyright (C) 2000 Silicon Graphics, Inc.&n; *&t;Written by Ulf Carlsson (ulfc@engr.sgi.com)&n; *&n; *&t;Based on code written by Paul Gortmaker.&n; *&n; *&t;This driver allows use of the real time clock (built into&n; *&t;nearly all computers) from user space. It exports the /dev/rtc&n; *&t;interface supporting various ioctl() and also the /proc/rtc&n; *&t;pseudo-file for status information.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; */
DECL|macro|RTC_VERSION
mdefine_line|#define RTC_VERSION&t;&t;&quot;1.09b&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/m48t35.h&gt;
macro_line|#include &lt;asm/sn/ioc3.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn0/ip27.h&gt;
macro_line|#include &lt;asm/sn/sn0/hub.h&gt;
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
suffix:semicolon
r_static
r_int
id|rtc_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_static
r_void
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|rtc_tm
)paren
suffix:semicolon
DECL|variable|rtc_ready
r_static
id|atomic_t
id|rtc_ready
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
suffix:semicolon
DECL|variable|rtc_freq
r_static
r_int
r_int
id|rtc_freq
suffix:semicolon
multiline_comment|/* Current periodic IRQ rate&t;*/
DECL|variable|rtc
r_static
r_struct
id|m48t35_rtc
op_star
id|rtc
suffix:semicolon
multiline_comment|/*&n; *&t;If this driver ever becomes modularised, it will be really nice&n; *&t;to make the epoch retain its value across module reload...&n; */
DECL|variable|epoch
r_static
r_int
r_int
id|epoch
op_assign
l_int|1970
suffix:semicolon
multiline_comment|/* year corresponding to 0x00&t;*/
DECL|variable|days_in_mo
r_static
r_const
r_int
r_char
id|days_in_mo
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
r_struct
id|rtc_time
id|wtime
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_RD_TIME
suffix:colon
multiline_comment|/* Read the time/date from RTC&t;*/
(brace
id|get_rtc_time
c_func
(paren
op_amp
id|wtime
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|RTC_SET_TIME
suffix:colon
multiline_comment|/* Set the RTC */
(brace
r_struct
id|rtc_time
id|rtc_tm
suffix:semicolon
r_int
r_char
id|mon
comma
id|day
comma
id|hrs
comma
id|min
comma
id|sec
comma
id|leap_yr
suffix:semicolon
r_int
r_int
id|yrs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
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
id|rtc_tm
comma
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|yrs
op_assign
id|rtc_tm.tm_year
op_plus
l_int|1900
suffix:semicolon
id|mon
op_assign
id|rtc_tm.tm_mon
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* tm_mon starts at zero */
id|day
op_assign
id|rtc_tm.tm_mday
suffix:semicolon
id|hrs
op_assign
id|rtc_tm.tm_hour
suffix:semicolon
id|min
op_assign
id|rtc_tm.tm_min
suffix:semicolon
id|sec
op_assign
id|rtc_tm.tm_sec
suffix:semicolon
r_if
c_cond
(paren
id|yrs
OL
l_int|1970
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|leap_yr
op_assign
(paren
(paren
op_logical_neg
(paren
id|yrs
op_mod
l_int|4
)paren
op_logical_and
(paren
id|yrs
op_mod
l_int|100
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|yrs
op_mod
l_int|400
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mon
OG
l_int|12
)paren
op_logical_or
(paren
id|day
op_eq
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|day
OG
(paren
id|days_in_mo
(braket
id|mon
)braket
op_plus
(paren
(paren
id|mon
op_eq
l_int|2
)paren
op_logical_and
id|leap_yr
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
(paren
id|hrs
op_ge
l_int|24
)paren
op_logical_or
(paren
id|min
op_ge
l_int|60
)paren
op_logical_or
(paren
id|sec
op_ge
l_int|60
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|yrs
op_sub_assign
id|epoch
)paren
OG
l_int|255
)paren
multiline_comment|/* They are unsigned */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|yrs
OG
l_int|169
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|yrs
op_ge
l_int|100
)paren
id|yrs
op_sub_assign
l_int|100
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|hrs
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|day
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|yrs
)paren
suffix:semicolon
id|rtc-&gt;control
op_and_assign
op_complement
id|M48T35_RTC_SET
suffix:semicolon
id|rtc-&gt;year
op_assign
id|yrs
suffix:semicolon
id|rtc-&gt;month
op_assign
id|mon
suffix:semicolon
id|rtc-&gt;date
op_assign
id|day
suffix:semicolon
id|rtc-&gt;hour
op_assign
id|hrs
suffix:semicolon
id|rtc-&gt;min
op_assign
id|min
suffix:semicolon
id|rtc-&gt;sec
op_assign
id|sec
suffix:semicolon
id|rtc-&gt;control
op_and_assign
op_complement
id|M48T35_RTC_SET
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|wtime
comma
r_sizeof
id|wtime
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We enforce only one user at a time here with the open/close.&n; *&t;Also clear the previous interrupt data on an open, and clean&n; *&t;up things on a close.&n; */
DECL|function|rtc_open
r_static
r_int
id|rtc_open
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
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|rtc_ready
)paren
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|rtc_ready
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtc_release
r_static
r_int
id|rtc_release
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
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|rtc_ready
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The various file operations we support.&n; */
DECL|variable|rtc_fops
r_static
r_struct
id|file_operations
id|rtc_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|rtc_ioctl
comma
dot
id|open
op_assign
id|rtc_open
comma
dot
id|release
op_assign
id|rtc_release
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
id|RTC_MINOR
comma
l_string|&quot;rtc&quot;
comma
op_amp
id|rtc_fops
)brace
suffix:semicolon
DECL|function|rtc_init
r_static
r_int
id|__init
id|rtc_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|nasid_t
id|nid
suffix:semicolon
id|nid
op_assign
id|get_nasid
c_func
(paren
)paren
suffix:semicolon
id|rtc
op_assign
(paren
r_struct
id|m48t35_rtc
op_star
)paren
id|KL_CONFIG_CH_CONS_INFO
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|memory_base
op_plus
id|IOC3_BYTEBUS_DEV0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Real Time Clock Driver v%s&bslash;n&quot;
comma
id|RTC_VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|rtc_dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtc: cannot register misc device.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_proc_read_entry
(paren
l_string|&quot;rtc&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|rtc_read_proc
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtc: cannot create /proc/rtc.&bslash;n&quot;
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|rtc_dev
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|rtc_freq
op_assign
l_int|1024
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtc_exit
r_static
r_void
id|__exit
id|rtc_exit
(paren
r_void
)paren
(brace
multiline_comment|/* interrupts and timer disabled at this point by rtc_release */
id|remove_proc_entry
(paren
l_string|&quot;rtc&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|rtc_dev
)paren
suffix:semicolon
)brace
DECL|variable|rtc_init
id|module_init
c_func
(paren
id|rtc_init
)paren
suffix:semicolon
DECL|variable|rtc_exit
id|module_exit
c_func
(paren
id|rtc_exit
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Info exported via &quot;/proc/rtc&quot;.&n; */
DECL|function|rtc_get_status
r_static
r_int
id|rtc_get_status
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_struct
id|rtc_time
id|tm
suffix:semicolon
multiline_comment|/*&n;&t; * Just emulate the standard /proc/rtc&n;&t; */
id|p
op_assign
id|buf
suffix:semicolon
id|get_rtc_time
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * There is no way to tell if the luser has the RTC set for local&n;&t; * time or for Universal Standard Time (GMT). Probably local though.&n;&t; */
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;rtc_time&bslash;t: %02d:%02d:%02d&bslash;n&quot;
l_string|&quot;rtc_date&bslash;t: %04d-%02d-%02d&bslash;n&quot;
l_string|&quot;rtc_epoch&bslash;t: %04lu&bslash;n&quot;
l_string|&quot;24hr&bslash;t&bslash;t: yes&bslash;n&quot;
comma
id|tm.tm_hour
comma
id|tm.tm_min
comma
id|tm.tm_sec
comma
id|tm.tm_year
op_plus
l_int|1900
comma
id|tm.tm_mon
op_plus
l_int|1
comma
id|tm.tm_mday
comma
id|epoch
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|rtc_read_proc
r_static
r_int
id|rtc_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|rtc_get_status
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|get_rtc_time
r_static
r_void
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|rtc_tm
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * Do we need to wait for the last update to finish?&n;&t; */
multiline_comment|/*&n;&t; * Only the values that we read from the RTC are set. We leave&n;&t; * tm_wday, tm_yday and tm_isdst untouched. Even though the&n;&t; * RTC has RTC_DAY_OF_WEEK, we ignore it, as it is only updated&n;&t; * by the RTC when initially set to a non-zero value.&n;&t; */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|rtc-&gt;control
op_or_assign
id|M48T35_RTC_READ
suffix:semicolon
id|rtc_tm-&gt;tm_sec
op_assign
id|rtc-&gt;sec
suffix:semicolon
id|rtc_tm-&gt;tm_min
op_assign
id|rtc-&gt;min
suffix:semicolon
id|rtc_tm-&gt;tm_hour
op_assign
id|rtc-&gt;hour
suffix:semicolon
id|rtc_tm-&gt;tm_mday
op_assign
id|rtc-&gt;date
suffix:semicolon
id|rtc_tm-&gt;tm_mon
op_assign
id|rtc-&gt;month
suffix:semicolon
id|rtc_tm-&gt;tm_year
op_assign
id|rtc-&gt;year
suffix:semicolon
id|rtc-&gt;control
op_and_assign
op_complement
id|M48T35_RTC_READ
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_mday
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_year
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Account for differences between how the RTC uses the values&n;&t; * and how they are defined in a struct rtc_time;&n;&t; */
r_if
c_cond
(paren
(paren
id|rtc_tm-&gt;tm_year
op_add_assign
(paren
id|epoch
op_minus
l_int|1900
)paren
)paren
op_le
l_int|69
)paren
id|rtc_tm-&gt;tm_year
op_add_assign
l_int|100
suffix:semicolon
id|rtc_tm-&gt;tm_mon
op_decrement
suffix:semicolon
)brace
eof
