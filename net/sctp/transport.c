multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001-2003 International Business Machines Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * This module provides the abstraction for an SCTP tranport representing&n; * a remote transport address.  For local transport addresses, we just use&n; * union sctp_addr.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson          &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    Xingang Guo           &lt;xingang.guo@intel.com&gt;&n; *    Hui Huang             &lt;hui.huang@nokia.com&gt;&n; *    Sridhar Samudrala&t;    &lt;sri@us.ibm.com&gt;&n; *    Ardelle Fan&t;    &lt;ardelle.fan@intel.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
multiline_comment|/* 1st Level Abstractions.  */
multiline_comment|/* Allocate and initialize a new transport.  */
DECL|function|sctp_transport_new
r_struct
id|sctp_transport
op_star
id|sctp_transport_new
c_func
(paren
r_const
r_union
id|sctp_addr
op_star
id|addr
comma
r_int
id|gfp
)paren
(brace
r_struct
id|sctp_transport
op_star
id|transport
suffix:semicolon
id|transport
op_assign
id|t_new
c_func
(paren
r_struct
id|sctp_transport
comma
id|gfp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transport
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sctp_transport_init
c_func
(paren
id|transport
comma
id|addr
comma
id|gfp
)paren
)paren
r_goto
id|fail_init
suffix:semicolon
id|transport-&gt;malloced
op_assign
l_int|1
suffix:semicolon
id|SCTP_DBG_OBJCNT_INC
c_func
(paren
id|transport
)paren
suffix:semicolon
r_return
id|transport
suffix:semicolon
id|fail_init
suffix:colon
id|kfree
c_func
(paren
id|transport
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Initialize a new transport from provided memory.  */
DECL|function|sctp_transport_init
r_struct
id|sctp_transport
op_star
id|sctp_transport_init
c_func
(paren
r_struct
id|sctp_transport
op_star
id|peer
comma
r_const
r_union
id|sctp_addr
op_star
id|addr
comma
r_int
id|gfp
)paren
(brace
multiline_comment|/* Copy in the address.  */
id|peer-&gt;ipaddr
op_assign
op_star
id|addr
suffix:semicolon
id|peer-&gt;af_specific
op_assign
id|sctp_get_af_specific
c_func
(paren
id|addr-&gt;sa.sa_family
)paren
suffix:semicolon
id|peer-&gt;asoc
op_assign
l_int|NULL
suffix:semicolon
id|peer-&gt;dst
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|peer-&gt;saddr
comma
l_int|0
comma
r_sizeof
(paren
r_union
id|sctp_addr
)paren
)paren
suffix:semicolon
multiline_comment|/* From 6.3.1 RTO Calculation:&n;&t; *&n;&t; * C1) Until an RTT measurement has been made for a packet sent to the&n;&t; * given destination transport address, set RTO to the protocol&n;&t; * parameter &squot;RTO.Initial&squot;.&n;&t; */
id|peer-&gt;rtt
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;rto
op_assign
id|sctp_rto_initial
suffix:semicolon
id|peer-&gt;rttvar
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;srtt
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;rto_pending
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;last_time_heard
op_assign
id|jiffies
suffix:semicolon
id|peer-&gt;last_time_used
op_assign
id|jiffies
suffix:semicolon
id|peer-&gt;last_time_ecne_reduced
op_assign
id|jiffies
suffix:semicolon
id|peer-&gt;active
op_assign
id|SCTP_ACTIVE
suffix:semicolon
id|peer-&gt;hb_allowed
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Initialize the default path max_retrans.  */
id|peer-&gt;max_retrans
op_assign
id|sctp_max_retrans_path
suffix:semicolon
id|peer-&gt;error_threshold
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;error_count
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|peer-&gt;transmitted
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|peer-&gt;send_ready
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|peer-&gt;transports
)paren
suffix:semicolon
multiline_comment|/* Set up the retransmission timer.  */
id|init_timer
c_func
(paren
op_amp
id|peer-&gt;T3_rtx_timer
)paren
suffix:semicolon
id|peer-&gt;T3_rtx_timer.function
op_assign
id|sctp_generate_t3_rtx_event
suffix:semicolon
id|peer-&gt;T3_rtx_timer.data
op_assign
(paren
r_int
r_int
)paren
id|peer
suffix:semicolon
multiline_comment|/* Set up the heartbeat timer. */
id|init_timer
c_func
(paren
op_amp
id|peer-&gt;hb_timer
)paren
suffix:semicolon
id|peer-&gt;hb_interval
op_assign
id|SCTP_DEFAULT_TIMEOUT_HEARTBEAT
suffix:semicolon
id|peer-&gt;hb_timer.function
op_assign
id|sctp_generate_heartbeat_event
suffix:semicolon
id|peer-&gt;hb_timer.data
op_assign
(paren
r_int
r_int
)paren
id|peer
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|peer-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
id|peer-&gt;dead
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;malloced
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Initialize the state information for SFR-CACC */
id|peer-&gt;cacc.changeover_active
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;cacc.cycling_changeover
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;cacc.next_tsn_at_change
op_assign
l_int|0
suffix:semicolon
id|peer-&gt;cacc.cacc_saw_newack
op_assign
l_int|0
suffix:semicolon
r_return
id|peer
suffix:semicolon
)brace
multiline_comment|/* This transport is no longer needed.  Free up if possible, or&n; * delay until it last reference count.&n; */
DECL|function|sctp_transport_free
r_void
id|sctp_transport_free
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
)paren
(brace
id|transport-&gt;dead
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Try to delete the heartbeat timer.  */
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|transport-&gt;hb_timer
)paren
)paren
id|sctp_transport_put
c_func
(paren
id|transport
)paren
suffix:semicolon
id|sctp_transport_put
c_func
(paren
id|transport
)paren
suffix:semicolon
)brace
multiline_comment|/* Destroy the transport data structure.&n; * Assumes there are no more users of this structure.&n; */
DECL|function|sctp_transport_destroy
r_void
id|sctp_transport_destroy
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
)paren
(brace
id|SCTP_ASSERT
c_func
(paren
id|transport-&gt;dead
comma
l_string|&quot;Transport is not dead&quot;
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transport-&gt;asoc
)paren
id|sctp_association_put
c_func
(paren
id|transport-&gt;asoc
)paren
suffix:semicolon
id|dst_release
c_func
(paren
id|transport-&gt;dst
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|transport
)paren
suffix:semicolon
id|SCTP_DBG_OBJCNT_DEC
c_func
(paren
id|transport
)paren
suffix:semicolon
)brace
multiline_comment|/* Start T3_rtx timer if it is not already running and update the heartbeat&n; * timer.  This routine is called every time a DATA chunk is sent.&n; */
DECL|function|sctp_transport_reset_timers
r_void
id|sctp_transport_reset_timers
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
)paren
(brace
multiline_comment|/* RFC 2960 6.3.2 Retransmission Timer Rules&n;&t; *&n;&t; * R1) Every time a DATA chunk is sent to any address(including a&n;&t; * retransmission), if the T3-rtx timer of that address is not running&n;&t; * start it running so that it will expire after the RTO of that&n;&t; * address.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|timer_pending
c_func
(paren
op_amp
id|transport-&gt;T3_rtx_timer
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|transport-&gt;T3_rtx_timer
comma
id|jiffies
op_plus
id|transport-&gt;rto
)paren
)paren
id|sctp_transport_hold
c_func
(paren
id|transport
)paren
suffix:semicolon
multiline_comment|/* When a data chunk is sent, reset the heartbeat interval.  */
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|transport-&gt;hb_timer
comma
id|sctp_transport_timeout
c_func
(paren
id|transport
)paren
)paren
)paren
id|sctp_transport_hold
c_func
(paren
id|transport
)paren
suffix:semicolon
)brace
multiline_comment|/* This transport has been assigned to an association.&n; * Initialize fields from the association or from the sock itself.&n; * Register the reference count in the association.&n; */
DECL|function|sctp_transport_set_owner
r_void
id|sctp_transport_set_owner
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
comma
r_struct
id|sctp_association
op_star
id|asoc
)paren
(brace
id|transport-&gt;asoc
op_assign
id|asoc
suffix:semicolon
id|sctp_association_hold
c_func
(paren
id|asoc
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the pmtu of a transport. */
DECL|function|sctp_transport_pmtu
r_void
id|sctp_transport_pmtu
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|dst
op_assign
id|transport-&gt;af_specific
op_member_access_from_pointer
id|get_dst
c_func
(paren
l_int|NULL
comma
op_amp
id|transport-&gt;ipaddr
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
id|transport-&gt;pmtu
op_assign
id|dst_pmtu
c_func
(paren
id|dst
)paren
suffix:semicolon
id|dst_release
c_func
(paren
id|dst
)paren
suffix:semicolon
)brace
r_else
id|transport-&gt;pmtu
op_assign
id|SCTP_DEFAULT_MAXSEGMENT
suffix:semicolon
)brace
multiline_comment|/* Caches the dst entry and source address for a transport&squot;s destination&n; * address.&n; */
DECL|function|sctp_transport_route
r_void
id|sctp_transport_route
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
comma
r_union
id|sctp_addr
op_star
id|saddr
comma
r_struct
id|sctp_opt
op_star
id|opt
)paren
(brace
r_struct
id|sctp_association
op_star
id|asoc
op_assign
id|transport-&gt;asoc
suffix:semicolon
r_struct
id|sctp_af
op_star
id|af
op_assign
id|transport-&gt;af_specific
suffix:semicolon
r_union
id|sctp_addr
op_star
id|daddr
op_assign
op_amp
id|transport-&gt;ipaddr
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
suffix:semicolon
id|dst
op_assign
id|af
op_member_access_from_pointer
id|get_dst
c_func
(paren
id|asoc
comma
id|daddr
comma
id|saddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saddr
)paren
id|memcpy
c_func
(paren
op_amp
id|transport-&gt;saddr
comma
id|saddr
comma
r_sizeof
(paren
r_union
id|sctp_addr
)paren
)paren
suffix:semicolon
r_else
id|af
op_member_access_from_pointer
id|get_saddr
c_func
(paren
id|asoc
comma
id|dst
comma
id|daddr
comma
op_amp
id|transport-&gt;saddr
)paren
suffix:semicolon
id|transport-&gt;dst
op_assign
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
id|transport-&gt;pmtu
op_assign
id|dst_pmtu
c_func
(paren
id|dst
)paren
suffix:semicolon
multiline_comment|/* Initialize sk-&gt;sk_rcv_saddr, if the transport is the&n;&t;&t; * association&squot;s active path for getsockname().&n;&t;&t; */
r_if
c_cond
(paren
id|asoc
op_logical_and
(paren
id|transport
op_eq
id|asoc-&gt;peer.active_path
)paren
)paren
id|af
op_member_access_from_pointer
id|to_sk_saddr
c_func
(paren
op_amp
id|transport-&gt;saddr
comma
id|asoc-&gt;base.sk
)paren
suffix:semicolon
)brace
r_else
id|transport-&gt;pmtu
op_assign
id|SCTP_DEFAULT_MAXSEGMENT
suffix:semicolon
)brace
multiline_comment|/* Hold a reference to a transport.  */
DECL|function|sctp_transport_hold
r_void
id|sctp_transport_hold
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|transport-&gt;refcnt
)paren
suffix:semicolon
)brace
multiline_comment|/* Release a reference to a transport and clean up&n; * if there are no more references.&n; */
DECL|function|sctp_transport_put
r_void
id|sctp_transport_put
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|transport-&gt;refcnt
)paren
)paren
id|sctp_transport_destroy
c_func
(paren
id|transport
)paren
suffix:semicolon
)brace
multiline_comment|/* Update transport&squot;s RTO based on the newly calculated RTT. */
DECL|function|sctp_transport_update_rto
r_void
id|sctp_transport_update_rto
c_func
(paren
r_struct
id|sctp_transport
op_star
id|tp
comma
id|__u32
id|rtt
)paren
(brace
multiline_comment|/* Check for valid transport.  */
id|SCTP_ASSERT
c_func
(paren
id|tp
comma
l_string|&quot;NULL transport&quot;
comma
r_return
)paren
suffix:semicolon
multiline_comment|/* We should not be doing any RTO updates unless rto_pending is set.  */
id|SCTP_ASSERT
c_func
(paren
id|tp-&gt;rto_pending
comma
l_string|&quot;rto_pending not set&quot;
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;rttvar
op_logical_or
id|tp-&gt;srtt
)paren
(brace
multiline_comment|/* 6.3.1 C3) When a new RTT measurement R&squot; is made, set&n;&t;&t; * RTTVAR &lt;- (1 - RTO.Beta) * RTTVAR + RTO.Beta * |SRTT - R&squot;|&n;&t;&t; * SRTT &lt;- (1 - RTO.Alpha) * SRTT + RTO.Alpha * R&squot;&n;&t;&t; */
multiline_comment|/* Note:  The above algorithm has been rewritten to&n;&t;&t; * express rto_beta and rto_alpha as inverse powers&n;&t;&t; * of two.&n;&t;&t; * For example, assuming the default value of RTO.Alpha of&n;&t;&t; * 1/8, rto_alpha would be expressed as 3.&n;&t;&t; */
id|tp-&gt;rttvar
op_assign
id|tp-&gt;rttvar
op_minus
(paren
id|tp-&gt;rttvar
op_rshift
id|sctp_rto_beta
)paren
op_plus
(paren
(paren
id|abs
c_func
(paren
id|tp-&gt;srtt
op_minus
id|rtt
)paren
)paren
op_rshift
id|sctp_rto_beta
)paren
suffix:semicolon
id|tp-&gt;srtt
op_assign
id|tp-&gt;srtt
op_minus
(paren
id|tp-&gt;srtt
op_rshift
id|sctp_rto_alpha
)paren
op_plus
(paren
id|rtt
op_rshift
id|sctp_rto_alpha
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 6.3.1 C2) When the first RTT measurement R is made, set&n;&t;&t; * SRTT &lt;- R, RTTVAR &lt;- R/2.&n;&t;&t; */
id|tp-&gt;srtt
op_assign
id|rtt
suffix:semicolon
id|tp-&gt;rttvar
op_assign
id|rtt
op_rshift
l_int|1
suffix:semicolon
)brace
multiline_comment|/* 6.3.1 G1) Whenever RTTVAR is computed, if RTTVAR = 0, then&n;&t; * adjust RTTVAR &lt;- G, where G is the CLOCK GRANULARITY.&n;&t; */
r_if
c_cond
(paren
id|tp-&gt;rttvar
op_eq
l_int|0
)paren
id|tp-&gt;rttvar
op_assign
id|SCTP_CLOCK_GRANULARITY
suffix:semicolon
multiline_comment|/* 6.3.1 C3) After the computation, update RTO &lt;- SRTT + 4 * RTTVAR. */
id|tp-&gt;rto
op_assign
id|tp-&gt;srtt
op_plus
(paren
id|tp-&gt;rttvar
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 6.3.1 C6) Whenever RTO is computed, if it is less than RTO.Min&n;&t; * seconds then it is rounded up to RTO.Min seconds.&n;&t; */
r_if
c_cond
(paren
id|tp-&gt;rto
OL
id|tp-&gt;asoc-&gt;rto_min
)paren
id|tp-&gt;rto
op_assign
id|tp-&gt;asoc-&gt;rto_min
suffix:semicolon
multiline_comment|/* 6.3.1 C7) A maximum value may be placed on RTO provided it is&n;&t; * at least RTO.max seconds.&n;&t; */
r_if
c_cond
(paren
id|tp-&gt;rto
OG
id|tp-&gt;asoc-&gt;rto_max
)paren
id|tp-&gt;rto
op_assign
id|tp-&gt;asoc-&gt;rto_max
suffix:semicolon
id|tp-&gt;rtt
op_assign
id|rtt
suffix:semicolon
multiline_comment|/* Reset rto_pending so that a new RTT measurement is started when a&n;&t; * new data chunk is sent.&n;&t; */
id|tp-&gt;rto_pending
op_assign
l_int|0
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: transport: %p, rtt: %d, srtt: %d &quot;
l_string|&quot;rttvar: %d, rto: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|tp
comma
id|rtt
comma
id|tp-&gt;srtt
comma
id|tp-&gt;rttvar
comma
id|tp-&gt;rto
)paren
suffix:semicolon
)brace
multiline_comment|/* This routine updates the transport&squot;s cwnd and partial_bytes_acked&n; * parameters based on the bytes acked in the received SACK.&n; */
DECL|function|sctp_transport_raise_cwnd
r_void
id|sctp_transport_raise_cwnd
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
comma
id|__u32
id|sack_ctsn
comma
id|__u32
id|bytes_acked
)paren
(brace
id|__u32
id|cwnd
comma
id|ssthresh
comma
id|flight_size
comma
id|pba
comma
id|pmtu
suffix:semicolon
id|cwnd
op_assign
id|transport-&gt;cwnd
suffix:semicolon
id|flight_size
op_assign
id|transport-&gt;flight_size
suffix:semicolon
multiline_comment|/* The appropriate cwnd increase algorithm is performed if, and only&n;&t; * if the cumulative TSN has advanced and the congestion window is&n;&t; * being fully utilized.&n;&t; */
r_if
c_cond
(paren
(paren
id|transport-&gt;asoc-&gt;ctsn_ack_point
op_ge
id|sack_ctsn
)paren
op_logical_or
(paren
id|flight_size
OL
id|cwnd
)paren
)paren
r_return
suffix:semicolon
id|ssthresh
op_assign
id|transport-&gt;ssthresh
suffix:semicolon
id|pba
op_assign
id|transport-&gt;partial_bytes_acked
suffix:semicolon
id|pmtu
op_assign
id|transport-&gt;asoc-&gt;pmtu
suffix:semicolon
r_if
c_cond
(paren
id|cwnd
op_le
id|ssthresh
)paren
(brace
multiline_comment|/* RFC 2960 7.2.1, sctpimpguide-05 2.14.2 When cwnd is less&n;&t;&t; * than or equal to ssthresh an SCTP endpoint MUST use the&n;&t;&t; * slow start algorithm to increase cwnd only if the current&n;&t;&t; * congestion window is being fully utilized and an incoming&n;&t;&t; * SACK advances the Cumulative TSN Ack Point. Only when these&n;&t;&t; * two conditions are met can the cwnd be increased otherwise&n;&t;&t; * the cwnd MUST not be increased. If these conditions are met&n;&t;&t; * then cwnd MUST be increased by at most the lesser of&n;&t;&t; * 1) the total size of the previously outstanding DATA&n;&t;&t; * chunk(s) acknowledged, and 2) the destination&squot;s path MTU.&n;&t;&t; */
r_if
c_cond
(paren
id|bytes_acked
OG
id|pmtu
)paren
id|cwnd
op_add_assign
id|pmtu
suffix:semicolon
r_else
id|cwnd
op_add_assign
id|bytes_acked
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: SLOW START: transport: %p, &quot;
l_string|&quot;bytes_acked: %d, cwnd: %d, ssthresh: %d, &quot;
l_string|&quot;flight_size: %d, pba: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|transport
comma
id|bytes_acked
comma
id|cwnd
comma
id|ssthresh
comma
id|flight_size
comma
id|pba
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* RFC 2960 7.2.2 Whenever cwnd is greater than ssthresh,&n;&t;&t; * upon each SACK arrival that advances the Cumulative TSN Ack&n;&t;&t; * Point, increase partial_bytes_acked by the total number of&n;&t;&t; * bytes of all new chunks acknowledged in that SACK including&n;&t;&t; * chunks acknowledged by the new Cumulative TSN Ack and by&n;&t;&t; * Gap Ack Blocks.&n;&t;&t; *&n;&t;&t; * When partial_bytes_acked is equal to or greater than cwnd&n;&t;&t; * and before the arrival of the SACK the sender had cwnd or&n;&t;&t; * more bytes of data outstanding (i.e., before arrival of the&n;&t;&t; * SACK, flightsize was greater than or equal to cwnd),&n;&t;&t; * increase cwnd by MTU, and reset partial_bytes_acked to&n;&t;&t; * (partial_bytes_acked - cwnd).&n;&t;&t; */
id|pba
op_add_assign
id|bytes_acked
suffix:semicolon
r_if
c_cond
(paren
id|pba
op_ge
id|cwnd
)paren
(brace
id|cwnd
op_add_assign
id|pmtu
suffix:semicolon
id|pba
op_assign
(paren
(paren
id|cwnd
OL
id|pba
)paren
ques
c_cond
(paren
id|pba
op_minus
id|cwnd
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: CONGESTION AVOIDANCE: &quot;
l_string|&quot;transport: %p, bytes_acked: %d, cwnd: %d, &quot;
l_string|&quot;ssthresh: %d, flight_size: %d, pba: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|transport
comma
id|bytes_acked
comma
id|cwnd
comma
id|ssthresh
comma
id|flight_size
comma
id|pba
)paren
suffix:semicolon
)brace
id|transport-&gt;cwnd
op_assign
id|cwnd
suffix:semicolon
id|transport-&gt;partial_bytes_acked
op_assign
id|pba
suffix:semicolon
)brace
multiline_comment|/* This routine is used to lower the transport&squot;s cwnd when congestion is&n; * detected.&n; */
DECL|function|sctp_transport_lower_cwnd
r_void
id|sctp_transport_lower_cwnd
c_func
(paren
r_struct
id|sctp_transport
op_star
id|transport
comma
id|sctp_lower_cwnd_t
id|reason
)paren
(brace
r_switch
c_cond
(paren
id|reason
)paren
(brace
r_case
id|SCTP_LOWER_CWND_T3_RTX
suffix:colon
multiline_comment|/* RFC 2960 Section 7.2.3, sctpimpguide-05 Section 2.9.2&n;&t;&t; * When the T3-rtx timer expires on an address, SCTP should&n;&t;&t; * perform slow start by:&n;&t;&t; *      ssthresh = max(cwnd/2, 2*MTU)&n;&t;&t; *      cwnd = 1*MTU&n;&t;&t; *      partial_bytes_acked = 0&n;&t;&t; */
id|transport-&gt;ssthresh
op_assign
id|max
c_func
(paren
id|transport-&gt;cwnd
op_div
l_int|2
comma
l_int|2
op_star
id|transport-&gt;asoc-&gt;pmtu
)paren
suffix:semicolon
id|transport-&gt;cwnd
op_assign
id|transport-&gt;asoc-&gt;pmtu
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_LOWER_CWND_FAST_RTX
suffix:colon
multiline_comment|/* RFC 2960 7.2.4 Adjust the ssthresh and cwnd of the&n;&t;&t; * destination address(es) to which the missing DATA chunks&n;&t;&t; * were last sent, according to the formula described in&n;&t;&t; * Section 7.2.3.&n;&t; &t; *&n;&t; &t; * RFC 2960 7.2.3, sctpimpguide-05 2.9.2 Upon detection of&n;&t;&t; * packet losses from SACK (see Section 7.2.4), An endpoint&n;&t;&t; * should do the following:&n;&t;&t; *      ssthresh = max(cwnd/2, 2*MTU)&n;&t;&t; *      cwnd = ssthresh&n;&t;&t; *      partial_bytes_acked = 0&n;&t;&t; */
id|transport-&gt;ssthresh
op_assign
id|max
c_func
(paren
id|transport-&gt;cwnd
op_div
l_int|2
comma
l_int|2
op_star
id|transport-&gt;asoc-&gt;pmtu
)paren
suffix:semicolon
id|transport-&gt;cwnd
op_assign
id|transport-&gt;ssthresh
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_LOWER_CWND_ECNE
suffix:colon
multiline_comment|/* RFC 2481 Section 6.1.2.&n;&t;&t; * If the sender receives an ECN-Echo ACK packet&n;&t;&t; * then the sender knows that congestion was encountered in the&n;&t;&t; * network on the path from the sender to the receiver. The&n;&t;&t; * indication of congestion should be treated just as a&n;&t;&t; * congestion loss in non-ECN Capable TCP. That is, the TCP&n;&t;&t; * source halves the congestion window &quot;cwnd&quot; and reduces the&n;&t;&t; * slow start threshold &quot;ssthresh&quot;.&n;&t;&t; * A critical condition is that TCP does not react to&n;&t;&t; * congestion indications more than once every window of&n;&t;&t; * data (or more loosely more than once every round-trip time).&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|jiffies
op_minus
id|transport-&gt;last_time_ecne_reduced
)paren
OG
id|transport-&gt;rtt
)paren
(brace
id|transport-&gt;ssthresh
op_assign
id|max
c_func
(paren
id|transport-&gt;cwnd
op_div
l_int|2
comma
l_int|2
op_star
id|transport-&gt;asoc-&gt;pmtu
)paren
suffix:semicolon
id|transport-&gt;cwnd
op_assign
id|transport-&gt;ssthresh
suffix:semicolon
id|transport-&gt;last_time_ecne_reduced
op_assign
id|jiffies
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SCTP_LOWER_CWND_INACTIVE
suffix:colon
multiline_comment|/* RFC 2960 Section 7.2.1, sctpimpguide-05 Section 2.14.2&n;&t;&t; * When the association does not transmit data on a given&n;&t;&t; * transport address within an RTO, the cwnd of the transport&n;&t;&t; * address should be adjusted to 2*MTU.&n;&t;&t; * NOTE: Although the draft recommends that this check needs&n;&t;&t; * to be done every RTO interval, we do it every hearbeat&n;&t;&t; * interval.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|jiffies
op_minus
id|transport-&gt;last_time_used
)paren
OG
id|transport-&gt;rto
)paren
id|transport-&gt;cwnd
op_assign
l_int|2
op_star
id|transport-&gt;asoc-&gt;pmtu
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|transport-&gt;partial_bytes_acked
op_assign
l_int|0
suffix:semicolon
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;%s: transport: %p reason: %d cwnd: &quot;
l_string|&quot;%d ssthresh: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|transport
comma
id|reason
comma
id|transport-&gt;cwnd
comma
id|transport-&gt;ssthresh
)paren
suffix:semicolon
)brace
multiline_comment|/* What is the next timeout value for this transport? */
DECL|function|sctp_transport_timeout
r_int
r_int
id|sctp_transport_timeout
c_func
(paren
r_struct
id|sctp_transport
op_star
id|t
)paren
(brace
r_int
r_int
id|timeout
suffix:semicolon
id|timeout
op_assign
id|t-&gt;hb_interval
op_plus
id|t-&gt;rto
op_plus
id|sctp_jitter
c_func
(paren
id|t-&gt;rto
)paren
suffix:semicolon
id|timeout
op_add_assign
id|jiffies
suffix:semicolon
r_return
id|timeout
suffix:semicolon
)brace
eof
