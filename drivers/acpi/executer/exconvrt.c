multiline_comment|/******************************************************************************&n; *&n; * Module Name: exconvrt - Object conversion routines&n; *              $Revision: 38 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exconvrt&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_convert_to_integer&n; *&n; * PARAMETERS:  *Obj_desc       - Object to be converted.  Must be an&n; *                                Integer, Buffer, or String&n; *              Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an ACPI Object to an integer.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_integer
id|acpi_ex_convert_to_integer
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
id|acpi_operand_object
op_star
id|ret_desc
suffix:semicolon
id|u32
id|count
suffix:semicolon
id|u8
op_star
id|pointer
suffix:semicolon
id|acpi_integer
id|result
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ex_convert_to_integer&quot;
comma
id|obj_desc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
op_star
id|result_desc
op_assign
id|obj_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|pointer
op_assign
(paren
id|u8
op_star
)paren
id|obj_desc-&gt;string.pointer
suffix:semicolon
id|count
op_assign
id|obj_desc-&gt;string.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|pointer
op_assign
id|obj_desc-&gt;buffer.pointer
suffix:semicolon
id|count
op_assign
id|obj_desc-&gt;buffer.length
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Convert the buffer/string to an integer.  Note that both buffers and&n;&t; * strings are treated as raw data - we don&squot;t convert ascii to hex for&n;&t; * strings.&n;&t; *&n;&t; * There are two terminating conditions for the loop:&n;&t; * 1) The size of an integer has been reached, or&n;&t; * 2) The end of the buffer or string has been reached&n;&t; */
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Transfer no more than an integer&squot;s worth of data */
r_if
c_cond
(paren
id|count
OG
id|acpi_gbl_integer_byte_width
)paren
(brace
id|count
op_assign
id|acpi_gbl_integer_byte_width
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * String conversion is different than Buffer conversion&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/*&n;&t;&t; * Convert string to an integer&n;&t;&t; * String must be hexadecimal as per the ACPI specification&n;&t;&t; */
id|status
op_assign
id|acpi_ut_strtoul64
(paren
(paren
r_char
op_star
)paren
id|pointer
comma
l_int|16
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/*&n;&t;&t; * Buffer conversion - we simply grab enough raw data from the&n;&t;&t; * buffer to fill an integer&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Get next byte and shift it into the Result.&n;&t;&t;&t; * Little endian is used, meaning that the first byte of the buffer&n;&t;&t;&t; * is the LSB of the integer&n;&t;&t;&t; */
id|result
op_or_assign
(paren
(paren
(paren
id|acpi_integer
)paren
id|pointer
(braket
id|i
)braket
)paren
op_lshift
(paren
id|i
op_star
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* No other types can get here */
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create a new integer&n;&t; */
id|ret_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_INTEGER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Save the Result, delete original descriptor, store new descriptor */
id|ret_desc-&gt;integer.value
op_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
op_star
id|result_desc
op_eq
id|obj_desc
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_ne
id|AML_STORE_OP
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
)brace
op_star
id|result_desc
op_assign
id|ret_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_convert_to_buffer&n; *&n; * PARAMETERS:  *Obj_desc       - Object to be converted.  Must be an&n; *                                Integer, Buffer, or String&n; *              Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an ACPI Object to an Buffer&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_buffer
id|acpi_ex_convert_to_buffer
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_operand_object
op_star
id|ret_desc
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u8
op_star
id|new_buf
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ex_convert_to_buffer&quot;
comma
id|obj_desc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/*&n;&t;&t; * Create a new Buffer object&n;&t;&t; */
id|ret_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_BUFFER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Need enough space for one integer */
id|new_buf
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|acpi_gbl_integer_byte_width
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_buf
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Ex_convert_to_buffer: Buffer allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|ret_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the integer to the buffer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_integer_byte_width
suffix:semicolon
id|i
op_increment
)paren
(brace
id|new_buf
(braket
id|i
)braket
op_assign
(paren
id|u8
)paren
(paren
id|obj_desc-&gt;integer.value
op_rshift
(paren
id|i
op_star
l_int|8
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Complete buffer object initialization */
id|ret_desc-&gt;buffer.flags
op_or_assign
id|AOPOBJ_DATA_VALID
suffix:semicolon
id|ret_desc-&gt;buffer.pointer
op_assign
id|new_buf
suffix:semicolon
id|ret_desc-&gt;buffer.length
op_assign
id|acpi_gbl_integer_byte_width
suffix:semicolon
multiline_comment|/* Return the new buffer descriptor */
op_star
id|result_desc
op_assign
id|ret_desc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/*&n;&t;&t; * Create a new Buffer object&n;&t;&t; */
id|ret_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_BUFFER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Need enough space for one integer */
id|new_buf
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|obj_desc-&gt;string.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_buf
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Ex_convert_to_buffer: Buffer allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|ret_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|ACPI_STRNCPY
(paren
(paren
r_char
op_star
)paren
id|new_buf
comma
(paren
r_char
op_star
)paren
id|obj_desc-&gt;string.pointer
comma
id|obj_desc-&gt;string.length
)paren
suffix:semicolon
id|ret_desc-&gt;buffer.flags
op_or_assign
id|AOPOBJ_DATA_VALID
suffix:semicolon
id|ret_desc-&gt;buffer.pointer
op_assign
id|new_buf
suffix:semicolon
id|ret_desc-&gt;buffer.length
op_assign
id|obj_desc-&gt;string.length
suffix:semicolon
multiline_comment|/* Return the new buffer descriptor */
op_star
id|result_desc
op_assign
id|ret_desc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
op_star
id|result_desc
op_assign
id|obj_desc
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* Mark buffer initialized */
(paren
op_star
id|result_desc
)paren
op_member_access_from_pointer
id|common.flags
op_or_assign
id|AOPOBJ_DATA_VALID
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_convert_ascii&n; *&n; * PARAMETERS:  Integer&n; *&n; * RETURN:      Actual string length&n; *&n; * DESCRIPTION: Convert an ACPI Integer to a hex string&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ex_convert_to_ascii
id|acpi_ex_convert_to_ascii
(paren
id|acpi_integer
id|integer
comma
id|u32
id|base
comma
id|u8
op_star
id|string
)paren
(brace
id|u32
id|i
suffix:semicolon
id|u32
id|j
suffix:semicolon
id|u32
id|k
op_assign
l_int|0
suffix:semicolon
r_char
id|hex_digit
suffix:semicolon
id|acpi_integer
id|digit
suffix:semicolon
id|u32
id|remainder
suffix:semicolon
id|u32
id|length
op_assign
r_sizeof
(paren
id|acpi_integer
)paren
suffix:semicolon
id|u8
id|leading_zero
op_assign
id|TRUE
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|base
)paren
(brace
r_case
l_int|10
suffix:colon
id|remainder
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ACPI_MAX_DECIMAL_DIGITS
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
multiline_comment|/* Divide by nth factor of 10 */
id|digit
op_assign
id|integer
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_short_divide
(paren
op_amp
id|digit
comma
l_int|10
comma
op_amp
id|digit
comma
op_amp
id|remainder
)paren
suffix:semicolon
)brace
multiline_comment|/* Create the decimal digit */
r_if
c_cond
(paren
id|digit
op_ne
l_int|0
)paren
(brace
id|leading_zero
op_assign
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|leading_zero
)paren
(brace
id|string
(braket
id|k
)braket
op_assign
(paren
id|u8
)paren
(paren
id|ACPI_ASCII_ZERO
op_plus
id|remainder
)paren
suffix:semicolon
id|k
op_increment
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
multiline_comment|/* Copy the integer to the buffer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
(paren
(paren
id|length
op_star
l_int|2
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|i
OL
(paren
id|length
op_star
l_int|2
)paren
suffix:semicolon
id|i
op_increment
comma
id|j
op_decrement
)paren
(brace
id|hex_digit
op_assign
id|acpi_ut_hex_to_ascii_char
(paren
id|integer
comma
(paren
id|j
op_star
l_int|4
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hex_digit
op_ne
id|ACPI_ASCII_ZERO
)paren
(brace
id|leading_zero
op_assign
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|leading_zero
)paren
(brace
id|string
(braket
id|k
)braket
op_assign
(paren
id|u8
)paren
id|hex_digit
suffix:semicolon
id|k
op_increment
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Since leading zeros are supressed, we must check for the case where&n;&t; * the integer equals 0.&n;&t; *&n;&t; * Finally, null terminate the string and return the length&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|k
)paren
(brace
id|string
(braket
l_int|0
)braket
op_assign
id|ACPI_ASCII_ZERO
suffix:semicolon
id|k
op_assign
l_int|1
suffix:semicolon
)brace
id|string
(braket
id|k
)braket
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|k
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_convert_to_string&n; *&n; * PARAMETERS:  *Obj_desc       - Object to be converted.  Must be an&n; *                                Integer, Buffer, or String&n; *              Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an ACPI Object to a string&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_string
id|acpi_ex_convert_to_string
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|u32
id|base
comma
id|u32
id|max_length
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_operand_object
op_star
id|ret_desc
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u32
id|index
suffix:semicolon
id|u32
id|string_length
suffix:semicolon
id|u8
op_star
id|new_buf
suffix:semicolon
id|u8
op_star
id|pointer
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ex_convert_to_string&quot;
comma
id|obj_desc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|string_length
op_assign
id|acpi_gbl_integer_byte_width
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|10
)paren
(brace
id|string_length
op_assign
id|ACPI_MAX_DECIMAL_DIGITS
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Create a new String&n;&t;&t; */
id|ret_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_STRING
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Need enough space for one ASCII integer plus null terminator */
id|new_buf
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|ACPI_SIZE
)paren
id|string_length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_buf
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Ex_convert_to_string: Buffer allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|ret_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert */
id|i
op_assign
id|acpi_ex_convert_to_ascii
(paren
id|obj_desc-&gt;integer.value
comma
id|base
comma
id|new_buf
)paren
suffix:semicolon
multiline_comment|/* Null terminate at the correct place */
r_if
c_cond
(paren
id|max_length
OL
id|i
)paren
(brace
id|new_buf
(braket
id|max_length
)braket
op_assign
l_int|0
suffix:semicolon
id|ret_desc-&gt;string.length
op_assign
id|max_length
suffix:semicolon
)brace
r_else
(brace
id|new_buf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|ret_desc-&gt;string.length
op_assign
id|i
suffix:semicolon
)brace
id|ret_desc-&gt;buffer.pointer
op_assign
id|new_buf
suffix:semicolon
multiline_comment|/* Return the new buffer descriptor */
r_if
c_cond
(paren
op_star
id|result_desc
op_eq
id|obj_desc
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_ne
id|AML_STORE_OP
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
)brace
op_star
id|result_desc
op_assign
id|ret_desc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|string_length
op_assign
id|obj_desc-&gt;buffer.length
op_star
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|10
)paren
(brace
id|string_length
op_assign
id|obj_desc-&gt;buffer.length
op_star
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|max_length
OG
id|ACPI_MAX_STRING_CONVERSION
)paren
(brace
r_if
c_cond
(paren
id|string_length
OG
id|ACPI_MAX_STRING_CONVERSION
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_STRING_LIMIT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Create a new string object&n;&t;&t; */
id|ret_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_STRING
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* String length is the lesser of the Max or the actual length */
r_if
c_cond
(paren
id|max_length
OL
id|string_length
)paren
(brace
id|string_length
op_assign
id|max_length
suffix:semicolon
)brace
id|new_buf
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|ACPI_SIZE
)paren
id|string_length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_buf
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Ex_convert_to_string: Buffer allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|ret_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Convert each byte of the buffer to two ASCII characters plus a space.&n;&t;&t; */
id|pointer
op_assign
id|obj_desc-&gt;buffer.pointer
suffix:semicolon
id|index
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|index
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|obj_desc-&gt;buffer.length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|index
op_assign
id|acpi_ex_convert_to_ascii
(paren
(paren
id|acpi_integer
)paren
id|pointer
(braket
id|i
)braket
comma
id|base
comma
op_amp
id|new_buf
(braket
id|index
)braket
)paren
suffix:semicolon
id|new_buf
(braket
id|index
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|index
op_increment
suffix:semicolon
)brace
multiline_comment|/* Null terminate */
id|new_buf
(braket
id|index
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|ret_desc-&gt;buffer.pointer
op_assign
id|new_buf
suffix:semicolon
id|ret_desc-&gt;string.length
op_assign
id|ACPI_STRLEN
(paren
(paren
r_char
op_star
)paren
id|new_buf
)paren
suffix:semicolon
multiline_comment|/* Return the new buffer descriptor */
r_if
c_cond
(paren
op_star
id|result_desc
op_eq
id|obj_desc
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_ne
id|AML_STORE_OP
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
)brace
op_star
id|result_desc
op_assign
id|ret_desc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_if
c_cond
(paren
id|max_length
op_ge
id|obj_desc-&gt;string.length
)paren
(brace
op_star
id|result_desc
op_assign
id|obj_desc
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Must copy the string first and then truncate it */
id|return_ACPI_STATUS
(paren
id|AE_NOT_IMPLEMENTED
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_convert_to_target_type&n; *&n; * PARAMETERS:  Destination_type    - Current type of the destination&n; *              Source_desc         - Source object to be converted.&n; *              Walk_state          - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Implements &quot;implicit conversion&quot; rules for storing an object.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_target_type
id|acpi_ex_convert_to_target_type
(paren
id|acpi_object_type
id|destination_type
comma
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ex_convert_to_target_type&quot;
)paren
suffix:semicolon
multiline_comment|/* Default behavior */
op_star
id|result_desc
op_assign
id|source_desc
suffix:semicolon
multiline_comment|/*&n;&t; * If required by the target,&n;&t; * perform implicit conversion on the source before we store it.&n;&t; */
r_switch
c_cond
(paren
id|GET_CURRENT_ARG_TYPE
(paren
id|walk_state-&gt;op_info-&gt;runtime_args
)paren
)paren
(brace
r_case
id|ARGI_SIMPLE_TARGET
suffix:colon
r_case
id|ARGI_FIXED_TARGET
suffix:colon
r_case
id|ARGI_INTEGER_REF
suffix:colon
multiline_comment|/* Handles Increment, Decrement cases */
r_switch
c_cond
(paren
id|destination_type
)paren
(brace
r_case
id|INTERNAL_TYPE_REGION_FIELD
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Named field can always handle conversions&n;&t;&t;&t; */
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* No conversion allowed for these types */
r_if
c_cond
(paren
id|destination_type
op_ne
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Target does not allow conversion of type %s to %s&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
comma
id|acpi_ut_get_type_name
(paren
id|destination_type
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_TYPE
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ARGI_TARGETREF
suffix:colon
r_switch
c_cond
(paren
id|destination_type
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_BANK_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_INDEX_FIELD
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * These types require an Integer operand.  We can convert&n;&t;&t;&t; * a Buffer or a String to an Integer if necessary.&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ex_convert_to_integer
(paren
id|source_desc
comma
id|result_desc
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * The operand must be a String.  We can convert an&n;&t;&t;&t; * Integer or Buffer if necessary&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ex_convert_to_string
(paren
id|source_desc
comma
id|result_desc
comma
l_int|16
comma
id|ACPI_UINT32_MAX
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * The operand must be a Buffer.  We can convert an&n;&t;&t;&t; * Integer or String if necessary&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ex_convert_to_buffer
(paren
id|source_desc
comma
id|result_desc
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_AML_INTERNAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ARGI_REFERENCE
suffix:colon
multiline_comment|/*&n;&t;&t; * Create_xxxx_field cases - we are storing the field object into the name&n;&t;&t; */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown Target type ID 0x%X Op %s Dest_type %s&bslash;n&quot;
comma
id|GET_CURRENT_ARG_TYPE
(paren
id|walk_state-&gt;op_info-&gt;runtime_args
)paren
comma
id|walk_state-&gt;op_info-&gt;name
comma
id|acpi_ut_get_type_name
(paren
id|destination_type
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_INTERNAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Source-to-Target conversion semantics:&n;&t; *&n;&t; * If conversion to the target type cannot be performed, then simply&n;&t; * overwrite the target with the new object and type.&n;&t; */
r_if
c_cond
(paren
id|status
op_eq
id|AE_TYPE
)paren
(brace
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
