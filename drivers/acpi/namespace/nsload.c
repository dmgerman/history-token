multiline_comment|/******************************************************************************&n; *&n; * Module Name: nsload - namespace loading/expanding/contracting procedures&n; *              $Revision: 58 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acdispat.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsload&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Ns_one_complete_parse&n; *&n; * PARAMETERS:  Pass_number             - 1 or 2&n; *              Table_desc              - The table to be parsed.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Perform one complete parse of an ACPI/AML table.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_one_complete_parse
id|acpi_ns_one_complete_parse
(paren
id|u32
id|pass_number
comma
id|acpi_table_desc
op_star
id|table_desc
)paren
(brace
id|acpi_parse_object
op_star
id|parse_root
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_walk_state
op_star
id|walk_state
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_one_complete_parse&quot;
)paren
suffix:semicolon
multiline_comment|/* Create and init a Root Node */
id|parse_root
op_assign
id|acpi_ps_create_scope_op
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_root
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Create and initialize a new walk state */
id|walk_state
op_assign
id|acpi_ds_create_walk_state
(paren
id|TABLE_ID_DSDT
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walk_state
)paren
(brace
id|acpi_ps_free_op
(paren
id|parse_root
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_init_aml_walk
(paren
id|walk_state
comma
id|parse_root
comma
l_int|NULL
comma
id|table_desc-&gt;aml_start
comma
id|table_desc-&gt;aml_length
comma
l_int|NULL
comma
l_int|NULL
comma
id|pass_number
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
id|acpi_ds_delete_walk_state
(paren
id|walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Parse the AML */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;*PARSE* pass %d parse&bslash;n&quot;
comma
id|pass_number
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ps_parse_aml
(paren
id|walk_state
)paren
suffix:semicolon
id|acpi_ps_delete_parse_tree
(paren
id|parse_root
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_parse_table&n; *&n; * PARAMETERS:  Table_desc      - An ACPI table descriptor for table to parse&n; *              Start_node      - Where to enter the table into the namespace&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Parse AML within an ACPI table and return a tree of ops&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_parse_table
id|acpi_ns_parse_table
(paren
id|acpi_table_desc
op_star
id|table_desc
comma
id|acpi_namespace_node
op_star
id|start_node
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_parse_table&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * AML Parse, pass 1&n;&t; *&n;&t; * In this pass, we load most of the namespace.  Control methods&n;&t; * are not parsed until later.  A parse tree is not created.  Instead,&n;&t; * each Parser Op subtree is deleted when it is finished.  This saves&n;&t; * a great deal of memory, and allows a small cache of parse objects&n;&t; * to service the entire parse.  The second pass of the parse then&n;&t; * performs another complete parse of the AML..&n;&t; */
id|status
op_assign
id|acpi_ns_one_complete_parse
(paren
l_int|1
comma
id|table_desc
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
multiline_comment|/*&n;&t; * AML Parse, pass 2&n;&t; *&n;&t; * In this pass, we resolve forward references and other things&n;&t; * that could not be completed during the first pass.&n;&t; * Another complete parse of the AML is performed, but the&n;&t; * overhead of this is compensated for by the fact that the&n;&t; * parse objects are all cached.&n;&t; */
id|status
op_assign
id|acpi_ns_one_complete_parse
(paren
l_int|2
comma
id|table_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_load_table&n; *&n; * PARAMETERS:  Table_desc      - Descriptor for table to be loaded&n; *              Node            - Owning NS node&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load one ACPI table into the namespace&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_load_table
id|acpi_ns_load_table
(paren
id|acpi_table_desc
op_star
id|table_desc
comma
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
l_string|&quot;Ns_load_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Check if table contains valid AML (must be DSDT, PSDT, SSDT, etc.) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_gbl_acpi_table_data
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
r_if
c_cond
(paren
op_logical_neg
id|table_desc-&gt;aml_length
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Zero-length AML block&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_load_table_by_type&n; *&n; * PARAMETERS:  Table_type          - Id of the table type to load&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load an ACPI table or tables into the namespace.  All tables&n; *              of the given type are loaded.  The mechanism allows this&n; *              routine to be called repeatedly.&n; *&n; ******************************************************************************/
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
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ns_load_table_by_type&quot;
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
op_amp
id|acpi_gbl_acpi_tables
(braket
id|ACPI_TABLE_DSDT
)braket
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
id|table_desc-&gt;table_id
op_assign
id|TABLE_ID_DSDT
suffix:semicolon
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
id|acpi_gbl_acpi_tables
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
op_amp
id|acpi_gbl_acpi_tables
(braket
id|ACPI_TABLE_SSDT
)braket
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
id|acpi_gbl_acpi_tables
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
id|acpi_gbl_acpi_tables
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
op_amp
id|acpi_gbl_acpi_tables
(braket
id|ACPI_TABLE_PSDT
)braket
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
id|acpi_gbl_acpi_tables
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_load_namespace&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load the name space from what ever is pointed to by DSDT.&n; *              (DSDT points to either the BIOS or a buffer.)&n; *&n; ******************************************************************************/
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
l_string|&quot;Acpi_load_name_space&quot;
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
id|ACPI_DB_OK
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_delete_subtree&n; *&n; * PARAMETERS:  Start_handle        - Handle in namespace where search begins&n; *&n; * RETURNS      Status&n; *&n; * DESCRIPTION: Walks the namespace starting at the given handle and deletes&n; *              all objects, entries, and scopes in the entire subtree.&n; *&n; *              Namespace/Interpreter should be locked or the subsystem should&n; *              be in shutdown before this routine is called.&n; *&n; ******************************************************************************/
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
l_string|&quot;Ns_delete_subtree&quot;
)paren
suffix:semicolon
id|parent_handle
op_assign
id|start_handle
suffix:semicolon
id|child_handle
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
l_int|0
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
l_int|0
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
multiline_comment|/*******************************************************************************&n; *&n; *  FUNCTION:       Acpi_ns_unload_name_space&n; *&n; *  PARAMETERS:     Handle          - Root of namespace subtree to be deleted&n; *&n; *  RETURN:         Status&n; *&n; *  DESCRIPTION:    Shrinks the namespace, typically in response to an undocking&n; *                  event.  Deletes an entire subtree starting from (and&n; *                  including) the given handle.&n; *&n; ******************************************************************************/
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
l_string|&quot;Ns_unload_name_space&quot;
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
