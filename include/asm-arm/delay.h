multiline_comment|/*&n; * Copyright (C) 1995-2004 Russell King&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
macro_line|#ifndef __ASM_ARM_DELAY_H
DECL|macro|__ASM_ARM_DELAY_H
mdefine_line|#define __ASM_ARM_DELAY_H
r_extern
r_void
id|__delay
c_func
(paren
r_int
id|loops
)paren
suffix:semicolon
multiline_comment|/*&n; * This function intentionally does not exist; if you see references to&n; * it, it means that you&squot;re calling udelay() with an out of range value.&n; *&n; * With currently imposed limits, this means that we support a max delay&n; * of 2000us and 671 bogomips&n; */
r_extern
r_void
id|__bad_udelay
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * division by multiplication: you don&squot;t have to worry about&n; * loss of precision.&n; *&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
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
id|__const_udelay
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|MAX_UDELAY_MS
mdefine_line|#define MAX_UDELAY_MS 2
DECL|macro|udelay
mdefine_line|#define udelay(n)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(__builtin_constant_p(n) ?&t;&t;&t;&t;&bslash;&n;&t;  ((n) &gt; (MAX_UDELAY_MS * 1000) ? __bad_udelay() :&t;&bslash;&n;&t;&t;&t;__const_udelay((n) * 0x68dbul)) :&t;&bslash;&n;&t;  __udelay(n))
macro_line|#endif /* defined(_ARM_DELAY_H) */
eof
