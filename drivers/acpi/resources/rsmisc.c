multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rsmisc - Miscellaneous resource descriptors&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acresrc.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rsmisc&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_end_tag_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_end_tag_resource
id|acpi_rs_end_tag_resource
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
id|acpi_size
id|struct_size
op_assign
id|ACPI_RESOURCE_LENGTH
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_end_tag_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The number of bytes consumed is static&n;&t; */
op_star
id|bytes_consumed
op_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t; *  Fill out the structure&n;&t; */
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_END_TAG
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Length parameter&n;&t; */
id|output_struct-&gt;length
op_assign
l_int|0
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_end_tag_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_end_tag_stream
id|acpi_rs_end_tag_stream
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
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_end_tag_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x79
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Set the Checksum - zero means that the resource data is treated as if&n;&t; * the checksum operation succeeded (ACPI Spec 1.0b Section 6.4.2.8)&n;&t; */
id|temp8
op_assign
l_int|0
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_vendor_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_vendor_resource
id|acpi_rs_vendor_resource
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
id|u8
id|index
suffix:semicolon
id|acpi_size
id|struct_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_vendor
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_vendor_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Dereference the Descriptor to find if this is a large or small item.&n;&t; */
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
l_int|0x80
)paren
(brace
multiline_comment|/*&n;&t;&t; * Large Item, point to the length field&n;&t;&t; */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* Dereference */
id|ACPI_MOVE_16_TO_16
(paren
op_amp
id|temp16
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Calculate bytes consumed */
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
multiline_comment|/* Point to the first vendor byte */
id|buffer
op_add_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Small Item, dereference the size&n;&t;&t; */
id|temp16
op_assign
(paren
id|u8
)paren
(paren
op_star
id|buffer
op_amp
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* Calculate bytes consumed */
op_star
id|bytes_consumed
op_assign
(paren
id|acpi_size
)paren
id|temp16
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Point to the first vendor byte */
id|buffer
op_add_assign
l_int|1
suffix:semicolon
)brace
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_VENDOR
suffix:semicolon
id|output_struct-&gt;data.vendor_specific.length
op_assign
id|temp16
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
id|temp16
suffix:semicolon
id|index
op_increment
)paren
(brace
id|output_struct-&gt;data.vendor_specific.reserved
(braket
id|index
)braket
op_assign
op_star
id|buffer
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * In order for the struct_size to fall on a 32-bit boundary,&n;&t; * calculate the length of the vendor string and expand the&n;&t; * struct_size to the next 32-bit boundary.&n;&t; */
id|struct_size
op_add_assign
id|ACPI_ROUND_UP_to_32_bITS
(paren
id|temp16
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_vendor_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_vendor_stream
id|acpi_rs_vendor_stream
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
l_string|&quot;rs_vendor_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Dereference the length to find if this is a large or small item.&n;&t; */
r_if
c_cond
(paren
id|linked_list-&gt;data.vendor_specific.length
OG
l_int|7
)paren
(brace
multiline_comment|/*&n;&t;&t; * Large Item, Set the descriptor field and length bytes&n;&t;&t; */
op_star
id|buffer
op_assign
l_int|0x84
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|temp16
op_assign
(paren
id|u16
)paren
id|linked_list-&gt;data.vendor_specific.length
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
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Small Item, Set the descriptor field&n;&t;&t; */
id|temp8
op_assign
l_int|0x70
suffix:semicolon
id|temp8
op_or_assign
(paren
id|u8
)paren
id|linked_list-&gt;data.vendor_specific.length
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
)brace
multiline_comment|/*&n;&t; * Loop through all of the Vendor Specific fields&n;&t; */
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|linked_list-&gt;data.vendor_specific.length
suffix:semicolon
id|index
op_increment
)paren
(brace
id|temp8
op_assign
id|linked_list-&gt;data.vendor_specific.reserved
(braket
id|index
)braket
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
)brace
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_start_depend_fns_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_start_depend_fns_resource
id|acpi_rs_start_depend_fns_resource
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
id|acpi_size
id|struct_size
op_assign
id|ACPI_SIZEOF_RESOURCE
(paren
r_struct
id|acpi_resource_start_dpf
)paren
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_start_depend_fns_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The number of bytes consumed are contained in the descriptor (Bits:0-1)&n;&t; */
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
op_star
id|bytes_consumed
op_assign
(paren
id|temp8
op_amp
l_int|0x01
)paren
op_plus
l_int|1
suffix:semicolon
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_START_DPF
suffix:semicolon
multiline_comment|/*&n;&t; * Point to Byte 1 if it is used&n;&t; */
r_if
c_cond
(paren
l_int|2
op_eq
op_star
id|bytes_consumed
)paren
(brace
id|buffer
op_add_assign
l_int|1
suffix:semicolon
id|temp8
op_assign
op_star
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Check Compatibility priority&n;&t;&t; */
id|output_struct-&gt;data.start_dpf.compatibility_priority
op_assign
id|temp8
op_amp
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
l_int|3
op_eq
id|output_struct-&gt;data.start_dpf.compatibility_priority
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_BAD_RESOURCE_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Check Performance/Robustness preference&n;&t;&t; */
id|output_struct-&gt;data.start_dpf.performance_robustness
op_assign
(paren
id|temp8
op_rshift
l_int|2
)paren
op_amp
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
l_int|3
op_eq
id|output_struct-&gt;data.start_dpf.performance_robustness
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_BAD_RESOURCE_VALUE
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|output_struct-&gt;data.start_dpf.compatibility_priority
op_assign
id|ACPI_ACCEPTABLE_CONFIGURATION
suffix:semicolon
id|output_struct-&gt;data.start_dpf.performance_robustness
op_assign
id|ACPI_ACCEPTABLE_CONFIGURATION
suffix:semicolon
)brace
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_end_depend_fns_resource&n; *&n; * PARAMETERS:  byte_stream_buffer      - Pointer to the resource input byte&n; *                                        stream&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        consumed the byte_stream_buffer is&n; *                                        returned&n; *              output_buffer           - Pointer to the return data buffer&n; *              structure_size          - Pointer to where the number of bytes&n; *                                        in the return data struct is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the resource byte stream and fill out the appropriate&n; *              structure pointed to by the output_buffer. Return the&n; *              number of bytes consumed from the byte stream.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_end_depend_fns_resource
id|acpi_rs_end_depend_fns_resource
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
id|acpi_size
id|struct_size
op_assign
id|ACPI_RESOURCE_LENGTH
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_end_depend_fns_resource&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The number of bytes consumed is static&n;&t; */
op_star
id|bytes_consumed
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *  Fill out the structure&n;&t; */
id|output_struct-&gt;id
op_assign
id|ACPI_RSTYPE_END_DPF
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_start_depend_fns_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - u32 pointer that is filled with&n; *                                        the number of bytes of the&n; *                                        output_buffer used&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_start_depend_fns_stream
id|acpi_rs_start_depend_fns_stream
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
id|u8
id|temp8
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_start_depend_fns_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is set based upon whether a byte is needed&n;&t; * to contain Priority data.&n;&t; */
r_if
c_cond
(paren
id|ACPI_ACCEPTABLE_CONFIGURATION
op_eq
id|linked_list-&gt;data.start_dpf.compatibility_priority
op_logical_and
id|ACPI_ACCEPTABLE_CONFIGURATION
op_eq
id|linked_list-&gt;data.start_dpf.performance_robustness
)paren
(brace
op_star
id|buffer
op_assign
l_int|0x30
suffix:semicolon
)brace
r_else
(brace
op_star
id|buffer
op_assign
l_int|0x31
suffix:semicolon
id|buffer
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the Priority Byte Definition&n;&t;&t; */
id|temp8
op_assign
l_int|0
suffix:semicolon
id|temp8
op_assign
(paren
id|u8
)paren
(paren
(paren
id|linked_list-&gt;data.start_dpf.performance_robustness
op_amp
l_int|0x03
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|temp8
op_or_assign
(paren
id|linked_list-&gt;data.start_dpf.compatibility_priority
op_amp
l_int|0x03
)paren
suffix:semicolon
op_star
id|buffer
op_assign
id|temp8
suffix:semicolon
)brace
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_end_depend_fns_stream&n; *&n; * PARAMETERS:  linked_list             - Pointer to the resource linked list&n; *              output_buffer           - Pointer to the user&squot;s return buffer&n; *              bytes_consumed          - Pointer to where the number of bytes&n; *                                        used in the output_buffer is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Take the linked list resource structure and fills in the&n; *              the appropriate bytes in a byte stream&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_end_depend_fns_stream
id|acpi_rs_end_depend_fns_stream
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
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_end_depend_fns_stream&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The descriptor field is static&n;&t; */
op_star
id|buffer
op_assign
l_int|0x38
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
