multiline_comment|/*&n; * linux/include/asm-cris/timex.h&n; *&n; * CRIS architecture timex specifications&n; */
macro_line|#ifndef _ASM_CRIS_TIMEX_H
DECL|macro|_ASM_CRIS_TIMEX_H
mdefine_line|#define _ASM_CRIS_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE 19200 /* Underlying frequency of the HZ timer */
multiline_comment|/*&n; * We don&squot;t have a cycle-counter.. but we do not support SMP anyway where this is&n; * used so it does not matter.&n; */
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
