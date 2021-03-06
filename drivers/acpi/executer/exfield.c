multiline_comment|/******************************************************************************&n; *&n; * Module Name: exfield - ACPI AML (p-code) execution - field manipulation&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exfield&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_read_data_from_field&n; *&n; * PARAMETERS:  walk_state          - Current execution state&n; *              obj_desc            - The named field&n; *              ret_buffer_desc     - Where the return data object is stored&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Read from a named field.  Returns either an Integer or a&n; *              Buffer, depending on the size of the field.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_read_data_from_field
id|acpi_ex_read_data_from_field
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_union
id|acpi_operand_object
op_star
op_star
id|ret_buffer_desc
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|buffer_desc
suffix:semicolon
id|acpi_size
id|length
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
id|u8
id|locked
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_read_data_from_field&quot;
comma
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_BUFFER_FIELD
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the buffer_field arguments have not been previously evaluated,&n;&t;&t; * evaluate them now and save the results.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|obj_desc-&gt;common.flags
op_amp
id|AOPOBJ_DATA_VALID
)paren
)paren
(brace
id|status
op_assign
id|acpi_ds_get_buffer_field_arguments
(paren
id|obj_desc
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
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_LOCAL_REGION_FIELD
)paren
op_logical_and
(paren
id|obj_desc-&gt;field.region_obj-&gt;region.space_id
op_eq
id|ACPI_ADR_SPACE_SMBUS
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is an SMBus read.  We must create a buffer to hold the data&n;&t;&t; * and directly access the region handler.&n;&t;&t; */
id|buffer_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
id|ACPI_SMBUS_BUFFER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Lock entire transaction if requested */
id|locked
op_assign
id|acpi_ex_acquire_global_lock
(paren
id|obj_desc-&gt;common_field.field_flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Perform the read.&n;&t;&t; * Note: Smbus protocol value is passed in upper 16-bits of Function&n;&t;&t; */
id|status
op_assign
id|acpi_ex_access_region
(paren
id|obj_desc
comma
l_int|0
comma
id|ACPI_CAST_PTR
(paren
id|acpi_integer
comma
id|buffer_desc-&gt;buffer.pointer
)paren
comma
id|ACPI_READ
op_or
(paren
id|obj_desc-&gt;field.attribute
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|acpi_ex_release_global_lock
(paren
id|locked
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate a buffer for the contents of the field.&n;&t; *&n;&t; * If the field is larger than the size of an acpi_integer, create&n;&t; * a BUFFER to hold it.  Otherwise, use an INTEGER.  This allows&n;&t; * the use of arithmetic operators on the returned value if the&n;&t; * field size is equal or smaller than an Integer.&n;&t; *&n;&t; * Note: Field.length is in bits.&n;&t; */
id|length
op_assign
(paren
id|acpi_size
)paren
id|ACPI_ROUND_BITS_UP_TO_BYTES
(paren
id|obj_desc-&gt;field.bit_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|acpi_gbl_integer_byte_width
)paren
(brace
multiline_comment|/* Field is too large for an Integer, create a Buffer instead */
id|buffer_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|buffer_desc-&gt;buffer.pointer
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Field will fit within an Integer (normal case) */
id|buffer_desc
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
id|buffer_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|length
op_assign
id|acpi_gbl_integer_byte_width
suffix:semicolon
id|buffer_desc-&gt;integer.value
op_assign
l_int|0
suffix:semicolon
id|buffer
op_assign
op_amp
id|buffer_desc-&gt;integer.value
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_BFIELD
comma
l_string|&quot;field_read [TO]:  Obj %p, Type %X, Buf %p, byte_len %X&bslash;n&quot;
comma
id|obj_desc
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
comma
id|buffer
comma
(paren
id|u32
)paren
id|length
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_BFIELD
comma
l_string|&quot;field_read [FROM]: bit_len %X, bit_off %X, byte_off %X&bslash;n&quot;
comma
id|obj_desc-&gt;common_field.bit_length
comma
id|obj_desc-&gt;common_field.start_field_bit_offset
comma
id|obj_desc-&gt;common_field.base_byte_offset
)paren
)paren
suffix:semicolon
multiline_comment|/* Lock entire transaction if requested */
id|locked
op_assign
id|acpi_ex_acquire_global_lock
(paren
id|obj_desc-&gt;common_field.field_flags
)paren
suffix:semicolon
multiline_comment|/* Read from the field */
id|status
op_assign
id|acpi_ex_extract_from_field
(paren
id|obj_desc
comma
id|buffer
comma
(paren
id|u32
)paren
id|length
)paren
suffix:semicolon
id|acpi_ex_release_global_lock
(paren
id|locked
)paren
suffix:semicolon
m_exit
suffix:colon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|buffer_desc
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ret_buffer_desc
)paren
(brace
op_star
id|ret_buffer_desc
op_assign
id|buffer_desc
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_write_data_to_field&n; *&n; * PARAMETERS:  source_desc         - Contains data to write&n; *              obj_desc            - The named field&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Write to a named field&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_write_data_to_field
id|acpi_ex_write_data_to_field
(paren
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
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
id|acpi_status
id|status
suffix:semicolon
id|u32
id|length
suffix:semicolon
id|u32
id|required_length
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_void
op_star
id|new_buffer
suffix:semicolon
id|u8
id|locked
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|buffer_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_write_data_to_field&quot;
comma
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|source_desc
op_logical_or
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_BUFFER_FIELD
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the buffer_field arguments have not been previously evaluated,&n;&t;&t; * evaluate them now and save the results.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|obj_desc-&gt;common.flags
op_amp
id|AOPOBJ_DATA_VALID
)paren
)paren
(brace
id|status
op_assign
id|acpi_ds_get_buffer_field_arguments
(paren
id|obj_desc
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
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_LOCAL_REGION_FIELD
)paren
op_logical_and
(paren
id|obj_desc-&gt;field.region_obj-&gt;region.space_id
op_eq
id|ACPI_ADR_SPACE_SMBUS
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is an SMBus write.  We will bypass the entire field mechanism&n;&t;&t; * and handoff the buffer directly to the handler.&n;&t;&t; *&n;&t;&t; * Source must be a buffer of sufficient size (ACPI_SMBUS_BUFFER_SIZE).&n;&t;&t; */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
op_ne
id|ACPI_TYPE_BUFFER
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;SMBus write requires Buffer, found type %s&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|source_desc-&gt;buffer.length
OL
id|ACPI_SMBUS_BUFFER_SIZE
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;SMBus write requires Buffer of length %X, found length %X&bslash;n&quot;
comma
id|ACPI_SMBUS_BUFFER_SIZE
comma
id|source_desc-&gt;buffer.length
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_BUFFER_LIMIT
)paren
suffix:semicolon
)brace
id|buffer_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
id|ACPI_SMBUS_BUFFER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|buffer_desc-&gt;buffer.pointer
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|buffer
comma
id|source_desc-&gt;buffer.pointer
comma
id|ACPI_SMBUS_BUFFER_SIZE
)paren
suffix:semicolon
multiline_comment|/* Lock entire transaction if requested */
id|locked
op_assign
id|acpi_ex_acquire_global_lock
(paren
id|obj_desc-&gt;common_field.field_flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Perform the write (returns status and perhaps data in the same buffer)&n;&t;&t; * Note: SMBus protocol type is passed in upper 16-bits of Function.&n;&t;&t; */
id|status
op_assign
id|acpi_ex_access_region
(paren
id|obj_desc
comma
l_int|0
comma
(paren
id|acpi_integer
op_star
)paren
id|buffer
comma
id|ACPI_WRITE
op_or
(paren
id|obj_desc-&gt;field.attribute
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|acpi_ex_release_global_lock
(paren
id|locked
)paren
suffix:semicolon
op_star
id|result_desc
op_assign
id|buffer_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get a pointer to the data to be written&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|buffer
op_assign
op_amp
id|source_desc-&gt;integer.value
suffix:semicolon
id|length
op_assign
r_sizeof
(paren
id|source_desc-&gt;integer.value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|buffer
op_assign
id|source_desc-&gt;buffer.pointer
suffix:semicolon
id|length
op_assign
id|source_desc-&gt;buffer.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|buffer
op_assign
id|source_desc-&gt;string.pointer
suffix:semicolon
id|length
op_assign
id|source_desc-&gt;string.length
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We must have a buffer that is at least as long as the field&n;&t; * we are writing to.  This is because individual fields are&n;&t; * indivisible and partial writes are not supported -- as per&n;&t; * the ACPI specification.&n;&t; */
id|new_buffer
op_assign
l_int|NULL
suffix:semicolon
id|required_length
op_assign
id|ACPI_ROUND_BITS_UP_TO_BYTES
(paren
id|obj_desc-&gt;common_field.bit_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
id|required_length
)paren
(brace
multiline_comment|/* We need to create a new buffer */
id|new_buffer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|required_length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_buffer
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Copy the original data to the new buffer, starting&n;&t;&t; * at Byte zero.  All unused (upper) bytes of the&n;&t;&t; * buffer will be 0.&n;&t;&t; */
id|ACPI_MEMCPY
(paren
(paren
r_char
op_star
)paren
id|new_buffer
comma
(paren
r_char
op_star
)paren
id|buffer
comma
id|length
)paren
suffix:semicolon
id|buffer
op_assign
id|new_buffer
suffix:semicolon
id|length
op_assign
id|required_length
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_BFIELD
comma
l_string|&quot;field_write [FROM]: Obj %p (%s:%X), Buf %p, byte_len %X&bslash;n&quot;
comma
id|source_desc
comma
id|acpi_ut_get_type_name
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
)paren
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
comma
id|buffer
comma
id|length
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_BFIELD
comma
l_string|&quot;field_write [TO]:  Obj %p (%s:%X), bit_len %X, bit_off %X, byte_off %X&bslash;n&quot;
comma
id|obj_desc
comma
id|acpi_ut_get_type_name
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
comma
id|obj_desc-&gt;common_field.bit_length
comma
id|obj_desc-&gt;common_field.start_field_bit_offset
comma
id|obj_desc-&gt;common_field.base_byte_offset
)paren
)paren
suffix:semicolon
multiline_comment|/* Lock entire transaction if requested */
id|locked
op_assign
id|acpi_ex_acquire_global_lock
(paren
id|obj_desc-&gt;common_field.field_flags
)paren
suffix:semicolon
multiline_comment|/* Write to the field */
id|status
op_assign
id|acpi_ex_insert_into_field
(paren
id|obj_desc
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
id|acpi_ex_release_global_lock
(paren
id|locked
)paren
suffix:semicolon
multiline_comment|/* Free temporary buffer if we used one */
r_if
c_cond
(paren
id|new_buffer
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|new_buffer
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
