multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbgetall - Get all required ACPI tables&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/actables.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbgetall&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_primary_table&n; *&n; * PARAMETERS:  Address             - Physical address of table to retrieve&n; *              *table_info         - Where the table info is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Maps the physical address of table into a logical address&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_primary_table
id|acpi_tb_get_primary_table
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
l_string|&quot;tb_get_primary_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Ignore a NULL address in the RSDT */
r_if
c_cond
(paren
op_logical_neg
id|address-&gt;pointer.value
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
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
multiline_comment|/* Clear the table_info */
id|ACPI_MEMSET
(paren
id|table_info
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_table_desc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check the table signature and make sure it is recognized.&n;&t; * Also checks the header checksum&n;&t; */
id|table_info-&gt;pointer
op_assign
op_amp
id|header
suffix:semicolon
id|status
op_assign
id|acpi_tb_recognize_table
(paren
id|table_info
comma
id|ACPI_TABLE_PRIMARY
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the table */
id|status
op_assign
id|acpi_tb_install_table
(paren
id|table_info
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_secondary_table&n; *&n; * PARAMETERS:  Address             - Physical address of table to retrieve&n; *              *table_info         - Where the table info is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Maps the physical address of table into a logical address&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_secondary_table
id|acpi_tb_get_secondary_table
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
id|acpi_string
id|signature
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
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;tb_get_secondary_table&quot;
comma
id|signature
)paren
suffix:semicolon
multiline_comment|/* Get the header in order to match the signature */
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
multiline_comment|/* Signature must match request */
r_if
c_cond
(paren
id|ACPI_STRNCMP
(paren
id|header.signature
comma
id|signature
comma
id|ACPI_NAME_SIZE
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Incorrect table signature - wanted [%s] found [%4.4s]&bslash;n&quot;
comma
id|signature
comma
id|header.signature
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_SIGNATURE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check the table signature and make sure it is recognized.&n;&t; * Also checks the header checksum&n;&t; */
id|table_info-&gt;pointer
op_assign
op_amp
id|header
suffix:semicolon
id|status
op_assign
id|acpi_tb_recognize_table
(paren
id|table_info
comma
id|ACPI_TABLE_SECONDARY
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the table */
id|status
op_assign
id|acpi_tb_install_table
(paren
id|table_info
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_required_tables&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load and validate tables other than the RSDT.  The RSDT must&n; *              already be loaded and validated.&n; *&n; *              Get the minimum set of ACPI tables, namely:&n; *&n; *              1) FADT (via RSDT in loop below)&n; *              2) FACS (via FADT)&n; *              3) DSDT (via FADT)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_required_tables
id|acpi_tb_get_required_tables
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|i
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
l_string|&quot;tb_get_required_tables&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;%d ACPI tables in RSDT&bslash;n&quot;
comma
id|acpi_gbl_rsdt_table_count
)paren
)paren
suffix:semicolon
id|address.pointer_type
op_assign
id|acpi_gbl_table_flags
op_or
id|ACPI_LOGICAL_ADDRESSING
suffix:semicolon
multiline_comment|/*&n;&t; * Loop through all table pointers found in RSDT.&n;&t; * This will NOT include the FACS and DSDT - we must get&n;&t; * them after the loop.&n;&t; *&n;&t; * The only tables we are interested in getting here is the FADT and&n;&t; * any SSDTs.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_rsdt_table_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Get the table address from the common internal XSDT */
id|address.pointer.value
op_assign
id|acpi_gbl_XSDT-&gt;table_offset_entry
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the tables needed by this subsystem (FADT and any SSDTs).&n;&t;&t; * NOTE: All other tables are completely ignored at this time.&n;&t;&t; */
id|status
op_assign
id|acpi_tb_get_primary_table
(paren
op_amp
id|address
comma
op_amp
id|table_info
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_ne
id|AE_OK
)paren
op_logical_and
(paren
id|status
op_ne
id|AE_TABLE_NOT_SUPPORTED
)paren
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;%s, while getting table at %8.8X%8.8X&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
comma
id|ACPI_FORMAT_UINT64
(paren
id|address.pointer.value
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* We must have a FADT to continue */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;No FADT present in RSDT/XSDT&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_ACPI_TABLES
)paren
suffix:semicolon
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not convert FADT to internal common format&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the FACS (Pointed to by the FADT)&n;&t; */
id|address.pointer.value
op_assign
id|acpi_gbl_FADT-&gt;xfirmware_ctrl
suffix:semicolon
id|status
op_assign
id|acpi_tb_get_secondary_table
(paren
op_amp
id|address
comma
id|FACS_SIG
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not get/install the FACS, %s&bslash;n&quot;
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
multiline_comment|/*&n;&t; * Get/install the DSDT (Pointed to by the FADT)&n;&t; */
id|address.pointer.value
op_assign
id|acpi_gbl_FADT-&gt;Xdsdt
suffix:semicolon
id|status
op_assign
id|acpi_tb_get_secondary_table
(paren
op_amp
id|address
comma
id|DSDT_SIG
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not get/install the DSDT&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Set Integer Width (32/64) based upon DSDT revision */
id|acpi_ut_set_integer_width
(paren
id|acpi_gbl_DSDT-&gt;revision
)paren
suffix:semicolon
multiline_comment|/* Dump the entire DSDT */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;Hex dump of entire DSDT, size %d (0x%X), Integer width = %d&bslash;n&quot;
comma
id|acpi_gbl_DSDT-&gt;length
comma
id|acpi_gbl_DSDT-&gt;length
comma
id|acpi_gbl_integer_bit_width
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
id|acpi_gbl_DSDT-&gt;length
)paren
suffix:semicolon
multiline_comment|/* Always delete the RSDP mapping, we are done with it */
id|acpi_tb_delete_tables_by_type
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
eof
