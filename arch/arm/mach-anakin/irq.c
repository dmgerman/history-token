multiline_comment|/*&n; *  linux/arch/arm/mach-anakin/irq.c&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   10-Apr-2001 TTC&t;Created&n; */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
r_extern
r_int
r_int
id|anakin_irq_mask
comma
id|anakin_active_irqs
suffix:semicolon
r_extern
r_void
id|do_IRQ
c_func
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
DECL|function|anakin_mask_irq
id|anakin_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|anakin_irq_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|anakin_unmask_irq
id|anakin_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|anakin_irq_mask
op_or_assign
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a faked interrupt to deal with parallel interrupt requests&n; * on the Anakin.  Make sure that its interrupt number is not in any&n; * way conflicting with the hardware interrupt numbers!  Check&n; * IRQ_ANAKIN in linux/include/asm-arm/arch-anakin/irqs.h.&n; */
r_static
r_void
DECL|function|anakin_interrupt
id|anakin_interrupt
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
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
id|irq
op_increment
)paren
r_if
c_cond
(paren
id|anakin_active_irqs
op_amp
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|variable|anakin_irq
r_static
r_struct
id|irqaction
id|anakin_irq
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Anakin IRQ&quot;
comma
id|handler
suffix:colon
id|anakin_interrupt
comma
id|flags
suffix:colon
id|SA_INTERRUPT
)brace
suffix:semicolon
r_void
id|__init
DECL|function|irq_init_irq
id|irq_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_UART0
suffix:colon
r_case
id|IRQ_UART1
suffix:colon
r_case
id|IRQ_UART2
suffix:colon
r_case
id|IRQ_TICK
suffix:colon
r_case
id|IRQ_CODEC
suffix:colon
r_case
id|IRQ_UART4
suffix:colon
r_case
id|IRQ_TOUCHSCREEN
suffix:colon
r_case
id|IRQ_UART3
suffix:colon
r_case
id|IRQ_FIFO
suffix:colon
r_case
id|IRQ_CAN
suffix:colon
r_case
id|IRQ_COMPACTFLASH
suffix:colon
r_case
id|IRQ_BOSH
suffix:colon
r_case
id|IRQ_ANAKIN
suffix:colon
id|irq_desc
(braket
id|irq
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|mask_ack
op_assign
id|anakin_mask_irq
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|mask
op_assign
id|anakin_mask_irq
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|unmask
op_assign
id|anakin_unmask_irq
suffix:semicolon
)brace
)brace
id|setup_arm_irq
c_func
(paren
id|IRQ_ANAKIN
comma
op_amp
id|anakin_irq
)paren
suffix:semicolon
)brace
eof
