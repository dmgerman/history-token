multiline_comment|/*&n; * linux/arch/arm/mach-xscale/irq.c&n; *&n; * Author:  Deepak Saxena&n; * Copyright:   (C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Based on IOP80310 code.  Currently there&squot;s nothing more than the&n; * 80200 on chip interrupts. That&squot;ll change once the hardware adds&n; * support for PCI though.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
DECL|function|xs80200_irq_mask
r_static
r_void
id|xs80200_irq_mask
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|INTCTL
suffix:semicolon
id|asm
(paren
l_string|&quot;mrc p13, 0, %0, c0, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|INTCTL
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_XS80200_BCU
suffix:colon
id|INTCTL
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_XS80200_PMU
suffix:colon
id|INTCTL
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_XS80200_EXTIRQ
suffix:colon
id|INTCTL
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_XS80200_EXTFIQ
suffix:colon
id|INTCTL
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|asm
(paren
l_string|&quot;mcr p13, 0, %0, c0, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|INTCTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|xs80200_irq_unmask
r_static
r_void
id|xs80200_irq_unmask
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|INTCTL
suffix:semicolon
id|asm
(paren
l_string|&quot;mrc p13, 0, %0, c0, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|INTCTL
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_XS80200_BCU
suffix:colon
id|INTCTL
op_or_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_XS80200_PMU
suffix:colon
id|INTCTL
op_or_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_XS80200_EXTIRQ
suffix:colon
id|INTCTL
op_or_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_XS80200_EXTFIQ
suffix:colon
id|INTCTL
op_or_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|asm
(paren
l_string|&quot;mcr p13, 0, %0, c0, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|INTCTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|adifcc_init_irq
r_void
id|__init
id|adifcc_init_irq
c_func
(paren
r_void
)paren
(brace
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
id|NR_XS80200_IRQS
suffix:semicolon
id|i
op_increment
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
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask_ack
op_assign
id|xs80200_irq_mask
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|mask
op_assign
id|xs80200_irq_mask
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|unmask
op_assign
id|xs80200_irq_unmask
suffix:semicolon
)brace
)brace
eof
