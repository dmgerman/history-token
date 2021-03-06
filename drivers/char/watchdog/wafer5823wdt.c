multiline_comment|/*&n; *&t;ICP Wafer 5823 Single Board Computer WDT driver&n; *      http://www.icpamerica.com/wafer_5823.php&n; *      May also work on other similar models&n; *&n; *&t;(c) Copyright 2002 Justin Cormack &lt;justin@street-vision.com&gt;&n; *&n; *      Release 0.02&n; *&n; *&t;Based on advantechwdt.c which is based on wdt.c.&n; *&t;Original copyright messages:&n; *&n; *&t;(c) Copyright 1996-1997 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.redhat.com&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide&n; *&t;warranty for any of this software. This material is provided&n; *&t;&quot;AS-IS&quot; and at no charge.&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|WATCHDOG_NAME
mdefine_line|#define WATCHDOG_NAME &quot;Wafer 5823 WDT&quot;
DECL|macro|PFX
mdefine_line|#define PFX WATCHDOG_NAME &quot;: &quot;
DECL|macro|WD_TIMO
mdefine_line|#define WD_TIMO 60&t;&t;&t;/* 60 sec default timeout */
DECL|variable|wafwdt_is_open
r_static
r_int
r_int
id|wafwdt_is_open
suffix:semicolon
DECL|variable|expect_close
r_static
r_char
id|expect_close
suffix:semicolon
DECL|variable|wafwdt_lock
r_static
id|spinlock_t
id|wafwdt_lock
suffix:semicolon
multiline_comment|/*&n; *&t;You must set these - there is no sane way to probe for this board.&n; *&n; *      To enable, write the timeout value in seconds (1 to 255) to I/O&n; *      port WDT_START, then read the port to start the watchdog. To pat&n; *      the dog, read port WDT_STOP to stop the timer, then read WDT_START&n; *      to restart it again.&n; */
DECL|variable|wdt_stop
r_static
r_int
id|wdt_stop
op_assign
l_int|0x843
suffix:semicolon
DECL|variable|wdt_start
r_static
r_int
id|wdt_start
op_assign
l_int|0x443
suffix:semicolon
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
id|WD_TIMO
suffix:semicolon
multiline_comment|/* in seconds */
id|module_param
c_func
(paren
id|timeout
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|timeout
comma
l_string|&quot;Watchdog timeout in seconds. 1&lt;= timeout &lt;=255, default=&quot;
id|__MODULE_STRING
c_func
(paren
id|WD_TIMO
)paren
l_string|&quot;.&quot;
)paren
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
DECL|function|wafwdt_ping
r_static
r_void
id|wafwdt_ping
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* pat watchdog */
id|spin_lock
c_func
(paren
op_amp
id|wafwdt_lock
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|wdt_stop
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|wdt_start
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|wafwdt_lock
)paren
suffix:semicolon
)brace
DECL|function|wafwdt_start
r_static
r_void
id|wafwdt_start
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* start up watchdog */
id|outb_p
c_func
(paren
id|timeout
comma
id|wdt_start
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|wdt_start
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|wafwdt_stop
id|wafwdt_stop
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* stop watchdog */
id|inb_p
c_func
(paren
id|wdt_stop
)paren
suffix:semicolon
)brace
DECL|function|wafwdt_write
r_static
id|ssize_t
id|wafwdt_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
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
multiline_comment|/* See if we got the magic character &squot;V&squot; and reload the timer */
r_if
c_cond
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* In case it was set long ago */
id|expect_close
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* scan to see whether or not we got the magic character */
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
id|expect_close
op_assign
l_int|42
suffix:semicolon
)brace
)brace
multiline_comment|/* Well, anyhow someone wrote to us, we should return that favour */
id|wafwdt_ping
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|wafwdt_ioctl
r_static
r_int
id|wafwdt_ioctl
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
r_int
id|__user
op_star
id|p
op_assign
id|argp
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
l_string|&quot;Wafer 5823 WDT&quot;
comma
)brace
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
id|argp
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
id|p
)paren
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|wafwdt_ping
c_func
(paren
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
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|new_timeout
OL
l_int|1
)paren
op_logical_or
(paren
id|new_timeout
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|timeout
op_assign
id|new_timeout
suffix:semicolon
id|wafwdt_stop
c_func
(paren
)paren
suffix:semicolon
id|wafwdt_start
c_func
(paren
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
id|timeout
comma
id|p
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
id|p
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
id|wafwdt_start
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
id|wafwdt_stop
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
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wafwdt_open
r_static
r_int
id|wafwdt_open
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
id|wafwdt_is_open
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/*&n;&t; *      Activate&n;&t; */
id|wafwdt_start
c_func
(paren
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
r_static
r_int
DECL|function|wafwdt_close
id|wafwdt_close
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
id|expect_close
op_eq
l_int|42
)paren
(brace
id|wafwdt_stop
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
id|PFX
l_string|&quot;WDT device closed unexpectedly.  WDT will not stop!&bslash;n&quot;
)paren
suffix:semicolon
id|wafwdt_ping
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
id|wafwdt_is_open
)paren
suffix:semicolon
id|expect_close
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Notifier for system down&n; */
DECL|function|wafwdt_notify_sys
r_static
r_int
id|wafwdt_notify_sys
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
multiline_comment|/* Turn the WDT off */
id|wafwdt_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Kernel Interfaces&n; */
DECL|variable|wafwdt_fops
r_static
r_struct
id|file_operations
id|wafwdt_fops
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
id|wafwdt_write
comma
dot
id|ioctl
op_assign
id|wafwdt_ioctl
comma
dot
id|open
op_assign
id|wafwdt_open
comma
dot
id|release
op_assign
id|wafwdt_close
comma
)brace
suffix:semicolon
DECL|variable|wafwdt_miscdev
r_static
r_struct
id|miscdevice
id|wafwdt_miscdev
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
id|wafwdt_fops
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The WDT needs to learn about soft shutdowns in order to&n; *&t;turn the timebomb registers off.&n; */
DECL|variable|wafwdt_notifier
r_static
r_struct
id|notifier_block
id|wafwdt_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|wafwdt_notify_sys
comma
)brace
suffix:semicolon
DECL|function|wafwdt_init
r_static
r_int
id|__init
id|wafwdt_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;WDT driver for Wafer 5823 single board computer initialising.&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|wafwdt_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
template_param
l_int|255
)paren
(brace
id|timeout
op_assign
id|WD_TIMO
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;timeout value must be 1&lt;=x&lt;=255, using %d&bslash;n&quot;
comma
id|timeout
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wdt_stop
op_ne
id|wdt_start
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|wdt_stop
comma
l_int|1
comma
l_string|&quot;Wafer 5823 WDT&quot;
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;I/O address 0x%04x already in use&bslash;n&quot;
comma
id|wdt_stop
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|wdt_start
comma
l_int|1
comma
l_string|&quot;Wafer 5823 WDT&quot;
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;I/O address 0x%04x already in use&bslash;n&quot;
comma
id|wdt_start
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error2
suffix:semicolon
)brace
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|wafwdt_notifier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register reboot notifier (err=%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|error3
suffix:semicolon
)brace
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|wafwdt_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|printk
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
r_goto
id|error4
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;initialized. timeout=%d sec (nowayout=%d)&bslash;n&quot;
comma
id|timeout
comma
id|nowayout
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|error4
suffix:colon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wafwdt_notifier
)paren
suffix:semicolon
id|error3
suffix:colon
id|release_region
c_func
(paren
id|wdt_start
comma
l_int|1
)paren
suffix:semicolon
id|error2
suffix:colon
r_if
c_cond
(paren
id|wdt_stop
op_ne
id|wdt_start
)paren
id|release_region
c_func
(paren
id|wdt_stop
comma
l_int|1
)paren
suffix:semicolon
id|error
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|wafwdt_exit
r_static
r_void
id|__exit
id|wafwdt_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|wafwdt_miscdev
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wafwdt_notifier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wdt_stop
op_ne
id|wdt_start
)paren
(brace
id|release_region
c_func
(paren
id|wdt_stop
comma
l_int|1
)paren
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|wdt_start
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|wafwdt_init
id|module_init
c_func
(paren
id|wafwdt_init
)paren
suffix:semicolon
DECL|variable|wafwdt_exit
id|module_exit
c_func
(paren
id|wafwdt_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Justin Cormack&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ICP Wafer 5823 Single Board Computer WDT driver&quot;
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
multiline_comment|/* end of wafer5823wdt.c */
eof
