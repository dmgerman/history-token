macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()      (local_bh_count(smp_processor_id())++)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()       (local_bh_count(smp_processor_id())--)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
