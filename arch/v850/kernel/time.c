multiline_comment|/*&n; * linux/arch/v850/kernel/time.c -- Arch-dependent timer functions&n; *&n; *  Copyright (C) 1991, 1992, 1995, 2001, 2002  Linus Torvalds&n; *&n; * This file contains the v850-specific time handling details.&n; * Most of the stuff is located in the machine specific files.&n; *&n; * 1997-09-10&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/config.h&gt; /* CONFIG_HEARTBEAT */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;mach.h&quot;
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE&t;(tick_nsec / 1000)
DECL|function|do_profile
r_static
r_inline
r_void
id|do_profile
(paren
r_int
r_int
id|pc
)paren
(brace
r_if
c_cond
(paren
id|prof_buffer
op_logical_and
id|current-&gt;pid
)paren
(brace
r_extern
r_int
id|_stext
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
r_if
c_cond
(paren
id|pc
OL
id|prof_len
)paren
op_increment
id|prof_buffer
(braket
id|pc
)braket
suffix:semicolon
r_else
multiline_comment|/*&n;&t;&t; * Don&squot;t ignore out-of-bounds PC values silently,&n;&t;&t; * put them into the last histogram slot, so if&n;&t;&t; * present, they will show up as a sharp peak.&n;&t;&t; */
op_increment
id|prof_buffer
(braket
id|prof_len
op_minus
l_int|1
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|function|timer_interrupt
r_static
r_void
id|timer_interrupt
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if 0
multiline_comment|/* last time the cmos clock got updated */
r_static
r_int
id|last_rtc_update
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* may need to kick the hardware timer */
r_if
c_cond
(paren
id|mach_tick
)paren
id|mach_tick
(paren
)paren
suffix:semicolon
id|do_timer
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
(paren
id|regs
)paren
)paren
id|do_profile
(paren
id|regs-&gt;pc
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; * If we have an externally synchronized Linux clock, then update&n;&t; * CMOS clock accordingly every ~11 minutes. Set_rtc_mmss() has to be&n;&t; * called as close as possible to 500 ms before the new second starts.&n;&t; */
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
id|set_rtc_mmss
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
macro_line|#ifdef CONFIG_HEARTBEAT
multiline_comment|/* use power LED as a heartbeat instead -- much more useful&n;&t;   for debugging -- based on the version for PReP by Cort */
multiline_comment|/* acts like an actual heart beat -- ie thump-thump-pause... */
r_if
c_cond
(paren
id|mach_heartbeat
)paren
(brace
r_static
r_int
id|cnt
op_assign
l_int|0
comma
id|period
op_assign
l_int|0
comma
id|dist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_eq
l_int|0
op_logical_or
id|cnt
op_eq
id|dist
)paren
id|mach_heartbeat
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cnt
op_eq
l_int|7
op_logical_or
id|cnt
op_eq
id|dist
op_plus
l_int|7
)paren
id|mach_heartbeat
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cnt
OG
id|period
)paren
(brace
id|cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The hyperbolic function below modifies the heartbeat period&n;&t;&t; * length in dependency of the current (5min) load. It goes&n;&t;&t; * through the points f(0)=126, f(1)=86, f(5)=51,&n;&t;&t; * f(inf)-&gt;30. */
id|period
op_assign
(paren
(paren
l_int|672
op_lshift
id|FSHIFT
)paren
op_div
(paren
l_int|5
op_star
id|avenrun
(braket
l_int|0
)braket
op_plus
(paren
l_int|7
op_lshift
id|FSHIFT
)paren
)paren
)paren
op_plus
l_int|30
suffix:semicolon
id|dist
op_assign
id|period
op_div
l_int|4
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_HEARTBEAT */
macro_line|#endif /* 0 */
)brace
multiline_comment|/*&n; * This version of gettimeofday has near microsecond resolution.&n; */
DECL|function|do_gettimeofday
r_void
id|do_gettimeofday
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
macro_line|#if 0 /* DAVIDM later if possible */
r_extern
r_volatile
r_int
r_int
id|lost_ticks
suffix:semicolon
r_int
r_int
id|lost
suffix:semicolon
macro_line|#endif
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|usec
comma
id|sec
suffix:semicolon
r_int
r_int
id|seq
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
macro_line|#if 0
id|usec
op_assign
id|mach_gettimeoffset
ques
c_cond
id|mach_gettimeoffset
(paren
)paren
suffix:colon
l_int|0
suffix:semicolon
macro_line|#else
id|usec
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if 0 /* DAVIDM later if possible */
id|lost
op_assign
id|lost_ticks
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
macro_line|#endif
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
DECL|function|do_settimeofday
r_void
id|do_settimeofday
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
id|write_seqlock_irq
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* This is revolting. We need to set the xtime.tv_nsec&n;&t; * correctly. However, the value in this location is&n;&t; * is value at the last tick.&n;&t; * Discover what correction gettimeofday&n;&t; * would have done, and then undo it!&n;&t; */
macro_line|#if 0
id|tv-&gt;tv_usec
op_sub_assign
id|mach_gettimeoffset
(paren
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|tv-&gt;tv_usec
OL
l_int|0
)paren
(brace
id|tv-&gt;tv_usec
op_add_assign
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_sec
op_decrement
suffix:semicolon
)brace
id|xtime.tv_sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|xtime.tv_nsec
op_assign
id|tv-&gt;tv_usec
op_star
l_int|1000
suffix:semicolon
id|time_adjust
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* stop active adjtime () */
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
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
DECL|variable|timer_dev_id
r_static
r_int
id|timer_dev_id
suffix:semicolon
DECL|variable|timer_irqaction
r_static
r_struct
id|irqaction
id|timer_irqaction
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
op_amp
id|timer_dev_id
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|time_init
r_void
id|time_init
(paren
r_void
)paren
(brace
id|mach_gettimeofday
(paren
op_amp
id|xtime
)paren
suffix:semicolon
id|mach_sched_init
(paren
op_amp
id|timer_irqaction
)paren
suffix:semicolon
)brace
eof
