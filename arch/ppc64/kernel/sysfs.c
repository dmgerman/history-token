macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#ifdef CONFIG_NUMA
DECL|variable|node_devices
r_static
r_struct
id|node
id|node_devices
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|function|register_nodes
r_static
r_void
id|register_nodes
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|node_online
c_func
(paren
id|i
)paren
)paren
(brace
r_int
id|p_node
op_assign
id|parent_node
c_func
(paren
id|i
)paren
suffix:semicolon
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|p_node
op_ne
id|i
)paren
id|parent
op_assign
op_amp
id|node_devices
(braket
id|p_node
)braket
suffix:semicolon
id|register_node
c_func
(paren
op_amp
id|node_devices
(braket
id|i
)braket
comma
id|i
comma
id|parent
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#else
DECL|function|register_nodes
r_static
r_void
id|register_nodes
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Only valid if CPU is online. */
DECL|function|show_physical_id
r_static
id|ssize_t
id|show_physical_id
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
id|get_hard_smp_processor_id
c_func
(paren
id|cpu-&gt;sysdev.id
)paren
)paren
suffix:semicolon
)brace
r_static
id|SYSDEV_ATTR
c_func
(paren
id|physical_id
comma
l_int|0444
comma
id|show_physical_id
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|cpu
comma
id|cpu_devices
)paren
suffix:semicolon
DECL|function|topology_init
r_static
r_int
id|__init
id|topology_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
id|register_nodes
c_func
(paren
)paren
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|cpu
)paren
(brace
r_struct
id|cpu
op_star
id|c
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_devices
comma
id|cpu
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
id|parent
op_assign
op_amp
id|node_devices
(braket
id|cpu_to_node
c_func
(paren
id|cpu
)paren
)braket
suffix:semicolon
macro_line|#endif
id|register_cpu
c_func
(paren
id|c
comma
id|cpu
comma
id|parent
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|c-&gt;sysdev
comma
op_amp
id|attr_physical_id
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|topology_init
id|__initcall
c_func
(paren
id|topology_init
)paren
suffix:semicolon
eof
