multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001-2002 International Business Machines Corp.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * This file is part of the implementation of the add-IP extension,&n; * based on &lt;draft-ietf-tsvwg-addip-sctp-02.txt&gt; June 29, 2001,&n; * for the SCTP kernel reference Implementation.&n; * &n; * The SCTP reference implementation  is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * the SCTP reference implementation  is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; *                 ************************&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to one of the following email&n; * addresses:&n; * &n; * La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; * Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; * Randall Stewart &lt;randall@stewart.chicago.il.us&gt;&n; * Ken Morneau &lt;kmorneau@cisco.com&gt;&n; * Qiaobing Xie &lt;qxie1@motorola.com&gt;&n; * Xingang Guo &lt;xingang.guo@intel.com&gt;&n; * Sridhar Samudrala &lt;samudrala@us.ibm.com&gt;&n; * Daisy Chang &lt;daisyc@us.ibm.com&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; * &n; * There are still LOTS of bugs in this code... I always run on the motto&n; * &quot;it is a wonder any code ever works :)&quot;&n; * &n; * &n; */
macro_line|#ifndef __sctp_constants_h__
DECL|macro|__sctp_constants_h__
mdefine_line|#define __sctp_constants_h__
macro_line|#include &lt;linux/tcp.h&gt;  /* For TCP states used in sctp_sock_state_t */
macro_line|#include &lt;linux/sctp.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt; /* For ipv6hdr. */
macro_line|#include &lt;net/sctp/user.h&gt;
multiline_comment|/* What a hack!  Jiminy Cricket!  */
DECL|enumerator|SCTP_MAX_STREAM
r_enum
(brace
id|SCTP_MAX_STREAM
op_assign
l_int|10
)brace
suffix:semicolon
multiline_comment|/* Define the amount of space to reserve for SCTP, IP, LL.&n; * There is a little bit of waste that we are always allocating&n; * for ipv6 headers, but this seems worth the simplicity.&n; */
DECL|macro|SCTP_IP_OVERHEAD
mdefine_line|#define SCTP_IP_OVERHEAD ((sizeof(struct sctphdr)&bslash;&n;                          + sizeof(struct ipv6hdr)&bslash;&n;                          + MAX_HEADER))
multiline_comment|/* Define the amount of space to reserve for SCTP, IP, LL.&n; * There is a little bit of waste that we are always allocating&n; * for ipv6 headers, but this seems worth the simplicity.&n; */
DECL|macro|SCTP_IP_OVERHEAD
mdefine_line|#define SCTP_IP_OVERHEAD ((sizeof(struct sctphdr)&bslash;&n;                          + sizeof(struct ipv6hdr)&bslash;&n;                          + MAX_HEADER))
multiline_comment|/* Since CIDs are sparse, we need all four of the following&n; * symbols.  CIDs are dense through SCTP_CID_BASE_MAX.&n; */
DECL|macro|SCTP_CID_BASE_MAX
mdefine_line|#define SCTP_CID_BASE_MAX&t;&t;SCTP_CID_SHUTDOWN_COMPLETE
DECL|macro|SCTP_CID_MAX
mdefine_line|#define SCTP_CID_MAX&t;&t;&t;SCTP_CID_ASCONF_ACK
DECL|macro|SCTP_NUM_BASE_CHUNK_TYPES
mdefine_line|#define SCTP_NUM_BASE_CHUNK_TYPES&t;(SCTP_CID_BASE_MAX + 1)
DECL|macro|SCTP_NUM_CHUNK_TYPES
mdefine_line|#define SCTP_NUM_CHUNK_TYPES&t;&t;(SCTP_NUM_BASE_CHUNKTYPES + 2)
multiline_comment|/* These are the different flavours of event.  */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_EVENT_T_CHUNK
id|SCTP_EVENT_T_CHUNK
op_assign
l_int|1
comma
DECL|enumerator|SCTP_EVENT_T_TIMEOUT
id|SCTP_EVENT_T_TIMEOUT
comma
DECL|enumerator|SCTP_EVENT_T_OTHER
id|SCTP_EVENT_T_OTHER
comma
DECL|enumerator|SCTP_EVENT_T_PRIMITIVE
id|SCTP_EVENT_T_PRIMITIVE
DECL|typedef|sctp_event_t
)brace
id|sctp_event_t
suffix:semicolon
DECL|macro|SCTP_EVENT_T_MAX
mdefine_line|#define SCTP_EVENT_T_MAX SCTP_EVENT_T_PRIMITIVE
DECL|macro|SCTP_EVENT_T_NUM
mdefine_line|#define SCTP_EVENT_T_NUM (SCTP_EVENT_T_MAX + 1)
multiline_comment|/* As a convenience for the state machine, we append SCTP_EVENT_* and&n; * SCTP_ULP_* to the list of possible chunks.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_EVENT_TIMEOUT_NONE
id|SCTP_EVENT_TIMEOUT_NONE
op_assign
l_int|0
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_T1_COOKIE
id|SCTP_EVENT_TIMEOUT_T1_COOKIE
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_T1_INIT
id|SCTP_EVENT_TIMEOUT_T1_INIT
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_T2_SHUTDOWN
id|SCTP_EVENT_TIMEOUT_T2_SHUTDOWN
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_T3_RTX
id|SCTP_EVENT_TIMEOUT_T3_RTX
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_T4_RTO
id|SCTP_EVENT_TIMEOUT_T4_RTO
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD
id|SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_HEARTBEAT
id|SCTP_EVENT_TIMEOUT_HEARTBEAT
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_SACK
id|SCTP_EVENT_TIMEOUT_SACK
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_AUTOCLOSE
id|SCTP_EVENT_TIMEOUT_AUTOCLOSE
comma
DECL|enumerator|SCTP_EVENT_TIMEOUT_PMTU_RAISE
id|SCTP_EVENT_TIMEOUT_PMTU_RAISE
comma
DECL|typedef|sctp_event_timeout_t
)brace
id|sctp_event_timeout_t
suffix:semicolon
DECL|macro|SCTP_EVENT_TIMEOUT_MAX
mdefine_line|#define SCTP_EVENT_TIMEOUT_MAX&t;&t;SCTP_EVENT_TIMEOUT_PMTU_RAISE
DECL|macro|SCTP_NUM_TIMEOUT_TYPES
mdefine_line|#define SCTP_NUM_TIMEOUT_TYPES&t;&t;(SCTP_EVENT_TIMEOUT_MAX + 1)
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_EVENT_NO_PENDING_TSN
id|SCTP_EVENT_NO_PENDING_TSN
op_assign
l_int|0
comma
DECL|enumerator|SCTP_EVENT_ICMP_UNREACHFRAG
id|SCTP_EVENT_ICMP_UNREACHFRAG
comma
DECL|typedef|sctp_event_other_t
)brace
id|sctp_event_other_t
suffix:semicolon
DECL|macro|SCTP_EVENT_OTHER_MAX
mdefine_line|#define SCTP_EVENT_OTHER_MAX&t;&t;SCTP_EVENT_ICMP_UNREACHFRAG
DECL|macro|SCTP_NUM_OTHER_TYPES
mdefine_line|#define SCTP_NUM_OTHER_TYPES&t;&t;(SCTP_EVENT_OTHER_MAX + 1)
multiline_comment|/* These are primitive requests from the ULP.  */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_PRIMITIVE_INITIALIZE
id|SCTP_PRIMITIVE_INITIALIZE
op_assign
l_int|0
comma
DECL|enumerator|SCTP_PRIMITIVE_ASSOCIATE
id|SCTP_PRIMITIVE_ASSOCIATE
comma
DECL|enumerator|SCTP_PRIMITIVE_SHUTDOWN
id|SCTP_PRIMITIVE_SHUTDOWN
comma
DECL|enumerator|SCTP_PRIMITIVE_ABORT
id|SCTP_PRIMITIVE_ABORT
comma
DECL|enumerator|SCTP_PRIMITIVE_SEND
id|SCTP_PRIMITIVE_SEND
comma
DECL|enumerator|SCTP_PRIMITIVE_SETPRIMARY
id|SCTP_PRIMITIVE_SETPRIMARY
comma
DECL|enumerator|SCTP_PRIMITIVE_RECEIVE
id|SCTP_PRIMITIVE_RECEIVE
comma
DECL|enumerator|SCTP_PRIMITIVE_STATUS
id|SCTP_PRIMITIVE_STATUS
comma
DECL|enumerator|SCTP_PRIMITIVE_CHANGEHEARTBEAT
id|SCTP_PRIMITIVE_CHANGEHEARTBEAT
comma
DECL|enumerator|SCTP_PRIMITIVE_REQUESTHEARTBEAT
id|SCTP_PRIMITIVE_REQUESTHEARTBEAT
comma
DECL|enumerator|SCTP_PRIMITIVE_GETSRTTREPORT
id|SCTP_PRIMITIVE_GETSRTTREPORT
comma
DECL|enumerator|SCTP_PRIMITIVE_SETFAILURETHRESHOLD
id|SCTP_PRIMITIVE_SETFAILURETHRESHOLD
comma
DECL|enumerator|SCTP_PRIMITIVE_SETPROTOPARAMETERS
id|SCTP_PRIMITIVE_SETPROTOPARAMETERS
comma
DECL|enumerator|SCTP_PRIMITIVE_RECEIVE_UNSENT
id|SCTP_PRIMITIVE_RECEIVE_UNSENT
comma
DECL|enumerator|SCTP_PRIMITIVE_RECEIVE_UNACKED
id|SCTP_PRIMITIVE_RECEIVE_UNACKED
comma
DECL|enumerator|SCTP_PRIMITIVE_DESTROY
id|SCTP_PRIMITIVE_DESTROY
comma
DECL|typedef|sctp_event_primitive_t
)brace
id|sctp_event_primitive_t
suffix:semicolon
DECL|macro|SCTP_EVENT_PRIMITIVE_MAX
mdefine_line|#define SCTP_EVENT_PRIMITIVE_MAX&t;SCTP_PRIMITIVE_DESTROY
DECL|macro|SCTP_NUM_PRIMITIVE_TYPES
mdefine_line|#define SCTP_NUM_PRIMITIVE_TYPES&t;(SCTP_EVENT_PRIMITIVE_MAX + 1)
multiline_comment|/* We define here a utility type for manipulating subtypes.&n; * The subtype constructors all work like this:&n; *&n; * &t;sctp_subtype_t foo = SCTP_ST_CHUNK(SCTP_CID_INIT);&n; */
r_typedef
r_union
(brace
DECL|member|chunk
id|sctp_cid_t
id|chunk
suffix:semicolon
DECL|member|timeout
id|sctp_event_timeout_t
id|timeout
suffix:semicolon
DECL|member|other
id|sctp_event_other_t
id|other
suffix:semicolon
DECL|member|primitive
id|sctp_event_primitive_t
id|primitive
suffix:semicolon
DECL|typedef|sctp_subtype_t
)brace
id|sctp_subtype_t
suffix:semicolon
DECL|macro|SCTP_SUBTYPE_CONSTRUCTOR
mdefine_line|#define SCTP_SUBTYPE_CONSTRUCTOR(_name, _type, _elt) &bslash;&n;static inline sctp_subtype_t&t;&bslash;&n;SCTP_ST_## _name (_type _arg)&t;&t;&bslash;&n;{ sctp_subtype_t _retval; _retval._elt = _arg; return _retval; }
id|SCTP_SUBTYPE_CONSTRUCTOR
c_func
(paren
id|CHUNK
comma
id|sctp_cid_t
comma
id|chunk
)paren
id|SCTP_SUBTYPE_CONSTRUCTOR
c_func
(paren
id|TIMEOUT
comma
id|sctp_event_timeout_t
comma
id|timeout
)paren
id|SCTP_SUBTYPE_CONSTRUCTOR
c_func
(paren
id|OTHER
comma
id|sctp_event_other_t
comma
id|other
)paren
id|SCTP_SUBTYPE_CONSTRUCTOR
c_func
(paren
id|PRIMITIVE
comma
id|sctp_event_primitive_t
comma
id|primitive
)paren
DECL|macro|sctp_chunk_is_control
mdefine_line|#define sctp_chunk_is_control(a) (a-&gt;chunk_hdr-&gt;type != SCTP_CID_DATA)
DECL|macro|sctp_chunk_is_data
mdefine_line|#define sctp_chunk_is_data(a) (a-&gt;chunk_hdr-&gt;type == SCTP_CID_DATA)
multiline_comment|/* Calculate the actual data size in a data chunk */
DECL|macro|SCTP_DATA_SNDSIZE
mdefine_line|#define SCTP_DATA_SNDSIZE(c) ((int)((unsigned long)(c-&gt;chunk_end)&bslash;&n;&t;&t;       &t;&t;- (unsigned long)(c-&gt;chunk_hdr)&bslash;&n;&t;&t;&t;&t;- sizeof(sctp_data_chunk_t)))
multiline_comment|/* This is a table of printable names of sctp_param_t&squot;s.  */
r_extern
r_const
r_char
op_star
id|sctp_param_tbl
(braket
)braket
suffix:semicolon
DECL|macro|SCTP_MAX_ERROR_CAUSE
mdefine_line|#define SCTP_MAX_ERROR_CAUSE  SCTP_ERROR_NONEXIST_IP
DECL|macro|SCTP_NUM_ERROR_CAUSE
mdefine_line|#define SCTP_NUM_ERROR_CAUSE  10
multiline_comment|/* Internal error codes */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_IERROR_NO_ERROR
id|SCTP_IERROR_NO_ERROR
op_assign
l_int|0
comma
DECL|enumerator|SCTP_IERROR_BASE
id|SCTP_IERROR_BASE
op_assign
l_int|1000
comma
DECL|enumerator|SCTP_IERROR_NO_COOKIE
id|SCTP_IERROR_NO_COOKIE
comma
DECL|enumerator|SCTP_IERROR_BAD_SIG
id|SCTP_IERROR_BAD_SIG
comma
DECL|enumerator|SCTP_IERROR_STALE_COOKIE
id|SCTP_IERROR_STALE_COOKIE
comma
DECL|enumerator|SCTP_IERROR_NOMEM
id|SCTP_IERROR_NOMEM
comma
DECL|enumerator|SCTP_IERROR_MALFORMED
id|SCTP_IERROR_MALFORMED
comma
DECL|enumerator|SCTP_IERROR_BAD_TAG
id|SCTP_IERROR_BAD_TAG
comma
DECL|enumerator|SCTP_IERROR_BIG_GAP
id|SCTP_IERROR_BIG_GAP
comma
DECL|enumerator|SCTP_IERROR_DUP_TSN
id|SCTP_IERROR_DUP_TSN
comma
DECL|typedef|sctp_ierror_t
)brace
id|sctp_ierror_t
suffix:semicolon
multiline_comment|/* SCTP state defines for internal state machine */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_STATE_EMPTY
id|SCTP_STATE_EMPTY
op_assign
l_int|0
comma
DECL|enumerator|SCTP_STATE_CLOSED
id|SCTP_STATE_CLOSED
op_assign
l_int|1
comma
DECL|enumerator|SCTP_STATE_COOKIE_WAIT
id|SCTP_STATE_COOKIE_WAIT
op_assign
l_int|2
comma
DECL|enumerator|SCTP_STATE_COOKIE_ECHOED
id|SCTP_STATE_COOKIE_ECHOED
op_assign
l_int|3
comma
DECL|enumerator|SCTP_STATE_ESTABLISHED
id|SCTP_STATE_ESTABLISHED
op_assign
l_int|4
comma
DECL|enumerator|SCTP_STATE_SHUTDOWN_PENDING
id|SCTP_STATE_SHUTDOWN_PENDING
op_assign
l_int|5
comma
DECL|enumerator|SCTP_STATE_SHUTDOWN_SENT
id|SCTP_STATE_SHUTDOWN_SENT
op_assign
l_int|6
comma
DECL|enumerator|SCTP_STATE_SHUTDOWN_RECEIVED
id|SCTP_STATE_SHUTDOWN_RECEIVED
op_assign
l_int|7
comma
DECL|enumerator|SCTP_STATE_SHUTDOWN_ACK_SENT
id|SCTP_STATE_SHUTDOWN_ACK_SENT
op_assign
l_int|8
comma
DECL|typedef|sctp_state_t
)brace
id|sctp_state_t
suffix:semicolon
DECL|macro|SCTP_STATE_MAX
mdefine_line|#define SCTP_STATE_MAX&t;&t;&t;SCTP_STATE_SHUTDOWN_ACK_SENT
DECL|macro|SCTP_STATE_NUM_STATES
mdefine_line|#define SCTP_STATE_NUM_STATES&t;&t;(SCTP_STATE_MAX + 1)
multiline_comment|/* These are values for sk-&gt;state.&n; * For a UDP-style SCTP socket, the states are defined as follows&n; *   (at this point of time, may change later after more discussions: FIXME)&n; * A socket in SCTP_SS_UNCONNECTED state indicates that it is not willing&n; * to accept new associations, but it can initiate the creation of new&n; * ones.&n; * A socket in SCTP_SS_LISTENING state indicates that it is willing to&n; * accept new  associations and can initiate the creation of new ones.&n; * A socket in SCTP_SS_ESTABLISHED state indicates that it is a peeled off&n; * socket with one association.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_SS_CLOSED
id|SCTP_SS_CLOSED
op_assign
id|TCP_CLOSE
comma
DECL|enumerator|SCTP_SS_LISTENING
id|SCTP_SS_LISTENING
op_assign
id|TCP_LISTEN
comma
DECL|enumerator|SCTP_SS_ESTABLISHING
id|SCTP_SS_ESTABLISHING
op_assign
id|TCP_SYN_SENT
comma
DECL|enumerator|SCTP_SS_ESTABLISHED
id|SCTP_SS_ESTABLISHED
op_assign
id|TCP_ESTABLISHED
comma
DECL|enumerator|SCTP_SS_DISCONNECTING
id|SCTP_SS_DISCONNECTING
op_assign
id|TCP_CLOSING
comma
DECL|typedef|sctp_sock_state_t
)brace
id|sctp_sock_state_t
suffix:semicolon
multiline_comment|/* These functions map various type to printable names.  */
r_const
r_char
op_star
id|sctp_cname
c_func
(paren
r_const
id|sctp_subtype_t
)paren
suffix:semicolon
multiline_comment|/* chunk types */
r_const
r_char
op_star
id|sctp_oname
c_func
(paren
r_const
id|sctp_subtype_t
)paren
suffix:semicolon
multiline_comment|/* other events */
r_const
r_char
op_star
id|sctp_tname
c_func
(paren
r_const
id|sctp_subtype_t
)paren
suffix:semicolon
multiline_comment|/* timeouts */
r_const
r_char
op_star
id|sctp_pname
c_func
(paren
r_const
id|sctp_subtype_t
)paren
suffix:semicolon
multiline_comment|/* primitives */
multiline_comment|/* This is a table of printable names of sctp_state_t&squot;s.  */
r_extern
r_const
r_char
op_star
id|sctp_state_tbl
(braket
)braket
comma
op_star
id|sctp_evttype_tbl
(braket
)braket
comma
op_star
id|sctp_status_tbl
(braket
)braket
suffix:semicolon
multiline_comment|/* SCTP reachability state for each address */
DECL|macro|SCTP_ADDR_NOHB
mdefine_line|#define SCTP_ADDR_NOHB&t;&t;&t;4
DECL|macro|SCTP_ADDR_REACHABLE
mdefine_line|#define SCTP_ADDR_REACHABLE&t;&t;2
DECL|macro|SCTP_ADDR_NOT_REACHABLE
mdefine_line|#define SCTP_ADDR_NOT_REACHABLE&t;&t;1
multiline_comment|/* Guess at how big to make the TSN mapping array.&n; * We guarantee that we can handle at least this big a gap between the&n; * cumulative ACK and the highest TSN.  In practice, we can often&n; * handle up to twice this value.&n; *&n; * NEVER make this more than 32767 (2^15-1).  The Gap Ack Blocks in a&n; * SACK (see  section 3.3.4) are only 16 bits, so 2*SCTP_TSN_MAP_SIZE&n; * must be less than 65535 (2^16 - 1), or we will have overflow&n; * problems creating SACK&squot;s.&n; */
DECL|macro|SCTP_TSN_MAP_SIZE
mdefine_line|#define SCTP_TSN_MAP_SIZE 2048
DECL|macro|SCTP_TSN_MAX_GAP
mdefine_line|#define SCTP_TSN_MAX_GAP  65535
multiline_comment|/* We will not record more than this many duplicate TSNs between two&n; * SACKs.  The minimum PMTU is 576.  Remove all the headers and there&n; * is enough room for 131 duplicate reports.  Round down to the&n; * nearest power of 2.&n; */
DECL|macro|SCTP_MAX_DUP_TSNS
mdefine_line|#define SCTP_MAX_DUP_TSNS 128
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_COUNTER_INIT_ERROR
id|SCTP_COUNTER_INIT_ERROR
comma
DECL|typedef|sctp_counter_t
)brace
id|sctp_counter_t
suffix:semicolon
multiline_comment|/* How many counters does an association need? */
DECL|macro|SCTP_NUMBER_COUNTERS
mdefine_line|#define SCTP_NUMBER_COUNTERS&t;5
multiline_comment|/* Here we define the default timers.  */
multiline_comment|/* cookie timer def = ? seconds */
DECL|macro|SCTP_DEFAULT_TIMEOUT_T1_COOKIE
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_T1_COOKIE&t;(3 * HZ)
multiline_comment|/* init timer def = 3 seconds  */
DECL|macro|SCTP_DEFAULT_TIMEOUT_T1_INIT
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_T1_INIT&t;(3 * HZ)
multiline_comment|/* shutdown timer def = 300 ms */
DECL|macro|SCTP_DEFAULT_TIMEOUT_T2_SHUTDOWN
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_T2_SHUTDOWN ((300 * HZ) / 1000)
multiline_comment|/* 0 seconds + RTO */
DECL|macro|SCTP_DEFAULT_TIMEOUT_HEARTBEAT
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_HEARTBEAT&t;(10 * HZ)
multiline_comment|/* recv timer def = 200ms (in usec) */
DECL|macro|SCTP_DEFAULT_TIMEOUT_SACK
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_SACK&t;((200 * HZ) / 1000)
DECL|macro|SCTP_DEFAULT_TIMEOUT_SACK_MAX
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_SACK_MAX&t;((500 * HZ) / 1000) /* 500 ms */
multiline_comment|/* How long do we wait before attempting to raise the PMTU?  */
DECL|macro|SCTP_DEFAULT_TIMEOUT_PMTU_RAISE
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_PMTU_RAISE (10 * 60 * HZ) /* 10 Minutes */
DECL|macro|SCTP_DEFAULT_TIMEOUT_PMTU_RAISE_MIN
mdefine_line|#define SCTP_DEFAULT_TIMEOUT_PMTU_RAISE_MIN (10 * 60 * HZ) /* 10 Minutes */
multiline_comment|/* RTO.Initial              - 3  seconds&n; * RTO.Min                  - 1  second&n; * RTO.Max                  - 60 seconds&n; * RTO.Alpha                - 1/8&n; * RTO.Beta                 - 1/4&n; */
DECL|macro|SCTP_RTO_INITIAL
mdefine_line|#define SCTP_RTO_INITIAL&t;(3 * HZ)
DECL|macro|SCTP_RTO_MIN
mdefine_line|#define SCTP_RTO_MIN&t;&t;(1 * HZ)
DECL|macro|SCTP_RTO_MAX
mdefine_line|#define SCTP_RTO_MAX&t;&t;(60 * HZ)
DECL|macro|SCTP_RTO_ALPHA
mdefine_line|#define SCTP_RTO_ALPHA          3   /* 1/8 when converted to right shifts. */
DECL|macro|SCTP_RTO_BETA
mdefine_line|#define SCTP_RTO_BETA           2   /* 1/4 when converted to right shifts. */
multiline_comment|/* Maximum number of new data packets that can be sent in a burst.  */
DECL|macro|SCTP_MAX_BURST
mdefine_line|#define SCTP_MAX_BURST&t;&t;4
DECL|macro|SCTP_CLOCK_GRANULARITY
mdefine_line|#define SCTP_CLOCK_GRANULARITY&t;1&t;/* 1 jiffy */
DECL|macro|SCTP_DEF_MAX_INIT
mdefine_line|#define SCTP_DEF_MAX_INIT 6
DECL|macro|SCTP_DEF_MAX_SEND
mdefine_line|#define SCTP_DEF_MAX_SEND 10
DECL|macro|SCTP_DEFAULT_COOKIE_LIFE_SEC
mdefine_line|#define SCTP_DEFAULT_COOKIE_LIFE_SEC&t;60 /* seconds */
DECL|macro|SCTP_DEFAULT_COOKIE_LIFE_USEC
mdefine_line|#define SCTP_DEFAULT_COOKIE_LIFE_USEC&t;0  /* microseconds */
DECL|macro|SCTP_DEFAULT_MINWINDOW
mdefine_line|#define SCTP_DEFAULT_MINWINDOW&t;1500&t;/* default minimum rwnd size */
DECL|macro|SCTP_DEFAULT_MAXWINDOW
mdefine_line|#define SCTP_DEFAULT_MAXWINDOW&t;32768&t;/* default rwnd size */
DECL|macro|SCTP_DEFAULT_MAXSEGMENT
mdefine_line|#define SCTP_DEFAULT_MAXSEGMENT 1500&t;/* MTU size, this is the limit&n;                                         * to which we will raise the P-MTU.&n;&t;&t;&t;&t;&t; */
DECL|macro|SCTP_DEFAULT_MINSEGMENT
mdefine_line|#define SCTP_DEFAULT_MINSEGMENT 512&t;/* MTU size ... if no mtu disc */
DECL|macro|SCTP_HOW_MANY_SECRETS
mdefine_line|#define SCTP_HOW_MANY_SECRETS 2&t;&t;/* How many secrets I keep */
DECL|macro|SCTP_HOW_LONG_COOKIE_LIVE
mdefine_line|#define SCTP_HOW_LONG_COOKIE_LIVE 3600&t;/* How many seconds the current&n;&t;&t;&t;&t;&t; * secret will live?&n;&t;&t;&t;&t;&t; */
DECL|macro|SCTP_SECRET_SIZE
mdefine_line|#define SCTP_SECRET_SIZE 32&t;&t;/* Number of octets in a 256 bits. */
DECL|macro|SCTP_SIGNATURE_SIZE
mdefine_line|#define SCTP_SIGNATURE_SIZE 20&t;        /* size of a SLA-1 signature */
DECL|macro|SCTP_COOKIE_MULTIPLE
mdefine_line|#define SCTP_COOKIE_MULTIPLE 64 /* Pad out our cookie to make our hash&n;&t;&t;&t;&t; * functions simpler to write.&n;&t;&t;&t;&t; */
multiline_comment|/* These return values describe the success or failure of a number of&n; * routines which form the lower interface to SCTP_outqueue.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_XMIT_OK
id|SCTP_XMIT_OK
comma
DECL|enumerator|SCTP_XMIT_PMTU_FULL
id|SCTP_XMIT_PMTU_FULL
comma
DECL|enumerator|SCTP_XMIT_RWND_FULL
id|SCTP_XMIT_RWND_FULL
comma
DECL|enumerator|SCTP_XMIT_MUST_FRAG
id|SCTP_XMIT_MUST_FRAG
comma
DECL|typedef|sctp_xmit_t
)brace
id|sctp_xmit_t
suffix:semicolon
multiline_comment|/* These are the commands for manipulating transports.  */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_TRANSPORT_UP
id|SCTP_TRANSPORT_UP
comma
DECL|enumerator|SCTP_TRANSPORT_DOWN
id|SCTP_TRANSPORT_DOWN
comma
DECL|typedef|sctp_transport_cmd_t
)brace
id|sctp_transport_cmd_t
suffix:semicolon
multiline_comment|/* These are the address scopes defined mainly for IPv4 addresses&n; * based on draft of SCTP IPv4 scoping &lt;draft-stewart-tsvwg-sctp-ipv4-00.txt&gt;.&n; * These scopes are hopefully generic enough to be used on scoping both&n; * IPv4 and IPv6 addresses in SCTP.&n; * At this point, the IPv6 scopes will be mapped to these internal scopes&n; * as much as possible.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_SCOPE_GLOBAL
id|SCTP_SCOPE_GLOBAL
comma
multiline_comment|/* IPv4 global addresses */
DECL|enumerator|SCTP_SCOPE_PRIVATE
id|SCTP_SCOPE_PRIVATE
comma
multiline_comment|/* IPv4 private addresses */
DECL|enumerator|SCTP_SCOPE_LINK
id|SCTP_SCOPE_LINK
comma
multiline_comment|/* IPv4 link local address */
DECL|enumerator|SCTP_SCOPE_LOOPBACK
id|SCTP_SCOPE_LOOPBACK
comma
multiline_comment|/* IPv4 loopback address */
DECL|enumerator|SCTP_SCOPE_UNUSABLE
id|SCTP_SCOPE_UNUSABLE
comma
multiline_comment|/* IPv4 unusable addresses */
DECL|typedef|sctp_scope_t
)brace
id|sctp_scope_t
suffix:semicolon
multiline_comment|/* Based on IPv4 scoping &lt;draft-stewart-tsvwg-sctp-ipv4-00.txt&gt;,&n; * SCTP IPv4 unusable addresses: 0.0.0.0/8, 224.0.0.0/4, 198.18.0.0/24,&n; * 192.88.99.0/24.&n; * Also, RFC 8.4, non-unicast addresses are not considered valid SCTP&n; * addresses.&n; */
DECL|macro|IS_IPV4_UNUSABLE_ADDRESS
mdefine_line|#define IS_IPV4_UNUSABLE_ADDRESS(a) &bslash;&n;&t;((INADDR_BROADCAST == *a) || &bslash;&n;&t;(MULTICAST(*a)) || &bslash;&n;&t;(((unsigned char *)(a))[0] == 0) || &bslash;&n;&t;((((unsigned char *)(a))[0] == 198) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[1] == 18) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[2] == 0)) || &bslash;&n;&t;((((unsigned char *)(a))[0] == 192) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[1] == 88) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[2] == 99)))
multiline_comment|/* IPv4 Link-local addresses: 169.254.0.0/16.  */
DECL|macro|IS_IPV4_LINK_ADDRESS
mdefine_line|#define IS_IPV4_LINK_ADDRESS(a) &bslash;&n;&t;((((unsigned char *)(a))[0] == 169) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[1] == 254))
multiline_comment|/* RFC 1918 &quot;Address Allocation for Private Internets&quot; defines the IPv4&n; * private address space as the following:&n; *&n; * 10.0.0.0 - 10.255.255.255 (10/8 prefix)&n; * 172.16.0.0.0 - 172.31.255.255 (172.16/12 prefix)&n; * 192.168.0.0 - 192.168.255.255 (192.168/16 prefix)&n; */
DECL|macro|IS_IPV4_PRIVATE_ADDRESS
mdefine_line|#define IS_IPV4_PRIVATE_ADDRESS(a) &bslash;&n;&t;((((unsigned char *)(a))[0] == 10) || &bslash;&n;&t;((((unsigned char *)(a))[0] == 172) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[1] &gt;= 16) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[1] &lt; 32)) || &bslash;&n;&t;((((unsigned char *)(a))[0] == 192) &amp;&amp; &bslash;&n;&t;(((unsigned char *)(a))[1] == 168)))
multiline_comment|/* Flags used for the bind address copy functions.  */
DECL|macro|SCTP_ADDR6_ALLOWED
mdefine_line|#define SCTP_ADDR6_ALLOWED&t;0x00000001&t;/* IPv6 address is allowed by&n;&t;&t;&t;&t;&t;&t;   local sock family */
DECL|macro|SCTP_ADDR4_PEERSUPP
mdefine_line|#define SCTP_ADDR4_PEERSUPP&t;0x00000002&t;/* IPv4 address is supported by&n;&t;&t;&t;&t;&t;&t;   peer */
DECL|macro|SCTP_ADDR6_PEERSUPP
mdefine_line|#define SCTP_ADDR6_PEERSUPP&t;0x00000004&t;/* IPv6 address is supported by&n;&t;&t;&t;&t;&t;&t;   peer */
multiline_comment|/* Reasons to lower cwnd. */
r_typedef
r_enum
(brace
DECL|enumerator|SCTP_LOWER_CWND_T3_RTX
id|SCTP_LOWER_CWND_T3_RTX
comma
DECL|enumerator|SCTP_LOWER_CWND_FAST_RTX
id|SCTP_LOWER_CWND_FAST_RTX
comma
DECL|enumerator|SCTP_LOWER_CWND_ECNE
id|SCTP_LOWER_CWND_ECNE
comma
DECL|enumerator|SCTP_LOWER_CWND_INACTIVE
id|SCTP_LOWER_CWND_INACTIVE
comma
DECL|typedef|sctp_lower_cwnd_t
)brace
id|sctp_lower_cwnd_t
suffix:semicolon
macro_line|#endif /* __sctp_constants_h__ */
eof
