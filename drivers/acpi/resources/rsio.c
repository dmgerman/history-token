multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rsio - IO and DMA resource descriptors&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acresrc.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rsio&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_io_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_io_resource
id|acpi_rs_io_resource
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
id|acpi_resource_io
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_io_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The number of bytes consumed are Constant&n;&t; */
op_star
id|bytes_consumed
op_assign
l_int|8
suffix:semicolon
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_IO
suffix:semicolon
multiline_comment|/*&n;&t; * Check Decode&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|output_struct-&gt;data.io.io_decode
op_assign
id|temp8
op_amp
l_int|0x01
suffix:semicolon
multiline_comment|/*&n;&t; * Check min_base Address&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|ACPI_MOVE_16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|output_struct-&gt;data.io.min_base_address
op_assign
id|temp16
suffix:semicolon
multiline_comment|/*&n;&t; * Check max_base Address&n;&t; */
id|buffer
op_add_assign
l_int|2
suffix:semicolon
id|ACPI_MOVE_16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|output_struct-&gt;data.io.max_base_address
op_assign
id|temp16
suffix:semicolon
multiline_comment|/*&n;&t; * Check Base alignment&n;&t; */
id|buffer
op_add_assign
l_int|2
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|output_struct-&gt;data.io.alignment
op_assign
id|temp8
suffix:semicolon
multiline_comment|/*&n;&t; * Check range_length&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|output_struct-&gt;data.io.range_length
op_assign
id|temp8
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_fixed_io_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_fixed_io_resource
id|acpi_rs_fixed_io_resource
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
id|acpi_resource_fixed_io
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_fixed_io_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The number of bytes consumed are Constant&n;&t; */
op_star
id|bytes_consumed
op_assign
l_int|4
suffix:semicolon
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_FIXED_IO
suffix:semicolon
multiline_comment|/*&n;&t; * Check Range Base Address&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|ACPI_MOVE_16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
id|output_struct-&gt;data.fixed_io.base_address
op_assign
id|temp16
suffix:semicolon
multiline_comment|/*&n;&t; * Check range_length&n;&t; */
id|buffer
op_add_assign
l_int|2
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
id|output_struct-&gt;data.fixed_io.range_length
op_assign
id|temp8
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_io_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_io_stream
id|acpi_rs_io_stream
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
l_string|&quot;rs_io_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x47
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Io Information Byte&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
(paren
id|linked_list-&gt;data.io.io_decode
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
id|temp16
op_assign
(paren
id|u16
)paren
id|linked_list-&gt;data.io.min_base_address
suffix:semicolon
id|ACPI_MOVE_16_TO_16
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
multiline_comment|/*&n;&t; * Set the Range maximum base address&n;&t; */
id|temp16
op_assign
(paren
id|u16
)paren
id|linked_list-&gt;data.io.max_base_address
suffix:semicolon
id|ACPI_MOVE_16_TO_16
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
multiline_comment|/*&n;&t; * Set the base alignment&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|linked_list-&gt;data.io.alignment
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
multiline_comment|/*&n;&t; * Set the range length&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|linked_list-&gt;data.io.range_length
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_fixed_io_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_fixed_io_stream
id|acpi_rs_fixed_io_stream
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
l_string|&quot;rs_fixed_io_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x4B
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Range base address&n;&t; */
id|temp16
op_assign
(paren
id|u16
)paren
id|linked_list-&gt;data.fixed_io.base_address
suffix:semicolon
id|ACPI_MOVE_16_TO_16
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
multiline_comment|/*&n;&t; * Set the range length&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
id|linked_list-&gt;data.fixed_io.range_length
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_dma_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_dma_resource
id|acpi_rs_dma_resource
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
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|u8
id|index
suffix:semicolon
id|u8
id|i
suffix:semicolon
id|acpi_size
id|struct_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_dma
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_dma_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The number of bytes consumed are Constant&n;&t; */
op_star
id|bytes_consumed
op_assign
l_int|3
suffix:semicolon
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_DMA
suffix:semicolon
multiline_comment|/*&n;&t; * Point to the 8-bits of Byte 1&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Decode the DMA channel bits */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
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
(paren
id|temp8
op_rshift
id|index
)paren
op_amp
l_int|0x01
)paren
(brace
id|output_struct-&gt;data.dma.channels
(braket
id|i
)braket
op_assign
id|index
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/* Zero DMA channels is valid */
id|output_struct-&gt;data.dma.number_of_channels
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Calculate the structure size based upon the number of interrupts&n;&t;&t; */
id|struct_size
op_add_assign
(paren
(paren
id|acpi_size
)paren
id|i
op_minus
l_int|1
)paren
op_star
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Point to Byte 2&n;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t; * Check for transfer preference (Bits[1:0])&n;&t; */
id|output_struct-&gt;data.dma.transfer
op_assign
id|temp8
op_amp
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
l_int|0x03
op_eq
id|output_struct-&gt;data.dma.transfer
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid DMA.Transfer preference (3)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get bus master preference (Bit[2])&n;&t; */
id|output_struct-&gt;data.dma.bus_master
op_assign
(paren
id|temp8
op_rshift
l_int|2
)paren
op_amp
l_int|0x01
suffix:semicolon
multiline_comment|/*&n;&t; * Get channel speed support (Bits[6:5])&n;&t; */
id|output_struct-&gt;data.dma.type
op_assign
(paren
id|temp8
op_rshift
l_int|5
)paren
op_amp
l_int|0x03
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_dma_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_dma_stream
id|acpi_rs_dma_stream
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
id|u8
id|index
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_dma_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x2A
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|temp8
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Loop through all of the Channels and set the mask bits&n;&t; */
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|linked_list-&gt;data.dma.number_of_channels
suffix:semicolon
id|index
op_increment
)paren
(brace
id|temp16
op_assign
(paren
id|u16
)paren
id|linked_list-&gt;data.dma.channels
(braket
id|index
)braket
suffix:semicolon
id|temp8
op_or_assign
l_int|0x1
op_lshift
id|temp16
suffix:semicolon
)brace
op_star
id|buffer
op_assign
id|temp8
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Set the DMA Info&n;&t; */
id|temp8
op_assign
(paren
id|u8
)paren
(paren
(paren
id|linked_list-&gt;data.dma.type
op_amp
l_int|0x03
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|temp8
op_or_assign
(paren
(paren
id|linked_list-&gt;data.dma.bus_master
op_amp
l_int|0x01
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|temp8
op_or_assign
(paren
id|linked_list-&gt;data.dma.transfer
op_amp
l_int|0x03
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
