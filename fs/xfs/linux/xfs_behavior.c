multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; *&n; */
macro_line|#include &lt;xfs.h&gt;
multiline_comment|/*&n; * Source file used to associate/disassociate behaviors with virtualized&n; * objects.  See xfs_behavior.h for more information about behaviors, etc.&n; *&n; * The implementation is split between functions in this file and macros&n; * in xfs_behavior.h.&n; */
multiline_comment|/*&n; * Insert a new behavior descriptor into a behavior chain.&n; *&n; * The behavior chain is ordered based on the &squot;position&squot; number which&n; * lives in the first field of the ops vector (higher numbers first).&n; *&n; * Attemps to insert duplicate ops result in an EINVAL return code.&n; * Otherwise, return 0 to indicate success.&n; */
r_int
DECL|function|bhv_insert
id|bhv_insert
c_func
(paren
id|bhv_head_t
op_star
id|bhp
comma
id|bhv_desc_t
op_star
id|bdp
)paren
(brace
id|bhv_desc_t
op_star
id|curdesc
comma
op_star
id|prev
suffix:semicolon
r_int
id|position
suffix:semicolon
multiline_comment|/*&n;&t; * Validate the position value of the new behavior.&n;&t; */
id|position
op_assign
id|BHV_POSITION
c_func
(paren
id|bdp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|position
op_ge
id|BHV_POSITION_BASE
op_logical_and
id|position
op_le
id|BHV_POSITION_TOP
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find location to insert behavior.  Check for duplicates.&n;&t; */
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|curdesc
op_assign
id|bhp-&gt;bh_first
suffix:semicolon
id|curdesc
op_ne
l_int|NULL
suffix:semicolon
id|curdesc
op_assign
id|curdesc-&gt;bd_next
)paren
(brace
multiline_comment|/* Check for duplication. */
r_if
c_cond
(paren
id|curdesc-&gt;bd_ops
op_eq
id|bdp-&gt;bd_ops
)paren
(brace
id|ASSERT
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Find correct position */
r_if
c_cond
(paren
id|position
op_ge
id|BHV_POSITION
c_func
(paren
id|curdesc
)paren
)paren
(brace
id|ASSERT
c_func
(paren
id|position
op_ne
id|BHV_POSITION
c_func
(paren
id|curdesc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* found it */
)brace
id|prev
op_assign
id|curdesc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* insert at front of chain */
id|bdp-&gt;bd_next
op_assign
id|bhp-&gt;bh_first
suffix:semicolon
id|bhp-&gt;bh_first
op_assign
id|bdp
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* insert after prev */
id|bdp-&gt;bd_next
op_assign
id|prev-&gt;bd_next
suffix:semicolon
id|prev-&gt;bd_next
op_assign
id|bdp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a behavior descriptor from a position in a behavior chain;&n; * the postition is guaranteed not to be the first position.&n; * Should only be called by the bhv_remove() macro.&n; */
r_void
DECL|function|bhv_remove_not_first
id|bhv_remove_not_first
c_func
(paren
id|bhv_head_t
op_star
id|bhp
comma
id|bhv_desc_t
op_star
id|bdp
)paren
(brace
id|bhv_desc_t
op_star
id|curdesc
comma
op_star
id|prev
suffix:semicolon
id|ASSERT
c_func
(paren
id|bhp-&gt;bh_first
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|bhp-&gt;bh_first-&gt;bd_next
op_ne
l_int|NULL
)paren
suffix:semicolon
id|prev
op_assign
id|bhp-&gt;bh_first
suffix:semicolon
r_for
c_loop
(paren
id|curdesc
op_assign
id|bhp-&gt;bh_first-&gt;bd_next
suffix:semicolon
id|curdesc
op_ne
l_int|NULL
suffix:semicolon
id|curdesc
op_assign
id|curdesc-&gt;bd_next
)paren
(brace
r_if
c_cond
(paren
id|curdesc
op_eq
id|bdp
)paren
r_break
suffix:semicolon
multiline_comment|/* found it */
id|prev
op_assign
id|curdesc
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|curdesc
op_eq
id|bdp
)paren
suffix:semicolon
id|prev-&gt;bd_next
op_assign
id|bdp-&gt;bd_next
suffix:semicolon
multiline_comment|/* remove from after prev */
)brace
multiline_comment|/*&n; * Look for a specific ops vector on the specified behavior chain.&n; * Return the associated behavior descriptor.  Or NULL, if not found.&n; */
id|bhv_desc_t
op_star
DECL|function|bhv_lookup
id|bhv_lookup
c_func
(paren
id|bhv_head_t
op_star
id|bhp
comma
r_void
op_star
id|ops
)paren
(brace
id|bhv_desc_t
op_star
id|curdesc
suffix:semicolon
r_for
c_loop
(paren
id|curdesc
op_assign
id|bhp-&gt;bh_first
suffix:semicolon
id|curdesc
op_ne
l_int|NULL
suffix:semicolon
id|curdesc
op_assign
id|curdesc-&gt;bd_next
)paren
(brace
r_if
c_cond
(paren
id|curdesc-&gt;bd_ops
op_eq
id|ops
)paren
r_return
id|curdesc
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Looks for the first behavior within a specified range of positions.&n; * Return the associated behavior descriptor.  Or NULL, if none found.&n; */
id|bhv_desc_t
op_star
DECL|function|bhv_lookup_range
id|bhv_lookup_range
c_func
(paren
id|bhv_head_t
op_star
id|bhp
comma
r_int
id|low
comma
r_int
id|high
)paren
(brace
id|bhv_desc_t
op_star
id|curdesc
suffix:semicolon
r_for
c_loop
(paren
id|curdesc
op_assign
id|bhp-&gt;bh_first
suffix:semicolon
id|curdesc
op_ne
l_int|NULL
suffix:semicolon
id|curdesc
op_assign
id|curdesc-&gt;bd_next
)paren
(brace
r_int
id|position
op_assign
id|BHV_POSITION
c_func
(paren
id|curdesc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|position
op_le
id|high
)paren
(brace
r_if
c_cond
(paren
id|position
op_ge
id|low
)paren
r_return
id|curdesc
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the base behavior in the chain, or NULL if the chain&n; * is empty.&n; *&n; * The caller has not read locked the behavior chain, so acquire the&n; * lock before traversing the chain.&n; */
id|bhv_desc_t
op_star
DECL|function|bhv_base
id|bhv_base
c_func
(paren
id|bhv_head_t
op_star
id|bhp
)paren
(brace
id|bhv_desc_t
op_star
id|curdesc
suffix:semicolon
r_for
c_loop
(paren
id|curdesc
op_assign
id|bhp-&gt;bh_first
suffix:semicolon
id|curdesc
op_ne
l_int|NULL
suffix:semicolon
id|curdesc
op_assign
id|curdesc-&gt;bd_next
)paren
(brace
r_if
c_cond
(paren
id|curdesc-&gt;bd_next
op_eq
l_int|NULL
)paren
(brace
r_return
id|curdesc
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|bhv_head_init
id|bhv_head_init
c_func
(paren
id|bhv_head_t
op_star
id|bhp
comma
r_char
op_star
id|name
)paren
(brace
id|bhp-&gt;bh_first
op_assign
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|bhv_insert_initial
id|bhv_insert_initial
c_func
(paren
id|bhv_head_t
op_star
id|bhp
comma
id|bhv_desc_t
op_star
id|bdp
)paren
(brace
id|ASSERT
c_func
(paren
id|bhp-&gt;bh_first
op_eq
l_int|NULL
)paren
suffix:semicolon
(paren
id|bhp
)paren
op_member_access_from_pointer
id|bh_first
op_assign
id|bdp
suffix:semicolon
)brace
r_void
DECL|function|bhv_head_destroy
id|bhv_head_destroy
c_func
(paren
id|bhv_head_t
op_star
id|bhp
)paren
(brace
id|ASSERT
c_func
(paren
id|bhp-&gt;bh_first
op_eq
l_int|NULL
)paren
suffix:semicolon
)brace
eof
