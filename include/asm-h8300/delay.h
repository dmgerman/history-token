macro_line|#ifndef _H8300_DELAY_H
DECL|macro|_H8300_DELAY_H
mdefine_line|#define _H8300_DELAY_H
macro_line|#include &lt;asm/param.h&gt;
multiline_comment|/*&n; * Copyright (C) 2002 Yoshinori Sato &lt;ysato@sourceforge.jp&gt;&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
DECL|function|__delay
r_extern
id|__inline__
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
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;dec.l #1,%0&bslash;n&bslash;t&quot;
l_string|&quot;bne 1b&quot;
suffix:colon
l_string|&quot;=r&quot;
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
multiline_comment|/*&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)  &n; */
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|function|udelay
r_extern
id|__inline__
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
id|usecs
op_mul_assign
l_int|4295
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 */
id|usecs
op_div_assign
(paren
id|loops_per_jiffy
op_star
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usecs
)paren
id|__delay
c_func
(paren
id|usecs
)paren
suffix:semicolon
)brace
macro_line|#endif /* _H8300_DELAY_H */
eof
