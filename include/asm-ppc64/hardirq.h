macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
multiline_comment|/*&n; * Use a brlock for the global irq lock, based on sparc64.&n; * Anton Blanchard &lt;anton@au1.ibm.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|member|__local_irq_count
r_int
r_int
id|__local_irq_count
suffix:semicolon
macro_line|#else
DECL|member|__unused_on_SMP
r_int
r_int
id|__unused_on_SMP
suffix:semicolon
multiline_comment|/* We use brlocks on SMP */
macro_line|#endif
DECL|member|__local_bh_count
r_int
r_int
id|__local_bh_count
suffix:semicolon
DECL|member|__syscall_count
r_int
r_int
id|__syscall_count
suffix:semicolon
DECL|member|__unused
r_int
r_int
id|__unused
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
multiline_comment|/* Note that local_irq_count() is replaced by ppc64 specific version for SMP */
macro_line|#ifndef CONFIG_SMP
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu)&t;&t;(local_irq_count(cpu)++)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu)&t;&t;(local_irq_count(cpu)--)
macro_line|#else
DECL|macro|local_irq_count
macro_line|#undef local_irq_count
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;(__brlock_array[cpu][BR_GLOBALIRQ_LOCK])
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu)&t;&t;br_read_lock(BR_GLOBALIRQ_LOCK)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu)&t;&t;br_read_unlock(BR_GLOBALIRQ_LOCK)
macro_line|#endif
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() ({ int __cpu = smp_processor_id(); &bslash;&n;&t;(local_irq_count(__cpu) + local_bh_count(__cpu) != 0); })
multiline_comment|/* This tests only the local processors hw IRQ context disposition.  */
DECL|macro|in_irq
mdefine_line|#define in_irq() (local_irq_count(smp_processor_id()) != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count(cpu) == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier()
DECL|macro|release_irqlock
mdefine_line|#define release_irqlock(cpu)&t;do { } while (0)
macro_line|#else /* CONFIG_SMP */
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
DECL|function|hardirq_trylock
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
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)    do { (void)(cpu); } while (0)
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
