multiline_comment|/* $Id: delay.h,v 1.4 2001/05/31 06:40:53 markusl Exp $ */
macro_line|#ifndef _CRIS_DELAY_H
DECL|macro|_CRIS_DELAY_H
mdefine_line|#define _CRIS_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999, 2000 Axis Communications AB&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif 
r_extern
r_void
id|__do_delay
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Special register call calling convention */
DECL|function|__delay
r_extern
id|__inline__
r_void
id|__delay
c_func
(paren
r_int
id|loops
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;move.d %0,r0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;cmpq 0,r0&bslash;n&bslash;t&quot;
l_string|&quot;beq 2f&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;subq 1,r0&bslash;n&bslash;t&quot;
l_string|&quot;ba 1b&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|loops
)paren
suffix:colon
l_string|&quot;r0&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Use only for very small delays ( &lt; 1 msec).  Should probably use a&n; * lookup table, really, as the multiplications take much too long with&n; * short delays.  This is a &quot;reasonable&quot; implementation, though (and the&n; * first constant multiplications gets optimized away if the delay is&n; * a constant)&n; */
r_extern
r_int
r_int
id|loops_per_usec
suffix:semicolon
multiline_comment|/* arch/cris/mm/init.c */
DECL|function|udelay
r_extern
id|__inline__
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
id|loops_per_usec
)paren
suffix:semicolon
)brace
macro_line|#endif /* defined(_CRIS_DELAY_H) */
eof
