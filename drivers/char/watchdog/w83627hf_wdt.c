multiline_comment|/*&n; *&t;w83627hf WDT driver&n; *&n; *&t;(c) Copyright 2003 P&#xfffd;draig Brady &lt;P@draigBrady.com&gt;&n; *&n; *&t;Based on advantechwdt.c which is based on wdt.c.&n; *&t;Original copyright messages:&n; *&n; *&t;(c) Copyright 2000-2001 Marek Michalkiewicz &lt;marekm@linux.org.pl&gt;&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.redhat.com&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide&n; *&t;warranty for any of this software. This material is provided&n; *&t;&quot;AS-IS&quot; and at no charge.&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@redhat.com&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|WATCHDOG_NAME
mdefine_line|#define WATCHDOG_NAME &quot;w83627hf WDT&quot;
DECL|macro|PFX
mdefine_line|#define PFX WATCHDOG_NAME &quot;: &quot;
DECL|macro|WATCHDOG_TIMEOUT
mdefine_line|#define WATCHDOG_TIMEOUT 60&t;&t;/* 60 sec default timeout */
DECL|variable|wdt_is_open
r_static
r_int
r_int
id|wdt_is_open
suffix:semicolon
DECL|variable|expect_close
r_static
r_char
id|expect_close
suffix:semicolon
multiline_comment|/* You must set this - there is no sane way to probe for this board. */
DECL|variable|wdt_io
r_static
r_int
id|wdt_io
op_assign
l_int|0x2E
suffix:semicolon
id|module_param
c_func
(paren
id|wdt_io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|wdt_io
comma
l_string|&quot;w83627hf WDT io port (default 0x2E)&quot;
)paren
suffix:semicolon
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
id|WATCHDOG_TIMEOUT
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
l_string|&quot;Watchdog timeout in seconds. 1&lt;= timeout &lt;=63, default=&quot;
id|__MODULE_STRING
c_func
(paren
id|WATCHDOG_TIMEOUT
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
multiline_comment|/*&n; *&t;Kernel methods.&n; */
DECL|macro|WDT_EFER
mdefine_line|#define WDT_EFER (wdt_io+0)   /* Extended Function Enable Registers */
DECL|macro|WDT_EFIR
mdefine_line|#define WDT_EFIR (wdt_io+0)   /* Extended Function Index Register (same as EFER) */
DECL|macro|WDT_EFDR
mdefine_line|#define WDT_EFDR (WDT_EFIR+1) /* Extended Function Data Register */
r_static
r_void
DECL|function|wdt_ctrl
id|wdt_ctrl
c_func
(paren
r_int
id|timeout
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x87
comma
id|WDT_EFER
)paren
suffix:semicolon
multiline_comment|/* Enter extended function mode */
id|outb_p
c_func
(paren
l_int|0x87
comma
id|WDT_EFER
)paren
suffix:semicolon
multiline_comment|/* Again according to manual */
id|outb_p
c_func
(paren
l_int|0x07
comma
id|WDT_EFER
)paren
suffix:semicolon
multiline_comment|/* point to logical device number reg */
id|outb_p
c_func
(paren
l_int|0x08
comma
id|WDT_EFDR
)paren
suffix:semicolon
multiline_comment|/* select logical device 8 (GPIO2) */
id|outb_p
c_func
(paren
l_int|0x30
comma
id|WDT_EFER
)paren
suffix:semicolon
multiline_comment|/* select CR30 */
id|outb_p
c_func
(paren
l_int|0x01
comma
id|WDT_EFDR
)paren
suffix:semicolon
multiline_comment|/* set bit 0 to activate GPIO2 */
id|outb_p
c_func
(paren
l_int|0xF6
comma
id|WDT_EFER
)paren
suffix:semicolon
multiline_comment|/* Select CRF6 */
id|outb_p
c_func
(paren
id|timeout
comma
id|WDT_EFDR
)paren
suffix:semicolon
multiline_comment|/* Write Timeout counter to CRF6 */
id|outb_p
c_func
(paren
l_int|0xAA
comma
id|WDT_EFER
)paren
suffix:semicolon
multiline_comment|/* Leave extended function mode */
)brace
r_static
r_void
DECL|function|wdt_ping
id|wdt_ping
c_func
(paren
r_void
)paren
(brace
id|wdt_ctrl
c_func
(paren
id|timeout
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|wdt_disable
id|wdt_disable
c_func
(paren
r_void
)paren
(brace
id|wdt_ctrl
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|wdt_write
id|wdt_write
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
multiline_comment|/*  Can&squot;t seek (pwrite) on this device  */
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
id|expect_close
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
id|expect_close
op_assign
l_int|42
suffix:semicolon
)brace
)brace
id|wdt_ping
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|wdt_ioctl
id|wdt_ioctl
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
l_string|&quot;Advantech WDT&quot;
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
id|wdt_ping
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
(paren
id|new_timeout
OL
l_int|1
)paren
op_logical_or
(paren
id|new_timeout
OG
l_int|63
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
id|wdt_ping
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
id|wdt_disable
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
id|wdt_ping
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
r_static
r_int
DECL|function|wdt_open
id|wdt_open
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
id|wdt_is_open
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Activate&n;&t; */
id|wdt_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|wdt_close
id|wdt_close
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
id|wdt_disable
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
l_string|&quot;Unexpected close, not stopping watchdog!&bslash;n&quot;
)paren
suffix:semicolon
id|wdt_ping
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
id|wdt_is_open
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
r_static
r_int
DECL|function|wdt_notify_sys
id|wdt_notify_sys
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
id|wdt_disable
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
DECL|variable|wdt_fops
r_static
r_struct
id|file_operations
id|wdt_fops
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
id|wdt_write
comma
dot
id|ioctl
op_assign
id|wdt_ioctl
comma
dot
id|open
op_assign
id|wdt_open
comma
dot
id|release
op_assign
id|wdt_close
comma
)brace
suffix:semicolon
DECL|variable|wdt_miscdev
r_static
r_struct
id|miscdevice
id|wdt_miscdev
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
id|wdt_fops
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The WDT needs to learn about soft shutdowns in order to&n; *&t;turn the timebomb registers off.&n; */
DECL|variable|wdt_notifier
r_static
r_struct
id|notifier_block
id|wdt_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|wdt_notify_sys
comma
dot
id|next
op_assign
l_int|NULL
comma
dot
id|priority
op_assign
l_int|0
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|wdt_init
id|wdt_init
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
l_string|&quot;WDT driver for Advantech single board computer initialising.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
template_param
l_int|63
)paren
(brace
id|timeout
op_assign
id|WATCHDOG_TIMEOUT
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;timeout value must be 1&lt;=x&lt;=63, using %d&bslash;n&quot;
comma
id|timeout
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|wdt_io
comma
l_int|1
comma
id|WATCHDOG_NAME
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;I/O address 0x%04x already in use&bslash;n&quot;
comma
id|wdt_io
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|wdt_notifier
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
id|unreg_regions
suffix:semicolon
)brace
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|wdt_miscdev
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
id|unreg_reboot
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
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
id|unreg_reboot
suffix:colon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wdt_notifier
)paren
suffix:semicolon
id|unreg_regions
suffix:colon
id|release_region
c_func
(paren
id|wdt_io
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|wdt_exit
id|wdt_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|wdt_miscdev
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wdt_notifier
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|wdt_io
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|wdt_init
id|module_init
c_func
(paren
id|wdt_init
)paren
suffix:semicolon
DECL|variable|wdt_exit
id|module_exit
c_func
(paren
id|wdt_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;P&#xfffd;draig Brady &lt;P@draigBrady.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;w38627hf WDT driver&quot;
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
