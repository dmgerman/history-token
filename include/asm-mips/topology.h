macro_line|#ifndef __ASM_TOPOLOGY_H
DECL|macro|__ASM_TOPOLOGY_H
mdefine_line|#define __ASM_TOPOLOGY_H
macro_line|#if CONFIG_SGI_IP27
macro_line|#include &lt;asm/mmzone.h&gt;
DECL|macro|cpu_to_node
mdefine_line|#define cpu_to_node(cpu)&t;(cputocnode(cpu))
macro_line|#endif
macro_line|#include &lt;asm-generic/topology.h&gt;
macro_line|#endif /* __ASM_TOPOLOGY_H */
eof
