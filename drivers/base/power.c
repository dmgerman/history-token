multiline_comment|/*&n; * power.c - power management functions for the device tree.&n; * &n; * Copyright (c) 2002-3 Patrick Mochel&n; *&t;&t; 2002-3 Open Source Development Lab&n; * &n; * This file is released under the GPLv2&n; * &n; *  Kai Germaschewski contributed to the list walking routines.&n; *&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|macro|to_dev
mdefine_line|#define to_dev(node) container_of(node,struct device,kobj.entry)
r_extern
r_struct
id|subsystem
id|devices_subsys
suffix:semicolon
multiline_comment|/**&n; * We handle system devices differently - we suspend and shut them &n; * down first and resume them first. That way, we do anything stupid like&n; * shutting down the interrupt controller before any devices..&n; *&n; * Note that there are not different stages for power management calls - &n; * they only get one called once when interrupts are disabled. &n; */
r_extern
r_int
id|sys_device_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sys_device_suspend
c_func
(paren
id|u32
id|state
)paren
suffix:semicolon
r_extern
r_int
id|sys_device_resume
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; * device_suspend - suspend/remove all devices on the device ree&n; * @state:&t;state we&squot;re entering&n; * @level:&t;what stage of the suspend process we&squot;re at&n; *    (emb: it seems that these two arguments are described backwards of what&n; *          they actually mean .. is this correct?)&n; *&n; * The entries in the global device list are inserted such that they&squot;re in a&n; * depth-first ordering.  So, simply interate over the list, and call the &n; * driver&squot;s suspend or remove callback for each device.&n; */
DECL|function|device_suspend
r_int
id|device_suspend
c_func
(paren
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Suspending devices&bslash;n&quot;
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|node
comma
op_amp
id|devices_subsys.kset.list
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_dev
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
op_logical_and
id|dev-&gt;driver-&gt;suspend
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;suspending device %s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|error
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|suspend
c_func
(paren
id|dev
comma
id|state
comma
id|level
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: suspend returned %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|error
)paren
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|SUSPEND_POWER_DOWN
)paren
id|sys_device_suspend
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * device_resume - resume all the devices in the system&n; * @level:&t;stage of resume process we&squot;re at &n; * &n; * Similar to device_suspend above, though we want to do a breadth-first&n; * walk of the tree to make sure we wake up parents before children.&n; * So, we iterate over the list backward. &n; */
DECL|function|device_resume
r_void
id|device_resume
c_func
(paren
id|u32
id|level
)paren
(brace
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|RESUME_POWER_ON
)paren
id|sys_device_resume
c_func
(paren
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
id|list_for_each_prev
c_func
(paren
id|node
comma
op_amp
id|devices_subsys.kset.list
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_dev
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
op_logical_and
id|dev-&gt;driver-&gt;resume
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;resuming device %s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|level
)paren
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Devices Resumed&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * device_shutdown - call -&gt;remove() on each device to shutdown. &n; */
DECL|function|device_shutdown
r_void
id|device_shutdown
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Shutting down devices&bslash;n&quot;
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|devices_subsys.kset.list
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|to_dev
c_func
(paren
id|entry
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;shutting down %s: &quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
op_logical_and
id|dev-&gt;driver-&gt;shutdown
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Ok&bslash;n&quot;
)paren
suffix:semicolon
id|dev-&gt;driver
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
id|pr_debug
c_func
(paren
l_string|&quot;Ignored.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|devices_subsys.rwsem
)paren
suffix:semicolon
id|sys_device_shutdown
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|device_suspend
id|EXPORT_SYMBOL
c_func
(paren
id|device_suspend
)paren
suffix:semicolon
DECL|variable|device_resume
id|EXPORT_SYMBOL
c_func
(paren
id|device_resume
)paren
suffix:semicolon
DECL|variable|device_shutdown
id|EXPORT_SYMBOL
c_func
(paren
id|device_shutdown
)paren
suffix:semicolon
eof
