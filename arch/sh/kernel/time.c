multiline_comment|/* $Id: time.c,v 1.19 2004/02/27 00:40:48 lethal Exp $&n; *&n; *  linux/arch/sh/kernel/time.c&n; *&n; *  Copyright (C) 1999  Tetsuya Okada &amp; Niibe Yutaka&n; *  Copyright (C) 2000  Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *  Copyright (C) 2002, 2003  Paul Mundt&n; *  Copyright (C) 2002  M. R. Brown  &lt;mrbrown@linux-sh.org&gt;&n; *&n; *  Some code taken from i386 version.&n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; */
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
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/freq.h&gt;
macro_line|#ifdef CONFIG_SH_KGDB
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
DECL|macro|TMU_TOCR_INIT
mdefine_line|#define TMU_TOCR_INIT&t;0x00
DECL|macro|TMU0_TCR_INIT
mdefine_line|#define TMU0_TCR_INIT&t;0x0020
DECL|macro|TMU_TSTR_INIT
mdefine_line|#define TMU_TSTR_INIT&t;1
DECL|macro|TMU0_TCR_CALIB
mdefine_line|#define TMU0_TCR_CALIB&t;0x0000
macro_line|#if defined(CONFIG_CPU_SH3)
DECL|macro|TMU_TOCR
mdefine_line|#define TMU_TOCR&t;0xfffffe90&t;/* Byte access */
DECL|macro|TMU_TSTR
mdefine_line|#define TMU_TSTR&t;0xfffffe92&t;/* Byte access */
DECL|macro|TMU0_TCOR
mdefine_line|#define TMU0_TCOR&t;0xfffffe94&t;/* Long access */
DECL|macro|TMU0_TCNT
mdefine_line|#define TMU0_TCNT&t;0xfffffe98&t;/* Long access */
DECL|macro|TMU0_TCR
mdefine_line|#define TMU0_TCR&t;0xfffffe9c&t;/* Word access */
macro_line|#elif defined(CONFIG_CPU_SH4)
DECL|macro|TMU_TOCR
mdefine_line|#define TMU_TOCR&t;0xffd80000&t;/* Byte access */
DECL|macro|TMU_TSTR
mdefine_line|#define TMU_TSTR&t;0xffd80004&t;/* Byte access */
DECL|macro|TMU0_TCOR
mdefine_line|#define TMU0_TCOR&t;0xffd80008&t;/* Long access */
DECL|macro|TMU0_TCNT
mdefine_line|#define TMU0_TCNT&t;0xffd8000c&t;/* Long access */
DECL|macro|TMU0_TCR
mdefine_line|#define TMU0_TCR&t;0xffd80010&t;/* Word access */
macro_line|#ifdef CONFIG_CPU_SUBTYPE_ST40STB1
DECL|macro|CLOCKGEN_MEMCLKCR
mdefine_line|#define CLOCKGEN_MEMCLKCR 0xbb040038
DECL|macro|MEMCLKCR_RATIO_MASK
mdefine_line|#define MEMCLKCR_RATIO_MASK 0x7
macro_line|#endif /* CONFIG_CPU_SUBTYPE_ST40STB1 */
macro_line|#endif /* CONFIG_CPU_SH3 or CONFIG_CPU_SH4 */
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE (tick_nsec / 1000)
DECL|variable|tmu0_lock
id|spinlock_t
id|tmu0_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
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
multiline_comment|/* XXX: Can we initialize this in a routine somewhere?  Dreamcast doesn&squot;t want&n; * these routines anywhere... */
macro_line|#ifdef CONFIG_SH_RTC
DECL|variable|rtc_get_time
r_void
(paren
op_star
id|rtc_get_time
)paren
(paren
r_struct
id|timespec
op_star
)paren
op_assign
id|sh_rtc_gettimeofday
suffix:semicolon
DECL|variable|rtc_set_time
r_int
(paren
op_star
id|rtc_set_time
)paren
(paren
r_const
id|time_t
)paren
op_assign
id|sh_rtc_settimeofday
suffix:semicolon
macro_line|#else
DECL|variable|rtc_get_time
r_void
(paren
op_star
id|rtc_get_time
)paren
(paren
r_struct
id|timespec
op_star
)paren
op_assign
l_int|0
suffix:semicolon
DECL|variable|rtc_set_time
r_int
(paren
op_star
id|rtc_set_time
)paren
(paren
r_const
id|time_t
)paren
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SH3)
DECL|variable|stc_multipliers
r_static
r_int
id|stc_multipliers
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|stc_values
r_static
r_int
id|stc_values
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|4
comma
l_int|2
comma
l_int|5
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|macro|bfc_divisors
mdefine_line|#define bfc_divisors stc_multipliers
DECL|macro|bfc_values
mdefine_line|#define bfc_values stc_values
DECL|variable|ifc_divisors
r_static
r_int
id|ifc_divisors
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|ifc_values
r_static
r_int
id|ifc_values
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|4
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|pfc_divisors
r_static
r_int
id|pfc_divisors
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|pfc_values
r_static
r_int
id|pfc_values
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|4
comma
l_int|2
comma
l_int|5
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
macro_line|#elif defined(CONFIG_CPU_SH4)
DECL|variable|ifc_divisors
r_static
r_int
id|ifc_divisors
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|8
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|ifc_values
r_static
r_int
id|ifc_values
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|0
comma
l_int|4
comma
l_int|0
comma
l_int|5
)brace
suffix:semicolon
DECL|macro|bfc_divisors
mdefine_line|#define bfc_divisors ifc_divisors&t;/* Same */
DECL|macro|bfc_values
mdefine_line|#define bfc_values ifc_values
DECL|variable|pfc_divisors
r_static
r_int
id|pfc_divisors
(braket
)braket
op_assign
(brace
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|8
comma
l_int|2
comma
l_int|2
comma
l_int|2
)brace
suffix:semicolon
DECL|variable|pfc_values
r_static
r_int
id|pfc_values
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|4
)brace
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Unknown ifc/bfc/pfc/stc values for this processor&quot;
macro_line|#endif
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
r_int
r_int
r_int
)paren
id|jiffies
op_star
(paren
l_int|1000000000
op_div
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|do_gettimeoffset
r_static
r_int
r_int
id|do_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
id|count
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_static
r_int
id|count_p
op_assign
l_int|0x7fffffff
suffix:semicolon
multiline_comment|/* for the first call after boot */
r_static
r_int
r_int
id|jiffies_p
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * cache volatile jiffies temporarily; we have IRQs turned off. &n;&t; */
r_int
r_int
id|jiffies_t
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tmu0_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|count
op_assign
id|ctrl_inl
c_func
(paren
id|TMU0_TCNT
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
id|jiffies_t
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; * avoiding timer inconsistencies (they are rare, but they happen)...&n;&t; * there is one kind of problem that must be avoided here:&n;&t; *  1. the timer counter underflows&n;&t; */
r_if
c_cond
(paren
id|jiffies_t
op_eq
id|jiffies_p
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|count_p
)paren
(brace
multiline_comment|/* the nutcase */
r_if
c_cond
(paren
id|ctrl_inw
c_func
(paren
id|TMU0_TCR
)paren
op_amp
l_int|0x100
)paren
(brace
multiline_comment|/* Check UNF bit */
multiline_comment|/*&n;&t;&t;&t;&t; * We cannot detect lost timer interrupts ... &n;&t;&t;&t;&t; * well, that&squot;s why we call them lost, don&squot;t we? :)&n;&t;&t;&t;&t; * [hmm, on the Pentium and Alpha we can ... sort of]&n;&t;&t;&t;&t; */
id|count
op_sub_assign
id|LATCH
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;do_slow_gettimeoffset(): hardware timer problem?&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
id|jiffies_p
op_assign
id|jiffies_t
suffix:semicolon
id|count_p
op_assign
id|count
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tmu0_lock
comma
id|flags
)paren
suffix:semicolon
id|count
op_assign
(paren
(paren
id|LATCH
op_minus
l_int|1
)paren
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
id|LATCH
op_div
l_int|2
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
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
id|seq
suffix:semicolon
r_int
r_int
id|usec
comma
id|sec
suffix:semicolon
r_int
r_int
id|lost
suffix:semicolon
r_do
(brace
id|seq
op_assign
id|read_seqbegin
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|usec
op_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
id|lost
op_assign
id|jiffies
op_minus
id|wall_jiffies
suffix:semicolon
r_if
c_cond
(paren
id|lost
)paren
id|usec
op_add_assign
id|lost
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_add_assign
id|xtime.tv_nsec
op_div
l_int|1000
suffix:semicolon
)brace
r_while
c_loop
(paren
id|read_seqretry
c_func
(paren
op_amp
id|xtime_lock
comma
id|seq
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
multiline_comment|/*&n;&t; * This is revolting. We need to set &quot;xtime&quot; correctly. However, the&n;&t; * value in this location is the value at the most recent update of&n;&t; * wall time.  Discover what correction gettimeofday() would have&n;&t; * made, and then undo it!&n;&t; */
id|nsec
op_sub_assign
l_int|1000
op_star
(paren
id|do_gettimeoffset
c_func
(paren
)paren
op_plus
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
)paren
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
multiline_comment|/* last time the RTC clock got updated */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
suffix:semicolon
multiline_comment|/* Profiling definitions */
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
r_extern
r_int
r_int
op_star
id|prof_buffer
suffix:semicolon
r_extern
r_int
r_int
id|prof_len
suffix:semicolon
r_extern
r_int
r_int
id|prof_shift
suffix:semicolon
r_extern
r_char
id|_stext
suffix:semicolon
DECL|function|sh_do_profile
r_static
r_inline
r_void
id|sh_do_profile
c_func
(paren
r_int
r_int
id|pc
)paren
(brace
multiline_comment|/* Don&squot;t profile cpu_idle.. */
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
op_logical_or
op_logical_neg
id|current-&gt;pid
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
l_int|0xa0000000UL
op_logical_and
id|pc
OL
l_int|0xc0000000UL
)paren
id|pc
op_sub_assign
l_int|0x20000000
suffix:semicolon
id|pc
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|pc
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds PC values silently,&n;&t; * put them into the last histogram slot, so if&n;&t; * present, they will show up as a sharp peak.&n;&t; */
r_if
c_cond
(paren
id|pc
OG
id|prof_len
op_minus
l_int|1
)paren
id|pc
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
id|pc
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|function|do_timer_interrupt
r_static
r_inline
r_void
id|do_timer_interrupt
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
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|sh_do_profile
c_func
(paren
id|regs-&gt;pc
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
r_if
c_cond
(paren
id|sh_mv.mv_heartbeat
op_ne
l_int|NULL
)paren
id|sh_mv
dot
id|mv_heartbeat
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * If we have an externally synchronized Linux clock, then update&n;&t; * RTC clock accordingly every ~11 minutes. Set_rtc_mmss() has to be&n;&t; * called as close as possible to 500 ms before the new second starts.&n;&t; */
r_if
c_cond
(paren
(paren
id|time_status
op_amp
id|STA_UNSYNC
)paren
op_eq
l_int|0
op_logical_and
id|xtime.tv_sec
OG
id|last_rtc_update
op_plus
l_int|660
op_logical_and
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
op_ge
l_int|500000
op_minus
(paren
(paren
r_int
)paren
id|TICK_SIZE
)paren
op_div
l_int|2
op_logical_and
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
op_le
l_int|500000
op_plus
(paren
(paren
r_int
)paren
id|TICK_SIZE
)paren
op_div
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|rtc_set_time
c_func
(paren
id|xtime.tv_sec
)paren
op_eq
l_int|0
)paren
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
r_else
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
multiline_comment|/* do it again in 60 s */
)brace
)brace
multiline_comment|/*&n; * This is the same as the above, except we _also_ save the current&n; * Time Stamp Counter value at the time of the timer interrupt, so that&n; * we later on can estimate the time of day more exactly.&n; */
DECL|function|timer_interrupt
r_static
id|irqreturn_t
id|timer_interrupt
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
r_int
id|timer_status
suffix:semicolon
multiline_comment|/* Clear UNF bit */
id|timer_status
op_assign
id|ctrl_inw
c_func
(paren
id|TMU0_TCR
)paren
suffix:semicolon
id|timer_status
op_and_assign
op_complement
l_int|0x100
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|timer_status
comma
id|TMU0_TCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Here we are in the timer irq handler. We just have irqs locally&n;&t; * disabled but we don&squot;t know if the timer_bh is running on the other&n;&t; * CPU. We need to avoid to SMP race with it. NOTE: we don&squot; t need&n;&t; * the irq version of write_lock because as just said we have irq&n;&t; * locally disabled. -arca&n;&t; */
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|do_timer_interrupt
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Hah!  We&squot;ll see if this works (switching from usecs to nsecs).&n; */
DECL|function|get_timer_frequency
r_static
r_int
r_int
id|__init
id|get_timer_frequency
c_func
(paren
r_void
)paren
(brace
id|u32
id|freq
suffix:semicolon
r_struct
id|timespec
id|ts1
comma
id|ts2
suffix:semicolon
r_int
r_int
id|diff_nsec
suffix:semicolon
r_int
r_int
id|factor
suffix:semicolon
multiline_comment|/* Setup the timer:  We don&squot;t want to generate interrupts, just&n;&t; * have it count down at its natural rate.&n;&t; */
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|TMU_TSTR
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|TMU_TOCR_INIT
comma
id|TMU_TOCR
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|TMU0_TCR_CALIB
comma
id|TMU0_TCR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0xffffffff
comma
id|TMU0_TCOR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0xffffffff
comma
id|TMU0_TCNT
)paren
suffix:semicolon
id|rtc_get_time
c_func
(paren
op_amp
id|ts2
)paren
suffix:semicolon
r_do
(brace
id|rtc_get_time
c_func
(paren
op_amp
id|ts1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ts1.tv_nsec
op_eq
id|ts2.tv_nsec
op_logical_and
id|ts1.tv_sec
op_eq
id|ts2.tv_sec
)paren
suffix:semicolon
multiline_comment|/* actually start the timer */
id|ctrl_outb
c_func
(paren
id|TMU_TSTR_INIT
comma
id|TMU_TSTR
)paren
suffix:semicolon
r_do
(brace
id|rtc_get_time
c_func
(paren
op_amp
id|ts2
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ts1.tv_nsec
op_eq
id|ts2.tv_nsec
op_logical_and
id|ts1.tv_sec
op_eq
id|ts2.tv_sec
)paren
suffix:semicolon
id|freq
op_assign
l_int|0xffffffff
op_minus
id|ctrl_inl
c_func
(paren
id|TMU0_TCNT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ts2.tv_nsec
OL
id|ts1.tv_nsec
)paren
(brace
id|ts2.tv_nsec
op_add_assign
l_int|1000000000
suffix:semicolon
id|ts2.tv_sec
op_decrement
suffix:semicolon
)brace
id|diff_nsec
op_assign
(paren
id|ts2.tv_sec
op_minus
id|ts1.tv_sec
)paren
op_star
l_int|1000000000
op_plus
(paren
id|ts2.tv_nsec
op_minus
id|ts1.tv_nsec
)paren
suffix:semicolon
multiline_comment|/* this should work well if the RTC has a precision of n Hz, where&n;&t; * n is an integer.  I don&squot;t think we have to worry about the other&n;&t; * cases. */
id|factor
op_assign
(paren
l_int|1000000000
op_plus
id|diff_nsec
op_div
l_int|2
)paren
op_div
id|diff_nsec
suffix:semicolon
r_if
c_cond
(paren
id|factor
op_star
id|diff_nsec
OG
l_int|1100000000
op_logical_or
id|factor
op_star
id|diff_nsec
OL
l_int|900000000
)paren
id|panic
c_func
(paren
l_string|&quot;weird RTC (diff_nsec %ld)&quot;
comma
id|diff_nsec
)paren
suffix:semicolon
r_return
id|freq
op_star
id|factor
suffix:semicolon
)brace
DECL|variable|board_time_init
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_void
)paren
op_assign
l_int|0
suffix:semicolon
DECL|variable|board_timer_setup
r_void
(paren
op_star
id|board_timer_setup
)paren
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|sh_pclk_freq
id|__initdata
op_assign
id|CONFIG_SH_PCLK_FREQ
suffix:semicolon
DECL|function|sh_pclk_setup
r_static
r_int
id|__init
id|sh_pclk_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|freq
)paren
)paren
id|sh_pclk_freq
op_assign
id|freq
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;sh_pclk=&quot;
comma
id|sh_pclk_setup
)paren
suffix:semicolon
DECL|variable|irq0
r_static
r_struct
id|irqaction
id|irq0
op_assign
(brace
id|timer_interrupt
comma
id|SA_INTERRUPT
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|get_current_frequency_divisors
r_void
id|get_current_frequency_divisors
c_func
(paren
r_int
r_int
op_star
id|ifc
comma
r_int
r_int
op_star
id|bfc
comma
r_int
r_int
op_star
id|pfc
)paren
(brace
r_int
r_int
id|frqcr
op_assign
id|ctrl_inw
c_func
(paren
id|FRQCR
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_SH3)
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
(paren
id|frqcr
op_amp
l_int|0x8000
)paren
op_rshift
l_int|13
suffix:semicolon
id|tmp
op_or_assign
(paren
id|frqcr
op_amp
l_int|0x0030
)paren
op_rshift
l_int|4
suffix:semicolon
op_star
id|bfc
op_assign
id|stc_multipliers
(braket
id|tmp
)braket
suffix:semicolon
id|tmp
op_assign
(paren
id|frqcr
op_amp
l_int|0x4000
)paren
op_rshift
l_int|12
suffix:semicolon
id|tmp
op_or_assign
(paren
id|frqcr
op_amp
l_int|0x000c
)paren
op_rshift
l_int|2
suffix:semicolon
op_star
id|ifc
op_assign
id|ifc_divisors
(braket
id|tmp
)braket
suffix:semicolon
id|tmp
op_assign
(paren
id|frqcr
op_amp
l_int|0x2000
)paren
op_rshift
l_int|11
suffix:semicolon
id|tmp
op_or_assign
id|frqcr
op_amp
l_int|0x0003
suffix:semicolon
op_star
id|pfc
op_assign
id|pfc_divisors
(braket
id|tmp
)braket
suffix:semicolon
macro_line|#elif defined(CONFIG_CPU_SH4)
op_star
id|ifc
op_assign
id|ifc_divisors
(braket
(paren
id|frqcr
op_rshift
l_int|6
)paren
op_amp
l_int|0x0007
)braket
suffix:semicolon
op_star
id|bfc
op_assign
id|bfc_divisors
(braket
(paren
id|frqcr
op_rshift
l_int|3
)paren
op_amp
l_int|0x0007
)braket
suffix:semicolon
op_star
id|pfc
op_assign
id|pfc_divisors
(braket
id|frqcr
op_amp
l_int|0x0007
)braket
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * This bit of ugliness builds up accessor routines to get at both&n; * the divisors and the physical values.&n; */
DECL|macro|_FREQ_TABLE
mdefine_line|#define _FREQ_TABLE(x) &bslash;&n;&t;unsigned int get_##x##_divisor(unsigned int value) &t;&bslash;&n;&t;&t;{ return x##_divisors[value]; }&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int get_##x##_value(unsigned int divisor)&t;&bslash;&n;&t;&t;{ return x##_values[(divisor - 1)]; }
DECL|variable|ifc
id|_FREQ_TABLE
c_func
(paren
id|ifc
)paren
suffix:semicolon
DECL|variable|bfc
id|_FREQ_TABLE
c_func
(paren
id|bfc
)paren
suffix:semicolon
DECL|variable|pfc
id|_FREQ_TABLE
c_func
(paren
id|pfc
)paren
suffix:semicolon
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|timer_freq
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ifc
comma
id|pfc
comma
id|bfc
suffix:semicolon
r_int
r_int
id|interval
suffix:semicolon
r_if
c_cond
(paren
id|board_time_init
)paren
id|board_time_init
c_func
(paren
)paren
suffix:semicolon
id|get_current_frequency_divisors
c_func
(paren
op_amp
id|ifc
comma
op_amp
id|bfc
comma
op_amp
id|pfc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we don&squot;t have an RTC (such as with the SH7300), don&squot;t attempt to&n;&t; * probe the timer frequency. Rely on an either hardcoded peripheral&n;&t; * clock value, or on the sh_pclk command line option.&n;&t; */
id|current_cpu_data.module_clock
op_assign
id|sh_pclk_freq
suffix:semicolon
multiline_comment|/* XXX: Switch this over to a more generic test. */
r_if
c_cond
(paren
id|current_cpu_data.type
op_ne
id|CPU_SH7300
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* &n;&t;&t; * If we&squot;ve specified a peripheral clock frequency, and we have&n;&t;&t; * an RTC, compare it against the autodetected value. Complain&n;&t;&t; * if there&squot;s a mismatch.&n;&t;&t; *&n;&t;&t; * Note: We should allow for some high and low watermarks for&n;&t;&t; * the frequency here (compensating for potential drift), as&n;&t;&t; * otherwise we&squot;ll likely end up triggering this essentially&n;&t;&t; * on every boot.&n;&t;&t; */
id|timer_freq
op_assign
id|get_timer_frequency
c_func
(paren
)paren
suffix:semicolon
id|freq
op_assign
id|timer_freq
op_star
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|sh_pclk_freq
op_logical_and
id|sh_pclk_freq
op_ne
id|freq
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Calculated peripheral clock value &quot;
l_string|&quot;%d differs from sh_pclk value %d, fixing..&bslash;n&quot;
comma
id|freq
comma
id|sh_pclk_freq
)paren
suffix:semicolon
id|current_cpu_data.module_clock
op_assign
id|freq
suffix:semicolon
)brace
)brace
id|rtc_get_time
c_func
(paren
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
r_if
c_cond
(paren
id|board_timer_setup
)paren
(brace
id|board_timer_setup
c_func
(paren
op_amp
id|irq0
)paren
suffix:semicolon
)brace
r_else
(brace
id|setup_irq
c_func
(paren
id|TIMER_IRQ
comma
op_amp
id|irq0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|current_cpu_data.master_clock
)paren
id|current_cpu_data.master_clock
op_assign
id|current_cpu_data.module_clock
op_star
id|pfc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current_cpu_data.bus_clock
)paren
id|current_cpu_data.bus_clock
op_assign
id|current_cpu_data.master_clock
op_div
id|bfc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current_cpu_data.cpu_clock
)paren
id|current_cpu_data.cpu_clock
op_assign
id|current_cpu_data.master_clock
op_div
id|ifc
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU clock: %d.%02dMHz&bslash;n&quot;
comma
(paren
id|current_cpu_data.cpu_clock
op_div
l_int|1000000
)paren
comma
(paren
id|current_cpu_data.cpu_clock
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Bus clock: %d.%02dMHz&bslash;n&quot;
comma
(paren
id|current_cpu_data.bus_clock
op_div
l_int|1000000
)paren
comma
(paren
id|current_cpu_data.bus_clock
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_SUBTYPE_ST40STB1
id|printk
c_func
(paren
l_string|&quot;Memory clock: %d.%02dMHz&bslash;n&quot;
comma
(paren
id|current_cpu_data.memory_clock
op_div
l_int|1000000
)paren
comma
(paren
id|current_cpu_data.memory_clock
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Module clock: %d.%02dMHz&bslash;n&quot;
comma
(paren
id|current_cpu_data.module_clock
op_div
l_int|1000000
)paren
comma
(paren
id|current_cpu_data.module_clock
op_mod
l_int|1000000
)paren
op_div
l_int|10000
)paren
suffix:semicolon
id|interval
op_assign
(paren
id|current_cpu_data.module_clock
op_div
l_int|4
op_plus
id|HZ
op_div
l_int|2
)paren
op_div
id|HZ
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Interval = %ld&bslash;n&quot;
comma
id|interval
)paren
suffix:semicolon
multiline_comment|/* Start TMU0 */
id|ctrl_outb
c_func
(paren
l_int|0
comma
id|TMU_TSTR
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|TMU_TOCR_INIT
comma
id|TMU_TOCR
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|TMU0_TCR_INIT
comma
id|TMU0_TCR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|interval
comma
id|TMU0_TCOR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|interval
comma
id|TMU0_TCNT
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|TMU_TSTR_INIT
comma
id|TMU_TSTR
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SH_KGDB)
multiline_comment|/*&n;&t; * Set up kgdb as requested. We do it here because the serial&n;&t; * init uses the timer vars we just set up for figuring baud.&n;&t; */
id|kgdb_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
