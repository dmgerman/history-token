multiline_comment|/*&n; *  arch/s390/kernel/delay.c&n; *    Precise Delay Loops for S390&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *&n; *  Derived from &quot;arch/i386/lib/delay.c&quot;&n; *    Copyright (C) 1993 Linus Torvalds&n; *    Copyright (C) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif
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
l_string|&quot;0: ahi  %0,-1&bslash;n&quot;
l_string|&quot;   jnm  0b&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|loops
)paren
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
l_string|&quot;LR    3,%1&bslash;n&bslash;t&quot;
l_string|&quot;MR    2,%2&bslash;n&bslash;t&quot;
l_string|&quot;LR    %0,2&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|xloops
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|xloops
)paren
comma
l_string|&quot;r&quot;
(paren
id|loops_per_sec
)paren
suffix:colon
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|xloops
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
eof
