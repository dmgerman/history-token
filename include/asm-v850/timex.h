multiline_comment|/*&n; * linux/include/asm-v850/timex.h&n; *&n; * v850 architecture timex specifications&n; */
macro_line|#ifndef __V850_TIMEX_H__
DECL|macro|__V850_TIMEX_H__
mdefine_line|#define __V850_TIMEX_H__
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
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
macro_line|#endif /* __V850_TIMEX_H__ */
eof
