multiline_comment|/*&n; * linux/include/asm-parisc/timex.h&n; *&n; * PARISC architecture timex specifications&n; */
macro_line|#ifndef _ASMPARISC_TIMEX_H
DECL|macro|_ASMPARISC_TIMEX_H
mdefine_line|#define _ASMPARISC_TIMEX_H
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/time.h&gt;
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
r_extern
id|cycles_t
id|cacheflush_time
suffix:semicolon
DECL|function|get_cycles
r_static
r_inline
id|cycles_t
id|get_cycles
(paren
r_void
)paren
(brace
r_return
id|mfctl
c_func
(paren
l_int|16
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
