macro_line|#ifndef _ASM_ALPHA_TOPOLOGY_H
DECL|macro|_ASM_ALPHA_TOPOLOGY_H
mdefine_line|#define _ASM_ALPHA_TOPOLOGY_H
macro_line|#if defined(CONFIG_NUMA) &amp;&amp; defined(CONFIG_ALPHA_WILDFIRE)
multiline_comment|/* With wildfire assume 4 CPUs per node */
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu)&t;&t;((cpu) &gt;&gt; 2)
macro_line|#else /* !CONFIG_NUMA || !CONFIG_ALPHA_WILDFIRE */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* CONFIG_NUMA &amp;&amp; CONFIG_ALPHA_WILDFIRE */
macro_line|#endif /* _ASM_ALPHA_TOPOLOGY_H */
eof
