macro_line|#ifndef _M68KNOMMU_DELAY_H
DECL|macro|_M68KNOMMU_DELAY_H
mdefine_line|#define _M68KNOMMU_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1994 Hamish Macdonald&n; * Copyright (C) 2004 Greg Ungerer &lt;gerg@snapgear.com&gt;&n; */
macro_line|#include &lt;asm/param.h&gt;
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
macro_line|#if defined(CONFIG_COLDFIRE)
multiline_comment|/* The coldfire runs this loop at significantly different speeds&n;&t; * depending upon long word alignment or not.  We&squot;ll pad it to&n;&t; * long word alignment which is the faster version.&n;&t; * The 0x4a8e is of course a &squot;tstl %fp&squot; instruction.  This is better&n;&t; * than using a NOP (0x4e71) instruction because it executes in one&n;&t; * cycle not three and doesn&squot;t allow for an arbitary delay waiting&n;&t; * for bus cycles to finish.  Also fp/a6 isn&squot;t likely to cause a&n;&t; * stall waiting for the register to become valid if such is added&n;&t; * to the coldfire at some stage.&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;.balignw 4, 0x4a8e&bslash;n&bslash;t&quot;
l_string|&quot;1: subql #1, %0&bslash;n&bslash;t&quot;
l_string|&quot;jcc 1b&quot;
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
macro_line|#else
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: subql #1, %0&bslash;n&bslash;t&quot;
l_string|&quot;jcc 1b&quot;
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
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Ideally we use a 32*32-&gt;64 multiply to calculate the number of&n; *&t;loop iterations, but the older standard 68k and ColdFire do not&n; *&t;have this instruction. So for them we have a clsoe approximation&n; *&t;loop using 32*32-&gt;32 multiplies only. This calculation based on&n; *&t;the ARM version of delay.&n; *&n; *&t;We want to implement:&n; *&n; *&t;loops = (usecs * 0x10c6 * HZ * loops_per_jiffy) / 2^32&n; */
DECL|macro|HZSCALE
mdefine_line|#define&t;HZSCALE&t;&t;(268435456 / (1000000/HZ))
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|function|_udelay
r_extern
id|__inline__
r_void
id|_udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
macro_line|#if defined(CONFIG_M68328) || defined(CONFIG_M68EZ328) || &bslash;&n;    defined(CONFIG_M68VZ328) || defined(CONFIG_M68360) || &bslash;&n;    defined(CONFIG_COLDFIRE)
id|__delay
c_func
(paren
(paren
(paren
(paren
id|usecs
op_star
id|HZSCALE
)paren
op_rshift
l_int|11
)paren
op_star
(paren
id|loops_per_jiffy
op_rshift
l_int|11
)paren
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|tmp
suffix:semicolon
id|usecs
op_mul_assign
l_int|4295
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 */
id|__asm__
(paren
l_string|&quot;mulul %2,%0:%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;1&quot;
(paren
id|loops_per_jiffy
op_star
id|HZ
)paren
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|usecs
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Moved the udelay() function into library code, no longer inlined.&n; *&t;I had to change the algorithm because we are overflowing now on&n; *&t;the faster ColdFire parts. The code is a little biger, so it makes&n; *&t;sense to library it.&n; */
r_extern
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
macro_line|#endif /* defined(_M68KNOMMU_DELAY_H) */
eof
