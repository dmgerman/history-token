multiline_comment|/*&n; * linux/include/asm-sparc64/timex.h&n; *&n; * sparc64 architecture timex specifications&n; */
macro_line|#ifndef _ASMsparc64_TIMEX_H
DECL|macro|_ASMsparc64_TIMEX_H
mdefine_line|#define _ASMsparc64_TIMEX_H
macro_line|#include &lt;asm/timer.h&gt;
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
multiline_comment|/* Getting on the cycle counter on sparc64. */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
DECL|macro|get_cycles
mdefine_line|#define get_cycles()&t;tick_ops-&gt;get_tick()
macro_line|#endif
eof
