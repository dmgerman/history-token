multiline_comment|/* delay.h: FRV delay code&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_DELAY_H
DECL|macro|_ASM_DELAY_H
mdefine_line|#define _ASM_DELAY_H
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/timer-regs.h&gt;
multiline_comment|/*&n; * delay loop - runs at __core_clock_speed_HZ / 2 [there are 2 insns in the loop]&n; */
r_extern
r_int
r_int
id|__delay_loops_MHz
suffix:semicolon
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
id|asm
r_volatile
(paren
l_string|&quot;1:&t;subicc&t;%0,#1,%0,icc0&t;&bslash;n&quot;
l_string|&quot;&t;&t;bnc&t;icc0,#2,1b&t;&bslash;n&quot;
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
suffix:colon
l_string|&quot;icc0&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|function|udelay
r_static
r_inline
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
id|__delay
c_func
(paren
id|usecs
op_star
id|__delay_loops_MHz
)paren
suffix:semicolon
)brace
DECL|macro|ndelay
mdefine_line|#define ndelay(n)&t;udelay((n) * 5)
macro_line|#endif /* _ASM_DELAY_H */
eof
