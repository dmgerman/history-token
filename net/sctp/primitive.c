multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * These functions implement the SCTP primitive functions from Section 10.&n; *&n; * Note that the descriptions from the specification are USER level&n; * functions--this file is the functions which populate the struct proto&n; * for SCTP which is the BOTTOM of the sockets interface.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Narasimha Budihal     &lt;narasimha@refcode.org&gt;&n; *    Karl Knutson          &lt;karl@athena.chicago.il.us&gt;&n; *    Ardelle Fan&t;    &lt;ardelle.fan@intel.com&gt;&n; *    Kevin Gao             &lt;kevin.gao@intel.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt; /* For struct list_head */
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/time.h&gt; /* For struct timeval */
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
DECL|macro|DECLARE_PRIMITIVE
mdefine_line|#define DECLARE_PRIMITIVE(name) &bslash;&n;/* This is called in the code as sctp_primitive_ ## name.  */ &bslash;&n;int sctp_primitive_ ## name(struct sctp_association *asoc, &bslash;&n;&t;&t;&t;    void *arg) { &bslash;&n;&t;int error = 0; &bslash;&n;&t;sctp_event_t event_type; sctp_subtype_t subtype; &bslash;&n;&t;sctp_state_t state; &bslash;&n;&t;struct sctp_endpoint *ep; &bslash;&n;&t;&bslash;&n;&t;event_type = SCTP_EVENT_T_PRIMITIVE; &bslash;&n;&t;subtype = SCTP_ST_PRIMITIVE(SCTP_PRIMITIVE_ ## name); &bslash;&n;&t;state = asoc ? asoc-&gt;state : SCTP_STATE_CLOSED; &bslash;&n;&t;ep = asoc ? asoc-&gt;ep : NULL; &bslash;&n;&t;&bslash;&n;&t;error = sctp_do_sm(event_type, subtype, state, ep, asoc, &bslash;&n;&t;&t;&t;   arg, GFP_KERNEL); &bslash;&n; &t;return error; &bslash;&n;}
multiline_comment|/* 10.1 ULP-to-SCTP&n; * B) Associate&n; *&n; * Format: ASSOCIATE(local SCTP instance name, destination transport addr,&n; *         outbound stream count)&n; * -&gt; association id [,destination transport addr list] [,outbound stream&n; *    count]&n; *&n; * This primitive allows the upper layer to initiate an association to a&n; * specific peer endpoint.&n; *&n; * This version assumes that asoc is fully populated with the initial&n; * parameters.  We then return a traditional kernel indicator of&n; * success or failure.&n; */
multiline_comment|/* This is called in the code as sctp_primitive_ASSOCIATE.  */
id|DECLARE_PRIMITIVE
c_func
(paren
id|ASSOCIATE
)paren
multiline_comment|/* 10.1 ULP-to-SCTP&n; * C) Shutdown&n; *&n; * Format: SHUTDOWN(association id)&n; * -&gt; result&n; *&n; * Gracefully closes an association. Any locally queued user data&n; * will be delivered to the peer. The association will be terminated only&n; * after the peer acknowledges all the SCTP packets sent.  A success code&n; * will be returned on successful termination of the association. If&n; * attempting to terminate the association results in a failure, an error&n; * code shall be returned.&n; */
id|DECLARE_PRIMITIVE
c_func
(paren
id|SHUTDOWN
)paren
suffix:semicolon
multiline_comment|/* 10.1 ULP-to-SCTP&n; * C) Abort&n; *&n; * Format: Abort(association id [, cause code])&n; * -&gt; result&n; *&n; * Ungracefully closes an association. Any locally queued user data&n; * will be discarded and an ABORT chunk is sent to the peer. A success&n; * code will be returned on successful abortion of the association. If&n; * attempting to abort the association results in a failure, an error&n; * code shall be returned.&n; */
DECL|variable|DECLARE_PRIMITIVE
id|DECLARE_PRIMITIVE
c_func
(paren
id|ABORT
)paren
suffix:semicolon
multiline_comment|/* 10.1 ULP-to-SCTP&n; * E) Send&n; *&n; * Format: SEND(association id, buffer address, byte count [,context]&n; *         [,stream id] [,life time] [,destination transport address]&n; *         [,unorder flag] [,no-bundle flag] [,payload protocol-id] )&n; * -&gt; result&n; *&n; * This is the main method to send user data via SCTP.&n; *&n; * Mandatory attributes:&n; *&n; *  o association id - local handle to the SCTP association&n; *&n; *  o buffer address - the location where the user message to be&n; *    transmitted is stored;&n; *&n; *  o byte count - The size of the user data in number of bytes;&n; *&n; * Optional attributes:&n; *&n; *  o context - an optional 32 bit integer that will be carried in the&n; *    sending failure notification to the ULP if the transportation of&n; *    this User Message fails.&n; *&n; *  o stream id - to indicate which stream to send the data on. If not&n; *    specified, stream 0 will be used.&n; *&n; *  o life time - specifies the life time of the user data. The user data&n; *    will not be sent by SCTP after the life time expires. This&n; *    parameter can be used to avoid efforts to transmit stale&n; *    user messages. SCTP notifies the ULP if the data cannot be&n; *    initiated to transport (i.e. sent to the destination via SCTP&squot;s&n; *    send primitive) within the life time variable. However, the&n; *    user data will be transmitted if SCTP has attempted to transmit a&n; *    chunk before the life time expired.&n; *&n; *  o destination transport address - specified as one of the destination&n; *    transport addresses of the peer endpoint to which this packet&n; *    should be sent. Whenever possible, SCTP should use this destination&n; *    transport address for sending the packets, instead of the current&n; *    primary path.&n; *&n; *  o unorder flag - this flag, if present, indicates that the user&n; *    would like the data delivered in an unordered fashion to the peer&n; *    (i.e., the U flag is set to 1 on all DATA chunks carrying this&n; *    message).&n; *&n; *  o no-bundle flag - instructs SCTP not to bundle this user data with&n; *    other outbound DATA chunks. SCTP MAY still bundle even when&n; *    this flag is present, when faced with network congestion.&n; *&n; *  o payload protocol-id - A 32 bit unsigned integer that is to be&n; *    passed to the peer indicating the type of payload protocol data&n; *    being transmitted. This value is passed as opaque data by SCTP.&n; */
DECL|variable|SEND
id|DECLARE_PRIMITIVE
c_func
(paren
id|SEND
)paren
suffix:semicolon
multiline_comment|/* 10.1 ULP-to-SCTP&n; * J) Request Heartbeat&n; *&n; * Format: REQUESTHEARTBEAT(association id, destination transport address)&n; *&n; * -&gt; result&n; *&n; * Instructs the local endpoint to perform a HeartBeat on the specified&n; * destination transport address of the given association. The returned&n; * result should indicate whether the transmission of the HEARTBEAT&n; * chunk to the destination address is successful.&n; *&n; * Mandatory attributes:&n; *&n; * o association id - local handle to the SCTP association&n; *&n; * o destination transport address - the transport address of the&n; *   association on which a heartbeat should be issued.&n; */
DECL|variable|REQUESTHEARTBEAT
id|DECLARE_PRIMITIVE
c_func
(paren
id|REQUESTHEARTBEAT
)paren
suffix:semicolon
multiline_comment|/* ADDIP&n;* 3.1.1 Address Configuration Change Chunk (ASCONF)&n;* &n;* This chunk is used to communicate to the remote endpoint one of the&n;* configuration change requests that MUST be acknowledged.  The&n;* information carried in the ASCONF Chunk uses the form of a&n;* Type-Length-Value (TLV), as described in &quot;3.2.1 Optional/&n;* Variable-length Parameter Format&quot; in RFC2960 [5], forall variable&n;* parameters.&n;*/
DECL|variable|ASCONF
id|DECLARE_PRIMITIVE
c_func
(paren
id|ASCONF
)paren
suffix:semicolon
eof
