multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 International Business Machines Corp.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * This file is part of the implementation of the add-IP extension,&n; * based on &lt;draft-ietf-tsvwg-addip-sctp-02.txt&gt; June 29, 2001,&n; * for the SCTP kernel reference Implementation.&n; * &n; * This file converts numerical ID value to alphabetical names for SCTP&n; * terms such as chunk type, parameter time, event type, etc.&n; * &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson          &lt;karl@athena.chicago.il.us&gt;&n; *    Xingang Guo           &lt;xingang.guo@intel.com&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    Daisy Chang&t;    &lt;daisyc@us.ibm.com&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#if SCTP_DEBUG
DECL|variable|sctp_debug_flag
r_int
id|sctp_debug_flag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Initially enable DEBUG */
macro_line|#endif&t;/* SCTP_DEBUG */
multiline_comment|/* These are printable forms of Chunk ID&squot;s from section 3.1.  */
DECL|variable|sctp_cid_tbl
r_static
r_const
r_char
op_star
id|sctp_cid_tbl
(braket
id|SCTP_NUM_BASE_CHUNK_TYPES
)braket
op_assign
(brace
l_string|&quot;DATA&quot;
comma
l_string|&quot;INIT&quot;
comma
l_string|&quot;INIT_ACK&quot;
comma
l_string|&quot;SACK&quot;
comma
l_string|&quot;HEARTBEAT&quot;
comma
l_string|&quot;HEARTBEAT_ACK&quot;
comma
l_string|&quot;ABORT&quot;
comma
l_string|&quot;SHUTDOWN&quot;
comma
l_string|&quot;SHUTDOWN_ACK&quot;
comma
l_string|&quot;ERROR&quot;
comma
l_string|&quot;COOKIE_ECHO&quot;
comma
l_string|&quot;COOKIE_ACK&quot;
comma
l_string|&quot;ECN_ECNE&quot;
comma
l_string|&quot;ECN_CWR&quot;
comma
l_string|&quot;SHUTDOWN_COMPLETE&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* Lookup &quot;chunk type&quot; debug name. */
DECL|function|sctp_cname
r_const
r_char
op_star
id|sctp_cname
c_func
(paren
r_const
id|sctp_subtype_t
id|cid
)paren
(brace
r_if
c_cond
(paren
id|cid.chunk
OL
l_int|0
)paren
r_return
l_string|&quot;illegal chunk id&quot;
suffix:semicolon
r_if
c_cond
(paren
id|cid.chunk
op_le
id|SCTP_CID_BASE_MAX
)paren
r_return
id|sctp_cid_tbl
(braket
id|cid.chunk
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cid.chunk
)paren
(brace
r_case
id|SCTP_CID_ASCONF
suffix:colon
r_return
l_string|&quot;ASCONF&quot;
suffix:semicolon
r_case
id|SCTP_CID_ASCONF_ACK
suffix:colon
r_return
l_string|&quot;ASCONF_ACK&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown chunk&quot;
suffix:semicolon
)brace
suffix:semicolon
r_return
l_string|&quot;unknown chunk&quot;
suffix:semicolon
)brace
multiline_comment|/* These are printable form of variable-length parameters. */
DECL|variable|sctp_param_tbl
r_const
r_char
op_star
id|sctp_param_tbl
(braket
id|SCTP_PARAM_ECN_CAPABLE
op_plus
l_int|1
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;PARAM_HEATBEAT_INFO&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;PARAM_IPV4_ADDRESS&quot;
comma
l_string|&quot;PARAM_IPV6_ADDRESS&quot;
comma
l_string|&quot;PARAM_STATE_COOKIE&quot;
comma
l_string|&quot;PARAM_UNRECOGNIZED_PARAMETERS&quot;
comma
l_string|&quot;PARAM_COOKIE_PRESERVATIVE&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;PARAM_HOST_NAME_ADDRESS&quot;
comma
l_string|&quot;PARAM_SUPPORTED_ADDRESS_TYPES&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* These are printable forms of the states.  */
DECL|variable|sctp_state_tbl
r_const
r_char
op_star
id|sctp_state_tbl
(braket
id|SCTP_STATE_NUM_STATES
)braket
op_assign
(brace
l_string|&quot;STATE_EMPTY&quot;
comma
l_string|&quot;STATE_CLOSED&quot;
comma
l_string|&quot;STATE_COOKIE_WAIT&quot;
comma
l_string|&quot;STATE_COOKIE_ECHOED&quot;
comma
l_string|&quot;STATE_ESTABLISHED&quot;
comma
l_string|&quot;STATE_SHUTDOWN_PENDING&quot;
comma
l_string|&quot;STATE_SHUTDOWN_SENT&quot;
comma
l_string|&quot;STATE_SHUTDOWN_RECEIVED&quot;
comma
l_string|&quot;STATE_SHUTDOWN_ACK_SENT&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* Events that could change the state of an association.  */
DECL|variable|sctp_evttype_tbl
r_const
r_char
op_star
id|sctp_evttype_tbl
(braket
)braket
op_assign
(brace
l_string|&quot;EVENT_T_unknown&quot;
comma
l_string|&quot;EVENT_T_CHUNK&quot;
comma
l_string|&quot;EVENT_T_TIMEOUT&quot;
comma
l_string|&quot;EVENT_T_OTHER&quot;
comma
l_string|&quot;EVENT_T_PRIMITIVE&quot;
)brace
suffix:semicolon
multiline_comment|/* Return value of a state function */
DECL|variable|sctp_status_tbl
r_const
r_char
op_star
id|sctp_status_tbl
(braket
)braket
op_assign
(brace
l_string|&quot;DISPOSITION_DISCARD&quot;
comma
l_string|&quot;DISPOSITION_CONSUME&quot;
comma
l_string|&quot;DISPOSITION_NOMEM&quot;
comma
l_string|&quot;DISPOSITION_DELETE_TCB&quot;
comma
l_string|&quot;DISPOSITION_ABORT&quot;
comma
l_string|&quot;DISPOSITION_VIOLATION&quot;
comma
l_string|&quot;DISPOSITION_NOT_IMPL&quot;
comma
l_string|&quot;DISPOSITION_ERROR&quot;
comma
l_string|&quot;DISPOSITION_BUG&quot;
)brace
suffix:semicolon
multiline_comment|/* Printable forms of primitives */
DECL|variable|sctp_primitive_tbl
r_static
r_const
r_char
op_star
id|sctp_primitive_tbl
(braket
id|SCTP_NUM_PRIMITIVE_TYPES
)braket
op_assign
(brace
l_string|&quot;PRIMITIVE_INITIALIZE&quot;
comma
l_string|&quot;PRIMITIVE_ASSOCIATE&quot;
comma
l_string|&quot;PRIMITIVE_SHUTDOWN&quot;
comma
l_string|&quot;PRIMITIVE_ABORT&quot;
comma
l_string|&quot;PRIMITIVE_SEND&quot;
comma
l_string|&quot;PRIMITIVE_SETPRIMARY&quot;
comma
l_string|&quot;PRIMITIVE_RECEIVE&quot;
comma
l_string|&quot;PRIMITIVE_STATUS&quot;
comma
l_string|&quot;PRIMITIVE_CHANGEHEARTBEAT&quot;
comma
l_string|&quot;PRIMITIVE_REQUESTHEARTBEAT&quot;
comma
l_string|&quot;PRIMITIVE_GETSRTTREPORT&quot;
comma
l_string|&quot;PRIMITIVE_SETFAILURETHRESHOLD&quot;
comma
l_string|&quot;PRIMITIVE_SETPROTOPARAMETERS&quot;
comma
l_string|&quot;PRIMITIVE_RECEIVE_UNSENT&quot;
comma
l_string|&quot;PRIMITIVE_RECEIVE_UNACKED&quot;
comma
l_string|&quot;PRIMITIVE_DESTROY&quot;
)brace
suffix:semicolon
multiline_comment|/* Lookup primitive debug name. */
DECL|function|sctp_pname
r_const
r_char
op_star
id|sctp_pname
c_func
(paren
r_const
id|sctp_subtype_t
id|id
)paren
(brace
r_if
c_cond
(paren
id|id.primitive
OL
l_int|0
)paren
r_return
l_string|&quot;illegal primitive&quot;
suffix:semicolon
r_if
c_cond
(paren
id|id.primitive
op_le
id|SCTP_EVENT_PRIMITIVE_MAX
)paren
r_return
id|sctp_primitive_tbl
(braket
id|id.primitive
)braket
suffix:semicolon
r_return
l_string|&quot;unknown_primitive&quot;
suffix:semicolon
)brace
DECL|variable|sctp_other_tbl
r_static
r_const
r_char
op_star
id|sctp_other_tbl
(braket
)braket
op_assign
(brace
l_string|&quot;NO_PENDING_TSN&quot;
comma
l_string|&quot;ICMP_UNREACHFRAG&quot;
)brace
suffix:semicolon
multiline_comment|/* Lookup &quot;other&quot; debug name. */
DECL|function|sctp_oname
r_const
r_char
op_star
id|sctp_oname
c_func
(paren
r_const
id|sctp_subtype_t
id|id
)paren
(brace
r_if
c_cond
(paren
id|id.other
OL
l_int|0
)paren
r_return
l_string|&quot;illegal &squot;other&squot; event&quot;
suffix:semicolon
r_if
c_cond
(paren
id|id.other
OL
id|SCTP_EVENT_OTHER_MAX
)paren
r_return
id|sctp_other_tbl
(braket
id|id.other
)braket
suffix:semicolon
r_return
l_string|&quot;unknown &squot;other&squot; event&quot;
suffix:semicolon
)brace
DECL|variable|sctp_timer_tbl
r_static
r_const
r_char
op_star
id|sctp_timer_tbl
(braket
)braket
op_assign
(brace
l_string|&quot;TIMEOUT_NONE&quot;
comma
l_string|&quot;TIMEOUT_T1_COOKIE&quot;
comma
l_string|&quot;TIMEOUT_T1_INIT&quot;
comma
l_string|&quot;TIMEOUT_T2_SHUTDOWN&quot;
comma
l_string|&quot;TIMEOUT_T3_RTX&quot;
comma
l_string|&quot;TIMEOUT_T4_RTO&quot;
comma
l_string|&quot;TIMEOUT_T5_SHUTDOWN_GUARD&quot;
comma
l_string|&quot;TIMEOUT_HEARTBEAT&quot;
comma
l_string|&quot;TIMEOUT_SACK&quot;
comma
l_string|&quot;TIMEOUT_AUTOCLOSE&quot;
comma
l_string|&quot;TIMEOUT_PMTU_RAISE&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* Lookup timer debug name. */
DECL|function|sctp_tname
r_const
r_char
op_star
id|sctp_tname
c_func
(paren
r_const
id|sctp_subtype_t
id|id
)paren
(brace
r_if
c_cond
(paren
id|id.timeout
OL
l_int|0
)paren
r_return
l_string|&quot;illegal &squot;timer&squot; event&quot;
suffix:semicolon
r_if
c_cond
(paren
id|id.timeout
op_le
id|SCTP_EVENT_TIMEOUT_MAX
)paren
r_return
id|sctp_timer_tbl
(braket
id|id.timeout
)braket
suffix:semicolon
r_return
l_string|&quot;unknown_timer&quot;
suffix:semicolon
)brace
eof
