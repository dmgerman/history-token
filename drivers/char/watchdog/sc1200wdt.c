multiline_comment|/*&n; *&t;National Semiconductor PC87307/PC97307 (ala SC1200) WDT driver&n; *&t;(c) Copyright 2002 Zwane Mwaikambo &lt;zwane@commfireservices.com&gt;,&n; *&t;&t;&t;All Rights Reserved.&n; *&t;Based on wdt.c and wdt977.c by Alan Cox and Woody Suwalski respectively.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;The author(s) of this software shall not be held liable for damages&n; *&t;of any nature resulting due to the use of this software. This&n; *&t;software is provided AS-IS with no warranties.&n; *&n; *&t;Changelog:&n; *&t;20020220 Zwane Mwaikambo&t;Code based on datasheet, no hardware.&n; *&t;20020221 Zwane Mwaikambo&t;Cleanups as suggested by Jeff Garzik and Alan Cox.&n; *&t;20020222 Zwane Mwaikambo&t;Added probing.&n; *&t;20020225 Zwane Mwaikambo&t;Added ISAPNP support.&n; *&t;20020412 Rob Radez&t;&t;Broke out start/stop functions&n; *&t;&t; &lt;rob@osinvestor.com&gt;&t;Return proper status instead of temperature warning&n; *&t;&t;&t;&t;&t;Add WDIOC_GETBOOTSTATUS and WDIOC_SETOPTIONS ioctls&n; *&t;&t;&t;&t;&t;Fix CONFIG_WATCHDOG_NOWAYOUT&n; *&t;20020530 Joel Becker&t;&t;Add Matt Domsch&squot;s nowayout module option&n; *&t;20030116 Adam Belay&t;&t;Updated to the latest pnp code&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|SC1200_MODULE_VER
mdefine_line|#define SC1200_MODULE_VER&t;&quot;build 20020303&quot;
DECL|macro|SC1200_MODULE_NAME
mdefine_line|#define SC1200_MODULE_NAME&t;&quot;sc1200wdt&quot;
DECL|macro|PFX
mdefine_line|#define PFX&t;&t;&t;SC1200_MODULE_NAME &quot;: &quot;
DECL|macro|MAX_TIMEOUT
mdefine_line|#define&t;MAX_TIMEOUT&t;255&t;/* 255 minutes */
DECL|macro|PMIR
mdefine_line|#define PMIR&t;&t;(io)&t;/* Power Management Index Register */
DECL|macro|PMDR
mdefine_line|#define PMDR&t;&t;(io+1)&t;/* Power Management Data Register */
multiline_comment|/* Data Register indexes */
DECL|macro|FER1
mdefine_line|#define FER1&t;&t;0x00&t;/* Function enable register 1 */
DECL|macro|FER2
mdefine_line|#define FER2&t;&t;0x01&t;/* Function enable register 2 */
DECL|macro|PMC1
mdefine_line|#define PMC1&t;&t;0x02&t;/* Power Management Ctrl 1 */
DECL|macro|PMC2
mdefine_line|#define PMC2&t;&t;0x03&t;/* Power Management Ctrl 2 */
DECL|macro|PMC3
mdefine_line|#define PMC3&t;&t;0x04&t;/* Power Management Ctrl 3 */
DECL|macro|WDTO
mdefine_line|#define WDTO&t;&t;0x05&t;/* Watchdog timeout register */
DECL|macro|WDCF
mdefine_line|#define&t;WDCF&t;&t;0x06&t;/* Watchdog config register */
DECL|macro|WDST
mdefine_line|#define WDST&t;&t;0x07&t;/* Watchdog status register */
multiline_comment|/* WDCF bitfields - which devices assert WDO */
DECL|macro|KBC_IRQ
mdefine_line|#define KBC_IRQ&t;&t;0x01&t;/* Keyboard Controller */
DECL|macro|MSE_IRQ
mdefine_line|#define MSE_IRQ&t;&t;0x02&t;/* Mouse */
DECL|macro|UART1_IRQ
mdefine_line|#define UART1_IRQ&t;0x03&t;/* Serial0 */
DECL|macro|UART2_IRQ
mdefine_line|#define UART2_IRQ&t;0x04&t;/* Serial1 */
multiline_comment|/* 5 -7 are reserved */
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
id|SC1200_MODULE_VER
suffix:semicolon
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
l_int|1
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|io_len
r_static
r_int
id|io_len
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* for non plug and play */
DECL|variable|open_sem
r_struct
id|semaphore
id|open_sem
suffix:semicolon
DECL|variable|expect_close
r_static
r_char
id|expect_close
suffix:semicolon
DECL|variable|sc1200wdt_lock
id|spinlock_t
id|sc1200wdt_lock
suffix:semicolon
multiline_comment|/* io port access serialisation */
macro_line|#if defined CONFIG_PNP
DECL|variable|isapnp
r_static
r_int
id|isapnp
op_assign
l_int|1
suffix:semicolon
DECL|variable|wdt_dev
r_static
r_struct
id|pnp_dev
op_star
id|wdt_dev
suffix:semicolon
id|module_param
c_func
(paren
id|isapnp
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|isapnp
comma
l_string|&quot;When set to 0 driver ISA PnP support will be disabled&quot;
)paren
suffix:semicolon
macro_line|#endif
id|module_param
c_func
(paren
id|io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;io port&quot;
)paren
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
l_string|&quot;range is 0-255 minutes, default is 1&quot;
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
multiline_comment|/* Read from Data Register */
DECL|function|sc1200wdt_read_data
r_static
r_inline
r_void
id|sc1200wdt_read_data
c_func
(paren
r_int
r_char
id|index
comma
r_int
r_char
op_star
id|data
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sc1200wdt_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|index
comma
id|PMIR
)paren
suffix:semicolon
op_star
id|data
op_assign
id|inb
c_func
(paren
id|PMDR
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sc1200wdt_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Write to Data Register */
DECL|function|sc1200wdt_write_data
r_static
r_inline
r_void
id|sc1200wdt_write_data
c_func
(paren
r_int
r_char
id|index
comma
r_int
r_char
id|data
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sc1200wdt_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|index
comma
id|PMIR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|PMDR
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sc1200wdt_lock
)paren
suffix:semicolon
)brace
DECL|function|sc1200wdt_start
r_static
r_void
id|sc1200wdt_start
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|reg
suffix:semicolon
id|sc1200wdt_read_data
c_func
(paren
id|WDCF
comma
op_amp
id|reg
)paren
suffix:semicolon
multiline_comment|/* assert WDO when any of the following interrupts are triggered too */
id|reg
op_or_assign
(paren
id|KBC_IRQ
op_or
id|MSE_IRQ
op_or
id|UART1_IRQ
op_or
id|UART2_IRQ
)paren
suffix:semicolon
id|sc1200wdt_write_data
c_func
(paren
id|WDCF
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* set the timeout and get the ball rolling */
id|sc1200wdt_write_data
c_func
(paren
id|WDTO
comma
id|timeout
)paren
suffix:semicolon
)brace
DECL|function|sc1200wdt_stop
r_static
r_void
id|sc1200wdt_stop
c_func
(paren
r_void
)paren
(brace
id|sc1200wdt_write_data
c_func
(paren
id|WDTO
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* This returns the status of the WDO signal, inactive high. */
DECL|function|sc1200wdt_status
r_static
r_inline
r_int
id|sc1200wdt_status
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|ret
suffix:semicolon
id|sc1200wdt_read_data
c_func
(paren
id|WDST
comma
op_amp
id|ret
)paren
suffix:semicolon
multiline_comment|/* If the bit is inactive, the watchdog is enabled, so return&n;&t; * KEEPALIVEPING which is a bit of a kludge because there&squot;s nothing&n;&t; * else for enabled/disabled status&n;&t; */
r_return
(paren
id|ret
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|0
suffix:colon
id|WDIOF_KEEPALIVEPING
suffix:semicolon
multiline_comment|/* bits 1 - 7 are undefined */
)brace
DECL|function|sc1200wdt_open
r_static
r_int
id|sc1200wdt_open
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
multiline_comment|/* allow one at a time */
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
id|sc1200wdt_start
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Watchdog enabled, timeout = %d min(s)&quot;
comma
id|timeout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sc1200wdt_ioctl
r_static
r_int
id|sc1200wdt_ioctl
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
l_int|0
comma
dot
id|identity
op_assign
l_string|&quot;PC87307/PC97307&quot;
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
multiline_comment|/* Keep Pavel Machek amused ;) */
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
id|sc1200wdt_status
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
id|sc1200wdt_write_data
c_func
(paren
id|WDTO
comma
id|timeout
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
multiline_comment|/* the API states this is given in secs */
id|new_timeout
op_div_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|new_timeout
template_param
id|MAX_TIMEOUT
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|timeout
op_assign
id|new_timeout
suffix:semicolon
id|sc1200wdt_write_data
c_func
(paren
id|WDTO
comma
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
id|timeout
op_star
l_int|60
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
(brace
r_int
id|options
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
id|options
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
id|options
op_amp
id|WDIOS_DISABLECARD
)paren
(brace
id|sc1200wdt_stop
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
id|options
op_amp
id|WDIOS_ENABLECARD
)paren
(brace
id|sc1200wdt_start
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
)brace
)brace
DECL|function|sc1200wdt_release
r_static
r_int
id|sc1200wdt_release
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
id|sc1200wdt_stop
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
id|sc1200wdt_write_data
c_func
(paren
id|WDTO
comma
id|timeout
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;Unexpected close!, timeout = %d min(s)&bslash;n&quot;
comma
id|timeout
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|open_sem
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
DECL|function|sc1200wdt_write
r_static
id|ssize_t
id|sc1200wdt_write
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
(brace
r_int
id|i
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
id|sc1200wdt_write_data
c_func
(paren
id|WDTO
comma
id|timeout
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sc1200wdt_notify_sys
r_static
r_int
id|sc1200wdt_notify_sys
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
id|sc1200wdt_stop
c_func
(paren
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|sc1200wdt_notifier
r_static
r_struct
id|notifier_block
id|sc1200wdt_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|sc1200wdt_notify_sys
comma
)brace
suffix:semicolon
DECL|variable|sc1200wdt_fops
r_static
r_struct
id|file_operations
id|sc1200wdt_fops
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
id|sc1200wdt_write
comma
dot
id|ioctl
op_assign
id|sc1200wdt_ioctl
comma
dot
id|open
op_assign
id|sc1200wdt_open
comma
dot
id|release
op_assign
id|sc1200wdt_release
comma
)brace
suffix:semicolon
DECL|variable|sc1200wdt_miscdev
r_static
r_struct
id|miscdevice
id|sc1200wdt_miscdev
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
id|sc1200wdt_fops
comma
)brace
suffix:semicolon
DECL|function|sc1200wdt_probe
r_static
r_int
id|__init
id|sc1200wdt_probe
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* The probe works by reading the PMC3 register&squot;s default value of 0x0e&n;&t; * there is one caveat, if the device disables the parallel port or any&n;&t; * of the UARTs we won&squot;t be able to detect it.&n;&t; * Nb. This could be done with accuracy by reading the SID registers, but&n;&t; * we don&squot;t have access to those io regions.&n;&t; */
r_int
r_char
id|reg
suffix:semicolon
id|sc1200wdt_read_data
c_func
(paren
id|PMC3
comma
op_amp
id|reg
)paren
suffix:semicolon
id|reg
op_and_assign
l_int|0x0f
suffix:semicolon
multiline_comment|/* we don&squot;t want the UART busy bits */
r_return
(paren
id|reg
op_eq
l_int|0x0e
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#if defined CONFIG_PNP
DECL|variable|scl200wdt_pnp_devices
r_struct
id|pnp_device_id
id|scl200wdt_pnp_devices
(braket
)braket
op_assign
(brace
multiline_comment|/* National Semiconductor PC87307/PC97307 watchdog component */
(brace
dot
id|id
op_assign
l_string|&quot;NSC0800&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|scl200wdt_pnp_probe
r_static
r_int
id|scl200wdt_pnp_probe
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|dev_id
)paren
(brace
multiline_comment|/* this driver only supports one card at a time */
r_if
c_cond
(paren
id|wdt_dev
op_logical_or
op_logical_neg
id|isapnp
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|wdt_dev
op_assign
id|dev
suffix:semicolon
id|io
op_assign
id|pnp_port_start
c_func
(paren
id|wdt_dev
comma
l_int|0
)paren
suffix:semicolon
id|io_len
op_assign
id|pnp_port_len
c_func
(paren
id|wdt_dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
id|io_len
comma
id|SC1200_MODULE_NAME
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unable to register IO port %#x&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;scl200wdt: PnP device found at io port %#x/%d&bslash;n&quot;
comma
id|io
comma
id|io_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scl200wdt_pnp_remove
r_static
r_void
id|scl200wdt_pnp_remove
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|wdt_dev
)paren
(brace
id|release_region
c_func
(paren
id|io
comma
id|io_len
)paren
suffix:semicolon
id|wdt_dev
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|scl200wdt_pnp_driver
r_static
r_struct
id|pnp_driver
id|scl200wdt_pnp_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scl200wdt&quot;
comma
dot
id|id_table
op_assign
id|scl200wdt_pnp_devices
comma
dot
id|probe
op_assign
id|scl200wdt_pnp_probe
comma
dot
id|remove
op_assign
id|scl200wdt_pnp_remove
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_PNP */
DECL|function|sc1200wdt_init
r_static
r_int
id|__init
id|sc1200wdt_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|banner
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|sc1200wdt_lock
)paren
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
macro_line|#if defined CONFIG_PNP
r_if
c_cond
(paren
id|isapnp
)paren
(brace
id|ret
op_assign
id|pnp_register_driver
c_func
(paren
op_amp
id|scl200wdt_pnp_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_clean
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|io
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;io parameter must be specified&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out_clean
suffix:semicolon
)brace
macro_line|#if defined CONFIG_PNP
multiline_comment|/* now that the user has specified an IO port and we haven&squot;t detected&n;&t; * any devices, disable pnp support */
id|isapnp
op_assign
l_int|0
suffix:semicolon
id|pnp_unregister_driver
c_func
(paren
op_amp
id|scl200wdt_pnp_driver
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
id|io_len
comma
id|SC1200_MODULE_NAME
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unable to register IO port %#x&bslash;n&quot;
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
id|out_clean
suffix:semicolon
)brace
id|ret
op_assign
id|sc1200wdt_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_io
suffix:semicolon
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|sc1200wdt_notifier
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
id|PFX
l_string|&quot;Unable to register reboot notifier err = %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_io
suffix:semicolon
)brace
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|sc1200wdt_miscdev
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
id|PFX
l_string|&quot;Unable to register miscdev on minor %d&bslash;n&quot;
comma
id|WATCHDOG_MINOR
)paren
suffix:semicolon
r_goto
id|out_rbt
suffix:semicolon
)brace
multiline_comment|/* ret = 0 */
id|out_clean
suffix:colon
r_return
id|ret
suffix:semicolon
id|out_rbt
suffix:colon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|sc1200wdt_notifier
)paren
suffix:semicolon
id|out_io
suffix:colon
id|release_region
c_func
(paren
id|io
comma
id|io_len
)paren
suffix:semicolon
r_goto
id|out_clean
suffix:semicolon
)brace
DECL|function|sc1200wdt_exit
r_static
r_void
id|__exit
id|sc1200wdt_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|sc1200wdt_miscdev
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|sc1200wdt_notifier
)paren
suffix:semicolon
macro_line|#if defined CONFIG_PNP
r_if
c_cond
(paren
id|isapnp
)paren
(brace
id|pnp_unregister_driver
c_func
(paren
op_amp
id|scl200wdt_pnp_driver
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|release_region
c_func
(paren
id|io
comma
id|io_len
)paren
suffix:semicolon
)brace
DECL|variable|sc1200wdt_init
id|module_init
c_func
(paren
id|sc1200wdt_init
)paren
suffix:semicolon
DECL|variable|sc1200wdt_exit
id|module_exit
c_func
(paren
id|sc1200wdt_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Zwane Mwaikambo &lt;zwane@commfireservices.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for National Semiconductor PC87307/PC97307 watchdog component&quot;
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
