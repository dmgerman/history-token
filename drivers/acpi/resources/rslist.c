multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rslist - Linked list utilities&n; *              $Revision: 17 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acresrc.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|MODULE_NAME
(paren
l_string|&quot;rslist&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_get_resource_type&n; *&n; * PARAMETERS:  Resource_start_byte     - Byte 0 of a resource descriptor&n; *&n; * RETURN:      The Resource Type (Name) with no extraneous bits&n; *&n; * DESCRIPTION: Extract the Resource Type/Name from the first byte of&n; *              a resource descriptor.&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_rs_get_resource_type
id|acpi_rs_get_resource_type
(paren
id|u8
id|resource_start_byte
)paren
(brace
multiline_comment|/*&n;&t; * Determine if this is a small or large resource&n;&t; */
r_switch
c_cond
(paren
id|resource_start_byte
op_amp
id|RESOURCE_DESC_TYPE_MASK
)paren
(brace
r_case
id|RESOURCE_DESC_TYPE_SMALL
suffix:colon
multiline_comment|/*&n;&t;&t; * Small Resource Type -- Only bits 6:3 are valid&n;&t;&t; */
r_return
(paren
(paren
id|u8
)paren
(paren
id|resource_start_byte
op_amp
id|RESOURCE_DESC_SMALL_MASK
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_TYPE_LARGE
suffix:colon
multiline_comment|/*&n;&t;&t; * Large Resource Type -- All bits are valid&n;&t;&t; */
r_return
(paren
id|resource_start_byte
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
(paren
l_int|0xFF
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_byte_stream_to_list&n; *&n; * PARAMETERS:  Byte_stream_buffer      - Pointer to the resource byte stream&n; *              Byte_stream_buffer_length - Length of Byte_stream_buffer&n; *              Output_buffer           - Pointer to the buffer that will&n; *                                        contain the output structures&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Takes the resource byte stream and parses it, creating a&n; *              linked list of resources in the caller&squot;s output buffer&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_rs_byte_stream_to_list
id|acpi_rs_byte_stream_to_list
(paren
id|u8
op_star
id|byte_stream_buffer
comma
id|u32
id|byte_stream_buffer_length
comma
id|u8
op_star
op_star
id|output_buffer
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|u32
id|bytes_parsed
op_assign
l_int|0
suffix:semicolon
id|u8
id|resource_type
op_assign
l_int|0
suffix:semicolon
id|u32
id|bytes_consumed
op_assign
l_int|0
suffix:semicolon
id|u8
op_star
op_star
id|buffer
op_assign
id|output_buffer
suffix:semicolon
id|u32
id|structure_size
op_assign
l_int|0
suffix:semicolon
id|u8
id|end_tag_processed
op_assign
id|FALSE
suffix:semicolon
r_while
c_loop
(paren
id|bytes_parsed
OL
id|byte_stream_buffer_length
op_logical_and
id|FALSE
op_eq
id|end_tag_processed
)paren
(brace
multiline_comment|/*&n;&t;&t; * The next byte in the stream is the resource type&n;&t;&t; */
id|resource_type
op_assign
id|acpi_rs_get_resource_type
(paren
op_star
id|byte_stream_buffer
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|resource_type
)paren
(brace
r_case
id|RESOURCE_DESC_MEMORY_24
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 24-Bit Memory Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_memory24_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_LARGE_VENDOR
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Vendor Defined Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_vendor_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_MEMORY_32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Memory Range Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_memory32_range_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_FIXED_MEMORY_32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Fixed Memory Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_fixed_memory32_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_QWORD_ADDRESS_SPACE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 64-Bit Address Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_address64_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_DWORD_ADDRESS_SPACE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Address Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_address32_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_WORD_ADDRESS_SPACE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 16-Bit Address Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_address16_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_EXTENDED_XRUPT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Extended IRQ&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_extended_irq_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_IRQ_FORMAT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IRQ Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_irq_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_DMA_FORMAT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * DMA Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_dma_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_START_DEPENDENT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Start Dependent Functions Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_start_dependent_functions_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_END_DEPENDENT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Dependent Functions Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_end_dependent_functions_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_IO_PORT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IO Port Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_io_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_FIXED_IO_PORT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Fixed IO Port Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_fixed_io_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_SMALL_VENDOR
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Vendor Specific Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_vendor_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESOURCE_DESC_END_TAG
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Tag&n;&t;&t;&t; */
id|end_tag_processed
op_assign
id|TRUE
suffix:semicolon
id|status
op_assign
id|acpi_rs_end_tag_resource
(paren
id|byte_stream_buffer
comma
op_amp
id|bytes_consumed
comma
id|buffer
comma
op_amp
id|structure_size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Invalid/Unknowns resource type&n;&t;&t;&t; */
id|status
op_assign
id|AE_AML_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
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
multiline_comment|/*&n;&t;&t; * Update the return value and counter&n;&t;&t; */
id|bytes_parsed
op_add_assign
id|bytes_consumed
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the byte stream to point to the next resource&n;&t;&t; */
id|byte_stream_buffer
op_add_assign
id|bytes_consumed
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the Buffer to the next structure&n;&t;&t; */
op_star
id|buffer
op_add_assign
id|structure_size
suffix:semicolon
)brace
multiline_comment|/*  end while */
multiline_comment|/*&n;&t; * Check the reason for exiting the while loop&n;&t; */
r_if
c_cond
(paren
id|TRUE
op_ne
id|end_tag_processed
)paren
(brace
r_return
(paren
id|AE_AML_ERROR
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_list_to_byte_stream&n; *&n; * PARAMETERS:  Linked_list             - Pointer to the resource linked list&n; *              Byte_steam_size_needed  - Calculated size of the byte stream&n; *                                        needed from calling&n; *                                        Acpi_rs_calculate_byte_stream_length()&n; *                                        The size of the Output_buffer is&n; *                                        guaranteed to be &gt;=&n; *                                        Byte_stream_size_needed&n; *              Output_buffer           - Pointer to the buffer that will&n; *                                        contain the byte stream&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Takes the resource linked list and parses it, creating a&n; *              byte stream of resources in the caller&squot;s output buffer&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_rs_list_to_byte_stream
id|acpi_rs_list_to_byte_stream
(paren
id|ACPI_RESOURCE
op_star
id|linked_list
comma
id|u32
id|byte_stream_size_needed
comma
id|u8
op_star
op_star
id|output_buffer
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|u8
op_star
id|buffer
op_assign
op_star
id|output_buffer
suffix:semicolon
id|u32
id|bytes_consumed
op_assign
l_int|0
suffix:semicolon
id|u8
id|done
op_assign
id|FALSE
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|done
)paren
(brace
r_switch
c_cond
(paren
id|linked_list-&gt;id
)paren
(brace
r_case
id|ACPI_RSTYPE_IRQ
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IRQ Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_irq_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_DMA
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * DMA Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_dma_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_START_DPF
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Start Dependent Functions Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_start_dependent_functions_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_END_DPF
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Dependent Functions Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_end_dependent_functions_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_IO
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IO Port Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_io_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_FIXED_IO
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Fixed IO Port Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_fixed_io_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_VENDOR
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Vendor Defined Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_vendor_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_END_TAG
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Tag&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_end_tag_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * An End Tag indicates the end of the Resource Template&n;&t;&t;&t; */
id|done
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_MEM24
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 24-Bit Memory Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_memory24_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_MEM32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Memory Range Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_memory32_range_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_FIXED_MEM32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Fixed Memory Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_fixed_memory32_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS16
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 16-Bit Address Descriptor Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_address16_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Address Descriptor Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_address32_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS64
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 64-Bit Address Descriptor Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_address64_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_EXT_IRQ
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Extended IRQ Resource&n;&t;&t;&t; */
id|status
op_assign
id|acpi_rs_extended_irq_stream
(paren
id|linked_list
comma
op_amp
id|buffer
comma
op_amp
id|bytes_consumed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * If we get here, everything is out of sync,&n;&t;&t;&t; *  so exit with an error&n;&t;&t;&t; */
id|status
op_assign
id|AE_BAD_DATA
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* switch (Linked_list-&gt;Id) */
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
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
multiline_comment|/*&n;&t;&t; * Set the Buffer to point to the open byte&n;&t;&t; */
id|buffer
op_add_assign
id|bytes_consumed
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Point to the next object&n;&t;&t; */
id|linked_list
op_assign
id|POINTER_ADD
(paren
id|ACPI_RESOURCE
comma
id|linked_list
comma
id|linked_list-&gt;length
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
