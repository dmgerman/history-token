multiline_comment|/*&n; * linux/include/asm-alpha/timex.h&n; *&n; * ALPHA architecture timex specifications&n; */
macro_line|#ifndef _ASMALPHA_TIMEX_H
DECL|macro|_ASMALPHA_TIMEX_H
mdefine_line|#define _ASMALPHA_TIMEX_H
multiline_comment|/* With only one or two oddballs, we use the RTC as the ticker, selecting&n;   the 32.768kHz reference clock, which nicely divides down to our HZ.  */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;32768
multiline_comment|/*&n; * Standard way to access the cycle counter.&n; * Currently only used on SMP for scheduling.&n; *&n; * Only the low 32 bits are available as a continuously counting entity. &n; * But this only means we&squot;ll force a reschedule every 8 seconds or so,&n; * which isn&squot;t an evil thing.&n; */
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
id|cycles_t
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;rpcc %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
eof
