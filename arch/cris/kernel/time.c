multiline_comment|/* $Id: time.c,v 1.2 2001/12/18 13:35:20 bjornw Exp $&n; *&n; *  linux/arch/cris/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *  Copyright (C) 1999, 2000, 2001 Axis Communications AB&n; *&n; * 1994-07-02    Alan Modra&n; *&t;fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1995-03-26    Markus Kuhn&n; *      fixed 500 ms bug at call to set_rtc_mmss, fixed DS12887&n; *      precision CMOS clock update&n; * 1996-05-03    Ingo Molnar&n; *      fixed time warps in do_[slow|fast]_gettimeoffset()&n; * 1997-09-10&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; *&n; * Linux/CRIS specific code:&n; *&n; * Authors:    Bjorn Wesen&n; *             Johan Adolfsson  &n; *&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/svinto.h&gt;
DECL|variable|jiffies_64
id|u64
id|jiffies_64
suffix:semicolon
DECL|variable|have_rtc
r_static
r_int
id|have_rtc
suffix:semicolon
multiline_comment|/* used to remember if we have an RTC or not */
multiline_comment|/* define this if you need to use print_timestamp */
multiline_comment|/* it will make jiffies at 96 hz instead of 100 hz though */
DECL|macro|USE_CASCADE_TIMERS
macro_line|#undef USE_CASCADE_TIMERS
r_extern
r_int
id|setup_etrax_irq
c_func
(paren
r_int
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
multiline_comment|/* Lookup table to convert *R_TIMER0 to microseconds (us) &n; * Timer goes from TIMER0_DIV down to 1 meaning 0-10000us in step of approx 52us&n; */
DECL|variable|cris_timer0_value_us
r_int
r_int
id|cris_timer0_value_us
(braket
id|TIMER0_DIV
op_plus
l_int|1
)braket
suffix:semicolon
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|function|do_slow_gettimeoffset
r_static
r_int
r_int
id|do_slow_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|usec_count
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_int
id|count_p
op_assign
id|LATCH
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
multiline_comment|/* The timer interrupt comes from Etrax timer 0. In order to get&n;&t; * better precision, we check the current value. It might have&n;&t; * underflowed already though.&n;&t; */
macro_line|#ifndef CONFIG_SVINTO_SIM
multiline_comment|/* Not available in the xsim simulator. */
id|count
op_assign
op_star
id|R_TIMER0_DATA
suffix:semicolon
macro_line|#else
id|count
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|jiffies_t
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; * avoiding timer inconsistencies (they are rare, but they happen)...&n;&t; * there are three kinds of problems that must be avoided here:&n;&t; *  1. the timer counter underflows&n;&t; *  2. we are after the timer interrupt, but the bottom half handler&n;&t; *     hasn&squot;t executed yet.&n; */
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
multiline_comment|/* Timer wrapped */
id|count
op_assign
id|count_p
suffix:semicolon
id|usec_count
op_assign
l_int|1000000
op_div
id|CLOCK_TICK_RATE
op_div
l_int|2
suffix:semicolon
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
multiline_comment|/* Convert timer value to usec using table lookup */
id|usec_count
op_add_assign
id|cris_timer0_value_us
(braket
id|count
)braket
suffix:semicolon
macro_line|#if 0
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
macro_line|#endif
r_return
id|usec_count
suffix:semicolon
)brace
DECL|variable|do_gettimeoffset
r_static
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
id|do_slow_gettimeoffset
suffix:semicolon
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
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
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
id|restore_flags
c_func
(paren
id|flags
)paren
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
id|cli
c_func
(paren
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
id|time_state
op_assign
id|TIME_ERROR
suffix:semicolon
multiline_comment|/* p. 24, (a) */
id|time_maxerror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|time_esterror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * BUG: This routine does not handle hour overflow properly; it just&n; *      sets the minutes. Usually you&squot;ll only notice that after reboot!&n; */
DECL|function|set_rtc_mmss
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|real_seconds
comma
id|real_minutes
comma
id|cmos_minutes
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;set_rtc_mmss(%lu)&bslash;n&quot;
comma
id|nowtime
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_rtc
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|cmos_minutes
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|cmos_minutes
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * since we&squot;re only adjusting minutes and seconds,&n;&t; * don&squot;t interfere with hour overflow. This avoids&n;&t; * messing with unknown time zones but requires your&n;&t; * RTC not to be off by more than 15 minutes&n;&t; */
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
OL
l_int|30
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|real_seconds
comma
id|RTC_SECONDS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|real_minutes
comma
id|RTC_MINUTES
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;set_rtc_mmss: can&squot;t update from %d to %d&bslash;n&quot;
comma
id|cmos_minutes
comma
id|real_minutes
)paren
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Excerpt from the Etrax100 HSDD about the built-in watchdog:&n; *&n; * 3.10.4 Watchdog timer&n;&n; * When the watchdog timer is started, it generates an NMI if the watchdog&n; * isn&squot;t restarted or stopped within 0.1 s. If it still isn&squot;t restarted or&n; * stopped after an additional 3.3 ms, the watchdog resets the chip.&n; * The watchdog timer is stopped after reset. The watchdog timer is controlled&n; * by the R_WATCHDOG register. The R_WATCHDOG register contains an enable bit&n; * and a 3-bit key value. The effect of writing to the R_WATCHDOG register is&n; * described in the table below:&n; * &n; *   Watchdog    Value written:&n; *   state:      To enable:  To key:      Operation:&n; *   --------    ----------  -------      ----------&n; *   stopped         0         X          No effect.&n; *   stopped         1       key_val      Start watchdog with key = key_val.&n; *   started         0       ~key         Stop watchdog&n; *   started         1       ~key         Restart watchdog with key = ~key.&n; *   started         X       new_key_val  Change key to new_key_val.&n; * &n; * Note: &squot;~&squot; is the bitwise NOT operator.&n; * &n; */
multiline_comment|/* right now, starting the watchdog is the same as resetting it */
DECL|macro|start_watchdog
mdefine_line|#define start_watchdog reset_watchdog
macro_line|#if defined(CONFIG_ETRAX_WATCHDOG) &amp;&amp; !defined(CONFIG_SVINTO_SIM)
DECL|variable|watchdog_key
r_static
r_int
id|watchdog_key
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* arbitrary number */
macro_line|#endif
multiline_comment|/* number of pages to consider &quot;out of memory&quot;. it is normal that the memory&n; * is used though, so put this really low.&n; */
DECL|macro|WATCHDOG_MIN_FREE_PAGES
mdefine_line|#define WATCHDOG_MIN_FREE_PAGES 8
r_void
DECL|function|reset_watchdog
id|reset_watchdog
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_ETRAX_WATCHDOG) &amp;&amp; !defined(CONFIG_SVINTO_SIM)
multiline_comment|/* only keep watchdog happy as long as we have memory left! */
r_if
c_cond
(paren
id|nr_free_pages
c_func
(paren
)paren
OG
id|WATCHDOG_MIN_FREE_PAGES
)paren
(brace
multiline_comment|/* reset the watchdog with the inverse of the old key */
id|watchdog_key
op_xor_assign
l_int|0x7
suffix:semicolon
multiline_comment|/* invert key, which is 3 bits */
op_star
id|R_WATCHDOG
op_assign
id|IO_FIELD
c_func
(paren
id|R_WATCHDOG
comma
id|key
comma
id|watchdog_key
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_WATCHDOG
comma
id|enable
comma
id|start
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* stop the watchdog - we still need the correct key */
r_void
DECL|function|stop_watchdog
id|stop_watchdog
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_ETRAX_WATCHDOG) &amp;&amp; !defined(CONFIG_SVINTO_SIM)
id|watchdog_key
op_xor_assign
l_int|0x7
suffix:semicolon
multiline_comment|/* invert key, which is 3 bits */
op_star
id|R_WATCHDOG
op_assign
id|IO_FIELD
c_func
(paren
id|R_WATCHDOG
comma
id|key
comma
id|watchdog_key
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_WATCHDOG
comma
id|enable
comma
id|stop
)paren
suffix:semicolon
macro_line|#endif&t;
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
singleline_comment|//static unsigned short myjiff; /* used by our debug routine print_timestamp */
r_static
r_inline
r_void
DECL|function|timer_interrupt
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
multiline_comment|/* acknowledge the timer irq */
macro_line|#ifdef USE_CASCADE_TIMERS
op_star
id|R_TIMER_CTRL
op_assign
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv1
comma
l_int|0
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv0
comma
l_int|0
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i1
comma
id|clr
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm1
comma
id|run
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel1
comma
id|cascade0
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i0
comma
id|clr
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm0
comma
id|run
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel0
comma
id|c6250kHz
)paren
suffix:semicolon
macro_line|#else
op_star
id|R_TIMER_CTRL
op_assign
id|r_timer_ctrl_shadow
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i0
comma
id|clr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* reset watchdog otherwise it resets us! */
id|reset_watchdog
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* call the real timer interrupt handler */
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
id|xtime.tv_usec
OG
l_int|500000
op_minus
(paren
id|tick
op_rshift
l_int|1
)paren
op_logical_and
id|xtime.tv_usec
OL
l_int|500000
op_plus
(paren
id|tick
op_rshift
l_int|1
)paren
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
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
)brace
)brace
macro_line|#if 0
multiline_comment|/* some old debug code for testing the microsecond timing of packets */
r_static
r_int
r_int
id|lastjiff
suffix:semicolon
r_void
id|print_timestamp
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|newjiff
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|newjiff
op_assign
(paren
id|myjiff
op_lshift
l_int|16
)paren
op_or
(paren
r_int
r_int
)paren
(paren
op_minus
op_star
id|R_TIMER01_DATA
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %x (%x)&bslash;n&quot;
comma
id|s
comma
id|newjiff
comma
id|newjiff
op_minus
id|lastjiff
)paren
suffix:semicolon
id|lastjiff
op_assign
id|newjiff
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* grab the time from the RTC chip */
r_int
r_int
DECL|function|get_cmos_time
id|get_cmos_time
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
id|sec
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mon
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;rtc: sec 0x%x min 0x%x hour 0x%x day 0x%x mon 0x%x year 0x%x&bslash;n&quot;
comma
id|sec
comma
id|min
comma
id|hour
comma
id|day
comma
id|mon
comma
id|year
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|year
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
r_return
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
)brace
multiline_comment|/* update xtime from the CMOS settings. used when /dev/rtc gets a SET_TIME.&n; * TODO: this doesn&squot;t reset the fancy NTP phase stuff as do_settimeofday does.&n; */
r_void
DECL|function|update_xtime_from_cmos
id|update_xtime_from_cmos
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|have_rtc
)paren
(brace
id|xtime.tv_sec
op_assign
id|get_cmos_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* timer is SA_SHIRQ so drivers can add stuff to the timer irq chain&n; * it needs to be SA_INTERRUPT to make the jiffies update work properly&n; */
DECL|variable|irq2
r_static
r_struct
id|irqaction
id|irq2
op_assign
(brace
id|timer_interrupt
comma
id|SA_SHIRQ
op_or
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
r_void
id|__init
DECL|function|time_init
id|time_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* probe for the RTC and read it if it exists */
r_if
c_cond
(paren
id|RTC_INIT
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* no RTC, start at 1980 */
id|xtime.tv_sec
op_assign
l_int|0
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
id|have_rtc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* get the current time */
id|have_rtc
op_assign
l_int|1
suffix:semicolon
id|update_xtime_from_cmos
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup the etrax timers&n;&t; * Base frequency is 19200 hz, divider 192 -&gt; 100 hz as Linux wants&n;&t; * In normal mode, we use timer0, so timer1 is free. In cascade&n;&t; * mode (which we sometimes use for debugging) both timers are used.&n;&t; * Remember that linux/timex.h contains #defines that rely on the&n;&t; * timer settings below (hz and divide factor) !!!&n;&t; */
macro_line|#ifdef USE_CASCADE_TIMERS
op_star
id|R_TIMER_CTRL
op_assign
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv1
comma
l_int|0
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv0
comma
l_int|0
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i1
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm1
comma
id|stop_ld
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel1
comma
id|cascade0
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i0
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm0
comma
id|stop_ld
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel0
comma
id|c6250kHz
)paren
suffix:semicolon
op_star
id|R_TIMER_CTRL
op_assign
id|r_timer_ctrl_shadow
op_assign
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv1
comma
l_int|0
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv0
comma
l_int|0
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i1
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm1
comma
id|run
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel1
comma
id|cascade0
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i0
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm0
comma
id|run
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel0
comma
id|c6250kHz
)paren
suffix:semicolon
macro_line|#else
op_star
id|R_TIMER_CTRL
op_assign
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv1
comma
l_int|192
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv0
comma
l_int|192
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i1
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm1
comma
id|stop_ld
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel1
comma
id|c19k2Hz
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i0
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm0
comma
id|stop_ld
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel0
comma
id|c19k2Hz
)paren
suffix:semicolon
op_star
id|R_TIMER_CTRL
op_assign
id|r_timer_ctrl_shadow
op_assign
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv1
comma
l_int|192
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_TIMER_CTRL
comma
id|timerdiv0
comma
l_int|192
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i1
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm1
comma
id|run
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel1
comma
id|c19k2Hz
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|i0
comma
id|nop
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|tm0
comma
id|run
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_TIMER_CTRL
comma
id|clksel0
comma
id|c19k2Hz
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|TIMER0_DIV
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* We must be careful not to get overflow... */
id|cris_timer0_value_us
(braket
id|TIMER0_DIV
op_minus
id|i
)braket
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
(paren
(paren
id|i
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
)paren
op_div
id|TIMER0_DIV
)paren
op_amp
l_int|0x0000FFFFL
)paren
suffix:semicolon
)brace
op_star
id|R_IRQ_MASK0_SET
op_assign
id|IO_STATE
c_func
(paren
id|R_IRQ_MASK0_SET
comma
id|timer0
comma
id|set
)paren
suffix:semicolon
multiline_comment|/* unmask the timer irq */
multiline_comment|/* now actually register the timer irq handler that calls timer_interrupt() */
id|setup_etrax_irq
c_func
(paren
l_int|2
comma
op_amp
id|irq2
)paren
suffix:semicolon
multiline_comment|/* irq 2 is the timer0 irq in etrax */
multiline_comment|/* enable watchdog if we should use one */
macro_line|#if defined(CONFIG_ETRAX_WATCHDOG) &amp;&amp; !defined(CONFIG_SVINTO_SIM)
id|printk
c_func
(paren
l_string|&quot;Enabling watchdog...&bslash;n&quot;
)paren
suffix:semicolon
id|start_watchdog
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If we use the hardware watchdog, we want to trap it as an NMI&n;&t;   and dump registers before it resets us.  For this to happen, we&n;&t;   must set the &quot;m&quot; NMI enable flag (which once set, is unset only&n;&t;   when an NMI is taken).&n;&n;&t;   The same goes for the external NMI, but that doesn&squot;t have any&n;&t;   driver or infrastructure support yet.  */
id|asm
(paren
l_string|&quot;setf m&quot;
)paren
suffix:semicolon
op_star
id|R_IRQ_MASK0_SET
op_assign
id|IO_STATE
c_func
(paren
id|R_IRQ_MASK0_SET
comma
id|watchdog_nmi
comma
id|set
)paren
suffix:semicolon
op_star
id|R_VECT_MASK_SET
op_assign
id|IO_STATE
c_func
(paren
id|R_VECT_MASK_SET
comma
id|nmi
comma
id|set
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
