multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2002 International Business Machines, Corp.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * These functions are the methods for accessing the SCTP inqueue.&n; *&n; * An SCTP inqueue is a queue into which you push SCTP packets&n; * (which might be bundles or fragments of chunks) and out of which you&n; * pop SCTP whole chunks.&n; * &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/* Initialize an SCTP inqueue.  */
DECL|function|sctp_inq_init
r_void
id|sctp_inq_init
c_func
(paren
r_struct
id|sctp_inq
op_star
id|queue
)paren
(brace
id|skb_queue_head_init
c_func
(paren
op_amp
id|queue-&gt;in
)paren
suffix:semicolon
id|queue-&gt;in_progress
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Create a task for delivering data.  */
id|INIT_WORK
c_func
(paren
op_amp
id|queue-&gt;immediate
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|queue-&gt;malloced
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Create an initialized sctp_inq.  */
DECL|function|sctp_inq_new
r_struct
id|sctp_inq
op_star
id|sctp_inq_new
c_func
(paren
r_void
)paren
(brace
r_struct
id|sctp_inq
op_star
id|retval
suffix:semicolon
id|retval
op_assign
id|t_new
c_func
(paren
r_struct
id|sctp_inq
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|sctp_inq_init
c_func
(paren
id|retval
)paren
suffix:semicolon
id|retval-&gt;malloced
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Release the memory associated with an SCTP inqueue.  */
DECL|function|sctp_inq_free
r_void
id|sctp_inq_free
c_func
(paren
r_struct
id|sctp_inq
op_star
id|queue
)paren
(brace
r_struct
id|sctp_chunk
op_star
id|chunk
suffix:semicolon
multiline_comment|/* Empty the queue.  */
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
id|skb_dequeue
c_func
(paren
op_amp
id|queue-&gt;in
)paren
)paren
op_ne
l_int|NULL
)paren
id|sctp_chunk_free
c_func
(paren
id|chunk
)paren
suffix:semicolon
multiline_comment|/* If there is a packet which is currently being worked on,&n;&t; * free it as well.&n;&t; */
r_if
c_cond
(paren
id|queue-&gt;in_progress
)paren
id|sctp_chunk_free
c_func
(paren
id|queue-&gt;in_progress
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;malloced
)paren
(brace
multiline_comment|/* Dump the master memory segment.  */
id|kfree
c_func
(paren
id|queue
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Put a new packet in an SCTP inqueue.&n; * We assume that packet-&gt;sctp_hdr is set and in host byte order.&n; */
DECL|function|sctp_inq_push
r_void
id|sctp_inq_push
c_func
(paren
r_struct
id|sctp_inq
op_star
id|q
comma
r_struct
id|sctp_chunk
op_star
id|packet
)paren
(brace
multiline_comment|/* Directly call the packet handling routine. */
multiline_comment|/* We are now calling this either from the soft interrupt&n;&t; * or from the backlog processing.&n;&t; * Eventually, we should clean up inqueue to not rely&n;&t; * on the BH related data structures.&n;&t; */
id|skb_queue_tail
c_func
(paren
op_amp
(paren
id|q-&gt;in
)paren
comma
(paren
r_struct
id|sk_buff
op_star
)paren
id|packet
)paren
suffix:semicolon
id|q-&gt;immediate
dot
id|func
c_func
(paren
id|q-&gt;immediate.data
)paren
suffix:semicolon
)brace
multiline_comment|/* Extract a chunk from an SCTP inqueue.&n; *&n; * WARNING:  If you need to put the chunk on another queue, you need to&n; * make a shallow copy (clone) of it.&n; */
DECL|function|sctp_inq_pop
r_struct
id|sctp_chunk
op_star
id|sctp_inq_pop
c_func
(paren
r_struct
id|sctp_inq
op_star
id|queue
)paren
(brace
r_struct
id|sctp_chunk
op_star
id|chunk
suffix:semicolon
id|sctp_chunkhdr_t
op_star
id|ch
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* The assumption is that we are safe to process the chunks&n;&t; * at this time.&n;&t; */
r_if
c_cond
(paren
(paren
id|chunk
op_assign
id|queue-&gt;in_progress
)paren
)paren
(brace
multiline_comment|/* There is a packet that we have been working on.&n;&t;&t; * Any post processing work to do before we move on?&n;&t;&t; */
r_if
c_cond
(paren
id|chunk-&gt;singleton
op_logical_or
id|chunk-&gt;end_of_packet
op_logical_or
id|chunk-&gt;pdiscard
)paren
(brace
id|sctp_chunk_free
c_func
(paren
id|chunk
)paren
suffix:semicolon
id|chunk
op_assign
id|queue-&gt;in_progress
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Nothing to do. Next chunk in the packet, please. */
id|ch
op_assign
(paren
id|sctp_chunkhdr_t
op_star
)paren
id|chunk-&gt;chunk_end
suffix:semicolon
multiline_comment|/* Force chunk-&gt;skb-&gt;data to chunk-&gt;chunk_end.  */
id|skb_pull
c_func
(paren
id|chunk-&gt;skb
comma
id|chunk-&gt;chunk_end
op_minus
id|chunk-&gt;skb-&gt;data
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Do we need to take the next packet out of the queue to process? */
r_if
c_cond
(paren
op_logical_neg
id|chunk
)paren
(brace
multiline_comment|/* Is the queue empty?  */
r_if
c_cond
(paren
id|skb_queue_empty
c_func
(paren
op_amp
id|queue-&gt;in
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|chunk
op_assign
id|queue-&gt;in_progress
op_assign
(paren
r_struct
id|sctp_chunk
op_star
)paren
id|skb_dequeue
c_func
(paren
op_amp
id|queue-&gt;in
)paren
suffix:semicolon
multiline_comment|/* This is the first chunk in the packet.  */
id|chunk-&gt;singleton
op_assign
l_int|1
suffix:semicolon
id|ch
op_assign
(paren
id|sctp_chunkhdr_t
op_star
)paren
id|chunk-&gt;skb-&gt;data
suffix:semicolon
)brace
id|chunk-&gt;chunk_hdr
op_assign
id|ch
suffix:semicolon
id|chunk-&gt;chunk_end
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
id|skb_pull
c_func
(paren
id|chunk-&gt;skb
comma
r_sizeof
(paren
id|sctp_chunkhdr_t
)paren
)paren
suffix:semicolon
id|chunk-&gt;subh.v
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Subheader is no longer valid.  */
r_if
c_cond
(paren
id|chunk-&gt;chunk_end
OL
id|chunk-&gt;skb-&gt;tail
)paren
(brace
multiline_comment|/* This is not a singleton */
id|chunk-&gt;singleton
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We are at the end of the packet, so mark the chunk&n;&t;&t; * in case we need to send a SACK.&n;&t;&t; */
id|chunk-&gt;end_of_packet
op_assign
l_int|1
suffix:semicolon
)brace
id|SCTP_DEBUG_PRINTK
c_func
(paren
l_string|&quot;+++sctp_inq_pop+++ chunk %p[%s],&quot;
l_string|&quot; length %d, skb-&gt;len %d&bslash;n&quot;
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
id|ntohs
c_func
(paren
id|chunk-&gt;chunk_hdr-&gt;length
)paren
comma
id|chunk-&gt;skb-&gt;len
)paren
suffix:semicolon
r_return
id|chunk
suffix:semicolon
)brace
multiline_comment|/* Set a top-half handler.&n; *&n; * Originally, we the top-half handler was scheduled as a BH.  We now&n; * call the handler directly in sctp_inq_push() at a time that&n; * we know we are lock safe.&n; * The intent is that this routine will pull stuff out of the&n; * inqueue and process it.&n; */
DECL|function|sctp_inq_set_th_handler
r_void
id|sctp_inq_set_th_handler
c_func
(paren
r_struct
id|sctp_inq
op_star
id|q
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
)paren
(brace
id|INIT_WORK
c_func
(paren
op_amp
id|q-&gt;immediate
comma
id|callback
comma
id|arg
)paren
suffix:semicolon
)brace
eof
