multiline_comment|/*&n; *  giu.c, General-purpose I/O Unit Interrupt routines for NEC VR4100 series.&n; *&n; *  Copyright (C) 2002 MontaVista Software Inc.&n; *    Author: Yoichi Yuasa &lt;yyuasa@mvista.com or source@mvista.com&gt;&n; *  Copyright (C) 2003-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Changes:&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - New creation, NEC VR4111, VR4121, VR4122 and VR4131 are supported.&n; *&n; *  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *  - Added support for NEC VR4133.&n; *  - Removed board_irq_init.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
DECL|macro|GIUIOSELL_TYPE1
mdefine_line|#define GIUIOSELL_TYPE1&t;KSEG1ADDR(0x0b000100)
DECL|macro|GIUIOSELL_TYPE2
mdefine_line|#define GIUIOSELL_TYPE2&t;KSEG1ADDR(0x0f000140)
DECL|macro|GIUIOSELL
mdefine_line|#define GIUIOSELL&t;0x00
DECL|macro|GIUIOSELH
mdefine_line|#define GIUIOSELH&t;0x02
DECL|macro|GIUINTSTATL
mdefine_line|#define GIUINTSTATL&t;0x08
DECL|macro|GIUINTSTATH
mdefine_line|#define GIUINTSTATH&t;0x0a
DECL|macro|GIUINTENL
mdefine_line|#define GIUINTENL&t;0x0c
DECL|macro|GIUINTENH
mdefine_line|#define GIUINTENH&t;0x0e
DECL|macro|GIUINTTYPL
mdefine_line|#define GIUINTTYPL&t;0x10
DECL|macro|GIUINTTYPH
mdefine_line|#define GIUINTTYPH&t;0x12
DECL|macro|GIUINTALSELL
mdefine_line|#define GIUINTALSELL&t;0x14
DECL|macro|GIUINTALSELH
mdefine_line|#define GIUINTALSELH&t;0x16
DECL|macro|GIUINTHTSELL
mdefine_line|#define GIUINTHTSELL&t;0x18
DECL|macro|GIUINTHTSELH
mdefine_line|#define GIUINTHTSELH&t;0x1a
DECL|macro|GIUFEDGEINHL
mdefine_line|#define GIUFEDGEINHL&t;0x20
DECL|macro|GIUFEDGEINHH
mdefine_line|#define GIUFEDGEINHH&t;0x22
DECL|macro|GIUREDGEINHL
mdefine_line|#define GIUREDGEINHL&t;0x24
DECL|macro|GIUREDGEINHH
mdefine_line|#define GIUREDGEINHH&t;0x26
DECL|variable|giu_base
r_static
r_uint32
id|giu_base
suffix:semicolon
DECL|macro|read_giuint
mdefine_line|#define read_giuint(offset)&t;&t;readw(giu_base + (offset))
DECL|macro|write_giuint
mdefine_line|#define write_giuint(val, offset)&t;writew((val), giu_base + (offset))
DECL|function|set_giuint
r_static
r_inline
r_uint16
id|set_giuint
c_func
(paren
r_uint8
id|offset
comma
r_uint16
id|set
)paren
(brace
r_uint16
id|res
suffix:semicolon
id|res
op_assign
id|read_giuint
c_func
(paren
id|offset
)paren
suffix:semicolon
id|res
op_or_assign
id|set
suffix:semicolon
id|write_giuint
c_func
(paren
id|res
comma
id|offset
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|clear_giuint
r_static
r_inline
r_uint16
id|clear_giuint
c_func
(paren
r_uint8
id|offset
comma
r_uint16
id|clear
)paren
(brace
r_uint16
id|res
suffix:semicolon
id|res
op_assign
id|read_giuint
c_func
(paren
id|offset
)paren
suffix:semicolon
id|res
op_and_assign
op_complement
id|clear
suffix:semicolon
id|write_giuint
c_func
(paren
id|res
comma
id|offset
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|vr41xx_enable_giuint
r_void
id|vr41xx_enable_giuint
c_func
(paren
r_int
id|pin
)paren
(brace
r_if
c_cond
(paren
id|pin
OL
l_int|16
)paren
id|set_giuint
c_func
(paren
id|GIUINTENL
comma
(paren
r_uint16
)paren
l_int|1
op_lshift
id|pin
)paren
suffix:semicolon
r_else
id|set_giuint
c_func
(paren
id|GIUINTENH
comma
(paren
r_uint16
)paren
l_int|1
op_lshift
(paren
id|pin
op_minus
l_int|16
)paren
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_disable_giuint
r_void
id|vr41xx_disable_giuint
c_func
(paren
r_int
id|pin
)paren
(brace
r_if
c_cond
(paren
id|pin
OL
l_int|16
)paren
id|clear_giuint
c_func
(paren
id|GIUINTENL
comma
(paren
r_uint16
)paren
l_int|1
op_lshift
id|pin
)paren
suffix:semicolon
r_else
id|clear_giuint
c_func
(paren
id|GIUINTENH
comma
(paren
r_uint16
)paren
l_int|1
op_lshift
(paren
id|pin
op_minus
l_int|16
)paren
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_clear_giuint
r_void
id|vr41xx_clear_giuint
c_func
(paren
r_int
id|pin
)paren
(brace
r_if
c_cond
(paren
id|pin
OL
l_int|16
)paren
id|write_giuint
c_func
(paren
(paren
r_uint16
)paren
l_int|1
op_lshift
id|pin
comma
id|GIUINTSTATL
)paren
suffix:semicolon
r_else
id|write_giuint
c_func
(paren
(paren
r_uint16
)paren
l_int|1
op_lshift
(paren
id|pin
op_minus
l_int|16
)paren
comma
id|GIUINTSTATH
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_set_irq_trigger
r_void
id|vr41xx_set_irq_trigger
c_func
(paren
r_int
id|pin
comma
r_int
id|trigger
comma
r_int
id|hold
)paren
(brace
r_uint16
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|pin
OL
l_int|16
)paren
(brace
id|mask
op_assign
(paren
r_uint16
)paren
l_int|1
op_lshift
id|pin
suffix:semicolon
r_if
c_cond
(paren
id|trigger
op_ne
id|TRIGGER_LEVEL
)paren
(brace
id|set_giuint
c_func
(paren
id|GIUINTTYPL
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hold
op_eq
id|SIGNAL_HOLD
)paren
id|set_giuint
c_func
(paren
id|GIUINTHTSELL
comma
id|mask
)paren
suffix:semicolon
r_else
id|clear_giuint
c_func
(paren
id|GIUINTHTSELL
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_VR4133
)paren
(brace
r_switch
c_cond
(paren
id|trigger
)paren
(brace
r_case
id|TRIGGER_EDGE_FALLING
suffix:colon
id|set_giuint
c_func
(paren
id|GIUFEDGEINHL
comma
id|mask
)paren
suffix:semicolon
id|clear_giuint
c_func
(paren
id|GIUREDGEINHL
comma
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRIGGER_EDGE_RISING
suffix:colon
id|clear_giuint
c_func
(paren
id|GIUFEDGEINHL
comma
id|mask
)paren
suffix:semicolon
id|set_giuint
c_func
(paren
id|GIUREDGEINHL
comma
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|set_giuint
c_func
(paren
id|GIUFEDGEINHL
comma
id|mask
)paren
suffix:semicolon
id|set_giuint
c_func
(paren
id|GIUREDGEINHL
comma
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|clear_giuint
c_func
(paren
id|GIUINTTYPL
comma
id|mask
)paren
suffix:semicolon
id|clear_giuint
c_func
(paren
id|GIUINTHTSELL
comma
id|mask
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|mask
op_assign
(paren
r_uint16
)paren
l_int|1
op_lshift
(paren
id|pin
op_minus
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trigger
op_ne
id|TRIGGER_LEVEL
)paren
(brace
id|set_giuint
c_func
(paren
id|GIUINTTYPH
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hold
op_eq
id|SIGNAL_HOLD
)paren
id|set_giuint
c_func
(paren
id|GIUINTHTSELH
comma
id|mask
)paren
suffix:semicolon
r_else
id|clear_giuint
c_func
(paren
id|GIUINTHTSELH
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_VR4133
)paren
(brace
r_switch
c_cond
(paren
id|trigger
)paren
(brace
r_case
id|TRIGGER_EDGE_FALLING
suffix:colon
id|set_giuint
c_func
(paren
id|GIUFEDGEINHH
comma
id|mask
)paren
suffix:semicolon
id|clear_giuint
c_func
(paren
id|GIUREDGEINHH
comma
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRIGGER_EDGE_RISING
suffix:colon
id|clear_giuint
c_func
(paren
id|GIUFEDGEINHH
comma
id|mask
)paren
suffix:semicolon
id|set_giuint
c_func
(paren
id|GIUREDGEINHH
comma
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|set_giuint
c_func
(paren
id|GIUFEDGEINHH
comma
id|mask
)paren
suffix:semicolon
id|set_giuint
c_func
(paren
id|GIUREDGEINHH
comma
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|clear_giuint
c_func
(paren
id|GIUINTTYPH
comma
id|mask
)paren
suffix:semicolon
id|clear_giuint
c_func
(paren
id|GIUINTHTSELH
comma
id|mask
)paren
suffix:semicolon
)brace
)brace
id|vr41xx_clear_giuint
c_func
(paren
id|pin
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_set_irq_level
r_void
id|vr41xx_set_irq_level
c_func
(paren
r_int
id|pin
comma
r_int
id|level
)paren
(brace
r_uint16
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|pin
OL
l_int|16
)paren
(brace
id|mask
op_assign
(paren
r_uint16
)paren
l_int|1
op_lshift
id|pin
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|LEVEL_HIGH
)paren
id|set_giuint
c_func
(paren
id|GIUINTALSELL
comma
id|mask
)paren
suffix:semicolon
r_else
id|clear_giuint
c_func
(paren
id|GIUINTALSELL
comma
id|mask
)paren
suffix:semicolon
)brace
r_else
(brace
id|mask
op_assign
(paren
r_uint16
)paren
l_int|1
op_lshift
(paren
id|pin
op_minus
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|LEVEL_HIGH
)paren
id|set_giuint
c_func
(paren
id|GIUINTALSELH
comma
id|mask
)paren
suffix:semicolon
r_else
id|clear_giuint
c_func
(paren
id|GIUINTALSELH
comma
id|mask
)paren
suffix:semicolon
)brace
id|vr41xx_clear_giuint
c_func
(paren
id|pin
)paren
suffix:semicolon
)brace
DECL|macro|GIUINT_NR_IRQS
mdefine_line|#define GIUINT_NR_IRQS&t;&t;32
r_enum
(brace
DECL|enumerator|GIUINT_NO_CASCADE
id|GIUINT_NO_CASCADE
comma
DECL|enumerator|GIUINT_CASCADE
id|GIUINT_CASCADE
)brace
suffix:semicolon
DECL|struct|vr41xx_giuint_cascade
r_struct
id|vr41xx_giuint_cascade
(brace
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
DECL|member|get_irq_number
r_int
(paren
op_star
id|get_irq_number
)paren
(paren
r_int
id|irq
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|giuint_cascade
r_static
r_struct
id|vr41xx_giuint_cascade
id|giuint_cascade
(braket
id|GIUINT_NR_IRQS
)braket
suffix:semicolon
DECL|variable|giu_cascade
r_static
r_struct
id|irqaction
id|giu_cascade
op_assign
(brace
id|no_action
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;cascade&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|no_irq_number
r_static
r_int
id|no_irq_number
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|vr41xx_cascade_irq
r_int
id|vr41xx_cascade_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
(paren
op_star
id|get_irq_number
)paren
(paren
r_int
id|irq
)paren
)paren
(brace
r_int
r_int
id|pin
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|irq
template_param
id|GIU_IRQ
c_func
(paren
l_int|31
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_irq_number
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pin
op_assign
id|GIU_IRQ_TO_PIN
c_func
(paren
id|irq
)paren
suffix:semicolon
id|giuint_cascade
(braket
id|pin
)braket
dot
id|flag
op_assign
id|GIUINT_CASCADE
suffix:semicolon
id|giuint_cascade
(braket
id|pin
)braket
dot
id|get_irq_number
op_assign
id|get_irq_number
suffix:semicolon
id|retval
op_assign
id|setup_irq
c_func
(paren
id|irq
comma
op_amp
id|giu_cascade
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|giuint_cascade
(braket
id|pin
)braket
dot
id|flag
op_assign
id|GIUINT_NO_CASCADE
suffix:semicolon
id|giuint_cascade
(braket
id|pin
)braket
dot
id|get_irq_number
op_assign
id|no_irq_number
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|giuint_do_IRQ
r_int
r_int
id|giuint_do_IRQ
c_func
(paren
r_int
id|pin
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|vr41xx_giuint_cascade
op_star
id|cascade
suffix:semicolon
r_int
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|giuint_irq
comma
id|cascade_irq
suffix:semicolon
id|disable_irq
c_func
(paren
id|GIUINT_CASCADE_IRQ
)paren
suffix:semicolon
id|cascade
op_assign
op_amp
id|giuint_cascade
(braket
id|pin
)braket
suffix:semicolon
id|giuint_irq
op_assign
id|GIU_IRQ
c_func
(paren
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cascade-&gt;flag
op_eq
id|GIUINT_CASCADE
)paren
(brace
id|cascade_irq
op_assign
id|cascade
op_member_access_from_pointer
id|get_irq_number
c_func
(paren
id|giuint_irq
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|giuint_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cascade_irq
OG
l_int|0
)paren
id|retval
op_assign
id|do_IRQ
c_func
(paren
id|cascade_irq
comma
id|regs
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|giuint_irq
)paren
suffix:semicolon
)brace
r_else
id|retval
op_assign
id|do_IRQ
c_func
(paren
id|giuint_irq
comma
id|regs
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|GIUINT_CASCADE_IRQ
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|vr41xx_giuint_init
r_void
id|__init
id|vr41xx_giuint_init
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
id|current_cpu_data.cputype
)paren
(brace
r_case
id|CPU_VR4111
suffix:colon
r_case
id|CPU_VR4121
suffix:colon
id|giu_base
op_assign
id|GIUIOSELL_TYPE1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4122
suffix:colon
r_case
id|CPU_VR4131
suffix:colon
r_case
id|CPU_VR4133
suffix:colon
id|giu_base
op_assign
id|GIUIOSELL_TYPE2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;GIU: Unexpected CPU of NEC VR4100 series&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|GIUINT_NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vr41xx_disable_giuint
c_func
(paren
id|i
)paren
suffix:semicolon
id|giuint_cascade
(braket
id|i
)braket
dot
id|flag
op_assign
id|GIUINT_NO_CASCADE
suffix:semicolon
id|giuint_cascade
(braket
id|i
)braket
dot
id|get_irq_number
op_assign
id|no_irq_number
suffix:semicolon
)brace
r_if
c_cond
(paren
id|setup_irq
c_func
(paren
id|GIUINT_CASCADE_IRQ
comma
op_amp
id|giu_cascade
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;GIUINT: Can not cascade IRQ %d.&bslash;n&quot;
comma
id|GIUINT_CASCADE_IRQ
)paren
suffix:semicolon
)brace
eof
