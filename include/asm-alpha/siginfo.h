macro_line|#ifndef _ALPHA_SIGINFO_H
DECL|macro|_ALPHA_SIGINFO_H
mdefine_line|#define _ALPHA_SIGINFO_H
DECL|macro|__ARCH_SI_PREAMBLE_SIZE
mdefine_line|#define __ARCH_SI_PREAMBLE_SIZE&t;&t;(4 * sizeof(int))
DECL|macro|__ARCH_SI_TRAPNO
mdefine_line|#define __ARCH_SI_TRAPNO
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;&t;&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|__ARCH_SI_BAND_T
mdefine_line|#define __ARCH_SI_BAND_T int
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#endif
eof
