macro_line|#ifndef _LINUX_DELAY_H
DECL|macro|_LINUX_DELAY_H
mdefine_line|#define _LINUX_DELAY_H
multiline_comment|/*&n; * Copyright (C) 1993 Linus Torvalds&n; *&n; * Delay routines, using a pre-computed &quot;loops_per_jiffy&quot; value.&n; */
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
macro_line|#include &lt;asm/delay.h&gt;
multiline_comment|/*&n; * Using udelay() for intervals greater than a few milliseconds can&n; * risk overflow for high loops_per_jiffy (high bogomips) machines. The&n; * mdelay() provides a wrapper to prevent this.  For delays greater&n; * than MAX_UDELAY_MS milliseconds, the wrapper is used.  Architecture&n; * specific values can be defined in asm-???/delay.h as an override.&n; * The 2nd mdelay() definition ensures GCC will optimize away the &n; * while loop for the common cases where n &lt;= MAX_UDELAY_MS  --  Paul G.&n; */
macro_line|#ifndef MAX_UDELAY_MS
DECL|macro|MAX_UDELAY_MS
mdefine_line|#define MAX_UDELAY_MS&t;5
macro_line|#endif
macro_line|#ifdef notdef
DECL|macro|mdelay
mdefine_line|#define mdelay(n) (&bslash;&n;&t;{unsigned long msec=(n); while (msec--) udelay(1000);})
macro_line|#else
DECL|macro|mdelay
mdefine_line|#define mdelay(n) (&bslash;&n;&t;(__builtin_constant_p(n) &amp;&amp; (n)&lt;=MAX_UDELAY_MS) ? udelay((n)*1000) : &bslash;&n;&t;({unsigned long msec=(n); while (msec--) udelay(1000);}))
macro_line|#endif
macro_line|#endif /* defined(_LINUX_DELAY_H) */
eof
