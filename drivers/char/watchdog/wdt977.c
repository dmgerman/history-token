multiline_comment|/*&n; *&t;Wdt977&t;0.02:&t;A Watchdog Device for Netwinder W83977AF chip&n; *&n; *&t;(c) Copyright 1998 Rebel.com (Woody Suwalski &lt;woody@netwinder.org&gt;)&n; *&n; *&t;&t;&t;-----------------------&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;&t;&t;-----------------------&n; *      14-Dec-2001 Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *           Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT&n; *&t;19-Dec-2001 Woody Suwalski: Netwinder fixes, ioctl interface&n; *&t;06-Jan-2002 Woody Suwalski: For compatibility, convert all timeouts&n; *&t;&t;&t;&t;    from minutes to seconds.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|WATCHDOG_MINOR
mdefine_line|#define WATCHDOG_MINOR&t;130
DECL|macro|DEFAULT_TIMEOUT
mdefine_line|#define&t;DEFAULT_TIMEOUT&t;1&t;/* default timeout = 1 minute */
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
id|DEFAULT_TIMEOUT
op_star
l_int|60
suffix:semicolon
multiline_comment|/* TO in seconds from user */
DECL|variable|timeoutM
r_static
r_int
id|timeoutM
op_assign
id|DEFAULT_TIMEOUT
suffix:semicolon
multiline_comment|/* timeout in minutes */
DECL|variable|timer_alive
r_static
r_int
r_int
id|timer_alive
suffix:semicolon
DECL|variable|testmode
r_static
r_int
id|testmode
suffix:semicolon
DECL|variable|expect_close
r_static
r_int
id|expect_close
op_assign
l_int|0
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
l_string|&quot;Watchdog timeout in seconds (60..15300), default=60&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|testmode
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|testmode
comma
l_string|&quot;Watchdog testmode (1 = no reboot), default=0&quot;
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
multiline_comment|/* This is kicking the watchdog by simply re-writing the timeout to reg. 0xF2 */
DECL|function|kick_wdog
r_static
r_int
id|kick_wdog
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;Refresh the timer.&n;&t; */
multiline_comment|/* unlock the SuperIO chip */
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
multiline_comment|/* select device Aux2 (device=8) and kicks watchdog reg F2 */
multiline_comment|/* F2 has the timeout in minutes */
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF2
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
id|timeoutM
comma
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* lock the SuperIO chip */
id|outb
c_func
(paren
l_int|0xAA
comma
l_int|0x370
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|wdt977_open
r_static
r_int
id|wdt977_open
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
multiline_comment|/* convert seconds to minutes, rounding up */
id|timeoutM
op_assign
id|timeout
op_plus
l_int|59
suffix:semicolon
id|timeoutM
op_div_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|nowayout
)paren
(brace
multiline_comment|/* do not permit disabling the watchdog by writing 0 to reg. 0xF2 */
r_if
c_cond
(paren
op_logical_neg
id|timeoutM
)paren
id|timeoutM
op_assign
id|DEFAULT_TIMEOUT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* we have a hw bug somewhere, so each 977 minute is actually only 30sec&n;&t;&t; *  this limits the max timeout to half of device max of 255 minutes...&n;&t;&t; */
id|timeoutM
op_add_assign
id|timeoutM
suffix:semicolon
)brace
multiline_comment|/* max timeout value = 255 minutes (0xFF). Write 0 to disable WatchDog. */
r_if
c_cond
(paren
id|timeoutM
OG
l_int|255
)paren
id|timeoutM
op_assign
l_int|255
suffix:semicolon
multiline_comment|/* convert seconds to minutes */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Wdt977 Watchdog activated: timeout = %d sec, nowayout = %i, testmode = %i.&bslash;n&quot;
comma
id|machine_is_netwinder
c_func
(paren
)paren
ques
c_cond
(paren
id|timeoutM
op_rshift
l_int|1
)paren
op_star
l_int|60
suffix:colon
id|timeoutM
op_star
l_int|60
comma
id|nowayout
comma
id|testmode
)paren
suffix:semicolon
multiline_comment|/* unlock the SuperIO chip */
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
multiline_comment|/* select device Aux2 (device=8) and set watchdog regs F2, F3 and F4&n;&t; * F2 has the timeout in minutes&n;&t; * F3 could be set to the POWER LED blink (with GP17 set to PowerLed)&n;&t; *   at timeout, and to reset timer on kbd/mouse activity (not impl.)&n;&t; * F4 is used to just clear the TIMEOUT&squot;ed state (bit 0)&n;&t; */
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF2
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
id|timeoutM
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF3
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* another setting is 0E for kbd/mouse/LED */
id|outb
c_func
(paren
l_int|0xF4
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* at last select device Aux1 (dev=7) and set GP16 as a watchdog output */
multiline_comment|/* in test mode watch the bit 1 on F4 to indicate &quot;triggered&quot; */
r_if
c_cond
(paren
op_logical_neg
id|testmode
)paren
(brace
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xE6
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0x371
)paren
suffix:semicolon
)brace
multiline_comment|/* lock the SuperIO chip */
id|outb
c_func
(paren
l_int|0xAA
comma
l_int|0x370
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wdt977_release
r_static
r_int
id|wdt977_release
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
op_logical_neg
id|nowayout
)paren
(brace
multiline_comment|/* unlock the SuperIO chip */
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
multiline_comment|/* select device Aux2 (device=8) and set watchdog regs F2,F3 and F4&n;&t;&t;* F3 is reset to its default state&n;&t;&t;* F4 can clear the TIMEOUT&squot;ed state (bit 0) - back to default&n;&t;&t;* We can not use GP17 as a PowerLed, as we use its usage as a RedLed&n;&t;&t;*/
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF2
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xFF
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF3
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF4
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF2
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* at last select device Aux1 (dev=7) and set GP16 as a watchdog output */
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xE6
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* lock the SuperIO chip */
id|outb
c_func
(paren
l_int|0xAA
comma
l_int|0x370
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|timer_alive
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Wdt977 Watchdog: shutdown&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;WDT device closed unexpectedly.  WDT will not stop!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *      wdt977_write:&n; *      @file: file handle to the watchdog&n; *      @buf: buffer to write (unused as data does not matter here&n; *      @count: count of bytes&n; *      @ppos: pointer to the position to write. No seeks allowed&n; *&n; *      A write to a watchdog device is defined as a keepalive signal. Any&n; *      write of data will do, as we we don&squot;t define content meaning.&n; */
DECL|function|wdt977_write
r_static
id|ssize_t
id|wdt977_write
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
l_int|1
suffix:semicolon
)brace
)brace
id|kick_wdog
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; *      wdt977_ioctl:&n; *      @inode: inode of the device&n; *      @file: file handle to the device&n; *      @cmd: watchdog command&n; *      @arg: argument pointer&n; *&n; *      The watchdog API defines a common set of functions for all watchdogs&n; *      according to their available features.&n; */
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
l_string|&quot;Winbond 83977&quot;
)brace
suffix:semicolon
DECL|function|wdt977_ioctl
r_static
r_int
id|wdt977_ioctl
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
id|temp
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
id|WDIOC_GETSTATUS
suffix:colon
multiline_comment|/* unlock the SuperIO chip */
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x87
comma
l_int|0x370
)paren
suffix:semicolon
multiline_comment|/* select device Aux2 (device=8) and read watchdog reg F4 */
id|outb
c_func
(paren
l_int|0x07
comma
l_int|0x370
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0x371
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xF4
comma
l_int|0x370
)paren
suffix:semicolon
id|temp
op_assign
id|inb
c_func
(paren
l_int|0x371
)paren
suffix:semicolon
multiline_comment|/* lock the SuperIO chip */
id|outb
c_func
(paren
l_int|0xAA
comma
l_int|0x370
)paren
suffix:semicolon
multiline_comment|/* return info if &quot;expired&quot; in test mode */
r_return
id|put_user
c_func
(paren
id|temp
op_amp
l_int|1
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
id|kick_wdog
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
id|temp
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
multiline_comment|/* convert seconds to minutes, rounding up */
id|temp
op_add_assign
l_int|59
suffix:semicolon
id|temp
op_div_assign
l_int|60
suffix:semicolon
multiline_comment|/* we have a hw bug somewhere, so each 977 minute is actually only 30sec&n;&t;&t;*  this limits the max timeout to half of device max of 255 minutes...&n;&t;&t;*/
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
(brace
id|temp
op_add_assign
id|temp
suffix:semicolon
)brace
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
id|temp
template_param
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|temp
op_logical_and
id|nowayout
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|timeoutM
op_assign
id|temp
suffix:semicolon
id|kick_wdog
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|wdt977_fops
r_static
r_struct
id|file_operations
id|wdt977_fops
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
id|wdt977_write
comma
dot
id|ioctl
op_assign
id|wdt977_ioctl
comma
dot
id|open
op_assign
id|wdt977_open
comma
dot
id|release
op_assign
id|wdt977_release
comma
)brace
suffix:semicolon
DECL|variable|wdt977_miscdev
r_static
r_struct
id|miscdevice
id|wdt977_miscdev
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
id|wdt977_fops
)brace
suffix:semicolon
DECL|function|nwwatchdog_init
r_static
r_int
id|__init
id|nwwatchdog_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|machine_is_netwinder
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|wdt977_miscdev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Wdt977 Watchdog sleeping.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nwwatchdog_exit
r_static
r_void
id|__exit
id|nwwatchdog_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|wdt977_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|nwwatchdog_init
id|module_init
c_func
(paren
id|nwwatchdog_init
)paren
suffix:semicolon
DECL|variable|nwwatchdog_exit
id|module_exit
c_func
(paren
id|nwwatchdog_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;W83977AF Watchdog driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
