macro_line|#ifndef _ASM_IA64_HARDIRQ_H
DECL|macro|_ASM_IA64_HARDIRQ_H
mdefine_line|#define _ASM_IA64_HARDIRQ_H
multiline_comment|/*&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * No irq_cpustat_t for IA-64.  The data is held in the per-CPU data structure.&n; */
DECL|macro|softirq_pending
mdefine_line|#define softirq_pending(cpu)&t;&t;(cpu_data(cpu)-&gt;softirq_pending)
DECL|macro|ksoftirqd_task
mdefine_line|#define ksoftirqd_task(cpu)&t;&t;(cpu_data(cpu)-&gt;ksoftirqd)
DECL|macro|irq_count
mdefine_line|#define irq_count(cpu)&t;&t;&t;(cpu_data(cpu)-&gt;irq_stat.f.irq_count)
DECL|macro|bh_count
mdefine_line|#define bh_count(cpu)&t;&t;&t;(cpu_data(cpu)-&gt;irq_stat.f.bh_count)
DECL|macro|syscall_count
mdefine_line|#define syscall_count(cpu)&t;&t;/* unused on IA-64 */
DECL|macro|nmi_count
mdefine_line|#define nmi_count(cpu)&t;&t;&t;0
DECL|macro|local_softirq_pending
mdefine_line|#define local_softirq_pending()&t;&t;(local_cpu_data-&gt;softirq_pending)
DECL|macro|local_ksoftirqd_task
mdefine_line|#define local_ksoftirqd_task()&t;&t;(local_cpu_data-&gt;ksoftirqd)
DECL|macro|really_local_irq_count
mdefine_line|#define really_local_irq_count()&t;(local_cpu_data-&gt;irq_stat.f.irq_count)&t;/* XXX fix me */
DECL|macro|really_local_bh_count
mdefine_line|#define really_local_bh_count()&t;&t;(local_cpu_data-&gt;irq_stat.f.bh_count)&t;/* XXX fix me */
DECL|macro|local_syscall_count
mdefine_line|#define local_syscall_count()&t;&t;/* unused on IA-64 */
DECL|macro|local_nmi_count
mdefine_line|#define local_nmi_count()&t;&t;0
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half or hardware interrupt&n; * processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()&t;&t;&t;(local_cpu_data-&gt;irq_stat.irq_and_bh_counts != 0)
DECL|macro|in_irq
mdefine_line|#define in_irq()&t;&t;&t;(local_cpu_data-&gt;irq_stat.f.irq_count != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|local_hardirq_trylock
macro_line|# define local_hardirq_trylock()&t;(really_local_irq_count() == 0)
DECL|macro|local_hardirq_endlock
macro_line|# define local_hardirq_endlock()&t;do { } while (0)
DECL|macro|local_irq_enter
macro_line|# define local_irq_enter(irq)&t;&t;(really_local_irq_count()++)
DECL|macro|local_irq_exit
macro_line|# define local_irq_exit(irq)&t;&t;(really_local_irq_count()--)
DECL|macro|synchronize_irq
macro_line|# define synchronize_irq()&t;&t;barrier()
macro_line|#else
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_extern
r_int
r_int
id|global_irq_holder
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|global_irq_lock
suffix:semicolon
r_static
r_inline
r_int
DECL|function|irqs_running
id|irqs_running
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|irq_count
c_func
(paren
id|i
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|release_irqlock
id|release_irqlock
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/* if we didn&squot;t own the irq lock, just ignore.. */
r_if
c_cond
(paren
id|global_irq_holder
op_eq
id|cpu
)paren
(brace
id|global_irq_holder
op_assign
id|NO_PROC_ID
suffix:semicolon
id|smp_mb__before_clear_bit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* need barrier before releasing lock... */
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|local_irq_enter
id|local_irq_enter
(paren
r_int
id|irq
)paren
(brace
id|really_local_irq_count
c_func
(paren
)paren
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
)brace
r_static
r_inline
r_void
DECL|function|local_irq_exit
id|local_irq_exit
(paren
r_int
id|irq
)paren
(brace
id|really_local_irq_count
c_func
(paren
)paren
op_decrement
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|local_hardirq_trylock
id|local_hardirq_trylock
(paren
r_void
)paren
(brace
r_return
op_logical_neg
id|really_local_irq_count
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
DECL|macro|local_hardirq_endlock
mdefine_line|#define local_hardirq_endlock()&t;&t;do { } while (0)
r_extern
r_void
id|synchronize_irq
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* _ASM_IA64_HARDIRQ_H */
eof
