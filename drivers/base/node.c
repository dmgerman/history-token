multiline_comment|/*&n; * drivers/base/node.c - basic Node class support&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/node.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
DECL|variable|node_class
r_static
r_struct
id|sysdev_class
id|node_class
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;node&quot;
)paren
comma
)brace
suffix:semicolon
DECL|function|node_read_cpumap
r_static
id|ssize_t
id|node_read_cpumap
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|node
op_star
id|node_dev
op_assign
id|to_node
c_func
(paren
id|to_root
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%lx&bslash;n&quot;
comma
id|node_dev-&gt;cpumap
)paren
suffix:semicolon
)brace
r_static
id|SYSDEV_ATTR
c_func
(paren
id|cpumap
comma
id|S_IRUGO
comma
id|node_read_cpumap
comma
l_int|NULL
)paren
suffix:semicolon
DECL|macro|K
mdefine_line|#define K(x) ((x) &lt;&lt; (PAGE_SHIFT - 10))
DECL|function|node_read_meminfo
r_static
id|ssize_t
id|node_read_meminfo
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|sys_root
op_star
id|node
op_assign
id|to_root
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|nid
op_assign
id|node-&gt;id
suffix:semicolon
r_struct
id|sysinfo
id|i
suffix:semicolon
id|si_meminfo_node
c_func
(paren
op_amp
id|i
comma
id|nid
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
l_string|&quot;Node %d MemTotal:     %8lu kB&bslash;n&quot;
l_string|&quot;Node %d MemFree:      %8lu kB&bslash;n&quot;
l_string|&quot;Node %d MemUsed:      %8lu kB&bslash;n&quot;
l_string|&quot;Node %d HighTotal:    %8lu kB&bslash;n&quot;
l_string|&quot;Node %d HighFree:     %8lu kB&bslash;n&quot;
l_string|&quot;Node %d LowTotal:     %8lu kB&bslash;n&quot;
l_string|&quot;Node %d LowFree:      %8lu kB&bslash;n&quot;
comma
id|nid
comma
id|K
c_func
(paren
id|i.totalram
)paren
comma
id|nid
comma
id|K
c_func
(paren
id|i.freeram
)paren
comma
id|nid
comma
id|K
c_func
(paren
id|i.totalram
op_minus
id|i.freeram
)paren
comma
id|nid
comma
id|K
c_func
(paren
id|i.totalhigh
)paren
comma
id|nid
comma
id|K
c_func
(paren
id|i.freehigh
)paren
comma
id|nid
comma
id|K
c_func
(paren
id|i.totalram
op_minus
id|i.totalhigh
)paren
comma
id|nid
comma
id|K
c_func
(paren
id|i.freeram
op_minus
id|i.freehigh
)paren
)paren
suffix:semicolon
)brace
DECL|macro|K
macro_line|#undef K 
r_static
id|SYSDEV_ATTR
c_func
(paren
id|meminfo
comma
id|S_IRUGO
comma
id|node_read_meminfo
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n; * register_node - Setup a driverfs device for a node.&n; * @num - Node number to use when creating the device.&n; *&n; * Initialize and register the node device.&n; */
DECL|function|register_node
r_int
id|__init
id|register_node
c_func
(paren
r_struct
id|node
op_star
id|node
comma
r_int
id|num
comma
r_struct
id|node
op_star
id|parent
)paren
(brace
r_int
id|error
suffix:semicolon
id|node-&gt;cpumap
op_assign
id|node_to_cpumask
c_func
(paren
id|num
)paren
suffix:semicolon
id|node-&gt;sysdev.id
op_assign
id|num
suffix:semicolon
id|node-&gt;sysdev.cls
op_assign
op_amp
id|node_class
suffix:semicolon
id|error
op_assign
id|sys_device_register
c_func
(paren
op_amp
id|node-&gt;sysdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|sys_device_create_file
c_func
(paren
op_amp
id|node-&gt;sysroot.dev
comma
op_amp
id|attr_cpumap
)paren
suffix:semicolon
id|sys_device_create_file
c_func
(paren
op_amp
id|node-&gt;sysroot.dev
comma
op_amp
id|attr_meminfo
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|register_node_type
r_int
id|__init
id|register_node_type
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
id|node_class
)paren
suffix:semicolon
)brace
DECL|variable|register_node_type
id|postcore_initcall
c_func
(paren
id|register_node_type
)paren
suffix:semicolon
eof
