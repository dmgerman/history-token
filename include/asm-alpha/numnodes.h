macro_line|#ifndef _ASM_MAX_NUMNODES_H
DECL|macro|_ASM_MAX_NUMNODES_H
mdefine_line|#define _ASM_MAX_NUMNODES_H
multiline_comment|/*&n; * Currently the Wildfire is the only discontigmem/NUMA capable Alpha core.&n; */
macro_line|#if defined(CONFIG_ALPHA_WILDFIRE) || defined(CONFIG_ALPHA_GENERIC)
macro_line|# include &lt;asm/core_wildfire.h&gt;
DECL|macro|MAX_NUMNODES
macro_line|# define MAX_NUMNODES&t;&t;WILDFIRE_MAX_QBB
macro_line|#endif
macro_line|#endif /* _ASM_MAX_NUMNODES_H */
eof
