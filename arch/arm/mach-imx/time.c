multiline_comment|/*&n; *  linux/arch/arm/mach-imx/time.c&n; *&n; *  Copyright (C) 2000-2001 Deep Blue Solutions&n; *  Copyright (C) 2002 Shane Nay (shane@minirl.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
multiline_comment|/* Use timer 1 as system timer */
DECL|macro|TIMER_BASE
mdefine_line|#define TIMER_BASE IMX_TIM1_BASE
multiline_comment|/*&n; * Returns number of us since last clock interrupt.  Note that interrupts&n; * will have been disabled by do_gettimeoffset()&n; */
DECL|function|imx_gettimeoffset
r_static
r_int
r_int
id|imx_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ticks
suffix:semicolon
multiline_comment|/*&n;&t; * Get the current number of ticks.  Note that there is a race&n;&t; * condition between us reading the timer and checking for&n;&t; * an interrupt.  We get around this by ensuring that the&n;&t; * counter has not reloaded between our two reads.&n;&t; */
id|ticks
op_assign
id|IMX_TCN
c_func
(paren
id|TIMER_BASE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Interrupt pending?  If so, we&squot;ve reloaded once already.&n;&t; */
r_if
c_cond
(paren
id|IMX_TSTAT
c_func
(paren
id|TIMER_BASE
)paren
op_amp
id|TSTAT_COMP
)paren
id|ticks
op_add_assign
id|LATCH
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the ticks to usecs&n;&t; */
r_return
(paren
l_int|1000000
op_div
id|CLK32
)paren
op_star
id|ticks
suffix:semicolon
)brace
multiline_comment|/*&n; * IRQ handler for the timer&n; */
r_static
id|irqreturn_t
DECL|function|imx_timer_interrupt
id|imx_timer_interrupt
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
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* clear the interrupt */
r_if
c_cond
(paren
id|IMX_TSTAT
c_func
(paren
id|TIMER_BASE
)paren
)paren
id|IMX_TSTAT
c_func
(paren
id|TIMER_BASE
)paren
op_assign
l_int|0
suffix:semicolon
id|timer_tick
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
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|imx_timer_irq
r_static
r_struct
id|irqaction
id|imx_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i.MX Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|imx_timer_interrupt
)brace
suffix:semicolon
multiline_comment|/*&n; * Set up timer interrupt, and return the current time in seconds.&n; */
DECL|function|imx_timer_init
r_static
r_void
id|__init
id|imx_timer_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Initialise to a known state (all timers off, and timing reset)&n;&t; */
id|IMX_TCTL
c_func
(paren
id|TIMER_BASE
)paren
op_assign
l_int|0
suffix:semicolon
id|IMX_TPRER
c_func
(paren
id|TIMER_BASE
)paren
op_assign
l_int|0
suffix:semicolon
id|IMX_TCMP
c_func
(paren
id|TIMER_BASE
)paren
op_assign
id|LATCH
op_minus
l_int|1
suffix:semicolon
id|IMX_TCTL
c_func
(paren
id|TIMER_BASE
)paren
op_assign
id|TCTL_CLK_32
op_or
id|TCTL_IRQEN
op_or
id|TCTL_TEN
suffix:semicolon
multiline_comment|/*&n;&t; * Make irqs happen for the system timer&n;&t; */
id|setup_irq
c_func
(paren
id|TIM1_INT
comma
op_amp
id|imx_timer_irq
)paren
suffix:semicolon
)brace
DECL|variable|imx_timer
r_struct
id|sys_timer
id|imx_timer
op_assign
(brace
dot
id|init
op_assign
id|imx_timer_init
comma
dot
id|offset
op_assign
id|imx_gettimeoffset
comma
)brace
suffix:semicolon
eof
