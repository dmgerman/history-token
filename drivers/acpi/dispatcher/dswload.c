multiline_comment|/******************************************************************************&n; *&n; * Module Name: dswload - Dispatcher namespace load callbacks&n; *              $Revision: 73 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acevents.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dswload&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_init_callbacks&n; *&n; * PARAMETERS:  Walk_state      - Current state of the parse tree walk&n; *              Pass_number     - 1, 2, or 3&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Init walk state callbacks&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_init_callbacks
id|acpi_ds_init_callbacks
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|u32
id|pass_number
)paren
(brace
r_switch
c_cond
(paren
id|pass_number
)paren
(brace
r_case
l_int|1
suffix:colon
id|walk_state-&gt;parse_flags
op_assign
id|ACPI_PARSE_LOAD_PASS1
op_or
id|ACPI_PARSE_DELETE_TREE
suffix:semicolon
id|walk_state-&gt;descending_callback
op_assign
id|acpi_ds_load1_begin_op
suffix:semicolon
id|walk_state-&gt;ascending_callback
op_assign
id|acpi_ds_load1_end_op
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|walk_state-&gt;parse_flags
op_assign
id|ACPI_PARSE_LOAD_PASS1
op_or
id|ACPI_PARSE_DELETE_TREE
suffix:semicolon
id|walk_state-&gt;descending_callback
op_assign
id|acpi_ds_load2_begin_op
suffix:semicolon
id|walk_state-&gt;ascending_callback
op_assign
id|acpi_ds_load2_end_op
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
id|walk_state-&gt;parse_flags
op_or_assign
id|ACPI_PARSE_EXECUTE
op_or
id|ACPI_PARSE_DELETE_TREE
suffix:semicolon
id|walk_state-&gt;descending_callback
op_assign
id|acpi_ds_exec_begin_op
suffix:semicolon
id|walk_state-&gt;ascending_callback
op_assign
id|acpi_ds_exec_end_op
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_load1_begin_op&n; *&n; * PARAMETERS:  Walk_state      - Current state of the parse tree walk&n; *              Op              - Op that has been just been reached in the&n; *                                walk;  Arguments have not been evaluated yet.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Descending callback used during the loading of ACPI tables.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_load1_begin_op
id|acpi_ds_load1_begin_op
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
op_star
id|out_op
)paren
(brace
id|acpi_parse_object
op_star
id|op
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_object_type
id|object_type
suffix:semicolon
id|NATIVE_CHAR
op_star
id|path
suffix:semicolon
id|u32
id|flags
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ds_load1_begin_op&quot;
)paren
suffix:semicolon
id|op
op_assign
id|walk_state-&gt;op
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Op=%p State=%p&bslash;n&quot;
comma
id|op
comma
id|walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/* We are only interested in opcodes that have an associated name */
r_if
c_cond
(paren
id|op
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_NAMED
)paren
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|walk_state-&gt;op_info
op_member_access_from_pointer
r_class
op_eq
id|AML_CLASS_EXECUTE
)paren
op_logical_or
(paren
id|walk_state-&gt;op_info
op_member_access_from_pointer
r_class
op_eq
id|AML_CLASS_CONTROL
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&bslash;n***EXECUTABLE OPCODE %s***&bslash;n&bslash;n&quot;
comma
id|walk_state-&gt;op_info-&gt;name
)paren
suffix:semicolon
op_star
id|out_op
op_assign
id|op
suffix:semicolon
r_return
(paren
id|AE_CTRL_SKIP
)paren
suffix:semicolon
)brace
macro_line|#endif
op_star
id|out_op
op_assign
id|op
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if this object has already been installed in the namespace */
r_if
c_cond
(paren
id|op-&gt;common.node
)paren
(brace
op_star
id|out_op
op_assign
id|op
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
id|path
op_assign
id|acpi_ps_get_next_namestring
(paren
op_amp
id|walk_state-&gt;parser_state
)paren
suffix:semicolon
multiline_comment|/* Map the raw opcode into an internal object type */
id|object_type
op_assign
id|walk_state-&gt;op_info-&gt;object_type
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;State=%p Op=%p [%s] &quot;
comma
id|walk_state
comma
id|op
comma
id|acpi_ut_get_type_name
(paren
id|object_type
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup the search flags.&n;&t; *&n;&t; * Since we are entering a name into the namespace, we do not want to&n;&t; *    enable the search-to-root upsearch.&n;&t; *&n;&t; * There are only two conditions where it is acceptable that the name&n;&t; *    already exists:&n;&t; *    1) the Scope() operator can reopen a scoping object that was&n;&t; *       previously defined (Scope, Method, Device, etc.)&n;&t; *    2) Whenever we are parsing a deferred opcode (Op_region, Buffer,&n;&t; *       Buffer_field, or Package), the name of the object is already&n;&t; *       in the namespace.&n;&t; */
id|flags
op_assign
id|ACPI_NS_NO_UPSEARCH
suffix:semicolon
r_if
c_cond
(paren
(paren
id|walk_state-&gt;opcode
op_ne
id|AML_SCOPE_OP
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|walk_state-&gt;parse_flags
op_amp
id|ACPI_PARSE_DEFERRED_OP
)paren
)paren
)paren
(brace
id|flags
op_or_assign
id|ACPI_NS_ERROR_IF_FOUND
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Cannot already exist&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Both Find or Create allowed&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Enter the named type into the internal namespace.  We enter the name&n;&t; * as we go downward in the parse tree.  Any necessary subobjects that involve&n;&t; * arguments to the opcode must be created as we go back up the parse tree later.&n;&t; */
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|path
comma
id|object_type
comma
id|ACPI_IMODE_LOAD_PASS1
comma
id|flags
comma
id|walk_state
comma
op_amp
(paren
id|node
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * For the scope op, we must check to make sure that the target is&n;&t; * one of the opcodes that actually opens a scope&n;&t; */
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_eq
id|AML_SCOPE_OP
)paren
(brace
r_switch
c_cond
(paren
id|node-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_ANY
suffix:colon
multiline_comment|/* Scope nodes are untyped (ANY) */
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
r_case
id|ACPI_TYPE_POWER
suffix:colon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
r_case
id|ACPI_TYPE_THERMAL
suffix:colon
multiline_comment|/* These are acceptable types */
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * These types we will allow, but we will change the type.  This&n;&t;&t;&t; * enables some existing code of the form:&n;&t;&t;&t; *&n;&t;&t;&t; *  Name (DEB, 0)&n;&t;&t;&t; *  Scope (DEB) { ... }&n;&t;&t;&t; */
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Invalid type (%s) for target of Scope operator [%4.4s], changing type to ANY&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|node-&gt;type
)paren
comma
id|path
)paren
)paren
suffix:semicolon
id|node-&gt;type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|walk_state-&gt;scope_info-&gt;common.value
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All other types are an error */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid type (%s) for target of Scope operator [%4.4s]&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|node-&gt;type
)paren
comma
id|path
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
multiline_comment|/* Create a new op */
id|op
op_assign
id|acpi_ps_alloc_op
(paren
id|walk_state-&gt;opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Initialize */
id|op-&gt;named.name
op_assign
id|node-&gt;name.integer
suffix:semicolon
macro_line|#if (defined (ACPI_NO_METHOD_EXECUTION) || defined (ACPI_CONSTANT_EVAL_ONLY))
id|op-&gt;named.path
op_assign
(paren
id|u8
op_star
)paren
id|path
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Put the Node in the &quot;op&quot; object that the parser uses, so we&n;&t; * can get it again quickly when this scope is closed&n;&t; */
id|op-&gt;common.node
op_assign
id|node
suffix:semicolon
id|acpi_ps_append_arg
(paren
id|acpi_ps_get_parent_scope
(paren
op_amp
id|walk_state-&gt;parser_state
)paren
comma
id|op
)paren
suffix:semicolon
op_star
id|out_op
op_assign
id|op
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_load1_end_op&n; *&n; * PARAMETERS:  Walk_state      - Current state of the parse tree walk&n; *              Op              - Op that has been just been completed in the&n; *                                walk;  Arguments have now been evaluated.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Ascending callback used during the loading of the namespace,&n; *              both control methods and everything else.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_load1_end_op
id|acpi_ds_load1_end_op
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_parse_object
op_star
id|op
suffix:semicolon
id|acpi_object_type
id|object_type
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ds_load1_end_op&quot;
)paren
suffix:semicolon
id|op
op_assign
id|walk_state-&gt;op
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Op=%p State=%p&bslash;n&quot;
comma
id|op
comma
id|walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/* We are only interested in opcodes that have an associated name */
r_if
c_cond
(paren
op_logical_neg
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
(paren
id|AML_NAMED
op_or
id|AML_FIELD
)paren
)paren
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the object type to determine if we should pop the scope */
id|object_type
op_assign
id|walk_state-&gt;op_info-&gt;object_type
suffix:semicolon
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
r_if
c_cond
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_FIELD
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_eq
id|AML_FIELD_OP
op_logical_or
id|walk_state-&gt;opcode
op_eq
id|AML_BANK_FIELD_OP
op_logical_or
id|walk_state-&gt;opcode
op_eq
id|AML_INDEX_FIELD_OP
)paren
(brace
id|status
op_assign
id|acpi_ds_init_field_objects
(paren
id|op
comma
id|walk_state
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
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
id|acpi_ex_create_region
(paren
id|op-&gt;named.data
comma
id|op-&gt;named.length
comma
(paren
id|ACPI_ADR_SPACE_TYPE
)paren
(paren
(paren
id|op-&gt;common.value.arg
)paren
op_member_access_from_pointer
id|common.value.integer
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_NAME_OP
)paren
(brace
multiline_comment|/* For Name opcode, get the object type from the argument */
r_if
c_cond
(paren
id|op-&gt;common.value.arg
)paren
(brace
id|object_type
op_assign
(paren
id|acpi_ps_get_opcode_info
(paren
(paren
id|op-&gt;common.value.arg
)paren
op_member_access_from_pointer
id|common.aml_opcode
)paren
)paren
op_member_access_from_pointer
id|object_type
suffix:semicolon
id|op-&gt;common.node-&gt;type
op_assign
(paren
id|u8
)paren
id|object_type
suffix:semicolon
)brace
)brace
multiline_comment|/* Pop the scope stack */
r_if
c_cond
(paren
id|acpi_ns_opens_scope
(paren
id|object_type
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;(%s): Popping scope for Op %p&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|object_type
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
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_load2_begin_op&n; *&n; * PARAMETERS:  Walk_state      - Current state of the parse tree walk&n; *              Op              - Op that has been just been reached in the&n; *                                walk;  Arguments have not been evaluated yet.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Descending callback used during the loading of ACPI tables.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_load2_begin_op
id|acpi_ds_load2_begin_op
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
op_star
id|out_op
)paren
(brace
id|acpi_parse_object
op_star
id|op
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_object_type
id|object_type
suffix:semicolon
id|NATIVE_CHAR
op_star
id|buffer_ptr
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_load2_begin_op&quot;
)paren
suffix:semicolon
id|op
op_assign
id|walk_state-&gt;op
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Op=%p State=%p&bslash;n&quot;
comma
id|op
comma
id|walk_state
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op
)paren
(brace
multiline_comment|/* We only care about Namespace opcodes here */
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_NSOPCODE
)paren
op_logical_and
(paren
id|walk_state-&gt;opcode
op_ne
id|AML_INT_NAMEPATH_OP
)paren
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_NAMED
)paren
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Get the name we are going to enter or lookup in the namespace&n;&t;&t; */
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
(brace
multiline_comment|/* For Namepath op, get the path string */
id|buffer_ptr
op_assign
id|op-&gt;common.value.string
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_ptr
)paren
(brace
multiline_comment|/* No name, just exit */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Get name from the op */
id|buffer_ptr
op_assign
(paren
id|NATIVE_CHAR
op_star
)paren
op_amp
id|op-&gt;named.name
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Get the namestring from the raw AML */
id|buffer_ptr
op_assign
id|acpi_ps_get_next_namestring
(paren
op_amp
id|walk_state-&gt;parser_state
)paren
suffix:semicolon
)brace
multiline_comment|/* Map the opcode into an internal object type */
id|object_type
op_assign
id|walk_state-&gt;op_info-&gt;object_type
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;State=%p Op=%p Type=%X&bslash;n&quot;
comma
id|walk_state
comma
id|op
comma
id|object_type
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_eq
id|AML_FIELD_OP
op_logical_or
id|walk_state-&gt;opcode
op_eq
id|AML_BANK_FIELD_OP
op_logical_or
id|walk_state-&gt;opcode
op_eq
id|AML_INDEX_FIELD_OP
)paren
(brace
id|node
op_assign
l_int|NULL
suffix:semicolon
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
(brace
multiline_comment|/*&n;&t;&t; * The Name_path is an object reference to an existing object. Don&squot;t enter the&n;&t;&t; * name into the namespace, but look it up for use later&n;&t;&t; */
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|buffer_ptr
comma
id|object_type
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_SEARCH_PARENT
comma
id|walk_state
comma
op_amp
(paren
id|node
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* All other opcodes */
r_if
c_cond
(paren
id|op
op_logical_and
id|op-&gt;common.node
)paren
(brace
multiline_comment|/* This op/node was previously entered into the namespace */
id|node
op_assign
id|op-&gt;common.node
suffix:semicolon
r_if
c_cond
(paren
id|acpi_ns_opens_scope
(paren
id|object_type
)paren
)paren
(brace
id|status
op_assign
id|acpi_ds_scope_stack_push
(paren
id|node
comma
id|object_type
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
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Enter the named type into the internal namespace.  We enter the name&n;&t;&t; * as we go downward in the parse tree.  Any necessary subobjects that involve&n;&t;&t; * arguments to the opcode must be created as we go back up the parse tree later.&n;&t;&t; */
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|buffer_ptr
comma
id|object_type
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_NO_UPSEARCH
comma
id|walk_state
comma
op_amp
(paren
id|node
)paren
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t;&t; * For the scope op, we must check to make sure that the target is&n;&t;&t; * one of the opcodes that actually opens a scope&n;&t;&t; */
r_if
c_cond
(paren
id|walk_state-&gt;opcode
op_eq
id|AML_SCOPE_OP
)paren
(brace
r_switch
c_cond
(paren
id|node-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_ANY
suffix:colon
multiline_comment|/* Scope nodes are untyped (ANY) */
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
r_case
id|ACPI_TYPE_POWER
suffix:colon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
r_case
id|ACPI_TYPE_THERMAL
suffix:colon
multiline_comment|/* These are acceptable types */
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * These types we will allow, but we will change the type.  This&n;&t;&t;&t;&t; * enables some existing code of the form:&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; *  Name (DEB, 0)&n;&t;&t;&t;&t; *  Scope (DEB) { ... }&n;&t;&t;&t;&t; */
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Invalid type (%s) for target of Scope operator [%4.4s], changing type to ANY&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|node-&gt;type
)paren
comma
id|buffer_ptr
)paren
)paren
suffix:semicolon
id|node-&gt;type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|walk_state-&gt;scope_info-&gt;common.value
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All other types are an error */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid type (%s) for target of Scope operator [%4.4s]&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|node-&gt;type
)paren
comma
id|buffer_ptr
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
multiline_comment|/* Create a new op */
id|op
op_assign
id|acpi_ps_alloc_op
(paren
id|walk_state-&gt;opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the new op */
r_if
c_cond
(paren
id|node
)paren
(brace
id|op-&gt;named.name
op_assign
id|node-&gt;name.integer
suffix:semicolon
)brace
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
)brace
multiline_comment|/*&n;&t;&t; * Put the Node in the &quot;op&quot; object that the parser uses, so we&n;&t;&t; * can get it again quickly when this scope is closed&n;&t;&t; */
id|op-&gt;common.node
op_assign
id|node
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_load2_end_op&n; *&n; * PARAMETERS:  Walk_state      - Current state of the parse tree walk&n; *              Op              - Op that has been just been completed in the&n; *                                walk;  Arguments have now been evaluated.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Ascending callback used during the loading of the namespace,&n; *              both control methods and everything else.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_load2_end_op
id|acpi_ds_load2_end_op
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_parse_object
op_star
id|op
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_object_type
id|object_type
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|acpi_namespace_node
op_star
id|new_node
suffix:semicolon
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
id|u32
id|i
suffix:semicolon
macro_line|#endif
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_load2_end_op&quot;
)paren
suffix:semicolon
id|op
op_assign
id|walk_state-&gt;op
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Opcode [%s] Op %p State %p&bslash;n&quot;
comma
id|walk_state-&gt;op_info-&gt;name
comma
id|op
comma
id|walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/* Only interested in opcodes that have namespace objects */
r_if
c_cond
(paren
op_logical_neg
(paren
id|walk_state-&gt;op_info-&gt;flags
op_amp
id|AML_NSOBJECT
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_SCOPE_OP
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Ending scope Op=%p State=%p&bslash;n&quot;
comma
id|op
comma
id|walk_state
)paren
)paren
suffix:semicolon
)brace
id|object_type
op_assign
id|walk_state-&gt;op_info-&gt;object_type
suffix:semicolon
multiline_comment|/*&n;&t; * Get the Node/name from the earlier lookup&n;&t; * (It was saved in the *op structure)&n;&t; */
id|node
op_assign
id|op-&gt;common.node
suffix:semicolon
multiline_comment|/*&n;&t; * Put the Node on the object stack (Contains the ACPI Name of&n;&t; * this object)&n;&t; */
id|walk_state-&gt;operands
(braket
l_int|0
)braket
op_assign
(paren
r_void
op_star
)paren
id|node
suffix:semicolon
id|walk_state-&gt;num_operands
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Pop the scope stack */
r_if
c_cond
(paren
id|acpi_ns_opens_scope
(paren
id|object_type
)paren
op_logical_and
(paren
id|op-&gt;common.aml_opcode
op_ne
id|AML_INT_METHODCALL_OP
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
id|object_type
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
multiline_comment|/*&n;&t; * Named operations are as follows:&n;&t; *&n;&t; * AML_ALIAS&n;&t; * AML_BANKFIELD&n;&t; * AML_CREATEBITFIELD&n;&t; * AML_CREATEBYTEFIELD&n;&t; * AML_CREATEDWORDFIELD&n;&t; * AML_CREATEFIELD&n;&t; * AML_CREATEQWORDFIELD&n;&t; * AML_CREATEWORDFIELD&n;&t; * AML_DATA_REGION&n;&t; * AML_DEVICE&n;&t; * AML_EVENT&n;&t; * AML_FIELD&n;&t; * AML_INDEXFIELD&n;&t; * AML_METHOD&n;&t; * AML_METHODCALL&n;&t; * AML_MUTEX&n;&t; * AML_NAME&n;&t; * AML_NAMEDFIELD&n;&t; * AML_OPREGION&n;&t; * AML_POWERRES&n;&t; * AML_PROCESSOR&n;&t; * AML_SCOPE&n;&t; * AML_THERMALZONE&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Create-Load [%s] State=%p Op=%p Named_obj=%p&bslash;n&quot;
comma
id|acpi_ps_get_opcode_name
(paren
id|op-&gt;common.aml_opcode
)paren
comma
id|walk_state
comma
id|op
comma
id|node
)paren
)paren
suffix:semicolon
multiline_comment|/* Decode the opcode */
id|arg
op_assign
id|op-&gt;common.value.arg
suffix:semicolon
r_switch
c_cond
(paren
id|walk_state-&gt;op_info-&gt;type
)paren
(brace
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
r_case
id|AML_TYPE_CREATE_FIELD
suffix:colon
multiline_comment|/*&n;&t;&t; * Create the field object, but the field buffer and index must&n;&t;&t; * be evaluated later during the execution phase&n;&t;&t; */
id|status
op_assign
id|acpi_ds_create_buffer_field
(paren
id|op
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_TYPE_NAMED_FIELD
suffix:colon
r_switch
c_cond
(paren
id|op-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_INDEX_FIELD_OP
suffix:colon
id|status
op_assign
id|acpi_ds_create_index_field
(paren
id|op
comma
(paren
id|acpi_handle
)paren
id|arg-&gt;common.node
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_BANK_FIELD_OP
suffix:colon
id|status
op_assign
id|acpi_ds_create_bank_field
(paren
id|op
comma
id|arg-&gt;common.node
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_FIELD_OP
suffix:colon
id|status
op_assign
id|acpi_ds_create_field
(paren
id|op
comma
id|arg-&gt;common.node
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All NAMED_FIELD opcodes must be handled above */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_TYPE_NAMED_SIMPLE
suffix:colon
id|status
op_assign
id|acpi_ds_create_operands
(paren
id|walk_state
comma
id|arg
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
r_switch
c_cond
(paren
id|op-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_PROCESSOR_OP
suffix:colon
id|status
op_assign
id|acpi_ex_create_processor
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_POWER_RES_OP
suffix:colon
id|status
op_assign
id|acpi_ex_create_power_resource
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_MUTEX_OP
suffix:colon
id|status
op_assign
id|acpi_ex_create_mutex
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_EVENT_OP
suffix:colon
id|status
op_assign
id|acpi_ex_create_event
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DATA_REGION_OP
suffix:colon
id|status
op_assign
id|acpi_ex_create_table_region
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_ALIAS_OP
suffix:colon
id|status
op_assign
id|acpi_ex_create_alias
(paren
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown opcode */
id|status
op_assign
id|AE_OK
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Delete operands */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|walk_state-&gt;num_operands
suffix:semicolon
id|i
op_increment
)paren
(brace
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
r_break
suffix:semicolon
macro_line|#endif /* ACPI_NO_METHOD_EXECUTION */
r_case
id|AML_TYPE_NAMED_COMPLEX
suffix:colon
r_switch
c_cond
(paren
id|op-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_METHOD_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Method_op Pkg_length Name_string Method_flags Term_list&n;&t;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;LOADING-Method: State=%p Op=%p Named_obj=%p&bslash;n&quot;
comma
id|walk_state
comma
id|op
comma
id|node
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_ns_get_attached_object
(paren
id|node
)paren
)paren
(brace
id|status
op_assign
id|acpi_ds_create_operands
(paren
id|walk_state
comma
id|arg
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
id|acpi_ex_create_method
(paren
id|op-&gt;named.data
comma
id|op-&gt;named.length
comma
id|walk_state
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
r_case
id|AML_REGION_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * The Op_region is not fully parsed at this time. Only valid argument is the Space_id.&n;&t;&t;&t; * (We must save the address of the AML of the address and length operands)&n;&t;&t;&t; */
multiline_comment|/*&n;&t;&t;&t; * If we have a valid region, initialize it&n;&t;&t;&t; * Namespace is NOT locked at this point.&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ev_initialize_region
(paren
id|acpi_ns_get_attached_object
(paren
id|node
)paren
comma
id|FALSE
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
multiline_comment|/*&n;&t;&t;&t;&t; *  If AE_NOT_EXIST is returned, it is not fatal&n;&t;&t;&t;&t; *  because many regions get created before a handler&n;&t;&t;&t;&t; *  is installed for said region.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|AE_NOT_EXIST
op_eq
id|status
)paren
(brace
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|AML_NAME_OP
suffix:colon
id|status
op_assign
id|acpi_ds_create_node
(paren
id|walk_state
comma
id|node
comma
id|op
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* ACPI_NO_METHOD_EXECUTION */
r_default
suffix:colon
multiline_comment|/* All NAMED_COMPLEX opcodes must be handled above */
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_CLASS_INTERNAL
suffix:colon
multiline_comment|/* case AML_INT_NAMEPATH_OP: */
r_break
suffix:semicolon
r_case
id|AML_CLASS_METHOD_CALL
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;RESOLVING-Method_call: State=%p Op=%p Named_obj=%p&bslash;n&quot;
comma
id|walk_state
comma
id|op
comma
id|node
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Lookup the method name and save the Node&n;&t;&t; */
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|arg-&gt;common.value.string
comma
id|ACPI_TYPE_ANY
comma
id|ACPI_IMODE_LOAD_PASS2
comma
id|ACPI_NS_SEARCH_PARENT
op_or
id|ACPI_NS_DONT_OPEN_SCOPE
comma
id|walk_state
comma
op_amp
(paren
id|new_node
)paren
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
multiline_comment|/*&n;&t;&t;&t; * Make sure that what we found is indeed a method&n;&t;&t;&t; * We didn&squot;t search for a method on purpose, to see if the name would resolve&n;&t;&t;&t; */
r_if
c_cond
(paren
id|new_node-&gt;type
op_ne
id|ACPI_TYPE_METHOD
)paren
(brace
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
)brace
multiline_comment|/* We could put the returned object (Node) on the object stack for later, but&n;&t;&t;&t; * for now, we will put it in the &quot;op&quot; object that the parser uses, so we&n;&t;&t;&t; * can get it again at the end of this scope&n;&t;&t;&t; */
id|op-&gt;common.node
op_assign
id|new_node
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|cleanup
suffix:colon
multiline_comment|/* Remove the Node pushed at the very beginning */
id|walk_state-&gt;operands
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|walk_state-&gt;num_operands
op_assign
l_int|0
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
