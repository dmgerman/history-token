multiline_comment|/*&n; *  linux/arch/alpha/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992, 1995, 1999, 2000  Linus Torvalds&n; *&n; * This file contains the PC-specific time handling details:&n; * reading the RTC at bootup, etc..&n; * 1994-07-02    Alan Modra&n; *&t;fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; * 1995-03-26    Markus Kuhn&n; *      fixed 500 ms bug at call to set_rtc_mmss, fixed DS12887&n; *      precision CMOS clock update&n; * 1997-09-10&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; * 1997-01-09    Adrian Sun&n; *      use interval timer if CONFIG_RTC=y&n; * 1997-10-29    John Bowman (bowman@math.ualberta.ca)&n; *      fixed tick loss calculation in timer_interrupt&n; *      (round system clock to nearest tick instead of truncating)&n; *      fixed algorithm in time_init for getting time from CMOS clock&n; * 1999-04-16&t;Thorsten Kranzkowski (dl8bcu@gmx.net)&n; *&t;fixed algorithm in do_gettimeofday() for calculating the precise time&n; *&t;from processor cycle counter (now taking lost_ticks into account)&n; * 2000-08-13&t;Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&n; * &t;Fixed time_init to be aware of epoches != 1900. This prevents&n; * &t;booting up in 2048 for me;) Code is stolen from rtc.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
multiline_comment|/* kernel/timer.c */
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|variable|rtc_lock
id|spinlock_t
id|rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE (tick_nsec / 1000)
multiline_comment|/*&n; * Shift amount by which scaled_ticks_per_cycle is scaled.  Shifting&n; * by 48 gives us 16 bits for HZ while keeping the accuracy good even&n; * for large CPU clock rates.&n; */
DECL|macro|FIX_SHIFT
mdefine_line|#define FIX_SHIFT&t;48
multiline_comment|/* lump static variables together for more efficient access: */
r_static
r_struct
(brace
multiline_comment|/* cycle counter last time it got invoked */
DECL|member|last_time
id|__u32
id|last_time
suffix:semicolon
multiline_comment|/* ticks/cycle * 2^48 */
DECL|member|scaled_ticks_per_cycle
r_int
r_int
id|scaled_ticks_per_cycle
suffix:semicolon
multiline_comment|/* last time the CMOS clock got updated */
DECL|member|last_rtc_update
id|time_t
id|last_rtc_update
suffix:semicolon
multiline_comment|/* partial unused tick */
DECL|member|partial_tick
r_int
r_int
id|partial_tick
suffix:semicolon
DECL|variable|state
)brace
id|state
suffix:semicolon
DECL|variable|est_cycle_freq
r_int
r_int
id|est_cycle_freq
suffix:semicolon
DECL|function|rpcc
r_static
r_inline
id|__u32
id|rpcc
c_func
(paren
r_void
)paren
(brace
id|__u32
id|result
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;rpcc %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
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
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|delta
suffix:semicolon
id|__u32
id|now
suffix:semicolon
r_int
id|nticks
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
multiline_comment|/* Not SMP, do kernel PC profiling here.  */
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
id|alpha_do_profile
c_func
(paren
id|regs-&gt;pc
)paren
suffix:semicolon
macro_line|#endif
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate how many ticks have passed since the last update,&n;&t; * including any previous partial leftover.  Save any resulting&n;&t; * fraction for the next pass.&n;&t; */
id|now
op_assign
id|rpcc
c_func
(paren
)paren
suffix:semicolon
id|delta
op_assign
id|now
op_minus
id|state.last_time
suffix:semicolon
id|state.last_time
op_assign
id|now
suffix:semicolon
id|delta
op_assign
id|delta
op_star
id|state.scaled_ticks_per_cycle
op_plus
id|state.partial_tick
suffix:semicolon
id|state.partial_tick
op_assign
id|delta
op_amp
(paren
(paren
l_int|1UL
op_lshift
id|FIX_SHIFT
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|nticks
op_assign
id|delta
op_rshift
id|FIX_SHIFT
suffix:semicolon
r_while
c_loop
(paren
id|nticks
OG
l_int|0
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|nticks
op_decrement
suffix:semicolon
)brace
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
id|state.last_rtc_update
op_plus
l_int|660
op_logical_and
id|xtime.tv_nsec
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
id|xtime.tv_nsec
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
r_int
id|tmp
op_assign
id|set_rtc_mmss
c_func
(paren
id|xtime.tv_sec
)paren
suffix:semicolon
id|state.last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
(paren
id|tmp
ques
c_cond
l_int|600
suffix:colon
l_int|0
)paren
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
r_void
DECL|function|common_init_rtc
id|common_init_rtc
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|x
suffix:semicolon
multiline_comment|/* Reset periodic interrupt frequency.  */
id|x
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
l_int|0x3f
suffix:semicolon
r_if
c_cond
(paren
id|x
op_ne
l_int|0x26
op_logical_and
id|x
op_ne
l_int|0x19
op_logical_and
id|x
op_ne
l_int|0x06
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Setting RTC_FREQ to 1024 Hz (%x)&bslash;n&quot;
comma
id|x
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
l_int|0x26
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
)brace
multiline_comment|/* Turn on periodic interrupts.  */
id|x
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
id|RTC_PIE
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Turning on RTC interrupts.&bslash;n&quot;
)paren
suffix:semicolon
id|x
op_or_assign
id|RTC_PIE
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|RTC_AIE
op_or
id|RTC_UIE
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|x
comma
id|RTC_CONTROL
)paren
suffix:semicolon
)brace
(paren
r_void
)paren
id|CMOS_READ
c_func
(paren
id|RTC_INTR_FLAGS
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x36
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* pit counter 0: system timer */
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x40
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x40
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xb6
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* pit counter 2: speaker */
id|outb
c_func
(paren
l_int|0x31
comma
l_int|0x42
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x13
comma
l_int|0x42
)paren
suffix:semicolon
id|init_rtc_irq
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Validate a computed cycle counter result against the known bounds for&n;   the given processor core.  There&squot;s too much brokenness in the way of&n;   timing hardware for any one method to work everywhere.  :-(&n;&n;   Return 0 if the result cannot be trusted, otherwise return the argument.  */
r_static
r_int
r_int
id|__init
DECL|function|validate_cc_value
id|validate_cc_value
c_func
(paren
r_int
r_int
id|cc
)paren
(brace
r_static
r_struct
id|bounds
(brace
r_int
r_int
id|min
comma
id|max
suffix:semicolon
)brace
id|cpu_hz
(braket
)braket
id|__initdata
op_assign
(brace
(braket
id|EV3_CPU
)braket
op_assign
(brace
l_int|50000000
comma
l_int|200000000
)brace
comma
multiline_comment|/* guess */
(braket
id|EV4_CPU
)braket
op_assign
(brace
l_int|100000000
comma
l_int|300000000
)brace
comma
(braket
id|LCA4_CPU
)braket
op_assign
(brace
l_int|100000000
comma
l_int|300000000
)brace
comma
multiline_comment|/* guess */
(braket
id|EV45_CPU
)braket
op_assign
(brace
l_int|200000000
comma
l_int|300000000
)brace
comma
(braket
id|EV5_CPU
)braket
op_assign
(brace
l_int|250000000
comma
l_int|433000000
)brace
comma
(braket
id|EV56_CPU
)braket
op_assign
(brace
l_int|333000000
comma
l_int|667000000
)brace
comma
(braket
id|PCA56_CPU
)braket
op_assign
(brace
l_int|400000000
comma
l_int|600000000
)brace
comma
multiline_comment|/* guess */
(braket
id|PCA57_CPU
)braket
op_assign
(brace
l_int|500000000
comma
l_int|600000000
)brace
comma
multiline_comment|/* guess */
(braket
id|EV6_CPU
)braket
op_assign
(brace
l_int|466000000
comma
l_int|600000000
)brace
comma
(braket
id|EV67_CPU
)braket
op_assign
(brace
l_int|600000000
comma
l_int|750000000
)brace
comma
(braket
id|EV68AL_CPU
)braket
op_assign
(brace
l_int|750000000
comma
l_int|940000000
)brace
comma
(braket
id|EV68CB_CPU
)braket
op_assign
(brace
l_int|1000000000
comma
l_int|1333333333
)brace
comma
multiline_comment|/* None of the following are shipping as of 2001-11-01.  */
(braket
id|EV68CX_CPU
)braket
op_assign
(brace
l_int|1000000000
comma
l_int|1700000000
)brace
comma
multiline_comment|/* guess */
(braket
id|EV69_CPU
)braket
op_assign
(brace
l_int|1000000000
comma
l_int|1700000000
)brace
comma
multiline_comment|/* guess */
(braket
id|EV7_CPU
)braket
op_assign
(brace
l_int|800000000
comma
l_int|1400000000
)brace
comma
multiline_comment|/* guess */
(braket
id|EV79_CPU
)braket
op_assign
(brace
l_int|1000000000
comma
l_int|2000000000
)brace
comma
multiline_comment|/* guess */
)brace
suffix:semicolon
multiline_comment|/* Allow for some drift in the crystal.  10MHz is more than enough.  */
r_const
r_int
r_int
id|deviation
op_assign
l_int|10000000
suffix:semicolon
r_struct
id|percpu_struct
op_star
id|cpu
suffix:semicolon
r_int
r_int
id|index
suffix:semicolon
id|cpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
)paren
suffix:semicolon
id|index
op_assign
id|cpu-&gt;type
op_amp
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* If index out of bounds, no way to validate.  */
r_if
c_cond
(paren
id|index
op_ge
r_sizeof
(paren
id|cpu_hz
)paren
op_div
r_sizeof
(paren
id|cpu_hz
(braket
l_int|0
)braket
)paren
)paren
r_return
id|cc
suffix:semicolon
multiline_comment|/* If index contains no data, no way to validate.  */
r_if
c_cond
(paren
id|cpu_hz
(braket
id|index
)braket
dot
id|max
op_eq
l_int|0
)paren
r_return
id|cc
suffix:semicolon
r_if
c_cond
(paren
id|cc
template_param
id|cpu_hz
(braket
id|index
)braket
dot
id|max
op_plus
id|deviation
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|cc
suffix:semicolon
)brace
multiline_comment|/*&n; * Calibrate CPU clock using legacy 8254 timer/counter. Stolen from&n; * arch/i386/time.c.&n; */
DECL|macro|CALIBRATE_LATCH
mdefine_line|#define CALIBRATE_LATCH&t;(52 * LATCH)
DECL|macro|CALIBRATE_TIME
mdefine_line|#define CALIBRATE_TIME&t;(52 * 1000020 / HZ)
r_static
r_int
r_int
id|__init
DECL|function|calibrate_cc_with_pic
id|calibrate_cc_with_pic
c_func
(paren
r_void
)paren
(brace
r_int
id|cc
comma
id|count
op_assign
l_int|0
suffix:semicolon
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
id|cc
op_assign
id|rpcc
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|count
op_add_assign
l_int|100
suffix:semicolon
multiline_comment|/* by 1 takes too long to timeout from 0 */
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
op_logical_and
id|count
OG
l_int|0
)paren
suffix:semicolon
id|cc
op_assign
id|rpcc
c_func
(paren
)paren
op_minus
id|cc
suffix:semicolon
multiline_comment|/* Error: ECTCNEVERSET or ECPUTOOFAST.  */
r_if
c_cond
(paren
id|count
op_le
l_int|100
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Error: ECPUTOOSLOW.  */
r_if
c_cond
(paren
id|cc
op_le
id|CALIBRATE_TIME
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|cc
op_star
l_int|1000000UL
)paren
op_div
id|CALIBRATE_TIME
suffix:semicolon
)brace
multiline_comment|/* The Linux interpretation of the CMOS clock register contents:&n;   When the Update-In-Progress (UIP) flag goes from 1 to 0, the&n;   RTC registers show the second which has precisely just started.&n;   Let&squot;s hope other operating systems interpret the RTC the same way.  */
r_static
r_int
r_int
id|__init
DECL|function|rpcc_after_update_in_progress
id|rpcc_after_update_in_progress
c_func
(paren
r_void
)paren
(brace
r_do
(brace
)brace
r_while
c_loop
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
suffix:semicolon
r_do
(brace
)brace
r_while
c_loop
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
suffix:semicolon
r_return
id|rpcc
c_func
(paren
)paren
suffix:semicolon
)brace
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
comma
id|cc1
comma
id|cc2
comma
id|epoch
suffix:semicolon
r_int
r_int
id|cycle_freq
comma
id|one_percent
suffix:semicolon
r_int
id|diff
suffix:semicolon
multiline_comment|/* Calibrate CPU clock -- attempt #1.  */
r_if
c_cond
(paren
op_logical_neg
id|est_cycle_freq
)paren
id|est_cycle_freq
op_assign
id|validate_cc_value
c_func
(paren
id|calibrate_cc_with_pic
c_func
(paren
)paren
)paren
suffix:semicolon
id|cc1
op_assign
id|rpcc_after_update_in_progress
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Calibrate CPU clock -- attempt #2.  */
r_if
c_cond
(paren
op_logical_neg
id|est_cycle_freq
)paren
(brace
id|cc2
op_assign
id|rpcc_after_update_in_progress
c_func
(paren
)paren
suffix:semicolon
id|est_cycle_freq
op_assign
id|validate_cc_value
c_func
(paren
id|cc2
op_minus
id|cc1
)paren
suffix:semicolon
id|cc1
op_assign
id|cc2
suffix:semicolon
)brace
id|cycle_freq
op_assign
id|hwrpb-&gt;cycle_freq
suffix:semicolon
r_if
c_cond
(paren
id|est_cycle_freq
)paren
(brace
multiline_comment|/* If the given value is within 1% of what we calculated, &n;&t;&t;   accept it.  Otherwise, use what we found.  */
id|one_percent
op_assign
id|cycle_freq
op_div
l_int|100
suffix:semicolon
id|diff
op_assign
id|cycle_freq
op_minus
id|est_cycle_freq
suffix:semicolon
r_if
c_cond
(paren
id|diff
OL
l_int|0
)paren
id|diff
op_assign
op_minus
id|diff
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|diff
OG
id|one_percent
)paren
(brace
id|cycle_freq
op_assign
id|est_cycle_freq
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HWRPB cycle frequency bogus.  &quot;
l_string|&quot;Estimated %lu Hz&bslash;n&quot;
comma
id|cycle_freq
)paren
suffix:semicolon
)brace
r_else
(brace
id|est_cycle_freq
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|validate_cc_value
(paren
id|cycle_freq
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HWRPB cycle frequency bogus, &quot;
l_string|&quot;and unable to estimate a proper value!&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* From John Bowman &lt;bowman@math.ualberta.ca&gt;: allow the values&n;&t;   to settle, as the Update-In-Progress bit going low isn&squot;t good&n;&t;   enough on some hardware.  2ms is our guess; we haven&squot;t found &n;&t;   bogomips yet, but this is close on a 500Mhz box.  */
id|__delay
c_func
(paren
l_int|1000000
)paren
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
multiline_comment|/* PC-like is standard; used for year &lt; 20 || year &gt;= 70 */
id|epoch
op_assign
l_int|1900
suffix:semicolon
r_if
c_cond
(paren
id|year
OL
l_int|20
)paren
id|epoch
op_assign
l_int|2000
suffix:semicolon
r_else
r_if
c_cond
(paren
id|year
op_ge
l_int|20
op_logical_and
id|year
OL
l_int|48
)paren
multiline_comment|/* NT epoch */
id|epoch
op_assign
l_int|1980
suffix:semicolon
r_else
r_if
c_cond
(paren
id|year
op_ge
l_int|48
op_logical_and
id|year
OL
l_int|70
)paren
multiline_comment|/* Digital UNIX epoch */
id|epoch
op_assign
l_int|1952
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using epoch = %d&bslash;n&quot;
comma
id|epoch
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|year
op_add_assign
id|epoch
)paren
OL
l_int|1970
)paren
id|year
op_add_assign
l_int|100
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|HZ
OG
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
(brace
r_extern
r_void
id|__you_loose
(paren
r_void
)paren
suffix:semicolon
id|__you_loose
c_func
(paren
)paren
suffix:semicolon
)brace
id|state.last_time
op_assign
id|cc1
suffix:semicolon
id|state.scaled_ticks_per_cycle
op_assign
(paren
(paren
r_int
r_int
)paren
id|HZ
op_lshift
id|FIX_SHIFT
)paren
op_div
id|cycle_freq
suffix:semicolon
id|state.last_rtc_update
op_assign
l_int|0
suffix:semicolon
id|state.partial_tick
op_assign
l_int|0L
suffix:semicolon
multiline_comment|/* Startup the timer source. */
id|alpha_mv
dot
id|init_rtc
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Use the cycle counter to estimate an displacement from the last time&n; * tick.  Unfortunately the Alpha designers made only the low 32-bits of&n; * the cycle counter active, so we overflow on 8.2 seconds on a 500MHz&n; * part.  So we can&squot;t do the &quot;find absolute time in terms of cycles&quot; thing&n; * that the other ports do.&n; */
r_void
DECL|function|do_gettimeofday
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
id|sec
comma
id|usec
comma
id|lost
comma
id|seq
suffix:semicolon
r_int
r_int
id|delta_cycles
comma
id|delta_usec
comma
id|partial_tick
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
id|delta_cycles
op_assign
id|rpcc
c_func
(paren
)paren
op_minus
id|state.last_time
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_assign
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
suffix:semicolon
id|partial_tick
op_assign
id|state.partial_tick
suffix:semicolon
id|lost
op_assign
id|jiffies
op_minus
id|wall_jiffies
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
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Until and unless we figure out how to get cpu cycle counters&n;&t;   in sync and keep them there, we can&squot;t use the rpcc tricks.  */
id|delta_usec
op_assign
id|lost
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * usec = cycles * ticks_per_cycle * 2**48 * 1e6 / (2**48 * ticks)&n;&t; *&t;= cycles * (s_t_p_c) * 1e6 / (2**48 * ticks)&n;&t; *&t;= cycles * (s_t_p_c) * 15625 / (2**42 * ticks)&n;&t; *&n;&t; * which, given a 600MHz cycle and a 1024Hz tick, has a&n;&t; * dynamic range of about 1.7e17, which is less than the&n;&t; * 1.8e19 in an unsigned long, so we are safe from overflow.&n;&t; *&n;&t; * Round, but with .5 up always, since .5 to even is harder&n;&t; * with no clear gain.&n;&t; */
id|delta_usec
op_assign
(paren
id|delta_cycles
op_star
id|state.scaled_ticks_per_cycle
op_plus
id|partial_tick
op_plus
(paren
id|lost
op_lshift
id|FIX_SHIFT
)paren
)paren
op_star
l_int|15625
suffix:semicolon
id|delta_usec
op_assign
(paren
(paren
id|delta_usec
op_div
(paren
(paren
l_int|1UL
op_lshift
(paren
id|FIX_SHIFT
op_minus
l_int|6
op_minus
l_int|1
)paren
)paren
op_star
id|HZ
)paren
)paren
op_plus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
macro_line|#endif
id|usec
op_add_assign
id|delta_usec
suffix:semicolon
r_if
c_cond
(paren
id|usec
op_ge
l_int|1000000
)paren
(brace
id|sec
op_add_assign
l_int|1
suffix:semicolon
id|usec
op_sub_assign
l_int|1000000
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
r_void
DECL|function|do_settimeofday
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
id|delta_usec
suffix:semicolon
r_int
id|sec
comma
id|usec
suffix:semicolon
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* The offset that is added into time in do_gettimeofday above&n;&t;   must be subtracted out here to keep a coherent view of the&n;&t;   time.  Without this, a full-tick error is possible.  */
macro_line|#ifdef CONFIG_SMP
id|delta_usec
op_assign
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
macro_line|#else
id|delta_usec
op_assign
id|rpcc
c_func
(paren
)paren
op_minus
id|state.last_time
suffix:semicolon
id|delta_usec
op_assign
(paren
id|delta_usec
op_star
id|state.scaled_ticks_per_cycle
op_plus
id|state.partial_tick
op_plus
(paren
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_lshift
id|FIX_SHIFT
)paren
)paren
op_star
l_int|15625
suffix:semicolon
id|delta_usec
op_assign
(paren
(paren
id|delta_usec
op_div
(paren
(paren
l_int|1UL
op_lshift
(paren
id|FIX_SHIFT
op_minus
l_int|6
op_minus
l_int|1
)paren
)paren
op_star
id|HZ
)paren
)paren
op_plus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
macro_line|#endif
id|sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|usec
op_assign
id|tv-&gt;tv_usec
suffix:semicolon
id|usec
op_sub_assign
id|delta_usec
suffix:semicolon
r_if
c_cond
(paren
id|usec
OL
l_int|0
)paren
(brace
id|usec
op_add_assign
l_int|1000000
suffix:semicolon
id|sec
op_sub_assign
l_int|1
suffix:semicolon
)brace
id|xtime.tv_sec
op_assign
id|sec
suffix:semicolon
id|xtime.tv_nsec
op_assign
(paren
id|usec
op_div
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
)brace
multiline_comment|/*&n; * In order to set the CMOS clock precisely, set_rtc_mmss has to be&n; * called 500 ms after the second nowtime has started, because when&n; * nowtime is written into the registers of the CMOS clock, it will&n; * jump to the next second precisely 500 ms later. Check the Motorola&n; * MC146818A or Dallas DS12887 data sheet for details.&n; *&n; * BUG: This routine does not handle hour overflow properly; it just&n; *      sets the minutes. Usually you won&squot;t notice until after reboot!&n; */
r_extern
r_int
id|abs
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_int
DECL|function|set_rtc_mmss
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
multiline_comment|/* irq are locally disabled here */
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
multiline_comment|/* Tell the clock it&squot;s being set */
id|save_control
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
(paren
id|save_control
op_or
id|RTC_SET
)paren
comma
id|RTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* Stop and reset prescaler */
id|save_freq_select
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
(brace
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
)brace
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
eof
