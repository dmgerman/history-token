multiline_comment|/* hardirq.h: 32-bit Sparc hard IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998-2000 Anton Blanchard (anton@samba.org)&n; */
macro_line|#ifndef __SPARC_HARDIRQ_H
DECL|macro|__SPARC_HARDIRQ_H
mdefine_line|#define __SPARC_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
multiline_comment|/* entry.S is sensitive to the offsets of these fields */
multiline_comment|/* XXX P3 Is it? */
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption&n; * counter. The bitmask has the following meaning:&n; *&n; * - bits 0-7 are the preemption count (max preemption depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; * - bits 16-23 are the hardirq count (max # of hardirqs: 256)&n; *&n; * - ( bit 26 is the PREEMPT_ACTIVE flag. )&n; *&n; * PREEMPT_MASK: 0x000000ff&n; * SOFTIRQ_MASK: 0x0000ff00&n; * HARDIRQ_MASK: 0x00ff0000&n; */
DECL|macro|PREEMPT_BITS
mdefine_line|#define PREEMPT_BITS    8
DECL|macro|SOFTIRQ_BITS
mdefine_line|#define SOFTIRQ_BITS    8
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS    8
DECL|macro|PREEMPT_SHIFT
mdefine_line|#define PREEMPT_SHIFT   0
DECL|macro|SOFTIRQ_SHIFT
mdefine_line|#define SOFTIRQ_SHIFT   (PREEMPT_SHIFT + PREEMPT_BITS)
DECL|macro|HARDIRQ_SHIFT
mdefine_line|#define HARDIRQ_SHIFT   (SOFTIRQ_SHIFT + SOFTIRQ_BITS)
DECL|macro|irq_enter
mdefine_line|#define irq_enter()             (preempt_count() += HARDIRQ_OFFSET)
DECL|macro|irq_exit
mdefine_line|#define irq_exit()                                                      &bslash;&n;do {                                                                    &bslash;&n;                preempt_count() -= IRQ_EXIT_OFFSET;                     &bslash;&n;                if (!in_interrupt() &amp;&amp; softirq_pending(smp_processor_id())) &bslash;&n;                        do_softirq();                                   &bslash;&n;                preempt_enable_no_resched();                            &bslash;&n;} while (0)
macro_line|#endif /* __SPARC_HARDIRQ_H */
eof
