multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; * Copyright (c) 2003  Maciej W. Rozycki&n; *&n; * Common time service routines for MIPS machines. See&n; * Documentation/mips/time.README.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/cpu-features.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/time.h&gt;
multiline_comment|/*&n; * The integer part of the number of usecs per jiffy is taken from tick,&n; * but the fractional part is not recorded, so we calculate it using the&n; * initial value of HZ.  This aids systems where tick isn&squot;t really an&n; * integer (e.g. for HZ = 128).&n; */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY&t;&t;TICK_SIZE
DECL|macro|USECS_PER_JIFFY_FRAC
mdefine_line|#define USECS_PER_JIFFY_FRAC&t;((unsigned long)(u32)((1000000ULL &lt;&lt; 32) / HZ))
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE&t;(tick_nsec / 1000)
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
multiline_comment|/*&n; * forward reference&n; */
r_extern
r_volatile
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|variable|rtc_lock
id|spinlock_t
id|rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * whether we emulate local_timer_interrupts for SMP machines.&n; */
DECL|variable|emulate_local_timer_interrupt
r_int
id|emulate_local_timer_interrupt
suffix:semicolon
multiline_comment|/*&n; * By default we provide the null RTC ops&n; */
DECL|function|null_rtc_get_time
r_static
r_int
r_int
id|null_rtc_get_time
c_func
(paren
r_void
)paren
(brace
r_return
id|mktime
c_func
(paren
l_int|2000
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|null_rtc_set_time
r_static
r_int
id|null_rtc_set_time
c_func
(paren
r_int
r_int
id|sec
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rtc_get_time
r_int
r_int
(paren
op_star
id|rtc_get_time
)paren
(paren
r_void
)paren
op_assign
id|null_rtc_get_time
suffix:semicolon
DECL|variable|rtc_set_time
r_int
(paren
op_star
id|rtc_set_time
)paren
(paren
r_int
r_int
)paren
op_assign
id|null_rtc_set_time
suffix:semicolon
DECL|variable|rtc_set_mmss
r_int
(paren
op_star
id|rtc_set_mmss
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* usecs per counter cycle, shifted to left by 32 bits */
DECL|variable|sll32_usecs_per_cycle
r_static
r_int
r_int
id|sll32_usecs_per_cycle
suffix:semicolon
multiline_comment|/* how many counter cycles in a jiffy */
DECL|variable|cycles_per_jiffy
r_static
r_int
r_int
id|cycles_per_jiffy
suffix:semicolon
multiline_comment|/* Cycle counter value at the previous timer interrupt.. */
DECL|variable|timerhi
DECL|variable|timerlo
r_static
r_int
r_int
id|timerhi
comma
id|timerlo
suffix:semicolon
multiline_comment|/* expirelo is the count value for next CPU timer interrupt */
DECL|variable|expirelo
r_static
r_int
r_int
id|expirelo
suffix:semicolon
multiline_comment|/*&n; * Null timer ack for systems not needing one (e.g. i8254).&n; */
DECL|function|null_timer_ack
r_static
r_void
id|null_timer_ack
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* nothing */
)brace
multiline_comment|/*&n; * Null high precision timer functions for systems lacking one.&n; */
DECL|function|null_hpt_read
r_static
r_int
r_int
id|null_hpt_read
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|null_hpt_init
r_static
r_void
id|null_hpt_init
c_func
(paren
r_int
r_int
id|count
)paren
(brace
multiline_comment|/* nothing */
)brace
multiline_comment|/*&n; * Timer ack for an R4k-compatible timer of a known frequency.&n; */
DECL|function|c0_timer_ack
r_static
r_void
id|c0_timer_ack
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* Ack this timer interrupt and set the next one.  */
id|expirelo
op_add_assign
id|cycles_per_jiffy
suffix:semicolon
id|write_c0_compare
c_func
(paren
id|expirelo
)paren
suffix:semicolon
multiline_comment|/* Check to see if we have missed any timer interrupts.  */
id|count
op_assign
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
op_minus
id|expirelo
)paren
OL
l_int|0x7fffffff
)paren
(brace
multiline_comment|/* missed_timer_count++; */
id|expirelo
op_assign
id|count
op_plus
id|cycles_per_jiffy
suffix:semicolon
id|write_c0_compare
c_func
(paren
id|expirelo
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * High precision timer functions for a R4k-compatible timer.&n; */
DECL|function|c0_hpt_read
r_static
r_int
r_int
id|c0_hpt_read
c_func
(paren
r_void
)paren
(brace
r_return
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* For use solely as a high precision timer.  */
DECL|function|c0_hpt_init
r_static
r_void
id|c0_hpt_init
c_func
(paren
r_int
r_int
id|count
)paren
(brace
id|write_c0_count
c_func
(paren
id|read_c0_count
c_func
(paren
)paren
op_minus
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* For use both as a high precision timer and an interrupt source.  */
DECL|function|c0_hpt_timer_init
r_static
r_void
id|c0_hpt_timer_init
c_func
(paren
r_int
r_int
id|count
)paren
(brace
id|count
op_assign
id|read_c0_count
c_func
(paren
)paren
op_minus
id|count
suffix:semicolon
id|expirelo
op_assign
(paren
id|count
op_div
id|cycles_per_jiffy
op_plus
l_int|1
)paren
op_star
id|cycles_per_jiffy
suffix:semicolon
id|write_c0_count
c_func
(paren
id|expirelo
op_minus
id|cycles_per_jiffy
)paren
suffix:semicolon
id|write_c0_compare
c_func
(paren
id|expirelo
)paren
suffix:semicolon
id|write_c0_count
c_func
(paren
id|count
)paren
suffix:semicolon
)brace
DECL|variable|mips_timer_state
r_int
(paren
op_star
id|mips_timer_state
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|mips_timer_ack
r_void
(paren
op_star
id|mips_timer_ack
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|mips_hpt_read
r_int
r_int
(paren
op_star
id|mips_hpt_read
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|mips_hpt_init
r_void
(paren
op_star
id|mips_hpt_init
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * This version of gettimeofday has microsecond resolution and better than&n; * microsecond precision on fast machines with cycle counter.&n; */
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
id|lost
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
multiline_comment|/*&n;&t; * This is revolting.  We need to set &quot;xtime&quot; correctly.  However,&n;&t; * the value in this location is the value at the most recent update&n;&t; * of wall time.  Discover what correction gettimeofday() would have&n;&t; * made, and then undo it!&n;&t; */
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
id|tick_nsec
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
multiline_comment|/*&n; * Gettimeoffset routines.  These routines returns the time duration&n; * since last timer interrupt in usecs.&n; *&n; * If the exact CPU counter frequency is known, use fixed_rate_gettimeoffset.&n; * Otherwise use calibrate_gettimeoffset()&n; *&n; * If the CPU does not have the counter register, you can either supply&n; * your own gettimeoffset() routine, or use null_gettimeoffset(), which&n; * gives the same resolution as HZ.&n; */
DECL|function|null_gettimeoffset
r_static
r_int
r_int
id|null_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The function pointer to one of the gettimeoffset funcs.  */
DECL|variable|do_gettimeoffset
r_int
r_int
(paren
op_star
id|do_gettimeoffset
)paren
(paren
r_void
)paren
op_assign
id|null_gettimeoffset
suffix:semicolon
DECL|function|fixed_rate_gettimeoffset
r_static
r_int
r_int
id|fixed_rate_gettimeoffset
c_func
(paren
r_void
)paren
(brace
id|u32
id|count
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
multiline_comment|/* Get last timer tick in absolute kernel time */
id|count
op_assign
id|mips_hpt_read
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy (32 bits is enough) */
id|count
op_sub_assign
id|timerlo
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;multu&t;%1,%2&quot;
suffix:colon
l_string|&quot;=h&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|count
)paren
comma
l_string|&quot;r&quot;
(paren
id|sll32_usecs_per_cycle
)paren
suffix:colon
l_string|&quot;lo&quot;
comma
l_string|&quot;accum&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Due to possible jiffies inconsistencies, we need to check&n;&t; * the result so that we&squot;ll get a timer that is monotonic.&n;&t; */
r_if
c_cond
(paren
id|res
op_ge
id|USECS_PER_JIFFY
)paren
id|res
op_assign
id|USECS_PER_JIFFY
op_minus
l_int|1
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Cached &quot;1/(clocks per usec) * 2^32&quot; value.&n; * It has to be recalculated once each jiffy.&n; */
DECL|variable|cached_quotient
r_static
r_int
r_int
id|cached_quotient
suffix:semicolon
multiline_comment|/* Last jiffy when calibrate_divXX_gettimeoffset() was called. */
DECL|variable|last_jiffies
r_static
r_int
r_int
id|last_jiffies
suffix:semicolon
multiline_comment|/*&n; * This is moved from dec/time.c:do_ioasic_gettimeoffset() by Maciej.&n; */
DECL|function|calibrate_div32_gettimeoffset
r_static
r_int
r_int
id|calibrate_div32_gettimeoffset
c_func
(paren
r_void
)paren
(brace
id|u32
id|count
suffix:semicolon
r_int
r_int
id|res
comma
id|tmp
suffix:semicolon
r_int
r_int
id|quotient
suffix:semicolon
id|tmp
op_assign
id|jiffies
suffix:semicolon
id|quotient
op_assign
id|cached_quotient
suffix:semicolon
r_if
c_cond
(paren
id|last_jiffies
op_ne
id|tmp
)paren
(brace
id|last_jiffies
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|last_jiffies
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|r0
suffix:semicolon
id|do_div64_32
c_func
(paren
id|r0
comma
id|timerhi
comma
id|timerlo
comma
id|tmp
)paren
suffix:semicolon
id|do_div64_32
c_func
(paren
id|quotient
comma
id|USECS_PER_JIFFY
comma
id|USECS_PER_JIFFY_FRAC
comma
id|r0
)paren
suffix:semicolon
id|cached_quotient
op_assign
id|quotient
suffix:semicolon
)brace
)brace
multiline_comment|/* Get last timer tick in absolute kernel time */
id|count
op_assign
id|mips_hpt_read
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy (32 bits is enough) */
id|count
op_sub_assign
id|timerlo
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;multu  %1,%2&quot;
suffix:colon
l_string|&quot;=h&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|count
)paren
comma
l_string|&quot;r&quot;
(paren
id|quotient
)paren
suffix:colon
l_string|&quot;lo&quot;
comma
l_string|&quot;accum&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Due to possible jiffies inconsistencies, we need to check&n;&t; * the result so that we&squot;ll get a timer that is monotonic.&n;&t; */
r_if
c_cond
(paren
id|res
op_ge
id|USECS_PER_JIFFY
)paren
id|res
op_assign
id|USECS_PER_JIFFY
op_minus
l_int|1
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|calibrate_div64_gettimeoffset
r_static
r_int
r_int
id|calibrate_div64_gettimeoffset
c_func
(paren
r_void
)paren
(brace
id|u32
id|count
suffix:semicolon
r_int
r_int
id|res
comma
id|tmp
suffix:semicolon
r_int
r_int
id|quotient
suffix:semicolon
id|tmp
op_assign
id|jiffies
suffix:semicolon
id|quotient
op_assign
id|cached_quotient
suffix:semicolon
r_if
c_cond
(paren
id|last_jiffies
op_ne
id|tmp
)paren
(brace
id|last_jiffies
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|last_jiffies
)paren
(brace
r_int
r_int
id|r0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.set&t;push&bslash;n&bslash;t&quot;
l_string|&quot;.set&t;mips3&bslash;n&bslash;t&quot;
l_string|&quot;lwu&t;%0,%3&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&t;%1,%2,0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%1,%1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ddivu&t;$0,%1,%4&bslash;n&bslash;t&quot;
l_string|&quot;mflo&t;%1&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&t;%0,%5,0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%0,%0,%6&bslash;n&bslash;t&quot;
l_string|&quot;ddivu&t;$0,%0,%1&bslash;n&bslash;t&quot;
l_string|&quot;mflo&t;%0&bslash;n&bslash;t&quot;
l_string|&quot;.set&t;pop&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|quotient
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|r0
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|timerhi
)paren
comma
l_string|&quot;m&quot;
(paren
id|timerlo
)paren
comma
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;r&quot;
(paren
id|USECS_PER_JIFFY
)paren
comma
l_string|&quot;r&quot;
(paren
id|USECS_PER_JIFFY_FRAC
)paren
suffix:colon
l_string|&quot;hi&quot;
comma
l_string|&quot;lo&quot;
comma
l_string|&quot;accum&quot;
)paren
suffix:semicolon
id|cached_quotient
op_assign
id|quotient
suffix:semicolon
)brace
)brace
multiline_comment|/* Get last timer tick in absolute kernel time */
id|count
op_assign
id|mips_hpt_read
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy (32 bits is enough) */
id|count
op_sub_assign
id|timerlo
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;multu&t;%1,%2&quot;
suffix:colon
l_string|&quot;=h&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|count
)paren
comma
l_string|&quot;r&quot;
(paren
id|quotient
)paren
suffix:colon
l_string|&quot;lo&quot;
comma
l_string|&quot;accum&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Due to possible jiffies inconsistencies, we need to check&n;&t; * the result so that we&squot;ll get a timer that is monotonic.&n;&t; */
r_if
c_cond
(paren
id|res
op_ge
id|USECS_PER_JIFFY
)paren
id|res
op_assign
id|USECS_PER_JIFFY
op_minus
l_int|1
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* last time when xtime and rtc are sync&squot;ed up */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
suffix:semicolon
multiline_comment|/*&n; * local_timer_interrupt() does profiling and process accounting&n; * on a per-CPU basis.&n; *&n; * In UP mode, it is invoked from the (global) timer_interrupt.&n; *&n; * In SMP mode, it might invoked by per-CPU timer interrupt, or&n; * a broadcasted inter-processor interrupt which itself is triggered&n; * by the global timer interrupt.&n; */
DECL|function|local_timer_interrupt
r_void
id|local_timer_interrupt
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
r_if
c_cond
(paren
id|current-&gt;pid
)paren
id|profile_tick
c_func
(paren
id|CPU_PROFILING
comma
id|regs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* in UP mode, update_process_times() is invoked by do_timer() */
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
)brace
multiline_comment|/*&n; * High-level timer interrupt service routines.  This function&n; * is set as irqaction-&gt;handler and is invoked through do_IRQ.&n; */
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
r_int
r_int
id|j
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|count
op_assign
id|mips_hpt_read
c_func
(paren
)paren
suffix:semicolon
id|mips_timer_ack
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Update timerhi/timerlo for intra-jiffy calibration. */
id|timerhi
op_add_assign
id|count
OL
id|timerlo
suffix:semicolon
multiline_comment|/* Wrap around */
id|timerlo
op_assign
id|count
suffix:semicolon
multiline_comment|/*&n;&t; * call the generic timer interrupt handling&n;&t; */
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we have an externally synchronized Linux clock, then update&n;&t; * CMOS clock accordingly every ~11 minutes. rtc_set_time() has to be&n;&t; * called as close as possible to 500 ms before the new second starts.&n;&t; */
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
id|rtc_set_mmss
c_func
(paren
id|xtime.tv_sec
)paren
op_eq
l_int|0
)paren
(brace
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* do it again in 60 s */
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
)brace
)brace
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If jiffies has overflown in this timer_interrupt, we must&n;&t; * update the timer[hi]/[lo] to make fast gettimeoffset funcs&n;&t; * quotient calc still valid. -arca&n;&t; *&n;&t; * The first timer interrupt comes late as interrupts are&n;&t; * enabled long after timers are initialized.  Therefore the&n;&t; * high precision timer is fast, leading to wrong gettimeoffset()&n;&t; * calculations.  We deal with it by setting it based on the&n;&t; * number of its ticks between the second and the third interrupt.&n;&t; * That is still somewhat imprecise, but it&squot;s a good estimate.&n;&t; * --macro&n;&t; */
id|j
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
l_int|4
)paren
(brace
r_static
r_int
r_int
id|prev_count
suffix:semicolon
r_static
r_int
id|hpt_initialized
suffix:semicolon
r_switch
c_cond
(paren
id|j
)paren
(brace
r_case
l_int|0
suffix:colon
id|timerhi
op_assign
id|timerlo
op_assign
l_int|0
suffix:semicolon
id|mips_hpt_init
c_func
(paren
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|prev_count
op_assign
id|count
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|hpt_initialized
)paren
(brace
r_int
r_int
id|c3
op_assign
l_int|3
op_star
(paren
id|count
op_minus
id|prev_count
)paren
suffix:semicolon
id|timerhi
op_assign
l_int|0
suffix:semicolon
id|timerlo
op_assign
id|c3
suffix:semicolon
id|mips_hpt_init
c_func
(paren
id|count
op_minus
id|c3
)paren
suffix:semicolon
id|hpt_initialized
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
macro_line|#if !defined(CONFIG_SMP)
multiline_comment|/*&n;&t; * In UP mode, we call local_timer_interrupt() to do profiling&n;&t; * and process accouting.&n;&t; *&n;&t; * In SMP mode, local_timer_interrupt() is invoked by appropriate&n;&t; * low-level local timer interrupt handler.&n;&t; */
id|local_timer_interrupt
c_func
(paren
id|irq
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
macro_line|#else&t;/* CONFIG_SMP */
r_if
c_cond
(paren
id|emulate_local_timer_interrupt
)paren
(brace
multiline_comment|/*&n;&t;&t; * this is the place where we send out inter-process&n;&t;&t; * interrupts and let each CPU do its own profiling&n;&t;&t; * and process accouting.&n;&t;&t; *&n;&t;&t; * Obviously we need to call local_timer_interrupt() for&n;&t;&t; * the current CPU too.&n;&t;&t; */
id|panic
c_func
(paren
l_string|&quot;Not implemented yet!!!&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_SMP */
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|ll_timer_interrupt
id|asmlinkage
r_void
id|ll_timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|kstat_this_cpu.irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
multiline_comment|/* we keep interrupt disabled all the time */
id|timer_interrupt
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ll_local_timer_interrupt
id|asmlinkage
r_void
id|ll_local_timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
l_int|0
)paren
id|kstat_this_cpu.irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
multiline_comment|/* we keep interrupt disabled all the time */
id|local_timer_interrupt
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * time_init() - it does the following things.&n; *&n; * 1) board_time_init() -&n; * &t;a) (optional) set up RTC routines,&n; *      b) (optional) calibrate and set the mips_hpt_frequency&n; *&t;    (only needed if you intended to use fixed_rate_gettimeoffset&n; *&t;     or use cpu counter as timer interrupt source)&n; * 2) setup xtime based on rtc_get_time().&n; * 3) choose a appropriate gettimeoffset routine.&n; * 4) calculate a couple of cached variables for later usage&n; * 5) board_timer_setup() -&n; *&t;a) (optional) over-write any choices made above by time_init().&n; *&t;b) machine specific code should setup the timer irqaction.&n; *&t;c) enable the timer interrupt&n; */
DECL|variable|board_time_init
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_void
)paren
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
suffix:semicolon
DECL|variable|mips_hpt_frequency
r_int
r_int
id|mips_hpt_frequency
suffix:semicolon
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
comma
)brace
suffix:semicolon
DECL|function|calibrate_hpt
r_static
r_int
r_int
id|__init
id|calibrate_hpt
c_func
(paren
r_void
)paren
(brace
id|u64
id|frequency
suffix:semicolon
id|u32
id|hpt_start
comma
id|hpt_end
comma
id|hpt_count
comma
id|hz
suffix:semicolon
r_const
r_int
id|loops
op_assign
id|HZ
op_div
l_int|10
suffix:semicolon
r_int
id|log_2_loops
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * We want to calibrate for 0.1s, but to avoid a 64-bit&n;&t; * division we round the number of loops up to the nearest&n;&t; * power of 2.&n;&t; */
r_while
c_loop
(paren
id|loops
OG
l_int|1
op_lshift
id|log_2_loops
)paren
id|log_2_loops
op_increment
suffix:semicolon
id|i
op_assign
l_int|1
op_lshift
id|log_2_loops
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for a rising edge of the timer interrupt.&n;&t; */
r_while
c_loop
(paren
id|mips_timer_state
c_func
(paren
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|mips_timer_state
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now see how many high precision timer ticks happen&n;&t; * during the calculated number of periods between timer&n;&t; * interrupts.&n;&t; */
id|hpt_start
op_assign
id|mips_hpt_read
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
r_while
c_loop
(paren
id|mips_timer_state
c_func
(paren
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|mips_timer_state
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
id|hpt_end
op_assign
id|mips_hpt_read
c_func
(paren
)paren
suffix:semicolon
id|hpt_count
op_assign
id|hpt_end
op_minus
id|hpt_start
suffix:semicolon
id|hz
op_assign
id|HZ
suffix:semicolon
id|frequency
op_assign
(paren
id|u64
)paren
id|hpt_count
op_star
(paren
id|u64
)paren
id|hz
suffix:semicolon
r_return
id|frequency
op_rshift
id|log_2_loops
suffix:semicolon
)brace
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
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
r_if
c_cond
(paren
op_logical_neg
id|rtc_set_mmss
)paren
id|rtc_set_mmss
op_assign
id|rtc_set_time
suffix:semicolon
id|xtime.tv_sec
op_assign
id|rtc_get_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
l_int|0
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
multiline_comment|/* Choose appropriate high precision timer routines.  */
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_counter
op_logical_and
op_logical_neg
id|mips_hpt_read
)paren
(brace
multiline_comment|/* No high precision timer -- sorry.  */
id|mips_hpt_read
op_assign
id|null_hpt_read
suffix:semicolon
id|mips_hpt_init
op_assign
id|null_hpt_init
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|mips_hpt_frequency
op_logical_and
op_logical_neg
id|mips_timer_state
)paren
(brace
multiline_comment|/* A high precision timer of unknown frequency.  */
r_if
c_cond
(paren
op_logical_neg
id|mips_hpt_read
)paren
(brace
multiline_comment|/* No external high precision timer -- use R4k.  */
id|mips_hpt_read
op_assign
id|c0_hpt_read
suffix:semicolon
id|mips_hpt_init
op_assign
id|c0_hpt_init
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|current_cpu_data.isa_level
op_eq
id|MIPS_CPU_ISA_M32
)paren
op_logical_or
(paren
id|current_cpu_data.isa_level
op_eq
id|MIPS_CPU_ISA_I
)paren
op_logical_or
(paren
id|current_cpu_data.isa_level
op_eq
id|MIPS_CPU_ISA_II
)paren
)paren
multiline_comment|/*&n;&t;&t;&t; * We need to calibrate the counter but we don&squot;t have&n;&t;&t;&t; * 64-bit division.&n;&t;&t;&t; */
id|do_gettimeoffset
op_assign
id|calibrate_div32_gettimeoffset
suffix:semicolon
r_else
multiline_comment|/*&n;&t;&t;&t; * We need to calibrate the counter but we *do* have&n;&t;&t;&t; * 64-bit division.&n;&t;&t;&t; */
id|do_gettimeoffset
op_assign
id|calibrate_div64_gettimeoffset
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We know counter frequency.  Or we can get it.  */
r_if
c_cond
(paren
op_logical_neg
id|mips_hpt_read
)paren
(brace
multiline_comment|/* No external high precision timer -- use R4k.  */
id|mips_hpt_read
op_assign
id|c0_hpt_read
suffix:semicolon
r_if
c_cond
(paren
id|mips_timer_state
)paren
id|mips_hpt_init
op_assign
id|c0_hpt_init
suffix:semicolon
r_else
(brace
multiline_comment|/* No external timer interrupt -- use R4k.  */
id|mips_hpt_init
op_assign
id|c0_hpt_timer_init
suffix:semicolon
id|mips_timer_ack
op_assign
id|c0_timer_ack
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|mips_hpt_frequency
)paren
id|mips_hpt_frequency
op_assign
id|calibrate_hpt
c_func
(paren
)paren
suffix:semicolon
id|do_gettimeoffset
op_assign
id|fixed_rate_gettimeoffset
suffix:semicolon
multiline_comment|/* Calculate cache parameters.  */
id|cycles_per_jiffy
op_assign
(paren
id|mips_hpt_frequency
op_plus
id|HZ
op_div
l_int|2
)paren
op_div
id|HZ
suffix:semicolon
multiline_comment|/* sll32_usecs_per_cycle = 10^6 * 2^32 / mips_counter_freq  */
id|do_div64_32
c_func
(paren
id|sll32_usecs_per_cycle
comma
l_int|1000000
comma
id|mips_hpt_frequency
op_div
l_int|2
comma
id|mips_hpt_frequency
)paren
suffix:semicolon
multiline_comment|/* Report the high precision timer rate for a reference.  */
id|printk
c_func
(paren
l_string|&quot;Using %u.%03u MHz high precision timer.&bslash;n&quot;
comma
(paren
(paren
id|mips_hpt_frequency
op_plus
l_int|500
)paren
op_div
l_int|1000
)paren
op_div
l_int|1000
comma
(paren
(paren
id|mips_hpt_frequency
op_plus
l_int|500
)paren
op_div
l_int|1000
)paren
op_mod
l_int|1000
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mips_timer_ack
)paren
multiline_comment|/* No timer interrupt ack (e.g. i8254).  */
id|mips_timer_ack
op_assign
id|null_timer_ack
suffix:semicolon
multiline_comment|/* This sets up the high precision timer for the first interrupt.  */
id|mips_hpt_init
c_func
(paren
id|mips_hpt_read
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Call board specific timer interrupt setup.&n;&t; *&n;&t; * this pointer must be setup in machine setup routine.&n;&t; *&n;&t; * Even if a machine chooses to use a low-level timer interrupt,&n;&t; * it still needs to setup the timer_irqaction.&n;&t; * In that case, it might be better to set timer_irqaction.handler&n;&t; * to be NULL function so that we are sure the high-level code&n;&t; * is not invoked accidentally.&n;&t; */
id|board_timer_setup
c_func
(paren
op_amp
id|timer_irqaction
)paren
suffix:semicolon
)brace
DECL|macro|FEBRUARY
mdefine_line|#define FEBRUARY&t;&t;2
DECL|macro|STARTOFTIME
mdefine_line|#define STARTOFTIME&t;&t;1970
DECL|macro|SECDAY
mdefine_line|#define SECDAY&t;&t;&t;86400L
DECL|macro|SECYR
mdefine_line|#define SECYR&t;&t;&t;(SECDAY * 365)
DECL|macro|leapyear
mdefine_line|#define leapyear(y)&t;&t;((!((y) % 4) &amp;&amp; ((y) % 100)) || !((y) % 400))
DECL|macro|days_in_year
mdefine_line|#define days_in_year(y)&t;&t;(leapyear(y) ? 366 : 365)
DECL|macro|days_in_month
mdefine_line|#define days_in_month(m)&t;(month_days[(m) - 1])
DECL|variable|month_days
r_static
r_int
id|month_days
(braket
l_int|12
)braket
op_assign
(brace
l_int|31
comma
l_int|28
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
DECL|function|to_tm
r_void
id|to_tm
c_func
(paren
r_int
r_int
id|tim
comma
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
r_int
id|hms
comma
id|day
comma
id|gday
suffix:semicolon
r_int
id|i
suffix:semicolon
id|gday
op_assign
id|day
op_assign
id|tim
op_div
id|SECDAY
suffix:semicolon
id|hms
op_assign
id|tim
op_mod
id|SECDAY
suffix:semicolon
multiline_comment|/* Hours, minutes, seconds are easy */
id|tm-&gt;tm_hour
op_assign
id|hms
op_div
l_int|3600
suffix:semicolon
id|tm-&gt;tm_min
op_assign
(paren
id|hms
op_mod
l_int|3600
)paren
op_div
l_int|60
suffix:semicolon
id|tm-&gt;tm_sec
op_assign
(paren
id|hms
op_mod
l_int|3600
)paren
op_mod
l_int|60
suffix:semicolon
multiline_comment|/* Number of years in days */
r_for
c_loop
(paren
id|i
op_assign
id|STARTOFTIME
suffix:semicolon
id|day
op_ge
id|days_in_year
c_func
(paren
id|i
)paren
suffix:semicolon
id|i
op_increment
)paren
id|day
op_sub_assign
id|days_in_year
c_func
(paren
id|i
)paren
suffix:semicolon
id|tm-&gt;tm_year
op_assign
id|i
suffix:semicolon
multiline_comment|/* Number of months in days left */
r_if
c_cond
(paren
id|leapyear
c_func
(paren
id|tm-&gt;tm_year
)paren
)paren
id|days_in_month
c_func
(paren
id|FEBRUARY
)paren
op_assign
l_int|29
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|day
op_ge
id|days_in_month
c_func
(paren
id|i
)paren
suffix:semicolon
id|i
op_increment
)paren
id|day
op_sub_assign
id|days_in_month
c_func
(paren
id|i
)paren
suffix:semicolon
id|days_in_month
c_func
(paren
id|FEBRUARY
)paren
op_assign
l_int|28
suffix:semicolon
id|tm-&gt;tm_mon
op_assign
id|i
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* tm_mon starts from 0 to 11 */
multiline_comment|/* Days are what is left over (+1) from all that. */
id|tm-&gt;tm_mday
op_assign
id|day
op_plus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Determine the day of week&n;&t; */
id|tm-&gt;tm_wday
op_assign
(paren
id|gday
op_plus
l_int|4
)paren
op_mod
l_int|7
suffix:semicolon
multiline_comment|/* 1970/1/1 was Thursday */
)brace
DECL|variable|rtc_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtc_lock
)paren
suffix:semicolon
DECL|variable|to_tm
id|EXPORT_SYMBOL
c_func
(paren
id|to_tm
)paren
suffix:semicolon
DECL|variable|rtc_set_time
id|EXPORT_SYMBOL
c_func
(paren
id|rtc_set_time
)paren
suffix:semicolon
DECL|variable|rtc_get_time
id|EXPORT_SYMBOL
c_func
(paren
id|rtc_get_time
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
