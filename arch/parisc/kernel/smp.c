multiline_comment|/*&n;** SMP Support&n;**&n;** Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n;** Copyright (C) 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n;** Copyright (C) 2001 Grant Grundler &lt;grundler@parisc-linux.org&gt;&n;** &n;** Lots of stuff stolen from arch/alpha/kernel/smp.c&n;** ...and then parisc stole from arch/ia64/kernel/smp.c. Thanks David! :^)&n;**&n;** Thanks to John Curry and Ullas Ponnadi. I learned alot from their work.&n;** -grant (1/12/2001)&n;**&n;**&t;This program is free software; you can redistribute it and/or modify&n;**&t;it under the terms of the GNU General Public License as published by&n;**      the Free Software Foundation; either version 2 of the License, or&n;**      (at your option) any later version.&n;*/
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
DECL|macro|ENTRY_SYS_CPUS
macro_line|#undef ENTRY_SYS_CPUS&t;/* syscall support for iCOD-like functionality */
macro_line|#include &lt;linux/autoconf.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;&t;/* for flush_tlb_all() proto/macro */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;&t;&t;/* for CPU_IRQ_REGION and friends */
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|macro|kDEBUG
mdefine_line|#define kDEBUG 0
DECL|variable|pa_dbit_lock
id|spinlock_t
id|pa_dbit_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|smp_lock
id|spinlock_t
id|smp_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|smp_init_current_idle_task
r_volatile
r_struct
id|task_struct
op_star
id|smp_init_current_idle_task
suffix:semicolon
DECL|variable|smp_commenced
r_static
r_volatile
r_int
id|smp_commenced
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set when the idlers are all forked */
DECL|variable|cpu_now_booting
r_static
r_volatile
r_int
id|cpu_now_booting
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* track which CPU is booting */
DECL|variable|cpu_online_map
id|cpumask_t
id|cpu_online_map
op_assign
id|CPU_MASK_NONE
suffix:semicolon
multiline_comment|/* Bitmap of online CPUs */
DECL|macro|IS_LOGGED_IN
mdefine_line|#define IS_LOGGED_IN(cpunum) (cpu_isset(cpunum, cpu_online_map))
DECL|variable|cpu_online_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
DECL|variable|smp_num_cpus
r_int
id|smp_num_cpus
op_assign
l_int|1
suffix:semicolon
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
op_assign
l_int|0
suffix:semicolon
DECL|variable|cache_decay_ticks
r_int
r_int
id|cache_decay_ticks
suffix:semicolon
DECL|variable|max_cpus
r_static
r_int
id|max_cpus
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Command line */
DECL|variable|cpu_present_mask
id|cpumask_t
id|cpu_present_mask
suffix:semicolon
DECL|variable|cpu_present_mask
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_present_mask
)paren
suffix:semicolon
DECL|struct|smp_call_struct
r_struct
id|smp_call_struct
(brace
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|wait
r_int
id|wait
suffix:semicolon
DECL|member|unstarted_count
id|atomic_t
id|unstarted_count
suffix:semicolon
DECL|member|unfinished_count
id|atomic_t
id|unfinished_count
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|smp_call_function_data
r_static
r_volatile
r_struct
id|smp_call_struct
op_star
id|smp_call_function_data
suffix:semicolon
DECL|enum|ipi_message_type
r_enum
id|ipi_message_type
(brace
DECL|enumerator|IPI_NOP
id|IPI_NOP
op_assign
l_int|0
comma
DECL|enumerator|IPI_RESCHEDULE
id|IPI_RESCHEDULE
op_assign
l_int|1
comma
DECL|enumerator|IPI_CALL_FUNC
id|IPI_CALL_FUNC
comma
DECL|enumerator|IPI_CPU_START
id|IPI_CPU_START
comma
DECL|enumerator|IPI_CPU_STOP
id|IPI_CPU_STOP
comma
DECL|enumerator|IPI_CPU_TEST
id|IPI_CPU_TEST
)brace
suffix:semicolon
multiline_comment|/********** SMP inter processor interrupt and communication routines */
DECL|macro|PER_CPU_IRQ_REGION
macro_line|#undef PER_CPU_IRQ_REGION
macro_line|#ifdef PER_CPU_IRQ_REGION
multiline_comment|/* XXX REVISIT Ignore for now.&n;**    *May* need this &quot;hook&quot; to register IPI handler&n;**    once we have perCPU ExtIntr switch tables.&n;*/
r_static
r_void
DECL|function|ipi_init
id|ipi_init
c_func
(paren
r_int
id|cpuid
)paren
(brace
multiline_comment|/* If CPU is present ... */
macro_line|#ifdef ENTRY_SYS_CPUS
multiline_comment|/* *and* running (not stopped) ... */
macro_line|#error iCOD support wants state checked here.
macro_line|#endif
macro_line|#error verify IRQ_OFFSET(IPI_IRQ) is ipi_interrupt() in new IRQ region
r_if
c_cond
(paren
id|IS_LOGGED_IN
c_func
(paren
id|cpuid
)paren
)paren
(brace
id|switch_to_idle_task
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;** Yoink this CPU from the runnable list... &n;**&n;*/
r_static
r_void
DECL|function|halt_processor
id|halt_processor
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef ENTRY_SYS_CPUS
macro_line|#error halt_processor() needs rework
multiline_comment|/*&n;** o migrate I/O interrupts off this CPU.&n;** o leave IPI enabled - __cli() will disable IPI.&n;** o leave CPU in online map - just change the state&n;*/
id|cpu_data
(braket
id|this_cpu
)braket
dot
id|state
op_assign
id|STATE_STOPPED
suffix:semicolon
id|mark_bh
c_func
(paren
id|IPI_BH
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* REVISIT : redirect I/O Interrupts to another CPU? */
multiline_comment|/* REVISIT : does PM *know* this CPU isn&squot;t available? */
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_online_map
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
macro_line|#endif
)brace
id|irqreturn_t
DECL|function|ipi_interrupt
id|ipi_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|this_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|cpuinfo_parisc
op_star
id|p
op_assign
op_amp
id|cpu_data
(braket
id|this_cpu
)braket
suffix:semicolon
r_int
r_int
id|ops
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Count this now; we may make a call that never returns. */
id|p-&gt;ipi_count
op_increment
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Order interrupt and bit testing. */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|p-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|ops
op_assign
id|p-&gt;pending_ipi
suffix:semicolon
id|p-&gt;pending_ipi
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|p-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Order bit clearing and data access. */
r_if
c_cond
(paren
op_logical_neg
id|ops
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
id|ops
)paren
(brace
r_int
r_int
id|which
op_assign
id|ffz
c_func
(paren
op_complement
id|ops
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
id|IPI_RESCHEDULE
suffix:colon
macro_line|#if (kDEBUG&gt;=100)
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU%d IPI_RESCHEDULE&bslash;n&quot;
comma
id|this_cpu
)paren
suffix:semicolon
macro_line|#endif /* kDEBUG */
id|ops
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|IPI_RESCHEDULE
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Reschedule callback.  Everything to be&n;&t;&t;&t;&t; * done is done by the interrupt return path.&n;&t;&t;&t;&t; */
r_break
suffix:semicolon
r_case
id|IPI_CALL_FUNC
suffix:colon
macro_line|#if (kDEBUG&gt;=100)
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU%d IPI_CALL_FUNC&bslash;n&quot;
comma
id|this_cpu
)paren
suffix:semicolon
macro_line|#endif /* kDEBUG */
id|ops
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|IPI_CALL_FUNC
)paren
suffix:semicolon
(brace
r_volatile
r_struct
id|smp_call_struct
op_star
id|data
suffix:semicolon
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
suffix:semicolon
r_void
op_star
id|info
suffix:semicolon
r_int
id|wait
suffix:semicolon
id|data
op_assign
id|smp_call_function_data
suffix:semicolon
id|func
op_assign
id|data-&gt;func
suffix:semicolon
id|info
op_assign
id|data-&gt;info
suffix:semicolon
id|wait
op_assign
id|data-&gt;wait
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|data-&gt;unstarted_count
)paren
suffix:semicolon
multiline_comment|/* At this point, *data can&squot;t&n;&t;&t;&t;&t;&t; * be relied upon.&n;&t;&t;&t;&t;&t; */
(paren
op_star
id|func
)paren
(paren
id|info
)paren
suffix:semicolon
multiline_comment|/* Notify the sending CPU that the&n;&t;&t;&t;&t;&t; * task is done.&n;&t;&t;&t;&t;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|atomic_dec
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|data-&gt;unfinished_count
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IPI_CPU_START
suffix:colon
macro_line|#if (kDEBUG&gt;=100)
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU%d IPI_CPU_START&bslash;n&quot;
comma
id|this_cpu
)paren
suffix:semicolon
macro_line|#endif /* kDEBUG */
id|ops
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|IPI_CPU_START
)paren
suffix:semicolon
macro_line|#ifdef ENTRY_SYS_CPUS
id|p-&gt;state
op_assign
id|STATE_RUNNING
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|IPI_CPU_STOP
suffix:colon
macro_line|#if (kDEBUG&gt;=100)
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU%d IPI_CPU_STOP&bslash;n&quot;
comma
id|this_cpu
)paren
suffix:semicolon
macro_line|#endif /* kDEBUG */
id|ops
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|IPI_CPU_STOP
)paren
suffix:semicolon
macro_line|#ifdef ENTRY_SYS_CPUS
macro_line|#else
id|halt_processor
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|IPI_CPU_TEST
suffix:colon
macro_line|#if (kDEBUG&gt;=100)
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU%d is alive!&bslash;n&quot;
comma
id|this_cpu
)paren
suffix:semicolon
macro_line|#endif /* kDEBUG */
id|ops
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|IPI_CPU_TEST
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Unknown IPI num on CPU%d: %lu&bslash;n&quot;
comma
id|this_cpu
comma
id|which
)paren
suffix:semicolon
id|ops
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|which
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
multiline_comment|/* Switch */
)brace
multiline_comment|/* while (ops) */
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ipi_send
id|ipi_send
c_func
(paren
r_int
id|cpu
comma
r_enum
id|ipi_message_type
id|op
)paren
(brace
r_struct
id|cpuinfo_parisc
op_star
id|p
op_assign
op_amp
id|cpu_data
(braket
id|cpu
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|p-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
id|p-&gt;pending_ipi
op_or_assign
l_int|1
op_lshift
id|op
suffix:semicolon
id|__raw_writel
c_func
(paren
id|IRQ_OFFSET
c_func
(paren
id|IPI_IRQ
)paren
comma
id|cpu_data
(braket
id|cpu
)braket
dot
id|hpa
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|p-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|send_IPI_single
id|send_IPI_single
c_func
(paren
r_int
id|dest_cpu
comma
r_enum
id|ipi_message_type
id|op
)paren
(brace
r_if
c_cond
(paren
id|dest_cpu
op_eq
id|NO_PROC_ID
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ipi_send
c_func
(paren
id|dest_cpu
comma
id|op
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|send_IPI_allbutself
id|send_IPI_allbutself
c_func
(paren
r_enum
id|ipi_message_type
id|op
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
(brace
r_if
c_cond
(paren
id|i
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
id|send_IPI_single
c_func
(paren
id|i
comma
id|op
)paren
suffix:semicolon
)brace
)brace
r_inline
r_void
DECL|function|smp_send_stop
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
id|send_IPI_allbutself
c_func
(paren
id|IPI_CPU_STOP
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|smp_send_start
id|smp_send_start
c_func
(paren
r_void
)paren
(brace
id|send_IPI_allbutself
c_func
(paren
id|IPI_CPU_START
)paren
suffix:semicolon
)brace
r_void
DECL|function|smp_send_reschedule
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
id|send_IPI_single
c_func
(paren
id|cpu
comma
id|IPI_RESCHEDULE
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * Run a function on all other CPUs.&n; *  &lt;func&gt;&t;The function to run. This must be fast and non-blocking.&n; *  &lt;info&gt;&t;An arbitrary pointer to pass to the function.&n; *  &lt;retry&gt;&t;If true, keep retrying until ready.&n; *  &lt;wait&gt;&t;If true, wait until function has completed on other CPUs.&n; *  [RETURNS]   0 on success, else a negative status code.&n; *&n; * Does not return until remote CPUs are nearly ready to execute &lt;func&gt;&n; * or have executed.&n; */
r_int
DECL|function|smp_call_function
id|smp_call_function
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|retry
comma
r_int
id|wait
)paren
(brace
r_struct
id|smp_call_struct
id|data
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
r_static
id|spinlock_t
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|data.func
op_assign
id|func
suffix:semicolon
id|data.info
op_assign
id|info
suffix:semicolon
id|data.wait
op_assign
id|wait
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.unstarted_count
comma
id|smp_num_cpus
op_minus
l_int|1
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.unfinished_count
comma
id|smp_num_cpus
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retry
)paren
(brace
id|spin_lock
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|smp_call_function_data
op_ne
l_int|0
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_call_function_data
)paren
(brace
id|spin_unlock
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|smp_call_function_data
op_assign
op_amp
id|data
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|lock
)paren
suffix:semicolon
multiline_comment|/*  Send a message to all other CPUs and wait for them to respond  */
id|send_IPI_allbutself
c_func
(paren
id|IPI_CALL_FUNC
)paren
suffix:semicolon
multiline_comment|/*  Wait for response  */
id|timeout
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
r_while
c_loop
(paren
(paren
id|atomic_read
(paren
op_amp
id|data.unstarted_count
)paren
OG
l_int|0
)paren
op_logical_and
id|time_before
(paren
id|jiffies
comma
id|timeout
)paren
)paren
id|barrier
(paren
)paren
suffix:semicolon
multiline_comment|/* We either got one or timed out. Release the lock */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|smp_call_function_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
id|data.unstarted_count
)paren
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;SMP CALL FUNCTION TIMED OUT! (cpu=%d)&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
r_while
c_loop
(paren
id|wait
op_logical_and
id|atomic_read
(paren
op_amp
id|data.unfinished_count
)paren
OG
l_int|0
)paren
id|barrier
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Setup routine for controlling SMP activation&n; *&n; *&t;Command-line option of &quot;nosmp&quot; or &quot;maxcpus=0&quot; will disable SMP&n; *&t;activation entirely (the MPS table probe still happens, though).&n; *&n; *&t;Command-line option of &quot;maxcpus=&lt;NUM&gt;&quot;, where &lt;NUM&gt; is an integer&n; *&t;greater than 0, limits the maximum number of CPUs activated in&n; *&t;SMP mode to &lt;NUM&gt;.&n; */
DECL|function|nosmp
r_static
r_int
id|__init
id|nosmp
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|max_cpus
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nosmp&quot;
comma
id|nosmp
)paren
suffix:semicolon
DECL|function|maxcpus
r_static
r_int
id|__init
id|maxcpus
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|max_cpus
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;maxcpus=&quot;
comma
id|maxcpus
)paren
suffix:semicolon
multiline_comment|/*&n; * Flush all other CPU&squot;s tlb and then mine.  Do this with on_each_cpu()&n; * as we want to ensure all TLB&squot;s flushed before proceeding.&n; */
r_extern
r_void
id|flush_tlb_all_local
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
DECL|function|smp_flush_tlb_all
id|smp_flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|on_each_cpu
c_func
(paren
(paren
r_void
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|flush_tlb_all_local
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|smp_do_timer
id|smp_do_timer
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|cpuinfo_parisc
op_star
id|data
op_assign
op_amp
id|cpu_data
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|data-&gt;prof_counter
)paren
(brace
id|data-&gt;prof_counter
op_assign
id|data-&gt;prof_multiplier
suffix:semicolon
id|update_process_times
c_func
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Called by secondaries to update state and initialize CPU registers.&n; */
r_static
r_void
id|__init
DECL|function|smp_cpu_init
id|smp_cpu_init
c_func
(paren
r_int
id|cpunum
)paren
(brace
r_extern
r_int
id|init_per_cpu
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* arch/parisc/kernel/setup.c */
r_extern
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* arch/parisc/kernel/irq.c */
multiline_comment|/* Set modes and Enable floating point coprocessor */
(paren
r_void
)paren
id|init_per_cpu
c_func
(paren
id|cpunum
)paren
suffix:semicolon
id|disable_sr_hashing
c_func
(paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Well, support 2.4 linux scheme as well. */
r_if
c_cond
(paren
id|cpu_test_and_set
c_func
(paren
id|cpunum
comma
id|cpu_online_map
)paren
)paren
(brace
r_extern
r_void
id|machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* arch/parisc.../process.c */
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;CPU#%d already initialized!&bslash;n&quot;
comma
id|cpunum
)paren
suffix:semicolon
id|machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialise the idle task for this CPU */
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|enter_lazy_tlb
c_func
(paren
op_amp
id|init_mm
comma
id|current
)paren
suffix:semicolon
id|init_IRQ
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure no IRQ&squot;s are enabled or pending */
)brace
multiline_comment|/*&n; * Slaves start using C here. Indirectly called from smp_slave_stext.&n; * Do what start_kernel() and main() do for boot strap processor (aka monarch)&n; */
DECL|function|smp_callin
r_void
id|__init
id|smp_callin
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* arch/parisc/kernel/process.c */
r_int
id|slave_id
op_assign
id|cpu_now_booting
suffix:semicolon
macro_line|#if 0
r_void
op_star
id|istack
suffix:semicolon
macro_line|#endif
id|smp_cpu_init
c_func
(paren
id|slave_id
)paren
suffix:semicolon
macro_line|#if 0&t;/* NOT WORKING YET - see entry.S */
id|istack
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|ISTACK_ORDER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|istack
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Failed to allocate interrupt stack for cpu %d&bslash;n&quot;
comma
id|slave_id
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|mtctl
c_func
(paren
id|istack
comma
l_int|31
)paren
suffix:semicolon
macro_line|#endif
id|flush_cache_all_local
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* start with known state */
id|flush_tlb_all_local
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Interrupts have been off until now */
multiline_comment|/* Slaves wait here until Big Poppa daddy say &quot;jump&quot; */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* PARANOID */
r_while
c_loop
(paren
op_logical_neg
id|smp_commenced
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* PARANOID */
id|cpu_idle
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Wait for timer to schedule some work */
multiline_comment|/* NOTREACHED */
id|panic
c_func
(paren
l_string|&quot;smp_callin() AAAAaaaaahhhh....&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create the idle task for a new Slave CPU.  DO NOT use kernel_thread()&n; * because that could end up calling schedule(). If it did, the new idle&n; * task could get scheduled before we had a chance to remove it from the&n; * run-queue...&n; */
DECL|function|fork_by_hand
r_static
r_struct
id|task_struct
op_star
id|fork_by_hand
c_func
(paren
r_void
)paren
(brace
r_struct
id|pt_regs
id|regs
suffix:semicolon
multiline_comment|/*&n;&t; * don&squot;t care about the regs settings since&n;&t; * we&squot;ll never reschedule the forked task.&n;&t; */
r_return
id|copy_process
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_IDLETASK
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Bring one cpu online.&n; */
DECL|function|smp_boot_one_cpu
r_static
r_int
id|__init
id|smp_boot_one_cpu
c_func
(paren
r_int
id|cpuid
comma
r_int
id|cpunum
)paren
(brace
r_struct
id|task_struct
op_star
id|idle
suffix:semicolon
r_int
id|timeout
suffix:semicolon
multiline_comment|/* &n;&t; * Create an idle task for this CPU.  Note the address wed* give &n;&t; * to kernel_thread is irrelevant -- it&squot;s going to start&n;&t; * where OS_BOOT_RENDEVZ vector in SAL says to start.  But&n;&t; * this gets all the other task-y sort of data structures set&n;&t; * up like we wish.   We need to pull the just created idle task &n;&t; * off the run queue and stuff it into the init_tasks[] array.  &n;&t; * Sheesh . . .&n;&t; */
id|idle
op_assign
id|fork_by_hand
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|idle
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;SMP: fork failed for CPU:%d&quot;
comma
id|cpuid
)paren
suffix:semicolon
id|wake_up_forked_process
c_func
(paren
id|idle
)paren
suffix:semicolon
id|init_idle
c_func
(paren
id|idle
comma
id|cpunum
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|idle
)paren
suffix:semicolon
id|idle-&gt;thread_info-&gt;cpu
op_assign
id|cpunum
suffix:semicolon
multiline_comment|/* Let _start know what logical CPU we&squot;re booting&n;&t;** (offset into init_tasks[],cpu_data[])&n;&t;*/
id|cpu_now_booting
op_assign
id|cpunum
suffix:semicolon
multiline_comment|/* &n;&t;** boot strap code needs to know the task address since&n;&t;** it also contains the process stack.&n;&t;*/
id|smp_init_current_idle_task
op_assign
id|idle
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;** This gets PDC to release the CPU from a very tight loop.&n;&t;** See MEM_RENDEZ comments in head.S.&n;&t;*/
id|__raw_writel
c_func
(paren
id|IRQ_OFFSET
c_func
(paren
id|TIMER_IRQ
)paren
comma
id|cpu_data
(braket
id|cpunum
)braket
dot
id|hpa
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * OK, wait a bit for that CPU to finish staggering about. &n;&t; * Slave will set a bit when it reaches smp_cpu_init() and then&n;&t; * wait for smp_commenced to be 1.&n;&t; * Once we see the bit change, we can move on.&n;&t; */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|0
suffix:semicolon
id|timeout
OL
l_int|10000
suffix:semicolon
id|timeout
op_increment
)paren
(brace
r_if
c_cond
(paren
id|IS_LOGGED_IN
c_func
(paren
id|cpunum
)paren
)paren
(brace
multiline_comment|/* Which implies Slave has started up */
id|cpu_now_booting
op_assign
l_int|0
suffix:semicolon
id|smp_init_current_idle_task
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|alive
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
id|put_task_struct
c_func
(paren
id|idle
)paren
suffix:semicolon
id|idle
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;SMP: CPU:%d is stuck.&bslash;n&quot;
comma
id|cpuid
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
id|alive
suffix:colon
multiline_comment|/* Remember the Slave data */
macro_line|#if (kDEBUG&gt;=100)
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;SMP: CPU:%d (num %d) came alive after %ld _us&bslash;n&quot;
comma
id|cpuid
comma
id|cpunum
comma
id|timeout
op_star
l_int|100
)paren
suffix:semicolon
macro_line|#endif /* kDEBUG */
macro_line|#ifdef ENTRY_SYS_CPUS
id|cpu_data
(braket
id|cpunum
)braket
dot
id|state
op_assign
id|STATE_RUNNING
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;** inventory.c:do_inventory() has already &squot;discovered&squot; the additional CPU&squot;s.&n;** We are ready to wrest them from PDC&squot;s control now.&n;** Called by smp_init bring all the secondaries online and hold them.  &n;**&n;** o Setup of the IPI irq handler is done in irq.c.&n;** o MEM_RENDEZ is initialzed in head.S:stext()&n;**&n;*/
DECL|function|smp_boot_cpus
r_void
id|__init
id|smp_boot_cpus
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|cpu_count
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|bogosum
op_assign
id|cpu_data
(braket
l_int|0
)braket
dot
id|loops_per_jiffy
suffix:semicolon
multiline_comment|/* Count Monarch */
multiline_comment|/* REVISIT - assumes first CPU reported by PAT PDC is BSP */
r_int
id|bootstrap_processor
op_assign
id|cpu_data
(braket
l_int|0
)braket
dot
id|cpuid
suffix:semicolon
multiline_comment|/* CPU ID of BSP */
multiline_comment|/* Setup BSP mappings */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;SMP: bootstrap CPU ID is %d&bslash;n&quot;
comma
id|bootstrap_processor
)paren
suffix:semicolon
id|init_task.thread_info-&gt;cpu
op_assign
id|bootstrap_processor
suffix:semicolon
id|current-&gt;thread_info-&gt;cpu
op_assign
id|bootstrap_processor
suffix:semicolon
multiline_comment|/* Mark Boostrap processor as present */
id|cpu_online_map
op_assign
id|cpumask_of_cpu
c_func
(paren
id|bootstrap_processor
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
macro_line|#ifdef ENTRY_SYS_CPUS
id|cpu_data
(braket
l_int|0
)braket
dot
id|state
op_assign
id|STATE_RUNNING
suffix:semicolon
macro_line|#endif
id|cpu_present_mask
op_assign
id|cpumask_of_cpu
c_func
(paren
id|bootstrap_processor
)paren
suffix:semicolon
multiline_comment|/* Nothing to do when told not to.  */
r_if
c_cond
(paren
id|max_cpus
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMP mode deactivated.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|max_cpus
op_ne
op_minus
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Limiting CPUs to %d&bslash;n&quot;
comma
id|max_cpus
)paren
suffix:semicolon
multiline_comment|/* We found more than one CPU.... */
r_if
c_cond
(paren
id|boot_cpu_data.cpu_count
OG
l_int|1
)paren
(brace
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
(brace
r_if
c_cond
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|cpuid
op_eq
id|NO_PROC_ID
op_logical_or
id|cpu_data
(braket
id|i
)braket
dot
id|cpuid
op_eq
id|bootstrap_processor
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|smp_boot_one_cpu
c_func
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|cpuid
comma
id|cpu_count
)paren
OL
l_int|0
)paren
r_continue
suffix:semicolon
id|bogosum
op_add_assign
id|cpu_data
(braket
id|i
)braket
dot
id|loops_per_jiffy
suffix:semicolon
id|cpu_count
op_increment
suffix:semicolon
multiline_comment|/* Count good CPUs only... */
id|cpu_present_mask
op_or_assign
l_int|1UL
op_lshift
id|i
suffix:semicolon
multiline_comment|/* Bail when we&squot;ve started as many CPUS as told to */
r_if
c_cond
(paren
id|cpu_count
op_eq
id|max_cpus
)paren
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cpu_count
op_eq
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMP: Bootstrap processor only.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * FIXME very rough.&n;&t; */
id|cache_decay_ticks
op_assign
id|HZ
op_div
l_int|100
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMP: Total %d of %d processors activated &quot;
l_string|&quot;(%lu.%02lu BogoMIPS noticed) (Present Mask: %lu).&bslash;n&quot;
comma
id|cpu_count
comma
id|boot_cpu_data.cpu_count
comma
(paren
id|bogosum
op_plus
l_int|25
)paren
op_div
l_int|5000
comma
(paren
(paren
id|bogosum
op_plus
l_int|25
)paren
op_div
l_int|50
)paren
op_mod
l_int|100
comma
id|cpu_present_mask
)paren
suffix:semicolon
id|smp_num_cpus
op_assign
id|cpu_count
suffix:semicolon
macro_line|#ifdef PER_CPU_IRQ_REGION
id|ipi_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/* &n; * Called from main.c by Monarch Processor.&n; * After this, any CPU can schedule any task.&n; */
DECL|function|smp_commence
r_void
id|smp_commence
c_func
(paren
r_void
)paren
(brace
id|smp_commenced
op_assign
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX FIXME : do nothing&n; */
DECL|function|smp_cpus_done
r_void
id|smp_cpus_done
c_func
(paren
r_int
r_int
id|cpu_max
)paren
(brace
id|smp_threads_ready
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|smp_prepare_cpus
r_void
id|__init
id|smp_prepare_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
id|smp_boot_cpus
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_prepare_boot_cpu
r_void
id|__devinit
id|smp_prepare_boot_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_online_map
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_present_mask
)paren
suffix:semicolon
)brace
DECL|function|__cpu_up
r_int
id|__devinit
id|__cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_return
id|cpu_online
c_func
(paren
id|cpu
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#ifdef ENTRY_SYS_CPUS
multiline_comment|/* Code goes along with:&n;**    entry.s:        ENTRY_NAME(sys_cpus)   / * 215, for cpu stat * /&n;*/
DECL|function|sys_cpus
r_int
id|sys_cpus
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
comma
id|j
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|current_pid
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sys_cpus:Only one argument supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
(brace
macro_line|#ifdef DUMP_MORE_STATE
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
(brace
r_int
id|cpus_per_line
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|IS_LOGGED_IN
c_func
(paren
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
id|j
op_increment
op_mod
id|cpus_per_line
)paren
id|printk
c_func
(paren
l_string|&quot; %3d&quot;
comma
id|i
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;n %3d&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;&bslash;n 0&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
(paren
id|argc
op_eq
l_int|2
)paren
op_logical_and
op_logical_neg
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-l&quot;
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nCPUSTATE  TASK CPUNUM CPUID HARDCPU(HPA)&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef DUMP_MORE_STATE
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|IS_LOGGED_IN
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|cpuid
op_ne
id|NO_PROC_ID
)paren
(brace
r_switch
c_cond
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|state
)paren
(brace
r_case
id|STATE_RENDEZVOUS
suffix:colon
id|printk
c_func
(paren
l_string|&quot;RENDEZVS &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_RUNNING
suffix:colon
id|printk
c_func
(paren
(paren
id|current_pid
c_func
(paren
id|i
)paren
op_ne
l_int|0
)paren
ques
c_cond
l_string|&quot;RUNNING  &quot;
suffix:colon
l_string|&quot;IDLING   &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_STOPPED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;STOPPED  &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_HALTED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;HALTED   &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%08x?&quot;
comma
id|cpu_data
(braket
id|i
)braket
dot
id|state
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IS_LOGGED_IN
c_func
(paren
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %4d&quot;
comma
id|current_pid
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %6d&quot;
comma
id|cpu_number_map
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %5d&quot;
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; 0x%lx&bslash;n&quot;
comma
id|cpu_data
(braket
id|i
)braket
dot
id|hpa
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s  %4d      0     0 --------&quot;
comma
(paren
id|current-&gt;pid
)paren
ques
c_cond
l_string|&quot;RUNNING &quot;
suffix:colon
l_string|&quot;IDLING  &quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
(paren
id|argc
op_eq
l_int|2
)paren
op_logical_and
op_logical_neg
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-s&quot;
)paren
)paren
)paren
(brace
macro_line|#ifdef DUMP_MORE_STATE
id|printk
c_func
(paren
l_string|&quot;&bslash;nCPUSTATE   CPUID&bslash;n&quot;
)paren
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|IS_LOGGED_IN
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|cpuid
op_ne
id|NO_PROC_ID
)paren
(brace
r_switch
c_cond
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|state
)paren
(brace
r_case
id|STATE_RENDEZVOUS
suffix:colon
id|printk
c_func
(paren
l_string|&quot;RENDEZVS&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_RUNNING
suffix:colon
id|printk
c_func
(paren
(paren
id|current_pid
c_func
(paren
id|i
)paren
op_ne
l_int|0
)paren
ques
c_cond
l_string|&quot;RUNNING &quot;
suffix:colon
l_string|&quot;IDLING&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_STOPPED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;STOPPED &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_HALTED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;HALTED  &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;  %5d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s    CPU0&quot;
comma
(paren
id|current-&gt;pid
op_eq
l_int|0
)paren
ques
c_cond
l_string|&quot;RUNNING &quot;
suffix:colon
l_string|&quot;IDLING  &quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;sys_cpus:Unknown request&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* ENTRY_SYS_CPUS */
macro_line|#ifdef CONFIG_PROC_FS
r_int
id|__init
DECL|function|setup_profiling_timer
id|setup_profiling_timer
c_func
(paren
r_int
r_int
id|multiplier
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
eof
