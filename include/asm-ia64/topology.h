multiline_comment|/*&n; * linux/include/asm-ia64/topology.h&n; *&n; * Copyright (C) 2002, Erich Focht, NEC&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#ifndef _ASM_IA64_TOPOLOGY_H
DECL|macro|_ASM_IA64_TOPOLOGY_H
mdefine_line|#define _ASM_IA64_TOPOLOGY_H
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/*&n; * Returns the number of the node containing CPU &squot;cpu&squot;&n; */
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu) (int)(cpu_to_node_map[cpu])
multiline_comment|/*&n; * Returns a bitmask of CPUs on Node &squot;node&squot;.&n; */
DECL|macro|node_to_cpumask
mdefine_line|#define node_to_cpumask(node) (node_to_cpu_mask[node])
multiline_comment|/*&n; * Returns the number of the node containing Node &squot;nid&squot;.&n; * Not implemented here. Multi-level hierarchies detected with&n; * the help of node_distance().&n; */
DECL|macro|parent_node
mdefine_line|#define parent_node(nid) (nid)
multiline_comment|/*&n; * Returns the number of the first CPU on Node &squot;node&squot;.&n; */
DECL|macro|node_to_first_cpu
mdefine_line|#define node_to_first_cpu(node) (__ffs(node_to_cpumask(node)))
r_void
id|build_cpu_to_node_map
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* sched_domains SD_NODE_INIT for IA64 NUMA machines */
DECL|macro|SD_NODE_INIT
mdefine_line|#define SD_NODE_INIT (struct sched_domain) {&t;&t;&bslash;&n;&t;.span&t;&t;&t;= CPU_MASK_NONE,&t;&bslash;&n;&t;.parent&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.groups&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.min_interval&t;&t;= 80,&t;&t;&t;&bslash;&n;&t;.max_interval&t;&t;= 320,&t;&t;&t;&bslash;&n;&t;.busy_factor&t;&t;= 320,&t;&t;&t;&bslash;&n;&t;.imbalance_pct&t;&t;= 125,&t;&t;&t;&bslash;&n;&t;.cache_hot_time&t;&t;= (10*1000000),&t;&t;&bslash;&n;&t;.cache_nice_tries&t;= 1,&t;&t;&t;&bslash;&n;&t;.per_cpu_gain&t;&t;= 100,&t;&t;&t;&bslash;&n;&t;.flags&t;&t;&t;= SD_LOAD_BALANCE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_EXEC&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_NEWIDLE&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_IDLE&t;&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_BALANCE,&t;&bslash;&n;&t;.last_balance&t;&t;= jiffies,&t;&t;&bslash;&n;&t;.balance_interval&t;= 1,&t;&t;&t;&bslash;&n;&t;.nr_balance_failed&t;= 0,&t;&t;&t;&bslash;&n;}
multiline_comment|/* sched_domains SD_ALLNODES_INIT for IA64 NUMA machines */
DECL|macro|SD_ALLNODES_INIT
mdefine_line|#define SD_ALLNODES_INIT (struct sched_domain) {&t;&bslash;&n;&t;.span&t;&t;&t;= CPU_MASK_NONE,&t;&bslash;&n;&t;.parent&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.groups&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.min_interval&t;&t;= 80,&t;&t;&t;&bslash;&n;&t;.max_interval&t;&t;= 320,&t;&t;&t;&bslash;&n;&t;.busy_factor&t;&t;= 320,&t;&t;&t;&bslash;&n;&t;.imbalance_pct&t;&t;= 125,&t;&t;&t;&bslash;&n;&t;.cache_hot_time&t;&t;= (10*1000000),&t;&t;&bslash;&n;&t;.cache_nice_tries&t;= 1,&t;&t;&t;&bslash;&n;&t;.per_cpu_gain&t;&t;= 100,&t;&t;&t;&bslash;&n;&t;.flags&t;&t;&t;= SD_LOAD_BALANCE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_EXEC,&t;&bslash;&n;&t;.last_balance&t;&t;= jiffies,&t;&t;&bslash;&n;&t;.balance_interval&t;= 100*(63+num_online_cpus())/64,   &bslash;&n;&t;.nr_balance_failed&t;= 0,&t;&t;&t;&bslash;&n;}
macro_line|#endif /* CONFIG_NUMA */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* _ASM_IA64_TOPOLOGY_H */
eof
