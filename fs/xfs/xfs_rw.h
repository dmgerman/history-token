multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_RW_H__
DECL|macro|__XFS_RW_H__
mdefine_line|#define __XFS_RW_H__
r_struct
id|bhv_desc
suffix:semicolon
r_struct
id|bmapval
suffix:semicolon
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|cred
suffix:semicolon
r_struct
id|uio
suffix:semicolon
r_struct
id|vnode
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_iocore
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
r_struct
id|xfs_dio
suffix:semicolon
r_struct
id|pm
suffix:semicolon
multiline_comment|/*&n; * Maximum count of bmaps used by read and write paths.&n; */
DECL|macro|XFS_MAX_RW_NBMAPS
mdefine_line|#define XFS_MAX_RW_NBMAPS&t;4
multiline_comment|/*&n; * Counts of readahead buffers to use based on physical memory size.&n; * None of these should be more than XFS_MAX_RW_NBMAPS.&n; */
DECL|macro|XFS_RW_NREADAHEAD_16MB
mdefine_line|#define XFS_RW_NREADAHEAD_16MB&t;2
DECL|macro|XFS_RW_NREADAHEAD_32MB
mdefine_line|#define XFS_RW_NREADAHEAD_32MB&t;3
DECL|macro|XFS_RW_NREADAHEAD_K32
mdefine_line|#define XFS_RW_NREADAHEAD_K32&t;4
DECL|macro|XFS_RW_NREADAHEAD_K64
mdefine_line|#define XFS_RW_NREADAHEAD_K64&t;4
multiline_comment|/*&n; * Maximum size of a buffer that we&bslash;&squot;ll map.  Making this&n; * too big will degrade performance due to the number of&n; * pages which need to be gathered.  Making it too small&n; * will prevent us from doing large I/O&bslash;&squot;s to hardware that&n; * needs it.&n; *&n; * This is currently set to 512 KB.&n; */
DECL|macro|XFS_MAX_BMAP_LEN_BB
mdefine_line|#define XFS_MAX_BMAP_LEN_BB&t;1024
DECL|macro|XFS_MAX_BMAP_LEN_BYTES
mdefine_line|#define XFS_MAX_BMAP_LEN_BYTES&t;524288
multiline_comment|/*&n; * Maximum size (in inodes) for the nfs refcache&n; */
DECL|macro|XFS_REFCACHE_SIZE_MAX
mdefine_line|#define XFS_REFCACHE_SIZE_MAX&t;512
multiline_comment|/*&n; * Convert the given file system block to a disk block.&n; * We have to treat it differently based on whether the&n; * file is a real time file or not, because the bmap code&n; * does.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FSB_TO_DB)
id|xfs_daddr_t
id|xfs_fsb_to_db
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
comma
id|xfs_fsblock_t
id|fsb
)paren
suffix:semicolon
DECL|macro|XFS_FSB_TO_DB
mdefine_line|#define XFS_FSB_TO_DB(ip,fsb)&t;xfs_fsb_to_db(ip,fsb)
macro_line|#else
DECL|macro|XFS_FSB_TO_DB
mdefine_line|#define XFS_FSB_TO_DB(ip,fsb) &bslash;&n;&t;&t;(((ip)-&gt;i_d.di_flags &amp; XFS_DIFLAG_REALTIME) ? &bslash;&n;&t;&t; (xfs_daddr_t)XFS_FSB_TO_BB((ip)-&gt;i_mount, (fsb)) : &bslash;&n;&t;&t; XFS_FSB_TO_DADDR((ip)-&gt;i_mount, (fsb)))
macro_line|#endif
DECL|macro|XFS_FSB_TO_DB_IO
mdefine_line|#define XFS_FSB_TO_DB_IO(io,fsb) &bslash;&n;&t;&t;(((io)-&gt;io_flags &amp; XFS_IOCORE_RT) ? &bslash;&n;&t;&t; XFS_FSB_TO_BB((io)-&gt;io_mount, (fsb)) : &bslash;&n;&t;&t; XFS_FSB_TO_DADDR((io)-&gt;io_mount, (fsb)))
multiline_comment|/*&n; * Defines for the trace mechanisms in xfs_rw.c.&n; */
DECL|macro|XFS_RW_KTRACE_SIZE
mdefine_line|#define XFS_RW_KTRACE_SIZE&t;64
DECL|macro|XFS_STRAT_KTRACE_SIZE
mdefine_line|#define XFS_STRAT_KTRACE_SIZE&t;64
DECL|macro|XFS_STRAT_GTRACE_SIZE
mdefine_line|#define XFS_STRAT_GTRACE_SIZE&t;512
DECL|macro|XFS_READ_ENTER
mdefine_line|#define XFS_READ_ENTER&t;&t;1
DECL|macro|XFS_WRITE_ENTER
mdefine_line|#define XFS_WRITE_ENTER&t;&t;2
DECL|macro|XFS_IOMAP_READ_ENTER
mdefine_line|#define XFS_IOMAP_READ_ENTER&t;3
DECL|macro|XFS_IOMAP_WRITE_ENTER
mdefine_line|#define XFS_IOMAP_WRITE_ENTER&t;4
DECL|macro|XFS_IOMAP_READ_MAP
mdefine_line|#define XFS_IOMAP_READ_MAP&t;5
DECL|macro|XFS_IOMAP_WRITE_MAP
mdefine_line|#define XFS_IOMAP_WRITE_MAP&t;6
DECL|macro|XFS_IOMAP_WRITE_NOSPACE
mdefine_line|#define XFS_IOMAP_WRITE_NOSPACE 7
DECL|macro|XFS_ITRUNC_START
mdefine_line|#define XFS_ITRUNC_START&t;8
DECL|macro|XFS_ITRUNC_FINISH1
mdefine_line|#define XFS_ITRUNC_FINISH1&t;9
DECL|macro|XFS_ITRUNC_FINISH2
mdefine_line|#define XFS_ITRUNC_FINISH2&t;10
DECL|macro|XFS_CTRUNC1
mdefine_line|#define XFS_CTRUNC1&t;&t;11
DECL|macro|XFS_CTRUNC2
mdefine_line|#define XFS_CTRUNC2&t;&t;12
DECL|macro|XFS_CTRUNC3
mdefine_line|#define XFS_CTRUNC3&t;&t;13
DECL|macro|XFS_CTRUNC4
mdefine_line|#define XFS_CTRUNC4&t;&t;14
DECL|macro|XFS_CTRUNC5
mdefine_line|#define XFS_CTRUNC5&t;&t;15
DECL|macro|XFS_CTRUNC6
mdefine_line|#define XFS_CTRUNC6&t;&t;16
DECL|macro|XFS_BUNMAPI
mdefine_line|#define XFS_BUNMAPI&t;&t;17
DECL|macro|XFS_INVAL_CACHED
mdefine_line|#define XFS_INVAL_CACHED&t;18
DECL|macro|XFS_DIORD_ENTER
mdefine_line|#define XFS_DIORD_ENTER&t;&t;19
DECL|macro|XFS_DIOWR_ENTER
mdefine_line|#define XFS_DIOWR_ENTER&t;&t;20
macro_line|#if defined(XFS_ALL_TRACE)
DECL|macro|XFS_RW_TRACE
mdefine_line|#define XFS_RW_TRACE
DECL|macro|XFS_STRAT_TRACE
mdefine_line|#define XFS_STRAT_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_RW_TRACE
macro_line|#undef XFS_RW_TRACE
DECL|macro|XFS_STRAT_TRACE
macro_line|#undef XFS_STRAT_TRACE
macro_line|#endif
multiline_comment|/*&n; * Prototypes for functions in xfs_rw.c.&n; */
r_int
id|xfs_write_clear_setuid
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
)paren
suffix:semicolon
r_int
id|xfs_bwrite
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
r_void
id|xfs_inval_cached_pages
c_func
(paren
r_struct
id|vnode
op_star
id|vp
comma
r_struct
id|xfs_iocore
op_star
id|io
comma
id|xfs_off_t
id|offset
comma
r_int
id|write
comma
r_int
id|relock
)paren
suffix:semicolon
r_void
id|xfs_refcache_insert
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
)paren
suffix:semicolon
r_void
id|xfs_refcache_purge_ip
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
)paren
suffix:semicolon
r_void
id|xfs_refcache_purge_mp
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_void
id|xfs_refcache_purge_some
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
r_void
id|xfs_refcache_resize
c_func
(paren
r_int
id|xfs_refcache_new_size
)paren
suffix:semicolon
r_int
id|xfs_bioerror
c_func
(paren
r_struct
id|xfs_buf
op_star
id|b
)paren
suffix:semicolon
multiline_comment|/*&n; * XFS I/O core functions&n; */
r_extern
r_int
id|xfs_bioerror_relse
c_func
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Needed by xfs_rw.c&n; */
r_int
id|xfs_rwlock
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|vrwlock_t
id|write_lock
)paren
suffix:semicolon
r_void
id|xfs_rwunlock
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
id|vrwlock_t
id|write_lock
)paren
suffix:semicolon
r_int
id|xfs_read_buf
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_buftarg_t
op_star
id|target
comma
id|xfs_daddr_t
id|blkno
comma
r_int
id|len
comma
id|uint
id|flags
comma
r_struct
id|xfs_buf
op_star
op_star
id|bpp
)paren
suffix:semicolon
r_void
id|xfs_ioerror_alert
c_func
(paren
r_char
op_star
id|func
comma
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_buf_t
op_star
id|bp
comma
id|xfs_daddr_t
id|blkno
)paren
suffix:semicolon
macro_line|#endif /* __XFS_RW_H__ */
eof
