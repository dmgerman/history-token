multiline_comment|/******************************************************************************&n; *&n; * Module Name: dswexec - Dispatcher method execution callbacks;&n; *                        dispatch to interpreter.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acdebug.h&gt;
macro_line|#include &lt;acpi/acdisasm.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dswexec&quot;
)paren
multiline_comment|/*&n; * Dispatch table for opcode classes&n; */
DECL|variable|acpi_gbl_op_type_dispatch
r_static
id|ACPI_EXECUTE_OP
id|acpi_gbl_op_type_dispatch
(braket
)braket
op_assign
(brace
id|acpi_ex_opcode_0A_0T_1R
comma
id|acpi_ex_opcode_1A_0T_0R
comma
id|acpi_ex_opcode_1A_0T_1R
comma
id|acpi_ex_opcode_1A_1T_0R
comma
id|acpi_ex_opcode_1A_1T_1R
comma
id|acpi_ex_opcode_2A_0T_0R
comma
id|acpi_ex_opcode_2A_0T_1R
comma
id|acpi_ex_opcode_2A_1T_1R
comma
id|acpi_ex_opcode_2A_2T_1R
comma
id|acpi_ex_opcode_3A_0T_0R
comma
id|acpi_ex_opcode_3A_1T_1R
comma
id|acpi_ex_opcode_6A_0T_1R
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ds_get_predicate_value&n; *&n; * PARAMETERS:  walk_state      - Current state of the parse tree walk&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get the result of a predicate evaluation&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|acpi_ds_get_predicate_value
id|acpi_ds_get_predicate_value
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_operand_object
op_star
id|result_obj
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_get_predicate_value&quot;
comma
id|walk_state
)paren
suffix:semicolon
id|walk_state-&gt;control_state-&gt;common.state
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|result_obj
)paren
(brace
id|status
op_assign
id|acpi_ds_result_pop
(paren
op_amp
id|obj_desc
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
l_string|&quot;Could not get result from predicate evaluation, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|status
op_assign
id|acpi_ds_create_operand
(paren
id|walk_state
comma
id|walk_state-&gt;op
comma
l_int|0
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
id|status
op_assign
id|acpi_ex_resolve_to_value
(paren
op_amp
id|walk_state-&gt;operands
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
id|obj_desc
op_assign
id|walk_state-&gt;operands
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;No predicate obj_desc=%p State=%p&bslash;n&quot;
comma
id|obj_desc
comma
id|walk_state
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Result of predicate evaluation currently must&n;&t; * be a number&n;&t; */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_INTEGER
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Bad predicate (not a number) obj_desc=%p State=%p Type=%X&bslash;n&quot;
comma
id|obj_desc
comma
id|walk_state
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
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
multiline_comment|/* Truncate the predicate to 32-bits if necessary */
id|acpi_ex_truncate_for32bit_table
(paren
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Save the result of the predicate evaluation on&n;&t; * the control stack&n;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;integer.value
)paren
(brace
id|walk_state-&gt;control_state-&gt;common.value
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Predicate is FALSE, we will just toss the&n;&t;&t; * rest of the package&n;&t;&t; */
id|walk_state-&gt;control_state-&gt;common.value
op_assign
id|FALSE
suffix:semicolon
id|status
op_assign
id|AE_CTRL_FALSE
suffix:semicolon
)brace
id|cleanup
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Completed a predicate eval=%X Op=%p&bslash;n&quot;
comma
id|walk_state-&gt;control_state-&gt;common.value
comma
id|walk_state-&gt;op
)paren
)paren
suffix:semicolon
multiline_comment|/* Break to debugger to display result */
id|ACPI_DEBUGGER_EXEC
(paren
id|acpi_db_display_result_object
(paren
id|obj_desc
comma
id|walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Delete the predicate result object (we know that&n;&t; * we don&squot;t need it anymore)&n;&t; */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|walk_state-&gt;control_state-&gt;common.state
op_assign
id|ACPI_CONTROL_NORMAL
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ds_exec_begin_op&n; *&n; * PARAMETERS:  walk_state      - Current state of the parse tree walk&n; *              out_op          - Return op if a new one is created&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Descending callback used during the execution of control&n; *              methods.  This is where most operators and operands are&n; *              dispatched to the interpreter.&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|acpi_ds_exec_begin_op
id|acpi_ds_exec_begin_op
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
op_star
id|out_op
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|op
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|opcode_class
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_exec_begin_op&quot;
comma
id|walk_state
)paren
suffix:semicolon
id|op
op_assign
id|walk_state-&gt;op
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|status
op_assign
id|acpi_ds_load2_begin_op
(paren
id|walk_state
comma
id|out_op
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
id|op
op_assign
op_star
id|out_op
suffix:semicolon
id|walk_state-&gt;op
op_assign
id|op
suffix:semicolon
id|walk_state-&gt;opcode
op_assign
id|op-&gt;common.aml_opcode
suffix:semicolon
id|walk_state-&gt;op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_ns_opens_scope
(paren
id|walk_state-&gt;op_info-&gt;object_type
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;(%s) Popping scope for Op %p&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|walk_state-&gt;op_info-&gt;object_type
)paren
comma
id|op
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ds_scope_stack_pop
(paren
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
)brace
)brace
r_if
c_cond
(paren
id|op
op_eq
id|walk_state-&gt;origin
)paren
(brace
r_if
c_cond
(paren
id|out_op
)paren
(brace
op_star
id|out_op
op_assign
id|op
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the previous opcode was a conditional, this opcode&n;&t; * must be the beginning of the associated predicate.&n;&t; * Save this knowledge in the current scope descriptor&n;&t; */
r_if
c_cond
(paren
(paren
id|walk_state-&gt;control_state
)paren
op_logical_and
(paren
id|walk_state-&gt;control_state-&gt;common.state
op_eq
id|ACPI_CONTROL_CONDITIONAL_EXECUTING
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Exec predicate Op=%p State=%p&bslash;n&quot;
comma
id|op
comma
id|walk_state
)paren
)paren
suffix:semicolon
id|walk_state-&gt;control_state-&gt;common.state
op_assign
id|ACPI_CONTROL_PREDICATE_EXECUTING
suffix:semicolon
multiline_comment|/* Save start of predicate */
id|walk_state-&gt;control_state-&gt;control.predicate_op
op_assign
id|op
suffix:semicolon
)brace
id|opcode_class
op_assign
id|walk_state-&gt;op_info
op_member_access_from_pointer
r_class
suffix:semicolon
multiline_comment|/* We want to send namepaths to the load code */
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
(brace
id|opcode_class
op_assign
id|AML_CLASS_NAMED_OBJECT
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Handle the opcode based upon the opcode type&n;&t; */
r_switch
c_cond
(paren
id|opcode_class
)paren
(brace
r_case
id|AML_CLASS_CONTROL
suffix:colon
id|status
op_assign
id|acpi_ds_result_stack_push
(paren
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
id|status
op_assign
id|acpi_ds_exec_begin_control_op
(paren
id|walk_state
comma
id|op
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_CLASS_NAMED_OBJECT
suffix:colon
r_if
c_cond
(paren
id|walk_state-&gt;walk_type
op_eq
id|ACPI_WALK_METHOD
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Found a named object declaration during method&n;&t;&t;&t; * execution;  we must enter this object into the&n;&t;&t;&t; * namespace.  The created object is temporary and&n;&t;&t;&t; * will be deleted upon completion of the execution&n;&t;&t;&t; * of this method.&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ds_load2_begin_op
(paren
id|walk_state
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_REGION_OP
)paren
(brace
id|status
op_assign
id|acpi_ds_result_stack_push
(paren
id|walk_state
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_CLASS_EXECUTE
suffix:colon
r_case
id|AML_CLASS_CREATE
suffix:colon
multiline_comment|/* most operators with arguments */
multiline_comment|/* Start a new result/operand state */
id|status
op_assign
id|acpi_ds_result_stack_push
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Nothing to do here during method execution */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    acpi_ds_exec_end_op&n; *&n; * PARAMETERS:  walk_state      - Current state of the parse tree walk&n; *              Op              - Op that has been just been completed in the&n; *                                walk;  Arguments have now been evaluated.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Ascending callback used during the execution of control&n; *              methods.  The only thing we really need to do here is to&n; *              notice the beginning of IF, ELSE, and WHILE blocks.&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|acpi_ds_exec_end_op
id|acpi_ds_exec_end_op
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|op
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|op_type
suffix:semicolon
id|u32
id|op_class
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|next_op
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|first_arg
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_exec_end_op&quot;
comma
id|walk_state
)paren
suffix:semicolon
id|op
op_assign
id|walk_state-&gt;op
suffix:semicolon
id|op_type
op_assign
id|walk_state-&gt;op_info-&gt;type
suffix:semicolon
id|op_class
op_assign
id|walk_state-&gt;op_info
op_member_access_from_pointer
r_class
suffix:semicolon
r_if
c_cond
(paren
id|op_class
op_eq
id|AML_CLASS_UNKNOWN
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown opcode %X&bslash;n&quot;
comma
id|op-&gt;common.aml_opcode
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_IMPLEMENTED
)paren
suffix:semicolon
)brace
id|first_arg
op_assign
id|op-&gt;common.value.arg
suffix:semicolon
multiline_comment|/* Init the walk state */
id|walk_state-&gt;num_operands
op_assign
l_int|0
suffix:semicolon
id|walk_state-&gt;return_desc
op_assign
l_int|NULL
suffix:semicolon
id|walk_state-&gt;result_obj
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Call debugger for single step support (DEBUG build only) */
id|ACPI_DEBUGGER_EXEC
(paren
id|status
op_assign
id|acpi_db_single_step
(paren
id|walk_state
comma
id|op
comma
id|op_class
)paren
)paren
suffix:semicolon
id|ACPI_DEBUGGER_EXEC
(paren
r_if
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
)paren
suffix:semicolon
multiline_comment|/* Decode the Opcode Class */
r_switch
c_cond
(paren
id|op_class
)paren
(brace
r_case
id|AML_CLASS_ARGUMENT
suffix:colon
multiline_comment|/* constants, literals, etc. -- do nothing */
r_break
suffix:semicolon
r_case
id|AML_CLASS_EXECUTE
suffix:colon
multiline_comment|/* most operators with arguments */
multiline_comment|/* Build resolved operand stack */
id|status
op_assign
id|acpi_ds_create_operands
(paren
id|walk_state
comma
id|first_arg
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
multiline_comment|/* Done with this result state (Now that operand stack is built) */
id|status
op_assign
id|acpi_ds_result_stack_pop
(paren
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
multiline_comment|/*&n;&t;&t; * All opcodes require operand resolution, with the only exceptions&n;&t;&t; * being the object_type and size_of operators.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_NO_OPERAND_RESOLVE
)paren
)paren
(brace
multiline_comment|/* Resolve all operands */
id|status
op_assign
id|acpi_ex_resolve_operands
(paren
id|walk_state-&gt;opcode
comma
op_amp
(paren
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
op_minus
l_int|1
)braket
)paren
comma
id|walk_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
id|ACPI_DUMP_OPERANDS
(paren
id|ACPI_WALK_OPERANDS
comma
id|ACPI_IMODE_EXECUTE
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
comma
id|walk_state-&gt;num_operands
comma
l_string|&quot;after ex_resolve_operands&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Dispatch the request to the appropriate interpreter handler&n;&t;&t;&t; * routine.  There is one routine per opcode &quot;type&quot; based upon the&n;&t;&t;&t; * number of opcode arguments and return type.&n;&t;&t;&t; */
id|status
op_assign
id|acpi_gbl_op_type_dispatch
(braket
id|op_type
)braket
(paren
id|walk_state
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Treat constructs of the form &quot;Store(local_x,local_x)&quot; as noops when the&n;&t;&t;&t; * Local is uninitialized.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|status
op_eq
id|AE_AML_UNINITIALIZED_LOCAL
)paren
op_logical_and
(paren
id|walk_state-&gt;opcode
op_eq
id|AML_STORE_OP
)paren
op_logical_and
(paren
id|walk_state-&gt;operands
(braket
l_int|0
)braket
op_member_access_from_pointer
id|common.type
op_eq
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
op_logical_and
(paren
id|walk_state-&gt;operands
(braket
l_int|1
)braket
op_member_access_from_pointer
id|common.type
op_eq
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
op_logical_and
(paren
id|walk_state-&gt;operands
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.opcode
op_eq
id|walk_state-&gt;operands
(braket
l_int|1
)braket
op_member_access_from_pointer
id|reference.opcode
)paren
op_logical_and
(paren
id|walk_state-&gt;operands
(braket
l_int|0
)braket
op_member_access_from_pointer
id|reference.offset
op_eq
id|walk_state-&gt;operands
(braket
l_int|1
)braket
op_member_access_from_pointer
id|reference.offset
)paren
)paren
(brace
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;[%s]: Could not resolve operands, %s&bslash;n&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|walk_state-&gt;opcode
)paren
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Always delete the argument objects and clear the operand stack */
id|acpi_ds_clear_operands
(paren
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If a result object was returned from above, push it on the&n;&t;&t; * current result stack&n;&t;&t; */
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
op_logical_and
id|walk_state-&gt;result_obj
)paren
(brace
id|status
op_assign
id|acpi_ds_result_push
(paren
id|walk_state-&gt;result_obj
comma
id|walk_state
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_switch
c_cond
(paren
id|op_type
)paren
(brace
r_case
id|AML_TYPE_CONTROL
suffix:colon
multiline_comment|/* Type 1 opcode, IF/ELSE/WHILE/NOOP */
multiline_comment|/* 1 Operand, 0 external_result, 0 internal_result */
id|status
op_assign
id|acpi_ds_exec_end_control_op
(paren
id|walk_state
comma
id|op
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
r_break
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_result_stack_pop
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_TYPE_METHOD_CALL
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Method invocation, Op=%p&bslash;n&quot;
comma
id|op
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * (AML_METHODCALL) Op-&gt;Value-&gt;Arg-&gt;Node contains&n;&t;&t;&t; * the method Node pointer&n;&t;&t;&t; */
multiline_comment|/* next_op points to the op that holds the method name */
id|next_op
op_assign
id|first_arg
suffix:semicolon
multiline_comment|/* next_op points to first argument op */
id|next_op
op_assign
id|next_op-&gt;common.next
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Get the method&squot;s arguments and put them on the operand stack&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ds_create_operands
(paren
id|walk_state
comma
id|next_op
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
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Since the operands will be passed to another control method,&n;&t;&t;&t; * we must resolve all local references here (Local variables,&n;&t;&t;&t; * arguments to *this* method, etc.)&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ds_resolve_operands
(paren
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
multiline_comment|/* On error, clear all resolved operands */
id|acpi_ds_clear_operands
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Tell the walk loop to preempt this running method and&n;&t;&t;&t; * execute the new method&n;&t;&t;&t; */
id|status
op_assign
id|AE_CTRL_TRANSFER
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Return now; we don&squot;t want to disturb anything,&n;&t;&t;&t; * especially the operand count!&n;&t;&t;&t; */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
r_case
id|AML_TYPE_CREATE_FIELD
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Executing create_field Buffer/Index Op=%p&bslash;n&quot;
comma
id|op
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ds_load2_end_op
(paren
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
r_break
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_eval_buffer_field_operands
(paren
id|walk_state
comma
id|op
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_TYPE_CREATE_OBJECT
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Executing create_object (Buffer/Package) Op=%p&bslash;n&quot;
comma
id|op
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_NAME_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * Put the Node on the object stack (Contains the ACPI Name of&n;&t;&t;&t;&t; * this object)&n;&t;&t;&t;&t; */
id|walk_state-&gt;operands
(braket
l_int|0
)braket
op_assign
(paren
r_void
op_star
)paren
id|op-&gt;common.parent-&gt;common.node
suffix:semicolon
id|walk_state-&gt;num_operands
op_assign
l_int|1
suffix:semicolon
id|status
op_assign
id|acpi_ds_create_node
(paren
id|walk_state
comma
id|op-&gt;common.parent-&gt;common.node
comma
id|op-&gt;common.parent
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
r_break
suffix:semicolon
)brace
multiline_comment|/* Fall through */
multiline_comment|/*lint -fallthrough */
r_case
id|AML_INT_EVAL_SUBTREE_OP
suffix:colon
id|status
op_assign
id|acpi_ds_eval_data_object_operands
(paren
id|walk_state
comma
id|op
comma
id|acpi_ns_get_attached_object
(paren
id|op-&gt;common.parent-&gt;common.node
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|acpi_ds_eval_data_object_operands
(paren
id|walk_state
comma
id|op
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * If a result object was returned from above, push it on the&n;&t;&t;&t; * current result stack&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
op_logical_and
id|walk_state-&gt;result_obj
)paren
(brace
id|status
op_assign
id|acpi_ds_result_push
(paren
id|walk_state-&gt;result_obj
comma
id|walk_state
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_TYPE_NAMED_FIELD
suffix:colon
r_case
id|AML_TYPE_NAMED_COMPLEX
suffix:colon
r_case
id|AML_TYPE_NAMED_SIMPLE
suffix:colon
r_case
id|AML_TYPE_NAMED_NO_OBJ
suffix:colon
id|status
op_assign
id|acpi_ds_load2_end_op
(paren
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
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_REGION_OP
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Executing op_region Address/Length Op=%p&bslash;n&quot;
comma
id|op
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ds_eval_region_operands
(paren
id|walk_state
comma
id|op
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
r_break
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_result_stack_pop
(paren
id|walk_state
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_TYPE_UNDEFINED
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Undefined opcode type Op=%p&bslash;n&quot;
comma
id|op
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_IMPLEMENTED
)paren
suffix:semicolon
r_case
id|AML_TYPE_BOGUS
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Internal opcode=%X type Op=%p&bslash;n&quot;
comma
id|walk_state-&gt;opcode
comma
id|op
)paren
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
l_string|&quot;Unimplemented opcode, class=%X type=%X Opcode=%X Op=%p&bslash;n&quot;
comma
id|op_class
comma
id|op_type
comma
id|op-&gt;common.aml_opcode
comma
id|op
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_NOT_IMPLEMENTED
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * ACPI 2.0 support for 64-bit integers: Truncate numeric&n;&t; * result value if we are executing from a 32-bit ACPI table&n;&t; */
id|acpi_ex_truncate_for32bit_table
(paren
id|walk_state-&gt;result_obj
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if we just completed the evaluation of a&n;&t; * conditional predicate&n;&t; */
r_if
c_cond
(paren
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
op_logical_and
(paren
id|walk_state-&gt;control_state
)paren
op_logical_and
(paren
id|walk_state-&gt;control_state-&gt;common.state
op_eq
id|ACPI_CONTROL_PREDICATE_EXECUTING
)paren
op_logical_and
(paren
id|walk_state-&gt;control_state-&gt;control.predicate_op
op_eq
id|op
)paren
)paren
(brace
id|status
op_assign
id|acpi_ds_get_predicate_value
(paren
id|walk_state
comma
id|walk_state-&gt;result_obj
)paren
suffix:semicolon
id|walk_state-&gt;result_obj
op_assign
l_int|NULL
suffix:semicolon
)brace
id|cleanup
suffix:colon
multiline_comment|/* Invoke exception handler on error */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_and
id|acpi_gbl_exception_handler
op_logical_and
op_logical_neg
(paren
id|status
op_amp
id|AE_CODE_CONTROL
)paren
)paren
(brace
id|acpi_ex_exit_interpreter
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_gbl_exception_handler
(paren
id|status
comma
id|walk_state-&gt;method_node-&gt;name.integer
comma
id|walk_state-&gt;opcode
comma
id|walk_state-&gt;aml_offset
comma
l_int|NULL
)paren
suffix:semicolon
id|acpi_ex_enter_interpreter
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|walk_state-&gt;result_obj
)paren
(brace
multiline_comment|/* Break to debugger to display result */
id|ACPI_DEBUGGER_EXEC
(paren
id|acpi_db_display_result_object
(paren
id|walk_state-&gt;result_obj
comma
id|walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Delete the result op if and only if:&n;&t;&t; * Parent will not use the result -- such as any&n;&t;&t; * non-nested type2 op in a method (parent will be method)&n;&t;&t; */
id|acpi_ds_delete_result_if_not_used
(paren
id|op
comma
id|walk_state-&gt;result_obj
comma
id|walk_state
)paren
suffix:semicolon
)brace
macro_line|#ifdef _UNDER_DEVELOPMENT
r_if
c_cond
(paren
id|walk_state-&gt;parser_state.aml
op_eq
id|walk_state-&gt;parser_state.aml_end
)paren
(brace
id|acpi_db_method_end
(paren
id|walk_state
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Always clear the object stack */
id|walk_state-&gt;num_operands
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef ACPI_DISASSEMBLER
multiline_comment|/* On error, display method locals/args */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|acpi_dm_dump_method_info
(paren
id|status
comma
id|walk_state
comma
id|op
)paren
suffix:semicolon
)brace
macro_line|#endif
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
