multiline_comment|/******************************************************************************&n; *&n; * Name: acresrc.h - Resource Manager function prototypes&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACRESRC_H__
DECL|macro|__ACRESRC_H__
mdefine_line|#define __ACRESRC_H__
multiline_comment|/*&n; *  Function prototypes called from Acpi* APIs&n; */
id|acpi_status
id|acpi_rs_get_prt_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_get_crs_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_get_prs_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_get_method_data
(paren
id|acpi_handle
id|handle
comma
r_char
op_star
id|path
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_set_srs_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_create_resource_list
(paren
r_union
id|acpi_operand_object
op_star
id|byte_stream_buffer
comma
r_struct
id|acpi_buffer
op_star
id|output_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_create_byte_stream
(paren
r_struct
id|acpi_resource
op_star
id|linked_list_buffer
comma
r_struct
id|acpi_buffer
op_star
id|output_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_create_pci_routing_table
(paren
r_union
id|acpi_operand_object
op_star
id|package_object
comma
r_struct
id|acpi_buffer
op_star
id|output_buffer
)paren
suffix:semicolon
multiline_comment|/*&n; * Function prototypes called from acpi_rs_create*&n; */
r_void
id|acpi_rs_dump_irq
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_address16
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_address32
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_address64
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_dma
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_io
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_extended_irq
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_fixed_io
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_fixed_memory32
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_memory24
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_memory32
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_start_depend_fns
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_vendor_specific
(paren
r_union
id|acpi_resource_data
op_star
id|data
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_resource_list
(paren
r_struct
id|acpi_resource
op_star
id|resource
)paren
suffix:semicolon
r_void
id|acpi_rs_dump_irq_list
(paren
id|u8
op_star
id|route_table
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_get_byte_stream_start
(paren
id|u8
op_star
id|byte_stream_buffer
comma
id|u8
op_star
op_star
id|byte_stream_start
comma
id|u32
op_star
id|size
)paren
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
id|acpi_rs_get_byte_stream_length
(paren
r_struct
id|acpi_resource
op_star
id|linked_list_buffer
comma
id|acpi_size
op_star
id|size_needed
)paren
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
id|output_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_rs_list_to_byte_stream
(paren
r_struct
id|acpi_resource
op_star
id|linked_list
comma
id|acpi_size
id|byte_stream_size_needed
comma
id|u8
op_star
id|output_buffer
)paren
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
id|acpi_rs_irq_resource
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
suffix:semicolon
id|acpi_status
id|acpi_rs_irq_stream
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
id|acpi_rs_address16_resource
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
suffix:semicolon
id|acpi_status
id|acpi_rs_address16_stream
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
suffix:semicolon
id|acpi_status
id|acpi_rs_address32_resource
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
suffix:semicolon
id|acpi_status
id|acpi_rs_address32_stream
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
suffix:semicolon
id|acpi_status
id|acpi_rs_address64_resource
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
suffix:semicolon
id|acpi_status
id|acpi_rs_address64_stream
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
id|acpi_rs_extended_irq_resource
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
suffix:semicolon
id|acpi_status
id|acpi_rs_extended_irq_stream
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|acpi_status
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
suffix:semicolon
id|u8
id|acpi_rs_get_resource_type
(paren
id|u8
id|resource_start_byte
)paren
suffix:semicolon
macro_line|#endif  /* __ACRESRC_H__ */
eof
