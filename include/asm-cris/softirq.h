macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()                      &bslash;&n;do {                                            &bslash;&n;        local_bh_count(smp_processor_id())++;   &bslash;&n;        barrier();                              &bslash;&n;} while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()                     &bslash;&n;do {                                            &bslash;&n;        barrier();                              &bslash;&n;        local_bh_count(smp_processor_id())--;   &bslash;&n;} while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()                               &bslash;&n;do {                                                    &bslash;&n;        if (!--local_bh_count(smp_processor_id())       &bslash;&n;            &amp;&amp; softirq_pending(smp_processor_id())) {   &bslash;&n;                do_softirq();                           &bslash;&n;                __sti();                                &bslash;&n;        }                                               &bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
