multiline_comment|/*&n; *  linux/arch/m32r/kernel/time.c&n; *&n; *  Copyright (c) 2001, 2002  Hiroyuki Kondo, Hirokazu Takata,&n; *                            Hitoshi Yamamoto&n; *  Taken from i386 version.&n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *    Copyright (C) 1996, 1997, 1998  Ralf Baechle&n; *&n; *  This file contains the time handling details for PC-style clocks as&n; *  found in some MIPS systems.&n; *&n; *  Some code taken from sh version.&n; *    Copyright (C) 1999  Tetsuya Okada &amp; Niibe Yutaka&n; *    Copyright (C) 2000  Philipp Rumpf &lt;prumpf@tux.org&gt;&n; */
multiline_comment|/* $Id$ */
DECL|macro|DEBUG_TIMER
macro_line|#undef  DEBUG_TIMER
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|send_IPI_allbutself
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
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
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE&t;(tick_nsec / 1000)
multiline_comment|/*&n; * Change this if you have some constant time drift&n; */
multiline_comment|/* This is for machines which generate the exact clock. */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY (1000000/HZ)
DECL|variable|latch
r_static
r_int
r_int
id|latch
suffix:semicolon
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
r_int
id|elapsed_time
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* [us] */
macro_line|#if defined(CONFIG_CHIP_M32102) || defined(CONFIG_CHIP_XNUX2) &bslash;&n;&t;|| defined(CONFIG_CHIP_VDEC2) || defined(CONFIG_CHIP_M32700) &bslash;&n;        || defined(CONFIG_CHIP_OPSP)
macro_line|#ifndef CONFIG_SMP
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|count
op_assign
id|inl
c_func
(paren
id|M32R_MFT2CUT_PORTL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inl
c_func
(paren
id|M32R_ICU_CR18_PORTL
)paren
op_amp
l_int|0x00000100
)paren
multiline_comment|/* underflow check */
id|count
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
(paren
id|latch
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|elapsed_time
op_assign
(paren
id|count
op_plus
id|latch
op_div
l_int|2
)paren
op_div
id|latch
suffix:semicolon
multiline_comment|/* NOTE: LATCH is equal to the &quot;interval&quot; value (= reload count). */
macro_line|#else /* CONFIG_SMP */
r_int
r_int
id|count
suffix:semicolon
r_static
r_int
r_int
id|p_jiffies
op_assign
op_minus
l_int|1
suffix:semicolon
r_static
r_int
r_int
id|p_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|count
op_assign
id|inl
c_func
(paren
id|M32R_MFT2CUT_PORTL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_eq
id|p_jiffies
op_logical_and
id|count
OG
id|p_count
)paren
id|count
op_assign
l_int|0
suffix:semicolon
id|p_jiffies
op_assign
id|jiffies
suffix:semicolon
id|p_count
op_assign
id|count
suffix:semicolon
id|count
op_assign
(paren
id|latch
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|elapsed_time
op_assign
(paren
id|count
op_plus
id|latch
op_div
l_int|2
)paren
op_div
id|latch
suffix:semicolon
multiline_comment|/* NOTE: LATCH is equal to the &quot;interval&quot; value (= reload count). */
macro_line|#endif /* CONFIG_SMP */
macro_line|#elif defined(CONFIG_CHIP_M32310)
macro_line|#warning do_gettimeoffse not implemented
macro_line|#else
macro_line|#error no chip configuration
macro_line|#endif
r_return
id|elapsed_time
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
id|max_ntp_tick
op_assign
id|tick_usec
op_minus
id|tickadj
suffix:semicolon
r_do
(brace
r_int
r_int
id|lost
suffix:semicolon
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
multiline_comment|/*&n;&t;&t; * If time_adjust is negative then NTP is slowing the clock&n;&t;&t; * so make sure not to go into next possible interval.&n;&t;&t; * Better to lose some accuracy than have time go backwards..&n;&t;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|time_adjust
OL
l_int|0
)paren
)paren
(brace
id|usec
op_assign
id|min
c_func
(paren
id|usec
comma
id|max_ntp_tick
)paren
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
id|max_ntp_tick
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|lost
)paren
)paren
id|usec
op_add_assign
id|lost
op_star
id|tick_usec
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
multiline_comment|/*&n;         * This is revolting. We need to set &quot;xtime&quot; correctly. However, the&n;         * value in this location is the value at the most recent update of&n;         * wall time.  Discover what correction gettimeofday() would have&n;         * made, and then undo it!&n;         */
id|nsec
op_sub_assign
id|do_gettimeoffset
c_func
(paren
)paren
op_star
id|NSEC_PER_USEC
suffix:semicolon
id|nsec
op_sub_assign
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_star
id|TICK_NSEC
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
multiline_comment|/*&n; * In order to set the CMOS clock precisely, set_rtc_mmss has to be&n; * called 500 ms after the second nowtime has started, because when&n; * nowtime is written into the registers of the CMOS clock, it will&n; * jump to the next second precisely 500 ms later. Check the Motorola&n; * MC146818A or Dallas DS12887 data sheet for details.&n; *&n; * BUG: This routine does not handle hour overflow properly; it just&n; *      sets the minutes. Usually you won&squot;t notice until after reboot!&n; */
DECL|function|set_rtc_mmss
r_static
id|__inline__
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* last time the cmos clock got updated */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|function|do_timer_interrupt
r_static
id|__inline__
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
multiline_comment|/* do it again in 60 s */
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
)brace
multiline_comment|/* As we return to user mode fire off the other CPU schedulers..&n;&t;   this is basically because we don&squot;t yet share IRQ&squot;s around.&n;&t;   This message is rigged to be safe on the 386 - basically it&squot;s&n;&t;   a hack, so don&squot;t look closely for now.. */
macro_line|#ifdef CONFIG_SMP
id|smp_local_timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|timer_interrupt
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
macro_line|#ifndef CONFIG_SMP
id|m32r_do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|irq0
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
l_string|&quot;MFT2&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
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
id|epoch
comma
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
id|sec
op_assign
id|min
op_assign
id|hour
op_assign
id|day
op_assign
id|mon
op_assign
id|year
op_assign
l_int|0
suffix:semicolon
id|epoch
op_assign
l_int|0
suffix:semicolon
id|year
op_assign
l_int|23
suffix:semicolon
id|mon
op_assign
l_int|4
suffix:semicolon
id|day
op_assign
l_int|17
suffix:semicolon
multiline_comment|/* Attempt to guess the epoch.  This is the same heuristic as in rtc.c&n;&t;   so no stupid things will happen to timekeeping.  Who knows, maybe&n;&t;   Ultrix also uses 1952 as epoch ...  */
r_if
c_cond
(paren
id|year
OG
l_int|10
op_logical_and
id|year
OL
l_int|44
)paren
id|epoch
op_assign
l_int|1980
suffix:semicolon
r_else
r_if
c_cond
(paren
id|year
OL
l_int|96
)paren
id|epoch
op_assign
l_int|1952
suffix:semicolon
id|year
op_add_assign
id|epoch
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
(paren
id|INITIAL_JIFFIES
op_mod
id|HZ
)paren
op_star
(paren
id|NSEC_PER_SEC
op_div
id|HZ
)paren
suffix:semicolon
id|wall_to_monotonic.tv_sec
op_assign
op_minus
id|xtime.tv_sec
suffix:semicolon
id|wall_to_monotonic.tv_nsec
op_assign
op_minus
id|xtime.tv_nsec
suffix:semicolon
macro_line|#if defined(CONFIG_CHIP_M32102) || defined(CONFIG_CHIP_XNUX2) &bslash;&n;&t;|| defined(CONFIG_CHIP_VDEC2) || defined(CONFIG_CHIP_M32700) &bslash;&n;        || defined(CONFIG_CHIP_OPSP)
multiline_comment|/* M32102 MFT setup */
id|setup_irq
c_func
(paren
id|M32R_IRQ_MFT2
comma
op_amp
id|irq0
)paren
suffix:semicolon
(brace
r_int
r_int
id|bus_clock
suffix:semicolon
r_int
r_int
id|divide
suffix:semicolon
id|bus_clock
op_assign
id|boot_cpu_data.bus_clock
suffix:semicolon
id|divide
op_assign
id|boot_cpu_data.timer_divide
suffix:semicolon
id|latch
op_assign
(paren
id|bus_clock
op_div
id|divide
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
l_string|&quot;Timer start : latch = %ld&bslash;n&quot;
comma
id|latch
)paren
suffix:semicolon
id|outl
c_func
(paren
(paren
id|M32R_MFTMOD_CC_MASK
op_or
id|M32R_MFTMOD_TCCR
"&bslash;"
op_or
id|M32R_MFTMOD_CSSEL011
)paren
comma
id|M32R_MFT2MOD_PORTL
)paren
suffix:semicolon
id|outl
c_func
(paren
id|latch
comma
id|M32R_MFT2RLD_PORTL
)paren
suffix:semicolon
id|outl
c_func
(paren
id|latch
comma
id|M32R_MFT2CUT_PORTL
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0
comma
id|M32R_MFT2CMPRLD_PORTL
)paren
suffix:semicolon
id|outl
c_func
(paren
(paren
id|M32R_MFTCR_MFT2MSK
op_or
id|M32R_MFTCR_MFT2EN
)paren
comma
id|M32R_MFTCR_PORTL
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_CHIP_M32310)
macro_line|#warning time_init not implemented
macro_line|#else
macro_line|#error no chip configuration
macro_line|#endif
)brace
multiline_comment|/*&n; *  Scheduler clock - returns current time in nanosec units.&n; */
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
