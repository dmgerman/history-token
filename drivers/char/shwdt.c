multiline_comment|/*&n; * drivers/char/shwdt.c&n; *&n; * Watchdog driver for integrated watchdog in the SuperH 3/4 processors.&n; *&n; * Copyright (C) 2001 Paul Mundt &lt;lethal@chaoticdreams.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * 14-Dec-2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *     Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#if defined(CONFIG_CPU_SH4)
DECL|macro|WTCNT
mdefine_line|#define WTCNT&t;&t;0xffc00008
DECL|macro|WTCSR
mdefine_line|#define WTCSR&t;&t;0xffc0000c
macro_line|#elif defined(CONFIG_CPU_SH3)
DECL|macro|WTCNT
mdefine_line|#define WTCNT&t;&t;0xffffff84
DECL|macro|WTCSR
mdefine_line|#define WTCSR&t;&t;0xffffff86
macro_line|#else
macro_line|#error &quot;Can&squot;t use SH 3/4 watchdog on non-SH 3/4 processor.&quot;
macro_line|#endif
DECL|macro|WTCNT_HIGH
mdefine_line|#define WTCNT_HIGH&t;0x5a00
DECL|macro|WTCSR_HIGH
mdefine_line|#define WTCSR_HIGH&t;0xa500
DECL|macro|WTCSR_TME
mdefine_line|#define WTCSR_TME&t;0x80
DECL|macro|WTCSR_WT
mdefine_line|#define WTCSR_WT&t;0x40
DECL|macro|WTCSR_RSTS
mdefine_line|#define WTCSR_RSTS&t;0x20
DECL|macro|WTCSR_WOVF
mdefine_line|#define WTCSR_WOVF&t;0x10
DECL|macro|WTCSR_IOVF
mdefine_line|#define WTCSR_IOVF&t;0x08
DECL|macro|WTCSR_CKS2
mdefine_line|#define WTCSR_CKS2&t;0x04
DECL|macro|WTCSR_CKS1
mdefine_line|#define WTCSR_CKS1&t;0x02
DECL|macro|WTCSR_CKS0
mdefine_line|#define WTCSR_CKS0&t;0x01
multiline_comment|/*&n; * CKS0-2 supports a number of clock division ratios. At the time the watchdog&n; * is enabled, it defaults to a 41 usec overflow period .. we overload this to&n; * something a little more reasonable, and really can&squot;t deal with anything&n; * lower than WTCSR_CKS_1024, else we drop back into the usec range.&n; *&n; * Clock Division Ratio         Overflow Period&n; * --------------------------------------------&n; *     1/32 (initial value)       41 usecs&n; *     1/64                       82 usecs&n; *     1/128                     164 usecs&n; *     1/256                     328 usecs&n; *     1/512                     656 usecs&n; *     1/1024                   1.31 msecs&n; *     1/2048                   2.62 msecs&n; *     1/4096                   5.25 msecs&n; */
DECL|macro|WTCSR_CKS_32
mdefine_line|#define WTCSR_CKS_32&t;0x00
DECL|macro|WTCSR_CKS_64
mdefine_line|#define WTCSR_CKS_64&t;0x01
DECL|macro|WTCSR_CKS_128
mdefine_line|#define WTCSR_CKS_128&t;0x02
DECL|macro|WTCSR_CKS_256
mdefine_line|#define WTCSR_CKS_256&t;0x03
DECL|macro|WTCSR_CKS_512
mdefine_line|#define WTCSR_CKS_512&t;0x04
DECL|macro|WTCSR_CKS_1024
mdefine_line|#define WTCSR_CKS_1024&t;0x05
DECL|macro|WTCSR_CKS_2048
mdefine_line|#define WTCSR_CKS_2048&t;0x06
DECL|macro|WTCSR_CKS_4096
mdefine_line|#define WTCSR_CKS_4096&t;0x07
multiline_comment|/*&n; * Default clock division ratio is 5.25 msecs. Overload this at module load&n; * time. Any value not in the msec range will default to a timeout of one&n; * jiffy, which exceeds the usec overflow periods.&n; */
DECL|variable|clock_division_ratio
r_static
r_int
id|clock_division_ratio
op_assign
id|WTCSR_CKS_4096
suffix:semicolon
DECL|macro|msecs_to_jiffies
mdefine_line|#define msecs_to_jiffies(msecs)&t;(jiffies + ((HZ * msecs + 999) / 1000))
DECL|macro|next_ping_period
mdefine_line|#define next_ping_period(cks)&t;msecs_to_jiffies(cks - 4)
DECL|macro|user_ping_period
mdefine_line|#define user_ping_period(cks)&t;(next_ping_period(cks) * 10)
DECL|variable|sh_is_open
r_static
r_int
r_int
id|sh_is_open
op_assign
l_int|0
suffix:semicolon
DECL|variable|sh_wdt_info
r_static
r_struct
id|watchdog_info
id|sh_wdt_info
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
multiline_comment|/**&n; *&t;sh_wdt_write_cnt - Write to Counter&n; *&n; *&t;@val: Value to write&n; *&n; *&t;Writes the given value @val to the lower byte of the timer counter.&n; *&t;The upper byte is set manually on each write.&n; */
DECL|function|sh_wdt_write_cnt
r_static
r_void
id|sh_wdt_write_cnt
c_func
(paren
id|__u8
id|val
)paren
(brace
id|ctrl_outw
c_func
(paren
id|WTCNT_HIGH
op_or
(paren
id|__u16
)paren
id|val
comma
id|WTCNT
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_write_csr - Write to Control/Status Register&n; *&n; * &t;@val: Value to write&n; *&n; * &t;Writes the given value @val to the lower byte of the control/status&n; * &t;register. The upper byte is set manually on each write.&n; */
DECL|function|sh_wdt_write_csr
r_static
r_void
id|sh_wdt_write_csr
c_func
(paren
id|__u8
id|val
)paren
(brace
id|ctrl_outw
c_func
(paren
id|WTCSR_HIGH
op_or
(paren
id|__u16
)paren
id|val
comma
id|WTCSR
)paren
suffix:semicolon
)brace
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
id|timer.expires
op_assign
id|next_ping_period
c_func
(paren
id|clock_division_ratio
)paren
suffix:semicolon
id|next_heartbeat
op_assign
id|user_ping_period
c_func
(paren
id|clock_division_ratio
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|sh_wdt_write_csr
c_func
(paren
id|WTCSR_WT
op_or
id|WTCSR_CKS_4096
)paren
suffix:semicolon
id|sh_wdt_write_cnt
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|sh_wdt_write_csr
c_func
(paren
(paren
id|ctrl_inb
c_func
(paren
id|WTCSR
)paren
op_or
id|WTCSR_TME
)paren
)paren
suffix:semicolon
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
id|del_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|sh_wdt_write_csr
c_func
(paren
(paren
id|ctrl_inb
c_func
(paren
id|WTCSR
)paren
op_amp
op_complement
id|WTCSR_TME
)paren
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
id|sh_wdt_write_csr
c_func
(paren
(paren
id|ctrl_inb
c_func
(paren
id|WTCSR
)paren
op_amp
op_complement
id|WTCSR_IOVF
)paren
)paren
suffix:semicolon
id|sh_wdt_write_cnt
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|timer.expires
op_assign
id|next_ping_period
c_func
(paren
id|clock_division_ratio
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|timer
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
r_switch
c_cond
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|WATCHDOG_MINOR
suffix:colon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|sh_is_open
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
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
id|sh_wdt_start
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
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
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_eq
id|WATCHDOG_MINOR
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
(brace
id|sh_wdt_stop
c_func
(paren
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|sh_is_open
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_read - Read from Device&n; *&n; * &t;@file: file handle of device&n; * &t;@buf: buffer to write to&n; * &t;@count: length of buffer&n; * &t;@ppos: offset&n; *&n; * &t;Unsupported.&n; */
DECL|function|sh_wdt_read
r_static
id|ssize_t
id|sh_wdt_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
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
r_return
op_minus
id|EINVAL
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
id|next_heartbeat
op_assign
id|user_ping_period
c_func
(paren
id|clock_division_ratio
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
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
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_int
op_star
)paren
id|arg
comma
op_amp
id|sh_is_open
comma
r_sizeof
(paren
r_int
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
id|WDIOC_KEEPALIVE
suffix:colon
id|next_heartbeat
op_assign
id|user_ping_period
c_func
(paren
id|clock_division_ratio
)paren
suffix:semicolon
r_break
suffix:semicolon
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
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|sh_wdt_read
comma
id|write
suffix:colon
id|sh_wdt_write
comma
id|ioctl
suffix:colon
id|sh_wdt_ioctl
comma
id|open
suffix:colon
id|sh_wdt_open
comma
id|release
suffix:colon
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
id|WDIOF_KEEPALIVEPING
comma
l_int|1
comma
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
id|sh_wdt_notify_sys
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|sh_wdt_miscdev
r_static
r_struct
id|miscdevice
id|sh_wdt_miscdev
op_assign
(brace
id|WATCHDOG_MINOR
comma
l_string|&quot;watchdog&quot;
comma
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
op_logical_neg
id|request_region
c_func
(paren
id|WTCNT
comma
l_int|1
comma
l_string|&quot;shwdt&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;shwdt: Can&squot;t request WTCNT region&bslash;n&quot;
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
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|WTCSR
comma
l_int|1
comma
l_string|&quot;shwdt&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;shwdt: Can&squot;t request WTCSR region&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|WTCNT
comma
l_int|1
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
id|ENXIO
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
id|release_region
c_func
(paren
id|WTCSR
comma
l_int|1
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|WTCNT
comma
l_int|1
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
id|release_region
c_func
(paren
id|WTCSR
comma
l_int|1
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|WTCNT
comma
l_int|1
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
l_string|&quot;Paul Mundt &lt;lethal@chaoticdreams.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SH 3/4 watchdog driver&quot;
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
