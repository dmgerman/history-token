multiline_comment|/*&n; *&t;Precise Delay Loops for SuperH&n; *&n; *&t;Copyright (C) 1999 Niibe Yutaka &amp; Kaz Kojima&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|function|__delay
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
c_func
(paren
l_string|&quot;tst&t;%0, %0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;bf/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; dt&t;%0&quot;
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
l_string|&quot;t&quot;
)paren
suffix:semicolon
)brace
DECL|function|__const_udelay
r_inline
r_void
id|__const_udelay
c_func
(paren
r_int
r_int
id|xloops
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;dmulu.l&t;%0, %2&bslash;n&bslash;t&quot;
l_string|&quot;sts&t;mach, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|xloops
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|xloops
)paren
comma
l_string|&quot;r&quot;
(paren
id|cpu_data
(braket
id|_smp_processor_id
c_func
(paren
)paren
)braket
dot
id|loops_per_jiffy
)paren
suffix:colon
l_string|&quot;macl&quot;
comma
l_string|&quot;mach&quot;
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|xloops
op_star
id|HZ
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
)paren
(brace
id|__const_udelay
c_func
(paren
id|usecs
op_star
l_int|0x000010c6
)paren
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 */
)brace
DECL|function|__ndelay
r_void
id|__ndelay
c_func
(paren
r_int
r_int
id|nsecs
)paren
(brace
id|__const_udelay
c_func
(paren
id|nsecs
op_star
l_int|0x00000005
)paren
suffix:semicolon
)brace
eof
