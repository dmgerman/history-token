macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable() &bslash;&n;&t;&t;do { preempt_count() += IRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable() &bslash;&n;&t;&t;do { barrier(); preempt_count() -= IRQ_OFFSET; } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable() &bslash;&n;do { &bslash;&n;&t;if (unlikely((preempt_count() == IRQ_OFFSET) &amp;&amp; &bslash;&n;&t;&t;     softirq_pending(smp_processor_id()))) { &bslash;&n;&t;&t;__local_bh_enable(); &bslash;&n;&t;&t;do_softirq(); &bslash;&n;&t;&t;preempt_check_resched(); &bslash;&n;&t;} else { &bslash;&n;&t;&t;__local_bh_enable(); &bslash;&n;&t;&t;preempt_check_resched(); &bslash;&n;&t;} &bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() in_interrupt()
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
eof
