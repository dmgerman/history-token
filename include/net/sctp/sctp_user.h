multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 International Business Machines, Corp.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * $Header: /cvsroot/lksctp/lksctp/sctp_cvs/include/net/sctp/sctp_user.h,v 1.17 2002/07/29 21:04:23 jgrimm Exp $&n; * &n; * This header represents the structures and constants needed to support&n; * the SCTP Extension to the Sockets API. &n; * &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    La Monte H.P. Yarroll    &lt;piggy@acm.org&gt;&n; *    R. Stewart               &lt;randall@sctp.chicago.il.us&gt;&n; *    K. Morneau               &lt;kmorneau@cisco.com&gt;&n; *    Q. Xie                   &lt;qxie1@email.mot.com&gt;&n; *    Karl Knutson             &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm                &lt;jgrimm@us.ibm.com&gt;&n; *    Daisy Chang              &lt;daisyc@us.ibm.com&gt;&n; * &n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#ifndef __net_sctp_user_h__
DECL|macro|__net_sctp_user_h__
mdefine_line|#define __net_sctp_user_h__
DECL|typedef|sctp_assoc_t
r_typedef
r_void
op_star
id|sctp_assoc_t
suffix:semicolon
multiline_comment|/* The following symbols come from the Sockets API Extensions for&n; * SCTP &lt;draft-ietf-tsvwg-sctpsocket-04.txt&gt;.&n; */
DECL|enum|sctp_optname
r_enum
id|sctp_optname
(brace
DECL|enumerator|SCTP_RTOINFO
id|SCTP_RTOINFO
comma
DECL|macro|SCTP_RTOINFO
mdefine_line|#define SCTP_RTOINFO SCTP_RTOINFO
DECL|enumerator|SCTP_ASSOCRTXINFO
id|SCTP_ASSOCRTXINFO
comma
DECL|macro|SCTP_ASSOCRTXINFO
mdefine_line|#define SCTP_ASSOCRTXINFO SCTP_ASSOCRTXINFO
DECL|enumerator|SCTP_INITMSG
id|SCTP_INITMSG
comma
DECL|macro|SCTP_INITMSG
mdefine_line|#define SCTP_INITMSG SCTP_INITMSG
DECL|enumerator|SCTP_AUTO_CLOSE
id|SCTP_AUTO_CLOSE
comma
DECL|macro|SCTP_AUTO_CLOSE
mdefine_line|#define SCTP_AUTO_CLOSE SCTP_AUTO_CLOSE
DECL|enumerator|SCTP_SET_PRIMARY_ADDR
id|SCTP_SET_PRIMARY_ADDR
comma
DECL|macro|SCTP_SET_PRIMARY_ADDR
mdefine_line|#define SCTP_SET_PRIMARY_ADDR SCTP_SET_PRIMARY_ADDR
DECL|enumerator|SCTP_SET_PEER_PRIMARY_ADDR
id|SCTP_SET_PEER_PRIMARY_ADDR
comma
DECL|macro|SCTP_SET_PEER_PRIMARY_ADDR
mdefine_line|#define SCTP_SET_PEER_PRIMARY_ADDR SCTP_SET_PEER_PRIMARY_ADDR
DECL|enumerator|SCTP_SET_ADAPTATION_LAYER
id|SCTP_SET_ADAPTATION_LAYER
comma
DECL|macro|SCTP_SET_ADAPTATION_LAYER
mdefine_line|#define SCTP_SET_ADAPTATION_LAYER SCTP_SET_ADAPTATION_LAYER
DECL|enumerator|SCTP_SET_STREAM_TIMEOUTS
id|SCTP_SET_STREAM_TIMEOUTS
comma
DECL|macro|SCTP_SET_STREAM_TIMEOUTS
mdefine_line|#define SCTP_SET_STREAM_TIMEOUTS SCTP_SET_STREAM_TIMEOUTS
DECL|enumerator|SCTP_DISABLE_FRAGMENTS
id|SCTP_DISABLE_FRAGMENTS
comma
DECL|macro|SCTP_DISABLE_FRAGMENTS
mdefine_line|#define SCTP_DISABLE_FRAGMENTS SCTP_DISABLE_FRAGMENTS
DECL|enumerator|SCTP_SET_PEER_ADDR_PARAMS
id|SCTP_SET_PEER_ADDR_PARAMS
comma
DECL|macro|SCTP_SET_PEER_ADDR_PARAMS
mdefine_line|#define SCTP_SET_PEER_ADDR_PARAMS SCTP_SET_PEER_ADDR_PARAMS
DECL|enumerator|SCTP_GET_PEER_ADDR_PARAMS
id|SCTP_GET_PEER_ADDR_PARAMS
comma
DECL|macro|SCTP_GET_PEER_ADDR_PARAMS
mdefine_line|#define SCTP_GET_PEER_ADDR_PARAMS SCTP_GET_PEER_ADDR_PARAMS
DECL|enumerator|SCTP_STATUS
id|SCTP_STATUS
comma
DECL|macro|SCTP_STATUS
mdefine_line|#define SCTP_STATUS SCTP_STATUS
DECL|enumerator|SCTP_GET_PEER_ADDR_INFO
id|SCTP_GET_PEER_ADDR_INFO
comma
DECL|macro|SCTP_GET_PEER_ADDR_INFO
mdefine_line|#define SCTP_GET_PEER_ADDR_INFO SCTP_GET_PEER_ADDR_INFO
DECL|enumerator|SCTP_SET_EVENTS
id|SCTP_SET_EVENTS
comma
DECL|macro|SCTP_SET_EVENTS
mdefine_line|#define SCTP_SET_EVENTS SCTP_SET_EVENTS
DECL|enumerator|SCTP_AUTOCLOSE
id|SCTP_AUTOCLOSE
comma
DECL|macro|SCTP_AUTOCLOSE
mdefine_line|#define SCTP_AUTOCLOSE SCTP_AUTOCLOSE
DECL|enumerator|SCTP_SET_DEFAULT_SEND_PARAM
id|SCTP_SET_DEFAULT_SEND_PARAM
comma
DECL|macro|SCTP_SET_DEFAULT_SEND_PARAM
mdefine_line|#define SCTP_SET_DEFAULT_SEND_PARAM SCTP_SET_DEFAULT_SEND_PARAM
DECL|enumerator|SCTP_SOCKOPT_DEBUG_NAME
id|SCTP_SOCKOPT_DEBUG_NAME
op_assign
l_int|42
comma
multiline_comment|/* FIXME */
DECL|macro|SCTP_SOCKOPT_DEBUG_NAME
mdefine_line|#define SCTP_SOCKOPT_DEBUG_NAME&t;SCTP_SOCKOPT_DEBUG_NAME
DECL|enumerator|SCTP_SOCKOPT_BINDX_ADD
id|SCTP_SOCKOPT_BINDX_ADD
comma
multiline_comment|/* BINDX requests for adding addresses. */
DECL|macro|SCTP_SOCKOPT_BINDX_ADD
mdefine_line|#define SCTP_SOCKOPT_BINDX_ADD&t;SCTP_SOCKOPT_BINDX_ADD
DECL|enumerator|SCTP_SOCKOPT_BINDX_REM
id|SCTP_SOCKOPT_BINDX_REM
comma
multiline_comment|/* BINDX requests for removing addresses. */
DECL|macro|SCTP_SOCKOPT_BINDX_REM
mdefine_line|#define SCTP_SOCKOPT_BINDX_REM&t;SCTP_SOCKOPT_BINDX_REM
DECL|enumerator|SCTP_SOCKOPT_PEELOFF
id|SCTP_SOCKOPT_PEELOFF
comma
multiline_comment|/* peel off association. */
DECL|macro|SCTP_SOCKOPT_PEELOFF
mdefine_line|#define SCTP_SOCKOPT_PEELOFF&t;SCTP_SOCKOPT_PEELOFF
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.2 SCTP msg_control Structures&n; *&n; * A key element of all SCTP-specific socket extensions is the use of&n; * ancillary data to specify and access SCTP-specific data via the&n; * struct msghdr&squot;s msg_control member used in sendmsg() and recvmsg().&n; * Fine-grained control over initialization and sending parameters are&n; * handled with ancillary data.&n; *&n; * Each ancillary data item is preceeded by a struct cmsghdr (see&n; * Section 5.1), which defines the function and purpose of the data&n; * contained in in the cmsg_data[] member.&n; */
multiline_comment|/*&n; * 5.2.1 SCTP Initiation Structure (SCTP_INIT)&n; *&n; *   This cmsghdr structure provides information for initializing new&n; *   SCTP associations with sendmsg().  The SCTP_INITMSG socket option&n; *   uses this same data structure.  This structure is not used for&n; *   recvmsg().&n; *&n; *   cmsg_level    cmsg_type      cmsg_data[]&n; *   ------------  ------------   ----------------------&n; *   IPPROTO_SCTP  SCTP_INIT      struct sctp_initmsg&n; *&n; */
DECL|struct|sctp_initmsg
r_struct
id|sctp_initmsg
(brace
DECL|member|sinit_num_ostreams
id|__u16
id|sinit_num_ostreams
suffix:semicolon
DECL|member|sinit_max_instreams
id|__u16
id|sinit_max_instreams
suffix:semicolon
DECL|member|sinit_max_attempts
id|__u16
id|sinit_max_attempts
suffix:semicolon
DECL|member|sinit_max_init_timeo
id|__u16
id|sinit_max_init_timeo
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)&n; *&n; *   This cmsghdr structure specifies SCTP options for sendmsg() and&n; *   describes SCTP header information about a received message through&n; *   recvmsg().&n; *&n; *   cmsg_level    cmsg_type      cmsg_data[]&n; *   ------------  ------------   ----------------------&n; *   IPPROTO_SCTP  SCTP_SNDRCV    struct sctp_sndrcvinfo&n; *&n; */
DECL|struct|sctp_sndrcvinfo
r_struct
id|sctp_sndrcvinfo
(brace
DECL|member|sinfo_stream
id|__u16
id|sinfo_stream
suffix:semicolon
DECL|member|sinfo_ssn
id|__u16
id|sinfo_ssn
suffix:semicolon
DECL|member|sinfo_flags
id|__u16
id|sinfo_flags
suffix:semicolon
DECL|member|sinfo_ppid
id|__u32
id|sinfo_ppid
suffix:semicolon
DECL|member|sinfo_context
id|__u32
id|sinfo_context
suffix:semicolon
DECL|member|sinfo_timetolive
id|__u32
id|sinfo_timetolive
suffix:semicolon
DECL|member|sinfo_tsn
id|__u32
id|sinfo_tsn
suffix:semicolon
DECL|member|sinfo_assoc_id
id|sctp_assoc_t
id|sinfo_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  sinfo_flags: 16 bits (unsigned integer)&n; *&n; *   This field may contain any of the following flags and is composed of&n; *   a bitwise OR of these values.&n; */
DECL|enum|sctp_sinfo_flags
r_enum
id|sctp_sinfo_flags
(brace
DECL|enumerator|MSG_UNORDERED
id|MSG_UNORDERED
op_assign
l_int|1
comma
multiline_comment|/* Send/recieve message unordered. */
DECL|enumerator|MSG_ADDR_OVER
id|MSG_ADDR_OVER
op_assign
l_int|2
comma
multiline_comment|/* Override the primary destination. */
DECL|enumerator|MSG_ABORT
id|MSG_ABORT
op_assign
l_int|4
comma
multiline_comment|/* Send an ABORT message to the peer. */
multiline_comment|/* MSG_EOF is already defined per socket.h */
)brace
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|raw
id|__u8
id|raw
suffix:semicolon
DECL|member|init
r_struct
id|sctp_initmsg
id|init
suffix:semicolon
DECL|member|sndrcv
r_struct
id|sctp_sndrcvinfo
id|sndrcv
suffix:semicolon
DECL|typedef|sctp_cmsg_data_t
)brace
id|sctp_cmsg_data_t
suffix:semicolon
multiline_comment|/* These are cmsg_types.  */
DECL|enum|sctp_cmsg_type
r_typedef
r_enum
id|sctp_cmsg_type
(brace
DECL|enumerator|SCTP_INIT
id|SCTP_INIT
comma
multiline_comment|/* 5.2.1 SCTP Initiation Structure */
DECL|enumerator|SCTP_SNDRCV
id|SCTP_SNDRCV
comma
multiline_comment|/* 5.2.2 SCTP Header Information Structure */
DECL|typedef|sctp_cmsg_t
)brace
id|sctp_cmsg_t
suffix:semicolon
multiline_comment|/*&n; * 5.3.1.1 SCTP_ASSOC_CHANGE&n; *&n; *   Communication notifications inform the ULP that an SCTP association&n; *   has either begun or ended. The identifier for a new association is&n; *   provided by this notificaion. The notification information has the&n; *   following format:&n; *&n; */
DECL|struct|sctp_assoc_change
r_struct
id|sctp_assoc_change
(brace
DECL|member|sac_type
id|__u16
id|sac_type
suffix:semicolon
DECL|member|sac_flags
id|__u16
id|sac_flags
suffix:semicolon
DECL|member|sac_length
id|__u32
id|sac_length
suffix:semicolon
DECL|member|sac_state
id|__u16
id|sac_state
suffix:semicolon
DECL|member|sac_error
id|__u16
id|sac_error
suffix:semicolon
DECL|member|sac_outbound_streams
id|__u16
id|sac_outbound_streams
suffix:semicolon
DECL|member|sac_inbound_streams
id|__u16
id|sac_inbound_streams
suffix:semicolon
DECL|member|sac_assoc_id
id|sctp_assoc_t
id|sac_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *   sac_state: 32 bits (signed integer)&n; *&n; *   This field holds one of a number of values that communicate the&n; *   event that happened to the association.  They include:&n; *&n; *   Note:  The following state names deviate from the API draft as&n; *   the names clash too easily with other kernel symbols.&n; */
DECL|enum|sctp_sac_state
r_enum
id|sctp_sac_state
(brace
DECL|enumerator|SCTP_COMM_UP
id|SCTP_COMM_UP
comma
DECL|enumerator|SCTP_COMM_LOST
id|SCTP_COMM_LOST
comma
DECL|enumerator|SCTP_RESTART
id|SCTP_RESTART
comma
DECL|enumerator|SCTP_SHUTDOWN_COMP
id|SCTP_SHUTDOWN_COMP
comma
DECL|enumerator|SCTP_CANT_STR_ASSOC
id|SCTP_CANT_STR_ASSOC
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n; *&n; *   When a destination address on a multi-homed peer encounters a change&n; *   an interface details event is sent.  The information has the&n; *   following structure:&n; */
DECL|struct|sctp_paddr_change
r_struct
id|sctp_paddr_change
(brace
DECL|member|spc_type
id|__u16
id|spc_type
suffix:semicolon
DECL|member|spc_flags
id|__u16
id|spc_flags
suffix:semicolon
DECL|member|spc_length
id|__u32
id|spc_length
suffix:semicolon
DECL|member|spc_aaddr
r_struct
id|sockaddr_storage
id|spc_aaddr
suffix:semicolon
DECL|member|spc_state
r_int
id|spc_state
suffix:semicolon
DECL|member|spc_error
r_int
id|spc_error
suffix:semicolon
DECL|member|spc_assoc_id
id|sctp_assoc_t
id|spc_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *    spc_state:  32 bits (signed integer)&n; *&n; *   This field holds one of a number of values that communicate the&n; *   event that happened to the address.  They include:&n; */
DECL|enum|sctp_spc_state
r_enum
id|sctp_spc_state
(brace
DECL|enumerator|ADDRESS_AVAILABLE
id|ADDRESS_AVAILABLE
comma
DECL|enumerator|ADDRESS_UNREACHABLE
id|ADDRESS_UNREACHABLE
comma
DECL|enumerator|ADDRESS_REMOVED
id|ADDRESS_REMOVED
comma
DECL|enumerator|ADDRESS_ADDED
id|ADDRESS_ADDED
comma
DECL|enumerator|ADDRESS_MADE_PRIM
id|ADDRESS_MADE_PRIM
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.3.1.3 SCTP_REMOTE_ERROR&n; *&n; *   A remote peer may send an Operational Error message to its peer.&n; *   This message indicates a variety of error conditions on an&n; *   association. The entire error TLV as it appears on the wire is&n; *   included in a SCTP_REMOTE_ERROR event.  Please refer to the SCTP&n; *   specification [SCTP] and any extensions for a list of possible&n; *   error formats. SCTP error TLVs have the format:&n; */
DECL|struct|sctp_remote_error
r_struct
id|sctp_remote_error
(brace
DECL|member|sre_type
id|__u16
id|sre_type
suffix:semicolon
DECL|member|sre_flags
id|__u16
id|sre_flags
suffix:semicolon
DECL|member|sre_length
id|__u32
id|sre_length
suffix:semicolon
DECL|member|sre_error
id|__u16
id|sre_error
suffix:semicolon
DECL|member|sre_len
id|__u16
id|sre_len
suffix:semicolon
DECL|member|sre_assoc_id
id|sctp_assoc_t
id|sre_assoc_id
suffix:semicolon
DECL|member|sre_data
id|__u8
id|sre_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.3.1.4 SCTP_SEND_FAILED&n; *&n; *   If SCTP cannot deliver a message it may return the message as a&n; *   notification.&n; */
DECL|struct|sctp_send_failed
r_struct
id|sctp_send_failed
(brace
DECL|member|ssf_type
id|__u16
id|ssf_type
suffix:semicolon
DECL|member|ssf_flags
id|__u16
id|ssf_flags
suffix:semicolon
DECL|member|ssf_length
id|__u32
id|ssf_length
suffix:semicolon
DECL|member|ssf_error
id|__u32
id|ssf_error
suffix:semicolon
DECL|member|ssf_info
r_struct
id|sctp_sndrcvinfo
id|ssf_info
suffix:semicolon
DECL|member|ssf_assoc_id
id|sctp_assoc_t
id|ssf_assoc_id
suffix:semicolon
DECL|member|ssf_data
id|__u8
id|ssf_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *   ssf_flags: 16 bits (unsigned integer)&n; *&n; *   The flag value will take one of the following values&n; *&n; *   SCTP_DATA_UNSENT  - Indicates that the data was never put on&n; *                       the wire.&n; *&n; *   SCTP_DATA_SENT    - Indicates that the data was put on the wire.&n; *                       Note that this does not necessarily mean that the&n; *                       data was (or was not) successfully delivered.&n; */
DECL|enum|sctp_ssf_flags
r_enum
id|sctp_ssf_flags
(brace
DECL|enumerator|SCTP_DATA_UNSENT
id|SCTP_DATA_UNSENT
comma
DECL|enumerator|SCTP_DATA_SENT
id|SCTP_DATA_SENT
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.3.1.5 SCTP_SHUTDOWN_EVENT&n; *&n; *   When a peer sends a SHUTDOWN, SCTP delivers this notification to&n; *   inform the application that it should cease sending data.&n; */
DECL|struct|sctp_shutdown_event
r_struct
id|sctp_shutdown_event
(brace
DECL|member|sse_type
id|__u16
id|sse_type
suffix:semicolon
DECL|member|sse_flags
id|__u16
id|sse_flags
suffix:semicolon
DECL|member|sse_length
id|__u32
id|sse_length
suffix:semicolon
DECL|member|sse_assoc_id
id|sctp_assoc_t
id|sse_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.3.1.6 SCTP_ADAPTION_INDICATION&n; *&n; *   When a peer sends a Adaption Layer Indication parameter , SCTP&n; *   delivers this notification to inform the application&n; *   that of the peers requested adaption layer.&n; */
DECL|struct|sctp_adaption_event
r_struct
id|sctp_adaption_event
(brace
DECL|member|sai_type
id|__u16
id|sai_type
suffix:semicolon
DECL|member|sai_flags
id|__u16
id|sai_flags
suffix:semicolon
DECL|member|sai_length
id|__u32
id|sai_length
suffix:semicolon
DECL|member|sai_adaptation_bits
id|__u32
id|sai_adaptation_bits
suffix:semicolon
DECL|member|sse_assoc_id
id|sctp_assoc_t
id|sse_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.3.1.7 SCTP_PARTIAL_DELIVERY_EVENT&n; *&n; *   When a reciever is engaged in a partial delivery of a&n; *   message this notification will be used to inidicate&n; *   various events.&n; */
DECL|struct|sctp_rcv_pdapi_event
r_struct
id|sctp_rcv_pdapi_event
(brace
DECL|member|pdapi_type
id|__u16
id|pdapi_type
suffix:semicolon
DECL|member|pdapi_flags
id|__u16
id|pdapi_flags
suffix:semicolon
DECL|member|pdapi_length
id|__u32
id|pdapi_length
suffix:semicolon
DECL|member|pdapi_indication
id|__u32
id|pdapi_indication
suffix:semicolon
DECL|member|pdapi_assoc_id
id|sctp_assoc_t
id|pdapi_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Described in Section 7.3&n; *   Ancillary Data and Notification Interest Options&n; */
DECL|struct|sctp_event_subscribe
r_struct
id|sctp_event_subscribe
(brace
DECL|member|sctp_data_io_event
id|__u8
id|sctp_data_io_event
suffix:semicolon
DECL|member|sctp_association_event
id|__u8
id|sctp_association_event
suffix:semicolon
DECL|member|sctp_address_event
id|__u8
id|sctp_address_event
suffix:semicolon
DECL|member|sctp_send_failure_event
id|__u8
id|sctp_send_failure_event
suffix:semicolon
DECL|member|sctp_peer_error_event
id|__u8
id|sctp_peer_error_event
suffix:semicolon
DECL|member|sctp_shutdown_event
id|__u8
id|sctp_shutdown_event
suffix:semicolon
DECL|member|sctp_partial_delivery_event
id|__u8
id|sctp_partial_delivery_event
suffix:semicolon
DECL|member|sctp_adaption_layer_event
id|__u8
id|sctp_adaption_layer_event
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 5.3.1 SCTP Notification Structure&n; *&n; *   The notification structure is defined as the union of all&n; *   notification types.&n; *&n; */
DECL|union|sctp_notification
r_union
id|sctp_notification
(brace
r_struct
(brace
DECL|member|sn_type
id|__u16
id|sn_type
suffix:semicolon
multiline_comment|/* Notification type. */
DECL|member|sn_flags
id|__u16
id|sn_flags
suffix:semicolon
DECL|member|sn_length
id|__u32
id|sn_length
suffix:semicolon
DECL|member|h
)brace
id|h
suffix:semicolon
DECL|member|sn_assoc_change
r_struct
id|sctp_assoc_change
id|sn_assoc_change
suffix:semicolon
DECL|member|sn_padr_change
r_struct
id|sctp_paddr_change
id|sn_padr_change
suffix:semicolon
DECL|member|sn_remote_error
r_struct
id|sctp_remote_error
id|sn_remote_error
suffix:semicolon
DECL|member|sn_send_failed
r_struct
id|sctp_send_failed
id|sn_send_failed
suffix:semicolon
DECL|member|sn_shutdown_event
r_struct
id|sctp_shutdown_event
id|sn_shutdown_event
suffix:semicolon
DECL|member|sn_adaption_event
r_struct
id|sctp_adaption_event
id|sn_adaption_event
suffix:semicolon
DECL|member|sn_rcv_pdapi_event
r_struct
id|sctp_rcv_pdapi_event
id|sn_rcv_pdapi_event
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Section 5.3.1&n; * All standard values for sn_type flags are greater than 2^15.&n; * Values from 2^15 and down are reserved.&n; */
DECL|enum|sctp_sn_type
r_enum
id|sctp_sn_type
(brace
DECL|enumerator|SCTP_SN_TYPE_BASE
id|SCTP_SN_TYPE_BASE
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
comma
DECL|enumerator|SCTP_ASSOC_CHANGE
id|SCTP_ASSOC_CHANGE
comma
DECL|enumerator|SCTP_PEER_ADDR_CHANGE
id|SCTP_PEER_ADDR_CHANGE
comma
DECL|enumerator|SCTP_REMOTE_ERROR
id|SCTP_REMOTE_ERROR
comma
DECL|enumerator|SCTP_SEND_FAILED
id|SCTP_SEND_FAILED
comma
DECL|enumerator|SCTP_SHUTDOWN_EVENT
id|SCTP_SHUTDOWN_EVENT
comma
DECL|enumerator|SCTP_PARTIAL_DELIVERY_EVENT
id|SCTP_PARTIAL_DELIVERY_EVENT
comma
DECL|enumerator|SCTP_ADAPTION_INDICATION
id|SCTP_ADAPTION_INDICATION
comma
)brace
suffix:semicolon
multiline_comment|/* Notification error codes used to fill up the error fields in some&n; * notifications.&n; * SCTP_PEER_ADDRESS_CHAGE &t;: spc_error&n; * SCTP_ASSOC_CHANGE&t;&t;: sac_error&n; * These names should be potentially included in the draft 04 of the SCTP&n; * sockets API specification.&n; */
DECL|enum|sctp_sn_error
r_typedef
r_enum
id|sctp_sn_error
(brace
DECL|enumerator|SCTP_FAILED_THRESHOLD
id|SCTP_FAILED_THRESHOLD
comma
DECL|enumerator|SCTP_RECEIVED_SACK
id|SCTP_RECEIVED_SACK
comma
DECL|enumerator|SCTP_HEARTBEAT_SUCCESS
id|SCTP_HEARTBEAT_SUCCESS
comma
DECL|enumerator|SCTP_RESPONSE_TO_USER_REQ
id|SCTP_RESPONSE_TO_USER_REQ
comma
DECL|enumerator|SCTP_INTERNAL_ERROR
id|SCTP_INTERNAL_ERROR
comma
DECL|enumerator|SCTP_SHUTDOWN_GUARD_EXPIRES
id|SCTP_SHUTDOWN_GUARD_EXPIRES
comma
DECL|enumerator|SCTP_PEER_FAULTY
id|SCTP_PEER_FAULTY
comma
DECL|typedef|sctp_sn_error_t
)brace
id|sctp_sn_error_t
suffix:semicolon
multiline_comment|/*&n; *&n; * 7.1.14 Peer Address Parameters&n; *&n; *   Applications can enable or disable heartbeats for any peer address&n; *   of an association, modify an address&squot;s heartbeat interval, force a&n; *   heartbeat to be sent immediately, and adjust the address&squot;s maximum&n; *   number of retransmissions sent before an address is considered&n; *   unreachable. The following structure is used to access and modify an&n; *   address&squot;s parameters:&n; */
DECL|struct|sctp_paddrparams
r_struct
id|sctp_paddrparams
(brace
DECL|member|spp_address
r_struct
id|sockaddr_storage
id|spp_address
suffix:semicolon
DECL|member|spp_hbinterval
id|__u32
id|spp_hbinterval
suffix:semicolon
DECL|member|spp_pathmaxrxt
id|__u16
id|spp_pathmaxrxt
suffix:semicolon
DECL|member|spp_assoc_id
id|sctp_assoc_t
id|spp_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.2.2 Peer Address Information&n; *&n; *   Applications can retrieve information about a specific peer address&n; *   of an association, including its reachability state, congestion&n; *   window, and retransmission timer values.  This information is&n; *   read-only. The following structure is used to access this&n; *   information:&n; */
DECL|struct|sctp_paddrinfo
r_struct
id|sctp_paddrinfo
(brace
DECL|member|spinfo_assoc_id
id|sctp_assoc_t
id|spinfo_assoc_id
suffix:semicolon
DECL|member|spinfo_address
r_struct
id|sockaddr_storage
id|spinfo_address
suffix:semicolon
DECL|member|spinfo_state
id|__s32
id|spinfo_state
suffix:semicolon
DECL|member|spinfo_cwnd
id|__u32
id|spinfo_cwnd
suffix:semicolon
DECL|member|spinfo_srtt
id|__u32
id|spinfo_srtt
suffix:semicolon
DECL|member|spinfo_rto
id|__u32
id|spinfo_rto
suffix:semicolon
DECL|member|spinfo_mtu
id|__u32
id|spinfo_mtu
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.1.1 Retransmission Timeout Parameters (SCTP_RTOINFO)&n; *&n; *   The protocol parameters used to initialize and bound retransmission&n; *   timeout (RTO) are tunable.  See [SCTP] for more information on how&n; *   these parameters are used in RTO calculation.  The peer address&n; *   parameter is ignored for TCP style socket.&n; */
DECL|struct|sctp_rtoinfo
r_struct
id|sctp_rtoinfo
(brace
DECL|member|srto_initial
id|__u32
id|srto_initial
suffix:semicolon
DECL|member|srto_max
id|__u32
id|srto_max
suffix:semicolon
DECL|member|srto_min
id|__u32
id|srto_min
suffix:semicolon
DECL|member|srto_assoc_id
id|sctp_assoc_t
id|srto_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.1.2 Association Retransmission Parameter (SCTP_ASSOCRTXINFO)&n; *&n; *   The protocol parameter used to set the number of retransmissions&n; *   sent before an association is considered unreachable.&n; *   See [SCTP] for more information on how this parameter is used.  The&n; *   peer address parameter is ignored for TCP style socket.&n; */
DECL|struct|sctp_assocparams
r_struct
id|sctp_assocparams
(brace
DECL|member|sasoc_asocmaxrxt
id|__u16
id|sasoc_asocmaxrxt
suffix:semicolon
DECL|member|sasoc_assoc_id
id|sctp_assoc_t
id|sasoc_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.1.9 Set Primary Address (SCTP_SET_PRIMARY_ADDR)&n; *&n; *  Requests that the peer mark the enclosed address as the association&n; *  primary. The enclosed address must be one of the association&squot;s&n; *  locally bound addresses. The following structure is used to make a&n; *   set primary request:&n; */
DECL|struct|sctp_setprim
r_struct
id|sctp_setprim
(brace
DECL|member|ssp_addr
r_struct
id|sockaddr_storage
id|ssp_addr
suffix:semicolon
DECL|member|ssp_assoc_id
id|sctp_assoc_t
id|ssp_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.1.10 Set Peer Primary Address (SCTP_SET_PEER_PRIMARY_ADDR)&n; *&n; *  Requests that the local SCTP stack use the enclosed peer address as&n; *  the association primary. The enclosed address must be one of the&n; *  association peer&squot;s addresses. The following structure is used to&n; *  make a set peer primary request:&n; */
DECL|struct|sctp_setpeerprim
r_struct
id|sctp_setpeerprim
(brace
DECL|member|sspp_addr
r_struct
id|sockaddr_storage
id|sspp_addr
suffix:semicolon
DECL|member|sspp_assoc_id
id|sctp_assoc_t
id|sspp_assoc_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.2.1 Association Status (SCTP_STATUS)&n; *&n; *   Applications can retrieve current status information about an&n; *   association, including association state, peer receiver window size,&n; *   number of unacked data chunks, and number of data chunks pending&n; *   receipt.  This information is read-only.  The following structure is&n; *   used to access this information:&n; */
DECL|struct|sctp_status
r_struct
id|sctp_status
(brace
DECL|member|sstat_assoc_id
id|sctp_assoc_t
id|sstat_assoc_id
suffix:semicolon
DECL|member|sstat_state
id|__s32
id|sstat_state
suffix:semicolon
DECL|member|sstat_rwnd
id|__u32
id|sstat_rwnd
suffix:semicolon
DECL|member|sstat_unackdata
id|__u16
id|sstat_unackdata
suffix:semicolon
DECL|member|sstat_penddata
id|__u16
id|sstat_penddata
suffix:semicolon
DECL|member|sstat_instrms
id|__u16
id|sstat_instrms
suffix:semicolon
DECL|member|sstat_outstrms
id|__u16
id|sstat_outstrms
suffix:semicolon
DECL|member|sstat_fragmentation_point
id|__u32
id|sstat_fragmentation_point
suffix:semicolon
DECL|member|sstat_primary
r_struct
id|sctp_paddrinfo
id|sstat_primary
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.1.12 Set Adaption Layer Indicator&n; *&n; * Requests that the local endpoint set the specified Adaption Layer&n; * Indication parameter for all future&n; *  INIT and INIT-ACK exchanges.&n; */
DECL|struct|sctp_setadaption
r_struct
id|sctp_setadaption
(brace
DECL|member|ssb_adaption_ind
id|__u32
id|ssb_adaption_ind
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * 7.1.12 Set default message time outs (SCTP_SET_STREAM_TIMEOUTS)&n; *&n; * This option requests that the requested stream apply a&n; *  default time-out for messages in queue.&n; */
DECL|struct|sctp_setstrm_timeout
r_struct
id|sctp_setstrm_timeout
(brace
DECL|member|ssto_assoc_id
id|sctp_assoc_t
id|ssto_assoc_id
suffix:semicolon
DECL|member|ssto_timeout
id|__u32
id|ssto_timeout
suffix:semicolon
DECL|member|ssto_streamid_start
id|__u16
id|ssto_streamid_start
suffix:semicolon
DECL|member|ssto_streamid_end
id|__u16
id|ssto_streamid_end
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* These are bit fields for msghdr-&gt;msg_flags.  See section 5.1.  */
multiline_comment|/* On user space Linux, these live in &lt;bits/socket.h&gt; as an enum.  */
DECL|enum|sctp_msg_flags
r_enum
id|sctp_msg_flags
(brace
DECL|enumerator|MSG_NOTIFICATION
id|MSG_NOTIFICATION
op_assign
l_int|0x8000
comma
DECL|macro|MSG_NOTIFICATION
mdefine_line|#define MSG_NOTIFICATION MSG_NOTIFICATION
)brace
suffix:semicolon
multiline_comment|/*&n; * 8.1 sctp_bindx()&n; *&n; * The flags parameter is formed from the bitwise OR of zero or more of the&n; * following currently defined flags:&n; */
DECL|macro|BINDX_ADD_ADDR
mdefine_line|#define BINDX_ADD_ADDR 0x01
DECL|macro|BINDX_REM_ADDR
mdefine_line|#define BINDX_REM_ADDR 0x02
multiline_comment|/* This is the structure that is passed as an argument(optval) to&n; * getsockopt(SCTP_SOCKOPT_PEELOFF).&n; */
r_typedef
r_struct
(brace
DECL|member|associd
id|sctp_assoc_t
id|associd
suffix:semicolon
DECL|member|sd
r_int
id|sd
suffix:semicolon
DECL|typedef|sctp_peeloff_arg_t
)brace
id|sctp_peeloff_arg_t
suffix:semicolon
macro_line|#endif /* __net_sctp_user_h__ */
eof
