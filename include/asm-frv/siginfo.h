macro_line|#ifndef _ASM_SIGINFO_H
DECL|macro|_ASM_SIGINFO_H
mdefine_line|#define _ASM_SIGINFO_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm-generic/siginfo.h&gt;
DECL|macro|FPE_MDAOVF
mdefine_line|#define FPE_MDAOVF&t;(__SI_FAULT|9)&t;/* media overflow */
DECL|macro|NSIGFPE
macro_line|#undef NSIGFPE
DECL|macro|NSIGFPE
mdefine_line|#define NSIGFPE&t;&t;9
macro_line|#endif
eof
