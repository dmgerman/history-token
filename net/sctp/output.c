multiline_comment|/* SCTP kernel reference Implementation&n; * (C) Copyright IBM Corp. 2001, 2004&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * These functions handle output processing.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson          &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm             &lt;jgrimm@austin.ibm.com&gt;&n; *    Sridhar Samudrala     &lt;sri@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/inet_ecn.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#ifndef TEST_FRAME
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#endif /* TEST_FRAME (not defined) */
macro_line|#include &lt;linux/socket.h&gt; /* for sa_family_t */
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
multiline_comment|/* Forward declarations for private helpers. */
r_static
id|sctp_xmit_t
id|sctp_packet_append_data
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
comma
r_struct
id|sctp_chunk
op_star
id|chunk
)paren
suffix:semicolon
multiline_comment|/* Config a packet.&n; * This appears to be a followup set of initializations.&n; */
DECL|function|sctp_packet_config
r_struct
id|sctp_packet
op_star
id|sctp_packet_config
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
comma
id|__u32
id|vtag
comma
r_int
id|ecn_capable
)paren
(brace
r_struct
id|sctp_chunk
op_star
id|chunk
op_assign
l_int|NULL
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: packet:%p vtag:0x%x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|packet
comma
id|vtag
)paren
suffix:semicolon
id|packet-&gt;vtag
op_assign
id|vtag
suffix:semicolon
id|packet-&gt;has_cookie_echo
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;has_sack
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;ipfragok
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ecn_capable
op_logical_and
id|sctp_packet_empty
c_func
(paren
id|packet
)paren
)paren
(brace
id|chunk
op_assign
id|sctp_get_ecne_prepend
c_func
(paren
id|packet-&gt;transport-&gt;asoc
)paren
suffix:semicolon
multiline_comment|/* If there a is a prepend chunk stick it on the list before&n;&t; &t; * any other chunks get appended.&n;&t; &t; */
r_if
c_cond
(paren
id|chunk
)paren
id|sctp_packet_append_chunk
c_func
(paren
id|packet
comma
id|chunk
)paren
suffix:semicolon
)brace
r_return
id|packet
suffix:semicolon
)brace
multiline_comment|/* Initialize the packet structure. */
DECL|function|sctp_packet_init
r_struct
id|sctp_packet
op_star
id|sctp_packet_init
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
comma
r_struct
id|sctp_transport
op_star
id|transport
comma
id|__u16
id|sport
comma
id|__u16
id|dport
)paren
(brace
r_struct
id|sctp_association
op_star
id|asoc
op_assign
id|transport-&gt;asoc
suffix:semicolon
r_int
id|overhead
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: packet:%p transport:%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|packet
comma
id|transport
)paren
suffix:semicolon
id|packet-&gt;transport
op_assign
id|transport
suffix:semicolon
id|packet-&gt;source_port
op_assign
id|sport
suffix:semicolon
id|packet-&gt;destination_port
op_assign
id|dport
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|packet-&gt;chunks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|asoc
)paren
(brace
r_struct
id|sctp_opt
op_star
id|sp
op_assign
id|sctp_sk
c_func
(paren
id|asoc-&gt;base.sk
)paren
suffix:semicolon
id|overhead
op_assign
id|sp-&gt;pf-&gt;af-&gt;net_header_len
suffix:semicolon
)brace
r_else
(brace
id|overhead
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
)brace
id|overhead
op_add_assign
r_sizeof
(paren
r_struct
id|sctphdr
)paren
suffix:semicolon
id|packet-&gt;overhead
op_assign
id|overhead
suffix:semicolon
id|packet-&gt;size
op_assign
id|overhead
suffix:semicolon
id|packet-&gt;vtag
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;has_cookie_echo
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;has_sack
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;ipfragok
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;malloced
op_assign
l_int|0
suffix:semicolon
r_return
id|packet
suffix:semicolon
)brace
multiline_comment|/* Free a packet.  */
DECL|function|sctp_packet_free
r_void
id|sctp_packet_free
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
)paren
(brace
r_struct
id|sctp_chunk
op_star
id|chunk
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: packet:%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|packet
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|chunk
op_assign
(paren
r_struct
id|sctp_chunk
op_star
)paren
id|__skb_dequeue
c_func
(paren
op_amp
id|packet-&gt;chunks
)paren
)paren
)paren
id|sctp_chunk_free
c_func
(paren
id|chunk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|packet-&gt;malloced
)paren
id|kfree
c_func
(paren
id|packet
)paren
suffix:semicolon
)brace
multiline_comment|/* This routine tries to append the chunk to the offered packet. If adding&n; * the chunk causes the packet to exceed the path MTU and COOKIE_ECHO chunk&n; * is not present in the packet, it transmits the input packet.&n; * Data can be bundled with a packet containing a COOKIE_ECHO chunk as long&n; * as it can fit in the packet, but any more data that does not fit in this&n; * packet can be sent only after receiving the COOKIE_ACK.&n; */
DECL|function|sctp_packet_transmit_chunk
id|sctp_xmit_t
id|sctp_packet_transmit_chunk
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
comma
r_struct
id|sctp_chunk
op_star
id|chunk
)paren
(brace
id|sctp_xmit_t
id|retval
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: packet:%p chunk:%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|packet
comma
id|chunk
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|retval
op_assign
(paren
id|sctp_packet_append_chunk
c_func
(paren
id|packet
comma
id|chunk
)paren
)paren
)paren
)paren
(brace
r_case
id|SCTP_XMIT_PMTU_FULL
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|packet-&gt;has_cookie_echo
)paren
(brace
id|error
op_assign
id|sctp_packet_transmit
c_func
(paren
id|packet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
id|chunk-&gt;skb-&gt;sk-&gt;sk_err
op_assign
op_minus
id|error
suffix:semicolon
multiline_comment|/* If we have an empty packet, then we can NOT ever&n;&t;&t;&t; * return PMTU_FULL.&n;&t;&t;&t; */
id|retval
op_assign
id|sctp_packet_append_chunk
c_func
(paren
id|packet
comma
id|chunk
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SCTP_XMIT_RWND_FULL
suffix:colon
r_case
id|SCTP_XMIT_OK
suffix:colon
r_case
id|SCTP_XMIT_NAGLE_DELAY
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Try to bundle a SACK with the packet. */
DECL|function|sctp_packet_bundle_sack
r_static
id|sctp_xmit_t
id|sctp_packet_bundle_sack
c_func
(paren
r_struct
id|sctp_packet
op_star
id|pkt
comma
r_struct
id|sctp_chunk
op_star
id|chunk
)paren
(brace
id|sctp_xmit_t
id|retval
op_assign
id|SCTP_XMIT_OK
suffix:semicolon
multiline_comment|/* If sending DATA and haven&squot;t aleady bundled a SACK, try to&n;&t; * bundle one in to the packet.&n;&t; */
r_if
c_cond
(paren
id|sctp_chunk_is_data
c_func
(paren
id|chunk
)paren
op_logical_and
op_logical_neg
id|pkt-&gt;has_sack
op_logical_and
op_logical_neg
id|pkt-&gt;has_cookie_echo
)paren
(brace
r_struct
id|sctp_association
op_star
id|asoc
suffix:semicolon
id|asoc
op_assign
id|pkt-&gt;transport-&gt;asoc
suffix:semicolon
r_if
c_cond
(paren
id|asoc-&gt;a_rwnd
OG
id|asoc-&gt;rwnd
)paren
(brace
r_struct
id|sctp_chunk
op_star
id|sack
suffix:semicolon
id|asoc-&gt;a_rwnd
op_assign
id|asoc-&gt;rwnd
suffix:semicolon
id|sack
op_assign
id|sctp_make_sack
c_func
(paren
id|asoc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sack
)paren
(brace
r_struct
id|timer_list
op_star
id|timer
suffix:semicolon
id|retval
op_assign
id|sctp_packet_append_chunk
c_func
(paren
id|pkt
comma
id|sack
)paren
suffix:semicolon
id|asoc-&gt;peer.sack_needed
op_assign
l_int|0
suffix:semicolon
id|timer
op_assign
op_amp
id|asoc-&gt;timers
(braket
id|SCTP_EVENT_TIMEOUT_SACK
)braket
suffix:semicolon
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
id|timer
)paren
op_logical_and
id|del_timer
c_func
(paren
id|timer
)paren
)paren
id|sctp_association_put
c_func
(paren
id|asoc
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Append a chunk to the offered packet reporting back any inability to do&n; * so.&n; */
DECL|function|sctp_packet_append_chunk
id|sctp_xmit_t
id|sctp_packet_append_chunk
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
comma
r_struct
id|sctp_chunk
op_star
id|chunk
)paren
(brace
id|sctp_xmit_t
id|retval
op_assign
id|SCTP_XMIT_OK
suffix:semicolon
id|__u16
id|chunk_len
op_assign
id|WORD_ROUND
c_func
(paren
id|ntohs
c_func
(paren
id|chunk-&gt;chunk_hdr-&gt;length
)paren
)paren
suffix:semicolon
r_int
id|psize
suffix:semicolon
r_int
id|pmtu
suffix:semicolon
r_int
id|too_big
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: packet:%p chunk:%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|packet
comma
id|chunk
)paren
suffix:semicolon
id|retval
op_assign
id|sctp_packet_bundle_sack
c_func
(paren
id|packet
comma
id|chunk
)paren
suffix:semicolon
id|psize
op_assign
id|packet-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
id|SCTP_XMIT_OK
)paren
r_goto
id|finish
suffix:semicolon
id|pmtu
op_assign
(paren
(paren
id|packet-&gt;transport-&gt;asoc
)paren
ques
c_cond
(paren
id|packet-&gt;transport-&gt;asoc-&gt;pmtu
)paren
suffix:colon
(paren
id|packet-&gt;transport-&gt;pmtu
)paren
)paren
suffix:semicolon
id|too_big
op_assign
(paren
id|psize
op_plus
id|chunk_len
OG
id|pmtu
)paren
suffix:semicolon
multiline_comment|/* Decide if we need to fragment or resubmit later. */
r_if
c_cond
(paren
id|too_big
)paren
(brace
multiline_comment|/* Both control chunks and data chunks with TSNs are&n;&t;&t; * non-fragmentable.&n;&t;&t; */
r_if
c_cond
(paren
id|sctp_packet_empty
c_func
(paren
id|packet
)paren
op_logical_or
op_logical_neg
id|sctp_chunk_is_data
c_func
(paren
id|chunk
)paren
)paren
(brace
multiline_comment|/* We no longer do re-fragmentation.&n;&t;&t;&t; * Just fragment at the IP layer, if we&n;&t;&t;&t; * actually hit this condition&n;&t;&t;&t; */
id|packet-&gt;ipfragok
op_assign
l_int|1
suffix:semicolon
r_goto
id|append
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
id|SCTP_XMIT_PMTU_FULL
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
)brace
id|append
suffix:colon
multiline_comment|/* We believe that this chunk is OK to add to the packet (as&n;&t; * long as we have the cwnd for it).&n;&t; */
multiline_comment|/* DATA is a special case since we must examine both rwnd and cwnd&n;&t; * before we send DATA.&n;&t; */
r_if
c_cond
(paren
id|sctp_chunk_is_data
c_func
(paren
id|chunk
)paren
)paren
(brace
id|retval
op_assign
id|sctp_packet_append_data
c_func
(paren
id|packet
comma
id|chunk
)paren
suffix:semicolon
multiline_comment|/* Disallow SACK bundling after DATA. */
id|packet-&gt;has_sack
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|SCTP_XMIT_OK
op_ne
id|retval
)paren
r_goto
id|finish
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|SCTP_CID_COOKIE_ECHO
op_eq
id|chunk-&gt;chunk_hdr-&gt;type
)paren
id|packet-&gt;has_cookie_echo
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|SCTP_CID_SACK
op_eq
id|chunk-&gt;chunk_hdr-&gt;type
)paren
id|packet-&gt;has_sack
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* It is OK to send this chunk.  */
id|__skb_queue_tail
c_func
(paren
op_amp
id|packet-&gt;chunks
comma
(paren
r_struct
id|sk_buff
op_star
)paren
id|chunk
)paren
suffix:semicolon
id|packet-&gt;size
op_add_assign
id|chunk_len
suffix:semicolon
id|finish
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* All packets are sent to the network through this function from&n; * sctp_outq_tail().&n; *&n; * The return value is a normal kernel error return value.&n; */
DECL|function|sctp_packet_transmit
r_int
id|sctp_packet_transmit
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
)paren
(brace
r_struct
id|sctp_transport
op_star
id|tp
op_assign
id|packet-&gt;transport
suffix:semicolon
r_struct
id|sctp_association
op_star
id|asoc
op_assign
id|tp-&gt;asoc
suffix:semicolon
r_struct
id|sctphdr
op_star
id|sh
suffix:semicolon
id|__u32
id|crc32
suffix:semicolon
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
r_struct
id|sctp_chunk
op_star
id|chunk
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|padding
suffix:semicolon
multiline_comment|/* How much padding do we need?  */
id|__u8
id|has_data
op_assign
l_int|0
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: packet:%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|packet
)paren
suffix:semicolon
multiline_comment|/* Do NOT generate a chunkless packet. */
id|chunk
op_assign
(paren
r_struct
id|sctp_chunk
op_star
)paren
id|skb_peek
c_func
(paren
op_amp
id|packet-&gt;chunks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|chunk
)paren
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* Set up convenience variables... */
id|sk
op_assign
id|chunk-&gt;skb-&gt;sk
suffix:semicolon
multiline_comment|/* Allocate the new skb.  */
id|nskb
op_assign
id|dev_alloc_skb
c_func
(paren
id|packet-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
r_goto
id|nomem
suffix:semicolon
multiline_comment|/* Make sure the outbound skb has enough header room reserved. */
id|skb_reserve
c_func
(paren
id|nskb
comma
id|packet-&gt;overhead
)paren
suffix:semicolon
multiline_comment|/* Set the owning socket so that we know where to get the&n;&t; * destination IP address.&n;&t; */
id|skb_set_owner_w
c_func
(paren
id|nskb
comma
id|sk
)paren
suffix:semicolon
multiline_comment|/* Build the SCTP header.  */
id|sh
op_assign
(paren
r_struct
id|sctphdr
op_star
)paren
id|skb_push
c_func
(paren
id|nskb
comma
r_sizeof
(paren
r_struct
id|sctphdr
)paren
)paren
suffix:semicolon
id|sh-&gt;source
op_assign
id|htons
c_func
(paren
id|packet-&gt;source_port
)paren
suffix:semicolon
id|sh-&gt;dest
op_assign
id|htons
c_func
(paren
id|packet-&gt;destination_port
)paren
suffix:semicolon
multiline_comment|/* From 6.8 Adler-32 Checksum Calculation:&n;&t; * After the packet is constructed (containing the SCTP common&n;&t; * header and one or more control or DATA chunks), the&n;&t; * transmitter shall:&n;&t; *&n;&t; * 1) Fill in the proper Verification Tag in the SCTP common&n;&t; *    header and initialize the checksum field to 0&squot;s.&n;&t; */
id|sh-&gt;vtag
op_assign
id|htonl
c_func
(paren
id|packet-&gt;vtag
)paren
suffix:semicolon
id|sh-&gt;checksum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 2) Calculate the Adler-32 checksum of the whole packet,&n;&t; *    including the SCTP common header and all the&n;&t; *    chunks.&n;&t; *&n;&t; * Note: Adler-32 is no longer applicable, as has been replaced&n;&t; * by CRC32-C as described in &lt;draft-ietf-tsvwg-sctpcsum-02.txt&gt;.&n;&t; */
id|crc32
op_assign
id|sctp_start_cksum
c_func
(paren
(paren
id|__u8
op_star
)paren
id|sh
comma
r_sizeof
(paren
r_struct
id|sctphdr
)paren
)paren
suffix:semicolon
multiline_comment|/**&n;&t; * 6.10 Bundling&n;&t; *&n;&t; *    An endpoint bundles chunks by simply including multiple&n;&t; *    chunks in one outbound SCTP packet.  ...&n;&t; */
multiline_comment|/**&n;&t; * 3.2  Chunk Field Descriptions&n;&t; *&n;&t; * The total length of a chunk (including Type, Length and&n;&t; * Value fields) MUST be a multiple of 4 bytes.  If the length&n;&t; * of the chunk is not a multiple of 4 bytes, the sender MUST&n;&t; * pad the chunk with all zero bytes and this padding is not&n;&t; * included in the chunk length field.  The sender should&n;&t; * never pad with more than 3 bytes.&n;&t; *&n;&t; * [This whole comment explains WORD_ROUND() below.]&n;&t; */
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;***sctp_transmit_packet***&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|chunk
op_assign
(paren
r_struct
id|sctp_chunk
op_star
)paren
id|__skb_dequeue
c_func
(paren
op_amp
id|packet-&gt;chunks
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|sctp_chunk_is_data
c_func
(paren
id|chunk
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|chunk-&gt;has_tsn
)paren
(brace
id|sctp_chunk_assign_ssn
c_func
(paren
id|chunk
)paren
suffix:semicolon
id|sctp_chunk_assign_tsn
c_func
(paren
id|chunk
)paren
suffix:semicolon
multiline_comment|/* 6.3.1 C4) When data is in flight and when allowed&n;&t;&t;&t; * by rule C5, a new RTT measurement MUST be made each&n;&t;&t;&t; * round trip.  Furthermore, new RTT measurements&n;&t;&t;&t; * SHOULD be made no more than once per round-trip&n;&t;&t;&t; * for a given destination transport address.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|tp-&gt;rto_pending
)paren
(brace
id|chunk-&gt;rtt_in_progress
op_assign
l_int|1
suffix:semicolon
id|tp-&gt;rto_pending
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|chunk-&gt;resent
op_assign
l_int|1
suffix:semicolon
id|chunk-&gt;sent_at
op_assign
id|jiffies
suffix:semicolon
id|has_data
op_assign
l_int|1
suffix:semicolon
)brace
id|padding
op_assign
id|WORD_ROUND
c_func
(paren
id|chunk-&gt;skb-&gt;len
)paren
op_minus
id|chunk-&gt;skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|padding
)paren
id|memset
c_func
(paren
id|skb_put
c_func
(paren
id|chunk-&gt;skb
comma
id|padding
)paren
comma
l_int|0
comma
id|padding
)paren
suffix:semicolon
id|crc32
op_assign
id|sctp_update_copy_cksum
c_func
(paren
id|skb_put
c_func
(paren
id|nskb
comma
id|chunk-&gt;skb-&gt;len
)paren
comma
id|chunk-&gt;skb-&gt;data
comma
id|chunk-&gt;skb-&gt;len
comma
id|crc32
)paren
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s %p[%s] %s 0x%x, %s %d, %s %d, %s %d&bslash;n&quot;
comma
l_string|&quot;*** Chunk&quot;
comma
id|chunk
comma
id|sctp_cname
c_func
(paren
id|SCTP_ST_CHUNK
c_func
(paren
id|chunk-&gt;chunk_hdr-&gt;type
)paren
)paren
comma
id|chunk-&gt;has_tsn
ques
c_cond
l_string|&quot;TSN&quot;
suffix:colon
l_string|&quot;No TSN&quot;
comma
id|chunk-&gt;has_tsn
ques
c_cond
id|ntohl
c_func
(paren
id|chunk-&gt;subh.data_hdr-&gt;tsn
)paren
suffix:colon
l_int|0
comma
l_string|&quot;length&quot;
comma
id|ntohs
c_func
(paren
id|chunk-&gt;chunk_hdr-&gt;length
)paren
comma
l_string|&quot;chunk-&gt;skb-&gt;len&quot;
comma
id|chunk-&gt;skb-&gt;len
comma
l_string|&quot;rtt_in_progress&quot;
comma
id|chunk-&gt;rtt_in_progress
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this is a control chunk, this is our last&n;&t;&t; * reference. Free data chunks after they&squot;ve been&n;&t;&t; * acknowledged or have failed.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sctp_chunk_is_data
c_func
(paren
id|chunk
)paren
)paren
id|sctp_chunk_free
c_func
(paren
id|chunk
)paren
suffix:semicolon
)brace
multiline_comment|/* Perform final transformation on checksum. */
id|crc32
op_assign
id|sctp_end_cksum
c_func
(paren
id|crc32
)paren
suffix:semicolon
multiline_comment|/* 3) Put the resultant value into the checksum field in the&n;&t; *    common header, and leave the rest of the bits unchanged.&n;&t; */
id|sh-&gt;checksum
op_assign
id|htonl
c_func
(paren
id|crc32
)paren
suffix:semicolon
multiline_comment|/* IP layer ECN support&n;&t; * From RFC 2481&n;&t; *  &quot;The ECN-Capable Transport (ECT) bit would be set by the&n;&t; *   data sender to indicate that the end-points of the&n;&t; *   transport protocol are ECN-capable.&quot;&n;&t; *&n;&t; * Now setting the ECT bit all the time, as it should not cause&n;&t; * any problems protocol-wise even if our peer ignores it.&n;&t; *&n;&t; * Note: The works for IPv6 layer checks this bit too later&n;&t; * in transmission.  See IP6_ECN_flow_xmit().&n;&t; */
id|INET_ECN_xmit
c_func
(paren
id|nskb-&gt;sk
)paren
suffix:semicolon
multiline_comment|/* Set up the IP options.  */
multiline_comment|/* BUG: not implemented&n;&t; * For v4 this all lives somewhere in sk-&gt;sk_opt...&n;&t; */
multiline_comment|/* Dump that on IP!  */
r_if
c_cond
(paren
id|asoc
op_logical_and
id|asoc-&gt;peer.last_sent_to
op_ne
id|tp
)paren
(brace
multiline_comment|/* Considering the multiple CPU scenario, this is a&n;&t;&t; * &quot;correcter&quot; place for last_sent_to.  --xguo&n;&t;&t; */
id|asoc-&gt;peer.last_sent_to
op_assign
id|tp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_data
)paren
(brace
r_struct
id|timer_list
op_star
id|timer
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|tp-&gt;last_time_used
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* Restart the AUTOCLOSE timer when sending data. */
r_if
c_cond
(paren
id|sctp_state
c_func
(paren
id|asoc
comma
id|ESTABLISHED
)paren
op_logical_and
id|asoc-&gt;autoclose
)paren
(brace
id|timer
op_assign
op_amp
id|asoc-&gt;timers
(braket
id|SCTP_EVENT_TIMEOUT_AUTOCLOSE
)braket
suffix:semicolon
id|timeout
op_assign
id|asoc-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_AUTOCLOSE
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
id|timer
comma
id|jiffies
op_plus
id|timeout
)paren
)paren
id|sctp_association_hold
c_func
(paren
id|asoc
)paren
suffix:semicolon
)brace
)brace
id|dst
op_assign
id|tp-&gt;dst
suffix:semicolon
multiline_comment|/* The &squot;obsolete&squot; field of dst is set to 2 when a dst is freed. */
r_if
c_cond
(paren
op_logical_neg
id|dst
op_logical_or
(paren
id|dst-&gt;obsolete
OG
l_int|1
)paren
)paren
(brace
id|dst_release
c_func
(paren
id|dst
)paren
suffix:semicolon
id|sctp_transport_route
c_func
(paren
id|tp
comma
l_int|NULL
comma
id|sctp_sk
c_func
(paren
id|sk
)paren
)paren
suffix:semicolon
id|sctp_assoc_sync_pmtu
c_func
(paren
id|asoc
)paren
suffix:semicolon
)brace
id|nskb-&gt;dst
op_assign
id|dst_clone
c_func
(paren
id|tp-&gt;dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb-&gt;dst
)paren
r_goto
id|no_route
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;***sctp_transmit_packet*** skb len %d&bslash;n&quot;
comma
id|nskb-&gt;len
)paren
suffix:semicolon
(paren
op_star
id|tp-&gt;af_specific-&gt;sctp_xmit
)paren
(paren
id|nskb
comma
id|tp
comma
id|packet-&gt;ipfragok
)paren
suffix:semicolon
id|out
suffix:colon
id|packet-&gt;size
op_assign
id|packet-&gt;overhead
suffix:semicolon
r_return
id|err
suffix:semicolon
id|no_route
suffix:colon
id|kfree_skb
c_func
(paren
id|nskb
)paren
suffix:semicolon
id|IP_INC_STATS_BH
c_func
(paren
id|IpOutNoRoutes
)paren
suffix:semicolon
multiline_comment|/* FIXME: Returning the &squot;err&squot; will effect all the associations&n;&t; * associated with a socket, although only one of the paths of the&n;&t; * association is unreachable.&n;&t; * The real failure of a transport or association can be passed on&n;&t; * to the user via notifications. So setting this error may not be&n;&t; * required.&n;&t; */
multiline_comment|/* err = -EHOSTUNREACH; */
id|err
suffix:colon
multiline_comment|/* Control chunks are unreliable so just drop them.  DATA chunks&n;&t; * will get resent or dropped later.&n;&t; */
r_while
c_loop
(paren
(paren
id|chunk
op_assign
(paren
r_struct
id|sctp_chunk
op_star
)paren
id|__skb_dequeue
c_func
(paren
op_amp
id|packet-&gt;chunks
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sctp_chunk_is_data
c_func
(paren
id|chunk
)paren
)paren
id|sctp_chunk_free
c_func
(paren
id|chunk
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
id|nomem
suffix:colon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
multiline_comment|/********************************************************************&n; * 2nd Level Abstractions&n; ********************************************************************/
multiline_comment|/* This private function handles the specifics of appending DATA chunks.  */
DECL|function|sctp_packet_append_data
r_static
id|sctp_xmit_t
id|sctp_packet_append_data
c_func
(paren
r_struct
id|sctp_packet
op_star
id|packet
comma
r_struct
id|sctp_chunk
op_star
id|chunk
)paren
(brace
id|sctp_xmit_t
id|retval
op_assign
id|SCTP_XMIT_OK
suffix:semicolon
r_int
id|datasize
comma
id|rwnd
comma
id|inflight
suffix:semicolon
r_struct
id|sctp_transport
op_star
id|transport
op_assign
id|packet-&gt;transport
suffix:semicolon
id|__u32
id|max_burst_bytes
suffix:semicolon
r_struct
id|sctp_association
op_star
id|asoc
op_assign
id|transport-&gt;asoc
suffix:semicolon
r_struct
id|sctp_opt
op_star
id|sp
op_assign
id|sctp_sk
c_func
(paren
id|asoc-&gt;base.sk
)paren
suffix:semicolon
r_struct
id|sctp_outq
op_star
id|q
op_assign
op_amp
id|asoc-&gt;outqueue
suffix:semicolon
multiline_comment|/* RFC 2960 6.1  Transmission of DATA Chunks&n;&t; *&n;&t; * A) At any given time, the data sender MUST NOT transmit new data to&n;&t; * any destination transport address if its peer&squot;s rwnd indicates&n;&t; * that the peer has no buffer space (i.e. rwnd is 0, see Section&n;&t; * 6.2.1).  However, regardless of the value of rwnd (including if it&n;&t; * is 0), the data sender can always have one DATA chunk in flight to&n;&t; * the receiver if allowed by cwnd (see rule B below).  This rule&n;&t; * allows the sender to probe for a change in rwnd that the sender&n;&t; * missed due to the SACK having been lost in transit from the data&n;&t; * receiver to the data sender.&n;&t; */
id|rwnd
op_assign
id|asoc-&gt;peer.rwnd
suffix:semicolon
id|inflight
op_assign
id|asoc-&gt;outqueue.outstanding_bytes
suffix:semicolon
id|datasize
op_assign
id|sctp_data_size
c_func
(paren
id|chunk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|datasize
OG
id|rwnd
)paren
(brace
r_if
c_cond
(paren
id|inflight
OG
l_int|0
)paren
(brace
multiline_comment|/* We have (at least) one data chunk in flight,&n;&t;&t;&t; * so we can&squot;t fall back to rule 6.1 B).&n;&t;&t;&t; */
id|retval
op_assign
id|SCTP_XMIT_RWND_FULL
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
)brace
multiline_comment|/* sctpimpguide-05 2.14.2&n;&t; * D) When the time comes for the sender to&n;&t; * transmit new DATA chunks, the protocol parameter Max.Burst MUST&n;&t; * first be applied to limit how many new DATA chunks may be sent.&n;&t; * The limit is applied by adjusting cwnd as follows:&n;&t; * &t;if ((flightsize + Max.Burst * MTU) &lt; cwnd)&n;&t; *&t;&t;cwnd = flightsize + Max.Burst * MTU&n;&t; */
id|max_burst_bytes
op_assign
id|asoc-&gt;max_burst
op_star
id|asoc-&gt;pmtu
suffix:semicolon
r_if
c_cond
(paren
(paren
id|transport-&gt;flight_size
op_plus
id|max_burst_bytes
)paren
OL
id|transport-&gt;cwnd
)paren
(brace
id|transport-&gt;cwnd
op_assign
id|transport-&gt;flight_size
op_plus
id|max_burst_bytes
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: cwnd limited by max_burst: &quot;
l_string|&quot;transport: %p, cwnd: %d, &quot;
l_string|&quot;ssthresh: %d, flight_size: %d, &quot;
l_string|&quot;pba: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|transport
comma
id|transport-&gt;cwnd
comma
id|transport-&gt;ssthresh
comma
id|transport-&gt;flight_size
comma
id|transport-&gt;partial_bytes_acked
)paren
suffix:semicolon
)brace
multiline_comment|/* RFC 2960 6.1  Transmission of DATA Chunks&n;&t; *&n;&t; * B) At any given time, the sender MUST NOT transmit new data&n;&t; * to a given transport address if it has cwnd or more bytes&n;&t; * of data outstanding to that transport address.&n;&t; */
multiline_comment|/* RFC 7.2.4 &amp; the Implementers Guide 2.8.&n;&t; *&n;&t; * 3) ...&n;&t; *    When a Fast Retransmit is being performed the sender SHOULD&n;&t; *    ignore the value of cwnd and SHOULD NOT delay retransmission.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|chunk-&gt;fast_retransmit
)paren
r_if
c_cond
(paren
id|transport-&gt;flight_size
op_ge
id|transport-&gt;cwnd
)paren
(brace
id|retval
op_assign
id|SCTP_XMIT_RWND_FULL
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
multiline_comment|/* Nagle&squot;s algorithm to solve small-packet problem:&n;&t; * Inhibit the sending of new chunks when new outgoing data arrives&n;&t; * if any previously transmitted data on the connection remains&n;&t; * unacknowledged.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sp-&gt;nodelay
op_logical_and
id|sctp_packet_empty
c_func
(paren
id|packet
)paren
op_logical_and
id|q-&gt;outstanding_bytes
op_logical_and
id|sctp_state
c_func
(paren
id|asoc
comma
id|ESTABLISHED
)paren
)paren
(brace
r_int
id|len
op_assign
id|datasize
op_plus
id|q-&gt;out_qlen
suffix:semicolon
multiline_comment|/* Check whether this chunk and all the rest of pending&n;&t;&t; * data will fit or delay in hopes of bundling a full&n;&t;&t; * sized packet.&n;&t;&t; */
r_if
c_cond
(paren
id|len
OL
id|asoc-&gt;pmtu
op_minus
id|packet-&gt;overhead
)paren
(brace
id|retval
op_assign
id|SCTP_XMIT_NAGLE_DELAY
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
)brace
multiline_comment|/* Keep track of how many bytes are in flight over this transport. */
id|transport-&gt;flight_size
op_add_assign
id|datasize
suffix:semicolon
multiline_comment|/* Keep track of how many bytes are in flight to the receiver. */
id|asoc-&gt;outqueue.outstanding_bytes
op_add_assign
id|datasize
suffix:semicolon
multiline_comment|/* Update our view of the receiver&squot;s rwnd. */
r_if
c_cond
(paren
id|datasize
OL
id|rwnd
)paren
id|rwnd
op_sub_assign
id|datasize
suffix:semicolon
r_else
id|rwnd
op_assign
l_int|0
suffix:semicolon
id|asoc-&gt;peer.rwnd
op_assign
id|rwnd
suffix:semicolon
multiline_comment|/* Has been accepted for transmission. */
id|chunk-&gt;msg-&gt;can_expire
op_assign
l_int|0
suffix:semicolon
id|finish
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
eof
