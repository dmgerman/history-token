multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/time-iq80310.c&n; *&n; * Timer functions for IQ80310 onboard timer&n; *&n; * Author:  Nicolas Pitre&n; * Copyright:   (C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
DECL|function|iq80310_write_timer
r_static
r_void
id|iq80310_write_timer
(paren
id|u_long
id|val
)paren
(brace
r_volatile
id|u_char
op_star
id|la0
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_LA0
suffix:semicolon
r_volatile
id|u_char
op_star
id|la1
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_LA1
suffix:semicolon
r_volatile
id|u_char
op_star
id|la2
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_LA2
suffix:semicolon
op_star
id|la0
op_assign
id|val
suffix:semicolon
op_star
id|la1
op_assign
id|val
op_rshift
l_int|8
suffix:semicolon
op_star
id|la2
op_assign
(paren
id|val
op_rshift
l_int|16
)paren
op_amp
l_int|0x3f
suffix:semicolon
)brace
DECL|function|iq80310_read_timer
r_static
id|u_long
id|iq80310_read_timer
(paren
r_void
)paren
(brace
r_volatile
id|u_char
op_star
id|la0
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_LA0
suffix:semicolon
r_volatile
id|u_char
op_star
id|la1
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_LA1
suffix:semicolon
r_volatile
id|u_char
op_star
id|la2
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_LA2
suffix:semicolon
r_volatile
id|u_char
op_star
id|la3
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_LA3
suffix:semicolon
id|u_long
id|b0
comma
id|b1
comma
id|b2
comma
id|b3
comma
id|val
suffix:semicolon
id|b0
op_assign
op_star
id|la0
suffix:semicolon
id|b1
op_assign
op_star
id|la1
suffix:semicolon
id|b2
op_assign
op_star
id|la2
suffix:semicolon
id|b3
op_assign
op_star
id|la3
suffix:semicolon
id|b0
op_assign
(paren
(paren
(paren
id|b0
op_amp
l_int|0x40
)paren
op_rshift
l_int|1
)paren
op_or
(paren
id|b0
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|b1
op_assign
(paren
(paren
(paren
id|b1
op_amp
l_int|0x40
)paren
op_rshift
l_int|1
)paren
op_or
(paren
id|b1
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|b2
op_assign
(paren
(paren
(paren
id|b2
op_amp
l_int|0x40
)paren
op_rshift
l_int|1
)paren
op_or
(paren
id|b2
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|b3
op_assign
(paren
id|b3
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|val
op_assign
(paren
(paren
id|b0
op_lshift
l_int|0
)paren
op_or
(paren
id|b1
op_lshift
l_int|6
)paren
op_or
(paren
id|b2
op_lshift
l_int|12
)paren
op_or
(paren
id|b3
op_lshift
l_int|18
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * IRQs are disabled before entering here from do_gettimeofday().&n; * Note that the counter may wrap.  When it does, &squot;elapsed&squot; will&n; * be small, but we will have a pending interrupt.&n; */
DECL|function|iq80310_gettimeoffset
r_static
r_int
r_int
id|iq80310_gettimeoffset
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
r_int
r_int
id|stat1
comma
id|stat2
suffix:semicolon
id|stat1
op_assign
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|IQ80310_INT_STAT
suffix:semicolon
id|elapsed
op_assign
id|iq80310_read_timer
c_func
(paren
)paren
suffix:semicolon
id|stat2
op_assign
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|IQ80310_INT_STAT
suffix:semicolon
multiline_comment|/*&n;&t; * If an interrupt was pending before we read the timer,&n;&t; * we&squot;ve already wrapped.  Factor this into the time.&n;&t; * If an interrupt was pending after we read the timer,&n;&t; * it may have wrapped between checking the interrupt&n;&t; * status and reading the timer.  Re-read the timer to&n;&t; * be sure its value is after the wrap.&n;&t; */
r_if
c_cond
(paren
id|stat1
op_amp
l_int|1
)paren
id|elapsed
op_add_assign
id|LATCH
suffix:semicolon
r_else
r_if
c_cond
(paren
id|stat2
op_amp
l_int|1
)paren
id|elapsed
op_assign
id|LATCH
op_plus
id|iq80310_read_timer
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
DECL|function|iq80310_timer_interrupt
id|iq80310_timer_interrupt
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
r_volatile
id|u_char
op_star
id|timer_en
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_EN
suffix:semicolon
multiline_comment|/* clear timer interrupt */
op_star
id|timer_en
op_and_assign
op_complement
l_int|2
suffix:semicolon
op_star
id|timer_en
op_or_assign
l_int|2
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
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
DECL|variable|timer_irq
r_static
r_struct
id|irqaction
id|timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;timer&quot;
comma
dot
id|handler
op_assign
id|iq80310_timer_interrupt
comma
)brace
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
r_volatile
id|u_char
op_star
id|timer_en
op_assign
(paren
r_volatile
id|u_char
op_star
)paren
id|IQ80310_TIMER_EN
suffix:semicolon
id|gettimeoffset
op_assign
id|iq80310_gettimeoffset
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_IQ80310_TIMER
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
op_star
id|timer_en
op_assign
l_int|0
suffix:semicolon
id|iq80310_write_timer
c_func
(paren
id|LATCH
)paren
suffix:semicolon
op_star
id|timer_en
op_or_assign
l_int|2
suffix:semicolon
op_star
id|timer_en
op_or_assign
l_int|1
suffix:semicolon
)brace
eof
