multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rscalc - Calculate stream and list lengths&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acresrc.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rscalc&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_get_byte_stream_length&n; *&n; * PARAMETERS:  linked_list         - Pointer to the resource linked list&n; *              size_needed         - u32 pointer of the size buffer needed&n; *                                    to properly return the parsed data&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Takes the resource byte stream and parses it once, calculating&n; *              the size buffer needed to hold the linked list that conveys&n; *              the resource data.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_byte_stream_length
id|acpi_rs_get_byte_stream_length
(paren
r_struct
id|acpi_resource
op_star
id|linked_list
comma
id|acpi_size
op_star
id|size_needed
)paren
(brace
id|acpi_size
id|byte_stream_size_needed
op_assign
l_int|0
suffix:semicolon
id|acpi_size
id|segment_size
suffix:semicolon
r_struct
id|acpi_resource_ext_irq
op_star
id|ex_irq
op_assign
l_int|NULL
suffix:semicolon
id|u8
id|done
op_assign
id|FALSE
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_get_byte_stream_length&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|done
)paren
(brace
multiline_comment|/*&n;&t;&t; * Init the variable that will hold the size to add to the total.&n;&t;&t; */
id|segment_size
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|linked_list-&gt;id
)paren
(brace
r_case
id|ACPI_RSTYPE_IRQ
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IRQ Resource&n;&t;&t;&t; * For an IRQ Resource, Byte 3, although optional, will&n;&t;&t;&t; * always be created - it holds IRQ information.&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_DMA
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * DMA Resource&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_START_DPF
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Start Dependent Functions Resource&n;&t;&t;&t; * For a start_dependent_functions Resource, Byte 1,&n;&t;&t;&t; * although optional, will always be created.&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_END_DPF
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Dependent Functions Resource&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_IO
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IO Port Resource&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_FIXED_IO
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Fixed IO Port Resource&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_VENDOR
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Vendor Defined Resource&n;&t;&t;&t; * For a Vendor Specific resource, if the Length is&n;&t;&t;&t; * between 1 and 7 it will be created as a Small&n;&t;&t;&t; * Resource data type, otherwise it is a Large&n;&t;&t;&t; * Resource data type.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|linked_list-&gt;data.vendor_specific.length
OG
l_int|7
)paren
(brace
id|segment_size
op_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
id|segment_size
op_assign
l_int|1
suffix:semicolon
)brace
id|segment_size
op_add_assign
id|linked_list-&gt;data.vendor_specific.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_END_TAG
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Tag&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|2
suffix:semicolon
id|done
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_MEM24
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 24-Bit Memory Resource&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|12
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_MEM32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Memory Range Resource&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_FIXED_MEM32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Fixed Memory Resource&n;&t;&t;&t; * For this resource the size is static&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|12
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS16
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 16-Bit Address Resource&n;&t;&t;&t; * The base size of this byte stream is 16. If a&n;&t;&t;&t; * Resource Source string is not NULL, add 1 for&n;&t;&t;&t; * the Index + the length of the null terminated&n;&t;&t;&t; * string Resource Source + 1 for the null.&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|linked_list-&gt;data.address16.resource_source.string_ptr
)paren
(brace
id|segment_size
op_add_assign
id|linked_list-&gt;data.address16.resource_source.string_length
suffix:semicolon
id|segment_size
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Address Resource&n;&t;&t;&t; * The base size of this byte stream is 26. If a Resource&n;&t;&t;&t; * Source string is not NULL, add 1 for the Index + the&n;&t;&t;&t; * length of the null terminated string Resource Source +&n;&t;&t;&t; * 1 for the null.&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|26
suffix:semicolon
r_if
c_cond
(paren
id|linked_list-&gt;data.address32.resource_source.string_ptr
)paren
(brace
id|segment_size
op_add_assign
id|linked_list-&gt;data.address32.resource_source.string_length
suffix:semicolon
id|segment_size
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS64
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 64-Bit Address Resource&n;&t;&t;&t; * The base size of this byte stream is 46. If a Resource&n;&t;&t;&t; * Source string is not NULL, add 1 for the Index + the&n;&t;&t;&t; * length of the null terminated string Resource Source +&n;&t;&t;&t; * 1 for the null.&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|46
suffix:semicolon
r_if
c_cond
(paren
id|linked_list-&gt;data.address64.resource_source.string_ptr
)paren
(brace
id|segment_size
op_add_assign
id|linked_list-&gt;data.address64.resource_source.string_length
suffix:semicolon
id|segment_size
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_EXT_IRQ
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Extended IRQ Resource&n;&t;&t;&t; * The base size of this byte stream is 9. This is for an&n;&t;&t;&t; * Interrupt table length of 1.  For each additional&n;&t;&t;&t; * interrupt, add 4.&n;&t;&t;&t; * If a Resource Source string is not NULL, add 1 for the&n;&t;&t;&t; * Index + the length of the null terminated string&n;&t;&t;&t; * Resource Source + 1 for the null.&n;&t;&t;&t; */
id|segment_size
op_assign
l_int|9
op_plus
(paren
(paren
(paren
id|acpi_size
)paren
id|linked_list-&gt;data.extended_irq.number_of_interrupts
op_minus
l_int|1
)paren
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ex_irq
op_logical_and
id|ex_irq-&gt;resource_source.string_ptr
)paren
(brace
id|segment_size
op_add_assign
id|linked_list-&gt;data.extended_irq.resource_source.string_length
suffix:semicolon
id|segment_size
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * If we get here, everything is out of sync,&n;&t;&t;&t; * so exit with an error&n;&t;&t;&t; */
id|return_ACPI_STATUS
(paren
id|AE_AML_INVALID_RESOURCE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* switch (linked_list-&gt;Id) */
multiline_comment|/*&n;&t;&t; * Update the total&n;&t;&t; */
id|byte_stream_size_needed
op_add_assign
id|segment_size
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Point to the next object&n;&t;&t; */
id|linked_list
op_assign
id|ACPI_PTR_ADD
(paren
r_struct
id|acpi_resource
comma
id|linked_list
comma
id|linked_list-&gt;length
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This is the data the caller needs&n;&t; */
op_star
id|size_needed
op_assign
id|byte_stream_size_needed
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_get_list_length&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource byte stream&n; *              byte_stream_buffer_length - Size of byte_stream_buffer&n; *              size_needed             - u32 pointer of the size buffer&n; *                                        needed to properly return the&n; *                                        parsed data&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Takes the resource byte stream and parses it once, calculating&n; *              the size buffer needed to hold the linked list that conveys&n; *              the resource data.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_list_length
id|acpi_rs_get_list_length
(paren
id|u8
op_star
id|byte_stream_buffer
comma
id|u32
id|byte_stream_buffer_length
comma
id|acpi_size
op_star
id|size_needed
)paren
(brace
id|u32
id|buffer_size
op_assign
l_int|0
suffix:semicolon
id|u32
id|bytes_parsed
op_assign
l_int|0
suffix:semicolon
id|u8
id|number_of_interrupts
op_assign
l_int|0
suffix:semicolon
id|u8
id|number_of_channels
op_assign
l_int|0
suffix:semicolon
id|u8
id|resource_type
suffix:semicolon
id|u32
id|structure_size
suffix:semicolon
id|u32
id|bytes_consumed
suffix:semicolon
id|u8
op_star
id|buffer
suffix:semicolon
id|u8
id|temp8
suffix:semicolon
id|u16
id|temp16
suffix:semicolon
id|u8
id|index
suffix:semicolon
id|u8
id|additional_bytes
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_get_list_length&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bytes_parsed
OL
id|byte_stream_buffer_length
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
id|ACPI_RDESC_TYPE_MEMORY_24
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 24-Bit Memory Resource&n;&t;&t;&t; */
id|bytes_consumed
op_assign
l_int|12
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_mem24
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_LARGE_VENDOR
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Vendor Defined Resource&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
op_increment
id|buffer
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|bytes_consumed
op_assign
id|temp16
op_plus
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Ensure a 32-bit boundary for the structure&n;&t;&t;&t; */
id|temp16
op_assign
(paren
id|u16
)paren
id|ACPI_ROUND_UP_to_32_bITS
(paren
id|temp16
)paren
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_vendor
)paren
op_plus
(paren
id|temp16
op_star
r_sizeof
(paren
id|u8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_MEMORY_32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Memory Range Resource&n;&t;&t;&t; */
id|bytes_consumed
op_assign
l_int|20
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_mem32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_FIXED_MEMORY_32
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Fixed Memory Resource&n;&t;&t;&t; */
id|bytes_consumed
op_assign
l_int|12
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_fixed_mem32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_QWORD_ADDRESS_SPACE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 64-Bit Address Resource&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
op_increment
id|buffer
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|bytes_consumed
op_assign
id|temp16
op_plus
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Resource Source Index and Resource Source are&n;&t;&t;&t; * optional elements.  Check the length of the&n;&t;&t;&t; * Bytestream.  If it is greater than 43, that&n;&t;&t;&t; * means that an Index exists and is followed by&n;&t;&t;&t; * a null termininated string.  Therefore, set&n;&t;&t;&t; * the temp variable to the length minus the minimum&n;&t;&t;&t; * byte stream length plus the byte for the Index to&n;&t;&t;&t; * determine the size of the NULL terminiated string.&n;&t;&t;&t; */
r_if
c_cond
(paren
l_int|43
OL
id|temp16
)paren
(brace
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|temp16
op_minus
l_int|44
)paren
suffix:semicolon
)brace
r_else
(brace
id|temp8
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Ensure a 64-bit boundary for the structure&n;&t;&t;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|ACPI_ROUND_UP_to_64_bITS
(paren
id|temp8
)paren
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_address64
)paren
op_plus
(paren
id|temp8
op_star
r_sizeof
(paren
id|u8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_DWORD_ADDRESS_SPACE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 32-Bit Address Resource&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
op_increment
id|buffer
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|bytes_consumed
op_assign
id|temp16
op_plus
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Resource Source Index and Resource Source are&n;&t;&t;&t; * optional elements.  Check the length of the&n;&t;&t;&t; * Bytestream.  If it is greater than 23, that&n;&t;&t;&t; * means that an Index exists and is followed by&n;&t;&t;&t; * a null termininated string.  Therefore, set&n;&t;&t;&t; * the temp variable to the length minus the minimum&n;&t;&t;&t; * byte stream length plus the byte for the Index to&n;&t;&t;&t; * determine the size of the NULL terminiated string.&n;&t;&t;&t; */
r_if
c_cond
(paren
l_int|23
OL
id|temp16
)paren
(brace
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|temp16
op_minus
l_int|24
)paren
suffix:semicolon
)brace
r_else
(brace
id|temp8
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Ensure a 32-bit boundary for the structure&n;&t;&t;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|ACPI_ROUND_UP_to_32_bITS
(paren
id|temp8
)paren
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_address32
)paren
op_plus
(paren
id|temp8
op_star
r_sizeof
(paren
id|u8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_WORD_ADDRESS_SPACE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 16-Bit Address Resource&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
op_increment
id|buffer
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|bytes_consumed
op_assign
id|temp16
op_plus
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Resource Source Index and Resource Source are&n;&t;&t;&t; * optional elements.  Check the length of the&n;&t;&t;&t; * Bytestream.  If it is greater than 13, that&n;&t;&t;&t; * means that an Index exists and is followed by&n;&t;&t;&t; * a null termininated string.  Therefore, set&n;&t;&t;&t; * the temp variable to the length minus the minimum&n;&t;&t;&t; * byte stream length plus the byte for the Index to&n;&t;&t;&t; * determine the size of the NULL terminiated string.&n;&t;&t;&t; */
r_if
c_cond
(paren
l_int|13
OL
id|temp16
)paren
(brace
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|temp16
op_minus
l_int|14
)paren
suffix:semicolon
)brace
r_else
(brace
id|temp8
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Ensure a 32-bit boundary for the structure&n;&t;&t;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|ACPI_ROUND_UP_to_32_bITS
(paren
id|temp8
)paren
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_address16
)paren
op_plus
(paren
id|temp8
op_star
r_sizeof
(paren
id|u8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_EXTENDED_XRUPT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Extended IRQ&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
op_increment
id|buffer
suffix:semicolon
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|bytes_consumed
op_assign
id|temp16
op_plus
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Point past the length field and the&n;&t;&t;&t; * Interrupt vector flags to save off the&n;&t;&t;&t; * Interrupt table length to the Temp8 variable.&n;&t;&t;&t; */
id|buffer
op_add_assign
l_int|3
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * To compensate for multiple interrupt numbers, add 4 bytes for&n;&t;&t;&t; * each additional interrupts greater than 1&n;&t;&t;&t; */
id|additional_bytes
op_assign
(paren
id|u8
)paren
(paren
(paren
id|temp8
op_minus
l_int|1
)paren
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Resource Source Index and Resource Source are&n;&t;&t;&t; * optional elements.  Check the length of the&n;&t;&t;&t; * Bytestream.  If it is greater than 9, that&n;&t;&t;&t; * means that an Index exists and is followed by&n;&t;&t;&t; * a null termininated string.  Therefore, set&n;&t;&t;&t; * the temp variable to the length minus the minimum&n;&t;&t;&t; * byte stream length plus the byte for the Index to&n;&t;&t;&t; * determine the size of the NULL terminiated string.&n;&t;&t;&t; */
r_if
c_cond
(paren
l_int|9
op_plus
id|additional_bytes
OL
id|temp16
)paren
(brace
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|temp16
op_minus
(paren
l_int|9
op_plus
id|additional_bytes
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|temp8
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Ensure a 32-bit boundary for the structure&n;&t;&t;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|ACPI_ROUND_UP_to_32_bITS
(paren
id|temp8
)paren
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_ext_irq
)paren
op_plus
(paren
id|additional_bytes
op_star
r_sizeof
(paren
id|u8
)paren
)paren
op_plus
(paren
id|temp8
op_star
r_sizeof
(paren
id|u8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_IRQ_FORMAT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IRQ Resource.&n;&t;&t;&t; * Determine if it there are two or three trailing bytes&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|temp8
op_amp
l_int|0x01
)paren
(brace
id|bytes_consumed
op_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|bytes_consumed
op_assign
l_int|3
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Point past the descriptor&n;&t;&t;&t; */
op_increment
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Look at the number of bits set&n;&t;&t;&t; */
id|ACPI_MOVE_UNALIGNED16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
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
l_int|16
suffix:semicolon
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|temp16
op_amp
l_int|0x1
)paren
(brace
op_increment
id|number_of_interrupts
suffix:semicolon
)brace
id|temp16
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_io
)paren
op_plus
(paren
id|number_of_interrupts
op_star
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_DMA_FORMAT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * DMA Resource&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
id|bytes_consumed
op_assign
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Point past the descriptor&n;&t;&t;&t; */
op_increment
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Look at the number of bits set&n;&t;&t;&t; */
id|temp8
op_assign
op_star
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
l_int|8
suffix:semicolon
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|temp8
op_amp
l_int|0x1
)paren
(brace
op_increment
id|number_of_channels
suffix:semicolon
)brace
id|temp8
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_dma
)paren
op_plus
(paren
id|number_of_channels
op_star
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_START_DEPENDENT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Start Dependent Functions Resource&n;&t;&t;&t; * Determine if it there are two or three trailing bytes&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|temp8
op_amp
l_int|0x01
)paren
(brace
id|bytes_consumed
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|bytes_consumed
op_assign
l_int|1
suffix:semicolon
)brace
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_start_dpf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_END_DEPENDENT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Dependent Functions Resource&n;&t;&t;&t; */
id|bytes_consumed
op_assign
l_int|1
suffix:semicolon
id|structure_size
op_assign
id|ACPI_RESOURCE_LENGTH
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_IO_PORT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * IO Port Resource&n;&t;&t;&t; */
id|bytes_consumed
op_assign
l_int|8
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_io
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_FIXED_IO_PORT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Fixed IO Port Resource&n;&t;&t;&t; */
id|bytes_consumed
op_assign
l_int|4
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_fixed_io
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_SMALL_VENDOR
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Vendor Specific Resource&n;&t;&t;&t; */
id|buffer
op_assign
id|byte_stream_buffer
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|temp8
op_amp
l_int|0x7
)paren
suffix:semicolon
id|bytes_consumed
op_assign
id|temp8
op_plus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Ensure a 32-bit boundary for the structure&n;&t;&t;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|ACPI_ROUND_UP_to_32_bITS
(paren
id|temp8
)paren
suffix:semicolon
id|structure_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_vendor
)paren
op_plus
(paren
id|temp8
op_star
r_sizeof
(paren
id|u8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RDESC_TYPE_END_TAG
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * End Tag&n;&t;&t;&t; */
id|bytes_consumed
op_assign
l_int|2
suffix:semicolon
id|structure_size
op_assign
id|ACPI_RESOURCE_LENGTH
suffix:semicolon
id|byte_stream_buffer_length
op_assign
id|bytes_parsed
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * If we get here, everything is out of sync,&n;&t;&t;&t; *  so exit with an error&n;&t;&t;&t; */
id|return_ACPI_STATUS
(paren
id|AE_AML_INVALID_RESOURCE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Update the return value and counter&n;&t;&t; */
id|buffer_size
op_add_assign
id|ACPI_ALIGN_RESOURCE_SIZE
c_func
(paren
id|structure_size
)paren
suffix:semicolon
id|bytes_parsed
op_add_assign
id|bytes_consumed
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the byte stream to point to the next resource&n;&t;&t; */
id|byte_stream_buffer
op_add_assign
id|bytes_consumed
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This is the data the caller needs&n;&t; */
op_star
id|size_needed
op_assign
id|buffer_size
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_get_pci_routing_table_length&n; *&n; * PARAMETERS:  package_object          - Pointer to the package object&n; *              buffer_size_needed      - u32 pointer of the size buffer&n; *                                        needed to properly return the&n; *                                        parsed data&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Given a package representing a PCI routing table, this&n; *              calculates the size of the corresponding linked list of&n; *              descriptions.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_pci_routing_table_length
id|acpi_rs_get_pci_routing_table_length
(paren
r_union
id|acpi_operand_object
op_star
id|package_object
comma
id|acpi_size
op_star
id|buffer_size_needed
)paren
(brace
id|u32
id|number_of_elements
suffix:semicolon
id|acpi_size
id|temp_size_needed
op_assign
l_int|0
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|top_object_list
suffix:semicolon
id|u32
id|index
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|package_element
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|sub_object_list
suffix:semicolon
id|u8
id|name_found
suffix:semicolon
id|u32
id|table_index
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_get_pci_routing_table_length&quot;
)paren
suffix:semicolon
id|number_of_elements
op_assign
id|package_object-&gt;package.count
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate the size of the return buffer.&n;&t; * The base size is the number of elements * the sizes of the&n;&t; * structures.  Additional space for the strings is added below.&n;&t; * The minus one is to subtract the size of the u8 Source[1]&n;&t; * member because it is added below.&n;&t; *&n;&t; * But each PRT_ENTRY structure has a pointer to a string and&n;&t; * the size of that string must be found.&n;&t; */
id|top_object_list
op_assign
id|package_object-&gt;package.elements
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
multiline_comment|/*&n;&t;&t; * Dereference the sub-package&n;&t;&t; */
id|package_element
op_assign
op_star
id|top_object_list
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The sub_object_list will now point to an array of the&n;&t;&t; * four IRQ elements: Address, Pin, Source and source_index&n;&t;&t; */
id|sub_object_list
op_assign
id|package_element-&gt;package.elements
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Scan the irq_table_elements for the Source Name String&n;&t;&t; */
id|name_found
op_assign
id|FALSE
suffix:semicolon
r_for
c_loop
(paren
id|table_index
op_assign
l_int|0
suffix:semicolon
id|table_index
OL
l_int|4
op_logical_and
op_logical_neg
id|name_found
suffix:semicolon
id|table_index
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|ACPI_TYPE_STRING
op_eq
id|ACPI_GET_OBJECT_TYPE
(paren
op_star
id|sub_object_list
)paren
)paren
op_logical_or
(paren
(paren
id|ACPI_TYPE_LOCAL_REFERENCE
op_eq
id|ACPI_GET_OBJECT_TYPE
(paren
op_star
id|sub_object_list
)paren
)paren
op_logical_and
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|reference.opcode
op_eq
id|AML_INT_NAMEPATH_OP
)paren
)paren
)paren
(brace
id|name_found
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Look at the next element&n;&t;&t;&t;&t; */
id|sub_object_list
op_increment
suffix:semicolon
)brace
)brace
id|temp_size_needed
op_add_assign
(paren
r_sizeof
(paren
r_struct
id|acpi_pci_routing_table
)paren
op_minus
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Was a String type found?&n;&t;&t; */
r_if
c_cond
(paren
id|name_found
)paren
(brace
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
op_star
id|sub_object_list
)paren
op_eq
id|ACPI_TYPE_STRING
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * The length String.Length field does not include the&n;&t;&t;&t;&t; * terminating NULL, add 1&n;&t;&t;&t;&t; */
id|temp_size_needed
op_add_assign
(paren
(paren
id|acpi_size
)paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|string.length
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|temp_size_needed
op_add_assign
id|acpi_ns_get_pathname_length
(paren
(paren
op_star
id|sub_object_list
)paren
op_member_access_from_pointer
id|reference.node
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * If no name was found, then this is a NULL, which is&n;&t;&t;&t; * translated as a u32 zero.&n;&t;&t;&t; */
id|temp_size_needed
op_add_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
)brace
multiline_comment|/* Round up the size since each element must be aligned */
id|temp_size_needed
op_assign
id|ACPI_ROUND_UP_to_64_bITS
(paren
id|temp_size_needed
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Point to the next union acpi_operand_object&n;&t;&t; */
id|top_object_list
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Adding an extra element to the end of the list, essentially a NULL terminator&n;&t; */
op_star
id|buffer_size_needed
op_assign
id|temp_size_needed
op_plus
r_sizeof
(paren
r_struct
id|acpi_pci_routing_table
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
