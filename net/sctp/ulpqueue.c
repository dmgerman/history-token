multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001-2002 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; * Copyright (c) 2001 Nokia, Inc.&n; * Copyright (c) 2001 La Monte H.P. Yarroll&n; *&n; * This abstraction carries sctp events to the ULP (sockets).&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Sridhar Samudrala     &lt;sri@us.ibm.com&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/sctp/structs.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
multiline_comment|/* Forward declarations for internal helpers.  */
r_static
r_inline
id|sctp_ulpevent_t
op_star
id|sctp_ulpqueue_reasm
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
op_star
id|event
)paren
suffix:semicolon
r_static
r_inline
id|sctp_ulpevent_t
op_star
id|sctp_ulpqueue_order
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
op_star
id|event
)paren
suffix:semicolon
multiline_comment|/* 1st Level Abstractions */
multiline_comment|/* Create a new ULP queue.  */
DECL|function|sctp_ulpqueue_new
id|sctp_ulpqueue_t
op_star
id|sctp_ulpqueue_new
c_func
(paren
id|sctp_association_t
op_star
id|asoc
comma
id|__u16
id|inbound
comma
r_int
id|priority
)paren
(brace
id|sctp_ulpqueue_t
op_star
id|ulpq
suffix:semicolon
r_int
id|size
suffix:semicolon
multiline_comment|/* Today, there is only a fixed size of storage needed for&n;&t; * stream support, but make the interfaces acceptable for&n;&t; * the future.&n;&t; */
id|size
op_assign
r_sizeof
(paren
id|sctp_ulpqueue_t
)paren
op_plus
id|sctp_ulpqueue_storage_size
c_func
(paren
id|inbound
)paren
suffix:semicolon
id|ulpq
op_assign
id|kmalloc
c_func
(paren
id|size
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
id|sctp_ulpqueue_init
c_func
(paren
id|ulpq
comma
id|asoc
comma
id|inbound
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
DECL|function|sctp_ulpqueue_init
id|sctp_ulpqueue_t
op_star
id|sctp_ulpqueue_init
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_association_t
op_star
id|asoc
comma
id|__u16
id|inbound
)paren
(brace
id|memset
c_func
(paren
id|ulpq
comma
r_sizeof
(paren
id|sctp_ulpqueue_t
)paren
op_plus
id|sctp_ulpqueue_storage_size
c_func
(paren
id|inbound
)paren
comma
l_int|0x00
)paren
suffix:semicolon
id|ulpq-&gt;asoc
op_assign
id|asoc
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|ulpq-&gt;lock
)paren
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
id|ulpq-&gt;malloced
op_assign
l_int|0
suffix:semicolon
r_return
id|ulpq
suffix:semicolon
)brace
multiline_comment|/* Flush the reassembly and ordering queues.  */
DECL|function|sctp_ulpqueue_flush
r_void
id|sctp_ulpqueue_flush
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
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
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
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
id|skb_dequeue
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
(paren
id|sctp_ulpevent_t
op_star
)paren
id|skb-&gt;cb
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
DECL|function|sctp_ulpqueue_free
r_void
id|sctp_ulpqueue_free
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
)paren
(brace
id|sctp_ulpqueue_flush
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
DECL|function|sctp_ulpqueue_tail_data
r_int
id|sctp_ulpqueue_tail_data
c_func
(paren
id|sctp_ulpqueue_t
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
id|sctp_ulpevent_t
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
multiline_comment|/* FIXME: Instead of event being the skb clone, we really should&n;&t; * have a new skb based chunk structure that we can convert to&n;&t; * an event.  Temporarily, I&squot;m carrying a few chunk fields in&n;&t; * the event to allow reassembly.  Its too painful to change&n;&t; * everything at once.  --jgrimm&n;&t; */
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
id|sctp_ulpqueue_reasm
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
id|event
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
id|skb_queue_tail
c_func
(paren
op_amp
id|temp
comma
id|event-&gt;parent
)paren
suffix:semicolon
id|event
op_assign
id|sctp_ulpqueue_order
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
id|sctp_ulpqueue_tail_event
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
multiline_comment|/* Add a new event for propogation to the ULP.  */
DECL|function|sctp_ulpqueue_tail_event
r_int
id|sctp_ulpqueue_tail_event
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
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
multiline_comment|/* If we are harvesting multiple skbs they will be&n;&t; * collected on a list.&n;&t; */
r_if
c_cond
(paren
id|event-&gt;parent-&gt;list
)paren
id|sctp_skb_list_tail
c_func
(paren
id|event-&gt;parent-&gt;list
comma
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
r_else
id|skb_queue_tail
c_func
(paren
op_amp
id|sk-&gt;receive_queue
comma
id|event-&gt;parent
)paren
suffix:semicolon
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
id|event-&gt;parent-&gt;list
)paren
id|skb_queue_purge
c_func
(paren
id|event-&gt;parent-&gt;list
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|event-&gt;parent
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* 2nd Level Abstractions */
multiline_comment|/* Helper function to store chunks that need to be reassembled.  */
DECL|function|sctp_ulpqueue_store_reasm
r_static
r_inline
r_void
id|sctp_ulpqueue_store_reasm
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
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
id|sctp_ulpevent_t
op_star
id|cevent
suffix:semicolon
id|__u32
id|tsn
comma
id|ctsn
suffix:semicolon
r_int
r_int
id|flags
id|__attribute
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|tsn
op_assign
id|event-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|ulpq-&gt;reasm.lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Find the right place in this list. We store them by TSN.  */
id|sctp_skb_for_each
c_func
(paren
id|pos
comma
op_amp
id|ulpq-&gt;reasm
comma
id|tmp
)paren
(brace
id|cevent
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|pos-&gt;cb
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
id|event-&gt;parent
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
id|event-&gt;parent
)paren
suffix:semicolon
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|ulpq-&gt;reasm.lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Helper function to return an event corresponding to the reassembled&n; * datagram.&n; */
DECL|function|sctp_make_reassembled_event
r_static
r_inline
id|sctp_ulpevent_t
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
id|sctp_ulpevent_t
op_star
id|event
suffix:semicolon
r_struct
id|sk_buff
op_star
id|pnext
suffix:semicolon
id|pos
op_assign
id|f_frag-&gt;next
suffix:semicolon
multiline_comment|/* Set the first fragment&squot;s frag_list to point to the 2nd fragment.  */
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
r_do
(brace
id|pnext
op_assign
id|pos-&gt;next
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
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|event
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|f_frag-&gt;cb
suffix:semicolon
r_return
id|event
suffix:semicolon
)brace
multiline_comment|/* Helper function to check if an incoming chunk has filled up the last&n; * missing fragment in a SCTP datagram and return the corresponding event.&n; */
DECL|function|sctp_ulpqueue_retrieve_reassembled
r_static
r_inline
id|sctp_ulpevent_t
op_star
id|sctp_ulpqueue_retrieve_reassembled
c_func
(paren
id|sctp_ulpqueue_t
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
id|tmp
suffix:semicolon
id|sctp_ulpevent_t
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
r_int
r_int
id|flags
id|__attribute
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|sctp_ulpevent_t
op_star
id|retval
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initialized to 0 just to avoid compiler warning message. Will&n;&t; * never be used with this value. It is referenced only after it&n;&t; * is set when we find the first fragment of a message.&n;&t; */
id|next_tsn
op_assign
l_int|0
suffix:semicolon
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|ulpq-&gt;reasm.lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* The chunks are held in the reasm queue sorted by TSN.&n;&t; * Walk through the queue sequentially and look for a sequence of&n;&t; * fragmented chunks that complete a datagram.&n;&t; * &squot;first_frag&squot; and next_tsn are reset when we find a chunk which&n;&t; * is the first fragment of a datagram. Once these 2 fields are set&n;&t; * we expect to find the remaining middle fragments and the last&n;&t; * fragment in order. If not, first_frag is reset to NULL and we&n;&t; * start the next pass when we find another first fragment.&n;&t; */
id|sctp_skb_for_each
c_func
(paren
id|pos
comma
op_amp
id|ulpq-&gt;reasm
comma
id|tmp
)paren
(brace
id|cevent
op_assign
(paren
id|sctp_ulpevent_t
op_star
)paren
id|pos-&gt;cb
suffix:semicolon
id|ctsn
op_assign
id|cevent-&gt;sndrcvinfo.sinfo_tsn
suffix:semicolon
r_switch
c_cond
(paren
id|cevent-&gt;chunk_flags
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
r_else
id|first_frag
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* We have the reassembled event. There is no need to look&n;&t;&t; * further.&n;&t;&t; */
r_if
c_cond
(paren
id|retval
)paren
r_break
suffix:semicolon
)brace
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|ulpq-&gt;reasm.lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Helper function to reassemble chunks. Hold chunks on the reasm queue that&n; * need reassembling.&n; */
DECL|function|sctp_ulpqueue_reasm
r_static
r_inline
id|sctp_ulpevent_t
op_star
id|sctp_ulpqueue_reasm
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
op_star
id|event
)paren
(brace
id|sctp_ulpevent_t
op_star
id|retval
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* FIXME: We should be using some new chunk structure here&n;&t; * instead of carrying chunk fields in the event structure.&n;&t; * This is temporary as it is too painful to change everything&n;&t; * at once.&n;&t; */
multiline_comment|/* Check if this is part of a fragmented message.  */
r_if
c_cond
(paren
id|SCTP_DATA_NOT_FRAG
op_eq
(paren
id|event-&gt;chunk_flags
op_amp
id|SCTP_DATA_FRAG_MASK
)paren
)paren
r_return
id|event
suffix:semicolon
id|sctp_ulpqueue_store_reasm
c_func
(paren
id|ulpq
comma
id|event
)paren
suffix:semicolon
id|retval
op_assign
id|sctp_ulpqueue_retrieve_reassembled
c_func
(paren
id|ulpq
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Helper function to gather skbs that have possibly become&n; * ordered by an an incoming chunk.&n; */
DECL|function|sctp_ulpqueue_retrieve_ordered
r_static
r_inline
r_void
id|sctp_ulpqueue_retrieve_ordered
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
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
id|sctp_ulpevent_t
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
r_int
r_int
id|flags
id|__attribute
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|sid
op_assign
id|event-&gt;sndrcvinfo.sinfo_stream
suffix:semicolon
id|ssn
op_assign
id|event-&gt;sndrcvinfo.sinfo_ssn
suffix:semicolon
multiline_comment|/* We are holding the chunks by stream, by SSN.  */
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|ulpq-&gt;lobby.lock
comma
id|flags
)paren
suffix:semicolon
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
id|sctp_ulpevent_t
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
id|ulpq-&gt;ssn
(braket
id|sid
)braket
)paren
r_break
suffix:semicolon
id|ulpq-&gt;ssn
(braket
id|sid
)braket
op_increment
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
id|event-&gt;parent-&gt;list
comma
id|pos
)paren
suffix:semicolon
)brace
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|ulpq-&gt;lobby.lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Helper function to store chunks needing ordering.  */
DECL|function|sctp_ulpqueue_store_ordered
r_static
r_inline
r_void
id|sctp_ulpqueue_store_ordered
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
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
id|sctp_ulpevent_t
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
r_int
r_int
id|flags
id|__attribute
(paren
(paren
id|unused
)paren
)paren
suffix:semicolon
id|sid
op_assign
id|event-&gt;sndrcvinfo.sinfo_stream
suffix:semicolon
id|ssn
op_assign
id|event-&gt;sndrcvinfo.sinfo_ssn
suffix:semicolon
id|sctp_spin_lock_irqsave
c_func
(paren
op_amp
id|ulpq-&gt;lobby.lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Find the right place in this list.  We store them by&n;&t; * stream ID and then by SSN.&n;&t; */
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
id|sctp_ulpevent_t
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
id|event-&gt;parent
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
id|event-&gt;parent
)paren
suffix:semicolon
id|sctp_spin_unlock_irqrestore
c_func
(paren
op_amp
id|ulpq-&gt;lobby.lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sctp_ulpqueue_order
r_static
r_inline
id|sctp_ulpevent_t
op_star
id|sctp_ulpqueue_order
c_func
(paren
id|sctp_ulpqueue_t
op_star
id|ulpq
comma
id|sctp_ulpevent_t
op_star
id|event
)paren
(brace
id|__u16
id|sid
comma
id|ssn
suffix:semicolon
multiline_comment|/* FIXME: We should be using some new chunk structure here&n;&t; * instead of carrying chunk fields in the event structure.&n;&t; * This is temporary as it is too painful to change everything&n;&t; * at once.&n;&t; */
multiline_comment|/* Check if this message needs ordering.  */
r_if
c_cond
(paren
id|SCTP_DATA_UNORDERED
op_amp
id|event-&gt;chunk_flags
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
multiline_comment|/* Is this the expected SSN for this stream ID?  */
r_if
c_cond
(paren
id|ssn
op_ne
id|ulpq-&gt;ssn
(braket
id|sid
)braket
)paren
(brace
multiline_comment|/* We&squot;ve received something out of order, so find where it&n;&t;&t; * needs to be placed.  We order by stream and then by SSN.&n;&t;&t; */
id|sctp_ulpqueue_store_ordered
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
id|ulpq-&gt;ssn
(braket
id|sid
)braket
op_increment
suffix:semicolon
multiline_comment|/* Go find any other chunks that were waiting for&n;&t; * ordering.&n;&t; */
id|sctp_ulpqueue_retrieve_ordered
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
eof
