macro_line|#ifndef _ASM_X86_64_TOPOLOGY_H
DECL|macro|_ASM_X86_64_TOPOLOGY_H
mdefine_line|#define _ASM_X86_64_TOPOLOGY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#include &lt;asm/mpspec.h&gt;
multiline_comment|/* Map the K8 CPU local memory controllers to a simple 1:1 CPU:NODE topology */
r_extern
r_int
id|fake_node
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu)&t;&t;(fake_node ? 0 : (cpu))
DECL|macro|memblk_to_node
mdefine_line|#define memblk_to_node(memblk) &t;(fake_node ? 0 : (memblk))
DECL|macro|parent_node
mdefine_line|#define parent_node(node)&t;&t;(node)
DECL|macro|node_to_first_cpu
mdefine_line|#define node_to_first_cpu(node) &t;(fake_node ? 0 : (node))
DECL|macro|node_to_cpu_mask
mdefine_line|#define node_to_cpu_mask(node)&t;(fake_node ? cpu_online_map : cpumask_of_cpu(node))
DECL|macro|node_to_memblk
mdefine_line|#define node_to_memblk(node)&t;&t;(node)
DECL|function|pcibus_to_cpumask
r_static
r_inline
id|cpumask_t
id|pcibus_to_cpumask
c_func
(paren
r_int
id|bus
)paren
(brace
id|cpumask_t
id|ret
suffix:semicolon
id|cpus_and
c_func
(paren
id|ret
comma
id|mp_bus_to_cpumask
(braket
id|bus
)braket
comma
id|cpu_online_map
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|NODE_BALANCE_RATE
mdefine_line|#define NODE_BALANCE_RATE 30&t;/* CHECKME */ 
macro_line|#endif
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif
eof
