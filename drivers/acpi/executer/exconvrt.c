multiline_comment|/******************************************************************************&n; *&n; * Module Name: exconvrt - Object conversion routines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exconvrt&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_convert_to_integer&n; *&n; * PARAMETERS:  obj_desc        - Object to be converted.  Must be an&n; *                                Integer, Buffer, or String&n; *              result_desc     - Where the new Integer object is returned&n; *              Flags           - Used for string conversion&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an ACPI Object to an integer.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_integer
id|acpi_ex_convert_to_integer
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_union
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|u32
id|flags
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|return_desc
suffix:semicolon
id|u8
op_star
id|pointer
suffix:semicolon
id|acpi_integer
id|result
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u32
id|count
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_convert_to_integer&quot;
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
multiline_comment|/* No conversion necessary */
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
id|ACPI_TYPE_BUFFER
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/* Note: Takes advantage of common buffer/string fields */
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
multiline_comment|/*&n;&t;&t; * Convert string to an integer - for most cases, the string must be&n;&t;&t; * hexadecimal as per the ACPI specification.  The only exception (as&n;&t;&t; * of ACPI 3.0) is that the to_integer() operator allows both decimal&n;&t;&t; * and hexadecimal strings (hex prefixed with &quot;0x&quot;).&n;&t;&t; */
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
id|flags
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
multiline_comment|/* Check for zero-length buffer */
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_BUFFER_LIMIT
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t;&t; * Convert buffer to an integer - we simply grab enough raw data&n;&t;&t; * from the buffer to fill an integer&n;&t;&t; */
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
id|return_desc
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
id|return_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Save the Result */
id|return_desc-&gt;integer.value
op_assign
id|result
suffix:semicolon
id|acpi_ex_truncate_for32bit_table
(paren
id|return_desc
)paren
suffix:semicolon
op_star
id|result_desc
op_assign
id|return_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_convert_to_buffer&n; *&n; * PARAMETERS:  obj_desc        - Object to be converted.  Must be an&n; *                                Integer, Buffer, or String&n; *              result_desc     - Where the new buffer object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an ACPI Object to a Buffer&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_buffer
id|acpi_ex_convert_to_buffer
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_union
id|acpi_operand_object
op_star
op_star
id|result_desc
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|return_desc
suffix:semicolon
id|u8
op_star
id|new_buf
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_convert_to_buffer&quot;
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
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/* No conversion necessary */
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
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/*&n;&t;&t; * Create a new Buffer object.&n;&t;&t; * Need enough space for one integer&n;&t;&t; */
id|return_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
id|acpi_gbl_integer_byte_width
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the integer to the buffer, LSB first */
id|new_buf
op_assign
id|return_desc-&gt;buffer.pointer
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|new_buf
comma
op_amp
id|obj_desc-&gt;integer.value
comma
id|acpi_gbl_integer_byte_width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/*&n;&t;&t; * Create a new Buffer object&n;&t;&t; * Size will be the string length&n;&t;&t; *&n;&t;&t; * NOTE: Add one to the string length to include the null terminator.&n;&t;&t; * The ACPI spec is unclear on this subject, but there is existing&n;&t;&t; * ASL/AML code that depends on the null being transferred to the new&n;&t;&t; * buffer.&n;&t;&t; */
id|return_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
(paren
id|acpi_size
)paren
id|obj_desc-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the string to the buffer */
id|new_buf
op_assign
id|return_desc-&gt;buffer.pointer
suffix:semicolon
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
id|return_desc-&gt;common.flags
op_or_assign
id|AOPOBJ_DATA_VALID
suffix:semicolon
op_star
id|result_desc
op_assign
id|return_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_convert_to_ascii&n; *&n; * PARAMETERS:  Integer         - Value to be converted&n; *              Base            - ACPI_STRING_DECIMAL or ACPI_STRING_HEX&n; *              String          - Where the string is returned&n; *              data_width      - Size of data item to be converted, in bytes&n; *&n; * RETURN:      Actual string length&n; *&n; * DESCRIPTION: Convert an ACPI Integer to a hex or decimal string&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ex_convert_to_ascii
id|acpi_ex_convert_to_ascii
(paren
id|acpi_integer
id|integer
comma
id|u16
id|base
comma
id|u8
op_star
id|string
comma
id|u8
id|data_width
)paren
(brace
id|acpi_integer
id|digit
suffix:semicolon
id|acpi_native_uint
id|i
suffix:semicolon
id|acpi_native_uint
id|j
suffix:semicolon
id|acpi_native_uint
id|k
op_assign
l_int|0
suffix:semicolon
id|acpi_native_uint
id|hex_length
suffix:semicolon
id|acpi_native_uint
id|decimal_length
suffix:semicolon
id|u32
id|remainder
suffix:semicolon
id|u8
id|supress_zeros
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
multiline_comment|/* Setup max length for the decimal number */
r_switch
c_cond
(paren
id|data_width
)paren
(brace
r_case
l_int|1
suffix:colon
id|decimal_length
op_assign
id|ACPI_MAX8_DECIMAL_DIGITS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|decimal_length
op_assign
id|ACPI_MAX32_DECIMAL_DIGITS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_default
suffix:colon
id|decimal_length
op_assign
id|ACPI_MAX64_DECIMAL_DIGITS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|supress_zeros
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/* No leading zeros */
id|remainder
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|decimal_length
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
l_int|0
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
multiline_comment|/* Handle leading zeros */
r_if
c_cond
(paren
id|remainder
op_ne
l_int|0
)paren
(brace
id|supress_zeros
op_assign
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|supress_zeros
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
id|hex_length
op_assign
id|ACPI_MUL_2
(paren
id|data_width
)paren
suffix:semicolon
multiline_comment|/* 2 ascii hex chars per data byte */
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
id|hex_length
op_minus
l_int|1
)paren
suffix:semicolon
id|i
OL
id|hex_length
suffix:semicolon
id|i
op_increment
comma
id|j
op_decrement
)paren
(brace
multiline_comment|/* Get one hex digit, most significant digits first */
id|string
(braket
id|k
)braket
op_assign
(paren
id|u8
)paren
id|acpi_ut_hex_to_ascii_char
(paren
id|integer
comma
id|ACPI_MUL_4
(paren
id|j
)paren
)paren
suffix:semicolon
id|k
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Since leading zeros are supressed, we must check for the case where&n;&t; * the integer equals 0&n;&t; *&n;&t; * Finally, null terminate the string and return the length&n;&t; */
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
(paren
id|u32
)paren
id|k
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_convert_to_string&n; *&n; * PARAMETERS:  obj_desc        - Object to be converted.  Must be an&n; *                                Integer, Buffer, or String&n; *              result_desc     - Where the string object is returned&n; *              Type            - String flags (base and conversion type)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an ACPI Object to a string&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_string
id|acpi_ex_convert_to_string
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_union
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|u32
id|type
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|return_desc
suffix:semicolon
id|u8
op_star
id|new_buf
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u32
id|string_length
op_assign
l_int|0
suffix:semicolon
id|u16
id|base
op_assign
l_int|16
suffix:semicolon
id|u8
id|separator
op_assign
l_char|&squot;,&squot;
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_convert_to_string&quot;
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
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/* No conversion necessary */
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
id|ACPI_TYPE_INTEGER
suffix:colon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_EXPLICIT_CONVERT_DECIMAL
suffix:colon
multiline_comment|/* Make room for maximum decimal number */
id|string_length
op_assign
id|ACPI_MAX_DECIMAL_DIGITS
suffix:semicolon
id|base
op_assign
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Two hex string characters for each integer byte */
id|string_length
op_assign
id|ACPI_MUL_2
(paren
id|acpi_gbl_integer_byte_width
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Create a new String&n;&t;&t; * Need enough space for one ASCII integer (plus null terminator)&n;&t;&t; */
id|return_desc
op_assign
id|acpi_ut_create_string_object
(paren
(paren
id|acpi_size
)paren
id|string_length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|new_buf
op_assign
id|return_desc-&gt;buffer.pointer
suffix:semicolon
multiline_comment|/* Convert integer to string */
id|string_length
op_assign
id|acpi_ex_convert_to_ascii
(paren
id|obj_desc-&gt;integer.value
comma
id|base
comma
id|new_buf
comma
id|acpi_gbl_integer_byte_width
)paren
suffix:semicolon
multiline_comment|/* Null terminate at the correct place */
id|return_desc-&gt;string.length
op_assign
id|string_length
suffix:semicolon
id|new_buf
(braket
id|string_length
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/* Setup string length, base, and separator */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_EXPLICIT_CONVERT_DECIMAL
suffix:colon
multiline_comment|/* Used by to_decimal_string operator */
multiline_comment|/*&n;&t;&t;&t; * From ACPI: &quot;If Data is a buffer, it is converted to a string of&n;&t;&t;&t; * decimal values separated by commas.&quot;&n;&t;&t;&t; */
id|base
op_assign
l_int|10
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Calculate the final string length.  Individual string values&n;&t;&t;&t; * are variable length (include separator for each)&n;&t;&t;&t; */
r_for
c_loop
(paren
id|i
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
r_if
c_cond
(paren
id|obj_desc-&gt;buffer.pointer
(braket
id|i
)braket
op_ge
l_int|100
)paren
(brace
id|string_length
op_add_assign
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|obj_desc-&gt;buffer.pointer
(braket
id|i
)braket
op_ge
l_int|10
)paren
(brace
id|string_length
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
id|string_length
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ACPI_IMPLICIT_CONVERT_HEX
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * From the ACPI spec:&n;&t;&t;&t; *&quot;The entire contents of the buffer are converted to a string of&n;&t;&t;&t; * two-character hexadecimal numbers, each separated by a space.&quot;&n;&t;&t;&t; */
id|separator
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|string_length
op_assign
(paren
id|obj_desc-&gt;buffer.length
op_star
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_EXPLICIT_CONVERT_HEX
suffix:colon
multiline_comment|/* Used by to_hex_string operator */
multiline_comment|/*&n;&t;&t;&t; * From ACPI: &quot;If Data is a buffer, it is converted to a string of&n;&t;&t;&t; * hexadecimal values separated by commas.&quot;&n;&t;&t;&t; */
id|string_length
op_assign
(paren
id|obj_desc-&gt;buffer.length
op_star
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Perform the conversion.&n;&t;&t; * (-1 because of extra separator included in string_length from above)&n;&t;&t; */
id|string_length
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|string_length
OG
id|ACPI_MAX_STRING_CONVERSION
)paren
multiline_comment|/* ACPI limit */
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_STRING_LIMIT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Create a new string object and string buffer&n;&t;&t; */
id|return_desc
op_assign
id|acpi_ut_create_string_object
(paren
(paren
id|acpi_size
)paren
id|string_length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|new_buf
op_assign
id|return_desc-&gt;buffer.pointer
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Convert buffer bytes to hex or decimal values&n;&t;&t; * (separated by commas or spaces)&n;&t;&t; */
r_for
c_loop
(paren
id|i
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
id|new_buf
op_add_assign
id|acpi_ex_convert_to_ascii
(paren
(paren
id|acpi_integer
)paren
id|obj_desc-&gt;buffer.pointer
(braket
id|i
)braket
comma
id|base
comma
id|new_buf
comma
l_int|1
)paren
suffix:semicolon
op_star
id|new_buf
op_increment
op_assign
id|separator
suffix:semicolon
multiline_comment|/* each separated by a comma or space */
)brace
multiline_comment|/* Null terminate the string (overwrites final comma/space from above) */
id|new_buf
op_decrement
suffix:semicolon
op_star
id|new_buf
op_assign
l_int|0
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
op_star
id|result_desc
op_assign
id|return_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_convert_to_target_type&n; *&n; * PARAMETERS:  destination_type    - Current type of the destination&n; *              source_desc         - Source object to be converted.&n; *              result_desc         - Where the converted object is returned&n; *              walk_state          - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Implements &quot;implicit conversion&quot; rules for storing an object.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_convert_to_target_type
id|acpi_ex_convert_to_target_type
(paren
id|acpi_object_type
id|destination_type
comma
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
r_union
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
r_struct
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
l_string|&quot;ex_convert_to_target_type&quot;
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
id|ACPI_TYPE_LOCAL_REGION_FIELD
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
id|ACPI_DB_INFO
comma
l_string|&quot;Explicit operator, will store (%s) over existing type (%s)&bslash;n&quot;
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
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
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
l_int|16
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
id|ACPI_IMPLICIT_CONVERT_HEX
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
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Bad destination type during conversion: %X&bslash;n&quot;
comma
id|destination_type
)paren
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t;&t; * create_xxxx_field cases - we are storing the field object into the name&n;&t;&t; */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown Target type ID 0x%X Op %s dest_type %s&bslash;n&quot;
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Bad Target Type (ARGI): %X&bslash;n&quot;
comma
id|GET_CURRENT_ARG_TYPE
(paren
id|walk_state-&gt;op_info-&gt;runtime_args
)paren
)paren
)paren
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
