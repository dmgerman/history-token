macro_line|#ifndef _ASM_MAX_NUMNODES_H
DECL|macro|_ASM_MAX_NUMNODES_H
mdefine_line|#define _ASM_MAX_NUMNODES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_X86_NUMAQ
multiline_comment|/* Max 16 Nodes */
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT&t;4
macro_line|#elif defined(CONFIG_ACPI_SRAT)
multiline_comment|/* Max 8 Nodes */
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT&t;3
macro_line|#endif /* CONFIG_X86_NUMAQ */
macro_line|#endif /* _ASM_MAX_NUMNODES_H */
eof
