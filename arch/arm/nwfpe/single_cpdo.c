multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.COM, 1998,1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &quot;fpa11.h&quot;
macro_line|#include &quot;softfloat.h&quot;
macro_line|#include &quot;fpopcode.h&quot;
id|float32
id|float32_exp
c_func
(paren
id|float32
id|Fm
)paren
suffix:semicolon
id|float32
id|float32_ln
c_func
(paren
id|float32
id|Fm
)paren
suffix:semicolon
id|float32
id|float32_sin
c_func
(paren
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_cos
c_func
(paren
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_arcsin
c_func
(paren
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_arctan
c_func
(paren
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_log
c_func
(paren
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_tan
c_func
(paren
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_arccos
c_func
(paren
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_pow
c_func
(paren
id|float32
id|rFn
comma
id|float32
id|rFm
)paren
suffix:semicolon
id|float32
id|float32_pol
c_func
(paren
id|float32
id|rFn
comma
id|float32
id|rFm
)paren
suffix:semicolon
DECL|function|float32_rsf
r_static
id|float32
id|float32_rsf
c_func
(paren
id|float32
id|rFn
comma
id|float32
id|rFm
)paren
(brace
r_return
id|float32_sub
c_func
(paren
id|rFm
comma
id|rFn
)paren
suffix:semicolon
)brace
DECL|function|float32_rdv
r_static
id|float32
id|float32_rdv
c_func
(paren
id|float32
id|rFn
comma
id|float32
id|rFm
)paren
(brace
r_return
id|float32_div
c_func
(paren
id|rFm
comma
id|rFn
)paren
suffix:semicolon
)brace
DECL|variable|dyadic_single
r_static
id|float32
(paren
op_star
r_const
id|dyadic_single
(braket
l_int|16
)braket
)paren
(paren
id|float32
id|rFn
comma
id|float32
id|rFm
)paren
op_assign
(brace
(braket
id|ADF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_add
comma
(braket
id|MUF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_mul
comma
(braket
id|SUF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_sub
comma
(braket
id|RSF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_rsf
comma
(braket
id|DVF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_div
comma
(braket
id|RDF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_rdv
comma
(braket
id|RMF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_rem
comma
(braket
id|FML_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_mul
comma
(braket
id|FDV_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_div
comma
(braket
id|FRD_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_rdv
comma
)brace
suffix:semicolon
DECL|function|float32_mvf
r_static
id|float32
id|float32_mvf
c_func
(paren
id|float32
id|rFm
)paren
(brace
r_return
id|rFm
suffix:semicolon
)brace
DECL|function|float32_mnf
r_static
id|float32
id|float32_mnf
c_func
(paren
id|float32
id|rFm
)paren
(brace
r_return
id|rFm
op_xor
l_int|0x80000000
suffix:semicolon
)brace
DECL|function|float32_abs
r_static
id|float32
id|float32_abs
c_func
(paren
id|float32
id|rFm
)paren
(brace
r_return
id|rFm
op_amp
l_int|0x7fffffff
suffix:semicolon
)brace
DECL|variable|monadic_single
r_static
id|float32
(paren
op_star
r_const
id|monadic_single
(braket
l_int|16
)braket
)paren
(paren
id|float32
id|rFm
)paren
op_assign
(brace
(braket
id|MVF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_mvf
comma
(braket
id|MNF_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_mnf
comma
(braket
id|ABS_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_abs
comma
(braket
id|RND_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_round_to_int
comma
(braket
id|URD_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_round_to_int
comma
(braket
id|SQT_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_sqrt
comma
(braket
id|NRM_CODE
op_rshift
l_int|20
)braket
op_assign
id|float32_mvf
comma
)brace
suffix:semicolon
DECL|function|SingleCPDO
r_int
r_int
id|SingleCPDO
c_func
(paren
r_const
r_int
r_int
id|opcode
comma
id|FPREG
op_star
id|rFd
)paren
(brace
id|FPA11
op_star
id|fpa11
op_assign
id|GET_FPA11
c_func
(paren
)paren
suffix:semicolon
id|float32
id|rFm
suffix:semicolon
r_int
r_int
id|Fm
comma
id|opc
suffix:semicolon
id|Fm
op_assign
id|getFm
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CONSTANT_FM
c_func
(paren
id|opcode
)paren
)paren
(brace
id|rFm
op_assign
id|getSingleConstant
c_func
(paren
id|Fm
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fm
)braket
op_eq
id|typeSingle
)paren
(brace
id|rFm
op_assign
id|fpa11-&gt;fpreg
(braket
id|Fm
)braket
dot
id|fSingle
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|opc
op_assign
id|opcode
op_amp
id|MASK_ARITHMETIC_OPCODE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MONADIC_INSTRUCTION
c_func
(paren
id|opcode
)paren
)paren
(brace
r_int
r_int
id|Fn
op_assign
id|getFn
c_func
(paren
id|opcode
)paren
suffix:semicolon
id|float32
id|rFn
suffix:semicolon
r_if
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fn
)braket
op_eq
id|typeSingle
op_logical_and
id|dyadic_single
(braket
id|opc
op_rshift
l_int|20
)braket
)paren
(brace
id|rFn
op_assign
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fSingle
suffix:semicolon
id|rFd-&gt;fSingle
op_assign
id|dyadic_single
(braket
id|opc
op_rshift
l_int|20
)braket
(paren
id|rFn
comma
id|rFm
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|monadic_single
(braket
id|opc
op_rshift
l_int|20
)braket
)paren
(brace
id|rFd-&gt;fSingle
op_assign
id|monadic_single
(braket
id|opc
op_rshift
l_int|20
)braket
(paren
id|rFm
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
