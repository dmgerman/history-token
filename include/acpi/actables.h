multiline_comment|/******************************************************************************&n; *&n; * Name: actables.h - ACPI table management&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACTABLES_H__
DECL|macro|__ACTABLES_H__
mdefine_line|#define __ACTABLES_H__
multiline_comment|/* Used in acpi_tb_map_acpi_table for size parameter if table header is to be used */
DECL|macro|SIZE_IN_HEADER
mdefine_line|#define SIZE_IN_HEADER          0
id|acpi_status
id|acpi_tb_handle_to_object
(paren
id|u16
id|table_id
comma
r_struct
id|acpi_table_desc
op_star
op_star
id|table_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * tbconvrt - Table conversion routines&n; */
id|acpi_status
id|acpi_tb_convert_to_xsdt
(paren
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_convert_table_fadt
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_build_common_facs
(paren
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|u32
id|acpi_tb_get_table_count
(paren
r_struct
id|rsdp_descriptor
op_star
id|RSDP
comma
r_struct
id|acpi_table_header
op_star
id|RSDT
)paren
suffix:semicolon
multiline_comment|/*&n; * tbget - Table &quot;get&quot; routines&n; */
id|acpi_status
id|acpi_tb_get_table
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_get_table_header
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_header
op_star
id|return_header
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_get_table_body
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_header
op_star
id|header
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_get_this_table
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_header
op_star
id|header
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_table_override
(paren
r_struct
id|acpi_table_header
op_star
id|header
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_get_table_ptr
(paren
id|acpi_table_type
id|table_type
comma
id|u32
id|instance
comma
r_struct
id|acpi_table_header
op_star
op_star
id|table_ptr_loc
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_verify_rsdp
(paren
r_struct
id|acpi_pointer
op_star
id|address
)paren
suffix:semicolon
r_void
id|acpi_tb_get_rsdt_address
(paren
r_struct
id|acpi_pointer
op_star
id|out_address
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_validate_rsdt
(paren
r_struct
id|acpi_table_header
op_star
id|table_ptr
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_get_required_tables
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_get_primary_table
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_get_secondary_table
(paren
r_struct
id|acpi_pointer
op_star
id|address
comma
id|acpi_string
id|signature
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
multiline_comment|/*&n; * tbinstall - Table installation&n; */
id|acpi_status
id|acpi_tb_install_table
(paren
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_match_signature
(paren
r_char
op_star
id|signature
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
comma
id|u8
id|search_type
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_recognize_table
(paren
r_struct
id|acpi_table_desc
op_star
id|table_info
comma
id|u8
id|search_type
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_init_table_descriptor
(paren
id|acpi_table_type
id|table_type
comma
r_struct
id|acpi_table_desc
op_star
id|table_info
)paren
suffix:semicolon
multiline_comment|/*&n; * tbremove - Table removal and deletion&n; */
r_void
id|acpi_tb_delete_all_tables
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_tb_delete_tables_by_type
(paren
id|acpi_table_type
id|type
)paren
suffix:semicolon
r_void
id|acpi_tb_delete_single_table
(paren
r_struct
id|acpi_table_desc
op_star
id|table_desc
)paren
suffix:semicolon
r_struct
id|acpi_table_desc
op_star
id|acpi_tb_uninstall_table
(paren
r_struct
id|acpi_table_desc
op_star
id|table_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * tbrsd - RSDP, RSDT utilities&n; */
id|acpi_status
id|acpi_tb_get_table_rsdt
(paren
r_void
)paren
suffix:semicolon
id|u8
op_star
id|acpi_tb_scan_memory_for_rsdp
(paren
id|u8
op_star
id|start_address
comma
id|u32
id|length
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_find_rsdp
(paren
r_struct
id|acpi_table_desc
op_star
id|table_info
comma
id|u32
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; * tbutils - common table utilities&n; */
id|acpi_status
id|acpi_tb_find_table
(paren
r_char
op_star
id|signature
comma
r_char
op_star
id|oem_id
comma
r_char
op_star
id|oem_table_id
comma
r_struct
id|acpi_table_header
op_star
op_star
id|table_ptr
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_verify_table_checksum
(paren
r_struct
id|acpi_table_header
op_star
id|table_header
)paren
suffix:semicolon
id|u8
id|acpi_tb_checksum
(paren
r_void
op_star
id|buffer
comma
id|u32
id|length
)paren
suffix:semicolon
id|acpi_status
id|acpi_tb_validate_table_header
(paren
r_struct
id|acpi_table_header
op_star
id|table_header
)paren
suffix:semicolon
macro_line|#endif /* __ACTABLES_H__ */
eof
