multiline_comment|/*&n; *  include/asm-s390/siginfo.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/siginfo.h&quot;&n; */
macro_line|#ifndef _S390_SIGINFO_H
DECL|macro|_S390_SIGINFO_H
mdefine_line|#define _S390_SIGINFO_H
macro_line|#ifdef __s390x__
DECL|macro|__ARCH_SI_PREAMBLE_SIZE
mdefine_line|#define __ARCH_SI_PREAMBLE_SIZE (4 * sizeof(int))
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_S390X
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE ((SIGEV_MAX_SIZE/sizeof(int)) - 4)
macro_line|#else
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE ((SIGEV_MAX_SIZE/sizeof(int)) - 3)
macro_line|#endif
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#endif
eof
