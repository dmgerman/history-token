macro_line|#ifndef _ASM_X8664_NUMA_H 
DECL|macro|_ASM_X8664_NUMA_H
mdefine_line|#define _ASM_X8664_NUMA_H 1
DECL|macro|MAXNODE
mdefine_line|#define MAXNODE 8 
DECL|macro|NODEMASK
mdefine_line|#define NODEMASK 0xff
DECL|struct|node
r_struct
id|node
(brace
DECL|member|start
DECL|member|end
id|u64
id|start
comma
id|end
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|for_all_nodes
mdefine_line|#define for_all_nodes(x) for ((x) = 0; (x) &lt;= maxnode; (x)++) &bslash;&n;&t;&t;&t;&t;if ((1UL &lt;&lt; (x)) &amp; nodes_present)
DECL|macro|early_for_all_nodes
mdefine_line|#define early_for_all_nodes(n) &bslash;&n;&t;for (n=0; n&lt;MAXNODE;n++) if (nodes[n].start!=nodes[n].end)
r_extern
r_int
id|compute_hash_shift
c_func
(paren
r_struct
id|node
op_star
id|nodes
comma
r_int
id|numnodes
comma
id|u64
id|maxmem
)paren
suffix:semicolon
r_extern
r_int
r_int
id|nodes_present
suffix:semicolon
DECL|macro|ZONE_ALIGN
mdefine_line|#define ZONE_ALIGN (1UL &lt;&lt; (MAX_ORDER+PAGE_SHIFT))
macro_line|#endif
eof
