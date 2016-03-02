macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable() &bslash;&n;&t;&t;do { preempt_count() += IRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable() &bslash;&n;&t;&t;do { barrier(); preempt_count() -= IRQ_OFFSET; } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (unlikely((preempt_count() == IRQ_OFFSET) &amp;&amp;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;softirq_pending(smp_processor_id()))) { &bslash;&n;&t;&t;__local_bh_enable();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_check_resched();&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__local_bh_enable();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_check_resched();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() in_interrupt()
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
