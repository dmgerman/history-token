multiline_comment|/*&n; * arch/ppc/syslib/gt64260_pic.c&n; *&n; * Interrupt controller support for Galileo&squot;s GT64260.&n; *&n; * Author: Chris Zankel &lt;chris@mvista.com&gt;&n; * Modified by: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * Based on sources from Rabeeh Khoury / Galileo Technology&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * This file contains the specific functions to support the GT64260&n; * interrupt controller.&n; *&n; * The GT64260 has two main interrupt registers (high and low) that&n; * summarizes the interrupts generated by the units of the GT64260.&n; * Each bit is assigned to an interrupt number, where the low register&n; * are assigned from IRQ0 to IRQ31 and the high cause register&n; * from IRQ32 to IRQ63&n; * The GPP (General Purpose Port) interrupts are assigned from IRQ64 (GPP0)&n; * to IRQ95 (GPP31).&n; * get_irq() returns the lowest interrupt number that is currently asserted.&n; *&n; * Note:&n; *  - This driver does not initialize the GPP when used as an interrupt&n; *    input.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/gt64260.h&gt;
multiline_comment|/* ========================== forward declaration ========================== */
r_static
r_void
id|gt64260_unmask_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|gt64260_mask_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* ========================== local declarations =========================== */
DECL|variable|gt64260_pic
r_struct
id|hw_interrupt_type
id|gt64260_pic
op_assign
(brace
l_string|&quot; GT64260_PIC &quot;
comma
multiline_comment|/* typename */
l_int|NULL
comma
multiline_comment|/* startup */
l_int|NULL
comma
multiline_comment|/* shutdown */
id|gt64260_unmask_irq
comma
multiline_comment|/* enable */
id|gt64260_mask_irq
comma
multiline_comment|/* disable */
id|gt64260_mask_irq
comma
multiline_comment|/* ack */
l_int|NULL
comma
multiline_comment|/* end */
l_int|NULL
multiline_comment|/* set_affinity */
)brace
suffix:semicolon
DECL|variable|gt64260_irq_base
id|u32
id|gt64260_irq_base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* GT64260 handles the next 96 IRQs from here */
multiline_comment|/* gt64260_init_irq()&n; *&n; *  This function initializes the interrupt controller. It assigns&n; *  all interrupts from IRQ0 to IRQ95 to the gt64260 interrupt controller.&n; *&n; * Input Variable(s):&n; *  None.&n; *&n; * Outpu. Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  void&n; *&n; * Note:&n; *  We register all GPP inputs as interrupt source, but disable them.&n; */
id|__init
r_void
DECL|function|gt64260_init_irq
id|gt64260_init_irq
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
l_string|&quot;gt64260_init_irq: enter&quot;
comma
l_int|0x0
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
id|gt_write
c_func
(paren
id|GT64260_GPP_INTR_MASK
comma
id|ppc_cached_irq_mask
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|gt_write
c_func
(paren
id|GT64260_GPP_INTR_CAUSE
comma
l_int|0
)paren
suffix:semicolon
id|gt_write
c_func
(paren
id|GT64260_IC_CPU_INTR_MASK_LO
comma
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|gt_write
c_func
(paren
id|GT64260_IC_CPU_INTR_MASK_HI
comma
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* use the gt64260 for all (possible) interrupt sources */
r_for
c_loop
(paren
id|i
op_assign
id|gt64260_irq_base
suffix:semicolon
id|i
OL
(paren
id|gt64260_irq_base
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
id|handler
op_assign
op_amp
id|gt64260_pic
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
l_string|&quot;gt64260_init_irq: exit&quot;
comma
l_int|0x0
)paren
suffix:semicolon
)brace
multiline_comment|/* gt64260_get_irq()&n; *&n; *  This function returns the lowest interrupt number of all interrupts that&n; *  are currently asserted.&n; *&n; * Input Variable(s):&n; *  struct pt_regs*&t;not used&n; *&n; * Output Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  int&t;&lt;interrupt number&gt; or -2 (bogus interrupt)&n; *&n; */
r_int
DECL|function|gt64260_get_irq
id|gt64260_get_irq
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
id|irq
op_assign
id|gt_read
c_func
(paren
id|GT64260_IC_MAIN_CAUSE_LO
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
id|gt_read
c_func
(paren
id|GT64260_IC_MAIN_CAUSE_HI
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
l_int|0x0f000db7
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
(brace
id|irq
op_assign
op_minus
l_int|2
suffix:semicolon
multiline_comment|/* bogus interrupt, should never happen */
)brace
r_else
(brace
r_if
c_cond
(paren
id|irq
op_ge
l_int|24
)paren
(brace
id|irq_gpp
op_assign
id|gt_read
c_func
(paren
id|GT64260_GPP_INTR_CAUSE
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
(brace
id|irq
op_assign
op_minus
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|irq
op_assign
id|irq_gpp
op_plus
l_int|64
suffix:semicolon
id|gt_write
c_func
(paren
id|GT64260_GPP_INTR_CAUSE
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
(brace
id|irq
op_add_assign
l_int|32
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
r_else
(brace
r_return
id|gt64260_irq_base
op_plus
id|irq
suffix:semicolon
)brace
)brace
multiline_comment|/* gt64260_unmask_irq()&n; *&n; *  This function enables an interrupt.&n; *&n; * Input Variable(s):&n; *  unsigned int&t;interrupt number (IRQ0...IRQ95).&n; *&n; * Output Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  void&n; */
r_static
r_void
DECL|function|gt64260_unmask_irq
id|gt64260_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|gt64260_irq_base
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
(brace
multiline_comment|/* unmask GPP irq */
id|gt_write
c_func
(paren
id|GT64260_GPP_INTR_MASK
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
)brace
r_else
(brace
multiline_comment|/* mask high interrupt register */
id|gt_write
c_func
(paren
id|GT64260_IC_CPU_INTR_MASK_HI
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
)brace
r_else
(brace
multiline_comment|/* mask low interrupt register */
id|gt_write
c_func
(paren
id|GT64260_IC_CPU_INTR_MASK_LO
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
)brace
)brace
multiline_comment|/* gt64260_mask_irq()&n; *&n; *  This funktion disables the requested interrupt.&n; *&n; * Input Variable(s):&n; *  unsigned int&t;interrupt number (IRQ0...IRQ95).&n; *&n; * Output Variable(s):&n; *  None.&n; *&n; * Returns:&n; *  void&n; */
r_static
r_void
DECL|function|gt64260_mask_irq
id|gt64260_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|gt64260_irq_base
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
(brace
multiline_comment|/* mask GPP irq */
id|gt_write
c_func
(paren
id|GT64260_GPP_INTR_MASK
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
)brace
r_else
(brace
multiline_comment|/* mask high interrupt register */
id|gt_write
c_func
(paren
id|GT64260_IC_CPU_INTR_MASK_HI
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
)brace
r_else
(brace
multiline_comment|/* mask low interrupt register */
id|gt_write
c_func
(paren
id|GT64260_IC_CPU_INTR_MASK_LO
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
)brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|36
)paren
(brace
multiline_comment|/* Seems necessary for SDMA interrupts */
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
eof
