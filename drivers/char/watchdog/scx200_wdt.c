multiline_comment|/* drivers/char/watchdog/scx200_wdt.c&n;&n;   National Semiconductor SCx200 Watchdog support&n;&n;   Copyright (c) 2001,2002 Christer Weinigel &lt;wingel@nano-system.com&gt;&n;&n;   Some code taken from:&n;   National Semiconductor PC87307/PC97307 (ala SC1200) WDT driver&n;   (c) Copyright 2002 Zwane Mwaikambo &lt;zwane@commfireservices.com&gt;&n;&n;   This program is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   The author(s) of this software shall not be held liable for damages&n;   of any nature resulting due to the use of this software. This&n;   software is provided AS-IS with no warranties. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/scx200.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|NAME
mdefine_line|#define NAME &quot;scx200_wdt&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christer Weinigel &lt;wingel@nano-system.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NatSemi SCx200 Watchdog Driver&quot;
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
macro_line|#ifndef CONFIG_WATCHDOG_NOWAYOUT
DECL|macro|CONFIG_WATCHDOG_NOWAYOUT
mdefine_line|#define CONFIG_WATCHDOG_NOWAYOUT 0
macro_line|#endif
DECL|variable|margin
r_static
r_int
id|margin
op_assign
l_int|60
suffix:semicolon
multiline_comment|/* in seconds */
id|module_param
c_func
(paren
id|margin
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|margin
comma
l_string|&quot;Watchdog margin in seconds&quot;
)paren
suffix:semicolon
DECL|variable|nowayout
r_static
r_int
id|nowayout
op_assign
id|CONFIG_WATCHDOG_NOWAYOUT
suffix:semicolon
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
l_string|&quot;Disable watchdog shutdown on close&quot;
)paren
suffix:semicolon
DECL|variable|wdto_restart
r_static
id|u16
id|wdto_restart
suffix:semicolon
DECL|variable|open_semaphore
r_static
r_struct
id|semaphore
id|open_semaphore
suffix:semicolon
DECL|variable|expect_close
r_static
r_char
id|expect_close
suffix:semicolon
multiline_comment|/* Bits of the WDCNFG register */
DECL|macro|W_ENABLE
mdefine_line|#define W_ENABLE 0x00fa&t;&t;/* Enable watchdog */
DECL|macro|W_DISABLE
mdefine_line|#define W_DISABLE 0x0000&t;/* Disable watchdog */
multiline_comment|/* The scaling factor for the timer, this depends on the value of W_ENABLE */
DECL|macro|W_SCALE
mdefine_line|#define W_SCALE (32768/1024)
DECL|function|scx200_wdt_ping
r_static
r_void
id|scx200_wdt_ping
c_func
(paren
r_void
)paren
(brace
id|outw
c_func
(paren
id|wdto_restart
comma
id|scx200_cb_base
op_plus
id|SCx200_WDT_WDTO
)paren
suffix:semicolon
)brace
DECL|function|scx200_wdt_update_margin
r_static
r_void
id|scx200_wdt_update_margin
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: timer margin %d seconds&bslash;n&quot;
comma
id|margin
)paren
suffix:semicolon
id|wdto_restart
op_assign
id|margin
op_star
id|W_SCALE
suffix:semicolon
)brace
DECL|function|scx200_wdt_enable
r_static
r_void
id|scx200_wdt_enable
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: enabling watchdog timer, wdto_restart = %d&bslash;n&quot;
comma
id|wdto_restart
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0
comma
id|scx200_cb_base
op_plus
id|SCx200_WDT_WDTO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|SCx200_WDT_WDSTS_WDOVF
comma
id|scx200_cb_base
op_plus
id|SCx200_WDT_WDSTS
)paren
suffix:semicolon
id|outw
c_func
(paren
id|W_ENABLE
comma
id|scx200_cb_base
op_plus
id|SCx200_WDT_WDCNFG
)paren
suffix:semicolon
id|scx200_wdt_ping
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|scx200_wdt_disable
r_static
r_void
id|scx200_wdt_disable
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: disabling watchdog timer&bslash;n&quot;
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0
comma
id|scx200_cb_base
op_plus
id|SCx200_WDT_WDTO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|SCx200_WDT_WDSTS_WDOVF
comma
id|scx200_cb_base
op_plus
id|SCx200_WDT_WDSTS
)paren
suffix:semicolon
id|outw
c_func
(paren
id|W_DISABLE
comma
id|scx200_cb_base
op_plus
id|SCx200_WDT_WDCNFG
)paren
suffix:semicolon
)brace
DECL|function|scx200_wdt_open
r_static
r_int
id|scx200_wdt_open
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
multiline_comment|/* only allow one at a time */
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|open_semaphore
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|scx200_wdt_enable
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
DECL|function|scx200_wdt_release
r_static
r_int
id|scx200_wdt_release
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
op_ne
l_int|42
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|NAME
l_string|&quot;: watchdog device closed unexpectedly, will not disable the watchdog timer&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
(brace
id|scx200_wdt_disable
c_func
(paren
)paren
suffix:semicolon
)brace
id|expect_close
op_assign
l_int|0
suffix:semicolon
id|up
c_func
(paren
op_amp
id|open_semaphore
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_wdt_notify_sys
r_static
r_int
id|scx200_wdt_notify_sys
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
id|SYS_HALT
op_logical_or
id|code
op_eq
id|SYS_POWER_OFF
)paren
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
id|scx200_wdt_disable
c_func
(paren
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|scx200_wdt_notifier
r_static
r_struct
id|notifier_block
id|scx200_wdt_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|scx200_wdt_notify_sys
comma
)brace
suffix:semicolon
DECL|function|scx200_wdt_write
r_static
id|ssize_t
id|scx200_wdt_write
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
multiline_comment|/* check for a magic close character */
r_if
c_cond
(paren
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
id|scx200_wdt_ping
c_func
(paren
)paren
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
OL
id|len
suffix:semicolon
op_increment
id|i
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
id|data
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
r_return
id|len
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_wdt_ioctl
r_static
r_int
id|scx200_wdt_ioctl
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
id|identity
op_assign
l_string|&quot;NatSemi SCx200 Watchdog&quot;
comma
dot
id|firmware_version
op_assign
l_int|1
comma
dot
id|options
op_assign
(paren
id|WDIOF_SETTIMEOUT
op_or
id|WDIOF_KEEPALIVEPING
)paren
comma
)brace
suffix:semicolon
r_int
id|new_margin
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
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_case
id|WDIOC_GETBOOTSTATUS
suffix:colon
r_if
c_cond
(paren
id|put_user
c_func
(paren
l_int|0
comma
id|p
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
id|WDIOC_KEEPALIVE
suffix:colon
id|scx200_wdt_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
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
id|new_margin
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
id|new_margin
OL
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|margin
op_assign
id|new_margin
suffix:semicolon
id|scx200_wdt_update_margin
c_func
(paren
)paren
suffix:semicolon
id|scx200_wdt_ping
c_func
(paren
)paren
suffix:semicolon
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|margin
comma
id|p
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
)brace
DECL|variable|scx200_wdt_fops
r_static
r_struct
id|file_operations
id|scx200_wdt_fops
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
id|scx200_wdt_write
comma
dot
id|ioctl
op_assign
id|scx200_wdt_ioctl
comma
dot
id|open
op_assign
id|scx200_wdt_open
comma
dot
id|release
op_assign
id|scx200_wdt_release
comma
)brace
suffix:semicolon
DECL|variable|scx200_wdt_miscdev
r_static
r_struct
id|miscdevice
id|scx200_wdt_miscdev
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
id|NAME
comma
dot
id|fops
op_assign
op_amp
id|scx200_wdt_fops
comma
)brace
suffix:semicolon
DECL|function|scx200_wdt_init
r_static
r_int
id|__init
id|scx200_wdt_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: NatSemi SCx200 Watchdog Driver&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* check that we have found the configuration block */
r_if
c_cond
(paren
op_logical_neg
id|scx200_cb_present
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|scx200_cb_base
op_plus
id|SCx200_WDT_OFFSET
comma
id|SCx200_WDT_SIZE
comma
l_string|&quot;NatSemi SCx200 Watchdog&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|NAME
l_string|&quot;: watchdog I/O region busy&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|scx200_wdt_update_margin
c_func
(paren
)paren
suffix:semicolon
id|scx200_wdt_disable
c_func
(paren
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|open_semaphore
comma
l_int|1
)paren
suffix:semicolon
id|r
op_assign
id|misc_register
c_func
(paren
op_amp
id|scx200_wdt_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|release_region
c_func
(paren
id|scx200_cb_base
op_plus
id|SCx200_WDT_OFFSET
comma
id|SCx200_WDT_SIZE
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
id|r
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|scx200_wdt_notifier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: unable to register reboot notifier&quot;
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|scx200_wdt_miscdev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|scx200_cb_base
op_plus
id|SCx200_WDT_OFFSET
comma
id|SCx200_WDT_SIZE
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_wdt_cleanup
r_static
r_void
id|__exit
id|scx200_wdt_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|scx200_wdt_notifier
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|scx200_wdt_miscdev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|scx200_cb_base
op_plus
id|SCx200_WDT_OFFSET
comma
id|SCx200_WDT_SIZE
)paren
suffix:semicolon
)brace
DECL|variable|scx200_wdt_init
id|module_init
c_func
(paren
id|scx200_wdt_init
)paren
suffix:semicolon
DECL|variable|scx200_wdt_cleanup
id|module_exit
c_func
(paren
id|scx200_wdt_cleanup
)paren
suffix:semicolon
multiline_comment|/*&n;    Local variables:&n;        compile-command: &quot;make -k -C ../.. SUBDIRS=drivers/char modules&quot;&n;        c-basic-offset: 8&n;    End:&n;*/
eof
