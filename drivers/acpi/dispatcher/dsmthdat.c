multiline_comment|/*******************************************************************************&n; *&n; * Module Name: dsmthdat - control method arguments and local variables&n; *              $Revision: 46 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|MODULE_NAME
(paren
l_string|&quot;dsmthdat&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_init&n; *&n; * PARAMETERS:  Walk_state          - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize the data structures that hold the method&squot;s arguments&n; *              and locals.  The data struct is an array of NTEs for each.&n; *              This allows Ref_of and De_ref_of to work properly for these&n; *              special data types.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_method_data_init
id|acpi_ds_method_data_init
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Walk_state fields are initialized to zero by the&n;&t; * Acpi_ut_callocate().&n;&t; *&n;&t; * An Node is assigned to each argument and local so&n;&t; * that Ref_of() can return a pointer to the Node.&n;&t; */
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
id|MOVE_UNALIGNED32_TO_32
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
id|name
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
id|data_type
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
id|MOVE_UNALIGNED32_TO_32
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
id|name
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
id|data_type
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
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_delete_all&n; *&n; * PARAMETERS:  Walk_state          - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Delete method locals and arguments.  Arguments are only&n; *              deleted if this method was called from another method.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_method_data_delete_all
id|acpi_ds_method_data_delete_all
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|u32
id|index
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|object
suffix:semicolon
multiline_comment|/* Delete the locals */
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
id|object
op_assign
id|walk_state-&gt;local_variables
(braket
id|index
)braket
dot
id|object
suffix:semicolon
r_if
c_cond
(paren
id|object
)paren
(brace
multiline_comment|/* Remove first */
id|walk_state-&gt;local_variables
(braket
id|index
)braket
dot
id|object
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Was given a ref when stored */
id|acpi_ut_remove_reference
(paren
id|object
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Delete the arguments */
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
id|object
op_assign
id|walk_state-&gt;arguments
(braket
id|index
)braket
dot
id|object
suffix:semicolon
r_if
c_cond
(paren
id|object
)paren
(brace
multiline_comment|/* Remove first */
id|walk_state-&gt;arguments
(braket
id|index
)braket
dot
id|object
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Was given a ref when stored */
id|acpi_ut_remove_reference
(paren
id|object
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_init_args&n; *&n; * PARAMETERS:  *Params         - Pointer to a parameter list for the method&n; *              Max_param_count - The arg count for this method&n; *              Walk_state      - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initialize arguments for a method&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_method_data_init_args
id|acpi_ds_method_data_init_args
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|params
comma
id|u32
id|max_param_count
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|u32
id|mindex
suffix:semicolon
id|u32
id|pindex
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|params
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy passed parameters into the new method stack frame  */
r_for
c_loop
(paren
id|pindex
op_assign
id|mindex
op_assign
l_int|0
suffix:semicolon
(paren
id|mindex
OL
id|MTH_NUM_ARGS
)paren
op_logical_and
(paren
id|pindex
OL
id|max_param_count
)paren
suffix:semicolon
id|mindex
op_increment
)paren
(brace
r_if
c_cond
(paren
id|params
(braket
id|pindex
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * A valid parameter.&n;&t;&t;&t; * Set the current method argument to the&n;&t;&t;&t; * Params[Pindex++] argument object descriptor&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ds_store_object_to_local
(paren
id|AML_ARG_OP
comma
id|mindex
comma
id|params
(braket
id|pindex
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
id|pindex
op_increment
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
)brace
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_get_entry&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to get&n; *              Entry               - Pointer to where a pointer to the stack&n; *                                    entry is returned.&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get the address of the object entry given by Opcode:Index&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_method_data_get_entry
id|acpi_ds_method_data_get_entry
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
op_star
id|entry
)paren
(brace
multiline_comment|/*&n;&t; * Get the requested object.&n;&t; * The stack &quot;Opcode&quot; is either a Local_variable or an Argument&n;&t; */
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
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
op_star
id|entry
op_assign
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
)paren
op_amp
id|walk_state-&gt;local_variables
(braket
id|index
)braket
dot
id|object
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
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
op_star
id|entry
op_assign
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
)paren
op_amp
id|walk_state-&gt;arguments
(braket
id|index
)braket
dot
id|object
suffix:semicolon
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_set_entry&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to get&n; *              Object              - Object to be inserted into the stack entry&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Insert an object onto the method stack at entry Opcode:Index.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_method_data_set_entry
id|acpi_ds_method_data_set_entry
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_OPERAND_OBJECT
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|entry
suffix:semicolon
multiline_comment|/* Get a pointer to the stack entry to set */
id|status
op_assign
id|acpi_ds_method_data_get_entry
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|entry
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
multiline_comment|/* Increment ref count so object can&squot;t be deleted while installed */
id|acpi_ut_add_reference
(paren
id|object
)paren
suffix:semicolon
multiline_comment|/* Install the object into the stack entry */
op_star
id|entry
op_assign
id|object
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_get_type&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument whose type&n; *                                      to get&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Data type of selected Arg or Local&n; *              Used only in Exec_monadic2()/Type_op.&n; *&n; ******************************************************************************/
id|ACPI_OBJECT_TYPE8
DECL|function|acpi_ds_method_data_get_type
id|acpi_ds_method_data_get_type
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|entry
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|object
suffix:semicolon
multiline_comment|/* Get a pointer to the requested stack entry */
id|status
op_assign
id|acpi_ds_method_data_get_entry
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|entry
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
(paren
id|ACPI_TYPE_NOT_FOUND
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the object from the method stack */
id|object
op_assign
op_star
id|entry
suffix:semicolon
multiline_comment|/* Get the object type */
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
multiline_comment|/* Any == 0 =&gt; &quot;uninitialized&quot; -- see spec 15.2.3.5.2.28 */
r_return
(paren
id|ACPI_TYPE_ANY
)paren
suffix:semicolon
)brace
r_return
(paren
id|object-&gt;common.type
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_get_node&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument whose type&n; *                                      to get&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Get the Node associated with a local or arg.&n; *&n; ******************************************************************************/
id|ACPI_NAMESPACE_NODE
op_star
DECL|function|acpi_ds_method_data_get_node
id|acpi_ds_method_data_get_node
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|node
op_assign
l_int|NULL
suffix:semicolon
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
r_return
(paren
id|node
)paren
suffix:semicolon
)brace
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
r_return
(paren
id|node
)paren
suffix:semicolon
)brace
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
r_break
suffix:semicolon
)brace
r_return
(paren
id|node
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_get_value&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to get&n; *              Walk_state          - Current walk state object&n; *              *Dest_desc          - Ptr to Descriptor into which selected Arg&n; *                                    or Local value should be copied&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Retrieve value of selected Arg or Local from the method frame&n; *              at the current top of the method stack.&n; *              Used only in Acpi_ex_resolve_to_value().&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_method_data_get_value
id|acpi_ds_method_data_get_value
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|dest_desc
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|entry
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|object
suffix:semicolon
multiline_comment|/* Validate the object descriptor */
r_if
c_cond
(paren
op_logical_neg
id|dest_desc
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get a pointer to the requested method stack entry */
id|status
op_assign
id|acpi_ds_method_data_get_entry
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|entry
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
multiline_comment|/* Get the object from the method stack */
id|object
op_assign
op_star
id|entry
suffix:semicolon
multiline_comment|/* Examine the returned object, it must be valid. */
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
multiline_comment|/*&n;&t;&t; * Index points to uninitialized object stack value.&n;&t;&t; * This means that either 1) The expected argument was&n;&t;&t; * not passed to the method, or 2) A local variable&n;&t;&t; * was referenced by the method (via the ASL)&n;&t;&t; * before it was initialized.  Either case is an error.&n;&t;&t; */
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_ARG_OP
suffix:colon
r_return
(paren
id|AE_AML_UNINITIALIZED_ARG
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_LOCAL_OP
suffix:colon
r_return
(paren
id|AE_AML_UNINITIALIZED_LOCAL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Index points to initialized and valid object stack value.&n;&t; * Return an additional reference to the object&n;&t; */
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
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_method_data_delete_value&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to delete&n; *              Walk_state          - Current walk state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Delete the entry at Opcode:Index on the method stack.  Inserts&n; *              a null into the stack slot after the object is deleted.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_method_data_delete_value
id|acpi_ds_method_data_delete_value
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|entry
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|object
suffix:semicolon
multiline_comment|/* Get a pointer to the requested entry */
id|status
op_assign
id|acpi_ds_method_data_get_entry
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|entry
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
multiline_comment|/* Get the current entry in this slot k */
id|object
op_assign
op_star
id|entry
suffix:semicolon
multiline_comment|/*&n;&t; * Undefine the Arg or Local by setting its descriptor&n;&t; * pointer to NULL. Locals/Args can contain both&n;&t; * ACPI_OPERAND_OBJECTS and ACPI_NAMESPACE_NODEs&n;&t; */
op_star
id|entry
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
id|VALID_DESCRIPTOR_TYPE
(paren
id|object
comma
id|ACPI_DESC_TYPE_INTERNAL
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * There is a valid object in this slot&n;&t;&t; * Decrement the reference count by one to balance the&n;&t;&t; * increment when the object was stored in the slot.&n;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|object
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_store_object_to_local&n; *&n; * PARAMETERS:  Opcode              - Either AML_LOCAL_OP or AML_ARG_OP&n; *              Index               - Which local_var or argument to set&n; *              Src_desc            - Value to be stored&n; *              Walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Store a value in an Arg or Local.  The Src_desc is installed&n; *              as the new value for the Arg or Local and the reference count&n; *              for Src_desc is incremented.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_store_object_to_local
id|acpi_ds_store_object_to_local
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_OPERAND_OBJECT
op_star
id|src_desc
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|entry
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|src_desc
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get a pointer to the requested method stack entry */
id|status
op_assign
id|acpi_ds_method_data_get_entry
(paren
id|opcode
comma
id|index
comma
id|walk_state
comma
op_amp
id|entry
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
op_star
id|entry
op_eq
id|src_desc
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If there is an object already in this slot, we either&n;&t; * have to delete it, or if this is an argument and there&n;&t; * is an object reference stored there, we have to do&n;&t; * an indirect store!&n;&t; */
r_if
c_cond
(paren
op_star
id|entry
)paren
(brace
multiline_comment|/*&n;&t;&t; * Check for an indirect store if an argument&n;&t;&t; * contains an object reference (stored as an Node).&n;&t;&t; * We don&squot;t allow this automatic dereferencing for&n;&t;&t; * locals, since a store to a local should overwrite&n;&t;&t; * anything there, including an object reference.&n;&t;&t; *&n;&t;&t; * If both Arg0 and Local0 contain Ref_of (Local4):&n;&t;&t; *&n;&t;&t; * Store (1, Arg0)             - Causes indirect store to local4&n;&t;&t; * Store (1, Local0)           - Stores 1 in local0, overwriting&n;&t;&t; *                                  the reference to local4&n;&t;&t; * Store (1, De_refof (Local0)) - Causes indirect store to local4&n;&t;&t; *&n;&t;&t; * Weird, but true.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|opcode
op_eq
id|AML_ARG_OP
)paren
op_logical_and
(paren
id|VALID_DESCRIPTOR_TYPE
(paren
op_star
id|entry
comma
id|ACPI_DESC_TYPE_NAMED
)paren
)paren
)paren
(brace
multiline_comment|/* Detach an existing object from the Node */
id|acpi_ns_detach_object
(paren
(paren
id|ACPI_NAMESPACE_NODE
op_star
)paren
op_star
id|entry
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Store this object into the Node&n;&t;&t;&t; * (do the indirect store)&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ns_attach_object
(paren
(paren
id|ACPI_NAMESPACE_NODE
op_star
)paren
op_star
id|entry
comma
id|src_desc
comma
id|src_desc-&gt;common.type
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
macro_line|#ifdef ACPI_ENABLE_IMPLICIT_CONVERSION
multiline_comment|/*&n;&t;&t; * Perform &quot;Implicit conversion&quot; of the new object to the type of the&n;&t;&t; * existing object&n;&t;&t; */
id|status
op_assign
id|acpi_ex_convert_to_target_type
(paren
(paren
op_star
id|entry
)paren
op_member_access_from_pointer
id|common.type
comma
op_amp
id|src_desc
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
macro_line|#endif
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
multiline_comment|/*&n;&t; * Install the Obj_stack descriptor (*Src_desc) into&n;&t; * the descriptor for the Arg or Local.&n;&t; * Install the new object in the stack entry&n;&t; * (increments the object reference count by one)&n;&t; */
id|status
op_assign
id|acpi_ds_method_data_set_entry
(paren
id|opcode
comma
id|index
comma
id|src_desc
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
multiline_comment|/* Normal exit */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
multiline_comment|/* Error exit */
id|cleanup
suffix:colon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
