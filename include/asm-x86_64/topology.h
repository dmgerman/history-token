macro_line|#ifndef _ASM_X86_64_TOPOLOGY_H
DECL|macro|_ASM_X86_64_TOPOLOGY_H
mdefine_line|#define _ASM_X86_64_TOPOLOGY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/* Map the K8 CPU local memory controllers to a simple 1:1 CPU:NODE topology */
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
r_extern
r_int
r_char
id|cpu_to_node
(braket
)braket
suffix:semicolon
r_extern
id|cpumask_t
id|node_to_cpumask
(braket
)braket
suffix:semicolon
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu)&t;&t;(cpu_to_node[cpu])
DECL|macro|parent_node
mdefine_line|#define parent_node(node)&t;&t;(node)
DECL|macro|node_to_first_cpu
mdefine_line|#define node_to_first_cpu(node) &t;(__ffs(node_to_cpumask[node]))
DECL|macro|node_to_cpumask
mdefine_line|#define node_to_cpumask(node)&t;&t;(node_to_cpumask[node])
DECL|function|pcibus_to_cpumask
r_static
r_inline
r_int
r_int
id|pcibus_to_cpumask
c_func
(paren
r_int
id|bus
)paren
(brace
r_return
id|mp_bus_to_cpumask
(braket
id|bus
)braket
op_amp
id|cpu_online_map
suffix:semicolon
)brace
DECL|macro|NODE_BALANCE_RATE
mdefine_line|#define NODE_BALANCE_RATE 30&t;/* CHECKME */ 
macro_line|#endif
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif
eof
