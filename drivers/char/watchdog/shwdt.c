multiline_comment|/*&n; * drivers/char/shwdt.c&n; *&n; * Watchdog driver for integrated watchdog in the SuperH processors.&n; *&n; * Copyright (C) 2001, 2002, 2003 Paul Mundt &lt;lethal@linux-sh.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * 14-Dec-2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *     Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT&n; *&n; * 19-Apr-2002 Rob Radez &lt;rob@osinvestor.com&gt;&n; *     Added expect close support, made emulated timeout runtime changeable&n; *     general cleanups, add some ioctls&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/watchdog.h&gt;
multiline_comment|/*&n; * Default clock division ratio is 5.25 msecs. For an additional table of&n; * values, consult the asm-sh/watchdog.h. Overload this at module load&n; * time. &n; *&n; * In order for this to work reliably we need to have HZ set to 1000 or&n; * something quite higher than 100 (or we need a proper high-res timer&n; * implementation that will deal with this properly), otherwise the 10ms&n; * resolution of a jiffy is enough to trigger the overflow. For things like&n; * the SH-4 and SH-5, this isn&squot;t necessarily that big of a problem, though&n; * for the SH-2 and SH-3, this isn&squot;t recommended unless the WDT is absolutely&n; * necssary.&n; *&n; * As a result of this timing problem, the only modes that are particularly&n; * feasible are the 4096 and the 2048 divisors, which yeild 5.25 and 2.62ms&n; * overflow periods respectively.&n; *&n; * Also, since we can&squot;t really expect userspace to be responsive enough&n; * before the overflow happens, we maintain two seperate timers .. One in&n; * the kernel for clearing out WOVF every 2ms or so (again, this depends on&n; * HZ == 1000), and another for monitoring userspace writes to the WDT device.&n; *&n; * As such, we currently use a configurable heartbeat interval which defaults&n; * to 30s. In this case, the userspace daemon is only responsible for periodic&n; * writes to the device before the next heartbeat is scheduled. If the daemon&n; * misses its deadline, the kernel timer will allow the WDT to overflow.&n; */
DECL|variable|clock_division_ratio
r_static
r_int
id|clock_division_ratio
op_assign
id|WTCSR_CKS_4096
suffix:semicolon
DECL|macro|msecs_to_jiffies
mdefine_line|#define msecs_to_jiffies(msecs)&t;(jiffies + (HZ * msecs + 9999) / 10000)
DECL|macro|next_ping_period
mdefine_line|#define next_ping_period(cks)&t;msecs_to_jiffies(cks - 4)
DECL|variable|shwdt_is_open
r_static
r_int
r_int
id|shwdt_is_open
suffix:semicolon
DECL|variable|sh_wdt_info
r_static
r_struct
id|watchdog_info
id|sh_wdt_info
suffix:semicolon
DECL|variable|shwdt_expect_close
r_static
r_char
id|shwdt_expect_close
suffix:semicolon
DECL|variable|timer
r_static
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|variable|next_heartbeat
r_static
r_int
r_int
id|next_heartbeat
suffix:semicolon
DECL|variable|heartbeat
r_static
r_int
id|heartbeat
op_assign
l_int|30
suffix:semicolon
macro_line|#ifdef CONFIG_WATCHDOG_NOWAYOUT
DECL|variable|nowayout
r_static
r_int
id|nowayout
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|nowayout
r_static
r_int
id|nowayout
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/**&n; * &t;sh_wdt_start - Start the Watchdog&n; *&n; * &t;Starts the watchdog.&n; */
DECL|function|sh_wdt_start
r_static
r_void
id|sh_wdt_start
c_func
(paren
r_void
)paren
(brace
id|__u8
id|csr
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|timer
comma
id|next_ping_period
c_func
(paren
id|clock_division_ratio
)paren
)paren
suffix:semicolon
id|next_heartbeat
op_assign
id|jiffies
op_plus
(paren
id|heartbeat
op_star
id|HZ
)paren
suffix:semicolon
id|csr
op_assign
id|sh_wdt_read_csr
c_func
(paren
)paren
suffix:semicolon
id|csr
op_or_assign
id|WTCSR_WT
op_or
id|clock_division_ratio
suffix:semicolon
id|sh_wdt_write_csr
c_func
(paren
id|csr
)paren
suffix:semicolon
id|sh_wdt_write_cnt
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * These processors have a bit of an inconsistent initialization&n;&t; * process.. starting with SH-3, RSTS was moved to WTCSR, and the&n;&t; * RSTCSR register was removed.&n;&t; *&n;&t; * On the SH-2 however, in addition with bits being in different&n;&t; * locations, we must deal with RSTCSR outright..&n;&t; */
id|csr
op_assign
id|sh_wdt_read_csr
c_func
(paren
)paren
suffix:semicolon
id|csr
op_or_assign
id|WTCSR_TME
suffix:semicolon
id|csr
op_and_assign
op_complement
id|WTCSR_RSTS
suffix:semicolon
id|sh_wdt_write_csr
c_func
(paren
id|csr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_SH2
multiline_comment|/*&n;&t; * Whoever came up with the RSTCSR semantics must&squot;ve been smoking&n;&t; * some of the good stuff, since in addition to the WTCSR/WTCNT write&n;&t; * brain-damage, it&squot;s managed to fuck things up one step further..&n;&t; *&n;&t; * If we need to clear the WOVF bit, the upper byte has to be 0xa5..&n;&t; * but if we want to touch RSTE or RSTS, the upper byte has to be&n;&t; * 0x5a..&n;&t; */
id|csr
op_assign
id|sh_wdt_read_rstcsr
c_func
(paren
)paren
suffix:semicolon
id|csr
op_and_assign
op_complement
id|RSTCSR_RSTS
suffix:semicolon
id|sh_wdt_write_rstcsr
c_func
(paren
id|csr
)paren
suffix:semicolon
macro_line|#endif&t;
)brace
multiline_comment|/**&n; * &t;sh_wdt_stop - Stop the Watchdog&n; *&n; * &t;Stops the watchdog.&n; */
DECL|function|sh_wdt_stop
r_static
r_void
id|sh_wdt_stop
c_func
(paren
r_void
)paren
(brace
id|__u8
id|csr
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|csr
op_assign
id|sh_wdt_read_csr
c_func
(paren
)paren
suffix:semicolon
id|csr
op_and_assign
op_complement
id|WTCSR_TME
suffix:semicolon
id|sh_wdt_write_csr
c_func
(paren
id|csr
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_ping - Ping the Watchdog&n; *&n; *&t;@data: Unused&n; *&n; * &t;Clears overflow bit, resets timer counter.&n; */
DECL|function|sh_wdt_ping
r_static
r_void
id|sh_wdt_ping
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|next_heartbeat
)paren
)paren
(brace
id|__u8
id|csr
suffix:semicolon
id|csr
op_assign
id|sh_wdt_read_csr
c_func
(paren
)paren
suffix:semicolon
id|csr
op_and_assign
op_complement
id|WTCSR_IOVF
suffix:semicolon
id|sh_wdt_write_csr
c_func
(paren
id|csr
)paren
suffix:semicolon
id|sh_wdt_write_cnt
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|timer
comma
id|next_ping_period
c_func
(paren
id|clock_division_ratio
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * &t;sh_wdt_open - Open the Device&n; *&n; * &t;@inode: inode of device&n; * &t;@file: file handle of device&n; *&n; * &t;Watchdog device is opened and started.&n; */
DECL|function|sh_wdt_open
r_static
r_int
id|sh_wdt_open
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
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|shwdt_is_open
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|nowayout
)paren
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|sh_wdt_start
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_close - Close the Device&n; *&n; * &t;@inode: inode of device&n; * &t;@file: file handle of device&n; *&n; * &t;Watchdog device is closed and stopped.&n; */
DECL|function|sh_wdt_close
r_static
r_int
id|sh_wdt_close
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
op_logical_neg
id|nowayout
op_logical_and
id|shwdt_expect_close
op_eq
l_int|42
)paren
(brace
id|sh_wdt_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;shwdt: Unexpected close, not stopping watchdog!&bslash;n&quot;
)paren
suffix:semicolon
id|next_heartbeat
op_assign
id|jiffies
op_plus
(paren
id|heartbeat
op_star
id|HZ
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|shwdt_is_open
)paren
suffix:semicolon
id|shwdt_expect_close
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_write - Write to Device&n; *&n; * &t;@file: file handle of device&n; * &t;@buf: buffer to write&n; * &t;@count: length of buffer&n; * &t;@ppos: offset&n; *&n; * &t;Pings the watchdog on write.&n; */
DECL|function|sh_wdt_write
r_static
id|ssize_t
id|sh_wdt_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
multiline_comment|/* Can&squot;t seek (pwrite) on this device */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
id|shwdt_expect_close
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_ne
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|buf
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;V&squot;
)paren
id|shwdt_expect_close
op_assign
l_int|42
suffix:semicolon
)brace
id|next_heartbeat
op_assign
id|jiffies
op_plus
(paren
id|heartbeat
op_star
id|HZ
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_ioctl - Query Device&n; *&n; * &t;@inode: inode of device&n; * &t;@file: file handle of device&n; * &t;@cmd: watchdog command&n; * &t;@arg: argument&n; *&n; * &t;Query basic information from the device or ping it, as outlined by the&n; * &t;watchdog API.&n; */
DECL|function|sh_wdt_ioctl
r_static
r_int
id|sh_wdt_ioctl
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
id|new_timeout
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|WDIOC_GETSUPPORT
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|watchdog_info
op_star
)paren
id|arg
comma
op_amp
id|sh_wdt_info
comma
r_sizeof
(paren
id|sh_wdt_info
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_case
id|WDIOC_GETBOOTSTATUS
suffix:colon
r_return
id|put_user
c_func
(paren
l_int|0
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|next_heartbeat
op_assign
id|jiffies
op_plus
(paren
id|heartbeat
op_star
id|HZ
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_SETTIMEOUT
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|new_timeout
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|new_timeout
template_param
l_int|3600
)paren
multiline_comment|/* arbitrary upper limit */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|heartbeat
op_assign
id|new_timeout
suffix:semicolon
id|next_heartbeat
op_assign
id|jiffies
op_plus
(paren
id|heartbeat
op_star
id|HZ
)paren
suffix:semicolon
multiline_comment|/* Fall */
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|heartbeat
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|WDIOC_SETOPTIONS
suffix:colon
(brace
r_int
id|options
comma
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|options
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|options
op_amp
id|WDIOS_DISABLECARD
)paren
(brace
id|sh_wdt_stop
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|options
op_amp
id|WDIOS_ENABLECARD
)paren
(brace
id|sh_wdt_start
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_notify_sys - Notifier Handler&n; * &t;&n; * &t;@this: notifier block&n; * &t;@code: notifier event&n; * &t;@unused: unused&n; *&n; * &t;Handles specific events, such as turning off the watchdog during a&n; * &t;shutdown event.&n; */
DECL|function|sh_wdt_notify_sys
r_static
r_int
id|sh_wdt_notify_sys
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|code
comma
r_void
op_star
id|unused
)paren
(brace
r_if
c_cond
(paren
id|code
op_eq
id|SYS_DOWN
op_logical_or
id|code
op_eq
id|SYS_HALT
)paren
(brace
id|sh_wdt_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|sh_wdt_fops
r_static
r_struct
id|file_operations
id|sh_wdt_fops
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
id|write
op_assign
id|sh_wdt_write
comma
dot
id|ioctl
op_assign
id|sh_wdt_ioctl
comma
dot
id|open
op_assign
id|sh_wdt_open
comma
dot
id|release
op_assign
id|sh_wdt_close
comma
)brace
suffix:semicolon
DECL|variable|sh_wdt_info
r_static
r_struct
id|watchdog_info
id|sh_wdt_info
op_assign
(brace
dot
id|options
op_assign
id|WDIOF_KEEPALIVEPING
op_or
id|WDIOF_SETTIMEOUT
op_or
id|WDIOF_MAGICCLOSE
comma
dot
id|firmware_version
op_assign
l_int|1
comma
dot
id|identity
op_assign
l_string|&quot;SH WDT&quot;
comma
)brace
suffix:semicolon
DECL|variable|sh_wdt_notifier
r_static
r_struct
id|notifier_block
id|sh_wdt_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|sh_wdt_notify_sys
comma
dot
id|priority
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|sh_wdt_miscdev
r_static
r_struct
id|miscdevice
id|sh_wdt_miscdev
op_assign
(brace
dot
id|minor
op_assign
id|WATCHDOG_MINOR
comma
dot
id|name
op_assign
l_string|&quot;watchdog&quot;
comma
dot
id|fops
op_assign
op_amp
id|sh_wdt_fops
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * &t;sh_wdt_init - Initialize module&n; *&n; * &t;Registers the device and notifier handler. Actual device&n; * &t;initialization is handled by sh_wdt_open().&n; */
DECL|function|sh_wdt_init
r_static
r_int
id|__init
id|sh_wdt_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|sh_wdt_miscdev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;shwdt: Can&squot;t register misc device&bslash;n&quot;
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
id|register_reboot_notifier
c_func
(paren
op_amp
id|sh_wdt_notifier
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;shwdt: Can&squot;t register reboot notifier&bslash;n&quot;
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|sh_wdt_miscdev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|timer.function
op_assign
id|sh_wdt_ping
suffix:semicolon
id|timer.data
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_exit - Deinitialize module&n; *&n; * &t;Unregisters the device and notifier handler. Actual device&n; * &t;deinitialization is handled by sh_wdt_close().&n; */
DECL|function|sh_wdt_exit
r_static
r_void
id|__exit
id|sh_wdt_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|sh_wdt_notifier
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|sh_wdt_miscdev
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Paul Mundt &lt;lethal@linux-sh.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SuperH watchdog driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|clock_division_ratio
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|clock_division_ratio
comma
l_string|&quot;Clock division ratio. Valid ranges are from 0x5 (1.31ms) to 0x7 (5.25ms). Defaults to 0x7.&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|nowayout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|nowayout
comma
l_string|&quot;Watchdog cannot be stopped once started (default=CONFIG_WATCHDOG_NOWAYOUT)&quot;
)paren
suffix:semicolon
DECL|variable|sh_wdt_init
id|module_init
c_func
(paren
id|sh_wdt_init
)paren
suffix:semicolon
DECL|variable|sh_wdt_exit
id|module_exit
c_func
(paren
id|sh_wdt_exit
)paren
suffix:semicolon
eof
