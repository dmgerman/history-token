multiline_comment|/* linux/drivers/char/watchdog/s3c2410_wdt.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 Watchdog Timer Support&n; *&n; * Based on, softdog.c by Alan Cox,&n; *     (c) Copyright 1996 Alan Cox &lt;alan@redhat.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/map.h&gt;
macro_line|#include &lt;asm/hardware/clock.h&gt;
DECL|macro|S3C2410_VA_WATCHDOG
macro_line|#undef S3C2410_VA_WATCHDOG
DECL|macro|S3C2410_VA_WATCHDOG
mdefine_line|#define S3C2410_VA_WATCHDOG (0)
macro_line|#include &lt;asm/arch/regs-watchdog.h&gt;
DECL|macro|PFX
mdefine_line|#define PFX &quot;s3c2410-wdt: &quot;
macro_line|#ifdef CONFIG_S3C2410_WATCHDOG_DEBUG
DECL|macro|pr_debug
macro_line|#undef pr_debug
DECL|macro|pr_debug
mdefine_line|#define pr_debug(msg, x...) do { printk(KERN_INFO msg, x); } while(0)
macro_line|#endif
multiline_comment|/* configurations from makefile */
macro_line|#ifndef CONFIG_WATCHDOG_NOWAYOUT
DECL|macro|CONFIG_WATCHDOG_NOWAYOUT
mdefine_line|#define CONFIG_WATCHDOG_NOWAYOUT (0)
macro_line|#endif
macro_line|#ifndef CONFIG_S3C2410_WATCHDOG_ATBOOT
DECL|macro|CONFIG_S3C2410_WATCHDOG_ATBOOT
mdefine_line|#define CONFIG_S3C2410_WATCHDOG_ATBOOT (0)
macro_line|#endif
macro_line|#ifndef CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME
DECL|macro|CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME
mdefine_line|#define CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME (15)
macro_line|#endif
DECL|variable|tmr_margin
r_static
r_int
id|tmr_margin
op_assign
id|CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME
suffix:semicolon
DECL|variable|tmr_atboot
r_static
r_int
id|tmr_atboot
op_assign
id|CONFIG_S3C2410_WATCHDOG_ATBOOT
suffix:semicolon
DECL|variable|nowayout
r_static
r_int
id|nowayout
op_assign
id|CONFIG_WATCHDOG_NOWAYOUT
suffix:semicolon
DECL|variable|soft_noboot
r_static
r_int
id|soft_noboot
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|tmr_margin
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|tmr_atboot
comma
r_int
comma
l_int|0
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
id|module_param
c_func
(paren
id|soft_noboot
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|tmr_margin
comma
l_string|&quot;Watchdog tmr_margin in seconds. default=&quot;
id|__MODULE_STRING
c_func
(paren
id|CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME
)paren
l_string|&quot;)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|tmr_atboot
comma
l_string|&quot;Watchdog is started at boot time if set to 1, default=&quot;
id|__MODULE_STRING
c_func
(paren
id|CONFIG_S3C2410_WATCHDOG_ATBOOT
)paren
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
id|MODULE_PARM_DESC
c_func
(paren
id|soft_noboot
comma
l_string|&quot;Watchdog action, set to 1 to ignore reboots, 0 to reboot (default depends on ONLY_TESTING)&quot;
)paren
suffix:semicolon
DECL|enum|close_state
r_typedef
r_enum
id|close_state
(brace
DECL|enumerator|CLOSE_STATE_NOT
id|CLOSE_STATE_NOT
comma
DECL|enumerator|CLOSE_STATE_ALLOW
id|CLOSE_STATE_ALLOW
op_assign
l_int|0x4021
DECL|typedef|close_state_t
)brace
id|close_state_t
suffix:semicolon
DECL|variable|open_lock
r_static
r_struct
id|semaphore
id|open_lock
suffix:semicolon
DECL|variable|wdt_mem
r_static
r_struct
id|resource
op_star
id|wdt_mem
suffix:semicolon
DECL|variable|wdt_irq
r_static
r_struct
id|resource
op_star
id|wdt_irq
suffix:semicolon
DECL|variable|wdt_clock
r_static
r_struct
id|clk
op_star
id|wdt_clock
suffix:semicolon
DECL|variable|wdt_base
r_static
r_int
r_int
id|wdt_base
suffix:semicolon
DECL|variable|wdt_count
r_static
r_int
r_int
id|wdt_count
suffix:semicolon
DECL|variable|allow_close
r_static
id|close_state_t
id|allow_close
suffix:semicolon
DECL|variable|tmr_count
r_static
r_int
r_int
id|tmr_count
suffix:semicolon
multiline_comment|/* watchdog control routines */
DECL|function|s3c2410wdt_keepalive
r_static
r_int
id|s3c2410wdt_keepalive
c_func
(paren
r_void
)paren
(brace
id|writel
c_func
(paren
id|wdt_count
comma
id|wdt_base
op_plus
id|S3C2410_WTCNT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410wdt_stop
r_static
r_int
id|s3c2410wdt_stop
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|wtcon
suffix:semicolon
id|wtcon
op_assign
id|readl
c_func
(paren
id|wdt_base
op_plus
id|S3C2410_WTCON
)paren
suffix:semicolon
id|wtcon
op_and_assign
op_complement
(paren
id|S3C2410_WTCON_ENABLE
op_or
id|S3C2410_WTCON_RSTEN
)paren
suffix:semicolon
id|writel
c_func
(paren
id|wtcon
comma
id|wdt_base
op_plus
id|S3C2410_WTCON
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410wdt_start
r_static
r_int
id|s3c2410wdt_start
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|wtcon
suffix:semicolon
id|wtcon
op_assign
id|readl
c_func
(paren
id|wdt_base
op_plus
id|S3C2410_WTCON
)paren
suffix:semicolon
id|wtcon
op_or_assign
id|S3C2410_WTCON_ENABLE
op_or
id|S3C2410_WTCON_DIV128
suffix:semicolon
r_if
c_cond
(paren
id|soft_noboot
)paren
(brace
id|wtcon
op_or_assign
id|S3C2410_WTCON_INTEN
suffix:semicolon
id|wtcon
op_and_assign
op_complement
id|S3C2410_WTCON_RSTEN
suffix:semicolon
)brace
r_else
(brace
id|wtcon
op_and_assign
op_complement
id|S3C2410_WTCON_INTEN
suffix:semicolon
id|wtcon
op_or_assign
id|S3C2410_WTCON_RSTEN
suffix:semicolon
)brace
id|clk_enable
c_func
(paren
id|wdt_clock
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: tmr_count=0x%08x, wtcon=%08lx&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|tmr_count
comma
id|wtcon
)paren
suffix:semicolon
id|writel
c_func
(paren
id|tmr_count
comma
id|wdt_base
op_plus
id|S3C2410_WTDAT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|wtcon
comma
id|wdt_base
op_plus
id|S3C2410_WTCON
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410wdt_set_heartbeat
r_static
r_int
id|s3c2410wdt_set_heartbeat
c_func
(paren
r_int
id|timeout
)paren
(brace
r_int
r_int
id|freq
op_assign
id|clk_get_rate
c_func
(paren
id|wdt_clock
)paren
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|divisor
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|wtcon
suffix:semicolon
r_if
c_cond
(paren
id|timeout
OL
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmr_margin
op_assign
id|timeout
suffix:semicolon
multiline_comment|/* I think someone must have missed a divide-by-2 in the 2410,&n;&t; * as a divisor of 128 gives half the calculated delay...&n;&t; */
id|freq
op_div_assign
l_int|128
op_div
l_int|2
suffix:semicolon
id|count
op_assign
id|timeout
op_star
id|freq
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: count=%d, timeout=%d, freq=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|count
comma
id|timeout
comma
id|freq
)paren
suffix:semicolon
multiline_comment|/* if the count is bigger than the watchdog register,&n;&t;   then work out what we need to do (and if) we can&n;&t;   actually make this value&n;&t;*/
r_if
c_cond
(paren
id|count
op_ge
l_int|0x10000
)paren
(brace
r_for
c_loop
(paren
id|divisor
op_assign
l_int|1
suffix:semicolon
id|divisor
op_le
l_int|0x100
suffix:semicolon
id|divisor
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|count
op_div
id|divisor
)paren
OL
l_int|0x10000
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|count
op_div
id|divisor
)paren
op_ge
l_int|0x10000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;timeout %d too big&bslash;n&quot;
comma
id|timeout
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: timeout=%d, divisor=%d, count=%d (%08x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|timeout
comma
id|divisor
comma
id|count
comma
id|count
op_div
id|divisor
)paren
suffix:semicolon
id|count
op_div_assign
id|divisor
suffix:semicolon
id|tmr_count
op_assign
id|count
suffix:semicolon
multiline_comment|/* update the pre-scaler */
id|wtcon
op_assign
id|readl
c_func
(paren
id|wdt_base
op_plus
id|S3C2410_WTCON
)paren
suffix:semicolon
id|wtcon
op_and_assign
op_complement
id|S3C2410_WTCON_PRESCALE_MASK
suffix:semicolon
id|wtcon
op_or_assign
id|S3C2410_WTCON_PRESCALE
c_func
(paren
id|divisor
op_minus
l_int|1
)paren
suffix:semicolon
id|writel
c_func
(paren
id|count
comma
id|wdt_base
op_plus
id|S3C2410_WTDAT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|wtcon
comma
id|wdt_base
op_plus
id|S3C2410_WTCON
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;/dev/watchdog handling&n; */
DECL|function|s3c2410wdt_open
r_static
r_int
id|s3c2410wdt_open
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
id|open_lock
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
(brace
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
r_else
(brace
id|allow_close
op_assign
id|CLOSE_STATE_ALLOW
suffix:semicolon
)brace
multiline_comment|/* start the timer */
id|s3c2410wdt_start
c_func
(paren
)paren
suffix:semicolon
r_return
id|nonseekable_open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|s3c2410wdt_release
r_static
r_int
id|s3c2410wdt_release
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
id|allow_close
op_eq
id|CLOSE_STATE_ALLOW
)paren
(brace
id|s3c2410wdt_stop
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
id|PFX
l_string|&quot;Unexpected close, not stopping watchdog!&bslash;n&quot;
)paren
suffix:semicolon
id|s3c2410wdt_keepalive
c_func
(paren
)paren
suffix:semicolon
)brace
id|allow_close
op_assign
id|CLOSE_STATE_NOT
suffix:semicolon
id|up
c_func
(paren
op_amp
id|open_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410wdt_write
r_static
id|ssize_t
id|s3c2410wdt_write
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
multiline_comment|/*&n;&t; *&t;Refresh the timer.&n;&t; */
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
multiline_comment|/* In case it was set long ago */
id|allow_close
op_assign
id|CLOSE_STATE_NOT
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
id|allow_close
op_assign
id|CLOSE_STATE_ALLOW
suffix:semicolon
)brace
)brace
id|s3c2410wdt_keepalive
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|macro|OPTIONS
mdefine_line|#define OPTIONS WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE
DECL|variable|s3c2410_wdt_ident
r_static
r_struct
id|watchdog_info
id|s3c2410_wdt_ident
op_assign
(brace
dot
id|options
op_assign
id|OPTIONS
comma
dot
id|firmware_version
op_assign
l_int|0
comma
dot
id|identity
op_assign
l_string|&quot;S3C2410 Watchdog&quot;
comma
)brace
suffix:semicolon
DECL|function|s3c2410wdt_ioctl
r_static
r_int
id|s3c2410wdt_ioctl
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
r_int
id|new_margin
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
id|s3c2410_wdt_ident
comma
r_sizeof
(paren
id|s3c2410_wdt_ident
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
id|s3c2410wdt_keepalive
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
id|new_margin
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410wdt_set_heartbeat
c_func
(paren
id|new_margin
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|s3c2410wdt_keepalive
c_func
(paren
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|tmr_margin
comma
id|p
)paren
suffix:semicolon
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|tmr_margin
comma
id|p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Notifier for system down&n; */
DECL|function|s3c2410wdt_notify_sys
r_static
r_int
id|s3c2410wdt_notify_sys
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
multiline_comment|/* Turn the WDT off */
id|s3c2410wdt_stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/* kernel interface */
DECL|variable|s3c2410wdt_fops
r_static
r_struct
id|file_operations
id|s3c2410wdt_fops
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
id|s3c2410wdt_write
comma
dot
id|ioctl
op_assign
id|s3c2410wdt_ioctl
comma
dot
id|open
op_assign
id|s3c2410wdt_open
comma
dot
id|release
op_assign
id|s3c2410wdt_release
comma
)brace
suffix:semicolon
DECL|variable|s3c2410wdt_miscdev
r_static
r_struct
id|miscdevice
id|s3c2410wdt_miscdev
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
id|s3c2410wdt_fops
comma
)brace
suffix:semicolon
DECL|variable|s3c2410wdt_notifier
r_static
r_struct
id|notifier_block
id|s3c2410wdt_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|s3c2410wdt_notify_sys
comma
)brace
suffix:semicolon
multiline_comment|/* interrupt handler code */
DECL|function|s3c2410wdt_irq
r_static
id|irqreturn_t
id|s3c2410wdt_irq
c_func
(paren
r_int
id|irqno
comma
r_void
op_star
id|param
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
id|KERN_INFO
id|PFX
l_string|&quot;Watchdog timer expired!&bslash;n&quot;
)paren
suffix:semicolon
id|s3c2410wdt_keepalive
c_func
(paren
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* device interface */
DECL|function|s3c2410wdt_probe
r_static
r_int
id|s3c2410wdt_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|platform_device
op_star
id|pdev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|started
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: probe=%p, device=%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|pdev
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* get the memory region for the watchdog timer */
id|res
op_assign
id|platform_get_resource
c_func
(paren
id|pdev
comma
id|IORESOURCE_MEM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;failed to get memory region resouce&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|res-&gt;start
comma
id|res-&gt;end
op_minus
id|res-&gt;start
comma
id|pdev-&gt;name
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;failed to get memory region&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|wdt_base
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|res-&gt;start
comma
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wdt_base
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;failed to ioremap() region&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;wdt_base=%08lx&bslash;n&quot;
comma
id|wdt_base
)paren
suffix:semicolon
id|res
op_assign
id|platform_get_resource
c_func
(paren
id|pdev
comma
id|IORESOURCE_IRQ
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;failed to get irq resource&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|ret
op_assign
id|request_irq
c_func
(paren
id|res-&gt;start
comma
id|s3c2410wdt_irq
comma
l_int|0
comma
id|pdev-&gt;name
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;failed to install irq (%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|wdt_clock
op_assign
id|clk_get
c_func
(paren
id|dev
comma
l_string|&quot;watchdog&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wdt_clock
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;failed to find watchdog clock source&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|clk_use
c_func
(paren
id|wdt_clock
)paren
suffix:semicolon
multiline_comment|/* see if we can actually set the requested timer margin, and if&n;&t; * not, try the default value */
r_if
c_cond
(paren
id|s3c2410wdt_set_heartbeat
c_func
(paren
id|tmr_margin
)paren
)paren
(brace
id|started
op_assign
id|s3c2410wdt_set_heartbeat
c_func
(paren
id|CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME
)paren
suffix:semicolon
r_if
c_cond
(paren
id|started
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;tmr_margin value out of range, default %d used&bslash;n&quot;
comma
id|CONFIG_S3C2410_WATCHDOG_DEFAULT_TIME
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;default timer value is out of range, cannot start&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|ret
op_assign
id|register_reboot_notifier
c_func
(paren
op_amp
id|s3c2410wdt_notifier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register reboot notifier (%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|s3c2410wdt_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot register miscdev on minor=%d (%d)&bslash;n&quot;
comma
id|WATCHDOG_MINOR
comma
id|ret
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|s3c2410wdt_notifier
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmr_atboot
op_logical_and
id|started
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Starting Watchdog Timer&bslash;n&quot;
)paren
suffix:semicolon
id|s3c2410wdt_start
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410wdt_remove
r_static
r_int
id|s3c2410wdt_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|wdt_mem
op_ne
l_int|NULL
)paren
(brace
id|release_mem_region
c_func
(paren
id|wdt_mem-&gt;start
comma
id|wdt_mem-&gt;end
op_minus
id|wdt_mem-&gt;start
)paren
suffix:semicolon
id|wdt_mem
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wdt_irq
op_ne
l_int|NULL
)paren
(brace
id|free_irq
c_func
(paren
id|wdt_irq-&gt;start
comma
id|dev
)paren
suffix:semicolon
id|wdt_irq
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wdt_clock
op_ne
l_int|NULL
)paren
(brace
id|clk_disable
c_func
(paren
id|wdt_clock
)paren
suffix:semicolon
id|clk_unuse
c_func
(paren
id|wdt_clock
)paren
suffix:semicolon
id|clk_put
c_func
(paren
id|wdt_clock
)paren
suffix:semicolon
id|wdt_clock
op_assign
l_int|NULL
suffix:semicolon
)brace
id|misc_deregister
c_func
(paren
op_amp
id|s3c2410wdt_miscdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|s3c2410wdt_driver
r_static
r_struct
id|device_driver
id|s3c2410wdt_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-wdt&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|s3c2410wdt_probe
comma
dot
id|remove
op_assign
id|s3c2410wdt_remove
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
l_string|&quot;S3C2410 Watchdog Timer, (c) 2004 Simtec Electronics&quot;
suffix:semicolon
DECL|function|watchdog_init
r_static
r_int
id|__init
id|watchdog_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|banner
)paren
suffix:semicolon
r_return
id|driver_register
c_func
(paren
op_amp
id|s3c2410wdt_driver
)paren
suffix:semicolon
)brace
DECL|function|watchdog_exit
r_static
r_void
id|__exit
id|watchdog_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|s3c2410wdt_driver
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|s3c2410wdt_notifier
)paren
suffix:semicolon
)brace
DECL|variable|watchdog_init
id|module_init
c_func
(paren
id|watchdog_init
)paren
suffix:semicolon
DECL|variable|watchdog_exit
id|module_exit
c_func
(paren
id|watchdog_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ben Dooks &lt;ben@simtec.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;S3C2410 Watchdog Device Driver&quot;
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
