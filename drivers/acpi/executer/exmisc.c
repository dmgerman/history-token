multiline_comment|/******************************************************************************&n; *&n; * Module Name: exmisc - ACPI AML (p-code) execution - specific opcodes&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exmisc&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_get_object_reference&n; *&n; * PARAMETERS:  obj_desc            - Create a reference to this object&n; *              return_desc         - Where to store the reference&n; *              walk_state          - Current state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Obtain and return a &quot;reference&quot; to the target object&n; *              Common code for the ref_of_op and the cond_ref_of_op.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_get_object_reference
id|acpi_ex_get_object_reference
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
id|return_desc
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|reference_obj
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|referenced_obj
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_get_object_reference&quot;
comma
id|obj_desc
)paren
suffix:semicolon
op_star
id|return_desc
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_DESC_TYPE_OPERAND
suffix:colon
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Must be a reference to a Local or Arg&n;&t;&t; */
r_switch
c_cond
(paren
id|obj_desc-&gt;reference.opcode
)paren
(brace
r_case
id|AML_LOCAL_OP
suffix:colon
r_case
id|AML_ARG_OP
suffix:colon
multiline_comment|/* The referenced object is the pseudo-node for the local/arg */
id|referenced_obj
op_assign
id|obj_desc-&gt;reference.object
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Unknown Reference subtype in get ref %X&bslash;n&quot;
comma
id|obj_desc-&gt;reference.opcode
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_NAMED
suffix:colon
multiline_comment|/*&n;&t;&t; * A named reference that has already been resolved to a Node&n;&t;&t; */
id|referenced_obj
op_assign
id|obj_desc
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid descriptor type in get ref: %X&bslash;n&quot;
comma
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* Create a new reference object */
id|reference_obj
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reference_obj
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|reference_obj-&gt;reference.opcode
op_assign
id|AML_REF_OF_OP
suffix:semicolon
id|reference_obj-&gt;reference.object
op_assign
id|referenced_obj
suffix:semicolon
op_star
id|return_desc
op_assign
id|reference_obj
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Object %p Type [%s], returning Reference %p&bslash;n&quot;
comma
id|obj_desc
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
op_star
id|return_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_concat_template&n; *&n; * PARAMETERS:  Operand0            - First source object&n; *              Operand1            - Second source object&n; *              actual_return_desc  - Where to place the return object&n; *              walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Concatenate two resource templates&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_concat_template
id|acpi_ex_concat_template
(paren
r_union
id|acpi_operand_object
op_star
id|operand0
comma
r_union
id|acpi_operand_object
op_star
id|operand1
comma
r_union
id|acpi_operand_object
op_star
op_star
id|actual_return_desc
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
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
id|u8
op_star
id|end_tag1
suffix:semicolon
id|u8
op_star
id|end_tag2
suffix:semicolon
id|acpi_size
id|length1
suffix:semicolon
id|acpi_size
id|length2
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_concat_template&quot;
)paren
suffix:semicolon
multiline_comment|/* Find the end_tags in each resource template */
id|end_tag1
op_assign
id|acpi_ut_get_resource_end_tag
(paren
id|operand0
)paren
suffix:semicolon
id|end_tag2
op_assign
id|acpi_ut_get_resource_end_tag
(paren
id|operand1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|end_tag1
op_logical_or
op_logical_neg
id|end_tag2
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* Compute the length of each part */
id|length1
op_assign
id|ACPI_PTR_DIFF
(paren
id|end_tag1
comma
id|operand0-&gt;buffer.pointer
)paren
suffix:semicolon
id|length2
op_assign
id|ACPI_PTR_DIFF
(paren
id|end_tag2
comma
id|operand1-&gt;buffer.pointer
)paren
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* Size of END_TAG */
multiline_comment|/* Create a new buffer object for the result */
id|return_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
id|length1
op_plus
id|length2
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
multiline_comment|/* Copy the templates to the new descriptor */
id|new_buf
op_assign
id|return_desc-&gt;buffer.pointer
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|new_buf
comma
id|operand0-&gt;buffer.pointer
comma
id|length1
)paren
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|new_buf
op_plus
id|length1
comma
id|operand1-&gt;buffer.pointer
comma
id|length2
)paren
suffix:semicolon
multiline_comment|/* Compute the new checksum */
id|new_buf
(braket
id|return_desc-&gt;buffer.length
op_minus
l_int|1
)braket
op_assign
id|acpi_ut_generate_checksum
(paren
id|return_desc-&gt;buffer.pointer
comma
(paren
id|return_desc-&gt;buffer.length
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Return the completed template descriptor */
op_star
id|actual_return_desc
op_assign
id|return_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_do_concatenate&n; *&n; * PARAMETERS:  Operand0            - First source object&n; *              Operand1            - Second source object&n; *              actual_return_desc  - Where to place the return object&n; *              walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Concatenate two objects OF THE SAME TYPE.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_do_concatenate
id|acpi_ex_do_concatenate
(paren
r_union
id|acpi_operand_object
op_star
id|operand0
comma
r_union
id|acpi_operand_object
op_star
id|operand1
comma
r_union
id|acpi_operand_object
op_star
op_star
id|actual_return_desc
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|local_operand1
op_assign
id|operand1
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|return_desc
suffix:semicolon
r_char
op_star
id|new_buf
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_do_concatenate&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the second operand if necessary.  The first operand&n;&t; * determines the type of the second operand, (See the Data Types&n;&t; * section of the ACPI specification.)  Both object types are&n;&t; * guaranteed to be either Integer/String/Buffer by the operand&n;&t; * resolution mechanism.&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand0
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|status
op_assign
id|acpi_ex_convert_to_integer
(paren
id|operand1
comma
op_amp
id|local_operand1
comma
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|status
op_assign
id|acpi_ex_convert_to_string
(paren
id|operand1
comma
op_amp
id|local_operand1
comma
id|ACPI_IMPLICIT_CONVERT_HEX
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|status
op_assign
id|acpi_ex_convert_to_buffer
(paren
id|operand1
comma
op_amp
id|local_operand1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Concat - invalid obj type: %X&bslash;n&quot;
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand0
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_INTERNAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Both operands are now known to be the same object type&n;&t; * (Both are Integer, String, or Buffer), and we can now perform the&n;&t; * concatenation.&n;&t; */
multiline_comment|/*&n;&t; * There are three cases to handle:&n;&t; *&n;&t; * 1) Two Integers concatenated to produce a new Buffer&n;&t; * 2) Two Strings concatenated to produce a new String&n;&t; * 3) Two Buffers concatenated to produce a new Buffer&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand0
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/* Result of two Integers is a Buffer */
multiline_comment|/* Need enough buffer space for two integers */
id|return_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
id|ACPI_MUL_2
(paren
id|acpi_gbl_integer_byte_width
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|new_buf
op_assign
(paren
r_char
op_star
)paren
id|return_desc-&gt;buffer.pointer
suffix:semicolon
multiline_comment|/* Copy the first integer, LSB first */
id|ACPI_MEMCPY
(paren
id|new_buf
comma
op_amp
id|operand0-&gt;integer.value
comma
id|acpi_gbl_integer_byte_width
)paren
suffix:semicolon
multiline_comment|/* Copy the second integer (LSB first) after the first */
id|ACPI_MEMCPY
(paren
id|new_buf
op_plus
id|acpi_gbl_integer_byte_width
comma
op_amp
id|local_operand1-&gt;integer.value
comma
id|acpi_gbl_integer_byte_width
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/* Result of two Strings is a String */
id|return_desc
op_assign
id|acpi_ut_create_string_object
(paren
(paren
id|acpi_size
)paren
id|operand0-&gt;string.length
op_plus
(paren
id|acpi_size
)paren
id|local_operand1-&gt;string.length
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
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|new_buf
op_assign
id|return_desc-&gt;string.pointer
suffix:semicolon
multiline_comment|/* Concatenate the strings */
id|ACPI_STRCPY
(paren
id|new_buf
comma
id|operand0-&gt;string.pointer
)paren
suffix:semicolon
id|ACPI_STRCPY
(paren
id|new_buf
op_plus
id|operand0-&gt;string.length
comma
id|local_operand1-&gt;string.pointer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/* Result of two Buffers is a Buffer */
id|return_desc
op_assign
id|acpi_ut_create_buffer_object
(paren
(paren
id|acpi_size
)paren
id|operand0-&gt;buffer.length
op_plus
(paren
id|acpi_size
)paren
id|local_operand1-&gt;buffer.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|new_buf
op_assign
(paren
r_char
op_star
)paren
id|return_desc-&gt;buffer.pointer
suffix:semicolon
multiline_comment|/* Concatenate the buffers */
id|ACPI_MEMCPY
(paren
id|new_buf
comma
id|operand0-&gt;buffer.pointer
comma
id|operand0-&gt;buffer.length
)paren
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|new_buf
op_plus
id|operand0-&gt;buffer.length
comma
id|local_operand1-&gt;buffer.pointer
comma
id|local_operand1-&gt;buffer.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Invalid object type, should not happen here */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Concatenate - Invalid object type: %X&bslash;n&quot;
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand0
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_INTERNAL
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
op_star
id|actual_return_desc
op_assign
id|return_desc
suffix:semicolon
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|local_operand1
op_ne
id|operand1
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|local_operand1
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_do_math_op&n; *&n; * PARAMETERS:  Opcode              - AML opcode&n; *              Integer0            - Integer operand #0&n; *              Integer1            - Integer operand #1&n; *&n; * RETURN:      Integer result of the operation&n; *&n; * DESCRIPTION: Execute a math AML opcode. The purpose of having all of the&n; *              math functions here is to prevent a lot of pointer dereferencing&n; *              to obtain the operands.&n; *&n; ******************************************************************************/
id|acpi_integer
DECL|function|acpi_ex_do_math_op
id|acpi_ex_do_math_op
(paren
id|u16
id|opcode
comma
id|acpi_integer
id|integer0
comma
id|acpi_integer
id|integer1
)paren
(brace
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_ADD_OP
suffix:colon
multiline_comment|/* Add (Integer0, Integer1, Result) */
r_return
(paren
id|integer0
op_plus
id|integer1
)paren
suffix:semicolon
r_case
id|AML_BIT_AND_OP
suffix:colon
multiline_comment|/* And (Integer0, Integer1, Result) */
r_return
(paren
id|integer0
op_amp
id|integer1
)paren
suffix:semicolon
r_case
id|AML_BIT_NAND_OP
suffix:colon
multiline_comment|/* NAnd (Integer0, Integer1, Result) */
r_return
(paren
op_complement
(paren
id|integer0
op_amp
id|integer1
)paren
)paren
suffix:semicolon
r_case
id|AML_BIT_OR_OP
suffix:colon
multiline_comment|/* Or (Integer0, Integer1, Result) */
r_return
(paren
id|integer0
op_or
id|integer1
)paren
suffix:semicolon
r_case
id|AML_BIT_NOR_OP
suffix:colon
multiline_comment|/* NOr (Integer0, Integer1, Result) */
r_return
(paren
op_complement
(paren
id|integer0
op_or
id|integer1
)paren
)paren
suffix:semicolon
r_case
id|AML_BIT_XOR_OP
suffix:colon
multiline_comment|/* XOr (Integer0, Integer1, Result) */
r_return
(paren
id|integer0
op_xor
id|integer1
)paren
suffix:semicolon
r_case
id|AML_MULTIPLY_OP
suffix:colon
multiline_comment|/* Multiply (Integer0, Integer1, Result) */
r_return
(paren
id|integer0
op_star
id|integer1
)paren
suffix:semicolon
r_case
id|AML_SHIFT_LEFT_OP
suffix:colon
multiline_comment|/* shift_left (Operand, shift_count, Result) */
r_return
(paren
id|integer0
op_lshift
id|integer1
)paren
suffix:semicolon
r_case
id|AML_SHIFT_RIGHT_OP
suffix:colon
multiline_comment|/* shift_right (Operand, shift_count, Result) */
r_return
(paren
id|integer0
op_rshift
id|integer1
)paren
suffix:semicolon
r_case
id|AML_SUBTRACT_OP
suffix:colon
multiline_comment|/* Subtract (Integer0, Integer1, Result) */
r_return
(paren
id|integer0
op_minus
id|integer1
)paren
suffix:semicolon
r_default
suffix:colon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_do_logical_numeric_op&n; *&n; * PARAMETERS:  Opcode              - AML opcode&n; *              Integer0            - Integer operand #0&n; *              Integer1            - Integer operand #1&n; *              logical_result      - TRUE/FALSE result of the operation&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a logical &quot;Numeric&quot; AML opcode. For these Numeric&n; *              operators (LAnd and LOr), both operands must be integers.&n; *&n; *              Note: cleanest machine code seems to be produced by the code&n; *              below, rather than using statements of the form:&n; *                  Result = (Integer0 &amp;&amp; Integer1);&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_do_logical_numeric_op
id|acpi_ex_do_logical_numeric_op
(paren
id|u16
id|opcode
comma
id|acpi_integer
id|integer0
comma
id|acpi_integer
id|integer1
comma
id|u8
op_star
id|logical_result
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u8
id|local_result
op_assign
id|FALSE
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_do_logical_numeric_op&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_LAND_OP
suffix:colon
multiline_comment|/* LAnd (Integer0, Integer1) */
r_if
c_cond
(paren
id|integer0
op_logical_and
id|integer1
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LOR_OP
suffix:colon
multiline_comment|/* LOr (Integer0, Integer1) */
r_if
c_cond
(paren
id|integer0
op_logical_or
id|integer1
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
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
multiline_comment|/* Return the logical result and status */
op_star
id|logical_result
op_assign
id|local_result
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_do_logical_op&n; *&n; * PARAMETERS:  Opcode              - AML opcode&n; *              Operand0            - operand #0&n; *              Operand1            - operand #1&n; *              logical_result      - TRUE/FALSE result of the operation&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a logical AML opcode. The purpose of having all of the&n; *              functions here is to prevent a lot of pointer dereferencing&n; *              to obtain the operands and to simplify the generation of the&n; *              logical value. For the Numeric operators (LAnd and LOr), both&n; *              operands must be integers. For the other logical operators,&n; *              operands can be any combination of Integer/String/Buffer. The&n; *              first operand determines the type to which the second operand&n; *              will be converted.&n; *&n; *              Note: cleanest machine code seems to be produced by the code&n; *              below, rather than using statements of the form:&n; *                  Result = (Operand0 == Operand1);&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_do_logical_op
id|acpi_ex_do_logical_op
(paren
id|u16
id|opcode
comma
r_union
id|acpi_operand_object
op_star
id|operand0
comma
r_union
id|acpi_operand_object
op_star
id|operand1
comma
id|u8
op_star
id|logical_result
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|local_operand1
op_assign
id|operand1
suffix:semicolon
id|acpi_integer
id|integer0
suffix:semicolon
id|acpi_integer
id|integer1
suffix:semicolon
id|u32
id|length0
suffix:semicolon
id|u32
id|length1
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u8
id|local_result
op_assign
id|FALSE
suffix:semicolon
r_int
id|compare
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_do_logical_op&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the second operand if necessary.  The first operand&n;&t; * determines the type of the second operand, (See the Data Types&n;&t; * section of the ACPI 3.0+ specification.)  Both object types are&n;&t; * guaranteed to be either Integer/String/Buffer by the operand&n;&t; * resolution mechanism.&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand0
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|status
op_assign
id|acpi_ex_convert_to_integer
(paren
id|operand1
comma
op_amp
id|local_operand1
comma
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|status
op_assign
id|acpi_ex_convert_to_string
(paren
id|operand1
comma
op_amp
id|local_operand1
comma
id|ACPI_IMPLICIT_CONVERT_HEX
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|status
op_assign
id|acpi_ex_convert_to_buffer
(paren
id|operand1
comma
op_amp
id|local_operand1
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
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Two cases: 1) Both Integers, 2) Both Strings or Buffers&n;&t; */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand0
)paren
op_eq
id|ACPI_TYPE_INTEGER
)paren
(brace
multiline_comment|/*&n;&t;&t; * 1) Both operands are of type integer&n;&t;&t; *    Note: local_operand1 may have changed above&n;&t;&t; */
id|integer0
op_assign
id|operand0-&gt;integer.value
suffix:semicolon
id|integer1
op_assign
id|local_operand1-&gt;integer.value
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_LEQUAL_OP
suffix:colon
multiline_comment|/* LEqual (Operand0, Operand1) */
r_if
c_cond
(paren
id|integer0
op_eq
id|integer1
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LGREATER_OP
suffix:colon
multiline_comment|/* LGreater (Operand0, Operand1) */
r_if
c_cond
(paren
id|integer0
OG
id|integer1
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LLESS_OP
suffix:colon
multiline_comment|/* LLess (Operand0, Operand1) */
r_if
c_cond
(paren
id|integer0
OL
id|integer1
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
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
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * 2) Both operands are Strings or both are Buffers&n;&t;&t; *    Note: Code below takes advantage of common Buffer/String&n;&t;&t; *          object fields. local_operand1 may have changed above&n;&t;&t; */
id|length0
op_assign
id|operand0-&gt;buffer.length
suffix:semicolon
id|length1
op_assign
id|local_operand1-&gt;buffer.length
suffix:semicolon
multiline_comment|/* Lexicographic compare: compare the data bytes */
id|compare
op_assign
id|ACPI_STRNCMP
(paren
(paren
r_const
r_char
op_star
)paren
id|operand0-&gt;buffer.pointer
comma
(paren
r_const
r_char
op_star
)paren
id|local_operand1-&gt;buffer.pointer
comma
(paren
id|length0
OG
id|length1
)paren
ques
c_cond
id|length1
suffix:colon
id|length0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_LEQUAL_OP
suffix:colon
multiline_comment|/* LEqual (Operand0, Operand1) */
multiline_comment|/* Length and all bytes must be equal */
r_if
c_cond
(paren
(paren
id|length0
op_eq
id|length1
)paren
op_logical_and
(paren
id|compare
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* Length and all bytes match ==&gt; TRUE */
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LGREATER_OP
suffix:colon
multiline_comment|/* LGreater (Operand0, Operand1) */
r_if
c_cond
(paren
id|compare
OG
l_int|0
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/* TRUE */
)brace
r_if
c_cond
(paren
id|compare
OL
l_int|0
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/* FALSE */
)brace
multiline_comment|/* Bytes match (to shortest length), compare lengths */
r_if
c_cond
(paren
id|length0
OG
id|length1
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LLESS_OP
suffix:colon
multiline_comment|/* LLess (Operand0, Operand1) */
r_if
c_cond
(paren
id|compare
OG
l_int|0
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/* FALSE */
)brace
r_if
c_cond
(paren
id|compare
OL
l_int|0
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/* TRUE */
)brace
multiline_comment|/* Bytes match (to shortest length), compare lengths */
r_if
c_cond
(paren
id|length0
OL
id|length1
)paren
(brace
id|local_result
op_assign
id|TRUE
suffix:semicolon
)brace
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
)brace
id|cleanup
suffix:colon
multiline_comment|/* New object was created if implicit conversion performed - delete */
r_if
c_cond
(paren
id|local_operand1
op_ne
id|operand1
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|local_operand1
)paren
suffix:semicolon
)brace
multiline_comment|/* Return the logical result and status */
op_star
id|logical_result
op_assign
id|local_result
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
