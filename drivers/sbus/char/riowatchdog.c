multiline_comment|/* $Id: riowatchdog.c,v 1.3.2.2 2002/01/23 18:48:02 davem Exp $&n; * riowatchdog.c - driver for hw watchdog inside Super I/O of RIO&n; *&n; * Copyright (C) 2001 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#include &lt;asm/bbc.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/watchdog.h&gt;
multiline_comment|/* RIO uses the NatSemi Super I/O power management logical device&n; * as its&squot; watchdog.&n; *&n; * When the watchdog triggers, it asserts a line to the BBC (Boot Bus&n; * Controller) of the machine.  The BBC can only be configured to&n; * trigger a power-on reset when the signal is asserted.  The BBC&n; * can be configured to ignore the signal entirely as well.&n; *&n; * The only Super I/O device register we care about is at index&n; * 0x05 (WDTO_INDEX) which is the watchdog time-out in minutes (1-255).&n; * If set to zero, this disables the watchdog.  When set, the system&n; * must periodically (before watchdog expires) clear (set to zero) and&n; * re-set the watchdog else it will trigger.&n; *&n; * There are two other indexed watchdog registers inside this Super I/O&n; * logical device, but they are unused.  The first, at index 0x06 is&n; * the watchdog control and can be used to make the watchdog timer re-set&n; * when the PS/2 mouse or serial lines show activity.  The second, at&n; * index 0x07 is merely a sampling of the line from the watchdog to the&n; * BBC.&n; *&n; * The watchdog device generates no interrupts.&n; */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David S. Miller &lt;davem@redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Hardware watchdog driver for Sun RIO&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;watchdog&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|RIOWD_NAME
mdefine_line|#define RIOWD_NAME&t;&quot;pmc&quot;
DECL|macro|RIOWD_MINOR
mdefine_line|#define RIOWD_MINOR&t;215
DECL|variable|riowd_lock
r_static
id|spinlock_t
id|riowd_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|bbc_regs
r_static
r_void
op_star
id|bbc_regs
suffix:semicolon
DECL|variable|riowd_regs
r_static
r_void
op_star
id|riowd_regs
suffix:semicolon
DECL|macro|WDTO_INDEX
mdefine_line|#define WDTO_INDEX&t;0x05
DECL|variable|riowd_timeout
r_static
r_int
id|riowd_timeout
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* in minutes */
id|MODULE_PARM
c_func
(paren
id|riowd_timeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|riowd_timeout
comma
l_string|&quot;Watchdog timeout in minutes&quot;
)paren
suffix:semicolon
macro_line|#if 0 /* Currently unused. */
r_static
id|u8
id|riowd_readreg
c_func
(paren
r_int
id|index
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|riowd_lock
comma
id|flags
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|index
comma
id|riowd_regs
op_plus
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
id|readb
c_func
(paren
id|riowd_regs
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|riowd_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
DECL|function|riowd_writereg
r_static
r_void
id|riowd_writereg
c_func
(paren
id|u8
id|val
comma
r_int
id|index
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|riowd_lock
comma
id|flags
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|index
comma
id|riowd_regs
op_plus
l_int|0
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|val
comma
id|riowd_regs
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|riowd_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|riowd_pingtimer
r_static
r_void
id|riowd_pingtimer
c_func
(paren
r_void
)paren
(brace
id|riowd_writereg
c_func
(paren
id|riowd_timeout
comma
id|WDTO_INDEX
)paren
suffix:semicolon
)brace
DECL|function|riowd_stoptimer
r_static
r_void
id|riowd_stoptimer
c_func
(paren
r_void
)paren
(brace
id|u8
id|val
suffix:semicolon
id|riowd_writereg
c_func
(paren
l_int|0
comma
id|WDTO_INDEX
)paren
suffix:semicolon
id|val
op_assign
id|readb
c_func
(paren
id|bbc_regs
op_plus
id|BBC_WDACTION
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|BBC_WDACTION_RST
suffix:semicolon
id|writeb
c_func
(paren
id|val
comma
id|bbc_regs
op_plus
id|BBC_WDACTION
)paren
suffix:semicolon
)brace
DECL|function|riowd_starttimer
r_static
r_void
id|riowd_starttimer
c_func
(paren
r_void
)paren
(brace
id|u8
id|val
suffix:semicolon
id|riowd_writereg
c_func
(paren
id|riowd_timeout
comma
id|WDTO_INDEX
)paren
suffix:semicolon
id|val
op_assign
id|readb
c_func
(paren
id|bbc_regs
op_plus
id|BBC_WDACTION
)paren
suffix:semicolon
id|val
op_or_assign
id|BBC_WDACTION_RST
suffix:semicolon
id|writeb
c_func
(paren
id|val
comma
id|bbc_regs
op_plus
id|BBC_WDACTION
)paren
suffix:semicolon
)brace
DECL|function|riowd_open
r_static
r_int
id|riowd_open
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
id|filp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|riowd_release
r_static
r_int
id|riowd_release
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
id|filp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|riowd_ioctl
r_static
r_int
id|riowd_ioctl
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
id|filp
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
id|info
op_assign
(brace
id|WDIOF_SETTIMEOUT
comma
l_int|0
comma
l_string|&quot;Natl. Semiconductor PC97317&quot;
)brace
suffix:semicolon
r_int
r_int
id|options
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
l_int|0
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
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|riowd_pingtimer
c_func
(paren
)paren
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
id|options
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|options
)paren
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
id|riowd_stoptimer
c_func
(paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|options
op_amp
id|WDIOS_ENABLECARD
)paren
id|riowd_starttimer
c_func
(paren
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
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
(paren
id|new_margin
OL
l_int|60
)paren
op_logical_or
(paren
id|new_margin
OG
(paren
l_int|255
op_star
l_int|60
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|riowd_timeout
op_assign
(paren
id|new_margin
op_plus
l_int|59
)paren
op_div
l_int|60
suffix:semicolon
id|riowd_pingtimer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fall */
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|riowd_timeout
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
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|riowd_write
r_static
id|ssize_t
id|riowd_write
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
id|count
)paren
(brace
id|riowd_pingtimer
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|riowd_fops
r_static
r_struct
id|file_operations
id|riowd_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|riowd_ioctl
comma
dot
id|open
op_assign
id|riowd_open
comma
dot
id|write
op_assign
id|riowd_write
comma
dot
id|release
op_assign
id|riowd_release
comma
)brace
suffix:semicolon
DECL|variable|riowd_miscdev
r_static
r_struct
id|miscdevice
id|riowd_miscdev
op_assign
(brace
id|RIOWD_MINOR
comma
id|RIOWD_NAME
comma
op_amp
id|riowd_fops
)brace
suffix:semicolon
DECL|function|riowd_bbc_init
r_static
r_int
id|__init
id|riowd_bbc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_ebus
op_star
id|ebus
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
op_assign
l_int|NULL
suffix:semicolon
id|u8
id|val
suffix:semicolon
id|for_each_ebus
c_func
(paren
id|ebus
)paren
(brace
id|for_each_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
l_string|&quot;bbc&quot;
)paren
)paren
r_goto
id|found_bbc
suffix:semicolon
)brace
)brace
id|found_bbc
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|edev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|bbc_regs
op_assign
id|ioremap
c_func
(paren
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
comma
id|BBC_REGS_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bbc_regs
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Turn it off. */
id|val
op_assign
id|readb
c_func
(paren
id|bbc_regs
op_plus
id|BBC_WDACTION
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|BBC_WDACTION_RST
suffix:semicolon
id|writeb
c_func
(paren
id|val
comma
id|bbc_regs
op_plus
id|BBC_WDACTION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|riowd_init
r_static
r_int
id|__init
id|riowd_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_ebus
op_star
id|ebus
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
op_assign
l_int|NULL
suffix:semicolon
id|for_each_ebus
c_func
(paren
id|ebus
)paren
(brace
id|for_each_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
id|RIOWD_NAME
)paren
)paren
r_goto
id|ebus_done
suffix:semicolon
)brace
)brace
id|ebus_done
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|edev
)paren
r_goto
id|fail
suffix:semicolon
id|riowd_regs
op_assign
id|ioremap
c_func
(paren
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|riowd_regs
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmc: Cannot map registers.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|riowd_bbc_init
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmc: Failure initializing BBC config.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|riowd_miscdev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmc: Cannot register watchdog misc device.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pmc: Hardware watchdog [%i minutes], &quot;
l_string|&quot;regs at %p&bslash;n&quot;
comma
id|riowd_timeout
comma
id|riowd_regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
r_if
c_cond
(paren
id|riowd_regs
)paren
(brace
id|iounmap
c_func
(paren
id|riowd_regs
)paren
suffix:semicolon
id|riowd_regs
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bbc_regs
)paren
(brace
id|iounmap
c_func
(paren
id|bbc_regs
)paren
suffix:semicolon
id|bbc_regs
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|riowd_cleanup
r_static
r_void
id|__exit
id|riowd_cleanup
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|riowd_miscdev
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|riowd_regs
)paren
suffix:semicolon
id|riowd_regs
op_assign
l_int|NULL
suffix:semicolon
id|iounmap
c_func
(paren
id|bbc_regs
)paren
suffix:semicolon
id|bbc_regs
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|riowd_init
id|module_init
c_func
(paren
id|riowd_init
)paren
suffix:semicolon
DECL|variable|riowd_cleanup
id|module_exit
c_func
(paren
id|riowd_cleanup
)paren
suffix:semicolon
eof
