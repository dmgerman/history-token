multiline_comment|/******************************************************************************&n; *&n; * Module Name: exresolv - AML Interpreter object resolution&n; *              $Revision: 114 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exresolv&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_resolve_to_value&n; *&n; * PARAMETERS:  **Stack_ptr         - Points to entry on Obj_stack, which can&n; *                                    be either an (acpi_operand_object *)&n; *                                    or an acpi_handle.&n; *              Walk_state          - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert Reference objects to values&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_resolve_to_value
id|acpi_ex_resolve_to_value
(paren
id|acpi_operand_object
op_star
op_star
id|stack_ptr
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ex_resolve_to_value&quot;
comma
id|stack_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack_ptr
op_logical_or
op_logical_neg
op_star
id|stack_ptr
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Internal - null pointer&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The entity pointed to by the Stack_ptr can be either&n;&t; * 1) A valid acpi_operand_object, or&n;&t; * 2) A acpi_namespace_node (Named_obj)&n;&t; */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
op_star
id|stack_ptr
)paren
op_eq
id|ACPI_DESC_TYPE_OPERAND
)paren
(brace
id|status
op_assign
id|acpi_ex_resolve_object_to_value
(paren
id|stack_ptr
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
)brace
multiline_comment|/*&n;&t; * Object on the stack may have changed if Acpi_ex_resolve_object_to_value()&n;&t; * was called (i.e., we can&squot;t use an _else_ here.)&n;&t; */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
op_star
id|stack_ptr
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
id|status
op_assign
id|acpi_ex_resolve_node_to_value
(paren
id|ACPI_CAST_INDIRECT_PTR
(paren
id|acpi_namespace_node
comma
id|stack_ptr
)paren
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
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Resolved object %p&bslash;n&quot;
comma
op_star
id|stack_ptr
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_resolve_object_to_value&n; *&n; * PARAMETERS:  Stack_ptr       - Pointer to a stack location that contains a&n; *                                ptr to an internal object.&n; *              Walk_state      - Current method state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Retrieve the value from an internal object.  The Reference type&n; *              uses the associated AML opcode to determine the value.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_resolve_object_to_value
id|acpi_ex_resolve_object_to_value
(paren
id|acpi_operand_object
op_star
op_star
id|stack_ptr
comma
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
id|stack_desc
suffix:semicolon
r_void
op_star
id|temp_node
suffix:semicolon
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|u16
id|opcode
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ex_resolve_object_to_value&quot;
)paren
suffix:semicolon
id|stack_desc
op_assign
op_star
id|stack_ptr
suffix:semicolon
multiline_comment|/* This is an acpi_operand_object  */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|stack_desc
)paren
)paren
(brace
r_case
id|INTERNAL_TYPE_REFERENCE
suffix:colon
id|opcode
op_assign
id|stack_desc-&gt;reference.opcode
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_NAME_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Convert indirect name ptr to a direct name ptr.&n;&t;&t;&t; * Then, Acpi_ex_resolve_node_to_value can be used to get the value&n;&t;&t;&t; */
id|temp_node
op_assign
id|stack_desc-&gt;reference.object
suffix:semicolon
multiline_comment|/* Delete the Reference Object */
id|acpi_ut_remove_reference
(paren
id|stack_desc
)paren
suffix:semicolon
multiline_comment|/* Put direct name pointer onto stack and exit */
(paren
op_star
id|stack_ptr
)paren
op_assign
id|temp_node
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_LOCAL_OP
suffix:colon
r_case
id|AML_ARG_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Get the local from the method&squot;s state info&n;&t;&t;&t; * Note: this increments the local&squot;s object reference count&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ds_method_data_get_value
(paren
id|opcode
comma
id|stack_desc-&gt;reference.offset
comma
id|walk_state
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Now we can delete the original Reference Object and&n;&t;&t;&t; * replace it with the resolve value&n;&t;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|stack_desc
)paren
suffix:semicolon
op_star
id|stack_ptr
op_assign
id|obj_desc
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[Arg/Local %d] Value_obj is %p&bslash;n&quot;
comma
id|stack_desc-&gt;reference.offset
comma
id|obj_desc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INDEX_OP
suffix:colon
r_switch
c_cond
(paren
id|stack_desc-&gt;reference.target_type
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
multiline_comment|/* Just return - leave the Reference on the stack */
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|obj_desc
op_assign
op_star
id|stack_desc-&gt;reference.where
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Valid obj descriptor, copy pointer to return value&n;&t;&t;&t;&t;&t; * (i.e., dereference the package index)&n;&t;&t;&t;&t;&t; * Delete the ref object, increment the returned object&n;&t;&t;&t;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|stack_desc
)paren
suffix:semicolon
id|acpi_ut_add_reference
(paren
id|obj_desc
)paren
suffix:semicolon
op_star
id|stack_ptr
op_assign
id|obj_desc
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * A NULL object descriptor means an unitialized element of&n;&t;&t;&t;&t;&t; * the package, can&squot;t dereference it&n;&t;&t;&t;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Attempt to deref an Index to NULL pkg element Idx=%p&bslash;n&quot;
comma
id|stack_desc
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_UNINITIALIZED_ELEMENT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Invalid reference object */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown Target_type %X in Index/Reference obj %p&bslash;n&quot;
comma
id|stack_desc-&gt;reference.target_type
comma
id|stack_desc
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
id|AML_DEBUG_OP
suffix:colon
multiline_comment|/* Just leave the object as-is */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unknown Reference opcode %X in %p&bslash;n&quot;
comma
id|opcode
comma
id|stack_desc
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
id|ACPI_TYPE_BUFFER
suffix:colon
id|status
op_assign
id|acpi_ds_get_buffer_arguments
(paren
id|stack_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|status
op_assign
id|acpi_ds_get_package_arguments
(paren
id|stack_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * These cases may never happen here, but just in case..&n;&t; */
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_REGION_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_BANK_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_INDEX_FIELD
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Field_read Source_desc=%p Type=%X&bslash;n&quot;
comma
id|stack_desc
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|stack_desc
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ex_read_data_from_field
(paren
id|walk_state
comma
id|stack_desc
comma
op_amp
id|obj_desc
)paren
suffix:semicolon
op_star
id|stack_ptr
op_assign
(paren
r_void
op_star
)paren
id|obj_desc
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
