multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * Common time service routines for MIPS machines. See &n; * Documentation/mips/time.README. &n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
multiline_comment|/* This is for machines which generate the exact clock. */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY (1000000/HZ)
DECL|macro|USECS_PER_JIFFY_FRAC
mdefine_line|#define USECS_PER_JIFFY_FRAC ((1000000ULL &lt;&lt; 32) / HZ &amp; 0xffffffff)
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
multiline_comment|/*&n; * forward reference&n; */
r_extern
r_volatile
r_int
r_int
id|wall_jiffies
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
multiline_comment|/*&n; * timeofday services, for syscalls.&n; */
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
op_star
id|tv
op_assign
id|xtime
suffix:semicolon
id|tv-&gt;tv_usec
op_add_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * xtime is atomically updated in timer_bh. &n;&t;&t; * jiffies - wall_jiffies&n;&t;&t; * is nonzero if the timer bottom half hasnt executed yet.&n;&t;&t; */
r_if
c_cond
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
id|tv-&gt;tv_usec
op_add_assign
id|USECS_PER_JIFFY
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
r_if
c_cond
(paren
id|tv-&gt;tv_usec
op_ge
l_int|1000000
)paren
(brace
id|tv-&gt;tv_usec
op_sub_assign
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_sec
op_increment
suffix:semicolon
)brace
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
id|write_seqlock_irq
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* This is revolting. We need to set the xtime.tv_usec&n;&t; * correctly. However, the value in this location is&n;&t; * is value at the last tick.&n;&t; * Discover what correction gettimeofday&n;&t; * would have done, and then undo it!&n;&t; */
id|tv-&gt;tv_usec
op_sub_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
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
id|xtime
op_assign
op_star
id|tv
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
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Gettimeoffset routines.  These routines returns the time duration&n; * since last timer interrupt in usecs.&n; *&n; * If the exact CPU counter frequency is known, use fixed_rate_gettimeoffset.&n; * Otherwise use calibrate_gettimeoffset()&n; *&n; * If the CPU does not have counter register all, you can either supply&n; * your own gettimeoffset() routine, or use null_gettimeoffset() routines,&n; * which gives the same resolution as HZ.&n; */
multiline_comment|/* This is for machines which generate the exact clock. */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY (1000000/HZ)
multiline_comment|/* usecs per counter cycle, shifted to left by 32 bits */
DECL|variable|sll32_usecs_per_cycle
r_static
r_int
r_int
id|sll32_usecs_per_cycle
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* how many counter cycles in a jiffy */
DECL|variable|cycles_per_jiffy
r_static
r_int
r_int
id|cycles_per_jiffy
op_assign
l_int|0
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
multiline_comment|/* last time when xtime and rtc are sync&squot;ed up */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
suffix:semicolon
multiline_comment|/* the function pointer to one of the gettimeoffset funcs*/
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
DECL|function|null_gettimeoffset
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
DECL|function|fixed_rate_gettimeoffset
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
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
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
l_string|&quot;multu&bslash;t%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;mfhi&bslash;t%0&quot;
suffix:colon
l_string|&quot;=r&quot;
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
multiline_comment|/*&n; * Cached &quot;1/(clocks per usec)*2^32&quot; value.&n; * It has to be recalculated once each jiffy.&n; */
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
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * This is copied from dec/time.c:do_ioasic_gettimeoffset() by Mercij.&n; */
DECL|function|calibrate_div32_gettimeoffset
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
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
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
l_string|&quot;multu  %2,%3&quot;
suffix:colon
l_string|&quot;=l&quot;
(paren
id|tmp
)paren
comma
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
id|tmp
op_logical_and
id|last_jiffies
op_ne
id|tmp
)paren
(brace
id|last_jiffies
op_assign
id|tmp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;lwu&bslash;t%0,%2&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t$1,%1,0&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t$1,$1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ddivu&bslash;t$0,$1,%3&bslash;n&bslash;t&quot;
l_string|&quot;mflo&bslash;t$1&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t%0,%4,0&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;ddivu&bslash;t$0,%0,$1&bslash;n&bslash;t&quot;
l_string|&quot;mflo&bslash;t%0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|quotient
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
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
id|cached_quotient
op_assign
id|quotient
suffix:semicolon
)brace
multiline_comment|/* Get last timer tick in absolute kernel time */
id|count
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
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
l_string|&quot;multu&bslash;t%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;mfhi&bslash;t%0&quot;
suffix:colon
l_string|&quot;=r&quot;
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
multiline_comment|/*&n; * high-level timer interrupt service routines.  This function&n; * is set as irqaction-&gt;handler and is invoked through do_IRQ.&n; */
DECL|function|timer_interrupt
r_void
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
id|seq
suffix:semicolon
r_if
c_cond
(paren
id|mips_cpu.options
op_amp
id|MIPS_CPU_COUNTER
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The cycle counter is only 32 bit which is good for about&n;&t;&t; * a minute at current count rates of upto 150MHz or so.&n;&t;&t; */
id|count
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_COUNT
)paren
suffix:semicolon
id|timerhi
op_add_assign
(paren
id|count
OL
id|timerlo
)paren
suffix:semicolon
multiline_comment|/* Wrap around */
id|timerlo
op_assign
id|count
suffix:semicolon
multiline_comment|/*&n;&t;&t; * set up for next timer interrupt - no harm if the machine&n;&t;&t; * is using another timer interrupt source.&n;&t;&t; * Note that writing to COMPARE register clears the interrupt&n;&t;&t; */
id|write_32bit_cp0_register
(paren
id|CP0_COMPARE
comma
id|count
op_plus
id|cycles_per_jiffy
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|pc
op_assign
id|regs-&gt;cp0_epc
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
multiline_comment|/*&n;&t;&t;&t; * Dont ignore out-of-bounds pc values silently,&n;&t;&t;&t; * put them into the last histogram slot, so if&n;&t;&t;&t; * present, they will show up as a sharp peak.&n;&t;&t;&t; */
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
)brace
multiline_comment|/*&n;&t; * call the generic timer interrupt handling&n;&t; */
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we have an externally synchronized Linux clock, then update&n;&t; * CMOS clock accordingly every ~11 minutes. rtc_set_time() has to be&n;&t; * called as close as possible to 500 ms before the new second starts.&n;&t; */
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
id|xtime.tv_usec
op_ge
l_int|500000
op_minus
(paren
(paren
r_int
)paren
id|tick
)paren
op_div
l_int|2
op_logical_and
id|xtime.tv_usec
op_le
l_int|500000
op_plus
(paren
(paren
r_int
)paren
id|tick
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
(brace
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
)brace
r_else
(brace
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
multiline_comment|/* do it again in 60 s */
)brace
)brace
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
multiline_comment|/*&n;&t; * If jiffies has overflowed in this timer_interrupt we must&n;&t; * update the timer[hi]/[lo] to make fast gettimeoffset funcs&n;&t; * quotient calc still valid. -arca&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|jiffies
)paren
(brace
id|timerhi
op_assign
id|timerlo
op_assign
l_int|0
suffix:semicolon
)brace
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
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|irqs
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
id|cpu
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|softirq_pending
c_func
(paren
id|cpu
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * time_init() - it does the following things.&n; *&n; * 1) board_time_init() - &n; * &t;a) (optional) set up RTC routines, &n; *      b) (optional) calibrate and set the mips_counter_frequency&n; *&t;    (only needed if you intended to use fixed_rate_gettimeoffset&n; *&t;     or use cpu counter as timer interrupt source)&n; * 2) setup xtime based on rtc_get_time().&n; * 3) choose a appropriate gettimeoffset routine.&n; * 4) calculate a couple of cached variables for later usage&n; * 5) board_timer_setup() - &n; *&t;a) (optional) over-write any choices made above by time_init().&n; *&t;b) machine specific code should setup the timer irqaction.&n; *&t;c) enable the timer interrupt&n; */
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
l_int|NULL
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
l_int|NULL
suffix:semicolon
DECL|variable|mips_counter_frequency
r_int
r_int
id|mips_counter_frequency
op_assign
l_int|0
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
id|xtime.tv_sec
op_assign
id|rtc_get_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* choose appropriate gettimeoffset routine */
r_if
c_cond
(paren
op_logical_neg
(paren
id|mips_cpu.options
op_amp
id|MIPS_CPU_COUNTER
)paren
)paren
(brace
multiline_comment|/* no cpu counter - sorry */
id|do_gettimeoffset
op_assign
id|null_gettimeoffset
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mips_counter_frequency
op_ne
l_int|0
)paren
(brace
multiline_comment|/* we have cpu counter and know counter frequency! */
id|do_gettimeoffset
op_assign
id|fixed_rate_gettimeoffset
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|mips_cpu.isa_level
op_eq
id|MIPS_CPU_ISA_M32
)paren
op_logical_or
(paren
id|mips_cpu.isa_level
op_eq
id|MIPS_CPU_ISA_I
)paren
op_logical_or
(paren
id|mips_cpu.isa_level
op_eq
id|MIPS_CPU_ISA_II
)paren
)paren
(brace
multiline_comment|/* we need to calibrate the counter but we don&squot;t have&n;&t;&t; * 64-bit division. */
id|do_gettimeoffset
op_assign
id|calibrate_div32_gettimeoffset
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we need to calibrate the counter but we *do* have&n;&t;&t; * 64-bit division. */
id|do_gettimeoffset
op_assign
id|calibrate_div64_gettimeoffset
suffix:semicolon
)brace
multiline_comment|/* caclulate cache parameters */
r_if
c_cond
(paren
id|mips_counter_frequency
)paren
(brace
id|cycles_per_jiffy
op_assign
id|mips_counter_frequency
op_div
id|HZ
suffix:semicolon
multiline_comment|/* sll32_usecs_per_cycle = 10^6 * 2^32 / mips_counter_freq */
multiline_comment|/* any better way to do this? */
id|sll32_usecs_per_cycle
op_assign
id|mips_counter_frequency
op_div
l_int|100000
suffix:semicolon
id|sll32_usecs_per_cycle
op_assign
l_int|0xffffffff
op_div
id|sll32_usecs_per_cycle
suffix:semicolon
id|sll32_usecs_per_cycle
op_mul_assign
l_int|10
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Call board specific timer interrupt setup.&n;&t; *&n;&t; * this pointer must be setup in machine setup routine. &n;&t; *&n;&t; * Even if the machine choose to use low-level timer interrupt,&n;&t; * it still needs to setup the timer_irqaction.&n;&t; * In that case, it might be better to set timer_irqaction.handler &n;&t; * to be NULL function so that we are sure the high-level code&n;&t; * is not invoked accidentally.&n;&t; */
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
mdefine_line|#define leapyear(year)&t;&t;((year) % 4 == 0)
DECL|macro|days_in_year
mdefine_line|#define days_in_year(a)&t;&t;(leapyear(a) ? 366 : 365)
DECL|macro|days_in_month
mdefine_line|#define days_in_month(a)&t;(month_days[(a) - 1])
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
suffix:semicolon
r_int
id|i
suffix:semicolon
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
suffix:semicolon
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
id|day
op_plus
l_int|3
)paren
op_mod
l_int|7
suffix:semicolon
)brace
eof
