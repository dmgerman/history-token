macro_line|#ifndef _M68K_DELAY_H
DECL|macro|_M68K_DELAY_H
mdefine_line|#define _M68K_DELAY_H
macro_line|#include &lt;asm/param.h&gt;
multiline_comment|/*&n; * Copyright (C) 1994 Hamish Macdonald&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_jiffy&quot; value.&n; */
DECL|function|__delay
r_static
r_inline
r_void
id|__delay
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: subql #1,%0; jcc 1b&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__bad_udelay
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
DECL|function|__const_udelay
r_static
r_inline
r_void
id|__const_udelay
c_func
(paren
r_int
r_int
id|xloops
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mulul %2,%0:%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|xloops
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|xloops
)paren
comma
l_string|&quot;1&quot;
(paren
id|loops_per_jiffy
)paren
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|xloops
op_star
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|__udelay
r_static
r_inline
r_void
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
id|__const_udelay
c_func
(paren
id|usecs
op_star
l_int|4295
)paren
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 */
)brace
DECL|macro|udelay
mdefine_line|#define udelay(n) (__builtin_constant_p(n) ? &bslash;&n;&t;((n) &gt; 20000 ? __bad_udelay() : __const_udelay((n) * 4295)) : &bslash;&n;&t;__udelay(n))
DECL|function|muldiv
r_static
r_inline
r_int
r_int
id|muldiv
c_func
(paren
r_int
r_int
id|a
comma
r_int
r_int
id|b
comma
r_int
r_int
id|c
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mulul %2,%0:%1; divul %3,%0:%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=d&quot;
(paren
id|a
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|b
)paren
comma
l_string|&quot;d&quot;
(paren
id|c
)paren
comma
l_string|&quot;1&quot;
(paren
id|a
)paren
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
macro_line|#endif /* defined(_M68K_DELAY_H) */
eof
