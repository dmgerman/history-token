multiline_comment|/*&n; * linux/include/asm-i386/timex.h&n; *&n; * i386 architecture timex specifications&n; */
macro_line|#ifndef _ASMi386_TIMEX_H
DECL|macro|_ASMi386_TIMEX_H
mdefine_line|#define _ASMi386_TIMEX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#ifdef CONFIG_X86_ELAN
DECL|macro|CLOCK_TICK_RATE
macro_line|#  define CLOCK_TICK_RATE 1189200 /* AMD Elan has different frequency! */
macro_line|#else
DECL|macro|CLOCK_TICK_RATE
macro_line|#  define CLOCK_TICK_RATE 1193182 /* Underlying HZ */
macro_line|#endif
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
r_int
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifndef CONFIG_X86_TSC
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_tsc
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_X86_GENERIC) || defined(CONFIG_X86_TSC)
id|rdtscll
c_func
(paren
id|ret
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_int
r_int
id|cpu_khz
suffix:semicolon
macro_line|#endif
eof
