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
r_extern
id|cpumask_t
id|pci_bus_to_cpumask
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_NUMA
r_extern
r_int
id|__node_distance
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|node_distance
mdefine_line|#define node_distance(a,b) __node_distance(a,b)
multiline_comment|/* #else fallback version */
macro_line|#endif
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu)&t;&t;(cpu_to_node[cpu])
DECL|macro|parent_node
mdefine_line|#define parent_node(node)&t;&t;(node)
DECL|macro|node_to_first_cpu
mdefine_line|#define node_to_first_cpu(node) &t;(__ffs(node_to_cpumask[node]))
DECL|macro|node_to_cpumask
mdefine_line|#define node_to_cpumask(node)&t;&t;(node_to_cpumask[node])
DECL|function|__pcibus_to_cpumask
r_static
r_inline
id|cpumask_t
id|__pcibus_to_cpumask
c_func
(paren
r_int
id|bus
)paren
(brace
id|cpumask_t
id|busmask
op_assign
id|pci_bus_to_cpumask
(braket
id|bus
)braket
suffix:semicolon
id|cpumask_t
id|online
op_assign
id|cpu_online_map
suffix:semicolon
id|cpumask_t
id|res
suffix:semicolon
id|cpus_and
c_func
(paren
id|res
comma
id|busmask
comma
id|online
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* broken generic file uses #ifndef later on this */
DECL|macro|pcibus_to_cpumask
mdefine_line|#define pcibus_to_cpumask(bus) __pcibus_to_cpumask(bus)
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/* sched_domains SD_NODE_INIT for x86_64 machines */
DECL|macro|SD_NODE_INIT
mdefine_line|#define SD_NODE_INIT (struct sched_domain) {&t;&t;&bslash;&n;&t;.span&t;&t;&t;= CPU_MASK_NONE,&t;&bslash;&n;&t;.parent&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.groups&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.min_interval&t;&t;= 8,&t;&t;&t;&bslash;&n;&t;.max_interval&t;&t;= 32,&t;&t;&t;&bslash;&n;&t;.busy_factor&t;&t;= 32,&t;&t;&t;&bslash;&n;&t;.imbalance_pct&t;&t;= 125,&t;&t;&t;&bslash;&n;&t;.cache_hot_time&t;&t;= (10*1000),&t;&t;&bslash;&n;&t;.cache_nice_tries&t;= 1,&t;&t;&t;&bslash;&n;&t;.per_cpu_gain&t;&t;= 100,&t;&t;&t;&bslash;&n;&t;.flags&t;&t;&t;= SD_LOAD_BALANCE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_NEWIDLE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_EXEC&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_IDLE&t;&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_BALANCE,&t;&bslash;&n;&t;.last_balance&t;&t;= jiffies,&t;&t;&bslash;&n;&t;.balance_interval&t;= 1,&t;&t;&t;&bslash;&n;&t;.nr_balance_failed&t;= 0,&t;&t;&t;&bslash;&n;}
macro_line|#endif
macro_line|#endif
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif
eof
