multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nsnames - Name manipulation and search&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsnames&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_build_external_path&n; *&n; * PARAMETERS:  Node            - NS node whose pathname is needed&n; *              Size            - Size of the pathname&n; *              *name_buffer    - Where to return the pathname&n; *&n; * RETURN:      Places the pathname into the name_buffer, in external format&n; *              (name segments separated by path separators)&n; *&n; * DESCRIPTION: Generate a full pathaname&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_build_external_path
id|acpi_ns_build_external_path
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_size
id|size
comma
r_char
op_star
id|name_buffer
)paren
(brace
id|acpi_size
id|index
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|parent_node
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ns_build_external_path&quot;
)paren
suffix:semicolon
multiline_comment|/* Special case for root */
id|index
op_assign
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
id|ACPI_NAME_SIZE
)paren
(brace
id|name_buffer
(braket
l_int|0
)braket
op_assign
id|AML_ROOT_PREFIX
suffix:semicolon
id|name_buffer
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Store terminator byte, then build name backwards */
id|parent_node
op_assign
id|node
suffix:semicolon
id|name_buffer
(braket
id|index
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|index
OG
id|ACPI_NAME_SIZE
)paren
op_logical_and
(paren
id|parent_node
op_ne
id|acpi_gbl_root_node
)paren
)paren
(brace
id|index
op_sub_assign
id|ACPI_NAME_SIZE
suffix:semicolon
multiline_comment|/* Put the name into the buffer */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
(paren
id|name_buffer
op_plus
id|index
)paren
comma
op_amp
id|parent_node-&gt;name
)paren
suffix:semicolon
id|parent_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|parent_node
)paren
suffix:semicolon
multiline_comment|/* Prefix name with the path separator */
id|index
op_decrement
suffix:semicolon
id|name_buffer
(braket
id|index
)braket
op_assign
id|ACPI_PATH_SEPARATOR
suffix:semicolon
)brace
multiline_comment|/* Overwrite final separator with the root prefix character */
id|name_buffer
(braket
id|index
)braket
op_assign
id|AML_ROOT_PREFIX
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ne
l_int|0
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not construct pathname; index=%X, size=%X, Path=%s&bslash;n&quot;
comma
(paren
id|u32
)paren
id|index
comma
(paren
id|u32
)paren
id|size
comma
op_amp
id|name_buffer
(braket
id|size
)braket
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
macro_line|#ifdef ACPI_DEBUG_OUTPUT
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_get_external_pathname&n; *&n; * PARAMETERS:  Node            - NS node whose pathname is needed&n; *&n; * RETURN:      Pointer to storage containing the fully qualified name of&n; *              the node, In external format (name segments separated by path&n; *              separators.)&n; *&n; * DESCRIPTION: Used for debug printing in acpi_ns_search_table().&n; *&n; ******************************************************************************/
r_char
op_star
DECL|function|acpi_ns_get_external_pathname
id|acpi_ns_get_external_pathname
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
r_char
op_star
id|name_buffer
suffix:semicolon
id|acpi_size
id|size
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ns_get_external_pathname&quot;
comma
id|node
)paren
suffix:semicolon
multiline_comment|/* Calculate required buffer size based on depth below root */
id|size
op_assign
id|acpi_ns_get_pathname_length
(paren
id|node
)paren
suffix:semicolon
multiline_comment|/* Allocate a buffer to be returned to caller */
id|name_buffer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_buffer
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ns_get_table_pathname: allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Build the path in the allocated buffer */
id|acpi_ns_build_external_path
(paren
id|node
comma
id|size
comma
id|name_buffer
)paren
suffix:semicolon
id|return_PTR
(paren
id|name_buffer
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_get_pathname_length&n; *&n; * PARAMETERS:  Node        - Namespace node&n; *&n; * RETURN:      Length of path, including prefix&n; *&n; * DESCRIPTION: Get the length of the pathname string for this node&n; *&n; ******************************************************************************/
id|acpi_size
DECL|function|acpi_ns_get_pathname_length
id|acpi_ns_get_pathname_length
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
id|acpi_size
id|size
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|next_node
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Compute length of pathname as 5 * number of name segments.&n;&t; * Go back up the parent tree to the root&n;&t; */
id|size
op_assign
l_int|0
suffix:semicolon
id|next_node
op_assign
id|node
suffix:semicolon
r_while
c_loop
(paren
id|next_node
op_logical_and
(paren
id|next_node
op_ne
id|acpi_gbl_root_node
)paren
)paren
(brace
id|size
op_add_assign
id|ACPI_PATH_SEGMENT_LENGTH
suffix:semicolon
id|next_node
op_assign
id|acpi_ns_get_parent_node
(paren
id|next_node
)paren
suffix:semicolon
)brace
r_return
(paren
id|size
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ns_handle_to_pathname&n; *&n; * PARAMETERS:  target_handle           - Handle of named object whose name is&n; *                                        to be found&n; *              Buffer                  - Where the pathname is returned&n; *&n; * RETURN:      Status, Buffer is filled with pathname if status is AE_OK&n; *&n; * DESCRIPTION: Build and return a full namespace pathname&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_handle_to_pathname
id|acpi_ns_handle_to_pathname
(paren
id|acpi_handle
id|target_handle
comma
r_struct
id|acpi_buffer
op_star
id|buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_size
id|required_size
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ns_handle_to_pathname&quot;
comma
id|target_handle
)paren
suffix:semicolon
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|target_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Determine size required for the caller buffer */
id|required_size
op_assign
id|acpi_ns_get_pathname_length
(paren
id|node
)paren
suffix:semicolon
multiline_comment|/* Validate/Allocate/Clear caller buffer */
id|status
op_assign
id|acpi_ut_initialize_buffer
(paren
id|buffer
comma
id|required_size
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
multiline_comment|/* Build the path in the caller buffer */
id|acpi_ns_build_external_path
(paren
id|node
comma
id|required_size
comma
id|buffer-&gt;pointer
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;%s [%X] &bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|buffer-&gt;pointer
comma
(paren
id|u32
)paren
id|required_size
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
