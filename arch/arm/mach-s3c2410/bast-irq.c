multiline_comment|/* linux/arch/arm/mach-s3c2410/bast-irq.c&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; *   Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * http://www.simtec.co.uk/products/EB2410ITX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Modifications:&n; *     08-Jan-2003 BJD  Moved from central IRQ code&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware/s3c2410/irq.h&gt;
macro_line|#if 0
macro_line|#include &lt;asm/debug-ll.h&gt;
macro_line|#endif
DECL|macro|irqdbf
mdefine_line|#define irqdbf(x...)
DECL|macro|irqdbf2
mdefine_line|#define irqdbf2(x...)
multiline_comment|/* handle PC104 ISA interrupts from the system CPLD */
multiline_comment|/* table of ISA irq nos to the relevant mask... zero means&n; * the irq is not implemented&n;*/
DECL|variable|bast_pc104_irqmasks
r_static
r_int
r_char
id|bast_pc104_irqmasks
(braket
)braket
op_assign
(brace
l_int|0
comma
multiline_comment|/* 0 */
l_int|0
comma
multiline_comment|/* 1 */
l_int|0
comma
multiline_comment|/* 2 */
l_int|1
comma
multiline_comment|/* 3 */
l_int|0
comma
multiline_comment|/* 4 */
l_int|2
comma
multiline_comment|/* 5 */
l_int|0
comma
multiline_comment|/* 6 */
l_int|4
comma
multiline_comment|/* 7 */
l_int|0
comma
multiline_comment|/* 8 */
l_int|0
comma
multiline_comment|/* 9 */
l_int|8
comma
multiline_comment|/* 10 */
l_int|0
comma
multiline_comment|/* 11 */
l_int|0
comma
multiline_comment|/* 12 */
l_int|0
comma
multiline_comment|/* 13 */
l_int|0
comma
multiline_comment|/* 14 */
l_int|0
comma
multiline_comment|/* 15 */
)brace
suffix:semicolon
DECL|variable|bast_pc104_irqs
r_static
r_int
r_char
id|bast_pc104_irqs
(braket
)braket
op_assign
(brace
l_int|3
comma
l_int|5
comma
l_int|7
comma
l_int|10
)brace
suffix:semicolon
r_static
r_void
DECL|function|bast_pc104_mask
id|bast_pc104_mask
c_func
(paren
r_int
r_int
id|irqno
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|temp
op_assign
id|__raw_readb
c_func
(paren
id|BAST_VA_PC104_IRQMASK
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
id|bast_pc104_irqmasks
(braket
id|irqno
)braket
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|temp
comma
id|BAST_VA_PC104_IRQMASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_eq
l_int|0
)paren
id|bast_extint_mask
c_func
(paren
id|IRQ_ISA
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|bast_pc104_ack
id|bast_pc104_ack
c_func
(paren
r_int
r_int
id|irqno
)paren
(brace
id|bast_extint_ack
c_func
(paren
id|IRQ_ISA
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|bast_pc104_unmask
id|bast_pc104_unmask
c_func
(paren
r_int
r_int
id|irqno
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|temp
op_assign
id|__raw_readb
c_func
(paren
id|BAST_VA_PC104_IRQMASK
)paren
suffix:semicolon
id|temp
op_or_assign
id|bast_pc104_irqmasks
(braket
id|irqno
)braket
suffix:semicolon
id|__raw_writeb
c_func
(paren
id|temp
comma
id|BAST_VA_PC104_IRQMASK
)paren
suffix:semicolon
id|bast_extint_unmask
c_func
(paren
id|IRQ_ISA
)paren
suffix:semicolon
)brace
r_static
r_struct
id|bast_pc104_chip
op_assign
(brace
dot
id|mask
op_assign
id|bast_pc104_mask
comma
dot
id|unmask
op_assign
id|bast_pc104_unmask
comma
dot
id|ack
op_assign
id|bast_pc104_ack
)brace
suffix:semicolon
r_static
r_void
DECL|function|bast_irq_pc104_demux
id|bast_irq_pc104_demux
c_func
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
id|stat
suffix:semicolon
r_int
r_int
id|irqno
suffix:semicolon
r_int
id|i
suffix:semicolon
id|stat
op_assign
id|__raw_readb
c_func
(paren
id|BAST_VA_PC104_IRQREQ
)paren
op_amp
l_int|0xf
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
l_int|4
op_logical_and
id|stat
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|stat
op_amp
l_int|1
)paren
(brace
id|irqno
op_assign
id|bast_pc104_irqs
(braket
id|i
)braket
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irqno
suffix:semicolon
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irqno
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
id|stat
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
eof
