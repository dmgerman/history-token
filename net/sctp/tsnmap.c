multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001 International Business Machines, Corp.&n; * Copyright (c) 2001 Intel Corp.&n; *&n; * This file is part of the SCTP kernel reference Implementation&n; *&n; * These functions manipulate sctp tsn mapping array.&n; *&n; * The SCTP reference implementation is free software;&n; * you can redistribute it and/or modify it under the terms of&n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * The SCTP reference implementation is distributed in the hope that it&n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.&n; *&n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; *&n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by:&n; *    La Monte H.P. Yarroll &lt;piggy@acm.org&gt;&n; *    Jon Grimm             &lt;jgrimm@us.ibm.com&gt;&n; *    Karl Knutson          &lt;karl@athena.chicago.il.us&gt;&n; *&n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
macro_line|#include &lt;net/sctp/sm.h&gt;
r_static
r_void
id|sctp_tsnmap_update
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
suffix:semicolon
r_static
r_void
id|sctp_tsnmap_update_pending_data
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
suffix:semicolon
r_static
r_void
id|sctp_tsnmap_find_gap_ack
c_func
(paren
id|__u8
op_star
id|map
comma
id|__u16
id|off
comma
id|__u16
id|len
comma
id|__u16
id|base
comma
r_int
op_star
id|started
comma
id|__u16
op_star
id|start
comma
r_int
op_star
id|ended
comma
id|__u16
op_star
id|end
)paren
suffix:semicolon
multiline_comment|/* Create a new sctp_tsnmap.&n; * Allocate room to store at least &squot;len&squot; contiguous TSNs.&n; */
DECL|function|sctp_tsnmap_new
r_struct
id|sctp_tsnmap
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
(brace
r_struct
id|sctp_tsnmap
op_star
id|retval
suffix:semicolon
id|retval
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sctp_tsnmap
)paren
op_plus
id|sctp_tsnmap_storage_size
c_func
(paren
id|len
)paren
comma
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sctp_tsnmap_init
c_func
(paren
id|retval
comma
id|len
comma
id|initial_tsn
)paren
)paren
r_goto
id|fail_map
suffix:semicolon
id|retval-&gt;malloced
op_assign
l_int|1
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|fail_map
suffix:colon
id|kfree
c_func
(paren
id|retval
)paren
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Initialize a block of memory as a tsnmap.  */
DECL|function|sctp_tsnmap_init
r_struct
id|sctp_tsnmap
op_star
id|sctp_tsnmap_init
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
comma
id|__u16
id|len
comma
id|__u32
id|initial_tsn
)paren
(brace
id|map-&gt;tsn_map
op_assign
id|map-&gt;raw_map
suffix:semicolon
id|map-&gt;overflow_map
op_assign
id|map-&gt;tsn_map
op_plus
id|len
suffix:semicolon
id|map-&gt;len
op_assign
id|len
suffix:semicolon
multiline_comment|/* Clear out a TSN ack status.  */
id|memset
c_func
(paren
id|map-&gt;tsn_map
comma
l_int|0x00
comma
id|map-&gt;len
op_plus
id|map-&gt;len
)paren
suffix:semicolon
multiline_comment|/* Keep track of TSNs represented by tsn_map.  */
id|map-&gt;base_tsn
op_assign
id|initial_tsn
suffix:semicolon
id|map-&gt;overflow_tsn
op_assign
id|initial_tsn
op_plus
id|map-&gt;len
suffix:semicolon
id|map-&gt;cumulative_tsn_ack_point
op_assign
id|initial_tsn
op_minus
l_int|1
suffix:semicolon
id|map-&gt;max_tsn_seen
op_assign
id|map-&gt;cumulative_tsn_ack_point
suffix:semicolon
id|map-&gt;malloced
op_assign
l_int|0
suffix:semicolon
id|map-&gt;pending_data
op_assign
l_int|0
suffix:semicolon
id|map-&gt;num_dup_tsns
op_assign
l_int|0
suffix:semicolon
r_return
id|map
suffix:semicolon
)brace
multiline_comment|/* Test the tracking state of this TSN.&n; * Returns:&n; *   0 if the TSN has not yet been seen&n; *  &gt;0 if the TSN has been seen (duplicate)&n; *  &lt;0 if the TSN is invalid (too large to track)&n; */
DECL|function|sctp_tsnmap_check
r_int
id|sctp_tsnmap_check
c_func
(paren
r_const
r_struct
id|sctp_tsnmap
op_star
id|map
comma
id|__u32
id|tsn
)paren
(brace
id|__s32
id|gap
suffix:semicolon
r_int
id|dup
suffix:semicolon
multiline_comment|/* Calculate the index into the mapping arrays.  */
id|gap
op_assign
id|tsn
op_minus
id|map-&gt;base_tsn
suffix:semicolon
multiline_comment|/* Verify that we can hold this TSN.  */
r_if
c_cond
(paren
id|gap
op_ge
(paren
multiline_comment|/* base */
id|map-&gt;len
op_plus
multiline_comment|/* overflow */
id|map-&gt;len
)paren
)paren
(brace
id|dup
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Honk if we&squot;ve already seen this TSN.&n;&t; * We have three cases:&n;&t; *&t;1. The TSN is ancient or belongs to a previous tsn_map.&n;&t; *&t;2. The TSN is already marked in the tsn_map.&n;&t; *&t;3. The TSN is already marked in the tsn_map_overflow.&n;&t; */
r_if
c_cond
(paren
id|gap
OL
l_int|0
op_logical_or
(paren
id|gap
OL
id|map-&gt;len
op_logical_and
id|map-&gt;tsn_map
(braket
id|gap
)braket
)paren
op_logical_or
(paren
id|gap
op_ge
id|map-&gt;len
op_logical_and
id|map-&gt;overflow_map
(braket
id|gap
op_minus
id|map-&gt;len
)braket
)paren
)paren
id|dup
op_assign
l_int|1
suffix:semicolon
r_else
id|dup
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|dup
suffix:semicolon
)brace
multiline_comment|/* Is there a gap in the TSN map?  */
DECL|function|sctp_tsnmap_has_gap
r_int
id|sctp_tsnmap_has_gap
c_func
(paren
r_const
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
(brace
r_int
id|has_gap
suffix:semicolon
id|has_gap
op_assign
(paren
id|map-&gt;cumulative_tsn_ack_point
op_ne
id|map-&gt;max_tsn_seen
)paren
suffix:semicolon
r_return
id|has_gap
suffix:semicolon
)brace
multiline_comment|/* Mark this TSN as seen.  */
DECL|function|sctp_tsnmap_mark
r_void
id|sctp_tsnmap_mark
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
comma
id|__u32
id|tsn
)paren
(brace
id|__s32
id|gap
suffix:semicolon
multiline_comment|/* Vacuously mark any TSN which precedes the map base or&n;&t; * exceeds the end of the map.&n;&t; */
r_if
c_cond
(paren
id|TSN_lt
c_func
(paren
id|tsn
comma
id|map-&gt;base_tsn
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|TSN_lt
c_func
(paren
id|tsn
comma
id|map-&gt;base_tsn
op_plus
id|map-&gt;len
op_plus
id|map-&gt;len
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Bump the max.  */
r_if
c_cond
(paren
id|TSN_lt
c_func
(paren
id|map-&gt;max_tsn_seen
comma
id|tsn
)paren
)paren
id|map-&gt;max_tsn_seen
op_assign
id|tsn
suffix:semicolon
multiline_comment|/* Assert: TSN is in range.  */
id|gap
op_assign
id|tsn
op_minus
id|map-&gt;base_tsn
suffix:semicolon
multiline_comment|/* Mark the TSN as received.  */
r_if
c_cond
(paren
id|gap
OL
id|map-&gt;len
)paren
id|map-&gt;tsn_map
(braket
id|gap
)braket
op_increment
suffix:semicolon
r_else
id|map-&gt;overflow_map
(braket
id|gap
op_minus
id|map-&gt;len
)braket
op_increment
suffix:semicolon
multiline_comment|/* Go fixup any internal TSN mapping variables including&n;&t; * cumulative_tsn_ack_point.&n;&t; */
id|sctp_tsnmap_update
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
DECL|function|sctp_tsnmap_report_dup
r_void
id|sctp_tsnmap_report_dup
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
comma
id|__u32
id|tsn
)paren
(brace
)brace
multiline_comment|/* Retrieve the Cumulative TSN Ack Point. */
DECL|function|sctp_tsnmap_get_ctsn
id|__u32
id|sctp_tsnmap_get_ctsn
c_func
(paren
r_const
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
(brace
r_return
id|map-&gt;cumulative_tsn_ack_point
suffix:semicolon
)brace
multiline_comment|/* Retrieve the highest TSN we&squot;ve seen.  */
DECL|function|sctp_tsnmap_get_max_tsn_seen
id|__u32
id|sctp_tsnmap_get_max_tsn_seen
c_func
(paren
r_const
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
(brace
r_return
id|map-&gt;max_tsn_seen
suffix:semicolon
)brace
multiline_comment|/* Dispose of a tsnmap.  */
DECL|function|sctp_tsnmap_free
r_void
id|sctp_tsnmap_free
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
(brace
r_if
c_cond
(paren
id|map-&gt;malloced
)paren
id|kfree
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize a Gap Ack Block iterator from memory being provided.  */
DECL|function|sctp_tsnmap_iter_init
r_void
id|sctp_tsnmap_iter_init
c_func
(paren
r_const
r_struct
id|sctp_tsnmap
op_star
id|map
comma
r_struct
id|sctp_tsnmap_iter
op_star
id|iter
)paren
(brace
multiline_comment|/* Only start looking one past the Cumulative TSN Ack Point.  */
id|iter-&gt;start
op_assign
id|map-&gt;cumulative_tsn_ack_point
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Get the next Gap Ack Blocks. Returns 0 if there was not another block&n; * to get.&n; */
DECL|function|sctp_tsnmap_next_gap_ack
r_int
id|sctp_tsnmap_next_gap_ack
c_func
(paren
r_const
r_struct
id|sctp_tsnmap
op_star
id|map
comma
r_struct
id|sctp_tsnmap_iter
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
(brace
r_int
id|started
comma
id|ended
suffix:semicolon
id|__u16
id|_start
comma
id|_end
comma
id|offset
suffix:semicolon
multiline_comment|/* We haven&squot;t found a gap yet.  */
id|started
op_assign
id|ended
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Search the first mapping array.  */
r_if
c_cond
(paren
id|iter-&gt;start
op_minus
id|map-&gt;base_tsn
OL
id|map-&gt;len
)paren
(brace
id|offset
op_assign
id|iter-&gt;start
op_minus
id|map-&gt;base_tsn
suffix:semicolon
id|sctp_tsnmap_find_gap_ack
c_func
(paren
id|map-&gt;tsn_map
comma
id|offset
comma
id|map-&gt;len
comma
l_int|0
comma
op_amp
id|started
comma
op_amp
id|_start
comma
op_amp
id|ended
comma
op_amp
id|_end
)paren
suffix:semicolon
)brace
multiline_comment|/* Do we need to check the overflow map? */
r_if
c_cond
(paren
op_logical_neg
id|ended
)paren
(brace
multiline_comment|/* Fix up where we&squot;d like to start searching in the&n;&t;&t; * overflow map.&n;&t;&t; */
r_if
c_cond
(paren
id|iter-&gt;start
op_minus
id|map-&gt;base_tsn
OL
id|map-&gt;len
)paren
id|offset
op_assign
l_int|0
suffix:semicolon
r_else
id|offset
op_assign
id|iter-&gt;start
op_minus
id|map-&gt;base_tsn
op_minus
id|map-&gt;len
suffix:semicolon
multiline_comment|/* Search the overflow map.  */
id|sctp_tsnmap_find_gap_ack
c_func
(paren
id|map-&gt;overflow_map
comma
id|offset
comma
id|map-&gt;len
comma
id|map-&gt;len
comma
op_amp
id|started
comma
op_amp
id|_start
comma
op_amp
id|ended
comma
op_amp
id|_end
)paren
suffix:semicolon
)brace
multiline_comment|/* The Gap Ack Block happens to end at the end of the&n;&t; * overflow map.&n;&t; */
r_if
c_cond
(paren
id|started
op_amp
op_logical_neg
id|ended
)paren
(brace
id|ended
op_increment
suffix:semicolon
id|_end
op_assign
id|map-&gt;len
op_plus
id|map-&gt;len
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* If we found a Gap Ack Block, return the start and end and&n;&t; * bump the iterator forward.&n;&t; */
r_if
c_cond
(paren
id|ended
)paren
(brace
multiline_comment|/* Fix up the start and end based on the&n;&t;&t; * Cumulative TSN Ack offset into the map.&n;&t;&t; */
r_int
id|gap
op_assign
id|map-&gt;cumulative_tsn_ack_point
op_minus
id|map-&gt;base_tsn
suffix:semicolon
op_star
id|start
op_assign
id|_start
op_minus
id|gap
suffix:semicolon
op_star
id|end
op_assign
id|_end
op_minus
id|gap
suffix:semicolon
multiline_comment|/* Move the iterator forward.  */
id|iter-&gt;start
op_assign
id|map-&gt;cumulative_tsn_ack_point
op_plus
op_star
id|end
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|ended
suffix:semicolon
)brace
multiline_comment|/********************************************************************&n; * 2nd Level Abstractions&n; ********************************************************************/
multiline_comment|/* This private helper function updates the tsnmap buffers and&n; * the Cumulative TSN Ack Point.&n; */
DECL|function|sctp_tsnmap_update
r_static
r_void
id|sctp_tsnmap_update
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
(brace
id|__u32
id|ctsn
suffix:semicolon
id|ctsn
op_assign
id|map-&gt;cumulative_tsn_ack_point
suffix:semicolon
r_do
(brace
id|ctsn
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ctsn
op_eq
id|map-&gt;overflow_tsn
)paren
(brace
multiline_comment|/* Now tsn_map must have been all &squot;1&squot;s,&n;&t;&t;&t; * so we swap the map and check the overflow table&n;&t;&t;&t; */
id|__u8
op_star
id|tmp
op_assign
id|map-&gt;tsn_map
suffix:semicolon
id|memset
c_func
(paren
id|tmp
comma
l_int|0
comma
id|map-&gt;len
)paren
suffix:semicolon
id|map-&gt;tsn_map
op_assign
id|map-&gt;overflow_map
suffix:semicolon
id|map-&gt;overflow_map
op_assign
id|tmp
suffix:semicolon
multiline_comment|/* Update the tsn_map boundaries.  */
id|map-&gt;base_tsn
op_add_assign
id|map-&gt;len
suffix:semicolon
id|map-&gt;overflow_tsn
op_add_assign
id|map-&gt;len
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|map-&gt;tsn_map
(braket
id|ctsn
op_minus
id|map-&gt;base_tsn
)braket
)paren
suffix:semicolon
id|map-&gt;cumulative_tsn_ack_point
op_assign
id|ctsn
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Back up one. */
id|sctp_tsnmap_update_pending_data
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
DECL|function|sctp_tsnmap_update_pending_data
r_static
r_void
id|sctp_tsnmap_update_pending_data
c_func
(paren
r_struct
id|sctp_tsnmap
op_star
id|map
)paren
(brace
id|__u32
id|cum_tsn
op_assign
id|map-&gt;cumulative_tsn_ack_point
suffix:semicolon
id|__u32
id|max_tsn
op_assign
id|map-&gt;max_tsn_seen
suffix:semicolon
id|__u32
id|base_tsn
op_assign
id|map-&gt;base_tsn
suffix:semicolon
id|__u16
id|pending_data
suffix:semicolon
id|__s32
id|gap
comma
id|start
comma
id|end
comma
id|i
suffix:semicolon
id|pending_data
op_assign
id|max_tsn
op_minus
id|cum_tsn
suffix:semicolon
id|gap
op_assign
id|max_tsn
op_minus
id|base_tsn
suffix:semicolon
r_if
c_cond
(paren
id|gap
op_le
l_int|0
op_logical_or
id|gap
op_ge
(paren
id|map-&gt;len
op_plus
id|map-&gt;len
)paren
)paren
r_goto
id|out
suffix:semicolon
id|start
op_assign
(paren
(paren
id|cum_tsn
op_ge
id|base_tsn
)paren
ques
c_cond
(paren
id|cum_tsn
op_minus
id|base_tsn
op_plus
l_int|1
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
id|end
op_assign
(paren
(paren
id|gap
OG
id|map-&gt;len
)paren
ques
c_cond
id|map-&gt;len
suffix:colon
id|gap
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|end
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|map-&gt;tsn_map
(braket
id|i
)braket
)paren
id|pending_data
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gap
op_ge
id|map-&gt;len
)paren
(brace
id|start
op_assign
l_int|0
suffix:semicolon
id|end
op_assign
id|gap
op_minus
id|map-&gt;len
op_plus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
OL
id|end
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|map-&gt;overflow_map
(braket
id|i
)braket
)paren
id|pending_data
op_decrement
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|map-&gt;pending_data
op_assign
id|pending_data
suffix:semicolon
)brace
multiline_comment|/* This is a private helper for finding Gap Ack Blocks.  It searches a&n; * single array for the start and end of a Gap Ack Block.&n; *&n; * The flags &quot;started&quot; and &quot;ended&quot; tell is if we found the beginning&n; * or (respectively) the end of a Gap Ack Block.&n; */
DECL|function|sctp_tsnmap_find_gap_ack
r_static
r_void
id|sctp_tsnmap_find_gap_ack
c_func
(paren
id|__u8
op_star
id|map
comma
id|__u16
id|off
comma
id|__u16
id|len
comma
id|__u16
id|base
comma
r_int
op_star
id|started
comma
id|__u16
op_star
id|start
comma
r_int
op_star
id|ended
comma
id|__u16
op_star
id|end
)paren
(brace
r_int
id|i
op_assign
id|off
suffix:semicolon
multiline_comment|/* Look through the entire array, but break out&n;&t; * early if we have found the end of the Gap Ack Block.&n;&t; */
multiline_comment|/* Look for the start. */
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|started
)paren
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|map
(braket
id|i
)braket
)paren
(brace
(paren
op_star
id|started
)paren
op_increment
suffix:semicolon
op_star
id|start
op_assign
id|base
op_plus
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Look for the end.  */
r_if
c_cond
(paren
op_star
id|started
)paren
(brace
multiline_comment|/* We have found the start, let&squot;s find the&n;&t;&t; * end.  If we find the end, break out.&n;&t;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|map
(braket
id|i
)braket
)paren
(brace
(paren
op_star
id|ended
)paren
op_increment
suffix:semicolon
op_star
id|end
op_assign
id|base
op_plus
id|i
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
eof
