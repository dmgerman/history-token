macro_line|#ifndef _ASM_X8664_NUMA_H 
DECL|macro|_ASM_X8664_NUMA_H
mdefine_line|#define _ASM_X8664_NUMA_H 1
macro_line|#include &lt;linux/nodemask.h&gt;
macro_line|#include &lt;asm/numnodes.h&gt;
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
mdefine_line|#define for_all_nodes(x) for ((x) = 0; (x) &lt; numnodes; (x)++) &bslash;&n;&t;&t;&t;&t;if (node_online(x))
r_extern
r_int
id|compute_hash_shift
c_func
(paren
r_struct
id|node
op_star
id|nodes
)paren
suffix:semicolon
DECL|macro|ZONE_ALIGN
mdefine_line|#define ZONE_ALIGN (1UL &lt;&lt; (MAX_ORDER+PAGE_SHIFT))
r_extern
r_void
id|numa_add_cpu
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|numa_init_array
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|numa_off
suffix:semicolon
macro_line|#endif
eof
