multiline_comment|/*&n; * linux/include/asm-ia64/topology.h&n; *&n; * Copyright (C) 2002, Erich Focht, NEC&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#ifndef _ASM_IA64_TOPOLOGY_H
DECL|macro|_ASM_IA64_TOPOLOGY_H
mdefine_line|#define _ASM_IA64_TOPOLOGY_H
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/*&n; * Returns the number of the node containing CPU &squot;cpu&squot;&n; */
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu) (int)(cpu_to_node_map[cpu])
multiline_comment|/*&n; * Returns a bitmask of CPUs on Node &squot;node&squot;.&n; */
DECL|macro|__node_to_cpu_mask
mdefine_line|#define __node_to_cpu_mask(node) (node_to_cpu_mask[node])
macro_line|#else
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu) (0)
DECL|macro|__node_to_cpu_mask
mdefine_line|#define __node_to_cpu_mask(node) (phys_cpu_present_map)
macro_line|#endif
multiline_comment|/*&n; * Returns the number of the node containing MemBlk &squot;memblk&squot;&n; */
macro_line|#ifdef CONFIG_ACPI_NUMA
DECL|macro|__memblk_to_node
mdefine_line|#define __memblk_to_node(memblk) (node_memblk[memblk].nid)
macro_line|#else
DECL|macro|__memblk_to_node
mdefine_line|#define __memblk_to_node(memblk) (memblk)
macro_line|#endif
multiline_comment|/*&n; * Returns the number of the node containing Node &squot;nid&squot;.&n; * Not implemented here. Multi-level hierarchies detected with&n; * the help of node_distance().&n; */
DECL|macro|__parent_node
mdefine_line|#define __parent_node(nid) (nid)
multiline_comment|/*&n; * Returns the number of the first CPU on Node &squot;node&squot;.&n; */
DECL|macro|__node_to_first_cpu
mdefine_line|#define __node_to_first_cpu(node) (__ffs(__node_to_cpu_mask(node)))
multiline_comment|/*&n; * Returns the number of the first MemBlk on Node &squot;node&squot;&n; * Should be fixed when IA64 discontigmem goes in.&n; */
DECL|macro|__node_to_memblk
mdefine_line|#define __node_to_memblk(node) (node)
multiline_comment|/* Cross-node load balancing interval. */
DECL|macro|NODE_BALANCE_RATE
mdefine_line|#define NODE_BALANCE_RATE 10
macro_line|#endif /* _ASM_IA64_TOPOLOGY_H */
eof
