multiline_comment|/*&n; *  linux/arch/parisc/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *  Modifications for ARM (C) 1994, 1995, 1996,1997 Russell King&n; *  Copyright (C) 1999 SuSE GmbH, (Philipp Rumpf, prumpf@tux.org)&n; *&n; * 1994-07-02  Alan Modra&n; *             fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1998-12-20  Updated NTP code according to technical memorandum Jan &squot;96&n; *             &quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/led.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
multiline_comment|/* xtime and wall_jiffies keep wall-clock time */
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|variable|clocktick
r_static
r_int
id|clocktick
suffix:semicolon
multiline_comment|/* timer cycles per tick */
DECL|variable|halftick
r_static
r_int
id|halftick
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_do_timer
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_static
r_inline
r_void
DECL|function|parisc_do_profile
id|parisc_do_profile
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pc
op_assign
id|regs-&gt;iaoq
(braket
l_int|0
)braket
suffix:semicolon
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
r_extern
r_char
id|_stext
suffix:semicolon
id|profile_hook
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
macro_line|#if 0
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
macro_line|#endif
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
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds PC values silently,&n;&t; * put them into the last histogram slot, so if&n;&t; * present, they will show up as a sharp peak.&n;&t; */
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
id|now
suffix:semicolon
r_int
id|next_tick
suffix:semicolon
r_int
id|nticks
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|parisc_do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
id|now
op_assign
id|mfctl
c_func
(paren
l_int|16
)paren
suffix:semicolon
multiline_comment|/* initialize next_tick to time at last clocktick */
id|next_tick
op_assign
id|cpu_data
(braket
id|cpu
)braket
dot
id|it_value
suffix:semicolon
multiline_comment|/* since time passes between the interrupt and the mfctl()&n;&t; * above, it is never true that last_tick + clocktick == now.  If we&n;&t; * never miss a clocktick, we could set next_tick = last_tick + clocktick&n;&t; * but maybe we&squot;ll miss ticks, hence the loop.&n;&t; *&n;&t; * Variables are *signed*.&n;&t; */
id|nticks
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|next_tick
op_minus
id|now
)paren
OL
id|halftick
)paren
(brace
id|next_tick
op_add_assign
id|clocktick
suffix:semicolon
id|nticks
op_increment
suffix:semicolon
)brace
id|mtctl
c_func
(paren
id|next_tick
comma
l_int|16
)paren
suffix:semicolon
id|cpu_data
(braket
id|cpu
)braket
dot
id|it_value
op_assign
id|next_tick
suffix:semicolon
r_while
c_loop
(paren
id|nticks
op_decrement
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|smp_do_timer
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
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|do_timer
c_func
(paren
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
)brace
)brace
macro_line|#ifdef CONFIG_CHASSIS_LCD_LED
multiline_comment|/* Only schedule the led tasklet on cpu 0, and only if it&n;&t; * is enabled.&n;&t; */
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
op_logical_and
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|led_tasklet.count
)paren
)paren
id|tasklet_schedule
c_func
(paren
op_amp
id|led_tasklet
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* check soft power switch status */
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
op_logical_and
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|power_tasklet.count
)paren
)paren
id|tasklet_schedule
c_func
(paren
op_amp
id|power_tasklet
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*** converted from ia64 ***/
multiline_comment|/*&n; * Return the number of micro-seconds that elapsed since the last&n; * update to wall time (aka xtime aka wall_jiffies).  The xtime_lock&n; * must be at least read-locked when calling this routine.&n; */
r_static
r_inline
r_int
r_int
DECL|function|gettimeoffset
id|gettimeoffset
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_SMP
multiline_comment|/*&n;&t; * FIXME: This won&squot;t work on smp because jiffies are updated by cpu 0.&n;&t; *    Once parisc-linux learns the cr16 difference between processors,&n;&t; *    this could be made to work.&n;&t; */
r_int
id|last_tick
suffix:semicolon
r_int
id|elapsed_cycles
suffix:semicolon
multiline_comment|/* it_value is the intended time of the next tick */
id|last_tick
op_assign
id|cpu_data
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|it_value
suffix:semicolon
multiline_comment|/* Subtract one tick and account for possible difference between&n;&t; * when we expected the tick and when it actually arrived.&n;&t; * (aka wall vs real)&n;&t; */
id|last_tick
op_sub_assign
id|clocktick
op_star
(paren
id|jiffies
op_minus
id|wall_jiffies
op_plus
l_int|1
)paren
suffix:semicolon
id|elapsed_cycles
op_assign
id|mfctl
c_func
(paren
l_int|16
)paren
op_minus
id|last_tick
suffix:semicolon
multiline_comment|/* the precision of this math could be improved */
r_return
id|elapsed_cycles
op_div
(paren
id|PAGE0-&gt;mem_10msec
op_div
l_int|10000
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|do_gettimeofday
id|do_gettimeofday
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
comma
id|seq
comma
id|usec
comma
id|sec
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
op_increment
id|sec
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
r_int
DECL|function|do_settimeofday
id|do_settimeofday
(paren
r_struct
id|timeval
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
(brace
multiline_comment|/*&n;&t;&t; * This is revolting. We need to set &quot;xtime&quot;&n;&t;&t; * correctly. However, the value in this location is&n;&t;&t; * the value at the most recent update of wall time.&n;&t;&t; * Discover what correction gettimeofday would have&n;&t;&t; * done, and then undo it!&n;&t;&t; */
id|tv-&gt;tv_nsec
op_sub_assign
id|gettimeoffset
c_func
(paren
)paren
op_star
l_int|1000
suffix:semicolon
id|tv-&gt;tv_nsec
op_sub_assign
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
)brace
id|write_sequnlock_irq
c_func
(paren
op_amp
id|xtime_lock
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
r_int
r_int
id|next_tick
suffix:semicolon
r_static
r_struct
id|pdc_tod
id|tod_data
suffix:semicolon
id|clocktick
op_assign
(paren
l_int|100
op_star
id|PAGE0-&gt;mem_10msec
)paren
op_div
id|HZ
suffix:semicolon
id|halftick
op_assign
id|clocktick
op_div
l_int|2
suffix:semicolon
multiline_comment|/* Setup clock interrupt timing */
id|next_tick
op_assign
id|mfctl
c_func
(paren
l_int|16
)paren
suffix:semicolon
id|next_tick
op_add_assign
id|clocktick
suffix:semicolon
id|cpu_data
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|it_value
op_assign
id|next_tick
suffix:semicolon
multiline_comment|/* kick off Itimer (CR16) */
id|mtctl
c_func
(paren
id|next_tick
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdc_tod_read
c_func
(paren
op_amp
id|tod_data
)paren
op_eq
l_int|0
)paren
(brace
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|tod_data.tod_sec
suffix:semicolon
id|xtime.tv_nsec
op_assign
id|tod_data.tod_usec
op_star
l_int|1000
suffix:semicolon
id|write_sequnlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Error reading tod clock&bslash;n&quot;
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
l_int|0
suffix:semicolon
id|xtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
