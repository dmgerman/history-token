macro_line|#ifndef __ALPHA_DELAY_H
DECL|macro|__ALPHA_DELAY_H
mdefine_line|#define __ALPHA_DELAY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/*&n; * Copyright (C) 1993, 2000 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_jiffy&quot; value.&n; */
multiline_comment|/*&n; * Use only for very small delays (&lt; 1 msec). &n; *&n; * The active part of our cycle counter is only 32-bits wide, and&n; * we&squot;re treating the difference between two marks as signed.  On&n; * a 1GHz box, that&squot;s about 2 seconds.&n; */
r_extern
id|__inline__
r_void
DECL|function|__delay
id|__delay
c_func
(paren
r_int
id|loops
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;rpcc %0&bslash;n&quot;
l_string|&quot;&t;addl %1,%0,%1&bslash;n&quot;
l_string|&quot;1:&t;rpcc %0&bslash;n&quot;
l_string|&quot;&t;subl %1,%0,%0&bslash;n&quot;
l_string|&quot;&t;bgt %0,1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|__udelay
id|__udelay
c_func
(paren
r_int
r_int
id|usecs
comma
r_int
r_int
id|lpj
)paren
(brace
id|usecs
op_mul_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|HZ
op_lshift
l_int|32
)paren
op_div
l_int|1000000
)paren
op_star
id|lpj
suffix:semicolon
id|__delay
c_func
(paren
(paren
r_int
)paren
id|usecs
op_rshift
l_int|32
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/sched.h&gt;&t;/* for smp_processor_id */
DECL|macro|udelay
mdefine_line|#define udelay(u)  __udelay((u), cpu_data[smp_processor_id()].loops_per_jiffy)
macro_line|#else
DECL|macro|udelay
mdefine_line|#define udelay(u)  __udelay((u), loops_per_jiffy)
macro_line|#endif
macro_line|#endif /* defined(__ALPHA_DELAY_H) */
eof
