multiline_comment|/*&n; *  linux/arch/arm/mach-clps711x/irq.c&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
DECL|function|mask_irq_int1
r_static
r_void
id|mask_irq_int1
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|intmr1
suffix:semicolon
id|intmr1
op_assign
id|clps_readl
c_func
(paren
id|INTMR1
)paren
suffix:semicolon
id|intmr1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|intmr1
comma
id|INTMR1
)paren
suffix:semicolon
)brace
DECL|function|mask_ack_irq_int1
r_static
r_void
id|mask_ack_irq_int1
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|intmr1
suffix:semicolon
id|intmr1
op_assign
id|clps_readl
c_func
(paren
id|INTMR1
)paren
suffix:semicolon
id|intmr1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|intmr1
comma
id|INTMR1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_CSINT
suffix:colon
id|clps_writel
c_func
(paren
l_int|0
comma
id|COEOI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_TC1OI
suffix:colon
id|clps_writel
c_func
(paren
l_int|0
comma
id|TC1EOI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_TC2OI
suffix:colon
id|clps_writel
c_func
(paren
l_int|0
comma
id|TC2EOI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_RTCMI
suffix:colon
id|clps_writel
c_func
(paren
l_int|0
comma
id|RTCEOI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_TINT
suffix:colon
id|clps_writel
c_func
(paren
l_int|0
comma
id|TEOI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_UMSINT
suffix:colon
id|clps_writel
c_func
(paren
l_int|0
comma
id|UMSEOI
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|unmask_irq_int1
r_static
r_void
id|unmask_irq_int1
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|intmr1
suffix:semicolon
id|intmr1
op_assign
id|clps_readl
c_func
(paren
id|INTMR1
)paren
suffix:semicolon
id|intmr1
op_or_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|clps_writel
c_func
(paren
id|intmr1
comma
id|INTMR1
)paren
suffix:semicolon
)brace
DECL|function|mask_irq_int2
r_static
r_void
id|mask_irq_int2
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|intmr2
suffix:semicolon
id|intmr2
op_assign
id|clps_readl
c_func
(paren
id|INTMR2
)paren
suffix:semicolon
id|intmr2
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|intmr2
comma
id|INTMR2
)paren
suffix:semicolon
)brace
DECL|function|mask_ack_irq_int2
r_static
r_void
id|mask_ack_irq_int2
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|intmr2
suffix:semicolon
id|intmr2
op_assign
id|clps_readl
c_func
(paren
id|INTMR2
)paren
suffix:semicolon
id|intmr2
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|intmr2
comma
id|INTMR2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_KBDINT
suffix:colon
id|clps_writel
c_func
(paren
l_int|0
comma
id|KBDEOI
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|unmask_irq_int2
r_static
r_void
id|unmask_irq_int2
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|intmr2
suffix:semicolon
id|intmr2
op_assign
id|clps_readl
c_func
(paren
id|INTMR2
)paren
suffix:semicolon
id|intmr2
op_or_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|intmr2
comma
id|INTMR2
)paren
suffix:semicolon
)brace
DECL|function|clps711x_init_irq
r_void
id|__init
id|clps711x_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|INT1_IRQS
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask_ack
op_assign
(paren
id|INT1_ACK_IRQS
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|mask_ack_irq_int1
suffix:colon
id|mask_irq_int1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask
op_assign
id|mask_irq_int1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|unmask
op_assign
id|unmask_irq_int1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|INT2_IRQS
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask_ack
op_assign
(paren
id|INT2_ACK_IRQS
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|mask_ack_irq_int2
suffix:colon
id|mask_irq_int2
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask
op_assign
id|mask_irq_int2
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|unmask
op_assign
id|unmask_irq_int2
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Disable interrupts&n;&t; */
id|clps_writel
c_func
(paren
l_int|0
comma
id|INTMR1
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|INTMR2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear down any pending interrupts&n;&t; */
id|clps_writel
c_func
(paren
l_int|0
comma
id|COEOI
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|TC1EOI
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|TC2EOI
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|RTCEOI
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|TEOI
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|UMSEOI
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|SYNCIO
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_int|0
comma
id|KBDEOI
)paren
suffix:semicolon
)brace
eof