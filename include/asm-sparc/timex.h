multiline_comment|/*&n; * linux/include/asm-sparc/timex.h&n; *&n; * sparc architecture timex specifications&n; */
macro_line|#ifndef _ASMsparc_TIMEX_H
DECL|macro|_ASMsparc_TIMEX_H
mdefine_line|#define _ASMsparc_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
multiline_comment|/* XXX Maybe do something better at some point... -DaveM */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
DECL|macro|get_cycles
mdefine_line|#define get_cycles()&t;(0)
macro_line|#endif
eof
