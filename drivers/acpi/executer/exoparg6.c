multiline_comment|/******************************************************************************&n; *&n; * Module Name: exoparg6 - AML execution - opcodes with 6 arguments&n; *              $Revision: 4 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|MODULE_NAME
(paren
l_string|&quot;exoparg6&quot;
)paren
multiline_comment|/*!&n; * Naming convention for AML interpreter execution routines.&n; *&n; * The routines that begin execution of AML opcodes are named with a common&n; * convention based upon the number of arguments, the number of target operands,&n; * and whether or not a value is returned:&n; *&n; *      AcpiExOpcode_xA_yT_zR&n; *&n; * Where:&n; *&n; * xA - ARGUMENTS:    The number of arguments (input operands) that are&n; *                    required for this opcode type (1 through 6 args).&n; * yT - TARGETS:      The number of targets (output operands) that are required&n; *                    for this opcode type (0, 1, or 2 targets).&n; * zR - RETURN VALUE: Indicates whether this opcode type returns a value&n; *                    as the function return (0 or 1).&n; *&n; * The AcpiExOpcode* functions are called via the Dispatcher component with&n; * fully resolved operands.&n;!*/
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_do_match&n; *&n; * PARAMETERS:  Match_op        - The AML match operand&n; *              Package_value   - Value from the target package&n; *              Match_value     - Value to be matched&n; *&n; * RETURN:      TRUE if the match is successful, FALSE otherwise&n; *&n; * DESCRIPTION: Implements the low-level match for the ASL Match operator&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ex_do_match
id|acpi_ex_do_match
(paren
id|u32
id|match_op
comma
id|acpi_integer
id|package_value
comma
id|acpi_integer
id|match_value
)paren
(brace
r_switch
c_cond
(paren
id|match_op
)paren
(brace
r_case
id|MATCH_MTR
suffix:colon
multiline_comment|/* always true */
r_break
suffix:semicolon
r_case
id|MATCH_MEQ
suffix:colon
multiline_comment|/* true if equal   */
r_if
c_cond
(paren
id|package_value
op_ne
id|match_value
)paren
(brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MATCH_MLE
suffix:colon
multiline_comment|/* true if less than or equal  */
r_if
c_cond
(paren
id|package_value
OG
id|match_value
)paren
(brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MATCH_MLT
suffix:colon
multiline_comment|/* true if less than   */
r_if
c_cond
(paren
id|package_value
op_ge
id|match_value
)paren
(brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MATCH_MGE
suffix:colon
multiline_comment|/* true if greater than or equal   */
r_if
c_cond
(paren
id|package_value
OL
id|match_value
)paren
(brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MATCH_MGT
suffix:colon
multiline_comment|/* true if greater than    */
r_if
c_cond
(paren
id|package_value
op_le
id|match_value
)paren
(brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* undefined   */
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
r_return
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_opcode_6A_0T_1R&n; *&n; * PARAMETERS:  Walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute opcode with 6 arguments, no target, and a return value&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_6A_0T_1R
id|acpi_ex_opcode_6A_0T_1R
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
id|u32
id|index
suffix:semicolon
id|acpi_operand_object
op_star
id|this_element
suffix:semicolon
id|FUNCTION_TRACE_STR
(paren
l_string|&quot;Ex_opcode_6A_0T_1R&quot;
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
id|AML_MATCH_OP
suffix:colon
multiline_comment|/*&n;&t;&t; * Match (Search_package[0], Match_op1[1], Match_object1[2],&n;&t;&t; *                          Match_op2[3], Match_object2[4], Start_index[5])&n;&t;&t; */
multiline_comment|/* Validate match comparison sub-opcodes */
r_if
c_cond
(paren
(paren
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|integer.value
OG
id|MAX_MATCH_OPERATOR
)paren
op_logical_or
(paren
id|operand
(braket
l_int|3
)braket
op_member_access_from_pointer
id|integer.value
OG
id|MAX_MATCH_OPERATOR
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;operation encoding out of range&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_VALUE
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
l_int|5
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ge
(paren
id|u32
)paren
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
l_string|&quot;Index beyond package end&bslash;n&quot;
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
multiline_comment|/* Default return value if no match found */
id|return_desc-&gt;integer.value
op_assign
id|ACPI_INTEGER_MAX
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Examine each element until a match is found.  Within the loop,&n;&t;&t; * &quot;continue&quot; signifies that the current element does not match&n;&t;&t; * and the next should be examined.&n;&t;&t; * Upon finding a match, the loop will terminate via &quot;break&quot; at&n;&t;&t; * the bottom.  If it terminates &quot;normally&quot;, Match_value will be -1&n;&t;&t; * (its initial value) indicating that no match was found.  When&n;&t;&t; * returned as a Number, this will produce the Ones value as specified.&n;&t;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|index
OL
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|package.count
suffix:semicolon
id|index
op_increment
)paren
(brace
id|this_element
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
multiline_comment|/*&n;&t;&t;&t; * Treat any NULL or non-numeric elements as non-matching.&n;&t;&t;&t; * TBD [Unhandled] - if an element is a Name,&n;&t;&t;&t; *      should we examine its value?&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|this_element
op_logical_or
id|this_element-&gt;common.type
op_ne
id|ACPI_TYPE_INTEGER
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Within these switch statements:&n;&t;&t;&t; *      &quot;break&quot; (exit from the switch) signifies a match;&n;&t;&t;&t; *      &quot;continue&quot; (proceed to next iteration of enclosing&n;&t;&t;&t; *          &quot;for&quot; loop) signifies a non-match.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ex_do_match
(paren
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
id|this_element-&gt;integer.value
comma
id|operand
(braket
l_int|2
)braket
op_member_access_from_pointer
id|integer.value
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_ex_do_match
(paren
(paren
id|u32
)paren
id|operand
(braket
l_int|3
)braket
op_member_access_from_pointer
id|integer.value
comma
id|this_element-&gt;integer.value
comma
id|operand
(braket
l_int|4
)braket
op_member_access_from_pointer
id|integer.value
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/* Match found: Index is the return value */
id|return_desc-&gt;integer.value
op_assign
id|index
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LOAD_TABLE_OP
suffix:colon
id|status
op_assign
id|AE_NOT_IMPLEMENTED
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ex_opcode_3A_0T_0R: Unknown opcode %X&bslash;n&quot;
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
r_break
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
