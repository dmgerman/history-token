multiline_comment|/*&n; * Copyright (c) 2000, 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_BEHAVIOR_H__
DECL|macro|__XFS_BEHAVIOR_H__
mdefine_line|#define __XFS_BEHAVIOR_H__
multiline_comment|/*&n; * Header file used to associate behaviors with virtualized objects.&n; *&n; * A virtualized object is an internal, virtualized representation of&n; * OS entities such as persistent files, processes, or sockets.&t; Examples&n; * of virtualized objects include vnodes, vprocs, and vsockets.&t; Often&n; * a virtualized object is referred to simply as an &quot;object.&quot;&n; *&n; * A behavior is essentially an implementation layer associated with&n; * an object.  Multiple behaviors for an object are chained together,&n; * the order of chaining determining the order of invocation.  Each&n; * behavior of a given object implements the same set of interfaces&n; * (e.g., the VOP interfaces).&n; *&n; * Behaviors may be dynamically inserted into an object&squot;s behavior chain,&n; * such that the addition is transparent to consumers that already have&n; * references to the object.  Typically, a given behavior will be inserted&n; * at a particular location in the behavior chain.  Insertion of new&n; * behaviors is synchronized with operations-in-progress (oip&squot;s) so that&n; * the oip&squot;s always see a consistent view of the chain.&n; *&n; * The term &quot;interpostion&quot; is used to refer to the act of inserting&n; * a behavior such that it interposes on (i.e., is inserted in front&n; * of) a particular other behavior.  A key example of this is when a&n; * system implementing distributed single system image wishes to&n; * interpose a distribution layer (providing distributed coherency)&n; * in front of an object that is otherwise only accessed locally.&n; *&n; * Note that the traditional vnode/inode combination is simply a virtualized&n; * object that has exactly one associated behavior.&n; *&n; * Behavior synchronization is logic which is necessary under certain&n; * circumstances that there is no conflict between ongoing operations&n; * traversing the behavior chain and those dunamically modifying the&n; * behavior chain.  Because behavior synchronization adds extra overhead&n; * to virtual operation invocation, we want to restrict, as much as&n; * we can, the requirement for this extra code, to those situations&n; * in which it is truly necessary.&n; *&n; * Behavior synchronization is needed whenever there&squot;s at least one class&n; * of object in the system for which:&n; * 1) multiple behaviors for a given object are supported,&n; * -- AND --&n; * 2a) insertion of a new behavior can happen dynamically at any time during&n; *     the life of an active object,&n; *&t;-- AND --&n; *&t;3a) insertion of a new behavior needs to synchronize with existing&n; *&t;    ops-in-progress.&n; *&t;-- OR --&n; *&t;3b) multiple different behaviors can be dynamically inserted at&n; *&t;    any time during the life of an active object&n; *&t;-- OR --&n; *&t;3c) removal of a behavior can occur at any time during the life of&n; *&t;    an active object.&n; * -- OR --&n; * 2b) removal of a behavior can occur at any time during the life of an&n; *     active object&n; *&n; */
DECL|typedef|bhv_head_lock_t
r_typedef
r_void
id|bhv_head_lock_t
suffix:semicolon
multiline_comment|/*&n; * Behavior head.  Head of the chain of behaviors.&n; * Contained within each virtualized object data structure.&n; */
DECL|struct|bhv_head
r_typedef
r_struct
id|bhv_head
(brace
DECL|member|bh_first
r_struct
id|bhv_desc
op_star
id|bh_first
suffix:semicolon
multiline_comment|/* first behavior in chain */
DECL|member|bh_lockp
id|bhv_head_lock_t
op_star
id|bh_lockp
suffix:semicolon
multiline_comment|/* pointer to lock info struct */
DECL|typedef|bhv_head_t
)brace
id|bhv_head_t
suffix:semicolon
multiline_comment|/*&n; * Behavior descriptor.&t; Descriptor associated with each behavior.&n; * Contained within the behavior&squot;s private data structure.&n; */
DECL|struct|bhv_desc
r_typedef
r_struct
id|bhv_desc
(brace
DECL|member|bd_pdata
r_void
op_star
id|bd_pdata
suffix:semicolon
multiline_comment|/* private data for this behavior */
DECL|member|bd_vobj
r_void
op_star
id|bd_vobj
suffix:semicolon
multiline_comment|/* virtual object associated with */
DECL|member|bd_ops
r_void
op_star
id|bd_ops
suffix:semicolon
multiline_comment|/* ops for this behavior */
DECL|member|bd_next
r_struct
id|bhv_desc
op_star
id|bd_next
suffix:semicolon
multiline_comment|/* next behavior in chain */
DECL|typedef|bhv_desc_t
)brace
id|bhv_desc_t
suffix:semicolon
multiline_comment|/*&n; * Behavior identity field.  A behavior&squot;s identity determines the position&n; * where it lives within a behavior chain, and it&squot;s always the first field&n; * of the behavior&squot;s ops vector. The optional id field further identifies the&n; * subsystem responsible for the behavior.&n; */
DECL|struct|bhv_identity
r_typedef
r_struct
id|bhv_identity
(brace
DECL|member|bi_id
id|__u16
id|bi_id
suffix:semicolon
multiline_comment|/* owning subsystem id */
DECL|member|bi_position
id|__u16
id|bi_position
suffix:semicolon
multiline_comment|/* position in chain */
DECL|typedef|bhv_identity_t
)brace
id|bhv_identity_t
suffix:semicolon
DECL|typedef|bhv_position_t
r_typedef
id|bhv_identity_t
id|bhv_position_t
suffix:semicolon
DECL|macro|BHV_IDENTITY_INIT
mdefine_line|#define BHV_IDENTITY_INIT(id,pos)&t;{id, pos}
DECL|macro|BHV_IDENTITY_INIT_POSITION
mdefine_line|#define BHV_IDENTITY_INIT_POSITION(pos) BHV_IDENTITY_INIT(0, pos)
multiline_comment|/*&n; * Define boundaries of position values.&n; */
DECL|macro|BHV_POSITION_INVALID
mdefine_line|#define BHV_POSITION_INVALID&t;0&t;/* invalid position number */
DECL|macro|BHV_POSITION_BASE
mdefine_line|#define BHV_POSITION_BASE&t;1&t;/* base (last) implementation layer */
DECL|macro|BHV_POSITION_TOP
mdefine_line|#define BHV_POSITION_TOP&t;63&t;/* top (first) implementation layer */
multiline_comment|/*&n; * Plumbing macros.&n; */
DECL|macro|BHV_HEAD_FIRST
mdefine_line|#define BHV_HEAD_FIRST(bhp)&t;(ASSERT((bhp)-&gt;bh_first), (bhp)-&gt;bh_first)
DECL|macro|BHV_NEXT
mdefine_line|#define BHV_NEXT(bdp)&t;&t;(ASSERT((bdp)-&gt;bd_next), (bdp)-&gt;bd_next)
DECL|macro|BHV_NEXTNULL
mdefine_line|#define BHV_NEXTNULL(bdp)&t;((bdp)-&gt;bd_next)
DECL|macro|BHV_VOBJ
mdefine_line|#define BHV_VOBJ(bdp)&t;&t;(ASSERT((bdp)-&gt;bd_vobj), (bdp)-&gt;bd_vobj)
DECL|macro|BHV_VOBJNULL
mdefine_line|#define BHV_VOBJNULL(bdp)&t;((bdp)-&gt;bd_vobj)
DECL|macro|BHV_PDATA
mdefine_line|#define BHV_PDATA(bdp)&t;&t;(bdp)-&gt;bd_pdata
DECL|macro|BHV_OPS
mdefine_line|#define BHV_OPS(bdp)&t;&t;(bdp)-&gt;bd_ops
DECL|macro|BHV_IDENTITY
mdefine_line|#define BHV_IDENTITY(bdp)&t;((bhv_identity_t *)(bdp)-&gt;bd_ops)
DECL|macro|BHV_POSITION
mdefine_line|#define BHV_POSITION(bdp)&t;(BHV_IDENTITY(bdp)-&gt;bi_position)
r_extern
r_void
id|bhv_head_init
c_func
(paren
id|bhv_head_t
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bhv_head_destroy
c_func
(paren
id|bhv_head_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bhv_head_reinit
c_func
(paren
id|bhv_head_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bhv_insert_initial
c_func
(paren
id|bhv_head_t
op_star
comma
id|bhv_desc_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize a new behavior descriptor.&n; * Arguments:&n; *   bdp - pointer to behavior descriptor&n; *   pdata - pointer to behavior&squot;s private data&n; *   vobj - pointer to associated virtual object&n; *   ops - pointer to ops for this behavior&n; */
DECL|macro|bhv_desc_init
mdefine_line|#define bhv_desc_init(bdp, pdata, vobj, ops)&t;&t;&bslash;&n; {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(bdp)-&gt;bd_pdata = pdata;&t;&t;&t;&bslash;&n;&t;(bdp)-&gt;bd_vobj = vobj;&t;&t;&t;&t;&bslash;&n;&t;(bdp)-&gt;bd_ops = ops;&t;&t;&t;&t;&bslash;&n;&t;(bdp)-&gt;bd_next = NULL;&t;&t;&t;&t;&bslash;&n; }
multiline_comment|/*&n; * Remove a behavior descriptor from a behavior chain.&n; */
DECL|macro|bhv_remove
mdefine_line|#define bhv_remove(bhp, bdp)&t;&t;&t;&t;&bslash;&n; {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((bhp)-&gt;bh_first == (bdp)) {&t;&t;&t;&bslash;&n;&t;&t;/*&t;&t;&t;&t;&t;&bslash;&n;&t;&t;* Remove from front of chain.&t;&t;&bslash;&n;&t;&t; * Atomic wrt oip&squot;s.&t;&t;&t;&bslash;&n;&t;&t;*/&t;&t;&t;&t;&t;&bslash;&n;&t;       (bhp)-&gt;bh_first = (bdp)-&gt;bd_next;&t;&bslash;&n;&t; } else {&t;&t;&t;&t;&t;&bslash;&n;&t;       /* remove from non-front of chain */&t;&bslash;&n;&t;       bhv_remove_not_first(bhp, bdp);&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(bdp)-&gt;bd_vobj = NULL;&t;&t;&t;&t;&bslash;&n; }
multiline_comment|/*&n; * Behavior module prototypes.&n; */
r_extern
r_void
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
suffix:semicolon
r_extern
id|bhv_desc_t
op_star
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
suffix:semicolon
r_extern
id|bhv_desc_t
op_star
id|bhv_lookup_unlocked
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
suffix:semicolon
r_extern
id|bhv_desc_t
op_star
id|bhv_base_unlocked
c_func
(paren
id|bhv_head_t
op_star
id|bhp
)paren
suffix:semicolon
macro_line|#endif /* __XFS_BEHAVIOR_H__ */
eof
