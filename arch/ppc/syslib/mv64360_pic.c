multiline_comment|/*&n; * arch/ppc/kernel/mv64360_pic.c&n; *&n; * Interrupt controller support for Marvell&squot;s MV64360.&n; *&n; * Author: Rabeeh Khoury &lt;rabeeh@galileo.co.il&gt;&n; * Based on MV64360 PIC written by&n; * Chris Zankel &lt;chris@mvista.com&gt;&n; * Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * Copyright 2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * This file contains the specific functions to support the MV64360&n; * interrupt controller.&n; *&n; * The MV64360 has two main interrupt registers (high and low) that&n; * summarizes the interrupts generated by the units of the MV64360.&n; * Each bit is assigned to an interrupt number, where the low register&n; * are assigned from IRQ0 to IRQ31 and the high cause register&n; * from IRQ32 to IRQ63&n; * The GPP (General Purpose Pins) interrupts are assigned from IRQ64 (GPP0)&n; * to IRQ95 (GPP31).&n; * get_irq() returns the lowest interrupt number that is currently asserted.&n; *&n; * Note:&n; *  - This driver does not initialize the GPP when used as an interrupt&n; *    input.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mv64x60.h&gt;
macro_line|#ifdef CONFIG_IRQ_ALL_CPUS
macro_line|#error &quot;The mv64360 does not support distribution of IRQs on all CPUs&quot;
macro_line|#endif
multiline_comment|/* ========================== forward declaration ========================== */
r_static
r_void
id|mv64360_unmask_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|mv64360_mask_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|mv64360_cpu_error_int_handler
c_func
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
suffix:semicolon
r_static
id|irqreturn_t
id|mv64360_sram_error_int_handler
c_func
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
suffix:semicolon
r_static
id|irqreturn_t
id|mv64360_pci_error_int_handler
c_func
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
suffix:semicolon
multiline_comment|/* ========================== local declarations =========================== */
DECL|variable|mv64360_pic
r_struct
id|hw_interrupt_type
id|mv64360_pic
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot; mv64360  &quot;
comma
dot
id|enable
op_assign
id|mv64360_unmask_irq
comma
dot
id|disable
op_assign
id|mv64360_mask_irq
comma
dot
id|ack
op_assign
id|mv64360_mask_irq
comma
dot
id|end
op_assign
id|mv64360_unmask_irq
comma
)brace
suffix:semicolon
DECL|macro|CPU_INTR_STR
mdefine_line|#define CPU_INTR_STR&t;&quot;mv64360 cpu interface error&quot;
DECL|macro|SRAM_INTR_STR
mdefine_line|#define SRAM_INTR_STR&t;&quot;mv64360 internal sram error&quot;
DECL|macro|PCI0_INTR_STR
mdefine_line|#define PCI0_INTR_STR&t;&quot;mv64360 pci 0 error&quot;
DECL|macro|PCI1_INTR_STR
mdefine_line|#define PCI1_INTR_STR&t;&quot;mv64360 pci 1 error&quot;
DECL|variable|bh
r_static
r_struct
id|mv64x60_handle
id|bh
suffix:semicolon
DECL|variable|mv64360_irq_base
id|u32
id|mv64360_irq_base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* MV64360 handles the next 96 IRQs from here */
multiline_comment|/* mv64360_init_irq()&n; *&n; * This function initializes the interrupt controller. It assigns&n; * all interrupts from IRQ0 to IRQ95 to the mv64360 interrupt controller.&n; *&n; * Input Variable(s):&n; *  None.&n; *&n; * Outpu. Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  void&n; *&n; * Note:&n; *  We register all GPP inputs as interrupt source, but disable them.&n; */
r_void
id|__init
DECL|function|mv64360_init_irq
id|mv64360_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mv64360_init_irq: enter&quot;
comma
l_int|0x0
)paren
suffix:semicolon
id|bh.v_base
op_assign
id|mv64x60_get_bridge_vbase
c_func
(paren
)paren
suffix:semicolon
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
op_assign
l_int|0x0f000000
suffix:semicolon
multiline_comment|/* Enable GPP intrs */
id|ppc_cached_irq_mask
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable all interrupts and clear current interrupts */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_MASK
comma
id|ppc_cached_irq_mask
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU0_INTR_MASK_LO
comma
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU0_INTR_MASK_HI
comma
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* All interrupts are level interrupts */
r_for
c_loop
(paren
id|i
op_assign
id|mv64360_irq_base
suffix:semicolon
id|i
OL
(paren
id|mv64360_irq_base
op_plus
l_int|96
)paren
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
op_or_assign
id|IRQ_LEVEL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|mv64360_pic
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mv64360_init_irq: exit&quot;
comma
l_int|0x0
)paren
suffix:semicolon
)brace
multiline_comment|/* mv64360_get_irq()&n; *&n; * This function returns the lowest interrupt number of all interrupts that&n; * are currently asserted.&n; *&n; * Input Variable(s):&n; *  struct pt_regs*&t;not used&n; *&n; * Output Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  int&t;&lt;interrupt number&gt; or -2 (bogus interrupt)&n; *&n; */
r_int
DECL|function|mv64360_get_irq
id|mv64360_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
r_int
id|irq_gpp
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t; * Second CPU gets only doorbell (message) interrupts.&n;&t; * The doorbell interrupt is BIT28 in the main interrupt low cause reg.&n;&t; */
r_int
id|cpu_nr
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_nr
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_MAIN_CAUSE_LO
)paren
op_amp
(paren
l_int|1
op_lshift
id|MV64x60_IRQ_DOORBELL
)paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|mv64360_irq_base
op_plus
id|MV64x60_IRQ_DOORBELL
suffix:semicolon
)brace
macro_line|#endif
id|irq
op_assign
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_MAIN_CAUSE_LO
)paren
suffix:semicolon
id|irq
op_assign
id|__ilog2
c_func
(paren
(paren
id|irq
op_amp
l_int|0x3dfffffe
)paren
op_amp
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
op_minus
l_int|1
)paren
(brace
id|irq
op_assign
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_MAIN_CAUSE_HI
)paren
suffix:semicolon
id|irq
op_assign
id|__ilog2
c_func
(paren
(paren
id|irq
op_amp
l_int|0x1f0003f7
)paren
op_amp
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
op_minus
l_int|1
)paren
id|irq
op_assign
op_minus
l_int|2
suffix:semicolon
multiline_comment|/* bogus interrupt, should never happen */
r_else
(brace
r_if
c_cond
(paren
(paren
id|irq
op_ge
l_int|24
)paren
op_logical_and
(paren
id|irq
OL
id|MV64x60_IRQ_DOORBELL
)paren
)paren
(brace
id|irq_gpp
op_assign
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_CAUSE
)paren
suffix:semicolon
id|irq_gpp
op_assign
id|__ilog2
c_func
(paren
id|irq_gpp
op_amp
id|ppc_cached_irq_mask
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_gpp
op_eq
op_minus
l_int|1
)paren
id|irq
op_assign
op_minus
l_int|2
suffix:semicolon
r_else
(brace
id|irq
op_assign
id|irq_gpp
op_plus
l_int|64
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_CAUSE
comma
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|64
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
id|irq
op_add_assign
l_int|32
suffix:semicolon
)brace
)brace
(paren
r_void
)paren
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_CAUSE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
r_return
(paren
id|irq
)paren
suffix:semicolon
r_else
r_return
(paren
id|mv64360_irq_base
op_plus
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/* mv64360_unmask_irq()&n; *&n; * This function enables an interrupt.&n; *&n; * Input Variable(s):&n; *  unsigned int&t;interrupt number (IRQ0...IRQ95).&n; *&n; * Output Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  void&n; */
r_static
r_void
DECL|function|mv64360_unmask_irq
id|mv64360_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* second CPU gets only doorbell interrupts */
r_if
c_cond
(paren
(paren
id|irq
op_minus
id|mv64360_irq_base
)paren
op_eq
id|MV64x60_IRQ_DOORBELL
)paren
(brace
id|mv64x60_set_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU1_INTR_MASK_LO
comma
(paren
l_int|1
op_lshift
id|MV64x60_IRQ_DOORBELL
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|irq
op_sub_assign
id|mv64360_irq_base
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|31
)paren
(brace
r_if
c_cond
(paren
id|irq
OG
l_int|63
)paren
multiline_comment|/* unmask GPP irq */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_MASK
comma
id|ppc_cached_irq_mask
(braket
l_int|2
)braket
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|64
)paren
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/* mask high interrupt register */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU0_INTR_MASK_HI
comma
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|32
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* mask low interrupt register */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU0_INTR_MASK_LO
comma
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
op_or_assign
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_MASK
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* mv64360_mask_irq()&n; *&n; * This function disables the requested interrupt.&n; *&n; * Input Variable(s):&n; *  unsigned int&t;interrupt number (IRQ0...IRQ95).&n; *&n; * Output Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  void&n; */
r_static
r_void
DECL|function|mv64360_mask_irq
id|mv64360_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
(paren
id|irq
op_minus
id|mv64360_irq_base
)paren
op_eq
id|MV64x60_IRQ_DOORBELL
)paren
(brace
id|mv64x60_clr_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU1_INTR_MASK_LO
comma
(paren
l_int|1
op_lshift
id|MV64x60_IRQ_DOORBELL
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|irq
op_sub_assign
id|mv64360_irq_base
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|31
)paren
(brace
r_if
c_cond
(paren
id|irq
OG
l_int|63
)paren
multiline_comment|/* mask GPP irq */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_MASK
comma
id|ppc_cached_irq_mask
(braket
l_int|2
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|64
)paren
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/* mask high interrupt register */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU0_INTR_MASK_HI
comma
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|32
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* mask low interrupt register */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_IC_CPU0_INTR_MASK_LO
comma
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_MASK
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|mv64360_cpu_error_int_handler
id|mv64360_cpu_error_int_handler
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mv64360_cpu_error_int_handler: %s 0x%08x&bslash;n&quot;
comma
l_string|&quot;Error on CPU interface - Cause regiser&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_CAUSE
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tCPU error register dump:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress low  0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_ADDR_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress high 0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_ADDR_HI
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tData low     0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_DATA_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tData high    0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_DATA_HI
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tParity       0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_PARITY
)paren
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|mv64360_sram_error_int_handler
id|mv64360_sram_error_int_handler
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mv64360_sram_error_int_handler: %s 0x%08x&bslash;n&quot;
comma
l_string|&quot;Error in internal SRAM - Cause register&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_CAUSE
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tSRAM error register dump:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress Low  0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_ADDR_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress High 0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_ADDR_HI
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tData Low     0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_DATA_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tData High    0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_DATA_HI
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tParity       0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_PARITY
)paren
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|mv64360_pci_error_int_handler
id|mv64360_pci_error_int_handler
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
id|val
suffix:semicolon
r_int
r_int
id|pci_bus
op_assign
(paren
r_int
r_int
)paren
id|dev_id
suffix:semicolon
r_if
c_cond
(paren
id|pci_bus
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Error on PCI 0 */
id|val
op_assign
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_CAUSE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error in PCI %d Interface&bslash;n&quot;
comma
l_string|&quot;mv64360_pci_error_int_handler&quot;
comma
id|pci_bus
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tPCI %d error register dump:&bslash;n&quot;
comma
id|pci_bus
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tCause register 0x%08x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress Low    0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_ADDR_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress High   0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_ADDR_HI
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAttribute      0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_DATA_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tCommand        0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_CMD
)paren
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_CAUSE
comma
op_complement
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_bus
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Error on PCI 1 */
id|val
op_assign
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_CAUSE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error in PCI %d Interface&bslash;n&quot;
comma
l_string|&quot;mv64360_pci_error_int_handler&quot;
comma
id|pci_bus
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tPCI %d error register dump:&bslash;n&quot;
comma
id|pci_bus
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tCause register 0x%08x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress Low    0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_ADDR_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAddress High   0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_ADDR_HI
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tAttribute      0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_DATA_LO
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;&bslash;tCommand        0x%08x&bslash;n&quot;
comma
id|mv64x60_read
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_CMD
)paren
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_CAUSE
comma
op_complement
id|val
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|mv64360_register_hdlrs
id|mv64360_register_hdlrs
c_func
(paren
r_void
)paren
(brace
id|u32
id|mask
suffix:semicolon
r_int
id|rc
suffix:semicolon
multiline_comment|/* Clear old errors and register CPU interface error intr handler */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|request_irq
c_func
(paren
id|MV64x60_IRQ_CPU_ERR
op_plus
id|mv64360_irq_base
comma
id|mv64360_cpu_error_int_handler
comma
id|SA_INTERRUPT
comma
id|CPU_INTR_STR
comma
l_int|0
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t register cpu error handler: %d&quot;
comma
id|rc
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_MASK
comma
l_int|0
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_ERR_MASK
comma
l_int|0x000000ff
)paren
suffix:semicolon
multiline_comment|/* Clear old errors and register internal SRAM error intr handler */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64360_SRAM_ERR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|request_irq
c_func
(paren
id|MV64360_IRQ_SRAM_PAR_ERR
op_plus
id|mv64360_irq_base
comma
id|mv64360_sram_error_int_handler
comma
id|SA_INTERRUPT
comma
id|SRAM_INTR_STR
comma
l_int|0
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t register SRAM error handler: %d&quot;
comma
id|rc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Bit 0 reserved on 64360 and erratum FEr PCI-#11 (PCI internal&n;&t; * data parity error set incorrectly) on rev 0 &amp; 1 of 64460 requires&n;&t; * bit 0 to be cleared.&n;&t; */
id|mask
op_assign
l_int|0x00a50c24
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mv64x60_get_bridge_type
c_func
(paren
)paren
op_eq
id|MV64x60_TYPE_MV64460
)paren
op_logical_and
(paren
id|mv64x60_get_bridge_rev
c_func
(paren
)paren
OG
l_int|1
)paren
)paren
id|mask
op_or_assign
l_int|0x1
suffix:semicolon
multiline_comment|/* enable DPErr on 64460 */
multiline_comment|/* Clear old errors and register PCI 0 error intr handler */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|request_irq
c_func
(paren
id|MV64360_IRQ_PCI0
op_plus
id|mv64360_irq_base
comma
id|mv64360_pci_error_int_handler
comma
id|SA_INTERRUPT
comma
id|PCI0_INTR_STR
comma
(paren
r_void
op_star
)paren
l_int|0
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t register pci 0 error handler: %d&quot;
comma
id|rc
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_MASK
comma
l_int|0
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ERR_MASK
comma
id|mask
)paren
suffix:semicolon
multiline_comment|/* Clear old errors and register PCI 1 error intr handler */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|request_irq
c_func
(paren
id|MV64360_IRQ_PCI1
op_plus
id|mv64360_irq_base
comma
id|mv64360_pci_error_int_handler
comma
id|SA_INTERRUPT
comma
id|PCI1_INTR_STR
comma
(paren
r_void
op_star
)paren
l_int|1
)paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t register pci 1 error handler: %d&quot;
comma
id|rc
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_MASK
comma
l_int|0
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ERR_MASK
comma
id|mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mv64360_register_hdlrs
id|arch_initcall
c_func
(paren
id|mv64360_register_hdlrs
)paren
suffix:semicolon
eof
