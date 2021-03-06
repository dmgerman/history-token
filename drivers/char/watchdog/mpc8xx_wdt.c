multiline_comment|/*&n; * mpc8xx_wdt.c - MPC8xx watchdog userspace interface&n; *&n; * Author: Florian Schirmer &lt;jolt@tuxbox.org&gt;&n; *&n; * 2002 (c) Florian Schirmer &lt;jolt@tuxbox.org&gt; This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;syslib/m8xx_wdt.h&gt;
DECL|variable|wdt_opened
r_static
r_int
r_int
id|wdt_opened
suffix:semicolon
DECL|variable|wdt_status
r_static
r_int
id|wdt_status
suffix:semicolon
DECL|function|mpc8xx_wdt_handler_disable
r_static
r_void
id|mpc8xx_wdt_handler_disable
c_func
(paren
r_void
)paren
(brace
r_volatile
id|immap_t
op_star
id|imap
op_assign
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|imap-&gt;im_sit.sit_piscr
op_and_assign
op_complement
(paren
id|PISCR_PIE
op_or
id|PISCR_PTE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;mpc8xx_wdt: keep-alive handler deactivated&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|mpc8xx_wdt_handler_enable
r_static
r_void
id|mpc8xx_wdt_handler_enable
c_func
(paren
r_void
)paren
(brace
r_volatile
id|immap_t
op_star
id|imap
op_assign
(paren
r_volatile
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|imap-&gt;im_sit.sit_piscr
op_or_assign
id|PISCR_PIE
op_or
id|PISCR_PTE
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;mpc8xx_wdt: keep-alive handler activated&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|mpc8xx_wdt_open
r_static
r_int
id|mpc8xx_wdt_open
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
id|wdt_opened
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|m8xx_wdt_reset
c_func
(paren
)paren
suffix:semicolon
id|mpc8xx_wdt_handler_disable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mpc8xx_wdt_release
r_static
r_int
id|mpc8xx_wdt_release
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
id|m8xx_wdt_reset
c_func
(paren
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_WATCHDOG_NOWAYOUT)
id|mpc8xx_wdt_handler_enable
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|wdt_opened
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mpc8xx_wdt_write
r_static
id|ssize_t
id|mpc8xx_wdt_write
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
id|m8xx_wdt_reset
c_func
(paren
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|mpc8xx_wdt_ioctl
r_static
r_int
id|mpc8xx_wdt_ioctl
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
id|timeout
suffix:semicolon
r_static
r_struct
id|watchdog_info
id|info
op_assign
(brace
dot
id|options
op_assign
id|WDIOF_KEEPALIVEPING
comma
dot
id|firmware_version
op_assign
l_int|0
comma
dot
id|identity
op_assign
l_string|&quot;MPC8xx watchdog&quot;
comma
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
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_case
id|WDIOC_GETBOOTSTATUS
suffix:colon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|wdt_status
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
id|wdt_status
op_and_assign
op_complement
id|WDIOF_KEEPALIVEPING
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_GETTEMP
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|WDIOC_SETOPTIONS
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|m8xx_wdt_reset
c_func
(paren
)paren
suffix:semicolon
id|wdt_status
op_or_assign
id|WDIOF_KEEPALIVEPING
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_SETTIMEOUT
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
id|timeout
op_assign
id|m8xx_wdt_get_timeout
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|timeout
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
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mpc8xx_wdt_fops
r_static
r_struct
id|file_operations
id|mpc8xx_wdt_fops
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
id|mpc8xx_wdt_write
comma
dot
id|ioctl
op_assign
id|mpc8xx_wdt_ioctl
comma
dot
id|open
op_assign
id|mpc8xx_wdt_open
comma
dot
id|release
op_assign
id|mpc8xx_wdt_release
comma
)brace
suffix:semicolon
DECL|variable|mpc8xx_wdt_miscdev
r_static
r_struct
id|miscdevice
id|mpc8xx_wdt_miscdev
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
id|mpc8xx_wdt_fops
comma
)brace
suffix:semicolon
DECL|function|mpc8xx_wdt_init
r_static
r_int
id|__init
id|mpc8xx_wdt_init
c_func
(paren
r_void
)paren
(brace
r_return
id|misc_register
c_func
(paren
op_amp
id|mpc8xx_wdt_miscdev
)paren
suffix:semicolon
)brace
DECL|function|mpc8xx_wdt_exit
r_static
r_void
id|__exit
id|mpc8xx_wdt_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|mpc8xx_wdt_miscdev
)paren
suffix:semicolon
id|m8xx_wdt_reset
c_func
(paren
)paren
suffix:semicolon
id|mpc8xx_wdt_handler_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|mpc8xx_wdt_init
id|module_init
c_func
(paren
id|mpc8xx_wdt_init
)paren
suffix:semicolon
DECL|variable|mpc8xx_wdt_exit
id|module_exit
c_func
(paren
id|mpc8xx_wdt_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Florian Schirmer &lt;jolt@tuxbox.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MPC8xx watchdog driver&quot;
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
