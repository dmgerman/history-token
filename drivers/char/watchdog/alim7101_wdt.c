multiline_comment|/*&n; *&t;ALi M7101 PMU Computer Watchdog Timer driver for Linux 2.4.x&n; *&n; *&t;Based on w83877f_wdt.c by Scott Jennings &lt;management@oro.net&gt;&n; *&t;and the Cobalt kernel WDT timer driver by Tim Hockin&n; *&t;                                      &lt;thockin@cobaltnet.com&gt;&n; *&n; *&t;(c)2002 Steve Hill &lt;steve@navaho.co.uk&gt;&n; * &n; *  Theory of operation:&n; *  A Watchdog Timer (WDT) is a hardware circuit that can &n; *  reset the computer system in case of a software fault.&n; *  You probably knew that already.&n; *&n; *  Usually a userspace daemon will notify the kernel WDT driver&n; *  via the /proc/watchdog special device file that userspace is&n; *  still alive, at regular intervals.  When such a notification&n; *  occurs, the driver will usually tell the hardware watchdog&n; *  that everything is in order, and that the watchdog should wait&n; *  for yet another little while to reset the system.&n; *  If userspace fails (RAM error, kernel bug, whatever), the&n; *  notifications cease to occur, and the hardware watchdog will&n; *  reset the system (causing a reboot) after the timeout occurs.&n; *&n; *  This WDT driver is different from most other Linux WDT&n; *  drivers in that the driver will ping the watchdog by itself,&n; *  because this particular WDT has a very short timeout (1.6&n; *  seconds) and it would be insane to count on any userspace&n; *  daemon always getting scheduled within that time frame.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|OUR_NAME
mdefine_line|#define OUR_NAME &quot;alim7101_wdt&quot;
DECL|macro|WDT_ENABLE
mdefine_line|#define WDT_ENABLE 0x9C
DECL|macro|WDT_DISABLE
mdefine_line|#define WDT_DISABLE 0x8C
DECL|macro|ALI_7101_WDT
mdefine_line|#define ALI_7101_WDT    0x92
DECL|macro|ALI_WDT_ARM
mdefine_line|#define ALI_WDT_ARM     0x01
multiline_comment|/*&n; * We&squot;re going to use a 1 second timeout.&n; * If we reset the watchdog every ~250ms we should be safe.  */
DECL|macro|WDT_INTERVAL
mdefine_line|#define WDT_INTERVAL (HZ/4+1)
multiline_comment|/*&n; * We must not require too good response from the userspace daemon.&n; * Here we require the userspace daemon to send us a heartbeat&n; * char to /dev/watchdog every 30 seconds.&n; */
DECL|macro|WDT_HEARTBEAT
mdefine_line|#define WDT_HEARTBEAT (HZ * 30)
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
DECL|variable|alim7101_pmu
r_static
r_struct
id|pci_dev
op_star
id|alim7101_pmu
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
r_char
id|tmp
suffix:semicolon
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
multiline_comment|/* Ping the WDT (this is actually a disarm/arm sequence) */
id|pci_read_config_byte
c_func
(paren
id|alim7101_pmu
comma
l_int|0x92
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|alim7101_pmu
comma
id|ALI_7101_WDT
comma
(paren
id|tmp
op_amp
op_complement
id|ALI_WDT_ARM
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|alim7101_pmu
comma
id|ALI_7101_WDT
comma
(paren
id|tmp
op_or
id|ALI_WDT_ARM
)paren
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
multiline_comment|/* &n; * Utility routines&n; */
DECL|function|wdt_change
r_static
r_void
id|wdt_change
c_func
(paren
r_int
id|writeval
)paren
(brace
r_char
id|tmp
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|alim7101_pmu
comma
l_int|0x92
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|writeval
op_eq
id|WDT_ENABLE
)paren
id|pci_write_config_byte
c_func
(paren
id|alim7101_pmu
comma
id|ALI_7101_WDT
comma
(paren
id|tmp
op_or
id|ALI_WDT_ARM
)paren
)paren
suffix:semicolon
r_else
id|pci_write_config_byte
c_func
(paren
id|alim7101_pmu
comma
id|ALI_7101_WDT
comma
(paren
id|tmp
op_amp
op_complement
id|ALI_WDT_ARM
)paren
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
multiline_comment|/* We must enable before we kick off the timer in case the timer&n;&t;   occurs as we ping it */
id|wdt_change
c_func
(paren
id|WDT_ENABLE
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
id|del_timer_sync
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|wdt_change
c_func
(paren
id|WDT_DISABLE
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
id|wdt_expect_close
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* someone wrote to us, we should restart timer */
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
suffix:semicolon
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
)paren
(brace
id|wdt_turnoff
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: device file closed unexpectedly. Will not stop the WDT!&bslash;n&quot;
)paren
suffix:semicolon
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
l_string|&quot;ALiM7101&quot;
)brace
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
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
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
id|wdt_turnoff
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
id|SYS_RESTART
)paren
(brace
multiline_comment|/*&n;&t;&t; * Cobalt devices have no way of rebooting themselves other than&n;&t;&t; * getting the watchdog to pull reset, so we restart the watchdog on&n;&t;&t; * reboot with no heartbeat&n;&t;&t; */
id|wdt_change
c_func
(paren
id|WDT_ENABLE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|OUR_NAME
l_string|&quot;: Watchdog timer is now enabled with no heartbeat - should reboot in ~1 second.&bslash;n&quot;
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
l_int|0
comma
dot
id|priority
op_assign
l_int|0
)brace
suffix:semicolon
DECL|function|alim7101_wdt_unload
r_static
r_void
id|__exit
id|alim7101_wdt_unload
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
)brace
DECL|function|alim7101_wdt_init
r_static
r_int
id|__init
id|alim7101_wdt_init
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
r_struct
id|pci_dev
op_star
id|ali1543_south
suffix:semicolon
r_char
id|tmp
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|OUR_NAME
l_string|&quot;: Steve Hill &lt;steve@navaho.co.uk&gt;.&bslash;n&quot;
)paren
suffix:semicolon
id|alim7101_pmu
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M7101
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alim7101_pmu
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|OUR_NAME
l_string|&quot;: ALi M7101 PMU not present - WDT not set&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* Set the WDT in the PMU to 1 second */
id|pci_write_config_byte
c_func
(paren
id|alim7101_pmu
comma
id|ALI_7101_WDT
comma
l_int|0x02
)paren
suffix:semicolon
id|ali1543_south
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M1533
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ali1543_south
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|OUR_NAME
l_string|&quot;: ALi 1543 South-Bridge not present - WDT not set&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|ali1543_south
comma
l_int|0x5e
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_amp
l_int|0x1e
)paren
op_ne
l_int|0x12
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|OUR_NAME
l_string|&quot;: ALi 1543 South-Bridge does not have the correct revision number (???1001?) - WDT not set&bslash;n&quot;
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
id|timer
)paren
suffix:semicolon
id|timer.function
op_assign
id|wdt_timer_ping
suffix:semicolon
id|timer.data
op_assign
l_int|1
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
r_return
id|rc
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
(brace
id|misc_deregister
c_func
(paren
op_amp
id|wdt_miscdev
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|OUR_NAME
l_string|&quot;: WDT driver for ALi M7101 initialised.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|alim7101_wdt_init
id|module_init
c_func
(paren
id|alim7101_wdt_init
)paren
suffix:semicolon
DECL|variable|alim7101_wdt_unload
id|module_exit
c_func
(paren
id|alim7101_wdt_unload
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Steve Hill&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
