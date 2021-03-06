multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.COM, 1998,1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &quot;fpa11.h&quot;
macro_line|#include &quot;softfloat.h&quot;
macro_line|#include &quot;fpopcode.h&quot;
id|floatx80
id|floatx80_exp
c_func
(paren
id|floatx80
id|Fm
)paren
suffix:semicolon
id|floatx80
id|floatx80_ln
c_func
(paren
id|floatx80
id|Fm
)paren
suffix:semicolon
id|floatx80
id|floatx80_sin
c_func
(paren
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_cos
c_func
(paren
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_arcsin
c_func
(paren
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_arctan
c_func
(paren
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_log
c_func
(paren
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_tan
c_func
(paren
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_arccos
c_func
(paren
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_pow
c_func
(paren
id|floatx80
id|rFn
comma
id|floatx80
id|rFm
)paren
suffix:semicolon
id|floatx80
id|floatx80_pol
c_func
(paren
id|floatx80
id|rFn
comma
id|floatx80
id|rFm
)paren
suffix:semicolon
DECL|function|floatx80_rsf
r_static
id|floatx80
id|floatx80_rsf
c_func
(paren
id|floatx80
id|rFn
comma
id|floatx80
id|rFm
)paren
(brace
r_return
id|floatx80_sub
c_func
(paren
id|rFm
comma
id|rFn
)paren
suffix:semicolon
)brace
DECL|function|floatx80_rdv
r_static
id|floatx80
id|floatx80_rdv
c_func
(paren
id|floatx80
id|rFn
comma
id|floatx80
id|rFm
)paren
(brace
r_return
id|floatx80_div
c_func
(paren
id|rFm
comma
id|rFn
)paren
suffix:semicolon
)brace
DECL|variable|dyadic_extended
r_static
id|floatx80
(paren
op_star
r_const
id|dyadic_extended
(braket
l_int|16
)braket
)paren
(paren
id|floatx80
id|rFn
comma
id|floatx80
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
id|floatx80_add
comma
(braket
id|MUF_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_mul
comma
(braket
id|SUF_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_sub
comma
(braket
id|RSF_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_rsf
comma
(braket
id|DVF_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_div
comma
(braket
id|RDF_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_rdv
comma
(braket
id|RMF_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_rem
comma
multiline_comment|/* strictly, these opcodes should not be implemented */
(braket
id|FML_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_mul
comma
(braket
id|FDV_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_div
comma
(braket
id|FRD_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_rdv
comma
)brace
suffix:semicolon
DECL|function|floatx80_mvf
r_static
id|floatx80
id|floatx80_mvf
c_func
(paren
id|floatx80
id|rFm
)paren
(brace
r_return
id|rFm
suffix:semicolon
)brace
DECL|function|floatx80_mnf
r_static
id|floatx80
id|floatx80_mnf
c_func
(paren
id|floatx80
id|rFm
)paren
(brace
id|rFm.high
op_xor_assign
l_int|0x8000
suffix:semicolon
r_return
id|rFm
suffix:semicolon
)brace
DECL|function|floatx80_abs
r_static
id|floatx80
id|floatx80_abs
c_func
(paren
id|floatx80
id|rFm
)paren
(brace
id|rFm.high
op_and_assign
l_int|0x7fff
suffix:semicolon
r_return
id|rFm
suffix:semicolon
)brace
DECL|variable|monadic_extended
r_static
id|floatx80
(paren
op_star
r_const
id|monadic_extended
(braket
l_int|16
)braket
)paren
(paren
id|floatx80
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
id|floatx80_mvf
comma
(braket
id|MNF_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_mnf
comma
(braket
id|ABS_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_abs
comma
(braket
id|RND_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_round_to_int
comma
(braket
id|URD_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_round_to_int
comma
(braket
id|SQT_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_sqrt
comma
(braket
id|NRM_CODE
op_rshift
l_int|20
)braket
op_assign
id|floatx80_mvf
comma
)brace
suffix:semicolon
DECL|function|ExtendedCPDO
r_int
r_int
id|ExtendedCPDO
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
id|floatx80
id|rFm
suffix:semicolon
r_int
r_int
id|Fm
comma
id|opc_mask_shift
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
id|getExtendedConstant
c_func
(paren
id|Fm
)paren
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fm
)braket
)paren
(brace
r_case
id|typeSingle
suffix:colon
id|rFm
op_assign
id|float32_to_floatx80
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fm
)braket
dot
id|fSingle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeDouble
suffix:colon
id|rFm
op_assign
id|float64_to_floatx80
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fm
)braket
dot
id|fDouble
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeExtended
suffix:colon
id|rFm
op_assign
id|fpa11-&gt;fpreg
(braket
id|Fm
)braket
dot
id|fExtended
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|opc_mask_shift
op_assign
(paren
id|opcode
op_amp
id|MASK_ARITHMETIC_OPCODE
)paren
op_rshift
l_int|20
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
id|floatx80
id|rFn
suffix:semicolon
r_switch
c_cond
(paren
id|fpa11-&gt;fType
(braket
id|Fn
)braket
)paren
(brace
r_case
id|typeSingle
suffix:colon
id|rFn
op_assign
id|float32_to_floatx80
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fSingle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeDouble
suffix:colon
id|rFn
op_assign
id|float64_to_floatx80
c_func
(paren
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fDouble
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|typeExtended
suffix:colon
id|rFn
op_assign
id|fpa11-&gt;fpreg
(braket
id|Fn
)braket
dot
id|fExtended
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dyadic_extended
(braket
id|opc_mask_shift
)braket
)paren
(brace
id|rFd-&gt;fExtended
op_assign
id|dyadic_extended
(braket
id|opc_mask_shift
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
id|monadic_extended
(braket
id|opc_mask_shift
)braket
)paren
(brace
id|rFd-&gt;fExtended
op_assign
id|monadic_extended
(braket
id|opc_mask_shift
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
