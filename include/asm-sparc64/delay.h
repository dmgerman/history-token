multiline_comment|/* $Id: delay.h,v 1.11 2001/01/02 08:15:32 davem Exp $&n; * delay.h: Linux delay routines on the V9.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu).&n; */
macro_line|#ifndef __SPARC64_DELAY_H
DECL|macro|__SPARC64_DELAY_H
mdefine_line|#define __SPARC64_DELAY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif 
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
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|b
comma
id|pt
op_mod
op_mod
id|xcc
comma
l_float|1f
id|cmp
op_mod
l_int|0
comma
l_int|0
dot
id|align
l_int|32
l_int|1
suffix:colon
id|bne
comma
id|pt
op_mod
op_mod
id|xcc
comma
l_int|1
id|b
id|subcc
op_mod
l_int|0
comma
l_int|1
comma
op_mod
l_int|0
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|loops
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|__udelay
r_extern
id|__inline__
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
id|lps
)paren
(brace
id|usecs
op_mul_assign
l_int|0x00000000000010c6UL
suffix:semicolon
multiline_comment|/* 2**32 / 1000000 */
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|mulx
op_mod
l_int|1
comma
op_mod
l_int|2
comma
op_mod
l_int|0
id|srlx
op_mod
l_int|0
comma
l_int|32
comma
op_mod
l_int|0
l_string|&quot;&t;: &quot;
op_assign
id|r
"&quot;"
(paren
id|usecs
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|usecs
)paren
comma
l_string|&quot;r&quot;
(paren
id|lps
)paren
)paren
suffix:semicolon
id|__delay
c_func
(paren
id|usecs
op_star
id|HZ
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val cpu_data[smp_processor_id()].udelay_val
macro_line|#else
DECL|macro|__udelay_val
mdefine_line|#define __udelay_val loops_per_jiffy
macro_line|#endif
DECL|macro|udelay
mdefine_line|#define udelay(usecs) __udelay((usecs),__udelay_val)
macro_line|#endif /* defined(__SPARC64_DELAY_H) */
eof
