multiline_comment|/*&n; * drivers/base/hotplug.c - hotplug call code&n; * &n; * Copyright (c) 2000-2001 David Brownell&n; * Copyright (c) 2002 Greg Kroah-Hartman&n; * Copyright (c) 2002 IBM Corp.&n; *&n; * Based off of drivers/usb/core/usb.c:call_agent(), which was &n; * written by David Brownell.&n; *&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;base.h&quot;
macro_line|#include &quot;fs/fs.h&quot;
multiline_comment|/*&n; * hotplugging invokes what /proc/sys/kernel/hotplug says (normally&n; * /sbin/hotplug) when devices or classes get added or removed.&n; *&n; * This invokes a user mode policy agent, typically helping to load driver&n; * or other modules, configure the device, and more.  Drivers can provide&n; * a MODULE_DEVICE_TABLE to help with module loading subtasks.&n; *&n; * See the documentation at http://linux-hotplug.sf.net for more info.&n; * &n; */
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE&t;1024&t;/* should be enough memory for the env */
DECL|macro|NUM_ENVP
mdefine_line|#define NUM_ENVP&t;32&t;/* number of env pointers */
DECL|variable|prefix
r_static
r_char
id|prefix
(braket
)braket
op_assign
l_string|&quot;devices&quot;
suffix:semicolon
multiline_comment|/* /sys/devices/... */
DECL|function|do_hotplug
r_static
r_int
id|do_hotplug
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|argv1
comma
r_const
r_char
op_star
id|action
comma
r_int
(paren
op_star
id|hotplug
)paren
(paren
r_struct
id|device
op_star
comma
r_char
op_star
op_star
comma
r_int
comma
r_char
op_star
comma
r_int
)paren
)paren
(brace
r_char
op_star
id|argv
(braket
l_int|3
)braket
comma
op_star
op_star
id|envp
comma
op_star
id|buffer
comma
op_star
id|scratch
suffix:semicolon
r_char
op_star
id|dev_path
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|dev_length
suffix:semicolon
id|pr_debug
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hotplug_path
(braket
l_int|0
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
(paren
)paren
)paren
(brace
id|pr_debug
(paren
l_string|&quot;%s - in_interrupt, not allowed!&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;fs-&gt;root
)paren
(brace
multiline_comment|/* don&squot;t try to do anything unless we have a root partition */
id|pr_debug
(paren
l_string|&quot;%s - %s -- no FS yet&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|action
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|envp
op_assign
(paren
r_char
op_star
op_star
)paren
id|kmalloc
(paren
id|NUM_ENVP
op_star
r_sizeof
(paren
r_char
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|envp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
(paren
id|envp
comma
l_int|0x00
comma
id|NUM_ENVP
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|buffer
op_assign
id|kmalloc
(paren
id|BUFFER_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|kfree
(paren
id|envp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dev_length
op_assign
id|get_devpath_length
(paren
id|dev
)paren
suffix:semicolon
id|dev_length
op_add_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
id|dev_path
op_assign
id|kmalloc
(paren
id|dev_length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_path
)paren
(brace
id|kfree
(paren
id|buffer
)paren
suffix:semicolon
id|kfree
(paren
id|envp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
(paren
id|dev_path
comma
l_int|0x00
comma
id|dev_length
)paren
suffix:semicolon
id|strcpy
(paren
id|dev_path
comma
id|prefix
)paren
suffix:semicolon
id|fill_devpath
(paren
id|dev
comma
id|dev_path
comma
id|dev_length
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|hotplug_path
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
id|argv1
suffix:semicolon
id|argv
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* minimal command environment */
id|envp
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;HOME=/&quot;
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;PATH=/sbin:/bin:/usr/sbin:/usr/bin&quot;
suffix:semicolon
id|scratch
op_assign
id|buffer
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|scratch
op_add_assign
id|sprintf
(paren
id|scratch
comma
l_string|&quot;ACTION=%s&quot;
comma
id|action
)paren
op_plus
l_int|1
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|scratch
op_add_assign
id|sprintf
(paren
id|scratch
comma
l_string|&quot;DEVPATH=%s&quot;
comma
id|dev_path
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hotplug
)paren
(brace
multiline_comment|/* have the bus specific function add its stuff */
id|retval
op_assign
id|hotplug
(paren
id|dev
comma
op_amp
id|envp
(braket
id|i
)braket
comma
id|NUM_ENVP
op_minus
id|i
comma
id|scratch
comma
id|BUFFER_SIZE
op_minus
(paren
id|scratch
op_minus
id|buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|pr_debug
(paren
l_string|&quot;%s - hotplug() returned %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
id|pr_debug
(paren
l_string|&quot;%s: %s %s %s %s %s %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
comma
id|envp
(braket
l_int|0
)braket
comma
id|envp
(braket
l_int|1
)braket
comma
id|envp
(braket
l_int|2
)braket
comma
id|envp
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|retval
op_assign
id|call_usermodehelper
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|pr_debug
(paren
l_string|&quot;%s - call_usermodehelper returned %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
m_exit
suffix:colon
id|kfree
(paren
id|dev_path
)paren
suffix:semicolon
id|kfree
(paren
id|buffer
)paren
suffix:semicolon
id|kfree
(paren
id|envp
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * dev_hotplug - called when any device is added or removed from a bus&n; */
DECL|function|dev_hotplug
r_int
id|dev_hotplug
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|action
)paren
(brace
id|pr_debug
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bus
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|do_hotplug
(paren
id|dev
comma
id|dev-&gt;bus-&gt;name
comma
id|action
comma
id|dev-&gt;bus-&gt;hotplug
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * class_hotplug - called when a class is added or removed from a device&n; */
DECL|function|class_hotplug
r_int
id|class_hotplug
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|action
)paren
(brace
r_struct
id|device_class
op_star
id|cls
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|pr_debug
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bus
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|cls
op_assign
id|get_devclass
c_func
(paren
id|dev-&gt;driver-&gt;devclass
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cls
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|retval
op_assign
id|do_hotplug
(paren
id|dev
comma
id|cls-&gt;name
comma
id|action
comma
id|cls-&gt;hotplug
)paren
suffix:semicolon
id|put_devclass
c_func
(paren
id|cls
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
