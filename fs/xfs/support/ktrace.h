multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_KTRACE_H__
DECL|macro|__XFS_SUPPORT_KTRACE_H__
mdefine_line|#define __XFS_SUPPORT_KTRACE_H__
macro_line|#include &lt;support/spin.h&gt;
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
macro_line|#ifdef CONFIG_XFS_TRACE
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
DECL|macro|ktrace_init
mdefine_line|#define ktrace_init(x)&t;do { } while (0)
DECL|macro|ktrace_uninit
mdefine_line|#define ktrace_uninit()&t;do { } while (0)
macro_line|#endif&t;/* CONFIG_XFS_TRACE */
macro_line|#endif&t;/* __XFS_SUPPORT_KTRACE_H__ */
eof
