multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nsalloc - Namespace allocation and deletion utilities&n; *              $Revision: 50 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|MODULE_NAME
(paren
l_string|&quot;nsalloc&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_create_node&n; *&n; * PARAMETERS:&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION:&n; *&n; ******************************************************************************/
id|ACPI_NAMESPACE_NODE
op_star
DECL|function|acpi_ns_create_node
id|acpi_ns_create_node
(paren
id|u32
id|acpi_name
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|node
suffix:semicolon
id|node
op_assign
id|acpi_ut_callocate
(paren
r_sizeof
(paren
id|ACPI_NAMESPACE_NODE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|INCREMENT_NAME_TABLE_METRICS
(paren
r_sizeof
(paren
id|ACPI_NAMESPACE_NODE
)paren
)paren
suffix:semicolon
id|node-&gt;data_type
op_assign
id|ACPI_DESC_TYPE_NAMED
suffix:semicolon
id|node-&gt;name
op_assign
id|acpi_name
suffix:semicolon
id|node-&gt;reference_count
op_assign
l_int|1
suffix:semicolon
r_return
(paren
id|node
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_delete_node&n; *&n; * PARAMETERS:&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION:&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_delete_node
id|acpi_ns_delete_node
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|node
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|prev_node
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|next_node
suffix:semicolon
id|parent_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|node
)paren
suffix:semicolon
id|prev_node
op_assign
l_int|NULL
suffix:semicolon
id|next_node
op_assign
id|parent_node-&gt;child
suffix:semicolon
r_while
c_loop
(paren
id|next_node
op_ne
id|node
)paren
(brace
id|prev_node
op_assign
id|next_node
suffix:semicolon
id|next_node
op_assign
id|prev_node-&gt;peer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev_node
)paren
(brace
id|prev_node-&gt;peer
op_assign
id|next_node-&gt;peer
suffix:semicolon
r_if
c_cond
(paren
id|next_node-&gt;flags
op_amp
id|ANOBJ_END_OF_PEER_LIST
)paren
(brace
id|prev_node-&gt;flags
op_or_assign
id|ANOBJ_END_OF_PEER_LIST
suffix:semicolon
)brace
)brace
r_else
(brace
id|parent_node-&gt;child
op_assign
id|next_node-&gt;peer
suffix:semicolon
)brace
id|DECREMENT_NAME_TABLE_METRICS
(paren
r_sizeof
(paren
id|ACPI_NAMESPACE_NODE
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Detach an object if there is one&n;&t; */
r_if
c_cond
(paren
id|node-&gt;object
)paren
(brace
id|acpi_ns_detach_object
(paren
id|node
)paren
suffix:semicolon
)brace
id|acpi_ut_free
(paren
id|node
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_install_node&n; *&n; * PARAMETERS:  Walk_state      - Current state of the walk&n; *              Parent_node     - The parent of the new Node&n; *              Node        - The new Node to install&n; *              Type            - ACPI object type of the new Node&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Initialize a new entry within a namespace table.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_install_node
id|acpi_ns_install_node
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
comma
multiline_comment|/* Parent */
id|ACPI_NAMESPACE_NODE
op_star
id|node
comma
multiline_comment|/* New Child*/
id|ACPI_OBJECT_TYPE8
id|type
)paren
(brace
id|u16
id|owner_id
op_assign
id|TABLE_ID_DSDT
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|child_node
suffix:semicolon
multiline_comment|/*&n;&t; * Get the owner ID from the Walk state&n;&t; * The owner ID is used to track table deletion and&n;&t; * deletion of objects created by methods&n;&t; */
r_if
c_cond
(paren
id|walk_state
)paren
(brace
id|owner_id
op_assign
id|walk_state-&gt;owner_id
suffix:semicolon
)brace
multiline_comment|/* link the new entry into the parent and existing children */
multiline_comment|/* TBD: Could be first, last, or alphabetic */
id|child_node
op_assign
id|parent_node-&gt;child
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child_node
)paren
(brace
id|parent_node-&gt;child
op_assign
id|node
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|child_node-&gt;flags
op_amp
id|ANOBJ_END_OF_PEER_LIST
)paren
)paren
(brace
id|child_node
op_assign
id|child_node-&gt;peer
suffix:semicolon
)brace
id|child_node-&gt;peer
op_assign
id|node
suffix:semicolon
multiline_comment|/* Clear end-of-list flag */
id|child_node-&gt;flags
op_and_assign
op_complement
id|ANOBJ_END_OF_PEER_LIST
suffix:semicolon
)brace
multiline_comment|/* Init the new entry */
id|node-&gt;owner_id
op_assign
id|owner_id
suffix:semicolon
id|node-&gt;flags
op_or_assign
id|ANOBJ_END_OF_PEER_LIST
suffix:semicolon
id|node-&gt;peer
op_assign
id|parent_node
suffix:semicolon
multiline_comment|/*&n;&t; * If adding a name with unknown type, or having to&n;&t; * add the region in order to define fields in it, we&n;&t; * have a forward reference.&n;&t; */
r_if
c_cond
(paren
(paren
id|ACPI_TYPE_ANY
op_eq
id|type
)paren
op_logical_or
(paren
id|INTERNAL_TYPE_FIELD_DEFN
op_eq
id|type
)paren
op_logical_or
(paren
id|INTERNAL_TYPE_BANK_FIELD_DEFN
op_eq
id|type
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We don&squot;t want to abort here, however!&n;&t;&t; * We will fill in the actual type when the&n;&t;&t; * real definition is found later.&n;&t;&t; */
)brace
multiline_comment|/*&n;&t; * The Def_field_defn and Bank_field_defn cases are actually&n;&t; * looking up the Region in which the field will be defined&n;&t; */
r_if
c_cond
(paren
(paren
id|INTERNAL_TYPE_FIELD_DEFN
op_eq
id|type
)paren
op_logical_or
(paren
id|INTERNAL_TYPE_BANK_FIELD_DEFN
op_eq
id|type
)paren
)paren
(brace
id|type
op_assign
id|ACPI_TYPE_REGION
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Scope, Def_any, and Index_field_defn are bogus &quot;types&quot; which do&n;&t; * not actually have anything to do with the type of the name&n;&t; * being looked up.  Save any other value of Type as the type of&n;&t; * the entry.&n;&t; */
r_if
c_cond
(paren
(paren
id|type
op_ne
id|INTERNAL_TYPE_SCOPE
)paren
op_logical_and
(paren
id|type
op_ne
id|INTERNAL_TYPE_DEF_ANY
)paren
op_logical_and
(paren
id|type
op_ne
id|INTERNAL_TYPE_INDEX_FIELD_DEFN
)paren
)paren
(brace
id|node-&gt;type
op_assign
(paren
id|u8
)paren
id|type
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Increment the reference count(s) of all parents up to&n;&t; * the root!&n;&t; */
r_while
c_loop
(paren
(paren
id|node
op_assign
id|acpi_ns_get_parent_object
(paren
id|node
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|node-&gt;reference_count
op_increment
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_delete_children&n; *&n; * PARAMETERS:  Parent_node     - Delete this objects children&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Delete all children of the parent object. Deletes a&n; *              &quot;scope&quot;.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_delete_children
id|acpi_ns_delete_children
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|child_node
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|next_node
suffix:semicolon
id|u8
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_node
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* If no children, all done! */
id|child_node
op_assign
id|parent_node-&gt;child
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child_node
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Deallocate all children at this level&n;&t; */
r_do
(brace
multiline_comment|/* Get the things we need */
id|next_node
op_assign
id|child_node-&gt;peer
suffix:semicolon
id|flags
op_assign
id|child_node-&gt;flags
suffix:semicolon
multiline_comment|/* Grandchildren should have all been deleted already */
multiline_comment|/* Now we can free this child object */
id|DECREMENT_NAME_TABLE_METRICS
(paren
r_sizeof
(paren
id|ACPI_NAMESPACE_NODE
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Detach an object if there is one&n;&t;&t; */
r_if
c_cond
(paren
id|child_node-&gt;object
)paren
(brace
id|acpi_ns_detach_object
(paren
id|child_node
)paren
suffix:semicolon
)brace
id|acpi_ut_free
(paren
id|child_node
)paren
suffix:semicolon
multiline_comment|/* And move on to the next child in the list */
id|child_node
op_assign
id|next_node
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ANOBJ_END_OF_PEER_LIST
)paren
)paren
suffix:semicolon
multiline_comment|/* Clear the parent&squot;s child pointer */
id|parent_node-&gt;child
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_delete_namespace_subtree&n; *&n; * PARAMETERS:  None.&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Delete a subtree of the namespace.  This includes all objects&n; *              stored within the subtree.  Scope tables are deleted also&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ns_delete_namespace_subtree
id|acpi_ns_delete_namespace_subtree
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|child_node
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|u32
id|level
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_node
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|child_node
op_assign
l_int|0
suffix:semicolon
id|level
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Traverse the tree of objects until we bubble back up&n;&t; * to where we started.&n;&t; */
r_while
c_loop
(paren
id|level
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Get the next typed object in this scope.&n;&t;&t; * Null returned if not found&n;&t;&t; */
id|child_node
op_assign
id|acpi_ns_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|parent_node
comma
id|child_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child_node
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Found an object - delete the object within&n;&t;&t;&t; * the Value field&n;&t;&t;&t; */
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|child_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
id|acpi_ns_detach_object
(paren
id|child_node
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if this object has any children */
r_if
c_cond
(paren
id|acpi_ns_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|child_node
comma
l_int|0
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * There is at least one child of this object,&n;&t;&t;&t;&t; * visit the object&n;&t;&t;&t;&t; */
id|level
op_increment
suffix:semicolon
id|parent_node
op_assign
id|child_node
suffix:semicolon
id|child_node
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * No more children in this object.&n;&t;&t;&t; * We will move up to the grandparent.&n;&t;&t;&t; */
id|level
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Now delete all of the children of this parent&n;&t;&t;&t; * all at the same time.&n;&t;&t;&t; */
id|acpi_ns_delete_children
(paren
id|parent_node
)paren
suffix:semicolon
multiline_comment|/* New &quot;last child&quot; is this parent object */
id|child_node
op_assign
id|parent_node
suffix:semicolon
multiline_comment|/* Now we can move up the tree to the grandparent */
id|parent_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|parent_node
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_remove_reference&n; *&n; * PARAMETERS:  Node           - Named object whose reference count is to be&n; *                                decremented&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Remove a Node reference.  Decrements the reference count&n; *              of all parent Nodes up to the root.  Any object along&n; *              the way that reaches zero references is freed.&n; *&n; ******************************************************************************/
r_static
r_void
DECL|function|acpi_ns_remove_reference
id|acpi_ns_remove_reference
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|node
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|next_node
suffix:semicolon
multiline_comment|/*&n;&t; * Decrement the reference count(s) of this object and all&n;&t; * objects up to the root,  Delete anything with zero remaining references.&n;&t; */
id|next_node
op_assign
id|node
suffix:semicolon
r_while
c_loop
(paren
id|next_node
)paren
(brace
multiline_comment|/* Decrement the reference count on this object*/
id|next_node-&gt;reference_count
op_decrement
suffix:semicolon
multiline_comment|/* Delete the object if no more references */
r_if
c_cond
(paren
op_logical_neg
id|next_node-&gt;reference_count
)paren
(brace
multiline_comment|/* Delete all children and delete the object */
id|acpi_ns_delete_children
(paren
id|next_node
)paren
suffix:semicolon
id|acpi_ns_delete_node
(paren
id|next_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Move up to parent */
id|next_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|next_node
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_delete_namespace_by_owner&n; *&n; * PARAMETERS:  None.&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Delete entries within the namespace that are owned by a&n; *              specific ID.  Used to delete entire ACPI tables.  All&n; *              reference counts are updated.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ns_delete_namespace_by_owner
id|acpi_ns_delete_namespace_by_owner
(paren
id|u16
id|owner_id
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|child_node
suffix:semicolon
id|u32
id|level
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
suffix:semicolon
id|parent_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
id|child_node
op_assign
l_int|0
suffix:semicolon
id|level
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Traverse the tree of objects until we bubble back up&n;&t; * to where we started.&n;&t; */
r_while
c_loop
(paren
id|level
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Get the next typed object in this scope.&n;&t;&t; * Null returned if not found&n;&t;&t; */
id|child_node
op_assign
id|acpi_ns_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|parent_node
comma
id|child_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child_node
)paren
(brace
r_if
c_cond
(paren
id|child_node-&gt;owner_id
op_eq
id|owner_id
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Found an object - delete the object within&n;&t;&t;&t;&t; * the Value field&n;&t;&t;&t;&t; */
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|child_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
id|acpi_ns_detach_object
(paren
id|child_node
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Check if this object has any children */
r_if
c_cond
(paren
id|acpi_ns_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|child_node
comma
l_int|0
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * There is at least one child of this object,&n;&t;&t;&t;&t; * visit the object&n;&t;&t;&t;&t; */
id|level
op_increment
suffix:semicolon
id|parent_node
op_assign
id|child_node
suffix:semicolon
id|child_node
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|child_node-&gt;owner_id
op_eq
id|owner_id
)paren
(brace
id|acpi_ns_remove_reference
(paren
id|child_node
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * No more children in this object.  Move up to grandparent.&n;&t;&t;&t; */
id|level
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|level
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|parent_node-&gt;owner_id
op_eq
id|owner_id
)paren
(brace
id|acpi_ns_remove_reference
(paren
id|parent_node
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* New &quot;last child&quot; is this parent object */
id|child_node
op_assign
id|parent_node
suffix:semicolon
multiline_comment|/* Now we can move up the tree to the grandparent */
id|parent_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|parent_node
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
eof
