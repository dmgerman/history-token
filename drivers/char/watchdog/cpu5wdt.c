multiline_comment|/*&n; * sma cpu5 watchdog driver&n; *&n; * Copyright (C) 2003 Heiko Ronsdorf &lt;hero@ihg.uni-duisburg.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
multiline_comment|/* adjustable parameters */
DECL|variable|verbose
r_static
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
DECL|variable|port
r_static
r_int
id|port
op_assign
l_int|0x91
suffix:semicolon
DECL|variable|ticks
r_static
r_int
id|ticks
op_assign
l_int|10000
suffix:semicolon
DECL|macro|PFX
mdefine_line|#define PFX&t;&t;&t;&quot;cpu5wdt: &quot;
DECL|macro|CPU5WDT_EXTENT
mdefine_line|#define CPU5WDT_EXTENT          0x0A
DECL|macro|CPU5WDT_STATUS_REG
mdefine_line|#define CPU5WDT_STATUS_REG      0x00
DECL|macro|CPU5WDT_TIME_A_REG
mdefine_line|#define CPU5WDT_TIME_A_REG      0x02
DECL|macro|CPU5WDT_TIME_B_REG
mdefine_line|#define CPU5WDT_TIME_B_REG      0x03
DECL|macro|CPU5WDT_MODE_REG
mdefine_line|#define CPU5WDT_MODE_REG        0x04
DECL|macro|CPU5WDT_TRIGGER_REG
mdefine_line|#define CPU5WDT_TRIGGER_REG     0x07
DECL|macro|CPU5WDT_ENABLE_REG
mdefine_line|#define CPU5WDT_ENABLE_REG      0x08
DECL|macro|CPU5WDT_RESET_REG
mdefine_line|#define CPU5WDT_RESET_REG       0x09
DECL|macro|CPU5WDT_INTERVAL
mdefine_line|#define CPU5WDT_INTERVAL&t;(HZ/10+1)
multiline_comment|/* some device data */
r_static
r_struct
(brace
DECL|member|stop
r_struct
id|semaphore
id|stop
suffix:semicolon
DECL|member|running
r_volatile
r_int
id|running
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|queue
r_volatile
r_int
id|queue
suffix:semicolon
DECL|member|default_ticks
r_int
id|default_ticks
suffix:semicolon
DECL|member|inuse
r_int
r_int
id|inuse
suffix:semicolon
DECL|variable|cpu5wdt_device
)brace
id|cpu5wdt_device
suffix:semicolon
multiline_comment|/* generic helper functions */
DECL|function|cpu5wdt_trigger
r_static
r_void
id|cpu5wdt_trigger
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
r_if
c_cond
(paren
id|verbose
OG
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;trigger at %i ticks&bslash;n&quot;
comma
id|ticks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu5wdt_device.running
)paren
(brace
id|ticks
op_decrement
suffix:semicolon
)brace
multiline_comment|/* keep watchdog alive */
id|outb
c_func
(paren
l_int|1
comma
id|port
op_plus
id|CPU5WDT_TRIGGER_REG
)paren
suffix:semicolon
multiline_comment|/* requeue?? */
r_if
c_cond
(paren
id|cpu5wdt_device.queue
op_logical_and
id|ticks
)paren
(brace
id|cpu5wdt_device.timer.expires
op_assign
id|jiffies
op_plus
id|CPU5WDT_INTERVAL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|cpu5wdt_device.timer
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ticks doesn&squot;t matter anyway */
id|up
c_func
(paren
op_amp
id|cpu5wdt_device.stop
)paren
suffix:semicolon
)brace
)brace
DECL|function|cpu5wdt_reset
r_static
r_void
id|cpu5wdt_reset
c_func
(paren
r_void
)paren
(brace
id|ticks
op_assign
id|cpu5wdt_device.default_ticks
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;reset (%i ticks)&bslash;n&quot;
comma
(paren
r_int
)paren
id|ticks
)paren
suffix:semicolon
)brace
DECL|function|cpu5wdt_start
r_static
r_void
id|cpu5wdt_start
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu5wdt_device.queue
)paren
(brace
id|cpu5wdt_device.queue
op_assign
l_int|1
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|port
op_plus
id|CPU5WDT_TIME_A_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|port
op_plus
id|CPU5WDT_TIME_B_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|1
comma
id|port
op_plus
id|CPU5WDT_MODE_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|port
op_plus
id|CPU5WDT_RESET_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|port
op_plus
id|CPU5WDT_ENABLE_REG
)paren
suffix:semicolon
id|cpu5wdt_device.timer.expires
op_assign
id|jiffies
op_plus
id|CPU5WDT_INTERVAL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|cpu5wdt_device.timer
)paren
suffix:semicolon
)brace
multiline_comment|/* if process dies, counter is not decremented */
id|cpu5wdt_device.running
op_increment
suffix:semicolon
)brace
DECL|function|cpu5wdt_stop
r_static
r_int
id|cpu5wdt_stop
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cpu5wdt_device.running
)paren
id|cpu5wdt_device.running
op_assign
l_int|0
suffix:semicolon
id|ticks
op_assign
id|cpu5wdt_device.default_ticks
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
id|KERN_CRIT
id|PFX
l_string|&quot;stop not possible&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* filesystem operations */
DECL|function|cpu5wdt_open
r_static
r_int
id|cpu5wdt_open
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
id|cpu5wdt_device.inuse
)paren
)paren
r_return
op_minus
id|EBUSY
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
DECL|function|cpu5wdt_release
r_static
r_int
id|cpu5wdt_release
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
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|cpu5wdt_device.inuse
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpu5wdt_ioctl
r_static
r_int
id|cpu5wdt_ioctl
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
r_int
id|value
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
id|WDIOF_CARDRESET
comma
dot
id|identity
op_assign
l_string|&quot;CPU5 WDT&quot;
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
id|WDIOC_KEEPALIVE
suffix:colon
id|cpu5wdt_reset
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
id|value
op_assign
id|inb
c_func
(paren
id|port
op_plus
id|CPU5WDT_STATUS_REG
)paren
suffix:semicolon
id|value
op_assign
(paren
id|value
op_rshift
l_int|2
)paren
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|value
comma
r_sizeof
(paren
r_int
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
id|WDIOC_GETSUPPORT
suffix:colon
r_if
c_cond
(paren
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
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
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
id|value
comma
id|argp
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|value
)paren
(brace
r_case
id|WDIOS_ENABLECARD
suffix:colon
id|cpu5wdt_start
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WDIOS_DISABLECARD
suffix:colon
r_return
id|cpu5wdt_stop
c_func
(paren
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
DECL|function|cpu5wdt_write
r_static
id|ssize_t
id|cpu5wdt_write
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
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|cpu5wdt_reset
c_func
(paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|cpu5wdt_fops
r_static
r_struct
id|file_operations
id|cpu5wdt_fops
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
id|ioctl
op_assign
id|cpu5wdt_ioctl
comma
dot
id|open
op_assign
id|cpu5wdt_open
comma
dot
id|write
op_assign
id|cpu5wdt_write
comma
dot
id|release
op_assign
id|cpu5wdt_release
comma
)brace
suffix:semicolon
DECL|variable|cpu5wdt_misc
r_static
r_struct
id|miscdevice
id|cpu5wdt_misc
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
id|cpu5wdt_fops
comma
)brace
suffix:semicolon
multiline_comment|/* init/exit function */
DECL|function|cpu5wdt_init
r_static
r_int
id|__devinit
id|cpu5wdt_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;port=0x%x, verbose=%i&bslash;n&quot;
comma
id|port
comma
id|verbose
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|misc_register
c_func
(paren
op_amp
id|cpu5wdt_misc
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;misc_register failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|no_misc
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|port
comma
id|CPU5WDT_EXTENT
comma
id|PFX
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;request_region failed&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|no_port
suffix:semicolon
)brace
multiline_comment|/* watchdog reboot? */
id|val
op_assign
id|inb
c_func
(paren
id|port
op_plus
id|CPU5WDT_STATUS_REG
)paren
suffix:semicolon
id|val
op_assign
(paren
id|val
op_rshift
l_int|2
)paren
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;sorry, was my fault&bslash;n&quot;
)paren
suffix:semicolon
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|cpu5wdt_device.stop
)paren
suffix:semicolon
id|cpu5wdt_device.queue
op_assign
l_int|0
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|cpu5wdt_device.inuse
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|cpu5wdt_device.timer
)paren
suffix:semicolon
id|cpu5wdt_device.timer.function
op_assign
id|cpu5wdt_trigger
suffix:semicolon
id|cpu5wdt_device.timer.data
op_assign
l_int|0
suffix:semicolon
id|cpu5wdt_device.default_ticks
op_assign
id|ticks
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;init success&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|no_port
suffix:colon
id|misc_deregister
c_func
(paren
op_amp
id|cpu5wdt_misc
)paren
suffix:semicolon
id|no_misc
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|cpu5wdt_init_module
r_static
r_int
id|__devinit
id|cpu5wdt_init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|cpu5wdt_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cpu5wdt_exit
r_static
r_void
id|__devexit
id|cpu5wdt_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cpu5wdt_device.queue
)paren
(brace
id|cpu5wdt_device.queue
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cpu5wdt_device.stop
)paren
suffix:semicolon
)brace
id|misc_deregister
c_func
(paren
op_amp
id|cpu5wdt_misc
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|port
comma
id|CPU5WDT_EXTENT
)paren
suffix:semicolon
)brace
DECL|function|cpu5wdt_exit_module
r_static
r_void
id|__devexit
id|cpu5wdt_exit_module
c_func
(paren
r_void
)paren
(brace
id|cpu5wdt_exit
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* module entry points */
DECL|variable|cpu5wdt_init_module
id|module_init
c_func
(paren
id|cpu5wdt_init_module
)paren
suffix:semicolon
DECL|variable|cpu5wdt_exit_module
id|module_exit
c_func
(paren
id|cpu5wdt_exit_module
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Heiko Ronsdorf &lt;hero@ihg.uni-duisburg.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;sma cpu5 watchdog driver&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;sma cpu5 watchdog&quot;
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
id|module_param
c_func
(paren
id|port
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|port
comma
l_string|&quot;base address of watchdog card, default is 0x91&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|verbose
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|verbose
comma
l_string|&quot;be verbose, default is 0 (no)&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|ticks
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ticks
comma
l_string|&quot;count down ticks, default is 10000&quot;
)paren
suffix:semicolon
eof
