multiline_comment|/*******************************************************************************&n; *&n; * Module Name: dbfileio - Debugger file I/O commands.  These can&squot;t usually&n; *              be used when running the debugger in Ring 0 (Kernel mode)&n; *              $Revision: 59 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acdebug.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;actables.h&quot;
macro_line|#ifdef ENABLE_DEBUGGER
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DEBUGGER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dbfileio&quot;
)paren
multiline_comment|/*&n; * NOTE: this is here for lack of a better place.  It is used in all&n; * flavors of the debugger, need LCD file&n; */
macro_line|#ifdef ACPI_APPLICATION
macro_line|#include &lt;stdio.h&gt;
DECL|variable|acpi_gbl_debug_file
id|FILE
op_star
id|acpi_gbl_debug_file
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
DECL|variable|acpi_gbl_db_table_ptr
id|acpi_table_header
op_star
id|acpi_gbl_db_table_ptr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_match_argument&n; *&n; * PARAMETERS:  User_argument           - User command line&n; *              Arguments               - Array of commands to match against&n; *&n; * RETURN:      Index into command array or ACPI_TYPE_NOT_FOUND if not found&n; *&n; * DESCRIPTION: Search command array for a command match&n; *&n; ******************************************************************************/
id|acpi_object_type
DECL|function|acpi_db_match_argument
id|acpi_db_match_argument
(paren
id|NATIVE_CHAR
op_star
id|user_argument
comma
id|ARGUMENT_INFO
op_star
id|arguments
)paren
(brace
id|u32
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_argument
op_logical_or
id|user_argument
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
r_return
(paren
id|ACPI_TYPE_NOT_FOUND
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|arguments
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ACPI_STRSTR
(paren
id|arguments
(braket
id|i
)braket
dot
id|name
comma
id|user_argument
)paren
op_eq
id|arguments
(braket
id|i
)braket
dot
id|name
)paren
(brace
r_return
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Argument not recognized */
r_return
(paren
id|ACPI_TYPE_NOT_FOUND
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_close_debug_file&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: If open, close the current debug output file&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_close_debug_file
id|acpi_db_close_debug_file
(paren
r_void
)paren
(brace
macro_line|#ifdef ACPI_APPLICATION
r_if
c_cond
(paren
id|acpi_gbl_debug_file
)paren
(brace
id|fclose
(paren
id|acpi_gbl_debug_file
)paren
suffix:semicolon
id|acpi_gbl_debug_file
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_db_output_to_file
op_assign
id|FALSE
suffix:semicolon
id|acpi_os_printf
(paren
l_string|&quot;Debug output file %s closed&bslash;n&quot;
comma
id|acpi_gbl_db_debug_filename
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_open_debug_file&n; *&n; * PARAMETERS:  Name                - Filename to open&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Open a file where debug output will be directed.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_db_open_debug_file
id|acpi_db_open_debug_file
(paren
id|NATIVE_CHAR
op_star
id|name
)paren
(brace
macro_line|#ifdef ACPI_APPLICATION
id|acpi_db_close_debug_file
(paren
)paren
suffix:semicolon
id|acpi_gbl_debug_file
op_assign
id|fopen
(paren
id|name
comma
l_string|&quot;w+&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_debug_file
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Debug output file %s opened&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|ACPI_STRCPY
(paren
id|acpi_gbl_db_debug_filename
comma
id|name
)paren
suffix:semicolon
id|acpi_gbl_db_output_to_file
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;Could not open debug file %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#ifdef ACPI_APPLICATION
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_load_table&n; *&n; * PARAMETERS:  fp              - File that contains table&n; *              Table_ptr       - Return value, buffer with table&n; *              Table_lenght    - Return value, length of table&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load the DSDT from the file pointer&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_db_load_table
id|acpi_db_load_table
c_func
(paren
id|FILE
op_star
id|fp
comma
id|acpi_table_header
op_star
op_star
id|table_ptr
comma
id|u32
op_star
id|table_length
)paren
(brace
id|acpi_table_header
id|table_header
suffix:semicolon
id|u8
op_star
id|aml_start
suffix:semicolon
id|u32
id|aml_length
suffix:semicolon
id|u32
id|actual
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* Read the table header */
r_if
c_cond
(paren
id|fread
(paren
op_amp
id|table_header
comma
l_int|1
comma
r_sizeof
(paren
id|table_header
)paren
comma
id|fp
)paren
op_ne
r_sizeof
(paren
id|acpi_table_header
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Couldn&squot;t read the table header&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_SIGNATURE
)paren
suffix:semicolon
)brace
multiline_comment|/* Validate the table header/length */
id|status
op_assign
id|acpi_tb_validate_table_header
(paren
op_amp
id|table_header
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
op_logical_or
(paren
id|table_header.length
OG
l_int|524288
)paren
)paren
multiline_comment|/* 1/2 Mbyte should be enough */
(brace
id|acpi_os_printf
(paren
l_string|&quot;Table header is invalid!&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|AE_ERROR
)paren
suffix:semicolon
)brace
multiline_comment|/* We only support a limited number of table types */
r_if
c_cond
(paren
id|ACPI_STRNCMP
(paren
(paren
r_char
op_star
)paren
id|table_header.signature
comma
id|DSDT_SIG
comma
l_int|4
)paren
op_logical_and
id|ACPI_STRNCMP
(paren
(paren
r_char
op_star
)paren
id|table_header.signature
comma
id|PSDT_SIG
comma
l_int|4
)paren
op_logical_and
id|ACPI_STRNCMP
(paren
(paren
r_char
op_star
)paren
id|table_header.signature
comma
id|SSDT_SIG
comma
l_int|4
)paren
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Table signature is invalid&bslash;n&quot;
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
op_amp
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
id|AE_ERROR
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate a buffer for the table */
op_star
id|table_length
op_assign
id|table_header.length
suffix:semicolon
op_star
id|table_ptr
op_assign
id|acpi_os_allocate
(paren
(paren
r_int
)paren
op_star
id|table_length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|table_ptr
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Could not allocate memory for ACPI table %4.4s (size=%X)&bslash;n&quot;
comma
id|table_header.signature
comma
id|table_header.length
)paren
suffix:semicolon
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|aml_start
op_assign
(paren
id|u8
op_star
)paren
op_star
id|table_ptr
op_plus
r_sizeof
(paren
id|table_header
)paren
suffix:semicolon
id|aml_length
op_assign
op_star
id|table_length
op_minus
r_sizeof
(paren
id|table_header
)paren
suffix:semicolon
multiline_comment|/* Copy the header to the buffer */
id|ACPI_MEMCPY
(paren
op_star
id|table_ptr
comma
op_amp
id|table_header
comma
r_sizeof
(paren
id|table_header
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the rest of the table */
id|actual
op_assign
id|fread
(paren
id|aml_start
comma
l_int|1
comma
(paren
r_int
)paren
id|aml_length
comma
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|actual
op_eq
id|aml_length
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|actual
OG
l_int|0
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Warning - reading table, asked for %X got %X&bslash;n&quot;
comma
id|aml_length
comma
id|actual
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;Error - could not read the table file&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_os_free
(paren
op_star
id|table_ptr
)paren
suffix:semicolon
op_star
id|table_ptr
op_assign
l_int|NULL
suffix:semicolon
op_star
id|table_length
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|AE_ERROR
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Ae_local_load_table&n; *&n; * PARAMETERS:  Table_ptr       - pointer to a buffer containing the entire&n; *                                table to be loaded&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to load a table from the caller&squot;s&n; *              buffer.  The buffer must contain an entire ACPI Table including&n; *              a valid header.  The header fields will be verified, and if it&n; *              is determined that the table is invalid, the call will fail.&n; *&n; *              If the call fails an appropriate status will be returned.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|ae_local_load_table
id|ae_local_load_table
(paren
id|acpi_table_header
op_star
id|table_ptr
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_table_desc
id|table_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ae_local_load_table&quot;
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
multiline_comment|/* Install the new table into the local data structures */
id|table_info.pointer
op_assign
id|table_ptr
suffix:semicolon
id|status
op_assign
id|acpi_tb_install_table
(paren
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
multiline_comment|/* Free table allocated by Acpi_tb_get_table */
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
macro_line|#ifndef PARSER_ONLY
id|status
op_assign
id|acpi_ns_load_table
(paren
id|table_info.installed_desc
comma
id|acpi_gbl_root_node
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
multiline_comment|/* Uninstall table and free the buffer */
id|acpi_tb_delete_acpi_table
(paren
id|ACPI_TABLE_DSDT
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
macro_line|#endif
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_db_load_acpi_table&n; *&n; * PARAMETERS:  Filname         - File where table is located&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Load an ACPI table from a file&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_db_load_acpi_table
id|acpi_db_load_acpi_table
(paren
id|NATIVE_CHAR
op_star
id|filename
)paren
(brace
macro_line|#ifdef ACPI_APPLICATION
id|FILE
op_star
id|fp
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|u32
id|table_length
suffix:semicolon
multiline_comment|/* Open the file */
id|fp
op_assign
id|fopen
(paren
id|filename
comma
l_string|&quot;rb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Could not open file %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_return
(paren
id|AE_ERROR
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the entire file */
id|acpi_os_printf
(paren
l_string|&quot;Loading Acpi table from file %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
id|status
op_assign
id|acpi_db_load_table
(paren
id|fp
comma
op_amp
id|acpi_gbl_db_table_ptr
comma
op_amp
id|table_length
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
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
id|acpi_os_printf
(paren
l_string|&quot;Couldn&squot;t get table from the file&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Attempt to recognize and install the table */
id|status
op_assign
id|ae_local_load_table
(paren
id|acpi_gbl_db_table_ptr
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_ALREADY_EXISTS
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;Table %4.4s is already installed&bslash;n&quot;
comma
op_amp
id|acpi_gbl_db_table_ptr-&gt;signature
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_printf
(paren
l_string|&quot;Could not install table, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;%4.4s at %p successfully installed and loaded&bslash;n&quot;
comma
op_amp
id|acpi_gbl_db_table_ptr-&gt;signature
comma
id|acpi_gbl_db_table_ptr
)paren
suffix:semicolon
id|acpi_gbl_acpi_hardware_present
op_assign
id|FALSE
suffix:semicolon
macro_line|#endif  /* ACPI_APPLICATION */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#endif  /* ENABLE_DEBUGGER */
eof
