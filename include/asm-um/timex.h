macro_line|#ifndef __UM_TIMEX_H
DECL|macro|__UM_TIMEX_H
mdefine_line|#define __UM_TIMEX_H
macro_line|#include &quot;linux/time.h&quot;
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
DECL|macro|cacheflush_time
mdefine_line|#define cacheflush_time (0)
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
l_int|0
suffix:semicolon
)brace
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE (HZ)
macro_line|#endif
eof
