multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; *&n; *  File:&n; *&t;@(#)&t;pa/spmath/dfcmp.c&t;&t;$Revision: 1.1 $&n; *&n; *  Purpose:&n; *&t;dbl_cmp: compare two values&n; *&n; *  External Interfaces:&n; *&t;dbl_fcmp(leftptr, rightptr, cond, status)&n; *&n; *  Internal Interfaces:&n; *&n; *  Theory:&n; *&t;&lt;&lt;please update with a overview of the operation of this file&gt;&gt;&n; *&n; * END_DESC&n;*/
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;dbl_float.h&quot;
multiline_comment|/*&n; * dbl_cmp: compare two values&n; */
r_int
DECL|function|dbl_fcmp
id|dbl_fcmp
(paren
id|dbl_floating_point
op_star
id|leftptr
comma
id|dbl_floating_point
op_star
id|rightptr
comma
r_int
r_int
id|cond
comma
r_int
r_int
op_star
id|status
)paren
multiline_comment|/* The predicate to be tested */
(brace
r_register
r_int
r_int
id|leftp1
comma
id|leftp2
comma
id|rightp1
comma
id|rightp2
suffix:semicolon
r_register
r_int
id|xorresult
suffix:semicolon
multiline_comment|/* Create local copies of the numbers */
id|Dbl_copyfromptr
c_func
(paren
id|leftptr
comma
id|leftp1
comma
id|leftp2
)paren
suffix:semicolon
id|Dbl_copyfromptr
c_func
(paren
id|rightptr
comma
id|rightp1
comma
id|rightp2
)paren
suffix:semicolon
multiline_comment|/*&n;     * Test for NaN&n;     */
r_if
c_cond
(paren
(paren
id|Dbl_exponent
c_func
(paren
id|leftp1
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
op_logical_or
(paren
id|Dbl_exponent
c_func
(paren
id|rightp1
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
)paren
(brace
multiline_comment|/* Check if a NaN is involved.  Signal an invalid exception when &n;&t; * comparing a signaling NaN or when comparing quiet NaNs and the&n;&t; * low bit of the condition is set */
r_if
c_cond
(paren
(paren
(paren
id|Dbl_exponent
c_func
(paren
id|leftp1
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
op_logical_and
id|Dbl_isnotzero_mantissa
c_func
(paren
id|leftp1
comma
id|leftp2
)paren
op_logical_and
(paren
id|Exception
c_func
(paren
id|cond
)paren
op_logical_or
id|Dbl_isone_signaling
c_func
(paren
id|leftp1
)paren
)paren
)paren
op_logical_or
(paren
(paren
id|Dbl_exponent
c_func
(paren
id|rightp1
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
op_logical_and
id|Dbl_isnotzero_mantissa
c_func
(paren
id|rightp1
comma
id|rightp2
)paren
op_logical_and
(paren
id|Exception
c_func
(paren
id|cond
)paren
op_logical_or
id|Dbl_isone_signaling
c_func
(paren
id|rightp1
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_invalidtrap_enabled
c_func
(paren
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Unordered
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
r_return
id|INVALIDEXCEPTION
suffix:semicolon
)brace
r_else
id|Set_invalidflag
c_func
(paren
)paren
suffix:semicolon
id|Set_status_cbit
c_func
(paren
id|Unordered
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/* All the exceptional conditions are handled, now special case&n;&t;   NaN compares */
r_else
r_if
c_cond
(paren
(paren
(paren
id|Dbl_exponent
c_func
(paren
id|leftp1
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
op_logical_and
id|Dbl_isnotzero_mantissa
c_func
(paren
id|leftp1
comma
id|leftp2
)paren
)paren
op_logical_or
(paren
(paren
id|Dbl_exponent
c_func
(paren
id|rightp1
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
op_logical_and
id|Dbl_isnotzero_mantissa
c_func
(paren
id|rightp1
comma
id|rightp2
)paren
)paren
)paren
(brace
multiline_comment|/* NaNs always compare unordered. */
id|Set_status_cbit
c_func
(paren
id|Unordered
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/* infinities will drop down to the normal compare mechanisms */
)brace
multiline_comment|/* First compare for unequal signs =&gt; less or greater or&n;     * special equal case */
id|Dbl_xortointp1
c_func
(paren
id|leftp1
comma
id|rightp1
comma
id|xorresult
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xorresult
OL
l_int|0
)paren
(brace
multiline_comment|/* left negative =&gt; less, left positive =&gt; greater.&n;         * equal is possible if both operands are zeros. */
r_if
c_cond
(paren
id|Dbl_iszero_exponentmantissa
c_func
(paren
id|leftp1
comma
id|leftp2
)paren
op_logical_and
id|Dbl_iszero_exponentmantissa
c_func
(paren
id|rightp1
comma
id|rightp2
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Equal
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|Dbl_isone_sign
c_func
(paren
id|leftp1
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Lessthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|Set_status_cbit
c_func
(paren
id|Greaterthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Signs are the same.  Treat negative numbers separately&n;     * from the positives because of the reversed sense.  */
r_else
r_if
c_cond
(paren
id|Dbl_isequal
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|rightp1
comma
id|rightp2
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Equal
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|Dbl_iszero_sign
c_func
(paren
id|leftp1
)paren
)paren
(brace
multiline_comment|/* Positive compare */
r_if
c_cond
(paren
id|Dbl_allp1
c_func
(paren
id|leftp1
)paren
OL
id|Dbl_allp1
c_func
(paren
id|rightp1
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Lessthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|Dbl_allp1
c_func
(paren
id|leftp1
)paren
OG
id|Dbl_allp1
c_func
(paren
id|rightp1
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Greaterthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Equal first parts.  Now we must use unsigned compares to&n;&t;     * resolve the two possibilities. */
r_if
c_cond
(paren
id|Dbl_allp2
c_func
(paren
id|leftp2
)paren
OL
id|Dbl_allp2
c_func
(paren
id|rightp2
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Lessthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|Set_status_cbit
c_func
(paren
id|Greaterthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* Negative compare.  Signed or unsigned compares&n;         * both work the same.  That distinction is only&n;         * important when the sign bits differ. */
r_if
c_cond
(paren
id|Dbl_allp1
c_func
(paren
id|leftp1
)paren
OG
id|Dbl_allp1
c_func
(paren
id|rightp1
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Lessthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|Dbl_allp1
c_func
(paren
id|leftp1
)paren
OL
id|Dbl_allp1
c_func
(paren
id|rightp1
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Greaterthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Equal first parts.  Now we must use unsigned compares to&n;&t;     * resolve the two possibilities. */
r_if
c_cond
(paren
id|Dbl_allp2
c_func
(paren
id|leftp2
)paren
OG
id|Dbl_allp2
c_func
(paren
id|rightp2
)paren
)paren
(brace
id|Set_status_cbit
c_func
(paren
id|Lessthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|Set_status_cbit
c_func
(paren
id|Greaterthan
c_func
(paren
id|cond
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
eof
