multiline_comment|/* arch/arm/mach-lh7a40x/irq-lpd7a40x.c&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *  Copyright (C) 2004 Logic Product Development&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
DECL|function|lh7a40x_ack_cpld_irq
r_static
r_void
id|lh7a40x_ack_cpld_irq
(paren
id|u32
id|irq
)paren
(brace
multiline_comment|/* CPLD doesn&squot;t have ack capability */
)brace
DECL|function|lh7a40x_mask_cpld_irq
r_static
r_void
id|lh7a40x_mask_cpld_irq
(paren
id|u32
id|irq
)paren
(brace
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_LPD7A40X_ETH_INT
suffix:colon
id|CPLD_INTERRUPTS
op_assign
id|CPLD_INTERRUPTS
op_or
l_int|0x4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_LPD7A400_TS
suffix:colon
id|CPLD_INTERRUPTS
op_assign
id|CPLD_INTERRUPTS
op_or
l_int|0x8
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|lh7a40x_unmask_cpld_irq
r_static
r_void
id|lh7a40x_unmask_cpld_irq
(paren
id|u32
id|irq
)paren
(brace
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_LPD7A40X_ETH_INT
suffix:colon
id|CPLD_INTERRUPTS
op_assign
id|CPLD_INTERRUPTS
op_amp
op_complement
l_int|0x4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_LPD7A400_TS
suffix:colon
id|CPLD_INTERRUPTS
op_assign
id|CPLD_INTERRUPTS
op_amp
op_complement
l_int|0x8
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|variable|lh7a40x_cpld_chip
r_static
r_struct
id|irqchip
id|lh7a40x_cpld_chip
op_assign
(brace
dot
id|ack
op_assign
id|lh7a40x_ack_cpld_irq
comma
dot
id|mask
op_assign
id|lh7a40x_mask_cpld_irq
comma
dot
id|unmask
op_assign
id|lh7a40x_unmask_cpld_irq
comma
)brace
suffix:semicolon
DECL|function|lh7a40x_cpld_handler
r_static
r_void
id|lh7a40x_cpld_handler
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|mask
op_assign
id|CPLD_INTERRUPTS
suffix:semicolon
id|desc-&gt;chip-&gt;ack
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mask
op_amp
l_int|0x1
)paren
op_eq
l_int|0
)paren
multiline_comment|/* WLAN */
id|IRQ_DISPATCH
(paren
id|IRQ_LPD7A40X_ETH_INT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mask
op_amp
l_int|0x2
)paren
op_eq
l_int|0
)paren
multiline_comment|/* Touch */
id|IRQ_DISPATCH
(paren
id|IRQ_LPD7A400_TS
)paren
suffix:semicolon
id|desc-&gt;chip-&gt;unmask
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* Level-triggered need this */
)brace
multiline_comment|/* IRQ initialization */
DECL|function|lh7a40x_init_board_irq
r_void
id|__init
id|lh7a40x_init_board_irq
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
multiline_comment|/* Rev A (v2.8): PF0, PF1, PF2, and PF3 are available IRQs.&n;&t;&t;                 PF7 supports the CPLD.&n;&t;&t;   Rev B (v3.4): PF0, PF1, and PF2 are available IRQs.&n;&t;&t;                 PF3 supports the CPLD.&n;&t;&t;   (Some) LPD7A404 prerelease boards report a version&n;&t;&t;   number of 0x16, but we force an override since the&n;&t;&t;   hardware is of the newer variety.&n;&t;&t;*/
r_int
r_char
id|cpld_version
op_assign
id|CPLD_REVISION
suffix:semicolon
r_int
id|pinCPLD
suffix:semicolon
macro_line|#if defined CONFIG_MACH_LPD7A404
id|cpld_version
op_assign
l_int|0x34
suffix:semicolon
multiline_comment|/* Override, for now */
macro_line|#endif
id|pinCPLD
op_assign
(paren
id|cpld_version
op_eq
l_int|0x28
)paren
ques
c_cond
l_int|7
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* First, configure user controlled GPIOF interrupts  */
id|GPIO_PFDD
op_and_assign
op_complement
l_int|0x0f
suffix:semicolon
multiline_comment|/* PF0-3 are inputs */
id|GPIO_INTTYPE1
op_and_assign
op_complement
l_int|0x0f
suffix:semicolon
multiline_comment|/* PF0-3 are level triggered */
id|GPIO_INTTYPE2
op_and_assign
op_complement
l_int|0x0f
suffix:semicolon
multiline_comment|/* PF0-3 are active low */
id|barrier
(paren
)paren
suffix:semicolon
id|GPIO_GPIOFINTEN
op_or_assign
l_int|0x0f
suffix:semicolon
multiline_comment|/* Enable PF0, PF1, PF2, and PF3 IRQs */
multiline_comment|/* Then, configure CPLD interrupt */
id|CPLD_INTERRUPTS
op_assign
l_int|0x0c
suffix:semicolon
multiline_comment|/* Disable all CPLD interrupts */
id|GPIO_PFDD
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|pinCPLD
)paren
suffix:semicolon
multiline_comment|/* Make input */
id|GPIO_INTTYPE1
op_or_assign
(paren
l_int|1
op_lshift
id|pinCPLD
)paren
suffix:semicolon
multiline_comment|/* Edge triggered */
id|GPIO_INTTYPE2
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|pinCPLD
)paren
suffix:semicolon
multiline_comment|/* Active low */
id|barrier
(paren
)paren
suffix:semicolon
id|GPIO_GPIOFINTEN
op_or_assign
(paren
l_int|1
op_lshift
id|pinCPLD
)paren
suffix:semicolon
multiline_comment|/* Enable */
multiline_comment|/* Cascade CPLD interrupts */
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_BOARD_START
suffix:semicolon
id|irq
OL
id|IRQ_BOARD_START
op_plus
id|NR_IRQ_BOARD
suffix:semicolon
op_increment
id|irq
)paren
(brace
id|set_irq_chip
(paren
id|irq
comma
op_amp
id|lh7a40x_cpld_chip
)paren
suffix:semicolon
id|set_irq_handler
(paren
id|irq
comma
id|do_edge_IRQ
)paren
suffix:semicolon
id|set_irq_flags
(paren
id|irq
comma
id|IRQF_VALID
)paren
suffix:semicolon
)brace
id|set_irq_chained_handler
(paren
(paren
id|cpld_version
op_eq
l_int|0x28
)paren
ques
c_cond
id|IRQ_CPLD_V28
suffix:colon
id|IRQ_CPLD_V34
comma
id|lh7a40x_cpld_handler
)paren
suffix:semicolon
)brace
eof
