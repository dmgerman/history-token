multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * Routines for generic manipulation of the interrupts found on the MIPS&n; * Atlas board.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mips-boards/atlas.h&gt;
macro_line|#include &lt;asm/mips-boards/atlasint.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
DECL|variable|atlas_hw0_icregs
r_static
r_struct
id|atlas_ictrl_regs
op_star
id|atlas_hw0_icregs
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|mipsIRQ
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DEBUG_INT(x...) printk(x)
macro_line|#else
DECL|macro|DEBUG_INT
mdefine_line|#define DEBUG_INT(x...)
macro_line|#endif
DECL|function|disable_atlas_irq
r_void
id|disable_atlas_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|atlas_hw0_icregs-&gt;intrsten
op_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|ATLASINT_BASE
)paren
)paren
suffix:semicolon
id|iob
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|enable_atlas_irq
r_void
id|enable_atlas_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|atlas_hw0_icregs-&gt;intseten
op_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|ATLASINT_BASE
)paren
)paren
suffix:semicolon
id|iob
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|startup_atlas_irq
r_static
r_int
r_int
id|startup_atlas_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_atlas_irq
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
DECL|macro|shutdown_atlas_irq
mdefine_line|#define shutdown_atlas_irq&t;disable_atlas_irq
DECL|macro|mask_and_ack_atlas_irq
mdefine_line|#define mask_and_ack_atlas_irq disable_atlas_irq
DECL|function|end_atlas_irq
r_static
r_void
id|end_atlas_irq
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
id|enable_atlas_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|atlas_irq_type
r_static
r_struct
id|hw_interrupt_type
id|atlas_irq_type
op_assign
(brace
l_string|&quot;Atlas&quot;
comma
id|startup_atlas_irq
comma
id|shutdown_atlas_irq
comma
id|enable_atlas_irq
comma
id|disable_atlas_irq
comma
id|mask_and_ack_atlas_irq
comma
id|end_atlas_irq
comma
l_int|NULL
)brace
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
DECL|function|atlas_hw0_irqdispatch
r_void
id|atlas_hw0_irqdispatch
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
id|int_status
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|int_status
op_assign
id|atlas_hw0_icregs-&gt;intstatus
suffix:semicolon
multiline_comment|/* if int_status == 0, then the interrupt has already been cleared */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|int_status
op_eq
l_int|0
)paren
)paren
r_return
suffix:semicolon
id|irq
op_assign
id|ATLASINT_BASE
op_plus
id|ls1bit32
c_func
(paren
id|int_status
)paren
suffix:semicolon
id|DEBUG_INT
c_func
(paren
l_string|&quot;atlas_hw0_irqdispatch: irq=%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|arch_init_irq
r_void
id|__init
id|arch_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|atlas_hw0_icregs
op_assign
(paren
r_struct
id|atlas_ictrl_regs
op_star
)paren
id|ioremap
(paren
id|ATLAS_ICTRL_REGS_BASE
comma
r_sizeof
(paren
r_struct
id|atlas_ictrl_regs
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Mask out all interrupt by writing &quot;1&quot; to all bit position in&n;&t; * the interrupt reset reg.&n;&t; */
id|atlas_hw0_icregs-&gt;intrsten
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* Now safe to set the exception vector. */
id|set_except_vector
c_func
(paren
l_int|0
comma
id|mipsIRQ
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ATLASINT_BASE
suffix:semicolon
id|i
op_le
id|ATLASINT_END
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
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|atlas_irq_type
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|irq_desc
(braket
id|i
)braket
dot
id|lock
)paren
suffix:semicolon
)brace
)brace
eof
