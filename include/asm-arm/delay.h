macro_line|#ifndef __ASM_ARM_DELAY_H
DECL|macro|__ASM_ARM_DELAY_H
mdefine_line|#define __ASM_ARM_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1995 Russell King&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
r_extern
r_void
id|__delay
c_func
(paren
r_int
id|loops
)paren
suffix:semicolon
multiline_comment|/*&n; * division by multiplication: you don&squot;t have to worry about&n; * loss of precision.&n; *&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
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
r_return
id|a
op_star
id|b
op_div
id|c
suffix:semicolon
)brace
macro_line|#endif /* defined(_ARM_DELAY_H) */
eof
