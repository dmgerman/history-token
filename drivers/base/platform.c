multiline_comment|/*&n; * platform.c - platform &squot;pseudo&squot; bus for legacy devices&n; *&n; * Copyright (c) 2002-3 Patrick Mochel&n; * Copyright (c) 2002-3 Open Source Development Labs&n; * &n; * This file is released under the GPLv2&n; *&n; * Please see Documentation/driver-model/platform.txt for more&n; * information.&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|platform_bus
r_struct
id|device
id|platform_bus
op_assign
(brace
dot
id|bus_id
op_assign
l_string|&quot;platform&quot;
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;platform_device_register - add a platform-level device&n; *&t;@dev:&t;platform device we&squot;re adding&n; *&n; */
DECL|function|platform_device_register
r_int
id|platform_device_register
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev-&gt;dev.parent
)paren
id|pdev-&gt;dev.parent
op_assign
op_amp
id|platform_bus
suffix:semicolon
id|pdev-&gt;dev.bus
op_assign
op_amp
id|platform_bus_type
suffix:semicolon
id|snprintf
c_func
(paren
id|pdev-&gt;dev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%s%u&quot;
comma
id|pdev-&gt;name
comma
id|pdev-&gt;id
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Registering platform device &squot;%s&squot;. Parent at %s&bslash;n&quot;
comma
id|pdev-&gt;dev.bus_id
comma
id|pdev-&gt;dev.parent-&gt;bus_id
)paren
suffix:semicolon
r_return
id|device_register
c_func
(paren
op_amp
id|pdev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|platform_device_unregister
r_void
id|platform_device_unregister
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
r_if
c_cond
(paren
id|pdev
)paren
id|device_unregister
c_func
(paren
op_amp
id|pdev-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;platform_match - bind platform device to platform driver.&n; *&t;@dev:&t;device.&n; *&t;@drv:&t;driver.&n; *&n; *&t;Platform device IDs are assumed to be encoded like this: &n; *&t;&quot;&lt;name&gt;&lt;instance&gt;&quot;, where &lt;name&gt; is a short description of the &n; *&t;type of device, like &quot;pci&quot; or &quot;floppy&quot;, and &lt;instance&gt; is the &n; *&t;enumerated instance of the device, like &squot;0&squot; or &squot;42&squot;.&n; *&t;Driver IDs are simply &quot;&lt;name&gt;&quot;. &n; *&t;So, extract the &lt;name&gt; from the platform_device structure, &n; *&t;and compare it against the name of the driver. Return whether &n; *&t;they match or not.&n; */
DECL|function|platform_match
r_static
r_int
id|platform_match
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|platform_device
op_star
id|pdev
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|platform_device
comma
id|dev
)paren
suffix:semicolon
r_return
(paren
id|strncmp
c_func
(paren
id|pdev-&gt;name
comma
id|drv-&gt;name
comma
id|BUS_ID_SIZE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|platform_suspend
r_static
r_int
id|platform_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
op_logical_and
id|dev-&gt;driver-&gt;suspend
)paren
(brace
id|ret
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
id|SUSPEND_DISABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
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
id|SUSPEND_SAVE_STATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
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
id|SUSPEND_POWER_DOWN
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|platform_resume
r_static
r_int
id|platform_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
op_logical_and
id|dev-&gt;driver-&gt;resume
)paren
(brace
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|RESUME_POWER_ON
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|RESUME_RESTORE_STATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|dev
comma
id|RESUME_ENABLE
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|platform_bus_type
r_struct
id|bus_type
id|platform_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;platform&quot;
comma
dot
id|match
op_assign
id|platform_match
comma
dot
id|suspend
op_assign
id|platform_suspend
comma
dot
id|resume
op_assign
id|platform_resume
comma
)brace
suffix:semicolon
DECL|function|platform_bus_init
r_int
id|__init
id|platform_bus_init
c_func
(paren
r_void
)paren
(brace
id|device_register
c_func
(paren
op_amp
id|platform_bus
)paren
suffix:semicolon
r_return
id|bus_register
c_func
(paren
op_amp
id|platform_bus_type
)paren
suffix:semicolon
)brace
DECL|variable|platform_bus
id|EXPORT_SYMBOL
c_func
(paren
id|platform_bus
)paren
suffix:semicolon
DECL|variable|platform_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|platform_bus_type
)paren
suffix:semicolon
DECL|variable|platform_device_register
id|EXPORT_SYMBOL
c_func
(paren
id|platform_device_register
)paren
suffix:semicolon
DECL|variable|platform_device_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|platform_device_unregister
)paren
suffix:semicolon
eof
