macro_line|#ifndef _ASM_MACH_TOPOLOGY_H
DECL|macro|_ASM_MACH_TOPOLOGY_H
mdefine_line|#define _ASM_MACH_TOPOLOGY_H&t;1
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/hub.h&gt;
macro_line|#include &lt;asm/mmzone.h&gt;
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu)&t;(cpu_data[(cpu)].p_nodeid)
DECL|macro|parent_node
mdefine_line|#define parent_node(node)&t;(node)
DECL|macro|node_to_cpumask
mdefine_line|#define node_to_cpumask(node)&t;(hub_data(node)-&gt;h_cpus)
DECL|macro|node_to_first_cpu
mdefine_line|#define node_to_first_cpu(node)&t;(first_cpu(node_to_cpumask(node)))
DECL|macro|pcibus_to_cpumask
mdefine_line|#define pcibus_to_cpumask(bus)&t;(cpu_online_map)
r_extern
r_int
r_char
id|__node_distances
(braket
id|MAX_COMPACT_NODES
)braket
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|macro|node_distance
mdefine_line|#define node_distance(from, to)&t;(__node_distances[(from)][(to)])
multiline_comment|/* sched_domains SD_NODE_INIT for SGI IP27 machines */
DECL|macro|SD_NODE_INIT
mdefine_line|#define SD_NODE_INIT (struct sched_domain) {&t;&t;&bslash;&n;&t;.span&t;&t;&t;= CPU_MASK_NONE,&t;&bslash;&n;&t;.parent&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.groups&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.min_interval&t;&t;= 8,&t;&t;&t;&bslash;&n;&t;.max_interval&t;&t;= 32,&t;&t;&t;&bslash;&n;&t;.busy_factor&t;&t;= 32,&t;&t;&t;&bslash;&n;&t;.imbalance_pct&t;&t;= 125,&t;&t;&t;&bslash;&n;&t;.cache_hot_time&t;&t;= (10*1000),&t;&t;&bslash;&n;&t;.cache_nice_tries&t;= 1,&t;&t;&t;&bslash;&n;&t;.per_cpu_gain&t;&t;= 100,&t;&t;&t;&bslash;&n;&t;.flags&t;&t;&t;= SD_LOAD_BALANCE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_EXEC&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_BALANCE,&t;&bslash;&n;&t;.last_balance&t;&t;= jiffies,&t;&t;&bslash;&n;&t;.balance_interval&t;= 1,&t;&t;&t;&bslash;&n;&t;.nr_balance_failed&t;= 0,&t;&t;&t;&bslash;&n;}
macro_line|#endif /* _ASM_MACH_TOPOLOGY_H */
eof
