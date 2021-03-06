macro_line|#ifndef _SPARC64_SIGINFO_H
DECL|macro|_SPARC64_SIGINFO_H
mdefine_line|#define _SPARC64_SIGINFO_H
DECL|macro|SI_PAD_SIZE32
mdefine_line|#define SI_PAD_SIZE32&t;((SI_MAX_SIZE/sizeof(int)) - 3)
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|__ARCH_SI_PREAMBLE_SIZE
mdefine_line|#define __ARCH_SI_PREAMBLE_SIZE&t;(4 * sizeof(int))
DECL|macro|__ARCH_SI_TRAPNO
mdefine_line|#define __ARCH_SI_TRAPNO
DECL|macro|__ARCH_SI_BAND_T
mdefine_line|#define __ARCH_SI_BAND_T int
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#ifdef CONFIG_COMPAT
r_struct
id|compat_siginfo
suffix:semicolon
macro_line|#endif /* CONFIG_COMPAT */
macro_line|#endif /* __KERNEL__ */
DECL|macro|SI_NOINFO
mdefine_line|#define SI_NOINFO&t;32767&t;&t;/* no information in siginfo_t */
multiline_comment|/*&n; * SIGEMT si_codes&n; */
DECL|macro|EMT_TAGOVF
mdefine_line|#define EMT_TAGOVF&t;(__SI_FAULT|1)&t;/* tag overflow */
DECL|macro|NSIGEMT
mdefine_line|#define NSIGEMT&t;&t;1
macro_line|#endif
eof
