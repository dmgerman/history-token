multiline_comment|/*&n; * Linux/PowerPC Real Time Clock Driver&n; *&n; * heavily based on:&n; * Linux/SPARC Real Time Clock Driver&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; *&n; * This is a little driver that lets a user-level program access&n; * the PPC clocks chip. It is no use unless you&n; * use the modified clock utility.&n; *&n; * Get the modified clock utility from:&n; *   ftp://vger.rutgers.edu/pub/linux/Sparc/userland/clock.c&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
DECL|variable|rtc_busy
r_static
r_int
id|rtc_busy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Retrieve the current date and time from the real time clock. */
DECL|function|get_rtc_time
r_void
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|t
)paren
(brace
r_int
r_int
id|nowtime
suffix:semicolon
id|nowtime
op_assign
(paren
id|ppc_md.get_rtc_time
)paren
(paren
)paren
suffix:semicolon
id|to_tm
c_func
(paren
id|nowtime
comma
id|t
)paren
suffix:semicolon
id|t-&gt;tm_year
op_sub_assign
l_int|1900
suffix:semicolon
id|t-&gt;tm_mon
op_sub_assign
l_int|1
suffix:semicolon
multiline_comment|/* Make sure userland has a 0-based month */
)brace
multiline_comment|/* Set the current date and time in the real time clock. */
DECL|function|set_rtc_time
r_void
id|set_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|t
)paren
(brace
r_int
r_int
id|nowtime
suffix:semicolon
id|nowtime
op_assign
id|mktime
c_func
(paren
id|t-&gt;tm_year
op_plus
l_int|1900
comma
id|t-&gt;tm_mon
op_plus
l_int|1
comma
id|t-&gt;tm_mday
comma
id|t-&gt;tm_hour
comma
id|t-&gt;tm_min
comma
id|t-&gt;tm_sec
)paren
suffix:semicolon
(paren
id|ppc_md.set_rtc_time
)paren
(paren
id|nowtime
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
r_struct
id|rtc_time
id|rtc_tm
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
r_if
c_cond
(paren
id|ppc_md.get_rtc_time
)paren
(brace
id|get_rtc_time
c_func
(paren
op_amp
id|rtc_tm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
op_amp
id|rtc_tm
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
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
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
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.set_rtc_time
)paren
(brace
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
id|set_rtc_time
c_func
(paren
op_amp
id|rtc_tm
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
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
id|rtc_busy
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|rtc_busy
op_assign
l_int|1
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|rtc_busy
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rtc_fops
r_static
r_struct
id|file_operations
id|rtc_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|no_llseek
comma
id|ioctl
suffix:colon
id|rtc_ioctl
comma
id|open
suffix:colon
id|rtc_open
comma
id|release
suffix:colon
id|rtc_release
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
id|error
suffix:semicolon
id|error
op_assign
id|misc_register
c_func
(paren
op_amp
id|rtc_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtc: unable to get misc minor&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtc_exit
r_static
r_void
id|__exit
id|rtc_exit
c_func
(paren
r_void
)paren
(brace
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
