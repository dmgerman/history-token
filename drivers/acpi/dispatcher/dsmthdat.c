multiline_comment|/*******************************************************************************&n; *&n; * Module Name: dsmthdat - control method arguments and local variables&n; *              $Revision: 66 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dsmthdat&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_init&n; *&n; * PARAMETERS:  Walk_state          - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize the data structures that hold the method&squot;s arguments&n; *              and locals.  The data struct is an array of NTEs for each.&n; *              This allows Ref_of and De_ref_of to work properly for these&n; *              special data types.&n; *&n; * NOTES:       Walk_state fields are initialized to zero by the&n; *              ACPI_MEM_CALLOCATE().&n; *&n; *              A pseudo-Namespace Node is assigned to each argument and local&n; *              so that Ref_of() can return a pointer to the Node.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ds_method_data_init
id|acpi_ds_method_data_init
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_method_data_init&quot;
)paren
suffix:semicolon
multiline_comment|/* Init the method arguments */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MTH_NUM_ARGS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|walk_state-&gt;arguments
(braket
id|i
)braket
dot
id|name
comma
id|NAMEOF_ARG_NTE
)paren
suffix:semicolon
id|walk_state-&gt;arguments
(braket
id|i
)braket
dot
id|name.integer
op_or_assign
(paren
id|i
op_lshift
l_int|24
)paren
suffix:semicolon
id|walk_state-&gt;arguments
(braket
id|i
)braket
dot
id|descriptor
op_assign
id|ACPI_DESC_TYPE_NAMED
suffix:semicolon
id|walk_state-&gt;arguments
(braket
id|i
)braket
dot
id|type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|walk_state-&gt;arguments
(braket
id|i
)braket
dot
id|flags
op_assign
id|ANOBJ_END_OF_PEER_LIST
op_or
id|ANOBJ_METHOD_ARG
suffix:semicolon
)brace
multiline_comment|/* Init the method locals */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MTH_NUM_LOCALS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|walk_state-&gt;local_variables
(braket
id|i
)braket
dot
id|name
comma
id|NAMEOF_LOCAL_NTE
)paren
suffix:semicolon
id|walk_state-&gt;local_variables
(braket
id|i
)braket
dot
id|name.integer
op_or_assign
(paren
id|i
op_lshift
l_int|24
)paren
suffix:semicolon
id|walk_state-&gt;local_variables
(braket
id|i
)braket
dot
id|descriptor
op_assign
id|ACPI_DESC_TYPE_NAMED
suffix:semicolon
id|walk_state-&gt;local_variables
(braket
id|i
)braket
dot
id|type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|walk_state-&gt;local_variables
(braket
id|i
)braket
dot
id|flags
op_assign
id|ANOBJ_END_OF_PEER_LIST
op_or
id|ANOBJ_METHOD_LOCAL
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_delete_all&n; *&n; * PARAMETERS:  Walk_state          - Current walk state object&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Delete method locals and arguments.  Arguments are only&n; *              deleted if this method was called from another method.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ds_method_data_delete_all
id|acpi_ds_method_data_delete_all
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|u32
id|index
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_method_data_delete_all&quot;
)paren
suffix:semicolon
multiline_comment|/* Detach the locals */
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MTH_NUM_LOCALS
suffix:semicolon
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;local_variables
(braket
id|index
)braket
dot
id|object
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Deleting Local%d=%p&bslash;n&quot;
comma
id|index
comma
id|walk_state-&gt;local_variables
(braket
id|index
)braket
dot
id|object
)paren
)paren
suffix:semicolon
multiline_comment|/* Detach object (if present) and remove a reference */
id|acpi_ns_detach_object
(paren
op_amp
id|walk_state-&gt;local_variables
(braket
id|index
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Detach the arguments */
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MTH_NUM_ARGS
suffix:semicolon
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;arguments
(braket
id|index
)braket
dot
id|object
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Deleting Arg%d=%p&bslash;n&quot;
comma
id|index
comma
id|walk_state-&gt;arguments
(braket
id|index
)braket
dot
id|object
)paren
)paren
suffix:semicolon
multiline_comment|/* Detach object (if present) and remove a reference */
id|acpi_ns_detach_object
(paren
op_amp
id|walk_state-&gt;arguments
(braket
id|index
)braket
)paren
suffix:semicolon
)brace
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_init_args&n; *&n; * PARAMETERS:  *Params         - Pointer to a parameter list for the method&n; *              Max_param_count - The arg count for this method&n; *              Walk_state      - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize arguments for a method.  The parameter list is a list&n; *              of ACPI operand objects, either null terminated or whose length&n; *              is defined by Max_param_count.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_method_data_init_args
id|acpi_ds_method_data_init_args
(paren
id|acpi_operand_object
op_star
op_star
id|params
comma
id|u32
id|max_param_count
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u32
id|index
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ds_method_data_init_args&quot;
comma
id|params
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|params
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;No param list passed to method&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy passed parameters into the new method stack frame  */
r_while
c_loop
(paren
(paren
id|index
OL
id|MTH_NUM_ARGS
)paren
op_logical_and
(paren
id|index
OL
id|max_param_count
)paren
op_logical_and
id|params
(braket
id|index
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t; * A valid parameter.&n;&t;&t; * Store the argument in the method/walk descriptor&n;&t;&t; */
id|status
op_assign
id|acpi_ds_store_object_to_local
(paren
id|AML_ARG_OP
comma
id|index
comma
id|params
(braket
id|index
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
id|index
op_increment
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;%d args passed to method&bslash;n&quot;
comma
id|index
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_get_node&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument whose type&n; *                                      to get&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Get the Node associated with a local or arg.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_method_data_get_node
id|acpi_ds_method_data_get_node
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_namespace_node
op_star
op_star
id|node
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_method_data_get_node&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Method Locals and Arguments are supported&n;&t; */
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_LOCAL_OP
suffix:colon
r_if
c_cond
(paren
id|index
OG
id|MTH_MAX_LOCAL
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Local index %d is invalid (max %d)&bslash;n&quot;
comma
id|index
comma
id|MTH_MAX_LOCAL
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INVALID_INDEX
)paren
suffix:semicolon
)brace
multiline_comment|/* Return a pointer to the pseudo-node */
op_star
id|node
op_assign
op_amp
id|walk_state-&gt;local_variables
(braket
id|index
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_ARG_OP
suffix:colon
r_if
c_cond
(paren
id|index
OG
id|MTH_MAX_ARG
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Arg index %d is invalid (max %d)&bslash;n&quot;
comma
id|index
comma
id|MTH_MAX_ARG
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INVALID_INDEX
)paren
suffix:semicolon
)brace
multiline_comment|/* Return a pointer to the pseudo-node */
op_star
id|node
op_assign
op_amp
id|walk_state-&gt;arguments
(braket
id|index
)braket
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
l_string|&quot;Opcode %d is invalid&bslash;n&quot;
comma
id|opcode
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_BAD_OPCODE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_set_value&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to get&n; *              Object              - Object to be inserted into the stack entry&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Insert an object onto the method stack at entry Opcode:Index.&n; *              Note: There is no &quot;implicit conversion&quot; for locals.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_method_data_set_value
id|acpi_ds_method_data_set_value
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|acpi_operand_object
op_star
id|object
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_operand_object
op_star
id|new_desc
op_assign
id|object
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_method_data_set_value&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;obj %p op %X, ref count = %d [%s]&bslash;n&quot;
comma
id|object
comma
id|opcode
comma
id|object-&gt;common.reference_count
comma
id|acpi_ut_get_type_name
(paren
id|object-&gt;common.type
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the namespace node for the arg/local */
id|status
op_assign
id|acpi_ds_method_data_get_node
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|node
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
multiline_comment|/*&n;&t; * If the object has just been created and is not attached to anything,&n;&t; * (the reference count is 1), then we can just store it directly into&n;&t; * the arg/local.  Otherwise, we must copy it.&n;&t; */
r_if
c_cond
(paren
id|object-&gt;common.reference_count
OG
l_int|1
)paren
(brace
id|status
op_assign
id|acpi_ut_copy_iobject_to_iobject
(paren
id|object
comma
op_amp
id|new_desc
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Object Copied %p, new %p&bslash;n&quot;
comma
id|object
comma
id|new_desc
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Increment ref count so object can&squot;t be deleted while installed */
id|acpi_ut_add_reference
(paren
id|new_desc
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the object */
id|node-&gt;object
op_assign
id|new_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_get_type&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument whose type&n; *                                      to get&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Data type of current value of the selected Arg or Local&n; *&n; ******************************************************************************/
id|acpi_object_type
DECL|function|acpi_ds_method_data_get_type
id|acpi_ds_method_data_get_type
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_operand_object
op_star
id|object
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_method_data_get_type&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the namespace node for the arg/local */
id|status
op_assign
id|acpi_ds_method_data_get_node
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|node
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
id|return_VALUE
(paren
(paren
id|ACPI_TYPE_NOT_FOUND
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the object */
id|object
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
multiline_comment|/* Uninitialized local/arg, return TYPE_ANY */
id|return_VALUE
(paren
id|ACPI_TYPE_ANY
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the object type */
id|return_VALUE
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|object
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_get_value&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to get&n; *              Walk_state          - Current walk state object&n; *              *Dest_desc          - Ptr to Descriptor into which selected Arg&n; *                                    or Local value should be copied&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Retrieve value of selected Arg or Local from the method frame&n; *              at the current top of the method stack.&n; *              Used only in Acpi_ex_resolve_to_value().&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_method_data_get_value
id|acpi_ds_method_data_get_value
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_operand_object
op_star
op_star
id|dest_desc
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_operand_object
op_star
id|object
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_method_data_get_value&quot;
)paren
suffix:semicolon
multiline_comment|/* Validate the object descriptor */
r_if
c_cond
(paren
op_logical_neg
id|dest_desc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Null object descriptor pointer&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the namespace node for the arg/local */
id|status
op_assign
id|acpi_ds_method_data_get_node
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|node
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
multiline_comment|/* Get the object from the node */
id|object
op_assign
id|node-&gt;object
suffix:semicolon
multiline_comment|/* Examine the returned object, it must be valid. */
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
multiline_comment|/*&n;&t;&t; * Index points to uninitialized object.&n;&t;&t; * This means that either 1) The expected argument was&n;&t;&t; * not passed to the method, or 2) A local variable&n;&t;&t; * was referenced by the method (via the ASL)&n;&t;&t; * before it was initialized.  Either case is an error.&n;&t;&t; */
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_ARG_OP
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Uninitialized Arg[%d] at node %p&bslash;n&quot;
comma
id|index
comma
id|node
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_UNINITIALIZED_ARG
)paren
suffix:semicolon
r_case
id|AML_LOCAL_OP
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Uninitialized Local[%d] at node %p&bslash;n&quot;
comma
id|index
comma
id|node
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_UNINITIALIZED_LOCAL
)paren
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * The Index points to an initialized and valid object.&n;&t; * Return an additional reference to the object&n;&t; */
op_star
id|dest_desc
op_assign
id|object
suffix:semicolon
id|acpi_ut_add_reference
(paren
id|object
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_delete_value&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to delete&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Delete the entry at Opcode:Index on the method stack.  Inserts&n; *              a null into the stack slot after the object is deleted.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ds_method_data_delete_value
id|acpi_ds_method_data_delete_value
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_operand_object
op_star
id|object
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_method_data_delete_value&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the namespace node for the arg/local */
id|status
op_assign
id|acpi_ds_method_data_get_node
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|node
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
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Get the associated object */
id|object
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Undefine the Arg or Local by setting its descriptor&n;&t; * pointer to NULL. Locals/Args can contain both&n;&t; * ACPI_OPERAND_OBJECTS and ACPI_NAMESPACE_NODEs&n;&t; */
id|node-&gt;object
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|object
)paren
op_logical_and
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|object
)paren
op_eq
id|ACPI_DESC_TYPE_OPERAND
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * There is a valid object.&n;&t;&t; * Decrement the reference count by one to balance the&n;&t;&t; * increment when the object was stored.&n;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|object
)paren
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_store_object_to_local&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to set&n; *              Obj_desc            - Value to be stored&n; *              Walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Store a value in an Arg or Local.  The Obj_desc is installed&n; *              as the new value for the Arg or Local and the reference count&n; *              for Obj_desc is incremented.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_store_object_to_local
id|acpi_ds_store_object_to_local
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_operand_object
op_star
id|current_obj_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ds_store_object_to_local&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Opcode=%d Idx=%d Obj=%p&bslash;n&quot;
comma
id|opcode
comma
id|index
comma
id|obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the namespace node for the arg/local */
id|status
op_assign
id|acpi_ds_method_data_get_node
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|node
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
id|current_obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_obj_desc
op_eq
id|obj_desc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Obj=%p already installed!&bslash;n&quot;
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If there is an object already in this slot, we either&n;&t; * have to delete it, or if this is an argument and there&n;&t; * is an object reference stored there, we have to do&n;&t; * an indirect store!&n;&t; */
r_if
c_cond
(paren
id|current_obj_desc
)paren
(brace
multiline_comment|/*&n;&t;&t; * Check for an indirect store if an argument&n;&t;&t; * contains an object reference (stored as an Node).&n;&t;&t; * We don&squot;t allow this automatic dereferencing for&n;&t;&t; * locals, since a store to a local should overwrite&n;&t;&t; * anything there, including an object reference.&n;&t;&t; *&n;&t;&t; * If both Arg0 and Local0 contain Ref_of (Local4):&n;&t;&t; *&n;&t;&t; * Store (1, Arg0)             - Causes indirect store to local4&n;&t;&t; * Store (1, Local0)           - Stores 1 in local0, overwriting&n;&t;&t; *                                  the reference to local4&n;&t;&t; * Store (1, De_refof (Local0)) - Causes indirect store to local4&n;&t;&t; *&n;&t;&t; * Weird, but true.&n;&t;&t; */
r_if
c_cond
(paren
id|opcode
op_eq
id|AML_ARG_OP
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Make sure that the object is the correct type.  This may be overkill, but&n;&t;&t;&t; * it is here because references were NS nodes in the past.  Now they are&n;&t;&t;&t; * operand objects of type Reference.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|current_obj_desc
)paren
op_ne
id|ACPI_DESC_TYPE_OPERAND
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid descriptor type while storing to method arg: %X&bslash;n&quot;
comma
id|current_obj_desc-&gt;common.type
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * If we have a valid reference object that came from Ref_of(), do the&n;&t;&t;&t; * indirect store&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|current_obj_desc-&gt;common.type
op_eq
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
op_logical_and
(paren
id|current_obj_desc-&gt;reference.opcode
op_eq
id|AML_REF_OF_OP
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Arg (%p) is an Obj_ref(Node), storing in node %p&bslash;n&quot;
comma
id|obj_desc
comma
id|current_obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Store this object to the Node&n;&t;&t;&t;&t; * (perform the indirect store)&n;&t;&t;&t;&t; */
id|status
op_assign
id|acpi_ex_store_object_to_node
(paren
id|obj_desc
comma
id|current_obj_desc-&gt;reference.object
comma
id|walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Delete the existing object&n;&t;&t; * before storing the new one&n;&t;&t; */
id|acpi_ds_method_data_delete_value
(paren
id|opcode
comma
id|index
comma
id|walk_state
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Install the Obj_stack descriptor (*Obj_desc) into&n;&t; * the descriptor for the Arg or Local.&n;&t; * Install the new object in the stack entry&n;&t; * (increments the object reference count by one)&n;&t; */
id|status
op_assign
id|acpi_ds_method_data_set_value
(paren
id|opcode
comma
id|index
comma
id|obj_desc
comma
id|walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
