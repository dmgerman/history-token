multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbxfroot - Find the root ACPI table (RSDT)&n; *              $Revision: 63 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;actables.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbxfroot&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_find_table&n; *&n; * PARAMETERS:  Signature           - String with ACPI table signature&n; *              Oem_id              - String with the table OEM ID&n; *              Oem_table_id        - String with the OEM Table ID.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Find an ACPI table (in the RSDT/XSDT) that matches the&n; *              Signature, OEM ID and OEM Table ID.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_find_table
id|acpi_tb_find_table
(paren
id|NATIVE_CHAR
op_star
id|signature
comma
id|NATIVE_CHAR
op_star
id|oem_id
comma
id|NATIVE_CHAR
op_star
id|oem_table_id
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
id|acpi_table_header
op_star
id|table
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_find_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Validate string lengths */
r_if
c_cond
(paren
(paren
id|ACPI_STRLEN
(paren
id|signature
)paren
OG
l_int|4
)paren
op_logical_or
(paren
id|ACPI_STRLEN
(paren
id|oem_id
)paren
OG
l_int|6
)paren
op_logical_or
(paren
id|ACPI_STRLEN
(paren
id|oem_table_id
)paren
OG
l_int|8
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_STRING_LIMIT
)paren
suffix:semicolon
)brace
multiline_comment|/* Find the table */
id|status
op_assign
id|acpi_get_firmware_table
(paren
id|signature
comma
l_int|1
comma
id|ACPI_LOGICAL_ADDRESSING
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Check Oem_id and Oem_table_id */
r_if
c_cond
(paren
(paren
id|oem_id
(braket
l_int|0
)braket
op_logical_and
id|ACPI_STRCMP
(paren
id|oem_id
comma
id|table-&gt;oem_id
)paren
)paren
op_logical_or
(paren
id|oem_table_id
(braket
l_int|0
)braket
op_logical_and
id|ACPI_STRCMP
(paren
id|oem_table_id
comma
id|table-&gt;oem_table_id
)paren
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_NAME_NOT_FOUND
)paren
suffix:semicolon
)brace
op_star
id|table_ptr
op_assign
id|table
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_firmware_table&n; *&n; * PARAMETERS:  Signature       - Any ACPI table signature&n; *              Instance        - the non zero instance of the table, allows&n; *                                support for multiple tables of the same type&n; *              Flags           - 0: Physical/Virtual support&n; *              Ret_buffer      - pointer to a structure containing a buffer to&n; *                                receive the table&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get an ACPI table.  The caller&n; *              supplies an Out_buffer large enough to contain the entire ACPI&n; *              table.  Upon completion&n; *              the Out_buffer-&gt;Length field will indicate the number of bytes&n; *              copied into the Out_buffer-&gt;Buf_ptr buffer. This table will be&n; *              a complete table including the header.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_firmware_table
id|acpi_get_firmware_table
(paren
id|acpi_string
id|signature
comma
id|u32
id|instance
comma
id|u32
id|flags
comma
id|acpi_table_header
op_star
op_star
id|table_pointer
)paren
(brace
id|ACPI_POINTER
id|rsdp_address
suffix:semicolon
id|ACPI_POINTER
id|address
suffix:semicolon
id|acpi_table_header
op_star
id|rsdt_ptr
op_assign
l_int|NULL
suffix:semicolon
id|acpi_table_header
op_star
id|table_ptr
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_SIZE
id|rsdt_size
op_assign
l_int|0
suffix:semicolon
id|ACPI_SIZE
id|table_size
suffix:semicolon
id|u32
id|table_count
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|u32
id|j
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Acpi_get_firmware_table&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that at least the table manager is initialized.  We don&squot;t&n;&t; * require that the entire ACPI subsystem is up for this interface&n;&t; */
multiline_comment|/*&n;&t; *  If we have a buffer, we must have a length too&n;&t; */
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
op_logical_neg
id|signature
)paren
op_logical_or
(paren
op_logical_neg
id|table_pointer
)paren
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
op_logical_neg
id|acpi_gbl_RSDP
)paren
(brace
multiline_comment|/* Get the RSDP */
id|status
op_assign
id|acpi_os_get_root_pointer
(paren
id|flags
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;RSDP  not found&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
multiline_comment|/* Map and validate the RSDP */
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
id|status
op_assign
id|acpi_os_map_memory
(paren
id|rsdp_address.pointer.physical
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
id|acpi_gbl_RSDP
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
r_else
(brace
id|acpi_gbl_RSDP
op_assign
id|rsdp_address.pointer.logical
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *  The signature and checksum must both be correct&n;&t;&t; */
r_if
c_cond
(paren
id|ACPI_STRNCMP
(paren
(paren
id|NATIVE_CHAR
op_star
)paren
id|acpi_gbl_RSDP
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
r_if
c_cond
(paren
id|acpi_tb_checksum
(paren
id|acpi_gbl_RSDP
comma
id|ACPI_RSDP_CHECKSUM_LENGTH
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Nope, BAD Checksum */
id|status
op_assign
id|AE_BAD_CHECKSUM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
multiline_comment|/* Get the RSDT and validate it */
id|acpi_tb_get_rsdt_address
(paren
op_amp
id|address
)paren
suffix:semicolon
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
id|address.pointer.value
)paren
comma
id|ACPI_LODWORD
(paren
id|address.pointer.value
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_tb_get_table_pointer
(paren
op_amp
id|address
comma
id|flags
comma
op_amp
id|rsdt_size
comma
op_amp
id|rsdt_ptr
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
id|acpi_tb_validate_rsdt
(paren
id|rsdt_ptr
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
multiline_comment|/* Get the number of table pointers within the RSDT */
id|table_count
op_assign
id|acpi_tb_get_table_count
(paren
id|acpi_gbl_RSDP
comma
id|rsdt_ptr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Search the RSDT/XSDT for the correct instance of the&n;&t; * requested table&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|table_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Get the next table pointer */
id|address.pointer_type
op_assign
id|acpi_gbl_table_flags
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_RSDP-&gt;revision
OL
l_int|2
)paren
(brace
id|address.pointer.value
op_assign
(paren
(paren
id|RSDT_DESCRIPTOR
op_star
)paren
id|rsdt_ptr
)paren
op_member_access_from_pointer
id|table_offset_entry
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
(brace
id|address.pointer.value
op_assign
id|ACPI_GET_ADDRESS
(paren
(paren
(paren
id|xsdt_descriptor
op_star
)paren
id|rsdt_ptr
)paren
op_member_access_from_pointer
id|table_offset_entry
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Get addressibility if necessary */
id|status
op_assign
id|acpi_tb_get_table_pointer
(paren
op_amp
id|address
comma
id|flags
comma
op_amp
id|table_size
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
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Compare table signatures and table instance */
r_if
c_cond
(paren
op_logical_neg
id|ACPI_STRNCMP
(paren
(paren
r_char
op_star
)paren
id|table_ptr
comma
id|signature
comma
id|ACPI_STRLEN
(paren
id|signature
)paren
)paren
)paren
(brace
multiline_comment|/* An instance of the table was found */
id|j
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|j
op_ge
id|instance
)paren
(brace
multiline_comment|/* Found the correct instance */
op_star
id|table_pointer
op_assign
id|table_ptr
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
multiline_comment|/* Delete table mapping if using virtual addressing */
r_if
c_cond
(paren
(paren
id|table_size
)paren
op_logical_and
(paren
(paren
id|flags
op_amp
id|ACPI_MEMORY_MODE
)paren
op_eq
id|ACPI_LOGICAL_ADDRESSING
)paren
)paren
(brace
id|acpi_os_unmap_memory
(paren
id|table_ptr
comma
id|table_size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Did not find the table */
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|rsdt_size
)paren
(brace
id|acpi_os_unmap_memory
(paren
id|rsdt_ptr
comma
id|rsdt_size
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* TBD: Move to a new file */
macro_line|#if ACPI_MACHINE_WIDTH != 16
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_find_root_pointer&n; *&n; * PARAMETERS:  **Rsdp_address          - Where to place the RSDP address&n; *              Flags                   - Logical/Physical addressing&n; *&n; * RETURN:      Status, Physical address of the RSDP&n; *&n; * DESCRIPTION: Find the RSDP&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_find_root_pointer
id|acpi_find_root_pointer
(paren
id|u32
id|flags
comma
id|ACPI_POINTER
op_star
id|rsdp_address
)paren
(brace
id|acpi_table_desc
id|table_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Acpi_find_root_pointer&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the RSDP */
id|status
op_assign
id|acpi_tb_find_rsdp
(paren
op_amp
id|table_info
comma
id|flags
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
l_string|&quot;RSDP structure not found&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
id|rsdp_address-&gt;pointer_type
op_assign
id|ACPI_PHYSICAL_POINTER
suffix:semicolon
id|rsdp_address-&gt;pointer.physical
op_assign
id|table_info.physical_address
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_scan_memory_for_rsdp&n; *&n; * PARAMETERS:  Start_address       - Starting pointer for search&n; *              Length              - Maximum length to search&n; *&n; * RETURN:      Pointer to the RSDP if found, otherwise NULL.&n; *&n; * DESCRIPTION: Search a block of memory for the RSDP signature&n; *&n; ******************************************************************************/
id|u8
op_star
DECL|function|acpi_tb_scan_memory_for_rsdp
id|acpi_tb_scan_memory_for_rsdp
(paren
id|u8
op_star
id|start_address
comma
id|u32
id|length
)paren
(brace
id|u32
id|offset
suffix:semicolon
id|u8
op_star
id|mem_rover
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_scan_memory_for_rsdp&quot;
)paren
suffix:semicolon
multiline_comment|/* Search from given start addr for the requested length  */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
comma
id|mem_rover
op_assign
id|start_address
suffix:semicolon
id|offset
OL
id|length
suffix:semicolon
id|offset
op_add_assign
id|RSDP_SCAN_STEP
comma
id|mem_rover
op_add_assign
id|RSDP_SCAN_STEP
)paren
(brace
multiline_comment|/* The signature and checksum must both be correct */
r_if
c_cond
(paren
id|ACPI_STRNCMP
(paren
(paren
id|NATIVE_CHAR
op_star
)paren
id|mem_rover
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
op_eq
l_int|0
op_logical_and
id|acpi_tb_checksum
(paren
id|mem_rover
comma
id|ACPI_RSDP_CHECKSUM_LENGTH
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* If so, we have found the RSDP */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;RSDP located at physical address %p&bslash;n&quot;
comma
id|mem_rover
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
id|mem_rover
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Searched entire block, no RSDP was found */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Searched entire block, no RSDP was found.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_find_rsdp&n; *&n; * PARAMETERS:  *Table_info             - Where the table info is returned&n; *              Flags                   - Current memory mode (logical vs.&n; *                                        physical addressing)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Search lower 1_mbyte of memory for the root system descriptor&n; *              pointer structure.  If it is found, set *RSDP to point to it.&n; *&n; *              NOTE: The RSDP must be either in the first 1_k of the Extended&n; *              BIOS Data Area or between E0000 and FFFFF (ACPI 1.0 section&n; *              5.2.2; assertion #421).&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_find_rsdp
id|acpi_tb_find_rsdp
(paren
id|acpi_table_desc
op_star
id|table_info
comma
id|u32
id|flags
)paren
(brace
id|u8
op_star
id|table_ptr
suffix:semicolon
id|u8
op_star
id|mem_rover
suffix:semicolon
id|u64
id|phys_addr
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Tb_find_rsdp&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Scan supports either 1) Logical addressing or 2) Physical addressing&n;&t; */
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
multiline_comment|/*&n;&t;&t; * 1) Search EBDA (low memory) paragraphs&n;&t;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
(paren
id|u64
)paren
id|LO_RSDP_WINDOW_BASE
comma
id|LO_RSDP_WINDOW_SIZE
comma
(paren
r_void
op_star
op_star
)paren
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
id|mem_rover
op_assign
id|acpi_tb_scan_memory_for_rsdp
(paren
id|table_ptr
comma
id|LO_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
id|acpi_os_unmap_memory
(paren
id|table_ptr
comma
id|LO_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_rover
)paren
(brace
multiline_comment|/* Found it, return the physical address */
id|phys_addr
op_assign
id|LO_RSDP_WINDOW_BASE
suffix:semicolon
id|phys_addr
op_add_assign
id|ACPI_PTR_DIFF
(paren
id|mem_rover
comma
id|table_ptr
)paren
suffix:semicolon
id|table_info-&gt;physical_address
op_assign
id|phys_addr
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * 2) Search upper memory: 16-byte boundaries in E0000h-F0000h&n;&t;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
(paren
id|u64
)paren
id|HI_RSDP_WINDOW_BASE
comma
id|HI_RSDP_WINDOW_SIZE
comma
(paren
r_void
op_star
op_star
)paren
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
id|mem_rover
op_assign
id|acpi_tb_scan_memory_for_rsdp
(paren
id|table_ptr
comma
id|HI_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
id|acpi_os_unmap_memory
(paren
id|table_ptr
comma
id|HI_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_rover
)paren
(brace
multiline_comment|/* Found it, return the physical address */
id|phys_addr
op_assign
id|HI_RSDP_WINDOW_BASE
suffix:semicolon
id|phys_addr
op_add_assign
id|ACPI_PTR_DIFF
(paren
id|mem_rover
comma
id|table_ptr
)paren
suffix:semicolon
id|table_info-&gt;physical_address
op_assign
id|phys_addr
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Physical addressing&n;&t; */
r_else
(brace
multiline_comment|/*&n;&t;&t; * 1) Search EBDA (low memory) paragraphs&n;&t;&t; */
id|mem_rover
op_assign
id|acpi_tb_scan_memory_for_rsdp
(paren
id|ACPI_PHYSADDR_TO_PTR
(paren
id|LO_RSDP_WINDOW_BASE
)paren
comma
id|LO_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_rover
)paren
(brace
multiline_comment|/* Found it, return the physical address */
id|table_info-&gt;physical_address
op_assign
id|ACPI_TO_INTEGER
(paren
id|mem_rover
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * 2) Search upper memory: 16-byte boundaries in E0000h-F0000h&n;&t;&t; */
id|mem_rover
op_assign
id|acpi_tb_scan_memory_for_rsdp
(paren
id|ACPI_PHYSADDR_TO_PTR
(paren
id|HI_RSDP_WINDOW_BASE
)paren
comma
id|HI_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_rover
)paren
(brace
multiline_comment|/* Found it, return the physical address */
id|table_info-&gt;physical_address
op_assign
id|ACPI_TO_INTEGER
(paren
id|mem_rover
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* RSDP signature was not found */
id|return_ACPI_STATUS
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
