macro_line|#ifndef _ASM_ALPHA_TOPOLOGY_H
DECL|macro|_ASM_ALPHA_TOPOLOGY_H
mdefine_line|#define _ASM_ALPHA_TOPOLOGY_H
macro_line|#ifdef CONFIG_NUMA
macro_line|#ifdef CONFIG_ALPHA_WILDFIRE
multiline_comment|/* With wildfire assume 4 CPUs per node */
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu)&t;&t;((cpu) &gt;&gt; 2)
macro_line|#endif /* CONFIG_ALPHA_WILDFIRE */
macro_line|#endif /* CONFIG_NUMA */
macro_line|#if !defined(CONFIG_NUMA) || !defined(CONFIG_ALPHA_WILDFIRE)
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu)&t;&t;(0)
DECL|macro|__memblk_to_node
mdefine_line|#define __memblk_to_node(memblk)&t;(0)
DECL|macro|__parent_node
mdefine_line|#define __parent_node(nid)&t;&t;(0)
DECL|macro|__node_to_first_cpu
mdefine_line|#define __node_to_first_cpu(node)&t;(0)
DECL|macro|__node_to_cpu_mask
mdefine_line|#define __node_to_cpu_mask(node)&t;(cpu_online_map)
DECL|macro|__node_to_memblk
mdefine_line|#define __node_to_memblk(node)&t;&t;(0)
macro_line|#endif /* !CONFIG_NUMA || !CONFIG_ALPHA_WILDFIRE */
macro_line|#endif /* _ASM_ALPHA_TOPOLOGY_H */
eof
