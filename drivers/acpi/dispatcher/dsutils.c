multiline_comment|/*******************************************************************************&n; *&n; * Module Name: dsutils - Dispatcher utilities&n; *              $Revision: 98 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acdebug.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dsutils&quot;
)paren
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_is_result_used&n; *&n; * PARAMETERS:  Op&n; *              Result_obj&n; *              Walk_state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Check if a result object will be used by the parent&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ds_is_result_used
id|acpi_ds_is_result_used
(paren
id|acpi_parse_object
op_star
id|op
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_const
id|acpi_opcode_info
op_star
id|parent_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_is_result_used&quot;
comma
id|op
)paren
suffix:semicolon
multiline_comment|/* Must have both an Op and a Result Object */
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Null Op&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|TRUE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If there is no parent, the result can&squot;t possibly be used!&n;&t; * (An executing method typically has no parent, since each&n;&t; * method is parsed separately)  However, a method that is&n;&t; * invoked from another method has a parent.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|op-&gt;common.parent
)paren
(brace
id|return_VALUE
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get info on the parent.  The root Op is AML_SCOPE&n;&t; */
id|parent_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent_info
op_member_access_from_pointer
r_class
op_eq
id|AML_CLASS_UNKNOWN
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown parent opcode. Op=%p&bslash;n&quot;
comma
id|op
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Decide what to do with the result based on the parent.  If&n;&t; * the parent opcode will not use the result, delete the object.&n;&t; * Otherwise leave it as is, it will be deleted when it is used&n;&t; * as an operand later.&n;&t; */
r_switch
c_cond
(paren
id|parent_info
op_member_access_from_pointer
r_class
)paren
(brace
r_case
id|AML_CLASS_CONTROL
suffix:colon
r_switch
c_cond
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_RETURN_OP
suffix:colon
multiline_comment|/* Never delete the return value associated with a return opcode */
r_goto
id|result_used
suffix:semicolon
r_case
id|AML_IF_OP
suffix:colon
r_case
id|AML_WHILE_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * If we are executing the predicate AND this is the predicate op,&n;&t;&t;&t; * we will use the return value&n;&t;&t;&t; */
r_if
c_cond
(paren
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
r_goto
id|result_used
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Ignore other control opcodes */
r_break
suffix:semicolon
)brace
multiline_comment|/* The general control opcode returns no result */
r_goto
id|result_not_used
suffix:semicolon
r_case
id|AML_CLASS_CREATE
suffix:colon
multiline_comment|/*&n;&t;&t; * These opcodes allow Term_arg(s) as operands and therefore&n;&t;&t; * the operands can be method calls.  The result is used.&n;&t;&t; */
r_goto
id|result_used
suffix:semicolon
r_case
id|AML_CLASS_NAMED_OBJECT
suffix:colon
r_if
c_cond
(paren
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
op_eq
id|AML_REGION_OP
)paren
op_logical_or
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
op_eq
id|AML_DATA_REGION_OP
)paren
op_logical_or
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
op_eq
id|AML_PACKAGE_OP
)paren
op_logical_or
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
op_eq
id|AML_VAR_PACKAGE_OP
)paren
op_logical_or
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
op_eq
id|AML_BUFFER_OP
)paren
op_logical_or
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
op_eq
id|AML_INT_EVAL_SUBTREE_OP
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * These opcodes allow Term_arg(s) as operands and therefore&n;&t;&t;&t; * the operands can be method calls.  The result is used.&n;&t;&t;&t; */
r_goto
id|result_used
suffix:semicolon
)brace
r_goto
id|result_not_used
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t; * In all other cases. the parent will actually use the return&n;&t;&t; * object, so keep it.&n;&t;&t; */
r_goto
id|result_used
suffix:semicolon
)brace
id|result_used
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Result of [%s] used by Parent [%s] Op=%p&bslash;n&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|op-&gt;common.aml_opcode
)paren
comma
id|acpi_ps_get_opcode_name
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
)paren
comma
id|op
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|TRUE
)paren
suffix:semicolon
id|result_not_used
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Result of [%s] not used by Parent [%s] Op=%p&bslash;n&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|op-&gt;common.aml_opcode
)paren
comma
id|acpi_ps_get_opcode_name
(paren
id|op-&gt;common.parent-&gt;common.aml_opcode
)paren
comma
id|op
)paren
)paren
suffix:semicolon
id|return_VALUE
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_delete_result_if_not_used&n; *&n; * PARAMETERS:  Op&n; *              Result_obj&n; *              Walk_state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Used after interpretation of an opcode.  If there is an internal&n; *              result descriptor, check if the parent opcode will actually use&n; *              this result.  If not, delete the result now so that it will&n; *              not become orphaned.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ds_delete_result_if_not_used
id|acpi_ds_delete_result_if_not_used
(paren
id|acpi_parse_object
op_star
id|op
comma
id|acpi_operand_object
op_star
id|result_obj
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_delete_result_if_not_used&quot;
comma
id|result_obj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Null Op&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|result_obj
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_ds_is_result_used
(paren
id|op
comma
id|walk_state
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Must pop the result stack (Obj_desc should be equal to Result_obj)&n;&t;&t; */
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
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|result_obj
)paren
suffix:semicolon
)brace
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_resolve_operands&n; *&n; * PARAMETERS:  Walk_state          - Current walk state with operands on stack&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Resolve all operands to their values.  Used to prepare&n; *              arguments to a control method invocation (a call from one&n; *              method to another.)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_resolve_operands
id|acpi_ds_resolve_operands
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_resolve_operands&quot;
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Attempt to resolve each of the valid operands&n;&t; * Method arguments are passed by value, not by reference&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|walk_state-&gt;num_operands
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_ex_resolve_to_value
(paren
op_amp
id|walk_state-&gt;operands
(braket
id|i
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
r_break
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_clear_operands&n; *&n; * PARAMETERS:  Walk_state          - Current walk state with operands on stack&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Clear all operands on the current walk state operand stack.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ds_clear_operands
id|acpi_ds_clear_operands
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Acpi_ds_clear_operands&quot;
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Remove a reference on each operand on the stack&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|walk_state-&gt;num_operands
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; * Remove a reference to all operands, including both&n;&t;&t; * &quot;Arguments&quot; and &quot;Targets&quot;.&n;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|walk_state-&gt;operands
(braket
id|i
)braket
)paren
suffix:semicolon
id|walk_state-&gt;operands
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|walk_state-&gt;num_operands
op_assign
l_int|0
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_operand&n; *&n; * PARAMETERS:  Walk_state&n; *              Arg&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Translate a parse tree object that is an argument to an AML&n; *              opcode to the equivalent interpreter object.  This may include&n; *              looking up a name or entering a new name into the internal&n; *              namespace.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_create_operand
id|acpi_ds_create_operand
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|arg
comma
id|u32
id|arg_index
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_char
op_star
id|name_string
suffix:semicolon
id|u32
id|name_length
suffix:semicolon
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_parse_object
op_star
id|parent_op
suffix:semicolon
id|u16
id|opcode
suffix:semicolon
id|acpi_interpreter_mode
id|interpreter_mode
suffix:semicolon
r_const
id|acpi_opcode_info
op_star
id|op_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_create_operand&quot;
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* A valid name must be looked up in the namespace */
r_if
c_cond
(paren
(paren
id|arg-&gt;common.aml_opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
op_logical_and
(paren
id|arg-&gt;common.value.string
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Getting a name: Arg=%p&bslash;n&quot;
comma
id|arg
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the entire name string from the AML stream */
id|status
op_assign
id|acpi_ex_get_name_string
(paren
id|ACPI_TYPE_ANY
comma
id|arg-&gt;common.value.buffer
comma
op_amp
id|name_string
comma
op_amp
id|name_length
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
multiline_comment|/*&n;&t;&t; * All prefixes have been handled, and the name is&n;&t;&t; * in Name_string&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Differentiate between a namespace &quot;create&quot; operation&n;&t;&t; * versus a &quot;lookup&quot; operation (IMODE_LOAD_PASS2 vs.&n;&t;&t; * IMODE_EXECUTE) in order to support the creation of&n;&t;&t; * namespace objects during the execution of control methods.&n;&t;&t; */
id|parent_op
op_assign
id|arg-&gt;common.parent
suffix:semicolon
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|parent_op-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|op_info-&gt;flags
op_amp
id|AML_NSNODE
)paren
op_logical_and
(paren
id|parent_op-&gt;common.aml_opcode
op_ne
id|AML_INT_METHODCALL_OP
)paren
op_logical_and
(paren
id|parent_op-&gt;common.aml_opcode
op_ne
id|AML_REGION_OP
)paren
op_logical_and
(paren
id|parent_op-&gt;common.aml_opcode
op_ne
id|AML_INT_NAMEPATH_OP
)paren
)paren
(brace
multiline_comment|/* Enter name into namespace if not found */
id|interpreter_mode
op_assign
id|ACPI_IMODE_LOAD_PASS2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Return a failure if name not found */
id|interpreter_mode
op_assign
id|ACPI_IMODE_EXECUTE
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|name_string
comma
id|ACPI_TYPE_ANY
comma
id|interpreter_mode
comma
id|ACPI_NS_SEARCH_PARENT
op_or
id|ACPI_NS_DONT_OPEN_SCOPE
comma
id|walk_state
comma
id|ACPI_CAST_INDIRECT_PTR
(paren
id|acpi_namespace_node
comma
op_amp
id|obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The only case where we pass through (ignore) a NOT_FOUND&n;&t;&t; * error is for the Cond_ref_of opcode.&n;&t;&t; */
r_if
c_cond
(paren
id|status
op_eq
id|AE_NOT_FOUND
)paren
(brace
r_if
c_cond
(paren
id|parent_op-&gt;common.aml_opcode
op_eq
id|AML_COND_REF_OF_OP
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * For the Conditional Reference op, it&squot;s OK if&n;&t;&t;&t;&t; * the name is not found;  We just need a way to&n;&t;&t;&t;&t; * indicate this to the interpreter, set the&n;&t;&t;&t;&t; * object to the root&n;&t;&t;&t;&t; */
id|obj_desc
op_assign
id|ACPI_CAST_PTR
(paren
id|acpi_operand_object
comma
id|acpi_gbl_root_node
)paren
suffix:semicolon
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * We just plain didn&squot;t find it -- which is a&n;&t;&t;&t;&t; * very serious error at this point&n;&t;&t;&t;&t; */
id|status
op_assign
id|AE_AML_NAME_NOT_FOUND
suffix:semicolon
)brace
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
id|ACPI_REPORT_NSERROR
(paren
id|name_string
comma
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Free the namestring created above */
id|ACPI_MEM_FREE
(paren
id|name_string
)paren
suffix:semicolon
multiline_comment|/* Check status from the lookup */
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
multiline_comment|/* Put the resulting object onto the current object stack */
id|status
op_assign
id|acpi_ds_obj_stack_push
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_DEBUGGER_EXEC
(paren
id|acpi_db_display_argument_object
(paren
id|obj_desc
comma
id|walk_state
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Check for null name case */
r_if
c_cond
(paren
id|arg-&gt;common.aml_opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * If the name is null, this means that this is an&n;&t;&t;&t; * optional result parameter that was not specified&n;&t;&t;&t; * in the original ASL.  Create a Zero Constant for a&n;&t;&t;&t; * placeholder.  (Store to a constant is a Noop.)&n;&t;&t;&t; */
id|opcode
op_assign
id|AML_ZERO_OP
suffix:semicolon
multiline_comment|/* Has no arguments! */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Null namepath: Arg=%p&bslash;n&quot;
comma
id|arg
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|opcode
op_assign
id|arg-&gt;common.aml_opcode
suffix:semicolon
)brace
multiline_comment|/* Get the object type of the argument */
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op_info-&gt;object_type
op_eq
id|ACPI_TYPE_INVALID
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NOT_IMPLEMENTED
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op_info-&gt;flags
op_amp
id|AML_HAS_RETVAL
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Argument previously created, already stacked &bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ACPI_DEBUGGER_EXEC
(paren
id|acpi_db_display_argument_object
(paren
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
op_minus
l_int|1
)braket
comma
id|walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Use value that was already previously returned&n;&t;&t;&t; * by the evaluation of this argument&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ds_result_pop_from_bottom
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
multiline_comment|/*&n;&t;&t;&t;&t; * Only error is underflow, and this indicates&n;&t;&t;&t;&t; * a missing or null operand!&n;&t;&t;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Missing or null operand, %s&bslash;n&quot;
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
multiline_comment|/* Create an ACPI_INTERNAL_OBJECT for the argument */
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|op_info-&gt;object_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the new object */
id|status
op_assign
id|acpi_ds_init_object_from_op
(paren
id|walk_state
comma
id|arg
comma
id|opcode
comma
op_amp
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
id|acpi_ut_delete_object_desc
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Put the operand object on the object stack */
id|status
op_assign
id|acpi_ds_obj_stack_push
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_DEBUGGER_EXEC
(paren
id|acpi_db_display_argument_object
(paren
id|obj_desc
comma
id|walk_state
)paren
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_operands&n; *&n; * PARAMETERS:  First_arg           - First argument of a parser argument tree&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an operator&squot;s arguments from a parse tree format to&n; *              namespace objects and place those argument object on the object&n; *              stack in preparation for evaluation by the interpreter.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_create_operands
id|acpi_ds_create_operands
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|first_arg
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|u32
id|arg_count
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_create_operands&quot;
comma
id|first_arg
)paren
suffix:semicolon
multiline_comment|/* For all arguments in the list... */
id|arg
op_assign
id|first_arg
suffix:semicolon
r_while
c_loop
(paren
id|arg
)paren
(brace
id|status
op_assign
id|acpi_ds_create_operand
(paren
id|walk_state
comma
id|arg
comma
id|arg_count
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Arg #%d (%p) done, Arg1=%p&bslash;n&quot;
comma
id|arg_count
comma
id|arg
comma
id|first_arg
)paren
)paren
suffix:semicolon
multiline_comment|/* Move on to next argument, if any */
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
id|arg_count
op_increment
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
id|cleanup
suffix:colon
multiline_comment|/*&n;&t; * We must undo everything done above; meaning that we must&n;&t; * pop everything off of the operand stack and delete those&n;&t; * objects&n;&t; */
(paren
r_void
)paren
id|acpi_ds_obj_stack_pop_and_delete
(paren
id|arg_count
comma
id|walk_state
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;While creating Arg %d - %s&bslash;n&quot;
comma
(paren
id|arg_count
op_plus
l_int|1
)paren
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
eof
