multiline_comment|/******************************************************************************&n; *&n; * Module Name: exoparg3 - AML execution - opcodes with 3 arguments&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exoparg3&quot;
)paren
multiline_comment|/*!&n; * Naming convention for AML interpreter execution routines.&n; *&n; * The routines that begin execution of AML opcodes are named with a common&n; * convention based upon the number of arguments, the number of target operands,&n; * and whether or not a value is returned:&n; *&n; *      AcpiExOpcode_xA_yT_zR&n; *&n; * Where:&n; *&n; * xA - ARGUMENTS:    The number of arguments (input operands) that are&n; *                    required for this opcode type (1 through 6 args).&n; * yT - TARGETS:      The number of targets (output operands) that are required&n; *                    for this opcode type (0, 1, or 2 targets).&n; * zR - RETURN VALUE: Indicates whether this opcode type returns a value&n; *                    as the function return (0 or 1).&n; *&n; * The AcpiExOpcode* functions are called via the Dispatcher component with&n; * fully resolved operands.&n;!*/
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_opcode_3A_0T_0R&n; *&n; * PARAMETERS:  walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute Triadic operator (3 operands)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_3A_0T_0R
id|acpi_ex_opcode_3A_0T_0R
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
id|acpi_signal_fatal_info
op_star
id|fatal
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;ex_opcode_3A_0T_0R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_FATAL_OP
suffix:colon
multiline_comment|/* Fatal (fatal_type fatal_code fatal_arg)   */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;fatal_op: Type %X Code %X Arg %X &lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&bslash;n&quot;
comma
(paren
id|u32
)paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
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
comma
(paren
id|u32
)paren
id|operand
(braket
l_int|2
)braket
op_member_access_from_pointer
id|integer.value
)paren
)paren
suffix:semicolon
id|fatal
op_assign
id|ACPI_MEM_ALLOCATE
(paren
r_sizeof
(paren
id|acpi_signal_fatal_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fatal
)paren
(brace
id|fatal-&gt;type
op_assign
(paren
id|u32
)paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
id|fatal-&gt;code
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
id|fatal-&gt;argument
op_assign
(paren
id|u32
)paren
id|operand
(braket
l_int|2
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Always signal the OS!&n;&t;&t; */
id|status
op_assign
id|acpi_os_signal
(paren
id|ACPI_SIGNAL_FATAL
comma
id|fatal
)paren
suffix:semicolon
multiline_comment|/* Might return while OS is shutting down, just continue */
id|ACPI_MEM_FREE
(paren
id|fatal
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ex_opcode_3A_0T_0R: Unknown opcode %X&bslash;n&quot;
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
id|cleanup
suffix:colon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_opcode_3A_1T_1R&n; *&n; * PARAMETERS:  walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute Triadic operator (3 operands)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_3A_1T_1R
id|acpi_ex_opcode_3A_1T_1R
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
r_char
op_star
id|buffer
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_native_uint
id|index
suffix:semicolon
id|acpi_size
id|length
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;ex_opcode_3A_1T_1R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_MID_OP
suffix:colon
multiline_comment|/* Mid  (Source[0], Index[1], Length[2], Result[3]) */
multiline_comment|/*&n;&t;&t; * Create the return object.  The Source operand is guaranteed to be&n;&t;&t; * either a String or a Buffer, so just use its type.&n;&t;&t; */
id|return_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|operand
(braket
l_int|0
)braket
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
multiline_comment|/* Get the Integer values from the objects */
id|index
op_assign
(paren
id|acpi_native_uint
)paren
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
id|length
op_assign
(paren
id|acpi_size
)paren
id|operand
(braket
l_int|2
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the index is beyond the length of the String/Buffer, or if the&n;&t;&t; * requested length is zero, return a zero-length String/Buffer&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|index
OL
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|string.length
)paren
op_logical_and
(paren
id|length
OG
l_int|0
)paren
)paren
(brace
multiline_comment|/* Truncate request if larger than the actual String/Buffer */
r_if
c_cond
(paren
(paren
id|index
op_plus
id|length
)paren
OG
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|string.length
)paren
(brace
id|length
op_assign
(paren
id|acpi_size
)paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|string.length
op_minus
id|index
suffix:semicolon
)brace
multiline_comment|/* Allocate a new buffer for the String/Buffer */
id|buffer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|acpi_size
)paren
id|length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
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
multiline_comment|/* Copy the portion requested */
id|ACPI_MEMCPY
(paren
id|buffer
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|string.pointer
op_plus
id|index
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* Set the length of the new String/Buffer */
id|return_desc-&gt;string.pointer
op_assign
id|buffer
suffix:semicolon
id|return_desc-&gt;string.length
op_assign
(paren
id|u32
)paren
id|length
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_ex_opcode_3A_0T_0R: Unknown opcode %X&bslash;n&quot;
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
multiline_comment|/* Store the result in the target */
id|status
op_assign
id|acpi_ex_store
(paren
id|return_desc
comma
id|operand
(braket
l_int|3
)braket
comma
id|walk_state
)paren
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
multiline_comment|/* Set the return object and exit */
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
