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
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &quot;mach_time.h&quot;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch_hooks.h&gt;
macro_line|#include &quot;io_ports.h&quot;
r_extern
id|spinlock_t
id|i8259A_lock
suffix:semicolon
DECL|variable|pit_latch_buggy
r_int
id|pit_latch_buggy
suffix:semicolon
multiline_comment|/* extern */
macro_line|#include &quot;do_timer.h&quot;
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
DECL|variable|cpu_khz
r_int
r_int
id|cpu_khz
suffix:semicolon
multiline_comment|/* Detected as we calibrate the TSC */
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
r_extern
r_struct
id|timer_opts
id|timer_none
suffix:semicolon
DECL|variable|timer
r_struct
id|timer_opts
op_star
id|timer
op_assign
op_amp
id|timer_none
suffix:semicolon
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
id|seq
suffix:semicolon
r_int
r_int
id|usec
comma
id|sec
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
id|timer
op_member_access_from_pointer
id|get_offset
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
multiline_comment|/*&n;&t; * This is revolting. We need to set &quot;xtime&quot; correctly. However, the&n;&t; * value in this location is the value at the most recent update of&n;&t; * wall time.  Discover what correction gettimeofday() would have&n;&t; * made, and then undo it!&n;&t; */
id|tv-&gt;tv_usec
op_sub_assign
id|timer
op_member_access_from_pointer
id|get_offset
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
id|USEC_PER_SEC
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
id|USEC_PER_SEC
suffix:semicolon
id|tv-&gt;tv_sec
op_decrement
suffix:semicolon
)brace
id|tv-&gt;tv_usec
op_mul_assign
id|NSEC_PER_USEC
suffix:semicolon
id|wall_to_monotonic.tv_sec
op_add_assign
id|xtime.tv_sec
op_minus
id|tv-&gt;tv_sec
suffix:semicolon
id|wall_to_monotonic.tv_nsec
op_add_assign
id|xtime.tv_nsec
op_minus
id|tv-&gt;tv_usec
suffix:semicolon
r_if
c_cond
(paren
id|wall_to_monotonic.tv_nsec
OG
id|NSEC_PER_SEC
)paren
(brace
id|wall_to_monotonic.tv_nsec
op_sub_assign
id|NSEC_PER_SEC
suffix:semicolon
id|wall_to_monotonic.tv_sec
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wall_to_monotonic.tv_nsec
OL
l_int|0
)paren
(brace
id|wall_to_monotonic.tv_nsec
op_add_assign
id|NSEC_PER_SEC
suffix:semicolon
id|wall_to_monotonic.tv_sec
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
suffix:semicolon
multiline_comment|/* gets recalled with irq locally disabled */
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|retval
op_assign
id|mach_set_rtc_mmss
c_func
(paren
id|nowtime
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
r_return
id|timer
op_member_access_from_pointer
id|monotonic_clock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|monotonic_clock
id|EXPORT_SYMBOL
c_func
(paren
id|monotonic_clock
)paren
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
id|PIC_MASTER_OCW3
)paren
suffix:semicolon
multiline_comment|/* Ack the IRQ; AEOI will end it automatically. */
id|inb
c_func
(paren
id|PIC_MASTER_POLL
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
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
op_ge
id|USEC_AFTER
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
id|USEC_BEFORE
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
multiline_comment|/*&n; * This is the same as the above, except we _also_ save the current&n; * Time Stamp Counter value at the time of the timer interrupt, so that&n; * we later on can estimate the time of day more exactly.&n; */
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
multiline_comment|/*&n;&t; * Here we are in the timer irq handler. We just have irqs locally&n;&t; * disabled but we don&squot;t know if the timer_bh is running on the other&n;&t; * CPU. We need to avoid to SMP race with it. NOTE: we don&squot; t need&n;&t; * the irq version of write_lock because as just said we have irq&n;&t; * locally disabled. -arca&n;&t; */
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|timer
op_member_access_from_pointer
id|mark_offset
c_func
(paren
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
r_return
id|IRQ_HANDLED
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
id|retval
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|retval
op_assign
id|mach_get_cmos_time
c_func
(paren
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
DECL|variable|rtc_sysclass
r_static
r_struct
id|sysdev_class
id|rtc_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;rtc&quot;
)paren
comma
)brace
suffix:semicolon
multiline_comment|/* XXX this driverfs stuff should probably go elsewhere later -john */
DECL|variable|device_i8253
r_static
r_struct
id|sys_device
id|device_i8253
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|rtc_sysclass
comma
)brace
suffix:semicolon
DECL|function|time_init_device
r_static
r_int
id|time_init_device
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|rtc_sysclass
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|sys_device_register
c_func
(paren
op_amp
id|device_i8253
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|time_init_device
id|device_initcall
c_func
(paren
id|time_init_device
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
id|wall_to_monotonic.tv_sec
op_assign
op_minus
id|xtime.tv_sec
op_plus
id|INITIAL_JIFFIES
op_div
id|HZ
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
id|wall_to_monotonic.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|timer
op_assign
id|select_timer
c_func
(paren
)paren
suffix:semicolon
id|time_init_hook
c_func
(paren
)paren
suffix:semicolon
)brace
eof
