multiline_comment|/*&n; * linux/arch/ia64/kernel/time.c&n; *&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&t;David Mosberger &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; * Copyright (C) 1999-2000 VA Linux Systems&n; * Copyright (C) 1999-2000 Walt Drummond &lt;drummond@valinux.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
r_extern
r_int
r_int
id|last_nsec_offset
suffix:semicolon
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_DEBUG_IRQ
DECL|variable|last_cli_ip
r_int
r_int
id|last_cli_ip
suffix:semicolon
macro_line|#endif
r_static
r_void
DECL|function|do_profile
id|do_profile
(paren
r_int
r_int
id|ip
)paren
(brace
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
r_extern
r_char
id|_stext
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
op_amp
id|prof_cpu_mask
)paren
)paren
r_return
suffix:semicolon
id|ip
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|ip
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds IP values silently, put them into the last&n;&t; * histogram slot, so if present, they will show up as a sharp peak.&n;&t; */
r_if
c_cond
(paren
id|ip
OG
id|prof_len
op_minus
l_int|1
)paren
id|ip
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
id|ip
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the number of nano-seconds that elapsed since the last update to jiffy.  The&n; * xtime_lock must be at least read-locked when calling this routine.&n; */
r_static
r_inline
r_int
r_int
DECL|function|gettimeoffset
id|gettimeoffset
(paren
r_void
)paren
(brace
r_int
r_int
id|elapsed_cycles
comma
id|lost
op_assign
id|jiffies
op_minus
id|wall_jiffies
suffix:semicolon
r_int
r_int
id|now
comma
id|last_tick
suffix:semicolon
DECL|macro|time_keeper_id
macro_line|#&t;define time_keeper_id&t;0&t;/* smp_processor_id() of time-keeper */
id|last_tick
op_assign
(paren
id|cpu_data
c_func
(paren
id|time_keeper_id
)paren
op_member_access_from_pointer
id|itm_next
op_minus
(paren
id|lost
op_plus
l_int|1
)paren
op_star
id|cpu_data
c_func
(paren
id|time_keeper_id
)paren
op_member_access_from_pointer
id|itm_delta
)paren
suffix:semicolon
id|now
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
r_int
)paren
(paren
id|now
op_minus
id|last_tick
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CPU %d: now &lt; last_tick (now=0x%lx,last_tick=0x%lx)!&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|now
comma
id|last_tick
)paren
suffix:semicolon
r_return
id|last_nsec_offset
suffix:semicolon
)brace
id|elapsed_cycles
op_assign
id|now
op_minus
id|last_tick
suffix:semicolon
r_return
(paren
id|elapsed_cycles
op_star
id|local_cpu_data-&gt;nsec_per_cyc
)paren
op_rshift
id|IA64_NSEC_PER_CYC_SHIFT
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|set_normalized_timespec
id|set_normalized_timespec
(paren
r_struct
id|timespec
op_star
id|ts
comma
id|time_t
id|sec
comma
r_int
id|nsec
)paren
(brace
r_while
c_loop
(paren
id|nsec
OG
id|NSEC_PER_SEC
)paren
(brace
id|nsec
op_sub_assign
id|NSEC_PER_SEC
suffix:semicolon
op_increment
id|sec
suffix:semicolon
)brace
r_while
c_loop
(paren
id|nsec
OL
l_int|0
)paren
(brace
id|nsec
op_add_assign
id|NSEC_PER_SEC
suffix:semicolon
op_decrement
id|sec
suffix:semicolon
)brace
id|ts-&gt;tv_sec
op_assign
id|sec
suffix:semicolon
id|ts-&gt;tv_nsec
op_assign
id|nsec
suffix:semicolon
)brace
r_void
DECL|function|do_settimeofday
id|do_settimeofday
(paren
r_struct
id|timeval
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
id|tv-&gt;tv_usec
op_star
l_int|1000
suffix:semicolon
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
(brace
multiline_comment|/*&n;&t;&t; * This is revolting. We need to set &quot;xtime&quot; correctly. However, the value&n;&t;&t; * in this location is the value at the most recent update of wall time.&n;&t;&t; * Discover what correction gettimeofday would have done, and then undo&n;&t;&t; * it!&n;&t;&t; */
id|nsec
op_sub_assign
id|gettimeoffset
c_func
(paren
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
)brace
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
)brace
r_void
DECL|function|do_gettimeofday
id|do_gettimeofday
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
comma
id|nsec
comma
id|usec
comma
id|sec
comma
id|old
comma
id|offset
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
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
(brace
id|old
op_assign
id|last_nsec_offset
suffix:semicolon
id|offset
op_assign
id|gettimeoffset
c_func
(paren
)paren
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|nsec
op_assign
id|xtime.tv_nsec
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlikely
c_func
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
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ensure that for any pair of causally ordered gettimeofday() calls, time&n;&t;&t; * never goes backwards (even when ITC on different CPUs are not perfectly&n;&t;&t; * synchronized).  (A pair of concurrent calls to gettimeofday() is by&n;&t;&t; * definition non-causal and hence it makes no sense to talk about&n;&t;&t; * time-continuity for such calls.)&n;&t;&t; *&n;&t;&t; * Doing this in a lock-free and race-free manner is tricky.  Here is why&n;&t;&t; * it works (most of the time): read_seqretry() just succeeded, which&n;&t;&t; * implies we calculated a consistent (valid) value for &quot;offset&quot;.  If the&n;&t;&t; * cmpxchg() below succeeds, we further know that last_nsec_offset still&n;&t;&t; * has the same value as at the beginning of the loop, so there was&n;&t;&t; * presumably no timer-tick or other updates to last_nsec_offset in the&n;&t;&t; * meantime.  This isn&squot;t 100% true though: there _is_ a possibility of a&n;&t;&t; * timer-tick occurring right right after read_seqretry() and then getting&n;&t;&t; * zero or more other readers which will set last_nsec_offset to the same&n;&t;&t; * value as the one we read at the beginning of the loop.  If this&n;&t;&t; * happens, we&squot;ll end up returning a slightly newer time than we ought to&n;&t;&t; * (the jump forward is at most &quot;offset&quot; nano-seconds).  There is no&n;&t;&t; * danger of causing time to go backwards, though, so we are safe in that&n;&t;&t; * sense.  We could make the probability of this unlucky case occurring&n;&t;&t; * arbitrarily small by encoding a version number in last_nsec_offset, but&n;&t;&t; * even without versioning, the probability of this unlucky case should be&n;&t;&t; * so small that we won&squot;t worry about it.&n;&t;&t; */
r_if
c_cond
(paren
id|offset
op_le
id|old
)paren
(brace
id|offset
op_assign
id|old
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|likely
c_func
(paren
id|cmpxchg
c_func
(paren
op_amp
id|last_nsec_offset
comma
id|old
comma
id|offset
)paren
op_eq
id|old
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* someone else beat us to updating last_nsec_offset; try again */
)brace
id|usec
op_assign
(paren
id|nsec
op_plus
id|offset
)paren
op_div
l_int|1000
suffix:semicolon
r_while
c_loop
(paren
id|unlikely
c_func
(paren
id|usec
op_ge
id|USEC_PER_SEC
)paren
)paren
(brace
id|usec
op_sub_assign
id|USEC_PER_SEC
suffix:semicolon
op_increment
id|sec
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
r_static
id|irqreturn_t
DECL|function|timer_interrupt
id|timer_interrupt
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
id|new_itm
suffix:semicolon
id|new_itm
op_assign
id|local_cpu_data-&gt;itm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|time_after
c_func
(paren
id|ia64_get_itc
c_func
(paren
)paren
comma
id|new_itm
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Oops: timer tick before it&squot;s due (itc=%lx,itm=%lx)&bslash;n&quot;
comma
id|ia64_get_itc
c_func
(paren
)paren
comma
id|new_itm
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Do kernel PC profiling here.  We multiply the instruction number by&n;&t;&t; * four so that we can use a prof_shift of 2 to get instruction-level&n;&t;&t; * instead of just bundle-level accuracy.&n;&t;&t; */
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
id|do_profile
c_func
(paren
id|regs-&gt;cr_iip
op_plus
l_int|4
op_star
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|new_itm
op_add_assign
id|local_cpu_data-&gt;itm_delta
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Here we are in the timer irq handler. We have irqs locally&n;&t;&t;&t; * disabled, but we don&squot;t know if the timer_bh is running on&n;&t;&t;&t; * another CPU. We need to avoid to SMP race by acquiring the&n;&t;&t;&t; * xtime_lock.&n;&t;&t;&t; */
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|local_cpu_data-&gt;itm_next
op_assign
id|new_itm
suffix:semicolon
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
r_else
id|local_cpu_data-&gt;itm_next
op_assign
id|new_itm
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|new_itm
comma
id|ia64_get_itc
c_func
(paren
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_do
(brace
multiline_comment|/*&n;&t;     * If we&squot;re too close to the next clock tick for comfort, we increase the&n;&t;     * safety margin by intentionally dropping the next tick(s).  We do NOT update&n;&t;     * itm.next because that would force us to call do_timer() which in turn would&n;&t;     * let our clock run too fast (with the potentially devastating effect of&n;&t;     * losing monotony of time).&n;&t;     */
r_while
c_loop
(paren
op_logical_neg
id|time_after
c_func
(paren
id|new_itm
comma
id|ia64_get_itc
c_func
(paren
)paren
op_plus
id|local_cpu_data-&gt;itm_delta
op_div
l_int|2
)paren
)paren
id|new_itm
op_add_assign
id|local_cpu_data-&gt;itm_delta
suffix:semicolon
id|ia64_set_itm
c_func
(paren
id|new_itm
)paren
suffix:semicolon
multiline_comment|/* double check, in case we got hit by a (slow) PMI: */
)brace
r_while
c_loop
(paren
id|time_after_eq
c_func
(paren
id|ia64_get_itc
c_func
(paren
)paren
comma
id|new_itm
)paren
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Encapsulate access to the itm structure for SMP.&n; */
r_void
DECL|function|ia64_cpu_local_tick
id|ia64_cpu_local_tick
(paren
r_void
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
r_int
r_int
id|shift
op_assign
l_int|0
comma
id|delta
suffix:semicolon
multiline_comment|/* arrange for the cycle counter to generate a timer interrupt: */
id|ia64_set_itv
c_func
(paren
id|IA64_TIMER_VECTOR
)paren
suffix:semicolon
id|delta
op_assign
id|local_cpu_data-&gt;itm_delta
suffix:semicolon
multiline_comment|/*&n;&t; * Stagger the timer tick for each CPU so they don&squot;t occur all at (almost) the&n;&t; * same time:&n;&t; */
r_if
c_cond
(paren
id|cpu
)paren
(brace
r_int
r_int
id|hi
op_assign
l_int|1UL
op_lshift
id|ia64_fls
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|shift
op_assign
(paren
l_int|2
op_star
(paren
id|cpu
op_minus
id|hi
)paren
op_plus
l_int|1
)paren
op_star
id|delta
op_div
id|hi
op_div
l_int|2
suffix:semicolon
)brace
id|local_cpu_data-&gt;itm_next
op_assign
id|ia64_get_itc
c_func
(paren
)paren
op_plus
id|delta
op_plus
id|shift
suffix:semicolon
id|ia64_set_itm
c_func
(paren
id|local_cpu_data-&gt;itm_next
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|ia64_init_itm
id|ia64_init_itm
(paren
r_void
)paren
(brace
r_int
r_int
id|platform_base_freq
comma
id|itc_freq
comma
id|drift
suffix:semicolon
r_struct
id|pal_freq_ratio
id|itc_ratio
comma
id|proc_ratio
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * According to SAL v2.6, we need to use a SAL call to determine the platform base&n;&t; * frequency and then a PAL call to determine the frequency ratio between the ITC&n;&t; * and the base frequency.&n;&t; */
id|status
op_assign
id|ia64_sal_freq_base
c_func
(paren
id|SAL_FREQ_BASE_PLATFORM
comma
op_amp
id|platform_base_freq
comma
op_amp
id|drift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SAL_FREQ_BASE_PLATFORM failed: %s&bslash;n&quot;
comma
id|ia64_sal_strerror
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|ia64_pal_freq_ratios
c_func
(paren
op_amp
id|proc_ratio
comma
l_int|0
comma
op_amp
id|itc_ratio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAL_FREQ_RATIOS failed with status=%ld&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
multiline_comment|/* invent &quot;random&quot; values */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SAL/PAL failed to obtain frequency info---inventing reasonable values&bslash;n&quot;
)paren
suffix:semicolon
id|platform_base_freq
op_assign
l_int|100000000
suffix:semicolon
id|itc_ratio.num
op_assign
l_int|3
suffix:semicolon
id|itc_ratio.den
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|platform_base_freq
OL
l_int|40000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Platform base frequency %lu bogus---resetting to 75MHz!&bslash;n&quot;
comma
id|platform_base_freq
)paren
suffix:semicolon
id|platform_base_freq
op_assign
l_int|75000000
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|proc_ratio.den
)paren
id|proc_ratio.den
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* avoid division by zero */
r_if
c_cond
(paren
op_logical_neg
id|itc_ratio.den
)paren
id|itc_ratio.den
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* avoid division by zero */
id|itc_freq
op_assign
(paren
id|platform_base_freq
op_star
id|itc_ratio.num
)paren
op_div
id|itc_ratio.den
suffix:semicolon
id|local_cpu_data-&gt;itm_delta
op_assign
(paren
id|itc_freq
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
id|KERN_INFO
l_string|&quot;CPU %d: base freq=%lu.%03luMHz, ITC ratio=%lu/%lu, &quot;
l_string|&quot;ITC freq=%lu.%03luMHz&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|platform_base_freq
op_div
l_int|1000000
comma
(paren
id|platform_base_freq
op_div
l_int|1000
)paren
op_mod
l_int|1000
comma
id|itc_ratio.num
comma
id|itc_ratio.den
comma
id|itc_freq
op_div
l_int|1000000
comma
(paren
id|itc_freq
op_div
l_int|1000
)paren
op_mod
l_int|1000
)paren
suffix:semicolon
id|local_cpu_data-&gt;proc_freq
op_assign
(paren
id|platform_base_freq
op_star
id|proc_ratio.num
)paren
op_div
id|proc_ratio.den
suffix:semicolon
id|local_cpu_data-&gt;itc_freq
op_assign
id|itc_freq
suffix:semicolon
id|local_cpu_data-&gt;cyc_per_usec
op_assign
(paren
id|itc_freq
op_plus
id|USEC_PER_SEC
op_div
l_int|2
)paren
op_div
id|USEC_PER_SEC
suffix:semicolon
id|local_cpu_data-&gt;nsec_per_cyc
op_assign
(paren
(paren
id|NSEC_PER_SEC
op_lshift
id|IA64_NSEC_PER_CYC_SHIFT
)paren
op_plus
id|itc_freq
op_div
l_int|2
)paren
op_div
id|itc_freq
suffix:semicolon
multiline_comment|/* Setup the CPU local timer tick */
id|ia64_cpu_local_tick
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|timer_irqaction
r_static
r_struct
id|irqaction
id|timer_irqaction
op_assign
(brace
dot
id|handler
op_assign
id|timer_interrupt
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|name
op_assign
l_string|&quot;timer&quot;
)brace
suffix:semicolon
r_void
id|__init
DECL|function|time_init
id|time_init
(paren
r_void
)paren
(brace
id|register_percpu_irq
c_func
(paren
id|IA64_TIMER_VECTOR
comma
op_amp
id|timer_irqaction
)paren
suffix:semicolon
id|efi_gettimeofday
c_func
(paren
op_amp
id|xtime
)paren
suffix:semicolon
id|ia64_init_itm
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize wall_to_monotonic such that adding it to xtime will yield zero, the&n;&t; * tv_nsec field must be normalized (i.e., 0 &lt;= nsec &lt; NSEC_PER_SEC).&n;&t; */
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
)brace
eof
