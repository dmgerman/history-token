multiline_comment|/*&n; *&t;60xx Single Board Computer Watchdog Timer driver for Linux 2.2.x&n; *&n; *      Based on acquirewdt.c by Alan Cox.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;The author does NOT admit liability nor provide warranty for&n; *&t;any of this software. This material is provided &quot;AS-IS&quot; in&n; *&t;the hope that it may be useful for others.&n; *&n; *&t;(c) Copyright 2000    Jakob Oestergaard &lt;jakob@unthought.net&gt;&n; *&n; *           12/4 - 2000      [Initial revision]&n; *           25/4 - 2000      Added /dev/watchdog support&n; *           09/5 - 2001      [smj@oro.net] fixed fop_write to &quot;return 1&quot; on success&n; *           12/4 - 2002      [rob@osinvestor.com] eliminate fop_read&n; *                            fix possible wdt_is_open race&n; *                            add CONFIG_WATCHDOG_NOWAYOUT support&n; *                            remove lock_kernel/unlock_kernel pairs&n; *                            added KERN_* to printk&squot;s&n; *                            got rid of extraneous comments&n; *                            changed watchdog_info to correctly reflect what the driver offers&n; *                            added WDIOC_GETSTATUS, WDIOC_GETBOOTSTATUS, WDIOC_SETTIMEOUT,&n; *                            WDIOC_GETTIMEOUT, and WDIOC_SETOPTIONS ioctls&n; *           09/8 - 2003      [wim@iguana.be] cleanup of trailing spaces&n; *                            use module_param&n; *                            made timeout (the emulated heartbeat) a module_param&n; *                            made the keepalive ping an internal subroutine&n; *                            made wdt_stop and wdt_start module params&n; *                            added extra printk&squot;s for startup problems&n; *                            added MODULE_AUTHOR and MODULE_DESCRIPTION info&n; *&n; *&n; *  This WDT driver is different from the other Linux WDT&n; *  drivers in the following ways:&n; *  *)  The driver will ping the watchdog by itself, because this&n; *      particular WDT has a very short timeout (one second) and it&n; *      would be insane to count on any userspace daemon always&n; *      getting scheduled within that time frame.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
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
DECL|macro|PFX
mdefine_line|#define PFX OUR_NAME &quot;: &quot;
multiline_comment|/*&n; * You must set these - The driver cannot probe for the settings&n; */
DECL|variable|wdt_stop
r_static
r_int
id|wdt_stop
op_assign
l_int|0x45
suffix:semicolon
id|module_param
c_func
(paren
id|wdt_stop
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|wdt_stop
comma
l_string|&quot;SBC60xx WDT &squot;stop&squot; io port (default 0x45)&quot;
)paren
suffix:semicolon
DECL|variable|wdt_start
r_static
r_int
id|wdt_start
op_assign
l_int|0x443
suffix:semicolon
id|module_param
c_func
(paren
id|wdt_start
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|wdt_start
comma
l_string|&quot;SBC60xx WDT &squot;start&squot; io port (default 0x443)&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * The 60xx board can use watchdog timeout values from one second&n; * to several minutes.  The default is one second, so if we reset&n; * the watchdog every ~250ms we should be safe.&n; */
DECL|macro|WDT_INTERVAL
mdefine_line|#define WDT_INTERVAL (HZ/4+1)
multiline_comment|/*&n; * We must not require too good response from the userspace daemon.&n; * Here we require the userspace daemon to send us a heartbeat&n; * char to /dev/watchdog every 30 seconds.&n; * If the daemon pulses us every 25 seconds, we can still afford&n; * a 5 second scheduling delay on the (high priority) daemon. That&n; * should be sufficient for a box under any load.&n; */
DECL|macro|WATCHDOG_TIMEOUT
mdefine_line|#define WATCHDOG_TIMEOUT 30&t;&t;/* 30 sec default timeout */
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
id|WATCHDOG_TIMEOUT
suffix:semicolon
multiline_comment|/* in seconds, will be multiplied by HZ to get seconds to wait for a ping */
id|module_param
c_func
(paren
id|timeout
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|timeout
comma
l_string|&quot;Watchdog timeout in seconds. (1&lt;=timeout&lt;=3600, default=&quot;
id|__MODULE_STRING
c_func
(paren
id|WATCHDOG_TIMEOUT
)paren
l_string|&quot;)&quot;
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
r_int
id|wdt_is_open
suffix:semicolon
DECL|variable|wdt_expect_close
r_static
r_char
id|wdt_expect_close
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
multiline_comment|/* If we got a heartbeat pulse within the WDT_US_INTERVAL&n;&t; * we agree to ping the WDT&n;&t; */
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
multiline_comment|/* Ping the WDT by reading from wdt_start */
id|inb_p
c_func
(paren
id|wdt_start
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
id|KERN_WARNING
id|PFX
l_string|&quot;Heartbeat lost! Will not ping the watchdog&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Utility routines&n; */
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
(paren
id|timeout
op_star
id|HZ
)paren
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
id|KERN_INFO
id|PFX
l_string|&quot;Watchdog timer is now enabled.&bslash;n&quot;
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
id|wdt_stop
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Watchdog timer is now disabled...&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|wdt_keepalive
r_static
r_void
id|wdt_keepalive
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* user land ping */
id|next_heartbeat
op_assign
id|jiffies
op_plus
(paren
id|timeout
op_star
id|HZ
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
id|__user
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
multiline_comment|/* See if we got the magic character &squot;V&squot; and reload the timer */
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
id|ofs
suffix:semicolon
multiline_comment|/* note: just in case someone wrote the magic character&n;&t;&t;&t; * five months ago... */
id|wdt_expect_close
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* scan to see whether or not we got the magic character */
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
l_int|42
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Well, anyhow someone wrote to us, we should return that favour */
id|wdt_keepalive
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|count
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
id|nonseekable_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
multiline_comment|/* Just in case we&squot;re already talking to someone... */
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|wdt_is_open
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
multiline_comment|/* Good, fire up the show */
id|wdt_startup
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
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
id|wdt_expect_close
op_eq
l_int|42
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
id|KERN_CRIT
id|PFX
l_string|&quot;device file closed unexpectedly. Will not stop the WDT!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|wdt_is_open
)paren
suffix:semicolon
id|wdt_expect_close
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
id|options
op_assign
id|WDIOF_KEEPALIVEPING
op_or
id|WDIOF_SETTIMEOUT
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
l_string|&quot;SBC60xx&quot;
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
id|ENOIOCTLCMD
suffix:semicolon
r_case
id|WDIOC_GETSUPPORT
suffix:colon
r_return
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
ques
op_minus
id|EFAULT
suffix:colon
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
id|p
)paren
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|wdt_keepalive
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_SETOPTIONS
suffix:colon
(brace
r_int
id|new_options
comma
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|new_options
comma
id|p
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
id|new_options
op_amp
id|WDIOS_DISABLECARD
)paren
(brace
id|wdt_turnoff
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_options
op_amp
id|WDIOS_ENABLECARD
)paren
(brace
id|wdt_startup
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
r_case
id|WDIOC_SETTIMEOUT
suffix:colon
(brace
r_int
id|new_timeout
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|new_timeout
comma
id|p
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
id|new_timeout
template_param
l_int|3600
)paren
(brace
multiline_comment|/* arbitrary upper limit */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|timeout
op_assign
id|new_timeout
suffix:semicolon
id|wdt_keepalive
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fall through */
)brace
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|timeout
comma
id|p
)paren
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
comma
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
multiline_comment|/*&n; *&t;The WDT needs to learn about soft shutdowns in order to&n; *&t;turn the timebomb registers off.&n; */
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
r_if
c_cond
(paren
(paren
id|wdt_stop
op_ne
l_int|0x45
)paren
op_logical_and
(paren
id|wdt_stop
op_ne
id|wdt_start
)paren
)paren
id|release_region
c_func
(paren
id|wdt_stop
comma
l_int|1
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|wdt_start
comma
l_int|1
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|timeout
template_param
l_int|3600
)paren
multiline_comment|/* arbitrary upper limit */
(brace
id|timeout
op_assign
id|WATCHDOG_TIMEOUT
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;timeout value must be 1&lt;=x&lt;=3600, using %d&bslash;n&quot;
comma
id|timeout
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|wdt_start
comma
l_int|1
comma
l_string|&quot;SBC 60XX WDT&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;I/O address 0x%04x already in use&bslash;n&quot;
comma
id|wdt_start
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
multiline_comment|/* We cannot reserve 0x45 - the kernel already has! */
r_if
c_cond
(paren
(paren
id|wdt_stop
op_ne
l_int|0x45
)paren
op_logical_and
(paren
id|wdt_stop
op_ne
id|wdt_start
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|wdt_stop
comma
l_int|1
comma
l_string|&quot;SBC 60XX WDT&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;I/O address 0x%04x already in use&bslash;n&quot;
comma
id|wdt_stop
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out_region1
suffix:semicolon
)brace
)brace
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register miscdev on minor=%d (err=%d)&bslash;n&quot;
comma
id|wdt_miscdev.minor
comma
id|rc
)paren
suffix:semicolon
r_goto
id|err_out_region2
suffix:semicolon
)brace
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register reboot notifier (err=%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|err_out_miscdev
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;WDT driver for 60XX single board computer initialised. timeout=%d sec (nowayout=%d)&bslash;n&quot;
comma
id|timeout
comma
id|nowayout
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
r_if
c_cond
(paren
(paren
id|wdt_stop
op_ne
l_int|0x45
)paren
op_logical_and
(paren
id|wdt_stop
op_ne
id|wdt_start
)paren
)paren
id|release_region
c_func
(paren
id|wdt_stop
comma
l_int|1
)paren
suffix:semicolon
id|err_out_region1
suffix:colon
id|release_region
c_func
(paren
id|wdt_start
comma
l_int|1
)paren
suffix:semicolon
id|err_out
suffix:colon
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
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jakob Oestergaard &lt;jakob@unthought.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;60xx Single Board Computer Watchdog Timer driver&quot;
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
eof
