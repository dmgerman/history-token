macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|__cpu_bh_enable
mdefine_line|#define __cpu_bh_enable(cpu) &bslash;&n;&t;&t;do { barrier(); local_bh_count(cpu)--; } while (0)
DECL|macro|cpu_bh_disable
mdefine_line|#define cpu_bh_disable(cpu) &bslash;&n;&t;&t;do { local_bh_count(cpu)++; barrier(); } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;cpu_bh_disable(smp_processor_id())
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;__cpu_bh_enable(smp_processor_id())
DECL|macro|__cpu_raise_softirq
mdefine_line|#define __cpu_raise_softirq(cpu,nr) set_bit((nr), &amp;softirq_pending(cpu))
DECL|macro|in_softirq
mdefine_line|#define in_softirq()&t;&t;(local_bh_count(smp_processor_id()) != 0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int *ptr = &amp;local_bh_count(smp_processor_id());&t;&bslash;&n;&t;if (!--*ptr &amp;&amp; ptr[-2])&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__(&quot;bl%? __do_softirq&quot;: : : &quot;lr&quot;);/* out of line */&bslash;&n;} while (0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
