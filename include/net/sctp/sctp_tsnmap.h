multiline_comment|/* SCTP kernel reference Implementation Copyright (C) 1999-2001&n; * Cisco, Motorola, Intel, and International Business Machines Corp.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * $Header: /cvsroot/lksctp/lksctp/sctp_cvs/include/net/sctp/sctp_tsnmap.h,v 1.8 2002/07/16 14:51:58 jgrimm Exp $&n; * &n; * These are the definitions needed for the tsnmap type.  The tsnmap is used&n; * to track out of order TSNs received.&n; * &n; * The SCTP reference implementation  is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * the SCTP reference implementation  is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to one of the&n; * following email addresses:&n; * &n; * Jon Grimm &lt;jgrimm@us.ibm.com&gt;&n; * La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; * Karl Knutson &lt;karl@athena.chicago.il.us&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;net/sctp/sctp_constants.h&gt;
macro_line|#ifndef __sctp_tsnmap_h__
DECL|macro|__sctp_tsnmap_h__
mdefine_line|#define __sctp_tsnmap_h__
multiline_comment|/* RFC 2960 12.2 Parameters necessary per association (i.e. the TCB)&n; * Mapping  An array of bits or bytes indicating which out of&n; * Array    order TSN&squot;s have been received (relative to the&n; *          Last Rcvd TSN). If no gaps exist, i.e. no out of&n; *          order packets have been received, this array&n; *          will be set to all zero. This structure may be&n; *          in the form of a circular buffer or bit array.&n; */
DECL|struct|sctp_tsnmap
r_typedef
r_struct
id|sctp_tsnmap
(brace
multiline_comment|/* This array counts the number of chunks with each TSN.&n;&t; * It points at one of the two buffers with which we will&n;&t; * ping-pong between.&n;&t; */
DECL|member|tsn_map
id|__u8
op_star
id|tsn_map
suffix:semicolon
multiline_comment|/* This marks the tsn which overflows the tsn_map, when the&n;&t; * cumulative ack point reaches this point we know we can switch&n;&t; * maps (tsn_map and overflow_map swap).&n;&t; */
DECL|member|overflow_tsn
id|__u32
id|overflow_tsn
suffix:semicolon
multiline_comment|/* This is the overflow array for tsn_map.&n;&t; * It points at one of the other ping-pong buffers.&n;&t; */
DECL|member|overflow_map
id|__u8
op_star
id|overflow_map
suffix:semicolon
multiline_comment|/* This is the TSN at tsn_map[0].  */
DECL|member|base_tsn
id|__u32
id|base_tsn
suffix:semicolon
multiline_comment|/* Last Rcvd   : This is the last TSN received in&n;&t; * TSN&t;       : sequence. This value is set initially by&n;&t; *             : taking the peer&squot;s Initial TSN, received in&n;&t; *             : the INIT or INIT ACK chunk, and subtracting&n;&t; *             : one from it.&n;&t; *&n;&t; * Throughout most of the specification this is called the&n;&t; * &quot;Cumulative TSN ACK Point&quot;.  In this case, we&n;&t; * ignore the advice in 12.2 in favour of the term&n;&t; * used in the bulk of the text.&n;&t; */
DECL|member|cumulative_tsn_ack_point
id|__u32
id|cumulative_tsn_ack_point
suffix:semicolon
multiline_comment|/* This is the minimum number of TSNs we can track.  This corresponds&n;&t; * to the size of tsn_map.   Note: the overflow_map allows us to&n;&t; * potentially track more than this quantity.&n;&t; */
DECL|member|len
id|__u16
id|len
suffix:semicolon
multiline_comment|/* This is the highest TSN we&squot;ve marked.  */
DECL|member|max_tsn_seen
id|__u32
id|max_tsn_seen
suffix:semicolon
multiline_comment|/* No. of data chunks pending receipt. used by SCTP_STATUS sockopt */
DECL|member|pending_data
id|__u16
id|pending_data
suffix:semicolon
DECL|member|malloced
r_int
id|malloced
suffix:semicolon
DECL|member|raw_map
id|__u8
id|raw_map
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|sctp_tsnmap_t
)brace
id|sctp_tsnmap_t
suffix:semicolon
DECL|struct|sctp_tsnmap_iter
r_typedef
r_struct
id|sctp_tsnmap_iter
(brace
DECL|member|start
id|__u32
id|start
suffix:semicolon
DECL|typedef|sctp_tsnmap_iter_t
)brace
id|sctp_tsnmap_iter_t
suffix:semicolon
multiline_comment|/* Create a new tsnmap.  */
id|sctp_tsnmap_t
op_star
id|sctp_tsnmap_new
c_func
(paren
id|__u16
id|len
comma
id|__u32
id|initial_tsn
comma
r_int
id|priority
)paren
suffix:semicolon
multiline_comment|/* Dispose of a tsnmap.  */
r_void
id|sctp_tsnmap_free
c_func
(paren
id|sctp_tsnmap_t
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/* This macro assists in creation of external storage for variable length&n; * internal buffers.  We double allocate so the overflow map works.&n; */
DECL|macro|sctp_tsnmap_storage_size
mdefine_line|#define sctp_tsnmap_storage_size(count) (sizeof(__u8) * (count) * 2)
multiline_comment|/* Initialize a block of memory as a tsnmap.  */
id|sctp_tsnmap_t
op_star
id|sctp_tsnmap_init
c_func
(paren
id|sctp_tsnmap_t
op_star
id|map
comma
id|__u16
id|len
comma
id|__u32
id|initial_tsn
)paren
suffix:semicolon
multiline_comment|/* Test the tracking state of this TSN.&n; * Returns:&n; *   0 if the TSN has not yet been seen&n; *  &gt;0 if the TSN has been seen (duplicate)&n; *  &lt;0 if the TSN is invalid (too large to track)&n; */
r_int
id|sctp_tsnmap_check
c_func
(paren
r_const
id|sctp_tsnmap_t
op_star
id|map
comma
id|__u32
id|tsn
)paren
suffix:semicolon
multiline_comment|/* Mark this TSN as seen.  */
r_void
id|sctp_tsnmap_mark
c_func
(paren
id|sctp_tsnmap_t
op_star
id|map
comma
id|__u32
id|tsn
)paren
suffix:semicolon
multiline_comment|/* Retrieve the Cumulative TSN ACK Point.  */
id|__u32
id|sctp_tsnmap_get_ctsn
c_func
(paren
r_const
id|sctp_tsnmap_t
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/* Retrieve the highest TSN we&squot;ve seen.  */
id|__u32
id|sctp_tsnmap_get_max_tsn_seen
c_func
(paren
r_const
id|sctp_tsnmap_t
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/* Is there a gap in the TSN map? */
r_int
id|sctp_tsnmap_has_gap
c_func
(paren
r_const
id|sctp_tsnmap_t
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/* Initialize a gap ack block interator from user-provided memory.  */
r_void
id|sctp_tsnmap_iter_init
c_func
(paren
r_const
id|sctp_tsnmap_t
op_star
id|map
comma
id|sctp_tsnmap_iter_t
op_star
id|iter
)paren
suffix:semicolon
multiline_comment|/* Get the next gap ack blocks.  We return 0 if there are no more&n; * gap ack blocks.&n; */
r_int
id|sctp_tsnmap_next_gap_ack
c_func
(paren
r_const
id|sctp_tsnmap_t
op_star
id|map
comma
id|sctp_tsnmap_iter_t
op_star
id|iter
comma
id|__u16
op_star
id|start
comma
id|__u16
op_star
id|end
)paren
suffix:semicolon
macro_line|#endif /* __sctp_tsnmap_h__ */
eof
