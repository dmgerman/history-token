multiline_comment|/*&n; *&t;60xx Single Board Computer Watchdog Timer driver for Linux 2.2.x&n; *&n; *      Based on acquirewdt.c by Alan Cox.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;The author does NOT admit liability nor provide warranty for &n; *&t;any of this software. This material is provided &quot;AS-IS&quot; in &n; *      the hope that it may be useful for others.&n; *&n; *&t;(c) Copyright 2000    Jakob Oestergaard &lt;jakob@ostenfeld.dk&gt;&n; *&n; *           12/4 - 2000      [Initial revision]&n; *           25/4 - 2000      Added /dev/watchdog support&n; *           09/5 - 2001      [smj@oro.net] fixed fop_write to &quot;return 1&quot; on success&n; *&n; *&n; *  Theory of operation:&n; *  A Watchdog Timer (WDT) is a hardware circuit that can &n; *  reset the computer system in case of a software fault.&n; *  You probably knew that already.&n; *&n; *  Usually a userspace daemon will notify the kernel WDT driver&n; *  via the /proc/watchdog special device file that userspace is&n; *  still alive, at regular intervals.  When such a notification&n; *  occurs, the driver will usually tell the hardware watchdog&n; *  that everything is in order, and that the watchdog should wait&n; *  for yet another little while to reset the system.&n; *  If userspace fails (RAM error, kernel bug, whatever), the&n; *  notifications cease to occur, and the hardware watchdog will&n; *  reset the system (causing a reboot) after the timeout occurs.&n; *&n; *  This WDT driver is different from the other Linux WDT &n; *  drivers in several ways:&n; *  *)  The driver will ping the watchdog by itself, because this&n; *      particular WDT has a very short timeout (one second) and it&n; *      would be insane to count on any userspace daemon always&n; *      getting scheduled within that time frame.&n; *  *)  This driver expects the userspace daemon to send a specific&n; *      character code (&squot;V&squot;) to /dev/watchdog before closing the&n; *      /dev/watchdog file.  If the userspace daemon closes the file&n; *      without sending this special character, the driver will assume&n; *      that the daemon (and userspace in general) died, and will&n; *      stop pinging the WDT without disabling it first.  This will&n; *      cause a reboot.&n; *&n; *  Why `V&squot; ?  Well, `V&squot; is the character in ASCII for the value 86,&n; *  and we all know that 86 is _the_ most random number in the universe.&n; *  Therefore it is the letter that has the slightest chance of occurring&n; *  by chance, when the system becomes corrupted.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
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
DECL|macro|OUR_NAME
mdefine_line|#define OUR_NAME &quot;sbc60xxwdt&quot;
multiline_comment|/*&n; * You must set these - The driver cannot probe for the settings&n; */
DECL|macro|WDT_STOP
mdefine_line|#define WDT_STOP 0x45
DECL|macro|WDT_START
mdefine_line|#define WDT_START 0x443
multiline_comment|/*&n; * The 60xx board can use watchdog timeout values from one second&n; * to several minutes.  The default is one second, so if we reset&n; * the watchdog every ~250ms we should be safe.&n; */
DECL|macro|WDT_INTERVAL
mdefine_line|#define WDT_INTERVAL (HZ/4+1)
multiline_comment|/*&n; * We must not require too good response from the userspace daemon.&n; * Here we require the userspace daemon to send us a heartbeat&n; * char to /dev/watchdog every 10 seconds.&n; * If the daemon pulses us every 5 seconds, we can still afford&n; * a 5 second scheduling delay on the (high priority) daemon. That&n; * should be sufficient for a box under any load.&n; */
DECL|macro|WDT_HEARTBEAT
mdefine_line|#define WDT_HEARTBEAT (HZ * 10)
r_static
r_void
id|wdt_timer_ping
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|variable|timer
r_static
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|variable|next_heartbeat
r_static
r_int
r_int
id|next_heartbeat
suffix:semicolon
DECL|variable|wdt_is_open
r_static
r_int
id|wdt_is_open
suffix:semicolon
DECL|variable|wdt_expect_close
r_static
r_int
id|wdt_expect_close
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
multiline_comment|/*&n; *&t;Whack the dog&n; */
DECL|function|wdt_timer_ping
r_static
r_void
id|wdt_timer_ping
c_func
(paren
r_int
r_int
id|data
)paren
(brace
multiline_comment|/* If we got a heartbeat pulse within the WDT_US_INTERVAL&n;&t; * we agree to ping the WDT &n;&t; */
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|next_heartbeat
)paren
)paren
(brace
multiline_comment|/* Ping the WDT by reading from WDT_START */
id|inb_p
c_func
(paren
id|WDT_START
)paren
suffix:semicolon
multiline_comment|/* Re-set the timer interval */
id|timer.expires
op_assign
id|jiffies
op_plus
id|WDT_INTERVAL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: Heartbeat lost! Will not ping the watchdog&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * Utility routines&n; */
DECL|function|wdt_startup
r_static
r_void
id|wdt_startup
c_func
(paren
r_void
)paren
(brace
id|next_heartbeat
op_assign
id|jiffies
op_plus
id|WDT_HEARTBEAT
suffix:semicolon
multiline_comment|/* Start the timer */
id|timer.expires
op_assign
id|jiffies
op_plus
id|WDT_INTERVAL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: Watchdog timer is now enabled.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|wdt_turnoff
r_static
r_void
id|wdt_turnoff
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Stop the timer */
id|del_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|WDT_STOP
)paren
suffix:semicolon
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: Watchdog timer is now disabled...&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * /dev/watchdog handling&n; */
DECL|function|fop_write
r_static
id|ssize_t
id|fop_write
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
multiline_comment|/* We can&squot;t seek */
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
multiline_comment|/* See if we got the magic character */
r_if
c_cond
(paren
id|count
)paren
(brace
r_int
id|ofs
suffix:semicolon
multiline_comment|/* note: just in case someone wrote the magic character&n;&t;&t; * five months ago... */
id|wdt_expect_close
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* now scan */
r_for
c_loop
(paren
id|ofs
op_assign
l_int|0
suffix:semicolon
id|ofs
op_ne
id|count
suffix:semicolon
id|ofs
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
id|ofs
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;V&squot;
)paren
(brace
id|wdt_expect_close
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Well, anyhow someone wrote to us, we should return that favour */
id|next_heartbeat
op_assign
id|jiffies
op_plus
id|WDT_HEARTBEAT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fop_read
r_static
id|ssize_t
id|fop_read
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
id|ppos
)paren
(brace
multiline_comment|/* No can do */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|fop_open
r_static
r_int
id|fop_open
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
multiline_comment|/* Just in case we&squot;re already talking to someone... */
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
r_if
c_cond
(paren
id|nowayout
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* Good, fire up the show */
id|wdt_is_open
op_assign
l_int|1
suffix:semicolon
id|wdt_startup
c_func
(paren
)paren
suffix:semicolon
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
DECL|function|fop_close
r_static
r_int
id|fop_close
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
id|wdt_expect_close
op_logical_and
op_logical_neg
id|nowayout
)paren
(brace
id|wdt_turnoff
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|del_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: device file closed unexpectedly. Will not stop the WDT!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|wdt_is_open
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fop_ioctl
r_static
r_int
id|fop_ioctl
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
dot
id|options
op_assign
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
l_string|&quot;SB60xx&quot;
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
id|WDIOC_KEEPALIVE
suffix:colon
id|next_heartbeat
op_assign
id|jiffies
op_plus
id|WDT_HEARTBEAT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
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
id|read
op_assign
id|fop_read
comma
dot
id|write
op_assign
id|fop_write
comma
dot
id|open
op_assign
id|fop_open
comma
dot
id|release
op_assign
id|fop_close
comma
dot
id|ioctl
op_assign
id|fop_ioctl
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
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Notifier for system down&n; */
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
id|wdt_turnoff
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The WDT needs to learn about soft shutdowns in order to&n; *&t;turn the timebomb registers off. &n; */
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
)brace
suffix:semicolon
DECL|function|sbc60xxwdt_unload
r_static
r_void
id|__exit
id|sbc60xxwdt_unload
c_func
(paren
r_void
)paren
(brace
id|wdt_turnoff
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Deregister */
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
id|WDT_START
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|//&t;release_region(WDT_STOP,1);
)brace
DECL|function|sbc60xxwdt_init
r_static
r_int
id|__init
id|sbc60xxwdt_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
singleline_comment|//&t;We cannot reserve 0x45 - the kernel already has!
singleline_comment|//&t;if (!request_region(WDT_STOP, 1, &quot;SBC 60XX WDT&quot;))
singleline_comment|//&t;&t;goto err_out;
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|WDT_START
comma
l_int|1
comma
l_string|&quot;SBC 60XX WDT&quot;
)paren
)paren
r_goto
id|err_out_region1
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|timer.function
op_assign
id|wdt_timer_ping
suffix:semicolon
id|timer.data
op_assign
l_int|0
suffix:semicolon
id|rc
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
id|rc
)paren
r_goto
id|err_out_region2
suffix:semicolon
id|rc
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
id|rc
)paren
r_goto
id|err_out_miscdev
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|OUR_NAME
l_string|&quot;: WDT driver for 60XX single board computer initialised.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_miscdev
suffix:colon
id|misc_deregister
c_func
(paren
op_amp
id|wdt_miscdev
)paren
suffix:semicolon
id|err_out_region2
suffix:colon
id|release_region
c_func
(paren
id|WDT_START
comma
l_int|1
)paren
suffix:semicolon
id|err_out_region1
suffix:colon
id|release_region
c_func
(paren
id|WDT_STOP
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* err_out: */
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|sbc60xxwdt_init
id|module_init
c_func
(paren
id|sbc60xxwdt_init
)paren
suffix:semicolon
DECL|variable|sbc60xxwdt_unload
id|module_exit
c_func
(paren
id|sbc60xxwdt_unload
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
