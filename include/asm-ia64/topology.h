multiline_comment|/*&n; * linux/include/asm-ia64/topology.h&n; *&n; * Copyright (C) 2002, Erich Focht, NEC&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#ifndef _ASM_IA64_TOPOLOGY_H
DECL|macro|_ASM_IA64_TOPOLOGY_H
mdefine_line|#define _ASM_IA64_TOPOLOGY_H
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
multiline_comment|/* Returns the number of the node containing CPU &squot;cpu&squot; */
macro_line|#ifdef CONFIG_NUMA
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu) cpu_to_node_map[cpu]
macro_line|#else
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu) (0)
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
multiline_comment|/*&n; * Returns the number of the first CPU on Node &squot;node&squot;.&n; * Slow in the current implementation.&n; * Who needs this?&n; */
multiline_comment|/* #define __node_to_first_cpu(node) pool_cpus[pool_ptr[node]] */
DECL|function|__node_to_first_cpu
r_static
r_inline
r_int
id|__node_to_first_cpu
c_func
(paren
r_int
id|node
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|__cpu_to_node
c_func
(paren
id|i
)paren
op_eq
id|node
)paren
r_return
id|i
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
multiline_comment|/*&n; * Returns a bitmask of CPUs on Node &squot;node&squot;.&n; */
DECL|function|__node_to_cpu_mask
r_static
r_inline
r_int
r_int
id|__node_to_cpu_mask
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
id|__cpu_to_node
c_func
(paren
id|cpu
)paren
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
multiline_comment|/*&n; * Returns the number of the first MemBlk on Node &squot;node&squot;&n; * Should be fixed when IA64 discontigmem goes in.&n; */
DECL|macro|__node_to_memblk
mdefine_line|#define __node_to_memblk(node) (node)
macro_line|#endif /* _ASM_IA64_TOPOLOGY_H */
eof
