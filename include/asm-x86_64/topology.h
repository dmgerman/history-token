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
multiline_comment|/* This is actually a cpumask_t, but doesn&squot;t matter because we don&squot;t have&n;   &gt;BITS_PER_LONG CPUs */
r_extern
r_int
r_int
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
DECL|macro|node_to_cpumask
mdefine_line|#define node_to_cpumask(node)&t;(fake_node ? cpu_online_map : (1UL &lt;&lt; (node)))
DECL|macro|node_to_memblk
mdefine_line|#define node_to_memblk(node)&t;&t;(node)
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
