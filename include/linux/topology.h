multiline_comment|/*&n; * include/linux/topology.h&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#ifndef _LINUX_TOPOLOGY_H
DECL|macro|_LINUX_TOPOLOGY_H
mdefine_line|#define _LINUX_TOPOLOGY_H
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
macro_line|#ifndef nr_cpus_node
DECL|macro|nr_cpus_node
mdefine_line|#define nr_cpus_node(node)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpumask_t __tmp__;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__tmp__ = node_to_cpumask(node);&t;&t;&t;&t;&bslash;&n;&t;&t;cpus_weight(__tmp__);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#endif
DECL|function|__next_node_with_cpus
r_static
r_inline
r_int
id|__next_node_with_cpus
c_func
(paren
r_int
id|node
)paren
(brace
r_do
op_increment
id|node
suffix:semicolon
r_while
c_loop
(paren
id|node
OL
id|numnodes
op_logical_and
op_logical_neg
id|nr_cpus_node
c_func
(paren
id|node
)paren
)paren
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
DECL|macro|for_each_node_with_cpus
mdefine_line|#define for_each_node_with_cpus(node) &bslash;&n;&t;for (node = 0; node &lt; numnodes; node = __next_node_with_cpus(node))
macro_line|#ifndef node_distance
multiline_comment|/* Conform to ACPI 2.0 SLIT distance definitions */
DECL|macro|LOCAL_DISTANCE
mdefine_line|#define LOCAL_DISTANCE&t;&t;10
DECL|macro|REMOTE_DISTANCE
mdefine_line|#define REMOTE_DISTANCE&t;&t;20
DECL|macro|node_distance
mdefine_line|#define node_distance(from,to)&t;((from) == (to) ? LOCAL_DISTANCE : REMOTE_DISTANCE)
macro_line|#endif
macro_line|#ifndef PENALTY_FOR_NODE_WITH_CPUS
DECL|macro|PENALTY_FOR_NODE_WITH_CPUS
mdefine_line|#define PENALTY_FOR_NODE_WITH_CPUS&t;(1)
macro_line|#endif
multiline_comment|/*&n; * Below are the 3 major initializers used in building sched_domains:&n; * SD_SIBLING_INIT, for SMT domains&n; * SD_CPU_INIT, for SMP domains&n; * SD_NODE_INIT, for NUMA domains&n; *&n; * Any architecture that cares to do any tuning to these values should do so&n; * by defining their own arch-specific initializer in include/asm/topology.h.&n; * A definition there will automagically override these default initializers&n; * and allow arch-specific performance tuning of sched_domains.&n; */
macro_line|#ifdef CONFIG_SCHED_SMT
multiline_comment|/* MCD - Do we really need this?  It is always on if CONFIG_SCHED_SMT is,&n; * so can&squot;t we drop this in favor of CONFIG_SCHED_SMT?&n; */
DECL|macro|ARCH_HAS_SCHED_WAKE_IDLE
mdefine_line|#define ARCH_HAS_SCHED_WAKE_IDLE
multiline_comment|/* Common values for SMT siblings */
macro_line|#ifndef SD_SIBLING_INIT
DECL|macro|SD_SIBLING_INIT
mdefine_line|#define SD_SIBLING_INIT (struct sched_domain) {&t;&t;&bslash;&n;&t;.span&t;&t;&t;= CPU_MASK_NONE,&t;&bslash;&n;&t;.parent&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.groups&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.min_interval&t;&t;= 1,&t;&t;&t;&bslash;&n;&t;.max_interval&t;&t;= 2,&t;&t;&t;&bslash;&n;&t;.busy_factor&t;&t;= 8,&t;&t;&t;&bslash;&n;&t;.imbalance_pct&t;&t;= 110,&t;&t;&t;&bslash;&n;&t;.cache_hot_time&t;&t;= 0,&t;&t;&t;&bslash;&n;&t;.cache_nice_tries&t;= 0,&t;&t;&t;&bslash;&n;&t;.per_cpu_gain&t;&t;= 25,&t;&t;&t;&bslash;&n;&t;.flags&t;&t;&t;= SD_LOAD_BALANCE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_NEWIDLE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_EXEC&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_AFFINE&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_IDLE&t;&t;&bslash;&n;&t;&t;&t;&t;| SD_SHARE_CPUPOWER,&t;&bslash;&n;&t;.last_balance&t;&t;= jiffies,&t;&t;&bslash;&n;&t;.balance_interval&t;= 1,&t;&t;&t;&bslash;&n;&t;.nr_balance_failed&t;= 0,&t;&t;&t;&bslash;&n;}
macro_line|#endif
macro_line|#endif /* CONFIG_SCHED_SMT */
multiline_comment|/* Common values for CPUs */
macro_line|#ifndef SD_CPU_INIT
DECL|macro|SD_CPU_INIT
mdefine_line|#define SD_CPU_INIT (struct sched_domain) {&t;&t;&bslash;&n;&t;.span&t;&t;&t;= CPU_MASK_NONE,&t;&bslash;&n;&t;.parent&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.groups&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.min_interval&t;&t;= 1,&t;&t;&t;&bslash;&n;&t;.max_interval&t;&t;= 4,&t;&t;&t;&bslash;&n;&t;.busy_factor&t;&t;= 64,&t;&t;&t;&bslash;&n;&t;.imbalance_pct&t;&t;= 125,&t;&t;&t;&bslash;&n;&t;.cache_hot_time&t;&t;= (5*1000000/2),&t;&bslash;&n;&t;.cache_nice_tries&t;= 1,&t;&t;&t;&bslash;&n;&t;.per_cpu_gain&t;&t;= 100,&t;&t;&t;&bslash;&n;&t;.flags&t;&t;&t;= SD_LOAD_BALANCE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_NEWIDLE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_EXEC&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_AFFINE&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_IDLE&t;&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_BALANCE,&t;&bslash;&n;&t;.last_balance&t;&t;= jiffies,&t;&t;&bslash;&n;&t;.balance_interval&t;= 1,&t;&t;&t;&bslash;&n;&t;.nr_balance_failed&t;= 0,&t;&t;&t;&bslash;&n;}
macro_line|#endif
macro_line|#ifdef CONFIG_NUMA
macro_line|#ifndef SD_NODE_INIT
macro_line|#error Please define an appropriate SD_NODE_INIT in include/asm/topology.h!!!
macro_line|#endif
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _LINUX_TOPOLOGY_H */
eof
