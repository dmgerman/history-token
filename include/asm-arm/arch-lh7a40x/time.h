multiline_comment|/* include/asm-arm/arch-lh7a40x/time.h&n; *&n; *  Copyright (C) 2004 Logic Product Development&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#if HZ &lt; 100
DECL|macro|TIMER_CONTROL
macro_line|# define TIMER_CONTROL&t;TIMER_CONTROL1
DECL|macro|TIMER_LOAD
macro_line|# define TIMER_LOAD&t;TIMER_LOAD1
DECL|macro|TIMER_CONSTANT
macro_line|# define TIMER_CONSTANT&t;(508469/HZ)
DECL|macro|TIMER_MODE
macro_line|# define TIMER_MODE&t;(TIMER_C_ENABLE | TIMER_C_PERIODIC | TIMER_C_508KHZ)
DECL|macro|TIMER_EOI
macro_line|# define TIMER_EOI&t;TIMER_EOI1
DECL|macro|TIMER_IRQ
macro_line|# define TIMER_IRQ&t;IRQ_T1UI
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
id|TIMER_EOI
op_assign
l_int|0
suffix:semicolon
id|do_profile
(paren
id|regs
)paren
suffix:semicolon
id|do_leds
c_func
(paren
)paren
suffix:semicolon
id|do_set_rtc
c_func
(paren
)paren
suffix:semicolon
id|do_timer
(paren
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
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
id|timer_irq.handler
op_assign
id|lh7a40x_timer_interrupt
suffix:semicolon
id|timer_irq.flags
op_or_assign
id|SA_INTERRUPT
suffix:semicolon
id|setup_irq
(paren
id|TIMER_IRQ
comma
op_amp
id|timer_irq
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
eof
