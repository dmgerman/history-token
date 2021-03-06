multiline_comment|/* SCTP kernel reference Implementation&n; * (C) Copyright IBM Corp. 2001, 2004&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * These are the definitions needed for the sctp_ulpq type.  The&n; * sctp_ulpq is the interface between the Upper Layer Protocol, or ULP,&n; * and the core SCTP state machine.  This is the component which handles&n; * reassembly and ordering.&n; *&n; * The SCTP reference implementation  is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * the SCTP reference implementation  is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email addresses:&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *   Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *   La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *   Sridhar Samudrala     &lt;sri@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#ifndef __sctp_ulpqueue_h__
DECL|macro|__sctp_ulpqueue_h__
mdefine_line|#define __sctp_ulpqueue_h__
multiline_comment|/* A structure to carry information to the ULP (e.g. Sockets API) */
DECL|struct|sctp_ulpq
r_struct
id|sctp_ulpq
(brace
DECL|member|malloced
r_char
id|malloced
suffix:semicolon
DECL|member|pd_mode
r_char
id|pd_mode
suffix:semicolon
DECL|member|asoc
r_struct
id|sctp_association
op_star
id|asoc
suffix:semicolon
DECL|member|reasm
r_struct
id|sk_buff_head
id|reasm
suffix:semicolon
DECL|member|lobby
r_struct
id|sk_buff_head
id|lobby
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Prototypes. */
r_struct
id|sctp_ulpq
op_star
id|sctp_ulpq_init
c_func
(paren
r_struct
id|sctp_ulpq
op_star
comma
r_struct
id|sctp_association
op_star
)paren
suffix:semicolon
r_void
id|sctp_ulpq_free
c_func
(paren
r_struct
id|sctp_ulpq
op_star
)paren
suffix:semicolon
multiline_comment|/* Add a new DATA chunk for processing. */
r_int
id|sctp_ulpq_tail_data
c_func
(paren
r_struct
id|sctp_ulpq
op_star
comma
r_struct
id|sctp_chunk
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Add a new event for propagation to the ULP. */
r_int
id|sctp_ulpq_tail_event
c_func
(paren
r_struct
id|sctp_ulpq
op_star
comma
r_struct
id|sctp_ulpevent
op_star
id|ev
)paren
suffix:semicolon
multiline_comment|/* Renege previously received chunks.  */
r_void
id|sctp_ulpq_renege
c_func
(paren
r_struct
id|sctp_ulpq
op_star
comma
r_struct
id|sctp_chunk
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Perform partial delivery. */
r_void
id|sctp_ulpq_partial_delivery
c_func
(paren
r_struct
id|sctp_ulpq
op_star
comma
r_struct
id|sctp_chunk
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Abort the partial delivery. */
r_void
id|sctp_ulpq_abort_pd
c_func
(paren
r_struct
id|sctp_ulpq
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Clear the partial data delivery condition on this socket. */
r_int
id|sctp_clear_pd
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
multiline_comment|/* Skip over an SSN. */
r_void
id|sctp_ulpq_skip
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
id|__u16
id|sid
comma
id|__u16
id|ssn
)paren
suffix:semicolon
macro_line|#endif /* __sctp_ulpqueue_h__ */
eof
