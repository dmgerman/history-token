macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_SETUP_H
DECL|macro|_PPC_SETUP_H
mdefine_line|#define _PPC_SETUP_H
DECL|macro|m68k_num_memory
mdefine_line|#define m68k_num_memory num_memory
DECL|macro|m68k_memory
mdefine_line|#define m68k_memory memory
macro_line|#include &lt;asm-m68k/setup.h&gt;
multiline_comment|/* We have a bigger command line buffer. */
DECL|macro|COMMAND_LINE_SIZE
macro_line|#undef COMMAND_LINE_SIZE
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;512
macro_line|#endif /* _PPC_SETUP_H */
macro_line|#endif /* __KERNEL__ */
eof
