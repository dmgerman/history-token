multiline_comment|/*&n; * drivers/base/memblk.c - basic Memory Block class support&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/memblk.h&gt;
macro_line|#include &lt;linux/node.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
DECL|function|memblk_add_device
r_static
r_int
id|memblk_add_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|memblk_devclass
r_struct
id|device_class
id|memblk_devclass
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;memblk&quot;
comma
dot
id|add_device
op_assign
id|memblk_add_device
comma
)brace
suffix:semicolon
DECL|variable|memblk_driver
r_struct
id|device_driver
id|memblk_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;memblk&quot;
comma
dot
id|bus
op_assign
op_amp
id|system_bus_type
comma
dot
id|devclass
op_assign
op_amp
id|memblk_devclass
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * register_memblk - Setup a driverfs device for a MemBlk&n; * @num - MemBlk number to use when creating the device.&n; *&n; * Initialize and register the MemBlk device.&n; */
DECL|function|register_memblk
r_int
id|__init
id|register_memblk
c_func
(paren
r_struct
id|memblk
op_star
id|memblk
comma
r_int
id|num
comma
r_struct
id|node
op_star
id|root
)paren
(brace
id|memblk-&gt;node_id
op_assign
id|__memblk_to_node
c_func
(paren
id|num
)paren
suffix:semicolon
id|memblk-&gt;sysdev.name
op_assign
l_string|&quot;memblk&quot;
suffix:semicolon
id|memblk-&gt;sysdev.id
op_assign
id|num
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
id|memblk-&gt;sysdev.root
op_assign
op_amp
id|root-&gt;sysroot
suffix:semicolon
id|snprintf
c_func
(paren
id|memblk-&gt;sysdev.dev.name
comma
id|DEVICE_NAME_SIZE
comma
l_string|&quot;Memory Block %u&quot;
comma
id|num
)paren
suffix:semicolon
id|memblk-&gt;sysdev.dev.driver
op_assign
op_amp
id|memblk_driver
suffix:semicolon
r_return
id|sys_device_register
c_func
(paren
op_amp
id|memblk-&gt;sysdev
)paren
suffix:semicolon
)brace
DECL|function|register_memblk_type
r_static
r_int
id|__init
id|register_memblk_type
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
id|devclass_register
c_func
(paren
op_amp
id|memblk_devclass
)paren
suffix:semicolon
r_return
id|error
ques
c_cond
id|error
suffix:colon
id|driver_register
c_func
(paren
op_amp
id|memblk_driver
)paren
suffix:semicolon
)brace
DECL|variable|register_memblk_type
id|postcore_initcall
c_func
(paren
id|register_memblk_type
)paren
suffix:semicolon
eof
