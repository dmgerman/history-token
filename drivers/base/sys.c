multiline_comment|/*&n; * sys.c - pseudo-bus for system &squot;devices&squot; (cpus, PICs, timers, etc)&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; *               2002-3 Open Source Development Lab&n; *&n; * This file is released under the GPLv2&n; * &n; * This exports a &squot;system&squot; bus type. &n; * By default, a &squot;sys&squot; bus gets added to the root of the system. There will&n; * always be core system devices. Devices can use sys_device_register() to&n; * add themselves as children of the system bus.&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/* The default system device parent. */
DECL|variable|system_bus
r_static
r_struct
id|device
id|system_bus
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;System Bus&quot;
comma
dot
id|bus_id
op_assign
l_string|&quot;sys&quot;
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;sys_register_root - add a subordinate system root&n; *&t;@root:&t;new root&n; *&t;&n; *&t;This is for NUMA-like systems so they can accurately &n; *&t;represent the topology of the entire system.&n; *&t;As boards are discovered, a new struct sys_root should &n; *&t;be allocated and registered. &n; *&t;The discovery mechanism should initialize the id field&n; *&t;of the struture, as well as much of the embedded device&n; *&t;structure as possible, inlcuding the name, the bus_id&n; *&t;and parent fields.&n; *&n; *&t;This simply calls device_register on the embedded device.&n; *&t;On success, it will use the struct @root-&gt;sysdev &n; *&t;device to create a pseudo-parent for system devices&n; *&t;on that board.&n; *&n; *&t;The platform code can then use @root to specifiy the&n; *&t;controlling board when discovering and registering &n; *&t;system devices.&n; */
DECL|function|sys_register_root
r_int
id|sys_register_root
c_func
(paren
r_struct
id|sys_root
op_star
id|root
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root-&gt;dev.parent
)paren
id|root-&gt;dev.parent
op_assign
op_amp
id|system_bus
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Registering system board %d&bslash;n&quot;
comma
id|root-&gt;id
)paren
suffix:semicolon
id|error
op_assign
id|device_register
c_func
(paren
op_amp
id|root-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|strlcpy
c_func
(paren
id|root-&gt;sysdev.bus_id
comma
l_string|&quot;sys&quot;
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|root-&gt;sysdev.name
comma
l_string|&quot;System Bus&quot;
comma
id|DEVICE_NAME_SIZE
)paren
suffix:semicolon
id|root-&gt;sysdev.parent
op_assign
op_amp
id|root-&gt;dev
suffix:semicolon
id|error
op_assign
id|device_register
c_func
(paren
op_amp
id|root-&gt;sysdev
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sys_unregister_root - remove subordinate root from tree&n; *&t;@root:&t;subordinate root in question.&n; *&n; *&t;We only decrement the reference count on @root-&gt;sysdev &n; *&t;and @root-&gt;dev.&n; *&t;If both are 0, they will be cleaned up by the core.&n; */
DECL|function|sys_unregister_root
r_void
id|sys_unregister_root
c_func
(paren
r_struct
id|sys_root
op_star
id|root
)paren
(brace
id|device_unregister
c_func
(paren
op_amp
id|root-&gt;sysdev
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|root-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sys_device_register - add a system device to the tree&n; *&t;@sysdev:&t;device in question&n; *&n; *&t;The hardest part about this is getting the ancestry right.&n; *&t;If the device has a parent - super! We do nothing.&n; *&t;If the device doesn&squot;t, but @dev-&gt;root is set, then we&squot;re&n; *&t;dealing with a NUMA like architecture where each root&n; *&t;has a system pseudo-bus to foster the device.&n; *&t;If not, then we fallback to system_bus (at the top of &n; *&t;this file). &n; *&n; *&t;One way or another, we call device_register() on it and &n; *&t;are done.&n; *&n; *&t;The caller is also responsible for initializing the bus_id &n; *&t;and name fields of @sysdev-&gt;dev.&n; */
DECL|function|sys_device_register
r_int
id|sys_device_register
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sysdev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysdev-&gt;dev.parent
)paren
(brace
r_if
c_cond
(paren
id|sysdev-&gt;root
)paren
id|sysdev-&gt;dev.parent
op_assign
op_amp
id|sysdev-&gt;root-&gt;sysdev
suffix:semicolon
r_else
id|sysdev-&gt;dev.parent
op_assign
op_amp
id|system_bus
suffix:semicolon
)brace
multiline_comment|/* make sure bus type is set */
r_if
c_cond
(paren
op_logical_neg
id|sysdev-&gt;dev.bus
)paren
id|sysdev-&gt;dev.bus
op_assign
op_amp
id|system_bus_type
suffix:semicolon
multiline_comment|/* construct bus_id */
id|snprintf
c_func
(paren
id|sysdev-&gt;dev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%s%u&quot;
comma
id|sysdev-&gt;name
comma
id|sysdev-&gt;id
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Registering system device %s&bslash;n&quot;
comma
id|sysdev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
id|device_register
c_func
(paren
op_amp
id|sysdev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|sys_device_unregister
r_void
id|sys_device_unregister
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
)paren
(brace
r_if
c_cond
(paren
id|sysdev
)paren
id|device_unregister
c_func
(paren
op_amp
id|sysdev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|variable|system_bus_type
r_struct
id|bus_type
id|system_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;system&quot;
comma
)brace
suffix:semicolon
DECL|function|sys_bus_init
r_int
id|__init
id|sys_bus_init
c_func
(paren
r_void
)paren
(brace
id|bus_register
c_func
(paren
op_amp
id|system_bus_type
)paren
suffix:semicolon
r_return
id|device_register
c_func
(paren
op_amp
id|system_bus
)paren
suffix:semicolon
)brace
DECL|variable|system_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|system_bus_type
)paren
suffix:semicolon
DECL|variable|sys_device_register
id|EXPORT_SYMBOL
c_func
(paren
id|sys_device_register
)paren
suffix:semicolon
DECL|variable|sys_device_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|sys_device_unregister
)paren
suffix:semicolon
eof
