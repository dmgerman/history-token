multiline_comment|/*&n; * &n; * Common time routines among all ppc machines.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) to merge&n; * Paul Mackerras&squot; version and mine for PReP and Pmac.&n; * MPC8xx/MBX changes by Dan Malek (dmalek@jlc.net).&n; * Converted for 64-bit by Mike Corrigan (mikejc@us.ibm.com)&n; *&n; * First round of bugfixes by Gabriel Paubert (paubert@iram.es)&n; * to make clock more stable (2.4.0-test5). The only thing&n; * that this code assumes is that the timebases have been synchronized&n; * by firmware on SMP and are never stopped (never do sleep&n; * on SMP then, nap and doze are OK).&n; * &n; * Speeded up do_gettimeofday by getting rid of references to&n; * xtime (which required locks for consistency). (mikejc@us.ibm.com)&n; *&n; * TODO (not necessarily in this file):&n; * - improve precision and reproducibility of timebase frequency&n; * measurement at boot time. (for iSeries, we calibrate the timebase&n; * against the Titan chip&squot;s clock.)&n; * - for astronomical applications: add a new function to get&n; * non ambiguous timestamps even around leap seconds. This needs&n; * a new timestamp format and a good name.&n; *&n; * 1997-09-10  Updated NTP code according to technical memorandum Jan &squot;96&n; *             &quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#ifdef CONFIG_PPC_ISERIES
macro_line|#include &lt;asm/iSeries/HvCallXm.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|jiffies_64
id|u64
id|jiffies_64
suffix:semicolon
multiline_comment|/* keep track of when we need to update the rtc */
DECL|variable|last_rtc_update
id|time_t
id|last_rtc_update
suffix:semicolon
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
r_extern
r_int
id|piranha_simulator
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|variable|iSeries_recal_titan
r_int
r_int
id|iSeries_recal_titan
op_assign
l_int|0
suffix:semicolon
DECL|variable|iSeries_recal_tb
r_int
r_int
id|iSeries_recal_tb
op_assign
l_int|0
suffix:semicolon
DECL|variable|first_settimeofday
r_static
r_int
r_int
id|first_settimeofday
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
DECL|macro|XSEC_PER_SEC
mdefine_line|#define XSEC_PER_SEC (1024*1024)
DECL|macro|USEC_PER_SEC
mdefine_line|#define USEC_PER_SEC (1000000)
DECL|variable|tb_ticks_per_jiffy
r_int
r_int
id|tb_ticks_per_jiffy
suffix:semicolon
DECL|variable|tb_ticks_per_usec
r_int
r_int
id|tb_ticks_per_usec
suffix:semicolon
DECL|variable|tb_ticks_per_sec
r_int
r_int
id|tb_ticks_per_sec
suffix:semicolon
DECL|variable|next_xtime_sync_tb
r_int
r_int
id|next_xtime_sync_tb
suffix:semicolon
DECL|variable|xtime_sync_interval
r_int
r_int
id|xtime_sync_interval
suffix:semicolon
DECL|variable|tb_to_xs
r_int
r_int
id|tb_to_xs
suffix:semicolon
DECL|variable|tb_to_us
r_int
id|tb_to_us
suffix:semicolon
DECL|variable|processor_freq
r_int
r_int
id|processor_freq
suffix:semicolon
DECL|variable|rtc_lock
id|spinlock_t
id|rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|do_gtod
r_struct
id|gettimeofday_struct
id|do_gtod
suffix:semicolon
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
r_extern
r_int
r_int
id|lpEvent_count
suffix:semicolon
r_extern
r_int
id|smp_tb_synchronized
suffix:semicolon
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
r_extern
r_int
r_int
op_star
id|prof_buffer
suffix:semicolon
r_extern
r_int
r_int
id|prof_len
suffix:semicolon
r_extern
r_int
r_int
id|prof_shift
suffix:semicolon
r_extern
r_char
id|_stext
suffix:semicolon
r_void
id|ppc_adjtimex
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|adjusting_time
r_static
r_int
id|adjusting_time
op_assign
l_int|0
suffix:semicolon
DECL|function|ppc_do_profile
r_static
r_inline
r_void
id|ppc_do_profile
(paren
r_int
r_int
id|nip
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Only measure the CPUs specified by /proc/irq/prof_cpu_mask.&n;&t; * (default is all CPUs.)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
op_amp
id|prof_cpu_mask
)paren
)paren
r_return
suffix:semicolon
id|nip
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|nip
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds EIP values silently,&n;&t; * put them into the last histogram slot, so if&n;&t; * present, they will show up as a sharp peak.&n;&t; */
r_if
c_cond
(paren
id|nip
OG
id|prof_len
op_minus
l_int|1
)paren
id|nip
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
id|nip
)braket
)paren
suffix:semicolon
)brace
DECL|function|timer_check_rtc
r_static
id|__inline__
r_void
id|timer_check_rtc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;         * update the rtc when needed, this should be performed on the&n;         * right fraction of a second. Half or full second ?&n;         * Full second works on mk48t59 clocks, others need testing.&n;         * Note that this update is basically only used through &n;         * the adjtimex system calls. Setting the HW clock in&n;         * any other way is a /dev/rtc and userland business.&n;         * This is still wrong by -0.5/+1.5 jiffies because of the&n;         * timer interrupt resolution and possible delay, but here we &n;         * hit a quantization limit which can only be solved by higher&n;         * resolution timers and decoupling time management from timer&n;         * interrupts. This is also wrong on the clocks&n;         * which require being written at the half second boundary.&n;         * We should have an rtc call that only sets the minutes and&n;         * seconds like on Intel to avoid problems with non UTC clocks.&n;         */
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
op_minus
id|last_rtc_update
op_ge
l_int|659
op_logical_and
id|abs
c_func
(paren
id|xtime.tv_usec
op_minus
(paren
l_int|1000000
op_minus
l_int|1000000
op_div
id|HZ
)paren
)paren
OL
l_int|500000
op_div
id|HZ
op_logical_and
id|jiffies
op_minus
id|wall_jiffies
op_eq
l_int|1
)paren
(brace
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|to_tm
c_func
(paren
id|xtime.tv_sec
op_plus
l_int|1
comma
op_amp
id|tm
)paren
suffix:semicolon
id|tm.tm_year
op_sub_assign
l_int|1900
suffix:semicolon
id|tm.tm_mon
op_sub_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md
dot
id|set_rtc_time
c_func
(paren
op_amp
id|tm
)paren
op_eq
l_int|0
)paren
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_plus
l_int|1
suffix:semicolon
r_else
multiline_comment|/* Try again one minute later */
id|last_rtc_update
op_add_assign
l_int|60
suffix:semicolon
)brace
)brace
multiline_comment|/* Synchronize xtime with do_gettimeofday */
DECL|function|timer_sync_xtime
r_static
id|__inline__
r_void
id|timer_sync_xtime
c_func
(paren
r_int
r_int
id|cur_tb
)paren
(brace
r_struct
id|timeval
id|my_tv
suffix:semicolon
r_if
c_cond
(paren
id|cur_tb
OG
id|next_xtime_sync_tb
)paren
(brace
id|next_xtime_sync_tb
op_assign
id|cur_tb
op_plus
id|xtime_sync_interval
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|my_tv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xtime.tv_sec
op_le
id|my_tv.tv_sec
)paren
(brace
id|xtime.tv_sec
op_assign
id|my_tv.tv_sec
suffix:semicolon
id|xtime.tv_usec
op_assign
id|my_tv.tv_usec
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef CONFIG_PPC_ISERIES
multiline_comment|/* &n; * This function recalibrates the timebase based on the 49-bit time-of-day value in the Titan chip.&n; * The Titan is much more accurate than the value returned by the service processor for the&n; * timebase frequency.  &n; */
DECL|function|iSeries_tb_recal
r_static
r_void
id|iSeries_tb_recal
c_func
(paren
r_void
)paren
(brace
r_struct
id|div_result
id|divres
suffix:semicolon
r_int
r_int
id|titan
comma
id|tb
suffix:semicolon
id|tb
op_assign
id|get_tb
c_func
(paren
)paren
suffix:semicolon
id|titan
op_assign
id|HvCallXm_loadTod
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iSeries_recal_titan
)paren
(brace
r_int
r_int
id|tb_ticks
op_assign
id|tb
op_minus
id|iSeries_recal_tb
suffix:semicolon
r_int
r_int
id|titan_usec
op_assign
(paren
id|titan
op_minus
id|iSeries_recal_titan
)paren
op_rshift
l_int|12
suffix:semicolon
r_int
r_int
id|new_tb_ticks_per_sec
op_assign
(paren
id|tb_ticks
op_star
id|USEC_PER_SEC
)paren
op_div
id|titan_usec
suffix:semicolon
r_int
r_int
id|new_tb_ticks_per_jiffy
op_assign
(paren
id|new_tb_ticks_per_sec
op_plus
(paren
id|HZ
op_div
l_int|2
)paren
)paren
op_div
id|HZ
suffix:semicolon
r_int
id|tick_diff
op_assign
id|new_tb_ticks_per_jiffy
op_minus
id|tb_ticks_per_jiffy
suffix:semicolon
r_char
id|sign
op_assign
l_char|&squot;+&squot;
suffix:semicolon
multiline_comment|/* make sure tb_ticks_per_sec and tb_ticks_per_jiffy are consistent */
id|new_tb_ticks_per_sec
op_assign
id|new_tb_ticks_per_jiffy
op_star
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|tick_diff
OL
l_int|0
)paren
(brace
id|tick_diff
op_assign
op_minus
id|tick_diff
suffix:semicolon
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tick_diff
)paren
(brace
r_if
c_cond
(paren
id|tick_diff
OL
id|tb_ticks_per_jiffy
op_div
l_int|25
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Titan recalibrate: new tb_ticks_per_jiffy = %lu (%c%ld)&bslash;n&quot;
comma
id|new_tb_ticks_per_jiffy
comma
id|sign
comma
id|tick_diff
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|new_tb_ticks_per_jiffy
suffix:semicolon
id|tb_ticks_per_sec
op_assign
id|new_tb_ticks_per_sec
suffix:semicolon
id|div128_by_32
c_func
(paren
id|XSEC_PER_SEC
comma
l_int|0
comma
id|tb_ticks_per_sec
comma
op_amp
id|divres
)paren
suffix:semicolon
id|do_gtod.tb_ticks_per_sec
op_assign
id|tb_ticks_per_sec
suffix:semicolon
id|tb_to_xs
op_assign
id|divres.result_low
suffix:semicolon
id|do_gtod.varp-&gt;tb_to_xs
op_assign
id|tb_to_xs
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Titan recalibrate: FAILED (difference &gt; 4 percent)&bslash;n&quot;
l_string|&quot;                   new tb_ticks_per_jiffy = %lu&bslash;n&quot;
l_string|&quot;                   old tb_ticks_per_jiffy = %lu&bslash;n&quot;
comma
id|new_tb_ticks_per_jiffy
comma
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
)brace
)brace
)brace
id|iSeries_recal_titan
op_assign
id|titan
suffix:semicolon
id|iSeries_recal_tb
op_assign
id|tb
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * For iSeries shared processors, we have to let the hypervisor&n; * set the hardware decrementer.  We set a virtual decrementer&n; * in the ItLpPaca and call the hypervisor if the virtual&n; * decrementer is less than the current value in the hardware&n; * decrementer. (almost always the new decrementer value will&n; * be greater than the current hardware decementer so the hypervisor&n; * call will not be needed)&n; */
DECL|variable|tb_last_stamp
r_int
r_int
id|tb_last_stamp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * timer_interrupt - gets called when the decrementer overflows,&n; * with interrupts disabled.&n; */
DECL|function|timer_interrupt
r_int
id|timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|next_dec
suffix:semicolon
r_int
r_int
id|cur_tb
suffix:semicolon
r_struct
id|paca_struct
op_star
id|lpaca
op_assign
id|get_paca
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|lpaca-&gt;xPacaIndex
suffix:semicolon
r_struct
id|ItLpQueue
op_star
id|lpq
suffix:semicolon
id|irq_enter
c_func
(paren
id|cpu
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PPC_ISERIES
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
id|ppc_do_profile
c_func
(paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
macro_line|#endif
id|lpaca-&gt;xLpPaca.xIntDword.xFields.xDecrInt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|lpaca-&gt;next_jiffy_update_tb
op_le
(paren
id|cur_tb
op_assign
id|get_tb
c_func
(paren
)paren
)paren
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|smp_local_timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|tb_last_stamp
op_assign
id|lpaca-&gt;next_jiffy_update_tb
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|timer_sync_xtime
c_func
(paren
id|cur_tb
)paren
suffix:semicolon
id|timer_check_rtc
c_func
(paren
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adjusting_time
op_logical_and
(paren
id|time_adjust
op_eq
l_int|0
)paren
)paren
id|ppc_adjtimex
c_func
(paren
)paren
suffix:semicolon
)brace
id|lpaca-&gt;next_jiffy_update_tb
op_add_assign
id|tb_ticks_per_jiffy
suffix:semicolon
)brace
id|next_dec
op_assign
id|lpaca-&gt;next_jiffy_update_tb
op_minus
id|cur_tb
suffix:semicolon
r_if
c_cond
(paren
id|next_dec
OG
id|lpaca-&gt;default_decr
)paren
id|next_dec
op_assign
id|lpaca-&gt;default_decr
suffix:semicolon
id|set_dec
c_func
(paren
id|next_dec
)paren
suffix:semicolon
id|lpq
op_assign
id|lpaca-&gt;lpQueuePtr
suffix:semicolon
r_if
c_cond
(paren
id|lpq
op_logical_and
id|ItLpQueue_isLpIntPending
c_func
(paren
id|lpq
)paren
)paren
id|lpEvent_count
op_add_assign
id|ItLpQueue_process
c_func
(paren
id|lpq
comma
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
id|cpu
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
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This version of gettimeofday has microsecond resolution.&n; */
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
id|sec
comma
id|usec
comma
id|tb_ticks
suffix:semicolon
r_int
r_int
id|xsec
comma
id|tb_xsec
suffix:semicolon
r_struct
id|gettimeofday_vars
op_star
id|temp_varp
suffix:semicolon
r_int
r_int
id|temp_tb_to_xs
comma
id|temp_stamp_xsec
suffix:semicolon
multiline_comment|/* These calculations are faster (gets rid of divides)&n;&t; * if done in units of 1/2^20 rather than microseconds.&n;&t; * The conversion to microseconds at the end is done&n;&t; * without a divide (and in fact, without a multiply) */
id|tb_ticks
op_assign
id|get_tb
c_func
(paren
)paren
op_minus
id|do_gtod.tb_orig_stamp
suffix:semicolon
id|temp_varp
op_assign
id|do_gtod.varp
suffix:semicolon
id|temp_tb_to_xs
op_assign
id|temp_varp-&gt;tb_to_xs
suffix:semicolon
id|temp_stamp_xsec
op_assign
id|temp_varp-&gt;stamp_xsec
suffix:semicolon
id|tb_xsec
op_assign
id|mulhdu
c_func
(paren
id|tb_ticks
comma
id|temp_tb_to_xs
)paren
suffix:semicolon
id|xsec
op_assign
id|temp_stamp_xsec
op_plus
id|tb_xsec
suffix:semicolon
id|sec
op_assign
id|xsec
op_div
id|XSEC_PER_SEC
suffix:semicolon
id|xsec
op_sub_assign
id|sec
op_star
id|XSEC_PER_SEC
suffix:semicolon
id|usec
op_assign
(paren
id|xsec
op_star
id|USEC_PER_SEC
)paren
op_div
id|XSEC_PER_SEC
suffix:semicolon
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
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|delta_xsec
suffix:semicolon
r_int
r_int
id|tb_delta
comma
id|new_usec
comma
id|new_sec
suffix:semicolon
r_int
r_int
id|new_xsec
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Updating the RTC is not the job of this code. If the time is&n;&t; * stepped under NTP, the RTC will be update after STA_UNSYNC&n;&t; * is cleared. Tool like clock/hwclock either copy the RTC&n;&t; * to the system time, in which case there is no point in writing&n;&t; * to the RTC again, or write to the RTC but then they don&squot;t call&n;&t; * settimeofday to perform this operation.&n;&t; */
macro_line|#ifdef CONFIG_PPC_ISERIES
r_if
c_cond
(paren
id|first_settimeofday
)paren
(brace
id|iSeries_tb_recal
c_func
(paren
)paren
suffix:semicolon
id|first_settimeofday
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|tb_delta
op_assign
id|tb_ticks_since
c_func
(paren
id|tb_last_stamp
)paren
suffix:semicolon
id|tb_delta
op_add_assign
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_star
id|tb_ticks_per_jiffy
suffix:semicolon
id|new_sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|new_usec
op_assign
id|tv-&gt;tv_usec
op_minus
id|tb_delta
op_div
id|tb_ticks_per_usec
suffix:semicolon
r_while
c_loop
(paren
id|new_usec
OL
l_int|0
)paren
(brace
id|new_sec
op_decrement
suffix:semicolon
id|new_usec
op_add_assign
id|USEC_PER_SEC
suffix:semicolon
)brace
id|xtime.tv_usec
op_assign
id|new_usec
suffix:semicolon
id|xtime.tv_sec
op_assign
id|new_sec
suffix:semicolon
multiline_comment|/* In case of a large backwards jump in time with NTP, we want the &n;&t; * clock to be updated as soon as the PLL is again in lock.&n;&t; */
id|last_rtc_update
op_assign
id|new_sec
op_minus
l_int|658
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
id|delta_xsec
op_assign
id|mulhdu
c_func
(paren
(paren
id|tb_last_stamp
op_minus
id|do_gtod.tb_orig_stamp
)paren
comma
id|do_gtod.varp-&gt;tb_to_xs
)paren
suffix:semicolon
id|new_xsec
op_assign
(paren
id|new_usec
op_star
id|XSEC_PER_SEC
)paren
op_div
id|USEC_PER_SEC
suffix:semicolon
id|new_xsec
op_add_assign
id|new_sec
op_star
id|XSEC_PER_SEC
suffix:semicolon
r_if
c_cond
(paren
id|new_xsec
OG
id|delta_xsec
)paren
(brace
id|do_gtod.varp-&gt;stamp_xsec
op_assign
id|new_xsec
op_minus
id|delta_xsec
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This is only for the case where the user is setting the time&n;&t;&t; * way back to a time such that the boot time would have been&n;&t;&t; * before 1970 ... eg. we booted ten days ago, and we are setting&n;&t;&t; * the time to Jan 5, 1970 */
id|do_gtod.varp-&gt;stamp_xsec
op_assign
id|new_xsec
suffix:semicolon
id|do_gtod.tb_orig_stamp
op_assign
id|tb_last_stamp
suffix:semicolon
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is a copy of the architecture independent function&n; * but which calls do_settimeofday rather than setting the xtime&n; * fields itself.  This way, the fields which are used for &n; * do_settimeofday get updated too.&n; */
DECL|function|ppc64_sys32_stime
r_int
id|ppc64_sys32_stime
c_func
(paren
r_int
op_star
id|tptr
)paren
(brace
r_int
id|value
suffix:semicolon
r_struct
id|timeval
id|myTimeval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|value
comma
id|tptr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|myTimeval.tv_sec
op_assign
id|value
suffix:semicolon
id|myTimeval.tv_usec
op_assign
l_int|0
suffix:semicolon
id|do_settimeofday
c_func
(paren
op_amp
id|myTimeval
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is a copy of the architecture independent function&n; * but which calls do_settimeofday rather than setting the xtime&n; * fields itself.  This way, the fields which are used for &n; * do_settimeofday get updated too.&n; */
DECL|function|ppc64_sys_stime
r_int
id|ppc64_sys_stime
c_func
(paren
r_int
op_star
id|tptr
)paren
(brace
r_int
id|value
suffix:semicolon
r_struct
id|timeval
id|myTimeval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|value
comma
id|tptr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|myTimeval.tv_sec
op_assign
id|value
suffix:semicolon
id|myTimeval.tv_usec
op_assign
l_int|0
suffix:semicolon
id|do_settimeofday
c_func
(paren
op_amp
id|myTimeval
)paren
suffix:semicolon
r_return
l_int|0
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
multiline_comment|/* This function is only called on the boot processor */
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|ppc_md
dot
id|calibrate_decr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|piranha_simulator
)paren
(brace
id|ppc_md
dot
id|get_boot_time
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
)brace
id|write_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|tm.tm_year
op_plus
l_int|1900
comma
id|tm.tm_mon
op_plus
l_int|1
comma
id|tm.tm_mday
comma
id|tm.tm_hour
comma
id|tm.tm_min
comma
id|tm.tm_sec
)paren
suffix:semicolon
id|tb_last_stamp
op_assign
id|get_tb
c_func
(paren
)paren
suffix:semicolon
id|do_gtod.tb_orig_stamp
op_assign
id|tb_last_stamp
suffix:semicolon
id|do_gtod.varp
op_assign
op_amp
id|do_gtod.vars
(braket
l_int|0
)braket
suffix:semicolon
id|do_gtod.var_idx
op_assign
l_int|0
suffix:semicolon
id|do_gtod.varp-&gt;stamp_xsec
op_assign
id|xtime.tv_sec
op_star
id|XSEC_PER_SEC
suffix:semicolon
id|do_gtod.tb_ticks_per_sec
op_assign
id|tb_ticks_per_sec
suffix:semicolon
id|do_gtod.varp-&gt;tb_to_xs
op_assign
id|tb_to_xs
suffix:semicolon
id|do_gtod.tb_to_us
op_assign
id|tb_to_us
suffix:semicolon
id|xtime_sync_interval
op_assign
id|tb_ticks_per_sec
op_minus
(paren
id|tb_ticks_per_sec
op_div
l_int|8
)paren
suffix:semicolon
id|next_xtime_sync_tb
op_assign
id|tb_last_stamp
op_plus
id|xtime_sync_interval
suffix:semicolon
id|time_freq
op_assign
l_int|0
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
multiline_comment|/* HACK HACK This allows the iSeries profiling to use /proc/profile */
id|prof_shift
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Not exact, but the timer interrupt takes care of this */
id|set_dec
c_func
(paren
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * After adjtimex is called, adjust the conversion of tb ticks&n; * to microseconds to keep do_gettimeofday synchronized &n; * with ntpd.&n;&n; * Use the time_adjust, time_freq and time_offset computed by adjtimex to &n; * adjust the frequency.&n;*/
multiline_comment|/* #define DEBUG_PPC_ADJTIMEX 1 */
DECL|function|ppc_adjtimex
r_void
id|ppc_adjtimex
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|den
comma
id|new_tb_ticks_per_sec
comma
id|tb_ticks
comma
id|old_xsec
comma
id|new_tb_to_xs
comma
id|new_xsec
comma
id|new_stamp_xsec
suffix:semicolon
r_int
r_int
id|tb_ticks_per_sec_delta
suffix:semicolon
r_int
id|delta_freq
comma
id|ltemp
suffix:semicolon
r_struct
id|div_result
id|divres
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|gettimeofday_vars
op_star
id|temp_varp
suffix:semicolon
r_int
id|temp_idx
suffix:semicolon
r_int
id|singleshot_ppm
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Compute parts per million frequency adjustment to accomplish the time adjustment&n;&t;   implied by time_offset to be applied over the elapsed time indicated by time_constant.&n;&t;   Use SHIFT_USEC to get it into the same units as time_freq. */
r_if
c_cond
(paren
id|time_offset
OL
l_int|0
)paren
(brace
id|ltemp
op_assign
op_minus
id|time_offset
suffix:semicolon
id|ltemp
op_lshift_assign
id|SHIFT_USEC
op_minus
id|SHIFT_UPDATE
suffix:semicolon
id|ltemp
op_rshift_assign
id|SHIFT_KG
op_plus
id|time_constant
suffix:semicolon
id|ltemp
op_assign
op_minus
id|ltemp
suffix:semicolon
)brace
r_else
(brace
id|ltemp
op_assign
id|time_offset
suffix:semicolon
id|ltemp
op_lshift_assign
id|SHIFT_USEC
op_minus
id|SHIFT_UPDATE
suffix:semicolon
id|ltemp
op_rshift_assign
id|SHIFT_KG
op_plus
id|time_constant
suffix:semicolon
)brace
multiline_comment|/* If there is a single shot time adjustment in progress */
r_if
c_cond
(paren
id|time_adjust
)paren
(brace
macro_line|#ifdef DEBUG_PPC_ADJTIMEX
id|printk
c_func
(paren
l_string|&quot;ppc_adjtimex: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adjusting_time
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;starting &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;single shot time_adjust = %ld&bslash;n&quot;
comma
id|time_adjust
)paren
suffix:semicolon
macro_line|#endif&t;
id|adjusting_time
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Compute parts per million frequency adjustment to match time_adjust */
id|singleshot_ppm
op_assign
id|tickadj
op_star
id|HZ
suffix:semicolon
multiline_comment|/* The adjustment should be tickadj*HZ to match the code in linux/kernel/timer.c, but&n;&t;&t;   experiments show that this is too large. 3/4 of tickadj*HZ seems about right */
id|singleshot_ppm
op_sub_assign
id|singleshot_ppm
op_div
l_int|4
suffix:semicolon
multiline_comment|/* Use SHIFT_USEC to get it into the same units as time_freq */
id|singleshot_ppm
op_lshift_assign
id|SHIFT_USEC
suffix:semicolon
r_if
c_cond
(paren
id|time_adjust
OL
l_int|0
)paren
id|singleshot_ppm
op_assign
op_minus
id|singleshot_ppm
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef DEBUG_PPC_ADJTIMEX
r_if
c_cond
(paren
id|adjusting_time
)paren
id|printk
c_func
(paren
l_string|&quot;ppc_adjtimex: ending single shot time_adjust&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|adjusting_time
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Add up all of the frequency adjustments */
id|delta_freq
op_assign
id|time_freq
op_plus
id|ltemp
op_plus
id|singleshot_ppm
suffix:semicolon
multiline_comment|/* Compute a new value for tb_ticks_per_sec based on the frequency adjustment */
id|den
op_assign
l_int|1000000
op_star
(paren
l_int|1
op_lshift
(paren
id|SHIFT_USEC
op_minus
l_int|8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta_freq
OL
l_int|0
)paren
(brace
id|tb_ticks_per_sec_delta
op_assign
(paren
id|tb_ticks_per_sec
op_star
(paren
(paren
op_minus
id|delta_freq
)paren
op_rshift
(paren
id|SHIFT_USEC
op_minus
l_int|8
)paren
)paren
)paren
op_div
id|den
suffix:semicolon
id|new_tb_ticks_per_sec
op_assign
id|tb_ticks_per_sec
op_plus
id|tb_ticks_per_sec_delta
suffix:semicolon
)brace
r_else
(brace
id|tb_ticks_per_sec_delta
op_assign
(paren
id|tb_ticks_per_sec
op_star
(paren
id|delta_freq
op_rshift
(paren
id|SHIFT_USEC
op_minus
l_int|8
)paren
)paren
)paren
op_div
id|den
suffix:semicolon
id|new_tb_ticks_per_sec
op_assign
id|tb_ticks_per_sec
op_minus
id|tb_ticks_per_sec_delta
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_PPC_ADJTIMEX
id|printk
c_func
(paren
l_string|&quot;ppc_adjtimex: ltemp = %ld, time_freq = %ld, singleshot_ppm = %ld&bslash;n&quot;
comma
id|ltemp
comma
id|time_freq
comma
id|singleshot_ppm
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ppc_adjtimex: tb_ticks_per_sec - base = %ld  new = %ld&bslash;n&quot;
comma
id|tb_ticks_per_sec
comma
id|new_tb_ticks_per_sec
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Compute a new value of tb_to_xs (used to convert tb to microseconds and a new value of &n;&t;   stamp_xsec which is the time (in 1/2^20 second units) corresponding to tb_orig_stamp.  This &n;&t;   new value of stamp_xsec compensates for the change in frequency (implied by the new tb_to_xs)&n;&t;   which guarantees that the current time remains the same */
id|tb_ticks
op_assign
id|get_tb
c_func
(paren
)paren
op_minus
id|do_gtod.tb_orig_stamp
suffix:semicolon
id|div128_by_32
c_func
(paren
l_int|1024
op_star
l_int|1024
comma
l_int|0
comma
id|new_tb_ticks_per_sec
comma
op_amp
id|divres
)paren
suffix:semicolon
id|new_tb_to_xs
op_assign
id|divres.result_low
suffix:semicolon
id|new_xsec
op_assign
id|mulhdu
c_func
(paren
id|tb_ticks
comma
id|new_tb_to_xs
)paren
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|old_xsec
op_assign
id|mulhdu
c_func
(paren
id|tb_ticks
comma
id|do_gtod.varp-&gt;tb_to_xs
)paren
suffix:semicolon
id|new_stamp_xsec
op_assign
id|do_gtod.varp-&gt;stamp_xsec
op_plus
id|old_xsec
op_minus
id|new_xsec
suffix:semicolon
multiline_comment|/* There are two copies of tb_to_xs and stamp_xsec so that no lock is needed to access and use these&n;&t;   values in do_gettimeofday.  We alternate the copies and as long as a reasonable time elapses between&n;&t;   changes, there will never be inconsistent values.  ntpd has a minimum of one minute between updates */
r_if
c_cond
(paren
id|do_gtod.var_idx
op_eq
l_int|0
)paren
(brace
id|temp_varp
op_assign
op_amp
id|do_gtod.vars
(braket
l_int|1
)braket
suffix:semicolon
id|temp_idx
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|temp_varp
op_assign
op_amp
id|do_gtod.vars
(braket
l_int|0
)braket
suffix:semicolon
id|temp_idx
op_assign
l_int|0
suffix:semicolon
)brace
id|temp_varp-&gt;tb_to_xs
op_assign
id|new_tb_to_xs
suffix:semicolon
id|temp_varp-&gt;stamp_xsec
op_assign
id|new_stamp_xsec
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|do_gtod.varp
op_assign
id|temp_varp
suffix:semicolon
id|do_gtod.var_idx
op_assign
id|temp_idx
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|macro|FEBRUARY
mdefine_line|#define FEBRUARY&t;2
DECL|macro|STARTOFTIME
mdefine_line|#define&t;STARTOFTIME&t;1970
DECL|macro|SECDAY
mdefine_line|#define SECDAY&t;&t;86400L
DECL|macro|SECYR
mdefine_line|#define SECYR&t;&t;(SECDAY * 365)
DECL|macro|leapyear
mdefine_line|#define&t;leapyear(year)&t;&t;((year) % 4 == 0)
DECL|macro|days_in_year
mdefine_line|#define&t;days_in_year(a) &t;(leapyear(a) ? 366 : 365)
DECL|macro|days_in_month
mdefine_line|#define&t;days_in_month(a) &t;(month_days[(a) - 1])
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
multiline_comment|/*&n; * This only works for the Gregorian calendar - i.e. after 1752 (in the UK)&n; */
DECL|function|GregorianDay
r_void
id|GregorianDay
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
r_int
id|leapsToDate
suffix:semicolon
r_int
id|lastYear
suffix:semicolon
r_int
id|day
suffix:semicolon
r_int
id|MonthOffset
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|59
comma
l_int|90
comma
l_int|120
comma
l_int|151
comma
l_int|181
comma
l_int|212
comma
l_int|243
comma
l_int|273
comma
l_int|304
comma
l_int|334
)brace
suffix:semicolon
id|lastYear
op_assign
id|tm-&gt;tm_year
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Number of leap corrections to apply up to end of last year&n;&t; */
id|leapsToDate
op_assign
id|lastYear
op_div
l_int|4
op_minus
id|lastYear
op_div
l_int|100
op_plus
id|lastYear
op_div
l_int|400
suffix:semicolon
multiline_comment|/*&n;&t; * This year is a leap year if it is divisible by 4 except when it is&n;&t; * divisible by 100 unless it is divisible by 400&n;&t; *&n;&t; * e.g. 1904 was a leap year, 1900 was not, 1996 is, and 2000 will be&n;&t; */
r_if
c_cond
(paren
(paren
id|tm-&gt;tm_year
op_mod
l_int|4
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
id|tm-&gt;tm_year
op_mod
l_int|100
op_ne
l_int|0
)paren
op_logical_or
(paren
id|tm-&gt;tm_year
op_mod
l_int|400
op_eq
l_int|0
)paren
)paren
op_logical_and
(paren
id|tm-&gt;tm_mon
OG
l_int|2
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We are past Feb. 29 in a leap year&n;&t;&t; */
id|day
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|day
op_assign
l_int|0
suffix:semicolon
)brace
id|day
op_add_assign
id|lastYear
op_star
l_int|365
op_plus
id|leapsToDate
op_plus
id|MonthOffset
(braket
id|tm-&gt;tm_mon
op_minus
l_int|1
)braket
op_plus
id|tm-&gt;tm_mday
suffix:semicolon
id|tm-&gt;tm_wday
op_assign
id|day
op_mod
l_int|7
suffix:semicolon
)brace
DECL|function|to_tm
r_void
id|to_tm
c_func
(paren
r_int
id|tim
comma
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_register
r_int
id|hms
comma
id|day
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
id|GregorianDay
c_func
(paren
id|tm
)paren
suffix:semicolon
)brace
multiline_comment|/* Auxiliary function to compute scaling factors */
multiline_comment|/* Actually the choice of a timebase running at 1/4 the of the bus&n; * frequency giving resolution of a few tens of nanoseconds is quite nice.&n; * It makes this computation very precise (27-28 bits typically) which&n; * is optimistic considering the stability of most processor clock&n; * oscillators and the precision with which the timebase frequency&n; * is measured but does not harm.&n; */
DECL|function|mulhwu_scale_factor
r_int
id|mulhwu_scale_factor
c_func
(paren
r_int
id|inscale
comma
r_int
id|outscale
)paren
(brace
r_int
id|mlt
op_assign
l_int|0
comma
id|tmp
comma
id|err
suffix:semicolon
multiline_comment|/* No concern for performance, it&squot;s done once: use a stupid&n;         * but safe and compact method to find the multiplier.&n;         */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|1U
op_lshift
l_int|31
suffix:semicolon
id|tmp
op_ne
l_int|0
suffix:semicolon
id|tmp
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|mulhwu
c_func
(paren
id|inscale
comma
id|mlt
op_or
id|tmp
)paren
OL
id|outscale
)paren
id|mlt
op_or_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* We might still be off by 1 for the best approximation.&n;         * A side effect of this is that if outscale is too large&n;         * the returned value will be zero.&n;         * Many corner cases have been checked and seem to work,&n;         * some might have been forgotten in the test however.&n;         */
id|err
op_assign
id|inscale
op_star
(paren
id|mlt
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_le
id|inscale
op_div
l_int|2
)paren
id|mlt
op_increment
suffix:semicolon
r_return
id|mlt
suffix:semicolon
)brace
multiline_comment|/*&n; * Divide a 128-bit dividend by a 32-bit divisor, leaving a 128 bit&n; * result.&n; */
DECL|function|div128_by_32
r_void
id|div128_by_32
c_func
(paren
r_int
r_int
id|dividend_high
comma
r_int
r_int
id|dividend_low
comma
r_int
id|divisor
comma
r_struct
id|div_result
op_star
id|dr
)paren
(brace
r_int
r_int
id|a
comma
id|b
comma
id|c
comma
id|d
comma
id|w
comma
id|x
comma
id|y
comma
id|z
comma
id|ra
comma
id|rb
comma
id|rc
suffix:semicolon
id|a
op_assign
id|dividend_high
op_rshift
l_int|32
suffix:semicolon
id|b
op_assign
id|dividend_high
op_amp
l_int|0xffffffff
suffix:semicolon
id|c
op_assign
id|dividend_low
op_rshift
l_int|32
suffix:semicolon
id|d
op_assign
id|dividend_low
op_amp
l_int|0xffffffff
suffix:semicolon
id|w
op_assign
id|a
op_div
id|divisor
suffix:semicolon
id|ra
op_assign
(paren
id|a
op_minus
(paren
id|w
op_star
id|divisor
)paren
)paren
op_lshift
l_int|32
suffix:semicolon
id|x
op_assign
(paren
id|ra
op_plus
id|b
)paren
op_div
id|divisor
suffix:semicolon
id|rb
op_assign
(paren
(paren
id|ra
op_plus
id|b
)paren
op_minus
(paren
id|x
op_star
id|divisor
)paren
)paren
op_lshift
l_int|32
suffix:semicolon
id|y
op_assign
(paren
id|rb
op_plus
id|c
)paren
op_div
id|divisor
suffix:semicolon
id|rc
op_assign
(paren
(paren
id|rb
op_plus
id|b
)paren
op_minus
(paren
id|y
op_star
id|divisor
)paren
)paren
op_lshift
l_int|32
suffix:semicolon
id|z
op_assign
(paren
id|rc
op_plus
id|d
)paren
op_div
id|divisor
suffix:semicolon
id|dr-&gt;result_high
op_assign
(paren
id|w
op_lshift
l_int|32
)paren
op_plus
id|x
suffix:semicolon
id|dr-&gt;result_low
op_assign
(paren
id|y
op_lshift
l_int|32
)paren
op_plus
id|z
suffix:semicolon
)brace
eof
