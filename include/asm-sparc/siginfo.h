multiline_comment|/* $Id: siginfo.h,v 1.9 2002/02/08 03:57:18 davem Exp $&n; * siginfo.c:&n; */
macro_line|#ifndef _SPARC_SIGINFO_H
DECL|macro|_SPARC_SIGINFO_H
mdefine_line|#define _SPARC_SIGINFO_H
DECL|macro|__ARCH_SI_UID_T
mdefine_line|#define __ARCH_SI_UID_T&t;&t;unsigned int
DECL|macro|__ARCH_SI_TRAPNO
mdefine_line|#define __ARCH_SI_TRAPNO
macro_line|#include &lt;asm-generic/siginfo.h&gt;
DECL|macro|SI_NOINFO
mdefine_line|#define SI_NOINFO&t;32767&t;&t;/* no information in siginfo_t */
multiline_comment|/*&n; * SIGEMT si_codes&n; */
DECL|macro|EMT_TAGOVF
mdefine_line|#define EMT_TAGOVF&t;(__SI_FAULT|1)&t;/* tag overflow */
DECL|macro|NSIGEMT
mdefine_line|#define NSIGEMT&t;&t;1
macro_line|#endif /* !(_SPARC_SIGINFO_H) */
eof
