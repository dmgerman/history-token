macro_line|#ifndef _ASM_X8664_NUMNODES_H
DECL|macro|_ASM_X8664_NUMNODES_H
mdefine_line|#define _ASM_X8664_NUMNODES_H 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_NUMA
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT&t;6
macro_line|#else
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT&t;0
macro_line|#endif
macro_line|#endif
eof
