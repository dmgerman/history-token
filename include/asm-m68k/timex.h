multiline_comment|/*&n; * linux/include/asm-m68k/timex.h&n; *&n; * m68k architecture timex specifications&n; */
macro_line|#ifndef _ASMm68k_TIMEX_H
DECL|macro|_ASMm68k_TIMEX_H
mdefine_line|#define _ASMm68k_TIMEX_H
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
macro_line|#endif
eof
