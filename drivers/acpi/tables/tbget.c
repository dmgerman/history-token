multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbget - ACPI Table get* routines&n; *              $Revision: 63 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;actables.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbget&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_get_table_ptr&n; *&n; * PARAMETERS:  Table_type      - one of the defined table types&n; *              Instance        - Which table of this type&n; *              Table_ptr_loc   - pointer to location to place the pointer for&n; *                                return&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the pointer to an ACPI table.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table_ptr
id|acpi_tb_get_table_ptr
(paren
id|acpi_table_type
id|table_type
comma
id|u32
id|instance
comma
id|acpi_table_header
op_star
op_star
id|table_ptr_loc
)paren
(brace
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_get_table_ptr&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_DSDT
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; * For all table types (Single/Multiple), the first&n;&t; * instance is always in the list head.&n;&t; */
r_if
c_cond
(paren
id|instance
op_eq
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Just pluck the pointer out of the global table!&n;&t;&t; * Will be null if no table is present&n;&t;&t; */
op_star
id|table_ptr_loc
op_assign
id|acpi_gbl_acpi_tables
(braket
id|table_type
)braket
dot
id|pointer
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check for instance out of range&n;&t; */
r_if
c_cond
(paren
id|instance
OG
id|acpi_gbl_acpi_tables
(braket
id|table_type
)braket
dot
id|count
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
multiline_comment|/* Walk the list to get the desired table&n;&t; * Since the if (Instance == 1) check above checked for the&n;&t; * first table, setting Table_desc equal to the .Next member&n;&t; * is actually pointing to the second table.  Therefore, we&n;&t; * need to walk from the 2nd table until we reach the Instance&n;&t; * that the user is looking for and return its table pointer.&n;&t; */
id|table_desc
op_assign
id|acpi_gbl_acpi_tables
(braket
id|table_type
)braket
dot
id|next
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
id|instance
suffix:semicolon
id|i
op_increment
)paren
(brace
id|table_desc
op_assign
id|table_desc-&gt;next
suffix:semicolon
)brace
multiline_comment|/* We are now pointing to the requested table&squot;s descriptor */
op_star
id|table_ptr_loc
op_assign
id|table_desc-&gt;pointer
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_get_table&n; *&n; * PARAMETERS:  Physical_address        - Physical address of table to retrieve&n; *              *Buffer_ptr             - If Buffer_ptr is valid, read data from&n; *                                         buffer rather than searching memory&n; *              *Table_info             - Where the table info is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Maps the physical address of table into a logical address&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table
id|acpi_tb_get_table
(paren
id|ACPI_PHYSICAL_ADDRESS
id|physical_address
comma
id|acpi_table_header
op_star
id|buffer_ptr
comma
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
id|acpi_table_header
op_star
id|table_header
op_assign
l_int|NULL
suffix:semicolon
id|acpi_table_header
op_star
id|full_table
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|u8
id|allocation
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_get_table&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table_info
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer_ptr
)paren
(brace
multiline_comment|/*&n;&t;&t; * Getting data from a buffer, not BIOS tables&n;&t;&t; */
id|table_header
op_assign
id|buffer_ptr
suffix:semicolon
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
multiline_comment|/* Table failed verification, map all errors to BAD_DATA */
id|return_ACPI_STATUS
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate buffer for the entire table */
id|full_table
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|table_header-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|full_table
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the entire table (including header) to the local buffer */
id|size
op_assign
id|table_header-&gt;length
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|full_table
comma
id|buffer_ptr
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Save allocation type */
id|allocation
op_assign
id|ACPI_MEM_ALLOCATED
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Not reading from a buffer, just map the table&squot;s physical memory&n;&t; * into our address space.&n;&t; */
r_else
(brace
id|size
op_assign
id|SIZE_IN_HEADER
suffix:semicolon
id|status
op_assign
id|acpi_tb_map_acpi_table
(paren
id|physical_address
comma
op_amp
id|size
comma
op_amp
id|full_table
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
multiline_comment|/* Save allocation type */
id|allocation
op_assign
id|ACPI_MEM_MAPPED
suffix:semicolon
)brace
multiline_comment|/* Return values */
id|table_info-&gt;pointer
op_assign
id|full_table
suffix:semicolon
id|table_info-&gt;length
op_assign
id|size
suffix:semicolon
id|table_info-&gt;allocation
op_assign
id|allocation
suffix:semicolon
id|table_info-&gt;base_pointer
op_assign
id|full_table
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_get_all_tables&n; *&n; * PARAMETERS:  Number_of_tables    - Number of tables to get&n; *              Table_ptr           - Input buffer pointer, optional&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load and validate all tables other than the RSDT.  The RSDT must&n; *              already be loaded and validated.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_all_tables
id|acpi_tb_get_all_tables
(paren
id|u32
id|number_of_tables
comma
id|acpi_table_header
op_star
id|table_ptr
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|index
suffix:semicolon
id|acpi_table_desc
id|table_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_get_all_tables&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Number of tables: %d&bslash;n&quot;
comma
id|number_of_tables
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Loop through all table pointers found in RSDT.&n;&t; * This will NOT include the FACS and DSDT - we must get&n;&t; * them after the loop&n;&t; */
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|number_of_tables
suffix:semicolon
id|index
op_increment
)paren
(brace
multiline_comment|/* Clear the Table_info each time */
id|ACPI_MEMSET
(paren
op_amp
id|table_info
comma
l_int|0
comma
r_sizeof
(paren
id|acpi_table_desc
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the table via the XSDT */
id|status
op_assign
id|acpi_tb_get_table
(paren
(paren
id|ACPI_PHYSICAL_ADDRESS
)paren
id|ACPI_GET_ADDRESS
(paren
id|acpi_gbl_XSDT-&gt;table_offset_entry
(braket
id|index
)braket
)paren
comma
id|table_ptr
comma
op_amp
id|table_info
)paren
suffix:semicolon
multiline_comment|/* Ignore a table that failed verification */
r_if
c_cond
(paren
id|status
op_eq
id|AE_BAD_DATA
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/* However, abort on serious errors */
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
multiline_comment|/* Recognize and install the table */
id|status
op_assign
id|acpi_tb_install_table
(paren
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
multiline_comment|/*&n;&t;&t;&t; * Unrecognized or unsupported table, delete it and ignore the&n;&t;&t;&t; * error.  Just get as many tables as we can, later we will&n;&t;&t;&t; * determine if there are enough tables to continue.&n;&t;&t;&t; */
id|acpi_tb_uninstall_table
(paren
op_amp
id|table_info
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Convert the FADT to a common format.  This allows earlier revisions of the&n;&t; * table to coexist with newer versions, using common access code.&n;&t; */
id|status
op_assign
id|acpi_tb_convert_table_fadt
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the minimum set of ACPI tables, namely:&n;&t; *&n;&t; * 1) FADT (via RSDT in loop above)&n;&t; * 2) FACS&n;&t; * 3) DSDT&n;&t; *&n;&t; */
multiline_comment|/*&n;&t; * Get the FACS (must have the FADT first, from loop above)&n;&t; * Acpi_tb_get_table_facs will fail if FADT pointer is not valid&n;&t; */
id|status
op_assign
id|acpi_tb_get_table_facs
(paren
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
multiline_comment|/* Install the FACS */
id|status
op_assign
id|acpi_tb_install_table
(paren
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
multiline_comment|/*&n;&t; * Create the common FACS pointer table&n;&t; * (Contains pointers to the original table)&n;&t; */
id|status
op_assign
id|acpi_tb_build_common_facs
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the DSDT (We know that the FADT is valid now)&n;&t; */
id|status
op_assign
id|acpi_tb_get_table
(paren
(paren
id|ACPI_PHYSICAL_ADDRESS
)paren
id|ACPI_GET_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xdsdt
)paren
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
multiline_comment|/* Install the DSDT */
id|status
op_assign
id|acpi_tb_install_table
(paren
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
multiline_comment|/* Dump the DSDT Header */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;Hex dump of DSDT Header:&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
(paren
id|u8
op_star
)paren
id|acpi_gbl_DSDT
comma
r_sizeof
(paren
id|acpi_table_header
)paren
)paren
suffix:semicolon
multiline_comment|/* Dump the entire DSDT */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;Hex dump of DSDT (After header), size %d (%x)&bslash;n&quot;
comma
id|acpi_gbl_DSDT-&gt;length
comma
id|acpi_gbl_DSDT-&gt;length
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
(paren
id|u8
op_star
)paren
(paren
id|acpi_gbl_DSDT
op_plus
l_int|1
)paren
comma
id|acpi_gbl_DSDT-&gt;length
)paren
suffix:semicolon
multiline_comment|/* Always delete the RSDP mapping, we are done with it */
id|acpi_tb_delete_acpi_table
(paren
id|ACPI_TABLE_RSDP
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_verify_rsdp&n; *&n; * PARAMETERS:  Number_of_tables    - Where the table count is placed&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load and validate the RSDP (ptr) and RSDT (table)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_verify_rsdp
id|acpi_tb_verify_rsdp
(paren
id|ACPI_PHYSICAL_ADDRESS
id|rsdp_physical_address
)paren
(brace
id|acpi_table_desc
id|table_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|RSDP_DESCRIPTOR
op_star
id|rsdp
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_verify_rsdp&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Obtain access to the RSDP structure&n;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
id|rsdp_physical_address
comma
r_sizeof
(paren
id|RSDP_DESCRIPTOR
)paren
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|rsdp
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
multiline_comment|/*&n;&t; *  The signature and checksum must both be correct&n;&t; */
r_if
c_cond
(paren
id|ACPI_STRNCMP
(paren
(paren
id|NATIVE_CHAR
op_star
)paren
id|rsdp
comma
id|RSDP_SIG
comma
r_sizeof
(paren
id|RSDP_SIG
)paren
op_minus
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Nope, BAD Signature */
id|status
op_assign
id|AE_BAD_SIGNATURE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Check the standard checksum */
r_if
c_cond
(paren
id|acpi_tb_checksum
(paren
id|rsdp
comma
id|ACPI_RSDP_CHECKSUM_LENGTH
)paren
op_ne
l_int|0
)paren
(brace
id|status
op_assign
id|AE_BAD_CHECKSUM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Check extended checksum if table version &gt;= 2 */
r_if
c_cond
(paren
id|rsdp-&gt;revision
op_ge
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|acpi_tb_checksum
(paren
id|rsdp
comma
id|ACPI_RSDP_XCHECKSUM_LENGTH
)paren
op_ne
l_int|0
)paren
(brace
id|status
op_assign
id|AE_BAD_CHECKSUM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
multiline_comment|/* The RSDP supplied is OK */
id|table_info.pointer
op_assign
(paren
id|acpi_table_header
op_star
)paren
id|rsdp
suffix:semicolon
id|table_info.length
op_assign
r_sizeof
(paren
id|RSDP_DESCRIPTOR
)paren
suffix:semicolon
id|table_info.allocation
op_assign
id|ACPI_MEM_MAPPED
suffix:semicolon
id|table_info.base_pointer
op_assign
id|rsdp
suffix:semicolon
multiline_comment|/* Save the table pointers and allocation info */
id|status
op_assign
id|acpi_tb_init_table_descriptor
(paren
id|ACPI_TABLE_RSDP
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
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Save the RSDP in a global for easy access */
id|acpi_gbl_RSDP
op_assign
(paren
id|RSDP_DESCRIPTOR
op_star
)paren
id|table_info.pointer
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
multiline_comment|/* Error exit */
id|cleanup
suffix:colon
id|acpi_os_unmap_memory
(paren
id|rsdp
comma
r_sizeof
(paren
id|RSDP_DESCRIPTOR
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_get_rsdt_address&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      RSDT physical address&n; *&n; * DESCRIPTION: Extract the address of the RSDT or XSDT, depending on the&n; *              version of the RSDP&n; *&n; ******************************************************************************/
id|ACPI_PHYSICAL_ADDRESS
DECL|function|acpi_tb_get_rsdt_address
id|acpi_tb_get_rsdt_address
(paren
r_void
)paren
(brace
id|ACPI_PHYSICAL_ADDRESS
id|physical_address
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For RSDP revision 0 or 1, we use the RSDT.&n;&t; * For RSDP revision 2 (and above), we use the XSDT&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_RSDP-&gt;revision
OL
l_int|2
)paren
(brace
id|physical_address
op_assign
(paren
id|ACPI_PHYSICAL_ADDRESS
)paren
id|acpi_gbl_RSDP-&gt;rsdt_physical_address
suffix:semicolon
)brace
r_else
(brace
id|physical_address
op_assign
(paren
id|ACPI_PHYSICAL_ADDRESS
)paren
id|ACPI_GET_ADDRESS
(paren
id|acpi_gbl_RSDP-&gt;xsdt_physical_address
)paren
suffix:semicolon
)brace
r_return
(paren
id|physical_address
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_validate_rsdt&n; *&n; * PARAMETERS:  Table_ptr       - Addressable pointer to the RSDT.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Validate signature for the RSDT or XSDT&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_validate_rsdt
id|acpi_tb_validate_rsdt
(paren
id|acpi_table_header
op_star
id|table_ptr
)paren
(brace
id|u32
id|no_match
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Tb_validate_rsdt&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For RSDP revision 0 or 1, we use the RSDT.&n;&t; * For RSDP revision 2 and above, we use the XSDT&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_RSDP-&gt;revision
OL
l_int|2
)paren
(brace
id|no_match
op_assign
id|ACPI_STRNCMP
(paren
(paren
r_char
op_star
)paren
id|table_ptr
comma
id|RSDT_SIG
comma
r_sizeof
(paren
id|RSDT_SIG
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|no_match
op_assign
id|ACPI_STRNCMP
(paren
(paren
r_char
op_star
)paren
id|table_ptr
comma
id|XSDT_SIG
comma
r_sizeof
(paren
id|XSDT_SIG
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|no_match
)paren
(brace
multiline_comment|/* Invalid RSDT or XSDT signature */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid signature where RSDP indicates RSDT/XSDT should be located&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
id|acpi_gbl_RSDP
comma
l_int|20
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;RSDT/XSDT signature at %X is invalid&bslash;n&quot;
comma
id|acpi_gbl_RSDP-&gt;rsdt_physical_address
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_SIGNATURE
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_get_table_pointer&n; *&n; * PARAMETERS:  Physical_address    - Address from RSDT&n; *              Flags               - virtual or physical addressing&n; *              Table_ptr           - Addressable address (output)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create an addressable pointer to an ACPI table&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table_pointer
id|acpi_tb_get_table_pointer
(paren
id|ACPI_PHYSICAL_ADDRESS
id|physical_address
comma
id|u32
id|flags
comma
id|u32
op_star
id|size
comma
id|acpi_table_header
op_star
op_star
id|table_ptr
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|ACPI_MEMORY_MODE
)paren
op_eq
id|ACPI_LOGICAL_ADDRESSING
)paren
(brace
op_star
id|size
op_assign
id|SIZE_IN_HEADER
suffix:semicolon
id|status
op_assign
id|acpi_tb_map_acpi_table
(paren
id|physical_address
comma
id|size
comma
id|table_ptr
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|size
op_assign
l_int|0
suffix:semicolon
op_star
id|table_ptr
op_assign
id|ACPI_PHYSADDR_TO_PTR
(paren
id|physical_address
)paren
suffix:semicolon
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_get_table_rsdt&n; *&n; * PARAMETERS:  Number_of_tables    - Where the table count is placed&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load and validate the RSDP (ptr) and RSDT (table)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table_rsdt
id|acpi_tb_get_table_rsdt
(paren
id|u32
op_star
id|number_of_tables
)paren
(brace
id|acpi_table_desc
id|table_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_PHYSICAL_ADDRESS
id|physical_address
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_get_table_rsdt&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the RSDT from the RSDP&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;RSDP located at %p, RSDT physical=%8.8X%8.8X &bslash;n&quot;
comma
id|acpi_gbl_RSDP
comma
id|ACPI_HIDWORD
(paren
id|acpi_gbl_RSDP-&gt;rsdt_physical_address
)paren
comma
id|ACPI_LODWORD
(paren
id|acpi_gbl_RSDP-&gt;rsdt_physical_address
)paren
)paren
)paren
suffix:semicolon
id|physical_address
op_assign
id|acpi_tb_get_rsdt_address
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the RSDT/XSDT */
id|status
op_assign
id|acpi_tb_get_table
(paren
id|physical_address
comma
l_int|NULL
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not get the RSDT, %s&bslash;n&quot;
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
multiline_comment|/* Check the RSDT or XSDT signature */
id|status
op_assign
id|acpi_tb_validate_rsdt
(paren
id|table_info.pointer
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
multiline_comment|/*&n;&t; * Valid RSDT signature, verify the checksum.  If it fails, just&n;&t; * print a warning and ignore it.&n;&t; */
id|status
op_assign
id|acpi_tb_verify_table_checksum
(paren
id|table_info.pointer
)paren
suffix:semicolon
multiline_comment|/* Convert and/or copy to an XSDT structure */
id|status
op_assign
id|acpi_tb_convert_to_xsdt
(paren
op_amp
id|table_info
comma
id|number_of_tables
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
multiline_comment|/* Save the table pointers and allocation info */
id|status
op_assign
id|acpi_tb_init_table_descriptor
(paren
id|ACPI_TABLE_XSDT
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
id|acpi_gbl_XSDT
op_assign
(paren
id|xsdt_descriptor
op_star
)paren
id|table_info.pointer
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;XSDT located at %p&bslash;n&quot;
comma
id|acpi_gbl_XSDT
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_get_table_facs&n; *&n; * PARAMETERS:  *Buffer_ptr             - If Buffer_ptr is valid, read data from&n; *                                        buffer rather than searching memory&n; *              *Table_info             - Where the table info is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Returns a pointer to the FACS as defined in FADT.  This&n; *              function assumes the global variable FADT has been&n; *              correctly initialized.  The value of FADT-&gt;Firmware_ctrl&n; *              into a far pointer which is returned.&n; *&n; *****************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table_facs
id|acpi_tb_get_table_facs
(paren
id|acpi_table_header
op_star
id|buffer_ptr
comma
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
id|acpi_table_header
op_star
id|table_ptr
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|u8
id|allocation
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_get_table_facs&quot;
)paren
suffix:semicolon
multiline_comment|/* Must have a valid FADT pointer */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
id|size
op_assign
r_sizeof
(paren
id|FACS_DESCRIPTOR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_ptr
)paren
(brace
multiline_comment|/*&n;&t;&t; * Getting table from a file -- allocate a buffer and&n;&t;&t; * read the table.&n;&t;&t; */
id|table_ptr
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|size
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
id|ACPI_MEMCPY
(paren
id|table_ptr
comma
id|buffer_ptr
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Save allocation type */
id|allocation
op_assign
id|ACPI_MEM_ALLOCATED
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Just map the physical memory to our address space */
id|status
op_assign
id|acpi_tb_map_acpi_table
(paren
(paren
id|ACPI_PHYSICAL_ADDRESS
)paren
id|ACPI_GET_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xfirmware_ctrl
)paren
comma
op_amp
id|size
comma
op_amp
id|table_ptr
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
multiline_comment|/* Save allocation type */
id|allocation
op_assign
id|ACPI_MEM_MAPPED
suffix:semicolon
)brace
multiline_comment|/* Return values */
id|table_info-&gt;pointer
op_assign
id|table_ptr
suffix:semicolon
id|table_info-&gt;length
op_assign
id|size
suffix:semicolon
id|table_info-&gt;allocation
op_assign
id|allocation
suffix:semicolon
id|table_info-&gt;base_pointer
op_assign
id|table_ptr
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
