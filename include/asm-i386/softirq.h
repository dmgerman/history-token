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
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
multiline_comment|/*&n; * NOTE: this assembly code assumes:&n; *&n; *    (char *)&amp;local_bh_count - 8 == (char *)&amp;softirq_pending&n; *&n; * If you change the offsets in irq_stat then you have to&n; * update this code as well.&n; */
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int *ptr = &amp;local_bh_count(smp_processor_id());&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;barrier();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!--*ptr)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;cmpl $0, -8(%0);&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;jnz 2f;&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;1:;&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LOCK_SECTION_START(&quot;&quot;)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;2: pushl %%eax; pushl %%ecx; pushl %%edx;&quot;&t;&bslash;&n;&t;&t;&t;&quot;call %c1;&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;popl %%edx; popl %%ecx; popl %%eax;&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;jmp 1b;&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;LOCK_SECTION_END&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: /* no output */&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (ptr), &quot;i&quot; (do_softirq)&t;&t;&t;&t;&bslash;&n;&t;&t;/* no registers clobbered */ );&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
