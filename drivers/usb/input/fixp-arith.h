macro_line|#ifndef _FIXP_ARITH_H
DECL|macro|_FIXP_ARITH_H
mdefine_line|#define _FIXP_ARITH_H
multiline_comment|/*&n; * $$&n; *&n; * Simplistic fixed-point arithmetics.&n; * Hmm, I&squot;m probably duplicating some code :(&n; *&n; * Copyright (c) 2002 Johann Deneux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so by&n; * e-mail - mail your message to &lt;deneux@ifrance.com&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
singleline_comment|// The type representing fixed-point values
DECL|typedef|fixp_t
r_typedef
id|s16
id|fixp_t
suffix:semicolon
DECL|macro|FRAC_N
mdefine_line|#define FRAC_N 8
DECL|macro|FRAC_MASK
mdefine_line|#define FRAC_MASK ((1&lt;&lt;FRAC_N)-1)
singleline_comment|// Not to be used directly. Use fixp_{cos,sin}
DECL|variable|cos_table
r_static
id|fixp_t
id|cos_table
(braket
l_int|45
)braket
op_assign
(brace
l_int|0x0100
comma
l_int|0x00FF
comma
l_int|0x00FF
comma
l_int|0x00FE
comma
l_int|0x00FD
comma
l_int|0x00FC
comma
l_int|0x00FA
comma
l_int|0x00F8
comma
l_int|0x00F6
comma
l_int|0x00F3
comma
l_int|0x00F0
comma
l_int|0x00ED
comma
l_int|0x00E9
comma
l_int|0x00E6
comma
l_int|0x00E2
comma
l_int|0x00DD
comma
l_int|0x00D9
comma
l_int|0x00D4
comma
l_int|0x00CF
comma
l_int|0x00C9
comma
l_int|0x00C4
comma
l_int|0x00BE
comma
l_int|0x00B8
comma
l_int|0x00B1
comma
l_int|0x00AB
comma
l_int|0x00A4
comma
l_int|0x009D
comma
l_int|0x0096
comma
l_int|0x008F
comma
l_int|0x0087
comma
l_int|0x0080
comma
l_int|0x0078
comma
l_int|0x0070
comma
l_int|0x0068
comma
l_int|0x005F
comma
l_int|0x0057
comma
l_int|0x004F
comma
l_int|0x0046
comma
l_int|0x003D
comma
l_int|0x0035
comma
l_int|0x002C
comma
l_int|0x0023
comma
l_int|0x001A
comma
l_int|0x0011
comma
l_int|0x0008
)brace
suffix:semicolon
multiline_comment|/* a: 123 -&gt; 123.0 */
DECL|function|fixp_new
r_static
r_inline
id|fixp_t
id|fixp_new
c_func
(paren
id|s16
id|a
)paren
(brace
r_return
id|a
op_lshift
id|FRAC_N
suffix:semicolon
)brace
multiline_comment|/* a: 0xFFFF -&gt; -1.0&n;      0x8000 -&gt; 1.0&n;      0x0000 -&gt; 0.0&n;*/
DECL|function|fixp_new16
r_static
r_inline
id|fixp_t
id|fixp_new16
c_func
(paren
id|s16
id|a
)paren
(brace
r_return
(paren
(paren
id|s32
)paren
id|a
)paren
op_rshift
(paren
l_int|16
op_minus
id|FRAC_N
)paren
suffix:semicolon
)brace
DECL|function|fixp_cos
r_static
r_inline
id|fixp_t
id|fixp_cos
c_func
(paren
r_int
r_int
id|degrees
)paren
(brace
r_int
id|quadrant
op_assign
(paren
id|degrees
op_div
l_int|90
)paren
op_amp
l_int|3
suffix:semicolon
r_int
r_int
id|i
op_assign
id|degrees
op_mod
l_int|90
suffix:semicolon
r_if
c_cond
(paren
id|quadrant
op_eq
l_int|1
op_logical_or
id|quadrant
op_eq
l_int|3
)paren
(brace
id|i
op_assign
l_int|89
op_minus
id|i
suffix:semicolon
)brace
id|i
op_rshift_assign
l_int|1
suffix:semicolon
r_return
(paren
id|quadrant
op_eq
l_int|1
op_logical_or
id|quadrant
op_eq
l_int|2
)paren
ques
c_cond
op_minus
id|cos_table
(braket
id|i
)braket
suffix:colon
id|cos_table
(braket
id|i
)braket
suffix:semicolon
)brace
DECL|function|fixp_sin
r_static
r_inline
id|fixp_t
id|fixp_sin
c_func
(paren
r_int
r_int
id|degrees
)paren
(brace
r_return
op_minus
id|fixp_cos
c_func
(paren
id|degrees
op_plus
l_int|90
)paren
suffix:semicolon
)brace
DECL|function|fixp_mult
r_static
r_inline
id|fixp_t
id|fixp_mult
c_func
(paren
id|fixp_t
id|a
comma
id|fixp_t
id|b
)paren
(brace
r_return
(paren
(paren
id|s32
)paren
(paren
id|a
op_star
id|b
)paren
)paren
op_rshift
id|FRAC_N
suffix:semicolon
)brace
macro_line|#endif
eof
