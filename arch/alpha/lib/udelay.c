macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt; /* for udelay&squot;s use of smp_processor_id */
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
multiline_comment|/*&n; * Copyright (C) 1993, 2000 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_jiffy&quot; value.&n; */
multiline_comment|/*&n; * Use only for very small delays (&lt; 1 msec). &n; *&n; * The active part of our cycle counter is only 32-bits wide, and&n; * we&squot;re treating the difference between two marks as signed.  On&n; * a 1GHz box, that&squot;s about 2 seconds.&n; */
DECL|function|__delay
r_void
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
DECL|function|__udelay
r_void
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
DECL|function|udelay
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|__udelay
c_func
(paren
id|usecs
comma
id|cpu_data
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|loops_per_jiffy
)paren
suffix:semicolon
macro_line|#else
id|__udelay
c_func
(paren
id|usecs
comma
id|loops_per_jiffy
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
