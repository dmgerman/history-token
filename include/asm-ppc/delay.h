macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_DELAY_H
DECL|macro|_PPC_DELAY_H
mdefine_line|#define _PPC_DELAY_H
macro_line|#include &lt;asm/param.h&gt;
multiline_comment|/*&n; * Copyright 1996, Paul Mackerras.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
multiline_comment|/* maximum permitted argument to udelay */
DECL|macro|__MAX_UDELAY
mdefine_line|#define __MAX_UDELAY&t;1000000
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
multiline_comment|/* N.B. the `secs&squot; parameter here is a fixed-point number with&n;   the binary point to the left of the most-significant bit. */
DECL|function|__const_udelay
r_extern
id|__inline__
r_void
id|__const_udelay
c_func
(paren
r_int
r_int
id|secs
)paren
(brace
r_int
r_int
id|loops
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mulhwu %0,%1,%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|secs
)paren
comma
l_string|&quot;r&quot;
(paren
id|loops_per_jiffy
)paren
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|loops
op_star
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * note that 4294 == 2^32 / 10^6, multiplying by 4294 converts from&n; * microseconds to a 32-bit fixed-point number of seconds.&n; */
DECL|function|__udelay
r_extern
id|__inline__
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
l_int|4294
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
multiline_comment|/* deliberately undefined */
DECL|macro|udelay
mdefine_line|#define udelay(n) (__builtin_constant_p(n)? &bslash;&n;&t;&t;   ((n) &gt; __MAX_UDELAY? __bad_udelay(): __const_udelay((n) * 4294u)) : &bslash;&n;&t;&t;   __udelay(n))
macro_line|#endif /* defined(_PPC_DELAY_H) */
macro_line|#endif /* __KERNEL__ */
eof
