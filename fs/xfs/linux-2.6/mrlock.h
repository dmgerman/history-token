multiline_comment|/*&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_MRLOCK_H__
DECL|macro|__XFS_SUPPORT_MRLOCK_H__
mdefine_line|#define __XFS_SUPPORT_MRLOCK_H__
macro_line|#include &lt;linux/rwsem.h&gt;
DECL|enumerator|MR_NONE
DECL|enumerator|MR_ACCESS
DECL|enumerator|MR_UPDATE
r_enum
(brace
id|MR_NONE
comma
id|MR_ACCESS
comma
id|MR_UPDATE
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|mr_lock
r_struct
id|rw_semaphore
id|mr_lock
suffix:semicolon
DECL|member|mr_writer
r_int
id|mr_writer
suffix:semicolon
DECL|typedef|mrlock_t
)brace
id|mrlock_t
suffix:semicolon
DECL|macro|mrinit
mdefine_line|#define mrinit(mrp, name)&t;&bslash;&n;&t;( (mrp)-&gt;mr_writer = 0, init_rwsem(&amp;(mrp)-&gt;mr_lock) )
DECL|macro|mrlock_init
mdefine_line|#define mrlock_init(mrp, t,n,s)&t;mrinit(mrp, n)
DECL|macro|mrfree
mdefine_line|#define mrfree(mrp)&t;&t;do { } while (0)
DECL|macro|mraccess
mdefine_line|#define mraccess(mrp)&t;&t;mraccessf(mrp, 0)
DECL|macro|mrupdate
mdefine_line|#define mrupdate(mrp)&t;&t;mrupdatef(mrp, 0)
DECL|function|mraccessf
r_static
r_inline
r_void
id|mraccessf
c_func
(paren
id|mrlock_t
op_star
id|mrp
comma
r_int
id|flags
)paren
(brace
id|down_read
c_func
(paren
op_amp
id|mrp-&gt;mr_lock
)paren
suffix:semicolon
)brace
DECL|function|mrupdatef
r_static
r_inline
r_void
id|mrupdatef
c_func
(paren
id|mrlock_t
op_star
id|mrp
comma
r_int
id|flags
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|mrp-&gt;mr_lock
)paren
suffix:semicolon
id|mrp-&gt;mr_writer
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|mrtryaccess
r_static
r_inline
r_int
id|mrtryaccess
c_func
(paren
id|mrlock_t
op_star
id|mrp
)paren
(brace
r_return
id|down_read_trylock
c_func
(paren
op_amp
id|mrp-&gt;mr_lock
)paren
suffix:semicolon
)brace
DECL|function|mrtryupdate
r_static
r_inline
r_int
id|mrtryupdate
c_func
(paren
id|mrlock_t
op_star
id|mrp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|down_write_trylock
c_func
(paren
op_amp
id|mrp-&gt;mr_lock
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|mrp-&gt;mr_writer
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mrunlock
r_static
r_inline
r_void
id|mrunlock
c_func
(paren
id|mrlock_t
op_star
id|mrp
)paren
(brace
r_if
c_cond
(paren
id|mrp-&gt;mr_writer
)paren
(brace
id|mrp-&gt;mr_writer
op_assign
l_int|0
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|mrp-&gt;mr_lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|up_read
c_func
(paren
op_amp
id|mrp-&gt;mr_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|mrdemote
r_static
r_inline
r_void
id|mrdemote
c_func
(paren
id|mrlock_t
op_star
id|mrp
)paren
(brace
id|mrp-&gt;mr_writer
op_assign
l_int|0
suffix:semicolon
id|downgrade_write
c_func
(paren
op_amp
id|mrp-&gt;mr_lock
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
multiline_comment|/*&n; * Debug-only routine, without some platform-specific asm code, we can&n; * now only answer requests regarding whether we hold the lock for write&n; * (reader state is outside our visibility, we only track writer state).&n; * Note: means !ismrlocked would give false positivies, so don&squot;t do that.&n; */
DECL|function|ismrlocked
r_static
r_inline
r_int
id|ismrlocked
c_func
(paren
id|mrlock_t
op_star
id|mrp
comma
r_int
id|type
)paren
(brace
r_if
c_cond
(paren
id|mrp
op_logical_and
id|type
op_eq
id|MR_UPDATE
)paren
r_return
id|mrp-&gt;mr_writer
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __XFS_SUPPORT_MRLOCK_H__ */
eof
