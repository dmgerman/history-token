multiline_comment|/******************************************************************************&n; *&n; * Module Name: exoparg2 - AML execution - opcodes with 2 arguments&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;amlcode.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exoparg2&quot;
)paren
multiline_comment|/*!&n; * Naming convention for AML interpreter execution routines.&n; *&n; * The routines that begin execution of AML opcodes are named with a common&n; * convention based upon the number of arguments, the number of target operands,&n; * and whether or not a value is returned:&n; *&n; *      AcpiExOpcode_xA_yT_zR&n; *&n; * Where:&n; *&n; * xA - ARGUMENTS:    The number of arguments (input operands) that are&n; *                    required for this opcode type (1 through 6 args).&n; * yT - TARGETS:      The number of targets (output operands) that are required&n; *                    for this opcode type (0, 1, or 2 targets).&n; * zR - RETURN VALUE: Indicates whether this opcode type returns a value&n; *                    as the function return (0 or 1).&n; *&n; * The AcpiExOpcode* functions are called via the Dispatcher component with&n; * fully resolved operands.&n;!*/
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_opcode_2A_0T_0R&n; *&n; * PARAMETERS:  walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute opcode with two arguments, no target, and no return&n; *              value.&n; *&n; * ALLOCATION:  Deletes both operands&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_2A_0T_0R
id|acpi_ex_opcode_2A_0T_0R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_operand_object
op_star
op_star
id|operand
op_assign
op_amp
id|walk_state-&gt;operands
(braket
l_int|0
)braket
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;ex_opcode_2A_0T_0R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/* Examine the opcode */
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_NOTIFY_OP
suffix:colon
multiline_comment|/* Notify (notify_object, notify_value) */
multiline_comment|/* The first operand is a namespace node */
id|node
op_assign
(paren
id|acpi_namespace_node
op_star
)paren
id|operand
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Notifies allowed on this object? */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ev_is_notify_object
(paren
id|node
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unexpected notify object type [%s]&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|node-&gt;type
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Dispatch the notify to the appropriate handler&n;&t;&t; * NOTE: the request is queued for execution after this method&n;&t;&t; * completes.  The notify handlers are NOT invoked synchronously&n;&t;&t; * from this thread -- because handlers may in turn run other&n;&t;&t; * control methods.&n;&t;&t; */
id|status
op_assign
id|acpi_ev_queue_notify_request
(paren
id|node
comma
(paren
id|u32
)paren
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ex_opcode_2A_0T_0R: Unknown opcode %X&bslash;n&quot;
comma
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_BAD_OPCODE
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_opcode_2A_2T_1R&n; *&n; * PARAMETERS:  walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a dyadic operator (2 operands) with 2 output targets&n; *              and one implicit return value.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_2A_2T_1R
id|acpi_ex_opcode_2A_2T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_operand_object
op_star
op_star
id|operand
op_assign
op_amp
id|walk_state-&gt;operands
(braket
l_int|0
)braket
suffix:semicolon
id|acpi_operand_object
op_star
id|return_desc1
op_assign
l_int|NULL
suffix:semicolon
id|acpi_operand_object
op_star
id|return_desc2
op_assign
l_int|NULL
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;ex_opcode_2A_2T_1R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Execute the opcode&n;&t; */
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_DIVIDE_OP
suffix:colon
multiline_comment|/* Divide (Dividend, Divisor, remainder_result quotient_result) */
id|return_desc1
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
id|return_desc1
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
id|return_desc2
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
id|return_desc2
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
multiline_comment|/* Quotient to return_desc1, remainder to return_desc2 */
id|status
op_assign
id|acpi_ut_divide
(paren
op_amp
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
comma
op_amp
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
comma
op_amp
id|return_desc1-&gt;integer.value
comma
op_amp
id|return_desc2-&gt;integer.value
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
r_goto
id|cleanup
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ex_opcode_2A_2T_1R: Unknown opcode %X&bslash;n&quot;
comma
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_BAD_OPCODE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Store the results to the target reference operands */
id|status
op_assign
id|acpi_ex_store
(paren
id|return_desc2
comma
id|operand
(braket
l_int|2
)braket
comma
id|walk_state
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
r_goto
id|cleanup
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ex_store
(paren
id|return_desc1
comma
id|operand
(braket
l_int|3
)braket
comma
id|walk_state
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
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Return the remainder */
id|walk_state-&gt;result_obj
op_assign
id|return_desc1
suffix:semicolon
id|cleanup
suffix:colon
multiline_comment|/*&n;&t; * Since the remainder is not returned indirectly, remove a reference to&n;&t; * it. Only the quotient is returned indirectly.&n;&t; */
id|acpi_ut_remove_reference
(paren
id|return_desc2
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
multiline_comment|/* Delete the return object */
id|acpi_ut_remove_reference
(paren
id|return_desc1
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_opcode_2A_1T_1R&n; *&n; * PARAMETERS:  walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute opcode with two arguments, one target, and a return&n; *              value.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_2A_1T_1R
id|acpi_ex_opcode_2A_1T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_operand_object
op_star
op_star
id|operand
op_assign
op_amp
id|walk_state-&gt;operands
(braket
l_int|0
)braket
suffix:semicolon
id|acpi_operand_object
op_star
id|return_desc
op_assign
l_int|NULL
suffix:semicolon
id|acpi_operand_object
op_star
id|temp_desc
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|index
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_size
id|length
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;ex_opcode_2A_1T_1R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Execute the opcode&n;&t; */
r_if
c_cond
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_MATH
)paren
(brace
multiline_comment|/* All simple math opcodes (add, etc.) */
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
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|return_desc-&gt;integer.value
op_assign
id|acpi_ex_do_math_op
(paren
id|walk_state-&gt;opcode
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
comma
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
)paren
suffix:semicolon
r_goto
id|store_result_to_target
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_MOD_OP
suffix:colon
multiline_comment|/* Mod (Dividend, Divisor, remainder_result (ACPI 2.0) */
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
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* return_desc will contain the remainder */
id|status
op_assign
id|acpi_ut_divide
(paren
op_amp
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
comma
op_amp
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
comma
l_int|NULL
comma
op_amp
id|return_desc-&gt;integer.value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_CONCAT_OP
suffix:colon
multiline_comment|/* Concatenate (Data1, Data2, Result) */
multiline_comment|/*&n;&t;&t; * Convert the second operand if necessary.  The first operand&n;&t;&t; * determines the type of the second operand, (See the Data Types&n;&t;&t; * section of the ACPI specification.)  Both object types are&n;&t;&t; * guaranteed to be either Integer/String/Buffer by the operand&n;&t;&t; * resolution mechanism above.&n;&t;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand
(braket
l_int|0
)braket
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
id|operand
(braket
l_int|1
)braket
comma
op_amp
id|temp_desc
comma
id|walk_state
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
id|operand
(braket
l_int|1
)braket
comma
op_amp
id|temp_desc
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
id|status
op_assign
id|acpi_ex_convert_to_buffer
(paren
id|operand
(braket
l_int|1
)braket
comma
op_amp
id|temp_desc
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
multiline_comment|/*&n;&t;&t; * Both operands are now known to be the same object type&n;&t;&t; * (Both are Integer, String, or Buffer), and we can now perform the&n;&t;&t; * concatenation.&n;&t;&t; */
id|status
op_assign
id|acpi_ex_do_concatenate
(paren
id|operand
(braket
l_int|0
)braket
comma
id|temp_desc
comma
op_amp
id|return_desc
comma
id|walk_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp_desc
op_ne
id|operand
(braket
l_int|1
)braket
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|temp_desc
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_TO_STRING_OP
suffix:colon
multiline_comment|/* to_string (Buffer, Length, Result) (ACPI 2.0) */
multiline_comment|/*&n;&t;&t; * Input object is guaranteed to be a buffer at this point (it may have&n;&t;&t; * been converted.)  Copy the raw buffer data to a new object of type String.&n;&t;&t; */
multiline_comment|/* Get the length of the new string */
id|length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Handle optional length value */
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
op_assign
id|ACPI_INTEGER_MAX
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|length
OL
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|buffer.length
)paren
op_logical_and
(paren
id|length
OL
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
)paren
op_logical_and
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|buffer.pointer
(braket
id|length
)braket
)paren
)paren
(brace
id|length
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
OG
id|ACPI_MAX_STRING_CONVERSION
)paren
(brace
id|status
op_assign
id|AE_AML_STRING_LIMIT
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Create the internal return object */
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
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Allocate a new string buffer (Length + 1 for null terminator) */
id|return_desc-&gt;string.pointer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc-&gt;string.pointer
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
multiline_comment|/* Copy the raw buffer data with no transform */
id|ACPI_MEMCPY
(paren
id|return_desc-&gt;string.pointer
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|buffer.pointer
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* Set the string length */
id|return_desc-&gt;string.length
op_assign
(paren
id|u32
)paren
id|length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_CONCAT_RES_OP
suffix:colon
multiline_comment|/* concatenate_res_template (Buffer, Buffer, Result) (ACPI 2.0) */
id|status
op_assign
id|acpi_ex_concat_template
(paren
id|operand
(braket
l_int|0
)braket
comma
id|operand
(braket
l_int|1
)braket
comma
op_amp
id|return_desc
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INDEX_OP
suffix:colon
multiline_comment|/* Index (Source Index Result) */
multiline_comment|/* Create the internal return object */
id|return_desc
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
id|index
op_assign
(paren
id|u32
)paren
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
multiline_comment|/*&n;&t;&t; * At this point, the Source operand is either a Package or a Buffer&n;&t;&t; */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand
(braket
l_int|0
)braket
)paren
op_eq
id|ACPI_TYPE_PACKAGE
)paren
(brace
multiline_comment|/* Object to be indexed is a Package */
r_if
c_cond
(paren
id|index
op_ge
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|package.count
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Index value (%X) beyond package end (%X)&bslash;n&quot;
comma
id|index
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|package.count
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_PACKAGE_LIMIT
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|return_desc-&gt;reference.target_type
op_assign
id|ACPI_TYPE_PACKAGE
suffix:semicolon
id|return_desc-&gt;reference.object
op_assign
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|package.elements
(braket
id|index
)braket
suffix:semicolon
id|return_desc-&gt;reference.where
op_assign
op_amp
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|package.elements
(braket
id|index
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Object to be indexed is a Buffer */
r_if
c_cond
(paren
id|index
op_ge
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|buffer.length
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Index value (%X) beyond end of buffer (%X)&bslash;n&quot;
comma
id|index
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|buffer.length
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_BUFFER_LIMIT
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|return_desc-&gt;reference.target_type
op_assign
id|ACPI_TYPE_BUFFER_FIELD
suffix:semicolon
id|return_desc-&gt;reference.object
op_assign
id|operand
(braket
l_int|0
)braket
suffix:semicolon
)brace
multiline_comment|/* Complete the Index reference object */
id|return_desc-&gt;reference.opcode
op_assign
id|AML_INDEX_OP
suffix:semicolon
id|return_desc-&gt;reference.offset
op_assign
id|index
suffix:semicolon
multiline_comment|/* Store the reference to the Target */
id|status
op_assign
id|acpi_ex_store
(paren
id|return_desc
comma
id|operand
(braket
l_int|2
)braket
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* Return the reference */
id|walk_state-&gt;result_obj
op_assign
id|return_desc
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ex_opcode_2A_1T_1R: Unknown opcode %X&bslash;n&quot;
comma
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_BAD_OPCODE
suffix:semicolon
r_break
suffix:semicolon
)brace
id|store_result_to_target
suffix:colon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Store the result of the operation (which is now in return_desc) into&n;&t;&t; * the Target descriptor.&n;&t;&t; */
id|status
op_assign
id|acpi_ex_store
(paren
id|return_desc
comma
id|operand
(braket
l_int|2
)braket
comma
id|walk_state
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
r_goto
id|cleanup
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|walk_state-&gt;result_obj
)paren
(brace
id|walk_state-&gt;result_obj
op_assign
id|return_desc
suffix:semicolon
)brace
)brace
id|cleanup
suffix:colon
multiline_comment|/* Delete return object on error */
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
id|return_desc
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_opcode_2A_0T_1R&n; *&n; * PARAMETERS:  walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute opcode with 2 arguments, no target, and a return value&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_2A_0T_1R
id|acpi_ex_opcode_2A_0T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_operand_object
op_star
op_star
id|operand
op_assign
op_amp
id|walk_state-&gt;operands
(braket
l_int|0
)braket
suffix:semicolon
id|acpi_operand_object
op_star
id|return_desc
op_assign
l_int|NULL
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u8
id|logical_result
op_assign
id|FALSE
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;ex_opcode_2A_0T_1R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/* Create the internal return object */
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
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Execute the Opcode&n;&t; */
r_if
c_cond
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_LOGICAL
)paren
multiline_comment|/* logical_op (Operand0, Operand1) */
(brace
id|logical_result
op_assign
id|acpi_ex_do_logical_op
(paren
id|walk_state-&gt;opcode
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
comma
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
)paren
suffix:semicolon
r_goto
id|store_logical_result
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_ACQUIRE_OP
suffix:colon
multiline_comment|/* Acquire (mutex_object, Timeout) */
id|status
op_assign
id|acpi_ex_acquire_mutex
(paren
id|operand
(braket
l_int|1
)braket
comma
id|operand
(braket
l_int|0
)braket
comma
id|walk_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|AE_TIME
)paren
(brace
id|logical_result
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/* TRUE = Acquire timed out */
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_WAIT_OP
suffix:colon
multiline_comment|/* Wait (event_object, Timeout) */
id|status
op_assign
id|acpi_ex_system_wait_event
(paren
id|operand
(braket
l_int|1
)braket
comma
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|AE_TIME
)paren
(brace
id|logical_result
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/* TRUE, Wait timed out */
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ex_opcode_2A_0T_1R: Unknown opcode %X&bslash;n&quot;
comma
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_BAD_OPCODE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|store_logical_result
suffix:colon
multiline_comment|/*&n;&t; * Set return value to according to logical_result. logical TRUE (all ones)&n;&t; * Default is FALSE (zero)&n;&t; */
r_if
c_cond
(paren
id|logical_result
)paren
(brace
id|return_desc-&gt;integer.value
op_assign
id|ACPI_INTEGER_MAX
suffix:semicolon
)brace
id|walk_state-&gt;result_obj
op_assign
id|return_desc
suffix:semicolon
id|cleanup
suffix:colon
multiline_comment|/* Delete return object on error */
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
id|return_desc
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
