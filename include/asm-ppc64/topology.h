macro_line|#ifndef _ASM_PPC64_TOPOLOGY_H
DECL|macro|_ASM_PPC64_TOPOLOGY_H
mdefine_line|#define _ASM_PPC64_TOPOLOGY_H
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/* XXX grab this from the device tree - Anton */
DECL|macro|__cpu_to_node
mdefine_line|#define __cpu_to_node(cpu)&t;((cpu) &gt;&gt; CPU_SHIFT_BITS)
macro_line|#endif /* CONFIG_NUMA */
multiline_comment|/* Get the rest of the topology definitions */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* _ASM_PPC64_TOPOLOGY_H */
eof
