macro_line|#ifndef _LINUX_PTRACE_H
DECL|macro|_LINUX_PTRACE_H
mdefine_line|#define _LINUX_PTRACE_H
multiline_comment|/* ptrace.h */
multiline_comment|/* structs and defines to help the user use the ptrace system call. */
multiline_comment|/* has the defines to get at the registers. */
DECL|macro|PTRACE_TRACEME
mdefine_line|#define PTRACE_TRACEME&t;&t;   0
DECL|macro|PTRACE_PEEKTEXT
mdefine_line|#define PTRACE_PEEKTEXT&t;&t;   1
DECL|macro|PTRACE_PEEKDATA
mdefine_line|#define PTRACE_PEEKDATA&t;&t;   2
DECL|macro|PTRACE_PEEKUSR
mdefine_line|#define PTRACE_PEEKUSR&t;&t;   3
DECL|macro|PTRACE_POKETEXT
mdefine_line|#define PTRACE_POKETEXT&t;&t;   4
DECL|macro|PTRACE_POKEDATA
mdefine_line|#define PTRACE_POKEDATA&t;&t;   5
DECL|macro|PTRACE_POKEUSR
mdefine_line|#define PTRACE_POKEUSR&t;&t;   6
DECL|macro|PTRACE_CONT
mdefine_line|#define PTRACE_CONT&t;&t;   7
DECL|macro|PTRACE_KILL
mdefine_line|#define PTRACE_KILL&t;&t;   8
DECL|macro|PTRACE_SINGLESTEP
mdefine_line|#define PTRACE_SINGLESTEP&t;   9
DECL|macro|PTRACE_ATTACH
mdefine_line|#define PTRACE_ATTACH&t;&t;0x10
DECL|macro|PTRACE_DETACH
mdefine_line|#define PTRACE_DETACH&t;&t;0x11
DECL|macro|PTRACE_SYSCALL
mdefine_line|#define PTRACE_SYSCALL&t;&t;  24
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#endif
eof
