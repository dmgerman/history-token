multiline_comment|/*&n; * drivers/base/cpu.c - basic CPU class support&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
DECL|function|cpu_add_device
r_static
r_int
id|cpu_add_device
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
DECL|variable|cpu_devclass
r_struct
id|device_class
id|cpu_devclass
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cpu&quot;
comma
dot
id|add_device
op_assign
id|cpu_add_device
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
dot
id|devclass
op_assign
op_amp
id|cpu_devclass
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
id|cpu-&gt;node_id
op_assign
id|__cpu_to_node
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
r_return
id|sys_device_register
c_func
(paren
op_amp
id|cpu-&gt;sysdev
)paren
suffix:semicolon
)brace
DECL|function|register_cpu_type
r_static
r_int
id|__init
id|register_cpu_type
c_func
(paren
r_void
)paren
(brace
id|devclass_register
c_func
(paren
op_amp
id|cpu_devclass
)paren
suffix:semicolon
r_return
id|driver_register
c_func
(paren
op_amp
id|cpu_driver
)paren
suffix:semicolon
)brace
DECL|variable|register_cpu_type
id|postcore_initcall
c_func
(paren
id|register_cpu_type
)paren
suffix:semicolon
eof
