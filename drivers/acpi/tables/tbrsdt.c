multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbrsdt - ACPI RSDT table utilities&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/actables.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbrsdt&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_verify_rsdp&n; *&n; * PARAMETERS:  Address         - RSDP (Pointer to RSDT)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load and validate the RSDP (ptr) and RSDT (table)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_verify_rsdp
id|acpi_tb_verify_rsdp
(paren
r_struct
id|acpi_pointer
op_star
id|address
)paren
(brace
r_struct
id|acpi_table_desc
id|table_info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|rsdp_descriptor
op_star
id|rsdp
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_verify_rsdp&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|address-&gt;pointer_type
)paren
(brace
r_case
id|ACPI_LOGICAL_POINTER
suffix:colon
id|rsdp
op_assign
id|address-&gt;pointer.logical
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_PHYSICAL_POINTER
suffix:colon
multiline_comment|/*&n;&t;&t; * Obtain access to the RSDP structure&n;&t;&t; */
id|status
op_assign
id|acpi_os_map_memory
(paren
id|address-&gt;pointer.physical
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
r_break
suffix:semicolon
r_default
suffix:colon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
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
r_char
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
id|ACPI_CAST_PTR
(paren
r_struct
id|acpi_table_header
comma
id|rsdp
)paren
suffix:semicolon
id|table_info.length
op_assign
r_sizeof
(paren
r_struct
id|rsdp_descriptor
)paren
suffix:semicolon
id|table_info.allocation
op_assign
id|ACPI_MEM_MAPPED
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
id|ACPI_CAST_PTR
(paren
r_struct
id|rsdp_descriptor
comma
id|table_info.pointer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
multiline_comment|/* Error exit */
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|acpi_gbl_table_flags
op_amp
id|ACPI_PHYSICAL_POINTER
)paren
(brace
id|acpi_os_unmap_memory
(paren
id|rsdp
comma
r_sizeof
(paren
r_struct
id|rsdp_descriptor
)paren
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_rsdt_address&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      RSDT physical address&n; *&n; * DESCRIPTION: Extract the address of the RSDT or XSDT, depending on the&n; *              version of the RSDP&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_tb_get_rsdt_address
id|acpi_tb_get_rsdt_address
(paren
r_struct
id|acpi_pointer
op_star
id|out_address
)paren
(brace
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|out_address-&gt;pointer_type
op_assign
id|acpi_gbl_table_flags
op_or
id|ACPI_LOGICAL_ADDRESSING
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
id|out_address-&gt;pointer.value
op_assign
id|acpi_gbl_RSDP-&gt;rsdt_physical_address
suffix:semicolon
)brace
r_else
(brace
id|out_address-&gt;pointer.value
op_assign
id|acpi_gbl_RSDP-&gt;xsdt_physical_address
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_validate_rsdt&n; *&n; * PARAMETERS:  table_ptr       - Addressable pointer to the RSDT.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Validate signature for the RSDT or XSDT&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_validate_rsdt
id|acpi_tb_validate_rsdt
(paren
r_struct
id|acpi_table_header
op_star
id|table_ptr
)paren
(brace
r_int
id|no_match
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;tb_validate_rsdt&quot;
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
l_string|&quot;RSDT/XSDT signature at %X (%p) is invalid&bslash;n&quot;
comma
id|acpi_gbl_RSDP-&gt;rsdt_physical_address
comma
(paren
r_void
op_star
)paren
(paren
id|acpi_native_uint
)paren
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_table_rsdt&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load and validate the RSDP (ptr) and RSDT (table)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_get_table_rsdt
id|acpi_tb_get_table_rsdt
(paren
r_void
)paren
(brace
r_struct
id|acpi_table_desc
id|table_info
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
l_string|&quot;tb_get_table_rsdt&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the RSDT/XSDT via the RSDP */
id|acpi_tb_get_rsdt_address
(paren
op_amp
id|address
)paren
suffix:semicolon
id|status
op_assign
id|acpi_tb_get_table
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
l_string|&quot;Could not get the RSDT/XSDT, %s&bslash;n&quot;
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;RSDP located at %p, points to RSDT physical=%8.8X%8.8X &bslash;n&quot;
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
multiline_comment|/* Get the number of tables defined in the RSDT or XSDT */
id|acpi_gbl_rsdt_table_count
op_assign
id|acpi_tb_get_table_count
(paren
id|acpi_gbl_RSDP
comma
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
id|XSDT_DESCRIPTOR
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
eof
