multiline_comment|/******************************************************************************&n; *&n; * Module Name: nsload - namespace loading/expanding/contracting procedures&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsload&quot;
)paren
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_load_table&n; *&n; * PARAMETERS:  table_desc      - Descriptor for table to be loaded&n; *              Node            - Owning NS node&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load one ACPI table into the namespace&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_load_table
id|acpi_ns_load_table
(paren
r_struct
id|acpi_table_desc
op_star
id|table_desc
comma
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_load_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Check if table contains valid AML (must be DSDT, PSDT, SSDT, etc.) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_gbl_table_data
(braket
id|table_desc-&gt;type
)braket
dot
id|flags
op_amp
id|ACPI_TABLE_EXECUTABLE
)paren
)paren
(brace
multiline_comment|/* Just ignore this table */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Check validity of the AML start and length */
r_if
c_cond
(paren
op_logical_neg
id|table_desc-&gt;aml_start
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Null AML pointer&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;AML block at %p&bslash;n&quot;
comma
id|table_desc-&gt;aml_start
)paren
)paren
suffix:semicolon
multiline_comment|/* Ignore table if there is no AML contained within */
r_if
c_cond
(paren
op_logical_neg
id|table_desc-&gt;aml_length
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Zero-length AML block in table [%4.4s]&bslash;n&quot;
comma
id|table_desc-&gt;pointer-&gt;signature
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Parse the table and load the namespace with all named&n;&t; * objects found within.  Control methods are NOT parsed&n;&t; * at this time.  In fact, the control methods cannot be&n;&t; * parsed until the entire namespace is loaded, because&n;&t; * if a control method makes a forward reference (call)&n;&t; * to another control method, we can&squot;t continue parsing&n;&t; * because we don&squot;t know how many arguments to parse next!&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;**** Loading table into namespace ****&bslash;n&quot;
)paren
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
id|status
op_assign
id|acpi_ns_parse_table
(paren
id|table_desc
comma
id|node-&gt;child
)paren
suffix:semicolon
(paren
r_void
)paren
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
multiline_comment|/*&n;&t; * Now we can parse the control methods.  We always parse&n;&t; * them here for a sanity check, and if configured for&n;&t; * just-in-time parsing, we delete the control method&n;&t; * parse trees.&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;**** Begin Table Method Parsing and Object Initialization ****&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ds_initialize_objects
(paren
id|table_desc
comma
id|node
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;**** Completed Table Method Parsing and Object Initialization ****&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_load_table_by_type&n; *&n; * PARAMETERS:  table_type          - Id of the table type to load&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load an ACPI table or tables into the namespace.  All tables&n; *              of the given type are loaded.  The mechanism allows this&n; *              routine to be called repeatedly.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_load_table_by_type
id|acpi_ns_load_table_by_type
(paren
id|acpi_table_type
id|table_type
)paren
(brace
id|u32
id|i
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_load_table_by_type&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_TABLES
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
multiline_comment|/*&n;&t; * Table types supported are:&n;&t; * DSDT (one), SSDT/PSDT (multiple)&n;&t; */
r_switch
c_cond
(paren
id|table_type
)paren
(brace
r_case
id|ACPI_TABLE_DSDT
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Loading DSDT&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|table_desc
op_assign
id|acpi_gbl_table_lists
(braket
id|ACPI_TABLE_DSDT
)braket
dot
id|next
suffix:semicolon
multiline_comment|/* If table already loaded into namespace, just return */
r_if
c_cond
(paren
id|table_desc-&gt;loaded_into_namespace
)paren
(brace
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Now load the single DSDT */
id|status
op_assign
id|acpi_ns_load_table
(paren
id|table_desc
comma
id|acpi_gbl_root_node
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
id|table_desc-&gt;loaded_into_namespace
op_assign
id|TRUE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_SSDT
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Loading %d SSDTs&bslash;n&quot;
comma
id|acpi_gbl_table_lists
(braket
id|ACPI_TABLE_SSDT
)braket
dot
id|count
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Traverse list of SSDT tables&n;&t;&t; */
id|table_desc
op_assign
id|acpi_gbl_table_lists
(braket
id|ACPI_TABLE_SSDT
)braket
dot
id|next
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_table_lists
(braket
id|ACPI_TABLE_SSDT
)braket
dot
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Only attempt to load table if it is not&n;&t;&t;&t; * already loaded!&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|table_desc-&gt;loaded_into_namespace
)paren
(brace
id|status
op_assign
id|acpi_ns_load_table
(paren
id|table_desc
comma
id|acpi_gbl_root_node
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
id|table_desc-&gt;loaded_into_namespace
op_assign
id|TRUE
suffix:semicolon
)brace
id|table_desc
op_assign
id|table_desc-&gt;next
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_PSDT
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Loading %d PSDTs&bslash;n&quot;
comma
id|acpi_gbl_table_lists
(braket
id|ACPI_TABLE_PSDT
)braket
dot
id|count
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Traverse list of PSDT tables&n;&t;&t; */
id|table_desc
op_assign
id|acpi_gbl_table_lists
(braket
id|ACPI_TABLE_PSDT
)braket
dot
id|next
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_table_lists
(braket
id|ACPI_TABLE_PSDT
)braket
dot
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Only attempt to load table if it is not already loaded! */
r_if
c_cond
(paren
op_logical_neg
id|table_desc-&gt;loaded_into_namespace
)paren
(brace
id|status
op_assign
id|acpi_ns_load_table
(paren
id|table_desc
comma
id|acpi_gbl_root_node
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
id|table_desc-&gt;loaded_into_namespace
op_assign
id|TRUE
suffix:semicolon
)brace
id|table_desc
op_assign
id|table_desc-&gt;next
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_SUPPORT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_TABLES
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_load_namespace&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load the name space from what ever is pointed to by DSDT.&n; *              (DSDT points to either the BIOS or a buffer.)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_load_namespace
id|acpi_ns_load_namespace
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_load_name_space&quot;
)paren
suffix:semicolon
multiline_comment|/* There must be at least a DSDT installed */
r_if
c_cond
(paren
id|acpi_gbl_DSDT
op_eq
l_int|NULL
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;DSDT is not in memory&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Load the namespace.  The DSDT is required,&n;&t; * but the SSDT and PSDT tables are optional.&n;&t; */
id|status
op_assign
id|acpi_ns_load_table_by_type
(paren
id|ACPI_TABLE_DSDT
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
multiline_comment|/* Ignore exceptions from these */
(paren
r_void
)paren
id|acpi_ns_load_table_by_type
(paren
id|ACPI_TABLE_SSDT
)paren
suffix:semicolon
(paren
r_void
)paren
id|acpi_ns_load_table_by_type
(paren
id|ACPI_TABLE_PSDT
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;ACPI Namespace successfully loaded at root %p&bslash;n&quot;
comma
id|acpi_gbl_root_node
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_delete_subtree&n; *&n; * PARAMETERS:  start_handle        - Handle in namespace where search begins&n; *&n; * RETURNS      Status&n; *&n; * DESCRIPTION: Walks the namespace starting at the given handle and deletes&n; *              all objects, entries, and scopes in the entire subtree.&n; *&n; *              Namespace/Interpreter should be locked or the subsystem should&n; *              be in shutdown before this routine is called.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_delete_subtree
id|acpi_ns_delete_subtree
(paren
id|acpi_handle
id|start_handle
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_handle
id|child_handle
suffix:semicolon
id|acpi_handle
id|parent_handle
suffix:semicolon
id|acpi_handle
id|next_child_handle
suffix:semicolon
id|acpi_handle
id|dummy
suffix:semicolon
id|u32
id|level
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_delete_subtree&quot;
)paren
suffix:semicolon
id|parent_handle
op_assign
id|start_handle
suffix:semicolon
id|child_handle
op_assign
l_int|NULL
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
multiline_comment|/* Attempt to get the next object in this scope */
id|status
op_assign
id|acpi_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|parent_handle
comma
id|child_handle
comma
op_amp
id|next_child_handle
)paren
suffix:semicolon
id|child_handle
op_assign
id|next_child_handle
suffix:semicolon
multiline_comment|/* Did we get a new object? */
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Check if this object has any children */
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|acpi_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|child_handle
comma
l_int|NULL
comma
op_amp
id|dummy
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * There is at least one child of this object,&n;&t;&t;&t;&t; * visit the object&n;&t;&t;&t;&t; */
id|level
op_increment
suffix:semicolon
id|parent_handle
op_assign
id|child_handle
suffix:semicolon
id|child_handle
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * No more children in this object, go back up to&n;&t;&t;&t; * the object&squot;s parent&n;&t;&t;&t; */
id|level
op_decrement
suffix:semicolon
multiline_comment|/* Delete all children now */
id|acpi_ns_delete_children
(paren
id|child_handle
)paren
suffix:semicolon
id|child_handle
op_assign
id|parent_handle
suffix:semicolon
id|status
op_assign
id|acpi_get_parent
(paren
id|parent_handle
comma
op_amp
id|parent_handle
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
multiline_comment|/* Now delete the starting object, and we are done */
id|acpi_ns_delete_node
(paren
id|child_handle
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; *  FUNCTION:       acpi_ns_unload_name_space&n; *&n; *  PARAMETERS:     Handle          - Root of namespace subtree to be deleted&n; *&n; *  RETURN:         Status&n; *&n; *  DESCRIPTION:    Shrinks the namespace, typically in response to an undocking&n; *                  event.  Deletes an entire subtree starting from (and&n; *                  including) the given handle.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_unload_namespace
id|acpi_ns_unload_namespace
(paren
id|acpi_handle
id|handle
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ns_unload_name_space&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
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
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* This function does the real work */
id|status
op_assign
id|acpi_ns_delete_subtree
(paren
id|handle
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
