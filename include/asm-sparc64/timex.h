multiline_comment|/*&n; * linux/include/asm-sparc64/timex.h&n; *&n; * sparc64 architecture timex specifications&n; */
macro_line|#ifndef _ASMsparc64_TIMEX_H
DECL|macro|_ASMsparc64_TIMEX_H
mdefine_line|#define _ASMsparc64_TIMEX_H
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((long)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
multiline_comment|/* Getting on the cycle counter on sparc64. */
DECL|typedef|cycles_t
r_typedef
r_int
r_int
id|cycles_t
suffix:semicolon
DECL|macro|get_cycles
mdefine_line|#define get_cycles() &bslash;&n;({&t;cycles_t ret; &bslash;&n;&t;__asm__ __volatile__(&quot;rd&t;%%tick, %0&quot; : &quot;=r&quot; (ret)); &bslash;&n;&t;ret; &bslash;&n;})
macro_line|#endif
eof
