multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nsaccess - Top-level functions for accessing ACPI namespace&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsaccess&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_root_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Allocate and initialize the default root named objects&n; *&n; * MUTEX:       Locks namespace for entire execution&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_root_initialize
id|acpi_ns_root_initialize
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_const
r_struct
id|acpi_predefined_names
op_star
id|init_val
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|new_node
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_string
id|val
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_root_initialize&quot;
)paren
suffix:semicolon
id|status
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
multiline_comment|/*&n;&t; * The global root ptr is initially NULL, so a non-NULL value indicates&n;&t; * that acpi_ns_root_initialize() has already been called; just return.&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_root_node
)paren
(brace
id|status
op_assign
id|AE_OK
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Tell the rest of the subsystem that the root is initialized&n;&t; * (This is OK because the namespace is locked)&n;&t; */
id|acpi_gbl_root_node
op_assign
op_amp
id|acpi_gbl_root_node_struct
suffix:semicolon
multiline_comment|/* Enter the pre-defined names in the name table */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Entering predefined entries into namespace&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|init_val
op_assign
id|acpi_gbl_pre_defined_names
suffix:semicolon
id|init_val-&gt;name
suffix:semicolon
id|init_val
op_increment
)paren
(brace
multiline_comment|/* _OSI is optional for now, will be permanent later */
r_if
c_cond
(paren
op_logical_neg
id|ACPI_STRCMP
(paren
id|init_val-&gt;name
comma
l_string|&quot;_OSI&quot;
)paren
op_logical_and
op_logical_neg
id|acpi_gbl_create_osi_method
)paren
(brace
r_continue
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ns_lookup
(paren
l_int|NULL
comma
id|init_val-&gt;name
comma
id|init_val-&gt;type
comma
id|ACPI_IMODE_LOAD_PASS2
comma
id|ACPI_NS_NO_UPSEARCH
comma
l_int|NULL
comma
op_amp
id|new_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_or
(paren
op_logical_neg
id|new_node
)paren
)paren
multiline_comment|/* Must be on same line for code converter */
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not create predefined name %s, %s&bslash;n&quot;
comma
id|init_val-&gt;name
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Name entered successfully.&n;&t;&t; * If entry in pre_defined_names[] specifies an&n;&t;&t; * initial value, create the initial value.&n;&t;&t; */
r_if
c_cond
(paren
id|init_val-&gt;val
)paren
(brace
id|status
op_assign
id|acpi_os_predefined_override
(paren
id|init_val
comma
op_amp
id|val
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not override predefined %s&bslash;n&quot;
comma
id|init_val-&gt;name
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
(brace
id|val
op_assign
id|init_val-&gt;val
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Entry requests an initial value, allocate a&n;&t;&t;&t; * descriptor for it.&n;&t;&t;&t; */
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|init_val-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Convert value string from table entry to&n;&t;&t;&t; * internal representation. Only types actually&n;&t;&t;&t; * used for initial values are implemented here.&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|init_val-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|obj_desc-&gt;method.param_count
op_assign
(paren
id|u8
)paren
id|ACPI_TO_INTEGER
(paren
id|val
)paren
suffix:semicolon
id|obj_desc-&gt;common.flags
op_or_assign
id|AOPOBJ_DATA_VALID
suffix:semicolon
macro_line|#if defined (_ACPI_ASL_COMPILER) || defined (_ACPI_DUMP_App)
multiline_comment|/*&n;&t;&t;&t;&t; * i_aSL Compiler cheats by putting parameter count&n;&t;&t;&t;&t; * in the owner_iD&n;&t;&t;&t;&t; */
id|new_node-&gt;owner_id
op_assign
id|obj_desc-&gt;method.param_count
suffix:semicolon
macro_line|#else
multiline_comment|/* Mark this as a very SPECIAL method */
id|obj_desc-&gt;method.method_flags
op_assign
id|AML_METHOD_INTERNAL_ONLY
suffix:semicolon
id|obj_desc-&gt;method.implementation
op_assign
id|acpi_ut_osi_implementation
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|obj_desc-&gt;integer.value
op_assign
id|ACPI_TO_INTEGER
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * Build an object around the static string&n;&t;&t;&t;&t; */
id|obj_desc-&gt;string.length
op_assign
(paren
id|u32
)paren
id|ACPI_STRLEN
(paren
id|val
)paren
suffix:semicolon
id|obj_desc-&gt;string.pointer
op_assign
id|val
suffix:semicolon
id|obj_desc-&gt;common.flags
op_or_assign
id|AOPOBJ_STATIC_POINTER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_MUTEX
suffix:colon
id|obj_desc-&gt;mutex.node
op_assign
id|new_node
suffix:semicolon
id|obj_desc-&gt;mutex.sync_level
op_assign
(paren
id|u8
)paren
(paren
id|ACPI_TO_INTEGER
(paren
id|val
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_STRCMP
(paren
id|init_val-&gt;name
comma
l_string|&quot;_GL_&quot;
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Create a counting semaphore for the&n;&t;&t;&t;&t;&t; * global lock&n;&t;&t;&t;&t;&t; */
id|status
op_assign
id|acpi_os_create_semaphore
(paren
id|ACPI_NO_UNIT_LIMIT
comma
l_int|1
comma
op_amp
id|obj_desc-&gt;mutex.semaphore
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
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * We just created the mutex for the&n;&t;&t;&t;&t;&t; * global lock, save it&n;&t;&t;&t;&t;&t; */
id|acpi_gbl_global_lock_semaphore
op_assign
id|obj_desc-&gt;mutex.semaphore
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Create a mutex */
id|status
op_assign
id|acpi_os_create_semaphore
(paren
l_int|1
comma
l_int|1
comma
op_amp
id|obj_desc-&gt;mutex.semaphore
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
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Unsupported initial type value %X&bslash;n&quot;
comma
id|init_val-&gt;type
)paren
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|obj_desc
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Store pointer to value descriptor in the Node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|new_node
comma
id|obj_desc
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Remove local reference to the object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
multiline_comment|/* Save a handle to &quot;_GPE&quot;, it is always present */
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
id|status
op_assign
id|acpi_ns_get_node_by_path
(paren
l_string|&quot;&bslash;&bslash;_GPE&quot;
comma
l_int|NULL
comma
id|ACPI_NS_NO_UPSEARCH
comma
op_amp
id|acpi_gbl_fadt_gpe_device
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_lookup&n; *&n; * PARAMETERS:  prefix_node     - Search scope if name is not fully qualified&n; *              Pathname        - Search pathname, in internal format&n; *                                (as represented in the AML stream)&n; *              Type            - Type associated with name&n; *              interpreter_mode - IMODE_LOAD_PASS2 =&gt; add name if not found&n; *              Flags           - Flags describing the search restrictions&n; *              walk_state      - Current state of the walk&n; *              return_node     - Where the Node is placed (if found&n; *                                or created successfully)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Find or enter the passed name in the name space.&n; *              Log an error if name not found in Exec mode.&n; *&n; * MUTEX:       Assumes namespace is locked.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_lookup
id|acpi_ns_lookup
(paren
r_union
id|acpi_generic_state
op_star
id|scope_info
comma
r_char
op_star
id|pathname
comma
id|acpi_object_type
id|type
comma
id|acpi_interpreter_mode
id|interpreter_mode
comma
id|u32
id|flags
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
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
r_char
op_star
id|path
op_assign
id|pathname
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|prefix_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|current_node
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|this_node
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|num_segments
suffix:semicolon
id|u32
id|num_carats
suffix:semicolon
id|acpi_name
id|simple_name
suffix:semicolon
id|acpi_object_type
id|type_to_check_for
suffix:semicolon
id|acpi_object_type
id|this_search_type
suffix:semicolon
id|u32
id|search_parent_flag
op_assign
id|ACPI_NS_SEARCH_PARENT
suffix:semicolon
id|u32
id|local_flags
op_assign
id|flags
op_amp
op_complement
(paren
id|ACPI_NS_ERROR_IF_FOUND
op_or
id|ACPI_NS_SEARCH_PARENT
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_lookup&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|return_node
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|acpi_gbl_ns_lookup_count
op_increment
suffix:semicolon
op_star
id|return_node
op_assign
id|ACPI_ENTRY_NOT_FOUND
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_root_node
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_NAMESPACE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the prefix scope.&n;&t; * A null scope means use the root scope&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|scope_info
)paren
op_logical_or
(paren
op_logical_neg
id|scope_info-&gt;scope.node
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Null scope prefix, using root node (%p)&bslash;n&quot;
comma
id|acpi_gbl_root_node
)paren
)paren
suffix:semicolon
id|prefix_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
)brace
r_else
(brace
id|prefix_node
op_assign
id|scope_info-&gt;scope.node
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|prefix_node
)paren
op_ne
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ns_lookup: %p is not a namespace node [%s]&bslash;n&quot;
comma
id|prefix_node
comma
id|acpi_ut_get_descriptor_name
(paren
id|prefix_node
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * This node might not be a actual &quot;scope&quot; node (such as a&n;&t;&t; * Device/Method, etc.)  It could be a Package or other object node.&n;&t;&t; * Backup up the tree to find the containing scope node.&n;&t;&t; */
r_while
c_loop
(paren
op_logical_neg
id|acpi_ns_opens_scope
(paren
id|prefix_node-&gt;type
)paren
op_logical_and
id|prefix_node-&gt;type
op_ne
id|ACPI_TYPE_ANY
)paren
(brace
id|prefix_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|prefix_node
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Save type   TBD: may be no longer necessary */
id|type_to_check_for
op_assign
id|type
suffix:semicolon
multiline_comment|/*&n;&t; * Begin examination of the actual pathname&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pathname
)paren
(brace
multiline_comment|/* A Null name_path is allowed and refers to the root */
id|num_segments
op_assign
l_int|0
suffix:semicolon
id|this_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
id|path
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Null Pathname (Zero segments), Flags=%X&bslash;n&quot;
comma
id|flags
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Name pointer is valid (and must be in internal name format)&n;&t;&t; *&n;&t;&t; * Check for scope prefixes:&n;&t;&t; *&n;&t;&t; * As represented in the AML stream, a namepath consists of an&n;&t;&t; * optional scope prefix followed by a name segment part.&n;&t;&t; *&n;&t;&t; * If present, the scope prefix is either a Root Prefix (in&n;&t;&t; * which case the name is fully qualified), or one or more&n;&t;&t; * Parent Prefixes (in which case the name&squot;s scope is relative&n;&t;&t; * to the current scope).&n;&t;&t; */
r_if
c_cond
(paren
op_star
id|path
op_eq
(paren
id|u8
)paren
id|AML_ROOT_PREFIX
)paren
(brace
multiline_comment|/* Pathname is fully qualified, start from the root */
id|this_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
id|search_parent_flag
op_assign
id|ACPI_NS_NO_UPSEARCH
suffix:semicolon
multiline_comment|/* Point to name segment part */
id|path
op_increment
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Path is absolute from root [%p]&bslash;n&quot;
comma
id|this_node
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Pathname is relative to current scope, start there */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Searching relative to prefix scope [%4.4s] (%p)&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|prefix_node
)paren
comma
id|prefix_node
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Handle multiple Parent Prefixes (carat) by just getting&n;&t;&t;&t; * the parent node for each prefix instance.&n;&t;&t;&t; */
id|this_node
op_assign
id|prefix_node
suffix:semicolon
id|num_carats
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|path
op_eq
(paren
id|u8
)paren
id|AML_PARENT_PREFIX
)paren
(brace
multiline_comment|/* Name is fully qualified, no search rules apply */
id|search_parent_flag
op_assign
id|ACPI_NS_NO_UPSEARCH
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Point past this prefix to the name segment&n;&t;&t;&t;&t; * part or the next Parent Prefix&n;&t;&t;&t;&t; */
id|path
op_increment
suffix:semicolon
multiline_comment|/* Backup to the parent node */
id|num_carats
op_increment
suffix:semicolon
id|this_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|this_node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this_node
)paren
(brace
multiline_comment|/* Current scope has no parent scope */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ACPI path has too many parent prefixes (^) - reached beyond root node&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|search_parent_flag
op_eq
id|ACPI_NS_NO_UPSEARCH
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Search scope is [%4.4s], path has %d carat(s)&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|this_node
)paren
comma
id|num_carats
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Determine the number of ACPI name segments in this pathname.&n;&t;&t; *&n;&t;&t; * The segment part consists of either:&n;&t;&t; *  - A Null name segment (0)&n;&t;&t; *  - A dual_name_prefix followed by two 4-byte name segments&n;&t;&t; *  - A multi_name_prefix followed by a byte indicating the&n;&t;&t; *      number of segments and the segments themselves.&n;&t;&t; *  - A single 4-byte name segment&n;&t;&t; *&n;&t;&t; * Examine the name prefix opcode, if any, to determine the number of&n;&t;&t; * segments.&n;&t;&t; */
r_switch
c_cond
(paren
op_star
id|path
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Null name after a root or parent prefixes. We already&n;&t;&t;&t; * have the correct target node and there are no name segments.&n;&t;&t;&t; */
id|num_segments
op_assign
l_int|0
suffix:semicolon
id|type
op_assign
id|this_node-&gt;type
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Prefix-only Pathname (Zero name segments), Flags=%X&bslash;n&quot;
comma
id|flags
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DUAL_NAME_PREFIX
suffix:colon
multiline_comment|/* More than one name_seg, search rules do not apply */
id|search_parent_flag
op_assign
id|ACPI_NS_NO_UPSEARCH
suffix:semicolon
multiline_comment|/* Two segments, point to first name segment */
id|num_segments
op_assign
l_int|2
suffix:semicolon
id|path
op_increment
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Dual Pathname (2 segments, Flags=%X)&bslash;n&quot;
comma
id|flags
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_MULTI_NAME_PREFIX_OP
suffix:colon
multiline_comment|/* More than one name_seg, search rules do not apply */
id|search_parent_flag
op_assign
id|ACPI_NS_NO_UPSEARCH
suffix:semicolon
multiline_comment|/* Extract segment count, point to first name segment */
id|path
op_increment
suffix:semicolon
id|num_segments
op_assign
(paren
id|u32
)paren
(paren
id|u8
)paren
op_star
id|path
suffix:semicolon
id|path
op_increment
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Multi Pathname (%d Segments, Flags=%X) &bslash;n&quot;
comma
id|num_segments
comma
id|flags
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Not a Null name, no Dual or Multi prefix, hence there is&n;&t;&t;&t; * only one name segment and Pathname is already pointing to it.&n;&t;&t;&t; */
id|num_segments
op_assign
l_int|1
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Simple Pathname (1 segment, Flags=%X)&bslash;n&quot;
comma
id|flags
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ACPI_DEBUG_EXEC
(paren
id|acpi_ns_print_pathname
(paren
id|num_segments
comma
id|path
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Search namespace for each segment of the name.  Loop through and&n;&t; * verify (or add to the namespace) each name segment.&n;&t; *&n;&t; * The object type is significant only at the last name&n;&t; * segment.  (We don&squot;t care about the types along the path, only&n;&t; * the type of the final target object.)&n;&t; */
id|this_search_type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|current_node
op_assign
id|this_node
suffix:semicolon
r_while
c_loop
(paren
id|num_segments
op_logical_and
id|current_node
)paren
(brace
id|num_segments
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_segments
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This is the last segment, enable typechecking&n;&t;&t;&t; */
id|this_search_type
op_assign
id|type
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Only allow automatic parent search (search rules) if the caller&n;&t;&t;&t; * requested it AND we have a single, non-fully-qualified name_seg&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|search_parent_flag
op_ne
id|ACPI_NS_NO_UPSEARCH
)paren
op_logical_and
(paren
id|flags
op_amp
id|ACPI_NS_SEARCH_PARENT
)paren
)paren
(brace
id|local_flags
op_or_assign
id|ACPI_NS_SEARCH_PARENT
suffix:semicolon
)brace
multiline_comment|/* Set error flag according to caller */
r_if
c_cond
(paren
id|flags
op_amp
id|ACPI_NS_ERROR_IF_FOUND
)paren
(brace
id|local_flags
op_or_assign
id|ACPI_NS_ERROR_IF_FOUND
suffix:semicolon
)brace
)brace
multiline_comment|/* Extract one ACPI name from the front of the pathname */
id|ACPI_MOVE_32_TO_32
(paren
op_amp
id|simple_name
comma
id|path
)paren
suffix:semicolon
multiline_comment|/* Try to find the single (4 character) ACPI name */
id|status
op_assign
id|acpi_ns_search_and_enter
(paren
id|simple_name
comma
id|walk_state
comma
id|current_node
comma
id|interpreter_mode
comma
id|this_search_type
comma
id|local_flags
comma
op_amp
id|this_node
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
multiline_comment|/* Name not found in ACPI namespace */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Name [%4.4s] not found in scope [%4.4s] %p&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|simple_name
comma
(paren
r_char
op_star
)paren
op_amp
id|current_node-&gt;name
comma
id|current_node
)paren
)paren
suffix:semicolon
)brace
op_star
id|return_node
op_assign
id|this_node
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Sanity typecheck of the target object:&n;&t;&t; *&n;&t;&t; * If 1) This is the last segment (num_segments == 0)&n;&t;&t; *    2) And we are looking for a specific type&n;&t;&t; *       (Not checking for TYPE_ANY)&n;&t;&t; *    3) Which is not an alias&n;&t;&t; *    4) Which is not a local type (TYPE_SCOPE)&n;&t;&t; *    5) And the type of target object is known (not TYPE_ANY)&n;&t;&t; *    6) And target object does not match what we are looking for&n;&t;&t; *&n;&t;&t; * Then we have a type mismatch.  Just warn and ignore it.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|num_segments
op_eq
l_int|0
)paren
op_logical_and
(paren
id|type_to_check_for
op_ne
id|ACPI_TYPE_ANY
)paren
op_logical_and
(paren
id|type_to_check_for
op_ne
id|ACPI_TYPE_LOCAL_ALIAS
)paren
op_logical_and
(paren
id|type_to_check_for
op_ne
id|ACPI_TYPE_LOCAL_METHOD_ALIAS
)paren
op_logical_and
(paren
id|type_to_check_for
op_ne
id|ACPI_TYPE_LOCAL_SCOPE
)paren
op_logical_and
(paren
id|this_node-&gt;type
op_ne
id|ACPI_TYPE_ANY
)paren
op_logical_and
(paren
id|this_node-&gt;type
op_ne
id|type_to_check_for
)paren
)paren
(brace
multiline_comment|/* Complain about a type mismatch */
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;ns_lookup: Type mismatch on %4.4s (%s), searching for (%s)&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|simple_name
comma
id|acpi_ut_get_type_name
(paren
id|this_node-&gt;type
)paren
comma
id|acpi_ut_get_type_name
(paren
id|type_to_check_for
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If this is the last name segment and we are not looking for a&n;&t;&t; * specific type, but the type of found object is known, use that type&n;&t;&t; * to see if it opens a scope.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|num_segments
op_eq
l_int|0
)paren
op_logical_and
(paren
id|type
op_eq
id|ACPI_TYPE_ANY
)paren
)paren
(brace
id|type
op_assign
id|this_node-&gt;type
suffix:semicolon
)brace
multiline_comment|/* Point to next name segment and make this node current */
id|path
op_add_assign
id|ACPI_NAME_SIZE
suffix:semicolon
id|current_node
op_assign
id|this_node
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Always check if we need to open a new scope&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|ACPI_NS_DONT_OPEN_SCOPE
)paren
op_logical_and
(paren
id|walk_state
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * If entry is a type which opens a scope, push the new scope on the&n;&t;&t; * scope stack.&n;&t;&t; */
r_if
c_cond
(paren
id|acpi_ns_opens_scope
(paren
id|type
)paren
)paren
(brace
id|status
op_assign
id|acpi_ds_scope_stack_push
(paren
id|this_node
comma
id|type
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
)brace
op_star
id|return_node
op_assign
id|this_node
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
