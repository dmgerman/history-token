multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
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
multiline_comment|/*&n; * Note that 19 * 226 == 4294 ==~ 2^32 / 10^6, so&n; * loops = (4294 * usecs * loops_per_jiffy * HZ) / 2^32.&n; *&n; * The mulhwu instruction gives us loops = (a * b) / 2^32.&n; * We choose a = usecs * 19 * HZ and b = loops_per_jiffy * 226&n; * because this lets us support a wide range of HZ and&n; * loops_per_jiffy values without either a or b overflowing 2^32.&n; * Thus we need usecs * HZ &lt;= (2^32 - 1) / 19 = 226050910 and&n; * loops_per_jiffy &lt;= (2^32 - 1) / 226 = 19004280&n; * (which corresponds to ~3800 bogomips at HZ = 100).&n; *  -- paulus&n; */
DECL|macro|__MAX_UDELAY
mdefine_line|#define __MAX_UDELAY&t;(226050910/HZ)&t;/* maximum udelay argument */
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
id|usecs
op_star
(paren
l_int|19
op_star
id|HZ
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|loops_per_jiffy
op_star
l_int|226
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
mdefine_line|#define udelay(n) (__builtin_constant_p(n)? &bslash;&n;&t;&t;   ((n) &gt; __MAX_UDELAY? __bad_udelay(): __udelay((n))) : &bslash;&n;&t;&t;   __udelay(n))
macro_line|#endif /* defined(_PPC_DELAY_H) */
macro_line|#endif /* __KERNEL__ */
eof
