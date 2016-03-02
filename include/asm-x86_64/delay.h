macro_line|#ifndef _X8664_DELAY_H
DECL|macro|_X8664_DELAY_H
mdefine_line|#define _X8664_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines calling functions in arch/x86_64/lib/delay.c&n; */
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
id|usecs
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
mdefine_line|#define udelay(n) (__builtin_constant_p(n) ? &bslash;&n;&t;((n) &gt; 20000 ? __bad_udelay() : __const_udelay((n) * 0x10c6ul)) : &bslash;&n;&t;__udelay(n))
DECL|macro|ndelay
mdefine_line|#define ndelay(n) (__builtin_constant_p(n) ? &bslash;&n;       ((n) &gt; 20000 ? __bad_ndelay() : __const_udelay((n) * 5ul)) : &bslash;&n;       __ndelay(n))
macro_line|#endif /* defined(_X8664_DELAY_H) */
eof
