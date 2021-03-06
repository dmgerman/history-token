multiline_comment|/*&n; * hvcserver.h&n; * Copyright (C) 2004 Ryan S Arnold, IBM Corporation&n; *&n; * PPC64 virtual I/O console server support.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _PPC64_HVCSERVER_H
DECL|macro|_PPC64_HVCSERVER_H
mdefine_line|#define _PPC64_HVCSERVER_H
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/* Converged Location Code length */
DECL|macro|HVCS_CLC_LENGTH
mdefine_line|#define HVCS_CLC_LENGTH&t;79
multiline_comment|/**&n; * hvcs_partner_info - an element in a list of partner info&n; * @node: list_head denoting this partner_info struct&squot;s position in the list of&n; *&t;partner info.&n; * @unit_address: The partner unit address of this entry.&n; * @partition_ID: The partner partition ID of this entry.&n; * @location_code: The converged location code of this entry + 1 char for the&n; *&t;null-term.&n; *&n; * This structure outlines the format that partner info is presented to a caller&n; * of the hvcs partner info fetching functions.  These are strung together into&n; * a list using linux kernel lists.&n; */
DECL|struct|hvcs_partner_info
r_struct
id|hvcs_partner_info
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|unit_address
r_uint32
id|unit_address
suffix:semicolon
DECL|member|partition_ID
r_uint32
id|partition_ID
suffix:semicolon
DECL|member|location_code
r_char
id|location_code
(braket
id|HVCS_CLC_LENGTH
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* CLC + 1 null-term char */
)brace
suffix:semicolon
r_extern
r_int
id|hvcs_free_partner_info
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
r_extern
r_int
id|hvcs_get_partner_info
c_func
(paren
r_uint32
id|unit_address
comma
r_struct
id|list_head
op_star
id|head
comma
r_int
r_int
op_star
id|pi_buff
)paren
suffix:semicolon
r_extern
r_int
id|hvcs_register_connection
c_func
(paren
r_uint32
id|unit_address
comma
r_uint32
id|p_partition_ID
comma
r_uint32
id|p_unit_address
)paren
suffix:semicolon
r_extern
r_int
id|hvcs_free_connection
c_func
(paren
r_uint32
id|unit_address
)paren
suffix:semicolon
macro_line|#endif /* _PPC64_HVCSERVER_H */
eof
