macro_line|#ifndef _X8664_SIGINFO_H
DECL|macro|_X8664_SIGINFO_H
mdefine_line|#define _X8664_SIGINFO_H
DECL|macro|__ARCH_SI_PREAMBLE_SIZE
mdefine_line|#define __ARCH_SI_PREAMBLE_SIZE&t;(4 * sizeof(int))
DECL|macro|__ARCH_SI_BAND_T
mdefine_line|#define __ARCH_SI_BAND_T long
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE ((SIGEV_MAX_SIZE/sizeof(int)) - 4)
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#endif
eof
