macro_line|#ifndef _ASM_IA64_HARDIRQ_H
DECL|macro|_ASM_IA64_HARDIRQ_H
mdefine_line|#define _ASM_IA64_HARDIRQ_H
multiline_comment|/*&n; * Modified 1998-2002, 2004 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * No irq_cpustat_t for IA-64.  The data is held in the per-CPU data structure.&n; */
DECL|macro|__ARCH_IRQ_STAT
mdefine_line|#define __ARCH_IRQ_STAT&t;1
DECL|macro|softirq_pending
mdefine_line|#define softirq_pending(cpu)&t;&t;(cpu_data(cpu)-&gt;softirq_pending)
DECL|macro|syscall_count
mdefine_line|#define syscall_count(cpu)&t;&t;/* unused on IA-64 */
DECL|macro|ksoftirqd_task
mdefine_line|#define ksoftirqd_task(cpu)&t;&t;(cpu_data(cpu)-&gt;ksoftirqd)
DECL|macro|nmi_count
mdefine_line|#define nmi_count(cpu)&t;&t;&t;0
DECL|macro|local_softirq_pending
mdefine_line|#define local_softirq_pending()&t;&t;(local_cpu_data-&gt;softirq_pending)
DECL|macro|local_syscall_count
mdefine_line|#define local_syscall_count()&t;&t;/* unused on IA-64 */
DECL|macro|local_ksoftirqd_task
mdefine_line|#define local_ksoftirqd_task()&t;&t;(local_cpu_data-&gt;ksoftirqd)
DECL|macro|local_nmi_count
mdefine_line|#define local_nmi_count()&t;&t;0
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption counter. The bitmask has the&n; * following meaning:&n; *&n; * - bits 0-7 are the preemption count (max preemption depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; * - bits 16-29 are the hardirq count (max # of hardirqs: 16384)&n; *&n; * - (bit 63 is the PREEMPT_ACTIVE flag---not currently implemented.)&n; *&n; * PREEMPT_MASK: 0x000000ff&n; * SOFTIRQ_MASK: 0x0000ff00&n; * HARDIRQ_MASK: 0x3fff0000&n; */
DECL|macro|PREEMPT_BITS
mdefine_line|#define PREEMPT_BITS&t;8
DECL|macro|SOFTIRQ_BITS
mdefine_line|#define SOFTIRQ_BITS&t;8
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;14
DECL|macro|PREEMPT_SHIFT
mdefine_line|#define PREEMPT_SHIFT&t;0
DECL|macro|SOFTIRQ_SHIFT
mdefine_line|#define SOFTIRQ_SHIFT&t;(PREEMPT_SHIFT + PREEMPT_BITS)
DECL|macro|HARDIRQ_SHIFT
mdefine_line|#define HARDIRQ_SHIFT&t;(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
multiline_comment|/*&n; * The hardirq mask has to be large enough to have space for potentially all IRQ sources&n; * in the system nesting on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
macro_line|#endif /* _ASM_IA64_HARDIRQ_H */
eof
