multiline_comment|/*&n; * drivers/base/cpu.c - basic CPU class support&n; */
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
DECL|variable|cpu_sysdev_class
r_struct
id|sysdev_class
id|cpu_sysdev_class
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;cpu&quot;
)paren
comma
)brace
suffix:semicolon
DECL|variable|cpu_sysdev_class
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_sysdev_class
)paren
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
id|cpu_to_node
c_func
(paren
id|num
)paren
suffix:semicolon
id|cpu-&gt;sysdev.id
op_assign
id|num
suffix:semicolon
id|cpu-&gt;sysdev.cls
op_assign
op_amp
id|cpu_sysdev_class
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
DECL|function|cpu_dev_init
r_int
id|__init
id|cpu_dev_init
c_func
(paren
r_void
)paren
(brace
r_return
id|sysdev_class_register
c_func
(paren
op_amp
id|cpu_sysdev_class
)paren
suffix:semicolon
)brace
eof
