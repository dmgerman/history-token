multiline_comment|/* hardirq.h: 64-bit Sparc hard IRQ support.&n; *&n; * Copyright (C) 1997, 1998 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_HARDIRQ_H
DECL|macro|__SPARC64_HARDIRQ_H
mdefine_line|#define __SPARC64_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/* entry.S is sensitive to the offsets of these fields */
multiline_comment|/* rtrap.S is sensitive to the size of this structure */
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|member|__unused_1
r_int
r_int
id|__unused_1
suffix:semicolon
macro_line|#warning DaveM kill SMP irq brlock... no longer needed...
DECL|member|__unused_2
r_int
r_int
id|__unused_2
suffix:semicolon
DECL|member|__unused_3
r_int
r_int
id|__unused_3
suffix:semicolon
DECL|member|__syscall_count
r_int
r_int
id|__syscall_count
suffix:semicolon
DECL|member|__ksoftirqd_task
r_struct
id|task_struct
op_star
id|__ksoftirqd_task
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|IRQ_OFFSET
mdefine_line|#define IRQ_OFFSET 64
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() &bslash;&n;&t;((preempt_count() &amp; ~PREEMPT_ACTIVE) &gt;= IRQ_OFFSET)
DECL|macro|in_irq
mdefine_line|#define in_irq in_interrupt
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock()&t;(!in_interrupt())
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock()&t;do { } while (0)
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;(preempt_count() += IRQ_OFFSET)
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;&t;(preempt_count() -= IRQ_OFFSET)
macro_line|#ifndef CONFIG_SMP
DECL|macro|synchronize_irq
macro_line|# define synchronize_irq()&t;barrier()
macro_line|#else
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* !(__SPARC64_HARDIRQ_H) */
eof
