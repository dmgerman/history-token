multiline_comment|/* $Id: display7seg.c,v 1.6 2002/01/08 16:00:16 davem Exp $&n; *&n; * display7seg - Driver implementation for the 7-segment display&n; * present on Sun Microsystems CP1400 and CP1500&n; *&n; * Copyright (c) 2000 Eric Brower (ebrower@usa.net)&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;&t;&t;/* request_region, check_region */
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;&t;&t;&t;/* EBus device&t;&t;&t;&t;&t;*/
macro_line|#include &lt;asm/oplib.h&gt;&t;&t;&t;/* OpenProm Library &t;&t;&t;*/
macro_line|#include &lt;asm/uaccess.h&gt;&t;&t;/* put_/get_user&t;&t;&t;*/
macro_line|#include &lt;asm/display7seg.h&gt;
DECL|macro|D7S_MINOR
mdefine_line|#define D7S_MINOR&t;193
DECL|macro|D7S_OBPNAME
mdefine_line|#define D7S_OBPNAME&t;&quot;display7seg&quot;
DECL|macro|D7S_DEVNAME
mdefine_line|#define D7S_DEVNAME &quot;d7s&quot;
DECL|variable|sol_compat
r_static
r_int
id|sol_compat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Solaris compatibility mode&t;*/
macro_line|#ifdef MODULE
multiline_comment|/* Solaris compatibility flag -&n; * The Solaris implementation omits support for several&n; * documented driver features (ref Sun doc 806-0180-03).  &n; * By default, this module supports the documented driver &n; * abilities, rather than the Solaris implementation:&n; *&n; * &t;1) Device ALWAYS reverts to OBP-specified FLIPPED mode&n; * &t;   upon closure of device or module unload.&n; * &t;2) Device ioctls D7SIOCRD/D7SIOCWR honor toggling of&n; * &t;   FLIP bit&n; *&n; * If you wish the device to operate as under Solaris,&n; * omitting above features, set this parameter to non-zero.&n; */
id|MODULE_PARM
(paren
id|sol_compat
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|sol_compat
comma
l_string|&quot;Disables documented functionality omitted from Solaris driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Eric Brower &lt;ebrower@usa.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;7-Segment Display driver for Sun Microsystems CP1400/1500&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
(paren
l_string|&quot;d7s&quot;
)paren
suffix:semicolon
macro_line|#endif /* ifdef MODULE */
multiline_comment|/*&n; * Register block address- see header for details&n; * -----------------------------------------&n; * | DP | ALARM | FLIP | 4 | 3 | 2 | 1 | 0 |&n; * -----------------------------------------&n; *&n; * DP &t;&t;- Toggles decimal point on/off &n; * ALARM&t;- Toggles &quot;Alarm&quot; LED green/red&n; * FLIP&t;&t;- Inverts display for upside-down mounted board&n; * bits 0-4&t;- 7-segment display contents&n; */
DECL|variable|d7s_regs
r_static
r_void
id|__iomem
op_star
id|d7s_regs
suffix:semicolon
DECL|function|d7s_free
r_static
r_inline
r_void
id|d7s_free
c_func
(paren
r_void
)paren
(brace
id|iounmap
c_func
(paren
id|d7s_regs
)paren
suffix:semicolon
)brace
DECL|function|d7s_obpflipped
r_static
r_inline
r_int
id|d7s_obpflipped
c_func
(paren
r_void
)paren
(brace
r_int
id|opt_node
suffix:semicolon
id|opt_node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|opt_node
op_assign
id|prom_searchsiblings
c_func
(paren
id|opt_node
comma
l_string|&quot;options&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
op_minus
l_int|1
op_ne
id|prom_getintdefault
c_func
(paren
id|opt_node
comma
l_string|&quot;d7s-flipped?&quot;
comma
op_minus
l_int|1
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|d7s_users
r_static
id|atomic_t
id|d7s_users
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|function|d7s_open
r_static
r_int
id|d7s_open
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
id|f
)paren
(brace
r_if
c_cond
(paren
id|D7S_MINOR
op_ne
id|iminor
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|d7s_users
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|d7s_release
r_static
r_int
id|d7s_release
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
id|f
)paren
(brace
multiline_comment|/* Reset flipped state to OBP default only if&n;&t; * no other users have the device open and we&n;&t; * are not operating in solaris-compat mode&n;&t; */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|d7s_users
)paren
op_logical_and
op_logical_neg
id|sol_compat
)paren
(brace
r_int
id|regval
op_assign
l_int|0
suffix:semicolon
id|regval
op_assign
id|readb
c_func
(paren
id|d7s_regs
)paren
suffix:semicolon
(paren
l_int|0
op_eq
id|d7s_obpflipped
c_func
(paren
)paren
)paren
ques
c_cond
id|writeb
c_func
(paren
id|regval
op_or_assign
id|D7S_FLIP
comma
id|d7s_regs
)paren
suffix:colon
id|writeb
c_func
(paren
id|regval
op_and_assign
op_complement
id|D7S_FLIP
comma
id|d7s_regs
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|d7s_ioctl
r_static
r_int
id|d7s_ioctl
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
id|f
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
id|__u8
id|regs
op_assign
id|readb
c_func
(paren
id|d7s_regs
)paren
suffix:semicolon
id|__u8
id|ireg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|D7S_MINOR
op_ne
id|iminor
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|D7SIOCWR
suffix:colon
multiline_comment|/* assign device register values&n;&t;&t; * we mask-out D7S_FLIP if in sol_compat mode&n;&t;&t; */
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|ireg
comma
(paren
r_int
id|__user
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
l_int|0
op_ne
id|sol_compat
)paren
(brace
(paren
id|regs
op_amp
id|D7S_FLIP
)paren
ques
c_cond
(paren
id|ireg
op_or_assign
id|D7S_FLIP
)paren
suffix:colon
(paren
id|ireg
op_and_assign
op_complement
id|D7S_FLIP
)paren
suffix:semicolon
)brace
id|writeb
c_func
(paren
id|ireg
comma
id|d7s_regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|D7SIOCRD
suffix:colon
multiline_comment|/* retrieve device register values&n;&t;&t; * NOTE: Solaris implementation returns D7S_FLIP bit&n;&t;&t; * as toggled by user, even though it does not honor it.&n;&t;&t; * This driver will not misinform you about the state&n;&t;&t; * of your hardware while in sol_compat mode&n;&t;&t; */
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|regs
comma
(paren
r_int
id|__user
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
id|D7SIOCTM
suffix:colon
multiline_comment|/* toggle device mode-- flip display orientation */
(paren
id|regs
op_amp
id|D7S_FLIP
)paren
ques
c_cond
(paren
id|regs
op_and_assign
op_complement
id|D7S_FLIP
)paren
suffix:colon
(paren
id|regs
op_or_assign
id|D7S_FLIP
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|regs
comma
id|d7s_regs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|d7s_fops
r_static
r_struct
id|file_operations
id|d7s_fops
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
id|d7s_ioctl
comma
dot
id|open
op_assign
id|d7s_open
comma
dot
id|release
op_assign
id|d7s_release
comma
)brace
suffix:semicolon
DECL|variable|d7s_miscdev
r_static
r_struct
id|miscdevice
id|d7s_miscdev
op_assign
(brace
id|D7S_MINOR
comma
id|D7S_DEVNAME
comma
op_amp
id|d7s_fops
)brace
suffix:semicolon
DECL|function|d7s_init
r_static
r_int
id|__init
id|d7s_init
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
r_int
id|iTmp
op_assign
l_int|0
comma
id|regs
op_assign
l_int|0
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
id|D7S_OBPNAME
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
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to locate device&bslash;n&quot;
comma
id|D7S_DEVNAME
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|d7s_regs
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
r_sizeof
(paren
id|__u8
)paren
)paren
suffix:semicolon
id|iTmp
op_assign
id|misc_register
c_func
(paren
op_amp
id|d7s_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|iTmp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to acquire miscdevice minor %i&bslash;n&quot;
comma
id|D7S_DEVNAME
comma
id|D7S_MINOR
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|d7s_regs
)paren
suffix:semicolon
r_return
id|iTmp
suffix:semicolon
)brace
multiline_comment|/* OBP option &quot;d7s-flipped?&quot; is honored as default&n;&t; * for the device, and reset default when detached&n;&t; */
id|regs
op_assign
id|readb
c_func
(paren
id|d7s_regs
)paren
suffix:semicolon
id|iTmp
op_assign
id|d7s_obpflipped
c_func
(paren
)paren
suffix:semicolon
(paren
l_int|0
op_eq
id|iTmp
)paren
ques
c_cond
id|writeb
c_func
(paren
id|regs
op_or_assign
id|D7S_FLIP
comma
id|d7s_regs
)paren
suffix:colon
id|writeb
c_func
(paren
id|regs
op_and_assign
op_complement
id|D7S_FLIP
comma
id|d7s_regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: 7-Segment Display%s at 0x%lx %s&bslash;n&quot;
comma
id|D7S_DEVNAME
comma
(paren
l_int|0
op_eq
id|iTmp
)paren
ques
c_cond
(paren
l_string|&quot; (FLIPPED)&quot;
)paren
suffix:colon
(paren
l_string|&quot;&quot;
)paren
comma
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
comma
(paren
l_int|0
op_ne
id|sol_compat
)paren
ques
c_cond
(paren
l_string|&quot;in sol_compat mode&quot;
)paren
suffix:colon
(paren
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|d7s_cleanup
r_static
r_void
id|__exit
id|d7s_cleanup
c_func
(paren
r_void
)paren
(brace
r_int
id|regs
op_assign
id|readb
c_func
(paren
id|d7s_regs
)paren
suffix:semicolon
multiline_comment|/* Honor OBP d7s-flipped? unless operating in solaris-compat mode */
r_if
c_cond
(paren
l_int|0
op_eq
id|sol_compat
)paren
(brace
(paren
l_int|0
op_eq
id|d7s_obpflipped
c_func
(paren
)paren
)paren
ques
c_cond
id|writeb
c_func
(paren
id|regs
op_or_assign
id|D7S_FLIP
comma
id|d7s_regs
)paren
suffix:colon
id|writeb
c_func
(paren
id|regs
op_and_assign
op_complement
id|D7S_FLIP
comma
id|d7s_regs
)paren
suffix:semicolon
)brace
id|misc_deregister
c_func
(paren
op_amp
id|d7s_miscdev
)paren
suffix:semicolon
id|d7s_free
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|d7s_init
id|module_init
c_func
(paren
id|d7s_init
)paren
suffix:semicolon
DECL|variable|d7s_cleanup
id|module_exit
c_func
(paren
id|d7s_cleanup
)paren
suffix:semicolon
eof
