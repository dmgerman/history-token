multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbutils - Table manipulation utilities&n; *              $Revision: 53 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;actables.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbutils&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_handle_to_object&n; *&n; * PARAMETERS:  Table_id            - Id for which the function is searching&n; *              Table_desc          - Pointer to return the matching table&n; *                                      descriptor.&n; *&n; * RETURN:      Search the tables to find one with a matching Table_id and&n; *              return a pointer to that table descriptor.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_handle_to_object
id|acpi_tb_handle_to_object
(paren
id|u16
id|table_id
comma
id|acpi_table_desc
op_star
op_star
id|table_desc
)paren
(brace
id|u32
id|i
suffix:semicolon
id|acpi_table_desc
op_star
id|list_head
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Tb_handle_to_object&quot;
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
id|list_head
op_assign
op_amp
id|acpi_gbl_acpi_tables
(braket
id|i
)braket
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|list_head-&gt;table_id
op_eq
id|table_id
)paren
(brace
op_star
id|table_desc
op_assign
id|list_head
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|list_head
op_assign
id|list_head-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|list_head
op_ne
op_amp
id|acpi_gbl_acpi_tables
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Table_id=%X does not exist&bslash;n&quot;
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_validate_table_header&n; *&n; * PARAMETERS:  Table_header        - Logical pointer to the table&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Check an ACPI table header for validity&n; *&n; * NOTE:  Table pointers are validated as follows:&n; *          1) Table pointer must point to valid physical memory&n; *          2) Signature must be 4 ASCII chars, even if we don&squot;t recognize the&n; *             name&n; *          3) Table must be readable for length specified in the header&n; *          4) Table checksum must be valid (with the exception of the FACS&n; *              which has no checksum for some odd reason)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_validate_table_header
id|acpi_tb_validate_table_header
(paren
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
l_string|&quot;Tb_validate_table_header&quot;
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
id|ACPI_MOVE_UNALIGNED32_TO_32
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_map_acpi_table&n; *&n; * PARAMETERS:  Physical_address        - Physical address of table to map&n; *              *Size                   - Size of the table.  If zero, the size&n; *                                        from the table header is used.&n; *                                        Actual size is returned here.&n; *              **Logical_address       - Logical address of mapped table&n; *&n; * RETURN:      Logical address of the mapped table.&n; *&n; * DESCRIPTION: Maps the physical address of table into a logical address&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_map_acpi_table
id|acpi_tb_map_acpi_table
(paren
id|ACPI_PHYSICAL_ADDRESS
id|physical_address
comma
id|ACPI_SIZE
op_star
id|size
comma
id|acpi_table_header
op_star
op_star
id|logical_address
)paren
(brace
id|acpi_table_header
op_star
id|table
suffix:semicolon
id|ACPI_SIZE
id|table_size
op_assign
op_star
id|size
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Tb_map_acpi_table&quot;
)paren
suffix:semicolon
multiline_comment|/* If size is zero, look at the table header to get the actual size */
r_if
c_cond
(paren
(paren
op_star
id|size
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Get the table header so we can extract the table length */
id|status
op_assign
id|acpi_os_map_memory
(paren
id|physical_address
comma
r_sizeof
(paren
id|acpi_table_header
)paren
comma
(paren
r_void
op_star
op_star
)paren
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Extract the full table length before we delete the mapping */
id|table_size
op_assign
(paren
id|ACPI_SIZE
)paren
id|table-&gt;length
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Validate the header and delete the mapping.&n;&t;&t; * We will create a mapping for the full table below.&n;&t;&t; */
id|status
op_assign
id|acpi_tb_validate_table_header
(paren
id|table
)paren
suffix:semicolon
multiline_comment|/* Always unmap the memory for the header */
id|acpi_os_unmap_memory
(paren
id|table
comma
r_sizeof
(paren
id|acpi_table_header
)paren
)paren
suffix:semicolon
multiline_comment|/* Exit if header invalid */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Map the physical memory for the correct length */
id|status
op_assign
id|acpi_os_map_memory
(paren
id|physical_address
comma
id|table_size
comma
(paren
r_void
op_star
op_star
)paren
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
r_return
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
l_string|&quot;Mapped memory for ACPI table, length=%d(%X) at %p&bslash;n&quot;
comma
id|table_size
comma
id|table_size
comma
id|table
)paren
)paren
suffix:semicolon
op_star
id|size
op_assign
id|table_size
suffix:semicolon
op_star
id|logical_address
op_assign
id|table
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_verify_table_checksum&n; *&n; * PARAMETERS:  *Table_header           - ACPI table to verify&n; *&n; * RETURN:      8 bit checksum of table&n; *&n; * DESCRIPTION: Does an 8 bit checksum of table and returns status.  A correct&n; *              table should have a checksum of 0.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_verify_table_checksum
id|acpi_tb_verify_table_checksum
(paren
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
l_string|&quot;Tb_verify_table_checksum&quot;
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
l_string|&quot;Invalid checksum (%X) in table %4.4s&bslash;n&quot;
comma
id|checksum
comma
id|table_header-&gt;signature
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_checksum&n; *&n; * PARAMETERS:  Buffer              - Buffer to checksum&n; *              Length              - Size of the buffer&n; *&n; * RETURNS      8 bit checksum of buffer&n; *&n; * DESCRIPTION: Computes an 8 bit checksum of the buffer(length) and returns it.&n; *&n; ******************************************************************************/
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
