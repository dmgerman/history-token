multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * These functions handle all input from the IP layer into SCTP.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; *    Xingang Guo &lt;xingang.guo@intel.com&gt;&n; *    Jon Grimm &lt;jgrimm@us.ibm.com&gt;&n; *    Hui Huang &lt;hui.huang@nokia.com&gt;&n; *    Daisy Chang &lt;daisyc@us.ibm.com&gt;&n; *    Sridhar Samudrala &lt;sri@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt; /* For struct list_head */
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/time.h&gt; /* For struct timeval */
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/ipsec.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
multiline_comment|/* Forward declarations for internal helpers. */
r_static
r_int
id|sctp_rcv_ootb
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
id|sctp_association_t
op_star
id|__sctp_rcv_lookup
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
id|sockaddr_storage_t
op_star
id|laddr
comma
r_const
id|sockaddr_storage_t
op_star
id|paddr
comma
id|sctp_transport_t
op_star
op_star
id|transportp
)paren
suffix:semicolon
id|sctp_endpoint_t
op_star
id|__sctp_rcv_lookup_endpoint
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
id|laddr
)paren
suffix:semicolon
multiline_comment|/* Initialize a sockaddr_storage from in incoming skb.&n; * FIXME:  This belongs with AF specific sctp_func_t.  --jgrimm&n; */
DECL|function|sctp_sockaddr_storage_init
r_static
id|sockaddr_storage_t
op_star
id|sctp_sockaddr_storage_init
c_func
(paren
id|sockaddr_storage_t
op_star
id|addr
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|is_saddr
)paren
(brace
id|sockaddr_storage_t
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_void
op_star
id|to
comma
op_star
id|saddr
comma
op_star
id|daddr
suffix:semicolon
id|__u16
op_star
id|port
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|sctphdr
op_star
id|sh
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;nh.iph-&gt;version
)paren
(brace
r_case
l_int|4
suffix:colon
id|to
op_assign
op_amp
id|addr-&gt;v4.sin_addr.s_addr
suffix:semicolon
id|port
op_assign
op_amp
id|addr-&gt;v4.sin_port
suffix:semicolon
id|saddr
op_assign
op_amp
id|skb-&gt;nh.iph-&gt;saddr
suffix:semicolon
id|daddr
op_assign
op_amp
id|skb-&gt;nh.iph-&gt;daddr
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
r_struct
id|in_addr
)paren
suffix:semicolon
id|addr-&gt;v4.sin_family
op_assign
id|AF_INET
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|SCTP_V6
c_func
(paren
id|to
op_assign
op_amp
id|addr-&gt;v6.sin6_addr
suffix:semicolon
id|port
op_assign
op_amp
id|addr-&gt;v6.sin6_port
suffix:semicolon
id|saddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
suffix:semicolon
id|daddr
op_assign
op_amp
id|skb-&gt;nh.ipv6h-&gt;daddr
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
r_struct
id|in6_addr
)paren
suffix:semicolon
id|addr-&gt;v6.sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|addr-&gt;v6.sin6_flowinfo
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME */
id|addr-&gt;v6.sin6_scope_id
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME */
r_break
suffix:semicolon
)paren
r_default
suffix:colon
r_goto
id|out
suffix:semicolon
)brace
suffix:semicolon
id|sh
op_assign
(paren
r_struct
id|sctphdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
r_if
c_cond
(paren
id|is_saddr
)paren
(brace
op_star
id|port
op_assign
id|ntohs
c_func
(paren
id|sh-&gt;source
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|to
comma
id|saddr
comma
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|port
op_assign
id|ntohs
c_func
(paren
id|sh-&gt;dest
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|to
comma
id|daddr
comma
id|len
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|addr
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Calculate the SCTP checksum of an SCTP packet.  */
DECL|function|sctp_rcv_checksum
r_static
r_inline
r_int
id|sctp_rcv_checksum
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sctphdr
op_star
id|sh
suffix:semicolon
id|__u32
id|cmp
comma
id|val
suffix:semicolon
id|sh
op_assign
(paren
r_struct
id|sctphdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|cmp
op_assign
id|ntohl
c_func
(paren
id|sh-&gt;checksum
)paren
suffix:semicolon
id|val
op_assign
id|count_crc
c_func
(paren
(paren
id|__u8
op_star
)paren
id|sh
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ne
id|cmp
)paren
(brace
multiline_comment|/* CRC failure, dump it. */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the routine which IP calls when receiving an SCTP packet.&n; */
DECL|function|sctp_rcv
r_int
id|sctp_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
id|sctp_endpoint_t
op_star
id|ep
op_assign
l_int|NULL
suffix:semicolon
id|sctp_endpoint_common_t
op_star
id|rcvr
suffix:semicolon
id|sctp_transport_t
op_star
id|transport
op_assign
l_int|NULL
suffix:semicolon
id|sctp_chunk_t
op_star
id|chunk
suffix:semicolon
r_struct
id|sctphdr
op_star
id|sh
suffix:semicolon
id|sockaddr_storage_t
id|src
suffix:semicolon
id|sockaddr_storage_t
id|dest
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_ne
id|PACKET_HOST
)paren
r_goto
id|discard_it
suffix:semicolon
id|sh
op_assign
(paren
r_struct
id|sctphdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
multiline_comment|/* Pull up the IP and SCTP headers. */
id|__skb_pull
c_func
(paren
id|skb
comma
id|skb-&gt;h.raw
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
r_sizeof
(paren
r_struct
id|sctphdr
)paren
)paren
r_goto
id|bad_packet
suffix:semicolon
r_if
c_cond
(paren
id|sctp_rcv_checksum
c_func
(paren
id|skb
)paren
OL
l_int|0
)paren
r_goto
id|bad_packet
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|sctphdr
)paren
)paren
suffix:semicolon
id|sctp_sockaddr_storage_init
c_func
(paren
op_amp
id|src
comma
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|sctp_sockaddr_storage_init
c_func
(paren
op_amp
id|dest
comma
id|skb
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* If the packet is to or from a non-unicast address,&n;&t; * silently discard the packet.&n;&t; *&n;&t; * This is not clearly defined in the RFC except in section&n;&t; * 8.4 - OOTB handling.  However, based on the book &quot;Stream Control&n;&t; * Transmission Protocol&quot; 2.1, &quot;It is important to note that the&n;&t; * IP address of an SCTP transport address must be a routable&n;&t; * unicast address.  In other words, IP multicast addresses and&n;&t; * IP broadcast addresses cannot be used in an SCTP transport&n;&t; * address.&quot;&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sctp_addr_is_valid
c_func
(paren
op_amp
id|src
)paren
op_logical_or
op_logical_neg
id|sctp_addr_is_valid
c_func
(paren
op_amp
id|dest
)paren
)paren
r_goto
id|discard_it
suffix:semicolon
id|asoc
op_assign
id|__sctp_rcv_lookup
c_func
(paren
id|skb
comma
op_amp
id|src
comma
op_amp
id|dest
comma
op_amp
id|transport
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * RFC 2960, 8.4 - Handle &quot;Out of the blue&quot; Packets.&n;&t; * An SCTP packet is called an &quot;out of the blue&quot; (OOTB)&n;&t; * packet if it is correctly formed, i.e., passed the&n;&t; * receiver&squot;s checksum check, but the receiver is not&n;&t; * able to identify the association to which this&n;&t; * packet belongs.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|asoc
)paren
(brace
id|ep
op_assign
id|__sctp_rcv_lookup_endpoint
c_func
(paren
op_amp
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sctp_rcv_ootb
c_func
(paren
id|skb
)paren
)paren
r_goto
id|discard_release
suffix:semicolon
)brace
multiline_comment|/* Retrieve the common input handling substructure. */
id|rcvr
op_assign
id|asoc
ques
c_cond
op_amp
id|asoc-&gt;base
suffix:colon
op_amp
id|ep-&gt;base
suffix:semicolon
id|sk
op_assign
id|rcvr-&gt;sk
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipsec_sk_policy
c_func
(paren
id|sk
comma
id|skb
)paren
)paren
r_goto
id|discard_release
suffix:semicolon
multiline_comment|/* Create an SCTP packet structure. */
id|chunk
op_assign
id|sctp_chunkify
c_func
(paren
id|skb
comma
id|asoc
comma
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chunk
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|discard_release
suffix:semicolon
)brace
multiline_comment|/* Remember what endpoint is to handle this packet. */
id|chunk-&gt;rcvr
op_assign
id|rcvr
suffix:semicolon
multiline_comment|/* Remember the SCTP header. */
id|chunk-&gt;sctp_hdr
op_assign
id|sh
suffix:semicolon
multiline_comment|/* Set the source and destination addresses of the incoming chunk.  */
id|sctp_init_addrs
c_func
(paren
id|chunk
)paren
suffix:semicolon
multiline_comment|/* Remember where we came from.  */
id|chunk-&gt;transport
op_assign
id|transport
suffix:semicolon
multiline_comment|/* Acquire access to the sock lock. Note: We are safe from other&n;&t; * bottom halves on this lock, but a user may be in the lock too,&n;&t; * so check if it is busy.&n;&t; */
id|sctp_bh_lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock_owned_by_user
c_func
(paren
id|sk
)paren
)paren
(brace
id|sk_add_backlog
c_func
(paren
id|sk
comma
(paren
r_struct
id|sk_buff
op_star
)paren
id|chunk
)paren
suffix:semicolon
)brace
r_else
(brace
id|sctp_backlog_rcv
c_func
(paren
id|sk
comma
(paren
r_struct
id|sk_buff
op_star
)paren
id|chunk
)paren
suffix:semicolon
)brace
multiline_comment|/* Release the sock and any reference counts we took in the&n;&t; * lookup calls.&n;&t; */
id|sctp_bh_unlock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|asoc
)paren
(brace
id|sctp_association_put
c_func
(paren
id|asoc
)paren
suffix:semicolon
)brace
r_else
(brace
id|sctp_endpoint_put
c_func
(paren
id|ep
)paren
suffix:semicolon
)brace
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|bad_packet
suffix:colon
macro_line|#if 0 /* FIXME */
id|SCTP_INC_STATS
c_func
(paren
id|SctpInErrs
)paren
suffix:semicolon
macro_line|#endif /* FIXME*/
id|discard_it
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|discard_release
suffix:colon
multiline_comment|/* Release any structures we may be holding. */
r_if
c_cond
(paren
id|asoc
)paren
(brace
id|sock_put
c_func
(paren
id|asoc-&gt;base.sk
)paren
suffix:semicolon
id|sctp_association_put
c_func
(paren
id|asoc
)paren
suffix:semicolon
)brace
r_else
(brace
id|sock_put
c_func
(paren
id|ep-&gt;base.sk
)paren
suffix:semicolon
id|sctp_endpoint_put
c_func
(paren
id|ep
)paren
suffix:semicolon
)brace
r_goto
id|discard_it
suffix:semicolon
)brace
multiline_comment|/* Handle second half of inbound skb processing.  If the sock was busy,&n; * we may have need to delay processing until later when the sock is&n; * released (on the backlog).   If not busy, we call this routine&n; * directly from the bottom half.&n; */
DECL|function|sctp_backlog_rcv
r_int
id|sctp_backlog_rcv
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|sctp_chunk_t
op_star
id|chunk
suffix:semicolon
id|sctp_inqueue_t
op_star
id|inqueue
suffix:semicolon
multiline_comment|/* One day chunk will live inside the skb, but for&n;&t; * now this works.&n;&t; */
id|chunk
op_assign
(paren
id|sctp_chunk_t
op_star
)paren
id|skb
suffix:semicolon
id|inqueue
op_assign
op_amp
id|chunk-&gt;rcvr-&gt;inqueue
suffix:semicolon
id|sctp_push_inqueue
c_func
(paren
id|inqueue
comma
id|chunk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called by the ICMP module when it gets some&n; * sort of error condition.  If err &lt; 0 then the socket should&n; * be closed and the error returned to the user.  If err &gt; 0&n; * it&squot;s just the icmp type &lt;&lt; 8 | icmp code.  After adjustment&n; * header points to the first 8 bytes of the sctp header.  We need&n; * to find the appropriate port.&n; *&n; * The locking strategy used here is very &quot;optimistic&quot;. When&n; * someone else accesses the socket the ICMP is just dropped&n; * and for some paths there is no check at all.&n; * A more general error queue to queue errors for later handling&n; * is probably better.&n; *&n; */
DECL|function|sctp_v4_err
r_void
id|sctp_v4_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|info
)paren
(brace
multiline_comment|/* This should probably involve a call to SCTPhandleICMP().  */
)brace
multiline_comment|/*&n; * RFC 2960, 8.4 - Handle &quot;Out of the blue&quot; Packets.&n; *&n; * This function scans all the chunks in the OOTB packet to determine if&n; * the packet should be discarded right away.  If a response might be needed&n; * for this packet, or, if further processing is possible, the packet will&n; * be queued to a proper inqueue for the next phase of handling.&n; *&n; * Output:&n; * Return 0 - If further processing is needed.&n; * Return 1 - If the packet can be discarded right away.&n; */
DECL|function|sctp_rcv_ootb
r_int
id|sctp_rcv_ootb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|sctp_chunkhdr_t
op_star
id|ch
suffix:semicolon
id|__u8
op_star
id|ch_end
suffix:semicolon
id|ch
op_assign
(paren
id|sctp_chunkhdr_t
op_star
)paren
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* Scan through all the chunks in the packet.  */
r_do
(brace
id|ch_end
op_assign
(paren
(paren
id|__u8
op_star
)paren
id|ch
)paren
op_plus
id|WORD_ROUND
c_func
(paren
id|ntohs
c_func
(paren
id|ch-&gt;length
)paren
)paren
suffix:semicolon
multiline_comment|/* RFC 8.4, 2) If the OOTB packet contains an ABORT chunk, the&n;&t;&t; * receiver MUST silently discard the OOTB packet and take no&n;&t;&t; * further action.&n;&t;&t; */
r_if
c_cond
(paren
id|SCTP_CID_ABORT
op_eq
id|ch-&gt;type
)paren
r_goto
id|discard
suffix:semicolon
multiline_comment|/* RFC 8.4, 6) If the packet contains a SHUTDOWN COMPLETE&n;&t;&t; * chunk, the receiver should silently discard the packet&n;&t;&t; * and take no further action.&n;&t;&t; */
r_if
c_cond
(paren
id|ch-&gt;type
op_eq
id|SCTP_CID_SHUTDOWN_COMPLETE
)paren
r_goto
id|discard
suffix:semicolon
multiline_comment|/* RFC 8.4, 7) If the packet contains a &quot;Stale cookie&quot; ERROR&n;&t;&t; * or a COOKIE ACK the SCTP Packet should be silently&n;&t;&t; * discarded.&n;&t;&t; */
r_if
c_cond
(paren
id|ch-&gt;type
op_eq
id|SCTP_CID_COOKIE_ACK
)paren
r_goto
id|discard
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;type
op_eq
id|SCTP_CID_ERROR
)paren
(brace
multiline_comment|/* FIXME - Need to check the &quot;Stale cookie&quot; ERROR. */
r_goto
id|discard
suffix:semicolon
)brace
id|ch
op_assign
(paren
id|sctp_chunkhdr_t
op_star
)paren
id|ch_end
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ch_end
OL
id|skb-&gt;tail
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|discard
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Insert endpoint into the hash table.  */
DECL|function|__sctp_hash_endpoint
r_void
id|__sctp_hash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
id|ep
)paren
(brace
id|sctp_endpoint_common_t
op_star
op_star
id|epp
suffix:semicolon
id|sctp_endpoint_common_t
op_star
id|epb
suffix:semicolon
id|sctp_hashbucket_t
op_star
id|head
suffix:semicolon
id|epb
op_assign
op_amp
id|ep-&gt;base
suffix:semicolon
id|epb-&gt;hashent
op_assign
id|sctp_ep_hashfn
c_func
(paren
id|epb-&gt;bind_addr.port
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|sctp_proto.ep_hashbucket
(braket
id|epb-&gt;hashent
)braket
suffix:semicolon
id|sctp_write_lock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
id|epp
op_assign
op_amp
id|head-&gt;chain
suffix:semicolon
id|epb-&gt;next
op_assign
op_star
id|epp
suffix:semicolon
r_if
c_cond
(paren
id|epb-&gt;next
)paren
(paren
op_star
id|epp
)paren
op_member_access_from_pointer
id|pprev
op_assign
op_amp
id|epb-&gt;next
suffix:semicolon
op_star
id|epp
op_assign
id|epb
suffix:semicolon
id|epb-&gt;pprev
op_assign
id|epp
suffix:semicolon
id|sctp_write_unlock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Add an endpoint to the hash. Local BH-safe. */
DECL|function|sctp_hash_endpoint
r_void
id|sctp_hash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
id|ep
)paren
(brace
id|sctp_local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|__sctp_hash_endpoint
c_func
(paren
id|ep
)paren
suffix:semicolon
id|sctp_local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove endpoint from the hash table.  */
DECL|function|__sctp_unhash_endpoint
r_void
id|__sctp_unhash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
id|ep
)paren
(brace
id|sctp_hashbucket_t
op_star
id|head
suffix:semicolon
id|sctp_endpoint_common_t
op_star
id|epb
suffix:semicolon
id|epb
op_assign
op_amp
id|ep-&gt;base
suffix:semicolon
id|epb-&gt;hashent
op_assign
id|sctp_ep_hashfn
c_func
(paren
id|epb-&gt;bind_addr.port
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|sctp_proto.ep_hashbucket
(braket
id|epb-&gt;hashent
)braket
suffix:semicolon
id|sctp_write_lock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|epb-&gt;pprev
)paren
(brace
r_if
c_cond
(paren
id|epb-&gt;next
)paren
id|epb-&gt;next-&gt;pprev
op_assign
id|epb-&gt;pprev
suffix:semicolon
op_star
id|epb-&gt;pprev
op_assign
id|epb-&gt;next
suffix:semicolon
id|epb-&gt;pprev
op_assign
l_int|NULL
suffix:semicolon
)brace
id|sctp_write_unlock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove endpoint from the hash.  Local BH-safe. */
DECL|function|sctp_unhash_endpoint
r_void
id|sctp_unhash_endpoint
c_func
(paren
id|sctp_endpoint_t
op_star
id|ep
)paren
(brace
id|sctp_local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|__sctp_unhash_endpoint
c_func
(paren
id|ep
)paren
suffix:semicolon
id|sctp_local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Look up an endpoint. */
DECL|function|__sctp_rcv_lookup_endpoint
id|sctp_endpoint_t
op_star
id|__sctp_rcv_lookup_endpoint
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
id|laddr
)paren
(brace
id|sctp_hashbucket_t
op_star
id|head
suffix:semicolon
id|sctp_endpoint_common_t
op_star
id|epb
suffix:semicolon
id|sctp_endpoint_t
op_star
id|ep
suffix:semicolon
r_int
id|hash
suffix:semicolon
id|hash
op_assign
id|sctp_ep_hashfn
c_func
(paren
id|laddr-&gt;v4.sin_port
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|sctp_proto.ep_hashbucket
(braket
id|hash
)braket
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|epb
op_assign
id|head-&gt;chain
suffix:semicolon
id|epb
suffix:semicolon
id|epb
op_assign
id|epb-&gt;next
)paren
(brace
id|ep
op_assign
id|sctp_ep
c_func
(paren
id|epb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sctp_endpoint_is_match
c_func
(paren
id|ep
comma
id|laddr
)paren
)paren
r_goto
id|hit
suffix:semicolon
)brace
id|ep
op_assign
id|sctp_sk
c_func
(paren
(paren
id|sctp_get_ctl_sock
c_func
(paren
)paren
)paren
)paren
op_member_access_from_pointer
id|ep
suffix:semicolon
id|epb
op_assign
op_amp
id|ep-&gt;base
suffix:semicolon
id|hit
suffix:colon
id|sctp_endpoint_hold
c_func
(paren
id|ep
)paren
suffix:semicolon
id|sock_hold
c_func
(paren
id|epb-&gt;sk
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_return
id|ep
suffix:semicolon
)brace
multiline_comment|/* Add an association to the hash. Local BH-safe. */
DECL|function|sctp_hash_established
r_void
id|sctp_hash_established
c_func
(paren
id|sctp_association_t
op_star
id|asoc
)paren
(brace
id|sctp_local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|__sctp_hash_established
c_func
(paren
id|asoc
)paren
suffix:semicolon
id|sctp_local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Insert association into the hash table.  */
DECL|function|__sctp_hash_established
r_void
id|__sctp_hash_established
c_func
(paren
id|sctp_association_t
op_star
id|asoc
)paren
(brace
id|sctp_endpoint_common_t
op_star
op_star
id|epp
suffix:semicolon
id|sctp_endpoint_common_t
op_star
id|epb
suffix:semicolon
id|sctp_hashbucket_t
op_star
id|head
suffix:semicolon
id|epb
op_assign
op_amp
id|asoc-&gt;base
suffix:semicolon
multiline_comment|/* Calculate which chain this entry will belong to. */
id|epb-&gt;hashent
op_assign
id|sctp_assoc_hashfn
c_func
(paren
id|epb-&gt;bind_addr.port
comma
id|asoc-&gt;peer.port
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|sctp_proto.assoc_hashbucket
(braket
id|epb-&gt;hashent
)braket
suffix:semicolon
id|sctp_write_lock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
id|epp
op_assign
op_amp
id|head-&gt;chain
suffix:semicolon
id|epb-&gt;next
op_assign
op_star
id|epp
suffix:semicolon
r_if
c_cond
(paren
id|epb-&gt;next
)paren
(paren
op_star
id|epp
)paren
op_member_access_from_pointer
id|pprev
op_assign
op_amp
id|epb-&gt;next
suffix:semicolon
op_star
id|epp
op_assign
id|epb
suffix:semicolon
id|epb-&gt;pprev
op_assign
id|epp
suffix:semicolon
id|sctp_write_unlock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove association from the hash table.  Local BH-safe. */
DECL|function|sctp_unhash_established
r_void
id|sctp_unhash_established
c_func
(paren
id|sctp_association_t
op_star
id|asoc
)paren
(brace
id|sctp_local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|__sctp_unhash_established
c_func
(paren
id|asoc
)paren
suffix:semicolon
id|sctp_local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove association from the hash table.  */
DECL|function|__sctp_unhash_established
r_void
id|__sctp_unhash_established
c_func
(paren
id|sctp_association_t
op_star
id|asoc
)paren
(brace
id|sctp_hashbucket_t
op_star
id|head
suffix:semicolon
id|sctp_endpoint_common_t
op_star
id|epb
suffix:semicolon
id|epb
op_assign
op_amp
id|asoc-&gt;base
suffix:semicolon
id|epb-&gt;hashent
op_assign
id|sctp_assoc_hashfn
c_func
(paren
id|epb-&gt;bind_addr.port
comma
id|asoc-&gt;peer.port
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|sctp_proto.assoc_hashbucket
(braket
id|epb-&gt;hashent
)braket
suffix:semicolon
id|sctp_write_lock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|epb-&gt;pprev
)paren
(brace
r_if
c_cond
(paren
id|epb-&gt;next
)paren
id|epb-&gt;next-&gt;pprev
op_assign
id|epb-&gt;pprev
suffix:semicolon
op_star
id|epb-&gt;pprev
op_assign
id|epb-&gt;next
suffix:semicolon
id|epb-&gt;pprev
op_assign
l_int|NULL
suffix:semicolon
)brace
id|sctp_write_unlock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Look up an association. */
DECL|function|__sctp_lookup_association
id|sctp_association_t
op_star
id|__sctp_lookup_association
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
id|laddr
comma
r_const
id|sockaddr_storage_t
op_star
id|paddr
comma
id|sctp_transport_t
op_star
op_star
id|transportp
)paren
(brace
id|sctp_hashbucket_t
op_star
id|head
suffix:semicolon
id|sctp_endpoint_common_t
op_star
id|epb
suffix:semicolon
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
id|sctp_transport_t
op_star
id|transport
suffix:semicolon
r_int
id|hash
suffix:semicolon
multiline_comment|/* Optimize here for direct hit, only listening connections can&n;&t; * have wildcards anyways.&n;&t; */
id|hash
op_assign
id|sctp_assoc_hashfn
c_func
(paren
id|laddr-&gt;v4.sin_port
comma
id|paddr-&gt;v4.sin_port
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|sctp_proto.assoc_hashbucket
(braket
id|hash
)braket
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|epb
op_assign
id|head-&gt;chain
suffix:semicolon
id|epb
suffix:semicolon
id|epb
op_assign
id|epb-&gt;next
)paren
(brace
id|asoc
op_assign
id|sctp_assoc
c_func
(paren
id|epb
)paren
suffix:semicolon
id|transport
op_assign
id|sctp_assoc_is_match
c_func
(paren
id|asoc
comma
id|laddr
comma
id|paddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transport
)paren
r_goto
id|hit
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
id|hit
suffix:colon
op_star
id|transportp
op_assign
id|transport
suffix:semicolon
id|sctp_association_hold
c_func
(paren
id|asoc
)paren
suffix:semicolon
id|sock_hold
c_func
(paren
id|epb-&gt;sk
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|head-&gt;lock
)paren
suffix:semicolon
r_return
id|asoc
suffix:semicolon
)brace
multiline_comment|/* Look up an association. BH-safe. */
DECL|function|sctp_lookup_association
id|sctp_association_t
op_star
id|sctp_lookup_association
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
id|laddr
comma
r_const
id|sockaddr_storage_t
op_star
id|paddr
comma
id|sctp_transport_t
op_star
op_star
id|transportp
)paren
(brace
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
id|sctp_local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|asoc
op_assign
id|__sctp_lookup_association
c_func
(paren
id|laddr
comma
id|paddr
comma
id|transportp
)paren
suffix:semicolon
id|sctp_local_bh_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|asoc
suffix:semicolon
)brace
multiline_comment|/* Is there an association matching the given local and peer addresses? */
DECL|function|sctp_has_association
r_int
id|sctp_has_association
c_func
(paren
r_const
id|sockaddr_storage_t
op_star
id|laddr
comma
r_const
id|sockaddr_storage_t
op_star
id|paddr
)paren
(brace
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
id|sctp_transport_t
op_star
id|transport
suffix:semicolon
r_if
c_cond
(paren
(paren
id|asoc
op_assign
id|sctp_lookup_association
c_func
(paren
id|laddr
comma
id|paddr
comma
op_amp
id|transport
)paren
)paren
)paren
(brace
id|sock_put
c_func
(paren
id|asoc-&gt;base.sk
)paren
suffix:semicolon
id|sctp_association_put
c_func
(paren
id|asoc
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * SCTP Implementors Guide, 2.18 Handling of address&n; * parameters within the INIT or INIT-ACK.&n; *&n; * D) When searching for a matching TCB upon reception of an INIT&n; *    or INIT-ACK chunk the receiver SHOULD use not only the&n; *    source address of the packet (containing the INIT or&n; *    INIT-ACK) but the receiver SHOULD also use all valid&n; *    address parameters contained within the chunk.&n; *&n; * 2.18.3 Solution description&n; *&n; * This new text clearly specifies to an implementor the need&n; * to look within the INIT or INIT-ACK. Any implementation that&n; * does not do this, may not be able to establish associations&n; * in certain circumstances.&n; *&n; */
DECL|function|__sctp_rcv_initack_lookup
r_static
id|sctp_association_t
op_star
id|__sctp_rcv_initack_lookup
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
id|sockaddr_storage_t
op_star
id|laddr
comma
id|sctp_transport_t
op_star
op_star
id|transportp
)paren
(brace
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
id|sockaddr_storage_t
id|addr
suffix:semicolon
id|sockaddr_storage_t
op_star
id|paddr
op_assign
op_amp
id|addr
suffix:semicolon
r_struct
id|sctphdr
op_star
id|sh
op_assign
(paren
r_struct
id|sctphdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|sctp_chunkhdr_t
op_star
id|ch
suffix:semicolon
id|__u8
op_star
id|ch_end
comma
op_star
id|data
suffix:semicolon
id|sctp_paramhdr_t
op_star
id|parm
suffix:semicolon
id|ch
op_assign
(paren
id|sctp_chunkhdr_t
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|ch_end
op_assign
(paren
(paren
id|__u8
op_star
)paren
id|ch
)paren
op_plus
id|WORD_ROUND
c_func
(paren
id|ntohs
c_func
(paren
id|ch-&gt;length
)paren
)paren
suffix:semicolon
multiline_comment|/* If this is INIT/INIT-ACK look inside the chunk too. */
r_switch
c_cond
(paren
id|ch-&gt;type
)paren
(brace
r_case
id|SCTP_CID_INIT
suffix:colon
r_case
id|SCTP_CID_INIT_ACK
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This code will NOT touch anything inside the chunk--it is&n;&t; * strictly READ-ONLY.&n;&t; *&n;&t; * RFC 2960 3  SCTP packet Format&n;&t; *&n;&t; * Multiple chunks can be bundled into one SCTP packet up to&n;&t; * the MTU size, except for the INIT, INIT ACK, and SHUTDOWN&n;&t; * COMPLETE chunks.  These chunks MUST NOT be bundled with any&n;&t; * other chunk in a packet.  See Section 6.10 for more details&n;&t; * on chunk bundling.&n;&t; */
multiline_comment|/* Find the start of the TLVs and the end of the chunk.  This is&n;&t; * the region we search for address parameters.&n;&t; */
id|data
op_assign
id|skb-&gt;data
op_plus
r_sizeof
(paren
id|sctp_init_chunk_t
)paren
suffix:semicolon
multiline_comment|/* See sctp_process_init() for how to go thru TLVs. */
r_while
c_loop
(paren
id|data
OL
id|ch_end
)paren
(brace
id|parm
op_assign
(paren
id|sctp_paramhdr_t
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parm-&gt;length
)paren
r_break
suffix:semicolon
id|data
op_add_assign
id|WORD_ROUND
c_func
(paren
id|ntohs
c_func
(paren
id|parm-&gt;length
)paren
)paren
suffix:semicolon
multiline_comment|/* Note: Ignoring hostname addresses. */
r_if
c_cond
(paren
(paren
id|SCTP_PARAM_IPV4_ADDRESS
op_ne
id|parm-&gt;type
)paren
op_logical_and
(paren
id|SCTP_PARAM_IPV6_ADDRESS
op_ne
id|parm-&gt;type
)paren
)paren
r_continue
suffix:semicolon
id|sctp_param2sockaddr
c_func
(paren
id|paddr
comma
(paren
id|sctp_addr_param_t
op_star
)paren
id|parm
comma
id|ntohs
c_func
(paren
id|sh-&gt;source
)paren
)paren
suffix:semicolon
id|asoc
op_assign
id|__sctp_lookup_association
c_func
(paren
id|laddr
comma
id|paddr
comma
id|transportp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|asoc
)paren
r_return
id|asoc
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Lookup an association for an inbound skb. */
DECL|function|__sctp_rcv_lookup
id|sctp_association_t
op_star
id|__sctp_rcv_lookup
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
id|sockaddr_storage_t
op_star
id|paddr
comma
r_const
id|sockaddr_storage_t
op_star
id|laddr
comma
id|sctp_transport_t
op_star
op_star
id|transportp
)paren
(brace
id|sctp_association_t
op_star
id|asoc
suffix:semicolon
id|asoc
op_assign
id|__sctp_lookup_association
c_func
(paren
id|laddr
comma
id|paddr
comma
id|transportp
)paren
suffix:semicolon
multiline_comment|/* Further lookup for INIT-ACK packet.&n;&t; * SCTP Implementors Guide, 2.18 Handling of address&n;&t; * parameters within the INIT or INIT-ACK.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|asoc
)paren
id|asoc
op_assign
id|__sctp_rcv_initack_lookup
c_func
(paren
id|skb
comma
id|laddr
comma
id|transportp
)paren
suffix:semicolon
r_return
id|asoc
suffix:semicolon
)brace
eof
