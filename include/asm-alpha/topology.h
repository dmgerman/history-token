macro_line|#ifndef _ASM_ALPHA_TOPOLOGY_H
DECL|macro|_ASM_ALPHA_TOPOLOGY_H
mdefine_line|#define _ASM_ALPHA_TOPOLOGY_H
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
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
r_if
c_cond
(paren
op_logical_neg
id|alpha_mv.cpuid_to_nid
)paren
r_return
l_int|0
suffix:semicolon
id|node
op_assign
id|alpha_mv
dot
id|cpuid_to_nid
c_func
(paren
id|cpu
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_NUMA
id|BUG_ON
c_func
(paren
id|node
OL
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_return
id|node
suffix:semicolon
)brace
DECL|function|node_to_cpumask
r_static
r_inline
id|cpumask_t
id|node_to_cpumask
c_func
(paren
r_int
id|node
)paren
(brace
id|cpumask_t
id|node_cpu_mask
op_assign
id|CPU_MASK_NONE
suffix:semicolon
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
(brace
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|cpu
)paren
op_logical_and
(paren
id|cpu_to_node
c_func
(paren
id|cpu
)paren
op_eq
id|node
)paren
)paren
id|cpu_set
c_func
(paren
id|cpu
comma
id|node_cpu_mask
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_NUMA
id|printk
c_func
(paren
l_string|&quot;node %d: cpu_mask: %016lx&bslash;n&quot;
comma
id|node
comma
id|node_cpu_mask
)paren
suffix:semicolon
macro_line|#endif
r_return
id|node_cpu_mask
suffix:semicolon
)brace
DECL|macro|pcibus_to_cpumask
mdefine_line|#define pcibus_to_cpumask(bus)&t;(cpu_online_map)
macro_line|#else /* CONFIG_NUMA */
macro_line|# include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* !CONFIG_NUMA */
macro_line|#endif /* _ASM_ALPHA_TOPOLOGY_H */
eof
