multiline_comment|/*******************************************************************************&n; *&n; * Module Name: utmath - Integer math support routines&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;utmath&quot;
)paren
multiline_comment|/*&n; * Support for double-precision integer divide.  This code is included here&n; * in order to support kernel environments where the double-precision math&n; * library is not available.&n; */
macro_line|#ifndef ACPI_USE_NATIVE_DIVIDE
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_short_divide&n; *&n; * PARAMETERS:  in_dividend         - Pointer to the dividend&n; *              Divisor             - 32-bit divisor&n; *              out_quotient        - Pointer to where the quotient is returned&n; *              out_remainder       - Pointer to where the remainder is returned&n; *&n; * RETURN:      Status (Checks for divide-by-zero)&n; *&n; * DESCRIPTION: Perform a short (maximum 64 bits divided by 32 bits)&n; *              divide and modulo.  The result is a 64-bit quotient and a&n; *              32-bit remainder.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_short_divide
id|acpi_ut_short_divide
(paren
id|acpi_integer
op_star
id|in_dividend
comma
id|u32
id|divisor
comma
id|acpi_integer
op_star
id|out_quotient
comma
id|u32
op_star
id|out_remainder
)paren
(brace
r_union
id|uint64_overlay
id|dividend
suffix:semicolon
r_union
id|uint64_overlay
id|quotient
suffix:semicolon
id|u32
id|remainder32
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_short_divide&quot;
)paren
suffix:semicolon
id|dividend.full
op_assign
op_star
id|in_dividend
suffix:semicolon
multiline_comment|/* Always check for a zero divisor */
r_if
c_cond
(paren
id|divisor
op_eq
l_int|0
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ut_short_divide: Divide by zero&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_DIVIDE_BY_ZERO
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The quotient is 64 bits, the remainder is always 32 bits,&n;&t; * and is generated by the second divide.&n;&t; */
id|ACPI_DIV_64_BY_32
(paren
l_int|0
comma
id|dividend.part.hi
comma
id|divisor
comma
id|quotient.part.hi
comma
id|remainder32
)paren
suffix:semicolon
id|ACPI_DIV_64_BY_32
(paren
id|remainder32
comma
id|dividend.part.lo
comma
id|divisor
comma
id|quotient.part.lo
comma
id|remainder32
)paren
suffix:semicolon
multiline_comment|/* Return only what was requested */
r_if
c_cond
(paren
id|out_quotient
)paren
(brace
op_star
id|out_quotient
op_assign
id|quotient.full
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out_remainder
)paren
(brace
op_star
id|out_remainder
op_assign
id|remainder32
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_divide&n; *&n; * PARAMETERS:  in_dividend         - Pointer to the dividend&n; *              in_divisor          - Pointer to the divisor&n; *              out_quotient        - Pointer to where the quotient is returned&n; *              out_remainder       - Pointer to where the remainder is returned&n; *&n; * RETURN:      Status (Checks for divide-by-zero)&n; *&n; * DESCRIPTION: Perform a divide and modulo.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_divide
id|acpi_ut_divide
(paren
id|acpi_integer
op_star
id|in_dividend
comma
id|acpi_integer
op_star
id|in_divisor
comma
id|acpi_integer
op_star
id|out_quotient
comma
id|acpi_integer
op_star
id|out_remainder
)paren
(brace
r_union
id|uint64_overlay
id|dividend
suffix:semicolon
r_union
id|uint64_overlay
id|divisor
suffix:semicolon
r_union
id|uint64_overlay
id|quotient
suffix:semicolon
r_union
id|uint64_overlay
id|remainder
suffix:semicolon
r_union
id|uint64_overlay
id|normalized_dividend
suffix:semicolon
r_union
id|uint64_overlay
id|normalized_divisor
suffix:semicolon
id|u32
id|partial1
suffix:semicolon
r_union
id|uint64_overlay
id|partial2
suffix:semicolon
r_union
id|uint64_overlay
id|partial3
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_divide&quot;
)paren
suffix:semicolon
multiline_comment|/* Always check for a zero divisor */
r_if
c_cond
(paren
op_star
id|in_divisor
op_eq
l_int|0
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ut_divide: Divide by zero&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_DIVIDE_BY_ZERO
)paren
suffix:semicolon
)brace
id|divisor.full
op_assign
op_star
id|in_divisor
suffix:semicolon
id|dividend.full
op_assign
op_star
id|in_dividend
suffix:semicolon
r_if
c_cond
(paren
id|divisor.part.hi
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * 1) Simplest case is where the divisor is 32 bits, we can&n;&t;&t; * just do two divides&n;&t;&t; */
id|remainder.part.hi
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The quotient is 64 bits, the remainder is always 32 bits,&n;&t;&t; * and is generated by the second divide.&n;&t;&t; */
id|ACPI_DIV_64_BY_32
(paren
l_int|0
comma
id|dividend.part.hi
comma
id|divisor.part.lo
comma
id|quotient.part.hi
comma
id|partial1
)paren
suffix:semicolon
id|ACPI_DIV_64_BY_32
(paren
id|partial1
comma
id|dividend.part.lo
comma
id|divisor.part.lo
comma
id|quotient.part.lo
comma
id|remainder.part.lo
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * 2) The general case where the divisor is a full 64 bits&n;&t;&t; * is more difficult&n;&t;&t; */
id|quotient.part.hi
op_assign
l_int|0
suffix:semicolon
id|normalized_dividend
op_assign
id|dividend
suffix:semicolon
id|normalized_divisor
op_assign
id|divisor
suffix:semicolon
multiline_comment|/* Normalize the operands (shift until the divisor is &lt; 32 bits) */
r_do
(brace
id|ACPI_SHIFT_RIGHT_64
(paren
id|normalized_divisor.part.hi
comma
id|normalized_divisor.part.lo
)paren
suffix:semicolon
id|ACPI_SHIFT_RIGHT_64
(paren
id|normalized_dividend.part.hi
comma
id|normalized_dividend.part.lo
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|normalized_divisor.part.hi
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Partial divide */
id|ACPI_DIV_64_BY_32
(paren
id|normalized_dividend.part.hi
comma
id|normalized_dividend.part.lo
comma
id|normalized_divisor.part.lo
comma
id|quotient.part.lo
comma
id|partial1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The quotient is always 32 bits, and simply requires adjustment.&n;&t;&t; * The 64-bit remainder must be generated.&n;&t;&t; */
id|partial1
op_assign
id|quotient.part.lo
op_star
id|divisor.part.hi
suffix:semicolon
id|partial2.full
op_assign
(paren
id|acpi_integer
)paren
id|quotient.part.lo
op_star
id|divisor.part.lo
suffix:semicolon
id|partial3.full
op_assign
(paren
id|acpi_integer
)paren
id|partial2.part.hi
op_plus
id|partial1
suffix:semicolon
id|remainder.part.hi
op_assign
id|partial3.part.lo
suffix:semicolon
id|remainder.part.lo
op_assign
id|partial2.part.lo
suffix:semicolon
r_if
c_cond
(paren
id|partial3.part.hi
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|partial3.part.lo
op_ge
id|dividend.part.hi
)paren
(brace
r_if
c_cond
(paren
id|partial3.part.lo
op_eq
id|dividend.part.hi
)paren
(brace
r_if
c_cond
(paren
id|partial2.part.lo
OG
id|dividend.part.lo
)paren
(brace
id|quotient.part.lo
op_decrement
suffix:semicolon
id|remainder.full
op_sub_assign
id|divisor.full
suffix:semicolon
)brace
)brace
r_else
(brace
id|quotient.part.lo
op_decrement
suffix:semicolon
id|remainder.full
op_sub_assign
id|divisor.full
suffix:semicolon
)brace
)brace
id|remainder.full
op_assign
id|remainder.full
op_minus
id|dividend.full
suffix:semicolon
id|remainder.part.hi
op_assign
(paren
id|u32
)paren
op_minus
(paren
(paren
id|s32
)paren
id|remainder.part.hi
)paren
suffix:semicolon
id|remainder.part.lo
op_assign
(paren
id|u32
)paren
op_minus
(paren
(paren
id|s32
)paren
id|remainder.part.lo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remainder.part.lo
)paren
(brace
id|remainder.part.hi
op_decrement
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Return only what was requested */
r_if
c_cond
(paren
id|out_quotient
)paren
(brace
op_star
id|out_quotient
op_assign
id|quotient.full
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out_remainder
)paren
(brace
op_star
id|out_remainder
op_assign
id|remainder.full
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_short_divide, acpi_ut_divide&n; *&n; * DESCRIPTION: Native versions of the ut_divide functions. Use these if either&n; *              1) The target is a 64-bit platform and therefore 64-bit&n; *                 integer math is supported directly by the machine.&n; *              2) The target is a 32-bit or 16-bit platform, and the&n; *                 double-precision integer math library is available to&n; *                 perform the divide.&n; *&n; ******************************************************************************/
id|acpi_status
id|acpi_ut_short_divide
(paren
id|acpi_integer
op_star
id|in_dividend
comma
id|u32
id|divisor
comma
id|acpi_integer
op_star
id|out_quotient
comma
id|u32
op_star
id|out_remainder
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_short_divide&quot;
)paren
suffix:semicolon
multiline_comment|/* Always check for a zero divisor */
r_if
c_cond
(paren
id|divisor
op_eq
l_int|0
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ut_short_divide: Divide by zero&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_DIVIDE_BY_ZERO
)paren
suffix:semicolon
)brace
multiline_comment|/* Return only what was requested */
r_if
c_cond
(paren
id|out_quotient
)paren
(brace
op_star
id|out_quotient
op_assign
op_star
id|in_dividend
op_div
id|divisor
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out_remainder
)paren
(brace
op_star
id|out_remainder
op_assign
(paren
id|u32
)paren
op_star
id|in_dividend
op_mod
id|divisor
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|acpi_status
id|acpi_ut_divide
(paren
id|acpi_integer
op_star
id|in_dividend
comma
id|acpi_integer
op_star
id|in_divisor
comma
id|acpi_integer
op_star
id|out_quotient
comma
id|acpi_integer
op_star
id|out_remainder
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_divide&quot;
)paren
suffix:semicolon
multiline_comment|/* Always check for a zero divisor */
r_if
c_cond
(paren
op_star
id|in_divisor
op_eq
l_int|0
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ut_divide: Divide by zero&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_DIVIDE_BY_ZERO
)paren
suffix:semicolon
)brace
multiline_comment|/* Return only what was requested */
r_if
c_cond
(paren
id|out_quotient
)paren
(brace
op_star
id|out_quotient
op_assign
op_star
id|in_dividend
op_div
op_star
id|in_divisor
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out_remainder
)paren
(brace
op_star
id|out_remainder
op_assign
op_star
id|in_dividend
op_mod
op_star
id|in_divisor
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
