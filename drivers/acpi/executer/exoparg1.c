multiline_comment|/******************************************************************************&n; *&n; * Module Name: exoparg1 - AML execution - opcodes with 1 argument&n; *              $Revision: 137 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exoparg1&quot;
)paren
multiline_comment|/*!&n; * Naming convention for AML interpreter execution routines.&n; *&n; * The routines that begin execution of AML opcodes are named with a common&n; * convention based upon the number of arguments, the number of target operands,&n; * and whether or not a value is returned:&n; *&n; *      AcpiExOpcode_xA_yT_zR&n; *&n; * Where:&n; *&n; * xA - ARGUMENTS:    The number of arguments (input operands) that are&n; *                    required for this opcode type (1 through 6 args).&n; * yT - TARGETS:      The number of targets (output operands) that are required&n; *                    for this opcode type (0, 1, or 2 targets).&n; * zR - RETURN VALUE: Indicates whether this opcode type returns a value&n; *                    as the function return (0 or 1).&n; *&n; * The AcpiExOpcode* functions are called via the Dispatcher component with&n; * fully resolved operands.&n;!*/
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_opcode_1A_0T_0R&n; *&n; * PARAMETERS:  Walk_state          - Current state (contains AML opcode)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute Type 1 monadic operator with numeric operand on&n; *              object stack&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_1A_0T_0R
id|acpi_ex_opcode_1A_0T_0R
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
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;Ex_opcode_1A_0T_0R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/* Examine the AML opcode */
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_RELEASE_OP
suffix:colon
multiline_comment|/*  Release (Mutex_object) */
id|status
op_assign
id|acpi_ex_release_mutex
(paren
id|operand
(braket
l_int|0
)braket
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_RESET_OP
suffix:colon
multiline_comment|/*  Reset (Event_object) */
id|status
op_assign
id|acpi_ex_system_reset_event
(paren
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_SIGNAL_OP
suffix:colon
multiline_comment|/*  Signal (Event_object) */
id|status
op_assign
id|acpi_ex_system_signal_event
(paren
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_SLEEP_OP
suffix:colon
multiline_comment|/*  Sleep (Msec_time) */
id|status
op_assign
id|acpi_ex_system_do_suspend
(paren
(paren
id|u32
)paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_STALL_OP
suffix:colon
multiline_comment|/*  Stall (Usec_time) */
id|status
op_assign
id|acpi_ex_system_do_stall
(paren
(paren
id|u32
)paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_UNLOAD_OP
suffix:colon
multiline_comment|/*  Unload (Handle) */
id|status
op_assign
id|acpi_ex_unload_table
(paren
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*  Unknown opcode  */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ex_opcode_1A_0T_0R: Unknown opcode %X&bslash;n&quot;
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_opcode_1A_1T_0R&n; *&n; * PARAMETERS:  Walk_state          - Current state (contains AML opcode)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute opcode with one argument, one target, and no&n; *              return value.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_1A_1T_0R
id|acpi_ex_opcode_1A_1T_0R
(paren
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
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;Ex_opcode_1A_1T_0R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/* Examine the AML opcode */
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_LOAD_OP
suffix:colon
id|status
op_assign
id|acpi_ex_load_op
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
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown opcode */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ex_opcode_1A_1T_0R: Unknown opcode %X&bslash;n&quot;
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_opcode_1A_1T_1R&n; *&n; * PARAMETERS:  Walk_state          - Current state (contains AML opcode)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute opcode with one argument, one target, and a&n; *              return value.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_1A_1T_1R
id|acpi_ex_opcode_1A_1T_1R
(paren
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
id|return_desc2
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|temp32
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u32
id|j
suffix:semicolon
id|acpi_integer
id|digit
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;Ex_opcode_1A_1T_1R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/* Examine the AML opcode */
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_BIT_NOT_OP
suffix:colon
r_case
id|AML_FIND_SET_LEFT_BIT_OP
suffix:colon
r_case
id|AML_FIND_SET_RIGHT_BIT_OP
suffix:colon
r_case
id|AML_FROM_BCD_OP
suffix:colon
r_case
id|AML_TO_BCD_OP
suffix:colon
r_case
id|AML_COND_REF_OF_OP
suffix:colon
multiline_comment|/* Create a return object of type Integer for these opcodes */
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
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_BIT_NOT_OP
suffix:colon
multiline_comment|/* Not (Operand, Result)  */
id|return_desc-&gt;integer.value
op_assign
op_complement
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_FIND_SET_LEFT_BIT_OP
suffix:colon
multiline_comment|/* Find_set_left_bit (Operand, Result) */
id|return_desc-&gt;integer.value
op_assign
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Acpi specification describes Integer type as a little&n;&t;&t;&t; * endian unsigned value, so this boundary condition is valid.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|temp32
op_assign
l_int|0
suffix:semicolon
id|return_desc-&gt;integer.value
op_logical_and
id|temp32
OL
id|ACPI_INTEGER_BIT_SIZE
suffix:semicolon
op_increment
id|temp32
)paren
(brace
id|return_desc-&gt;integer.value
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|return_desc-&gt;integer.value
op_assign
id|temp32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_FIND_SET_RIGHT_BIT_OP
suffix:colon
multiline_comment|/* Find_set_right_bit (Operand, Result) */
id|return_desc-&gt;integer.value
op_assign
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The Acpi specification describes Integer type as a little&n;&t;&t;&t; * endian unsigned value, so this boundary condition is valid.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|temp32
op_assign
l_int|0
suffix:semicolon
id|return_desc-&gt;integer.value
op_logical_and
id|temp32
OL
id|ACPI_INTEGER_BIT_SIZE
suffix:semicolon
op_increment
id|temp32
)paren
(brace
id|return_desc-&gt;integer.value
op_lshift_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Since the bit position is one-based, subtract from 33 (65) */
id|return_desc-&gt;integer.value
op_assign
id|temp32
op_eq
l_int|0
ques
c_cond
l_int|0
suffix:colon
(paren
id|ACPI_INTEGER_BIT_SIZE
op_plus
l_int|1
)paren
op_minus
id|temp32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_FROM_BCD_OP
suffix:colon
multiline_comment|/* From_bcd (BCDValue, Result) */
multiline_comment|/*&n;&t;&t;&t; * The 64-bit ACPI integer can hold 16 4-bit BCD integers&n;&t;&t;&t; */
id|return_desc-&gt;integer.value
op_assign
l_int|0
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
id|ACPI_MAX_BCD_DIGITS
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Get one BCD digit */
id|digit
op_assign
(paren
id|acpi_integer
)paren
(paren
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
op_rshift
(paren
id|i
op_star
l_int|4
)paren
)paren
op_amp
l_int|0xF
)paren
suffix:semicolon
multiline_comment|/* Check the range of the digit */
r_if
c_cond
(paren
id|digit
OG
l_int|9
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;BCD digit too large: %d&bslash;n&quot;
comma
(paren
id|u32
)paren
id|digit
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_NUMERIC_OVERFLOW
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
r_if
c_cond
(paren
id|digit
OG
l_int|0
)paren
(brace
multiline_comment|/* Sum into the result with the appropriate power of 10 */
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
id|digit
op_mul_assign
l_int|10
suffix:semicolon
)brace
id|return_desc-&gt;integer.value
op_add_assign
id|digit
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|AML_TO_BCD_OP
suffix:colon
multiline_comment|/* To_bcd (Operand, Result) */
r_if
c_cond
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
OG
id|ACPI_MAX_BCD_VALUE
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;BCD overflow: %8.8X%8.8X&bslash;n&quot;
comma
id|ACPI_HIDWORD
c_func
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
)paren
comma
id|ACPI_LODWORD
c_func
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_NUMERIC_OVERFLOW
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|return_desc-&gt;integer.value
op_assign
l_int|0
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
id|ACPI_MAX_BCD_DIGITS
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Divide by nth factor of 10 */
id|temp32
op_assign
l_int|0
suffix:semicolon
id|digit
op_assign
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
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
op_amp
id|digit
comma
l_int|10
comma
op_amp
id|digit
comma
op_amp
id|temp32
)paren
suffix:semicolon
)brace
multiline_comment|/* Create the BCD digit from the remainder above */
r_if
c_cond
(paren
id|digit
OG
l_int|0
)paren
(brace
id|return_desc-&gt;integer.value
op_add_assign
(paren
(paren
id|acpi_integer
)paren
id|temp32
op_lshift
(paren
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|AML_COND_REF_OF_OP
suffix:colon
multiline_comment|/* Cond_ref_of (Source_object, Result) */
multiline_comment|/*&n;&t;&t;&t; * This op is a little strange because the internal return value is&n;&t;&t;&t; * different than the return value stored in the result descriptor&n;&t;&t;&t; * (There are really two return values)&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|operand
(braket
l_int|0
)braket
op_eq
id|acpi_gbl_root_node
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * This means that the object does not exist in the namespace,&n;&t;&t;&t;&t; * return FALSE&n;&t;&t;&t;&t; */
id|return_desc-&gt;integer.value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Must delete the result descriptor since there is no reference&n;&t;&t;&t;&t; * being returned&n;&t;&t;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|operand
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Get the object reference and store it */
id|status
op_assign
id|acpi_ex_get_object_reference
(paren
id|operand
(braket
l_int|0
)braket
comma
op_amp
id|return_desc2
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
id|return_desc2
comma
id|operand
(braket
l_int|1
)braket
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* The object exists in the namespace, return TRUE */
id|return_desc-&gt;integer.value
op_assign
id|ACPI_INTEGER_MAX
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* No other opcodes get here */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_STORE_OP
suffix:colon
multiline_comment|/* Store (Source, Target) */
multiline_comment|/*&n;&t;&t; * A store operand is typically a number, string, buffer or lvalue&n;&t;&t; * Be careful about deleting the source object,&n;&t;&t; * since the object itself may have been stored.&n;&t;&t; */
id|status
op_assign
id|acpi_ex_store
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Normally, we would remove a reference on the Operand[0] parameter;&n;&t;&t; * But since it is being used as the internal return object&n;&t;&t; * (meaning we would normally increment it), the two cancel out,&n;&t;&t; * and we simply don&squot;t do anything.&n;&t;&t; */
id|walk_state-&gt;result_obj
op_assign
id|operand
(braket
l_int|0
)braket
suffix:semicolon
id|walk_state-&gt;operands
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Prevent deletion */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * ACPI 2.0 Opcodes&n;&t; */
r_case
id|AML_COPY_OP
suffix:colon
multiline_comment|/* Copy (Source, Target) */
id|status
op_assign
id|acpi_ut_copy_iobject_to_iobject
(paren
id|operand
(braket
l_int|0
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
id|AML_TO_DECSTRING_OP
suffix:colon
multiline_comment|/* To_decimal_string (Data, Result) */
id|status
op_assign
id|acpi_ex_convert_to_string
(paren
id|operand
(braket
l_int|0
)braket
comma
op_amp
id|return_desc
comma
l_int|10
comma
id|ACPI_UINT32_MAX
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_TO_HEXSTRING_OP
suffix:colon
multiline_comment|/* To_hex_string (Data, Result) */
id|status
op_assign
id|acpi_ex_convert_to_string
(paren
id|operand
(braket
l_int|0
)braket
comma
op_amp
id|return_desc
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
id|AML_TO_BUFFER_OP
suffix:colon
multiline_comment|/* To_buffer (Data, Result) */
id|status
op_assign
id|acpi_ex_convert_to_buffer
(paren
id|operand
(braket
l_int|0
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
id|AML_TO_INTEGER_OP
suffix:colon
multiline_comment|/* To_integer (Data, Result) */
id|status
op_assign
id|acpi_ex_convert_to_integer
(paren
id|operand
(braket
l_int|0
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
id|AML_SHIFT_LEFT_BIT_OP
suffix:colon
multiline_comment|/*  Shift_left_bit (Source, Bit_num) */
r_case
id|AML_SHIFT_RIGHT_BIT_OP
suffix:colon
multiline_comment|/*  Shift_right_bit (Source, Bit_num) */
multiline_comment|/*&n;&t;&t; * These are two obsolete opcodes&n;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;%s is obsolete and not implemented&bslash;n&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_SUPPORT
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown opcode */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ex_opcode_1A_1T_1R: Unknown opcode %X&bslash;n&quot;
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
multiline_comment|/*&n;&t; * Store the return value computed above into the target object&n;&t; */
id|status
op_assign
id|acpi_ex_store
(paren
id|return_desc
comma
id|operand
(braket
l_int|1
)braket
comma
id|walk_state
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|walk_state-&gt;result_obj
op_assign
id|return_desc
suffix:semicolon
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_opcode_1A_0T_1R&n; *&n; * PARAMETERS:  Walk_state          - Current state (contains AML opcode)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute opcode with one argument, no target, and a return value&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_opcode_1A_0T_1R
id|acpi_ex_opcode_1A_0T_1R
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
id|temp_desc
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
id|type
suffix:semicolon
id|acpi_integer
id|value
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;Ex_opcode_1A_0T_0R&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
)paren
suffix:semicolon
multiline_comment|/* Examine the AML opcode */
r_switch
c_cond
(paren
id|walk_state-&gt;opcode
)paren
(brace
r_case
id|AML_LNOT_OP
suffix:colon
multiline_comment|/* LNot (Operand) */
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
op_logical_neg
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|integer.value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DECREMENT_OP
suffix:colon
multiline_comment|/* Decrement (Operand)  */
r_case
id|AML_INCREMENT_OP
suffix:colon
multiline_comment|/* Increment (Operand)  */
multiline_comment|/*&n;&t;&t; * Since we are expecting a Reference operand, it&n;&t;&t; * can be either a NS Node or an internal object.&n;&t;&t; */
id|return_desc
op_assign
id|operand
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|operand
(braket
l_int|0
)braket
)paren
op_eq
id|ACPI_DESC_TYPE_OPERAND
)paren
(brace
multiline_comment|/* Internal reference object - prevent deletion */
id|acpi_ut_add_reference
(paren
id|return_desc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Convert the Return_desc Reference to a Number&n;&t;&t; * (This removes a reference on the Return_desc object)&n;&t;&t; */
id|status
op_assign
id|acpi_ex_resolve_operands
(paren
id|AML_LNOT_OP
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
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;%s: bad operand(s) %s&bslash;n&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
comma
id|acpi_format_exception
c_func
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Return_desc is now guaranteed to be an Integer object&n;&t;&t; * Do the actual increment or decrement&n;&t;&t; */
r_if
c_cond
(paren
id|AML_INCREMENT_OP
op_eq
id|walk_state-&gt;opcode
)paren
(brace
id|return_desc-&gt;integer.value
op_increment
suffix:semicolon
)brace
r_else
(brace
id|return_desc-&gt;integer.value
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Store the result back in the original descriptor */
id|status
op_assign
id|acpi_ex_store
(paren
id|return_desc
comma
id|operand
(braket
l_int|0
)braket
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_TYPE_OP
suffix:colon
multiline_comment|/* Object_type (Source_object) */
r_if
c_cond
(paren
id|INTERNAL_TYPE_REFERENCE
op_eq
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|common.type
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Not a Name -- an indirect name pointer would have&n;&t;&t;&t; * been converted to a direct name pointer in Resolve_operands&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
)paren
(brace
r_case
id|AML_ZERO_OP
suffix:colon
r_case
id|AML_ONE_OP
suffix:colon
r_case
id|AML_ONES_OP
suffix:colon
r_case
id|AML_REVISION_OP
suffix:colon
multiline_comment|/* Constants are of type Integer */
id|type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DEBUG_OP
suffix:colon
multiline_comment|/* The Debug Object is of type &quot;Debug_object&quot; */
id|type
op_assign
id|ACPI_TYPE_DEBUG_OBJECT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INDEX_OP
suffix:colon
multiline_comment|/* Get the type of this reference (index into another object) */
id|type
op_assign
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.target_type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|ACPI_TYPE_PACKAGE
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * The main object is a package, we want to get the type&n;&t;&t;&t;&t;&t; * of the individual package element that is referenced by&n;&t;&t;&t;&t;&t; * the index.&n;&t;&t;&t;&t;&t; */
id|type
op_assign
(paren
op_star
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.where
)paren
)paren
op_member_access_from_pointer
id|common.type
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LOCAL_OP
suffix:colon
r_case
id|AML_ARG_OP
suffix:colon
id|type
op_assign
id|acpi_ds_method_data_get_type
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.offset
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ex_opcode_1A_0T_1R/Type_op: Internal error - Unknown Reference subtype %X&bslash;n&quot;
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
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
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * It&squot;s not a Reference, so it must be a direct name pointer.&n;&t;&t;&t; */
id|type
op_assign
id|acpi_ns_get_type
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Convert internal types to external types */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|INTERNAL_TYPE_REGION_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_BANK_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_INDEX_FIELD
suffix:colon
id|type
op_assign
id|ACPI_TYPE_FIELD_UNIT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* No change to Type required */
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Allocate a descriptor to hold the type. */
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
id|type
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_SIZE_OF_OP
suffix:colon
multiline_comment|/* Size_of (Source_object) */
id|temp_desc
op_assign
id|operand
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|operand
(braket
l_int|0
)braket
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
id|temp_desc
op_assign
id|acpi_ns_get_attached_object
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|temp_desc
)paren
(brace
id|value
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Type is guaranteed to be a buffer, string, or package at this&n;&t;&t;&t; * point (even if the original operand was an object reference, it&n;&t;&t;&t; * will be resolved and typechecked during operand resolution.)&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|temp_desc-&gt;common.type
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|value
op_assign
id|temp_desc-&gt;buffer.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|value
op_assign
id|temp_desc-&gt;string.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|value
op_assign
id|temp_desc-&gt;package.count
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
l_string|&quot;Size_of, Not Buf/Str/Pkg - found type %s&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|temp_desc-&gt;common.type
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Now that we have the size of the object, create a result&n;&t;&t; * object to hold the value&n;&t;&t; */
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
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_REF_OF_OP
suffix:colon
multiline_comment|/* Ref_of (Source_object) */
id|status
op_assign
id|acpi_ex_get_object_reference
(paren
id|operand
(braket
l_int|0
)braket
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
r_case
id|AML_DEREF_OF_OP
suffix:colon
multiline_comment|/* Deref_of (Obj_reference | String) */
multiline_comment|/* Check for a method local or argument, or standalone String */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|operand
(braket
l_int|0
)braket
)paren
op_ne
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
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
id|INTERNAL_TYPE_REFERENCE
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * This is a Deref_of (Local_x | Arg_x)&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * Must resolve/dereference the local/arg reference first&n;&t;&t;&t;&t; */
r_switch
c_cond
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
)paren
(brace
r_case
id|AML_LOCAL_OP
suffix:colon
r_case
id|AML_ARG_OP
suffix:colon
multiline_comment|/* Set Operand[0] to the value of the local/arg */
id|status
op_assign
id|acpi_ds_method_data_get_value
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.offset
comma
id|walk_state
comma
op_amp
id|temp_desc
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
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Delete our reference to the input object and&n;&t;&t;&t;&t;&t; * point to the object just retrieved&n;&t;&t;&t;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|operand
(braket
l_int|0
)braket
op_assign
id|temp_desc
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Must be an Index op - handled below */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * This is a Deref_of (String). The string is a reference to a named ACPI object.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * 1) Find the owning Node&n;&t;&t;&t;&t; * 2) Dereference the node to an actual object.  Could be a Field, so we nee&n;&t;&t;&t;&t; *    to resolve the node to a value.&n;&t;&t;&t;&t; */
id|status
op_assign
id|acpi_ns_get_node_by_path
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|string.pointer
comma
id|walk_state-&gt;scope_info-&gt;scope.node
comma
id|ACPI_NS_SEARCH_PARENT
comma
id|ACPI_CAST_INDIRECT_PTR
(paren
id|acpi_namespace_node
comma
op_amp
id|return_desc
)paren
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
id|acpi_ex_resolve_node_to_value
(paren
id|ACPI_CAST_INDIRECT_PTR
(paren
id|acpi_namespace_node
comma
op_amp
id|return_desc
)paren
comma
id|walk_state
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
multiline_comment|/* Operand[0] may have changed from the code above */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|operand
(braket
l_int|0
)braket
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This is a Deref_of (Object_reference)&n;&t;&t;&t; * Get the actual object from the Node (This is the dereference).&n;&t;&t;&t; * -- This case may only happen when a Local_x or Arg_x is dereferenced above.&n;&t;&t;&t; */
id|return_desc
op_assign
id|acpi_ns_get_attached_object
(paren
(paren
id|acpi_namespace_node
op_star
)paren
id|operand
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * This must be a reference object produced by either the Index() or&n;&t;&t;&t; * Ref_of() operator&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
)paren
(brace
r_case
id|AML_INDEX_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * The target type for the Index operator must be&n;&t;&t;&t;&t; * either a Buffer or a Package&n;&t;&t;&t;&t; */
r_switch
c_cond
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.target_type
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
multiline_comment|/* Ensure that the Buffer arguments are evaluated */
id|temp_desc
op_assign
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.object
suffix:semicolon
macro_line|#if 0
id|status
op_assign
id|acpi_ds_get_buffer_arguments
(paren
id|temp_desc
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
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Create a new object that contains one element of the&n;&t;&t;&t;&t;&t; * buffer -- the element pointed to by the index.&n;&t;&t;&t;&t;&t; *&n;&t;&t;&t;&t;&t; * NOTE: index into a buffer is NOT a pointer to a&n;&t;&t;&t;&t;&t; * sub-buffer of the main buffer, it is only a pointer to a&n;&t;&t;&t;&t;&t; * single element (byte) of the buffer!&n;&t;&t;&t;&t;&t; */
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
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Since we are returning the value of the buffer at the&n;&t;&t;&t;&t;&t; * indexed location, we don&squot;t need to add an additional&n;&t;&t;&t;&t;&t; * reference to the buffer itself.&n;&t;&t;&t;&t;&t; */
id|return_desc-&gt;integer.value
op_assign
id|temp_desc-&gt;buffer.pointer
(braket
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.offset
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
macro_line|#if 0
multiline_comment|/* Ensure that the Package arguments are evaluated */
id|status
op_assign
id|acpi_ds_get_package_arguments
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.object
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
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Return the referenced element of the package.  We must add&n;&t;&t;&t;&t;&t; * another reference to the referenced object, however.&n;&t;&t;&t;&t;&t; */
id|return_desc
op_assign
op_star
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.where
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_desc
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t; * We can&squot;t return a NULL dereferenced value.  This is&n;&t;&t;&t;&t;&t;&t; * an uninitialized package element and is thus a&n;&t;&t;&t;&t;&t;&t; * severe error.&n;&t;&t;&t;&t;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;NULL package element obj %p&bslash;n&quot;
comma
id|operand
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_UNINITIALIZED_ELEMENT
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|acpi_ut_add_reference
(paren
id|return_desc
)paren
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
l_string|&quot;Unknown Index Target_type %X in obj %p&bslash;n&quot;
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.target_type
comma
id|operand
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_REF_OF_OP
suffix:colon
id|return_desc
op_assign
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.object
suffix:semicolon
multiline_comment|/* Add another reference to the object! */
id|acpi_ut_add_reference
(paren
id|return_desc
)paren
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
l_string|&quot;Unknown opcode in ref(%p) - %X&bslash;n&quot;
comma
id|operand
(braket
l_int|0
)braket
comma
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_TYPE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Acpi_ex_opcode_1A_0T_1R: Unknown opcode %X&bslash;n&quot;
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
id|walk_state-&gt;result_obj
op_assign
id|return_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
