macro_line|#ifndef _ASM_X8664_NUMNODES_H
DECL|macro|_ASM_X8664_NUMNODES_H
mdefine_line|#define _ASM_X8664_NUMNODES_H 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES 8&t;/* APIC limit currently */
macro_line|#else
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES 1
macro_line|#endif
macro_line|#endif
eof
