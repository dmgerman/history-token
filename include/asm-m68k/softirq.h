macro_line|#ifndef __M68K_SOFTIRQ_H
DECL|macro|__M68K_SOFTIRQ_H
mdefine_line|#define __M68K_SOFTIRQ_H
multiline_comment|/*&n; * Software interrupts.. no SMP here either.&n; */
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|cpu_bh_disable
mdefine_line|#define cpu_bh_disable(cpu)&t;do { local_bh_count(cpu)++; barrier(); } while (0)
DECL|macro|cpu_bh_enable
mdefine_line|#define cpu_bh_enable(cpu)&t;do { barrier(); local_bh_count(cpu)--; } while (0)
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;cpu_bh_disable(smp_processor_id())
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;cpu_bh_enable(smp_processor_id())
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif
eof
