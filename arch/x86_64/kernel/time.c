multiline_comment|/*&n; *  linux/arch/x86-64/kernel/time.c&n; *&n; *  &quot;High Precision Event Timer&quot; based timekeeping.&n; *&n; *  Copyright (c) 1991,1992,1995  Linus Torvalds&n; *  Copyright (c) 1994  Alan Modra&n; *  Copyright (c) 1995  Markus Kuhn&n; *  Copyright (c) 1996  Ingo Molnar&n; *  Copyright (c) 1998  Andrea Arcangeli&n; *  Copyright (c) 2002  Vojtech Pavlik&n; *  Copyright (c) 2003  Andi Kleen&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/vsyscall.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#endif
DECL|variable|jiffies_64
id|u64
id|jiffies_64
suffix:semicolon
r_extern
r_int
id|using_apic_timer
suffix:semicolon
DECL|variable|rtc_lock
id|spinlock_t
id|rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_extern
r_int
id|using_apic_timer
suffix:semicolon
r_extern
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|cpu_khz
r_int
r_int
id|cpu_khz
suffix:semicolon
multiline_comment|/* TSC clocks / usec, not used here */
DECL|variable|hpet_period
r_int
r_int
id|hpet_period
suffix:semicolon
multiline_comment|/* fsecs / HPET clock */
DECL|variable|hpet_tick
r_int
r_int
id|hpet_tick
suffix:semicolon
multiline_comment|/* HPET clocks / interrupt */
DECL|variable|hpet_report_lost_ticks
r_int
id|hpet_report_lost_ticks
suffix:semicolon
multiline_comment|/* command line option */
DECL|variable|__section_hpet
r_struct
id|hpet_data
id|__hpet
id|__section_hpet
suffix:semicolon
multiline_comment|/* address, quotient, trigger, hz */
DECL|variable|__section_jiffies
r_volatile
r_int
r_int
id|__jiffies
id|__section_jiffies
suffix:semicolon
DECL|variable|__section_wall_jiffies
r_int
r_int
id|__wall_jiffies
id|__section_wall_jiffies
suffix:semicolon
DECL|variable|__section_xtime
r_struct
id|timespec
id|__xtime
id|__section_xtime
suffix:semicolon
DECL|variable|__section_sys_tz
r_struct
id|timezone
id|__sys_tz
id|__section_sys_tz
suffix:semicolon
multiline_comment|/*&n; * do_gettimeoffset() returns microseconds since last timer interrupt was&n; * triggered by hardware. A memory read of HPET is slower than a register read&n; * of TSC, but much more reliable. It&squot;s also synchronized to the timer&n; * interrupt. Note that do_gettimeoffset() may return more than hpet_tick, if a&n; * timer interrupt has happened already, but hpet.trigger wasn&squot;t updated yet.&n; * This is not a problem, because jiffies hasn&squot;t updated either. They are bound&n; * together by xtime_lock.&n;         */
DECL|function|do_gettimeoffset
r_inline
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
id|t
suffix:semicolon
id|sync_core
c_func
(paren
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|t
)paren
suffix:semicolon
r_return
(paren
id|t
op_minus
id|hpet.last_tsc
)paren
op_star
(paren
l_int|1000000L
op_div
id|HZ
)paren
op_div
id|hpet.ticks
op_plus
id|hpet.offset
suffix:semicolon
)brace
multiline_comment|/*&n; * This version of gettimeofday() has microsecond resolution and better than&n; * microsecond precision, as we&squot;re using at least a 10 MHz (usually 14.31818&n; * MHz) HPET timer.&n; */
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
comma
id|t
suffix:semicolon
r_int
r_int
id|sec
comma
id|usec
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
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_assign
id|xtime.tv_nsec
op_div
l_int|1000
suffix:semicolon
id|t
op_assign
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_star
(paren
l_int|1000000L
op_div
id|HZ
)paren
op_plus
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
id|usec
op_add_assign
id|t
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
id|tv-&gt;tv_sec
op_assign
id|sec
op_plus
id|usec
op_div
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|usec
op_mod
l_int|1000000
suffix:semicolon
)brace
multiline_comment|/*&n; * settimeofday() first undoes the correction that gettimeofday would do&n; * on the time, and then saves it. This is ugly, but has been like this for&n; * ages already.&n; */
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
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|tv-&gt;tv_usec
op_sub_assign
id|do_gettimeoffset
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
id|tick_usec
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
(paren
id|tv-&gt;tv_usec
op_star
l_int|1000
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
)brace
multiline_comment|/*&n; * In order to set the CMOS clock precisely, set_rtc_mmss has to be called 500&n; * ms after the second nowtime has started, because when nowtime is written&n; * into the registers of the CMOS clock, it will jump to the next second&n; * precisely 500 ms later. Check the Motorola MC146818A or Dallas DS12887 data&n; * sheet for details.&n; */
DECL|function|set_rtc_mmss
r_static
r_void
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|real_seconds
comma
id|real_minutes
comma
id|cmos_minutes
suffix:semicolon
r_int
r_char
id|control
comma
id|freq_select
suffix:semicolon
multiline_comment|/*&n; * IRQs are disabled when we&squot;re called from the timer interrupt,&n; * no need for spin_lock_irqsave()&n; */
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
multiline_comment|/*&n; * Tell the clock it&squot;s being set and stop it.&n; */
id|control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|control
op_or
id|RTC_SET
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|freq_select
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|freq_select
op_or
id|RTC_DIV_RESET2
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
id|BCD_TO_BIN
c_func
(paren
id|cmos_minutes
)paren
suffix:semicolon
multiline_comment|/*&n; * since we&squot;re only adjusting minutes and seconds, don&squot;t interfere with hour&n; * overflow. This avoids messing with unknown time zones but requires your RTC&n; * not to be off by more than 15 minutes. Since we&squot;re calling it only when&n; * our clock is externally synchronized using NTP, this shouldn&squot;t be a problem.&n;&t; */
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;time.c: can&squot;t update CMOS clock from %d to %d&bslash;n&quot;
comma
id|cmos_minutes
comma
id|real_minutes
)paren
suffix:semicolon
multiline_comment|/*&n; * The following flags have to be released exactly in this order, otherwise the&n; * DS12887 (popular MC146818A clone with integrated battery and quartz) will&n; * not reset the oscillator and will not update precisely 500 ms later. You&n; * won&squot;t find this mentioned in the Dallas Semiconductor data sheets, but who&n; * believes data sheets anyway ... -- Markus Kuhn&n; */
id|CMOS_WRITE
c_func
(paren
id|control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|freq_select
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
)brace
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
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_int
r_int
id|rtc_update
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Here we are in the timer irq handler. We have irqs locally disabled (so we&n; * don&squot;t need spin_lock_irqsave()) but we don&squot;t know if the timer_bh is running&n; * on the other CPU, so we need a lock. We also need to lock the vsyscall&n; * variables, because both do_timer() and us change them -arca+vojtech&n;&t; */
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
(brace
r_int
r_int
id|t
suffix:semicolon
id|sync_core
c_func
(paren
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|t
)paren
suffix:semicolon
id|hpet.offset
op_assign
(paren
id|t
op_minus
id|hpet.last_tsc
)paren
op_star
(paren
l_int|1000000L
op_div
id|HZ
)paren
op_div
id|hpet.ticks
op_plus
id|hpet.offset
op_minus
l_int|1000000L
op_div
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|hpet.offset
op_ge
l_int|1000000L
op_div
id|HZ
)paren
id|hpet.offset
op_assign
l_int|0
suffix:semicolon
id|hpet.ticks
op_assign
id|min_t
c_func
(paren
r_int
comma
id|max_t
c_func
(paren
r_int
comma
(paren
id|t
op_minus
id|hpet.last_tsc
)paren
op_star
(paren
l_int|1000000L
op_div
id|HZ
)paren
op_div
(paren
l_int|1000000L
op_div
id|HZ
op_minus
id|hpet.offset
)paren
comma
id|cpu_khz
op_star
l_int|1000
op_div
id|HZ
op_star
l_int|15
op_div
l_int|16
)paren
comma
id|cpu_khz
op_star
l_int|1000
op_div
id|HZ
op_star
l_int|16
op_div
l_int|15
)paren
suffix:semicolon
id|hpet.last_tsc
op_assign
id|t
suffix:semicolon
)brace
multiline_comment|/*&n; * Do the timer stuff.&n; */
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * In the SMP case we use the local APIC timer interrupt to do the profiling,&n; * except when we simulate SMP mode on a uniprocessor system, in that case we&n; * have to call the local interrupt handler.&n; */
macro_line|#ifndef CONFIG_X86_LOCAL_APIC
id|x86_do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|using_apic_timer
)paren
id|smp_local_timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * If we have an externally synchronized Linux clock, then update CMOS clock&n; * accordingly every ~11 minutes. set_rtc_mmss() will be called in the jiffy&n; * closest to exactly 500 ms before the next second. If the update fails, we&n; * don&squot;tcare, as it&squot;ll be updated on the next turn, and the problem (time way&n; * off) isn&squot;t likely to go away much sooner anyway.&n; */
r_if
c_cond
(paren
(paren
op_complement
id|time_status
op_amp
id|STA_UNSYNC
)paren
op_logical_and
id|xtime.tv_sec
OG
id|rtc_update
op_logical_and
id|abs
c_func
(paren
id|xtime.tv_nsec
op_minus
l_int|500000000
)paren
op_le
id|tick_nsec
op_div
l_int|2
)paren
(brace
id|set_rtc_mmss
c_func
(paren
id|xtime.tv_sec
)paren
suffix:semicolon
id|rtc_update
op_assign
id|xtime.tv_sec
op_plus
l_int|660
suffix:semicolon
)brace
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
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
id|timeout
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
r_int
r_char
id|last
comma
id|this
suffix:semicolon
multiline_comment|/*&n; * The Linux interpretation of the CMOS clock register contents: When the&n; * Update-In-Progress (UIP) flag goes from 1 to 0, the RTC registers show the&n; * second which has precisely just started. Waiting for this can take up to 1&n; * second, we timeout approximately after 2.4 seconds on a machine with&n; * standard 8.3 MHz ISA bus.&n; */
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|timeout
op_assign
l_int|1000000
suffix:semicolon
id|last
op_assign
id|this
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_logical_and
id|last
op_logical_and
op_logical_neg
id|this
)paren
(brace
id|last
op_assign
id|this
suffix:semicolon
id|this
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
suffix:semicolon
id|timeout
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n; * Here we are safe to assume the registers won&squot;t change for a whole second, so&n; * we just go ahead and read them.&n;&t; */
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
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
multiline_comment|/*&n; * We know that x86-64 always uses BCD format, no need to check the config&n; * register.&n; */
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
multiline_comment|/*&n; * This will work up to Dec 31, 2069.&n; */
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
multiline_comment|/*&n; * calibrate_tsc() calibrates the processor TSC in a very simple way, comparing&n; * it to the HPET timer of known frequency.&n; */
DECL|macro|TICK_COUNT
mdefine_line|#define TICK_COUNT 100000000
multiline_comment|/*&n; * pit_calibrate_tsc() uses the speaker output (channel 2) of&n; * the PIT. This is better than using the timer interrupt output,&n; * because we can read the value of the speaker with just one inb(),&n; * where we need three i/o operations for the interrupt channel.&n; * We count how many ticks the TSC does in 50 ms.&n; */
DECL|function|pit_calibrate_tsc
r_static
r_int
r_int
id|__init
id|pit_calibrate_tsc
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
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
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xb0
comma
l_int|0x43
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|1193182
op_div
(paren
l_int|1000
op_div
l_int|50
)paren
)paren
op_amp
l_int|0xff
comma
l_int|0x42
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|1193182
op_div
(paren
l_int|1000
op_div
l_int|50
)paren
)paren
op_rshift
l_int|8
comma
l_int|0x42
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|start
)paren
suffix:semicolon
id|sync_core
c_func
(paren
)paren
suffix:semicolon
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
id|sync_core
c_func
(paren
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|end
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
id|end
op_minus
id|start
)paren
op_div
l_int|50
suffix:semicolon
)brace
DECL|function|pit_init
r_void
id|__init
id|pit_init
c_func
(paren
r_void
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
multiline_comment|/* binary, mode 2, LSB/MSB, ch 0 */
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
multiline_comment|/* LSB */
id|outb_p
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
)brace
DECL|function|time_setup
r_int
id|__init
id|time_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|hpet_report_lost_ticks
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|irq0
r_static
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
l_string|&quot;timer&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_extern
r_void
id|__init
id|config_acpi_tables
c_func
(paren
r_void
)paren
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
id|xtime.tv_sec
op_assign
id|get_cmos_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|pit_init
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;time.c: Using 1.1931816 MHz PIT timer.&bslash;n&quot;
)paren
suffix:semicolon
id|cpu_khz
op_assign
id|pit_calibrate_tsc
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;time.c: Detected %d.%03d MHz processor.&bslash;n&quot;
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
id|hpet.ticks
op_assign
id|cpu_khz
op_star
(paren
l_int|1000
op_div
id|HZ
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|hpet.last_tsc
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|0
comma
op_amp
id|irq0
)paren
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;report_lost_ticks&quot;
comma
id|time_setup
)paren
suffix:semicolon
eof
