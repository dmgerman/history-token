multiline_comment|/*&n; * arch/arm/mach-iop3xx/iop331-time.c&n; *&n; * Timer code for IOP331 based systems&n; *&n; * Author: Dave Jiang &lt;dave.jiang@intel.com&gt;&n; *&n; * Copyright 2003 Intel Corp.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
DECL|function|get_elapsed
r_static
r_inline
r_int
r_int
id|get_elapsed
c_func
(paren
r_void
)paren
(brace
r_return
id|LATCH
op_minus
op_star
id|IOP331_TU_TCR0
suffix:semicolon
)brace
DECL|function|iop331_gettimeoffset
r_static
r_int
r_int
id|iop331_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|elapsed
comma
id|usec
suffix:semicolon
id|u32
id|tisr1
comma
id|tisr2
suffix:semicolon
multiline_comment|/*&n;&t; * If an interrupt was pending before we read the timer,&n;&t; * we&squot;ve already wrapped.  Factor this into the time.&n;&t; * If an interrupt was pending after we read the timer,&n;&t; * it may have wrapped between checking the interrupt&n;&t; * status and reading the timer.  Re-read the timer to&n;&t; * be sure its value is after the wrap.&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;mrc p6, 0, %0, c6, c1, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tisr1
)paren
)paren
suffix:semicolon
id|elapsed
op_assign
id|get_elapsed
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mrc p6, 0, %0, c6, c1, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tisr2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tisr1
op_amp
l_int|1
)paren
(brace
id|elapsed
op_add_assign
id|LATCH
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tisr2
op_amp
l_int|1
)paren
id|elapsed
op_assign
id|LATCH
op_plus
id|get_elapsed
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now convert them to usec.&n;&t; */
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
DECL|function|iop331_timer_interrupt
id|iop331_timer_interrupt
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
id|u32
id|tisr
suffix:semicolon
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mrc p6, 0, %0, c6, c1, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tisr
)paren
)paren
suffix:semicolon
id|tisr
op_or_assign
l_int|1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mcr p6, 0, %0, c6, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|tisr
)paren
)paren
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
DECL|variable|iop331_timer_irq
r_static
r_struct
id|irqaction
id|iop331_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IOP331 Timer Tick&quot;
comma
dot
id|handler
op_assign
id|iop331_timer_interrupt
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
)brace
suffix:semicolon
DECL|function|iop331_timer_init
r_static
r_void
id|__init
id|iop331_timer_init
c_func
(paren
r_void
)paren
(brace
id|u32
id|timer_ctl
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_IOP331_TIMER0
comma
op_amp
id|iop331_timer_irq
)paren
suffix:semicolon
id|timer_ctl
op_assign
id|IOP331_TMR_EN
op_or
id|IOP331_TMR_PRIVILEGED
op_or
id|IOP331_TMR_RELOAD
op_or
id|IOP331_TMR_RATIO_1_1
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mcr p6, 0, %0, c4, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|LATCH
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mcr p6, 0, %0, c0, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|timer_ctl
)paren
)paren
suffix:semicolon
)brace
DECL|variable|iop331_timer
r_struct
id|sys_timer
id|iop331_timer
op_assign
(brace
dot
id|init
op_assign
id|iop331_timer_init
comma
dot
id|offset
op_assign
id|iop331_gettimeoffset
comma
)brace
suffix:semicolon
eof
