multiline_comment|/*&n; * Copyright 2002 Momentum Computer&n; * Author: mdharm@momenco.com&n; * Copyright (C) 2004 Ralf Baechle &lt;ralf@linux-mips.org&gt;&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mv64340.h&gt;
DECL|variable|irq_base
r_static
r_int
r_int
id|irq_base
suffix:semicolon
DECL|function|ls1bit32
r_static
r_inline
r_int
id|ls1bit32
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|b
op_assign
l_int|31
comma
id|s
suffix:semicolon
id|s
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|x
op_lshift
l_int|16
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
id|x
op_lshift_assign
id|s
suffix:semicolon
id|s
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|x
op_lshift
l_int|8
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
id|x
op_lshift_assign
id|s
suffix:semicolon
id|s
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|x
op_lshift
l_int|4
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
id|x
op_lshift_assign
id|s
suffix:semicolon
id|s
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|x
op_lshift
l_int|2
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
id|x
op_lshift_assign
id|s
suffix:semicolon
id|s
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|x
op_lshift
l_int|1
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/* mask off an interrupt -- 1 is enable, 0 is disable */
DECL|function|mask_mv64340_irq
r_static
r_inline
r_void
id|mask_mv64340_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_uint32
id|value
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
(paren
id|irq_base
op_plus
l_int|32
)paren
)paren
(brace
id|value
op_assign
id|MV_READ
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_LOW
)paren
suffix:semicolon
id|value
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|irq_base
)paren
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_LOW
comma
id|value
)paren
suffix:semicolon
)brace
r_else
(brace
id|value
op_assign
id|MV_READ
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_HIGH
)paren
suffix:semicolon
id|value
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|irq_base
op_minus
l_int|32
)paren
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_HIGH
comma
id|value
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* unmask an interrupt -- 1 is enable, 0 is disable */
DECL|function|unmask_mv64340_irq
r_static
r_inline
r_void
id|unmask_mv64340_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_uint32
id|value
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
(paren
id|irq_base
op_plus
l_int|32
)paren
)paren
(brace
id|value
op_assign
id|MV_READ
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_LOW
)paren
suffix:semicolon
id|value
op_or_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|irq_base
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_LOW
comma
id|value
)paren
suffix:semicolon
)brace
r_else
(brace
id|value
op_assign
id|MV_READ
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_HIGH
)paren
suffix:semicolon
id|value
op_or_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|irq_base
op_minus
l_int|32
)paren
suffix:semicolon
id|MV_WRITE
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_HIGH
comma
id|value
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Enables the IRQ on Marvell Chip&n; */
DECL|function|enable_mv64340_irq
r_static
r_void
id|enable_mv64340_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|unmask_mv64340_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the IRQ on Marvell Chip&n; */
DECL|function|startup_mv64340_irq
r_static
r_int
r_int
id|startup_mv64340_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|unmask_mv64340_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Disables the IRQ on Marvell Chip&n; */
DECL|function|disable_mv64340_irq
r_static
r_void
id|disable_mv64340_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|mask_mv64340_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Masks and ACKs an IRQ&n; */
DECL|function|mask_and_ack_mv64340_irq
r_static
r_void
id|mask_and_ack_mv64340_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|mask_mv64340_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * End IRQ processing&n; */
DECL|function|end_mv64340_irq
r_static
r_void
id|end_mv64340_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|unmask_mv64340_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Interrupt handler for interrupts coming from the Marvell chip.&n; * It could be built in ethernet ports etc...&n; */
DECL|function|ll_mv64340_irq
r_void
id|ll_mv64340_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|irq_src_low
comma
id|irq_src_high
suffix:semicolon
r_int
r_int
id|irq_mask_low
comma
id|irq_mask_high
suffix:semicolon
multiline_comment|/* read the interrupt status registers */
id|irq_mask_low
op_assign
id|MV_READ
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_LOW
)paren
suffix:semicolon
id|irq_mask_high
op_assign
id|MV_READ
c_func
(paren
id|MV64340_INTERRUPT0_MASK_0_HIGH
)paren
suffix:semicolon
id|irq_src_low
op_assign
id|MV_READ
c_func
(paren
id|MV64340_MAIN_INTERRUPT_CAUSE_LOW
)paren
suffix:semicolon
id|irq_src_high
op_assign
id|MV_READ
c_func
(paren
id|MV64340_MAIN_INTERRUPT_CAUSE_HIGH
)paren
suffix:semicolon
multiline_comment|/* mask for just the interrupts we want */
id|irq_src_low
op_and_assign
id|irq_mask_low
suffix:semicolon
id|irq_src_high
op_and_assign
id|irq_mask_high
suffix:semicolon
r_if
c_cond
(paren
id|irq_src_low
)paren
id|do_IRQ
c_func
(paren
id|ls1bit32
c_func
(paren
id|irq_src_low
)paren
op_plus
id|irq_base
comma
id|regs
)paren
suffix:semicolon
r_else
id|do_IRQ
c_func
(paren
id|ls1bit32
c_func
(paren
id|irq_src_high
)paren
op_plus
id|irq_base
op_plus
l_int|32
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|macro|shutdown_mv64340_irq
mdefine_line|#define shutdown_mv64340_irq&t;disable_mv64340_irq
DECL|variable|mv64340_irq_type
r_struct
id|hw_interrupt_type
id|mv64340_irq_type
op_assign
(brace
l_string|&quot;MV-64340&quot;
comma
id|startup_mv64340_irq
comma
id|shutdown_mv64340_irq
comma
id|enable_mv64340_irq
comma
id|disable_mv64340_irq
comma
id|mask_and_ack_mv64340_irq
comma
id|end_mv64340_irq
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|mv64340_irq_init
r_void
id|__init
id|mv64340_irq_init
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Reset irq handlers pointers to NULL */
r_for
c_loop
(paren
id|i
op_assign
id|base
suffix:semicolon
id|i
OL
id|base
op_plus
l_int|64
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
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|2
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|mv64340_irq_type
suffix:semicolon
)brace
id|irq_base
op_assign
id|base
suffix:semicolon
)brace
eof
