multiline_comment|/*&n; * linux/include/asm-x86_64/timex.h&n; *&n; * x86-64 architecture timex specifications&n; */
macro_line|#ifndef _ASMx8664_TIMEX_H
DECL|macro|_ASMx8664_TIMEX_H
mdefine_line|#define _ASMx8664_TIMEX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/8253pit.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/vsyscall.h&gt;
macro_line|#include &lt;asm/hpet.h&gt;
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;PIT_TICK_RATE&t;/* Underlying HZ */
DECL|typedef|cycles_t
r_typedef
r_int
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
r_int
r_int
r_int
id|ret
suffix:semicolon
id|rdtscll
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_int
r_int
id|cpu_khz
suffix:semicolon
r_extern
r_struct
id|vxtime_data
id|vxtime
suffix:semicolon
macro_line|#endif
eof
