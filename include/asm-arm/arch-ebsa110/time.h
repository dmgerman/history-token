multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/time.h&n; *&n; *  Copyright (C) 1996,1997,1998 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * No real time clock on the evalulation board!&n; *&n; * Changelog:&n; *  10-Oct-1996&t;RMK&t;Created&n; *  04-Dec-1997&t;RMK&t;Updated for new arch/arm/kernel/time.c&n; *  07-Aug-1998&t;RMK&t;Updated for arch/arm/kernel/leds.c&n; *  28-Dec-1998&t;APH&t;Made leds code optional&n; */
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_int
r_int
(paren
op_star
id|gettimeoffset
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PIT_CTRL
mdefine_line|#define PIT_CTRL&t;&t;(PIT_BASE + 0x0d)
DECL|macro|PIT_T2
mdefine_line|#define PIT_T2&t;&t;&t;(PIT_BASE + 0x09)
DECL|macro|PIT_T1
mdefine_line|#define PIT_T1&t;&t;&t;(PIT_BASE + 0x05)
DECL|macro|PIT_T0
mdefine_line|#define PIT_T0&t;&t;&t;(PIT_BASE + 0x01)
multiline_comment|/*&n; * This is the rate at which your MCLK signal toggles (in Hz)&n; * This was measured on a 10 digit frequency counter sampling&n; * over 1 second.&n; */
DECL|macro|MCLK
mdefine_line|#define MCLK&t;47894000
multiline_comment|/*&n; * This is the rate at which the PIT timers get clocked&n; */
DECL|macro|CLKBY7
mdefine_line|#define CLKBY7&t;(MCLK / 7)
multiline_comment|/*&n; * This is the counter value.  We tick at 200Hz on this platform.&n; */
DECL|macro|COUNT
mdefine_line|#define COUNT&t;((CLKBY7 + (HZ / 2)) / HZ)
multiline_comment|/*&n; * Get the time offset from the system PIT.  Note that if we have missed an&n; * interrupt, then the PIT counter will roll over (ie, be negative).&n; * This actually works out to be convenient.&n; */
DECL|function|ebsa110_gettimeoffset
r_static
r_int
r_int
id|ebsa110_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
comma
id|count
suffix:semicolon
id|__raw_writeb
c_func
(paren
l_int|0x40
comma
id|PIT_CTRL
)paren
suffix:semicolon
id|count
op_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
suffix:semicolon
id|count
op_or_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/*&n;&t; * If count &gt; COUNT, make the number negative.&n;&t; */
r_if
c_cond
(paren
id|count
OG
id|COUNT
)paren
id|count
op_or_assign
l_int|0xffff0000
suffix:semicolon
id|offset
op_assign
id|COUNT
suffix:semicolon
id|offset
op_sub_assign
id|count
suffix:semicolon
multiline_comment|/*&n;&t; * `offset&squot; is in units of timer counts.  Convert&n;&t; * offset to units of microseconds.&n;&t; */
id|offset
op_assign
id|offset
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
op_div
id|COUNT
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|timer_interrupt
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
id|u32
id|count
suffix:semicolon
multiline_comment|/* latch and read timer 1 */
id|__raw_writeb
c_func
(paren
l_int|0x40
comma
id|PIT_CTRL
)paren
suffix:semicolon
id|count
op_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
suffix:semicolon
id|count
op_or_assign
id|__raw_readb
c_func
(paren
id|PIT_T1
)paren
op_lshift
l_int|8
suffix:semicolon
id|count
op_add_assign
id|COUNT
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|PIT_T1
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|PIT_T1
)paren
suffix:semicolon
id|do_leds
c_func
(paren
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up timer interrupt.&n; */
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Timer 1, mode 2, LSB/MSB&n;&t; */
id|__raw_writeb
c_func
(paren
l_int|0x70
comma
id|PIT_CTRL
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|COUNT
op_amp
l_int|0xff
comma
id|PIT_T1
)paren
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|COUNT
op_rshift
l_int|8
comma
id|PIT_T1
)paren
suffix:semicolon
id|gettimeoffset
op_assign
id|ebsa110_gettimeoffset
suffix:semicolon
id|timer_irq.handler
op_assign
id|timer_interrupt
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_EBSA110_TIMER0
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
)brace
eof
