multiline_comment|/*&n; * MixCom Watchdog: A Simple Hardware Watchdog Device&n; * Based on Softdog driver by Alan Cox and PC Watchdog driver by Ken Hollis&n; *&n; * Author: Gergely Madarasz &lt;gorgo@itc.hu&gt;&n; *&n; * Copyright (c) 1999 ITConsult-Pro Co. &lt;info@itc.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Version 0.1 (99/04/15):&n; *&t;&t;- first version&n; *&n; * Version 0.2 (99/06/16):&n; *&t;&t;- added kernel timer watchdog ping after close&n; *&t;&t;  since the hardware does not support watchdog shutdown&n; *&n; * Version 0.3 (99/06/21):&n; *&t;&t;- added WDIOC_GETSTATUS and WDIOC_GETSUPPORT ioctl calls&n; *&n; * Version 0.3.1 (99/06/22):&n; *&t;&t;- allow module removal while internal timer is active,&n; *&t;&t;  print warning about probable reset&n; *&n; * Version 0.4 (99/11/15):&n; *&t;&t;- support for one more type board&n; *&n; * Version 0.5 (2001/12/14) Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *              - added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT&n; *&n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;0.5&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|mixcomwd_ioports
r_static
r_int
id|mixcomwd_ioports
(braket
)braket
op_assign
(brace
l_int|0x180
comma
l_int|0x280
comma
l_int|0x380
comma
l_int|0x000
)brace
suffix:semicolon
DECL|macro|MIXCOM_WATCHDOG_OFFSET
mdefine_line|#define MIXCOM_WATCHDOG_OFFSET 0xc10
DECL|macro|MIXCOM_ID
mdefine_line|#define MIXCOM_ID 0x11
DECL|macro|FLASHCOM_WATCHDOG_OFFSET
mdefine_line|#define FLASHCOM_WATCHDOG_OFFSET 0x4
DECL|macro|FLASHCOM_ID
mdefine_line|#define FLASHCOM_ID 0x18
DECL|variable|mixcomwd_opened
r_static
r_int
r_int
id|mixcomwd_opened
suffix:semicolon
multiline_comment|/* long req&squot;d for setbit --RR */
DECL|variable|watchdog_port
r_static
r_int
id|watchdog_port
suffix:semicolon
DECL|variable|mixcomwd_timer_alive
r_static
r_int
id|mixcomwd_timer_alive
suffix:semicolon
DECL|variable|mixcomwd_timer
r_static
r_struct
id|timer_list
id|mixcomwd_timer
op_assign
id|TIMER_INITIALIZER
c_func
(paren
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|expect_close
r_static
r_char
id|expect_close
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
DECL|function|mixcomwd_ping
r_static
r_void
id|mixcomwd_ping
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|55
comma
id|watchdog_port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mixcomwd_timerfun
r_static
r_void
id|mixcomwd_timerfun
c_func
(paren
r_int
r_int
id|d
)paren
(brace
id|mixcomwd_ping
c_func
(paren
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|mixcomwd_timer
comma
id|jiffies
op_plus
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|mixcomwd_open
r_static
r_int
id|mixcomwd_open
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
id|mixcomwd_opened
)paren
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|mixcomwd_ping
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nowayout
)paren
(brace
multiline_comment|/*&n;&t;&t; * fops_get() code via open() has already done&n;&t;&t; * a try_module_get() so it is safe to do the&n;&t;&t; * __module_get().&n;&t;&t; */
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mixcomwd_timer_alive
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|mixcomwd_timer
)paren
suffix:semicolon
id|mixcomwd_timer_alive
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixcomwd_release
r_static
r_int
id|mixcomwd_release
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
r_if
c_cond
(paren
id|mixcomwd_timer_alive
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mixcomwd: release called while internal timer alive&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|mixcomwd_timer
)paren
suffix:semicolon
id|mixcomwd_timer.expires
op_assign
id|jiffies
op_plus
l_int|5
op_star
id|HZ
suffix:semicolon
id|mixcomwd_timer.function
op_assign
id|mixcomwd_timerfun
suffix:semicolon
id|mixcomwd_timer.data
op_assign
l_int|0
suffix:semicolon
id|mixcomwd_timer_alive
op_assign
l_int|1
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|mixcomwd_timer
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;mixcomwd: WDT device closed unexpectedly.  WDT will not stop!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|mixcomwd_opened
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
DECL|function|mixcomwd_write
r_static
id|ssize_t
id|mixcomwd_write
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
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
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
id|mixcomwd_ping
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|mixcomwd_ioctl
r_static
r_int
id|mixcomwd_ioctl
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
id|status
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
l_int|1
comma
dot
id|identity
op_assign
l_string|&quot;MixCOM watchdog&quot;
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
id|WDIOC_GETSTATUS
suffix:colon
id|status
op_assign
id|mixcomwd_opened
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
(brace
id|status
op_or_assign
id|mixcomwd_timer_alive
suffix:semicolon
)brace
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
id|status
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
r_break
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|mixcomwd_ping
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
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mixcomwd_fops
r_static
r_struct
id|file_operations
id|mixcomwd_fops
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
id|mixcomwd_write
comma
dot
id|ioctl
op_assign
id|mixcomwd_ioctl
comma
dot
id|open
op_assign
id|mixcomwd_open
comma
dot
id|release
op_assign
id|mixcomwd_release
comma
)brace
suffix:semicolon
DECL|variable|mixcomwd_miscdev
r_static
r_struct
id|miscdevice
id|mixcomwd_miscdev
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
id|mixcomwd_fops
comma
)brace
suffix:semicolon
DECL|function|mixcomwd_checkcard
r_static
r_int
id|__init
id|mixcomwd_checkcard
c_func
(paren
r_int
id|port
)paren
(brace
r_int
id|id
suffix:semicolon
id|port
op_add_assign
id|MIXCOM_WATCHDOG_OFFSET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|port
comma
l_int|1
comma
l_string|&quot;MixCOM watchdog&quot;
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|id
op_assign
id|inb_p
c_func
(paren
id|port
)paren
op_amp
l_int|0x3f
suffix:semicolon
r_if
c_cond
(paren
id|id
op_ne
id|MIXCOM_ID
)paren
(brace
id|release_region
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|port
suffix:semicolon
)brace
DECL|function|flashcom_checkcard
r_static
r_int
id|__init
id|flashcom_checkcard
c_func
(paren
r_int
id|port
)paren
(brace
r_int
id|id
suffix:semicolon
id|port
op_add_assign
id|FLASHCOM_WATCHDOG_OFFSET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|port
comma
l_int|1
comma
l_string|&quot;MixCOM watchdog&quot;
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|id
op_assign
id|inb_p
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_ne
id|FLASHCOM_ID
)paren
(brace
id|release_region
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|port
suffix:semicolon
)brace
DECL|function|mixcomwd_init
r_static
r_int
id|__init
id|mixcomwd_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|found
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
op_logical_neg
id|found
op_logical_and
id|mixcomwd_ioports
(braket
id|i
)braket
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|watchdog_port
op_assign
id|mixcomwd_checkcard
c_func
(paren
id|mixcomwd_ioports
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|watchdog_port
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* The FlashCOM card can be set up at 0x300 -&gt; 0x378, in 0x8 jumps */
r_for
c_loop
(paren
id|i
op_assign
l_int|0x300
suffix:semicolon
op_logical_neg
id|found
op_logical_and
id|i
OL
l_int|0x380
suffix:semicolon
id|i
op_add_assign
l_int|0x8
)paren
(brace
id|watchdog_port
op_assign
id|flashcom_checkcard
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|watchdog_port
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mixcomwd: No card detected, or port not available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|mixcomwd_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|release_region
c_func
(paren
id|watchdog_port
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;MixCOM watchdog driver v%s, watchdog port at 0x%3x&bslash;n&quot;
comma
id|VERSION
comma
id|watchdog_port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mixcomwd_exit
r_static
r_void
id|__exit
id|mixcomwd_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nowayout
)paren
(brace
r_if
c_cond
(paren
id|mixcomwd_timer_alive
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mixcomwd: I quit now, hardware will&quot;
l_string|&quot; probably reboot!&bslash;n&quot;
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|mixcomwd_timer
)paren
suffix:semicolon
id|mixcomwd_timer_alive
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|release_region
c_func
(paren
id|watchdog_port
comma
l_int|1
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|mixcomwd_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|mixcomwd_init
id|module_init
c_func
(paren
id|mixcomwd_init
)paren
suffix:semicolon
DECL|variable|mixcomwd_exit
id|module_exit
c_func
(paren
id|mixcomwd_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
