multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbutils - Table manipulation utilities&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/actables.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbutils&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_handle_to_object&n; *&n; * PARAMETERS:  table_id            - Id for which the function is searching&n; *              table_desc          - Pointer to return the matching table&n; *                                      descriptor.&n; *&n; * RETURN:      Search the tables to find one with a matching table_id and&n; *              return a pointer to that table descriptor.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_handle_to_object
id|acpi_tb_handle_to_object
(paren
id|u16
id|table_id
comma
r_struct
id|acpi_table_desc
op_star
op_star
id|return_table_desc
)paren
(brace
id|u32
id|i
suffix:semicolon
r_struct
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;tb_handle_to_object&quot;
)paren
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
id|ACPI_TABLE_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|table_desc
op_assign
id|acpi_gbl_table_lists
(braket
id|i
)braket
dot
id|next
suffix:semicolon
r_while
c_loop
(paren
id|table_desc
)paren
(brace
r_if
c_cond
(paren
id|table_desc-&gt;table_id
op_eq
id|table_id
)paren
(brace
op_star
id|return_table_desc
op_assign
id|table_desc
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|table_desc
op_assign
id|table_desc-&gt;next
suffix:semicolon
)brace
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;table_id=%X does not exist&bslash;n&quot;
comma
id|table_id
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_validate_table_header&n; *&n; * PARAMETERS:  table_header        - Logical pointer to the table&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Check an ACPI table header for validity&n; *&n; * NOTE:  Table pointers are validated as follows:&n; *          1) Table pointer must point to valid physical memory&n; *          2) Signature must be 4 ASCII chars, even if we don&squot;t recognize the&n; *             name&n; *          3) Table must be readable for length specified in the header&n; *          4) Table checksum must be valid (with the exception of the FACS&n; *              which has no checksum because it contains variable fields)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_validate_table_header
id|acpi_tb_validate_table_header
(paren
r_struct
id|acpi_table_header
op_star
id|table_header
)paren
(brace
id|acpi_name
id|signature
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;tb_validate_table_header&quot;
)paren
suffix:semicolon
multiline_comment|/* Verify that this is a valid address */
r_if
c_cond
(paren
op_logical_neg
id|acpi_os_readable
(paren
id|table_header
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Cannot read table header at %p&bslash;n&quot;
comma
id|table_header
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_ADDRESS
)paren
suffix:semicolon
)brace
multiline_comment|/* Ensure that the signature is 4 ASCII characters */
id|ACPI_MOVE_32_TO_32
(paren
op_amp
id|signature
comma
id|table_header-&gt;signature
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_acpi_name
(paren
id|signature
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Table signature at %p [%p] has invalid characters&bslash;n&quot;
comma
id|table_header
comma
op_amp
id|signature
)paren
)paren
suffix:semicolon
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Invalid table signature found: [%4.4s]&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|signature
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
id|table_header
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_SIGNATURE
)paren
suffix:semicolon
)brace
multiline_comment|/* Validate the table length */
r_if
c_cond
(paren
id|table_header-&gt;length
OL
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid length in table header %p name %4.4s&bslash;n&quot;
comma
id|table_header
comma
(paren
r_char
op_star
)paren
op_amp
id|signature
)paren
)paren
suffix:semicolon
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Invalid table header length (0x%X) found&bslash;n&quot;
comma
(paren
id|u32
)paren
id|table_header-&gt;length
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
id|table_header
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_HEADER
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_verify_table_checksum&n; *&n; * PARAMETERS:  *table_header           - ACPI table to verify&n; *&n; * RETURN:      8 bit checksum of table&n; *&n; * DESCRIPTION: Does an 8 bit checksum of table and returns status.  A correct&n; *              table should have a checksum of 0.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_verify_table_checksum
id|acpi_tb_verify_table_checksum
(paren
r_struct
id|acpi_table_header
op_star
id|table_header
)paren
(brace
id|u8
id|checksum
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_verify_table_checksum&quot;
)paren
suffix:semicolon
multiline_comment|/* Compute the checksum on the table */
id|checksum
op_assign
id|acpi_tb_checksum
(paren
id|table_header
comma
id|table_header-&gt;length
)paren
suffix:semicolon
multiline_comment|/* Return the appropriate exception */
r_if
c_cond
(paren
id|checksum
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Invalid checksum in table [%4.4s] (%02X, sum %02X is not zero)&bslash;n&quot;
comma
id|table_header-&gt;signature
comma
(paren
id|u32
)paren
id|table_header-&gt;checksum
comma
(paren
id|u32
)paren
id|checksum
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_BAD_CHECKSUM
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_checksum&n; *&n; * PARAMETERS:  Buffer              - Buffer to checksum&n; *              Length              - Size of the buffer&n; *&n; * RETURNS      8 bit checksum of buffer&n; *&n; * DESCRIPTION: Computes an 8 bit checksum of the buffer(length) and returns it.&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_tb_checksum
id|acpi_tb_checksum
(paren
r_void
op_star
id|buffer
comma
id|u32
id|length
)paren
(brace
r_const
id|u8
op_star
id|limit
suffix:semicolon
r_const
id|u8
op_star
id|rover
suffix:semicolon
id|u8
id|sum
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_logical_and
id|length
)paren
(brace
multiline_comment|/*  Buffer and Length are valid   */
id|limit
op_assign
(paren
id|u8
op_star
)paren
id|buffer
op_plus
id|length
suffix:semicolon
r_for
c_loop
(paren
id|rover
op_assign
id|buffer
suffix:semicolon
id|rover
OL
id|limit
suffix:semicolon
id|rover
op_increment
)paren
(brace
id|sum
op_assign
(paren
id|u8
)paren
(paren
id|sum
op_plus
op_star
id|rover
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|sum
)paren
suffix:semicolon
)brace
eof
