multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001-2002 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * This abstraction represents an SCTP endpoint.&n; *&n; * This file is part of the implementation of the add-IP extension,&n; * based on &lt;draft-ietf-tsvwg-addip-sctp-02.txt&gt; June 29, 2001,&n; * for the SCTP kernel reference Implementation.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; *    Jon Grimm &lt;jgrimm@austin.ibm.com&gt;&n; *    Daisy Chang &lt;daisyc@us.ibm.com&gt;&n; *    Dajiang Zhang &lt;dajiang.zhang@nokia.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/random.h&gt;&t;/* get_random_bytes() */
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
multiline_comment|/* Forward declarations for internal helpers. */
r_static
r_void
id|sctp_endpoint_bh_rcv
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
)paren
suffix:semicolon
multiline_comment|/* Create a sctp_endpoint with all that boring stuff initialized.&n; * Returns NULL if there isn&squot;t enough memory.&n; */
DECL|function|sctp_endpoint_new
r_struct
id|sctp_endpoint
op_star
id|sctp_endpoint_new
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|gfp
)paren
(brace
r_struct
id|sctp_endpoint
op_star
id|ep
suffix:semicolon
multiline_comment|/* Build a local endpoint. */
id|ep
op_assign
id|t_new
c_func
(paren
r_struct
id|sctp_endpoint
comma
id|gfp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ep
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sctp_endpoint_init
c_func
(paren
id|ep
comma
id|sk
comma
id|gfp
)paren
)paren
r_goto
id|fail_init
suffix:semicolon
id|ep-&gt;base.malloced
op_assign
l_int|1
suffix:semicolon
id|SCTP_DBG_OBJCNT_INC
c_func
(paren
id|ep
)paren
suffix:semicolon
r_return
id|ep
suffix:semicolon
id|fail_init
suffix:colon
id|kfree
c_func
(paren
id|ep
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the base fields of the endpoint structure.&n; */
DECL|function|sctp_endpoint_init
r_struct
id|sctp_endpoint
op_star
id|sctp_endpoint_init
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
comma
r_struct
id|sock
op_star
id|sk
comma
r_int
id|gfp
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
id|sk
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ep
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sctp_endpoint
)paren
)paren
suffix:semicolon
multiline_comment|/* Initialize the base structure. */
multiline_comment|/* What type of endpoint are we?  */
id|ep-&gt;base.type
op_assign
id|SCTP_EP_TYPE_SOCKET
suffix:semicolon
multiline_comment|/* Initialize the basic object fields. */
id|atomic_set
c_func
(paren
op_amp
id|ep-&gt;base.refcnt
comma
l_int|1
)paren
suffix:semicolon
id|ep-&gt;base.dead
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;base.malloced
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Create an input queue.  */
id|sctp_inq_init
c_func
(paren
op_amp
id|ep-&gt;base.inqueue
)paren
suffix:semicolon
multiline_comment|/* Set its top-half handler */
id|sctp_inq_set_th_handler
c_func
(paren
op_amp
id|ep-&gt;base.inqueue
comma
(paren
r_void
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|sctp_endpoint_bh_rcv
comma
id|ep
)paren
suffix:semicolon
multiline_comment|/* Initialize the bind addr area */
id|sctp_bind_addr_init
c_func
(paren
op_amp
id|ep-&gt;base.bind_addr
comma
l_int|0
)paren
suffix:semicolon
id|ep-&gt;base.addr_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Remember who we are attached to.  */
id|ep-&gt;base.sk
op_assign
id|sk
suffix:semicolon
id|sock_hold
c_func
(paren
id|ep-&gt;base.sk
)paren
suffix:semicolon
multiline_comment|/* Create the lists of associations.  */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ep-&gt;asocs
)paren
suffix:semicolon
multiline_comment|/* Set up the base timeout information.  */
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_NONE
)braket
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_T1_COOKIE
)braket
op_assign
id|SCTP_DEFAULT_TIMEOUT_T1_COOKIE
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_T1_INIT
)braket
op_assign
id|SCTP_DEFAULT_TIMEOUT_T1_INIT
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_T2_SHUTDOWN
)braket
op_assign
id|MSECS_TO_JIFFIES
c_func
(paren
id|sp-&gt;rtoinfo.srto_initial
)paren
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_T3_RTX
)braket
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_T4_RTO
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* sctpimpguide-05 Section 2.12.2&n;&t; * If the &squot;T5-shutdown-guard&squot; timer is used, it SHOULD be set to the&n;&t; * recommended value of 5 times &squot;RTO.Max&squot;.&n;&t; */
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD
)braket
op_assign
l_int|5
op_star
id|MSECS_TO_JIFFIES
c_func
(paren
id|sp-&gt;rtoinfo.srto_max
)paren
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_HEARTBEAT
)braket
op_assign
id|SCTP_DEFAULT_TIMEOUT_HEARTBEAT
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_SACK
)braket
op_assign
id|SCTP_DEFAULT_TIMEOUT_SACK
suffix:semicolon
id|ep-&gt;timeouts
(braket
id|SCTP_EVENT_TIMEOUT_AUTOCLOSE
)braket
op_assign
id|sp-&gt;autoclose
op_star
id|HZ
suffix:semicolon
multiline_comment|/* Use SCTP specific send buffer space queues.  */
id|sk-&gt;sk_write_space
op_assign
id|sctp_write_space
suffix:semicolon
id|sk-&gt;sk_use_write_queue
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Initialize the secret key used with cookie. */
id|get_random_bytes
c_func
(paren
op_amp
id|ep-&gt;secret_key
(braket
l_int|0
)braket
comma
id|SCTP_SECRET_SIZE
)paren
suffix:semicolon
id|ep-&gt;last_key
op_assign
id|ep-&gt;current_key
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;key_changed_at
op_assign
id|jiffies
suffix:semicolon
id|ep-&gt;debug_name
op_assign
l_string|&quot;unnamedEndpoint&quot;
suffix:semicolon
r_return
id|ep
suffix:semicolon
)brace
multiline_comment|/* Add an association to an endpoint.  */
DECL|function|sctp_endpoint_add_asoc
r_void
id|sctp_endpoint_add_asoc
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
comma
r_struct
id|sctp_association
op_star
id|asoc
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|ep-&gt;base.sk
suffix:semicolon
multiline_comment|/* Now just add it to our list of asocs */
id|list_add_tail
c_func
(paren
op_amp
id|asoc-&gt;asocs
comma
op_amp
id|ep-&gt;asocs
)paren
suffix:semicolon
multiline_comment|/* Increment the backlog value for a TCP-style listening socket. */
r_if
c_cond
(paren
id|sctp_style
c_func
(paren
id|sk
comma
id|TCP
)paren
op_logical_and
id|sctp_sstate
c_func
(paren
id|sk
comma
id|LISTENING
)paren
)paren
id|sk-&gt;sk_ack_backlog
op_increment
suffix:semicolon
)brace
multiline_comment|/* Free the endpoint structure.  Delay cleanup until&n; * all users have released their reference count on this structure.&n; */
DECL|function|sctp_endpoint_free
r_void
id|sctp_endpoint_free
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
)paren
(brace
id|ep-&gt;base.dead
op_assign
l_int|1
suffix:semicolon
id|sctp_endpoint_put
c_func
(paren
id|ep
)paren
suffix:semicolon
)brace
multiline_comment|/* Final destructor for endpoint.  */
DECL|function|sctp_endpoint_destroy
r_void
id|sctp_endpoint_destroy
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
)paren
(brace
id|SCTP_ASSERT
c_func
(paren
id|ep-&gt;base.dead
comma
l_string|&quot;Endpoint is not dead&quot;
comma
r_return
)paren
suffix:semicolon
id|ep-&gt;base.sk-&gt;sk_state
op_assign
id|SCTP_SS_CLOSED
suffix:semicolon
multiline_comment|/* Unlink this endpoint, so we can&squot;t find it again! */
id|sctp_unhash_endpoint
c_func
(paren
id|ep
)paren
suffix:semicolon
multiline_comment|/* Free up the HMAC transform. */
r_if
c_cond
(paren
id|sctp_sk
c_func
(paren
id|ep-&gt;base.sk
)paren
op_member_access_from_pointer
id|hmac
)paren
id|sctp_crypto_free_tfm
c_func
(paren
id|sctp_sk
c_func
(paren
id|ep-&gt;base.sk
)paren
op_member_access_from_pointer
id|hmac
)paren
suffix:semicolon
multiline_comment|/* Cleanup. */
id|sctp_inq_free
c_func
(paren
op_amp
id|ep-&gt;base.inqueue
)paren
suffix:semicolon
id|sctp_bind_addr_free
c_func
(paren
op_amp
id|ep-&gt;base.bind_addr
)paren
suffix:semicolon
multiline_comment|/* Remove and free the port */
r_if
c_cond
(paren
id|sctp_sk
c_func
(paren
id|ep-&gt;base.sk
)paren
op_member_access_from_pointer
id|bind_hash
)paren
id|sctp_put_port
c_func
(paren
id|ep-&gt;base.sk
)paren
suffix:semicolon
multiline_comment|/* Give up our hold on the sock. */
r_if
c_cond
(paren
id|ep-&gt;base.sk
)paren
id|sock_put
c_func
(paren
id|ep-&gt;base.sk
)paren
suffix:semicolon
multiline_comment|/* Finally, free up our memory. */
r_if
c_cond
(paren
id|ep-&gt;base.malloced
)paren
(brace
id|kfree
c_func
(paren
id|ep
)paren
suffix:semicolon
id|SCTP_DBG_OBJCNT_DEC
c_func
(paren
id|ep
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Hold a reference to an endpoint. */
DECL|function|sctp_endpoint_hold
r_void
id|sctp_endpoint_hold
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|ep-&gt;base.refcnt
)paren
suffix:semicolon
)brace
multiline_comment|/* Release a reference to an endpoint and clean up if there are&n; * no more references.&n; */
DECL|function|sctp_endpoint_put
r_void
id|sctp_endpoint_put
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ep-&gt;base.refcnt
)paren
)paren
id|sctp_endpoint_destroy
c_func
(paren
id|ep
)paren
suffix:semicolon
)brace
multiline_comment|/* Is this the endpoint we are looking for?  */
DECL|function|sctp_endpoint_is_match
r_struct
id|sctp_endpoint
op_star
id|sctp_endpoint_is_match
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
comma
r_const
r_union
id|sctp_addr
op_star
id|laddr
)paren
(brace
r_struct
id|sctp_endpoint
op_star
id|retval
suffix:semicolon
id|sctp_read_lock
c_func
(paren
op_amp
id|ep-&gt;base.addr_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep-&gt;base.bind_addr.port
op_eq
id|laddr-&gt;v4.sin_port
)paren
(brace
r_if
c_cond
(paren
id|sctp_bind_addr_match
c_func
(paren
op_amp
id|ep-&gt;base.bind_addr
comma
id|laddr
comma
id|sctp_sk
c_func
(paren
id|ep-&gt;base.sk
)paren
)paren
)paren
(brace
id|retval
op_assign
id|ep
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|retval
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
id|sctp_read_unlock
c_func
(paren
op_amp
id|ep-&gt;base.addr_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Find the association that goes with this chunk.&n; * We do a linear search of the associations for this endpoint.&n; * We return the matching transport address too.&n; */
DECL|function|__sctp_endpoint_lookup_assoc
r_struct
id|sctp_association
op_star
id|__sctp_endpoint_lookup_assoc
c_func
(paren
r_const
r_struct
id|sctp_endpoint
op_star
id|ep
comma
r_const
r_union
id|sctp_addr
op_star
id|paddr
comma
r_struct
id|sctp_transport
op_star
op_star
id|transport
)paren
(brace
r_int
id|rport
suffix:semicolon
r_struct
id|sctp_association
op_star
id|asoc
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|rport
op_assign
id|paddr-&gt;v4.sin_port
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|ep-&gt;asocs
)paren
(brace
id|asoc
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|sctp_association
comma
id|asocs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rport
op_eq
id|asoc-&gt;peer.port
)paren
(brace
id|sctp_read_lock
c_func
(paren
op_amp
id|asoc-&gt;base.addr_lock
)paren
suffix:semicolon
op_star
id|transport
op_assign
id|sctp_assoc_lookup_paddr
c_func
(paren
id|asoc
comma
id|paddr
)paren
suffix:semicolon
id|sctp_read_unlock
c_func
(paren
op_amp
id|asoc-&gt;base.addr_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|transport
)paren
r_return
id|asoc
suffix:semicolon
)brace
)brace
op_star
id|transport
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Lookup association on an endpoint based on a peer address.  BH-safe.  */
DECL|function|sctp_endpoint_lookup_assoc
r_struct
id|sctp_association
op_star
id|sctp_endpoint_lookup_assoc
c_func
(paren
r_const
r_struct
id|sctp_endpoint
op_star
id|ep
comma
r_const
r_union
id|sctp_addr
op_star
id|paddr
comma
r_struct
id|sctp_transport
op_star
op_star
id|transport
)paren
(brace
r_struct
id|sctp_association
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
id|__sctp_endpoint_lookup_assoc
c_func
(paren
id|ep
comma
id|paddr
comma
id|transport
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
multiline_comment|/* Look for any peeled off association from the endpoint that matches the&n; * given peer address.&n; */
DECL|function|sctp_endpoint_is_peeled_off
r_int
id|sctp_endpoint_is_peeled_off
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
comma
r_const
r_union
id|sctp_addr
op_star
id|paddr
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|sctp_sockaddr_entry
op_star
id|addr
suffix:semicolon
r_struct
id|sctp_bind_addr
op_star
id|bp
suffix:semicolon
id|sctp_read_lock
c_func
(paren
op_amp
id|ep-&gt;base.addr_lock
)paren
suffix:semicolon
id|bp
op_assign
op_amp
id|ep-&gt;base.bind_addr
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|bp-&gt;address_list
)paren
(brace
id|addr
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|sctp_sockaddr_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sctp_has_association
c_func
(paren
op_amp
id|addr-&gt;a
comma
id|paddr
)paren
)paren
(brace
id|sctp_read_unlock
c_func
(paren
op_amp
id|ep-&gt;base.addr_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|sctp_read_unlock
c_func
(paren
op_amp
id|ep-&gt;base.addr_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Do delayed input processing.  This is scheduled by sctp_rcv().&n; * This may be called on BH or task time.&n; */
DECL|function|sctp_endpoint_bh_rcv
r_static
r_void
id|sctp_endpoint_bh_rcv
c_func
(paren
r_struct
id|sctp_endpoint
op_star
id|ep
)paren
(brace
r_struct
id|sctp_association
op_star
id|asoc
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_struct
id|sctp_transport
op_star
id|transport
suffix:semicolon
r_struct
id|sctp_chunk
op_star
id|chunk
suffix:semicolon
r_struct
id|sctp_inq
op_star
id|inqueue
suffix:semicolon
id|sctp_subtype_t
id|subtype
suffix:semicolon
id|sctp_state_t
id|state
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ep-&gt;base.dead
)paren
r_return
suffix:semicolon
id|asoc
op_assign
l_int|NULL
suffix:semicolon
id|inqueue
op_assign
op_amp
id|ep-&gt;base.inqueue
suffix:semicolon
id|sk
op_assign
id|ep-&gt;base.sk
suffix:semicolon
r_while
c_loop
(paren
l_int|NULL
op_ne
(paren
id|chunk
op_assign
id|sctp_inq_pop
c_func
(paren
id|inqueue
)paren
)paren
)paren
(brace
id|subtype.chunk
op_assign
id|chunk-&gt;chunk_hdr-&gt;type
suffix:semicolon
multiline_comment|/* We might have grown an association since last we&n;&t;&t; * looked, so try again.&n;&t;&t; *&n;&t;&t; * This happens when we&squot;ve just processed our&n;&t;&t; * COOKIE-ECHO chunk.&n;&t;&t; */
r_if
c_cond
(paren
l_int|NULL
op_eq
id|chunk-&gt;asoc
)paren
(brace
id|asoc
op_assign
id|sctp_endpoint_lookup_assoc
c_func
(paren
id|ep
comma
id|sctp_source
c_func
(paren
id|chunk
)paren
comma
op_amp
id|transport
)paren
suffix:semicolon
id|chunk-&gt;asoc
op_assign
id|asoc
suffix:semicolon
id|chunk-&gt;transport
op_assign
id|transport
suffix:semicolon
)brace
id|state
op_assign
id|asoc
ques
c_cond
id|asoc-&gt;state
suffix:colon
id|SCTP_STATE_CLOSED
suffix:semicolon
multiline_comment|/* Remember where the last DATA chunk came from so we&n;&t;&t; * know where to send the SACK.&n;&t;&t; */
r_if
c_cond
(paren
id|asoc
op_logical_and
id|sctp_chunk_is_data
c_func
(paren
id|chunk
)paren
)paren
id|asoc-&gt;peer.last_data_from
op_assign
id|chunk-&gt;transport
suffix:semicolon
r_else
id|SCTP_INC_STATS
c_func
(paren
id|SctpInCtrlChunks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;transport
)paren
id|chunk-&gt;transport-&gt;last_time_heard
op_assign
id|jiffies
suffix:semicolon
id|error
op_assign
id|sctp_do_sm
c_func
(paren
id|SCTP_EVENT_T_CHUNK
comma
id|subtype
comma
id|state
comma
id|ep
comma
id|asoc
comma
id|chunk
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_and
id|chunk
)paren
id|chunk-&gt;pdiscard
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Check to see if the endpoint is freed in response to&n;&t;&t; * the incoming chunk. If so, get out of the while loop.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sctp_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|ep
)paren
r_break
suffix:semicolon
)brace
)brace
eof
