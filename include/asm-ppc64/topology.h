macro_line|#ifndef _ASM_PPC64_TOPOLOGY_H
DECL|macro|_ASM_PPC64_TOPOLOGY_H
mdefine_line|#define _ASM_PPC64_TOPOLOGY_H
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
r_int
id|cpu
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|numa_cpu_lookup_table
(braket
id|cpu
)braket
op_eq
id|node
)paren
r_return
id|cpu
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* couldn&squot;t find a cpu on given node */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
r_int
id|cpu
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0UL
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
OL
id|NR_CPUS
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|numa_cpu_lookup_table
(braket
id|cpu
)braket
op_eq
id|node
)paren
id|mask
op_or_assign
l_int|1UL
op_lshift
id|cpu
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
multiline_comment|/* Cross-node load balancing interval. */
DECL|macro|NODE_BALANCE_RATE
mdefine_line|#define NODE_BALANCE_RATE 10
macro_line|#else /* !CONFIG_NUMA */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _ASM_PPC64_TOPOLOGY_H */
eof
