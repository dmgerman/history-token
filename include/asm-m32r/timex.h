macro_line|#ifndef _ASM_M32R_TIMEX_H
DECL|macro|_ASM_M32R_TIMEX_H
mdefine_line|#define _ASM_M32R_TIMEX_H
multiline_comment|/* $Id$ */
multiline_comment|/*&n; * linux/include/asm-m32r/timex.h&n; *&n; * m32r architecture timex specifications&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;(CONFIG_BUS_CLOCK / CONFIG_TIMER_DIVIDE)
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((long)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Standard way to access the cycle counter.&n; * Currently only used on SMP.&n; */
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
id|__inline__
id|cycles_t
id|get_cycles
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif  /* _ASM_M32R_TIMEX_H */
eof
