multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbxface - Public interfaces to the ACPI subsystem&n; *                         ACPI table oriented interfaces&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/actables.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbxface&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_load_tables&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to load the ACPI tables from the&n; *              provided RSDT&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_load_tables
id|acpi_load_tables
(paren
r_void
)paren
(brace
r_struct
id|acpi_pointer
id|rsdp_address
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_load_tables&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the RSDP */
id|status
op_assign
id|acpi_os_get_root_pointer
(paren
id|ACPI_LOGICAL_ADDRESSING
comma
op_amp
id|rsdp_address
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_load_tables: Could not get RSDP, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
r_goto
id|error_exit
suffix:semicolon
)brace
multiline_comment|/* Map and validate the RSDP */
id|acpi_gbl_table_flags
op_assign
id|rsdp_address.pointer_type
suffix:semicolon
id|status
op_assign
id|acpi_tb_verify_rsdp
(paren
op_amp
id|rsdp_address
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_load_tables: RSDP Failed validation: %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
r_goto
id|error_exit
suffix:semicolon
)brace
multiline_comment|/* Get the RSDT via the RSDP */
id|status
op_assign
id|acpi_tb_get_table_rsdt
(paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_load_tables: Could not load RSDT: %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
r_goto
id|error_exit
suffix:semicolon
)brace
multiline_comment|/* Now get the tables needed by this subsystem (FADT, DSDT, etc.) */
id|status
op_assign
id|acpi_tb_get_required_tables
(paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_load_tables: Error getting required tables (DSDT/FADT/FACS): %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
r_goto
id|error_exit
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;ACPI Tables successfully acquired&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Load the namespace from the tables */
id|status
op_assign
id|acpi_ns_load_namespace
(paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_load_tables: Could not load namespace: %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
r_goto
id|error_exit
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
id|error_exit
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;acpi_load_tables: Could not load tables: %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_load_table&n; *&n; * PARAMETERS:  table_ptr       - pointer to a buffer containing the entire&n; *                                table to be loaded&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to load a table from the caller&squot;s&n; *              buffer.  The buffer must contain an entire ACPI Table including&n; *              a valid header.  The header fields will be verified, and if it&n; *              is determined that the table is invalid, the call will fail.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_load_table
id|acpi_load_table
(paren
r_struct
id|acpi_table_header
op_star
id|table_ptr
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_table_desc
id|table_info
suffix:semicolon
r_struct
id|acpi_pointer
id|address
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_load_table&quot;
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
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the table to a local buffer */
id|address.pointer_type
op_assign
id|ACPI_LOGICAL_POINTER
op_or
id|ACPI_LOGICAL_ADDRESSING
suffix:semicolon
id|address.pointer.logical
op_assign
id|table_ptr
suffix:semicolon
id|status
op_assign
id|acpi_tb_get_table_body
(paren
op_amp
id|address
comma
id|table_ptr
comma
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the new table into the local data structures */
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
multiline_comment|/* Free table allocated by acpi_tb_get_table_body */
id|acpi_tb_delete_single_table
(paren
op_amp
id|table_info
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert the table to common format if necessary */
r_switch
c_cond
(paren
id|table_info.type
)paren
(brace
r_case
id|ACPI_TABLE_FADT
suffix:colon
id|status
op_assign
id|acpi_tb_convert_table_fadt
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_FACS
suffix:colon
id|status
op_assign
id|acpi_tb_build_common_facs
(paren
op_amp
id|table_info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Load table into namespace if it contains executable AML */
id|status
op_assign
id|acpi_ns_load_table
(paren
id|table_info.installed_desc
comma
id|acpi_gbl_root_node
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Uninstall table and free the buffer */
(paren
r_void
)paren
id|acpi_tb_uninstall_table
(paren
id|table_info.installed_desc
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_unload_table&n; *&n; * PARAMETERS:  table_type    - Type of table to be unloaded&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This routine is used to force the unload of a table&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_unload_table
id|acpi_unload_table
(paren
id|acpi_table_type
id|table_type
)paren
(brace
r_struct
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_unload_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
id|table_type
OG
id|ACPI_TABLE_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Find all tables of the requested type */
id|table_desc
op_assign
id|acpi_gbl_table_lists
(braket
id|table_type
)braket
dot
id|next
suffix:semicolon
r_while
c_loop
(paren
id|table_desc
)paren
suffix:semicolon
(brace
multiline_comment|/*&n;&t;&t; * Delete all namespace entries owned by this table.  Note that these&n;&t;&t; * entries can appear anywhere in the namespace by virtue of the AML&n;&t;&t; * &quot;Scope&quot; operator.  Thus, we need to track ownership by an ID, not&n;&t;&t; * simply a position within the hierarchy&n;&t;&t; */
id|acpi_ns_delete_namespace_by_owner
(paren
id|table_desc-&gt;table_id
)paren
suffix:semicolon
id|table_desc
op_assign
id|table_desc-&gt;next
suffix:semicolon
)brace
multiline_comment|/* Delete (or unmap) all tables of this type */
id|acpi_tb_delete_tables_by_type
(paren
id|table_type
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_table_header&n; *&n; * PARAMETERS:  table_type      - one of the defined table types&n; *              Instance        - the non zero instance of the table, allows&n; *                                support for multiple tables of the same type&n; *                                see acpi_gbl_acpi_table_flag&n; *              out_table_header - pointer to the struct acpi_table_header if successful&n; *&n; * DESCRIPTION: This function is called to get an ACPI table header.  The caller&n; *              supplies an pointer to a data area sufficient to contain an ACPI&n; *              struct acpi_table_header structure.&n; *&n; *              The header contains a length field that can be used to determine&n; *              the size of the buffer needed to contain the entire table.  This&n; *              function is not valid for the RSD PTR table since it does not&n; *              have a standard header and is fixed length.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_table_header
id|acpi_get_table_header
(paren
id|acpi_table_type
id|table_type
comma
id|u32
id|instance
comma
r_struct
id|acpi_table_header
op_star
id|out_table_header
)paren
(brace
r_struct
id|acpi_table_header
op_star
id|tbl_ptr
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_table_header&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|instance
op_eq
l_int|0
)paren
op_logical_or
(paren
id|table_type
op_eq
id|ACPI_TABLE_RSDP
)paren
op_logical_or
(paren
op_logical_neg
id|out_table_header
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Check the table type and instance */
r_if
c_cond
(paren
(paren
id|table_type
OG
id|ACPI_TABLE_MAX
)paren
op_logical_or
(paren
id|ACPI_IS_SINGLE_TABLE
(paren
id|acpi_gbl_table_data
(braket
id|table_type
)braket
dot
id|flags
)paren
op_logical_and
id|instance
OG
l_int|1
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get a pointer to the entire table */
id|status
op_assign
id|acpi_tb_get_table_ptr
(paren
id|table_type
comma
id|instance
comma
op_amp
id|tbl_ptr
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
multiline_comment|/*&n;&t; * The function will return a NULL pointer if the table is not loaded&n;&t; */
r_if
c_cond
(paren
id|tbl_ptr
op_eq
l_int|NULL
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Copy the header to the caller&squot;s buffer&n;&t; */
id|ACPI_MEMCPY
(paren
(paren
r_void
op_star
)paren
id|out_table_header
comma
(paren
r_void
op_star
)paren
id|tbl_ptr
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_table&n; *&n; * PARAMETERS:  table_type      - one of the defined table types&n; *              Instance        - the non zero instance of the table, allows&n; *                                support for multiple tables of the same type&n; *                                see acpi_gbl_acpi_table_flag&n; *              ret_buffer      - pointer to a structure containing a buffer to&n; *                                receive the table&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get an ACPI table.  The caller&n; *              supplies an out_buffer large enough to contain the entire ACPI&n; *              table.  The caller should call the acpi_get_table_header function&n; *              first to determine the buffer size needed.  Upon completion&n; *              the out_buffer-&gt;Length field will indicate the number of bytes&n; *              copied into the out_buffer-&gt;buf_ptr buffer. This table will be&n; *              a complete table including the header.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_table
id|acpi_get_table
(paren
id|acpi_table_type
id|table_type
comma
id|u32
id|instance
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
r_struct
id|acpi_table_header
op_star
id|tbl_ptr
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_size
id|table_length
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
id|instance
op_eq
l_int|0
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_validate_buffer
(paren
id|ret_buffer
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
multiline_comment|/* Check the table type and instance */
r_if
c_cond
(paren
(paren
id|table_type
OG
id|ACPI_TABLE_MAX
)paren
op_logical_or
(paren
id|ACPI_IS_SINGLE_TABLE
(paren
id|acpi_gbl_table_data
(braket
id|table_type
)braket
dot
id|flags
)paren
op_logical_and
id|instance
OG
l_int|1
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get a pointer to the entire table */
id|status
op_assign
id|acpi_tb_get_table_ptr
(paren
id|table_type
comma
id|instance
comma
op_amp
id|tbl_ptr
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
multiline_comment|/*&n;&t; * acpi_tb_get_table_ptr will return a NULL pointer if the&n;&t; * table is not loaded.&n;&t; */
r_if
c_cond
(paren
id|tbl_ptr
op_eq
l_int|NULL
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the table length */
r_if
c_cond
(paren
id|table_type
op_eq
id|ACPI_TABLE_RSDP
)paren
(brace
multiline_comment|/*&n;&t;&t; *  RSD PTR is the only &quot;table&quot; without a header&n;&t;&t; */
id|table_length
op_assign
r_sizeof
(paren
r_struct
id|rsdp_descriptor
)paren
suffix:semicolon
)brace
r_else
(brace
id|table_length
op_assign
(paren
id|acpi_size
)paren
id|tbl_ptr-&gt;length
suffix:semicolon
)brace
multiline_comment|/* Validate/Allocate/Clear caller buffer */
id|status
op_assign
id|acpi_ut_initialize_buffer
(paren
id|ret_buffer
comma
id|table_length
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
multiline_comment|/* Copy the table to the buffer */
id|ACPI_MEMCPY
(paren
(paren
r_void
op_star
)paren
id|ret_buffer-&gt;pointer
comma
(paren
r_void
op_star
)paren
id|tbl_ptr
comma
id|table_length
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
