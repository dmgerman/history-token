multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbinstal - ACPI table installation and removal&n; *              $Revision: 65 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;actables.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbinstal&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_match_signature&n; *&n; * PARAMETERS:  Signature           - Table signature to match&n; *              Table_info          - Return data&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Compare signature against the list of &quot;ACPI-subsystem-owned&quot;&n; *              tables (DSDT/FADT/SSDT, etc.) Returns the Table_type_iD on match.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_match_signature
id|acpi_tb_match_signature
(paren
r_char
op_star
id|signature
comma
id|acpi_table_desc
op_star
id|table_info
comma
id|u8
id|search_type
)paren
(brace
id|NATIVE_UINT
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_match_signature&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Search for a signature match among the known table types&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_ACPI_TABLES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|acpi_gbl_acpi_table_data
(braket
id|i
)braket
dot
id|flags
op_amp
id|ACPI_TABLE_TYPE_MASK
)paren
op_ne
id|search_type
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ACPI_STRNCMP
(paren
id|signature
comma
id|acpi_gbl_acpi_table_data
(braket
id|i
)braket
dot
id|signature
comma
id|acpi_gbl_acpi_table_data
(braket
id|i
)braket
dot
id|sig_length
)paren
)paren
(brace
multiline_comment|/* Found a signature match, return index if requested */
r_if
c_cond
(paren
id|table_info
)paren
(brace
id|table_info-&gt;type
op_assign
(paren
id|u8
)paren
id|i
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Table [%4.4s] matched and is a required ACPI table&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|acpi_gbl_acpi_table_data
(braket
id|i
)braket
dot
id|signature
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Table [%4.4s] is not a required ACPI table - ignored&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|signature
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_TABLE_NOT_SUPPORTED
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_install_table&n; *&n; * PARAMETERS:  Table_info          - Return value from Acpi_tb_get_table_body&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load and validate all tables other than the RSDT.  The RSDT must&n; *              already be loaded and validated.&n; *              Install the table into the global data structs.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_install_table
id|acpi_tb_install_table
(paren
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_install_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Lock tables while installing */
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not acquire table mutex for [%4.4s], %s&bslash;n&quot;
comma
id|table_info-&gt;pointer-&gt;signature
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
multiline_comment|/* Install the table into the global data structure */
id|status
op_assign
id|acpi_tb_init_table_descriptor
(paren
id|table_info-&gt;type
comma
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not install ACPI table [%s], %s&bslash;n&quot;
comma
id|table_info-&gt;pointer-&gt;signature
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;%s located at %p&bslash;n&quot;
comma
id|acpi_gbl_acpi_table_data
(braket
id|table_info-&gt;type
)braket
dot
id|name
comma
id|table_info-&gt;pointer
)paren
)paren
suffix:semicolon
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_recognize_table&n; *&n; * PARAMETERS:  Table_info          - Return value from Acpi_tb_get_table_body&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Check a table signature for a match against known table types&n; *&n; * NOTE:  All table pointers are validated as follows:&n; *          1) Table pointer must point to valid physical memory&n; *          2) Signature must be 4 ASCII chars, even if we don&squot;t recognize the&n; *             name&n; *          3) Table must be readable for length specified in the header&n; *          4) Table checksum must be valid (with the exception of the FACS&n; *             which has no checksum for some odd reason)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_recognize_table
id|acpi_tb_recognize_table
(paren
id|acpi_table_desc
op_star
id|table_info
comma
id|u8
id|search_type
)paren
(brace
id|acpi_table_header
op_star
id|table_header
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_recognize_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Ensure that we have a valid table pointer */
id|table_header
op_assign
(paren
id|acpi_table_header
op_star
)paren
id|table_info-&gt;pointer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table_header
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We only &quot;recognize&quot; a limited number of ACPI tables -- namely, the&n;&t; * ones that are used by the subsystem (DSDT, FADT, etc.)&n;&t; *&n;&t; * An AE_TABLE_NOT_SUPPORTED means that the table was not recognized.&n;&t; * This can be any one of many valid ACPI tables, it just isn&squot;t one of&n;&t; * the tables that is consumed by the core subsystem&n;&t; */
id|status
op_assign
id|acpi_tb_match_signature
(paren
id|table_header-&gt;signature
comma
id|table_info
comma
id|search_type
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
id|acpi_tb_validate_table_header
(paren
id|table_header
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
multiline_comment|/* Return the table type and length via the info struct */
id|table_info-&gt;length
op_assign
(paren
id|ACPI_SIZE
)paren
id|table_header-&gt;length
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_init_table_descriptor&n; *&n; * PARAMETERS:  Table_type          - The type of the table&n; *              Table_info          - A table info struct&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Install a table into the global data structs.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_init_table_descriptor
id|acpi_tb_init_table_descriptor
(paren
id|acpi_table_type
id|table_type
comma
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
id|acpi_table_desc
op_star
id|list_head
suffix:semicolon
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;Tb_init_table_descriptor&quot;
comma
id|table_type
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Install the table into the global data structure&n;&t; */
id|list_head
op_assign
op_amp
id|acpi_gbl_acpi_tables
(braket
id|table_type
)braket
suffix:semicolon
id|table_desc
op_assign
id|list_head
suffix:semicolon
multiline_comment|/*&n;&t; * Two major types of tables:  1) Only one instance is allowed.  This&n;&t; * includes most ACPI tables such as the DSDT.  2) Multiple instances of&n;&t; * the table are allowed.  This includes SSDT and PSDTs.&n;&t; */
r_if
c_cond
(paren
id|ACPI_IS_SINGLE_TABLE
(paren
id|acpi_gbl_acpi_table_data
(braket
id|table_type
)braket
dot
id|flags
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Only one table allowed, and a table has alread been installed&n;&t;&t; *  at this location, so return an error.&n;&t;&t; */
r_if
c_cond
(paren
id|list_head-&gt;pointer
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_ALREADY_EXISTS
)paren
suffix:semicolon
)brace
id|table_desc-&gt;count
op_assign
l_int|1
suffix:semicolon
id|table_desc-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|table_desc-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Multiple tables allowed for this table type, we must link&n;&t;&t; * the new table in to the list of tables of this type.&n;&t;&t; */
r_if
c_cond
(paren
id|list_head-&gt;pointer
)paren
(brace
id|table_desc
op_assign
id|ACPI_MEM_CALLOCATE
(paren
r_sizeof
(paren
id|acpi_table_desc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|list_head-&gt;count
op_increment
suffix:semicolon
multiline_comment|/* Update the original previous */
id|list_head-&gt;prev-&gt;next
op_assign
id|table_desc
suffix:semicolon
multiline_comment|/* Update new entry */
id|table_desc-&gt;prev
op_assign
id|list_head-&gt;prev
suffix:semicolon
id|table_desc-&gt;next
op_assign
id|list_head
suffix:semicolon
multiline_comment|/* Update list head */
id|list_head-&gt;prev
op_assign
id|table_desc
suffix:semicolon
)brace
r_else
(brace
id|table_desc-&gt;count
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Common initialization of the table descriptor */
id|table_desc-&gt;type
op_assign
id|table_info-&gt;type
suffix:semicolon
id|table_desc-&gt;pointer
op_assign
id|table_info-&gt;pointer
suffix:semicolon
id|table_desc-&gt;length
op_assign
id|table_info-&gt;length
suffix:semicolon
id|table_desc-&gt;allocation
op_assign
id|table_info-&gt;allocation
suffix:semicolon
id|table_desc-&gt;aml_start
op_assign
(paren
id|u8
op_star
)paren
(paren
id|table_desc-&gt;pointer
op_plus
l_int|1
)paren
comma
id|table_desc-&gt;aml_length
op_assign
(paren
id|u32
)paren
(paren
id|table_desc-&gt;length
op_minus
(paren
id|u32
)paren
r_sizeof
(paren
id|acpi_table_header
)paren
)paren
suffix:semicolon
id|table_desc-&gt;table_id
op_assign
id|acpi_ut_allocate_owner_id
(paren
id|ACPI_OWNER_TYPE_TABLE
)paren
suffix:semicolon
id|table_desc-&gt;loaded_into_namespace
op_assign
id|FALSE
suffix:semicolon
multiline_comment|/*&n;&t; * Set the appropriate global pointer (if there is one) to point to the&n;&t; * newly installed table&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_acpi_table_data
(braket
id|table_type
)braket
dot
id|global_ptr
)paren
(brace
op_star
(paren
id|acpi_gbl_acpi_table_data
(braket
id|table_type
)braket
dot
id|global_ptr
)paren
op_assign
id|table_info-&gt;pointer
suffix:semicolon
)brace
multiline_comment|/* Return Data */
id|table_info-&gt;table_id
op_assign
id|table_desc-&gt;table_id
suffix:semicolon
id|table_info-&gt;installed_desc
op_assign
id|table_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_delete_acpi_tables&n; *&n; * PARAMETERS:  None.&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Delete all internal ACPI tables&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_tb_delete_acpi_tables
id|acpi_tb_delete_acpi_tables
(paren
r_void
)paren
(brace
id|acpi_table_type
id|type
suffix:semicolon
multiline_comment|/*&n;&t; * Free memory allocated for ACPI tables&n;&t; * Memory can either be mapped or allocated&n;&t; */
r_for
c_loop
(paren
id|type
op_assign
l_int|0
suffix:semicolon
id|type
OL
id|NUM_ACPI_TABLES
suffix:semicolon
id|type
op_increment
)paren
(brace
id|acpi_tb_delete_acpi_table
(paren
id|type
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_delete_acpi_table&n; *&n; * PARAMETERS:  Type                - The table type to be deleted&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Delete an internal ACPI table&n; *              Locks the ACPI table mutex&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_tb_delete_acpi_table
id|acpi_tb_delete_acpi_table
(paren
id|acpi_table_type
id|type
)paren
(brace
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;Tb_delete_acpi_table&quot;
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OG
id|ACPI_TABLE_MAX
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_TABLES
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Clear the appropriate &quot;typed&quot; global table pointer */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TABLE_RSDP
suffix:colon
id|acpi_gbl_RSDP
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_DSDT
suffix:colon
id|acpi_gbl_DSDT
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_FADT
suffix:colon
id|acpi_gbl_FADT
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_FACS
suffix:colon
id|acpi_gbl_FACS
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_XSDT
suffix:colon
id|acpi_gbl_XSDT
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TABLE_SSDT
suffix:colon
r_case
id|ACPI_TABLE_PSDT
suffix:colon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Free the table */
id|acpi_tb_free_acpi_tables_of_type
(paren
op_amp
id|acpi_gbl_acpi_tables
(braket
id|type
)braket
)paren
suffix:semicolon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_TABLES
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_free_acpi_tables_of_type&n; *&n; * PARAMETERS:  Table_info          - A table info struct&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Free the memory associated with an internal ACPI table&n; *              Table mutex should be locked.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_tb_free_acpi_tables_of_type
id|acpi_tb_free_acpi_tables_of_type
(paren
id|acpi_table_desc
op_star
id|list_head
)paren
(brace
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|u32
id|count
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Tb_free_acpi_tables_of_type&quot;
comma
id|list_head
)paren
suffix:semicolon
multiline_comment|/* Get the head of the list */
id|table_desc
op_assign
id|list_head
suffix:semicolon
id|count
op_assign
id|list_head-&gt;count
suffix:semicolon
multiline_comment|/*&n;&t; * Walk the entire list, deleting both the allocated tables&n;&t; * and the table descriptors&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|table_desc
op_assign
id|acpi_tb_uninstall_table
(paren
id|table_desc
)paren
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_delete_single_table&n; *&n; * PARAMETERS:  Table_info          - A table info struct&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Low-level free for a single ACPI table.  Handles cases where&n; *              the table was allocated a buffer or was mapped.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_tb_delete_single_table
id|acpi_tb_delete_single_table
(paren
id|acpi_table_desc
op_star
id|table_desc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|table_desc
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|table_desc-&gt;pointer
)paren
(brace
multiline_comment|/* Valid table, determine type of memory allocation */
r_switch
c_cond
(paren
id|table_desc-&gt;allocation
)paren
(brace
r_case
id|ACPI_MEM_NOT_ALLOCATED
suffix:colon
r_break
suffix:semicolon
r_case
id|ACPI_MEM_ALLOCATED
suffix:colon
id|ACPI_MEM_FREE
(paren
id|table_desc-&gt;pointer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_MEM_MAPPED
suffix:colon
id|acpi_os_unmap_memory
(paren
id|table_desc-&gt;pointer
comma
id|table_desc-&gt;length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_uninstall_table&n; *&n; * PARAMETERS:  Table_info          - A table info struct&n; *&n; * RETURN:      Pointer to the next table in the list (of same type)&n; *&n; * DESCRIPTION: Free the memory associated with an internal ACPI table that&n; *              is either installed or has never been installed.&n; *              Table mutex should be locked.&n; *&n; ******************************************************************************/
id|acpi_table_desc
op_star
DECL|function|acpi_tb_uninstall_table
id|acpi_tb_uninstall_table
(paren
id|acpi_table_desc
op_star
id|table_desc
)paren
(brace
id|acpi_table_desc
op_star
id|next_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Acpi_tb_uninstall_table&quot;
comma
id|table_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table_desc
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Unlink the descriptor */
r_if
c_cond
(paren
id|table_desc-&gt;prev
)paren
(brace
id|table_desc-&gt;prev-&gt;next
op_assign
id|table_desc-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|table_desc-&gt;next
)paren
(brace
id|table_desc-&gt;next-&gt;prev
op_assign
id|table_desc-&gt;prev
suffix:semicolon
)brace
multiline_comment|/* Free the memory allocated for the table itself */
id|acpi_tb_delete_single_table
(paren
id|table_desc
)paren
suffix:semicolon
multiline_comment|/* Free the table descriptor (Don&squot;t delete the list head, tho) */
r_if
c_cond
(paren
(paren
id|table_desc-&gt;prev
)paren
op_eq
(paren
id|table_desc-&gt;next
)paren
)paren
(brace
id|next_desc
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Clear the list head */
id|table_desc-&gt;pointer
op_assign
l_int|NULL
suffix:semicolon
id|table_desc-&gt;length
op_assign
l_int|0
suffix:semicolon
id|table_desc-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Free the table descriptor */
id|next_desc
op_assign
id|table_desc-&gt;next
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|table_desc
)paren
suffix:semicolon
)brace
id|return_PTR
(paren
id|next_desc
)paren
suffix:semicolon
)brace
eof
