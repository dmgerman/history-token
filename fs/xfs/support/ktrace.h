multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_KTRACE_H__
DECL|macro|__XFS_SUPPORT_KTRACE_H__
mdefine_line|#define __XFS_SUPPORT_KTRACE_H__
multiline_comment|/*&n; * Trace buffer entry structure.&n; */
DECL|struct|ktrace_entry
r_typedef
r_struct
id|ktrace_entry
(brace
DECL|member|val
r_void
op_star
id|val
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|ktrace_entry_t
)brace
id|ktrace_entry_t
suffix:semicolon
multiline_comment|/*&n; * Trace buffer header structure.&n; */
DECL|struct|ktrace
r_typedef
r_struct
id|ktrace
(brace
DECL|member|kt_lock
id|lock_t
id|kt_lock
suffix:semicolon
multiline_comment|/* mutex to guard counters */
DECL|member|kt_nentries
r_int
id|kt_nentries
suffix:semicolon
multiline_comment|/* number of entries in trace buf */
DECL|member|kt_index
r_int
id|kt_index
suffix:semicolon
multiline_comment|/* current index in entries */
DECL|member|kt_rollover
r_int
id|kt_rollover
suffix:semicolon
DECL|member|kt_entries
id|ktrace_entry_t
op_star
id|kt_entries
suffix:semicolon
multiline_comment|/* buffer of entries */
DECL|typedef|ktrace_t
)brace
id|ktrace_t
suffix:semicolon
multiline_comment|/*&n; * Trace buffer snapshot structure.&n; */
DECL|struct|ktrace_snap
r_typedef
r_struct
id|ktrace_snap
(brace
DECL|member|ks_start
r_int
id|ks_start
suffix:semicolon
multiline_comment|/* kt_index at time of snap */
DECL|member|ks_index
r_int
id|ks_index
suffix:semicolon
multiline_comment|/* current index */
DECL|typedef|ktrace_snap_t
)brace
id|ktrace_snap_t
suffix:semicolon
multiline_comment|/*&n; * Exported interfaces.&n; */
r_extern
id|ktrace_t
op_star
id|ktrace_alloc
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#if&t;(defined(DEBUG) || defined(CONFIG_XFS_VNODE_TRACING))
r_extern
r_void
id|ktrace_init
c_func
(paren
r_int
id|zentries
)paren
suffix:semicolon
r_extern
r_void
id|ktrace_uninit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ktrace_free
c_func
(paren
id|ktrace_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ktrace_enter
c_func
(paren
id|ktrace_t
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
id|ktrace_entry_t
op_star
id|ktrace_first
c_func
(paren
id|ktrace_t
op_star
comma
id|ktrace_snap_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ktrace_nentries
c_func
(paren
id|ktrace_t
op_star
)paren
suffix:semicolon
r_extern
id|ktrace_entry_t
op_star
id|ktrace_next
c_func
(paren
id|ktrace_t
op_star
comma
id|ktrace_snap_t
op_star
)paren
suffix:semicolon
r_extern
id|ktrace_entry_t
op_star
id|ktrace_skip
c_func
(paren
id|ktrace_t
op_star
comma
r_int
comma
id|ktrace_snap_t
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ktrace_free
mdefine_line|#define&t;ktrace_free(ktp)
DECL|macro|ktrace_enter
mdefine_line|#define&t;ktrace_enter(ktp,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
macro_line|#endif
macro_line|#endif /* __XFS_SUPPORT_KTRACE_H__ */
eof
