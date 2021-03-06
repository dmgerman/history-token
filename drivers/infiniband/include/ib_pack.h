multiline_comment|/*&n; * Copyright (c) 2004 Topspin Corporation.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: ib_pack.h 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#ifndef IB_PACK_H
DECL|macro|IB_PACK_H
mdefine_line|#define IB_PACK_H
macro_line|#include &lt;ib_verbs.h&gt;
r_enum
(brace
DECL|enumerator|IB_LRH_BYTES
id|IB_LRH_BYTES
op_assign
l_int|8
comma
DECL|enumerator|IB_GRH_BYTES
id|IB_GRH_BYTES
op_assign
l_int|40
comma
DECL|enumerator|IB_BTH_BYTES
id|IB_BTH_BYTES
op_assign
l_int|12
comma
DECL|enumerator|IB_DETH_BYTES
id|IB_DETH_BYTES
op_assign
l_int|8
)brace
suffix:semicolon
DECL|struct|ib_field
r_struct
id|ib_field
(brace
DECL|member|struct_offset_bytes
r_int
id|struct_offset_bytes
suffix:semicolon
DECL|member|struct_size_bytes
r_int
id|struct_size_bytes
suffix:semicolon
DECL|member|offset_words
r_int
id|offset_words
suffix:semicolon
DECL|member|offset_bits
r_int
id|offset_bits
suffix:semicolon
DECL|member|size_bits
r_int
id|size_bits
suffix:semicolon
DECL|member|field_name
r_char
op_star
id|field_name
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RESERVED
mdefine_line|#define RESERVED &bslash;&n;&t;.field_name          = &quot;reserved&quot;
multiline_comment|/*&n; * This macro cleans up the definitions of constants for BTH opcodes.&n; * It is used to define constants such as IB_OPCODE_UD_SEND_ONLY,&n; * which becomes IB_OPCODE_UD + IB_OPCODE_SEND_ONLY, and this gives&n; * the correct value.&n; *&n; * In short, user code should use the constants defined using the&n; * macro rather than worrying about adding together other constants.&n;*/
DECL|macro|IB_OPCODE
mdefine_line|#define IB_OPCODE(transport, op) &bslash;&n;&t;IB_OPCODE_ ## transport ## _ ## op = &bslash;&n;&t;&t;IB_OPCODE_ ## transport + IB_OPCODE_ ## op
r_enum
(brace
multiline_comment|/* transport types -- just used to define real constants */
DECL|enumerator|IB_OPCODE_RC
id|IB_OPCODE_RC
op_assign
l_int|0x00
comma
DECL|enumerator|IB_OPCODE_UC
id|IB_OPCODE_UC
op_assign
l_int|0x20
comma
DECL|enumerator|IB_OPCODE_RD
id|IB_OPCODE_RD
op_assign
l_int|0x40
comma
DECL|enumerator|IB_OPCODE_UD
id|IB_OPCODE_UD
op_assign
l_int|0x60
comma
multiline_comment|/* operations -- just used to define real constants */
DECL|enumerator|IB_OPCODE_SEND_FIRST
id|IB_OPCODE_SEND_FIRST
op_assign
l_int|0x00
comma
DECL|enumerator|IB_OPCODE_SEND_MIDDLE
id|IB_OPCODE_SEND_MIDDLE
op_assign
l_int|0x01
comma
DECL|enumerator|IB_OPCODE_SEND_LAST
id|IB_OPCODE_SEND_LAST
op_assign
l_int|0x02
comma
DECL|enumerator|IB_OPCODE_SEND_LAST_WITH_IMMEDIATE
id|IB_OPCODE_SEND_LAST_WITH_IMMEDIATE
op_assign
l_int|0x03
comma
DECL|enumerator|IB_OPCODE_SEND_ONLY
id|IB_OPCODE_SEND_ONLY
op_assign
l_int|0x04
comma
DECL|enumerator|IB_OPCODE_SEND_ONLY_WITH_IMMEDIATE
id|IB_OPCODE_SEND_ONLY_WITH_IMMEDIATE
op_assign
l_int|0x05
comma
DECL|enumerator|IB_OPCODE_RDMA_WRITE_FIRST
id|IB_OPCODE_RDMA_WRITE_FIRST
op_assign
l_int|0x06
comma
DECL|enumerator|IB_OPCODE_RDMA_WRITE_MIDDLE
id|IB_OPCODE_RDMA_WRITE_MIDDLE
op_assign
l_int|0x07
comma
DECL|enumerator|IB_OPCODE_RDMA_WRITE_LAST
id|IB_OPCODE_RDMA_WRITE_LAST
op_assign
l_int|0x08
comma
DECL|enumerator|IB_OPCODE_RDMA_WRITE_LAST_WITH_IMMEDIATE
id|IB_OPCODE_RDMA_WRITE_LAST_WITH_IMMEDIATE
op_assign
l_int|0x09
comma
DECL|enumerator|IB_OPCODE_RDMA_WRITE_ONLY
id|IB_OPCODE_RDMA_WRITE_ONLY
op_assign
l_int|0x0a
comma
DECL|enumerator|IB_OPCODE_RDMA_WRITE_ONLY_WITH_IMMEDIATE
id|IB_OPCODE_RDMA_WRITE_ONLY_WITH_IMMEDIATE
op_assign
l_int|0x0b
comma
DECL|enumerator|IB_OPCODE_RDMA_READ_REQUEST
id|IB_OPCODE_RDMA_READ_REQUEST
op_assign
l_int|0x0c
comma
DECL|enumerator|IB_OPCODE_RDMA_READ_RESPONSE_FIRST
id|IB_OPCODE_RDMA_READ_RESPONSE_FIRST
op_assign
l_int|0x0d
comma
DECL|enumerator|IB_OPCODE_RDMA_READ_RESPONSE_MIDDLE
id|IB_OPCODE_RDMA_READ_RESPONSE_MIDDLE
op_assign
l_int|0x0e
comma
DECL|enumerator|IB_OPCODE_RDMA_READ_RESPONSE_LAST
id|IB_OPCODE_RDMA_READ_RESPONSE_LAST
op_assign
l_int|0x0f
comma
DECL|enumerator|IB_OPCODE_RDMA_READ_RESPONSE_ONLY
id|IB_OPCODE_RDMA_READ_RESPONSE_ONLY
op_assign
l_int|0x10
comma
DECL|enumerator|IB_OPCODE_ACKNOWLEDGE
id|IB_OPCODE_ACKNOWLEDGE
op_assign
l_int|0x11
comma
DECL|enumerator|IB_OPCODE_ATOMIC_ACKNOWLEDGE
id|IB_OPCODE_ATOMIC_ACKNOWLEDGE
op_assign
l_int|0x12
comma
DECL|enumerator|IB_OPCODE_COMPARE_SWAP
id|IB_OPCODE_COMPARE_SWAP
op_assign
l_int|0x13
comma
DECL|enumerator|IB_OPCODE_FETCH_ADD
id|IB_OPCODE_FETCH_ADD
op_assign
l_int|0x14
comma
multiline_comment|/* real constants follow -- see comment about above IB_OPCODE()&n;&t;   macro for more details */
multiline_comment|/* RC */
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|SEND_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|SEND_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|SEND_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|SEND_LAST_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|SEND_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|SEND_ONLY_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_WRITE_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_WRITE_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_WRITE_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_WRITE_LAST_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_WRITE_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_WRITE_ONLY_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_READ_REQUEST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_READ_RESPONSE_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_READ_RESPONSE_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_READ_RESPONSE_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|RDMA_READ_RESPONSE_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|ACKNOWLEDGE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|ATOMIC_ACKNOWLEDGE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|COMPARE_SWAP
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RC
comma
id|FETCH_ADD
)paren
comma
multiline_comment|/* UC */
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|SEND_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|SEND_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|SEND_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|SEND_LAST_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|SEND_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|SEND_ONLY_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|RDMA_WRITE_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|RDMA_WRITE_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|RDMA_WRITE_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|RDMA_WRITE_LAST_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|RDMA_WRITE_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UC
comma
id|RDMA_WRITE_ONLY_WITH_IMMEDIATE
)paren
comma
multiline_comment|/* RD */
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|SEND_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|SEND_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|SEND_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|SEND_LAST_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|SEND_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|SEND_ONLY_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_WRITE_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_WRITE_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_WRITE_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_WRITE_LAST_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_WRITE_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_WRITE_ONLY_WITH_IMMEDIATE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_READ_REQUEST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_READ_RESPONSE_FIRST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_READ_RESPONSE_MIDDLE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_READ_RESPONSE_LAST
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|RDMA_READ_RESPONSE_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|ACKNOWLEDGE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|ATOMIC_ACKNOWLEDGE
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|COMPARE_SWAP
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|RD
comma
id|FETCH_ADD
)paren
comma
multiline_comment|/* UD */
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UD
comma
id|SEND_ONLY
)paren
comma
DECL|enumerator|IB_OPCODE
id|IB_OPCODE
c_func
(paren
id|UD
comma
id|SEND_ONLY_WITH_IMMEDIATE
)paren
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IB_LNH_RAW
id|IB_LNH_RAW
op_assign
l_int|0
comma
DECL|enumerator|IB_LNH_IP
id|IB_LNH_IP
op_assign
l_int|1
comma
DECL|enumerator|IB_LNH_IBA_LOCAL
id|IB_LNH_IBA_LOCAL
op_assign
l_int|2
comma
DECL|enumerator|IB_LNH_IBA_GLOBAL
id|IB_LNH_IBA_GLOBAL
op_assign
l_int|3
)brace
suffix:semicolon
DECL|struct|ib_unpacked_lrh
r_struct
id|ib_unpacked_lrh
(brace
DECL|member|virtual_lane
id|u8
id|virtual_lane
suffix:semicolon
DECL|member|link_version
id|u8
id|link_version
suffix:semicolon
DECL|member|service_level
id|u8
id|service_level
suffix:semicolon
DECL|member|link_next_header
id|u8
id|link_next_header
suffix:semicolon
DECL|member|destination_lid
id|__be16
id|destination_lid
suffix:semicolon
DECL|member|packet_length
id|__be16
id|packet_length
suffix:semicolon
DECL|member|source_lid
id|__be16
id|source_lid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ib_unpacked_grh
r_struct
id|ib_unpacked_grh
(brace
DECL|member|ip_version
id|u8
id|ip_version
suffix:semicolon
DECL|member|traffic_class
id|u8
id|traffic_class
suffix:semicolon
DECL|member|flow_label
id|__be32
id|flow_label
suffix:semicolon
DECL|member|payload_length
id|__be16
id|payload_length
suffix:semicolon
DECL|member|next_header
id|u8
id|next_header
suffix:semicolon
DECL|member|hop_limit
id|u8
id|hop_limit
suffix:semicolon
DECL|member|source_gid
r_union
id|ib_gid
id|source_gid
suffix:semicolon
DECL|member|destination_gid
r_union
id|ib_gid
id|destination_gid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ib_unpacked_bth
r_struct
id|ib_unpacked_bth
(brace
DECL|member|opcode
id|u8
id|opcode
suffix:semicolon
DECL|member|solicited_event
id|u8
id|solicited_event
suffix:semicolon
DECL|member|mig_req
id|u8
id|mig_req
suffix:semicolon
DECL|member|pad_count
id|u8
id|pad_count
suffix:semicolon
DECL|member|transport_header_version
id|u8
id|transport_header_version
suffix:semicolon
DECL|member|pkey
id|__be16
id|pkey
suffix:semicolon
DECL|member|destination_qpn
id|__be32
id|destination_qpn
suffix:semicolon
DECL|member|ack_req
id|u8
id|ack_req
suffix:semicolon
DECL|member|psn
id|__be32
id|psn
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ib_unpacked_deth
r_struct
id|ib_unpacked_deth
(brace
DECL|member|qkey
id|__be32
id|qkey
suffix:semicolon
DECL|member|source_qpn
id|__be32
id|source_qpn
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ib_ud_header
r_struct
id|ib_ud_header
(brace
DECL|member|lrh
r_struct
id|ib_unpacked_lrh
id|lrh
suffix:semicolon
DECL|member|grh_present
r_int
id|grh_present
suffix:semicolon
DECL|member|grh
r_struct
id|ib_unpacked_grh
id|grh
suffix:semicolon
DECL|member|bth
r_struct
id|ib_unpacked_bth
id|bth
suffix:semicolon
DECL|member|deth
r_struct
id|ib_unpacked_deth
id|deth
suffix:semicolon
DECL|member|immediate_present
r_int
id|immediate_present
suffix:semicolon
DECL|member|immediate_data
id|__be32
id|immediate_data
suffix:semicolon
)brace
suffix:semicolon
r_void
id|ib_pack
c_func
(paren
r_const
r_struct
id|ib_field
op_star
id|desc
comma
r_int
id|desc_len
comma
r_void
op_star
id|structure
comma
r_void
op_star
id|buf
)paren
suffix:semicolon
r_void
id|ib_unpack
c_func
(paren
r_const
r_struct
id|ib_field
op_star
id|desc
comma
r_int
id|desc_len
comma
r_void
op_star
id|buf
comma
r_void
op_star
id|structure
)paren
suffix:semicolon
r_void
id|ib_ud_header_init
c_func
(paren
r_int
id|payload_bytes
comma
r_int
id|grh_present
comma
r_struct
id|ib_ud_header
op_star
id|header
)paren
suffix:semicolon
r_int
id|ib_ud_header_pack
c_func
(paren
r_struct
id|ib_ud_header
op_star
id|header
comma
r_void
op_star
id|buf
)paren
suffix:semicolon
r_int
id|ib_ud_header_unpack
c_func
(paren
r_void
op_star
id|buf
comma
r_struct
id|ib_ud_header
op_star
id|header
)paren
suffix:semicolon
macro_line|#endif /* IB_PACK_H */
eof
