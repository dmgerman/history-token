multiline_comment|/*&n; *  linux/arch/h8300/kernel/time.c&n; *&n; *  Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; *  Copied/hacked from:&n; *&n; *  linux/arch/m68k/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *&n; * This file contains the m68k-specific time handling details.&n; * Most of the stuff is located in the machine specific files.&n; *&n; * 1997-09-10&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/config.h&gt; /* CONFIG_HEARTBEAT */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/target_time.h&gt;
DECL|macro|TICK_SIZE
mdefine_line|#define&t;TICK_SIZE (tick_nsec / 1000)
DECL|variable|jiffies_64
id|u64
id|jiffies_64
suffix:semicolon
DECL|variable|jiffies_64
id|EXPORT_SYMBOL
c_func
(paren
id|jiffies_64
)paren
suffix:semicolon
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
multiline_comment|/* may need to kick the hardware timer */
id|platform_timer_eoi
c_func
(paren
)paren
suffix:semicolon
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
)brace
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
multiline_comment|/* FIX by dqg : Set to zero for platforms that don&squot;t have tod */
multiline_comment|/* without this time is undefined and can overflow time_t, causing  */
multiline_comment|/* very stange errors */
id|year
op_assign
l_int|1980
suffix:semicolon
id|mon
op_assign
id|day
op_assign
l_int|1
suffix:semicolon
id|hour
op_assign
id|min
op_assign
id|sec
op_assign
l_int|0
suffix:semicolon
id|platform_gettod
(paren
op_amp
id|year
comma
op_amp
id|mon
comma
op_amp
id|day
comma
op_amp
id|hour
comma
op_amp
id|min
comma
op_amp
id|sec
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|year
op_add_assign
l_int|1900
)paren
OL
l_int|1970
)paren
id|year
op_add_assign
l_int|100
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|platform_timer_setup
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
r_int
r_int
id|usec
comma
id|sec
suffix:semicolon
id|read_lock_irqsave
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
l_int|0
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_add_assign
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
suffix:semicolon
id|read_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
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
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* This is revolting. We need to set the xtime.tv_usec&n;&t; * correctly. However, the value in this location is&n;&t; * is value at the last tick.&n;&t; * Discover what correction gettimeofday&n;&t; * would have done, and then undo it!&n;&t; */
r_while
c_loop
(paren
id|tv-&gt;tv_nsec
OL
l_int|0
)paren
(brace
id|tv-&gt;tv_nsec
op_add_assign
id|NSEC_PER_SEC
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
id|tv-&gt;tv_nsec
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
eof
