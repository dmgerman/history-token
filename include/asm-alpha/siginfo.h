macro_line|#ifndef _ALPHA_SIGINFO_H
DECL|macro|_ALPHA_SIGINFO_H
mdefine_line|#define _ALPHA_SIGINFO_H
DECL|macro|SI_PAD_SIZE
mdefine_line|#define SI_PAD_SIZE&t;((SI_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|SIGEV_PAD_SIZE
mdefine_line|#define SIGEV_PAD_SIZE&t;((SIGEV_MAX_SIZE/sizeof(int)) - 4)
DECL|macro|HAVE_ARCH_COPY_SIGINFO
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO
DECL|macro|HAVE_ARCH_COPY_SIGINFO_TO_USER
mdefine_line|#define HAVE_ARCH_COPY_SIGINFO_TO_USER
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/string.h&gt;
DECL|function|copy_siginfo
r_extern
r_inline
r_void
id|copy_siginfo
c_func
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
id|from-&gt;si_code
OL
l_int|0
)paren
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/* _sigchld is currently the largest know union member */
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
l_int|4
op_star
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
id|from-&gt;_sifields._sigchld
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
