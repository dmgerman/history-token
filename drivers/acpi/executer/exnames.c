multiline_comment|/******************************************************************************&n; *&n; * Module Name: exnames - interpreter/scanner name load/execute&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exnames&quot;
)paren
multiline_comment|/* AML Package Length encodings */
DECL|macro|ACPI_AML_PACKAGE_TYPE1
mdefine_line|#define ACPI_AML_PACKAGE_TYPE1   0x40
DECL|macro|ACPI_AML_PACKAGE_TYPE2
mdefine_line|#define ACPI_AML_PACKAGE_TYPE2   0x4000
DECL|macro|ACPI_AML_PACKAGE_TYPE3
mdefine_line|#define ACPI_AML_PACKAGE_TYPE3   0x400000
DECL|macro|ACPI_AML_PACKAGE_TYPE4
mdefine_line|#define ACPI_AML_PACKAGE_TYPE4   0x40000000
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_allocate_name_string&n; *&n; * PARAMETERS:  prefix_count        - Count of parent levels. Special cases:&n; *                                    (-1) = root,  0 = none&n; *              num_name_segs       - count of 4-character name segments&n; *&n; * RETURN:      A pointer to the allocated string segment.  This segment must&n; *              be deleted by the caller.&n; *&n; * DESCRIPTION: Allocate a buffer for a name string. Ensure allocated name&n; *              string is long enough, and set up prefix if any.&n; *&n; ******************************************************************************/
r_char
op_star
DECL|function|acpi_ex_allocate_name_string
id|acpi_ex_allocate_name_string
(paren
id|u32
id|prefix_count
comma
id|u32
id|num_name_segs
)paren
(brace
r_char
op_star
id|temp_ptr
suffix:semicolon
r_char
op_star
id|name_string
suffix:semicolon
id|u32
id|size_needed
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_allocate_name_string&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allow room for all &bslash; and ^ prefixes, all segments, and a multi_name_prefix.&n;&t; * Also, one byte for the null terminator.&n;&t; * This may actually be somewhat longer than needed.&n;&t; */
r_if
c_cond
(paren
id|prefix_count
op_eq
id|ACPI_UINT32_MAX
)paren
(brace
multiline_comment|/* Special case for root */
id|size_needed
op_assign
l_int|1
op_plus
(paren
id|ACPI_NAME_SIZE
op_star
id|num_name_segs
)paren
op_plus
l_int|2
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|size_needed
op_assign
id|prefix_count
op_plus
(paren
id|ACPI_NAME_SIZE
op_star
id|num_name_segs
)paren
op_plus
l_int|2
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate a buffer for the name.&n;&t; * This buffer must be deleted by the caller!&n;&t; */
id|name_string
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|size_needed
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_string
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ex_allocate_name_string: Could not allocate size %d&bslash;n&quot;
comma
id|size_needed
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|temp_ptr
op_assign
id|name_string
suffix:semicolon
multiline_comment|/* Set up Root or Parent prefixes if needed */
r_if
c_cond
(paren
id|prefix_count
op_eq
id|ACPI_UINT32_MAX
)paren
(brace
op_star
id|temp_ptr
op_increment
op_assign
id|AML_ROOT_PREFIX
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|prefix_count
op_decrement
)paren
(brace
op_star
id|temp_ptr
op_increment
op_assign
id|AML_PARENT_PREFIX
suffix:semicolon
)brace
)brace
multiline_comment|/* Set up Dual or Multi prefixes if needed */
r_if
c_cond
(paren
id|num_name_segs
OG
l_int|2
)paren
(brace
multiline_comment|/* Set up multi prefixes   */
op_star
id|temp_ptr
op_increment
op_assign
id|AML_MULTI_NAME_PREFIX_OP
suffix:semicolon
op_star
id|temp_ptr
op_increment
op_assign
(paren
r_char
)paren
id|num_name_segs
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
l_int|2
op_eq
id|num_name_segs
)paren
(brace
multiline_comment|/* Set up dual prefixes */
op_star
id|temp_ptr
op_increment
op_assign
id|AML_DUAL_NAME_PREFIX
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Terminate string following prefixes. acpi_ex_name_segment() will&n;&t; * append the segment(s)&n;&t; */
op_star
id|temp_ptr
op_assign
l_int|0
suffix:semicolon
id|return_PTR
(paren
id|name_string
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_name_segment&n; *&n; * PARAMETERS:  interpreter_mode    - Current running mode (load1/Load2/Exec)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a name segment (4 bytes)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_name_segment
id|acpi_ex_name_segment
(paren
id|u8
op_star
op_star
id|in_aml_address
comma
r_char
op_star
id|name_string
)paren
(brace
r_char
op_star
id|aml_address
op_assign
(paren
r_void
op_star
)paren
op_star
id|in_aml_address
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|index
suffix:semicolon
r_char
id|char_buf
(braket
l_int|5
)braket
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_name_segment&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If first character is a digit, then we know that we aren&squot;t looking at a&n;&t; * valid name segment&n;&t; */
id|char_buf
(braket
l_int|0
)braket
op_assign
op_star
id|aml_address
suffix:semicolon
r_if
c_cond
(paren
l_char|&squot;0&squot;
op_le
id|char_buf
(braket
l_int|0
)braket
op_logical_and
id|char_buf
(braket
l_int|0
)braket
op_le
l_char|&squot;9&squot;
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;leading digit: %c&bslash;n&quot;
comma
id|char_buf
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_CTRL_PENDING
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_LOAD
comma
l_string|&quot;Bytes from stream:&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
(paren
id|index
OL
id|ACPI_NAME_SIZE
)paren
op_logical_and
(paren
id|acpi_ut_valid_acpi_character
(paren
op_star
id|aml_address
)paren
)paren
suffix:semicolon
id|index
op_increment
)paren
(brace
id|char_buf
(braket
id|index
)braket
op_assign
op_star
id|aml_address
op_increment
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_LOAD
comma
l_string|&quot;%c&bslash;n&quot;
comma
id|char_buf
(braket
id|index
)braket
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Valid name segment  */
r_if
c_cond
(paren
id|index
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Found 4 valid characters */
id|char_buf
(braket
l_int|4
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|name_string
)paren
(brace
id|ACPI_STRCAT
(paren
id|name_string
comma
id|char_buf
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;Appended to - %s &bslash;n&quot;
comma
id|name_string
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_NAMES
comma
l_string|&quot;No Name string - %s &bslash;n&quot;
comma
id|char_buf
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * First character was not a valid name character,&n;&t;&t; * so we are looking at something other than a name.&n;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Leading character is not alpha: %02Xh (not a name)&bslash;n&quot;
comma
id|char_buf
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_CTRL_PENDING
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Segment started with one or more valid characters, but fewer than 4 */
id|status
op_assign
id|AE_AML_BAD_NAME
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Bad character %02x in name, at %p&bslash;n&quot;
comma
op_star
id|aml_address
comma
id|aml_address
)paren
)paren
suffix:semicolon
)brace
op_star
id|in_aml_address
op_assign
(paren
id|u8
op_star
)paren
id|aml_address
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_get_name_string&n; *&n; * PARAMETERS:  data_type           - Data type to be associated with this name&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get a name, including any prefixes.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_get_name_string
id|acpi_ex_get_name_string
(paren
id|acpi_object_type
id|data_type
comma
id|u8
op_star
id|in_aml_address
comma
r_char
op_star
op_star
id|out_name_string
comma
id|u32
op_star
id|out_name_length
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u8
op_star
id|aml_address
op_assign
id|in_aml_address
suffix:semicolon
r_char
op_star
id|name_string
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|num_segments
suffix:semicolon
id|u32
id|prefix_count
op_assign
l_int|0
suffix:semicolon
id|u8
id|has_prefix
op_assign
id|FALSE
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_get_name_string&quot;
comma
id|aml_address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_TYPE_LOCAL_REGION_FIELD
op_eq
id|data_type
op_logical_or
id|ACPI_TYPE_LOCAL_BANK_FIELD
op_eq
id|data_type
op_logical_or
id|ACPI_TYPE_LOCAL_INDEX_FIELD
op_eq
id|data_type
)paren
(brace
multiline_comment|/* Disallow prefixes for types associated with field_unit names */
id|name_string
op_assign
id|acpi_ex_allocate_name_string
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_string
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|acpi_ex_name_segment
(paren
op_amp
id|aml_address
comma
id|name_string
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * data_type is not a field name.&n;&t;&t; * Examine first character of name for root or parent prefix operators&n;&t;&t; */
r_switch
c_cond
(paren
op_star
id|aml_address
)paren
(brace
r_case
id|AML_ROOT_PREFIX
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_LOAD
comma
l_string|&quot;root_prefix(&bslash;&bslash;) at %p&bslash;n&quot;
comma
id|aml_address
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Remember that we have a root_prefix --&n;&t;&t;&t; * see comment in acpi_ex_allocate_name_string()&n;&t;&t;&t; */
id|aml_address
op_increment
suffix:semicolon
id|prefix_count
op_assign
id|ACPI_UINT32_MAX
suffix:semicolon
id|has_prefix
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_PARENT_PREFIX
suffix:colon
multiline_comment|/* Increment past possibly multiple parent prefixes */
r_do
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_LOAD
comma
l_string|&quot;parent_prefix (^) at %p&bslash;n&quot;
comma
id|aml_address
)paren
)paren
suffix:semicolon
id|aml_address
op_increment
suffix:semicolon
id|prefix_count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|aml_address
op_eq
id|AML_PARENT_PREFIX
)paren
suffix:semicolon
id|has_prefix
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Not a prefix character */
r_break
suffix:semicolon
)brace
multiline_comment|/* Examine first character of name for name segment prefix operator */
r_switch
c_cond
(paren
op_star
id|aml_address
)paren
(brace
r_case
id|AML_DUAL_NAME_PREFIX
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_LOAD
comma
l_string|&quot;dual_name_prefix at %p&bslash;n&quot;
comma
id|aml_address
)paren
)paren
suffix:semicolon
id|aml_address
op_increment
suffix:semicolon
id|name_string
op_assign
id|acpi_ex_allocate_name_string
(paren
id|prefix_count
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_string
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Indicate that we processed a prefix */
id|has_prefix
op_assign
id|TRUE
suffix:semicolon
id|status
op_assign
id|acpi_ex_name_segment
(paren
op_amp
id|aml_address
comma
id|name_string
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
id|status
op_assign
id|acpi_ex_name_segment
(paren
op_amp
id|aml_address
comma
id|name_string
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_MULTI_NAME_PREFIX_OP
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_LOAD
comma
l_string|&quot;multi_name_prefix at %p&bslash;n&quot;
comma
id|aml_address
)paren
)paren
suffix:semicolon
multiline_comment|/* Fetch count of segments remaining in name path */
id|aml_address
op_increment
suffix:semicolon
id|num_segments
op_assign
op_star
id|aml_address
suffix:semicolon
id|name_string
op_assign
id|acpi_ex_allocate_name_string
(paren
id|prefix_count
comma
id|num_segments
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_string
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Indicate that we processed a prefix */
id|aml_address
op_increment
suffix:semicolon
id|has_prefix
op_assign
id|TRUE
suffix:semicolon
r_while
c_loop
(paren
id|num_segments
op_logical_and
(paren
id|status
op_assign
id|acpi_ex_name_segment
(paren
op_amp
id|aml_address
comma
id|name_string
)paren
)paren
op_eq
id|AE_OK
)paren
(brace
id|num_segments
op_decrement
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* null_name valid as of 8-12-98 ASL/AML Grammar Update */
r_if
c_cond
(paren
id|prefix_count
op_eq
id|ACPI_UINT32_MAX
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;name_seg is &bslash;&quot;&bslash;&bslash;&bslash;&quot; followed by NULL&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Consume the NULL byte */
id|aml_address
op_increment
suffix:semicolon
id|name_string
op_assign
id|acpi_ex_allocate_name_string
(paren
id|prefix_count
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_string
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Name segment string */
id|name_string
op_assign
id|acpi_ex_allocate_name_string
(paren
id|prefix_count
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_string
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_break
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ex_name_segment
(paren
op_amp
id|aml_address
comma
id|name_string
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|AE_CTRL_PENDING
op_eq
id|status
op_logical_and
id|has_prefix
)paren
(brace
multiline_comment|/* Ran out of segments after processing a prefix */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ex_do_name: Malformed Name at %p&bslash;n&quot;
comma
id|name_string
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_BAD_NAME
suffix:semicolon
)brace
op_star
id|out_name_string
op_assign
id|name_string
suffix:semicolon
op_star
id|out_name_length
op_assign
(paren
id|u32
)paren
(paren
id|aml_address
op_minus
id|in_aml_address
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
