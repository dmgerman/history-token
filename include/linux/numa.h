macro_line|#ifndef _LINUX_NUMA_H
DECL|macro|_LINUX_NUMA_H
mdefine_line|#define _LINUX_NUMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#include &lt;asm/numnodes.h&gt;
macro_line|#endif
macro_line|#ifndef NODES_SHIFT
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT     0
macro_line|#endif
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES    (1 &lt;&lt; NODES_SHIFT)
macro_line|#endif /* _LINUX_NUMA_H */
eof
