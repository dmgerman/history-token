multiline_comment|/*&n; *  include/asm-s390/softirq.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/softirq.h&quot;&n; */
macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#ifndef __LINUX_SMP_H
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_bh_count(smp_processor_id())++;&t;&bslash;&n;&t;barrier();&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;barrier();&t;&t;&t;&t;&bslash;&n;&t;local_bh_count(smp_processor_id())--;&t;&bslash;&n;} while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!--local_bh_count(smp_processor_id())&t;&bslash;&n;&t;    &amp;&amp; softirq_pending(smp_processor_id())) {&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&bslash;&n;&t;&t;__sti();&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__cpu_raise_softirq
mdefine_line|#define __cpu_raise_softirq(cpu, nr) (softirq_pending(cpu) |= (1&lt;&lt;nr))
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
