multiline_comment|/* &n; * linux/arch/sh/board/adx/setup.c&n; *&n; * Copyright (C) 2001 A&amp;D Co., Ltd.&n; *&n; * I/O routine and setup routines for A&amp;D ADX Board&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;linux/module.h&gt;
r_extern
r_void
id|init_adx_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|cf_io_base
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;A&amp;D ADX&quot;
suffix:semicolon
)brace
DECL|function|adx_isa_port2addr
r_int
r_int
id|adx_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
multiline_comment|/* CompactFlash (IDE) */
r_if
c_cond
(paren
(paren
(paren
id|offset
op_ge
l_int|0x1f0
)paren
op_logical_and
(paren
id|offset
op_le
l_int|0x1f7
)paren
)paren
op_logical_or
(paren
id|offset
op_eq
l_int|0x3f6
)paren
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|cf_io_base
op_plus
id|offset
suffix:semicolon
)brace
multiline_comment|/* eth0 */
r_if
c_cond
(paren
(paren
id|offset
op_ge
l_int|0x300
)paren
op_logical_and
(paren
id|offset
op_le
l_int|0x30f
)paren
)paren
(brace
r_return
l_int|0xa5000000
op_plus
id|offset
suffix:semicolon
multiline_comment|/* COMM BOARD (AREA1) */
)brace
r_return
id|offset
op_plus
l_int|0xb0000000
suffix:semicolon
multiline_comment|/* IOBUS (AREA 4)*/
)brace
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_adx
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
l_int|48
comma
dot
id|mv_isa_port2addr
op_assign
id|adx_isa_port2addr
comma
dot
id|mv_init_irq
op_assign
id|init_adx_IRQ
comma
)brace
suffix:semicolon
DECL|function|ALIAS_MV
id|ALIAS_MV
c_func
(paren
id|adx
)paren
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing to see here .. */
r_return
l_int|0
suffix:semicolon
)brace
eof
