multiline_comment|/*&n; * arch/arm/mach-pxa/time.c&n; *&n; * Author:&t;Nicolas Pitre&n; * Created:&t;Jun 15, 2001&n; * Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
DECL|function|pxa_get_rtc_time
r_static
r_inline
r_int
r_int
id|pxa_get_rtc_time
c_func
(paren
r_void
)paren
(brace
r_return
id|RCNR
suffix:semicolon
)brace
DECL|function|pxa_set_rtc
r_static
r_int
id|pxa_set_rtc
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|current_time
op_assign
id|xtime.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|RTSR
op_amp
id|RTSR_ALE
)paren
(brace
multiline_comment|/* make sure not to forward the clock over an alarm */
r_int
r_int
id|alarm
op_assign
id|RTAR
suffix:semicolon
r_if
c_cond
(paren
id|current_time
op_ge
id|alarm
op_logical_and
id|alarm
op_ge
id|RCNR
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|RCNR
op_assign
id|current_time
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* IRQs are disabled before entering here from do_gettimeofday() */
DECL|function|pxa_gettimeoffset
r_static
r_int
r_int
id|pxa_gettimeoffset
(paren
r_void
)paren
(brace
r_int
id|ticks_to_match
comma
id|elapsed
comma
id|usec
suffix:semicolon
multiline_comment|/* Get ticks before next timer match */
id|ticks_to_match
op_assign
id|OSMR0
op_minus
id|OSCR
suffix:semicolon
multiline_comment|/* We need elapsed ticks since last match */
id|elapsed
op_assign
id|LATCH
op_minus
id|ticks_to_match
suffix:semicolon
multiline_comment|/* don&squot;t get fooled by the workaround in pxa_timer_interrupt() */
r_if
c_cond
(paren
id|elapsed
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Now convert them to usec */
id|usec
op_assign
(paren
r_int
r_int
)paren
(paren
id|elapsed
op_star
(paren
id|tick_nsec
op_div
l_int|1000
)paren
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|usec
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|pxa_timer_interrupt
id|pxa_timer_interrupt
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
id|next_match
suffix:semicolon
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* Loop until we get ahead of the free running timer.&n;&t; * This ensures an exact clock tick count and time accuracy.&n;&t; * IRQs are disabled inside the loop to ensure coherence between&n;&t; * lost_ticks (updated in do_timer()) and the match reg value, so we&n;&t; * can use do_gettimeofday() from interrupt handlers.&n;&t; *&n;&t; * HACK ALERT: it seems that the PXA timer regs aren&squot;t updated right&n;&t; * away in all cases when a write occurs.  We therefore compare with&n;&t; * 8 instead of 0 in the while() condition below to avoid missing a&n;&t; * match if OSCR has already reached the next OSMR value.&n;&t; * Experience has shown that up to 6 ticks are needed to work around&n;&t; * this problem, but let&squot;s use 8 to be conservative.  Note that this&n;&t; * affect things only when the timer IRQ has been delayed by nearly&n;&t; * exactly one tick period which should be a pretty rare event.&n;&t; */
r_do
(brace
id|timer_tick
c_func
(paren
id|regs
)paren
suffix:semicolon
id|OSSR
op_assign
id|OSSR_M0
suffix:semicolon
multiline_comment|/* Clear match on timer 0 */
id|next_match
op_assign
(paren
id|OSMR0
op_add_assign
id|LATCH
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
(paren
id|next_match
op_minus
id|OSCR
)paren
op_le
l_int|8
)paren
(brace
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
DECL|variable|pxa_timer_irq
r_static
r_struct
id|irqaction
id|pxa_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PXA Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|pxa_timer_interrupt
)brace
suffix:semicolon
DECL|function|pxa_timer_init
r_static
r_void
id|__init
id|pxa_timer_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|timespec
id|tv
suffix:semicolon
id|set_rtc
op_assign
id|pxa_set_rtc
suffix:semicolon
id|tv.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|tv.tv_sec
op_assign
id|pxa_get_rtc_time
c_func
(paren
)paren
suffix:semicolon
id|do_settimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|OSMR0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set initial match at 0 */
id|OSSR
op_assign
l_int|0xf
suffix:semicolon
multiline_comment|/* clear status on all timers */
id|setup_irq
c_func
(paren
id|IRQ_OST0
comma
op_amp
id|pxa_timer_irq
)paren
suffix:semicolon
id|OIER
op_or_assign
id|OIER_E0
suffix:semicolon
multiline_comment|/* enable match on timer 0 to cause interrupts */
id|OSCR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* initialize free-running timer, force first match */
)brace
macro_line|#ifdef CONFIG_PM
DECL|variable|osmr
DECL|variable|oier
r_static
r_int
r_int
id|osmr
(braket
l_int|4
)braket
comma
id|oier
suffix:semicolon
DECL|function|pxa_timer_suspend
r_static
r_void
id|pxa_timer_suspend
c_func
(paren
r_void
)paren
(brace
id|osmr
(braket
l_int|0
)braket
op_assign
id|OSMR0
suffix:semicolon
id|osmr
(braket
l_int|1
)braket
op_assign
id|OSMR1
suffix:semicolon
id|osmr
(braket
l_int|2
)braket
op_assign
id|OSMR2
suffix:semicolon
id|osmr
(braket
l_int|3
)braket
op_assign
id|OSMR3
suffix:semicolon
id|oier
op_assign
id|OIER
suffix:semicolon
)brace
DECL|function|pxa_timer_resume
r_static
r_void
id|pxa_timer_resume
c_func
(paren
r_void
)paren
(brace
id|OSMR0
op_assign
id|osmr
(braket
l_int|0
)braket
suffix:semicolon
id|OSMR1
op_assign
id|osmr
(braket
l_int|1
)braket
suffix:semicolon
id|OSMR2
op_assign
id|osmr
(braket
l_int|2
)braket
suffix:semicolon
id|OSMR3
op_assign
id|osmr
(braket
l_int|3
)braket
suffix:semicolon
id|OIER
op_assign
id|oier
suffix:semicolon
multiline_comment|/*&n;&t; * OSMR0 is the system timer: make sure OSCR is sufficiently behind&n;&t; */
id|OSCR
op_assign
id|OSMR0
op_minus
id|LATCH
suffix:semicolon
)brace
macro_line|#else
DECL|macro|pxa_timer_suspend
mdefine_line|#define pxa_timer_suspend NULL
DECL|macro|pxa_timer_resume
mdefine_line|#define pxa_timer_resume NULL
macro_line|#endif
DECL|variable|pxa_timer
r_struct
id|sys_timer
id|pxa_timer
op_assign
(brace
dot
id|init
op_assign
id|pxa_timer_init
comma
dot
id|suspend
op_assign
id|pxa_timer_suspend
comma
dot
id|resume
op_assign
id|pxa_timer_resume
comma
dot
id|offset
op_assign
id|pxa_gettimeoffset
comma
)brace
suffix:semicolon
eof
