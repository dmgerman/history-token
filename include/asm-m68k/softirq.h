macro_line|#ifndef __M68K_SOFTIRQ_H
DECL|macro|__M68K_SOFTIRQ_H
mdefine_line|#define __M68K_SOFTIRQ_H
multiline_comment|/*&n; * Software interrupts.. no SMP here either.&n; */
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable() &bslash;&n;&t;&t;do { preempt_count() += SOFTIRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable() &bslash;&n;&t;&t;do { barrier(); preempt_count() -= SOFTIRQ_OFFSET; } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__local_bh_enable();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(!in_interrupt() &amp;&amp; softirq_pending(smp_processor_id()))) &bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_check_resched();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
eof
