multiline_comment|/*&n; * linux/arch/m32r/lib/delay.c&n; *&n; * Copyright (c) 2002  Hitoshi Yamamoto, Hirokazu Takata&n; * Copyright (c) 2004  Hirokazu Takata&n; */
multiline_comment|/* $Id$ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif  /* CONFIG_SMP */
macro_line|#include &lt;asm/processor.h&gt;
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
macro_line|#ifdef CONFIG_ISA_DUAL_ISSUE
id|__asm__
id|__volatile__
(paren
l_string|&quot;beqz&t;%0, 2f&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot; .fillinsn&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;1:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;cmpz&t;%0  ||  addi  %0, #-1&t;&bslash;n&bslash;t&quot;
l_string|&quot;bc&t;2f  ||  cmpz  %0&t;&bslash;n&bslash;t&quot;
l_string|&quot;bc&t;2f  ||  addi  %0, #-1&t;&bslash;n&bslash;t&quot;
l_string|&quot;cmpz&t;%0  ||  addi  %0, #-1&t;&bslash;n&bslash;t&quot;
l_string|&quot;bc&t;2f  ||  cmpz  %0&t;&bslash;n&bslash;t&quot;
l_string|&quot;bnc&t;1b  ||  addi  %0, #-1&t;&bslash;n&bslash;t&quot;
l_string|&quot; .fillinsn&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;2:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;cbit&quot;
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
(paren
l_string|&quot;beqz&t;%0, 2f&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot; .fillinsn&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;1:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;blez&t;%0, 2f&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;blez&t;%0, 2f&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;blez&t;%0, 2f&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;bgtz&t;%0, 1b&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot; .fillinsn&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;2:&t;&t;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|__const_udelay
r_void
id|__const_udelay
c_func
(paren
r_int
r_int
id|xloops
)paren
(brace
macro_line|#if defined(CONFIG_ISA_M32R2) &amp;&amp; defined(CONFIG_ISA_DSP_LEVEL2)
multiline_comment|/*&n;&t; * loops [1] = (xloops &gt;&gt; 32) [sec] * loops_per_jiffy [1/jiffy]&n;&t; *            * HZ [jiffy/sec]&n;&t; *          = (xloops &gt;&gt; 32) [sec] * (loops_per_jiffy * HZ) [1/sec]&n;&t; *          = (((xloops * loops_per_jiffy) &gt;&gt; 32) * HZ) [1]&n;&t; *&n;&t; * NOTE:&n;&t; *   - &squot;[]&squot; depicts variable&squot;s dimension in the above equation.&n;&t; *   - &quot;rac&quot; instruction rounds the accumulator in word size.&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;srli&t;%0, #1&t;&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mulwhi&t;%0, %1&t;; a0&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mulwu1&t;%0, %1&t;; a1&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;sadd&t;&t;; a0 += (a1 &gt;&gt; 16)&t;&bslash;n&bslash;t&quot;
l_string|&quot;rac&t;a0, a0, #1&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvfacmi %0, a0&t;&t;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|xloops
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|current_cpu_data.loops_per_jiffy
)paren
suffix:colon
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ISA_M32R2) || defined(CONFIG_ISA_M32R)
multiline_comment|/*&n;&t; * u64 ull;&n;&t; * ull = (u64)xloops * (u64)current_cpu_data.loops_per_jiffy;&n;&t; * xloops = (ull &gt;&gt; 32);&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;and3&t;r4, %0, #0xffff&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;and3&t;r5, %1, #0xffff&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mul&t;r4, r5&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl3&t;r6, %0, #16&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;srli&t;r4, #16&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mul&t;r5, r6&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;r4, r5&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;and3&t;r5, %0, #0xffff&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl3&t;r6, %1, #16&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mul&t;r5, r6&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;r4, r5&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl3&t;r5, %0, #16&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;srli&t;r4, #16&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mul&t;r5, r6&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;r4, r5&t;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mv&t;%0, r4&t;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|xloops
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|current_cpu_data.loops_per_jiffy
)paren
suffix:colon
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;r6&quot;
)paren
suffix:semicolon
macro_line|#else
macro_line|#error unknown isa configuration
macro_line|#endif
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
l_int|0x000010c7
)paren
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 (rounded up) */
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
