multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nssearch - Namespace search&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nssearch&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_search_node&n; *&n; * PARAMETERS:  *target_name        - Ascii ACPI name to search for&n; *              *Node               - Starting node where search will begin&n; *              Type                - Object type to match&n; *              **return_node       - Where the matched Named obj is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Search a single level of the namespace.  Performs a&n; *              simple search of the specified level, and does not add&n; *              entries or search parents.&n; *&n; *&n; *      Named object lists are built (and subsequently dumped) in the&n; *      order in which the names are encountered during the namespace load;&n; *&n; *      All namespace searching is linear in this implementation, but&n; *      could be easily modified to support any improved search&n; *      algorithm.  However, the linear search was chosen for simplicity&n; *      and because the trees are small and the other interpreter&n; *      execution overhead is relatively high.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_search_node
id|acpi_ns_search_node
(paren
id|u32
id|target_name
comma
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_object_type
id|type
comma
r_struct
id|acpi_namespace_node
op_star
op_star
id|return_node
)paren
(brace
r_struct
id|acpi_namespace_node
op_star
id|next_node
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_search_node&quot;
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG_OUTPUT
r_if
c_cond
(paren
id|ACPI_LV_NAMES
op_amp
id|acpi_dbg_level
)paren
(brace
r_char
op_star
id|scope_name
suffix:semicolon
id|scope_name
op_assign
id|acpi_ns_get_external_pathname
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scope_name
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Searching %s (%p) For [%4.4s] (%s)&bslash;n&quot;
comma
id|scope_name
comma
id|node
comma
(paren
r_char
op_star
)paren
op_amp
id|target_name
comma
id|acpi_ut_get_type_name
(paren
id|type
)paren
)paren
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|scope_name
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Search for name at this namespace level, which is to say that we&n;&t; * must search for the name among the children of this object&n;&t; */
id|next_node
op_assign
id|node-&gt;child
suffix:semicolon
r_while
c_loop
(paren
id|next_node
)paren
(brace
multiline_comment|/* Check for match against the name */
r_if
c_cond
(paren
id|next_node-&gt;name.integer
op_eq
id|target_name
)paren
(brace
multiline_comment|/* Resolve a control method alias if any */
r_if
c_cond
(paren
id|acpi_ns_get_type
(paren
id|next_node
)paren
op_eq
id|ACPI_TYPE_LOCAL_METHOD_ALIAS
)paren
(brace
id|next_node
op_assign
id|ACPI_CAST_PTR
(paren
r_struct
id|acpi_namespace_node
comma
id|next_node-&gt;object
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Found matching entry.&n;&t;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Name [%4.4s] (%s) %p found in scope [%4.4s] %p&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|target_name
comma
id|acpi_ut_get_type_name
(paren
id|next_node-&gt;type
)paren
comma
id|next_node
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
comma
id|node
)paren
)paren
suffix:semicolon
op_star
id|return_node
op_assign
id|next_node
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * The last entry in the list points back to the parent,&n;&t;&t; * so a flag is used to indicate the end-of-list&n;&t;&t; */
r_if
c_cond
(paren
id|next_node-&gt;flags
op_amp
id|ANOBJ_END_OF_PEER_LIST
)paren
(brace
multiline_comment|/* Searched entire list, we are done */
r_break
suffix:semicolon
)brace
multiline_comment|/* Didn&squot;t match name, move on to the next peer object */
id|next_node
op_assign
id|next_node-&gt;peer
suffix:semicolon
)brace
multiline_comment|/* Searched entire namespace level, not found */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Name [%4.4s] (%s) not found in search in scope [%4.4s] %p first child %p&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|target_name
comma
id|acpi_ut_get_type_name
(paren
id|type
)paren
comma
id|acpi_ut_get_node_name
(paren
id|node
)paren
comma
id|node
comma
id|node-&gt;child
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_search_parent_tree&n; *&n; * PARAMETERS:  *target_name        - Ascii ACPI name to search for&n; *              *Node               - Starting node where search will begin&n; *              Type                - Object type to match&n; *              **return_node       - Where the matched Node is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Called when a name has not been found in the current namespace&n; *              level.  Before adding it or giving up, ACPI scope rules require&n; *              searching enclosing scopes in cases identified by acpi_ns_local().&n; *&n; *              &quot;A name is located by finding the matching name in the current&n; *              name space, and then in the parent name space. If the parent&n; *              name space does not contain the name, the search continues&n; *              recursively until either the name is found or the name space&n; *              does not have a parent (the root of the name space).  This&n; *              indicates that the name is not found&quot; (From ACPI Specification,&n; *              section 5.3)&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ns_search_parent_tree
id|acpi_ns_search_parent_tree
(paren
id|u32
id|target_name
comma
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_object_type
id|type
comma
r_struct
id|acpi_namespace_node
op_star
op_star
id|return_node
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|parent_node
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_search_parent_tree&quot;
)paren
suffix:semicolon
id|parent_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|node
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If there is no parent (i.e., we are at the root) or type is &quot;local&quot;,&n;&t; * we won&squot;t be searching the parent tree.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|parent_node
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;[%4.4s] has no parent&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|target_name
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_ns_local
(paren
id|type
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;[%4.4s] type [%s] must be local to this scope (no parent search)&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|target_name
comma
id|acpi_ut_get_type_name
(paren
id|type
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
multiline_comment|/* Search the parent tree */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Searching parent [%4.4s] for [%4.4s]&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|parent_node
)paren
comma
(paren
r_char
op_star
)paren
op_amp
id|target_name
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Search parents until target is found or we have backed up to the root&n;&t; */
r_while
c_loop
(paren
id|parent_node
)paren
(brace
multiline_comment|/*&n;&t;&t; * Search parent scope.  Use TYPE_ANY because we don&squot;t care about the&n;&t;&t; * object type at this point, we only care about the existence of&n;&t;&t; * the actual name we are searching for.  Typechecking comes later.&n;&t;&t; */
id|status
op_assign
id|acpi_ns_search_node
(paren
id|target_name
comma
id|parent_node
comma
id|ACPI_TYPE_ANY
comma
id|return_node
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Not found here, go up another level&n;&t;&t; * (until we reach the root)&n;&t;&t; */
id|parent_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|parent_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Not found in parent tree */
id|return_ACPI_STATUS
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_search_and_enter&n; *&n; * PARAMETERS:  target_name         - Ascii ACPI name to search for (4 chars)&n; *              walk_state          - Current state of the walk&n; *              *Node               - Starting node where search will begin&n; *              interpreter_mode    - Add names only in ACPI_MODE_LOAD_PASS_x.&n; *                                    Otherwise,search only.&n; *              Type                - Object type to match&n; *              Flags               - Flags describing the search restrictions&n; *              **return_node       - Where the Node is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Search for a name segment in a single namespace level,&n; *              optionally adding it if it is not found.  If the passed&n; *              Type is not Any and the type previously stored in the&n; *              entry was Any (i.e. unknown), update the stored type.&n; *&n; *              In ACPI_IMODE_EXECUTE, search only.&n; *              In other modes, search and add if not found.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_search_and_enter
id|acpi_ns_search_and_enter
(paren
id|u32
id|target_name
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_interpreter_mode
id|interpreter_mode
comma
id|acpi_object_type
id|type
comma
id|u32
id|flags
comma
r_struct
id|acpi_namespace_node
op_star
op_star
id|return_node
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|new_node
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_search_and_enter&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|node
op_logical_or
op_logical_neg
id|target_name
op_logical_or
op_logical_neg
id|return_node
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Null param: Node %p Name %X return_node %p&bslash;n&quot;
comma
id|node
comma
id|target_name
comma
id|return_node
)paren
)paren
suffix:semicolon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ns_search_and_enter: Null parameter&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Name must consist of printable characters */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_acpi_name
(paren
id|target_name
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ns_search_and_enter: Bad character in ACPI Name: %X&bslash;n&quot;
comma
id|target_name
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_CHARACTER
)paren
suffix:semicolon
)brace
multiline_comment|/* Try to find the name in the namespace level specified by the caller */
op_star
id|return_node
op_assign
id|ACPI_ENTRY_NOT_FOUND
suffix:semicolon
id|status
op_assign
id|acpi_ns_search_node
(paren
id|target_name
comma
id|node
comma
id|type
comma
id|return_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we found it AND the request specifies that a find is an error,&n;&t;&t; * return the error&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|status
op_eq
id|AE_OK
)paren
op_logical_and
(paren
id|flags
op_amp
id|ACPI_NS_ERROR_IF_FOUND
)paren
)paren
(brace
id|status
op_assign
id|AE_ALREADY_EXISTS
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Either found it or there was an error&n;&t;&t; * -- finished either way&n;&t;&t; */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The name was not found.  If we are NOT performing the first pass&n;&t; * (name entry) of loading the namespace, search the parent tree (all the&n;&t; * way to the root if necessary.) We don&squot;t want to perform the parent&n;&t; * search when the namespace is actually being loaded.  We want to perform&n;&t; * the search when namespace references are being resolved (load pass 2)&n;&t; * and during the execution phase.&n;&t; */
r_if
c_cond
(paren
(paren
id|interpreter_mode
op_ne
id|ACPI_IMODE_LOAD_PASS1
)paren
op_logical_and
(paren
id|flags
op_amp
id|ACPI_NS_SEARCH_PARENT
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Not found at this level - search parent tree according to the&n;&t;&t; * ACPI specification&n;&t;&t; */
id|status
op_assign
id|acpi_ns_search_parent_tree
(paren
id|target_name
comma
id|node
comma
id|type
comma
id|return_node
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * In execute mode, just search, never add names.  Exit now.&n;&t; */
r_if
c_cond
(paren
id|interpreter_mode
op_eq
id|ACPI_IMODE_EXECUTE
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;%4.4s Not found in %p [Not adding]&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|target_name
comma
id|node
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
multiline_comment|/* Create the new named object */
id|new_node
op_assign
id|acpi_ns_create_node
(paren
id|target_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_node
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the new object into the parent&squot;s list of children */
id|acpi_ns_install_node
(paren
id|walk_state
comma
id|node
comma
id|new_node
comma
id|type
)paren
suffix:semicolon
op_star
id|return_node
op_assign
id|new_node
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
