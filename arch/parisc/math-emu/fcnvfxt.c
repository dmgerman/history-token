multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; *&n; *  File:&n; *&t;@(#)&t;pa/spmath/fcnvfxt.c&t;&t;$Revision: 1.1 $&n; *&n; *  Purpose:&n; *&t;Single Floating-point to Single Fixed-point /w truncated result&n; *&t;Single Floating-point to Double Fixed-point /w truncated result&n; *&t;Double Floating-point to Single Fixed-point /w truncated result&n; *&t;Double Floating-point to Double Fixed-point /w truncated result&n; *&n; *  External Interfaces:&n; *&t;dbl_to_dbl_fcnvfxt(srcptr,nullptr,dstptr,status)&n; *&t;dbl_to_sgl_fcnvfxt(srcptr,nullptr,dstptr,status)&n; *&t;sgl_to_dbl_fcnvfxt(srcptr,nullptr,dstptr,status)&n; *&t;sgl_to_sgl_fcnvfxt(srcptr,nullptr,dstptr,status)&n; *&n; *  Internal Interfaces:&n; *&n; *  Theory:&n; *&t;&lt;&lt;please update with a overview of the operation of this file&gt;&gt;&n; *&n; * END_DESC&n;*/
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;sgl_float.h&quot;
macro_line|#include &quot;dbl_float.h&quot;
macro_line|#include &quot;cnv_float.h&quot;
multiline_comment|/*&n; *  Convert single floating-point to single fixed-point format&n; *  with truncated result&n; */
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|sgl_to_sgl_fcnvfxt
id|sgl_to_sgl_fcnvfxt
c_func
(paren
id|sgl_floating_point
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
r_int
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
id|temp
suffix:semicolon
r_register
r_int
id|src_exponent
comma
id|result
suffix:semicolon
id|src
op_assign
op_star
id|srcptr
suffix:semicolon
id|src_exponent
op_assign
id|Sgl_exponent
c_func
(paren
id|src
)paren
op_minus
id|SGL_BIAS
suffix:semicolon
multiline_comment|/* &n;&t; * Test for overflow&n;&t; */
r_if
c_cond
(paren
id|src_exponent
OG
id|SGL_FX_MAX_EXP
)paren
(brace
multiline_comment|/* check for MININT */
r_if
c_cond
(paren
(paren
id|src_exponent
OG
id|SGL_FX_MAX_EXP
op_plus
l_int|1
)paren
op_logical_or
id|Sgl_isnotzero_mantissa
c_func
(paren
id|src
)paren
op_logical_or
id|Sgl_iszero_sign
c_func
(paren
id|src
)paren
)paren
(brace
r_if
c_cond
(paren
id|Sgl_iszero_sign
c_func
(paren
id|src
)paren
)paren
id|result
op_assign
l_int|0x7fffffff
suffix:semicolon
r_else
id|result
op_assign
l_int|0x80000000
suffix:semicolon
r_if
c_cond
(paren
id|Is_invalidtrap_enabled
c_func
(paren
)paren
)paren
(brace
r_return
id|INVALIDEXCEPTION
suffix:semicolon
)brace
id|Set_invalidflag
c_func
(paren
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
)brace
multiline_comment|/*&n;&t; * Generate result&n;&t; */
r_if
c_cond
(paren
id|src_exponent
op_ge
l_int|0
)paren
(brace
id|temp
op_assign
id|src
suffix:semicolon
id|Sgl_clear_signexponent_set_hidden
c_func
(paren
id|temp
)paren
suffix:semicolon
id|Int_from_sgl_mantissa
c_func
(paren
id|temp
comma
id|src_exponent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Sgl_isone_sign
c_func
(paren
id|src
)paren
)paren
id|result
op_assign
op_minus
id|Sgl_all
c_func
(paren
id|temp
)paren
suffix:semicolon
r_else
id|result
op_assign
id|Sgl_all
c_func
(paren
id|temp
)paren
suffix:semicolon
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Sgl_isinexact_to_fix
c_func
(paren
id|src
comma
id|src_exponent
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|dstptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Sgl_isnotzero_exponentmantissa
c_func
(paren
id|src
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; *  Single Floating-point to Double Fixed-point &n; */
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|sgl_to_dbl_fcnvfxt
id|sgl_to_dbl_fcnvfxt
c_func
(paren
id|sgl_floating_point
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
id|dbl_integer
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
id|src_exponent
comma
id|resultp1
suffix:semicolon
r_register
r_int
r_int
id|src
comma
id|temp
comma
id|resultp2
suffix:semicolon
id|src
op_assign
op_star
id|srcptr
suffix:semicolon
id|src_exponent
op_assign
id|Sgl_exponent
c_func
(paren
id|src
)paren
op_minus
id|SGL_BIAS
suffix:semicolon
multiline_comment|/* &n;&t; * Test for overflow&n;&t; */
r_if
c_cond
(paren
id|src_exponent
OG
id|DBL_FX_MAX_EXP
)paren
(brace
multiline_comment|/* check for MININT */
r_if
c_cond
(paren
(paren
id|src_exponent
OG
id|DBL_FX_MAX_EXP
op_plus
l_int|1
)paren
op_logical_or
id|Sgl_isnotzero_mantissa
c_func
(paren
id|src
)paren
op_logical_or
id|Sgl_iszero_sign
c_func
(paren
id|src
)paren
)paren
(brace
r_if
c_cond
(paren
id|Sgl_iszero_sign
c_func
(paren
id|src
)paren
)paren
(brace
id|resultp1
op_assign
l_int|0x7fffffff
suffix:semicolon
id|resultp2
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
r_else
(brace
id|resultp1
op_assign
l_int|0x80000000
suffix:semicolon
id|resultp2
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Is_invalidtrap_enabled
c_func
(paren
)paren
)paren
(brace
r_return
id|INVALIDEXCEPTION
suffix:semicolon
)brace
id|Set_invalidflag
c_func
(paren
)paren
suffix:semicolon
id|Dint_copytoptr
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
id|Dint_set_minint
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|Dint_copytoptr
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
multiline_comment|/*&n;&t; * Generate result&n;&t; */
r_if
c_cond
(paren
id|src_exponent
op_ge
l_int|0
)paren
(brace
id|temp
op_assign
id|src
suffix:semicolon
id|Sgl_clear_signexponent_set_hidden
c_func
(paren
id|temp
)paren
suffix:semicolon
id|Dint_from_sgl_mantissa
c_func
(paren
id|temp
comma
id|src_exponent
comma
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Sgl_isone_sign
c_func
(paren
id|src
)paren
)paren
(brace
id|Dint_setone_sign
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
)brace
id|Dint_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Sgl_isinexact_to_fix
c_func
(paren
id|src
comma
id|src_exponent
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|Dint_setzero
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|Dint_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Sgl_isnotzero_exponentmantissa
c_func
(paren
id|src
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; *  Double Floating-point to Single Fixed-point &n; */
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|dbl_to_sgl_fcnvfxt
id|dbl_to_sgl_fcnvfxt
c_func
(paren
id|dbl_floating_point
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
r_int
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
id|srcp1
comma
id|srcp2
comma
id|tempp1
comma
id|tempp2
suffix:semicolon
r_register
r_int
id|src_exponent
comma
id|result
suffix:semicolon
id|Dbl_copyfromptr
c_func
(paren
id|srcptr
comma
id|srcp1
comma
id|srcp2
)paren
suffix:semicolon
id|src_exponent
op_assign
id|Dbl_exponent
c_func
(paren
id|srcp1
)paren
op_minus
id|DBL_BIAS
suffix:semicolon
multiline_comment|/* &n;&t; * Test for overflow&n;&t; */
r_if
c_cond
(paren
id|src_exponent
OG
id|SGL_FX_MAX_EXP
)paren
(brace
multiline_comment|/* check for MININT */
r_if
c_cond
(paren
id|Dbl_isoverflow_to_int
c_func
(paren
id|src_exponent
comma
id|srcp1
comma
id|srcp2
)paren
)paren
(brace
r_if
c_cond
(paren
id|Dbl_iszero_sign
c_func
(paren
id|srcp1
)paren
)paren
id|result
op_assign
l_int|0x7fffffff
suffix:semicolon
r_else
id|result
op_assign
l_int|0x80000000
suffix:semicolon
r_if
c_cond
(paren
id|Is_invalidtrap_enabled
c_func
(paren
)paren
)paren
(brace
r_return
id|INVALIDEXCEPTION
suffix:semicolon
)brace
id|Set_invalidflag
c_func
(paren
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
)brace
multiline_comment|/*&n;&t; * Generate result&n;&t; */
r_if
c_cond
(paren
id|src_exponent
op_ge
l_int|0
)paren
(brace
id|tempp1
op_assign
id|srcp1
suffix:semicolon
id|tempp2
op_assign
id|srcp2
suffix:semicolon
id|Dbl_clear_signexponent_set_hidden
c_func
(paren
id|tempp1
)paren
suffix:semicolon
id|Int_from_dbl_mantissa
c_func
(paren
id|tempp1
comma
id|tempp2
comma
id|src_exponent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Dbl_isone_sign
c_func
(paren
id|srcp1
)paren
op_logical_and
(paren
id|src_exponent
op_le
id|SGL_FX_MAX_EXP
)paren
)paren
id|result
op_assign
op_minus
id|Dbl_allp1
c_func
(paren
id|tempp1
)paren
suffix:semicolon
r_else
id|result
op_assign
id|Dbl_allp1
c_func
(paren
id|tempp1
)paren
suffix:semicolon
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Dbl_isinexact_to_fix
c_func
(paren
id|srcp1
comma
id|srcp2
comma
id|src_exponent
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|dstptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Dbl_isnotzero_exponentmantissa
c_func
(paren
id|srcp1
comma
id|srcp2
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; *  Double Floating-point to Double Fixed-point &n; */
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|dbl_to_dbl_fcnvfxt
id|dbl_to_dbl_fcnvfxt
c_func
(paren
id|dbl_floating_point
op_star
id|srcptr
comma
r_int
r_int
op_star
id|nullptr
comma
id|dbl_integer
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
id|src_exponent
comma
id|resultp1
suffix:semicolon
r_register
r_int
r_int
id|srcp1
comma
id|srcp2
comma
id|tempp1
comma
id|tempp2
comma
id|resultp2
suffix:semicolon
id|Dbl_copyfromptr
c_func
(paren
id|srcptr
comma
id|srcp1
comma
id|srcp2
)paren
suffix:semicolon
id|src_exponent
op_assign
id|Dbl_exponent
c_func
(paren
id|srcp1
)paren
op_minus
id|DBL_BIAS
suffix:semicolon
multiline_comment|/* &n;&t; * Test for overflow&n;&t; */
r_if
c_cond
(paren
id|src_exponent
OG
id|DBL_FX_MAX_EXP
)paren
(brace
multiline_comment|/* check for MININT */
r_if
c_cond
(paren
(paren
id|src_exponent
OG
id|DBL_FX_MAX_EXP
op_plus
l_int|1
)paren
op_logical_or
id|Dbl_isnotzero_mantissa
c_func
(paren
id|srcp1
comma
id|srcp2
)paren
op_logical_or
id|Dbl_iszero_sign
c_func
(paren
id|srcp1
)paren
)paren
(brace
r_if
c_cond
(paren
id|Dbl_iszero_sign
c_func
(paren
id|srcp1
)paren
)paren
(brace
id|resultp1
op_assign
l_int|0x7fffffff
suffix:semicolon
id|resultp2
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
r_else
(brace
id|resultp1
op_assign
l_int|0x80000000
suffix:semicolon
id|resultp2
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Is_invalidtrap_enabled
c_func
(paren
)paren
)paren
(brace
r_return
id|INVALIDEXCEPTION
suffix:semicolon
)brace
id|Set_invalidflag
c_func
(paren
)paren
suffix:semicolon
id|Dint_copytoptr
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
)brace
multiline_comment|/*&n;&t; * Generate result&n;&t; */
r_if
c_cond
(paren
id|src_exponent
op_ge
l_int|0
)paren
(brace
id|tempp1
op_assign
id|srcp1
suffix:semicolon
id|tempp2
op_assign
id|srcp2
suffix:semicolon
id|Dbl_clear_signexponent_set_hidden
c_func
(paren
id|tempp1
)paren
suffix:semicolon
id|Dint_from_dbl_mantissa
c_func
(paren
id|tempp1
comma
id|tempp2
comma
id|src_exponent
comma
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Dbl_isone_sign
c_func
(paren
id|srcp1
)paren
)paren
(brace
id|Dint_setone_sign
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
)brace
id|Dint_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Dbl_isinexact_to_fix
c_func
(paren
id|srcp1
comma
id|srcp2
comma
id|src_exponent
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|Dint_setzero
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|Dint_copytoptr
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|dstptr
)paren
suffix:semicolon
multiline_comment|/* check for inexact */
r_if
c_cond
(paren
id|Dbl_isnotzero_exponentmantissa
c_func
(paren
id|srcp1
comma
id|srcp2
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
eof
