multiline_comment|/***************************************************************************/
multiline_comment|/*&n; *&t;pit.c -- Motorola ColdFire PIT timer. Currently this type of&n; *&t;         hardware timer only exists in the Motorola ColdFire&n; *&t;&t; 5282 CPU.&n; *&n; *&t;Copyright (C) 1999-2003, Greg Ungerer (gerg@snapgear.com)&n; *&t;Copyright (C) 2001-2003, SnapGear Inc. (www.snapgear.com)&n; *&n; */
multiline_comment|/***************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#include &lt;asm/mcfpit.h&gt;
macro_line|#include &lt;asm/mcfsim.h&gt;
multiline_comment|/***************************************************************************/
DECL|function|coldfire_pit_tick
r_void
id|coldfire_pit_tick
c_func
(paren
r_void
)paren
(brace
r_volatile
r_struct
id|mcfpit
op_star
id|tp
suffix:semicolon
multiline_comment|/* Reset the ColdFire timer */
id|tp
op_assign
(paren
r_volatile
r_struct
id|mcfpit
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFPIT_BASE1
)paren
suffix:semicolon
id|tp-&gt;pcsr
op_or_assign
id|MCFPIT_PCSR_PIF
suffix:semicolon
)brace
multiline_comment|/***************************************************************************/
DECL|function|coldfire_pit_init
r_void
id|coldfire_pit_init
c_func
(paren
id|irqreturn_t
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
r_volatile
r_int
r_char
op_star
id|icrp
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|imrp
suffix:semicolon
r_volatile
r_struct
id|mcfpit
op_star
id|tp
suffix:semicolon
id|request_irq
c_func
(paren
l_int|64
op_plus
l_int|55
comma
id|handler
comma
id|SA_INTERRUPT
comma
l_string|&quot;ColdFire Timer&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|icrp
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFICM_INTC0
op_plus
id|MCFINTC_ICR0
op_plus
id|MCFINT_PIT1
)paren
suffix:semicolon
op_star
id|icrp
op_assign
l_int|0x2b
suffix:semicolon
multiline_comment|/* PIT1 with level 5, priority 3 */
id|imrp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFICM_INTC0
op_plus
id|MCFINTC_IMRH
)paren
suffix:semicolon
op_star
id|imrp
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|55
op_minus
l_int|32
)paren
)paren
suffix:semicolon
multiline_comment|/* Set up PIT timer 1 as poll clock */
id|tp
op_assign
(paren
r_volatile
r_struct
id|mcfpit
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFPIT_BASE1
)paren
suffix:semicolon
id|tp-&gt;pcsr
op_assign
id|MCFPIT_PCSR_DISABLE
suffix:semicolon
id|tp-&gt;pmr
op_assign
(paren
(paren
id|MCF_CLK
op_div
l_int|2
)paren
op_div
l_int|64
)paren
op_div
id|HZ
suffix:semicolon
id|tp-&gt;pcsr
op_assign
id|MCFPIT_PCSR_EN
op_or
id|MCFPIT_PCSR_PIE
op_or
id|MCFPIT_PCSR_OVW
op_or
id|MCFPIT_PCSR_RLD
op_or
id|MCFPIT_PCSR_CLK64
suffix:semicolon
)brace
multiline_comment|/***************************************************************************/
DECL|function|coldfire_pit_offset
r_int
r_int
id|coldfire_pit_offset
c_func
(paren
r_void
)paren
(brace
r_volatile
r_struct
id|mcfpit
op_star
id|tp
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|ipr
suffix:semicolon
r_int
r_int
id|pmr
comma
id|pcntr
comma
id|offset
suffix:semicolon
id|tp
op_assign
(paren
r_volatile
r_struct
id|mcfpit
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFPIT_BASE1
)paren
suffix:semicolon
id|ipr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFICM_INTC0
op_plus
id|MCFINTC_IPRH
)paren
suffix:semicolon
id|pmr
op_assign
id|tp-&gt;pmr
suffix:semicolon
id|pcntr
op_assign
id|tp-&gt;pcntr
suffix:semicolon
multiline_comment|/*&n;&t; * If we are still in the first half of the upcount and a&n;&t; * timer interupt is pending, then add on a ticks worth of time.&n;&t; */
id|offset
op_assign
(paren
(paren
id|pcntr
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
)paren
op_div
id|pmr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|offset
OL
(paren
l_int|1000000
op_div
id|HZ
op_div
l_int|2
)paren
)paren
op_logical_and
(paren
op_star
id|ipr
op_amp
(paren
l_int|1
op_lshift
(paren
l_int|55
op_minus
l_int|32
)paren
)paren
)paren
)paren
id|offset
op_add_assign
l_int|1000000
op_div
id|HZ
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
multiline_comment|/***************************************************************************/
eof
