multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rscreate - Create resource lists/tables&n; *              $Revision: 53 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acresrc.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rscreate&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_create_resource_list&n; *&n; * PARAMETERS:  Byte_stream_buffer      - Pointer to the resource byte stream&n; *              Output_buffer           - Pointer to the user&squot;s buffer&n; *              Output_buffer_length    - Pointer to the size of Output_buffer&n; *&n; * RETURN:      Status  - AE_OK if okay, else a valid acpi_status code&n; *              If Output_buffer is not large enough, Output_buffer_length&n; *              indicates how large Output_buffer should be, else it&n; *              indicates how may u8 elements of Output_buffer are valid.&n; *&n; * DESCRIPTION: Takes the byte stream returned from a _CRS, _PRS control method&n; *              execution and parses the stream to create a linked list&n; *              of device resources.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_create_resource_list
id|acpi_rs_create_resource_list
(paren
id|acpi_operand_object
op_star
id|byte_stream_buffer
comma
id|acpi_buffer
op_star
id|output_buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u8
op_star
id|byte_stream_start
suffix:semicolon
id|ACPI_SIZE
id|list_size_needed
op_assign
l_int|0
suffix:semicolon
id|u32
id|byte_stream_buffer_length
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Rs_create_resource_list&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Byte_stream_buffer = %p&bslash;n&quot;
comma
id|byte_stream_buffer
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Params already validated, so we don&squot;t re-validate here&n;&t; */
id|byte_stream_buffer_length
op_assign
id|byte_stream_buffer-&gt;buffer.length
suffix:semicolon
id|byte_stream_start
op_assign
id|byte_stream_buffer-&gt;buffer.pointer
suffix:semicolon
multiline_comment|/*&n;&t; * Pass the Byte_stream_buffer into a module that can calculate&n;&t; * the buffer size needed for the linked list&n;&t; */
id|status
op_assign
id|acpi_rs_calculate_list_length
(paren
id|byte_stream_start
comma
id|byte_stream_buffer_length
comma
op_amp
id|list_size_needed
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Status=%X List_size_needed=%X&bslash;n&quot;
comma
id|status
comma
id|list_size_needed
)paren
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
multiline_comment|/* Validate/Allocate/Clear caller buffer */
id|status
op_assign
id|acpi_ut_initialize_buffer
(paren
id|output_buffer
comma
id|list_size_needed
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
multiline_comment|/* Do the conversion */
id|status
op_assign
id|acpi_rs_byte_stream_to_list
(paren
id|byte_stream_start
comma
id|byte_stream_buffer_length
comma
id|output_buffer-&gt;pointer
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Output_buffer %p Length %X&bslash;n&quot;
comma
id|output_buffer-&gt;pointer
comma
id|output_buffer-&gt;length
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_create_pci_routing_table&n; *&n; * PARAMETERS:  Package_object          - Pointer to an acpi_operand_object&n; *                                        package&n; *              Output_buffer           - Pointer to the user&squot;s buffer&n; *              Output_buffer_length    - Size of Output_buffer&n; *&n; * RETURN:      Status  AE_OK if okay, else a valid acpi_status code.&n; *              If the Output_buffer is too small, the error will be&n; *              AE_BUFFER_OVERFLOW and Output_buffer-&gt;Length will point&n; *              to the size buffer needed.&n; *&n; * DESCRIPTION: Takes the acpi_operand_object  package and creates a&n; *              linked list of PCI interrupt descriptions&n; *&n; * NOTE: It is the caller&squot;s responsibility to ensure that the start of the&n; * output buffer is aligned properly (if necessary).&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_create_pci_routing_table
id|acpi_rs_create_pci_routing_table
(paren
id|acpi_operand_object
op_star
id|package_object
comma
id|acpi_buffer
op_star
id|output_buffer
)paren
(brace
id|u8
op_star
id|buffer
suffix:semicolon
id|acpi_operand_object
op_star
op_star
id|top_object_list
op_assign
l_int|NULL
suffix:semicolon
id|acpi_operand_object
op_star
op_star
id|sub_object_list
op_assign
l_int|NULL
suffix:semicolon
id|acpi_operand_object
op_star
id|package_element
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_SIZE
id|buffer_size_needed
op_assign
l_int|0
suffix:semicolon
id|u32
id|number_of_elements
op_assign
l_int|0
suffix:semicolon
id|u32
id|index
op_assign
l_int|0
suffix:semicolon
id|acpi_pci_routing_table
op_star
id|user_prt
op_assign
l_int|NULL
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_buffer
id|path_buffer
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Rs_create_pci_routing_table&quot;
)paren
suffix:semicolon
multiline_comment|/* Params already validated, so we don&squot;t re-validate here */
multiline_comment|/*&n;&t; * Get the required buffer length&n;&t; */
id|status
op_assign
id|acpi_rs_calculate_pci_routing_table_length
(paren
id|package_object
comma
op_amp
id|buffer_size_needed
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Buffer_size_needed = %X&bslash;n&quot;
comma
id|buffer_size_needed
)paren
)paren
suffix:semicolon
multiline_comment|/* Validate/Allocate/Clear caller buffer */
id|status
op_assign
id|acpi_ut_initialize_buffer
(paren
id|output_buffer
comma
id|buffer_size_needed
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
multiline_comment|/*&n;&t; * Loop through the ACPI_INTERNAL_OBJECTS - Each object should contain an&n;&t; * acpi_integer Address, a u8 Pin, a Name and a u8 Source_index.&n;&t; */
id|top_object_list
op_assign
id|package_object-&gt;package.elements
suffix:semicolon
id|number_of_elements
op_assign
id|package_object-&gt;package.count
suffix:semicolon
id|buffer
op_assign
id|output_buffer-&gt;pointer
suffix:semicolon
id|user_prt
op_assign
(paren
id|acpi_pci_routing_table
op_star
)paren
id|buffer
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|number_of_elements
suffix:semicolon
id|index
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; * Point User_prt past this current structure&n;&t;&t; *&n;&t;&t; * NOTE: On the first iteration, User_prt-&gt;Length will&n;&t;&t; * be zero because we cleared the return buffer earlier&n;&t;&t; */
id|buffer
op_add_assign
id|user_prt-&gt;length
suffix:semicolon
id|user_prt
op_assign
(paren
id|acpi_pci_routing_table
op_star
)paren
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Fill in the Length field with the information we have at this point.&n;&t;&t; * The minus four is to subtract the size of the u8 Source[4] member&n;&t;&t; * because it is added below.&n;&t;&t; */
id|user_prt-&gt;length
op_assign
(paren
r_sizeof
(paren
id|acpi_pci_routing_table
)paren
op_minus
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Dereference the sub-package&n;&t;&t; */
id|package_element
op_assign
op_star
id|top_object_list
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The Sub_object_list will now point to an array of the four IRQ&n;&t;&t; * elements: Address, Pin, Source and Source_index&n;&t;&t; */
id|sub_object_list
op_assign
id|package_element-&gt;package.elements
suffix:semicolon
multiline_comment|/*&n;&t;&t; * 1) First subobject:  Dereference the Address&n;&t;&t; */
r_if
c_cond
(paren
id|ACPI_TYPE_INTEGER
op_eq
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
(brace
id|user_prt-&gt;address
op_assign
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|integer.value
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Need Integer, found %s&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * 2) Second subobject: Dereference the Pin&n;&t;&t; */
id|sub_object_list
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_TYPE_INTEGER
op_eq
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
(brace
id|user_prt-&gt;pin
op_assign
(paren
id|u32
)paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|integer.value
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Need Integer, found %s&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * 3) Third subobject: Dereference the Source Name&n;&t;&t; */
id|sub_object_list
op_increment
suffix:semicolon
r_switch
c_cond
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
(brace
r_case
id|INTERNAL_TYPE_REFERENCE
suffix:colon
r_if
c_cond
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|reference.opcode
op_ne
id|AML_INT_NAMEPATH_OP
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Need name, found reference op %X&bslash;n&quot;
comma
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|reference.opcode
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
id|node
op_assign
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|reference.node
suffix:semicolon
multiline_comment|/* Use *remaining* length of the buffer as max for pathname */
id|path_buffer.length
op_assign
id|output_buffer-&gt;length
op_minus
(paren
id|u32
)paren
(paren
(paren
id|u8
op_star
)paren
id|user_prt-&gt;source
op_minus
(paren
id|u8
op_star
)paren
id|output_buffer-&gt;pointer
)paren
suffix:semicolon
id|path_buffer.pointer
op_assign
id|user_prt-&gt;source
suffix:semicolon
id|status
op_assign
id|acpi_ns_handle_to_pathname
(paren
(paren
id|acpi_handle
op_star
)paren
id|node
comma
op_amp
id|path_buffer
)paren
suffix:semicolon
id|user_prt-&gt;length
op_add_assign
id|ACPI_STRLEN
(paren
id|user_prt-&gt;source
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* include null terminator */
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|ACPI_STRCPY
(paren
id|user_prt-&gt;source
comma
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|string.pointer
)paren
suffix:semicolon
multiline_comment|/* Add to the Length field the length of the string */
id|user_prt-&gt;length
op_add_assign
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|string.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * If this is a number, then the Source Name is NULL, since the&n;&t;&t;&t; * entire buffer was zeroed out, we can leave this alone.&n;&t;&t;&t; *&n;&t;&t;&t; * Add to the Length field the length of the u32 NULL&n;&t;&t;&t; */
id|user_prt-&gt;length
op_add_assign
r_sizeof
(paren
id|u32
)paren
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
l_string|&quot;Need Integer, found %s&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/* Now align the current length */
id|user_prt-&gt;length
op_assign
id|ACPI_ROUND_UP_TO_64_bITS
(paren
id|user_prt-&gt;length
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * 4) Fourth subobject: Dereference the Source Index&n;&t;&t; */
id|sub_object_list
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_TYPE_INTEGER
op_eq
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
(brace
id|user_prt-&gt;source_index
op_assign
(paren
id|u32
)paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|integer.value
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Need Integer, found %s&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|common.type
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/* Point to the next acpi_operand_object */
id|top_object_list
op_increment
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Output_buffer %p Length %X&bslash;n&quot;
comma
id|output_buffer-&gt;pointer
comma
id|output_buffer-&gt;length
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_create_byte_stream&n; *&n; * PARAMETERS:  Linked_list_buffer      - Pointer to the resource linked list&n; *              Output_buffer           - Pointer to the user&squot;s buffer&n; *&n; * RETURN:      Status  AE_OK if okay, else a valid acpi_status code.&n; *              If the Output_buffer is too small, the error will be&n; *              AE_BUFFER_OVERFLOW and Output_buffer-&gt;Length will point&n; *              to the size buffer needed.&n; *&n; * DESCRIPTION: Takes the linked list of device resources and&n; *              creates a bytestream to be used as input for the&n; *              _SRS control method.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_create_byte_stream
id|acpi_rs_create_byte_stream
(paren
id|acpi_resource
op_star
id|linked_list_buffer
comma
id|acpi_buffer
op_star
id|output_buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_SIZE
id|byte_stream_size_needed
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Rs_create_byte_stream&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Linked_list_buffer = %p&bslash;n&quot;
comma
id|linked_list_buffer
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Params already validated, so we don&squot;t re-validate here&n;&t; *&n;&t; * Pass the Linked_list_buffer into a module that calculates&n;&t; * the buffer size needed for the byte stream.&n;&t; */
id|status
op_assign
id|acpi_rs_calculate_byte_stream_length
(paren
id|linked_list_buffer
comma
op_amp
id|byte_stream_size_needed
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Byte_stream_size_needed=%X, %s&bslash;n&quot;
comma
id|byte_stream_size_needed
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
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
multiline_comment|/* Validate/Allocate/Clear caller buffer */
id|status
op_assign
id|acpi_ut_initialize_buffer
(paren
id|output_buffer
comma
id|byte_stream_size_needed
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
multiline_comment|/* Do the conversion */
id|status
op_assign
id|acpi_rs_list_to_byte_stream
(paren
id|linked_list_buffer
comma
id|byte_stream_size_needed
comma
id|output_buffer-&gt;pointer
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Output_buffer %p Length %X&bslash;n&quot;
comma
id|output_buffer-&gt;pointer
comma
id|output_buffer-&gt;length
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
