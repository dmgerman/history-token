multiline_comment|/*&n; *&t;AMD Elan SC520 processor Watchdog Timer driver for Linux 2.4.x&n; *&n; *      Based on acquirewdt.c by Alan Cox,&n; *           and sbc60xxwdt.c by Jakob Oestergaard &lt;jakob@ostenfeld.dk&gt;&n; *     &n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;The authors do NOT admit liability nor provide warranty for &n; *&t;any of this software. This material is provided &quot;AS-IS&quot; in &n; *      the hope that it may be useful for others.&n; *&n; *&t;(c) Copyright 2001    Scott Jennings &lt;linuxdrivers@oro.net&gt;&n; *           9/27 - 2001      [Initial release]&n; *&t;&n; *&t;Additional fixes Alan Cox&n; *&t;-&t;Fixed formatting&n; *&t;-&t;Removed debug printks&n; *&t;-&t;Fixed SMP built kernel deadlock&n; *&t;-&t;Switched to private locks not lock_kernel&n; *&t;-&t;Used ioremap/writew/readw&n; *&t;-&t;Added NOWAYOUT support&n; *&n; *  Theory of operation:&n; *  A Watchdog Timer (WDT) is a hardware circuit that can &n; *  reset the computer system in case of a software fault.&n; *  You probably knew that already.&n; *&n; *  Usually a userspace daemon will notify the kernel WDT driver&n; *  via the /proc/watchdog special device file that userspace is&n; *  still alive, at regular intervals.  When such a notification&n; *  occurs, the driver will usually tell the hardware watchdog&n; *  that everything is in order, and that the watchdog should wait&n; *  for yet another little while to reset the system.&n; *  If userspace fails (RAM error, kernel bug, whatever), the&n; *  notifications cease to occur, and the hardware watchdog will&n; *  reset the system (causing a reboot) after the timeout occurs.&n; *&n; *  This WDT driver is different from most other Linux WDT&n; *  drivers in that the driver will ping the watchdog by itself,&n; *  because this particular WDT has a very short timeout (1.6&n; *  seconds) and it would be insane to count on any userspace&n; *  daemon always getting scheduled within that time frame.&n; *&n; *  This driver uses memory mapped IO, and spinlock.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
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
multiline_comment|/*&n; * The SC520 can timeout anywhere from 492us to 32.21s.&n; * If we reset the watchdog every ~250ms we should be safe.&n; */
DECL|macro|WDT_INTERVAL
mdefine_line|#define WDT_INTERVAL (HZ/4+1)
multiline_comment|/*&n; * We must not require too good response from the userspace daemon.&n; * Here we require the userspace daemon to send us a heartbeat&n; * char to /dev/watchdog every 30 seconds.&n; */
DECL|macro|WDT_HEARTBEAT
mdefine_line|#define WDT_HEARTBEAT (HZ * 30)
multiline_comment|/*&n; * AMD Elan SC520 timeout value is 492us times a power of 2 (0-7)&n; *&n; *   0: 492us    2: 1.01s    4: 4.03s   6: 16.22s&n; *   1: 503ms    3: 2.01s    5: 8.05s   7: 32.21s&n; */
DECL|macro|TIMEOUT_EXPONENT
mdefine_line|#define TIMEOUT_EXPONENT ( 1 &lt;&lt; 3 )  /* 0x08 = 2.01s */
multiline_comment|/* #define MMCR_BASE_DEFAULT 0xfffef000 */
DECL|macro|MMCR_BASE_DEFAULT
mdefine_line|#define MMCR_BASE_DEFAULT ((__u16 *)0xffffe)
DECL|macro|OFFS_WDTMRCTL
mdefine_line|#define OFFS_WDTMRCTL ((unsigned int)0xcb0)
DECL|macro|WDT_ENB
mdefine_line|#define WDT_ENB 0x8000&t;&t;/* [15] Watchdog Timer Enable */
DECL|macro|WDT_WRST_ENB
mdefine_line|#define WDT_WRST_ENB 0x4000&t;/* [14] Watchdog Timer Reset Enable */
DECL|macro|OUR_NAME
mdefine_line|#define OUR_NAME &quot;sc520_wdt&quot;
DECL|macro|WRT_DOG
mdefine_line|#define WRT_DOG(data) *wdtmrctl=data
DECL|variable|wdtmrctl
r_static
id|__u16
op_star
id|wdtmrctl
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
DECL|variable|wdt_spinlock
r_static
id|spinlock_t
id|wdt_spinlock
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
multiline_comment|/* Ping the WDT */
id|spin_lock
c_func
(paren
op_amp
id|wdt_spinlock
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0xAAAA
comma
id|wdtmrctl
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0x5555
comma
id|wdtmrctl
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|wdt_spinlock
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
DECL|function|wdt_config
r_static
r_void
id|wdt_config
c_func
(paren
r_int
id|writeval
)paren
(brace
id|__u16
id|dummy
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* buy some time (ping) */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|wdt_spinlock
comma
id|flags
)paren
suffix:semicolon
id|dummy
op_assign
id|readw
c_func
(paren
id|wdtmrctl
)paren
suffix:semicolon
multiline_comment|/* ensure write synchronization */
id|writew
c_func
(paren
l_int|0xAAAA
comma
id|wdtmrctl
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0x5555
comma
id|wdtmrctl
)paren
suffix:semicolon
multiline_comment|/* make WDT configuration register writable one time */
id|writew
c_func
(paren
l_int|0x3333
comma
id|wdtmrctl
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0xCCCC
comma
id|wdtmrctl
)paren
suffix:semicolon
multiline_comment|/* write WDT configuration register */
id|writew
c_func
(paren
id|writeval
comma
id|wdtmrctl
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|wdt_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
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
id|wdt_config
c_func
(paren
id|WDT_ENB
op_or
id|WDT_WRST_ENB
op_or
id|TIMEOUT_EXPONENT
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
r_if
c_cond
(paren
op_logical_neg
id|nowayout
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
id|wdt_config
c_func
(paren
l_int|0
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
multiline_comment|/* Good, fire up the show */
id|wdt_startup
c_func
(paren
)paren
suffix:semicolon
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
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|wdt_is_open
)paren
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
l_string|&quot;SC520&quot;
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
DECL|function|sc520_wdt_unload
r_static
r_void
id|__exit
id|sc520_wdt_unload
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
id|iounmap
c_func
(paren
id|wdtmrctl
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|wdt_notifier
)paren
suffix:semicolon
)brace
DECL|function|sc520_wdt_init
r_static
r_int
id|__init
id|sc520_wdt_init
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
r_int
r_int
id|cbar
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|wdt_spinlock
)paren
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
multiline_comment|/* get the Base Address Register */
id|cbar
op_assign
id|inl_p
c_func
(paren
l_int|0xfffc
)paren
suffix:semicolon
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: CBAR: 0x%08lx&bslash;n&quot;
comma
id|cbar
)paren
suffix:semicolon
multiline_comment|/* check if MMCR aliasing bit is set */
r_if
c_cond
(paren
id|cbar
op_amp
l_int|0x80000000
)paren
(brace
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: MMCR Aliasing enabled.&bslash;n&quot;
)paren
suffix:semicolon
id|wdtmrctl
op_assign
(paren
id|__u16
op_star
)paren
(paren
id|cbar
op_amp
l_int|0x3fffffff
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;!!! WARNING !!!&bslash;n&quot;
l_string|&quot;&bslash;t MMCR Aliasing found NOT enabled!&bslash;n&quot;
l_string|&quot;&bslash;t Using default value of: %p&bslash;n&quot;
l_string|&quot;&bslash;t This has not been tested!&bslash;n&quot;
l_string|&quot;&bslash;t Please email Scott Jennings &lt;smj@oro.net&gt;&bslash;n&quot;
l_string|&quot;&bslash;t  and Bill Jennings &lt;bj@oro.net&gt; if it works!&bslash;n&quot;
comma
id|MMCR_BASE_DEFAULT
)paren
suffix:semicolon
id|wdtmrctl
op_assign
id|MMCR_BASE_DEFAULT
suffix:semicolon
)brace
id|wdtmrctl
op_assign
(paren
id|__u16
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|wdtmrctl
op_plus
id|OFFS_WDTMRCTL
)paren
suffix:semicolon
id|wdtmrctl
op_assign
id|ioremap
c_func
(paren
(paren
r_int
r_int
)paren
id|wdtmrctl
comma
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|OUR_NAME
l_string|&quot;: WDT driver for SC520 initialised.&bslash;n&quot;
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
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|sc520_wdt_init
id|module_init
c_func
(paren
id|sc520_wdt_init
)paren
suffix:semicolon
DECL|variable|sc520_wdt_unload
id|module_exit
c_func
(paren
id|sc520_wdt_unload
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Scott and Bill Jennings&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for watchdog timer in AMD &bslash;&quot;Elan&bslash;&quot; SC520 uProcessor&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
