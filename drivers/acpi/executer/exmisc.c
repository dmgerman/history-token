multiline_comment|/******************************************************************************&n; *&n; * Module Name: exmisc - ACPI AML (p-code) execution - specific opcodes&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown Reference subtype %X&bslash;n&quot;
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid descriptor type %X in %p&bslash;n&quot;
comma
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
comma
id|obj_desc
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_concat_template&n; *&n; * PARAMETERS:  *obj_desc           - Object to be converted.  Must be an&n; *                                    Integer, Buffer, or String&n; *              walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Concatenate two resource templates&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_concat_template
id|acpi_ex_concat_template
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc1
comma
r_union
id|acpi_operand_object
op_star
id|obj_desc2
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
id|obj_desc1
)paren
suffix:semicolon
id|end_tag2
op_assign
id|acpi_ut_get_resource_end_tag
(paren
id|obj_desc2
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
id|obj_desc1-&gt;buffer.pointer
)paren
suffix:semicolon
id|length2
op_assign
id|ACPI_PTR_DIFF
(paren
id|end_tag2
comma
id|obj_desc2-&gt;buffer.pointer
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
id|obj_desc1-&gt;buffer.pointer
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
id|obj_desc2-&gt;buffer.pointer
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_do_concatenate&n; *&n; * PARAMETERS:  obj_desc1           - First source object&n; *              obj_desc2           - Second source object&n; *              actual_return_desc  - Where to place the return object&n; *              walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Concatenate two objects OF THE SAME TYPE.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_do_concatenate
id|acpi_ex_do_concatenate
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc1
comma
r_union
id|acpi_operand_object
op_star
id|obj_desc2
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
id|acpi_status
id|status
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|acpi_integer
id|this_integer
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
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * There are three cases to handle:&n;&t; *&n;&t; * 1) Two Integers concatenated to produce a new Buffer&n;&t; * 2) Two Strings concatenated to produce a new String&n;&t; * 3) Two Buffers concatenated to produce a new Buffer&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc1
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
id|acpi_gbl_integer_byte_width
op_star
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
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
multiline_comment|/* Convert the first integer */
id|this_integer
op_assign
id|obj_desc1-&gt;integer.value
suffix:semicolon
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
r_char
)paren
id|this_integer
suffix:semicolon
id|this_integer
op_rshift_assign
l_int|8
suffix:semicolon
)brace
multiline_comment|/* Convert the second integer */
id|this_integer
op_assign
id|obj_desc2-&gt;integer.value
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
(paren
id|ACPI_MUL_2
(paren
id|acpi_gbl_integer_byte_width
)paren
)paren
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
r_char
)paren
id|this_integer
suffix:semicolon
id|this_integer
op_rshift_assign
l_int|8
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/* Result of two Strings is a String */
id|return_desc
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
id|return_desc
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Operand0 is string  */
id|new_buf
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|acpi_size
)paren
id|obj_desc1-&gt;string.length
op_plus
(paren
id|acpi_size
)paren
id|obj_desc2-&gt;string.length
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
l_string|&quot;ex_do_concatenate: String allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Concatenate the strings */
id|ACPI_STRCPY
(paren
id|new_buf
comma
id|obj_desc1-&gt;string.pointer
)paren
suffix:semicolon
id|ACPI_STRCPY
(paren
id|new_buf
op_plus
id|obj_desc1-&gt;string.length
comma
id|obj_desc2-&gt;string.pointer
)paren
suffix:semicolon
multiline_comment|/* Complete the String object initialization */
id|return_desc-&gt;string.pointer
op_assign
id|new_buf
suffix:semicolon
id|return_desc-&gt;string.length
op_assign
id|obj_desc1-&gt;string.length
op_plus
id|obj_desc2-&gt;string.length
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
id|obj_desc1-&gt;buffer.length
op_plus
(paren
id|acpi_size
)paren
id|obj_desc2-&gt;buffer.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
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
id|obj_desc1-&gt;buffer.pointer
comma
id|obj_desc1-&gt;buffer.length
)paren
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|new_buf
op_plus
id|obj_desc1-&gt;buffer.length
comma
id|obj_desc2-&gt;buffer.pointer
comma
id|obj_desc2-&gt;buffer.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Invalid object type, should not happen here */
id|status
op_assign
id|AE_AML_INTERNAL
suffix:semicolon
id|return_desc
op_assign
l_int|NULL
suffix:semicolon
)brace
op_star
id|actual_return_desc
op_assign
id|return_desc
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|acpi_ut_remove_reference
(paren
id|return_desc
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_do_math_op&n; *&n; * PARAMETERS:  Opcode              - AML opcode&n; *              Operand0            - Integer operand #0&n; *              Operand1            - Integer operand #1&n; *&n; * RETURN:      Integer result of the operation&n; *&n; * DESCRIPTION: Execute a math AML opcode. The purpose of having all of the&n; *              math functions here is to prevent a lot of pointer dereferencing&n; *              to obtain the operands.&n; *&n; ******************************************************************************/
id|acpi_integer
DECL|function|acpi_ex_do_math_op
id|acpi_ex_do_math_op
(paren
id|u16
id|opcode
comma
id|acpi_integer
id|operand0
comma
id|acpi_integer
id|operand1
)paren
(brace
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_ADD_OP
suffix:colon
multiline_comment|/* Add (Operand0, Operand1, Result) */
r_return
(paren
id|operand0
op_plus
id|operand1
)paren
suffix:semicolon
r_case
id|AML_BIT_AND_OP
suffix:colon
multiline_comment|/* And (Operand0, Operand1, Result) */
r_return
(paren
id|operand0
op_amp
id|operand1
)paren
suffix:semicolon
r_case
id|AML_BIT_NAND_OP
suffix:colon
multiline_comment|/* NAnd (Operand0, Operand1, Result) */
r_return
(paren
op_complement
(paren
id|operand0
op_amp
id|operand1
)paren
)paren
suffix:semicolon
r_case
id|AML_BIT_OR_OP
suffix:colon
multiline_comment|/* Or (Operand0, Operand1, Result) */
r_return
(paren
id|operand0
op_or
id|operand1
)paren
suffix:semicolon
r_case
id|AML_BIT_NOR_OP
suffix:colon
multiline_comment|/* NOr (Operand0, Operand1, Result) */
r_return
(paren
op_complement
(paren
id|operand0
op_or
id|operand1
)paren
)paren
suffix:semicolon
r_case
id|AML_BIT_XOR_OP
suffix:colon
multiline_comment|/* XOr (Operand0, Operand1, Result) */
r_return
(paren
id|operand0
op_xor
id|operand1
)paren
suffix:semicolon
r_case
id|AML_MULTIPLY_OP
suffix:colon
multiline_comment|/* Multiply (Operand0, Operand1, Result) */
r_return
(paren
id|operand0
op_star
id|operand1
)paren
suffix:semicolon
r_case
id|AML_SHIFT_LEFT_OP
suffix:colon
multiline_comment|/* shift_left (Operand, shift_count, Result) */
r_return
(paren
id|operand0
op_lshift
id|operand1
)paren
suffix:semicolon
r_case
id|AML_SHIFT_RIGHT_OP
suffix:colon
multiline_comment|/* shift_right (Operand, shift_count, Result) */
r_return
(paren
id|operand0
op_rshift
id|operand1
)paren
suffix:semicolon
r_case
id|AML_SUBTRACT_OP
suffix:colon
multiline_comment|/* Subtract (Operand0, Operand1, Result) */
r_return
(paren
id|operand0
op_minus
id|operand1
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_do_logical_op&n; *&n; * PARAMETERS:  Opcode              - AML opcode&n; *              Operand0            - Integer operand #0&n; *              Operand1            - Integer operand #1&n; *&n; * RETURN:      TRUE/FALSE result of the operation&n; *&n; * DESCRIPTION: Execute a logical AML opcode. The purpose of having all of the&n; *              functions here is to prevent a lot of pointer dereferencing&n; *              to obtain the operands and to simplify the generation of the&n; *              logical value.&n; *&n; *              Note: cleanest machine code seems to be produced by the code&n; *              below, rather than using statements of the form:&n; *                  Result = (Operand0 == Operand1);&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ex_do_logical_op
id|acpi_ex_do_logical_op
(paren
id|u16
id|opcode
comma
id|acpi_integer
id|operand0
comma
id|acpi_integer
id|operand1
)paren
(brace
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_LAND_OP
suffix:colon
multiline_comment|/* LAnd (Operand0, Operand1) */
r_if
c_cond
(paren
id|operand0
op_logical_and
id|operand1
)paren
(brace
r_return
(paren
id|TRUE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LEQUAL_OP
suffix:colon
multiline_comment|/* LEqual (Operand0, Operand1) */
r_if
c_cond
(paren
id|operand0
op_eq
id|operand1
)paren
(brace
r_return
(paren
id|TRUE
)paren
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
id|operand0
OG
id|operand1
)paren
(brace
r_return
(paren
id|TRUE
)paren
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
id|operand0
OL
id|operand1
)paren
(brace
r_return
(paren
id|TRUE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LOR_OP
suffix:colon
multiline_comment|/* LOr (Operand0, Operand1) */
r_if
c_cond
(paren
id|operand0
op_logical_or
id|operand1
)paren
(brace
r_return
(paren
id|TRUE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
eof
