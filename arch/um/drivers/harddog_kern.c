multiline_comment|/* UML hardware watchdog, shamelessly stolen from:&n; *&n; *&t;SoftDog&t;0.05:&t;A Software Watchdog Device&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.redhat.com&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide &n; *&t;warranty for any of this software. This material is provided &n; *&t;&quot;AS-IS&quot; and at no charge.&t;&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; *&t;Software only watchdog driver. Unlike its big brother the WDT501P&n; *&t;driver this won&squot;t always recover a failed machine.&n; *&n; *  03/96: Angelo Haritsis &lt;ah@doc.ic.ac.uk&gt; :&n; *&t;Modularised.&n; *&t;Added soft_margin; use upon insmod to change the timer delay.&n; *&t;NB: uses same minor as wdt (WATCHDOG_MINOR); we could use separate&n; *&t;    minors.&n; *&n; *  19980911 Alan Cox&n; *&t;Made SMP safe for 2.3.x&n; *&n; *  20011127 Joel Becker (jlbec@evilplan.org&gt;&n; *&t;Added soft_noboot; Allows testing the softdog trigger without &n; *&t;requiring a recompile.&n; *&t;Added WDIOC_GETTIMEOUT and WDIOC_SETTIMOUT.&n; */
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
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;mconsole.h&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|timer_alive
r_static
r_int
id|timer_alive
suffix:semicolon
DECL|variable|harddog_in_fd
r_static
r_int
id|harddog_in_fd
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|harddog_out_fd
r_static
r_int
id|harddog_out_fd
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
r_extern
r_int
id|start_watchdog
c_func
(paren
r_int
op_star
id|in_fd_ret
comma
r_int
op_star
id|out_fd_ret
comma
r_char
op_star
id|sock
)paren
suffix:semicolon
DECL|function|harddog_open
r_static
r_int
id|harddog_open
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
id|err
suffix:semicolon
r_char
op_star
id|sock
op_assign
l_int|NULL
suffix:semicolon
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
macro_line|#ifdef CONFIG_HARDDOG_NOWAYOUT&t; 
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MCONSOLE
id|sock
op_assign
id|mconsole_notify_socket
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|err
op_assign
id|start_watchdog
c_func
(paren
op_amp
id|harddog_in_fd
comma
op_amp
id|harddog_out_fd
comma
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|timer_alive
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|stop_watchdog
c_func
(paren
r_int
id|in_fd
comma
r_int
id|out_fd
)paren
suffix:semicolon
DECL|function|harddog_release
r_static
r_int
id|harddog_release
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
multiline_comment|/*&n;&t; *&t;Shut off the timer.&n;&t; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|stop_watchdog
c_func
(paren
id|harddog_in_fd
comma
id|harddog_out_fd
)paren
suffix:semicolon
id|harddog_in_fd
op_assign
op_minus
l_int|1
suffix:semicolon
id|harddog_out_fd
op_assign
op_minus
l_int|1
suffix:semicolon
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
r_extern
r_int
id|ping_watchdog
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
DECL|function|harddog_write
r_static
id|ssize_t
id|harddog_write
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
r_return
id|ping_watchdog
c_func
(paren
id|harddog_out_fd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|harddog_ioctl
r_static
r_int
id|harddog_ioctl
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
id|WDIOC_SETTIMEOUT
comma
l_int|0
comma
l_string|&quot;UML Hardware Watchdog&quot;
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
id|harddog_info
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
r_return
id|ping_watchdog
c_func
(paren
id|harddog_out_fd
)paren
suffix:semicolon
)brace
)brace
DECL|variable|harddog_fops
r_static
r_struct
id|file_operations
id|harddog_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|write
suffix:colon
id|harddog_write
comma
id|ioctl
suffix:colon
id|harddog_ioctl
comma
id|open
suffix:colon
id|harddog_open
comma
id|release
suffix:colon
id|harddog_release
comma
)brace
suffix:semicolon
DECL|variable|harddog_miscdev
r_static
r_struct
id|miscdevice
id|harddog_miscdev
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
id|harddog_fops
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
l_string|&quot;UML Watchdog Timer&bslash;n&quot;
suffix:semicolon
DECL|function|harddog_init
r_static
r_int
id|__init
id|harddog_init
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
id|harddog_miscdev
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
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|harddog_exit
r_static
r_void
id|__exit
id|harddog_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|harddog_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|harddog_init
id|module_init
c_func
(paren
id|harddog_init
)paren
suffix:semicolon
DECL|variable|harddog_exit
id|module_exit
c_func
(paren
id|harddog_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof