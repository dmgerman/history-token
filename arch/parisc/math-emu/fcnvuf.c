multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; *&n; *  File:&n; *&t;@(#)&t;pa/spmath/fcnvuf.c&t;&t;$Revision: 1.1 $&n; *&n; *  Purpose:&n; *&t;Fixed point to Floating-point Converts&n; *&n; *  External Interfaces:&n; *&t;dbl_to_dbl_fcnvuf(srcptr,nullptr,dstptr,status)&n; *&t;dbl_to_sgl_fcnvuf(srcptr,nullptr,dstptr,status)&n; *&t;sgl_to_dbl_fcnvuf(srcptr,nullptr,dstptr,status)&n; *&t;sgl_to_sgl_fcnvuf(srcptr,nullptr,dstptr,status)&n; *&n; *  Internal Interfaces:&n; *&n; *  Theory:&n; *&t;&lt;&lt;please update with a overview of the operation of this file&gt;&gt;&n; *&n; * END_DESC&n;*/
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;sgl_float.h&quot;
macro_line|#include &quot;dbl_float.h&quot;
macro_line|#include &quot;cnv_float.h&quot;
multiline_comment|/************************************************************************&n; *  Fixed point to Floating-point Converts&t;&t;&t;&t;*&n; ************************************************************************/
multiline_comment|/*&n; *  Convert Single Unsigned Fixed to Single Floating-point format&n; */
r_int
DECL|function|sgl_to_sgl_fcnvuf
id|sgl_to_sgl_fcnvuf
c_func
(paren
r_int
r_int
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
id|sgl_floating_point
op_star
id|dstptr
comma
r_int
r_int
op_star
id|status
)paren
(brace
r_register
r_int
r_int
id|src
comma
id|result
op_assign
l_int|0
suffix:semicolon
r_register
r_int
id|dst_exponent
suffix:semicolon
id|src
op_assign
op_star
id|srcptr
suffix:semicolon
multiline_comment|/* Check for zero */
r_if
c_cond
(paren
id|src
op_eq
l_int|0
)paren
(brace
id|Sgl_setzero
c_func
(paren
id|result
)paren
suffix:semicolon
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Generate exponent and normalized mantissa&n;&t; */
id|dst_exponent
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* initialize for normalization */
multiline_comment|/*&n;&t; * Check word for most significant bit set.  Returns&n;&t; * a value in dst_exponent indicating the bit position,&n;&t; * between -1 and 30.&n;&t; */
id|Find_ms_one_bit
c_func
(paren
id|src
comma
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/*  left justify source, with msb at bit position 0  */
id|src
op_lshift_assign
id|dst_exponent
op_plus
l_int|1
suffix:semicolon
id|Sgl_set_mantissa
c_func
(paren
id|result
comma
id|src
op_rshift
id|SGL_EXP_LENGTH
)paren
suffix:semicolon
id|Sgl_set_exponent
c_func
(paren
id|result
comma
l_int|30
op_plus
id|SGL_BIAS
op_minus
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Suint_isinexact_to_sgl
c_func
(paren
id|src
)paren
)paren
(brace
r_switch
c_cond
(paren
id|Rounding_mode
c_func
(paren
)paren
)paren
(brace
r_case
id|ROUNDPLUS
suffix:colon
id|Sgl_increment
c_func
(paren
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDMINUS
suffix:colon
multiline_comment|/* never negative */
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
id|Sgl_roundnearest_from_suint
c_func
(paren
id|src
comma
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
(brace
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
r_return
id|INEXACTEXCEPTION
suffix:semicolon
)brace
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; *  Single Unsigned Fixed to Double Floating-point &n; */
r_int
DECL|function|sgl_to_dbl_fcnvuf
id|sgl_to_dbl_fcnvuf
c_func
(paren
r_int
r_int
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
id|dbl_floating_point
op_star
id|dstptr
comma
r_int
r_int
op_star
id|status
)paren
(brace
r_register
r_int
id|dst_exponent
suffix:semicolon
r_register
r_int
r_int
id|src
comma
id|resultp1
op_assign
l_int|0
comma
id|resultp2
op_assign
l_int|0
suffix:semicolon
id|src
op_assign
op_star
id|srcptr
suffix:semicolon
multiline_comment|/* Check for zero */
r_if
c_cond
(paren
id|src
op_eq
l_int|0
)paren
(brace
id|Dbl_setzero
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|Dbl_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Generate exponent and normalized mantissa&n;&t; */
id|dst_exponent
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* initialize for normalization */
multiline_comment|/*&n;&t; * Check word for most significant bit set.  Returns&n;&t; * a value in dst_exponent indicating the bit position,&n;&t; * between -1 and 30.&n;&t; */
id|Find_ms_one_bit
c_func
(paren
id|src
comma
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/*  left justify source, with msb at bit position 0  */
id|src
op_lshift_assign
id|dst_exponent
op_plus
l_int|1
suffix:semicolon
id|Dbl_set_mantissap1
c_func
(paren
id|resultp1
comma
id|src
op_rshift
id|DBL_EXP_LENGTH
)paren
suffix:semicolon
id|Dbl_set_mantissap2
c_func
(paren
id|resultp2
comma
id|src
op_lshift
(paren
l_int|32
op_minus
id|DBL_EXP_LENGTH
)paren
)paren
suffix:semicolon
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
(paren
l_int|30
op_plus
id|DBL_BIAS
)paren
op_minus
id|dst_exponent
)paren
suffix:semicolon
id|Dbl_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; *  Double Unsigned Fixed to Single Floating-point &n; */
r_int
DECL|function|dbl_to_sgl_fcnvuf
id|dbl_to_sgl_fcnvuf
c_func
(paren
id|dbl_unsigned
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
id|sgl_floating_point
op_star
id|dstptr
comma
r_int
r_int
op_star
id|status
)paren
(brace
r_int
id|dst_exponent
suffix:semicolon
r_int
r_int
id|srcp1
comma
id|srcp2
comma
id|result
op_assign
l_int|0
suffix:semicolon
id|Duint_copyfromptr
c_func
(paren
id|srcptr
comma
id|srcp1
comma
id|srcp2
)paren
suffix:semicolon
multiline_comment|/* Check for zero */
r_if
c_cond
(paren
id|srcp1
op_eq
l_int|0
op_logical_and
id|srcp2
op_eq
l_int|0
)paren
(brace
id|Sgl_setzero
c_func
(paren
id|result
)paren
suffix:semicolon
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Generate exponent and normalized mantissa&n;&t; */
id|dst_exponent
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* initialize for normalization */
r_if
c_cond
(paren
id|srcp1
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Check word for most significant bit set.  Returns&n;&t;&t; * a value in dst_exponent indicating the bit position,&n;&t;&t; * between -1 and 30.&n;&t;&t; */
id|Find_ms_one_bit
c_func
(paren
id|srcp2
comma
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/*  left justify source, with msb at bit position 0  */
id|srcp1
op_assign
id|srcp2
op_lshift
id|dst_exponent
op_plus
l_int|1
suffix:semicolon
id|srcp2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  since msb set is in second word, need to &n;&t;&t; *  adjust bit position count&n;&t;&t; */
id|dst_exponent
op_add_assign
l_int|32
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Check word for most significant bit set.  Returns&n;&t;&t; * a value in dst_exponent indicating the bit position,&n;&t;&t; * between -1 and 30.&n;&t;&t; *&n;&t;&t; */
id|Find_ms_one_bit
c_func
(paren
id|srcp1
comma
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/*  left justify source, with msb at bit position 0  */
r_if
c_cond
(paren
id|dst_exponent
op_ge
l_int|0
)paren
(brace
id|Variable_shift_double
c_func
(paren
id|srcp1
comma
id|srcp2
comma
(paren
l_int|31
op_minus
id|dst_exponent
)paren
comma
id|srcp1
)paren
suffix:semicolon
id|srcp2
op_lshift_assign
id|dst_exponent
op_plus
l_int|1
suffix:semicolon
)brace
)brace
id|Sgl_set_mantissa
c_func
(paren
id|result
comma
id|srcp1
op_rshift
id|SGL_EXP_LENGTH
)paren
suffix:semicolon
id|Sgl_set_exponent
c_func
(paren
id|result
comma
(paren
l_int|62
op_plus
id|SGL_BIAS
)paren
op_minus
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Duint_isinexact_to_sgl
c_func
(paren
id|srcp1
comma
id|srcp2
)paren
)paren
(brace
r_switch
c_cond
(paren
id|Rounding_mode
c_func
(paren
)paren
)paren
(brace
r_case
id|ROUNDPLUS
suffix:colon
id|Sgl_increment
c_func
(paren
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDMINUS
suffix:colon
multiline_comment|/* never negative */
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
id|Sgl_roundnearest_from_duint
c_func
(paren
id|srcp1
comma
id|srcp2
comma
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
(brace
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
r_return
id|INEXACTEXCEPTION
suffix:semicolon
)brace
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; *  Double Unsigned Fixed to Double Floating-point &n; */
r_int
DECL|function|dbl_to_dbl_fcnvuf
id|dbl_to_dbl_fcnvuf
c_func
(paren
id|dbl_unsigned
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
id|dbl_floating_point
op_star
id|dstptr
comma
r_int
r_int
op_star
id|status
)paren
(brace
r_register
r_int
id|dst_exponent
suffix:semicolon
r_register
r_int
r_int
id|srcp1
comma
id|srcp2
comma
id|resultp1
op_assign
l_int|0
comma
id|resultp2
op_assign
l_int|0
suffix:semicolon
id|Duint_copyfromptr
c_func
(paren
id|srcptr
comma
id|srcp1
comma
id|srcp2
)paren
suffix:semicolon
multiline_comment|/* Check for zero */
r_if
c_cond
(paren
id|srcp1
op_eq
l_int|0
op_logical_and
id|srcp2
op_eq
l_int|0
)paren
(brace
id|Dbl_setzero
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|Dbl_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Generate exponent and normalized mantissa&n;&t; */
id|dst_exponent
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* initialize for normalization */
r_if
c_cond
(paren
id|srcp1
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Check word for most significant bit set.  Returns&n;&t;&t; * a value in dst_exponent indicating the bit position,&n;&t;&t; * between -1 and 30.&n;&t;&t; */
id|Find_ms_one_bit
c_func
(paren
id|srcp2
comma
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/*  left justify source, with msb at bit position 0  */
id|srcp1
op_assign
id|srcp2
op_lshift
id|dst_exponent
op_plus
l_int|1
suffix:semicolon
id|srcp2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  since msb set is in second word, need to &n;&t;&t; *  adjust bit position count&n;&t;&t; */
id|dst_exponent
op_add_assign
l_int|32
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Check word for most significant bit set.  Returns&n;&t;&t; * a value in dst_exponent indicating the bit position,&n;&t;&t; * between -1 and 30.&n;&t;&t; */
id|Find_ms_one_bit
c_func
(paren
id|srcp1
comma
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/*  left justify source, with msb at bit position 0  */
r_if
c_cond
(paren
id|dst_exponent
op_ge
l_int|0
)paren
(brace
id|Variable_shift_double
c_func
(paren
id|srcp1
comma
id|srcp2
comma
(paren
l_int|31
op_minus
id|dst_exponent
)paren
comma
id|srcp1
)paren
suffix:semicolon
id|srcp2
op_lshift_assign
id|dst_exponent
op_plus
l_int|1
suffix:semicolon
)brace
)brace
id|Dbl_set_mantissap1
c_func
(paren
id|resultp1
comma
id|srcp1
op_rshift
id|DBL_EXP_LENGTH
)paren
suffix:semicolon
id|Shiftdouble
c_func
(paren
id|srcp1
comma
id|srcp2
comma
id|DBL_EXP_LENGTH
comma
id|resultp2
)paren
suffix:semicolon
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
(paren
l_int|62
op_plus
id|DBL_BIAS
)paren
op_minus
id|dst_exponent
)paren
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Duint_isinexact_to_dbl
c_func
(paren
id|srcp2
)paren
)paren
(brace
r_switch
c_cond
(paren
id|Rounding_mode
c_func
(paren
)paren
)paren
(brace
r_case
id|ROUNDPLUS
suffix:colon
id|Dbl_increment
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDMINUS
suffix:colon
multiline_comment|/* never negative */
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
id|Dbl_roundnearest_from_duint
c_func
(paren
id|srcp2
comma
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
(brace
id|Dbl_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|INEXACTEXCEPTION
suffix:semicolon
)brace
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
id|Dbl_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
eof
