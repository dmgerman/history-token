multiline_comment|/*&n; * linux/include/asm-i386/topology.h&n; *&n; * Written by: Matthew Dobson, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;colpatch@us.ibm.com&gt;&n; */
macro_line|#ifndef _ASM_I386_TOPOLOGY_H
DECL|macro|_ASM_I386_TOPOLOGY_H
mdefine_line|#define _ASM_I386_TOPOLOGY_H
macro_line|#ifdef CONFIG_NUMA
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
multiline_comment|/* Mappings between logical cpu number and node number */
r_extern
id|cpumask_t
id|node_2_cpu_mask
(braket
)braket
suffix:semicolon
r_extern
r_int
id|cpu_2_node
(braket
)braket
suffix:semicolon
multiline_comment|/* Returns the number of the node containing CPU &squot;cpu&squot; */
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
r_return
id|cpu_2_node
(braket
id|cpu
)braket
suffix:semicolon
)brace
multiline_comment|/* Returns the number of the node containing Node &squot;node&squot;.  This architecture is flat, &n;   so it is a pretty simple function! */
DECL|macro|parent_node
mdefine_line|#define parent_node(node) (node)
multiline_comment|/* Returns a bitmask of CPUs on Node &squot;node&squot;. */
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
r_return
id|node_2_cpu_mask
(braket
id|node
)braket
suffix:semicolon
)brace
multiline_comment|/* Returns the number of the first CPU on Node &squot;node&squot;. */
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
id|cpumask_t
id|mask
op_assign
id|node_to_cpumask
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
id|first_cpu
c_func
(paren
id|mask
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the number of the node containing PCI bus &squot;bus&squot; */
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
r_return
id|node_to_cpumask
c_func
(paren
id|mp_bus_id_to_node
(braket
id|bus
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* sched_domains SD_NODE_INIT for NUMAQ machines */
DECL|macro|SD_NODE_INIT
mdefine_line|#define SD_NODE_INIT (struct sched_domain) {&t;&t;&bslash;&n;&t;.span&t;&t;&t;= CPU_MASK_NONE,&t;&bslash;&n;&t;.parent&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.groups&t;&t;&t;= NULL,&t;&t;&t;&bslash;&n;&t;.min_interval&t;&t;= 8,&t;&t;&t;&bslash;&n;&t;.max_interval&t;&t;= 32,&t;&t;&t;&bslash;&n;&t;.busy_factor&t;&t;= 32,&t;&t;&t;&bslash;&n;&t;.imbalance_pct&t;&t;= 125,&t;&t;&t;&bslash;&n;&t;.cache_hot_time&t;&t;= (10*1000),&t;&t;&bslash;&n;&t;.cache_nice_tries&t;= 1,&t;&t;&t;&bslash;&n;&t;.per_cpu_gain&t;&t;= 100,&t;&t;&t;&bslash;&n;&t;.flags&t;&t;&t;= SD_LOAD_BALANCE&t;&bslash;&n;&t;&t;&t;&t;| SD_BALANCE_EXEC&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_IDLE&t;&t;&bslash;&n;&t;&t;&t;&t;| SD_WAKE_BALANCE,&t;&bslash;&n;&t;.last_balance&t;&t;= jiffies,&t;&t;&bslash;&n;&t;.balance_interval&t;= 1,&t;&t;&t;&bslash;&n;&t;.nr_balance_failed&t;= 0,&t;&t;&t;&bslash;&n;}
macro_line|#else /* !CONFIG_NUMA */
multiline_comment|/*&n; * Other i386 platforms should define their own version of the &n; * above macros here.&n; */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _ASM_I386_TOPOLOGY_H */
eof
