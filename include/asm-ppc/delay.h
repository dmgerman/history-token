macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_DELAY_H
DECL|macro|_PPC_DELAY_H
mdefine_line|#define _PPC_DELAY_H
multiline_comment|/*&n; * Copyright 1996, Paul Mackerras.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
r_extern
r_int
r_int
id|loops_per_sec
suffix:semicolon
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
r_if
c_cond
(paren
id|loops
op_ne
l_int|0
)paren
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mtctr %0; 1: bdnz 1b&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;ctr&quot;
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|loops
suffix:semicolon
multiline_comment|/* compute (usecs * 2^32 / 10^6) * loops_per_sec / 2^32 */
id|usecs
op_mul_assign
l_int|0x10c6
suffix:semicolon
multiline_comment|/* 2^32 / 10^6 */
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
id|usecs
)paren
comma
l_string|&quot;r&quot;
(paren
id|loops_per_sec
)paren
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|loops
)paren
suffix:semicolon
)brace
macro_line|#endif /* defined(_PPC_DELAY_H) */
macro_line|#endif /* __KERNEL__ */
eof
