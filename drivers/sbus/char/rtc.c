multiline_comment|/* $Id: rtc.c,v 1.28 2001/10/08 22:19:51 davem Exp $&n; *&n; * Linux/SPARC Real Time Clock Driver&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; *&n; * This is a little driver that lets a user-level program access&n; * the SPARC Mostek real time clock chip. It is no use unless you&n; * use the modified clock utility.&n; *&n; * Get the modified clock utility from:&n; *   ftp://vger.kernel.org/pub/linux/Sparc/userland/clock.c&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mostek.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
DECL|variable|rtc_busy
r_static
r_int
id|rtc_busy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Retrieve the current date and time from the real time clock. */
DECL|function|get_rtc_time
r_static
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
r_void
op_star
id|__iomem
id|regs
op_assign
id|mstk48t02_regs
suffix:semicolon
id|u8
id|tmp
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_or_assign
id|MSTK_CREG_READ
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|t-&gt;sec
op_assign
id|MSTK_REG_SEC
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;min
op_assign
id|MSTK_REG_MIN
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;hour
op_assign
id|MSTK_REG_HOUR
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;dow
op_assign
id|MSTK_REG_DOW
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;dom
op_assign
id|MSTK_REG_DOM
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;month
op_assign
id|MSTK_REG_MONTH
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;year
op_assign
id|MSTK_CVT_YEAR
c_func
(paren
id|MSTK_REG_YEAR
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|MSTK_CREG_READ
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the current date and time inthe real time clock. */
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
r_void
op_star
id|__iomem
id|regs
op_assign
id|mstk48t02_regs
suffix:semicolon
id|u8
id|tmp
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_or_assign
id|MSTK_CREG_WRITE
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|MSTK_SET_REG_SEC
c_func
(paren
id|regs
comma
id|t-&gt;sec
)paren
suffix:semicolon
id|MSTK_SET_REG_MIN
c_func
(paren
id|regs
comma
id|t-&gt;min
)paren
suffix:semicolon
id|MSTK_SET_REG_HOUR
c_func
(paren
id|regs
comma
id|t-&gt;hour
)paren
suffix:semicolon
id|MSTK_SET_REG_DOW
c_func
(paren
id|regs
comma
id|t-&gt;dow
)paren
suffix:semicolon
id|MSTK_SET_REG_DOM
c_func
(paren
id|regs
comma
id|t-&gt;dom
)paren
suffix:semicolon
id|MSTK_SET_REG_MONTH
c_func
(paren
id|regs
comma
id|t-&gt;month
)paren
suffix:semicolon
id|MSTK_SET_REG_YEAR
c_func
(paren
id|regs
comma
id|t-&gt;year
op_minus
id|MSTK_YEAR_ZERO
)paren
suffix:semicolon
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|MSTK_CREG_WRITE
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
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
r_void
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTCGET
suffix:colon
id|memset
c_func
(paren
op_amp
id|rtc_tm
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
suffix:semicolon
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
id|argp
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
r_case
id|RTCSET
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
id|copy_from_user
c_func
(paren
op_amp
id|rtc_tm
comma
id|argp
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
r_int
id|ret
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtc_busy
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
id|rtc_busy
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
r_return
id|ret
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
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
DECL|function|rtc_sun_init
r_static
r_int
id|__init
id|rtc_sun_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
multiline_comment|/* It is possible we are being driven by some other RTC chip&n;&t; * and thus another RTC driver is handling things.&n;&t; */
r_if
c_cond
(paren
id|mstk48t02_regs
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
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
l_string|&quot;rtc: unable to get misc minor for Mostek&bslash;n&quot;
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
DECL|function|rtc_sun_cleanup
r_static
r_void
id|__exit
id|rtc_sun_cleanup
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
DECL|variable|rtc_sun_init
id|module_init
c_func
(paren
id|rtc_sun_init
)paren
suffix:semicolon
DECL|variable|rtc_sun_cleanup
id|module_exit
c_func
(paren
id|rtc_sun_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
