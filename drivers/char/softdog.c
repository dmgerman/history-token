multiline_comment|/*&n; *&t;SoftDog&t;0.05:&t;A Software Watchdog Device&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.redhat.com&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide &n; *&t;warranty for any of this software. This material is provided &n; *&t;&quot;AS-IS&quot; and at no charge.&t;&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; *&t;Software only watchdog driver. Unlike its big brother the WDT501P&n; *&t;driver this won&squot;t always recover a failed machine.&n; *&n; *  03/96: Angelo Haritsis &lt;ah@doc.ic.ac.uk&gt; :&n; *&t;Modularised.&n; *&t;Added soft_margin; use upon insmod to change the timer delay.&n; *&t;NB: uses same minor as wdt (WATCHDOG_MINOR); we could use separate&n; *&t;    minors.&n; *&n; *  19980911 Alan Cox&n; *&t;Made SMP safe for 2.3.x&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|TIMER_MARGIN
mdefine_line|#define TIMER_MARGIN&t;60&t;&t;/* (secs) Default is 1 minute */
DECL|variable|soft_margin
r_static
r_int
id|soft_margin
op_assign
id|TIMER_MARGIN
suffix:semicolon
multiline_comment|/* in seconds */
id|MODULE_PARM
c_func
(paren
id|soft_margin
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Our timer&n; */
r_static
r_void
id|watchdog_fire
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|variable|watchdog_ticktock
r_static
r_struct
id|timer_list
id|watchdog_ticktock
op_assign
(brace
id|function
suffix:colon
id|watchdog_fire
comma
)brace
suffix:semicolon
DECL|variable|timer_alive
r_static
r_int
id|timer_alive
suffix:semicolon
multiline_comment|/*&n; *&t;If the timer expires..&n; */
DECL|function|watchdog_fire
r_static
r_void
id|watchdog_fire
c_func
(paren
r_int
r_int
id|data
)paren
(brace
macro_line|#ifdef ONLY_TESTING
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;SOFTDOG: Would Reboot.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;SOFTDOG: Initiating system reboot.&bslash;n&quot;
)paren
suffix:semicolon
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;WATCHDOG: Reboot didn&squot;t ?????&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|softdog_open
r_static
r_int
id|softdog_open
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
id|timer_alive
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_WATCHDOG_NOWAYOUT&t; 
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif&t;
multiline_comment|/*&n;&t; *&t;Activate timer&n;&t; */
id|mod_timer
c_func
(paren
op_amp
id|watchdog_ticktock
comma
id|jiffies
op_plus
(paren
id|soft_margin
op_star
id|HZ
)paren
)paren
suffix:semicolon
id|timer_alive
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|softdog_release
r_static
r_int
id|softdog_release
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
multiline_comment|/*&n;&t; *&t;Shut off the timer.&n;&t; * &t;Lock it in if it&squot;s a module and we defined ...NOWAYOUT&n;&t; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_WATCHDOG_NOWAYOUT&t; 
id|del_timer
c_func
(paren
op_amp
id|watchdog_ticktock
)paren
suffix:semicolon
macro_line|#endif&t;
id|timer_alive
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|softdog_write
r_static
id|ssize_t
id|softdog_write
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
multiline_comment|/*&n;&t; *&t;Refresh the timer.&n;&t; */
r_if
c_cond
(paren
id|len
)paren
(brace
id|mod_timer
c_func
(paren
op_amp
id|watchdog_ticktock
comma
id|jiffies
op_plus
(paren
id|soft_margin
op_star
id|HZ
)paren
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
DECL|function|softdog_ioctl
r_static
r_int
id|softdog_ioctl
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
r_static
r_struct
id|watchdog_info
id|ident
op_assign
(brace
id|identity
suffix:colon
l_string|&quot;Software Watchdog&quot;
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
id|ENOTTY
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
id|mod_timer
c_func
(paren
op_amp
id|watchdog_ticktock
comma
id|jiffies
op_plus
(paren
id|soft_margin
op_star
id|HZ
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|softdog_fops
r_static
r_struct
id|file_operations
id|softdog_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|write
suffix:colon
id|softdog_write
comma
id|ioctl
suffix:colon
id|softdog_ioctl
comma
id|open
suffix:colon
id|softdog_open
comma
id|release
suffix:colon
id|softdog_release
comma
)brace
suffix:semicolon
DECL|variable|softdog_miscdev
r_static
r_struct
id|miscdevice
id|softdog_miscdev
op_assign
(brace
id|minor
suffix:colon
id|WATCHDOG_MINOR
comma
id|name
suffix:colon
l_string|&quot;watchdog&quot;
comma
id|fops
suffix:colon
op_amp
id|softdog_fops
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
l_string|&quot;Software Watchdog Timer: 0.05, timer margin: %d sec&bslash;n&quot;
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
id|misc_register
c_func
(paren
op_amp
id|softdog_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|banner
comma
id|soft_margin
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
id|softdog_miscdev
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
eof
