multiline_comment|/* delay.h: Linux delay routines on sparc64.&n; *&n; * Copyright (C) 1996, 2004 David S. Miller (davem@davemloft.net).&n; *&n; * Based heavily upon x86 variant which is:&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines calling functions in arch/sparc64/lib/delay.c&n; */
macro_line|#ifndef __SPARC64_DELAY_H
DECL|macro|__SPARC64_DELAY_H
mdefine_line|#define __SPARC64_DELAY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;asm/cpudata.h&gt;
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__bad_udelay
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__bad_ndelay
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_void
id|__ndelay
c_func
(paren
r_int
r_int
id|nsecs
)paren
suffix:semicolon
r_extern
r_void
id|__const_udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_void
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
suffix:semicolon
DECL|macro|udelay
mdefine_line|#define udelay(n) (__builtin_constant_p(n) ? &bslash;&n;&t;((n) &gt; 20000 ? __bad_udelay() : __const_udelay((n) * 0x10c7ul)) : &bslash;&n;&t;__udelay(n))
DECL|macro|ndelay
mdefine_line|#define ndelay(n) (__builtin_constant_p(n) ? &bslash;&n;&t;((n) &gt; 20000 ? __bad_ndelay() : __const_udelay((n) * 5ul)) : &bslash;&n;&t;__ndelay(n))
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* defined(__SPARC64_DELAY_H) */
eof
