macro_line|#ifndef _ASM_MAX_NUMNODES_H
DECL|macro|_ASM_MAX_NUMNODES_H
mdefine_line|#define _ASM_MAX_NUMNODES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_X86_NUMAQ
macro_line|#include &lt;asm/numaq.h&gt;
macro_line|#elif CONFIG_X86_SUMMIT
macro_line|#include &lt;asm/srat.h&gt;
macro_line|#else
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES&t;1
macro_line|#endif /* CONFIG_X86_NUMAQ */
macro_line|#endif /* _ASM_MAX_NUMNODES_H */
eof
