multiline_comment|/*&n; *  linux/arch/m68k/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *&n; * This file contains the m68k-specific time handling details.&n; * Most of the stuff is located in the machine specific files.&n; *&n; * 1997-09-10&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/config.h&gt; /* CONFIG_HEARTBEAT */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
DECL|function|set_rtc_mmss
r_static
r_inline
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_if
c_cond
(paren
id|mach_set_clock_mmss
)paren
r_return
id|mach_set_clock_mmss
(paren
id|nowtime
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
c_func
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
id|do_profile
c_func
(paren
id|regs-&gt;pc
)paren
suffix:semicolon
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
c_func
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
c_func
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
)brace
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|rtc_time
id|time
suffix:semicolon
r_if
c_cond
(paren
id|mach_hwclk
)paren
(brace
id|mach_hwclk
c_func
(paren
l_int|0
comma
op_amp
id|time
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|time.tm_year
op_add_assign
l_int|1900
)paren
OL
l_int|1970
)paren
id|time.tm_year
op_add_assign
l_int|100
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|time.tm_year
comma
id|time.tm_mon
comma
id|time.tm_mday
comma
id|time.tm_hour
comma
id|time.tm_min
comma
id|time.tm_sec
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
id|mach_sched_init
c_func
(paren
id|timer_interrupt
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This version of gettimeofday has near microsecond resolution.&n; */
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
r_extern
r_int
r_int
id|wall_jiffies
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
comma
id|lost
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
id|usec
op_assign
id|mach_gettimeoffset
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
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* This is revolting. We need to set the xtime.tv_nsec&n;&t; * correctly. However, the value in this location is&n;&t; * is value at the last tick.&n;&t; * Discover what correction gettimeofday&n;&t; * would have done, and then undo it!&n;&t; */
id|tv-&gt;tv_usec
op_sub_assign
id|mach_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
id|tv-&gt;tv_usec
op_sub_assign
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
suffix:semicolon
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
)brace
eof
