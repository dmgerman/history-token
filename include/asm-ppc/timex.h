multiline_comment|/*&n; * BK Id: SCCS/s.timex.h 1.5 05/17/01 18:14:26 cort&n; */
multiline_comment|/*&n; * linux/include/asm-ppc/timex.h&n; *&n; * ppc architecture timex specifications&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASMppc_TIMEX_H
DECL|macro|_ASMppc_TIMEX_H
mdefine_line|#define _ASMppc_TIMEX_H
macro_line|#include &lt;linux/config.h&gt;
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
id|cycles_t
suffix:semicolon
multiline_comment|/*&n; * For the &quot;cycle&quot; counter we use the timebase lower half.&n; * Currently only used on SMP.&n; *&n; * Since SMP kernels won&squot;t run on the PPC601 CPU (which doesn&squot;t have&n; * the timebase register) anyway, we don&squot;t bother checking the CPU version.&n; */
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
macro_line|#ifdef CONFIG_SMP
id|cycles_t
id|ret
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mftb %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
