multiline_comment|/*&n; *&t;Precise Delay Loops for x86-64&n; *&n; *&t;Copyright (C) 1993 Linus Torvalds&n; *&t;Copyright (C) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; *&n; *&t;The __delay function must _NOT_ be inlined as its execution time&n; *&t;depends wildly on alignment on many x86 processors. &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif
DECL|variable|x86_udelay_tsc
r_int
id|x86_udelay_tsc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Delay via TSC */
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
r_int
id|bclock
comma
id|now
suffix:semicolon
id|rdtscl
c_func
(paren
id|bclock
)paren
suffix:semicolon
r_do
(brace
id|rep_nop
c_func
(paren
)paren
suffix:semicolon
id|rdtscl
c_func
(paren
id|now
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|now
op_minus
id|bclock
)paren
OL
id|loops
)paren
(brace
suffix:semicolon
)brace
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
id|__delay
c_func
(paren
(paren
(paren
id|xloops
op_star
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
op_rshift
l_int|32
)paren
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
l_int|0x00005
)paren
suffix:semicolon
multiline_comment|/* 2**32 / 1000000000 (rounded up) */
)brace
eof
