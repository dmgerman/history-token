multiline_comment|/*&n; * drivers/watchdog/ixp4xx_wdt.c&n; *&n; * Watchdog driver for Intel IXP4xx network processors&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2004 (c) MontaVista, Software, Inc.&n; * Based on sa1100 driver, Copyright (C) 2000 Oleg Drokin &lt;green@crimea.edu&gt;&n; *&n; * This file is licensed under  the terms of the GNU General Public&n; * License version 2. This program is licensed &quot;as is&quot; without any&n; * warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
DECL|variable|heartbeat
r_static
r_int
id|heartbeat
op_assign
l_int|60
suffix:semicolon
multiline_comment|/* (secs) Default is 1 minute */
DECL|variable|wdt_status
r_static
r_int
r_int
id|wdt_status
suffix:semicolon
DECL|variable|boot_status
r_static
r_int
r_int
id|boot_status
suffix:semicolon
DECL|macro|WDT_TICK_RATE
mdefine_line|#define WDT_TICK_RATE (IXP4XX_PERIPHERAL_BUS_CLOCK * 1000000UL)
DECL|macro|WDT_IN_USE
mdefine_line|#define&t;WDT_IN_USE&t;&t;0
DECL|macro|WDT_OK_TO_CLOSE
mdefine_line|#define&t;WDT_OK_TO_CLOSE&t;&t;1
r_static
r_void
DECL|function|wdt_enable
id|wdt_enable
c_func
(paren
r_void
)paren
(brace
op_star
id|IXP4XX_OSWK
op_assign
id|IXP4XX_WDT_KEY
suffix:semicolon
op_star
id|IXP4XX_OSWE
op_assign
l_int|0
suffix:semicolon
op_star
id|IXP4XX_OSWT
op_assign
id|WDT_TICK_RATE
op_star
id|heartbeat
suffix:semicolon
op_star
id|IXP4XX_OSWE
op_assign
id|IXP4XX_WDT_COUNT_ENABLE
op_or
id|IXP4XX_WDT_RESET_ENABLE
suffix:semicolon
op_star
id|IXP4XX_OSWK
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|wdt_disable
id|wdt_disable
c_func
(paren
r_void
)paren
(brace
op_star
id|IXP4XX_OSWK
op_assign
id|IXP4XX_WDT_KEY
suffix:semicolon
op_star
id|IXP4XX_OSWE
op_assign
l_int|0
suffix:semicolon
op_star
id|IXP4XX_OSWK
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ixp4xx_wdt_open
id|ixp4xx_wdt_open
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
id|WDT_IN_USE
comma
op_amp
id|wdt_status
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|clear_bit
c_func
(paren
id|WDT_OK_TO_CLOSE
comma
op_amp
id|wdt_status
)paren
suffix:semicolon
id|wdt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ixp4xx_wdt_write
id|ixp4xx_wdt_write
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
id|clear_bit
c_func
(paren
id|WDT_OK_TO_CLOSE
comma
op_amp
id|wdt_status
)paren
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
id|set_bit
c_func
(paren
id|WDT_OK_TO_CLOSE
comma
op_amp
id|wdt_status
)paren
suffix:semicolon
)brace
)brace
id|wdt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|WDIOF_CARDRESET
op_or
id|WDIOF_MAGICCLOSE
op_or
id|WDIOF_SETTIMEOUT
op_or
id|WDIOF_KEEPALIVEPING
comma
dot
id|identity
op_assign
l_string|&quot;IXP4xx Watchdog&quot;
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|ixp4xx_wdt_ioctl
id|ixp4xx_wdt_ioctl
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
id|ret
op_assign
op_minus
id|ENOIOCTLCMD
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
r_case
id|WDIOC_GETSUPPORT
suffix:colon
id|ret
op_assign
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
r_break
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
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
id|WDIOC_GETBOOTSTATUS
suffix:colon
id|ret
op_assign
id|put_user
c_func
(paren
id|boot_status
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
id|WDIOC_SETTIMEOUT
suffix:colon
id|ret
op_assign
id|get_user
c_func
(paren
id|time
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
r_if
c_cond
(paren
id|time
op_le
l_int|0
op_logical_or
id|time
OG
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
id|heartbeat
op_assign
id|time
suffix:semicolon
id|wdt_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fall through */
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
id|ret
op_assign
id|put_user
c_func
(paren
id|heartbeat
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
id|wdt_enable
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
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|ixp4xx_wdt_release
id|ixp4xx_wdt_release
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
id|test_bit
c_func
(paren
id|WDT_OK_TO_CLOSE
comma
op_amp
id|wdt_status
)paren
)paren
(brace
id|wdt_disable
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;WATCHDOG: Device closed unexpectdly - &quot;
l_string|&quot;timer will not stop&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|WDT_IN_USE
comma
op_amp
id|wdt_status
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|WDT_OK_TO_CLOSE
comma
op_amp
id|wdt_status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ixp4xx_wdt_fops
r_static
r_struct
id|file_operations
id|ixp4xx_wdt_fops
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
id|ixp4xx_wdt_write
comma
dot
id|ioctl
op_assign
id|ixp4xx_wdt_ioctl
comma
dot
id|open
op_assign
id|ixp4xx_wdt_open
comma
dot
id|release
op_assign
id|ixp4xx_wdt_release
comma
)brace
suffix:semicolon
DECL|variable|ixp4xx_wdt_miscdev
r_static
r_struct
id|miscdevice
id|ixp4xx_wdt_miscdev
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
l_string|&quot;IXP4xx Watchdog&quot;
comma
dot
id|fops
op_assign
op_amp
id|ixp4xx_wdt_fops
comma
)brace
suffix:semicolon
DECL|function|ixp4xx_wdt_init
r_static
r_int
id|__init
id|ixp4xx_wdt_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|processor_id
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mrc p15, 0, %0, cr0, cr0, 0;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|processor_id
)paren
suffix:colon
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|processor_id
op_amp
l_int|0xf
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IXP4XXX Watchdog: Rev. A0 CPU detected - &quot;
l_string|&quot;watchdog disabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|ixp4xx_wdt_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;IXP4xx Watchdog Timer: heartbeat %d sec&bslash;n&quot;
comma
id|heartbeat
)paren
suffix:semicolon
id|boot_status
op_assign
(paren
op_star
id|IXP4XX_OSST
op_amp
id|IXP4XX_OSST_TIMER_WARM_RESET
)paren
ques
c_cond
id|WDIOF_CARDRESET
suffix:colon
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ixp4xx_wdt_exit
r_static
r_void
id|__exit
id|ixp4xx_wdt_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|ixp4xx_wdt_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|ixp4xx_wdt_init
id|module_init
c_func
(paren
id|ixp4xx_wdt_init
)paren
suffix:semicolon
DECL|variable|ixp4xx_wdt_exit
id|module_exit
c_func
(paren
id|ixp4xx_wdt_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Deepak Saxena &lt;dsaxena@plexity.net&quot;
OG
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IXP4xx Network Processor Watchdog&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|heartbeat
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|heartbeat
comma
l_string|&quot;Watchdog heartbeat in seconds (default 60s)&quot;
)paren
suffix:semicolon
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
l_string|&quot;Watchdog cannot be stopped once started&quot;
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
