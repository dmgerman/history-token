macro_line|#ifndef _ASM_MAX_NUMNODES_H
DECL|macro|_ASM_MAX_NUMNODES_H
mdefine_line|#define _ASM_MAX_NUMNODES_H
macro_line|#ifdef CONFIG_IA64_DIG
multiline_comment|/* Max 8 Nodes */
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT&t;3
macro_line|#elif defined(CONFIG_IA64_SGI_SN2) || defined(CONFIG_IA64_GENERIC)
multiline_comment|/* Max 128 Nodes */
DECL|macro|NODES_SHIFT
mdefine_line|#define NODES_SHIFT&t;7
macro_line|#endif
macro_line|#endif /* _ASM_MAX_NUMNODES_H */
eof
