multiline_comment|/*&n; *&t;Eurotech CPU-1220/1410 on board WDT driver for Linux 2.4.x&n; *&n; *&t;(c) Copyright 2001 Ascensit &lt;support@ascensit.com&gt;&n; *&t;(c) Copyright 2001 Rodolfo Giometti &lt;giometti@ascensit.com&gt;&n; *&n; *&t;Based on wdt.c.&n; *&t;Original copyright messages:&n; *&n; *      (c) Copyright 1996-1997 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *                              http://www.redhat.com&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *      Neither Alan Cox nor CymruNet Ltd. admit liability nor provide&n; *      warranty for any of this software. This material is provided&n; *      &quot;AS-IS&quot; and at no charge.&n; *&n; *      (c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;*&n; *&n; *      14-Dec-2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *          Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT&n; *          Added timeout module option to override default&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|variable|eurwdt_is_open
r_static
r_int
id|eurwdt_is_open
suffix:semicolon
DECL|variable|eurwdt_lock
r_static
id|spinlock_t
id|eurwdt_lock
suffix:semicolon
multiline_comment|/*&n; *      You must set these - there is no sane way to probe for this board.&n; *      You can use wdt=x,y to set these now.&n; */
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x3f0
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|10
suffix:semicolon
DECL|variable|ev
r_static
r_char
op_star
id|ev
op_assign
l_string|&quot;int&quot;
suffix:semicolon
DECL|macro|WDT_TIMEOUT
mdefine_line|#define WDT_TIMEOUT&t;&t;60                /* 1 minute */
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
id|WDT_TIMEOUT
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|timeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|timeout
comma
l_string|&quot;Eurotech WDT timeout in seconds (default=60)&quot;
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
multiline_comment|/*&n; * Some symbolic names &n; */
DECL|macro|WDT_CTRL_REG
mdefine_line|#define WDT_CTRL_REG&t;&t;0x30
DECL|macro|WDT_OUTPIN_CFG
mdefine_line|#define WDT_OUTPIN_CFG&t;&t;0xe2
DECL|macro|WDT_EVENT_INT
mdefine_line|#define WDT_EVENT_INT&t;   0x00
DECL|macro|WDT_EVENT_REBOOT
mdefine_line|#define WDT_EVENT_REBOOT&t;   0x08
DECL|macro|WDT_UNIT_SEL
mdefine_line|#define WDT_UNIT_SEL&t;&t;0xf1
DECL|macro|WDT_UNIT_SECS
mdefine_line|#define WDT_UNIT_SECS&t;   0x80
DECL|macro|WDT_TIMEOUT_VAL
mdefine_line|#define WDT_TIMEOUT_VAL&t;&t;0xf2
DECL|macro|WDT_TIMER_CFG
mdefine_line|#define WDT_TIMER_CFG&t;&t;0xf3
macro_line|#ifndef MODULE
multiline_comment|/**&n; *      eurwdt_setup:&n; *      @str: command line string&n; *&n; *      Setup options. The board isn&squot;t really probe-able so we have to&n; *      get the user to tell us the configuration. Sane people build it&n; *      modular but the others come here.&n; */
DECL|function|eurwdt_setup
r_static
r_int
id|__init
id|eurwdt_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|ints
(braket
l_int|4
)braket
suffix:semicolon
id|str
op_assign
id|get_options
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|0
)paren
(brace
id|io
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|1
)paren
id|irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;wdt=&quot;
comma
id|eurwdt_setup
)paren
suffix:semicolon
macro_line|#endif /* !MODULE */
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;Eurotech WDT io port (default=0x3f0)&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;Eurotech WDT irq (default=10)&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ev
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ev
comma
l_string|&quot;Eurotech WDT event type (default is `reboot&squot;)&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *      Programming support&n; */
DECL|function|eurwdt_validate_timeout
r_static
r_void
id|__init
id|eurwdt_validate_timeout
c_func
(paren
r_void
)paren
(brace
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
id|WDT_TIMEOUT
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;eurwdt: timeout must be 0 &lt; x &lt; 255, using %d&bslash;n&quot;
comma
id|timeout
)paren
suffix:semicolon
)brace
)brace
DECL|function|eurwdt_write_reg
r_static
r_inline
r_void
id|eurwdt_write_reg
c_func
(paren
id|u8
id|index
comma
id|u8
id|data
)paren
(brace
id|outb
c_func
(paren
id|index
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|io
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|eurwdt_lock_chip
r_static
r_inline
r_void
id|eurwdt_lock_chip
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0xaa
comma
id|io
)paren
suffix:semicolon
)brace
DECL|function|eurwdt_unlock_chip
r_static
r_inline
r_void
id|eurwdt_unlock_chip
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0x55
comma
id|io
)paren
suffix:semicolon
id|eurwdt_write_reg
c_func
(paren
l_int|0x07
comma
l_int|0x08
)paren
suffix:semicolon
multiline_comment|/* set the logical device */
)brace
DECL|function|eurwdt_set_timeout
r_static
r_inline
r_void
id|eurwdt_set_timeout
c_func
(paren
r_int
id|timeout
)paren
(brace
id|eurwdt_write_reg
c_func
(paren
id|WDT_TIMEOUT_VAL
comma
(paren
id|u8
)paren
id|timeout
)paren
suffix:semicolon
)brace
DECL|function|eurwdt_disable_timer
r_static
r_inline
r_void
id|eurwdt_disable_timer
c_func
(paren
r_void
)paren
(brace
id|eurwdt_set_timeout
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|eurwdt_activate_timer
r_static
r_void
id|eurwdt_activate_timer
c_func
(paren
r_void
)paren
(brace
id|eurwdt_disable_timer
c_func
(paren
)paren
suffix:semicolon
id|eurwdt_write_reg
c_func
(paren
id|WDT_CTRL_REG
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* activate the WDT */
id|eurwdt_write_reg
c_func
(paren
id|WDT_OUTPIN_CFG
comma
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;int&quot;
comma
id|ev
)paren
ques
c_cond
id|WDT_EVENT_INT
suffix:colon
id|WDT_EVENT_REBOOT
)paren
suffix:semicolon
multiline_comment|/* Setting interrupt line */
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
op_logical_or
id|irq
OG
l_int|15
op_logical_or
id|irq
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;: invalid irq number&bslash;n&quot;
)paren
suffix:semicolon
id|irq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* if invalid we disable interrupt */
)brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;: interrupt disabled&bslash;n&quot;
)paren
suffix:semicolon
id|eurwdt_write_reg
c_func
(paren
id|WDT_TIMER_CFG
comma
id|irq
op_lshift
l_int|4
)paren
suffix:semicolon
id|eurwdt_write_reg
c_func
(paren
id|WDT_UNIT_SEL
comma
id|WDT_UNIT_SECS
)paren
suffix:semicolon
multiline_comment|/* we use seconds */
id|eurwdt_set_timeout
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* the default timeout */
)brace
multiline_comment|/*&n; *      Kernel methods.&n; */
DECL|function|eurwdt_interrupt
r_void
id|eurwdt_interrupt
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
l_string|&quot;timeout WDT timeout&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef ONLY_TESTING
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Would Reboot.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Initiating system reboot.&bslash;n&quot;
)paren
suffix:semicolon
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/**&n; *      eurwdt_ping:&n; *&n; *      Reload counter one with the watchdog timeout.&n; */
DECL|function|eurwdt_ping
r_static
r_void
id|eurwdt_ping
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Write the watchdog default value */
id|eurwdt_set_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *      eurwdt_write:&n; *      @file: file handle to the watchdog&n; *      @buf: buffer to write (unused as data does not matter here&n; *      @count: count of bytes&n; *      @ppos: pointer to the position to write. No seeks allowed&n; *&n; *      A write to a watchdog device is defined as a keepalive signal. Any&n; *      write of data will do, as we we don&squot;t define content meaning.&n; */
DECL|function|eurwdt_write
r_static
id|ssize_t
id|eurwdt_write
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
id|eurwdt_ping
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* the default timeout */
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      eurwdt_ioctl:&n; *      @inode: inode of the device&n; *      @file: file handle to the device&n; *      @cmd: watchdog command&n; *      @arg: argument pointer&n; *&n; *      The watchdog API defines a common set of functions for all watchdogs&n; *      according to their available features.&n; */
DECL|function|eurwdt_ioctl
r_static
r_int
id|eurwdt_ioctl
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
id|options
suffix:colon
id|WDIOF_CARDRESET
comma
id|firmware_version
suffix:colon
l_int|1
comma
id|identity
suffix:colon
l_string|&quot;WDT Eurotech CPU-1220/1410&quot;
)brace
suffix:semicolon
r_int
id|time
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
r_return
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
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
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
id|eurwdt_ping
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
id|copy_from_user
c_func
(paren
op_amp
id|time
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
id|time
template_param
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|timeout
op_assign
id|time
suffix:semicolon
id|eurwdt_set_timeout
c_func
(paren
id|time
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *      eurwdt_open:&n; *      @inode: inode of device&n; *      @file: file handle to device&n; *&n; *      The misc device has been opened. The watchdog device is single&n; *      open and on opening we load the counter.&n; */
DECL|function|eurwdt_open
r_static
r_int
id|eurwdt_open
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
id|spin_lock
c_func
(paren
op_amp
id|eurwdt_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eurwdt_is_open
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|eurwdt_lock
)paren
suffix:semicolon
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
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
id|eurwdt_is_open
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Activate the WDT */
id|eurwdt_activate_timer
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|eurwdt_lock
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|TEMP_MINOR
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *      eurwdt_release:&n; *      @inode: inode to board&n; *      @file: file handle to board&n; *&n; *      The watchdog has a configurable API. There is a religious dispute&n; *      between people who want their watchdog to be able to shut down and&n; *      those who want to be sure if the watchdog manager dies the machine&n; *      reboots. In the former case we disable the counters, in the latter&n; *      case you have to open it again very soon.&n; */
DECL|function|eurwdt_release
r_static
r_int
id|eurwdt_release
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
id|eurwdt_disable_timer
c_func
(paren
)paren
suffix:semicolon
)brace
id|eurwdt_is_open
op_assign
l_int|0
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      eurwdt_notify_sys:&n; *      @this: our notifier block&n; *      @code: the event being reported&n; *      @unused: unused&n; *&n; *      Our notifier is called on system shutdowns. We want to turn the card&n; *      off at reboot otherwise the machine will reboot again during memory&n; *      test or worse yet during the following fsck. This would suck, in fact&n; *      trust me - if it happens it does suck.&n; */
DECL|function|eurwdt_notify_sys
r_static
r_int
id|eurwdt_notify_sys
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
multiline_comment|/* Turn the card off */
id|eurwdt_disable_timer
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *      Kernel Interfaces&n; */
DECL|variable|eurwdt_fops
r_static
r_struct
id|file_operations
id|eurwdt_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|no_llseek
comma
id|write
suffix:colon
id|eurwdt_write
comma
id|ioctl
suffix:colon
id|eurwdt_ioctl
comma
id|open
suffix:colon
id|eurwdt_open
comma
id|release
suffix:colon
id|eurwdt_release
comma
)brace
suffix:semicolon
DECL|variable|eurwdt_miscdev
r_static
r_struct
id|miscdevice
id|eurwdt_miscdev
op_assign
(brace
id|WATCHDOG_MINOR
comma
l_string|&quot;watchdog&quot;
comma
op_amp
id|eurwdt_fops
)brace
suffix:semicolon
multiline_comment|/*&n; *      The WDT card needs to learn about soft shutdowns in order to&n; *      turn the timebomb registers off.&n; */
DECL|variable|eurwdt_notifier
r_static
r_struct
id|notifier_block
id|eurwdt_notifier
op_assign
(brace
id|eurwdt_notify_sys
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/**&n; *      cleanup_module:&n; *&n; *      Unload the watchdog. You cannot do this with any file handles open.&n; *      If your watchdog is set to continue ticking on close and you unload&n; *      it, well it keeps ticking. We won&squot;t get the interrupt but the board&n; *      will not touch PC memory so all is fine. You just have to load a new&n; *      module in 60 seconds or reboot.&n; */
DECL|function|eurwdt_exit
r_static
r_void
id|__exit
id|eurwdt_exit
c_func
(paren
r_void
)paren
(brace
id|eurwdt_lock_chip
c_func
(paren
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|eurwdt_miscdev
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|eurwdt_notifier
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *      eurwdt_init:&n; *&n; *      Set up the WDT watchdog board. After grabbing the resources &n; *      we require we need also to unlock the device.&n; *      The open() function will actually kick the board off.&n; */
DECL|function|eurwdt_init
r_static
r_int
id|__init
id|eurwdt_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|eurwdt_validate_timeout
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|eurwdt_miscdev
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
l_string|&quot;eurwdt: can&squot;t misc_register on minor=%d&bslash;n&quot;
comma
id|WATCHDOG_MINOR
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|request_irq
c_func
(paren
id|irq
comma
id|eurwdt_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;eurwdt&quot;
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;eurwdt: IRQ %d is not free.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_goto
id|outmisc
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
l_int|2
comma
l_string|&quot;eurwdt&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;eurwdt: IO %X is not free.&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|outirq
suffix:semicolon
)brace
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|eurwdt_notifier
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
l_string|&quot;eurwdt: can&squot;t register reboot notifier (err=%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|outreg
suffix:semicolon
)brace
id|eurwdt_unlock_chip
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Eurotech WDT driver 0.01 at %X (Interrupt %d)&quot;
l_string|&quot; - timeout event: %s&bslash;n&quot;
comma
id|io
comma
id|irq
comma
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;int&quot;
comma
id|ev
)paren
ques
c_cond
l_string|&quot;int&quot;
suffix:colon
l_string|&quot;reboot&quot;
)paren
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|eurwdt_lock
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
id|outreg
suffix:colon
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
id|outirq
suffix:colon
id|free_irq
c_func
(paren
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
id|outmisc
suffix:colon
id|misc_deregister
c_func
(paren
op_amp
id|eurwdt_miscdev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|eurwdt_init
id|module_init
c_func
(paren
id|eurwdt_init
)paren
suffix:semicolon
DECL|variable|eurwdt_exit
id|module_exit
c_func
(paren
id|eurwdt_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Rodolfo Giometti&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for Eurotech CPU-1220/1410 on board watchdog&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
