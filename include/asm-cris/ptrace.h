macro_line|#ifndef _CRIS_PTRACE_H
DECL|macro|_CRIS_PTRACE_H
mdefine_line|#define _CRIS_PTRACE_H
macro_line|#include &lt;asm/arch/ptrace.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS            12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS            13
macro_line|#endif
macro_line|#endif /* _CRIS_PTRACE_H */
eof
