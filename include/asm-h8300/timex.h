multiline_comment|/*&n; * linux/include/asm-h8300/timex.h&n; *&n; * H8/300 architecture timex specifications&n; */
macro_line|#ifndef _ASM_H8300_TIMEX_H
DECL|macro|_ASM_H8300_TIMEX_H
mdefine_line|#define _ASM_H8300_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE CONFIG_CPU_CLOCK*1000/8192 /* Timer input freq. */
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
