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
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/vsyscall.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#include &lt;asm/apic.h&gt;
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
id|using_apic_timer
suffix:semicolon
DECL|variable|rtc_lock
id|spinlock_t
id|rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|i8253_lock
id|spinlock_t
id|i8253_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|HPET_HACK_ENABLE_DANGEROUS
macro_line|#undef HPET_HACK_ENABLE_DANGEROUS
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
DECL|variable|vxtime_hz
r_int
r_int
id|vxtime_hz
op_assign
l_int|1193182
suffix:semicolon
DECL|variable|report_lost_ticks
r_int
id|report_lost_ticks
suffix:semicolon
multiline_comment|/* command line option */
DECL|variable|monotonic_base
r_int
r_int
r_int
id|monotonic_base
suffix:semicolon
DECL|variable|__section_vxtime
r_struct
id|vxtime_data
id|__vxtime
id|__section_vxtime
suffix:semicolon
multiline_comment|/* for vsyscalls */
DECL|variable|__section_jiffies
r_volatile
r_int
r_int
id|__jiffies
id|__section_jiffies
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
DECL|variable|__section_wall_jiffies
r_int
r_int
id|__wall_jiffies
id|__section_wall_jiffies
op_assign
id|INITIAL_JIFFIES
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
DECL|function|rdtscll_sync
r_static
r_inline
r_void
id|rdtscll_sync
c_func
(paren
r_int
r_int
op_star
id|tsc
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|sync_core
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|rdtscll
c_func
(paren
op_star
id|tsc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * do_gettimeoffset() returns microseconds since last timer interrupt was&n; * triggered by hardware. A memory read of HPET is slower than a register read&n; * of TSC, but much more reliable. It&squot;s also synchronized to the timer&n; * interrupt. Note that do_gettimeoffset() may return more than hpet_tick, if a&n; * timer interrupt has happened already, but vxtime.trigger wasn&squot;t updated yet.&n; * This is not a problem, because jiffies hasn&squot;t updated either. They are bound&n; * together by xtime_lock.&n;         */
DECL|function|do_gettimeoffset_tsc
r_static
r_inline
r_int
r_int
id|do_gettimeoffset_tsc
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|t
suffix:semicolon
r_int
r_int
id|x
suffix:semicolon
id|rdtscll_sync
c_func
(paren
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
OL
id|vxtime.last_tsc
)paren
id|t
op_assign
id|vxtime.last_tsc
suffix:semicolon
multiline_comment|/* hack */
id|x
op_assign
(paren
(paren
id|t
op_minus
id|vxtime.last_tsc
)paren
op_star
id|vxtime.tsc_quot
)paren
op_rshift
l_int|32
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|function|do_gettimeoffset_hpet
r_static
r_inline
r_int
r_int
id|do_gettimeoffset_hpet
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
id|hpet_readl
c_func
(paren
id|HPET_COUNTER
)paren
op_minus
id|vxtime.last
)paren
op_star
id|vxtime.quot
)paren
op_rshift
l_int|32
suffix:semicolon
)brace
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
id|do_gettimeoffset_tsc
suffix:semicolon
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
multiline_comment|/* i386 does some correction here to keep the clock &n;&t;&t;   monotonus even when ntpd is fixing drift.&n;&t;&t;   But they didn&squot;t work for me, there is a non monotonic&n;&t;&t;   clock anyways with ntp.&n;&t;&t;   I dropped all corrections now until a real solution can&n;&t;&t;   be found. Note when you fix it here you need to do the same&n;&t;&t;   in arch/x86_64/kernel/vsyscall.c and export all needed&n;&t;&t;   variables in vmlinux.lds. -AK */
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
DECL|variable|do_gettimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_gettimeofday
)paren
suffix:semicolon
multiline_comment|/*&n; * settimeofday() first undoes the correction that gettimeofday would do&n; * on the time, and then saves it. This is ugly, but has been like this for&n; * ages already.&n; */
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
id|nsec
op_sub_assign
id|do_gettimeoffset
c_func
(paren
)paren
op_star
l_int|1000
op_plus
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_star
(paren
id|NSEC_PER_SEC
op_div
id|HZ
)paren
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
l_string|&quot;time.c: can&squot;t update CMOS clock &quot;
l_string|&quot;from %d to %d&bslash;n&quot;
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
multiline_comment|/* monotonic_clock(): returns # of nanoseconds passed since time_init()&n; *&t;&t;Note: This function is required to return accurate&n; *&t;&t;time even in the absence of multiple timer ticks.&n; */
DECL|function|monotonic_clock
r_int
r_int
r_int
id|monotonic_clock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|seq
suffix:semicolon
id|u32
id|last_offset
comma
id|this_offset
comma
id|offset
suffix:semicolon
r_int
r_int
r_int
id|base
suffix:semicolon
r_if
c_cond
(paren
id|vxtime.mode
op_eq
id|VXTIME_HPET
)paren
(brace
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
id|last_offset
op_assign
id|vxtime.last
suffix:semicolon
id|base
op_assign
id|monotonic_base
suffix:semicolon
id|this_offset
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T0_CMP
)paren
op_minus
id|hpet_tick
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
id|offset
op_assign
(paren
id|this_offset
op_minus
id|last_offset
)paren
suffix:semicolon
id|offset
op_mul_assign
(paren
id|NSEC_PER_SEC
op_div
id|HZ
)paren
op_div
id|hpet_tick
suffix:semicolon
r_return
id|base
op_plus
id|offset
suffix:semicolon
)brace
r_else
(brace
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
id|last_offset
op_assign
id|vxtime.last_tsc
suffix:semicolon
id|base
op_assign
id|monotonic_base
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
id|sync_core
c_func
(paren
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|this_offset
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|this_offset
op_minus
id|last_offset
)paren
op_star
l_int|1000
op_div
id|cpu_khz
suffix:semicolon
r_return
id|base
op_plus
id|offset
suffix:semicolon
)brace
)brace
DECL|variable|monotonic_clock
id|EXPORT_SYMBOL
c_func
(paren
id|monotonic_clock
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
r_static
r_int
r_int
id|rtc_update
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tsc
comma
id|lost
op_assign
l_int|0
suffix:semicolon
r_int
id|delay
comma
id|offset
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
r_if
c_cond
(paren
id|vxtime.hpet_address
)paren
(brace
id|offset
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T0_CMP
)paren
op_minus
id|hpet_tick
suffix:semicolon
id|delay
op_assign
id|hpet_readl
c_func
(paren
id|HPET_COUNTER
)paren
op_minus
id|offset
suffix:semicolon
)brace
r_else
(brace
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
id|delay
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
id|delay
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
id|delay
op_assign
id|LATCH
op_minus
l_int|1
op_minus
id|delay
suffix:semicolon
)brace
id|rdtscll_sync
c_func
(paren
op_amp
id|tsc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vxtime.mode
op_eq
id|VXTIME_HPET
)paren
(brace
r_if
c_cond
(paren
id|offset
op_minus
id|vxtime.last
OG
id|hpet_tick
)paren
(brace
id|lost
op_assign
(paren
id|offset
op_minus
id|vxtime.last
)paren
op_div
id|hpet_tick
op_minus
l_int|1
suffix:semicolon
)brace
id|monotonic_base
op_add_assign
(paren
id|offset
op_minus
id|vxtime.last
)paren
op_star
(paren
id|NSEC_PER_SEC
op_div
id|HZ
)paren
op_div
id|hpet_tick
suffix:semicolon
id|vxtime.last
op_assign
id|offset
suffix:semicolon
)brace
r_else
(brace
id|offset
op_assign
(paren
(paren
(paren
id|tsc
op_minus
id|vxtime.last_tsc
)paren
op_star
id|vxtime.tsc_quot
)paren
op_rshift
l_int|32
)paren
op_minus
(paren
id|USEC_PER_SEC
op_div
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
(paren
id|USEC_PER_SEC
op_div
id|HZ
)paren
)paren
(brace
id|lost
op_assign
id|offset
op_div
(paren
id|USEC_PER_SEC
op_div
id|HZ
)paren
suffix:semicolon
id|offset
op_mod_assign
(paren
id|USEC_PER_SEC
op_div
id|HZ
)paren
suffix:semicolon
)brace
id|monotonic_base
op_add_assign
(paren
id|tsc
op_minus
id|vxtime.last_tsc
)paren
op_star
l_int|1000000
op_div
id|cpu_khz
suffix:semicolon
id|vxtime.last_tsc
op_assign
id|tsc
op_minus
id|vxtime.quot
op_star
id|delay
op_div
id|vxtime.tsc_quot
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
(paren
id|tsc
op_minus
id|vxtime.last_tsc
)paren
op_star
id|vxtime.tsc_quot
)paren
op_rshift
l_int|32
)paren
OL
id|offset
)paren
id|vxtime.last_tsc
op_assign
id|tsc
op_minus
(paren
(paren
(paren
r_int
)paren
id|offset
op_lshift
l_int|32
)paren
op_div
id|vxtime.tsc_quot
)paren
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lost
)paren
(brace
r_if
c_cond
(paren
id|report_lost_ticks
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;time.c: Lost %ld timer &quot;
l_string|&quot;tick(s)! (rip %016lx)&bslash;n&quot;
comma
(paren
id|offset
op_minus
id|vxtime.last
)paren
op_div
id|hpet_tick
op_minus
l_int|1
comma
id|regs-&gt;rip
)paren
suffix:semicolon
id|jiffies
op_add_assign
id|lost
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
multiline_comment|/*&n; * If we have an externally synchronized Linux clock, then update CMOS clock&n; * accordingly every ~11 minutes. set_rtc_mmss() will be called in the jiffy&n; * closest to exactly 500 ms before the next second. If the update fails, we&n; * don&squot;t care, as it&squot;ll be updated on the next turn, and the problem (time way&n; * off) isn&squot;t likely to go away much sooner anyway.&n; */
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
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* RED-PEN: calculation is done in 32bits with multiply for performance&n;   and could overflow, it may be better (but slower)to use an 64bit division. */
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
r_int
r_int
id|a
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Don&squot;t do a HPET read here. Using TSC always is much faster&n;&t;   and HPET may not be mapped yet when the scheduler first runs.&n;           Disadvantage is a small drift between CPUs in some configurations,&n;&t;   but that should be tolerable. */
r_if
c_cond
(paren
id|__vxtime.mode
op_eq
id|VXTIME_HPET
)paren
r_return
(paren
id|hpet_readl
c_func
(paren
id|HPET_COUNTER
)paren
op_star
id|vxtime.quot
)paren
op_rshift
l_int|32
suffix:semicolon
macro_line|#endif
multiline_comment|/* Could do CPU core sync here. Opteron can execute rdtsc speculatively,&n;&t;   which means it is not completely exact and may not be monotonous between&n;&t;   CPUs. But the errors should be too small to matter for scheduling&n;&t;   purposes. */
id|rdtscll
c_func
(paren
id|a
)paren
suffix:semicolon
r_return
(paren
id|a
op_star
id|vxtime.tsc_quot
)paren
op_rshift
l_int|32
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
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n; * The Linux interpretation of the CMOS clock register contents: When the&n; * Update-In-Progress (UIP) flag goes from 1 to 0, the RTC registers show the&n; * second which has precisely just started. Waiting for this can take up to 1&n; * second, we timeout approximately after 2.4 seconds on a machine with&n; * standard 8.3 MHz ISA bus.&n; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
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
macro_line|#ifdef CONFIG_CPU_FREQ
multiline_comment|/* Frequency scaling support. Adjust the TSC based timer when the cpu frequency&n;   changes.&n;   &n;   RED-PEN: On SMP we assume all CPUs run with the same frequency.  It&squot;s&n;   not that important because current Opteron setups do not support&n;   scaling on SMP anyroads.&n;&n;   Should fix up last_tsc too. Currently gettimeofday in the&n;   first tick after the change will be slightly wrong. */
DECL|variable|ref_freq
r_static
r_int
r_int
id|ref_freq
op_assign
l_int|0
suffix:semicolon
DECL|variable|loops_per_jiffy_ref
r_static
r_int
r_int
id|loops_per_jiffy_ref
op_assign
l_int|0
suffix:semicolon
DECL|variable|cpu_khz_ref
r_static
r_int
r_int
id|cpu_khz_ref
op_assign
l_int|0
suffix:semicolon
DECL|function|time_cpufreq_notifier
r_static
r_int
id|time_cpufreq_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|cpufreq_freqs
op_star
id|freq
op_assign
id|data
suffix:semicolon
r_int
r_int
op_star
id|lpj
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|lpj
op_assign
op_amp
id|cpu_data
(braket
id|freq-&gt;cpu
)braket
dot
id|loops_per_jiffy
suffix:semicolon
macro_line|#else
id|lpj
op_assign
op_amp
id|boot_cpu_data.loops_per_jiffy
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|ref_freq
)paren
(brace
id|ref_freq
op_assign
id|freq-&gt;old
suffix:semicolon
id|loops_per_jiffy_ref
op_assign
op_star
id|lpj
suffix:semicolon
id|cpu_khz_ref
op_assign
id|cpu_khz
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|val
op_eq
id|CPUFREQ_PRECHANGE
op_logical_and
id|freq-&gt;old
OL
id|freq
op_member_access_from_pointer
r_new
)paren
op_logical_or
(paren
id|val
op_eq
id|CPUFREQ_POSTCHANGE
op_logical_and
id|freq-&gt;old
OG
id|freq
op_member_access_from_pointer
r_new
)paren
)paren
(brace
op_star
id|lpj
op_assign
id|cpufreq_scale
c_func
(paren
id|loops_per_jiffy_ref
comma
id|ref_freq
comma
id|freq
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
id|cpu_khz
op_assign
id|cpufreq_scale
c_func
(paren
id|cpu_khz_ref
comma
id|ref_freq
comma
id|freq
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
id|vxtime.tsc_quot
op_assign
(paren
l_int|1000L
op_lshift
l_int|32
)paren
op_div
id|cpu_khz
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|time_cpufreq_notifier_block
r_static
r_struct
id|notifier_block
id|time_cpufreq_notifier_block
op_assign
(brace
dot
id|notifier_call
op_assign
id|time_cpufreq_notifier
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * calibrate_tsc() calibrates the processor TSC in a very simple way, comparing&n; * it to the HPET timer of known frequency.&n; */
DECL|macro|TICK_COUNT
mdefine_line|#define TICK_COUNT 100000000
DECL|function|hpet_calibrate_tsc
r_static
r_int
r_int
id|__init
id|hpet_calibrate_tsc
c_func
(paren
r_void
)paren
(brace
r_int
id|tsc_start
comma
id|hpet_start
suffix:semicolon
r_int
id|tsc_now
comma
id|hpet_now
suffix:semicolon
r_int
r_int
id|flags
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
id|hpet_start
op_assign
id|hpet_readl
c_func
(paren
id|HPET_COUNTER
)paren
suffix:semicolon
id|rdtscl
c_func
(paren
id|tsc_start
)paren
suffix:semicolon
r_do
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|hpet_now
op_assign
id|hpet_readl
c_func
(paren
id|HPET_COUNTER
)paren
suffix:semicolon
id|sync_core
c_func
(paren
)paren
suffix:semicolon
id|rdtscl
c_func
(paren
id|tsc_now
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|tsc_now
op_minus
id|tsc_start
)paren
OL
id|TICK_COUNT
op_logical_and
(paren
id|hpet_now
op_minus
id|hpet_start
)paren
OL
id|TICK_COUNT
)paren
suffix:semicolon
r_return
(paren
id|tsc_now
op_minus
id|tsc_start
)paren
op_star
l_int|1000000000L
op_div
(paren
(paren
id|hpet_now
op_minus
id|hpet_start
)paren
op_star
id|hpet_period
op_div
l_int|1000
)paren
suffix:semicolon
)brace
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8253_lock
comma
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
DECL|function|hpet_init
r_static
r_int
id|hpet_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cfg
comma
id|id
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vxtime.hpet_address
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|set_fixmap_nocache
c_func
(paren
id|FIX_HPET_BASE
comma
id|vxtime.hpet_address
)paren
suffix:semicolon
id|__set_fixmap
c_func
(paren
id|VSYSCALL_HPET
comma
id|vxtime.hpet_address
comma
id|PAGE_KERNEL_VSYSCALL_NOCACHE
)paren
suffix:semicolon
multiline_comment|/*&n; * Read the period, compute tick and quotient.&n; */
id|id
op_assign
id|hpet_readl
c_func
(paren
id|HPET_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|id
op_amp
id|HPET_ID_VENDOR
)paren
op_logical_or
op_logical_neg
(paren
id|id
op_amp
id|HPET_ID_NUMBER
)paren
op_logical_or
op_logical_neg
(paren
id|id
op_amp
id|HPET_ID_LEGSUP
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|hpet_period
op_assign
id|hpet_readl
c_func
(paren
id|HPET_PERIOD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hpet_period
template_param
l_int|100000000
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|hpet_tick
op_assign
(paren
l_int|1000000000L
op_star
(paren
id|USEC_PER_SEC
op_div
id|HZ
)paren
op_plus
id|hpet_period
op_div
l_int|2
)paren
op_div
id|hpet_period
suffix:semicolon
multiline_comment|/*&n; * Stop the timers and reset the main counter.&n; */
id|cfg
op_assign
id|hpet_readl
c_func
(paren
id|HPET_CFG
)paren
suffix:semicolon
id|cfg
op_and_assign
op_complement
(paren
id|HPET_CFG_ENABLE
op_or
id|HPET_CFG_LEGACY
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cfg
comma
id|HPET_CFG
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
l_int|0
comma
id|HPET_COUNTER
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
l_int|0
comma
id|HPET_COUNTER
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n; * Set up timer 0, as periodic with first interrupt to happen at hpet_tick,&n; * and period also hpet_tick.&n; */
id|hpet_writel
c_func
(paren
id|HPET_T0_ENABLE
op_or
id|HPET_T0_PERIODIC
op_or
id|HPET_T0_SETVAL
op_or
id|HPET_T0_32BIT
comma
id|HPET_T0_CFG
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
id|hpet_tick
comma
id|HPET_T0_CMP
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
id|hpet_tick
comma
id|HPET_T0_CMP
)paren
suffix:semicolon
multiline_comment|/*&n; * Go!&n; */
id|cfg
op_or_assign
id|HPET_CFG_ENABLE
op_or
id|HPET_CFG_LEGACY
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cfg
comma
id|HPET_CFG
)paren
suffix:semicolon
r_return
l_int|0
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
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
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
id|report_lost_ticks
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
r_char
op_star
id|timename
suffix:semicolon
macro_line|#ifdef HPET_HACK_ENABLE_DANGEROUS
r_if
c_cond
(paren
op_logical_neg
id|vxtime.hpet_address
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;time.c: WARNING: Enabling HPET base &quot;
l_string|&quot;manually!&bslash;n&quot;
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x800038a0
comma
l_int|0xcf8
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0xff000001
comma
l_int|0xcfc
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x800038a0
comma
l_int|0xcf8
)paren
suffix:semicolon
id|hpet_address
op_assign
id|inl
c_func
(paren
l_int|0xcfc
)paren
op_amp
l_int|0xfffffffe
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;time.c: WARNING: Enabled HPET &quot;
l_string|&quot;at %#lx.&bslash;n&quot;
comma
id|hpet_address
)paren
suffix:semicolon
)brace
macro_line|#endif
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
r_if
c_cond
(paren
op_logical_neg
id|hpet_init
c_func
(paren
)paren
)paren
(brace
id|vxtime_hz
op_assign
(paren
l_int|1000000000000000L
op_plus
id|hpet_period
op_div
l_int|2
)paren
op_div
id|hpet_period
suffix:semicolon
id|cpu_khz
op_assign
id|hpet_calibrate_tsc
c_func
(paren
)paren
suffix:semicolon
id|timename
op_assign
l_string|&quot;HPET&quot;
suffix:semicolon
)brace
r_else
(brace
id|pit_init
c_func
(paren
)paren
suffix:semicolon
id|cpu_khz
op_assign
id|pit_calibrate_tsc
c_func
(paren
)paren
suffix:semicolon
id|timename
op_assign
l_string|&quot;PIT&quot;
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;time.c: Using %ld.%06ld MHz %s timer.&bslash;n&quot;
comma
id|vxtime_hz
op_div
l_int|1000000
comma
id|vxtime_hz
op_mod
l_int|1000000
comma
id|timename
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
id|vxtime.mode
op_assign
id|VXTIME_TSC
suffix:semicolon
id|vxtime.quot
op_assign
(paren
l_int|1000000L
op_lshift
l_int|32
)paren
op_div
id|vxtime_hz
suffix:semicolon
id|vxtime.tsc_quot
op_assign
(paren
l_int|1000L
op_lshift
l_int|32
)paren
op_div
id|cpu_khz
suffix:semicolon
id|vxtime.hz
op_assign
id|vxtime_hz
suffix:semicolon
id|rdtscll_sync
c_func
(paren
op_amp
id|vxtime.last_tsc
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
macro_line|#ifdef CONFIG_CPU_FREQ
id|cpufreq_register_notifier
c_func
(paren
op_amp
id|time_cpufreq_notifier_block
comma
id|CPUFREQ_TRANSITION_NOTIFIER
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|time_init_smp
r_void
id|__init
id|time_init_smp
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|timetype
suffix:semicolon
r_if
c_cond
(paren
id|vxtime.hpet_address
)paren
(brace
id|timetype
op_assign
l_string|&quot;HPET&quot;
suffix:semicolon
id|vxtime.last
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T0_CMP
)paren
op_minus
id|hpet_tick
suffix:semicolon
id|vxtime.mode
op_assign
id|VXTIME_HPET
suffix:semicolon
id|do_gettimeoffset
op_assign
id|do_gettimeoffset_hpet
suffix:semicolon
)brace
r_else
(brace
id|timetype
op_assign
l_string|&quot;PIT/TSC&quot;
suffix:semicolon
id|vxtime.mode
op_assign
id|VXTIME_TSC
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;time.c: Using %s based timekeeping.&bslash;n&quot;
comma
id|timetype
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
