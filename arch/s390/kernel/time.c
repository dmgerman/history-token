multiline_comment|/*&n; *  arch/s390/kernel/time.c&n; *    Time of day based timer functions.&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  Derived from &quot;arch/i386/kernel/time.c&quot;&n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
multiline_comment|/* change this if you have some constant time drift */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY     ((unsigned long) 1000000/HZ)
DECL|macro|CLK_TICKS_PER_JIFFY
mdefine_line|#define CLK_TICKS_PER_JIFFY ((unsigned long) USECS_PER_JIFFY &lt;&lt; 12)
multiline_comment|/*&n; * Create a small time difference between the timer interrupts&n; * on the different cpus to avoid lock contention.&n; */
DECL|macro|CPU_DEVIATION
mdefine_line|#define CPU_DEVIATION       (smp_processor_id() &lt;&lt; 12)
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
DECL|variable|jiffies_64
id|EXPORT_SYMBOL
c_func
(paren
id|jiffies_64
)paren
suffix:semicolon
DECL|variable|ext_int_info_cc
r_static
id|ext_int_info_t
id|ext_int_info_cc
suffix:semicolon
DECL|variable|init_timer_cc
r_static
id|u64
id|init_timer_cc
suffix:semicolon
DECL|variable|jiffies_timer_cc
r_static
id|u64
id|jiffies_timer_cc
suffix:semicolon
DECL|variable|xtime_cc
r_static
id|u64
id|xtime_cc
suffix:semicolon
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
multiline_comment|/*&n; * Scheduler clock - returns current time in nanosec units.&n; */
DECL|function|sched_clock
r_int
r_int
r_int
id|sched_clock
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
id|get_clock
c_func
(paren
)paren
op_minus
id|jiffies_timer_cc
)paren
op_star
l_int|1000
)paren
op_rshift
l_int|12
suffix:semicolon
)brace
DECL|function|tod_to_timeval
r_void
id|tod_to_timeval
c_func
(paren
id|__u64
id|todval
comma
r_struct
id|timespec
op_star
id|xtime
)paren
(brace
r_int
r_int
r_int
id|sec
suffix:semicolon
id|sec
op_assign
id|todval
op_rshift
l_int|12
suffix:semicolon
id|do_div
c_func
(paren
id|sec
comma
l_int|1000000
)paren
suffix:semicolon
id|xtime-&gt;tv_sec
op_assign
id|sec
suffix:semicolon
id|todval
op_sub_assign
(paren
id|sec
op_star
l_int|1000000
)paren
op_lshift
l_int|12
suffix:semicolon
id|xtime-&gt;tv_nsec
op_assign
(paren
(paren
id|todval
op_star
l_int|1000
)paren
op_rshift
l_int|12
)paren
suffix:semicolon
)brace
DECL|function|do_gettimeoffset
r_static
r_inline
r_int
r_int
id|do_gettimeoffset
c_func
(paren
r_void
)paren
(brace
id|__u64
id|now
suffix:semicolon
id|now
op_assign
(paren
id|get_clock
c_func
(paren
)paren
op_minus
id|jiffies_timer_cc
)paren
op_rshift
l_int|12
suffix:semicolon
multiline_comment|/* We require the offset from the latest update of xtime */
id|now
op_sub_assign
(paren
id|__u64
)paren
id|wall_jiffies
op_star
id|USECS_PER_JIFFY
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|now
suffix:semicolon
)brace
multiline_comment|/*&n; * This version of gettimeofday has microsecond resolution.&n; */
DECL|function|do_gettimeofday
r_void
id|do_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|seq
suffix:semicolon
r_int
r_int
id|usec
comma
id|sec
suffix:semicolon
r_do
(brace
id|seq
op_assign
id|read_seqbegin_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_assign
id|xtime.tv_nsec
op_div
l_int|1000
op_plus
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|read_seqretry_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|seq
comma
id|flags
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|usec
op_ge
l_int|1000000
)paren
(brace
id|usec
op_sub_assign
l_int|1000000
suffix:semicolon
id|sec
op_increment
suffix:semicolon
)brace
id|tv-&gt;tv_sec
op_assign
id|sec
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|usec
suffix:semicolon
)brace
DECL|variable|do_gettimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_gettimeofday
)paren
suffix:semicolon
DECL|function|do_settimeofday
r_int
id|do_settimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
id|time_t
id|wtm_sec
comma
id|sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
r_int
id|wtm_nsec
comma
id|nsec
op_assign
id|tv-&gt;tv_nsec
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|tv-&gt;tv_nsec
op_ge
id|NSEC_PER_SEC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* This is revolting. We need to set the xtime.tv_nsec&n;&t; * correctly. However, the value in this location is&n;&t; * is value at the last tick.&n;&t; * Discover what correction gettimeofday&n;&t; * would have done, and then undo it!&n;&t; */
id|nsec
op_sub_assign
id|do_gettimeoffset
c_func
(paren
)paren
op_star
l_int|1000
suffix:semicolon
id|wtm_sec
op_assign
id|wall_to_monotonic.tv_sec
op_plus
(paren
id|xtime.tv_sec
op_minus
id|sec
)paren
suffix:semicolon
id|wtm_nsec
op_assign
id|wall_to_monotonic.tv_nsec
op_plus
(paren
id|xtime.tv_nsec
op_minus
id|nsec
)paren
suffix:semicolon
id|set_normalized_timespec
c_func
(paren
op_amp
id|xtime
comma
id|sec
comma
id|nsec
)paren
suffix:semicolon
id|set_normalized_timespec
c_func
(paren
op_amp
id|wall_to_monotonic
comma
id|wtm_sec
comma
id|wtm_nsec
)paren
suffix:semicolon
id|time_adjust
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* stop active adjtime() */
id|time_status
op_or_assign
id|STA_UNSYNC
suffix:semicolon
id|time_maxerror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|time_esterror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|write_sequnlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|clock_was_set
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|do_settimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_settimeofday
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
r_static
r_inline
id|__u32
DECL|function|__calculate_ticks
id|__calculate_ticks
c_func
(paren
id|__u64
id|elapsed
)paren
(brace
id|register_pair
id|rp
suffix:semicolon
id|rp.pair
op_assign
id|elapsed
op_rshift
l_int|1
suffix:semicolon
id|asm
(paren
l_string|&quot;dr %0,%1&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|rp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|CLK_TICKS_PER_JIFFY
op_rshift
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|rp.subreg.odd
suffix:semicolon
)brace
macro_line|#else /* CONFIG_ARCH_S390X */
r_static
r_inline
id|__u32
DECL|function|__calculate_ticks
id|__calculate_ticks
c_func
(paren
id|__u64
id|elapsed
)paren
(brace
r_return
id|elapsed
op_div
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ARCH_S390X */
macro_line|#ifdef CONFIG_PROFILING
r_extern
r_char
id|_stext
comma
id|_etext
suffix:semicolon
multiline_comment|/*&n; * The profiling function is SMP safe. (nothing can mess&n; * around with &quot;current&quot;, and the profiling counters are&n; * updated with atomic operations). This is especially&n; * useful with a profiling multiplier != 1&n; */
DECL|function|s390_do_profile
r_static
r_inline
r_void
id|s390_do_profile
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|eip
suffix:semicolon
r_extern
id|cpumask_t
id|prof_cpu_mask
suffix:semicolon
id|profile_hook
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
id|eip
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Only measure the CPUs specified by /proc/irq/prof_cpu_mask.&n;&t; * (default is all CPUs.)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|prof_cpu_mask
)paren
)paren
r_return
suffix:semicolon
id|eip
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|eip
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds EIP values silently,&n;&t; * put them into the last histogram slot, so if&n;&t; * present, they will show up as a sharp peak.&n;&t; */
r_if
c_cond
(paren
id|eip
OG
id|prof_len
op_minus
l_int|1
)paren
id|eip
op_assign
id|prof_len
op_minus
l_int|1
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|eip
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|s390_do_profile
mdefine_line|#define s390_do_profile(regs)  do { ; } while(0)
macro_line|#endif /* CONFIG_PROFILING */
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|function|account_ticks
r_void
id|account_ticks
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|__u64
id|tmp
suffix:semicolon
id|__u32
id|ticks
suffix:semicolon
multiline_comment|/* Calculate how many ticks have passed. */
r_if
c_cond
(paren
id|S390_lowcore.int_clock
OL
id|S390_lowcore.jiffy_timer
)paren
r_return
suffix:semicolon
id|tmp
op_assign
id|S390_lowcore.int_clock
op_minus
id|S390_lowcore.jiffy_timer
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ge
l_int|2
op_star
id|CLK_TICKS_PER_JIFFY
)paren
(brace
multiline_comment|/* more than two ticks ? */
id|ticks
op_assign
id|__calculate_ticks
c_func
(paren
id|tmp
)paren
op_plus
l_int|1
suffix:semicolon
id|S390_lowcore.jiffy_timer
op_add_assign
id|CLK_TICKS_PER_JIFFY
op_star
(paren
id|__u64
)paren
id|ticks
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tmp
op_ge
id|CLK_TICKS_PER_JIFFY
)paren
(brace
id|ticks
op_assign
l_int|2
suffix:semicolon
id|S390_lowcore.jiffy_timer
op_add_assign
l_int|2
op_star
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
)brace
r_else
(brace
id|ticks
op_assign
l_int|1
suffix:semicolon
id|S390_lowcore.jiffy_timer
op_add_assign
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
)brace
multiline_comment|/* set clock comparator for next tick */
id|tmp
op_assign
id|S390_lowcore.jiffy_timer
op_plus
id|CPU_DEVIATION
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;SCKC %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t; * Do not rely on the boot cpu to do the calls to do_timer.&n;&t; * Spread it over all cpus instead.&n;&t; */
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S390_lowcore.jiffy_timer
OG
id|xtime_cc
)paren
(brace
id|__u32
id|xticks
suffix:semicolon
id|tmp
op_assign
id|S390_lowcore.jiffy_timer
op_minus
id|xtime_cc
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ge
l_int|2
op_star
id|CLK_TICKS_PER_JIFFY
)paren
(brace
id|xticks
op_assign
id|__calculate_ticks
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|xtime_cc
op_add_assign
(paren
id|__u64
)paren
id|xticks
op_star
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
)brace
r_else
(brace
id|xticks
op_assign
l_int|1
suffix:semicolon
id|xtime_cc
op_add_assign
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
)brace
r_while
c_loop
(paren
id|xticks
op_decrement
)paren
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ticks
op_decrement
)paren
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
macro_line|#else
r_while
c_loop
(paren
id|ticks
op_decrement
)paren
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|s390_do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NO_IDLE_HZ
macro_line|#ifdef CONFIG_NO_IDLE_HZ_INIT
DECL|variable|sysctl_hz_timer
r_int
id|sysctl_hz_timer
op_assign
l_int|0
suffix:semicolon
macro_line|#else
DECL|variable|sysctl_hz_timer
r_int
id|sysctl_hz_timer
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Stop the HZ tick on the current CPU.&n; * Only cpu_idle may call this function.&n; */
DECL|function|stop_hz_timer
r_static
r_inline
r_void
id|stop_hz_timer
c_func
(paren
r_void
)paren
(brace
id|__u64
id|timer
suffix:semicolon
r_if
c_cond
(paren
id|sysctl_hz_timer
op_ne
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Leave the clock comparator set up for the next timer&n;&t; * tick if either rcu or a softirq is pending.&n;&t; */
r_if
c_cond
(paren
id|rcu_pending
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_logical_or
id|local_softirq_pending
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * This cpu is going really idle. Set up the clock comparator&n;&t; * for the next event.&n;&t; */
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|nohz_cpu_mask
)paren
suffix:semicolon
id|timer
op_assign
(paren
id|__u64
)paren
(paren
id|next_timer_interrupt
c_func
(paren
)paren
op_minus
id|jiffies
)paren
op_plus
id|jiffies_64
suffix:semicolon
id|timer
op_assign
id|jiffies_timer_cc
op_plus
id|timer
op_star
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;SCKC %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|timer
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start the HZ tick on the current CPU.&n; * Only cpu_idle may call this function.&n; */
DECL|function|start_hz_timer
r_static
r_inline
r_void
id|start_hz_timer
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|nohz_cpu_mask
)paren
)paren
r_return
suffix:semicolon
id|account_ticks
c_func
(paren
id|__KSTK_PTREGS
c_func
(paren
id|current
)paren
)paren
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|nohz_cpu_mask
)paren
suffix:semicolon
)brace
DECL|function|nohz_idle_notify
r_static
r_int
id|nohz_idle_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|action
comma
r_void
op_star
id|hcpu
)paren
(brace
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|CPU_IDLE
suffix:colon
id|stop_hz_timer
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_NOT_IDLE
suffix:colon
id|start_hz_timer
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
DECL|variable|nohz_idle_nb
r_static
r_struct
id|notifier_block
id|nohz_idle_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|nohz_idle_notify
comma
)brace
suffix:semicolon
DECL|function|nohz_init
r_void
id|__init
id|nohz_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|register_idle_notifier
c_func
(paren
op_amp
id|nohz_idle_nb
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register idle notifier&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Start the clock comparator on the current CPU.&n; */
DECL|function|init_cpu_timer
r_void
id|init_cpu_timer
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cr0
suffix:semicolon
id|__u64
id|timer
suffix:semicolon
id|timer
op_assign
id|jiffies_timer_cc
op_plus
id|jiffies_64
op_star
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
id|S390_lowcore.jiffy_timer
op_assign
id|timer
op_plus
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
id|timer
op_add_assign
id|CLK_TICKS_PER_JIFFY
op_plus
id|CPU_DEVIATION
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;SCKC %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|timer
)paren
)paren
suffix:semicolon
multiline_comment|/* allow clock comparator timer interrupt */
id|__ctl_store
c_func
(paren
id|cr0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|cr0
op_or_assign
l_int|0x800
suffix:semicolon
id|__ctl_load
c_func
(paren
id|cr0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_void
id|vtime_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize the TOD clock and the CPU timer of&n; * the boot cpu.&n; */
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
id|__u64
id|set_time_cc
suffix:semicolon
r_int
id|cc
suffix:semicolon
multiline_comment|/* kick the TOD clock */
id|asm
r_volatile
(paren
l_string|&quot;STCK 0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;IPM  %0&bslash;n&bslash;t&quot;
l_string|&quot;SRL  %0,28&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|init_timer_cc
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cc
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* clock in set state: all is fine */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* clock in non-set state: FIXME */
id|printk
c_func
(paren
l_string|&quot;time_init: TOD clock in non-set state&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* clock in error state: FIXME */
id|printk
c_func
(paren
l_string|&quot;time_init: TOD clock in error state&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* clock in stopped or not-operational state: FIXME */
id|printk
c_func
(paren
l_string|&quot;time_init: TOD clock stopped/non-operational&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|jiffies_timer_cc
op_assign
id|init_timer_cc
op_minus
id|jiffies_64
op_star
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
multiline_comment|/* set xtime */
id|xtime_cc
op_assign
id|init_timer_cc
op_plus
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
id|set_time_cc
op_assign
id|init_timer_cc
op_minus
l_int|0x8126d60e46000000LL
op_plus
(paren
l_int|0x3c26700LL
op_star
l_int|1000000
op_star
l_int|4096
)paren
suffix:semicolon
id|tod_to_timeval
c_func
(paren
id|set_time_cc
comma
op_amp
id|xtime
)paren
suffix:semicolon
id|set_normalized_timespec
c_func
(paren
op_amp
id|wall_to_monotonic
comma
op_minus
id|xtime.tv_sec
comma
op_minus
id|xtime.tv_nsec
)paren
suffix:semicolon
multiline_comment|/* request the clock comparator external interrupt */
r_if
c_cond
(paren
id|register_early_external_interrupt
c_func
(paren
l_int|0x1004
comma
l_int|0
comma
op_amp
id|ext_int_info_cc
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t request external interrupt 0x1004&quot;
)paren
suffix:semicolon
id|init_cpu_timer
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NO_IDLE_HZ
id|nohz_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIRT_TIMER
id|vtime_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
