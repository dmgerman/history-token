multiline_comment|/*&n; *&t;IndyDog&t;0.3&t;A Hardware Watchdog Device for SGI IP22&n; *&n; *&t;(c) Copyright 2002 Guido Guenther &lt;agx@sigxcpu.org&gt;, All Rights Reserved.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;based on softdog.c by Alan Cox &lt;alan@redhat.com&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/sgi/mc.h&gt;
DECL|macro|PFX
mdefine_line|#define PFX &quot;indydog: &quot;
DECL|variable|indydog_alive
r_static
r_int
id|indydog_alive
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
DECL|macro|WATCHDOG_TIMEOUT
mdefine_line|#define WATCHDOG_TIMEOUT 30&t;&t;/* 30 sec default timeout */
id|module_param
c_func
(paren
id|nowayout
comma
r_int
comma
l_int|0
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
DECL|function|indydog_start
r_static
r_void
id|indydog_start
c_func
(paren
r_void
)paren
(brace
id|u32
id|mc_ctrl0
op_assign
id|sgimc-&gt;cpuctrl0
suffix:semicolon
id|mc_ctrl0
op_assign
id|sgimc-&gt;cpuctrl0
op_or
id|SGIMC_CCTRL0_WDOG
suffix:semicolon
id|sgimc-&gt;cpuctrl0
op_assign
id|mc_ctrl0
suffix:semicolon
)brace
DECL|function|indydog_stop
r_static
r_void
id|indydog_stop
c_func
(paren
r_void
)paren
(brace
id|u32
id|mc_ctrl0
op_assign
id|sgimc-&gt;cpuctrl0
suffix:semicolon
id|mc_ctrl0
op_and_assign
op_complement
id|SGIMC_CCTRL0_WDOG
suffix:semicolon
id|sgimc-&gt;cpuctrl0
op_assign
id|mc_ctrl0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Stopped watchdog timer.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|indydog_ping
r_static
r_void
id|indydog_ping
c_func
(paren
r_void
)paren
(brace
id|sgimc-&gt;watchdogt
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|indydog_open
r_static
r_int
id|indydog_open
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
id|indydog_alive
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
multiline_comment|/* Activate timer */
id|indydog_start
c_func
(paren
)paren
suffix:semicolon
id|indydog_ping
c_func
(paren
)paren
suffix:semicolon
id|indydog_alive
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Started watchdog timer.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|nonseekable_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|indydog_release
r_static
r_int
id|indydog_release
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
multiline_comment|/* Shut off the timer.&n;&t; * Lock it in if it&squot;s a module and we defined ...NOWAYOUT */
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
id|indydog_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Turn the WDT off */
id|indydog_alive
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|indydog_write
r_static
id|ssize_t
id|indydog_write
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
id|data
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
multiline_comment|/* Refresh the timer. */
r_if
c_cond
(paren
id|len
)paren
(brace
id|indydog_ping
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|indydog_ioctl
r_static
r_int
id|indydog_ioctl
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
id|options
comma
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_static
r_struct
id|watchdog_info
id|ident
op_assign
(brace
dot
id|options
op_assign
id|WDIOF_KEEPALIVEPING
op_or
id|WDIOF_MAGICCLOSE
comma
dot
id|firmware_version
op_assign
l_int|0
comma
dot
id|identity
op_assign
l_string|&quot;Hardware Watchdog for SGI IP22&quot;
comma
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
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
id|ident
comma
r_sizeof
(paren
id|ident
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
id|indydog_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|WATCHDOG_TIMEOUT
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
id|indydog_stop
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
id|indydog_start
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
)brace
)brace
DECL|function|indydog_notify_sys
r_static
r_int
id|indydog_notify_sys
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
id|indydog_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Turn the WDT off */
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|indydog_fops
r_static
r_struct
id|file_operations
id|indydog_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|write
op_assign
id|indydog_write
comma
dot
id|ioctl
op_assign
id|indydog_ioctl
comma
dot
id|open
op_assign
id|indydog_open
comma
dot
id|release
op_assign
id|indydog_release
comma
)brace
suffix:semicolon
DECL|variable|indydog_miscdev
r_static
r_struct
id|miscdevice
id|indydog_miscdev
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
id|indydog_fops
comma
)brace
suffix:semicolon
DECL|variable|indydog_notifier
r_static
r_struct
id|notifier_block
id|indydog_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|indydog_notify_sys
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
id|PFX
l_string|&quot;Hardware Watchdog Timer for SGI IP22: 0.3&bslash;n&quot;
suffix:semicolon
DECL|function|watchdog_init
r_static
r_int
id|__init
id|watchdog_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|indydog_notifier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register reboot notifier (err=%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|indydog_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register miscdev on minor=%d (err=%d)&bslash;n&quot;
comma
id|WATCHDOG_MINOR
comma
id|ret
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|indydog_notifier
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|printk
c_func
(paren
id|banner
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|watchdog_exit
r_static
r_void
id|__exit
id|watchdog_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|indydog_miscdev
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|indydog_notifier
)paren
suffix:semicolon
)brace
DECL|variable|watchdog_init
id|module_init
c_func
(paren
id|watchdog_init
)paren
suffix:semicolon
DECL|variable|watchdog_exit
id|module_exit
c_func
(paren
id|watchdog_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Guido Guenther &lt;agx@sigxcpu.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Hardware Watchdog Device for SGI IP22&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|WATCHDOG_MINOR
id|MODULE_ALIAS_MISCDEV
c_func
(paren
id|WATCHDOG_MINOR
)paren
suffix:semicolon
eof
