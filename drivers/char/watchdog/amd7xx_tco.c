multiline_comment|/*&n; *&t;AMD 766/768 TCO Timer Driver&n; *&t;(c) Copyright 2002 Zwane Mwaikambo &lt;zwane@holomorphy.com&gt;&n; *&t;All Rights Reserved.&n; *&n; *&t;Parts from;&n; *&t;Hardware driver for the AMD 768 Random Number Generator (RNG)&n; *&t;(c) Copyright 2001 Red Hat Inc &lt;alan@redhat.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License version 2&n; *&t;as published by the Free Software Foundation.&n; *&n; *&t;The author(s) of this software shall not be held liable for damages&n; *&t;of any nature resulting due to the use of this software. This&n; *&t;software is provided AS-IS with no warranties.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|AMDTCO_MODULE_VER
mdefine_line|#define AMDTCO_MODULE_VER&t;&quot;build 20021116&quot;
DECL|macro|AMDTCO_MODULE_NAME
mdefine_line|#define AMDTCO_MODULE_NAME&t;&quot;amd7xx_tco&quot;
DECL|macro|PFX
mdefine_line|#define PFX&t;&t;&t;AMDTCO_MODULE_NAME &quot;: &quot;
DECL|macro|MAX_TIMEOUT
mdefine_line|#define&t;MAX_TIMEOUT&t;38&t;/* max of 38 seconds, although the system will only&n;&t;&t;&t;&t; * reset itself after the second timeout */
multiline_comment|/* pmbase registers */
DECL|macro|TCO_RELOAD_REG
mdefine_line|#define TCO_RELOAD_REG&t;0x40&t;&t;/* bits 0-5 are current count, 6-7 are reserved */
DECL|macro|TCO_INITVAL_REG
mdefine_line|#define TCO_INITVAL_REG&t;0x41&t;&t;/* bits 0-5 are value to load, 6-7 are reserved */
DECL|macro|TCO_TIMEOUT_MASK
mdefine_line|#define TCO_TIMEOUT_MASK&t;0x3f
DECL|macro|TCO_STATUS1_REG
mdefine_line|#define TCO_STATUS1_REG 0x44
DECL|macro|TCO_STATUS2_REG
mdefine_line|#define TCO_STATUS2_REG&t;0x46
DECL|macro|NDTO_STS2
mdefine_line|#define NDTO_STS2&t;(1 &lt;&lt; 1)&t;/* we&squot;re interested in the second timeout */
DECL|macro|BOOT_STS
mdefine_line|#define BOOT_STS&t;(1 &lt;&lt; 2)&t;/* will be set if NDTO_STS2 was set before reboot */
DECL|macro|TCO_CTRL1_REG
mdefine_line|#define TCO_CTRL1_REG&t;0x48
DECL|macro|TCO_HALT
mdefine_line|#define TCO_HALT&t;(1 &lt;&lt; 11)
DECL|macro|NO_REBOOT
mdefine_line|#define NO_REBOOT&t;(1 &lt;&lt; 10)&t;/* in DevB:3x48 */
DECL|variable|__initdata
r_static
r_char
id|banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
id|PFX
id|AMDTCO_MODULE_VER
l_string|&quot;&bslash;n&quot;
suffix:semicolon
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
id|MAX_TIMEOUT
suffix:semicolon
DECL|variable|pmbase
r_static
id|u32
id|pmbase
suffix:semicolon
multiline_comment|/* PMxx I/O base */
DECL|variable|dev
r_static
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|variable|open_sem
r_static
r_struct
id|semaphore
id|open_sem
suffix:semicolon
DECL|variable|amdtco_lock
r_static
id|spinlock_t
id|amdtco_lock
suffix:semicolon
multiline_comment|/* only for device access */
DECL|variable|expect_close
r_static
r_char
id|expect_close
suffix:semicolon
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
l_string|&quot;range is 0-38 seconds, default is 38&quot;
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
DECL|function|seconds_to_ticks
r_static
r_inline
id|u8
id|seconds_to_ticks
c_func
(paren
r_int
id|seconds
)paren
(brace
multiline_comment|/* the internal timer is stored as ticks which decrement&n;&t; * every 0.6 seconds */
r_return
(paren
id|seconds
op_star
l_int|10
)paren
op_div
l_int|6
suffix:semicolon
)brace
DECL|function|ticks_to_seconds
r_static
r_inline
r_int
id|ticks_to_seconds
c_func
(paren
id|u8
id|ticks
)paren
(brace
r_return
(paren
id|ticks
op_star
l_int|6
)paren
op_div
l_int|10
suffix:semicolon
)brace
DECL|function|amdtco_status
r_static
r_inline
r_int
id|amdtco_status
c_func
(paren
r_void
)paren
(brace
id|u16
id|reg
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|reg
op_assign
id|inb
c_func
(paren
id|pmbase
op_plus
id|TCO_CTRL1_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reg
op_amp
id|TCO_HALT
)paren
op_eq
l_int|0
)paren
id|status
op_or_assign
id|WDIOF_KEEPALIVEPING
suffix:semicolon
id|reg
op_assign
id|inb
c_func
(paren
id|pmbase
op_plus
id|TCO_STATUS2_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
id|BOOT_STS
)paren
id|status
op_or_assign
id|WDIOF_CARDRESET
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|amdtco_ping
r_static
r_inline
r_void
id|amdtco_ping
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|1
comma
id|pmbase
op_plus
id|TCO_RELOAD_REG
)paren
suffix:semicolon
)brace
DECL|function|amdtco_gettimeout
r_static
r_inline
r_int
id|amdtco_gettimeout
c_func
(paren
r_void
)paren
(brace
id|u8
id|reg
op_assign
id|inb
c_func
(paren
id|pmbase
op_plus
id|TCO_RELOAD_REG
)paren
op_amp
id|TCO_TIMEOUT_MASK
suffix:semicolon
r_return
id|ticks_to_seconds
c_func
(paren
id|reg
)paren
suffix:semicolon
)brace
DECL|function|amdtco_settimeout
r_static
r_inline
r_void
id|amdtco_settimeout
c_func
(paren
r_int
r_int
id|timeout
)paren
(brace
id|u8
id|reg
op_assign
id|seconds_to_ticks
c_func
(paren
id|timeout
)paren
op_amp
id|TCO_TIMEOUT_MASK
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|pmbase
op_plus
id|TCO_INITVAL_REG
)paren
suffix:semicolon
)brace
DECL|function|amdtco_global_enable
r_static
r_inline
r_void
id|amdtco_global_enable
c_func
(paren
r_void
)paren
(brace
id|u16
id|reg
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|amdtco_lock
)paren
suffix:semicolon
multiline_comment|/* clear NO_REBOOT on DevB:3x48 p97 */
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|reg
)paren
suffix:semicolon
id|reg
op_and_assign
op_complement
id|NO_REBOOT
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|amdtco_lock
)paren
suffix:semicolon
)brace
DECL|function|amdtco_enable
r_static
r_inline
r_void
id|amdtco_enable
c_func
(paren
r_void
)paren
(brace
id|u16
id|reg
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|amdtco_lock
)paren
suffix:semicolon
id|reg
op_assign
id|inw
c_func
(paren
id|pmbase
op_plus
id|TCO_CTRL1_REG
)paren
suffix:semicolon
id|reg
op_and_assign
op_complement
id|TCO_HALT
suffix:semicolon
id|outw
c_func
(paren
id|reg
comma
id|pmbase
op_plus
id|TCO_CTRL1_REG
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|amdtco_lock
)paren
suffix:semicolon
)brace
DECL|function|amdtco_disable
r_static
r_inline
r_void
id|amdtco_disable
c_func
(paren
r_void
)paren
(brace
id|u16
id|reg
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|amdtco_lock
)paren
suffix:semicolon
id|reg
op_assign
id|inw
c_func
(paren
id|pmbase
op_plus
id|TCO_CTRL1_REG
)paren
suffix:semicolon
id|reg
op_or_assign
id|TCO_HALT
suffix:semicolon
id|outw
c_func
(paren
id|reg
comma
id|pmbase
op_plus
id|TCO_CTRL1_REG
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|amdtco_lock
)paren
suffix:semicolon
)brace
DECL|function|amdtco_fop_open
r_static
r_int
id|amdtco_fop_open
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
id|down_trylock
c_func
(paren
op_amp
id|open_sem
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|timeout
OG
id|MAX_TIMEOUT
)paren
id|timeout
op_assign
id|MAX_TIMEOUT
suffix:semicolon
id|amdtco_disable
c_func
(paren
)paren
suffix:semicolon
id|amdtco_settimeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|amdtco_global_enable
c_func
(paren
)paren
suffix:semicolon
id|amdtco_enable
c_func
(paren
)paren
suffix:semicolon
id|amdtco_ping
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Watchdog enabled, timeout = %ds of %ds&bslash;n&quot;
comma
id|amdtco_gettimeout
c_func
(paren
)paren
comma
id|timeout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amdtco_fop_ioctl
r_static
r_int
id|amdtco_fop_ioctl
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
id|new_timeout
suffix:semicolon
r_int
id|tmp
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
id|WDIOF_SETTIMEOUT
op_or
id|WDIOF_CARDRESET
comma
dot
id|identity
op_assign
l_string|&quot;AMD 766/768&quot;
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
id|ident
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_return
id|put_user
c_func
(paren
id|amdtco_status
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
id|WDIOC_KEEPALIVE
suffix:colon
id|amdtco_ping
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
id|get_user
c_func
(paren
id|new_timeout
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|new_timeout
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|new_timeout
OG
id|MAX_TIMEOUT
)paren
id|new_timeout
op_assign
id|MAX_TIMEOUT
suffix:semicolon
id|timeout
op_assign
id|new_timeout
suffix:semicolon
id|amdtco_settimeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
multiline_comment|/* fall through and return the new timeout */
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|amdtco_gettimeout
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
id|WDIOC_SETOPTIONS
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
id|tmp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|WDIOS_DISABLECARD
)paren
id|amdtco_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|WDIOS_ENABLECARD
)paren
id|amdtco_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|amdtco_fop_release
r_static
r_int
id|amdtco_fop_release
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
id|amdtco_disable
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Watchdog disabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|amdtco_ping
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Unexpected close!, timeout in %d seconds&bslash;n&quot;
comma
id|timeout
)paren
suffix:semicolon
)brace
id|expect_close
op_assign
l_int|0
suffix:semicolon
id|up
c_func
(paren
op_amp
id|open_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amdtco_fop_write
r_static
id|ssize_t
id|amdtco_fop_write
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
r_return
op_minus
id|ESPIPE
suffix:semicolon
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
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
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
id|amdtco_ping
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
id|amdtco_notify_sys
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
id|amdtco_disable
c_func
(paren
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
r_static
r_struct
id|notifier_block
id|amdtco_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|amdtco_notify_sys
comma
)brace
suffix:semicolon
r_static
r_struct
id|file_operations
id|amdtco_fops
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
id|amdtco_fop_write
comma
dot
id|ioctl
op_assign
id|amdtco_fop_ioctl
comma
dot
id|open
op_assign
id|amdtco_fop_open
comma
dot
id|release
op_assign
id|amdtco_fop_release
comma
)brace
suffix:semicolon
r_static
r_struct
id|miscdevice
id|amdtco_miscdev
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
id|amdtco_fops
comma
)brace
suffix:semicolon
r_static
r_struct
id|pci_device_id
id|amdtco_pci_tbl
(braket
)braket
op_assign
(brace
multiline_comment|/* AMD 766 PCI_IDs here */
(brace
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_OPUS_7443
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|amdtco_pci_tbl
)paren
suffix:semicolon
r_static
r_int
id|__init
id|amdtco_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|open_sem
comma
l_int|1
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|amdtco_lock
)paren
suffix:semicolon
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|pci_match_device
(paren
id|amdtco_pci_tbl
comma
id|dev
)paren
op_ne
l_int|NULL
)paren
r_goto
id|found_one
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
id|found_one
suffix:colon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|amdtco_notifier
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unable to register reboot notifier err = %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_clean
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|amdtco_miscdev
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unable to register miscdev on minor %d&bslash;n&quot;
comma
id|WATCHDOG_MINOR
)paren
suffix:semicolon
r_goto
id|out_unreg_reboot
suffix:semicolon
)brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x58
comma
op_amp
id|pmbase
)paren
suffix:semicolon
id|pmbase
op_and_assign
l_int|0x0000FF00
suffix:semicolon
r_if
c_cond
(paren
id|pmbase
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;power management base not set&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_unreg_misc
suffix:semicolon
)brace
multiline_comment|/* ret = 0; */
id|printk
c_func
(paren
id|banner
)paren
suffix:semicolon
r_goto
id|out_clean
suffix:semicolon
id|out_unreg_misc
suffix:colon
id|misc_deregister
c_func
(paren
op_amp
id|amdtco_miscdev
)paren
suffix:semicolon
id|out_unreg_reboot
suffix:colon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|amdtco_notifier
)paren
suffix:semicolon
id|out_clean
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
id|__exit
id|amdtco_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|amdtco_miscdev
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|amdtco_notifier
)paren
suffix:semicolon
)brace
macro_line|#ifndef MODULE
r_static
r_int
id|__init
id|amdtco_setup
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
id|timeout
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
op_logical_or
id|timeout
OG
id|MAX_TIMEOUT
)paren
id|timeout
op_assign
id|MAX_TIMEOUT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;amd7xx_tco=&quot;
comma
id|amdtco_setup
)paren
suffix:semicolon
macro_line|#endif
id|module_init
c_func
(paren
id|amdtco_init
)paren
suffix:semicolon
id|module_exit
c_func
(paren
id|amdtco_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Zwane Mwaikambo &lt;zwane@holomorphy.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AMD 766/768 TCO Timer Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
