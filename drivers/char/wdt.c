multiline_comment|/*&n; *&t;Industrial Computer Source WDT500/501 driver for Linux 2.1.x&n; *&n; *&t;(c) Copyright 1996-1997 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.redhat.com&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide &n; *&t;warranty for any of this software. This material is provided &n; *&t;&quot;AS-IS&quot; and at no charge.&t;&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; *&t;Release 0.08.&n; *&n; *&t;Fixes&n; *&t;&t;Dave Gregorich&t;:&t;Modularisation and minor bugs&n; *&t;&t;Alan Cox&t;:&t;Added the watchdog ioctl() stuff&n; *&t;&t;Alan Cox&t;:&t;Fixed the reboot problem (as noted by&n; *&t;&t;&t;&t;&t;Matt Crocker).&n; *&t;&t;Alan Cox&t;:&t;Added wdt= boot option&n; *&t;&t;Alan Cox&t;:&t;Cleaned up copy/user stuff&n; *&t;&t;Tim Hockin&t;:&t;Added insmod parameters, comment cleanup&n; *&t;&t;&t;&t;&t;Parameterized timeout&n; *&t;&t;Tigran Aivazian&t;:&t;Restructured wdt_init() to handle failures&n; */
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
macro_line|#include &quot;wd501p.h&quot;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|wdt_is_open
r_static
r_int
id|wdt_is_open
suffix:semicolon
multiline_comment|/*&n; *&t;You must set these - there is no sane way to probe for this board.&n; *&t;You can use wdt=x,y to set these now.&n; */
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x240
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|11
suffix:semicolon
DECL|macro|WD_TIMO
mdefine_line|#define WD_TIMO (100*60)&t;&t;/* 1 minute */
macro_line|#ifndef MODULE
multiline_comment|/**&n; *&t;wdt_setup:&n; *&t;@str: command line string&n; *&n; *&t;Setup options. The board isn&squot;t really probe-able so we have to&n; *&t;get the user to tell us the configuration. Sane people build it &n; *&t;modular but the others come here.&n; */
DECL|function|wdt_setup
r_static
r_int
id|__init
id|wdt_setup
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
(brace
id|irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
)brace
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
id|wdt_setup
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
l_string|&quot;WDT io port (default=0x240)&quot;
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
l_string|&quot;WDT irq (default=11)&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Programming support&n; */
DECL|function|wdt_ctr_mode
r_static
r_void
id|wdt_ctr_mode
c_func
(paren
r_int
id|ctr
comma
r_int
id|mode
)paren
(brace
id|ctr
op_lshift_assign
l_int|6
suffix:semicolon
id|ctr
op_or_assign
l_int|0x30
suffix:semicolon
id|ctr
op_or_assign
(paren
id|mode
op_lshift
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ctr
comma
id|WDT_CR
)paren
suffix:semicolon
)brace
DECL|function|wdt_ctr_load
r_static
r_void
id|wdt_ctr_load
c_func
(paren
r_int
id|ctr
comma
r_int
id|val
)paren
(brace
id|outb_p
c_func
(paren
id|val
op_amp
l_int|0xFF
comma
id|WDT_COUNT0
op_plus
id|ctr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_rshift
l_int|8
comma
id|WDT_COUNT0
op_plus
id|ctr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Kernel methods.&n; */
multiline_comment|/**&n; *&t;wdt_status:&n; *&t;&n; *&t;Extract the status information from a WDT watchdog device. There are&n; *&t;several board variants so we have to know which bits are valid. Some&n; *&t;bits default to one and some to zero in order to be maximally painful.&n; *&n; *&t;we then map the bits onto the status ioctl flags.&n; */
DECL|function|wdt_status
r_static
r_int
id|wdt_status
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;Status register to bit flags&n;&t; */
r_int
id|flag
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|status
op_assign
id|inb_p
c_func
(paren
id|WDT_SR
)paren
suffix:semicolon
id|status
op_or_assign
id|FEATUREMAP1
suffix:semicolon
id|status
op_and_assign
op_complement
id|FEATUREMAP2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_TGOOD
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_OVERHEAT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUOVER
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_POWEROVER
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUUNDR
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_POWERUNDER
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_FANGOOD
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_FANFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|WDC_SR_ISOI0
)paren
(brace
id|flag
op_or_assign
id|WDIOF_EXTERN1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|WDC_SR_ISII1
)paren
(brace
id|flag
op_or_assign
id|WDIOF_EXTERN2
suffix:semicolon
)brace
r_return
id|flag
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdt_interrupt:&n; *&t;@irq:&t;&t;Interrupt number&n; *&t;@dev_id:&t;Unused as we don&squot;t allow multiple devices.&n; *&t;@regs:&t;&t;Unused.&n; *&n; *&t;Handle an interrupt from the board. These are raised when the status&n; *&t;map changes in what the board considers an interesting way. That means&n; *&t;a failure condition occuring.&n; */
DECL|function|wdt_interrupt
r_void
id|wdt_interrupt
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
multiline_comment|/*&n;&t; *&t;Read the status register see what is up and&n;&t; *&t;then printk it. &n;&t; */
r_int
r_char
id|status
op_assign
id|inb_p
c_func
(paren
id|WDT_SR
)paren
suffix:semicolon
id|status
op_or_assign
id|FEATUREMAP1
suffix:semicolon
id|status
op_and_assign
op_complement
id|FEATUREMAP2
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;WDT status %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_TGOOD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Overheat alarm.(%d)&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|WDT_RT
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUOVER
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;PSU over voltage.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUUNDR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;PSU under voltage.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_FANGOOD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Possible fan fault.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_WCCR
)paren
)paren
(brace
macro_line|#ifdef SOFTWARE_REBOOT
macro_line|#ifdef ONLY_TESTING
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Would Reboot.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#else&t;&t;
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
macro_line|#endif&t;&t;
macro_line|#else
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Reset in 5ms.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;&t;
)brace
multiline_comment|/**&n; *&t;wdt_ping:&n; *&n; *&t;Reload counter one with the watchdog timeout. We don&squot;t bother reloading&n; *&t;the cascade counter. &n; */
DECL|function|wdt_ping
r_static
r_void
id|wdt_ping
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Write a watchdog value */
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
id|wdt_ctr_mode
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|wdt_ctr_load
c_func
(paren
l_int|1
comma
id|WD_TIMO
)paren
suffix:semicolon
multiline_comment|/* Timeout */
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_DC
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;wdt_write:&n; *&t;@file: file handle to the watchdog&n; *&t;@buf: buffer to write (unused as data does not matter here &n; *&t;@count: count of bytes&n; *&t;@ppos: pointer to the position to write. No seeks allowed&n; *&n; *&t;A write to a watchdog device is defined as a keepalive signal. Any&n; *&t;write of data will do, as we we don&squot;t define content meaning.&n; */
DECL|function|wdt_write
r_static
id|ssize_t
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
id|wdt_ping
c_func
(paren
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
multiline_comment|/**&n; *&t;wdt_read:&n; *&t;@file: file handle to the watchdog board&n; *&t;@buf: buffer to write 1 byte into&n; *&t;@count: length of buffer&n; *&t;@ptr: offset (no seek allowed)&n; *&n; *&t;Read reports the temperature in degrees Fahrenheit. The API is in&n; *&t;farenheit. It was designed by an imperial measurement luddite.&n; */
DECL|function|wdt_read
r_static
id|ssize_t
id|wdt_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ptr
)paren
(brace
r_int
r_int
id|c
op_assign
id|inb_p
c_func
(paren
id|WDT_RT
)paren
suffix:semicolon
r_int
r_char
id|cp
suffix:semicolon
multiline_comment|/*  Can&squot;t seek (pread) on this device  */
r_if
c_cond
(paren
id|ptr
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|TEMP_MINOR
suffix:colon
id|c
op_mul_assign
l_int|11
suffix:semicolon
id|c
op_div_assign
l_int|15
suffix:semicolon
id|cp
op_assign
id|c
op_plus
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|cp
comma
l_int|1
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;wdt_ioctl:&n; *&t;@inode: inode of the device&n; *&t;@file: file handle to the device&n; *&t;@cmd: watchdog command&n; *&t;@arg: argument pointer&n; *&n; *&t;The watchdog API defines a common set of functions for all watchdogs&n; *&t;according to their available features. We only actually usefully support&n; *&t;querying capabilities and current status. &n; */
DECL|function|wdt_ioctl
r_static
r_int
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
r_static
r_struct
id|watchdog_info
id|ident
op_assign
(brace
id|WDIOF_OVERHEAT
op_or
id|WDIOF_POWERUNDER
op_or
id|WDIOF_POWEROVER
op_or
id|WDIOF_EXTERN1
op_or
id|WDIOF_EXTERN2
op_or
id|WDIOF_FANFAULT
comma
l_int|1
comma
l_string|&quot;WDT500/501&quot;
)brace
suffix:semicolon
id|ident.options
op_and_assign
id|WDT_OPTION_MASK
suffix:semicolon
multiline_comment|/* Mask down to the card we have */
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
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_return
id|put_user
c_func
(paren
id|wdt_status
c_func
(paren
)paren
comma
(paren
r_int
op_star
)paren
id|arg
)paren
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
id|wdt_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;wdt_open:&n; *&t;@inode: inode of device&n; *&t;@file: file handle to device&n; *&n; *&t;One of our two misc devices has been opened. The watchdog device is&n; *&t;single open and on opening we load the counters. Counter zero is a &n; *&t;100Hz cascade, into counter 1 which downcounts to reboot. When the&n; *&t;counter triggers counter 2 downcounts the length of the reset pulse&n; *&t;which set set to be as long as possible. &n; */
DECL|function|wdt_open
r_static
r_int
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
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|WATCHDOG_MINOR
suffix:colon
r_if
c_cond
(paren
id|wdt_is_open
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *&t;Activate &n;&t;&t;&t; */
id|wdt_is_open
op_assign
l_int|1
suffix:semicolon
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable */
id|wdt_ctr_mode
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
id|wdt_ctr_mode
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|wdt_ctr_mode
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
id|wdt_ctr_load
c_func
(paren
l_int|0
comma
l_int|8948
)paren
suffix:semicolon
multiline_comment|/* count at 100Hz */
id|wdt_ctr_load
c_func
(paren
l_int|1
comma
id|WD_TIMO
)paren
suffix:semicolon
multiline_comment|/* Timeout 120 seconds */
id|wdt_ctr_load
c_func
(paren
l_int|2
comma
l_int|65535
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Enable */
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
multiline_comment|/**&n; *&t;wdt_close:&n; *&t;@inode: inode to board&n; *&t;@file: file handle to board&n; *&n; *&t;The watchdog has a configurable API. There is a religious dispute &n; *&t;between people who want their watchdog to be able to shut down and &n; *&t;those who want to be sure if the watchdog manager dies the machine&n; *&t;reboots. In the former case we disable the counters, in the latter&n; *&t;case you have to open it again very soon.&n; */
DECL|function|wdt_release
r_static
r_int
id|wdt_release
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_eq
id|WATCHDOG_MINOR
)paren
(brace
macro_line|#ifndef CONFIG_WATCHDOG_NOWAYOUT&t;
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable counters */
id|wdt_ctr_load
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 0 length reset pulses now */
macro_line|#endif&t;&t;
id|wdt_is_open
op_assign
l_int|0
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;notify_sys:&n; *&t;@this: our notifier block&n; *&t;@code: the event being reported&n; *&t;@unused: unused&n; *&n; *&t;Our notifier is called on system shutdowns. We want to turn the card&n; *&t;off at reboot otherwise the machine will reboot again during memory&n; *&t;test or worse yet during the following fsck. This would suck, in fact&n; *&t;trust me - if it happens it does suck.&n; */
DECL|function|wdt_notify_sys
r_static
r_int
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
multiline_comment|/* Turn the card off */
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
id|wdt_ctr_load
c_func
(paren
l_int|2
comma
l_int|0
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
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|no_llseek
comma
id|read
suffix:colon
id|wdt_read
comma
id|write
suffix:colon
id|wdt_write
comma
id|ioctl
suffix:colon
id|wdt_ioctl
comma
id|open
suffix:colon
id|wdt_open
comma
id|release
suffix:colon
id|wdt_release
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
id|WATCHDOG_MINOR
comma
l_string|&quot;watchdog&quot;
comma
op_amp
id|wdt_fops
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501
DECL|variable|temp_miscdev
r_static
r_struct
id|miscdevice
id|temp_miscdev
op_assign
(brace
id|TEMP_MINOR
comma
l_string|&quot;temperature&quot;
comma
op_amp
id|wdt_fops
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;The WDT card needs to learn about soft shutdowns in order to&n; *&t;turn the timebomb registers off. &n; */
DECL|variable|wdt_notifier
r_static
r_struct
id|notifier_block
id|wdt_notifier
op_assign
(brace
id|wdt_notify_sys
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;cleanup_module:&n; *&n; *&t;Unload the watchdog. You cannot do this with any file handles open.&n; *&t;If your watchdog is set to continue ticking on close and you unload&n; *&t;it, well it keeps ticking. We won&squot;t get the interrupt but the board&n; *&t;will not touch PC memory so all is fine. You just have to load a new&n; *&t;module in 60 seconds or reboot.&n; */
DECL|function|wdt_exit
r_static
r_void
id|__exit
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
macro_line|#ifdef CONFIG_WDT_501&t;
id|misc_deregister
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
macro_line|#endif&t;
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
id|io
comma
l_int|8
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
multiline_comment|/**&n; * &t;wdt_init:&n; *&n; *&t;Set up the WDT watchdog board. All we have to do is grab the&n; *&t;resources we require and bitch if anyone beat us to them.&n; *&t;The open() function will actually kick the board off.&n; */
DECL|function|wdt_init
r_static
r_int
id|__init
id|wdt_init
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
id|wdt_miscdev
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
l_string|&quot;wdt: can&squot;t misc_register on minor=%d&bslash;n&quot;
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
id|wdt_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;wdt501p&quot;
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
l_string|&quot;wdt: IRQ %d is not free.&bslash;n&quot;
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
l_int|8
comma
l_string|&quot;wdt501p&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;wdt: IO %X is not free.&bslash;n&quot;
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
id|wdt_notifier
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
l_string|&quot;wdt: can&squot;t register reboot notifier (err=%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|outreg
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_WDT_501
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|temp_miscdev
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
l_string|&quot;wdt: can&squot;t misc_register (temp) on minor=%d&bslash;n&quot;
comma
id|TEMP_MINOR
)paren
suffix:semicolon
r_goto
id|outrbt
suffix:semicolon
)brace
macro_line|#endif
id|ret
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;WDT500/501-P driver 0.07 at %X (Interrupt %d)&bslash;n&quot;
comma
id|io
comma
id|irq
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501
id|outrbt
suffix:colon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wdt_notifier
)paren
suffix:semicolon
macro_line|#endif
id|outreg
suffix:colon
id|release_region
c_func
(paren
id|io
comma
l_int|8
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
id|wdt_miscdev
)paren
suffix:semicolon
r_goto
id|out
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
eof
