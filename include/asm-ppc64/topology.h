macro_line|#ifndef _ASM_PPC64_TOPOLOGY_H
DECL|macro|_ASM_PPC64_TOPOLOGY_H
mdefine_line|#define _ASM_PPC64_TOPOLOGY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#ifdef CONFIG_NUMA
DECL|function|cpu_to_node
r_static
r_inline
r_int
id|cpu_to_node
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|node
suffix:semicolon
id|node
op_assign
id|numa_cpu_lookup_table
(braket
id|cpu
)braket
suffix:semicolon
macro_line|#ifdef DEBUG_NUMA
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|node
suffix:semicolon
)brace
DECL|macro|memblk_to_node
mdefine_line|#define memblk_to_node(memblk)&t;(memblk)
DECL|macro|parent_node
mdefine_line|#define parent_node(node)&t;(node)
DECL|function|node_to_cpumask
r_static
r_inline
r_int
r_int
id|node_to_cpumask
c_func
(paren
r_int
id|node
)paren
(brace
r_return
id|numa_cpumask_lookup_table
(braket
id|node
)braket
suffix:semicolon
)brace
DECL|function|node_to_first_cpu
r_static
r_inline
r_int
id|node_to_first_cpu
c_func
(paren
r_int
id|node
)paren
(brace
r_return
id|__ffs
c_func
(paren
id|node_to_cpumask
c_func
(paren
id|node
)paren
)paren
suffix:semicolon
)brace
DECL|macro|node_to_memblk
mdefine_line|#define node_to_memblk(node)&t;(node)
DECL|macro|pcibus_to_cpumask
mdefine_line|#define pcibus_to_cpumask(bus)&t;(cpu_online_map)
DECL|macro|nr_cpus_node
mdefine_line|#define nr_cpus_node(node)&t;(nr_cpus_in_node[node])
multiline_comment|/* Cross-node load balancing interval. */
DECL|macro|NODE_BALANCE_RATE
mdefine_line|#define NODE_BALANCE_RATE 10
macro_line|#else /* !CONFIG_NUMA */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _ASM_PPC64_TOPOLOGY_H */
eof
