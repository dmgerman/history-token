multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rsmem24 - Memory resource descriptors&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acresrc.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rsmemory&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_memory24_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_memory24_resource
id|acpi_rs_memory24_resource
(paren
id|u8
op_star
id|byte_stream_buffer
comma
id|acpi_size
op_star
id|bytes_consumed
comma
id|u8
op_star
op_star
id|output_buffer
comma
id|acpi_size
op_star
id|structure_size
)paren
(brace
id|u8
op_star
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
r_struct
id|acpi_resource
op_star
id|output_struct
op_assign
(paren
r_void
op_star
)paren
op_star
id|output_buffer
suffix:semicolon
id|u16
id|temp16
op_assign
l_int|0
suffix:semicolon
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|acpi_size
id|struct_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_mem24
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_memory24_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Point past the Descriptor to get the number of bytes consumed&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
op_star
id|bytes_consumed
op_assign
(paren
id|acpi_size
)paren
id|temp16
op_plus
l_int|3
suffix:semicolon
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_MEM24
suffix:semicolon
multiline_comment|/*&n;&t; * Check Byte 3 the Read/Write bit&n;&t; */
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|output_struct-&gt;data.memory24.read_write_attribute
op_assign
id|temp8
op_amp
l_int|0x01
suffix:semicolon
multiline_comment|/*&n;&t; * Get min_base_address (Bytes 4-5)&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
id|output_struct-&gt;data.memory24.min_base_address
op_assign
id|temp16
suffix:semicolon
multiline_comment|/*&n;&t; * Get max_base_address (Bytes 6-7)&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
id|output_struct-&gt;data.memory24.max_base_address
op_assign
id|temp16
suffix:semicolon
multiline_comment|/*&n;&t; * Get Alignment (Bytes 8-9)&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
id|output_struct-&gt;data.memory24.alignment
op_assign
id|temp16
suffix:semicolon
multiline_comment|/*&n;&t; * Get range_length (Bytes 10-11)&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|output_struct-&gt;data.memory24.range_length
op_assign
id|temp16
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Length parameter&n;&t; */
id|output_struct-&gt;length
op_assign
(paren
id|u32
)paren
id|struct_size
suffix:semicolon
multiline_comment|/*&n;&t; * Return the final size of the structure&n;&t; */
op_star
id|structure_size
op_assign
id|struct_size
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_memory24_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_memory24_stream
id|acpi_rs_memory24_stream
(paren
r_struct
id|acpi_resource
op_star
id|linked_list
comma
id|u8
op_star
op_star
id|output_buffer
comma
id|acpi_size
op_star
id|bytes_consumed
)paren
(brace
id|u8
op_star
id|buffer
op_assign
op_star
id|output_buffer
suffix:semicolon
id|u16
id|temp16
op_assign
l_int|0
suffix:semicolon
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_memory24_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x81
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * The length field is static&n;&t; */
id|temp16
op_assign
l_int|0x09
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
id|buffer
comma
op_amp
id|temp16
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Information Byte&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|linked_list-&gt;data.memory24.read_write_attribute
op_amp
l_int|0x01
)paren
suffix:semicolon
op_star
id|buffer
op_assign
id|temp8
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Range minimum base address&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory24.min_base_address
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Range maximum base address&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory24.max_base_address
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Set the base alignment&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory24.alignment
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Set the range length&n;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory24.range_length
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Return the number of bytes consumed in this operation&n;&t; */
op_star
id|bytes_consumed
op_assign
id|ACPI_PTR_DIFF
(paren
id|buffer
comma
op_star
id|output_buffer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_memory32_range_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_memory32_range_resource
id|acpi_rs_memory32_range_resource
(paren
id|u8
op_star
id|byte_stream_buffer
comma
id|acpi_size
op_star
id|bytes_consumed
comma
id|u8
op_star
op_star
id|output_buffer
comma
id|acpi_size
op_star
id|structure_size
)paren
(brace
id|u8
op_star
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
r_struct
id|acpi_resource
op_star
id|output_struct
op_assign
(paren
r_void
op_star
)paren
op_star
id|output_buffer
suffix:semicolon
id|u16
id|temp16
op_assign
l_int|0
suffix:semicolon
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|acpi_size
id|struct_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_mem32
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_memory32_range_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Point past the Descriptor to get the number of bytes consumed&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
op_star
id|bytes_consumed
op_assign
(paren
id|acpi_size
)paren
id|temp16
op_plus
l_int|3
suffix:semicolon
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_MEM32
suffix:semicolon
multiline_comment|/*&n;&t; *  Point to the place in the output buffer where the data portion will&n;&t; *  begin.&n;&t; *  1. Set the RESOURCE_DATA * Data to point to it&squot;s own address, then&n;&t; *  2. Set the pointer to the next address.&n;&t; *&n;&t; *  NOTE: output_struct-&gt;Data is cast to u8, otherwise, this addition adds&n;&t; *  4 * sizeof(RESOURCE_DATA) instead of 4 * sizeof(u8)&n;&t; */
multiline_comment|/*&n;&t; * Check Byte 3 the Read/Write bit&n;&t; */
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|output_struct-&gt;data.memory32.read_write_attribute
op_assign
id|temp8
op_amp
l_int|0x01
suffix:semicolon
multiline_comment|/*&n;&t; * Get min_base_address (Bytes 4-7)&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|output_struct-&gt;data.memory32.min_base_address
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Get max_base_address (Bytes 8-11)&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|output_struct-&gt;data.memory32.max_base_address
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Get Alignment (Bytes 12-15)&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|output_struct-&gt;data.memory32.alignment
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Get range_length (Bytes 16-19)&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|output_struct-&gt;data.memory32.range_length
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Length parameter&n;&t; */
id|output_struct-&gt;length
op_assign
(paren
id|u32
)paren
id|struct_size
suffix:semicolon
multiline_comment|/*&n;&t; * Return the final size of the structure&n;&t; */
op_star
id|structure_size
op_assign
id|struct_size
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_fixed_memory32_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_fixed_memory32_resource
id|acpi_rs_fixed_memory32_resource
(paren
id|u8
op_star
id|byte_stream_buffer
comma
id|acpi_size
op_star
id|bytes_consumed
comma
id|u8
op_star
op_star
id|output_buffer
comma
id|acpi_size
op_star
id|structure_size
)paren
(brace
id|u8
op_star
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
r_struct
id|acpi_resource
op_star
id|output_struct
op_assign
(paren
r_void
op_star
)paren
op_star
id|output_buffer
suffix:semicolon
id|u16
id|temp16
op_assign
l_int|0
suffix:semicolon
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|acpi_size
id|struct_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_fixed_mem32
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_fixed_memory32_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Point past the Descriptor to get the number of bytes consumed&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
op_star
id|bytes_consumed
op_assign
(paren
id|acpi_size
)paren
id|temp16
op_plus
l_int|3
suffix:semicolon
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_FIXED_MEM32
suffix:semicolon
multiline_comment|/*&n;&t; * Check Byte 3 the Read/Write bit&n;&t; */
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|output_struct-&gt;data.fixed_memory32.read_write_attribute
op_assign
id|temp8
op_amp
l_int|0x01
suffix:semicolon
multiline_comment|/*&n;&t; * Get range_base_address (Bytes 4-7)&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|output_struct-&gt;data.fixed_memory32.range_base_address
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Get range_length (Bytes 8-11)&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|output_struct-&gt;data.fixed_memory32.range_length
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Length parameter&n;&t; */
id|output_struct-&gt;length
op_assign
(paren
id|u32
)paren
id|struct_size
suffix:semicolon
multiline_comment|/*&n;&t; * Return the final size of the structure&n;&t; */
op_star
id|structure_size
op_assign
id|struct_size
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_memory32_range_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_memory32_range_stream
id|acpi_rs_memory32_range_stream
(paren
r_struct
id|acpi_resource
op_star
id|linked_list
comma
id|u8
op_star
op_star
id|output_buffer
comma
id|acpi_size
op_star
id|bytes_consumed
)paren
(brace
id|u8
op_star
id|buffer
op_assign
op_star
id|output_buffer
suffix:semicolon
id|u16
id|temp16
op_assign
l_int|0
suffix:semicolon
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_memory32_range_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x85
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * The length field is static&n;&t; */
id|temp16
op_assign
l_int|0x11
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
id|buffer
comma
op_amp
id|temp16
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Information Byte&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|linked_list-&gt;data.memory32.read_write_attribute
op_amp
l_int|0x01
)paren
suffix:semicolon
op_star
id|buffer
op_assign
id|temp8
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Range minimum base address&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory32.min_base_address
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Range maximum base address&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory32.max_base_address
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Set the base alignment&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory32.alignment
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Set the range length&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.memory32.range_length
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Return the number of bytes consumed in this operation&n;&t; */
op_star
id|bytes_consumed
op_assign
id|ACPI_PTR_DIFF
(paren
id|buffer
comma
op_star
id|output_buffer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_fixed_memory32_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_fixed_memory32_stream
id|acpi_rs_fixed_memory32_stream
(paren
r_struct
id|acpi_resource
op_star
id|linked_list
comma
id|u8
op_star
op_star
id|output_buffer
comma
id|acpi_size
op_star
id|bytes_consumed
)paren
(brace
id|u8
op_star
id|buffer
op_assign
op_star
id|output_buffer
suffix:semicolon
id|u16
id|temp16
op_assign
l_int|0
suffix:semicolon
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_fixed_memory32_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x86
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * The length field is static&n;&t; */
id|temp16
op_assign
l_int|0x09
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
id|buffer
comma
op_amp
id|temp16
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Information Byte&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|linked_list-&gt;data.fixed_memory32.read_write_attribute
op_amp
l_int|0x01
)paren
suffix:semicolon
op_star
id|buffer
op_assign
id|temp8
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Range base address&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.fixed_memory32.range_base_address
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Set the range length&n;&t; */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
id|buffer
comma
op_amp
id|linked_list-&gt;data.fixed_memory32.range_length
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * Return the number of bytes consumed in this operation&n;&t; */
op_star
id|bytes_consumed
op_assign
id|ACPI_PTR_DIFF
(paren
id|buffer
comma
op_star
id|output_buffer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
