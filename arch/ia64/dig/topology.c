multiline_comment|/*&n; * arch/ia64/dig/topology.c&n; *&t;Popuate driverfs with topology information.&n; *&t;Derived entirely from i386/mach-default.c&n; *  Intel Corporation - Ashok Raj&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|ia64_cpu
comma
id|cpu_devices
)paren
suffix:semicolon
multiline_comment|/*&n; * First Pass: simply borrowed code for now. Later should hook into&n; * hotplug notification for node/cpu/memory as applicable&n; */
DECL|function|arch_register_cpu
r_static
r_int
id|arch_register_cpu
c_func
(paren
r_int
id|num
)paren
(brace
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
singleline_comment|//parent = &amp;node_devices[cpu_to_node(num)].node;
macro_line|#endif
r_return
id|register_cpu
c_func
(paren
op_amp
id|per_cpu
c_func
(paren
id|cpu_devices
comma
id|num
)paren
dot
id|cpu
comma
id|num
comma
id|parent
)paren
suffix:semicolon
)brace
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
id|i
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
id|arch_register_cpu
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|topology_init
id|subsys_initcall
c_func
(paren
id|topology_init
)paren
suffix:semicolon
eof
