multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nsalloc - Namespace allocation and deletion utilities&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsalloc&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_create_node&n; *&n; * PARAMETERS:  acpi_name       - Name of the new node&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Create a namespace node&n; *&n; ******************************************************************************/
r_struct
id|acpi_namespace_node
op_star
DECL|function|acpi_ns_create_node
id|acpi_ns_create_node
(paren
id|u32
id|name
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_create_node&quot;
)paren
suffix:semicolon
id|node
op_assign
id|ACPI_MEM_CALLOCATE
(paren
r_sizeof
(paren
r_struct
id|acpi_namespace_node
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
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|ACPI_MEM_TRACKING
(paren
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_NSNODE
)braket
dot
id|total_allocated
op_increment
)paren
suffix:semicolon
id|node-&gt;name.integer
op_assign
id|name
suffix:semicolon
id|node-&gt;reference_count
op_assign
l_int|1
suffix:semicolon
id|ACPI_SET_DESCRIPTOR_TYPE
(paren
id|node
comma
id|ACPI_DESC_TYPE_NAMED
)paren
suffix:semicolon
id|return_PTR
(paren
id|node
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_delete_node&n; *&n; * PARAMETERS:  Node            - Node to be deleted&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Delete a namespace node&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_delete_node
id|acpi_ns_delete_node
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|parent_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|prev_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|next_node
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ns_delete_node&quot;
comma
id|node
)paren
suffix:semicolon
id|parent_node
op_assign
id|acpi_ns_get_parent_node
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
multiline_comment|/* Find the node that is the previous peer in the parent&squot;s child list */
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
multiline_comment|/* Node is not first child, unlink it */
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
multiline_comment|/* Node is first child (has no previous peer) */
r_if
c_cond
(paren
id|next_node-&gt;flags
op_amp
id|ANOBJ_END_OF_PEER_LIST
)paren
(brace
multiline_comment|/* No peers at all */
id|parent_node-&gt;child
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Link peer list to parent */
id|parent_node-&gt;child
op_assign
id|next_node-&gt;peer
suffix:semicolon
)brace
)brace
id|ACPI_MEM_TRACKING
(paren
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_NSNODE
)braket
dot
id|total_freed
op_increment
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Detach an object if there is one then delete the node&n;&t; */
id|acpi_ns_detach_object
(paren
id|node
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|node
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
macro_line|#ifdef ACPI_ALPHABETIC_NAMESPACE
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_compare_names&n; *&n; * PARAMETERS:  Name1           - First name to compare&n; *              Name2           - Second name to compare&n; *&n; * RETURN:      value from strncmp&n; *&n; * DESCRIPTION: Compare two ACPI names.  Names that are prefixed with an&n; *              underscore are forced to be alphabetically first.&n; *&n; ******************************************************************************/
r_int
DECL|function|acpi_ns_compare_names
id|acpi_ns_compare_names
(paren
r_char
op_star
id|name1
comma
r_char
op_star
id|name2
)paren
(brace
r_char
id|reversed_name1
(braket
id|ACPI_NAME_SIZE
)braket
suffix:semicolon
r_char
id|reversed_name2
(braket
id|ACPI_NAME_SIZE
)braket
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u32
id|j
suffix:semicolon
multiline_comment|/*&n;&t; * Replace all instances of &quot;underscore&quot; with a value that is smaller so&n;&t; * that all names that are prefixed with underscore(s) are alphabetically&n;&t; * first.&n;&t; *&n;&t; * Reverse the name bytewise so we can just do a 32-bit compare instead&n;&t; * of a strncmp.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
(paren
id|ACPI_NAME_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|i
OL
id|ACPI_NAME_SIZE
suffix:semicolon
id|i
op_increment
comma
id|j
op_decrement
)paren
(brace
id|reversed_name1
(braket
id|j
)braket
op_assign
id|name1
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|name1
(braket
id|i
)braket
op_eq
l_char|&squot;_&squot;
)paren
(brace
id|reversed_name1
(braket
id|j
)braket
op_assign
l_char|&squot;*&squot;
suffix:semicolon
)brace
id|reversed_name2
(braket
id|j
)braket
op_assign
id|name2
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|name2
(braket
id|i
)braket
op_eq
l_char|&squot;_&squot;
)paren
(brace
id|reversed_name2
(braket
id|j
)braket
op_assign
l_char|&squot;*&squot;
suffix:semicolon
)brace
)brace
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|reversed_name1
op_minus
op_star
(paren
r_int
op_star
)paren
id|reversed_name2
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_install_node&n; *&n; * PARAMETERS:  walk_state      - Current state of the walk&n; *              parent_node     - The parent of the new Node&n; *              Node            - The new Node to install&n; *              Type            - ACPI object type of the new Node&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Initialize a new namespace node and install it amongst&n; *              its peers.&n; *&n; *              Note: Current namespace lookup is linear search.  However, the&n; *              nodes are linked in alphabetical order to 1) put all reserved&n; *              names (start with underscore) first, and to 2) make a readable&n; *              namespace dump.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_install_node
id|acpi_ns_install_node
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_namespace_node
op_star
id|parent_node
comma
multiline_comment|/* Parent */
r_struct
id|acpi_namespace_node
op_star
id|node
comma
multiline_comment|/* New Child*/
id|acpi_object_type
id|type
)paren
(brace
id|u16
id|owner_id
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|child_node
suffix:semicolon
macro_line|#ifdef ACPI_ALPHABETIC_NAMESPACE
r_struct
id|acpi_namespace_node
op_star
id|previous_child_node
suffix:semicolon
macro_line|#endif
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_install_node&quot;
)paren
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
multiline_comment|/* Link the new entry into the parent and existing children */
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
id|node-&gt;flags
op_or_assign
id|ANOBJ_END_OF_PEER_LIST
suffix:semicolon
id|node-&gt;peer
op_assign
id|parent_node
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef ACPI_ALPHABETIC_NAMESPACE
multiline_comment|/*&n;&t;&t; * Walk the list whilst searching for the the correct&n;&t;&t; * alphabetic placement.&n;&t;&t; */
id|previous_child_node
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|acpi_ns_compare_names
(paren
id|acpi_ut_get_node_name
(paren
id|child_node
)paren
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|child_node-&gt;flags
op_amp
id|ANOBJ_END_OF_PEER_LIST
)paren
(brace
multiline_comment|/* Last peer;  Clear end-of-list flag */
id|child_node-&gt;flags
op_and_assign
op_complement
id|ANOBJ_END_OF_PEER_LIST
suffix:semicolon
multiline_comment|/* This node is the new peer to the child node */
id|child_node-&gt;peer
op_assign
id|node
suffix:semicolon
multiline_comment|/* This node is the new end-of-list */
id|node-&gt;flags
op_or_assign
id|ANOBJ_END_OF_PEER_LIST
suffix:semicolon
id|node-&gt;peer
op_assign
id|parent_node
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Get next peer */
id|previous_child_node
op_assign
id|child_node
suffix:semicolon
id|child_node
op_assign
id|child_node-&gt;peer
suffix:semicolon
)brace
multiline_comment|/* Did the node get inserted at the end-of-list? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|node-&gt;flags
op_amp
id|ANOBJ_END_OF_PEER_LIST
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Loop above terminated without reaching the end-of-list.&n;&t;&t;&t; * Insert the new node at the current location&n;&t;&t;&t; */
r_if
c_cond
(paren
id|previous_child_node
)paren
(brace
multiline_comment|/* Insert node alphabetically */
id|node-&gt;peer
op_assign
id|child_node
suffix:semicolon
id|previous_child_node-&gt;peer
op_assign
id|node
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Insert node alphabetically at start of list */
id|node-&gt;peer
op_assign
id|child_node
suffix:semicolon
id|parent_node-&gt;child
op_assign
id|node
suffix:semicolon
)brace
)brace
macro_line|#else
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
id|node-&gt;flags
op_or_assign
id|ANOBJ_END_OF_PEER_LIST
suffix:semicolon
id|node-&gt;peer
op_assign
id|parent_node
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Init the new entry */
id|node-&gt;owner_id
op_assign
id|owner_id
suffix:semicolon
id|node-&gt;type
op_assign
(paren
id|u8
)paren
id|type
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;%4.4s (%s) [Node %p Owner %X] added to %4.4s (%s) [Node %p]&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
comma
id|acpi_ut_get_type_name
(paren
id|node-&gt;type
)paren
comma
id|node
comma
id|owner_id
comma
id|acpi_ut_get_node_name
(paren
id|parent_node
)paren
comma
id|acpi_ut_get_type_name
(paren
id|parent_node-&gt;type
)paren
comma
id|parent_node
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Increment the reference count(s) of all parents up to&n;&t; * the root!&n;&t; */
r_while
c_loop
(paren
(paren
id|node
op_assign
id|acpi_ns_get_parent_node
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
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_delete_children&n; *&n; * PARAMETERS:  parent_node     - Delete this objects children&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Delete all children of the parent object. In other words,&n; *              deletes a &quot;scope&quot;.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_delete_children
id|acpi_ns_delete_children
(paren
r_struct
id|acpi_namespace_node
op_star
id|parent_node
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|child_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|next_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|u8
id|flags
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ns_delete_children&quot;
comma
id|parent_node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_node
)paren
(brace
id|return_VOID
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
id|return_VOID
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
r_if
c_cond
(paren
id|child_node-&gt;child
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Found a grandchild! P=%p C=%p&bslash;n&quot;
comma
id|parent_node
comma
id|child_node
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Now we can free this child object */
id|ACPI_MEM_TRACKING
(paren
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_NSNODE
)braket
dot
id|total_freed
op_increment
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Object %p, Remaining %X&bslash;n&quot;
comma
id|child_node
comma
id|acpi_gbl_current_node_count
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Detach an object if there is one, then free the child node&n;&t;&t; */
id|acpi_ns_detach_object
(paren
id|child_node
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Decrement the reference count(s) of all parents up to&n;&t;&t; * the root! (counts were incremented when the node was created)&n;&t;&t; */
id|node
op_assign
id|child_node
suffix:semicolon
r_while
c_loop
(paren
(paren
id|node
op_assign
id|acpi_ns_get_parent_node
(paren
id|node
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|node-&gt;reference_count
op_decrement
suffix:semicolon
)brace
multiline_comment|/* There should be only one reference remaining on this node */
r_if
c_cond
(paren
id|child_node-&gt;reference_count
op_ne
l_int|1
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Existing references (%d) on node being deleted (%p)&bslash;n&quot;
comma
id|child_node-&gt;reference_count
comma
id|child_node
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Now we can delete the node */
id|ACPI_MEM_FREE
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
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_delete_namespace_subtree&n; *&n; * PARAMETERS:  parent_node     - Root of the subtree to be deleted&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Delete a subtree of the namespace.  This includes all objects&n; *              stored within the subtree.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_delete_namespace_subtree
id|acpi_ns_delete_namespace_subtree
(paren
r_struct
id|acpi_namespace_node
op_star
id|parent_node
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|child_node
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|level
op_assign
l_int|1
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_delete_namespace_subtree&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_node
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Traverse the tree of objects until we bubble back up&n;&t; * to where we started.&n;&t; */
r_while
c_loop
(paren
id|level
OG
l_int|0
)paren
(brace
multiline_comment|/* Get the next node in this scope (NULL if none) */
id|child_node
op_assign
id|acpi_ns_get_next_node
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
multiline_comment|/* Found a child node - detach any attached object */
id|acpi_ns_detach_object
(paren
id|child_node
)paren
suffix:semicolon
multiline_comment|/* Check if this node has any children */
r_if
c_cond
(paren
id|acpi_ns_get_next_node
(paren
id|ACPI_TYPE_ANY
comma
id|child_node
comma
l_int|NULL
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * There is at least one child of this node,&n;&t;&t;&t;&t; * visit the node&n;&t;&t;&t;&t; */
id|level
op_increment
suffix:semicolon
id|parent_node
op_assign
id|child_node
suffix:semicolon
id|child_node
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * No more children of this parent node.&n;&t;&t;&t; * Move up to the grandparent.&n;&t;&t;&t; */
id|level
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Now delete all of the children of this parent&n;&t;&t;&t; * all at the same time.&n;&t;&t;&t; */
id|acpi_ns_delete_children
(paren
id|parent_node
)paren
suffix:semicolon
multiline_comment|/* New &quot;last child&quot; is this parent node */
id|child_node
op_assign
id|parent_node
suffix:semicolon
multiline_comment|/* Move up the tree to the grandparent */
id|parent_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|parent_node
)paren
suffix:semicolon
)brace
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_remove_reference&n; *&n; * PARAMETERS:  Node           - Named node whose reference count is to be&n; *                               decremented&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Remove a Node reference.  Decrements the reference count&n; *              of all parent Nodes up to the root.  Any node along&n; *              the way that reaches zero references is freed.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_remove_reference
id|acpi_ns_remove_reference
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|parent_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|this_node
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Decrement the reference count(s) of this node and all&n;&t; * nodes up to the root,  Delete anything with zero remaining references.&n;&t; */
id|this_node
op_assign
id|node
suffix:semicolon
r_while
c_loop
(paren
id|this_node
)paren
(brace
multiline_comment|/* Prepare to move up to parent */
id|parent_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|this_node
)paren
suffix:semicolon
multiline_comment|/* Decrement the reference count on this node */
id|this_node-&gt;reference_count
op_decrement
suffix:semicolon
multiline_comment|/* Delete the node if no more references */
r_if
c_cond
(paren
op_logical_neg
id|this_node-&gt;reference_count
)paren
(brace
multiline_comment|/* Delete all children and delete the node */
id|acpi_ns_delete_children
(paren
id|this_node
)paren
suffix:semicolon
id|acpi_ns_delete_node
(paren
id|this_node
)paren
suffix:semicolon
)brace
id|this_node
op_assign
id|parent_node
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_delete_namespace_by_owner&n; *&n; * PARAMETERS:  owner_id    - All nodes with this owner will be deleted&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Delete entries within the namespace that are owned by a&n; *              specific ID.  Used to delete entire ACPI tables.  All&n; *              reference counts are updated.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_delete_namespace_by_owner
id|acpi_ns_delete_namespace_by_owner
(paren
id|u16
id|owner_id
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|child_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|deletion_node
suffix:semicolon
id|u32
id|level
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|parent_node
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;ns_delete_namespace_by_owner&quot;
comma
id|owner_id
)paren
suffix:semicolon
id|parent_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
id|child_node
op_assign
l_int|NULL
suffix:semicolon
id|deletion_node
op_assign
l_int|NULL
suffix:semicolon
id|level
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Traverse the tree of nodes until we bubble back up&n;&t; * to where we started.&n;&t; */
r_while
c_loop
(paren
id|level
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Get the next child of this parent node. When child_node is NULL,&n;&t;&t; * the first child of the parent is returned&n;&t;&t; */
id|child_node
op_assign
id|acpi_ns_get_next_node
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
id|deletion_node
)paren
(brace
id|acpi_ns_remove_reference
(paren
id|deletion_node
)paren
suffix:semicolon
id|deletion_node
op_assign
l_int|NULL
suffix:semicolon
)brace
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
multiline_comment|/* Found a matching child node - detach any attached object */
id|acpi_ns_detach_object
(paren
id|child_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if this node has any children */
r_if
c_cond
(paren
id|acpi_ns_get_next_node
(paren
id|ACPI_TYPE_ANY
comma
id|child_node
comma
l_int|NULL
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * There is at least one child of this node,&n;&t;&t;&t;&t; * visit the node&n;&t;&t;&t;&t; */
id|level
op_increment
suffix:semicolon
id|parent_node
op_assign
id|child_node
suffix:semicolon
id|child_node
op_assign
l_int|NULL
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
id|deletion_node
op_assign
id|child_node
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * No more children of this parent node.&n;&t;&t;&t; * Move up to the grandparent.&n;&t;&t;&t; */
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
id|deletion_node
op_assign
id|parent_node
suffix:semicolon
)brace
)brace
multiline_comment|/* New &quot;last child&quot; is this parent node */
id|child_node
op_assign
id|parent_node
suffix:semicolon
multiline_comment|/* Move up the tree to the grandparent */
id|parent_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|parent_node
)paren
suffix:semicolon
)brace
)brace
id|return_VOID
suffix:semicolon
)brace
eof
