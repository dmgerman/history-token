multiline_comment|/*&n; *  include/asm-s390/softirq.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/softirq.h&quot;&n; */
macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable() &bslash;&n;&t;&t;do { preempt_count() += SOFTIRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable() &bslash;&n;&t;&t;do { barrier(); preempt_count() -= SOFTIRQ_OFFSET; } while (0)
r_extern
r_void
id|do_call_softirq
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__local_bh_enable();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!in_interrupt() &amp;&amp; softirq_pending(smp_processor_id()))&t;&bslash;&n;&t;&t;/* Use the async. stack for softirq */&t;&t;&t;&bslash;&n;&t;&t;do_call_softirq();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
