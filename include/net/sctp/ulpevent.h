multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * These are the definitions needed for the sctp_ulpevent type.  The &n; * sctp_ulpevent type is used to carry information from the state machine&n; * upwards to the ULP. &n; * &n; * The SCTP reference implementation  is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * the SCTP reference implementation  is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to one of the&n; * following email addresses:&n; * &n; * Jon Grimm &lt;jgrimm@us.ibm.com&gt;&n; * La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; * Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#ifndef __sctp_ulpevent_h__
DECL|macro|__sctp_ulpevent_h__
mdefine_line|#define __sctp_ulpevent_h__
multiline_comment|/* A structure to carry information to the ULP (e.g. Sockets API) */
multiline_comment|/* Warning: This sits inside an skb.cb[] area.  Be very careful of&n; * growing this structure as it is at the maximum limit now.&n; */
DECL|struct|sctp_ulpevent
r_typedef
r_struct
id|sctp_ulpevent
(brace
DECL|member|malloced
r_int
id|malloced
suffix:semicolon
DECL|member|asoc
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
DECL|member|parent
r_struct
id|sk_buff
op_star
id|parent
suffix:semicolon
DECL|member|sndrcvinfo
r_struct
id|sctp_sndrcvinfo
id|sndrcvinfo
suffix:semicolon
DECL|member|chunk_flags
r_int
id|chunk_flags
suffix:semicolon
multiline_comment|/* Temp. until we get a new chunk_t */
DECL|member|msg_flags
r_int
id|msg_flags
suffix:semicolon
DECL|typedef|sctp_ulpevent_t
)brace
id|sctp_ulpevent_t
suffix:semicolon
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
suffix:semicolon
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
id|skb
comma
r_int
id|msg_flags
)paren
suffix:semicolon
r_void
id|sctp_ulpevent_free
c_func
(paren
id|sctp_ulpevent_t
op_star
id|event
)paren
suffix:semicolon
r_int
id|sctp_ulpevent_is_notification
c_func
(paren
r_const
id|sctp_ulpevent_t
op_star
id|event
)paren
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_assoc_change
c_func
(paren
r_const
r_struct
id|SCTP_association
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
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_peer_addr_change
c_func
(paren
r_const
r_struct
id|SCTP_association
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
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_remote_error
c_func
(paren
r_const
r_struct
id|SCTP_association
op_star
id|asoc
comma
r_struct
id|SCTP_chunk
op_star
id|chunk
comma
id|__u16
id|flags
comma
r_int
id|priority
)paren
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_send_failed
c_func
(paren
r_const
r_struct
id|SCTP_association
op_star
id|asoc
comma
r_struct
id|SCTP_chunk
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
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_shutdown_event
c_func
(paren
r_const
r_struct
id|SCTP_association
op_star
id|asoc
comma
id|__u16
id|flags
comma
r_int
id|priority
)paren
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|sctp_ulpevent_make_rcvmsg
c_func
(paren
r_struct
id|SCTP_association
op_star
id|asoc
comma
r_struct
id|SCTP_chunk
op_star
id|chunk
comma
r_int
id|priority
)paren
suffix:semicolon
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
suffix:semicolon
id|__u16
id|sctp_ulpevent_get_notification_type
c_func
(paren
r_const
id|sctp_ulpevent_t
op_star
id|event
)paren
suffix:semicolon
multiline_comment|/* Given an event subscription, is this event enabled? */
DECL|function|sctp_ulpevent_is_enabled
r_static
r_inline
r_int
id|sctp_ulpevent_is_enabled
c_func
(paren
r_const
id|sctp_ulpevent_t
op_star
id|event
comma
r_const
r_struct
id|sctp_event_subscribe
op_star
id|mask
)paren
(brace
r_const
r_char
op_star
id|amask
op_assign
(paren
r_const
r_char
op_star
)paren
id|mask
suffix:semicolon
id|__u16
id|sn_type
suffix:semicolon
r_int
id|enabled
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sctp_ulpevent_is_notification
c_func
(paren
id|event
)paren
)paren
(brace
id|sn_type
op_assign
id|sctp_ulpevent_get_notification_type
c_func
(paren
id|event
)paren
suffix:semicolon
id|enabled
op_assign
id|amask
(braket
id|sn_type
op_minus
id|SCTP_SN_TYPE_BASE
)braket
suffix:semicolon
)brace
r_return
id|enabled
suffix:semicolon
)brace
macro_line|#endif /* __sctp_ulpevent_h__ */
eof