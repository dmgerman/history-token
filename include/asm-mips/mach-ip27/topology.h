macro_line|#ifndef _ASM_MACH_TOPOLOGY_H
DECL|macro|_ASM_MACH_TOPOLOGY_H
mdefine_line|#define _ASM_MACH_TOPOLOGY_H&t;1
macro_line|#include &lt;asm/sn/hub.h&gt;
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu)&t;(cpu_data[(cpu)].p_nodeid)
DECL|macro|parent_node
mdefine_line|#define parent_node(node)&t;(node)
DECL|macro|node_to_cpumask
mdefine_line|#define node_to_cpumask(node)&t;(HUB_DATA(node)-&gt;h_cpus)
DECL|macro|node_to_first_cpu
mdefine_line|#define node_to_first_cpu(node)&t;(first_cpu(node_to_cpumask(node)))
DECL|macro|pcibus_to_cpumask
mdefine_line|#define pcibus_to_cpumask(bus)&t;(cpu_online_map)
r_extern
r_int
id|node_distance
c_func
(paren
id|nasid_t
id|nasid_a
comma
id|nasid_t
id|nasid_b
)paren
suffix:semicolon
DECL|macro|node_distance
mdefine_line|#define node_distance(from, to)&t;node_distance(from, to)
macro_line|#endif /* _ASM_MACH_TOPOLOGY_H */
eof
