multiline_comment|/*&n; * drivers/base/cpu.c - basic CPU class support&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
DECL|variable|cpu_class
r_struct
r_class
id|cpu_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cpu&quot;
comma
)brace
suffix:semicolon
DECL|variable|cpu_driver
r_struct
id|device_driver
id|cpu_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cpu&quot;
comma
dot
id|bus
op_assign
op_amp
id|system_bus_type
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * register_cpu - Setup a driverfs device for a CPU.&n; * @num - CPU number to use when creating the device.&n; *&n; * Initialize and register the CPU device.&n; */
DECL|function|register_cpu
r_int
id|__init
id|register_cpu
c_func
(paren
r_struct
id|cpu
op_star
id|cpu
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
r_int
id|retval
suffix:semicolon
id|cpu-&gt;node_id
op_assign
id|cpu_to_node
c_func
(paren
id|num
)paren
suffix:semicolon
id|cpu-&gt;sysdev.name
op_assign
l_string|&quot;cpu&quot;
suffix:semicolon
id|cpu-&gt;sysdev.id
op_assign
id|num
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
id|cpu-&gt;sysdev.root
op_assign
op_amp
id|root-&gt;sysroot
suffix:semicolon
id|snprintf
c_func
(paren
id|cpu-&gt;sysdev.dev.name
comma
id|DEVICE_NAME_SIZE
comma
l_string|&quot;CPU %u&quot;
comma
id|num
)paren
suffix:semicolon
id|cpu-&gt;sysdev.dev.driver
op_assign
op_amp
id|cpu_driver
suffix:semicolon
id|retval
op_assign
id|sys_device_register
c_func
(paren
op_amp
id|cpu-&gt;sysdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cpu-&gt;sysdev.class_dev
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|class_device
)paren
)paren
suffix:semicolon
id|cpu-&gt;sysdev.class_dev.dev
op_assign
op_amp
id|cpu-&gt;sysdev.dev
suffix:semicolon
id|cpu-&gt;sysdev.class_dev
dot
r_class
op_assign
op_amp
id|cpu_class
suffix:semicolon
id|snprintf
c_func
(paren
id|cpu-&gt;sysdev.class_dev.class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;cpu%d&quot;
comma
id|num
)paren
suffix:semicolon
id|retval
op_assign
id|class_device_register
c_func
(paren
op_amp
id|cpu-&gt;sysdev.class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
singleline_comment|// FIXME cleanup sys_device_register
r_return
id|retval
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpu_dev_init
r_int
id|__init
id|cpu_dev_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|class_register
c_func
(paren
op_amp
id|cpu_class
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|driver_register
c_func
(paren
op_amp
id|cpu_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|class_unregister
c_func
(paren
op_amp
id|cpu_class
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
eof
