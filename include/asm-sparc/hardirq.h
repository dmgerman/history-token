multiline_comment|/* hardirq.h: 32-bit Sparc hard IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998-2000 Anton Blanchard (anton@samba.org)&n; */
macro_line|#ifndef __SPARC_HARDIRQ_H
DECL|macro|__SPARC_HARDIRQ_H
mdefine_line|#define __SPARC_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
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
DECL|member|__unused_1
r_int
r_int
id|__unused_1
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|member|WAS__local_irq_count
r_int
r_int
id|WAS__local_irq_count
suffix:semicolon
macro_line|#else
DECL|member|__unused_on_SMP
r_int
r_int
id|__unused_on_SMP
suffix:semicolon
multiline_comment|/* DaveM says use brlock for SMP irq. KAO */
macro_line|#endif
DECL|member|WAS__local_bh_count
r_int
r_int
id|WAS__local_bh_count
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
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption&n; * counter. The bitmask has the following meaning:&n; *&n; * - bits 0-7 are the preemption count (max preemption depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; * - bits 16-23 are the hardirq count (max # of hardirqs: 256)&n; *&n; * - ( bit 26 is the PREEMPT_ACTIVE flag. )&n; *&n; * PREEMPT_MASK: 0x000000ff&n; * HARDIRQ_MASK: 0x0000ff00&n; * SOFTIRQ_MASK: 0x00ff0000&n; */
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
DECL|macro|__MASK
mdefine_line|#define __MASK(x)       ((1UL &lt;&lt; (x))-1)
DECL|macro|PREEMPT_MASK
mdefine_line|#define PREEMPT_MASK    (__MASK(PREEMPT_BITS) &lt;&lt; PREEMPT_SHIFT)
DECL|macro|HARDIRQ_MASK
mdefine_line|#define HARDIRQ_MASK    (__MASK(HARDIRQ_BITS) &lt;&lt; HARDIRQ_SHIFT)
DECL|macro|SOFTIRQ_MASK
mdefine_line|#define SOFTIRQ_MASK    (__MASK(SOFTIRQ_BITS) &lt;&lt; SOFTIRQ_SHIFT)
DECL|macro|hardirq_count
mdefine_line|#define hardirq_count() (preempt_count() &amp; HARDIRQ_MASK)
DECL|macro|softirq_count
mdefine_line|#define softirq_count() (preempt_count() &amp; SOFTIRQ_MASK)
DECL|macro|irq_count
mdefine_line|#define irq_count()     (preempt_count() &amp; (HARDIRQ_MASK | SOFTIRQ_MASK))
DECL|macro|PREEMPT_OFFSET
mdefine_line|#define PREEMPT_OFFSET  (1UL &lt;&lt; PREEMPT_SHIFT)
DECL|macro|SOFTIRQ_OFFSET
mdefine_line|#define SOFTIRQ_OFFSET  (1UL &lt;&lt; SOFTIRQ_SHIFT)
DECL|macro|HARDIRQ_OFFSET
mdefine_line|#define HARDIRQ_OFFSET  (1UL &lt;&lt; HARDIRQ_SHIFT)
multiline_comment|/*&n; * The hardirq mask has to be large enough to have&n; * space for potentially all IRQ sources in the system&n; * nesting on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
multiline_comment|/*&n; * Are we doing bottom half or hardware interrupt processing?&n; * Are we in a softirq context? Interrupt context?&n; */
DECL|macro|in_irq
mdefine_line|#define in_irq()                (hardirq_count())
DECL|macro|in_softirq
mdefine_line|#define in_softirq()            (softirq_count())
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()          (irq_count())
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock()       (!in_interrupt())
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock()       do { } while (0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|irq_enter
mdefine_line|#define irq_enter()             (preempt_count() += HARDIRQ_OFFSET)
macro_line|#if CONFIG_PREEMPT
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET (HARDIRQ_OFFSET-1)
macro_line|#else
DECL|macro|IRQ_EXIT_OFFSET
macro_line|# define IRQ_EXIT_OFFSET HARDIRQ_OFFSET
macro_line|#endif
DECL|macro|irq_exit
mdefine_line|#define irq_exit()                                                      &bslash;&n;do {                                                                    &bslash;&n;                preempt_count() -= IRQ_EXIT_OFFSET;                     &bslash;&n;                if (!in_interrupt() &amp;&amp; softirq_pending(smp_processor_id())) &bslash;&n;                        do_softirq();                                   &bslash;&n;                preempt_enable_no_resched();                            &bslash;&n;} while (0)
macro_line|#else
multiline_comment|/* Note that local_irq_count() is replaced by sparc64 specific version for SMP */
multiline_comment|/* XXX This is likely to be broken by the above preempt-based IRQs */
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;br_read_lock(BR_GLOBALIRQ_LOCK)
DECL|macro|local_irq_count
macro_line|#undef local_irq_count
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;(__brlock_array[cpu][BR_GLOBALIRQ_LOCK])
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;&t;br_read_unlock(BR_GLOBALIRQ_LOCK)
macro_line|#endif
macro_line|#ifndef CONFIG_SMP
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier()
macro_line|#else /* (CONFIG_SMP) */
DECL|function|irqs_running
r_static
id|__inline__
r_int
id|irqs_running
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|local_irq_count
c_func
(paren
id|cpu_logical_map
c_func
(paren
id|i
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
r_char
id|global_irq_holder
suffix:semicolon
DECL|function|release_irqlock
r_static
r_inline
r_void
id|release_irqlock
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/* if we didn&squot;t own the irq lock, just ignore... */
r_if
c_cond
(paren
id|global_irq_holder
op_eq
(paren
r_int
r_char
)paren
id|cpu
)paren
(brace
id|global_irq_holder
op_assign
id|NO_PROC_ID
suffix:semicolon
id|br_write_unlock
c_func
(paren
id|BR_GLOBALIRQ_LOCK
)paren
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_static
r_inline
r_int
id|hardirq_trylock
c_func
(paren
r_int
id|cpu
)paren
(brace
id|spinlock_t
op_star
id|lock
op_assign
op_amp
id|__br_write_locks
(braket
id|BR_GLOBALIRQ_LOCK
)braket
dot
id|lock
suffix:semicolon
r_return
(paren
op_logical_neg
id|local_irq_count
c_func
(paren
id|cpu
)paren
op_logical_and
op_logical_neg
id|spin_is_locked
c_func
(paren
id|lock
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
singleline_comment|// extern void show_stack(unsigned long * esp);
macro_line|#endif /* __SPARC_HARDIRQ_H */
eof
