multiline_comment|/* $Id: delay.h,v 1.11 2001/01/01 01:46:15 davem Exp $&n; * delay.h: Linux delay routines on the Sparc.&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu).&n; */
macro_line|#ifndef __SPARC_DELAY_H
DECL|macro|__SPARC_DELAY_H
mdefine_line|#define __SPARC_DELAY_H
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
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
l_string|&quot;cmp %0, 0&bslash;n&bslash;t&quot;
l_string|&quot;1: bne 1b&bslash;n&bslash;t&quot;
l_string|&quot;subcc %0, 1, %0&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
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
multiline_comment|/* This is too messy with inline asm on the Sparc. */
r_extern
r_void
id|udelay
c_func
(paren
r_int
r_int
id|usecs
)paren
suffix:semicolon
macro_line|#endif /* defined(__SPARC_DELAY_H) */
eof
