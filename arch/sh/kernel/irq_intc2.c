multiline_comment|/*&n; * linux/arch/sh/kernel/irq_intc2.c&n; *&n; * Copyright (C) 2001 David J. Mckay (david.mckay@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.                            &n; *&n; * Interrupt handling for INTC2-based IRQ.&n; *&n; * These are the &quot;new Hitachi style&quot; interrupts, as present on the &n; * Hitachi 7751 and the STM ST40 STB1.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
DECL|struct|intc2_data
r_struct
id|intc2_data
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* Address of Interrupt Priority Register */
DECL|member|mask
r_int
id|mask
suffix:semicolon
multiline_comment|/*Mask to apply */
)brace
suffix:semicolon
DECL|variable|intc2_data
r_static
r_struct
id|intc2_data
id|intc2_data
(braket
id|NR_INTC2_IRQS
)braket
suffix:semicolon
r_static
r_void
id|enable_intc2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|disable_intc2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/* shutdown is same as &quot;disable&quot; */
DECL|macro|shutdown_intc2_irq
mdefine_line|#define shutdown_intc2_irq disable_intc2_irq
r_static
r_void
id|mask_and_ack_intc2
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|end_intc2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|function|startup_intc2_irq
r_static
r_int
r_int
id|startup_intc2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_intc2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* never anything pending */
)brace
DECL|variable|intc2_irq_type
r_static
r_struct
id|hw_interrupt_type
id|intc2_irq_type
op_assign
(brace
l_string|&quot;INTC2-IRQ&quot;
comma
id|startup_intc2_irq
comma
id|shutdown_intc2_irq
comma
id|enable_intc2_irq
comma
id|disable_intc2_irq
comma
id|mask_and_ack_intc2
comma
id|end_intc2_irq
)brace
suffix:semicolon
DECL|function|disable_intc2_irq
r_static
r_void
id|disable_intc2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|addr
suffix:semicolon
r_int
id|offset
op_assign
id|irq
op_minus
id|INTC2_FIRST_IRQ
suffix:semicolon
r_int
id|val
comma
id|flags
suffix:semicolon
singleline_comment|// Sanity check
r_if
c_cond
(paren
id|offset
OL
l_int|0
op_logical_or
id|offset
op_ge
id|NR_INTC2_IRQS
)paren
(brace
r_return
suffix:semicolon
)brace
id|addr
op_assign
id|intc2_data
(braket
id|offset
)braket
dot
id|addr
op_plus
id|INTC2_INTMSK_OFFSET
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
suffix:semicolon
id|val
op_or_assign
id|intc2_data
(braket
id|offset
)braket
dot
id|mask
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_intc2_irq
r_static
r_void
id|enable_intc2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|offset
op_assign
id|irq
op_minus
id|INTC2_FIRST_IRQ
suffix:semicolon
singleline_comment|// Sanity check
r_if
c_cond
(paren
id|offset
OL
l_int|0
op_logical_or
id|offset
op_ge
id|NR_INTC2_IRQS
)paren
(brace
r_return
suffix:semicolon
)brace
id|ctrl_outl
c_func
(paren
id|intc2_data
(braket
id|offset
)braket
dot
id|mask
comma
id|intc2_data
(braket
id|offset
)braket
dot
id|addr
op_plus
id|INTC2_INTMSKCLR_OFFSET
)paren
suffix:semicolon
)brace
DECL|function|mask_and_ack_intc2
r_static
r_void
id|mask_and_ack_intc2
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_intc2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_intc2_irq
r_static
r_void
id|end_intc2_irq
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
id|enable_intc2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|make_intc2_irq
r_void
id|make_intc2_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|group
comma
r_int
id|pos
comma
r_int
id|priority
)paren
(brace
r_int
id|offset
op_assign
id|irq
op_minus
id|INTC2_FIRST_IRQ
suffix:semicolon
r_int
id|flags
comma
id|val
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
op_logical_or
id|offset
op_ge
id|NR_INTC2_IRQS
)paren
(brace
r_return
suffix:semicolon
)brace
id|disable_irq_nosync
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* Fill the data we need */
id|intc2_data
(braket
id|offset
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
id|intc2_data
(braket
id|offset
)braket
dot
id|mask
op_assign
l_int|1
op_lshift
id|pos
suffix:semicolon
multiline_comment|/* Set the priority level */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|ctrl_inl
c_func
(paren
id|addr
op_plus
id|INTC2_INTPRI_OFFSET
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|priority
)paren
op_lshift
(paren
id|group
op_lshift
l_int|4
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|val
comma
id|addr
op_plus
id|INTC2_INTPRI_OFFSET
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_assign
op_amp
id|intc2_irq_type
suffix:semicolon
id|disable_intc2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
eof
