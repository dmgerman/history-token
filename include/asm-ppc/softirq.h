multiline_comment|/*&n; * BK Id: SCCS/s.softirq.h 1.5 05/17/01 18:14:25 cort&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_SOFTIRQ_H
DECL|macro|__ASM_SOFTIRQ_H
mdefine_line|#define __ASM_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;do { local_bh_count(smp_processor_id())++; barrier(); } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;do { barrier(); local_bh_count(smp_processor_id())--; } while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif&t;/* __ASM_SOFTIRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
