multiline_comment|/*&n; *  acpi_utils.c - ACPI Utility Functions ($Revision: 10 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_BUS_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;acpi_utils&quot;
)paren
multiline_comment|/* --------------------------------------------------------------------------&n;                            Object Evaluation Helpers&n;   -------------------------------------------------------------------------- */
macro_line|#ifdef ACPI_DEBUG_OUTPUT
DECL|macro|acpi_util_eval_error
mdefine_line|#define acpi_util_eval_error(h,p,s) {&bslash;&n;&t;char prefix[80] = {&squot;&bslash;0&squot;};&bslash;&n;&t;struct acpi_buffer buffer = {sizeof(prefix), prefix};&bslash;&n;&t;acpi_get_name(h, ACPI_FULL_PATHNAME, &amp;buffer);&bslash;&n;&t;ACPI_DEBUG_PRINT((ACPI_DB_INFO, &quot;Evaluate [%s.%s]: %s&bslash;n&quot;,&bslash;&n;&t;&t;(char *) prefix, p, acpi_format_exception(s))); }
macro_line|#else
mdefine_line|#define acpi_util_eval_error(h,p,s)
macro_line|#endif
id|acpi_status
DECL|function|acpi_extract_package
id|acpi_extract_package
(paren
r_union
id|acpi_object
op_star
id|package
comma
r_struct
id|acpi_buffer
op_star
id|format
comma
r_struct
id|acpi_buffer
op_star
id|buffer
)paren
(brace
id|u32
id|size_required
op_assign
l_int|0
suffix:semicolon
id|u32
id|tail_offset
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|format_string
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|format_count
op_assign
l_int|0
suffix:semicolon
id|u32
id|i
op_assign
l_int|0
suffix:semicolon
id|u8
op_star
id|head
op_assign
l_int|NULL
suffix:semicolon
id|u8
op_star
id|tail
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_extract_package&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|package
op_logical_or
(paren
id|package-&gt;type
op_ne
id|ACPI_TYPE_PACKAGE
)paren
op_logical_or
(paren
id|package-&gt;package.count
OL
l_int|1
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid &squot;package&squot; argument&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|format
op_logical_or
op_logical_neg
id|format-&gt;pointer
op_logical_or
(paren
id|format-&gt;length
OL
l_int|1
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid &squot;format&squot; argument&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid &squot;buffer&squot; argument&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|format_count
op_assign
(paren
id|format-&gt;length
op_div
r_sizeof
(paren
r_char
)paren
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|format_count
OG
id|package-&gt;package.count
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Format specifies more objects [%d] than exist in package [%d].&quot;
comma
id|format_count
comma
id|package-&gt;package.count
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
id|format_string
op_assign
(paren
r_char
op_star
)paren
id|format-&gt;pointer
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate size_required.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|format_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_union
id|acpi_object
op_star
id|element
op_assign
op_amp
(paren
id|package-&gt;package.elements
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|element
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|element-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_switch
c_cond
(paren
id|format_string
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;N&squot;
suffix:colon
id|size_required
op_add_assign
r_sizeof
(paren
id|acpi_integer
)paren
suffix:semicolon
id|tail_offset
op_add_assign
r_sizeof
(paren
id|acpi_integer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;S&squot;
suffix:colon
id|size_required
op_add_assign
r_sizeof
(paren
r_char
op_star
)paren
op_plus
r_sizeof
(paren
id|acpi_integer
)paren
op_plus
r_sizeof
(paren
r_char
)paren
suffix:semicolon
id|tail_offset
op_add_assign
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid package element [%d]: got number, expecing [%c].&bslash;n&quot;
comma
id|i
comma
id|format_string
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
r_switch
c_cond
(paren
id|format_string
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;S&squot;
suffix:colon
id|size_required
op_add_assign
r_sizeof
(paren
r_char
op_star
)paren
op_plus
(paren
id|element-&gt;string.length
op_star
r_sizeof
(paren
r_char
)paren
)paren
op_plus
r_sizeof
(paren
r_char
)paren
suffix:semicolon
id|tail_offset
op_add_assign
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;B&squot;
suffix:colon
id|size_required
op_add_assign
r_sizeof
(paren
id|u8
op_star
)paren
op_plus
(paren
id|element-&gt;buffer.length
op_star
r_sizeof
(paren
id|u8
)paren
)paren
suffix:semicolon
id|tail_offset
op_add_assign
r_sizeof
(paren
id|u8
op_star
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid package element [%d] got string/buffer, expecing [%c].&bslash;n&quot;
comma
id|i
comma
id|format_string
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Found unsupported element at index=%d&bslash;n&quot;
comma
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/* TBD: handle nested packages... */
id|return_ACPI_STATUS
c_func
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Validate output buffer.&n;&t; */
r_if
c_cond
(paren
id|buffer-&gt;length
OL
id|size_required
)paren
(brace
id|buffer-&gt;length
op_assign
id|size_required
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BUFFER_OVERFLOW
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|buffer-&gt;length
op_ne
id|size_required
op_logical_or
op_logical_neg
id|buffer-&gt;pointer
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|head
op_assign
id|buffer-&gt;pointer
suffix:semicolon
id|tail
op_assign
id|buffer-&gt;pointer
op_plus
id|tail_offset
suffix:semicolon
multiline_comment|/*&n;&t; * Extract package data.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|format_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u8
op_star
op_star
id|pointer
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_object
op_star
id|element
op_assign
op_amp
(paren
id|package-&gt;package.elements
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|element
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|element-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_switch
c_cond
(paren
id|format_string
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;N&squot;
suffix:colon
op_star
(paren
(paren
id|acpi_integer
op_star
)paren
id|head
)paren
op_assign
id|element-&gt;integer.value
suffix:semicolon
id|head
op_add_assign
r_sizeof
(paren
id|acpi_integer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;S&squot;
suffix:colon
id|pointer
op_assign
(paren
id|u8
op_star
op_star
)paren
id|head
suffix:semicolon
op_star
id|pointer
op_assign
id|tail
suffix:semicolon
op_star
(paren
(paren
id|acpi_integer
op_star
)paren
id|tail
)paren
op_assign
id|element-&gt;integer.value
suffix:semicolon
id|head
op_add_assign
r_sizeof
(paren
id|acpi_integer
op_star
)paren
suffix:semicolon
id|tail
op_add_assign
r_sizeof
(paren
id|acpi_integer
)paren
suffix:semicolon
multiline_comment|/* NULL terminate string */
op_star
id|tail
op_assign
(paren
r_char
)paren
l_int|0
suffix:semicolon
id|tail
op_add_assign
r_sizeof
(paren
r_char
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Should never get here */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
r_switch
c_cond
(paren
id|format_string
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;S&squot;
suffix:colon
id|pointer
op_assign
(paren
id|u8
op_star
op_star
)paren
id|head
suffix:semicolon
op_star
id|pointer
op_assign
id|tail
suffix:semicolon
id|memcpy
c_func
(paren
id|tail
comma
id|element-&gt;string.pointer
comma
id|element-&gt;string.length
)paren
suffix:semicolon
id|head
op_add_assign
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|tail
op_add_assign
id|element-&gt;string.length
op_star
r_sizeof
(paren
r_char
)paren
suffix:semicolon
multiline_comment|/* NULL terminate string */
op_star
id|tail
op_assign
(paren
r_char
)paren
l_int|0
suffix:semicolon
id|tail
op_add_assign
r_sizeof
(paren
r_char
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;B&squot;
suffix:colon
id|pointer
op_assign
(paren
id|u8
op_star
op_star
)paren
id|head
suffix:semicolon
op_star
id|pointer
op_assign
id|tail
suffix:semicolon
id|memcpy
c_func
(paren
id|tail
comma
id|element-&gt;buffer.pointer
comma
id|element-&gt;buffer.length
)paren
suffix:semicolon
id|head
op_add_assign
r_sizeof
(paren
id|u8
op_star
)paren
suffix:semicolon
id|tail
op_add_assign
id|element-&gt;buffer.length
op_star
r_sizeof
(paren
id|u8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Should never get here */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
multiline_comment|/* TBD: handle nested packages... */
r_default
suffix:colon
multiline_comment|/* Should never get here */
r_break
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
DECL|variable|acpi_extract_package
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_extract_package
)paren
suffix:semicolon
id|acpi_status
DECL|function|acpi_evaluate_integer
id|acpi_evaluate_integer
(paren
id|acpi_handle
id|handle
comma
id|acpi_string
id|pathname
comma
r_struct
id|acpi_object_list
op_star
id|arguments
comma
r_int
r_int
op_star
id|data
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_union
id|acpi_object
id|element
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
r_sizeof
(paren
r_union
id|acpi_object
)paren
comma
op_amp
id|element
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_evaluate_integer&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|handle
comma
id|pathname
comma
id|arguments
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|status
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|element.type
op_ne
id|ACPI_TYPE_INTEGER
)paren
(brace
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|AE_BAD_DATA
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
op_star
id|data
op_assign
id|element.integer.value
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Return value [%lu]&bslash;n&quot;
comma
op_star
id|data
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
DECL|variable|acpi_evaluate_integer
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_evaluate_integer
)paren
suffix:semicolon
macro_line|#if 0
id|acpi_status
id|acpi_evaluate_string
(paren
id|acpi_handle
id|handle
comma
id|acpi_string
id|pathname
comma
id|acpi_object_list
op_star
id|arguments
comma
id|acpi_string
op_star
id|data
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_object
op_star
id|element
op_assign
l_int|NULL
suffix:semicolon
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_evaluate_string&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|handle
comma
id|pathname
comma
id|arguments
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|status
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
id|element
op_assign
(paren
id|acpi_object
op_star
)paren
id|buffer.pointer
suffix:semicolon
r_if
c_cond
(paren
(paren
id|element-&gt;type
op_ne
id|ACPI_TYPE_STRING
)paren
op_logical_or
(paren
id|element-&gt;type
op_ne
id|ACPI_TYPE_BUFFER
)paren
op_logical_or
op_logical_neg
id|element-&gt;string.length
)paren
(brace
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|AE_BAD_DATA
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
op_star
id|data
op_assign
id|kmalloc
c_func
(paren
id|element-&gt;string.length
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Memory allocation error&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
op_star
id|data
comma
l_int|0
comma
id|element-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_star
id|data
comma
id|element-&gt;string.pointer
comma
id|element-&gt;string.length
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Return value [%s]&bslash;n&quot;
comma
op_star
id|data
)paren
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#endif
id|acpi_status
DECL|function|acpi_evaluate_reference
id|acpi_evaluate_reference
(paren
id|acpi_handle
id|handle
comma
id|acpi_string
id|pathname
comma
r_struct
id|acpi_object_list
op_star
id|arguments
comma
r_struct
id|acpi_handle_list
op_star
id|list
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_union
id|acpi_object
op_star
id|package
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_object
op_star
id|element
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
id|u32
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_evaluate_reference&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Evaluate object. */
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|handle
comma
id|pathname
comma
id|arguments
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
r_goto
id|end
suffix:semicolon
id|package
op_assign
(paren
r_union
id|acpi_object
op_star
)paren
id|buffer.pointer
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer.length
op_eq
l_int|0
)paren
op_logical_or
op_logical_neg
id|package
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;No return object (len %X ptr %p)&bslash;n&quot;
comma
(paren
r_int
)paren
id|buffer.length
comma
id|package
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_BAD_DATA
suffix:semicolon
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|status
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|package-&gt;type
op_ne
id|ACPI_TYPE_PACKAGE
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Expecting a [Package], found type %X&bslash;n&quot;
comma
id|package-&gt;type
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_BAD_DATA
suffix:semicolon
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|status
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|package-&gt;package.count
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;[Package] has zero elements (%p)&bslash;n&quot;
comma
id|package
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_BAD_DATA
suffix:semicolon
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|status
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|package-&gt;package.count
OG
id|ACPI_MAX_HANDLES
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|list-&gt;count
op_assign
id|package-&gt;package.count
suffix:semicolon
multiline_comment|/* Extract package data. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|element
op_assign
op_amp
(paren
id|package-&gt;package.elements
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|element-&gt;type
op_ne
id|ACPI_TYPE_ANY
)paren
(brace
id|status
op_assign
id|AE_BAD_DATA
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Expecting a [Reference] package element, found type %X&bslash;n&quot;
comma
id|element-&gt;type
)paren
)paren
suffix:semicolon
id|acpi_util_eval_error
c_func
(paren
id|handle
comma
id|pathname
comma
id|status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Get the  acpi_handle. */
id|list-&gt;handles
(braket
id|i
)braket
op_assign
id|element-&gt;reference.handle
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Found reference [%p]&bslash;n&quot;
comma
id|list-&gt;handles
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|end
suffix:colon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|list-&gt;count
op_assign
l_int|0
suffix:semicolon
singleline_comment|//kfree(list-&gt;handles);
)brace
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
DECL|variable|acpi_evaluate_reference
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_evaluate_reference
)paren
suffix:semicolon
eof
