multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000, 2001 MIPS Technologies, Inc.&n; * Copyright (C) 2001 Ralf Baechle&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Routines for generic manipulation of the interrupts found on the MIPS &n; * Malta board.&n; * The interrupt controller is located in the South Bridge a PIIX4 device &n; * with two internal 82C95 interrupt controllers.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mips-boards/malta.h&gt;
macro_line|#include &lt;asm/mips-boards/maltaint.h&gt;
macro_line|#include &lt;asm/mips-boards/piix4.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
macro_line|#include &lt;asm/mips-boards/generic.h&gt;
r_extern
id|asmlinkage
r_void
id|mipsIRQ
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|malta_hw0_irqdispatch
r_void
id|malta_hw0_irqdispatch
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
multiline_comment|/*  &n;&t; * Determine highest priority pending interrupt by performing a PCI&n;&t; * Interrupt Acknowledge cycle.&n;&t; */
id|GT_READ
c_func
(paren
id|GT_PCI0_IACK_OFS
comma
id|irq
)paren
suffix:semicolon
id|irq
op_and_assign
l_int|0xFF
suffix:semicolon
multiline_comment|/*  &n;&t; * IRQ7 is used to detect spurious interrupts.  The interrupt&n;&t; * acknowledge cycle returns IRQ7, if no interrupts is requested.  We&n;&t; * can differentiate between this situation and a &quot;normal&quot; IRQ7 by&n;&t; * reading the ISR.&n;&t; */
r_if
c_cond
(paren
id|irq
op_eq
l_int|7
)paren
(brace
id|outb
c_func
(paren
id|PIIX4_OCW3_SEL
op_or
id|PIIX4_OCW3_ISR
comma
id|PIIX4_ICTLR1_OCW3
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|PIIX4_ICTLR1_OCW3
)paren
op_amp
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Spurious interrupt. */
)brace
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
id|set_except_vector
c_func
(paren
l_int|0
comma
id|mipsIRQ
)paren
suffix:semicolon
id|init_generic_irq
c_func
(paren
)paren
suffix:semicolon
id|init_i8259_irqs
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_REMOTE_DEBUG
r_if
c_cond
(paren
id|remote_debug
)paren
(brace
id|set_debug_traps
c_func
(paren
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
