multiline_comment|/******************************************************************************&n; *&n; * Module Name: nswalk - Functions for walking the ACPI namespace&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nswalk&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_get_next_node&n; *&n; * PARAMETERS:  Type                - Type of node to be searched for&n; *              parent_node         - Parent node whose children we are&n; *                                     getting&n; *              child_node          - Previous child that was found.&n; *                                    The NEXT child will be returned&n; *&n; * RETURN:      struct acpi_namespace_node - Pointer to the NEXT child or NULL if&n; *                                    none is found.&n; *&n; * DESCRIPTION: Return the next peer node within the namespace.  If Handle&n; *              is valid, Scope is ignored.  Otherwise, the first node&n; *              within Scope is returned.&n; *&n; ******************************************************************************/
r_struct
id|acpi_namespace_node
op_star
DECL|function|acpi_ns_get_next_node
id|acpi_ns_get_next_node
(paren
id|acpi_object_type
id|type
comma
r_struct
id|acpi_namespace_node
op_star
id|parent_node
comma
r_struct
id|acpi_namespace_node
op_star
id|child_node
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|next_node
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child_node
)paren
(brace
multiline_comment|/* It&squot;s really the parent&squot;s _scope_ that we want */
r_if
c_cond
(paren
id|parent_node-&gt;child
)paren
(brace
id|next_node
op_assign
id|parent_node-&gt;child
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Start search at the NEXT node */
id|next_node
op_assign
id|acpi_ns_get_next_valid_node
(paren
id|child_node
)paren
suffix:semicolon
)brace
multiline_comment|/* If any type is OK, we are done */
r_if
c_cond
(paren
id|type
op_eq
id|ACPI_TYPE_ANY
)paren
(brace
multiline_comment|/* next_node is NULL if we are at the end-of-list */
r_return
(paren
id|next_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Must search for the node -- but within this scope only */
r_while
c_loop
(paren
id|next_node
)paren
(brace
multiline_comment|/* If type matches, we are done */
r_if
c_cond
(paren
id|next_node-&gt;type
op_eq
id|type
)paren
(brace
r_return
(paren
id|next_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Otherwise, move on to the next node */
id|next_node
op_assign
id|acpi_ns_get_next_valid_node
(paren
id|next_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Not found */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_walk_namespace&n; *&n; * PARAMETERS:  Type                - acpi_object_type to search for&n; *              start_node          - Handle in namespace where search begins&n; *              max_depth           - Depth to which search is to reach&n; *              unlock_before_callback- Whether to unlock the NS before invoking&n; *                                    the callback routine&n; *              user_function       - Called when an object of &quot;Type&quot; is found&n; *              Context             - Passed to user function&n; *              return_value        - from the user_function if terminated early.&n; *                                    Otherwise, returns NULL.&n; * RETURNS:     Status&n; *&n; * DESCRIPTION: Performs a modified depth-first walk of the namespace tree,&n; *              starting (and ending) at the node specified by start_handle.&n; *              The user_function is called whenever a node that matches&n; *              the type parameter is found.  If the user function returns&n; *              a non-zero value, the search is terminated immediately and this&n; *              value is returned to the caller.&n; *&n; *              The point of this procedure is to provide a generic namespace&n; *              walk routine that can be called from multiple places to&n; *              provide multiple services;  the User Function can be tailored&n; *              to each task, whether it is a print function, a compare&n; *              function, etc.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_walk_namespace
id|acpi_ns_walk_namespace
(paren
id|acpi_object_type
id|type
comma
id|acpi_handle
id|start_node
comma
id|u32
id|max_depth
comma
id|u8
id|unlock_before_callback
comma
id|acpi_walk_callback
id|user_function
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
id|acpi_status
id|status
suffix:semicolon
id|acpi_status
id|mutex_status
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|child_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|parent_node
suffix:semicolon
id|acpi_object_type
id|child_type
suffix:semicolon
id|u32
id|level
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_walk_namespace&quot;
)paren
suffix:semicolon
multiline_comment|/* Special case for the namespace Root Node */
r_if
c_cond
(paren
id|start_node
op_eq
id|ACPI_ROOT_OBJECT
)paren
(brace
id|start_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
)brace
multiline_comment|/* Null child means &quot;get first node&quot; */
id|parent_node
op_assign
id|start_node
suffix:semicolon
id|child_node
op_assign
l_int|NULL
suffix:semicolon
id|child_type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|level
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Traverse the tree of nodes until we bubble back up to where we&n;&t; * started. When Level is zero, the loop is done because we have&n;&t; * bubbled up to (and passed) the original parent handle (start_entry)&n;&t; */
r_while
c_loop
(paren
id|level
OG
l_int|0
)paren
(brace
multiline_comment|/* Get the next node in this scope.  Null if not found */
id|status
op_assign
id|AE_OK
suffix:semicolon
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
multiline_comment|/*&n;&t;&t;&t; * Found node, Get the type if we are not&n;&t;&t;&t; * searching for ANY&n;&t;&t;&t; */
r_if
c_cond
(paren
id|type
op_ne
id|ACPI_TYPE_ANY
)paren
(brace
id|child_type
op_assign
id|child_node-&gt;type
suffix:semicolon
)brace
r_if
c_cond
(paren
id|child_type
op_eq
id|type
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Found a matching node, invoke the user&n;&t;&t;&t;&t; * callback function&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|unlock_before_callback
)paren
(brace
id|mutex_status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|mutex_status
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|mutex_status
)paren
suffix:semicolon
)brace
)brace
id|status
op_assign
id|user_function
(paren
id|child_node
comma
id|level
comma
id|context
comma
id|return_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlock_before_callback
)paren
(brace
id|mutex_status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|mutex_status
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|mutex_status
)paren
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|AE_OK
suffix:colon
r_case
id|AE_CTRL_DEPTH
suffix:colon
multiline_comment|/* Just keep going */
r_break
suffix:semicolon
r_case
id|AE_CTRL_TERMINATE
suffix:colon
multiline_comment|/* Exit now, with OK status */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All others are valid exceptions */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t;&t; * Depth first search:&n;&t;&t;&t; * Attempt to go down another level in the namespace&n;&t;&t;&t; * if we are allowed to.  Don&squot;t go any further if we&n;&t;&t;&t; * have reached the caller specified maximum depth&n;&t;&t;&t; * or if the user function has specified that the&n;&t;&t;&t; * maximum depth has been reached.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|level
OL
id|max_depth
)paren
op_logical_and
(paren
id|status
op_ne
id|AE_CTRL_DEPTH
)paren
)paren
(brace
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
multiline_comment|/*&n;&t;&t;&t;&t;&t; * There is at least one child of this&n;&t;&t;&t;&t;&t; * node, visit the onde&n;&t;&t;&t;&t;&t; */
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
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * No more children of this node (acpi_ns_get_next_node&n;&t;&t;&t; * failed), go back upwards in the namespace tree to&n;&t;&t;&t; * the node&squot;s parent.&n;&t;&t;&t; */
id|level
op_decrement
suffix:semicolon
id|child_node
op_assign
id|parent_node
suffix:semicolon
id|parent_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|parent_node
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Complete walk, not terminated by user function */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
