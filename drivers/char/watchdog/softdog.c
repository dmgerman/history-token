multiline_comment|/*&n; *&t;SoftDog&t;0.06:&t;A Software Watchdog Device&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.redhat.com&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide&n; *&t;warranty for any of this software. This material is provided&n; *&t;&quot;AS-IS&quot; and at no charge.&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; *&t;Software only watchdog driver. Unlike its big brother the WDT501P&n; *&t;driver this won&squot;t always recover a failed machine.&n; *&n; *  03/96: Angelo Haritsis &lt;ah@doc.ic.ac.uk&gt; :&n; *&t;Modularised.&n; *&t;Added soft_margin; use upon insmod to change the timer delay.&n; *&t;NB: uses same minor as wdt (WATCHDOG_MINOR); we could use separate&n; *&t;    minors.&n; *&n; *  19980911 Alan Cox&n; *&t;Made SMP safe for 2.3.x&n; *&n; *  20011127 Joel Becker (jlbec@evilplan.org&gt;&n; *&t;Added soft_noboot; Allows testing the softdog trigger without&n; *&t;requiring a recompile.&n; *&t;Added WDIOC_GETTIMEOUT and WDIOC_SETTIMOUT.&n; *&n; *  20020530 Joel Becker &lt;joel.becker@oracle.com&gt;&n; *  &t;Added Matt Domsch&squot;s nowayout module option.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|TIMER_MARGIN
mdefine_line|#define TIMER_MARGIN&t;60&t;&t;/* (secs) Default is 1 minute */
DECL|variable|expect_close
r_static
r_char
id|expect_close
suffix:semicolon
DECL|variable|soft_margin
r_static
r_int
id|soft_margin
op_assign
id|TIMER_MARGIN
suffix:semicolon
multiline_comment|/* in seconds */
macro_line|#ifdef ONLY_TESTING
DECL|variable|soft_noboot
r_static
r_int
id|soft_noboot
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|soft_noboot
r_static
r_int
id|soft_noboot
op_assign
l_int|0
suffix:semicolon
macro_line|#endif  /* ONLY_TESTING */
id|module_param
c_func
(paren
id|soft_margin
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|soft_noboot
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
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
id|TIMER_INITIALIZER
c_func
(paren
id|watchdog_fire
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|timer_alive
r_static
r_int
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
r_if
c_cond
(paren
id|soft_noboot
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;SOFTDOG: Triggered - Reboot ignored.&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
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
l_string|&quot;SOFTDOG: Reboot didn&squot;t ?????&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|timer_alive
)paren
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; *&t;Shut off the timer.&n;&t; * &t;Lock it in if it&squot;s a module and we set nowayout&n;&t; */
r_if
c_cond
(paren
id|expect_close
op_eq
l_int|42
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|watchdog_ticktock
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;SOFTDOG: WDT device closed unexpectedly.  WDT will not stop!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|timer_alive
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_ne
id|len
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
)brace
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
)brace
r_return
id|len
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
r_int
id|new_margin
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
id|WDIOF_SETTIMEOUT
op_or
id|WDIOF_MAGICCLOSE
comma
dot
id|identity
op_assign
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
id|new_margin
OL
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|soft_margin
op_assign
id|new_margin
suffix:semicolon
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
multiline_comment|/* Fall */
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|soft_margin
comma
(paren
r_int
op_star
)paren
id|arg
)paren
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
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|write
op_assign
id|softdog_write
comma
dot
id|ioctl
op_assign
id|softdog_ioctl
comma
dot
id|open
op_assign
id|softdog_open
comma
dot
id|release
op_assign
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
l_string|&quot;Software Watchdog Timer: 0.06, soft_margin: %d sec, nowayout: %d&bslash;n&quot;
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
comma
id|nowayout
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
