multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_LRW_H__
DECL|macro|__XFS_LRW_H__
mdefine_line|#define __XFS_LRW_H__
r_struct
id|vnode
suffix:semicolon
r_struct
id|bhv_desc
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_iocore
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_bmbt_irec
suffix:semicolon
r_struct
id|page_buf_s
suffix:semicolon
r_struct
id|page_buf_bmap_s
suffix:semicolon
macro_line|#if defined(XFS_RW_TRACE)
multiline_comment|/*&n; * Defines for the trace mechanisms in xfs_lrw.c.&n; */
DECL|macro|XFS_RW_KTRACE_SIZE
mdefine_line|#define&t;XFS_RW_KTRACE_SIZE&t;64
DECL|macro|XFS_STRAT_KTRACE_SIZE
mdefine_line|#define&t;XFS_STRAT_KTRACE_SIZE&t;64
DECL|macro|XFS_STRAT_GTRACE_SIZE
mdefine_line|#define&t;XFS_STRAT_GTRACE_SIZE&t;512
DECL|macro|XFS_READ_ENTER
mdefine_line|#define&t;XFS_READ_ENTER&t;&t;1
DECL|macro|XFS_WRITE_ENTER
mdefine_line|#define&t;XFS_WRITE_ENTER&t;&t;2
DECL|macro|XFS_IOMAP_READ_ENTER
mdefine_line|#define XFS_IOMAP_READ_ENTER&t;3
DECL|macro|XFS_IOMAP_WRITE_ENTER
mdefine_line|#define&t;XFS_IOMAP_WRITE_ENTER&t;4
DECL|macro|XFS_IOMAP_READ_MAP
mdefine_line|#define&t;XFS_IOMAP_READ_MAP&t;5
DECL|macro|XFS_IOMAP_WRITE_MAP
mdefine_line|#define&t;XFS_IOMAP_WRITE_MAP&t;6
DECL|macro|XFS_IOMAP_WRITE_NOSPACE
mdefine_line|#define&t;XFS_IOMAP_WRITE_NOSPACE&t;7
DECL|macro|XFS_ITRUNC_START
mdefine_line|#define&t;XFS_ITRUNC_START&t;8
DECL|macro|XFS_ITRUNC_FINISH1
mdefine_line|#define&t;XFS_ITRUNC_FINISH1&t;9
DECL|macro|XFS_ITRUNC_FINISH2
mdefine_line|#define&t;XFS_ITRUNC_FINISH2&t;10
DECL|macro|XFS_CTRUNC1
mdefine_line|#define&t;XFS_CTRUNC1&t;&t;11
DECL|macro|XFS_CTRUNC2
mdefine_line|#define&t;XFS_CTRUNC2&t;&t;12
DECL|macro|XFS_CTRUNC3
mdefine_line|#define&t;XFS_CTRUNC3&t;&t;13
DECL|macro|XFS_CTRUNC4
mdefine_line|#define&t;XFS_CTRUNC4&t;&t;14
DECL|macro|XFS_CTRUNC5
mdefine_line|#define&t;XFS_CTRUNC5&t;&t;15
DECL|macro|XFS_CTRUNC6
mdefine_line|#define&t;XFS_CTRUNC6&t;&t;16
DECL|macro|XFS_BUNMAPI
mdefine_line|#define&t;XFS_BUNMAPI&t;&t;17
DECL|macro|XFS_INVAL_CACHED
mdefine_line|#define&t;XFS_INVAL_CACHED&t;18
DECL|macro|XFS_DIORD_ENTER
mdefine_line|#define&t;XFS_DIORD_ENTER&t;&t;19
DECL|macro|XFS_DIOWR_ENTER
mdefine_line|#define&t;XFS_DIOWR_ENTER&t;&t;20
r_extern
r_void
id|xfs_rw_enter_trace
c_func
(paren
r_int
comma
r_struct
id|xfs_iocore
op_star
comma
r_const
r_struct
id|iovec
op_star
comma
r_int
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xfs_inval_cached_trace
c_func
(paren
r_struct
id|xfs_iocore
op_star
comma
id|xfs_off_t
comma
id|xfs_off_t
comma
id|xfs_off_t
comma
id|xfs_off_t
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_rw_enter_trace
mdefine_line|#define xfs_rw_enter_trace(tag, io, iovec, segs, offset, ioflags)
DECL|macro|xfs_inval_cached_trace
mdefine_line|#define xfs_inval_cached_trace(io, offset, len, first, last)
macro_line|#endif
multiline_comment|/*&n; * Maximum count of bmaps used by read and write paths.&n; */
DECL|macro|XFS_MAX_RW_NBMAPS
mdefine_line|#define&t;XFS_MAX_RW_NBMAPS&t;4
r_extern
r_int
id|xfs_bmap
c_func
(paren
r_struct
id|bhv_desc
op_star
comma
id|xfs_off_t
comma
id|ssize_t
comma
r_int
comma
r_struct
id|page_buf_bmap_s
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfsbdstrat
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|page_buf_s
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_bdstrat_cb
c_func
(paren
r_struct
id|page_buf_s
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_zero_eof
c_func
(paren
r_struct
id|vnode
op_star
comma
r_struct
id|xfs_iocore
op_star
comma
id|xfs_off_t
comma
id|xfs_fsize_t
comma
id|xfs_fsize_t
)paren
suffix:semicolon
r_extern
r_void
id|xfs_inval_cached_pages
c_func
(paren
r_struct
id|vnode
op_star
comma
r_struct
id|xfs_iocore
op_star
comma
id|xfs_off_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
id|ssize_t
id|xfs_read
c_func
(paren
r_struct
id|bhv_desc
op_star
comma
r_struct
id|kiocb
op_star
comma
r_const
r_struct
id|iovec
op_star
comma
r_int
r_int
comma
id|loff_t
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_extern
id|ssize_t
id|xfs_write
c_func
(paren
r_struct
id|bhv_desc
op_star
comma
r_struct
id|kiocb
op_star
comma
r_const
r_struct
id|iovec
op_star
comma
r_int
r_int
comma
id|loff_t
op_star
comma
r_int
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_extern
id|ssize_t
id|xfs_sendfile
c_func
(paren
r_struct
id|bhv_desc
op_star
comma
r_struct
id|file
op_star
comma
id|loff_t
op_star
comma
r_int
comma
r_int
comma
id|read_actor_t
comma
r_void
op_star
comma
r_struct
id|cred
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_iomap
c_func
(paren
r_struct
id|xfs_iocore
op_star
comma
id|xfs_off_t
comma
id|ssize_t
comma
r_int
comma
r_struct
id|page_buf_bmap_s
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_iomap_write_direct
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
id|loff_t
comma
r_int
comma
r_int
comma
r_struct
id|xfs_bmbt_irec
op_star
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_iomap_write_delay
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
id|loff_t
comma
r_int
comma
r_int
comma
r_struct
id|xfs_bmbt_irec
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_iomap_write_allocate
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
r_struct
id|xfs_bmbt_irec
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_iomap_write_unwritten
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dev_is_read_only
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|macro|XFS_FSB_TO_DB_IO
mdefine_line|#define XFS_FSB_TO_DB_IO(io,fsb) &bslash;&n;&t;&t;(((io)-&gt;io_flags &amp; XFS_IOCORE_RT) ? &bslash;&n;&t;&t; XFS_FSB_TO_BB((io)-&gt;io_mount, (fsb)) : &bslash;&n;&t;&t; XFS_FSB_TO_DADDR((io)-&gt;io_mount, (fsb)))
macro_line|#endif&t;/* __XFS_LRW_H__ */
eof
