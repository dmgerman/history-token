multiline_comment|/*&n; *  linux/arch/i386/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *&n; * This file contains the PC-specific time handling details:&n; * reading the RTC at bootup, etc..&n; * 1994-07-02    Alan Modra&n; *&t;fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1995-03-26    Markus Kuhn&n; *      fixed 500 ms bug at call to set_rtc_mmss, fixed DS12887&n; *      precision CMOS clock update&n; * 1996-05-03    Ingo Molnar&n; *      fixed time warps in do_[slow|fast]_gettimeoffset()&n; * 1997-09-10&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; * 1998-09-05    (Various)&n; *&t;More robust do_fast_gettimeoffset() algorithm implemented&n; *&t;(works with APM, Cyrix 6x86MX and Centaur C6),&n; *&t;monotonic gettimeofday() with fast_get_timeoffset(),&n; *&t;drift-proof precision TSC calibration on boot&n; *&t;(C. Scott Ananian &lt;cananian@alumni.princeton.edu&gt;, Andrew D.&n; *&t;Balsa &lt;andrebalsa@altern.org&gt;, Philip Gladstone &lt;philip@raptor.com&gt;;&n; *&t;ported from 2.0.35 Jumbo-9 by Michael Krause &lt;m.krause@tu-harburg.de&gt;).&n; * 1998-12-16    Andrea Arcangeli&n; *&t;Fixed Jumbo-9 code in 2.1.131: do_gettimeofday was missing 1 jiffy&n; *&t;because was not accounting lost_ticks.&n; * 1998-12-24 Copyright (C) 1998  Andrea Arcangeli&n; *&t;Fixed a xtime SMP race (we need the xtime_lock rw spinlock to&n; *&t;serialize accesses to xtime/lost_ticks).&n; */
macro_line|#include &lt;linux/errno.h&gt;
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
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch_hooks.h&gt;
r_extern
id|spinlock_t
id|i8259A_lock
suffix:semicolon
macro_line|#include &quot;do_timer.h&quot;
multiline_comment|/*&n; * for x86_do_profile()&n; */
macro_line|#include &lt;linux/irq.h&gt;
DECL|variable|cpu_khz
r_int
r_int
id|cpu_khz
suffix:semicolon
multiline_comment|/* Detected as we calibrate the TSC */
multiline_comment|/* Number of usecs that the last interrupt was delayed */
DECL|variable|delay_at_last_interrupt
r_static
r_int
id|delay_at_last_interrupt
suffix:semicolon
DECL|variable|last_tsc_low
r_static
r_int
r_int
id|last_tsc_low
suffix:semicolon
multiline_comment|/* lsb 32 bits of Time Stamp Counter */
multiline_comment|/* Cached *multiplier* to convert TSC counts to microseconds.&n; * (see the equation below).&n; * Equal to 2^32 * (1 / (clocks per usec) ).&n; * Initialized in time_init.&n; */
DECL|variable|fast_gettimeoffset_quotient
r_int
r_int
id|fast_gettimeoffset_quotient
suffix:semicolon
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
r_extern
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
DECL|function|do_fast_gettimeoffset
r_static
r_inline
r_int
r_int
id|do_fast_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|eax
comma
id|edx
suffix:semicolon
multiline_comment|/* Read the Time Stamp Counter */
id|rdtsc
c_func
(paren
id|eax
comma
id|edx
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy (32 bits is enough) */
id|eax
op_sub_assign
id|last_tsc_low
suffix:semicolon
multiline_comment|/* tsc_low delta */
multiline_comment|/*&n;         * Time offset = (tsc_low delta) * fast_gettimeoffset_quotient&n;         *             = (tsc_low delta) * (usecs_per_clock)&n;         *             = (tsc_low delta) * (usecs_per_jiffy / clocks_per_jiffy)&n;&t; *&n;&t; * Using a mull instead of a divl saves up to 31 clock cycles&n;&t; * in the critical path.&n;         */
id|__asm__
c_func
(paren
l_string|&quot;mull %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|fast_gettimeoffset_quotient
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
)paren
suffix:semicolon
multiline_comment|/* our adjusted time offset in microseconds */
r_return
id|delay_at_last_interrupt
op_plus
id|edx
suffix:semicolon
)brace
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|variable|i8253_lock
id|spinlock_t
id|i8253_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|i8253_lock
id|EXPORT_SYMBOL
c_func
(paren
id|i8253_lock
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_X86_TSC
multiline_comment|/* This function must be called with interrupts disabled &n; * It was inspired by Steve McCanne&squot;s microtime-i386 for BSD.  -- jrs&n; * &n; * However, the pc-audio speaker driver changes the divisor so that&n; * it gets interrupted rather more often - it loads 64 into the&n; * counter rather than 11932! This has an adverse impact on&n; * do_gettimeoffset() -- it stops working! What is also not&n; * good is that the interval that our timer function gets called&n; * is no longer 10.0002 ms, but 9.9767 ms. To get around this&n; * would require using a different timing source. Maybe someone&n; * could use the RTC - I know that this can interrupt at frequencies&n; * ranging from 8192Hz to 2Hz. If I had the energy, I&squot;d somehow fix&n; * it so that at startup, the timer code in sched.c would select&n; * using either the RTC or the 8253 timer. The decision would be&n; * based on whether there was any other device around that needed&n; * to trample on the 8253. I&squot;d set up the RTC to interrupt at 1024 Hz,&n; * and then do some jiggery to have a version of do_timer that &n; * advanced the clock by 1/1024 s. Every time that reached over 1/100&n; * of a second, then do all the old code. If the time was kept correct&n; * then do_gettimeoffset could just return 0 - there is no low order&n; * divider that can be accessed.&n; *&n; * Ideally, you would be able to use the RTC for the speaker driver,&n; * but it appears that the speaker driver really needs interrupt more&n; * often than every 120 us or so.&n; *&n; * Anyway, this needs more thought....&t;&t;pjsg (1993-08-28)&n; * &n; * If you are really that interested, you should be reading&n; * comp.protocols.time.ntp!&n; */
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
id|count
suffix:semicolon
r_static
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
multiline_comment|/* gets recalled with irq locally disabled */
id|spin_lock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
multiline_comment|/*&n;&t; * We do this guaranteed double memory access instead of a _p &n;&t; * postfix in the previous port access. Wheee, hackady hack&n;&t; */
id|jiffies_t
op_assign
id|jiffies
suffix:semicolon
id|count
op_or_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* VIA686a test code... reset the latch if count &gt; max + 1 */
r_if
c_cond
(paren
id|count
OG
id|LATCH
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x34
comma
l_int|0x43
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
id|count
op_assign
id|LATCH
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * avoiding timer inconsistencies (they are rare, but they happen)...&n;&t; * there are two kinds of problems that must be avoided here:&n;&t; *  1. the timer counter underflows&n;&t; *  2. hardware problem with the timer, not giving us continuous time,&n;&t; *     the counter does small &quot;jumps&quot; upwards on some Pentium systems,&n;&t; *     (see c&squot;t 95/10 page 335 for Neptun bug.)&n;&t; */
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
id|count
op_assign
id|do_timer_overflow
c_func
(paren
id|count
)paren
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
macro_line|#else
DECL|macro|do_gettimeoffset
mdefine_line|#define do_gettimeoffset()&t;do_fast_gettimeoffset()
macro_line|#endif
multiline_comment|/*&n; * This version of gettimeofday has microsecond resolution&n; * and better than microsecond precision on fast x86 machines with TSC.&n; */
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
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
(brace
r_int
r_int
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
)brace
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_add_assign
id|xtime.tv_usec
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
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is revolting. We need to set &quot;xtime&quot; correctly. However, the&n;&t; * value in this location is the value at the most recent update of&n;&t; * wall time.  Discover what correction gettimeofday() would have&n;&t; * made, and then undo it!&n;&t; */
id|tv-&gt;tv_usec
op_sub_assign
id|do_gettimeoffset
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
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * In order to set the CMOS clock precisely, set_rtc_mmss has to be&n; * called 500 ms after the second nowtime has started, because when&n; * nowtime is written into the registers of the CMOS clock, it will&n; * jump to the next second precisely 500 ms later. Check the Motorola&n; * MC146818A or Dallas DS12887 data sheet for details.&n; *&n; * BUG: This routine does not handle hour overflow properly; it just&n; *      sets the minutes. Usually you&squot;ll only notice that after reboot!&n; */
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
r_int
r_char
id|save_control
comma
id|save_freq_select
suffix:semicolon
multiline_comment|/* gets recalled with irq locally disabled */
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|save_control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being set */
id|CMOS_WRITE
c_func
(paren
(paren
id|save_control
op_or
id|RTC_SET
)paren
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|save_freq_select
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
multiline_comment|/* stop and reset prescaler */
id|CMOS_WRITE
c_func
(paren
(paren
id|save_freq_select
op_or
id|RTC_DIV_RESET2
)paren
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|cmos_minutes
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
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
)brace
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
multiline_comment|/* The following flags have to be released exactly in this order,&n;&t; * otherwise the DS12887 (popular MC146818A clone with integrated&n;&t; * battery and quartz) will not reset the oscillator and will not&n;&t; * update precisely 500 ms later. You won&squot;t find this mentioned in&n;&t; * the Dallas Semiconductor data sheets, but who believes data&n;&t; * sheets anyway ...                           -- Markus Kuhn&n;&t; */
id|CMOS_WRITE
c_func
(paren
id|save_control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|save_freq_select
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* last time the cmos clock got updated */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
suffix:semicolon
DECL|variable|timer_ack
r_int
id|timer_ack
suffix:semicolon
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
macro_line|#ifdef CONFIG_X86_IO_APIC
r_if
c_cond
(paren
id|timer_ack
)paren
(brace
multiline_comment|/*&n;&t;&t; * Subtle, when I/O APICs are used we have to ack timer IRQ&n;&t;&t; * manually to reset the IRR bit for do_slow_gettimeoffset().&n;&t;&t; * This will also deassert NMI lines for the watchdog if run&n;&t;&t; * on an 82489DX-based system.&n;&t;&t; */
id|spin_lock
c_func
(paren
op_amp
id|i8259A_lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0c
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Ack the IRQ; AEOI will end it automatically. */
id|inb
c_func
(paren
l_int|0x20
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i8259A_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
id|do_timer_interrupt_hook
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
multiline_comment|/* do it again in 60 s */
)brace
macro_line|#ifdef CONFIG_MCA
r_if
c_cond
(paren
id|MCA_bus
)paren
(brace
multiline_comment|/* The PS/2 uses level-triggered interrupts.  You can&squot;t&n;&t;&t;turn them off, nor would you want to (any attempt to&n;&t;&t;enable edge-triggered interrupts usually gets intercepted by a&n;&t;&t;special hardware circuit).  Hence we have to acknowledge&n;&t;&t;the timer interrupt.  Through some incredibly stupid&n;&t;&t;design idea, the reset for IRQ 0 is done by setting the&n;&t;&t;high bit of the PPI port B (0x61).  Note that some PS/2s,&n;&t;&t;notably the 55SX, work fine if this is removed.  */
id|irq
op_assign
id|inb_p
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/* read the current state */
id|outb_p
c_func
(paren
id|irq
op_or
l_int|0x80
comma
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/* reset the IRQ */
)brace
macro_line|#endif
)brace
DECL|variable|use_tsc
r_static
r_int
id|use_tsc
suffix:semicolon
multiline_comment|/*&n; * This is the same as the above, except we _also_ save the current&n; * Time Stamp Counter value at the time of the timer interrupt, so that&n; * we later on can estimate the time of day more exactly.&n; */
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
id|count
suffix:semicolon
multiline_comment|/*&n;&t; * Here we are in the timer irq handler. We just have irqs locally&n;&t; * disabled but we don&squot;t know if the timer_bh is running on the other&n;&t; * CPU. We need to avoid to SMP race with it. NOTE: we don&squot; t need&n;&t; * the irq version of write_lock because as just said we have irq&n;&t; * locally disabled. -arca&n;&t; */
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_tsc
)paren
(brace
multiline_comment|/*&n;&t;&t; * It is important that these two operations happen almost at&n;&t;&t; * the same time. We do the RDTSC stuff first, since it&squot;s&n;&t;&t; * faster. To avoid any inconsistencies, we need interrupts&n;&t;&t; * disabled locally.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Interrupts are just disabled locally since the timer irq&n;&t;&t; * has the SA_INTERRUPT flag set. -arca&n;&t;&t; */
multiline_comment|/* read Pentium cycle counter */
id|rdtscl
c_func
(paren
id|last_tsc_low
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
id|count
op_or_assign
id|inb
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i8253_lock
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
id|delay_at_last_interrupt
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
)brace
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
id|write_unlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* not static: needed by APM */
DECL|function|get_cmos_time
r_int
r_int
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
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
multiline_comment|/* The Linux interpretation of the CMOS clock register contents:&n;&t; * When the Update-In-Progress (UIP) flag goes from 1 to 0, the&n;&t; * RTC registers show the second which has precisely just started.&n;&t; * Let&squot;s hope other operating systems interpret the RTC the same way.&n;&t; */
multiline_comment|/* read RTC exactly on falling edge of update flag */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* may take up to 1 second... */
r_if
c_cond
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* must try at least 2.228 ms */
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
)paren
r_break
suffix:semicolon
r_do
(brace
multiline_comment|/* Isn&squot;t this overkill ? UIP above should guarantee consistency */
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
)brace
r_while
c_loop
(paren
id|sec
op_ne
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
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
)brace
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
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
multiline_comment|/* ------ Calibrate the TSC ------- &n; * Return 2^32 * (1 / (TSC clocks per usec)) for do_fast_gettimeoffset().&n; * Too much 64-bit arithmetic here to do this cleanly in C, and for&n; * accuracy&squot;s sake we want to keep the overhead on the CTC speaker (channel 2)&n; * output busy loop as low as possible. We avoid reading the CTC registers&n; * directly because of the awkward 8-bit access mechanism of the 82C54&n; * device.&n; */
DECL|macro|CALIBRATE_LATCH
mdefine_line|#define CALIBRATE_LATCH&t;(5 * LATCH)
DECL|macro|CALIBRATE_TIME
mdefine_line|#define CALIBRATE_TIME&t;(5 * 1000020/HZ)
macro_line|#ifdef CONFIG_X86_TSC
DECL|function|calibrate_tsc
r_static
r_int
r_int
id|__init
id|calibrate_tsc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Set the Gate high, disable speaker */
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
l_int|0x61
)paren
op_amp
op_complement
l_int|0x02
)paren
op_or
l_int|0x01
comma
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now let&squot;s take care of CTC channel 2&n;&t; *&n;&t; * Set the Gate high, program CTC channel 2 for mode 0,&n;&t; * (interrupt on terminal count mode), binary count,&n;&t; * load 5 * LATCH count, (LSB and MSB) to begin countdown.&n;&t; */
id|outb
c_func
(paren
l_int|0xb0
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* binary, mode 0, LSB/MSB, Ch 2 */
id|outb
c_func
(paren
id|CALIBRATE_LATCH
op_amp
l_int|0xff
comma
l_int|0x42
)paren
suffix:semicolon
multiline_comment|/* LSB of count */
id|outb
c_func
(paren
id|CALIBRATE_LATCH
op_rshift
l_int|8
comma
l_int|0x42
)paren
suffix:semicolon
multiline_comment|/* MSB of count */
(brace
r_int
r_int
id|startlow
comma
id|starthigh
suffix:semicolon
r_int
r_int
id|endlow
comma
id|endhigh
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|rdtsc
c_func
(paren
id|startlow
comma
id|starthigh
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
l_int|0x61
)paren
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|rdtsc
c_func
(paren
id|endlow
comma
id|endhigh
)paren
suffix:semicolon
id|last_tsc_low
op_assign
id|endlow
suffix:semicolon
multiline_comment|/* Error: ECTCNEVERSET */
r_if
c_cond
(paren
id|count
op_le
l_int|1
)paren
r_goto
id|bad_ctc
suffix:semicolon
multiline_comment|/* 64-bit subtract - gcc just messes up with long longs */
id|__asm__
c_func
(paren
l_string|&quot;subl %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;sbbl %3,%1&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|endlow
)paren
comma
l_string|&quot;=d&quot;
(paren
id|endhigh
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|startlow
)paren
comma
l_string|&quot;g&quot;
(paren
id|starthigh
)paren
comma
l_string|&quot;0&quot;
(paren
id|endlow
)paren
comma
l_string|&quot;1&quot;
(paren
id|endhigh
)paren
)paren
suffix:semicolon
multiline_comment|/* Error: ECPUTOOFAST */
r_if
c_cond
(paren
id|endhigh
)paren
r_goto
id|bad_ctc
suffix:semicolon
multiline_comment|/* Error: ECPUTOOSLOW */
r_if
c_cond
(paren
id|endlow
op_le
id|CALIBRATE_TIME
)paren
r_goto
id|bad_ctc
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|endlow
)paren
comma
l_string|&quot;=d&quot;
(paren
id|endhigh
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|endlow
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;1&quot;
(paren
id|CALIBRATE_TIME
)paren
)paren
suffix:semicolon
r_return
id|endlow
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The CTC wasn&squot;t reliable: we got a hit on the very first read,&n;&t; * or the CPU was so fast/slow that the quotient wouldn&squot;t fit in&n;&t; * 32 bits..&n;&t; */
id|bad_ctc
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_X86_TSC */
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|x86_udelay_tsc
suffix:semicolon
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
multiline_comment|/*&n; * If we have APM enabled or the CPU clock speed is variable&n; * (CPU stops clock on HLT or slows clock to save power)&n; * then the TSC timestamps may diverge by up to 1 jiffy from&n; * &squot;real time&squot; but nothing will break.&n; * The most frequent case is that the CPU is &quot;woken&quot; from a halt&n; * state by the timer interrupt itself, so we get 0 error. In the&n; * rare cases where a driver would &quot;wake&quot; the CPU and request a&n; * timestamp, the maximum error is &lt; 1 jiffy. But timestamps are&n; * still perfectly ordered.&n; * Note that the TSC counter will be reset if APM suspends&n; * to disk; this won&squot;t break the kernel, though, &squot;cuz we&squot;re&n; * smart.  See arch/i386/kernel/apm.c.&n; */
macro_line|#ifdef CONFIG_X86_TSC
multiline_comment|/*&n; &t; *&t;Firstly we have to do a CPU check for chips with&n; &t; * &t;a potentially buggy TSC. At this point we haven&squot;t run&n; &t; *&t;the ident/bugs checks so we must run this hook as it&n; &t; *&t;may turn off the TSC flag.&n; &t; *&n; &t; *&t;NOTE: this doesnt yet handle SMP 486 machines where only&n; &t; *&t;some CPU&squot;s have a TSC. Thats never worked and nobody has&n; &t; *&t;moaned if you have the only one in the world - you fix it!&n; &t; */
id|dodgy_tsc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_tsc
)paren
(brace
r_int
r_int
id|tsc_quotient
op_assign
id|calibrate_tsc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsc_quotient
)paren
(brace
id|fast_gettimeoffset_quotient
op_assign
id|tsc_quotient
suffix:semicolon
id|use_tsc
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;We could be more selective here I suspect&n;&t;&t;&t; *&t;and just enable this for the next intel chips ?&n;&t;&t;&t; */
id|x86_udelay_tsc
op_assign
l_int|1
suffix:semicolon
macro_line|#ifndef do_gettimeoffset
id|do_gettimeoffset
op_assign
id|do_fast_gettimeoffset
suffix:semicolon
macro_line|#endif
multiline_comment|/* report CPU clock rate in Hz.&n;&t;&t;&t; * The formula is (10^6 * 2^32) / (2^32 * 1 / (clocks/us)) =&n;&t;&t;&t; * clock/second. Our precision is about 100 ppm.&n;&t;&t;&t; */
(brace
r_int
r_int
id|eax
op_assign
l_int|0
comma
id|edx
op_assign
l_int|1000
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|cpu_khz
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|tsc_quotient
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
comma
l_string|&quot;1&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Detected %lu.%03lu MHz processor.&bslash;n&quot;
comma
id|cpu_khz
op_div
l_int|1000
comma
id|cpu_khz
op_mod
l_int|1000
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* CONFIG_X86_TSC */
id|time_init_hook
c_func
(paren
)paren
suffix:semicolon
)brace
eof
