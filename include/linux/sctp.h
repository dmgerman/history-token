multiline_comment|/* SCTP kernel reference Implementation&n; * (C) Copyright IBM Corp. 2001, 2003&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * Various protocol defined structures.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developerst@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm &lt;jgrimm@us.ibm.com&gt;&n; *    Xingang Guo &lt;xingang.guo@intel.com&gt;&n; *    randall@sctp.chicago.il.us&n; *    kmorneau@cisco.com&n; *    qxie1@email.mot.com&n; *    Sridhar Samudrala &lt;sri@us.ibm.com&gt;&n; *    Kevin Gao &lt;kevin.gao@intel.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#ifndef __LINUX_SCTP_H__
DECL|macro|__LINUX_SCTP_H__
mdefine_line|#define __LINUX_SCTP_H__
macro_line|#include &lt;linux/in.h&gt;&t;&t;/* We need in_addr.  */
macro_line|#include &lt;linux/in6.h&gt;&t;&t;/* We need in6_addr.  */
multiline_comment|/* Section 3.1.  SCTP Common Header Format */
DECL|struct|sctphdr
r_typedef
r_struct
id|sctphdr
(brace
DECL|member|source
id|__u16
id|source
suffix:semicolon
DECL|member|dest
id|__u16
id|dest
suffix:semicolon
DECL|member|vtag
id|__u32
id|vtag
suffix:semicolon
DECL|member|checksum
id|__u32
id|checksum
suffix:semicolon
DECL|typedef|sctp_sctphdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_sctphdr_t
suffix:semicolon
multiline_comment|/* Section 3.2.  Chunk Field Descriptions. */
DECL|struct|sctp_chunkhdr
r_typedef
r_struct
id|sctp_chunkhdr
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|typedef|sctp_chunkhdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_chunkhdr_t
suffix:semicolon
multiline_comment|/* Section 3.2.  Chunk Type Values.&n; * [Chunk Type] identifies the type of information contained in the Chunk&n; * Value field. It takes a value from 0 to 254. The value of 255 is&n; * reserved for future use as an extension field.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_CID_DATA
id|SCTP_CID_DATA
op_assign
l_int|0
comma
DECL|enumerator|SCTP_CID_INIT
id|SCTP_CID_INIT
op_assign
l_int|1
comma
DECL|enumerator|SCTP_CID_INIT_ACK
id|SCTP_CID_INIT_ACK
op_assign
l_int|2
comma
DECL|enumerator|SCTP_CID_SACK
id|SCTP_CID_SACK
op_assign
l_int|3
comma
DECL|enumerator|SCTP_CID_HEARTBEAT
id|SCTP_CID_HEARTBEAT
op_assign
l_int|4
comma
DECL|enumerator|SCTP_CID_HEARTBEAT_ACK
id|SCTP_CID_HEARTBEAT_ACK
op_assign
l_int|5
comma
DECL|enumerator|SCTP_CID_ABORT
id|SCTP_CID_ABORT
op_assign
l_int|6
comma
DECL|enumerator|SCTP_CID_SHUTDOWN
id|SCTP_CID_SHUTDOWN
op_assign
l_int|7
comma
DECL|enumerator|SCTP_CID_SHUTDOWN_ACK
id|SCTP_CID_SHUTDOWN_ACK
op_assign
l_int|8
comma
DECL|enumerator|SCTP_CID_ERROR
id|SCTP_CID_ERROR
op_assign
l_int|9
comma
DECL|enumerator|SCTP_CID_COOKIE_ECHO
id|SCTP_CID_COOKIE_ECHO
op_assign
l_int|10
comma
DECL|enumerator|SCTP_CID_COOKIE_ACK
id|SCTP_CID_COOKIE_ACK
op_assign
l_int|11
comma
DECL|enumerator|SCTP_CID_ECN_ECNE
id|SCTP_CID_ECN_ECNE
op_assign
l_int|12
comma
DECL|enumerator|SCTP_CID_ECN_CWR
id|SCTP_CID_ECN_CWR
op_assign
l_int|13
comma
DECL|enumerator|SCTP_CID_SHUTDOWN_COMPLETE
id|SCTP_CID_SHUTDOWN_COMPLETE
op_assign
l_int|14
comma
multiline_comment|/* Use hex, as defined in ADDIP sec. 3.1 */
DECL|enumerator|SCTP_CID_ASCONF
id|SCTP_CID_ASCONF
op_assign
l_int|0xC1
comma
DECL|enumerator|SCTP_CID_ASCONF_ACK
id|SCTP_CID_ASCONF_ACK
op_assign
l_int|0x80
comma
DECL|typedef|sctp_cid_t
)brace
id|sctp_cid_t
suffix:semicolon
multiline_comment|/* enum */
multiline_comment|/* Section 3.2&n; *  Chunk Types are encoded such that the highest-order two bits specify&n; *  the action that must be taken if the processing endpoint does not&n; *  recognize the Chunk Type.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_CID_ACTION_DISCARD
id|SCTP_CID_ACTION_DISCARD
op_assign
l_int|0x00
comma
DECL|enumerator|SCTP_CID_ACTION_DISCARD_ERR
id|SCTP_CID_ACTION_DISCARD_ERR
op_assign
l_int|0x40
comma
DECL|enumerator|SCTP_CID_ACTION_SKIP
id|SCTP_CID_ACTION_SKIP
op_assign
l_int|0x80
comma
DECL|enumerator|SCTP_CID_ACTION_SKIP_ERR
id|SCTP_CID_ACTION_SKIP_ERR
op_assign
l_int|0xc0
comma
DECL|typedef|sctp_cid_action_t
)brace
id|sctp_cid_action_t
suffix:semicolon
DECL|enumerator|SCTP_CID_ACTION_MASK
r_enum
(brace
id|SCTP_CID_ACTION_MASK
op_assign
l_int|0xc0
comma
)brace
suffix:semicolon
multiline_comment|/* This flag is used in Chunk Flags for ABORT and SHUTDOWN COMPLETE.&n; *&n; * 3.3.7 Abort Association (ABORT) (6):&n; *    The T bit is set to 0 if the sender had a TCB that it destroyed.&n; *    If the sender did not have a TCB it should set this bit to 1.&n; */
DECL|enumerator|SCTP_CHUNK_FLAG_T
r_enum
(brace
id|SCTP_CHUNK_FLAG_T
op_assign
l_int|0x01
)brace
suffix:semicolon
multiline_comment|/*&n; *  Set the T bit&n; *&n; *      0                   1                   2                   3&n; *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1&n; *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *     |   Type = 14   |Reserved     |T|      Length = 4               |&n; *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&n; * Chunk Flags: 8 bits&n; *&n; *   Reserved:  7 bits&n; *     Set to 0 on transmit and ignored on receipt.&n; *&n; *   T bit:  1 bit&n; *     The T bit is set to 0 if the sender had a TCB that it destroyed. If&n; *     the sender did NOT have a TCB it should set this bit to 1.&n; *&n; * Note: Special rules apply to this chunk for verification, please&n; * see Section 8.5.1 for details.&n; */
DECL|macro|sctp_test_T_bit
mdefine_line|#define sctp_test_T_bit(c)    ((c)-&gt;chunk_hdr-&gt;flags &amp; SCTP_CHUNK_FLAG_T)
multiline_comment|/* RFC 2960&n; * Section 3.2.1 Optional/Variable-length Parmaeter Format.&n; */
DECL|struct|sctp_paramhdr
r_typedef
r_struct
id|sctp_paramhdr
(brace
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|typedef|sctp_paramhdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_paramhdr_t
suffix:semicolon
r_typedef
r_enum
(brace
multiline_comment|/* RFC 2960 Section 3.3.5 */
DECL|enumerator|SCTP_PARAM_HEARTBEAT_INFO
id|SCTP_PARAM_HEARTBEAT_INFO
op_assign
id|__constant_htons
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* RFC 2960 Section 3.3.2.1 */
DECL|enumerator|SCTP_PARAM_IPV4_ADDRESS
id|SCTP_PARAM_IPV4_ADDRESS
op_assign
id|__constant_htons
c_func
(paren
l_int|5
)paren
comma
DECL|enumerator|SCTP_PARAM_IPV6_ADDRESS
id|SCTP_PARAM_IPV6_ADDRESS
op_assign
id|__constant_htons
c_func
(paren
l_int|6
)paren
comma
DECL|enumerator|SCTP_PARAM_STATE_COOKIE
id|SCTP_PARAM_STATE_COOKIE
op_assign
id|__constant_htons
c_func
(paren
l_int|7
)paren
comma
DECL|enumerator|SCTP_PARAM_UNRECOGNIZED_PARAMETERS
id|SCTP_PARAM_UNRECOGNIZED_PARAMETERS
op_assign
id|__constant_htons
c_func
(paren
l_int|8
)paren
comma
DECL|enumerator|SCTP_PARAM_COOKIE_PRESERVATIVE
id|SCTP_PARAM_COOKIE_PRESERVATIVE
op_assign
id|__constant_htons
c_func
(paren
l_int|9
)paren
comma
DECL|enumerator|SCTP_PARAM_HOST_NAME_ADDRESS
id|SCTP_PARAM_HOST_NAME_ADDRESS
op_assign
id|__constant_htons
c_func
(paren
l_int|11
)paren
comma
DECL|enumerator|SCTP_PARAM_SUPPORTED_ADDRESS_TYPES
id|SCTP_PARAM_SUPPORTED_ADDRESS_TYPES
op_assign
id|__constant_htons
c_func
(paren
l_int|12
)paren
comma
DECL|enumerator|SCTP_PARAM_ECN_CAPABLE
id|SCTP_PARAM_ECN_CAPABLE
op_assign
id|__constant_htons
c_func
(paren
l_int|0x8000
)paren
comma
multiline_comment|/* Add-IP Extension. Section 3.2 */
DECL|enumerator|SCTP_PARAM_ADD_IP
id|SCTP_PARAM_ADD_IP
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc001
)paren
comma
DECL|enumerator|SCTP_PARAM_DEL_IP
id|SCTP_PARAM_DEL_IP
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc002
)paren
comma
DECL|enumerator|SCTP_PARAM_ERR_CAUSE
id|SCTP_PARAM_ERR_CAUSE
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc003
)paren
comma
DECL|enumerator|SCTP_PARAM_SET_PRIMARY
id|SCTP_PARAM_SET_PRIMARY
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc004
)paren
comma
DECL|enumerator|SCTP_PARAM_SUCCESS_REPORT
id|SCTP_PARAM_SUCCESS_REPORT
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc005
)paren
comma
DECL|enumerator|SCTP_PARAM_ADAPTION_LAYER_IND
id|SCTP_PARAM_ADAPTION_LAYER_IND
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc006
)paren
comma
DECL|typedef|sctp_param_t
)brace
id|sctp_param_t
suffix:semicolon
multiline_comment|/* enum */
multiline_comment|/* RFC 2960 Section 3.2.1&n; *  The Parameter Types are encoded such that the highest-order two bits&n; *  specify the action that must be taken if the processing endpoint does&n; *  not recognize the Parameter Type.&n; *&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_PARAM_ACTION_DISCARD
id|SCTP_PARAM_ACTION_DISCARD
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0000
)paren
comma
DECL|enumerator|SCTP_PARAM_ACTION_DISCARD_ERR
id|SCTP_PARAM_ACTION_DISCARD_ERR
op_assign
id|__constant_htons
c_func
(paren
l_int|0x4000
)paren
comma
DECL|enumerator|SCTP_PARAM_ACTION_SKIP
id|SCTP_PARAM_ACTION_SKIP
op_assign
id|__constant_htons
c_func
(paren
l_int|0x8000
)paren
comma
DECL|enumerator|SCTP_PARAM_ACTION_SKIP_ERR
id|SCTP_PARAM_ACTION_SKIP_ERR
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc000
)paren
comma
DECL|typedef|sctp_param_action_t
)brace
id|sctp_param_action_t
suffix:semicolon
DECL|enumerator|SCTP_PARAM_ACTION_MASK
r_enum
(brace
id|SCTP_PARAM_ACTION_MASK
op_assign
id|__constant_htons
c_func
(paren
l_int|0xc000
)paren
comma
)brace
suffix:semicolon
multiline_comment|/* RFC 2960 Section 3.3.1 Payload Data (DATA) (0) */
DECL|struct|sctp_datahdr
r_typedef
r_struct
id|sctp_datahdr
(brace
DECL|member|tsn
id|__u32
id|tsn
suffix:semicolon
DECL|member|stream
id|__u16
id|stream
suffix:semicolon
DECL|member|ssn
id|__u16
id|ssn
suffix:semicolon
DECL|member|ppid
id|__u32
id|ppid
suffix:semicolon
DECL|member|payload
id|__u8
id|payload
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_datahdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_datahdr_t
suffix:semicolon
DECL|struct|sctp_data_chunk
r_typedef
r_struct
id|sctp_data_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|data_hdr
id|sctp_datahdr_t
id|data_hdr
suffix:semicolon
DECL|typedef|sctp_data_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_data_chunk_t
suffix:semicolon
multiline_comment|/* DATA Chuck Specific Flags */
r_enum
(brace
DECL|enumerator|SCTP_DATA_MIDDLE_FRAG
id|SCTP_DATA_MIDDLE_FRAG
op_assign
l_int|0x00
comma
DECL|enumerator|SCTP_DATA_LAST_FRAG
id|SCTP_DATA_LAST_FRAG
op_assign
l_int|0x01
comma
DECL|enumerator|SCTP_DATA_FIRST_FRAG
id|SCTP_DATA_FIRST_FRAG
op_assign
l_int|0x02
comma
DECL|enumerator|SCTP_DATA_NOT_FRAG
id|SCTP_DATA_NOT_FRAG
op_assign
l_int|0x03
comma
DECL|enumerator|SCTP_DATA_UNORDERED
id|SCTP_DATA_UNORDERED
op_assign
l_int|0x04
comma
)brace
suffix:semicolon
DECL|enumerator|SCTP_DATA_FRAG_MASK
r_enum
(brace
id|SCTP_DATA_FRAG_MASK
op_assign
l_int|0x03
comma
)brace
suffix:semicolon
multiline_comment|/* RFC 2960 Section 3.3.2 Initiation (INIT) (1)&n; *&n; *  This chunk is used to initiate a SCTP association between two&n; *  endpoints.&n; */
DECL|struct|sctp_inithdr
r_typedef
r_struct
id|sctp_inithdr
(brace
DECL|member|init_tag
id|__u32
id|init_tag
suffix:semicolon
DECL|member|a_rwnd
id|__u32
id|a_rwnd
suffix:semicolon
DECL|member|num_outbound_streams
id|__u16
id|num_outbound_streams
suffix:semicolon
DECL|member|num_inbound_streams
id|__u16
id|num_inbound_streams
suffix:semicolon
DECL|member|initial_tsn
id|__u32
id|initial_tsn
suffix:semicolon
DECL|member|params
id|__u8
id|params
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_inithdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_inithdr_t
suffix:semicolon
DECL|struct|sctp_init_chunk
r_typedef
r_struct
id|sctp_init_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|init_hdr
id|sctp_inithdr_t
id|init_hdr
suffix:semicolon
DECL|typedef|sctp_init_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_init_chunk_t
suffix:semicolon
multiline_comment|/* Section 3.3.2.1. IPv4 Address Parameter (5) */
DECL|struct|sctp_ipv4addr_param
r_typedef
r_struct
id|sctp_ipv4addr_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|member|addr
r_struct
id|in_addr
id|addr
suffix:semicolon
DECL|typedef|sctp_ipv4addr_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_ipv4addr_param_t
suffix:semicolon
multiline_comment|/* Section 3.3.2.1. IPv6 Address Parameter (6) */
DECL|struct|sctp_ipv6addr_param
r_typedef
r_struct
id|sctp_ipv6addr_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|member|addr
r_struct
id|in6_addr
id|addr
suffix:semicolon
DECL|typedef|sctp_ipv6addr_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_ipv6addr_param_t
suffix:semicolon
multiline_comment|/* Section 3.3.2.1 Cookie Preservative (9) */
DECL|struct|sctp_cookie_preserve_param
r_typedef
r_struct
id|sctp_cookie_preserve_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|member|lifespan_increment
r_uint32
id|lifespan_increment
suffix:semicolon
DECL|typedef|sctp_cookie_preserve_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_cookie_preserve_param_t
suffix:semicolon
multiline_comment|/* Section 3.3.2.1 Host Name Address (11) */
DECL|struct|sctp_hostname_param
r_typedef
r_struct
id|sctp_hostname_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|member|hostname
r_uint8
id|hostname
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_hostname_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_hostname_param_t
suffix:semicolon
multiline_comment|/* Section 3.3.2.1 Supported Address Types (12) */
DECL|struct|sctp_supported_addrs_param
r_typedef
r_struct
id|sctp_supported_addrs_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|member|types
r_uint16
id|types
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_supported_addrs_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_supported_addrs_param_t
suffix:semicolon
multiline_comment|/* Appendix A. ECN Capable (32768) */
DECL|struct|sctp_ecn_capable_param
r_typedef
r_struct
id|sctp_ecn_capable_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|typedef|sctp_ecn_capable_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_ecn_capable_param_t
suffix:semicolon
multiline_comment|/* RFC 2960.  Section 3.3.3 Initiation Acknowledgement (INIT ACK) (2):&n; *   The INIT ACK chunk is used to acknowledge the initiation of an SCTP&n; *   association.&n; */
DECL|typedef|sctp_initack_chunk_t
r_typedef
id|sctp_init_chunk_t
id|sctp_initack_chunk_t
suffix:semicolon
multiline_comment|/* Section 3.3.3.1 State Cookie (7) */
DECL|struct|sctp_cookie_param
r_typedef
r_struct
id|sctp_cookie_param
(brace
DECL|member|p
id|sctp_paramhdr_t
id|p
suffix:semicolon
DECL|member|body
id|__u8
id|body
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_cookie_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_cookie_param_t
suffix:semicolon
multiline_comment|/* Section 3.3.3.1 Unrecognized Parameters (8) */
DECL|struct|sctp_unrecognized_param
r_typedef
r_struct
id|sctp_unrecognized_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|member|unrecognized
id|sctp_paramhdr_t
id|unrecognized
suffix:semicolon
DECL|typedef|sctp_unrecognized_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_unrecognized_param_t
suffix:semicolon
multiline_comment|/*&n; * 3.3.4 Selective Acknowledgement (SACK) (3):&n; *&n; *  This chunk is sent to the peer endpoint to acknowledge received DATA&n; *  chunks and to inform the peer endpoint of gaps in the received&n; *  subsequences of DATA chunks as represented by their TSNs.&n; */
DECL|struct|sctp_gap_ack_block
r_typedef
r_struct
id|sctp_gap_ack_block
(brace
DECL|member|start
id|__u16
id|start
suffix:semicolon
DECL|member|end
id|__u16
id|end
suffix:semicolon
DECL|typedef|sctp_gap_ack_block_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_gap_ack_block_t
suffix:semicolon
DECL|typedef|sctp_dup_tsn_t
r_typedef
r_uint32
id|sctp_dup_tsn_t
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|gab
id|sctp_gap_ack_block_t
id|gab
suffix:semicolon
DECL|member|dup
id|sctp_dup_tsn_t
id|dup
suffix:semicolon
DECL|typedef|sctp_sack_variable_t
)brace
id|sctp_sack_variable_t
suffix:semicolon
DECL|struct|sctp_sackhdr
r_typedef
r_struct
id|sctp_sackhdr
(brace
DECL|member|cum_tsn_ack
id|__u32
id|cum_tsn_ack
suffix:semicolon
DECL|member|a_rwnd
id|__u32
id|a_rwnd
suffix:semicolon
DECL|member|num_gap_ack_blocks
id|__u16
id|num_gap_ack_blocks
suffix:semicolon
DECL|member|num_dup_tsns
id|__u16
id|num_dup_tsns
suffix:semicolon
DECL|member|variable
id|sctp_sack_variable_t
id|variable
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_sackhdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_sackhdr_t
suffix:semicolon
DECL|struct|sctp_sack_chunk
r_typedef
r_struct
id|sctp_sack_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|sack_hdr
id|sctp_sackhdr_t
id|sack_hdr
suffix:semicolon
DECL|typedef|sctp_sack_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_sack_chunk_t
suffix:semicolon
multiline_comment|/* RFC 2960.  Section 3.3.5 Heartbeat Request (HEARTBEAT) (4):&n; *&n; *  An endpoint should send this chunk to its peer endpoint to probe the&n; *  reachability of a particular destination transport address defined in&n; *  the present association.&n; */
DECL|struct|sctp_heartbeathdr
r_typedef
r_struct
id|sctp_heartbeathdr
(brace
DECL|member|info
id|sctp_paramhdr_t
id|info
suffix:semicolon
DECL|typedef|sctp_heartbeathdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_heartbeathdr_t
suffix:semicolon
DECL|struct|sctp_heartbeat_chunk
r_typedef
r_struct
id|sctp_heartbeat_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|hb_hdr
id|sctp_heartbeathdr_t
id|hb_hdr
suffix:semicolon
DECL|typedef|sctp_heartbeat_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_heartbeat_chunk_t
suffix:semicolon
multiline_comment|/* For the abort and shutdown ACK we must carry the init tag in the&n; * common header. Just the common header is all that is needed with a&n; * chunk descriptor.&n; */
DECL|struct|sctp_abort_chunk
r_typedef
r_struct
id|sctp_abort_chunk
(brace
DECL|member|uh
id|sctp_chunkhdr_t
id|uh
suffix:semicolon
DECL|typedef|sctp_abort_chunkt_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_abort_chunkt_t
suffix:semicolon
multiline_comment|/* For the graceful shutdown we must carry the tag (in common header)&n; * and the highest consecutive acking value.&n; */
DECL|struct|sctp_shutdownhdr
r_typedef
r_struct
id|sctp_shutdownhdr
(brace
DECL|member|cum_tsn_ack
id|__u32
id|cum_tsn_ack
suffix:semicolon
DECL|typedef|sctp_shutdownhdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_shutdownhdr_t
suffix:semicolon
DECL|struct|sctp_shutdown_chunk_t
r_struct
id|sctp_shutdown_chunk_t
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|shutdown_hdr
id|sctp_shutdownhdr_t
id|shutdown_hdr
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* RFC 2960.  Section 3.3.10 Operation Error (ERROR) (9) */
DECL|struct|sctp_errhdr
r_typedef
r_struct
id|sctp_errhdr
(brace
DECL|member|cause
id|__u16
id|cause
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|variable
id|__u8
id|variable
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_errhdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_errhdr_t
suffix:semicolon
DECL|struct|sctp_operr_chunk
r_typedef
r_struct
id|sctp_operr_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|err_hdr
id|sctp_errhdr_t
id|err_hdr
suffix:semicolon
DECL|typedef|sctp_operr_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_operr_chunk_t
suffix:semicolon
multiline_comment|/* RFC 2960 3.3.10 - Operation Error&n; *&n; * Cause Code: 16 bits (unsigned integer)&n; *&n; *     Defines the type of error conditions being reported.&n; *    Cause Code&n; *     Value           Cause Code&n; *     ---------      ----------------&n; *      1              Invalid Stream Identifier&n; *      2              Missing Mandatory Parameter&n; *      3              Stale Cookie Error&n; *      4              Out of Resource&n; *      5              Unresolvable Address&n; *      6              Unrecognized Chunk Type&n; *      7              Invalid Mandatory Parameter&n; *      8              Unrecognized Parameters&n; *      9              No User Data&n; *     10              Cookie Received While Shutting Down&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_ERROR_NO_ERROR
id|SCTP_ERROR_NO_ERROR
op_assign
id|__constant_htons
c_func
(paren
l_int|0x00
)paren
comma
DECL|enumerator|SCTP_ERROR_INV_STRM
id|SCTP_ERROR_INV_STRM
op_assign
id|__constant_htons
c_func
(paren
l_int|0x01
)paren
comma
DECL|enumerator|SCTP_ERROR_MISS_PARAM
id|SCTP_ERROR_MISS_PARAM
op_assign
id|__constant_htons
c_func
(paren
l_int|0x02
)paren
comma
DECL|enumerator|SCTP_ERROR_STALE_COOKIE
id|SCTP_ERROR_STALE_COOKIE
op_assign
id|__constant_htons
c_func
(paren
l_int|0x03
)paren
comma
DECL|enumerator|SCTP_ERROR_NO_RESOURCE
id|SCTP_ERROR_NO_RESOURCE
op_assign
id|__constant_htons
c_func
(paren
l_int|0x04
)paren
comma
DECL|enumerator|SCTP_ERROR_DNS_FAILED
id|SCTP_ERROR_DNS_FAILED
op_assign
id|__constant_htons
c_func
(paren
l_int|0x05
)paren
comma
DECL|enumerator|SCTP_ERROR_UNKNOWN_CHUNK
id|SCTP_ERROR_UNKNOWN_CHUNK
op_assign
id|__constant_htons
c_func
(paren
l_int|0x06
)paren
comma
DECL|enumerator|SCTP_ERROR_INV_PARAM
id|SCTP_ERROR_INV_PARAM
op_assign
id|__constant_htons
c_func
(paren
l_int|0x07
)paren
comma
DECL|enumerator|SCTP_ERROR_UNKNOWN_PARAM
id|SCTP_ERROR_UNKNOWN_PARAM
op_assign
id|__constant_htons
c_func
(paren
l_int|0x08
)paren
comma
DECL|enumerator|SCTP_ERROR_NO_DATA
id|SCTP_ERROR_NO_DATA
op_assign
id|__constant_htons
c_func
(paren
l_int|0x09
)paren
comma
DECL|enumerator|SCTP_ERROR_COOKIE_IN_SHUTDOWN
id|SCTP_ERROR_COOKIE_IN_SHUTDOWN
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0a
)paren
comma
multiline_comment|/* SCTP Implementation Guide:&n;&t; *  11  Restart of an association with new addresses&n;&t; *  12  User Initiated Abort&n;&t; *  13  Protocol Violation&n;&t; */
DECL|enumerator|SCTP_ERROR_RESTART
id|SCTP_ERROR_RESTART
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0b
)paren
comma
DECL|enumerator|SCTP_ERROR_USER_ABORT
id|SCTP_ERROR_USER_ABORT
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0c
)paren
comma
DECL|enumerator|SCTP_ERROR_PROTO_VIOLATION
id|SCTP_ERROR_PROTO_VIOLATION
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0d
)paren
comma
multiline_comment|/* ADDIP Section 3.3  New Error Causes&n;&t; *&n;&t; * Four new Error Causes are added to the SCTP Operational Errors,&n;&t; * primarily for use in the ASCONF-ACK chunk.&n;&t; *&n;&t; * Value          Cause Code&n;&t; * ---------      ----------------&n;&t; * 0x0100          Request to Delete Last Remaining IP Address.&n;&t; * 0x0101          Operation Refused Due to Resource Shortage.&n;&t; * 0x0102          Request to Delete Source IP Address.&n;&t; * 0x0103          Association Aborted due to illegal ASCONF-ACK&n;&t; * 0x0104          Request refused - no authorization.&n;&t; */
DECL|enumerator|SCTP_ERROR_DEL_LAST_IP
id|SCTP_ERROR_DEL_LAST_IP
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0100
)paren
comma
DECL|enumerator|SCTP_ERROR_RSRC_LOW
id|SCTP_ERROR_RSRC_LOW
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0101
)paren
comma
DECL|enumerator|SCTP_ERROR_DEL_SRC_IP
id|SCTP_ERROR_DEL_SRC_IP
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0102
)paren
comma
DECL|enumerator|SCTP_ERROR_ASCONF_ACK
id|SCTP_ERROR_ASCONF_ACK
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0103
)paren
comma
DECL|enumerator|SCTP_ERROR_REQ_REFUSED
id|SCTP_ERROR_REQ_REFUSED
op_assign
id|__constant_htons
c_func
(paren
l_int|0x0104
)paren
DECL|typedef|sctp_error_t
)brace
id|sctp_error_t
suffix:semicolon
multiline_comment|/* RFC 2960.  Appendix A.  Explicit Congestion Notification.&n; *   Explicit Congestion Notification Echo (ECNE) (12)&n; */
DECL|struct|sctp_ecnehdr
r_typedef
r_struct
id|sctp_ecnehdr
(brace
DECL|member|lowest_tsn
id|__u32
id|lowest_tsn
suffix:semicolon
DECL|typedef|sctp_ecnehdr_t
)brace
id|sctp_ecnehdr_t
suffix:semicolon
DECL|struct|sctp_ecne_chunk
r_typedef
r_struct
id|sctp_ecne_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|ence_hdr
id|sctp_ecnehdr_t
id|ence_hdr
suffix:semicolon
DECL|typedef|sctp_ecne_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_ecne_chunk_t
suffix:semicolon
multiline_comment|/* RFC 2960.  Appendix A.  Explicit Congestion Notification.&n; *   Congestion Window Reduced (CWR) (13)&n; */
DECL|struct|sctp_cwrhdr
r_typedef
r_struct
id|sctp_cwrhdr
(brace
DECL|member|lowest_tsn
id|__u32
id|lowest_tsn
suffix:semicolon
DECL|typedef|sctp_cwrhdr_t
)brace
id|sctp_cwrhdr_t
suffix:semicolon
DECL|struct|sctp_cwr_chunk
r_typedef
r_struct
id|sctp_cwr_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|cwr_hdr
id|sctp_cwrhdr_t
id|cwr_hdr
suffix:semicolon
DECL|typedef|sctp_cwr_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_cwr_chunk_t
suffix:semicolon
multiline_comment|/*&n; * ADDIP Section 3.1 New Chunk Types&n; */
multiline_comment|/* ADDIP&n; * Section 3.1.1 Address Configuration Change Chunk (ASCONF)&n; *&n; * &t;Serial Number: 32 bits (unsigned integer)&n; *&t;This value represents a Serial Number for the ASCONF Chunk. The&n; *&t;valid range of Serial Number is from 0 to 2^32-1.&n; *&t;Serial Numbers wrap back to 0 after reaching 2^32 -1.&n; *&n; *&t;Address Parameter: 8 or 20 bytes (depending on type)&n; *&t;The address is an address of the sender of the ASCONF chunk,&n; *&t;the address MUST be considered part of the association by the&n; *&t;peer endpoint. This field may be used by the receiver of the &n; *&t;ASCONF to help in finding the association. This parameter MUST&n; *&t;be present in every ASCONF message i.e. it is a mandatory TLV&n; *&t;parameter.&n; *&n; *&t;ASCONF Parameter: TLV format&n; *&t;Each Address configuration change is represented by a TLV&n; *&t;parameter as defined in Section 3.2. One or more requests may&n; *&t;be present in an ASCONF Chunk.&n; *&n; * Section 3.1.2 Address Configuration Acknowledgement Chunk (ASCONF-ACK)&n; * &n; *&t;Serial Number: 32 bits (unsigned integer)&n; *&t;This value represents the Serial Number for the received ASCONF&n; *&t;Chunk that is acknowledged by this chunk. This value is copied&n; *&t;from the received ASCONF Chunk. &n; *&n; *&t;ASCONF Parameter Response: TLV format&n; *&t;The ASCONF Parameter Response is used in the ASCONF-ACK to&n; *&t;report status of ASCONF processing.&n; */
DECL|struct|sctp_addip_param
r_typedef
r_struct
id|sctp_addip_param
(brace
DECL|member|param_hdr
id|sctp_paramhdr_t
id|param_hdr
suffix:semicolon
DECL|member|crr_id
id|__u32
id|crr_id
suffix:semicolon
DECL|typedef|sctp_addip_param_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_addip_param_t
suffix:semicolon
DECL|struct|sctp_addiphdr
r_typedef
r_struct
id|sctp_addiphdr
(brace
DECL|member|serial
id|__u32
id|serial
suffix:semicolon
DECL|member|params
id|__u8
id|params
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_addiphdr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_addiphdr_t
suffix:semicolon
DECL|struct|sctp_addip_chunk
r_typedef
r_struct
id|sctp_addip_chunk
(brace
DECL|member|chunk_hdr
id|sctp_chunkhdr_t
id|chunk_hdr
suffix:semicolon
DECL|member|addip_hdr
id|sctp_addiphdr_t
id|addip_hdr
suffix:semicolon
DECL|typedef|sctp_addip_chunk_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|sctp_addip_chunk_t
suffix:semicolon
macro_line|#endif /* __LINUX_SCTP_H__ */
eof
