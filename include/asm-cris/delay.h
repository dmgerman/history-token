macro_line|#ifndef _CRIS_DELAY_H
DECL|macro|_CRIS_DELAY_H
mdefine_line|#define _CRIS_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1998-2002 Axis Communications AB&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_second&quot; value.&n; */
macro_line|#include &lt;asm/arch/delay.h&gt;
multiline_comment|/* Use only for very small delays ( &lt; 1 msec).  */
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
