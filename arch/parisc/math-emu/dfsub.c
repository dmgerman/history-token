multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; *&n; *  File:&n; *&t;@(#)&t;pa/spmath/dfsub.c&t;&t;$Revision: 1.1 $&n; *&n; *  Purpose:&n; *&t;Double_subtract: subtract two double precision values.&n; *&n; *  External Interfaces:&n; *&t;dbl_fsub(leftptr, rightptr, dstptr, status)&n; *&n; *  Internal Interfaces:&n; *&n; *  Theory:&n; *&t;&lt;&lt;please update with a overview of the operation of this file&gt;&gt;&n; *&n; * END_DESC&n;*/
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;dbl_float.h&quot;
multiline_comment|/*&n; * Double_subtract: subtract two double precision values.&n; */
r_int
DECL|function|dbl_fsub
id|dbl_fsub
c_func
(paren
id|dbl_floating_point
op_star
id|leftptr
comma
id|dbl_floating_point
op_star
id|rightptr
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
id|signless_upper_left
comma
id|signless_upper_right
comma
id|save
suffix:semicolon
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
comma
id|extent
suffix:semicolon
r_register
r_int
r_int
id|resultp1
op_assign
l_int|0
comma
id|resultp2
op_assign
l_int|0
suffix:semicolon
r_register
r_int
id|result_exponent
comma
id|right_exponent
comma
id|diff_exponent
suffix:semicolon
r_register
r_int
id|sign_save
comma
id|jumpsize
suffix:semicolon
r_register
id|boolean
id|inexact
op_assign
id|FALSE
comma
id|underflowtrap
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
multiline_comment|/* A zero &quot;save&quot; helps discover equal operands (for later),  *&n;     * and is used in swapping operands (if needed).             */
id|Dbl_xortointp1
c_func
(paren
id|leftp1
comma
id|rightp1
comma
multiline_comment|/*to*/
id|save
)paren
suffix:semicolon
multiline_comment|/*&n;     * check first operand for NaN&squot;s or infinity&n;     */
r_if
c_cond
(paren
(paren
id|result_exponent
op_assign
id|Dbl_exponent
c_func
(paren
id|leftp1
)paren
)paren
op_eq
id|DBL_INFINITY_EXPONENT
)paren
(brace
r_if
c_cond
(paren
id|Dbl_iszero_mantissa
c_func
(paren
id|leftp1
comma
id|leftp2
)paren
)paren
(brace
r_if
c_cond
(paren
id|Dbl_isnotnan
c_func
(paren
id|rightp1
comma
id|rightp2
)paren
)paren
(brace
r_if
c_cond
(paren
id|Dbl_isinfinity
c_func
(paren
id|rightp1
comma
id|rightp2
)paren
op_logical_and
id|save
op_eq
l_int|0
)paren
(brace
multiline_comment|/* &n;&t;&t;     * invalid since operands are same signed infinity&squot;s&n;&t;&t;     */
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
id|Set_invalidflag
c_func
(paren
)paren
suffix:semicolon
id|Dbl_makequietnan
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
multiline_comment|/*&n;&t; &t; * return infinity&n;&t; &t; */
id|Dbl_copytoptr
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;             * is NaN; signaling or quiet?&n;             */
r_if
c_cond
(paren
id|Dbl_isone_signaling
c_func
(paren
id|leftp1
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
id|leftp1
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t;     * is second operand a signaling NaN? &n;&t;     */
r_else
r_if
c_cond
(paren
id|Dbl_is_signalingnan
c_func
(paren
id|rightp1
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
id|rightp1
)paren
suffix:semicolon
id|Dbl_copytoptr
c_func
(paren
id|rightp1
comma
id|rightp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n; &t;     * return quiet NaN&n; &t;     */
id|Dbl_copytoptr
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
)brace
multiline_comment|/* End left NaN or Infinity processing */
multiline_comment|/*&n;     * check second operand for NaN&squot;s or infinity&n;     */
r_if
c_cond
(paren
id|Dbl_isinfinity_exponent
c_func
(paren
id|rightp1
)paren
)paren
(brace
r_if
c_cond
(paren
id|Dbl_iszero_mantissa
c_func
(paren
id|rightp1
comma
id|rightp2
)paren
)paren
(brace
multiline_comment|/* return infinity */
id|Dbl_invert_sign
c_func
(paren
id|rightp1
)paren
suffix:semicolon
id|Dbl_copytoptr
c_func
(paren
id|rightp1
comma
id|rightp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/*&n;         * is NaN; signaling or quiet?&n;         */
r_if
c_cond
(paren
id|Dbl_isone_signaling
c_func
(paren
id|rightp1
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
id|rightp1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * return quiet NaN&n; &t; */
id|Dbl_copytoptr
c_func
(paren
id|rightp1
comma
id|rightp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/* End right NaN or Infinity processing */
multiline_comment|/* Invariant: Must be dealing with finite numbers */
multiline_comment|/* Compare operands by removing the sign */
id|Dbl_copytoint_exponentmantissap1
c_func
(paren
id|leftp1
comma
id|signless_upper_left
)paren
suffix:semicolon
id|Dbl_copytoint_exponentmantissap1
c_func
(paren
id|rightp1
comma
id|signless_upper_right
)paren
suffix:semicolon
multiline_comment|/* sign difference selects add or sub operation. */
r_if
c_cond
(paren
id|Dbl_ismagnitudeless
c_func
(paren
id|leftp2
comma
id|rightp2
comma
id|signless_upper_left
comma
id|signless_upper_right
)paren
)paren
(brace
multiline_comment|/* Set the left operand to the larger one by XOR swap *&n;&t; *  First finish the first word using &quot;save&quot;          */
id|Dbl_xorfromintp1
c_func
(paren
id|save
comma
id|rightp1
comma
multiline_comment|/*to*/
id|rightp1
)paren
suffix:semicolon
id|Dbl_xorfromintp1
c_func
(paren
id|save
comma
id|leftp1
comma
multiline_comment|/*to*/
id|leftp1
)paren
suffix:semicolon
id|Dbl_swap_lower
c_func
(paren
id|leftp2
comma
id|rightp2
)paren
suffix:semicolon
id|result_exponent
op_assign
id|Dbl_exponent
c_func
(paren
id|leftp1
)paren
suffix:semicolon
id|Dbl_invert_sign
c_func
(paren
id|leftp1
)paren
suffix:semicolon
)brace
multiline_comment|/* Invariant:  left is not smaller than right. */
r_if
c_cond
(paren
(paren
id|right_exponent
op_assign
id|Dbl_exponent
c_func
(paren
id|rightp1
)paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Denormalized operands.  First look for zeroes */
r_if
c_cond
(paren
id|Dbl_iszero_mantissa
c_func
(paren
id|rightp1
comma
id|rightp2
)paren
)paren
(brace
multiline_comment|/* right is zero */
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
)paren
(brace
multiline_comment|/* Both operands are zeros */
id|Dbl_invert_sign
c_func
(paren
id|rightp1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Is_rounding_mode
c_func
(paren
id|ROUNDMINUS
)paren
)paren
(brace
id|Dbl_or_signs
c_func
(paren
id|leftp1
comma
multiline_comment|/*with*/
id|rightp1
)paren
suffix:semicolon
)brace
r_else
(brace
id|Dbl_and_signs
c_func
(paren
id|leftp1
comma
multiline_comment|/*with*/
id|rightp1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Left is not a zero and must be the result.  Trapped&n;&t;&t; * underflows are signaled if left is denormalized.  Result&n;&t;&t; * is always exact. */
r_if
c_cond
(paren
(paren
id|result_exponent
op_eq
l_int|0
)paren
op_logical_and
id|Is_underflowtrap_enabled
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* need to normalize results mantissa */
id|sign_save
op_assign
id|Dbl_signextendedsign
c_func
(paren
id|leftp1
)paren
suffix:semicolon
id|Dbl_leftshiftby1
c_func
(paren
id|leftp1
comma
id|leftp2
)paren
suffix:semicolon
id|Dbl_normalize
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|result_exponent
)paren
suffix:semicolon
id|Dbl_set_sign
c_func
(paren
id|leftp1
comma
multiline_comment|/*using*/
id|sign_save
)paren
suffix:semicolon
id|Dbl_setwrapped_exponent
c_func
(paren
id|leftp1
comma
id|result_exponent
comma
id|unfl
)paren
suffix:semicolon
id|Dbl_copytoptr
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|dstptr
)paren
suffix:semicolon
multiline_comment|/* inexact = FALSE */
r_return
id|UNDERFLOWEXCEPTION
suffix:semicolon
)brace
)brace
id|Dbl_copytoptr
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|dstptr
)paren
suffix:semicolon
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
multiline_comment|/* Neither are zeroes */
id|Dbl_clear_sign
c_func
(paren
id|rightp1
)paren
suffix:semicolon
multiline_comment|/* Exponent is already cleared */
r_if
c_cond
(paren
id|result_exponent
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Both operands are denormalized.  The result must be exact&n;&t;     * and is simply calculated.  A sum could become normalized and a&n;&t;     * difference could cancel to a true zero. */
r_if
c_cond
(paren
(paren
multiline_comment|/*signed*/
r_int
)paren
id|save
op_ge
l_int|0
)paren
(brace
id|Dbl_subtract
c_func
(paren
id|leftp1
comma
id|leftp2
comma
multiline_comment|/*minus*/
id|rightp1
comma
id|rightp2
comma
multiline_comment|/*into*/
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Dbl_iszero_mantissa
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
)paren
(brace
r_if
c_cond
(paren
id|Is_rounding_mode
c_func
(paren
id|ROUNDMINUS
)paren
)paren
(brace
id|Dbl_setone_sign
c_func
(paren
id|resultp1
)paren
suffix:semicolon
)brace
r_else
(brace
id|Dbl_setzero_sign
c_func
(paren
id|resultp1
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
)brace
r_else
(brace
id|Dbl_addition
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|rightp1
comma
id|rightp2
comma
multiline_comment|/*into*/
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Dbl_isone_hidden
c_func
(paren
id|resultp1
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
id|NOEXCEPTION
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|Is_underflowtrap_enabled
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* need to normalize result */
id|sign_save
op_assign
id|Dbl_signextendedsign
c_func
(paren
id|resultp1
)paren
suffix:semicolon
id|Dbl_leftshiftby1
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|Dbl_normalize
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|result_exponent
)paren
suffix:semicolon
id|Dbl_set_sign
c_func
(paren
id|resultp1
comma
multiline_comment|/*using*/
id|sign_save
)paren
suffix:semicolon
id|Dbl_setwrapped_exponent
c_func
(paren
id|resultp1
comma
id|result_exponent
comma
id|unfl
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
multiline_comment|/* inexact = FALSE */
r_return
id|UNDERFLOWEXCEPTION
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
id|right_exponent
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Set exponent to reflect different bias&n;&t;&t;&t;&t; * with denomalized numbers. */
)brace
r_else
(brace
id|Dbl_clear_signexponent_set_hidden
c_func
(paren
id|rightp1
)paren
suffix:semicolon
)brace
id|Dbl_clear_exponent_set_hidden
c_func
(paren
id|leftp1
)paren
suffix:semicolon
id|diff_exponent
op_assign
id|result_exponent
op_minus
id|right_exponent
suffix:semicolon
multiline_comment|/* &n;     * Special case alignment of operands that would force alignment &n;     * beyond the extent of the extension.  A further optimization&n;     * could special case this but only reduces the path length for this&n;     * infrequent case.&n;     */
r_if
c_cond
(paren
id|diff_exponent
OG
id|DBL_THRESHOLD
)paren
(brace
id|diff_exponent
op_assign
id|DBL_THRESHOLD
suffix:semicolon
)brace
multiline_comment|/* Align right operand by shifting to right */
id|Dbl_right_align
c_func
(paren
multiline_comment|/*operand*/
id|rightp1
comma
id|rightp2
comma
multiline_comment|/*shifted by*/
id|diff_exponent
comma
multiline_comment|/*and lower to*/
id|extent
)paren
suffix:semicolon
multiline_comment|/* Treat sum and difference of the operands separately. */
r_if
c_cond
(paren
(paren
multiline_comment|/*signed*/
r_int
)paren
id|save
op_ge
l_int|0
)paren
(brace
multiline_comment|/*&n;&t; * Difference of the two operands.  Their can be no overflow.  A&n;&t; * borrow can occur out of the hidden bit and force a post&n;&t; * normalization phase.&n;&t; */
id|Dbl_subtract_withextension
c_func
(paren
id|leftp1
comma
id|leftp2
comma
multiline_comment|/*minus*/
id|rightp1
comma
id|rightp2
comma
multiline_comment|/*with*/
id|extent
comma
multiline_comment|/*into*/
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Dbl_iszero_hidden
c_func
(paren
id|resultp1
)paren
)paren
(brace
multiline_comment|/* Handle normalization */
multiline_comment|/* A straight foward algorithm would now shift the result&n;&t;     * and extension left until the hidden bit becomes one.  Not&n;&t;     * all of the extension bits need participate in the shift.&n;&t;     * Only the two most significant bits (round and guard) are&n;&t;     * needed.  If only a single shift is needed then the guard&n;&t;     * bit becomes a significant low order bit and the extension&n;&t;     * must participate in the rounding.  If more than a single &n;&t;     * shift is needed, then all bits to the right of the guard &n;&t;     * bit are zeros, and the guard bit may or may not be zero. */
id|sign_save
op_assign
id|Dbl_signextendedsign
c_func
(paren
id|resultp1
)paren
suffix:semicolon
id|Dbl_leftshiftby1_withextent
c_func
(paren
id|resultp1
comma
id|resultp2
comma
id|extent
comma
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
multiline_comment|/* Need to check for a zero result.  The sign and exponent&n;&t;     * fields have already been zeroed.  The more efficient test&n;&t;     * of the full object can be used.&n;&t;     */
r_if
c_cond
(paren
id|Dbl_iszero
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
)paren
multiline_comment|/* Must have been &quot;x-x&quot; or &quot;x+(-x)&quot;. */
(brace
r_if
c_cond
(paren
id|Is_rounding_mode
c_func
(paren
id|ROUNDMINUS
)paren
)paren
(brace
id|Dbl_setone_sign
c_func
(paren
id|resultp1
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
id|result_exponent
op_decrement
suffix:semicolon
multiline_comment|/* Look to see if normalization is finished. */
r_if
c_cond
(paren
id|Dbl_isone_hidden
c_func
(paren
id|resultp1
)paren
)paren
(brace
r_if
c_cond
(paren
id|result_exponent
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Denormalized, exponent should be zero.  Left operand *&n;&t;&t;     * was normalized, so extent (guard, round) was zero    */
r_goto
id|underflow
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* No further normalization is needed. */
id|Dbl_set_sign
c_func
(paren
id|resultp1
comma
multiline_comment|/*using*/
id|sign_save
)paren
suffix:semicolon
id|Ext_leftshiftby1
c_func
(paren
id|extent
)paren
suffix:semicolon
r_goto
id|round
suffix:semicolon
)brace
)brace
multiline_comment|/* Check for denormalized, exponent should be zero.  Left    *&n;&t;     * operand was normalized, so extent (guard, round) was zero */
r_if
c_cond
(paren
op_logical_neg
(paren
id|underflowtrap
op_assign
id|Is_underflowtrap_enabled
c_func
(paren
)paren
)paren
op_logical_and
id|result_exponent
op_eq
l_int|0
)paren
(brace
r_goto
id|underflow
suffix:semicolon
)brace
multiline_comment|/* Shift extension to complete one bit of normalization and&n;&t;     * update exponent. */
id|Ext_leftshiftby1
c_func
(paren
id|extent
)paren
suffix:semicolon
multiline_comment|/* Discover first one bit to determine shift amount.  Use a&n;&t;     * modified binary search.  We have already shifted the result&n;&t;     * one position right and still not found a one so the remainder&n;&t;     * of the extension must be zero and simplifies rounding. */
multiline_comment|/* Scan bytes */
r_while
c_loop
(paren
id|Dbl_iszero_hiddenhigh7mantissa
c_func
(paren
id|resultp1
)paren
)paren
(brace
id|Dbl_leftshiftby8
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result_exponent
op_sub_assign
l_int|8
)paren
op_le
l_int|0
op_logical_and
op_logical_neg
id|underflowtrap
)paren
(brace
r_goto
id|underflow
suffix:semicolon
)brace
)brace
multiline_comment|/* Now narrow it down to the nibble */
r_if
c_cond
(paren
id|Dbl_iszero_hiddenhigh3mantissa
c_func
(paren
id|resultp1
)paren
)paren
(brace
multiline_comment|/* The lower nibble contains the normalizing one */
id|Dbl_leftshiftby4
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result_exponent
op_sub_assign
l_int|4
)paren
op_le
l_int|0
op_logical_and
op_logical_neg
id|underflowtrap
)paren
(brace
r_goto
id|underflow
suffix:semicolon
)brace
)brace
multiline_comment|/* Select case were first bit is set (already normalized)&n;&t;     * otherwise select the proper shift. */
r_if
c_cond
(paren
(paren
id|jumpsize
op_assign
id|Dbl_hiddenhigh3mantissa
c_func
(paren
id|resultp1
)paren
)paren
OG
l_int|7
)paren
(brace
multiline_comment|/* Already normalized */
r_if
c_cond
(paren
id|result_exponent
op_le
l_int|0
)paren
(brace
r_goto
id|underflow
suffix:semicolon
)brace
id|Dbl_set_sign
c_func
(paren
id|resultp1
comma
multiline_comment|/*using*/
id|sign_save
)paren
suffix:semicolon
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
multiline_comment|/*using*/
id|result_exponent
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
id|Dbl_sethigh4bits
c_func
(paren
id|resultp1
comma
multiline_comment|/*using*/
id|sign_save
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|jumpsize
)paren
(brace
r_case
l_int|1
suffix:colon
(brace
id|Dbl_leftshiftby3
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|result_exponent
op_sub_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
(brace
id|Dbl_leftshiftby2
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|result_exponent
op_sub_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_case
l_int|7
suffix:colon
(brace
id|Dbl_leftshiftby1
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|result_exponent
op_sub_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result_exponent
OG
l_int|0
)paren
(brace
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
multiline_comment|/*using*/
id|result_exponent
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
multiline_comment|/* Sign bit is already set */
)brace
multiline_comment|/* Fixup potential underflows */
id|underflow
suffix:colon
r_if
c_cond
(paren
id|Is_underflowtrap_enabled
c_func
(paren
)paren
)paren
(brace
id|Dbl_set_sign
c_func
(paren
id|resultp1
comma
id|sign_save
)paren
suffix:semicolon
id|Dbl_setwrapped_exponent
c_func
(paren
id|resultp1
comma
id|result_exponent
comma
id|unfl
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
multiline_comment|/* inexact = FALSE */
r_return
id|UNDERFLOWEXCEPTION
suffix:semicolon
)brace
multiline_comment|/* &n;&t;     * Since we cannot get an inexact denormalized result,&n;&t;     * we can now return.&n;&t;     */
id|Dbl_fix_overshift
c_func
(paren
id|resultp1
comma
id|resultp2
comma
(paren
l_int|1
op_minus
id|result_exponent
)paren
comma
id|extent
)paren
suffix:semicolon
id|Dbl_clear_signexponent
c_func
(paren
id|resultp1
)paren
suffix:semicolon
id|Dbl_set_sign
c_func
(paren
id|resultp1
comma
id|sign_save
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
multiline_comment|/* end if(hidden...)... */
multiline_comment|/* Fall through and round */
)brace
multiline_comment|/* end if(save &gt;= 0)... */
r_else
(brace
multiline_comment|/* Subtract magnitudes */
id|Dbl_addition
c_func
(paren
id|leftp1
comma
id|leftp2
comma
id|rightp1
comma
id|rightp2
comma
multiline_comment|/*to*/
id|resultp1
comma
id|resultp2
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
(brace
multiline_comment|/* Prenormalization required. */
id|Dbl_rightshiftby1_withextent
c_func
(paren
id|resultp2
comma
id|extent
comma
id|extent
)paren
suffix:semicolon
id|Dbl_arithrightshiftby1
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
id|result_exponent
op_increment
suffix:semicolon
)brace
multiline_comment|/* end if hiddenoverflow... */
)brace
multiline_comment|/* end else ...subtract magnitudes... */
multiline_comment|/* Round the result.  If the extension is all zeros,then the result is&n;     * exact.  Otherwise round in the correct direction.  No underflow is&n;     * possible. If a postnormalization is necessary, then the mantissa is&n;     * all zeros so no shift is needed. */
id|round
suffix:colon
r_if
c_cond
(paren
id|Ext_isnotzero
c_func
(paren
id|extent
)paren
)paren
(brace
id|inexact
op_assign
id|TRUE
suffix:semicolon
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
id|ROUNDNEAREST
suffix:colon
multiline_comment|/* The default. */
r_if
c_cond
(paren
id|Ext_isone_sign
c_func
(paren
id|extent
)paren
)paren
(brace
multiline_comment|/* at least 1/2 ulp */
r_if
c_cond
(paren
id|Ext_isnotzero_lower
c_func
(paren
id|extent
)paren
op_logical_or
id|Dbl_isone_lowmantissap2
c_func
(paren
id|resultp2
)paren
)paren
(brace
multiline_comment|/* either exactly half way and odd or more than 1/2ulp */
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
r_break
suffix:semicolon
r_case
id|ROUNDPLUS
suffix:colon
r_if
c_cond
(paren
id|Dbl_iszero_sign
c_func
(paren
id|resultp1
)paren
)paren
(brace
multiline_comment|/* Round up positive results */
id|Dbl_increment
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
)brace
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
id|resultp1
)paren
)paren
(brace
multiline_comment|/* Round down negative results */
id|Dbl_increment
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
)brace
r_case
id|ROUNDZERO
suffix:colon
suffix:semicolon
multiline_comment|/* truncate is simple */
)brace
multiline_comment|/* end switch... */
r_if
c_cond
(paren
id|Dbl_isone_hiddenoverflow
c_func
(paren
id|resultp1
)paren
)paren
(brace
id|result_exponent
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result_exponent
op_eq
id|DBL_INFINITY_EXPONENT
)paren
(brace
multiline_comment|/* Overflow */
r_if
c_cond
(paren
id|Is_overflowtrap_enabled
c_func
(paren
)paren
)paren
(brace
id|Dbl_setwrapped_exponent
c_func
(paren
id|resultp1
comma
id|result_exponent
comma
id|ovfl
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
r_if
c_cond
(paren
id|inexact
)paren
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
r_return
id|OVERFLOWEXCEPTION
op_or
id|INEXACTEXCEPTION
suffix:semicolon
r_else
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
r_return
id|OVERFLOWEXCEPTION
suffix:semicolon
)brace
r_else
(brace
id|inexact
op_assign
id|TRUE
suffix:semicolon
id|Set_overflowflag
c_func
(paren
)paren
suffix:semicolon
id|Dbl_setoverflow
c_func
(paren
id|resultp1
comma
id|resultp2
)paren
suffix:semicolon
)brace
)brace
r_else
id|Dbl_set_exponent
c_func
(paren
id|resultp1
comma
id|result_exponent
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
r_if
c_cond
(paren
id|inexact
)paren
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
(brace
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
r_return
id|NOEXCEPTION
suffix:semicolon
)brace
eof
