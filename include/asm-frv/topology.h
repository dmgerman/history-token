macro_line|#ifndef _ASM_TOPOLOGY_H
DECL|macro|_ASM_TOPOLOGY_H
mdefine_line|#define _ASM_TOPOLOGY_H
macro_line|#ifdef CONFIG_NUMA
macro_line|#error NUMA not supported yet
macro_line|#else /* !CONFIG_NUMA */
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _ASM_TOPOLOGY_H */
eof
