multiline_comment|/*&n; * linux/include/asm-x8664/timex.h&n; *&n; * x8664 architecture timex specifications&n; */
macro_line|#ifndef _ASMx8664_TIMEX_H
DECL|macro|_ASMx8664_TIMEX_H
mdefine_line|#define _ASMx8664_TIMEX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/vsyscall.h&gt;
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((int)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
multiline_comment|/*&n; * Standard way to access the cycle counter on i586+ CPUs.&n; * Currently only used on SMP.&n; *&n; * If you really have a SMP machine with i486 chips or older,&n; * compile for that, and this will just always return zero.&n; * That&squot;s ok, it just means that the nicer scheduling heuristics&n; * won&squot;t work for you.&n; *&n; * We only use the low 32 bits, and we&squot;d simply better make sure&n; * that we reschedule before that wraps. Scheduling at least every&n; * four billion cycles just basically sounds like a good idea,&n; * regardless of how fast the machine is. &n; */
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
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_X86_TSC
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_int
r_int
r_int
id|ret
suffix:semicolon
id|rdtscll
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#endif
)brace
r_extern
r_int
r_int
id|cpu_khz
suffix:semicolon
DECL|macro|ARCH_HAS_JIFFIES_64
mdefine_line|#define ARCH_HAS_JIFFIES_64
macro_line|#endif
eof
