macro_line|#ifndef __ASM_SH_SOFTIRQ_H
DECL|macro|__ASM_SH_SOFTIRQ_H
mdefine_line|#define __ASM_SH_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_bh_count(smp_processor_id())++;&t;&bslash;&n;&t;barrier();&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;barrier();&t;&t;&t;&t;&bslash;&n;&t;local_bh_count(smp_processor_id())--;&t;&bslash;&n;} while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!--local_bh_count(smp_processor_id())&t;&bslash;&n;&t;    &amp;&amp; softirq_pending(smp_processor_id())) {&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&bslash;&n;&t;&t;__sti();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__cpu_raise_softirq
mdefine_line|#define __cpu_raise_softirq(cpu, nr) set_bit((nr), &amp;softirq_pending(cpu));
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif /* __ASM_SH_SOFTIRQ_H */
eof
