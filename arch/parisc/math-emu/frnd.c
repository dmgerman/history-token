multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; *&n; *  Purpose:&n; *&t;Single Floating-point Round to Integer&n; *&t;Double Floating-point Round to Integer&n; *&t;Quad Floating-point Round to Integer (returns unimplemented)&n; *&n; *  External Interfaces:&n; *&t;dbl_frnd(srcptr,nullptr,dstptr,status)&n; *&t;sgl_frnd(srcptr,nullptr,dstptr,status)&n; *&n; * END_DESC&n;*/
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;sgl_float.h&quot;
macro_line|#include &quot;dbl_float.h&quot;
macro_line|#include &quot;cnv_float.h&quot;
multiline_comment|/*&n; *  Single Floating-point Round to Integer&n; */
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|sgl_frnd
id|sgl_frnd
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
suffix:semicolon
r_register
r_int
id|src_exponent
suffix:semicolon
r_register
id|boolean
id|inexact
op_assign
id|FALSE
suffix:semicolon
id|src
op_assign
op_star
id|srcptr
suffix:semicolon
multiline_comment|/*&n;         * check source operand for NaN or infinity&n;         */
r_if
c_cond
(paren
(paren
id|src_exponent
op_assign
id|Sgl_exponent
c_func
(paren
id|src
)paren
)paren
op_eq
id|SGL_INFINITY_EXPONENT
)paren
(brace
multiline_comment|/*&n;                 * is signaling NaN?&n;                 */
r_if
c_cond
(paren
id|Sgl_isone_signaling
c_func
(paren
id|src
)paren
)paren
(brace
multiline_comment|/* trap if INVALIDTRAP enabled */
r_if
c_cond
(paren
id|Is_invalidtrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INVALIDEXCEPTION
suffix:semicolon
multiline_comment|/* make NaN quiet */
id|Set_invalidflag
c_func
(paren
)paren
suffix:semicolon
id|Sgl_set_quiet
c_func
(paren
id|src
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;                 * return quiet NaN or infinity&n;                 */
op_star
id|dstptr
op_assign
id|src
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Need to round?&n;&t; */
r_if
c_cond
(paren
(paren
id|src_exponent
op_sub_assign
id|SGL_BIAS
)paren
op_ge
id|SGL_P
op_minus
l_int|1
)paren
(brace
op_star
id|dstptr
op_assign
id|src
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
id|Sgl_clear_exponent_set_hidden
c_func
(paren
id|src
)paren
suffix:semicolon
id|result
op_assign
id|src
suffix:semicolon
id|Sgl_rightshift
c_func
(paren
id|result
comma
(paren
id|SGL_P
op_minus
l_int|1
)paren
op_minus
(paren
id|src_exponent
)paren
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
id|inexact
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/*  round result  */
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
r_if
c_cond
(paren
id|Sgl_iszero_sign
c_func
(paren
id|src
)paren
)paren
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
r_if
c_cond
(paren
id|Sgl_isone_sign
c_func
(paren
id|src
)paren
)paren
id|Sgl_increment
c_func
(paren
id|result
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
r_if
c_cond
(paren
id|Sgl_isone_roundbit
c_func
(paren
id|src
comma
id|src_exponent
)paren
)paren
r_if
c_cond
(paren
id|Sgl_isone_stickybit
c_func
(paren
id|src
comma
id|src_exponent
)paren
op_logical_or
(paren
id|Sgl_isone_lowmantissa
c_func
(paren
id|result
)paren
)paren
)paren
id|Sgl_increment
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
)brace
id|Sgl_leftshift
c_func
(paren
id|result
comma
(paren
id|SGL_P
op_minus
l_int|1
)paren
op_minus
(paren
id|src_exponent
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Sgl_isone_hiddenoverflow
c_func
(paren
id|result
)paren
)paren
id|Sgl_set_exponent
c_func
(paren
id|result
comma
id|src_exponent
op_plus
(paren
id|SGL_BIAS
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_else
id|Sgl_set_exponent
c_func
(paren
id|result
comma
id|src_exponent
op_plus
id|SGL_BIAS
)paren
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|src
suffix:semicolon
multiline_comment|/* set sign */
id|Sgl_setzero_exponentmantissa
c_func
(paren
id|result
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
id|inexact
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/*  round result  */
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
r_if
c_cond
(paren
id|Sgl_iszero_sign
c_func
(paren
id|src
)paren
)paren
id|Sgl_set_exponent
c_func
(paren
id|result
comma
id|SGL_BIAS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDMINUS
suffix:colon
r_if
c_cond
(paren
id|Sgl_isone_sign
c_func
(paren
id|src
)paren
)paren
id|Sgl_set_exponent
c_func
(paren
id|result
comma
id|SGL_BIAS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
r_if
c_cond
(paren
id|src_exponent
op_eq
op_minus
l_int|1
)paren
r_if
c_cond
(paren
id|Sgl_isnotzero_mantissa
c_func
(paren
id|src
)paren
)paren
id|Sgl_set_exponent
c_func
(paren
id|result
comma
id|SGL_BIAS
)paren
suffix:semicolon
)brace
)brace
)brace
op_star
id|dstptr
op_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|inexact
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
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; *  Double Floating-point Round to Integer&n; */
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|dbl_frnd
id|dbl_frnd
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
r_int
id|srcp1
comma
id|srcp2
comma
id|resultp1
comma
id|resultp2
suffix:semicolon
r_register
r_int
id|src_exponent
suffix:semicolon
r_register
id|boolean
id|inexact
op_assign
id|FALSE
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
multiline_comment|/*&n;         * check source operand for NaN or infinity&n;         */
r_if
c_cond
(paren
(paren
id|src_exponent
op_assign
id|Dbl_exponent
c_func
(paren
id|srcp1
)paren
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
(brace
multiline_comment|/*&n;                 * is signaling NaN?&n;                 */
r_if
c_cond
(paren
id|Dbl_isone_signaling
c_func
(paren
id|srcp1
)paren
)paren
(brace
multiline_comment|/* trap if INVALIDTRAP enabled */
r_if
c_cond
(paren
id|Is_invalidtrap_enabled
c_func
(paren
)paren
)paren
r_return
id|INVALIDEXCEPTION
suffix:semicolon
multiline_comment|/* make NaN quiet */
id|Set_invalidflag
c_func
(paren
)paren
suffix:semicolon
id|Dbl_set_quiet
c_func
(paren
id|srcp1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;                 * return quiet NaN or infinity&n;                 */
id|Dbl_copytoptr
c_func
(paren
id|srcp1
comma
id|srcp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Need to round?&n;&t; */
r_if
c_cond
(paren
(paren
id|src_exponent
op_sub_assign
id|DBL_BIAS
)paren
op_ge
id|DBL_P
op_minus
l_int|1
)paren
(brace
id|Dbl_copytoptr
c_func
(paren
id|srcp1
comma
id|srcp2
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
id|Dbl_clear_exponent_set_hidden
c_func
(paren
id|srcp1
)paren
suffix:semicolon
id|resultp1
op_assign
id|srcp1
suffix:semicolon
id|resultp2
op_assign
id|srcp2
suffix:semicolon
id|Dbl_rightshift
c_func
(paren
id|resultp1
comma
id|resultp2
comma
(paren
id|DBL_P
op_minus
l_int|1
)paren
op_minus
(paren
id|src_exponent
)paren
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
id|inexact
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/*  round result  */
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
r_if
c_cond
(paren
id|Dbl_iszero_sign
c_func
(paren
id|srcp1
)paren
)paren
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
r_if
c_cond
(paren
id|Dbl_isone_sign
c_func
(paren
id|srcp1
)paren
)paren
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
id|ROUNDNEAREST
suffix:colon
r_if
c_cond
(paren
id|Dbl_isone_roundbit
c_func
(paren
id|srcp1
comma
id|srcp2
comma
id|src_exponent
)paren
)paren
r_if
c_cond
(paren
id|Dbl_isone_stickybit
c_func
(paren
id|srcp1
comma
id|srcp2
comma
id|src_exponent
)paren
op_logical_or
(paren
id|Dbl_isone_lowmantissap2
c_func
(paren
id|resultp2
)paren
)paren
)paren
id|Dbl_increment
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
)brace
)brace
id|Dbl_leftshift
c_func
(paren
id|resultp1
comma
id|resultp2
comma
(paren
id|DBL_P
op_minus
l_int|1
)paren
op_minus
(paren
id|src_exponent
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Dbl_isone_hiddenoverflow
c_func
(paren
id|resultp1
)paren
)paren
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
id|src_exponent
op_plus
(paren
id|DBL_BIAS
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_else
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
id|src_exponent
op_plus
id|DBL_BIAS
)paren
suffix:semicolon
)brace
r_else
(brace
id|resultp1
op_assign
id|srcp1
suffix:semicolon
multiline_comment|/* set sign */
id|Dbl_setzero_exponentmantissa
c_func
(paren
id|resultp1
comma
id|resultp2
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
id|inexact
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/*  round result  */
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
r_if
c_cond
(paren
id|Dbl_iszero_sign
c_func
(paren
id|srcp1
)paren
)paren
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
id|DBL_BIAS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDMINUS
suffix:colon
r_if
c_cond
(paren
id|Dbl_isone_sign
c_func
(paren
id|srcp1
)paren
)paren
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
id|DBL_BIAS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ROUNDNEAREST
suffix:colon
r_if
c_cond
(paren
id|src_exponent
op_eq
op_minus
l_int|1
)paren
r_if
c_cond
(paren
id|Dbl_isnotzero_mantissa
c_func
(paren
id|srcp1
comma
id|srcp2
)paren
)paren
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
id|DBL_BIAS
)paren
suffix:semicolon
)brace
)brace
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
r_if
c_cond
(paren
id|inexact
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
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
eof
