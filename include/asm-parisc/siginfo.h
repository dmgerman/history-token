macro_line|#ifndef _PARISC_SIGINFO_H
DECL|macro|_PARISC_SIGINFO_H
mdefine_line|#define _PARISC_SIGINFO_H
DECL|macro|HAVE_ARCH_COPY_SIGINFO_TO_USER
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO_TO_USER
macro_line|#include &lt;asm-generic/siginfo.h&gt;
multiline_comment|/*&n; * SIGTRAP si_codes&n; */
DECL|macro|TRAP_BRANCH
mdefine_line|#define TRAP_BRANCH&t;(__SI_FAULT|3)&t;/* process taken branch trap */
DECL|macro|TRAP_HWBKPT
mdefine_line|#define TRAP_HWBKPT&t;(__SI_FAULT|4)&t;/* hardware breakpoint or watchpoint */
DECL|macro|NSIGTRAP
macro_line|#undef NSIGTRAP
DECL|macro|NSIGTRAP
mdefine_line|#define NSIGTRAP&t;4
macro_line|#endif
eof
