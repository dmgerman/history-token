multiline_comment|/*&n; *  linux/arch/arm26/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *  Modifications for ARM (C) 1994-2001 Russell King&n; *  Mods for ARM26 (C) 2003 Ian Molton&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains the ARM-specific time handling details:&n; *  reading the RTC at bootup, etc...&n; *&n; *  1994-07-02  Alan Modra&n; *              fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; *  1998-12-20  Updated NTP code according to technical memorandum Jan &squot;96&n; *              &quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ioc.h&gt;
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
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
multiline_comment|/* this needs a better home */
DECL|variable|rtc_lock
id|spinlock_t
id|rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* change this if you have some constant time drift */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY&t;(1000000/HZ)
DECL|function|dummy_set_rtc
r_static
r_int
id|dummy_set_rtc
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hook for setting the RTC&squot;s idea of the current time.&n; */
DECL|variable|set_rtc
r_int
(paren
op_star
id|set_rtc
)paren
(paren
r_void
)paren
op_assign
id|dummy_set_rtc
suffix:semicolon
multiline_comment|/*&n; * Get time offset based on IOCs timer.&n; * FIXME - if this is called with interrutps off, why the shennanigans&n; * below ?&n; */
DECL|function|gettimeoffset
r_static
r_int
r_int
id|gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|count1
comma
id|count2
comma
id|status
suffix:semicolon
r_int
id|offset
suffix:semicolon
id|ioc_writeb
(paren
l_int|0
comma
id|IOC_T0LATCH
)paren
suffix:semicolon
id|barrier
(paren
)paren
suffix:semicolon
id|count1
op_assign
id|ioc_readb
c_func
(paren
id|IOC_T0CNTL
)paren
op_or
(paren
id|ioc_readb
c_func
(paren
id|IOC_T0CNTH
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|barrier
(paren
)paren
suffix:semicolon
id|status
op_assign
id|ioc_readb
c_func
(paren
id|IOC_IRQREQA
)paren
suffix:semicolon
id|barrier
(paren
)paren
suffix:semicolon
id|ioc_writeb
(paren
l_int|0
comma
id|IOC_T0LATCH
)paren
suffix:semicolon
id|barrier
(paren
)paren
suffix:semicolon
id|count2
op_assign
id|ioc_readb
c_func
(paren
id|IOC_T0CNTL
)paren
op_or
(paren
id|ioc_readb
c_func
(paren
id|IOC_T0CNTH
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|offset
op_assign
id|count2
suffix:semicolon
r_if
c_cond
(paren
id|count2
OL
id|count1
)paren
(brace
multiline_comment|/*&n;                 * We have not had an interrupt between reading count1&n;                 * and count2.&n;                 */
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
id|offset
op_sub_assign
id|LATCH
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|count2
OG
id|count1
)paren
(brace
multiline_comment|/*&n;                 * We have just had another interrupt between reading&n;                 * count1 and count2.&n;                 */
id|offset
op_sub_assign
id|LATCH
suffix:semicolon
)brace
id|offset
op_assign
(paren
id|LATCH
op_minus
id|offset
)paren
op_star
(paren
id|tick_nsec
op_div
l_int|1000
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|LATCH
op_div
l_int|2
)paren
op_div
id|LATCH
suffix:semicolon
)brace
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
DECL|variable|next_rtc_update
r_static
r_int
r_int
id|next_rtc_update
suffix:semicolon
multiline_comment|/*&n; * If we have an externally synchronized linux clock, then update&n; * CMOS clock accordingly every ~11 minutes.  set_rtc() has to be&n; * called as close as possible to 500 ms before the new second&n; * starts.&n; */
DECL|function|do_set_rtc
r_static
r_inline
r_void
id|do_set_rtc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|time_status
op_amp
id|STA_UNSYNC
op_logical_or
id|set_rtc
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
singleline_comment|//FIXME - timespec.tv_sec is a time_t not unsigned long
r_if
c_cond
(paren
id|next_rtc_update
op_logical_and
id|time_before
c_func
(paren
(paren
r_int
r_int
)paren
id|xtime.tv_sec
comma
id|next_rtc_update
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|xtime.tv_nsec
OL
l_int|500000000
op_minus
(paren
(paren
r_int
)paren
id|tick_nsec
op_rshift
l_int|1
)paren
op_logical_and
id|xtime.tv_nsec
op_ge
l_int|500000000
op_plus
(paren
(paren
r_int
)paren
id|tick_nsec
op_rshift
l_int|1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|set_rtc
c_func
(paren
)paren
)paren
multiline_comment|/*&n;&t;&t; * rtc update failed.  Try again in 60s&n;&t;&t; */
id|next_rtc_update
op_assign
id|xtime.tv_sec
op_plus
l_int|60
suffix:semicolon
r_else
id|next_rtc_update
op_assign
id|xtime.tv_sec
op_plus
l_int|660
suffix:semicolon
)brace
DECL|macro|do_leds
mdefine_line|#define do_leds()
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
id|gettimeoffset
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
id|USECS_PER_JIFFY
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
multiline_comment|/* usec may have gone up a lot: be safe */
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
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is revolting. We need to set &quot;xtime&quot; correctly. However, the&n;&t; * value in this location is the value at the most recent update of&n;&t; * wall time.  Discover what correction gettimeofday() would have&n;&t; * done, and then undo it!&n;&t; */
id|tv-&gt;tv_nsec
op_sub_assign
l_int|1000
op_star
(paren
id|gettimeoffset
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
id|USECS_PER_JIFFY
)paren
suffix:semicolon
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
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
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
macro_line|#endif
id|do_set_rtc
c_func
(paren
)paren
suffix:semicolon
singleline_comment|//FIME - EVERY timer IRQ?
id|profile_tick
c_func
(paren
id|CPU_PROFILING
comma
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
singleline_comment|//FIXME - is this right?
)brace
DECL|variable|timer_irq
r_static
r_struct
id|irqaction
id|timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;timer&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|timer_interrupt
comma
)brace
suffix:semicolon
r_extern
r_void
id|ioctime_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Set up timer interrupt.&n; */
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
id|ioc_writeb
c_func
(paren
id|LATCH
op_amp
l_int|255
comma
id|IOC_T0LTCHL
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
id|IOC_T0LTCHH
)paren
suffix:semicolon
id|ioc_writeb
c_func
(paren
l_int|0
comma
id|IOC_T0GO
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_TIMER
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
)brace
eof
