multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001-2003 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * This abstraction carries sctp events to the ULP (sockets).&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Sridhar Samudrala     &lt;sri@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/sctp/structs.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
multiline_comment|/* Forward declarations for internal helpers.  */
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_ulpq_reasm
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_ulpevent
op_star
)paren
suffix:semicolon
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_ulpq_order
c_func
(paren
r_struct
id|sctp_ulpq
op_star
comma
r_struct
id|sctp_ulpevent
op_star
)paren
suffix:semicolon
multiline_comment|/* 1st Level Abstractions */
multiline_comment|/* Create a new ULP queue.  */
DECL|function|sctp_ulpq_new
r_struct
id|sctp_ulpq
op_star
id|sctp_ulpq_new
c_func
(paren
id|sctp_association_t
op_star
id|asoc
comma
r_int
id|priority
)paren
(brace
r_struct
id|sctp_ulpq
op_star
id|ulpq
suffix:semicolon
id|ulpq
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sctp_ulpq
)paren
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulpq
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sctp_ulpq_init
c_func
(paren
id|ulpq
comma
id|asoc
)paren
)paren
r_goto
id|fail_init
suffix:semicolon
id|ulpq-&gt;malloced
op_assign
l_int|1
suffix:semicolon
r_return
id|ulpq
suffix:semicolon
id|fail_init
suffix:colon
id|kfree
c_func
(paren
id|ulpq
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Initialize a ULP queue from a block of memory.  */
DECL|function|sctp_ulpq_init
r_struct
id|sctp_ulpq
op_star
id|sctp_ulpq_init
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
id|sctp_association_t
op_star
id|asoc
)paren
(brace
id|memset
c_func
(paren
id|ulpq
comma
r_sizeof
(paren
r_struct
id|sctp_ulpq
)paren
comma
l_int|0x00
)paren
suffix:semicolon
id|ulpq-&gt;asoc
op_assign
id|asoc
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|ulpq-&gt;reasm
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|ulpq-&gt;lobby
)paren
suffix:semicolon
id|ulpq-&gt;pd_mode
op_assign
l_int|0
suffix:semicolon
id|ulpq-&gt;malloced
op_assign
l_int|0
suffix:semicolon
r_return
id|ulpq
suffix:semicolon
)brace
multiline_comment|/* Flush the reassembly and ordering queues.  */
DECL|function|sctp_ulpq_flush
r_void
id|sctp_ulpq_flush
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|event
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|ulpq-&gt;lobby
)paren
)paren
)paren
(brace
id|event
op_assign
id|sctp_skb2event
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sctp_ulpevent_free
c_func
(paren
id|event
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|ulpq-&gt;reasm
)paren
)paren
)paren
(brace
id|event
op_assign
id|sctp_skb2event
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sctp_ulpevent_free
c_func
(paren
id|event
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Dispose of a ulpqueue.  */
DECL|function|sctp_ulpq_free
r_void
id|sctp_ulpq_free
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
)paren
(brace
id|sctp_ulpq_flush
c_func
(paren
id|ulpq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ulpq-&gt;malloced
)paren
id|kfree
c_func
(paren
id|ulpq
)paren
suffix:semicolon
)brace
multiline_comment|/* Process an incoming DATA chunk.  */
DECL|function|sctp_ulpq_tail_data
r_int
id|sctp_ulpq_tail_data
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
id|sctp_chunk_t
op_star
id|chunk
comma
r_int
id|priority
)paren
(brace
r_struct
id|sk_buff_head
id|temp
suffix:semicolon
id|sctp_data_chunk_t
op_star
id|hdr
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|event
suffix:semicolon
id|hdr
op_assign
(paren
id|sctp_data_chunk_t
op_star
)paren
id|chunk-&gt;chunk_hdr
suffix:semicolon
multiline_comment|/* Create an event from the incoming chunk. */
id|event
op_assign
id|sctp_ulpevent_make_rcvmsg
c_func
(paren
id|chunk-&gt;asoc
comma
id|chunk
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Do reassembly if needed.  */
id|event
op_assign
id|sctp_ulpq_reasm
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
multiline_comment|/* Do ordering if needed.  */
r_if
c_cond
(paren
(paren
id|event
)paren
op_logical_and
(paren
id|event-&gt;msg_flags
op_amp
id|MSG_EOR
)paren
)paren
(brace
multiline_comment|/* Create a temporary list to collect chunks on.  */
id|skb_queue_head_init
c_func
(paren
op_amp
id|temp
)paren
suffix:semicolon
id|__skb_queue_tail
c_func
(paren
op_amp
id|temp
comma
id|sctp_event2skb
c_func
(paren
id|event
)paren
)paren
suffix:semicolon
id|event
op_assign
id|sctp_ulpq_order
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
)brace
multiline_comment|/* Send event to the ULP.  */
r_if
c_cond
(paren
id|event
)paren
id|sctp_ulpq_tail_event
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear the partial delivery mode for this socket.   Note: This&n; * assumes that no association is currently in partial delivery mode.&n; */
DECL|function|sctp_clear_pd
r_int
id|sctp_clear_pd
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_struct
id|sctp_opt
op_star
id|sp
suffix:semicolon
id|sp
op_assign
id|sctp_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sp-&gt;pd_mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_queue_empty
c_func
(paren
op_amp
id|sp-&gt;pd_lobby
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|sctp_skb_list_tail
c_func
(paren
op_amp
id|sp-&gt;pd_lobby
comma
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
id|list
op_assign
(paren
r_struct
id|list_head
op_star
)paren
op_amp
id|sctp_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|pd_lobby
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|list
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
multiline_comment|/* Clear the pd_mode and restart any pending messages waiting for delivery. */
DECL|function|sctp_ulpq_clear_pd
r_static
r_int
id|sctp_ulpq_clear_pd
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
)paren
(brace
id|ulpq-&gt;pd_mode
op_assign
l_int|0
suffix:semicolon
r_return
id|sctp_clear_pd
c_func
(paren
id|ulpq-&gt;asoc-&gt;base.sk
)paren
suffix:semicolon
)brace
multiline_comment|/* Add a new event for propagation to the ULP.  */
DECL|function|sctp_ulpq_tail_event
r_int
id|sctp_ulpq_tail_event
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_ulpevent
op_star
id|event
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|ulpq-&gt;asoc-&gt;base.sk
suffix:semicolon
r_struct
id|sk_buff_head
op_star
id|queue
suffix:semicolon
r_int
id|clear_pd
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If the socket is just going to throw this away, do not&n;&t; * even try to deliver it.&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;dead
op_logical_or
(paren
id|sk-&gt;shutdown
op_amp
id|RCV_SHUTDOWN
)paren
)paren
r_goto
id|out_free
suffix:semicolon
multiline_comment|/* Check if the user wishes to receive this event.  */
r_if
c_cond
(paren
op_logical_neg
id|sctp_ulpevent_is_enabled
c_func
(paren
id|event
comma
op_amp
id|sctp_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|subscribe
)paren
)paren
r_goto
id|out_free
suffix:semicolon
multiline_comment|/* If we are in partial delivery mode, post to the lobby until&n;&t; * partial delivery is cleared, unless, of course _this_ is&n;&t; * the association the cause of the partial delivery.&n;&t; */
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
id|pd_mode
)paren
(brace
id|queue
op_assign
op_amp
id|sk-&gt;receive_queue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ulpq-&gt;pd_mode
)paren
(brace
r_if
c_cond
(paren
id|event-&gt;msg_flags
op_amp
id|MSG_NOTIFICATION
)paren
id|queue
op_assign
op_amp
id|sctp_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|pd_lobby
suffix:semicolon
r_else
(brace
id|clear_pd
op_assign
id|event-&gt;msg_flags
op_amp
id|MSG_EOR
suffix:semicolon
id|queue
op_assign
op_amp
id|sk-&gt;receive_queue
suffix:semicolon
)brace
)brace
r_else
id|queue
op_assign
op_amp
id|sctp_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|pd_lobby
suffix:semicolon
multiline_comment|/* If we are harvesting multiple skbs they will be&n;&t; * collected on a list.&n;&t; */
r_if
c_cond
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
op_member_access_from_pointer
id|list
)paren
id|sctp_skb_list_tail
c_func
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
op_member_access_from_pointer
id|list
comma
id|queue
)paren
suffix:semicolon
r_else
id|__skb_queue_tail
c_func
(paren
id|queue
comma
id|sctp_event2skb
c_func
(paren
id|event
)paren
)paren
suffix:semicolon
multiline_comment|/* Did we just complete partial delivery and need to get&n;&t; * rolling again?  Move pending data to the receive&n;&t; * queue.&n;&t; */
r_if
c_cond
(paren
id|clear_pd
)paren
id|sctp_ulpq_clear_pd
c_func
(paren
id|ulpq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue
op_eq
op_amp
id|sk-&gt;receive_queue
)paren
id|wake_up_interruptible
c_func
(paren
id|sk-&gt;sleep
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|out_free
suffix:colon
r_if
c_cond
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
op_member_access_from_pointer
id|list
)paren
id|skb_queue_purge
c_func
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
op_member_access_from_pointer
id|list
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* 2nd Level Abstractions */
multiline_comment|/* Helper function to store chunks that need to be reassembled.  */
DECL|function|sctp_ulpq_store_reasm
r_static
r_inline
r_void
id|sctp_ulpq_store_reasm
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_ulpevent
op_star
id|event
)paren
(brace
r_struct
id|sk_buff
op_star
id|pos
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|cevent
suffix:semicolon
id|__u32
id|tsn
comma
id|ctsn
suffix:semicolon
id|tsn
op_assign
id|event-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
multiline_comment|/* Find the right place in this list. We store them by TSN.  */
id|skb_queue_walk
c_func
(paren
op_amp
id|ulpq-&gt;reasm
comma
id|pos
)paren
(brace
id|cevent
op_assign
id|sctp_skb2event
c_func
(paren
id|pos
)paren
suffix:semicolon
id|ctsn
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
r_if
c_cond
(paren
id|TSN_lt
c_func
(paren
id|tsn
comma
id|ctsn
)paren
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* If the queue is empty, we have a different function to call.  */
r_if
c_cond
(paren
id|skb_peek
c_func
(paren
op_amp
id|ulpq-&gt;reasm
)paren
)paren
id|__skb_insert
c_func
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
comma
id|pos-&gt;prev
comma
id|pos
comma
op_amp
id|ulpq-&gt;reasm
)paren
suffix:semicolon
r_else
id|__skb_queue_tail
c_func
(paren
op_amp
id|ulpq-&gt;reasm
comma
id|sctp_event2skb
c_func
(paren
id|event
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Helper function to return an event corresponding to the reassembled&n; * datagram.&n; * This routine creates a re-assembled skb given the first and last skb&squot;s&n; * as stored in the reassembly queue. The skb&squot;s may be non-linear if the sctp&n; * payload was fragmented on the way and ip had to reassemble them.&n; * We add the rest of skb&squot;s to the first skb&squot;s fraglist.&n; */
DECL|function|sctp_make_reassembled_event
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_make_reassembled_event
c_func
(paren
r_struct
id|sk_buff
op_star
id|f_frag
comma
r_struct
id|sk_buff
op_star
id|l_frag
)paren
(brace
r_struct
id|sk_buff
op_star
id|pos
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|event
suffix:semicolon
r_struct
id|sk_buff
op_star
id|pnext
comma
op_star
id|last
suffix:semicolon
r_struct
id|sk_buff
op_star
id|list
op_assign
id|skb_shinfo
c_func
(paren
id|f_frag
)paren
op_member_access_from_pointer
id|frag_list
suffix:semicolon
multiline_comment|/* Store the pointer to the 2nd skb */
r_if
c_cond
(paren
id|f_frag
op_eq
id|l_frag
)paren
id|pos
op_assign
l_int|NULL
suffix:semicolon
r_else
id|pos
op_assign
id|f_frag-&gt;next
suffix:semicolon
multiline_comment|/* Get the last skb in the f_frag&squot;s frag_list if present. */
r_for
c_loop
(paren
id|last
op_assign
id|list
suffix:semicolon
id|list
suffix:semicolon
id|last
op_assign
id|list
comma
id|list
op_assign
id|list-&gt;next
)paren
suffix:semicolon
multiline_comment|/* Add the list of remaining fragments to the first fragments&n;&t; * frag_list.&n;&t; */
r_if
c_cond
(paren
id|last
)paren
id|last-&gt;next
op_assign
id|pos
suffix:semicolon
r_else
id|skb_shinfo
c_func
(paren
id|f_frag
)paren
op_member_access_from_pointer
id|frag_list
op_assign
id|pos
suffix:semicolon
multiline_comment|/* Remove the first fragment from the reassembly queue.  */
id|__skb_unlink
c_func
(paren
id|f_frag
comma
id|f_frag-&gt;list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pos
)paren
(brace
id|pnext
op_assign
id|pos-&gt;next
suffix:semicolon
multiline_comment|/* Update the len and data_len fields of the first fragment. */
id|f_frag-&gt;len
op_add_assign
id|pos-&gt;len
suffix:semicolon
id|f_frag-&gt;data_len
op_add_assign
id|pos-&gt;len
suffix:semicolon
multiline_comment|/* Remove the fragment from the reassembly queue.  */
id|__skb_unlink
c_func
(paren
id|pos
comma
id|pos-&gt;list
)paren
suffix:semicolon
multiline_comment|/* Break if we have reached the last fragment.  */
r_if
c_cond
(paren
id|pos
op_eq
id|l_frag
)paren
r_break
suffix:semicolon
id|pos-&gt;next
op_assign
id|pnext
suffix:semicolon
id|pos
op_assign
id|pnext
suffix:semicolon
)brace
suffix:semicolon
id|event
op_assign
id|sctp_skb2event
c_func
(paren
id|f_frag
)paren
suffix:semicolon
id|SCTP_INC_STATS
c_func
(paren
id|SctpReasmUsrMsgs
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
)brace
multiline_comment|/* Helper function to check if an incoming chunk has filled up the last&n; * missing fragment in a SCTP datagram and return the corresponding event.&n; */
DECL|function|sctp_ulpq_retrieve_reassembled
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_ulpq_retrieve_reassembled
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
)paren
(brace
r_struct
id|sk_buff
op_star
id|pos
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|cevent
suffix:semicolon
r_struct
id|sk_buff
op_star
id|first_frag
op_assign
l_int|NULL
suffix:semicolon
id|__u32
id|ctsn
comma
id|next_tsn
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|retval
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initialized to 0 just to avoid compiler warning message.  Will&n;&t; * never be used with this value. It is referenced only after it&n;&t; * is set when we find the first fragment of a message.&n;&t; */
id|next_tsn
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The chunks are held in the reasm queue sorted by TSN.&n;&t; * Walk through the queue sequentially and look for a sequence of&n;&t; * fragmented chunks that complete a datagram.&n;&t; * &squot;first_frag&squot; and next_tsn are reset when we find a chunk which&n;&t; * is the first fragment of a datagram. Once these 2 fields are set&n;&t; * we expect to find the remaining middle fragments and the last&n;&t; * fragment in order. If not, first_frag is reset to NULL and we&n;&t; * start the next pass when we find another first fragment.&n;&t; */
id|skb_queue_walk
c_func
(paren
op_amp
id|ulpq-&gt;reasm
comma
id|pos
)paren
(brace
id|cevent
op_assign
id|sctp_skb2event
c_func
(paren
id|pos
)paren
suffix:semicolon
id|ctsn
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
r_switch
c_cond
(paren
id|cevent-&gt;msg_flags
op_amp
id|SCTP_DATA_FRAG_MASK
)paren
(brace
r_case
id|SCTP_DATA_FIRST_FRAG
suffix:colon
id|first_frag
op_assign
id|pos
suffix:semicolon
id|next_tsn
op_assign
id|ctsn
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_DATA_MIDDLE_FRAG
suffix:colon
r_if
c_cond
(paren
(paren
id|first_frag
)paren
op_logical_and
(paren
id|ctsn
op_eq
id|next_tsn
)paren
)paren
id|next_tsn
op_increment
suffix:semicolon
r_else
id|first_frag
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_DATA_LAST_FRAG
suffix:colon
r_if
c_cond
(paren
id|first_frag
op_logical_and
(paren
id|ctsn
op_eq
id|next_tsn
)paren
)paren
r_goto
id|found
suffix:semicolon
r_else
id|first_frag
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
id|done
suffix:colon
r_return
id|retval
suffix:semicolon
id|found
suffix:colon
id|retval
op_assign
id|sctp_make_reassembled_event
c_func
(paren
id|first_frag
comma
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|retval-&gt;msg_flags
op_or_assign
id|MSG_EOR
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* Retrieve the next set of fragments of a partial message. */
DECL|function|sctp_ulpq_retrieve_partial
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_ulpq_retrieve_partial
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
)paren
(brace
r_struct
id|sk_buff
op_star
id|pos
comma
op_star
id|last_frag
comma
op_star
id|first_frag
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|cevent
suffix:semicolon
id|__u32
id|ctsn
comma
id|next_tsn
suffix:semicolon
r_int
id|is_last
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|retval
suffix:semicolon
multiline_comment|/* The chunks are held in the reasm queue sorted by TSN.&n;&t; * Walk through the queue sequentially and look for the first&n;&t; * sequence of fragmented chunks.&n;&t; */
r_if
c_cond
(paren
id|skb_queue_empty
c_func
(paren
op_amp
id|ulpq-&gt;reasm
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|last_frag
op_assign
id|first_frag
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
l_int|NULL
suffix:semicolon
id|next_tsn
op_assign
l_int|0
suffix:semicolon
id|is_last
op_assign
l_int|0
suffix:semicolon
id|skb_queue_walk
c_func
(paren
op_amp
id|ulpq-&gt;reasm
comma
id|pos
)paren
(brace
id|cevent
op_assign
id|sctp_skb2event
c_func
(paren
id|pos
)paren
suffix:semicolon
id|ctsn
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
r_switch
c_cond
(paren
id|cevent-&gt;msg_flags
op_amp
id|SCTP_DATA_FRAG_MASK
)paren
(brace
r_case
id|SCTP_DATA_MIDDLE_FRAG
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|first_frag
)paren
(brace
id|first_frag
op_assign
id|pos
suffix:semicolon
id|next_tsn
op_assign
id|ctsn
op_plus
l_int|1
suffix:semicolon
id|last_frag
op_assign
id|pos
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|next_tsn
op_eq
id|ctsn
)paren
id|next_tsn
op_increment
suffix:semicolon
r_else
r_goto
id|done
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_DATA_LAST_FRAG
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|first_frag
)paren
id|first_frag
op_assign
id|pos
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ctsn
op_ne
id|next_tsn
)paren
r_goto
id|done
suffix:semicolon
id|last_frag
op_assign
id|pos
suffix:semicolon
id|is_last
op_assign
l_int|1
suffix:semicolon
r_goto
id|done
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* We have the reassembled event. There is no need to look&n;&t; * further.&n;&t; */
id|done
suffix:colon
id|retval
op_assign
id|sctp_make_reassembled_event
c_func
(paren
id|first_frag
comma
id|last_frag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_logical_and
id|is_last
)paren
id|retval-&gt;msg_flags
op_or_assign
id|MSG_EOR
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Helper function to reassemble chunks.  Hold chunks on the reasm queue that&n; * need reassembling.&n; */
DECL|function|sctp_ulpq_reasm
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_ulpq_reasm
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_ulpevent
op_star
id|event
)paren
(brace
r_struct
id|sctp_ulpevent
op_star
id|retval
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Check if this is part of a fragmented message.  */
r_if
c_cond
(paren
id|SCTP_DATA_NOT_FRAG
op_eq
(paren
id|event-&gt;msg_flags
op_amp
id|SCTP_DATA_FRAG_MASK
)paren
)paren
(brace
id|event-&gt;msg_flags
op_or_assign
id|MSG_EOR
suffix:semicolon
r_return
id|event
suffix:semicolon
)brace
id|sctp_ulpq_store_reasm
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulpq-&gt;pd_mode
)paren
id|retval
op_assign
id|sctp_ulpq_retrieve_reassembled
c_func
(paren
id|ulpq
)paren
suffix:semicolon
r_else
(brace
id|__u32
id|ctsn
comma
id|ctsnap
suffix:semicolon
multiline_comment|/* Do not even bother unless this is the next tsn to&n;&t;&t; * be delivered.&n;&t;&t; */
id|ctsn
op_assign
id|event-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
id|ctsnap
op_assign
id|sctp_tsnmap_get_ctsn
c_func
(paren
op_amp
id|ulpq-&gt;asoc-&gt;peer.tsn_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TSN_lte
c_func
(paren
id|ctsn
comma
id|ctsnap
)paren
)paren
id|retval
op_assign
id|sctp_ulpq_retrieve_partial
c_func
(paren
id|ulpq
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Retrieve the first part (sequential fragments) for partial delivery.  */
DECL|function|sctp_ulpq_retrieve_first
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_ulpq_retrieve_first
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
)paren
(brace
r_struct
id|sk_buff
op_star
id|pos
comma
op_star
id|last_frag
comma
op_star
id|first_frag
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|cevent
suffix:semicolon
id|__u32
id|ctsn
comma
id|next_tsn
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|retval
suffix:semicolon
multiline_comment|/* The chunks are held in the reasm queue sorted by TSN.&n;&t; * Walk through the queue sequentially and look for a sequence of&n;&t; * fragmented chunks that start a datagram.&n;&t; */
r_if
c_cond
(paren
id|skb_queue_empty
c_func
(paren
op_amp
id|ulpq-&gt;reasm
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|last_frag
op_assign
id|first_frag
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
l_int|NULL
suffix:semicolon
id|next_tsn
op_assign
l_int|0
suffix:semicolon
id|skb_queue_walk
c_func
(paren
op_amp
id|ulpq-&gt;reasm
comma
id|pos
)paren
(brace
id|cevent
op_assign
id|sctp_skb2event
c_func
(paren
id|pos
)paren
suffix:semicolon
id|ctsn
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
r_switch
c_cond
(paren
id|cevent-&gt;msg_flags
op_amp
id|SCTP_DATA_FRAG_MASK
)paren
(brace
r_case
id|SCTP_DATA_FIRST_FRAG
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|first_frag
)paren
(brace
id|first_frag
op_assign
id|pos
suffix:semicolon
id|next_tsn
op_assign
id|ctsn
op_plus
l_int|1
suffix:semicolon
id|last_frag
op_assign
id|pos
suffix:semicolon
)brace
r_else
r_goto
id|done
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCTP_DATA_MIDDLE_FRAG
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|first_frag
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ctsn
op_eq
id|next_tsn
)paren
(brace
id|next_tsn
op_increment
suffix:semicolon
id|last_frag
op_assign
id|pos
suffix:semicolon
)brace
r_else
r_goto
id|done
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* We have the reassembled event. There is no need to look&n;&t; * further.&n;&t; */
id|done
suffix:colon
id|retval
op_assign
id|sctp_make_reassembled_event
c_func
(paren
id|first_frag
comma
id|last_frag
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Helper function to gather skbs that have possibly become&n; * ordered by an an incoming chunk.&n; */
DECL|function|sctp_ulpq_retrieve_ordered
r_static
r_inline
r_void
id|sctp_ulpq_retrieve_ordered
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_ulpevent
op_star
id|event
)paren
(brace
r_struct
id|sk_buff
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|cevent
suffix:semicolon
r_struct
id|sctp_stream
op_star
id|in
suffix:semicolon
id|__u16
id|sid
comma
id|csid
suffix:semicolon
id|__u16
id|ssn
comma
id|cssn
suffix:semicolon
id|sid
op_assign
id|event-&gt;sndrcvinfo.sinfo_stream
suffix:semicolon
id|ssn
op_assign
id|event-&gt;sndrcvinfo.sinfo_ssn
suffix:semicolon
id|in
op_assign
op_amp
id|ulpq-&gt;asoc-&gt;ssnmap-&gt;in
suffix:semicolon
multiline_comment|/* We are holding the chunks by stream, by SSN.  */
id|sctp_skb_for_each
c_func
(paren
id|pos
comma
op_amp
id|ulpq-&gt;lobby
comma
id|tmp
)paren
(brace
id|cevent
op_assign
(paren
r_struct
id|sctp_ulpevent
op_star
)paren
id|pos-&gt;cb
suffix:semicolon
id|csid
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_stream
suffix:semicolon
id|cssn
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_ssn
suffix:semicolon
multiline_comment|/* Have we gone too far?  */
r_if
c_cond
(paren
id|csid
OG
id|sid
)paren
r_break
suffix:semicolon
multiline_comment|/* Have we not gone far enough?  */
r_if
c_cond
(paren
id|csid
OL
id|sid
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cssn
op_ne
id|sctp_ssn_peek
c_func
(paren
id|in
comma
id|sid
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Found it, so mark in the ssnmap. */
id|sctp_ssn_next
c_func
(paren
id|in
comma
id|sid
)paren
suffix:semicolon
id|__skb_unlink
c_func
(paren
id|pos
comma
id|pos-&gt;list
)paren
suffix:semicolon
multiline_comment|/* Attach all gathered skbs to the event.  */
id|__skb_queue_tail
c_func
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
op_member_access_from_pointer
id|list
comma
id|pos
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Helper function to store chunks needing ordering.  */
DECL|function|sctp_ulpq_store_ordered
r_static
r_inline
r_void
id|sctp_ulpq_store_ordered
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_ulpevent
op_star
id|event
)paren
(brace
r_struct
id|sk_buff
op_star
id|pos
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|cevent
suffix:semicolon
id|__u16
id|sid
comma
id|csid
suffix:semicolon
id|__u16
id|ssn
comma
id|cssn
suffix:semicolon
id|sid
op_assign
id|event-&gt;sndrcvinfo.sinfo_stream
suffix:semicolon
id|ssn
op_assign
id|event-&gt;sndrcvinfo.sinfo_ssn
suffix:semicolon
multiline_comment|/* Find the right place in this list.  We store them by&n;&t; * stream ID and then by SSN.&n;&t; */
id|skb_queue_walk
c_func
(paren
op_amp
id|ulpq-&gt;lobby
comma
id|pos
)paren
(brace
id|cevent
op_assign
(paren
r_struct
id|sctp_ulpevent
op_star
)paren
id|pos-&gt;cb
suffix:semicolon
id|csid
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_stream
suffix:semicolon
id|cssn
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_ssn
suffix:semicolon
r_if
c_cond
(paren
id|csid
OG
id|sid
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|csid
op_eq
id|sid
op_logical_and
id|SSN_lt
c_func
(paren
id|ssn
comma
id|cssn
)paren
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* If the queue is empty, we have a different function to call.  */
r_if
c_cond
(paren
id|skb_peek
c_func
(paren
op_amp
id|ulpq-&gt;lobby
)paren
)paren
id|__skb_insert
c_func
(paren
id|sctp_event2skb
c_func
(paren
id|event
)paren
comma
id|pos-&gt;prev
comma
id|pos
comma
op_amp
id|ulpq-&gt;lobby
)paren
suffix:semicolon
r_else
id|__skb_queue_tail
c_func
(paren
op_amp
id|ulpq-&gt;lobby
comma
id|sctp_event2skb
c_func
(paren
id|event
)paren
)paren
suffix:semicolon
)brace
DECL|function|sctp_ulpq_order
r_static
r_inline
r_struct
id|sctp_ulpevent
op_star
id|sctp_ulpq_order
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_ulpevent
op_star
id|event
)paren
(brace
id|__u16
id|sid
comma
id|ssn
suffix:semicolon
r_struct
id|sctp_stream
op_star
id|in
suffix:semicolon
multiline_comment|/* Check if this message needs ordering.  */
r_if
c_cond
(paren
id|SCTP_DATA_UNORDERED
op_amp
id|event-&gt;msg_flags
)paren
r_return
id|event
suffix:semicolon
multiline_comment|/* Note: The stream ID must be verified before this routine.  */
id|sid
op_assign
id|event-&gt;sndrcvinfo.sinfo_stream
suffix:semicolon
id|ssn
op_assign
id|event-&gt;sndrcvinfo.sinfo_ssn
suffix:semicolon
id|in
op_assign
op_amp
id|ulpq-&gt;asoc-&gt;ssnmap-&gt;in
suffix:semicolon
multiline_comment|/* Is this the expected SSN for this stream ID?  */
r_if
c_cond
(paren
id|ssn
op_ne
id|sctp_ssn_peek
c_func
(paren
id|in
comma
id|sid
)paren
)paren
(brace
multiline_comment|/* We&squot;ve received something out of order, so find where it&n;&t;&t; * needs to be placed.  We order by stream and then by SSN.&n;&t;&t; */
id|sctp_ulpq_store_ordered
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Mark that the next chunk has been found.  */
id|sctp_ssn_next
c_func
(paren
id|in
comma
id|sid
)paren
suffix:semicolon
multiline_comment|/* Go find any other chunks that were waiting for&n;&t; * ordering.&n;&t; */
id|sctp_ulpq_retrieve_ordered
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
r_return
id|event
suffix:semicolon
)brace
multiline_comment|/* Renege &squot;needed&squot; bytes from the ordering queue. */
DECL|function|sctp_ulpq_renege_order
r_static
id|__u16
id|sctp_ulpq_renege_order
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
id|__u16
id|needed
)paren
(brace
id|__u16
id|freed
op_assign
l_int|0
suffix:semicolon
id|__u32
id|tsn
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|event
suffix:semicolon
r_struct
id|sctp_tsnmap
op_star
id|tsnmap
suffix:semicolon
id|tsnmap
op_assign
op_amp
id|ulpq-&gt;asoc-&gt;peer.tsn_map
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|__skb_dequeue_tail
c_func
(paren
op_amp
id|ulpq-&gt;lobby
)paren
)paren
)paren
(brace
id|freed
op_add_assign
id|skb_headlen
c_func
(paren
id|skb
)paren
suffix:semicolon
id|event
op_assign
id|sctp_skb2event
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tsn
op_assign
id|event-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
id|sctp_ulpevent_free
c_func
(paren
id|event
)paren
suffix:semicolon
id|sctp_tsnmap_renege
c_func
(paren
id|tsnmap
comma
id|tsn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freed
op_ge
id|needed
)paren
r_return
id|freed
suffix:semicolon
)brace
r_return
id|freed
suffix:semicolon
)brace
multiline_comment|/* Renege &squot;needed&squot; bytes from the reassembly queue. */
DECL|function|sctp_ulpq_renege_frags
r_static
id|__u16
id|sctp_ulpq_renege_frags
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
id|__u16
id|needed
)paren
(brace
id|__u16
id|freed
op_assign
l_int|0
suffix:semicolon
id|__u32
id|tsn
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|sctp_ulpevent
op_star
id|event
suffix:semicolon
r_struct
id|sctp_tsnmap
op_star
id|tsnmap
suffix:semicolon
id|tsnmap
op_assign
op_amp
id|ulpq-&gt;asoc-&gt;peer.tsn_map
suffix:semicolon
multiline_comment|/* Walk backwards through the list, reneges the newest tsns. */
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|__skb_dequeue_tail
c_func
(paren
op_amp
id|ulpq-&gt;reasm
)paren
)paren
)paren
(brace
id|freed
op_add_assign
id|skb_headlen
c_func
(paren
id|skb
)paren
suffix:semicolon
id|event
op_assign
id|sctp_skb2event
c_func
(paren
id|skb
)paren
suffix:semicolon
id|tsn
op_assign
id|event-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
id|sctp_ulpevent_free
c_func
(paren
id|event
)paren
suffix:semicolon
id|sctp_tsnmap_renege
c_func
(paren
id|tsnmap
comma
id|tsn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freed
op_ge
id|needed
)paren
r_return
id|freed
suffix:semicolon
)brace
r_return
id|freed
suffix:semicolon
)brace
multiline_comment|/* Partial deliver the first message as there is pressure on rwnd. */
DECL|function|sctp_ulpq_partial_delivery
r_void
id|sctp_ulpq_partial_delivery
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_chunk
op_star
id|chunk
comma
r_int
id|priority
)paren
(brace
r_struct
id|sctp_ulpevent
op_star
id|event
suffix:semicolon
r_struct
id|sctp_association
op_star
id|asoc
suffix:semicolon
id|asoc
op_assign
id|ulpq-&gt;asoc
suffix:semicolon
multiline_comment|/* Are we already in partial delivery mode?  */
r_if
c_cond
(paren
op_logical_neg
id|sctp_sk
c_func
(paren
id|asoc-&gt;base.sk
)paren
op_member_access_from_pointer
id|pd_mode
)paren
(brace
multiline_comment|/* Is partial delivery possible?  */
id|event
op_assign
id|sctp_ulpq_retrieve_first
c_func
(paren
id|ulpq
)paren
suffix:semicolon
multiline_comment|/* Send event to the ULP.   */
r_if
c_cond
(paren
id|event
)paren
(brace
id|sctp_ulpq_tail_event
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
id|sctp_sk
c_func
(paren
id|asoc-&gt;base.sk
)paren
op_member_access_from_pointer
id|pd_mode
op_assign
l_int|1
suffix:semicolon
id|ulpq-&gt;pd_mode
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Renege some packets to make room for an incoming chunk.  */
DECL|function|sctp_ulpq_renege
r_void
id|sctp_ulpq_renege
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_struct
id|sctp_chunk
op_star
id|chunk
comma
r_int
id|priority
)paren
(brace
r_struct
id|sctp_association
op_star
id|asoc
suffix:semicolon
id|__u16
id|needed
comma
id|freed
suffix:semicolon
id|asoc
op_assign
id|ulpq-&gt;asoc
suffix:semicolon
r_if
c_cond
(paren
id|chunk
)paren
(brace
id|needed
op_assign
id|ntohs
c_func
(paren
id|chunk-&gt;chunk_hdr-&gt;length
)paren
suffix:semicolon
id|needed
op_sub_assign
r_sizeof
(paren
id|sctp_data_chunk_t
)paren
suffix:semicolon
)brace
r_else
id|needed
op_assign
id|SCTP_DEFAULT_MAXWINDOW
suffix:semicolon
id|freed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|skb_queue_empty
c_func
(paren
op_amp
id|asoc-&gt;base.sk-&gt;receive_queue
)paren
)paren
(brace
id|freed
op_assign
id|sctp_ulpq_renege_order
c_func
(paren
id|ulpq
comma
id|needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freed
OL
id|needed
)paren
(brace
id|freed
op_add_assign
id|sctp_ulpq_renege_frags
c_func
(paren
id|ulpq
comma
id|needed
op_minus
id|freed
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* If able to free enough room, accept this chunk. */
r_if
c_cond
(paren
id|chunk
op_logical_and
(paren
id|freed
op_ge
id|needed
)paren
)paren
(brace
id|__u32
id|tsn
suffix:semicolon
id|tsn
op_assign
id|ntohl
c_func
(paren
id|chunk-&gt;subh.data_hdr-&gt;tsn
)paren
suffix:semicolon
id|sctp_tsnmap_mark
c_func
(paren
op_amp
id|asoc-&gt;peer.tsn_map
comma
id|tsn
)paren
suffix:semicolon
id|sctp_ulpq_tail_data
c_func
(paren
id|ulpq
comma
id|chunk
comma
id|priority
)paren
suffix:semicolon
id|sctp_ulpq_partial_delivery
c_func
(paren
id|ulpq
comma
id|chunk
comma
id|priority
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Notify the application if an association is aborted and in&n; * partial delivery mode.  Send up any pending received messages.&n; */
DECL|function|sctp_ulpq_abort_pd
r_void
id|sctp_ulpq_abort_pd
c_func
(paren
r_struct
id|sctp_ulpq
op_star
id|ulpq
comma
r_int
id|priority
)paren
(brace
r_struct
id|sctp_ulpevent
op_star
id|ev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ulpq-&gt;pd_mode
)paren
r_return
suffix:semicolon
id|sk
op_assign
id|ulpq-&gt;asoc-&gt;base.sk
suffix:semicolon
r_if
c_cond
(paren
id|sctp_ulpevent_type_enabled
c_func
(paren
id|SCTP_PARTIAL_DELIVERY_EVENT
comma
op_amp
id|sctp_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|subscribe
)paren
)paren
id|ev
op_assign
id|sctp_ulpevent_make_pdapi
c_func
(paren
id|ulpq-&gt;asoc
comma
id|SCTP_PARTIAL_DELIVERY_ABORTED
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ev
)paren
id|__skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;receive_queue
comma
id|sctp_event2skb
c_func
(paren
id|ev
)paren
)paren
suffix:semicolon
multiline_comment|/* If there is data waiting, send it up the socket now. */
r_if
c_cond
(paren
id|sctp_ulpq_clear_pd
c_func
(paren
id|ulpq
)paren
op_logical_or
id|ev
)paren
id|wake_up_interruptible
c_func
(paren
id|sk-&gt;sleep
)paren
suffix:semicolon
)brace
eof
