multiline_comment|/*&n; *&t;Watchdog driver for the SA11x0/PXA2xx&n; *&n; *      (c) Copyright 2000 Oleg Drokin &lt;green@crimea.edu&gt;&n; *          Based on SoftDog driver by Alan Cox &lt;alan@redhat.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Neither Oleg Drokin nor iXcelerator.com admit liability nor provide&n; *&t;warranty for any of this software. This material is provided&n; *&t;&quot;AS-IS&quot; and at no charge.&n; *&n; *&t;(c) Copyright 2000           Oleg Drokin &lt;green@crimea.edu&gt;&n; *&n; *      27/11/2000 Initial release&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_ARCH_PXA
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|OSCR_FREQ
mdefine_line|#define OSCR_FREQ&t;&t;3686400
DECL|macro|SA1100_CLOSE_MAGIC
mdefine_line|#define SA1100_CLOSE_MAGIC&t;(0x5afc4453)
DECL|variable|sa1100wdt_users
r_static
r_int
r_int
id|sa1100wdt_users
suffix:semicolon
DECL|variable|expect_close
r_static
r_int
id|expect_close
suffix:semicolon
DECL|variable|pre_margin
r_static
r_int
id|pre_margin
suffix:semicolon
DECL|variable|boot_status
r_static
r_int
id|boot_status
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
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|sa1100dog_open
r_static
r_int
id|sa1100dog_open
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
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|1
comma
op_amp
id|sa1100wdt_users
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Activate SA1100 Watchdog timer */
id|OSMR3
op_assign
id|OSCR
op_plus
id|pre_margin
suffix:semicolon
id|OSSR
op_assign
id|OSSR_M3
suffix:semicolon
id|OWER
op_assign
id|OWER_WME
suffix:semicolon
id|OIER
op_or_assign
id|OIER_E3
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Shut off the timer.&n; * &t;Lock it in if it&squot;s a module and we defined ...NOWAYOUT&n; *&t;Oddly, the watchdog can only be enabled, but we can turn off&n; *&t;the interrupt, which appears to prevent the watchdog timing out.&n; */
DECL|function|sa1100dog_release
r_static
r_int
id|sa1100dog_release
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
id|OSMR3
op_assign
id|OSCR
op_plus
id|pre_margin
suffix:semicolon
r_if
c_cond
(paren
id|expect_close
op_eq
id|SA1100_CLOSE_MAGIC
)paren
(brace
id|OIER
op_and_assign
op_complement
id|OIER_E3
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;WATCHDOG: WDT device closed unexpectedly.  WDT will not stop!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
l_int|1
comma
op_amp
id|sa1100wdt_users
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
DECL|function|sa1100dog_write
r_static
id|ssize_t
id|sa1100dog_write
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
id|SA1100_CLOSE_MAGIC
suffix:semicolon
)brace
)brace
multiline_comment|/* Refresh OSMR3 timer. */
id|OSMR3
op_assign
id|OSCR
op_plus
id|pre_margin
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
l_string|&quot;SA1100 Watchdog&quot;
comma
)brace
suffix:semicolon
DECL|function|sa1100dog_ioctl
r_static
r_int
id|sa1100dog_ioctl
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
l_int|255
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
id|pre_margin
op_assign
id|OSCR_FREQ
op_star
id|time
suffix:semicolon
id|OSMR3
op_assign
id|OSCR
op_plus
id|pre_margin
suffix:semicolon
multiline_comment|/*fall through*/
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
id|ret
op_assign
id|put_user
c_func
(paren
id|pre_margin
op_div
id|OSCR_FREQ
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
id|OSMR3
op_assign
id|OSCR
op_plus
id|pre_margin
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
DECL|variable|sa1100dog_fops
r_static
r_struct
id|file_operations
id|sa1100dog_fops
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
id|sa1100dog_write
comma
dot
id|ioctl
op_assign
id|sa1100dog_ioctl
comma
dot
id|open
op_assign
id|sa1100dog_open
comma
dot
id|release
op_assign
id|sa1100dog_release
comma
)brace
suffix:semicolon
DECL|variable|sa1100dog_miscdev
r_static
r_struct
id|miscdevice
id|sa1100dog_miscdev
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
l_string|&quot;SA1100/PXA2xx watchdog&quot;
comma
dot
id|fops
op_assign
op_amp
id|sa1100dog_fops
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|margin
id|__initdata
op_assign
l_int|60
suffix:semicolon
multiline_comment|/* (secs) Default is 1 minute */
DECL|function|sa1100dog_init
r_static
r_int
id|__init
id|sa1100dog_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Read the reset status, and save it for later.  If&n;&t; * we suspend, RCSR will be cleared, and the watchdog&n;&t; * reset reason will be lost.&n;&t; */
id|boot_status
op_assign
(paren
id|RCSR
op_amp
id|RCSR_WDR
)paren
ques
c_cond
id|WDIOF_CARDRESET
suffix:colon
l_int|0
suffix:semicolon
id|pre_margin
op_assign
id|OSCR_FREQ
op_star
id|margin
suffix:semicolon
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|sa1100dog_miscdev
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
l_string|&quot;SA1100/PXA2xx Watchdog Timer: timer margin %d sec&bslash;n&quot;
comma
id|margin
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sa1100dog_exit
r_static
r_void
id|__exit
id|sa1100dog_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|sa1100dog_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|sa1100dog_init
id|module_init
c_func
(paren
id|sa1100dog_init
)paren
suffix:semicolon
DECL|variable|sa1100dog_exit
id|module_exit
c_func
(paren
id|sa1100dog_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Oleg Drokin &lt;green@crimea.edu&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SA1100/PXA2xx Watchdog&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|margin
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|margin
comma
l_string|&quot;Watchdog margin in seconds (default 60s)&quot;
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
