multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbxfroot - Find the root ACPI table (RSDT)&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/actables.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbxfroot&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_find_table&n; *&n; * PARAMETERS:  Signature           - String with ACPI table signature&n; *              oem_id              - String with the table OEM ID&n; *              oem_table_id        - String with the OEM Table ID.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Find an ACPI table (in the RSDT/XSDT) that matches the&n; *              Signature, OEM ID and OEM Table ID.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_find_table
id|acpi_tb_find_table
(paren
r_char
op_star
id|signature
comma
r_char
op_star
id|oem_id
comma
r_char
op_star
id|oem_table_id
comma
r_struct
id|acpi_table_header
op_star
op_star
id|table_ptr
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|table
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_find_table&quot;
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
id|ACPI_NAME_SIZE
)paren
op_logical_or
(paren
id|ACPI_STRLEN
(paren
id|oem_id
)paren
OG
r_sizeof
(paren
id|table-&gt;oem_id
)paren
)paren
op_logical_or
(paren
id|ACPI_STRLEN
(paren
id|oem_table_id
)paren
OG
r_sizeof
(paren
id|table-&gt;oem_table_id
)paren
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_STRING_LIMIT
)paren
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
id|DSDT_SIG
comma
id|ACPI_NAME_SIZE
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * The DSDT pointer is contained in the FADT, not the RSDT.&n;&t;&t; * This code should suffice, because the only code that would perform&n;&t;&t; * a &quot;find&quot; on the DSDT is the data_table_region() AML opcode -- in&n;&t;&t; * which case, the DSDT is guaranteed to be already loaded.&n;&t;&t; * If this becomes insufficient, the FADT will have to be found first.&n;&t;&t; */
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
id|table
op_assign
id|acpi_gbl_DSDT
suffix:semicolon
)brace
r_else
(brace
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
)brace
multiline_comment|/* Check oem_id and oem_table_id */
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;Found table [%4.4s]&bslash;n&quot;
comma
id|table-&gt;signature
)paren
)paren
suffix:semicolon
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_firmware_table&n; *&n; * PARAMETERS:  Signature       - Any ACPI table signature&n; *              Instance        - the non zero instance of the table, allows&n; *                                support for multiple tables of the same type&n; *              Flags           - Physical/Virtual support&n; *              table_pointer   - Where a buffer containing the table is&n; *                                returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get an ACPI table. A buffer is&n; *              allocated for the table and returned in table_pointer.&n; *              This table will be a complete table including the header.&n; *&n; ******************************************************************************/
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
r_struct
id|acpi_table_header
op_star
op_star
id|table_pointer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_pointer
id|address
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_table_desc
op_star
id|table_info
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_table_desc
op_star
id|rsdt_info
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
l_string|&quot;acpi_get_firmware_table&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that at least the table manager is initialized.  We don&squot;t&n;&t; * require that the entire ACPI subsystem is up for this interface.&n;&t; * If we have a buffer, we must have a length too&n;&t; */
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
multiline_comment|/* Ensure that we have a RSDP */
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
id|address
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
l_string|&quot;RSDP not found&bslash;n&quot;
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
id|address.pointer.physical
comma
r_sizeof
(paren
r_struct
id|rsdp_descriptor
)paren
comma
(paren
r_void
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
id|address.pointer.logical
suffix:semicolon
)brace
multiline_comment|/* The signature and checksum must both be correct */
r_if
c_cond
(paren
id|ACPI_STRNCMP
(paren
(paren
r_char
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
id|return_ACPI_STATUS
(paren
id|AE_BAD_SIGNATURE
)paren
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
id|return_ACPI_STATUS
(paren
id|AE_BAD_CHECKSUM
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Get the RSDT address via the RSDP */
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
id|ACPI_FORMAT_UINT64
(paren
id|address.pointer.value
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Insert processor_mode flags */
id|address.pointer_type
op_or_assign
id|flags
suffix:semicolon
multiline_comment|/* Get and validate the RSDT */
id|rsdt_info
op_assign
id|ACPI_MEM_CALLOCATE
(paren
r_sizeof
(paren
r_struct
id|acpi_table_desc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdt_info
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_tb_get_table
(paren
op_amp
id|address
comma
id|rsdt_info
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
id|status
op_assign
id|acpi_tb_validate_rsdt
(paren
id|rsdt_info-&gt;pointer
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
multiline_comment|/* Allocate a scratch table header and table descriptor */
id|header
op_assign
id|ACPI_MEM_ALLOCATE
(paren
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|table_info
op_assign
id|ACPI_MEM_ALLOCATE
(paren
r_sizeof
(paren
r_struct
id|acpi_table_desc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table_info
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
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
id|rsdt_info-&gt;pointer
)paren
suffix:semicolon
id|address.pointer_type
op_assign
id|acpi_gbl_table_flags
op_or
id|flags
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
multiline_comment|/* Get the next table pointer, handle RSDT vs. XSDT */
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
id|ACPI_CAST_PTR
(paren
id|RSDT_DESCRIPTOR
comma
id|rsdt_info-&gt;pointer
)paren
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
(paren
id|ACPI_CAST_PTR
(paren
id|XSDT_DESCRIPTOR
comma
id|rsdt_info-&gt;pointer
)paren
)paren
op_member_access_from_pointer
id|table_offset_entry
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* Get the table header */
id|status
op_assign
id|acpi_tb_get_table_header
(paren
op_amp
id|address
comma
id|header
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
id|header-&gt;signature
comma
id|signature
comma
id|ACPI_NAME_SIZE
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
multiline_comment|/* Found the correct instance, get the entire table */
id|status
op_assign
id|acpi_tb_get_table_body
(paren
op_amp
id|address
comma
id|header
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
r_goto
id|cleanup
suffix:semicolon
)brace
op_star
id|table_pointer
op_assign
id|table_info-&gt;pointer
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Did not find the table */
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
id|cleanup
suffix:colon
id|acpi_os_unmap_memory
(paren
id|rsdt_info-&gt;pointer
comma
(paren
id|acpi_size
)paren
id|rsdt_info-&gt;pointer-&gt;length
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|rsdt_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|header
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|header
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|table_info
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|table_info
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_find_root_pointer&n; *&n; * PARAMETERS:  **rsdp_address          - Where to place the RSDP address&n; *              Flags                   - Logical/Physical addressing&n; *&n; * RETURN:      Status, Physical address of the RSDP&n; *&n; * DESCRIPTION: Find the RSDP&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_find_root_pointer
id|acpi_find_root_pointer
(paren
id|u32
id|flags
comma
r_struct
id|acpi_pointer
op_star
id|rsdp_address
)paren
(brace
r_struct
id|acpi_table_desc
id|table_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_find_root_pointer&quot;
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
l_string|&quot;RSDP structure not found, %s Flags=%X&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
comma
id|flags
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_scan_memory_for_rsdp&n; *&n; * PARAMETERS:  start_address       - Starting pointer for search&n; *              Length              - Maximum length to search&n; *&n; * RETURN:      Pointer to the RSDP if found, otherwise NULL.&n; *&n; * DESCRIPTION: Search a block of memory for the RSDP signature&n; *&n; ******************************************************************************/
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
l_string|&quot;tb_scan_memory_for_rsdp&quot;
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
id|ACPI_RSDP_SCAN_STEP
comma
id|mem_rover
op_add_assign
id|ACPI_RSDP_SCAN_STEP
)paren
(brace
multiline_comment|/* The signature and checksum must both be correct */
r_if
c_cond
(paren
id|ACPI_STRNCMP
(paren
(paren
r_char
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_find_rsdp&n; *&n; * PARAMETERS:  *table_info             - Where the table info is returned&n; *              Flags                   - Current memory mode (logical vs.&n; *                                        physical addressing)&n; *&n; * RETURN:      Status, RSDP physical address&n; *&n; * DESCRIPTION: search lower 1_mbyte of memory for the root system descriptor&n; *              pointer structure.  If it is found, set *RSDP to point to it.&n; *&n; *              NOTE1: The RSDp must be either in the first 1_k of the Extended&n; *              BIOS Data Area or between E0000 and FFFFF (From ACPI Spec.)&n; *              Only a 32-bit physical address is necessary.&n; *&n; *              NOTE2: This function is always available, regardless of the&n; *              initialization state of the rest of ACPI.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_find_rsdp
id|acpi_tb_find_rsdp
(paren
r_struct
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
id|u32
id|physical_address
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_find_rsdp&quot;
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
multiline_comment|/*&n;&t;&t; * 1a) Get the location of the EBDA&n;&t;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
(paren
id|acpi_physical_address
)paren
id|ACPI_EBDA_PTR_LOCATION
comma
id|ACPI_EBDA_PTR_LENGTH
comma
(paren
r_void
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not map memory at %8.8X for length %X&bslash;n&quot;
comma
id|ACPI_EBDA_PTR_LOCATION
comma
id|ACPI_EBDA_PTR_LENGTH
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_MOVE_16_TO_32
(paren
op_amp
id|physical_address
comma
id|table_ptr
)paren
suffix:semicolon
id|physical_address
op_lshift_assign
l_int|4
suffix:semicolon
multiline_comment|/* Convert segment to physical address */
id|acpi_os_unmap_memory
(paren
id|table_ptr
comma
id|ACPI_EBDA_PTR_LENGTH
)paren
suffix:semicolon
multiline_comment|/* EBDA present? */
r_if
c_cond
(paren
id|physical_address
OG
l_int|0x400
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 1b) Search EBDA paragraphs (EBDa is required to be a minimum of 1_k length)&n;&t;&t;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
(paren
id|acpi_physical_address
)paren
id|physical_address
comma
id|ACPI_EBDA_WINDOW_SIZE
comma
(paren
r_void
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not map memory at %8.8X for length %X&bslash;n&quot;
comma
id|physical_address
comma
id|ACPI_EBDA_WINDOW_SIZE
)paren
)paren
suffix:semicolon
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
id|ACPI_EBDA_WINDOW_SIZE
)paren
suffix:semicolon
id|acpi_os_unmap_memory
(paren
id|table_ptr
comma
id|ACPI_EBDA_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_rover
)paren
(brace
multiline_comment|/* Found it, return the physical address */
id|physical_address
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
(paren
id|acpi_physical_address
)paren
id|physical_address
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * 2) Search upper memory: 16-byte boundaries in E0000h-FFFFFh&n;&t;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
(paren
id|acpi_physical_address
)paren
id|ACPI_HI_RSDP_WINDOW_BASE
comma
id|ACPI_HI_RSDP_WINDOW_SIZE
comma
(paren
r_void
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not map memory at %8.8X for length %X&bslash;n&quot;
comma
id|ACPI_HI_RSDP_WINDOW_BASE
comma
id|ACPI_HI_RSDP_WINDOW_SIZE
)paren
)paren
suffix:semicolon
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
id|ACPI_HI_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
id|acpi_os_unmap_memory
(paren
id|table_ptr
comma
id|ACPI_HI_RSDP_WINDOW_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_rover
)paren
(brace
multiline_comment|/* Found it, return the physical address */
id|physical_address
op_assign
id|ACPI_HI_RSDP_WINDOW_BASE
op_plus
id|ACPI_PTR_DIFF
(paren
id|mem_rover
comma
id|table_ptr
)paren
suffix:semicolon
id|table_info-&gt;physical_address
op_assign
(paren
id|acpi_physical_address
)paren
id|physical_address
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
multiline_comment|/*&n;&t;&t; * 1a) Get the location of the EBDA&n;&t;&t; */
id|ACPI_MOVE_16_TO_32
(paren
op_amp
id|physical_address
comma
id|ACPI_EBDA_PTR_LOCATION
)paren
suffix:semicolon
id|physical_address
op_lshift_assign
l_int|4
suffix:semicolon
multiline_comment|/* Convert segment to physical address */
multiline_comment|/* EBDA present? */
r_if
c_cond
(paren
id|physical_address
OG
l_int|0x400
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 1b) Search EBDA paragraphs (EBDa is required to be a minimum of 1_k length)&n;&t;&t;&t; */
id|mem_rover
op_assign
id|acpi_tb_scan_memory_for_rsdp
(paren
id|ACPI_PHYSADDR_TO_PTR
(paren
id|physical_address
)paren
comma
id|ACPI_EBDA_WINDOW_SIZE
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
multiline_comment|/*&n;&t;&t; * 2) Search upper memory: 16-byte boundaries in E0000h-FFFFFh&n;&t;&t; */
id|mem_rover
op_assign
id|acpi_tb_scan_memory_for_rsdp
(paren
id|ACPI_PHYSADDR_TO_PTR
(paren
id|ACPI_HI_RSDP_WINDOW_BASE
)paren
comma
id|ACPI_HI_RSDP_WINDOW_SIZE
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
