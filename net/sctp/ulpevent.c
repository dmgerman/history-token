multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; * &n; * These functions manipulate an sctp event.   The sctp_ulpevent_t is used&n; * to carry notifications and data to the ULP (sockets).  &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sctp/structs.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
r_static
r_void
id|sctp_ulpevent_set_owner_r
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|sctp_association_t
op_star
id|asoc
)paren
suffix:semicolon
r_static
r_void
id|sctp_ulpevent_set_owner
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
id|sctp_association_t
op_star
id|asoc
)paren
suffix:semicolon
multiline_comment|/* Create a new sctp_ulpevent.  */
DECL|function|sctp_ulpevent_new
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_new
c_func
(paren
r_int
id|size
comma
r_int
id|msg_flags
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|fail
suffix:semicolon
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|event
op_assign
id|sctp_ulpevent_init
c_func
(paren
id|event
comma
id|skb
comma
id|msg_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|fail_init
suffix:semicolon
id|event-&gt;malloced
op_assign
l_int|1
suffix:semicolon
r_return
id|event
suffix:semicolon
id|fail_init
suffix:colon
id|kfree_skb
c_func
(paren
id|event-&gt;parent
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Initialize an ULP event from an given skb.  */
DECL|function|sctp_ulpevent_init
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_init
c_func
(paren
id|sctp_ulpevent_t
op_star
id|event
comma
r_struct
id|sk_buff
op_star
id|parent
comma
r_int
id|msg_flags
)paren
(brace
id|memset
c_func
(paren
id|event
comma
r_sizeof
(paren
id|sctp_ulpevent_t
)paren
comma
l_int|0x00
)paren
suffix:semicolon
id|event-&gt;msg_flags
op_assign
id|msg_flags
suffix:semicolon
id|event-&gt;parent
op_assign
id|parent
suffix:semicolon
id|event-&gt;malloced
op_assign
l_int|0
suffix:semicolon
r_return
id|event
suffix:semicolon
)brace
multiline_comment|/* Dispose of an event.  */
DECL|function|sctp_ulpevent_free
r_void
id|sctp_ulpevent_free
c_func
(paren
id|sctp_ulpevent_t
op_star
id|event
)paren
(brace
r_if
c_cond
(paren
id|event-&gt;malloced
)paren
id|kfree_skb
c_func
(paren
id|event-&gt;parent
)paren
suffix:semicolon
)brace
multiline_comment|/* Is this a MSG_NOTIFICATION?  */
DECL|function|sctp_ulpevent_is_notification
r_int
id|sctp_ulpevent_is_notification
c_func
(paren
r_const
id|sctp_ulpevent_t
op_star
id|event
)paren
(brace
r_return
id|event-&gt;msg_flags
op_amp
id|MSG_NOTIFICATION
suffix:semicolon
)brace
multiline_comment|/* Create and initialize an SCTP_ASSOC_CHANGE event.&n; *&n; * 5.3.1.1 SCTP_ASSOC_CHANGE&n; *&n; * Communication notifications inform the ULP that an SCTP association&n; * has either begun or ended. The identifier for a new association is&n; * provided by this notification.&n; *&n; * Note: There is no field checking here.  If a field is unused it will be&n; * zero&squot;d out.&n; */
DECL|function|sctp_ulpevent_make_assoc_change
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_assoc_change
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
comma
id|__u16
id|flags
comma
id|__u16
id|state
comma
id|__u16
id|error
comma
id|__u16
id|outbound
comma
id|__u16
id|inbound
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_struct
id|sctp_assoc_change
op_star
id|sac
suffix:semicolon
id|event
op_assign
id|sctp_ulpevent_new
c_func
(paren
r_sizeof
(paren
r_struct
id|sctp_assoc_change
)paren
comma
id|MSG_NOTIFICATION
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|fail
suffix:semicolon
id|sac
op_assign
(paren
r_struct
id|sctp_assoc_change
op_star
)paren
id|skb_put
c_func
(paren
id|event-&gt;parent
comma
r_sizeof
(paren
r_struct
id|sctp_assoc_change
)paren
)paren
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * sac_type:&n;&t; * It should be SCTP_ASSOC_CHANGE.&n;&t; */
id|sac-&gt;sac_type
op_assign
id|SCTP_ASSOC_CHANGE
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * sac_state: 32 bits (signed integer)&n;&t; * This field holds one of a number of values that communicate the&n;&t; * event that happened to the association.&n;&t; */
id|sac-&gt;sac_state
op_assign
id|state
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * sac_flags: 16 bits (unsigned integer)&n;&t; * Currently unused.&n;&t; */
id|sac-&gt;sac_flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * sac_length: sizeof (__u32)&n;&t; * This field is the total length of the notification data, including&n;&t; * the notification header.&n;&t; */
id|sac-&gt;sac_length
op_assign
r_sizeof
(paren
r_struct
id|sctp_assoc_change
)paren
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * sac_error:  32 bits (signed integer)&n;&t; *&n;&t; * If the state was reached due to a error condition (e.g.&n;&t; * COMMUNICATION_LOST) any relevant error information is available in&n;&t; * this field. This corresponds to the protocol error codes defined in&n;&t; * [SCTP].&n;&t; */
id|sac-&gt;sac_error
op_assign
id|error
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * sac_outbound_streams:  16 bits (unsigned integer)&n;&t; * sac_inbound_streams:  16 bits (unsigned integer)&n;&t; *&n;&t; * The maximum number of streams allowed in each direction are&n;&t; * available in sac_outbound_streams and sac_inbound streams.&n;&t; */
id|sac-&gt;sac_outbound_streams
op_assign
id|outbound
suffix:semicolon
id|sac-&gt;sac_inbound_streams
op_assign
id|inbound
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * sac_assoc_id: sizeof (sctp_assoc_t)&n;&t; *&n;&t; * The association id field, holds the identifier for the association.&n;&t; * All notifications for a given association have the same association&n;&t; * identifier.  For TCP style socket, this field is ignored.&n;&t; */
id|sctp_ulpevent_set_owner
c_func
(paren
id|event-&gt;parent
comma
id|asoc
)paren
suffix:semicolon
id|sac-&gt;sac_assoc_id
op_assign
id|sctp_assoc2id
c_func
(paren
id|asoc
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Create and initialize an SCTP_PEER_ADDR_CHANGE event.&n; *&n; * Socket Extensions for SCTP - draft-01&n; * 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n; *&n; * When a destination address on a multi-homed peer encounters a change&n; * an interface details event is sent.&n; */
DECL|function|sctp_ulpevent_make_peer_addr_change
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_peer_addr_change
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
comma
r_const
r_struct
id|sockaddr_storage
op_star
id|aaddr
comma
r_int
id|flags
comma
r_int
id|state
comma
r_int
id|error
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_struct
id|sctp_paddr_change
op_star
id|spc
suffix:semicolon
id|event
op_assign
id|sctp_ulpevent_new
c_func
(paren
r_sizeof
(paren
r_struct
id|sctp_paddr_change
)paren
comma
id|MSG_NOTIFICATION
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|fail
suffix:semicolon
id|spc
op_assign
(paren
r_struct
id|sctp_paddr_change
op_star
)paren
id|skb_put
c_func
(paren
id|event-&gt;parent
comma
r_sizeof
(paren
r_struct
id|sctp_paddr_change
)paren
)paren
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n;&t; *&n;&t; * spc_type:&n;&t; *&n;&t; *    It should be SCTP_PEER_ADDR_CHANGE.&n;&t; */
id|spc-&gt;spc_type
op_assign
id|SCTP_PEER_ADDR_CHANGE
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n;&t; *&n;&t; * spc_length: sizeof (__u32)&n;&t; *&n;&t; * This field is the total length of the notification data, including&n;&t; * the notification header.&n;&t; */
id|spc-&gt;spc_length
op_assign
r_sizeof
(paren
r_struct
id|sctp_paddr_change
)paren
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n;&t; *&n;&t; * spc_flags: 16 bits (unsigned integer)&n;&t; * Currently unused.&n;&t; */
id|spc-&gt;spc_flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n;&t; *&n;&t; * spc_state:  32 bits (signed integer)&n;&t; * &n;&t; * This field holds one of a number of values that communicate the&n;&t; * event that happened to the address.&n;&t; */
id|spc-&gt;spc_state
op_assign
id|state
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n;&t; *&n;&t; * spc_error:  32 bits (signed integer)&n;&t; *&n;&t; * If the state was reached due to any error condition (e.g.&n;&t; * ADDRESS_UNREACHABLE) any relevant error information is available in&n;&t; * this field.&n;&t; */
id|spc-&gt;spc_error
op_assign
id|error
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.1 SCTP_ASSOC_CHANGE&n;&t; *&n;&t; * spc_assoc_id: sizeof (sctp_assoc_t)&n;&t; *&n;&t; * The association id field, holds the identifier for the association.&n;&t; * All notifications for a given association have the same association&n;&t; * identifier.  For TCP style socket, this field is ignored.&n;&t; */
id|sctp_ulpevent_set_owner
c_func
(paren
id|event-&gt;parent
comma
id|asoc
)paren
suffix:semicolon
id|spc-&gt;spc_assoc_id
op_assign
id|sctp_assoc2id
c_func
(paren
id|asoc
)paren
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE&n;&t; *&n;&t; * spc_aaddr: sizeof (struct sockaddr_storage)&n;&t; *&n;&t; * The affected address field, holds the remote peer&squot;s address that is&n;&t; * encountering the change of state.&n;&t; */
id|memcpy
c_func
(paren
op_amp
id|spc-&gt;spc_aaddr
comma
id|aaddr
comma
r_sizeof
(paren
r_struct
id|sockaddr_storage
)paren
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Create and initialize an SCTP_REMOTE_ERROR notification.&n; *&n; * Note: This assumes that the chunk-&gt;skb-&gt;data already points to the&n; * operation error payload.&n; *&n; * Socket Extensions for SCTP - draft-01&n; * 5.3.1.3 SCTP_REMOTE_ERROR&n; *&n; * A remote peer may send an Operational Error message to its peer.&n; * This message indicates a variety of error conditions on an&n; * association. The entire error TLV as it appears on the wire is&n; * included in a SCTP_REMOTE_ERROR event.  Please refer to the SCTP&n; * specification [SCTP] and any extensions for a list of possible&n; * error formats.&n; */
DECL|function|sctp_ulpevent_make_remote_error
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_remote_error
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
comma
id|sctp_chunk_t
op_star
id|chunk
comma
id|__u16
id|flags
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_struct
id|sctp_remote_error
op_star
id|sre
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|sctp_errhdr_t
op_star
id|ch
suffix:semicolon
id|__u16
id|cause
suffix:semicolon
r_int
id|elen
suffix:semicolon
id|ch
op_assign
(paren
id|sctp_errhdr_t
op_star
)paren
(paren
id|chunk-&gt;skb-&gt;data
)paren
suffix:semicolon
id|cause
op_assign
id|ch-&gt;cause
suffix:semicolon
id|elen
op_assign
id|ntohs
c_func
(paren
id|ch-&gt;length
)paren
op_minus
r_sizeof
(paren
id|sctp_errhdr_t
)paren
suffix:semicolon
multiline_comment|/* Pull off the ERROR header.  */
id|skb_pull
c_func
(paren
id|chunk-&gt;skb
comma
r_sizeof
(paren
id|sctp_errhdr_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Copy the skb to a new skb with room for us to prepend&n;&t; * notification with.&n;&t; */
id|skb
op_assign
id|skb_copy_expand
c_func
(paren
id|chunk-&gt;skb
comma
r_sizeof
(paren
r_struct
id|sctp_remote_error
)paren
comma
multiline_comment|/* headroom */
l_int|0
comma
multiline_comment|/* tailroom */
id|priority
)paren
suffix:semicolon
multiline_comment|/* Pull off the rest of the cause TLV from the chunk.  */
id|skb_pull
c_func
(paren
id|chunk-&gt;skb
comma
id|elen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* Embed the event fields inside the cloned skb.  */
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|event
op_assign
id|sctp_ulpevent_init
c_func
(paren
id|event
comma
id|skb
comma
id|MSG_NOTIFICATION
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|fail
suffix:semicolon
id|event-&gt;malloced
op_assign
l_int|1
suffix:semicolon
id|sre
op_assign
(paren
r_struct
id|sctp_remote_error
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|sctp_remote_error
)paren
)paren
suffix:semicolon
multiline_comment|/* Trim the buffer to the right length.  */
id|skb_trim
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|sctp_remote_error
)paren
op_plus
id|elen
)paren
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.3 SCTP_REMOTE_ERROR&n;&t; *&n;&t; * sre_type:&n;&t; *   It should be SCTP_REMOTE_ERROR.&n;&t; */
id|sre-&gt;sre_type
op_assign
id|SCTP_REMOTE_ERROR
suffix:semicolon
multiline_comment|/*&n;&t; * Socket Extensions for SCTP&n;&t; * 5.3.1.3 SCTP_REMOTE_ERROR&n;&t; *&n;&t; * sre_flags: 16 bits (unsigned integer)&n;&t; *   Currently unused.&n;&t; */
id|sre-&gt;sre_flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.3 SCTP_REMOTE_ERROR&n;&t; *&n;&t; * sre_length: sizeof (__u32)&n;&t; *&n;&t; * This field is the total length of the notification data,&n;&t; * including the notification header.&n;&t; */
id|sre-&gt;sre_length
op_assign
id|skb-&gt;len
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.3 SCTP_REMOTE_ERROR&n;&t; *&n;&t; * sre_error: 16 bits (unsigned integer)&n;&t; * This value represents one of the Operational Error causes defined in&n;&t; * the SCTP specification, in network byte order.&n;&t; */
id|sre-&gt;sre_error
op_assign
id|cause
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.3 SCTP_REMOTE_ERROR&n;&t; *&n;&t; * sre_assoc_id: sizeof (sctp_assoc_t)&n;&t; *&n;&t; * The association id field, holds the identifier for the association.&n;&t; * All notifications for a given association have the same association&n;&t; * identifier.  For TCP style socket, this field is ignored.&n;&t; */
id|sctp_ulpevent_set_owner
c_func
(paren
id|event-&gt;parent
comma
id|asoc
)paren
suffix:semicolon
id|sre-&gt;sre_assoc_id
op_assign
id|sctp_assoc2id
c_func
(paren
id|asoc
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Create and initialize a SCTP_SEND_FAILED notification.&n; *&n; * Socket Extensions for SCTP - draft-01&n; * 5.3.1.4 SCTP_SEND_FAILED&n; */
DECL|function|sctp_ulpevent_make_send_failed
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_send_failed
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
comma
id|sctp_chunk_t
op_star
id|chunk
comma
id|__u16
id|flags
comma
id|__u32
id|error
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_struct
id|sctp_send_failed
op_star
id|ssf
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* Make skb with more room so we can prepend notification.  */
id|skb
op_assign
id|skb_copy_expand
c_func
(paren
id|chunk-&gt;skb
comma
r_sizeof
(paren
r_struct
id|sctp_send_failed
)paren
comma
multiline_comment|/* headroom */
l_int|0
comma
multiline_comment|/* tailroom */
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* Pull off the common chunk header and DATA header.  */
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|sctp_data_chunk_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Embed the event fields inside the cloned skb.  */
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|event
op_assign
id|sctp_ulpevent_init
c_func
(paren
id|event
comma
id|skb
comma
id|MSG_NOTIFICATION
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* Mark as malloced, even though the constructor was not&n;&t; * called.&n;&t; */
id|event-&gt;malloced
op_assign
l_int|1
suffix:semicolon
id|ssf
op_assign
(paren
r_struct
id|sctp_send_failed
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|sctp_send_failed
)paren
)paren
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.4 SCTP_SEND_FAILED&n;&t; *&n;&t; * ssf_type:&n;&t; * It should be SCTP_SEND_FAILED.&n;&t; */
id|ssf-&gt;ssf_type
op_assign
id|SCTP_SEND_FAILED
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.4 SCTP_SEND_FAILED&n;&t; *&n;&t; * ssf_flags: 16 bits (unsigned integer)&n;&t; * The flag value will take one of the following values&n;&t; *&n;&t; * SCTP_DATA_UNSENT - Indicates that the data was never put on&n;&t; *                    the wire.&n;&t; *&n;&t; * SCTP_DATA_SENT   - Indicates that the data was put on the wire.&n;&t; *                    Note that this does not necessarily mean that the&n;&t; *                    data was (or was not) successfully delivered.&n;&t; */
id|ssf-&gt;ssf_flags
op_assign
id|flags
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.4 SCTP_SEND_FAILED&n;&t; *&n;&t; * ssf_length: sizeof (__u32)&n;&t; * This field is the total length of the notification data, including&n;&t; * the notification header.&n;&t; */
id|ssf-&gt;ssf_length
op_assign
id|skb-&gt;len
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.4 SCTP_SEND_FAILED&n;&t; *&n;&t; * ssf_error: 16 bits (unsigned integer)&n;&t; * This value represents the reason why the send failed, and if set,&n;&t; * will be a SCTP protocol error code as defined in [SCTP] section&n;&t; * 3.3.10.&n;&t; */
id|ssf-&gt;ssf_error
op_assign
id|error
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.4 SCTP_SEND_FAILED&n;&t; *&n;&t; * ssf_info: sizeof (struct sctp_sndrcvinfo)&n;&t; * The original send information associated with the undelivered&n;&t; * message.&n;&t; */
id|memcpy
c_func
(paren
op_amp
id|ssf-&gt;ssf_info
comma
op_amp
id|chunk-&gt;sinfo
comma
r_sizeof
(paren
r_struct
id|sctp_sndrcvinfo
)paren
)paren
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.4 SCTP_SEND_FAILED&n;&t; *&n;&t; * ssf_assoc_id: sizeof (sctp_assoc_t)&n;&t; * The association id field, sf_assoc_id, holds the identifier for the&n;&t; * association.  All notifications for a given association have the&n;&t; * same association identifier.  For TCP style socket, this field is&n;&t; * ignored.&n;&t; */
id|sctp_ulpevent_set_owner
c_func
(paren
id|event-&gt;parent
comma
id|asoc
)paren
suffix:semicolon
id|ssf-&gt;ssf_assoc_id
op_assign
id|sctp_assoc2id
c_func
(paren
id|asoc
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Create and initialize a SCTP_SHUTDOWN_EVENT notification.&n; *&n; * Socket Extensions for SCTP - draft-01&n; * 5.3.1.5 SCTP_SHUTDOWN_EVENT&n; */
DECL|function|sctp_ulpevent_make_shutdown_event
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_shutdown_event
c_func
(paren
r_const
id|sctp_association_t
op_star
id|asoc
comma
id|__u16
id|flags
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_struct
id|sctp_shutdown_event
op_star
id|sse
suffix:semicolon
id|event
op_assign
id|sctp_ulpevent_new
c_func
(paren
r_sizeof
(paren
r_struct
id|sctp_assoc_change
)paren
comma
id|MSG_NOTIFICATION
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|fail
suffix:semicolon
id|sse
op_assign
(paren
r_struct
id|sctp_shutdown_event
op_star
)paren
id|skb_put
c_func
(paren
id|event-&gt;parent
comma
r_sizeof
(paren
r_struct
id|sctp_shutdown_event
)paren
)paren
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.5 SCTP_SHUTDOWN_EVENT&n;&t; *&n;&t; * sse_type&n;&t; * It should be SCTP_SHUTDOWN_EVENT&n;&t; */
id|sse-&gt;sse_type
op_assign
id|SCTP_SHUTDOWN_EVENT
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.5 SCTP_SHUTDOWN_EVENT&n;&t; *&n;&t; * sse_flags: 16 bits (unsigned integer)&n;&t; * Currently unused.&n;&t; */
id|sse-&gt;sse_flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.5 SCTP_SHUTDOWN_EVENT&n;&t; *&n;&t; * sse_length: sizeof (__u32)&n;&t; * This field is the total length of the notification data, including&n;&t; * the notification header.&n;&t; */
id|sse-&gt;sse_length
op_assign
r_sizeof
(paren
r_struct
id|sctp_shutdown_event
)paren
suffix:semicolon
multiline_comment|/* Socket Extensions for SCTP&n;&t; * 5.3.1.5 SCTP_SHUTDOWN_EVENT&n;&t; *&n;&t; * sse_assoc_id: sizeof (sctp_assoc_t)&n;&t; * The association id field, holds the identifier for the association.&n;&t; * All notifications for a given association have the same association&n;&t; * identifier.  For TCP style socket, this field is ignored.&n;&t; */
id|sctp_ulpevent_set_owner
c_func
(paren
id|event-&gt;parent
comma
id|asoc
)paren
suffix:semicolon
id|sse-&gt;sse_assoc_id
op_assign
id|sctp_assoc2id
c_func
(paren
id|asoc
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* A message has been received.  Package this message as a notification&n; * to pass it to the upper layers.  Go ahead and calculate the sndrcvinfo&n; * even if filtered out later.&n; *&n; * Socket Extensions for SCTP - draft-01&n; * 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)&n; */
DECL|function|sctp_ulpevent_make_rcvmsg
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_rcvmsg
c_func
(paren
id|sctp_association_t
op_star
id|asoc
comma
id|sctp_chunk_t
op_star
id|chunk
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
comma
op_star
id|levent
suffix:semicolon
r_struct
id|sctp_sndrcvinfo
op_star
id|info
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
comma
op_star
id|list
suffix:semicolon
r_int
id|padding
comma
id|len
suffix:semicolon
multiline_comment|/* Clone the original skb, sharing the data.  */
id|skb
op_assign
id|skb_clone
c_func
(paren
id|chunk-&gt;skb
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* First calculate the padding, so we don&squot;t inadvertently&n;&t; * pass up the wrong length to the user.&n;&t; *&n;&t; * RFC 2960 - Section 3.2  Chunk Field Descriptions&n;&t; *&n;&t; * The total length of a chunk(including Type, Length and Value fields)&n;&t; * MUST be a multiple of 4 bytes.  If the length of the chunk is not a&n;&t; * multiple of 4 bytes, the sender MUST pad the chunk with all zero&n;&t; * bytes and this padding is not included in the chunk length field.&n;&t; * The sender should never pad with more than 3 bytes.  The receiver&n;&t; * MUST ignore the padding bytes.&n;&t; */
id|len
op_assign
id|ntohs
c_func
(paren
id|chunk-&gt;chunk_hdr-&gt;length
)paren
suffix:semicolon
id|padding
op_assign
id|WORD_ROUND
c_func
(paren
id|len
)paren
op_minus
id|len
suffix:semicolon
multiline_comment|/* Fixup cloned skb with just this chunks data.  */
id|skb_trim
c_func
(paren
id|skb
comma
id|chunk-&gt;chunk_end
op_minus
id|padding
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
multiline_comment|/* Set up a destructor to do rwnd accounting.  */
id|sctp_ulpevent_set_owner_r
c_func
(paren
id|skb
comma
id|asoc
)paren
suffix:semicolon
multiline_comment|/* Embed the event fields inside the cloned skb.  */
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
multiline_comment|/* Initialize event with flags 0.  */
id|event
op_assign
id|sctp_ulpevent_init
c_func
(paren
id|event
comma
id|skb
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|fail_init
suffix:semicolon
id|event-&gt;malloced
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|list
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
id|sctp_ulpevent_set_owner_r
c_func
(paren
id|list
comma
id|asoc
)paren
suffix:semicolon
multiline_comment|/* Initialize event with flags 0.  */
id|levent
op_assign
id|sctp_ulpevent_init
c_func
(paren
id|event
comma
id|skb
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|levent
)paren
r_goto
id|fail_init
suffix:semicolon
id|levent-&gt;malloced
op_assign
l_int|1
suffix:semicolon
)brace
id|info
op_assign
(paren
r_struct
id|sctp_sndrcvinfo
op_star
)paren
op_amp
id|event-&gt;sndrcvinfo
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)&n;&t; *&n;&t; * sinfo_stream: 16 bits (unsigned integer)&n;&t; *&n;&t; * For recvmsg() the SCTP stack places the message&squot;s stream number in&n;&t; * this value.&n;&t; */
id|info-&gt;sinfo_stream
op_assign
id|ntohs
c_func
(paren
id|chunk-&gt;subh.data_hdr-&gt;stream
)paren
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)&n;&t; *&n;&t; * sinfo_ssn: 16 bits (unsigned integer)&n;&t; *&n;&t; * For recvmsg() this value contains the stream sequence number that&n;&t; * the remote endpoint placed in the DATA chunk.  For fragmented&n;&t; * messages this is the same number for all deliveries of the message&n;&t; * (if more than one recvmsg() is needed to read the message).&n;&t; */
id|info-&gt;sinfo_ssn
op_assign
id|ntohs
c_func
(paren
id|chunk-&gt;subh.data_hdr-&gt;ssn
)paren
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)&n;&t; *&n;&t; * sinfo_ppid: 32 bits (unsigned integer)&n;&t; *&n;&t; * In recvmsg() this value is&n;&t; * the same information that was passed by the upper layer in the peer&n;&t; * application.  Please note that byte order issues are NOT accounted&n;&t; * for and this information is passed opaquely by the SCTP stack from&n;&t; * one end to the other.&n;&t; */
id|info-&gt;sinfo_ppid
op_assign
id|ntohl
c_func
(paren
id|chunk-&gt;subh.data_hdr-&gt;ppid
)paren
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)&n;&t; *&n;&t; * sinfo_flags: 16 bits (unsigned integer)&n;&t; *&n;&t; * This field may contain any of the following flags and is composed of&n;&t; * a bitwise OR of these values.&n;&t; *&n;&t; * recvmsg() flags:&n;&t; *&n;&t; * MSG_UNORDERED - This flag is present when the message was sent&n;&t; *                 non-ordered.&n;&t; */
r_if
c_cond
(paren
id|chunk-&gt;chunk_hdr-&gt;flags
op_amp
id|SCTP_DATA_UNORDERED
)paren
id|info-&gt;sinfo_flags
op_or_assign
id|MSG_UNORDERED
suffix:semicolon
multiline_comment|/* FIXME:  For reassembly, we need to have the fragmentation bits.&n;&t; * This really does not belong in the event structure, but&n;&t; * its difficult to fix everything at the same time.   Eventually,&n;&t; * we should create and skb based chunk structure.   This structure&n;&t; * storage can be converted to an event.  --jgrimm&n;&t; */
id|event-&gt;chunk_flags
op_assign
id|chunk-&gt;chunk_hdr-&gt;flags
suffix:semicolon
multiline_comment|/* With -04 draft, tsn moves into sndrcvinfo. */
id|info-&gt;sinfo_tsn
op_assign
id|ntohl
c_func
(paren
id|chunk-&gt;subh.data_hdr-&gt;tsn
)paren
suffix:semicolon
multiline_comment|/* Context is not used on receive. */
id|info-&gt;sinfo_context
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Sockets API Extensions for SCTP&n;&t; * Section 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)&n;&t; *&n;&t; * sinfo_assoc_id: sizeof (sctp_assoc_t)&n;&t; *&n;&t; * The association handle field, sinfo_assoc_id, holds the identifier&n;&t; * for the association announced in the COMMUNICATION_UP notification.&n;&t; * All notifications for a given association have the same identifier.&n;&t; * Ignored for TCP-style sockets.&n;&t; */
id|info-&gt;sinfo_assoc_id
op_assign
id|sctp_assoc2id
c_func
(paren
id|asoc
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
id|fail_init
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Return the notification type, assuming this is a notification&n; * event.&n; */
DECL|function|sctp_ulpevent_get_notification_type
id|__u16
id|sctp_ulpevent_get_notification_type
c_func
(paren
r_const
id|sctp_ulpevent_t
op_star
id|event
)paren
(brace
r_union
id|sctp_notification
op_star
id|notification
suffix:semicolon
id|notification
op_assign
(paren
r_union
id|sctp_notification
op_star
)paren
id|event-&gt;parent-&gt;data
suffix:semicolon
r_return
id|notification-&gt;h.sn_type
suffix:semicolon
)brace
multiline_comment|/* Copy out the sndrcvinfo into a msghdr.  */
DECL|function|sctp_ulpevent_read_sndrcvinfo
r_void
id|sctp_ulpevent_read_sndrcvinfo
c_func
(paren
r_const
id|sctp_ulpevent_t
op_star
id|event
comma
r_struct
id|msghdr
op_star
id|msghdr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sctp_ulpevent_is_notification
c_func
(paren
id|event
)paren
)paren
(brace
id|put_cmsg
c_func
(paren
id|msghdr
comma
id|IPPROTO_SCTP
comma
id|SCTP_SNDRCV
comma
r_sizeof
(paren
r_struct
id|sctp_sndrcvinfo
)paren
comma
(paren
r_void
op_star
)paren
op_amp
id|event-&gt;sndrcvinfo
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Do accounting for bytes just read by user.  */
DECL|function|sctp_rcvmsg_rfree
r_static
r_void
id|sctp_rcvmsg_rfree
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
multiline_comment|/* Current stack structures assume that the rcv buffer is&n;&t; * per socket.   For UDP style sockets this is not true as&n;&t; * multiple associations may be on a single UDP-style socket.&n;&t; * Use the local private area of the skb to track the owning&n;&t; * association.&n;&t; */
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|asoc
op_assign
id|event-&gt;asoc
suffix:semicolon
id|sctp_assoc_rwnd_increase
c_func
(paren
id|asoc
comma
id|skb_headlen
c_func
(paren
id|skb
)paren
)paren
suffix:semicolon
id|sctp_association_put
c_func
(paren
id|asoc
)paren
suffix:semicolon
)brace
multiline_comment|/* Charge receive window for bytes received.  */
DECL|function|sctp_ulpevent_set_owner_r
r_static
r_void
id|sctp_ulpevent_set_owner_r
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|sctp_association_t
op_star
id|asoc
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
multiline_comment|/* The current stack structures assume that the rcv buffer is&n;&t; * per socket.  For UDP-style sockets this is not true as&n;&t; * multiple associations may be on a single UDP-style socket.&n;&t; * We use the local private area of the skb to track the owning&n;&t; * association.&n;&t; */
id|sctp_association_hold
c_func
(paren
id|asoc
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|asoc-&gt;base.sk
suffix:semicolon
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|event-&gt;asoc
op_assign
id|asoc
suffix:semicolon
id|skb-&gt;destructor
op_assign
id|sctp_rcvmsg_rfree
suffix:semicolon
id|sctp_assoc_rwnd_decrease
c_func
(paren
id|asoc
comma
id|skb_headlen
c_func
(paren
id|skb
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* A simple destructor to give up the reference to the association. */
DECL|function|sctp_ulpevent_rfree
r_static
r_void
id|sctp_ulpevent_rfree
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|sctp_association_put
c_func
(paren
id|event-&gt;asoc
)paren
suffix:semicolon
)brace
multiline_comment|/* Hold the association in case the msg_name needs read out of &n; * the association. &n; */
DECL|function|sctp_ulpevent_set_owner
r_static
r_void
id|sctp_ulpevent_set_owner
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
id|sctp_association_t
op_star
id|asoc
)paren
(brace
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
multiline_comment|/* Cast away the const, as we are just wanting to&n;&t; * bump the reference count.&n;&t; */
id|sctp_association_hold
c_func
(paren
(paren
id|sctp_association_t
op_star
)paren
id|asoc
)paren
suffix:semicolon
id|skb-&gt;sk
op_assign
id|asoc-&gt;base.sk
suffix:semicolon
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
id|event-&gt;asoc
op_assign
(paren
id|sctp_association_t
op_star
)paren
id|asoc
suffix:semicolon
id|skb-&gt;destructor
op_assign
id|sctp_ulpevent_rfree
suffix:semicolon
)brace
eof
