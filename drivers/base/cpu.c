multiline_comment|/*&n; * drivers/base/cpu.c - basic CPU class support&n; */
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
macro_line|#include &lt;linux/device.h&gt;
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
macro_line|#ifdef CONFIG_HOTPLUG_CPU
DECL|function|show_online
r_static
id|ssize_t
id|show_online
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|cpu
op_star
id|cpu
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|cpu
comma
id|sysdev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%u&bslash;n&quot;
comma
op_logical_neg
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu-&gt;sysdev.id
)paren
)paren
suffix:semicolon
)brace
DECL|function|store_online
r_static
id|ssize_t
id|store_online
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|cpu
op_star
id|cpu
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|cpu
comma
id|sysdev
)paren
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|buf
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;0&squot;
suffix:colon
id|ret
op_assign
id|cpu_down
c_func
(paren
id|cpu-&gt;sysdev.id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|kobject_hotplug
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
id|KOBJ_OFFLINE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;1&squot;
suffix:colon
id|ret
op_assign
id|cpu_up
c_func
(paren
id|cpu-&gt;sysdev.id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
id|ret
op_assign
id|count
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|SYSDEV_ATTR
c_func
(paren
id|online
comma
l_int|0600
comma
id|show_online
comma
id|store_online
)paren
suffix:semicolon
DECL|function|register_cpu_control
r_static
r_void
id|__devinit
id|register_cpu_control
c_func
(paren
r_struct
id|cpu
op_star
id|cpu
)paren
(brace
id|sysdev_create_file
c_func
(paren
op_amp
id|cpu-&gt;sysdev
comma
op_amp
id|attr_online
)paren
suffix:semicolon
)brace
DECL|function|unregister_cpu
r_void
id|unregister_cpu
c_func
(paren
r_struct
id|cpu
op_star
id|cpu
comma
r_struct
id|node
op_star
id|root
)paren
(brace
r_if
c_cond
(paren
id|root
)paren
id|sysfs_remove_link
c_func
(paren
op_amp
id|root-&gt;sysdev.kobj
comma
id|kobject_name
c_func
(paren
op_amp
id|cpu-&gt;sysdev.kobj
)paren
)paren
suffix:semicolon
id|sysdev_remove_file
c_func
(paren
op_amp
id|cpu-&gt;sysdev
comma
op_amp
id|attr_online
)paren
suffix:semicolon
id|sysdev_unregister
c_func
(paren
op_amp
id|cpu-&gt;sysdev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#else /* ... !CONFIG_HOTPLUG_CPU */
DECL|function|register_cpu_control
r_static
r_inline
r_void
id|register_cpu_control
c_func
(paren
r_struct
id|cpu
op_star
id|cpu
)paren
(brace
)brace
macro_line|#endif /* CONFIG_HOTPLUG_CPU */
multiline_comment|/*&n; * register_cpu - Setup a driverfs device for a CPU.&n; * @cpu - Callers can set the cpu-&gt;no_control field to 1, to indicate not to&n; *&t;&t;  generate a control file in sysfs for this CPU.&n; * @num - CPU number to use when creating the device.&n; *&n; * Initialize and register the CPU device.&n; */
DECL|function|register_cpu
r_int
id|__devinit
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
id|error
suffix:semicolon
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
id|error
op_assign
id|sysdev_register
c_func
(paren
op_amp
id|cpu-&gt;sysdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
id|root
)paren
id|error
op_assign
id|sysfs_create_link
c_func
(paren
op_amp
id|root-&gt;sysdev.kobj
comma
op_amp
id|cpu-&gt;sysdev.kobj
comma
id|kobject_name
c_func
(paren
op_amp
id|cpu-&gt;sysdev.kobj
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
op_logical_neg
id|cpu-&gt;no_control
)paren
id|register_cpu_control
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_return
id|error
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
