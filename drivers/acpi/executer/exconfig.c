multiline_comment|/******************************************************************************&n; *&n; * Module Name: exconfig - Namespace reconfiguration (Load/Unload opcodes)&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
macro_line|#include &lt;acpi/actables.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exconfig&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_add_table&n; *&n; * PARAMETERS:  Table               - Pointer to raw table&n; *              parent_node         - Where to load the table (scope)&n; *              ddb_handle          - Where to return the table handle.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Common function to Install and Load an ACPI table with a&n; *              returned table handle.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_add_table
id|acpi_ex_add_table
(paren
r_struct
id|acpi_table_header
op_star
id|table
comma
r_struct
id|acpi_namespace_node
op_star
id|parent_node
comma
r_union
id|acpi_operand_object
op_star
op_star
id|ddb_handle
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_table_desc
id|table_info
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_add_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Create an object to be the table handle */
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the new table into the local data structures */
id|table_info.pointer
op_assign
id|table
suffix:semicolon
id|table_info.length
op_assign
(paren
id|acpi_size
)paren
id|table-&gt;length
suffix:semicolon
id|table_info.allocation
op_assign
id|ACPI_MEM_ALLOCATED
suffix:semicolon
id|status
op_assign
id|acpi_tb_install_table
(paren
op_amp
id|table_info
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
multiline_comment|/* Add the table to the namespace */
id|status
op_assign
id|acpi_ns_load_table
(paren
id|table_info.installed_desc
comma
id|parent_node
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
multiline_comment|/* Uninstall table on error */
(paren
r_void
)paren
id|acpi_tb_uninstall_table
(paren
id|table_info.installed_desc
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Init the table handle */
id|obj_desc-&gt;reference.opcode
op_assign
id|AML_LOAD_OP
suffix:semicolon
id|obj_desc-&gt;reference.object
op_assign
id|table_info.installed_desc
suffix:semicolon
op_star
id|ddb_handle
op_assign
id|obj_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_load_table_op&n; *&n; * PARAMETERS:  walk_state          - Current state with operands&n; *              return_desc         - Where to store the return object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load an ACPI table&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_load_table_op
id|acpi_ex_load_table_op
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_operand_object
op_star
op_star
id|return_desc
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|operand
op_assign
op_amp
id|walk_state-&gt;operands
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|table
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|parent_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|start_node
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|parameter_node
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|ddb_handle
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_load_table_op&quot;
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; * Make sure that the signature does not match one of the tables that&n;&t; * is already loaded.&n;&t; */
id|status
op_assign
id|acpi_tb_match_signature
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|string.pointer
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|AE_OK
)paren
(brace
multiline_comment|/* Signature matched -- don&squot;t allow override */
id|return_ACPI_STATUS
(paren
id|AE_ALREADY_EXISTS
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Find the ACPI table */
id|status
op_assign
id|acpi_tb_find_table
(paren
id|operand
(braket
l_int|0
)braket
op_member_access_from_pointer
id|string.pointer
comma
id|operand
(braket
l_int|1
)braket
op_member_access_from_pointer
id|string.pointer
comma
id|operand
(braket
l_int|2
)braket
op_member_access_from_pointer
id|string.pointer
comma
op_amp
id|table
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
op_ne
id|AE_NOT_FOUND
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Not found, return an Integer=0 and AE_OK */
id|ddb_handle
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_INTEGER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ddb_handle
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|ddb_handle-&gt;integer.value
op_assign
l_int|0
suffix:semicolon
op_star
id|return_desc
op_assign
id|ddb_handle
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Default nodes */
id|start_node
op_assign
id|walk_state-&gt;scope_info-&gt;scope.node
suffix:semicolon
id|parent_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
multiline_comment|/* root_path (optional parameter) */
r_if
c_cond
(paren
id|operand
(braket
l_int|3
)braket
op_member_access_from_pointer
id|string.length
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Find the node referenced by the root_path_string. This is the&n;&t;&t; * location within the namespace where the table will be loaded.&n;&t;&t; */
id|status
op_assign
id|acpi_ns_get_node_by_path
(paren
id|operand
(braket
l_int|3
)braket
op_member_access_from_pointer
id|string.pointer
comma
id|start_node
comma
id|ACPI_NS_SEARCH_PARENT
comma
op_amp
id|parent_node
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
multiline_comment|/* parameter_path (optional parameter) */
r_if
c_cond
(paren
id|operand
(braket
l_int|4
)braket
op_member_access_from_pointer
id|string.length
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|operand
(braket
l_int|4
)braket
op_member_access_from_pointer
id|string.pointer
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;&bslash;&squot;
)paren
op_logical_and
(paren
id|operand
(braket
l_int|4
)braket
op_member_access_from_pointer
id|string.pointer
(braket
l_int|0
)braket
op_ne
l_char|&squot;^&squot;
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Path is not absolute, so it will be relative to the node&n;&t;&t;&t; * referenced by the root_path_string (or the NS root if omitted)&n;&t;&t;&t; */
id|start_node
op_assign
id|parent_node
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Find the node referenced by the parameter_path_string&n;&t;&t; */
id|status
op_assign
id|acpi_ns_get_node_by_path
(paren
id|operand
(braket
l_int|4
)braket
op_member_access_from_pointer
id|string.pointer
comma
id|start_node
comma
id|ACPI_NS_SEARCH_PARENT
comma
op_amp
id|parameter_node
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
multiline_comment|/* Load the table into the namespace */
id|status
op_assign
id|acpi_ex_add_table
(paren
id|table
comma
id|parent_node
comma
op_amp
id|ddb_handle
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
multiline_comment|/* Parameter Data (optional) */
r_if
c_cond
(paren
id|parameter_node
)paren
(brace
multiline_comment|/* Store the parameter data into the optional parameter object */
id|status
op_assign
id|acpi_ex_store
(paren
id|operand
(braket
l_int|5
)braket
comma
id|ACPI_CAST_PTR
(paren
r_union
id|acpi_operand_object
comma
id|parameter_node
)paren
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
(paren
r_void
)paren
id|acpi_ex_unload_table
(paren
id|ddb_handle
)paren
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_load_op&n; *&n; * PARAMETERS:  obj_desc        - Region or Field where the table will be&n; *                                obtained&n; *              Target          - Where a handle to the table will be stored&n; *              walk_state      - Current state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load an ACPI table from a field or operation region&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_load_op
id|acpi_ex_load_op
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_union
id|acpi_operand_object
op_star
id|target
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|ddb_handle
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|buffer_desc
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|table_ptr
op_assign
l_int|NULL
suffix:semicolon
id|u8
op_star
id|table_data_ptr
suffix:semicolon
r_struct
id|acpi_table_header
id|table_header
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_load_op&quot;
)paren
suffix:semicolon
multiline_comment|/* Object can be either an op_region or a Field */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Load from Region %p %s&bslash;n&quot;
comma
id|obj_desc
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the table header */
id|table_header.length
op_assign
l_int|0
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
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_ev_address_space_dispatch
(paren
id|obj_desc
comma
id|ACPI_READ
comma
(paren
id|acpi_physical_address
)paren
id|i
comma
l_int|8
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|table_header
)paren
op_plus
id|i
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
multiline_comment|/* Allocate a buffer for the entire table */
id|table_ptr
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|table_header.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table_ptr
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the header to the buffer */
id|ACPI_MEMCPY
(paren
id|table_ptr
comma
op_amp
id|table_header
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
id|table_data_ptr
op_assign
id|ACPI_PTR_ADD
(paren
id|u8
comma
id|table_ptr
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the table from the op region */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|table_header.length
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_ev_address_space_dispatch
(paren
id|obj_desc
comma
id|ACPI_READ
comma
(paren
id|acpi_physical_address
)paren
id|i
comma
l_int|8
comma
(paren
(paren
id|u8
op_star
)paren
id|table_data_ptr
op_plus
id|i
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
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Load from Field %p %s&bslash;n&quot;
comma
id|obj_desc
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The length of the field must be at least as large as the table.&n;&t;&t; * Read the entire field and thus the entire table.  Buffer is&n;&t;&t; * allocated during the read.&n;&t;&t; */
id|status
op_assign
id|acpi_ex_read_data_from_field
(paren
id|walk_state
comma
id|obj_desc
comma
op_amp
id|buffer_desc
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
id|table_ptr
op_assign
id|ACPI_CAST_PTR
(paren
r_struct
id|acpi_table_header
comma
id|buffer_desc-&gt;buffer.pointer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* The table must be either an SSDT or a PSDT */
r_if
c_cond
(paren
(paren
op_logical_neg
id|ACPI_STRNCMP
(paren
id|table_ptr-&gt;signature
comma
id|acpi_gbl_acpi_table_data
(braket
id|ACPI_TABLE_PSDT
)braket
dot
id|signature
comma
id|acpi_gbl_acpi_table_data
(braket
id|ACPI_TABLE_PSDT
)braket
dot
id|sig_length
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|ACPI_STRNCMP
(paren
id|table_ptr-&gt;signature
comma
id|acpi_gbl_acpi_table_data
(braket
id|ACPI_TABLE_SSDT
)braket
dot
id|signature
comma
id|acpi_gbl_acpi_table_data
(braket
id|ACPI_TABLE_SSDT
)braket
dot
id|sig_length
)paren
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Table has invalid signature [%4.4s], must be SSDT or PSDT&bslash;n&quot;
comma
id|table_ptr-&gt;signature
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_BAD_SIGNATURE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Install the new table into the local data structures */
id|status
op_assign
id|acpi_ex_add_table
(paren
id|table_ptr
comma
id|acpi_gbl_root_node
comma
op_amp
id|ddb_handle
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
multiline_comment|/* Store the ddb_handle into the Target operand */
id|status
op_assign
id|acpi_ex_store
(paren
id|ddb_handle
comma
id|target
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
(paren
r_void
)paren
id|acpi_ex_unload_table
(paren
id|ddb_handle
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|buffer_desc
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|buffer_desc
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_MEM_FREE
(paren
id|table_ptr
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_unload_table&n; *&n; * PARAMETERS:  ddb_handle          - Handle to a previously loaded table&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Unload an ACPI table&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_unload_table
id|acpi_ex_unload_table
(paren
r_union
id|acpi_operand_object
op_star
id|ddb_handle
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_NOT_IMPLEMENTED
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|table_desc
op_assign
id|ddb_handle
suffix:semicolon
r_struct
id|acpi_table_desc
op_star
id|table_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_unload_table&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Validate the handle&n;&t; * Although the handle is partially validated in acpi_ex_reconfiguration(),&n;&t; * when it calls acpi_ex_resolve_operands(), the handle is more completely&n;&t; * validated here.&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|ddb_handle
)paren
op_logical_or
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|ddb_handle
)paren
op_ne
id|ACPI_DESC_TYPE_OPERAND
)paren
op_logical_or
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|ddb_handle
)paren
op_ne
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the actual table descriptor from the ddb_handle */
id|table_info
op_assign
(paren
r_struct
id|acpi_table_desc
op_star
)paren
id|table_desc-&gt;reference.object
suffix:semicolon
multiline_comment|/*&n;&t; * Delete the entire namespace under this table Node&n;&t; * (Offset contains the table_id)&n;&t; */
id|acpi_ns_delete_namespace_by_owner
(paren
id|table_info-&gt;table_id
)paren
suffix:semicolon
multiline_comment|/* Delete the table itself */
(paren
r_void
)paren
id|acpi_tb_uninstall_table
(paren
id|table_info-&gt;installed_desc
)paren
suffix:semicolon
multiline_comment|/* Delete the table descriptor (ddb_handle) */
id|acpi_ut_remove_reference
(paren
id|table_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
