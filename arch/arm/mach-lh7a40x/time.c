multiline_comment|/* &n; *  arch/arm/mach-lh7a40x/time.c&n; *&n; *  Copyright (C) 2004 Logic Product Development&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &quot;common.h&quot;
macro_line|#if HZ &lt; 100
DECL|macro|TIMER_CONTROL
macro_line|# define TIMER_CONTROL&t;TIMER_CONTROL2
DECL|macro|TIMER_LOAD
macro_line|# define TIMER_LOAD&t;TIMER_LOAD2
DECL|macro|TIMER_CONSTANT
macro_line|# define TIMER_CONSTANT&t;(508469/HZ)
DECL|macro|TIMER_MODE
macro_line|# define TIMER_MODE&t;(TIMER_C_ENABLE | TIMER_C_PERIODIC | TIMER_C_508KHZ)
DECL|macro|TIMER_EOI
macro_line|# define TIMER_EOI&t;TIMER_EOI2
DECL|macro|TIMER_IRQ
macro_line|# define TIMER_IRQ&t;IRQ_T2UI
macro_line|#else
DECL|macro|TIMER_CONTROL
macro_line|# define TIMER_CONTROL&t;TIMER_CONTROL3
DECL|macro|TIMER_LOAD
macro_line|# define TIMER_LOAD&t;TIMER_LOAD3
DECL|macro|TIMER_CONSTANT
macro_line|# define TIMER_CONSTANT&t;(3686400/HZ)
DECL|macro|TIMER_MODE
macro_line|# define TIMER_MODE&t;(TIMER_C_ENABLE | TIMER_C_PERIODIC)
DECL|macro|TIMER_EOI
macro_line|# define TIMER_EOI&t;TIMER_EOI3
DECL|macro|TIMER_IRQ
macro_line|# define TIMER_IRQ&t;IRQ_T3UI
macro_line|#endif
r_static
id|irqreturn_t
DECL|function|lh7a40x_timer_interrupt
id|lh7a40x_timer_interrupt
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
id|TIMER_EOI
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
DECL|variable|lh7a40x_timer_irq
r_static
r_struct
id|irqaction
id|lh7a40x_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;LHA740x Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|lh7a40x_timer_interrupt
)brace
suffix:semicolon
DECL|function|lh7a40x_timer_init
r_static
r_void
id|__init
id|lh7a40x_timer_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Stop/disable all timers */
id|TIMER_CONTROL1
op_assign
l_int|0
suffix:semicolon
id|TIMER_CONTROL2
op_assign
l_int|0
suffix:semicolon
id|TIMER_CONTROL3
op_assign
l_int|0
suffix:semicolon
id|setup_irq
(paren
id|TIMER_IRQ
comma
op_amp
id|lh7a40x_timer_irq
)paren
suffix:semicolon
id|TIMER_LOAD
op_assign
id|TIMER_CONSTANT
suffix:semicolon
id|TIMER_CONTROL
op_assign
id|TIMER_MODE
suffix:semicolon
)brace
DECL|variable|lh7a40x_timer
r_struct
id|sys_timer
id|lh7a40x_timer
op_assign
(brace
dot
id|init
op_assign
op_amp
id|lh7a40x_timer_init
comma
)brace
suffix:semicolon
eof
