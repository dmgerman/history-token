multiline_comment|/*&n; *&t;Intel 21285 watchdog driver&n; *&t;Copyright (c) Phil Blundell &lt;pb@nexus.co.uk&gt;, 1998&n; *&n; *&t;based on&n; *&n; *&t;SoftDog&t;0.05:&t;A Software Watchdog Device&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
multiline_comment|/*&n; * Define this to stop the watchdog actually rebooting the machine.&n; */
DECL|macro|ONLY_TESTING
macro_line|#undef ONLY_TESTING
DECL|variable|soft_margin
r_static
r_int
r_int
id|soft_margin
op_assign
l_int|60
suffix:semicolon
multiline_comment|/* in seconds */
DECL|variable|reload
r_static
r_int
r_int
id|reload
suffix:semicolon
DECL|variable|timer_alive
r_static
r_int
r_int
id|timer_alive
suffix:semicolon
macro_line|#ifdef ONLY_TESTING
multiline_comment|/*&n; *&t;If the timer expires..&n; */
DECL|function|watchdog_fire
r_static
r_void
id|watchdog_fire
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Watchdog: Would Reboot.&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|CSR_TIMER4_CNTL
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_TIMER4_CLR
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Refresh the timer.&n; */
DECL|function|watchdog_ping
r_static
r_void
id|watchdog_ping
c_func
(paren
r_void
)paren
(brace
op_star
id|CSR_TIMER4_LOAD
op_assign
id|reload
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|watchdog_open
r_static
r_int
id|watchdog_open
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
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_star
id|CSR_SA110_CNTL
op_amp
(paren
l_int|1
op_lshift
l_int|13
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|1
comma
op_amp
id|timer_alive
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|reload
op_assign
id|soft_margin
op_star
(paren
id|mem_fclk_21285
op_div
l_int|256
)paren
suffix:semicolon
op_star
id|CSR_TIMER4_CLR
op_assign
l_int|0
suffix:semicolon
id|watchdog_ping
c_func
(paren
)paren
suffix:semicolon
op_star
id|CSR_TIMER4_CNTL
op_assign
id|TIMER_CNTL_ENABLE
op_or
id|TIMER_CNTL_AUTORELOAD
op_or
id|TIMER_CNTL_DIV256
suffix:semicolon
macro_line|#ifdef ONLY_TESTING
id|ret
op_assign
id|request_irq
c_func
(paren
id|IRQ_TIMER4
comma
id|watchdog_fire
comma
l_int|0
comma
l_string|&quot;watchdog&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
op_star
id|CSR_TIMER4_CNTL
op_assign
l_int|0
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|1
comma
op_amp
id|timer_alive
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n;&t; * Setting this bit is irreversible; once enabled, there is&n;&t; * no way to disable the watchdog.&n;&t; */
op_star
id|CSR_SA110_CNTL
op_or_assign
l_int|1
op_lshift
l_int|13
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Shut off the timer.&n; *&t;Note: if we really have enabled the watchdog, there&n; *&t;is no way to turn off.&n; */
DECL|function|watchdog_release
r_static
r_int
id|watchdog_release
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
macro_line|#ifdef ONLY_TESTING
id|free_irq
c_func
(paren
id|IRQ_TIMER4
comma
l_int|NULL
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|1
comma
op_amp
id|timer_alive
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|watchdog_write
id|watchdog_write
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
multiline_comment|/* Can&squot;t seek (pwrite) on this device  */
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
id|watchdog_ping
c_func
(paren
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|ident
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
comma
dot
id|identity
op_assign
l_string|&quot;Footbridge Watchdog&quot;
)brace
suffix:semicolon
r_static
r_int
DECL|function|watchdog_ioctl
id|watchdog_ioctl
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
r_int
id|new_margin
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOIOCTLCMD
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
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
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
id|ret
op_assign
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
id|ret
op_assign
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
r_break
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|watchdog_ping
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_SETTIMEOUT
suffix:colon
id|ret
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
multiline_comment|/* Arbitrary, can&squot;t find the card&squot;s limits */
r_if
c_cond
(paren
id|new_margin
template_param
l_int|60
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|soft_margin
op_assign
id|new_margin
suffix:semicolon
id|reload
op_assign
id|soft_margin
op_star
(paren
id|mem_fclk_21285
op_div
l_int|256
)paren
suffix:semicolon
id|watchdog_ping
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fall */
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
id|ret
op_assign
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
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|watchdog_fops
r_static
r_struct
id|file_operations
id|watchdog_fops
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
id|watchdog_write
comma
dot
id|ioctl
op_assign
id|watchdog_ioctl
comma
dot
id|open
op_assign
id|watchdog_open
comma
dot
id|release
op_assign
id|watchdog_release
comma
)brace
suffix:semicolon
DECL|variable|watchdog_miscdev
r_static
r_struct
id|miscdevice
id|watchdog_miscdev
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
id|watchdog_fops
)brace
suffix:semicolon
DECL|function|footbridge_watchdog_init
r_static
r_int
id|__init
id|footbridge_watchdog_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|retval
op_assign
id|misc_register
c_func
(paren
op_amp
id|watchdog_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Footbridge Watchdog Timer: 0.01, timer margin: %d sec&bslash;n&quot;
comma
id|soft_margin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_cats
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: Watchdog reset may not work on this machine.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|footbridge_watchdog_exit
r_static
r_void
id|__exit
id|footbridge_watchdog_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|watchdog_miscdev
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Phil Blundell &lt;pb@nexus.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Footbridge watchdog driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
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
id|MODULE_PARM_DESC
c_func
(paren
id|soft_margin
comma
l_string|&quot;Watchdog timeout in seconds&quot;
)paren
suffix:semicolon
DECL|variable|footbridge_watchdog_init
id|module_init
c_func
(paren
id|footbridge_watchdog_init
)paren
suffix:semicolon
DECL|variable|footbridge_watchdog_exit
id|module_exit
c_func
(paren
id|footbridge_watchdog_exit
)paren
suffix:semicolon
eof
