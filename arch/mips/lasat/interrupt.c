multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Routines for generic manipulation of the interrupts found on the &n; * Lasat boards.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/lasat/lasatint.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
DECL|variable|lasat_int_status
r_static
r_volatile
r_int
op_star
id|lasat_int_status
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|lasat_int_mask
r_static
r_volatile
r_int
op_star
id|lasat_int_mask
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|lasat_int_mask_shift
r_static
r_volatile
r_int
id|lasat_int_mask_shift
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|lasatIRQ
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|disable_lasat_irq
r_void
id|disable_lasat_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|lasat_int_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq_nr
)paren
op_lshift
id|lasat_int_mask_shift
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_lasat_irq
r_void
id|enable_lasat_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|lasat_int_mask
op_or_assign
(paren
l_int|1
op_lshift
id|irq_nr
)paren
op_lshift
id|lasat_int_mask_shift
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_lasat_irq
r_static
r_int
r_int
id|startup_lasat_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_lasat_irq
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
DECL|macro|shutdown_lasat_irq
mdefine_line|#define shutdown_lasat_irq&t;disable_lasat_irq
DECL|macro|mask_and_ack_lasat_irq
mdefine_line|#define mask_and_ack_lasat_irq disable_lasat_irq
DECL|function|end_lasat_irq
r_static
r_void
id|end_lasat_irq
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
id|enable_lasat_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|lasat_irq_type
r_static
r_struct
id|hw_interrupt_type
id|lasat_irq_type
op_assign
(brace
l_string|&quot;Lasat&quot;
comma
id|startup_lasat_irq
comma
id|shutdown_lasat_irq
comma
id|enable_lasat_irq
comma
id|disable_lasat_irq
comma
id|mask_and_ack_lasat_irq
comma
id|end_lasat_irq
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
DECL|variable|get_int_status
r_static
r_int
r_int
(paren
op_star
id|get_int_status
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_int_status_100
r_static
r_int
r_int
id|get_int_status_100
c_func
(paren
r_void
)paren
(brace
r_return
op_star
id|lasat_int_status
op_amp
op_star
id|lasat_int_mask
suffix:semicolon
)brace
DECL|function|get_int_status_200
r_static
r_int
r_int
id|get_int_status_200
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|int_status
suffix:semicolon
id|int_status
op_assign
op_star
id|lasat_int_status
suffix:semicolon
id|int_status
op_and_assign
(paren
id|int_status
op_rshift
id|LASATINT_MASK_SHIFT_200
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_return
id|int_status
suffix:semicolon
)brace
DECL|function|lasat_hw0_irqdispatch
r_void
id|lasat_hw0_irqdispatch
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
id|get_int_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if int_status == 0, then the interrupt has already been cleared */
r_if
c_cond
(paren
id|int_status
)paren
(brace
id|irq
op_assign
id|ls1bit32
c_func
(paren
id|int_status
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
r_switch
c_cond
(paren
id|mips_machtype
)paren
(brace
r_case
id|MACH_LASAT_100
suffix:colon
id|lasat_int_status
op_assign
(paren
r_void
op_star
)paren
id|LASAT_INT_STATUS_REG_100
suffix:semicolon
id|lasat_int_mask
op_assign
(paren
r_void
op_star
)paren
id|LASAT_INT_MASK_REG_100
suffix:semicolon
id|lasat_int_mask_shift
op_assign
id|LASATINT_MASK_SHIFT_100
suffix:semicolon
id|get_int_status
op_assign
id|get_int_status_100
suffix:semicolon
op_star
id|lasat_int_mask
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_LASAT_200
suffix:colon
id|lasat_int_status
op_assign
(paren
r_void
op_star
)paren
id|LASAT_INT_STATUS_REG_200
suffix:semicolon
id|lasat_int_mask
op_assign
(paren
r_void
op_star
)paren
id|LASAT_INT_MASK_REG_200
suffix:semicolon
id|lasat_int_mask_shift
op_assign
id|LASATINT_MASK_SHIFT_200
suffix:semicolon
id|get_int_status
op_assign
id|get_int_status_200
suffix:semicolon
op_star
id|lasat_int_mask
op_and_assign
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;arch_init_irq: mips_machtype incorrect&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Now safe to set the exception vector. */
id|set_except_vector
c_func
(paren
l_int|0
comma
id|lasatIRQ
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|LASATINT_END
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
id|lasat_irq_type
suffix:semicolon
)brace
)brace
eof
