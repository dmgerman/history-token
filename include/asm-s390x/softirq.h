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
DECL|macro|__cpu_bh_enable
mdefine_line|#define __cpu_bh_enable(cpu) &bslash;&n;&t;&t;do { barrier(); local_bh_count(cpu)--; } while (0)
DECL|macro|cpu_bh_disable
mdefine_line|#define cpu_bh_disable(cpu) &bslash;&n;&t;&t;do { local_bh_count(cpu)++; barrier(); } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()      cpu_bh_disable(smp_processor_id())
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()     __cpu_bh_enable(smp_processor_id())
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;          &t;        &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;                &bslash;&n;&t;unsigned int *ptr = &amp;local_bh_count(smp_processor_id());        &bslash;&n;&t;barrier();                                                      &bslash;&n;&t;if (!--*ptr)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (softirq_pending(smp_processor_id()))&t;&t;&bslash;&n;&t;&t;&t;do_softirq();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
