multiline_comment|/******************************************************************************&n; *&n; * Module Name: dsobject - Dispatcher object management routines&n; *              $Revision: 65 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|MODULE_NAME
(paren
l_string|&quot;dsobject&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_init_one_object&n; *&n; * PARAMETERS:  Obj_handle      - Node&n; *              Level           - Current nesting level&n; *              Context         - Points to a init info struct&n; *              Return_value    - Not used&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Callback from Acpi_walk_namespace. Invoked for every object&n; *              within the  namespace.&n; *&n; *              Currently, the only objects that require initialization are:&n; *              1) Methods&n; *              2) Op Regions&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_init_one_object
id|acpi_ds_init_one_object
(paren
id|ACPI_HANDLE
id|obj_handle
comma
id|u32
id|level
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|return_value
)paren
(brace
id|ACPI_OBJECT_TYPE8
id|type
suffix:semicolon
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_INIT_WALK_INFO
op_star
id|info
op_assign
(paren
id|ACPI_INIT_WALK_INFO
op_star
)paren
id|context
suffix:semicolon
id|u8
id|table_revision
suffix:semicolon
id|PROC_NAME
(paren
l_string|&quot;Ds_init_one_object&quot;
)paren
suffix:semicolon
id|info-&gt;object_count
op_increment
suffix:semicolon
id|table_revision
op_assign
id|info-&gt;table_desc-&gt;pointer-&gt;revision
suffix:semicolon
multiline_comment|/*&n;&t; * We are only interested in objects owned by the table that&n;&t; * was just loaded&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|ACPI_NAMESPACE_NODE
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|owner_id
op_ne
id|info-&gt;table_desc-&gt;table_id
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* And even then, we are only interested in a few object types */
id|type
op_assign
id|acpi_ns_get_type
(paren
id|obj_handle
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|acpi_ds_initialize_region
(paren
id|obj_handle
)paren
suffix:semicolon
id|info-&gt;op_region_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|info-&gt;method_count
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the execution data width (32 or 64) based upon the&n;&t;&t; * revision number of the parent ACPI table.&n;&t;&t; */
r_if
c_cond
(paren
id|table_revision
op_eq
l_int|1
)paren
(brace
(paren
(paren
id|ACPI_NAMESPACE_NODE
op_star
)paren
id|obj_handle
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|ANOBJ_DATA_WIDTH_32
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Always parse methods to detect errors, we may delete&n;&t;&t; * the parse tree below&n;&t;&t; */
id|status
op_assign
id|acpi_ds_parse_method
(paren
id|obj_handle
)paren
suffix:semicolon
multiline_comment|/* TBD: [Errors] what do we do with an error? */
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
multiline_comment|/*&n;&t;&t; * Delete the parse tree.  We simple re-parse the method&n;&t;&t; * for every execution since there isn&squot;t much overhead&n;&t;&t; */
id|acpi_ns_delete_namespace_subtree
(paren
id|obj_handle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We ignore errors from above, and always return OK, since&n;&t; * we don&squot;t want to abort the walk on a single error.&n;&t; */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_initialize_objects&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Walk the entire namespace and perform any necessary&n; *              initialization on the objects found therein&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_initialize_objects
id|acpi_ds_initialize_objects
(paren
id|ACPI_TABLE_DESC
op_star
id|table_desc
comma
id|ACPI_NAMESPACE_NODE
op_star
id|start_node
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_INIT_WALK_INFO
id|info
suffix:semicolon
id|info.method_count
op_assign
l_int|0
suffix:semicolon
id|info.op_region_count
op_assign
l_int|0
suffix:semicolon
id|info.object_count
op_assign
l_int|0
suffix:semicolon
id|info.table_desc
op_assign
id|table_desc
suffix:semicolon
multiline_comment|/* Walk entire namespace from the supplied root */
id|status
op_assign
id|acpi_walk_namespace
(paren
id|ACPI_TYPE_ANY
comma
id|start_node
comma
id|ACPI_UINT32_MAX
comma
id|acpi_ds_init_one_object
comma
op_amp
id|info
comma
l_int|NULL
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_init_object_from_op&n; *&n; * PARAMETERS:  Op              - Parser op used to init the internal object&n; *              Opcode          - AML opcode associated with the object&n; *              Obj_desc        - Namespace object to be initialized&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize a namespace object from a parser Op and its&n; *              associated arguments.  The namespace object is a more compact&n; *              representation of the Op and its arguments.&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_init_object_from_op
id|acpi_ds_init_object_from_op
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|u16
id|opcode
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|obj_desc
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_PARSE_OBJECT
op_star
id|arg
suffix:semicolon
id|ACPI_PARSE2_OBJECT
op_star
id|byte_list
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|arg_desc
suffix:semicolon
id|ACPI_OPCODE_INFO
op_star
id|op_info
suffix:semicolon
id|PROC_NAME
(paren
l_string|&quot;Ds_init_object_from_op&quot;
)paren
suffix:semicolon
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
id|ACPI_GET_OP_TYPE
(paren
id|op_info
)paren
op_ne
id|ACPI_OP_TYPE_OPCODE
)paren
(brace
multiline_comment|/* Unknown opcode */
r_return
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* Get and prepare the first argument */
r_switch
c_cond
(paren
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|common.type
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/* First arg is a number */
id|acpi_ds_create_operand
(paren
id|walk_state
comma
id|op-&gt;value.arg
comma
l_int|0
)paren
suffix:semicolon
id|arg_desc
op_assign
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
op_minus
l_int|1
)braket
suffix:semicolon
id|acpi_ds_obj_stack_pop
(paren
l_int|1
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* Resolve the object (could be an arg or local) */
id|status
op_assign
id|acpi_ex_resolve_to_value
(paren
op_amp
id|arg_desc
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
id|acpi_ut_remove_reference
(paren
id|arg_desc
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* We are expecting a number */
r_if
c_cond
(paren
id|arg_desc-&gt;common.type
op_ne
id|ACPI_TYPE_INTEGER
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|arg_desc
)paren
suffix:semicolon
r_return
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the value, delete the internal object */
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.length
op_assign
(paren
id|u32
)paren
id|arg_desc-&gt;integer.value
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|arg_desc
)paren
suffix:semicolon
multiline_comment|/* Allocate the buffer */
r_if
c_cond
(paren
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.length
op_eq
l_int|0
)paren
(brace
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.pointer
op_assign
l_int|NULL
suffix:semicolon
id|REPORT_WARNING
(paren
(paren
l_string|&quot;Buffer created with zero length in AML&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.pointer
op_assign
id|acpi_ut_callocate
(paren
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.pointer
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Second arg is the buffer data (optional)&n;&t;&t; * Byte_list can be either individual bytes or a&n;&t;&t; * string initializer!&n;&t;&t; */
multiline_comment|/* skip first arg */
id|arg
op_assign
id|op-&gt;value.arg
suffix:semicolon
id|byte_list
op_assign
(paren
id|ACPI_PARSE2_OBJECT
op_star
)paren
id|arg-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|byte_list
)paren
(brace
r_if
c_cond
(paren
id|byte_list-&gt;opcode
op_ne
id|AML_INT_BYTELIST_OP
)paren
(brace
r_return
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
id|MEMCPY
(paren
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.pointer
comma
id|byte_list-&gt;data
comma
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|buffer.length
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
multiline_comment|/*&n;&t;&t; * When called, an internal package object has already&n;&t;&t; *  been built and is pointed to by *Obj_desc.&n;&t;&t; *  Acpi_ds_build_internal_object build another internal&n;&t;&t; *  package object, so remove reference to the original&n;&t;&t; *  so that it is deleted.  Error checking is done&n;&t;&t; *  within the remove reference function.&n;&t;&t; */
id|acpi_ut_remove_reference
c_func
(paren
op_star
id|obj_desc
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ds_build_internal_object
(paren
id|walk_state
comma
id|op
comma
id|obj_desc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|integer.value
op_assign
id|op-&gt;value.integer
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|string.pointer
op_assign
id|op-&gt;value.string
suffix:semicolon
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|string.length
op_assign
id|STRLEN
(paren
id|op-&gt;value.string
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
r_break
suffix:semicolon
r_case
id|INTERNAL_TYPE_REFERENCE
suffix:colon
r_switch
c_cond
(paren
id|ACPI_GET_OP_CLASS
(paren
id|op_info
)paren
)paren
(brace
r_case
id|OPTYPE_LOCAL_VARIABLE
suffix:colon
multiline_comment|/* Split the opcode into a base opcode + offset */
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|reference.opcode
op_assign
id|AML_LOCAL_OP
suffix:semicolon
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|reference.offset
op_assign
id|opcode
op_minus
id|AML_LOCAL_OP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPTYPE_METHOD_ARGUMENT
suffix:colon
multiline_comment|/* Split the opcode into a base opcode + offset */
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|reference.opcode
op_assign
id|AML_ARG_OP
suffix:semicolon
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|reference.offset
op_assign
id|opcode
op_minus
id|AML_ARG_OP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Constants, Literals, etc.. */
r_if
c_cond
(paren
id|op-&gt;opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
(brace
multiline_comment|/* Node was saved in Op */
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|reference.node
op_assign
id|op-&gt;node
suffix:semicolon
)brace
(paren
op_star
id|obj_desc
)paren
op_member_access_from_pointer
id|reference.opcode
op_assign
id|opcode
suffix:semicolon
r_break
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
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_build_internal_simple_obj&n; *&n; * PARAMETERS:  Op              - Parser object to be translated&n; *              Obj_desc_ptr    - Where the ACPI internal object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Translate a parser Op object to the equivalent namespace object&n; *              Simple objects are any objects other than a package object!&n; *&n; ****************************************************************************/
r_static
id|ACPI_STATUS
DECL|function|acpi_ds_build_internal_simple_obj
id|acpi_ds_build_internal_simple_obj
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|obj_desc_ptr
)paren
(brace
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_OBJECT_TYPE8
id|type
suffix:semicolon
id|ACPI_STATUS
id|status
suffix:semicolon
id|u32
id|length
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is an object reference.  If The name was&n;&t;&t; * previously looked up in the NS, it is stored in this op.&n;&t;&t; * Otherwise, go ahead and look it up now&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|op-&gt;node
)paren
(brace
id|status
op_assign
id|acpi_ns_lookup
(paren
id|walk_state-&gt;scope_info
comma
id|op-&gt;value.string
comma
id|ACPI_TYPE_ANY
comma
id|IMODE_EXECUTE
comma
id|NS_SEARCH_PARENT
op_or
id|NS_DONT_OPEN_SCOPE
comma
l_int|NULL
comma
(paren
id|ACPI_NAMESPACE_NODE
op_star
op_star
)paren
op_amp
(paren
id|op-&gt;node
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_NOT_FOUND
)paren
(brace
id|name
op_assign
l_int|NULL
suffix:semicolon
id|acpi_ns_externalize_name
(paren
id|ACPI_UINT32_MAX
comma
id|op-&gt;value.string
comma
op_amp
id|length
comma
op_amp
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
(brace
id|REPORT_WARNING
(paren
(paren
l_string|&quot;Reference %s at AML %X not found&bslash;n&quot;
comma
id|name
comma
id|op-&gt;aml_offset
)paren
)paren
suffix:semicolon
id|acpi_ut_free
(paren
id|name
)paren
suffix:semicolon
)brace
r_else
(brace
id|REPORT_WARNING
(paren
(paren
l_string|&quot;Reference %s at AML %X not found&bslash;n&quot;
comma
id|op-&gt;value.string
comma
id|op-&gt;aml_offset
)paren
)paren
suffix:semicolon
)brace
op_star
id|obj_desc_ptr
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t;&t; * The reference will be a Reference&n;&t;&t; * TBD: [Restructure] unless we really need a separate&n;&t;&t; *  type of INTERNAL_TYPE_REFERENCE change&n;&t;&t; *  Acpi_ds_map_opcode_to_data_type to handle this case&n;&t;&t; */
id|type
op_assign
id|INTERNAL_TYPE_REFERENCE
suffix:semicolon
)brace
r_else
(brace
id|type
op_assign
id|acpi_ds_map_opcode_to_data_type
(paren
id|op-&gt;opcode
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Create and init the internal ACPI object */
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_init_object_from_op
(paren
id|walk_state
comma
id|op
comma
id|op-&gt;opcode
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
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
op_star
id|obj_desc_ptr
op_assign
id|obj_desc
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_build_internal_package_obj&n; *&n; * PARAMETERS:  Op              - Parser object to be translated&n; *              Obj_desc_ptr    - Where the ACPI internal object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Translate a parser Op package object to the equivalent&n; *              namespace object&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_build_internal_package_obj
id|acpi_ds_build_internal_package_obj
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|obj_desc_ptr
)paren
(brace
id|ACPI_PARSE_OBJECT
op_star
id|arg
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_PACKAGE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* The first argument must be the package length */
id|arg
op_assign
id|op-&gt;value.arg
suffix:semicolon
id|obj_desc-&gt;package.count
op_assign
id|arg-&gt;value.integer
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate the array of pointers (ptrs to the&n;&t; * individual objects) Add an extra pointer slot so&n;&t; * that the list is always null terminated.&n;&t; */
id|obj_desc-&gt;package.elements
op_assign
id|acpi_ut_callocate
(paren
(paren
id|obj_desc-&gt;package.count
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc-&gt;package.elements
)paren
(brace
id|acpi_ut_delete_object_desc
(paren
id|obj_desc
)paren
suffix:semicolon
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|obj_desc-&gt;package.next_element
op_assign
id|obj_desc-&gt;package.elements
suffix:semicolon
multiline_comment|/*&n;&t; * Now init the elements of the package&n;&t; */
id|arg
op_assign
id|arg-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|arg
)paren
(brace
r_if
c_cond
(paren
id|arg-&gt;opcode
op_eq
id|AML_PACKAGE_OP
)paren
(brace
id|status
op_assign
id|acpi_ds_build_internal_package_obj
(paren
id|walk_state
comma
id|arg
comma
id|obj_desc-&gt;package.next_element
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|acpi_ds_build_internal_simple_obj
(paren
id|walk_state
comma
id|arg
comma
id|obj_desc-&gt;package.next_element
)paren
suffix:semicolon
)brace
id|obj_desc-&gt;package.next_element
op_increment
suffix:semicolon
id|arg
op_assign
id|arg-&gt;next
suffix:semicolon
)brace
op_star
id|obj_desc_ptr
op_assign
id|obj_desc
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_build_internal_object&n; *&n; * PARAMETERS:  Op              - Parser object to be translated&n; *              Obj_desc_ptr    - Where the ACPI internal object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Translate a parser Op object to the equivalent namespace&n; *              object&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_build_internal_object
id|acpi_ds_build_internal_object
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|obj_desc_ptr
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;opcode
op_eq
id|AML_PACKAGE_OP
)paren
(brace
id|status
op_assign
id|acpi_ds_build_internal_package_obj
(paren
id|walk_state
comma
id|op
comma
id|obj_desc_ptr
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|acpi_ds_build_internal_simple_obj
(paren
id|walk_state
comma
id|op
comma
id|obj_desc_ptr
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_node&n; *&n; * PARAMETERS:  Op              - Parser object to be translated&n; *              Obj_desc_ptr    - Where the ACPI internal object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_create_node
id|acpi_ds_create_node
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_NAMESPACE_NODE
op_star
id|node
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op-&gt;value.arg
)paren
(brace
multiline_comment|/* No arguments, there is nothing to do */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Build an internal object for the argument(s) */
id|status
op_assign
id|acpi_ds_build_internal_object
(paren
id|walk_state
comma
id|op-&gt;value.arg
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Re-type the object according to it&squot;s argument */
id|node-&gt;type
op_assign
id|obj_desc-&gt;common.type
suffix:semicolon
multiline_comment|/* Init obj */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|node
comma
id|obj_desc
comma
(paren
id|u8
)paren
id|node-&gt;type
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
r_return
(paren
id|status
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
