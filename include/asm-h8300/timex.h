multiline_comment|/*&n; * linux/include/asm-h8300/timex.h&n; *&n; * H8/300 architecture timex specifications&n; */
macro_line|#ifndef _ASM_H8300_TIMEX_H
DECL|macro|_ASM_H8300_TIMEX_H
mdefine_line|#define _ASM_H8300_TIMEX_H
DECL|macro|H8300_TIMER_DEFINE
mdefine_line|#define H8300_TIMER_DEFINE
macro_line|#include &lt;asm/machine-depend.h&gt;
DECL|macro|H8300_TIMER_DEFINE
macro_line|#undef  H8300_TIMER_DEFINE
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE H8300_TIMER_FREQ
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((long)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
r_extern
r_int
id|h8300_timer_count
suffix:semicolon
DECL|function|get_cycles
r_static
r_inline
id|cycles_t
id|get_cycles
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
