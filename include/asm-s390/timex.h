multiline_comment|/*&n; *  include/asm-s390/timex.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *&n; *  Derived from &quot;include/asm-i386/timex.h&quot;&n; *    Copyright (C) 1992, Linus Torvalds&n; */
macro_line|#ifndef _ASM_S390_TIMEX_H
DECL|macro|_ASM_S390_TIMEX_H
mdefine_line|#define _ASM_S390_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((long)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
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
c_func
(paren
r_void
)paren
(brace
id|cycles_t
id|cycles
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;stck 0(%1)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|cycles
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|cycles
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|cycles
op_rshift
l_int|2
suffix:semicolon
)brace
DECL|function|get_clock
r_static
r_inline
r_int
r_int
r_int
id|get_clock
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|clk
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;stck 0(%1)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|clk
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|clk
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|clk
suffix:semicolon
)brace
macro_line|#endif
eof
