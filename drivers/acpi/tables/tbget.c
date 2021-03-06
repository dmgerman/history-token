multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbget - ACPI Table get* routines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/actables.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbget&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_table&n; *&n; * PARAMETERS:  Address             - Address of table to retrieve.  Can be&n; *                                    Logical or Physical&n; *              table_info          - Where table info is returned&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Get entire table of unknown size.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table
id|acpi_tb_get_table
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_table_header
id|header
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_get_table&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the header in order to get signature and table size&n;&t; */
id|status
op_assign
id|acpi_tb_get_table_header
(paren
id|address
comma
op_amp
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the entire table */
id|status
op_assign
id|acpi_tb_get_table_body
(paren
id|address
comma
op_amp
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not get ACPI table (size %X), %s&bslash;n&quot;
comma
id|header.length
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
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_table_header&n; *&n; * PARAMETERS:  Address             - Address of table to retrieve.  Can be&n; *                                    Logical or Physical&n; *              return_header       - Where the table header is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get an ACPI table header.  Works in both physical or virtual&n; *              addressing mode.  Works with both physical or logical pointers.&n; *              Table is either copied or mapped, depending on the pointer&n; *              type and mode of the processor.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table_header
id|acpi_tb_get_table_header
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_header
op_star
id|return_header
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_get_table_header&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Flags contains the current processor mode (Virtual or Physical addressing)&n;&t; * The pointer_type is either Logical or Physical&n;&t; */
r_switch
c_cond
(paren
id|address-&gt;pointer_type
)paren
(brace
r_case
id|ACPI_PHYSMODE_PHYSPTR
suffix:colon
r_case
id|ACPI_LOGMODE_LOGPTR
suffix:colon
multiline_comment|/* Pointer matches processor mode, copy the header */
id|ACPI_MEMCPY
(paren
id|return_header
comma
id|address-&gt;pointer.logical
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_LOGMODE_PHYSPTR
suffix:colon
multiline_comment|/* Create a logical address for the physical pointer*/
id|status
op_assign
id|acpi_os_map_memory
(paren
id|address-&gt;pointer.physical
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
comma
(paren
r_void
op_star
)paren
op_amp
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not map memory at %8.8X%8.8X for length %X&bslash;n&quot;
comma
id|ACPI_FORMAT_UINT64
(paren
id|address-&gt;pointer.physical
)paren
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
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
multiline_comment|/* Copy header and delete mapping */
id|ACPI_MEMCPY
(paren
id|return_header
comma
id|header
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
id|acpi_os_unmap_memory
(paren
id|header
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid address flags %X&bslash;n&quot;
comma
id|address-&gt;pointer_type
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
id|ACPI_DB_TABLES
comma
l_string|&quot;Table Signature: [%4.4s]&bslash;n&quot;
comma
id|return_header-&gt;signature
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_table_body&n; *&n; * PARAMETERS:  Address             - Address of table to retrieve.  Can be&n; *                                    Logical or Physical&n; *              Header              - Header of the table to retrieve&n; *              table_info          - Where the table info is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get an entire ACPI table with support to allow the host OS to&n; *              replace the table with a newer version (table override.)&n; *              Works in both physical or virtual&n; *              addressing mode.  Works with both physical or logical pointers.&n; *              Table is either copied or mapped, depending on the pointer&n; *              type and mode of the processor.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table_body
id|acpi_tb_get_table_body
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_header
op_star
id|header
comma
r_struct
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
l_string|&quot;tb_get_table_body&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table_info
op_logical_or
op_logical_neg
id|address
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Attempt table override.&n;&t; */
id|status
op_assign
id|acpi_tb_table_override
(paren
id|header
comma
id|table_info
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
multiline_comment|/* Table was overridden by the host OS */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* No override, get the original table */
id|status
op_assign
id|acpi_tb_get_this_table
(paren
id|address
comma
id|header
comma
id|table_info
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_table_override&n; *&n; * PARAMETERS:  Header              - Pointer to table header&n; *              table_info          - Return info if table is overridden&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Attempts override of current table with a new one if provided&n; *              by the host OS.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_table_override
id|acpi_tb_table_override
(paren
r_struct
id|acpi_table_header
op_star
id|header
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
r_struct
id|acpi_table_header
op_star
id|new_table
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_pointer
id|address
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_table_override&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The OSL will examine the header and decide whether to override this&n;&t; * table.  If it decides to override, a table will be returned in new_table,&n;&t; * which we will then copy.&n;&t; */
id|status
op_assign
id|acpi_os_table_override
(paren
id|header
comma
op_amp
id|new_table
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
multiline_comment|/* Some severe error from the OSL, but we basically ignore it */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not override ACPI table, %s&bslash;n&quot;
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
r_if
c_cond
(paren
op_logical_neg
id|new_table
)paren
(brace
multiline_comment|/* No table override */
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We have a new table to override the old one.  Get a copy of&n;&t; * the new one.  We know that the new table has a logical pointer.&n;&t; */
id|address.pointer_type
op_assign
id|ACPI_LOGICAL_POINTER
op_or
id|ACPI_LOGICAL_ADDRESSING
suffix:semicolon
id|address.pointer.logical
op_assign
id|new_table
suffix:semicolon
id|status
op_assign
id|acpi_tb_get_this_table
(paren
op_amp
id|address
comma
id|new_table
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
l_string|&quot;Could not copy override ACPI table, %s&bslash;n&quot;
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
multiline_comment|/* Copy the table info */
id|ACPI_REPORT_INFO
(paren
(paren
l_string|&quot;Table [%4.4s] replaced by host OS&bslash;n&quot;
comma
id|table_info-&gt;pointer-&gt;signature
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_this_table&n; *&n; * PARAMETERS:  Address             - Address of table to retrieve.  Can be&n; *                                    Logical or Physical&n; *              Header              - Header of the table to retrieve&n; *              table_info          - Where the table info is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get an entire ACPI table.  Works in both physical or virtual&n; *              addressing mode.  Works with both physical or logical pointers.&n; *              Table is either copied or mapped, depending on the pointer&n; *              type and mode of the processor.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_this_table
id|acpi_tb_get_this_table
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_header
op_star
id|header
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
r_struct
id|acpi_table_header
op_star
id|full_table
op_assign
l_int|NULL
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
l_string|&quot;tb_get_this_table&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Flags contains the current processor mode (Virtual or Physical addressing)&n;&t; * The pointer_type is either Logical or Physical&n;&t; */
r_switch
c_cond
(paren
id|address-&gt;pointer_type
)paren
(brace
r_case
id|ACPI_PHYSMODE_PHYSPTR
suffix:colon
r_case
id|ACPI_LOGMODE_LOGPTR
suffix:colon
multiline_comment|/* Pointer matches processor mode, copy the table to a new buffer */
id|full_table
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|header-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|full_table
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not allocate table memory for [%4.4s] length %X&bslash;n&quot;
comma
id|header-&gt;signature
comma
id|header-&gt;length
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the entire table (including header) to the local buffer */
id|ACPI_MEMCPY
(paren
id|full_table
comma
id|address-&gt;pointer.logical
comma
id|header-&gt;length
)paren
suffix:semicolon
multiline_comment|/* Save allocation type */
id|allocation
op_assign
id|ACPI_MEM_ALLOCATED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_LOGMODE_PHYSPTR
suffix:colon
multiline_comment|/*&n;&t;&t; * Just map the table&squot;s physical memory&n;&t;&t; * into our address space.&n;&t;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
id|address-&gt;pointer.physical
comma
(paren
id|acpi_size
)paren
id|header-&gt;length
comma
(paren
r_void
op_star
)paren
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not map memory for table [%4.4s] at %8.8X%8.8X for length %X&bslash;n&quot;
comma
id|header-&gt;signature
comma
id|ACPI_FORMAT_UINT64
(paren
id|address-&gt;pointer.physical
)paren
comma
id|header-&gt;length
)paren
)paren
suffix:semicolon
r_return
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
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid address flags %X&bslash;n&quot;
comma
id|address-&gt;pointer_type
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Validate checksum for _most_ tables,&n;&t; * even the ones whose signature we don&squot;t recognize&n;&t; */
r_if
c_cond
(paren
id|table_info-&gt;type
op_ne
id|ACPI_TABLE_FACS
)paren
(brace
id|status
op_assign
id|acpi_tb_verify_table_checksum
(paren
id|full_table
)paren
suffix:semicolon
macro_line|#if (!ACPI_CHECKSUM_ABORT)
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Ignore the error if configuration says so */
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* Return values */
id|table_info-&gt;pointer
op_assign
id|full_table
suffix:semicolon
id|table_info-&gt;length
op_assign
(paren
id|acpi_size
)paren
id|header-&gt;length
suffix:semicolon
id|table_info-&gt;allocation
op_assign
id|allocation
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Found table [%4.4s] at %8.8X%8.8X, mapped/copied to %p&bslash;n&quot;
comma
id|full_table-&gt;signature
comma
id|ACPI_FORMAT_UINT64
(paren
id|address-&gt;pointer.physical
)paren
comma
id|full_table
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_table_ptr&n; *&n; * PARAMETERS:  table_type      - one of the defined table types&n; *              Instance        - Which table of this type&n; *              table_ptr_loc   - pointer to location to place the pointer for&n; *                                return&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the pointer to an ACPI table.&n; *&n; ******************************************************************************/
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
r_struct
id|acpi_table_header
op_star
op_star
id|table_ptr_loc
)paren
(brace
r_struct
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_get_table_ptr&quot;
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
multiline_comment|/* Get the first */
op_star
id|table_ptr_loc
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_table_lists
(braket
id|table_type
)braket
dot
id|next
)paren
(brace
op_star
id|table_ptr_loc
op_assign
id|acpi_gbl_table_lists
(braket
id|table_type
)braket
dot
id|next-&gt;pointer
suffix:semicolon
)brace
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
id|acpi_gbl_table_lists
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
multiline_comment|/* Walk the list to get the desired table&n;&t; * Since the if (Instance == 1) check above checked for the&n;&t; * first table, setting table_desc equal to the .Next member&n;&t; * is actually pointing to the second table.  Therefore, we&n;&t; * need to walk from the 2nd table until we reach the Instance&n;&t; * that the user is looking for and return its table pointer.&n;&t; */
id|table_desc
op_assign
id|acpi_gbl_table_lists
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
eof
