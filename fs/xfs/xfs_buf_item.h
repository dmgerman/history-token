multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_BUF_ITEM_H__
DECL|macro|__XFS_BUF_ITEM_H__
mdefine_line|#define __XFS_BUF_ITEM_H__
multiline_comment|/*&n; * This is the structure used to lay out a buf log item in the&n; * log.&t; The data map describes which 128 byte chunks of the buffer&n; * have been logged.  This structure works only on buffers that&n; * reside up to the first TB in the filesystem.&t; These buffers are&n; * generated only by pre-6.2 systems and are known as XFS_LI_6_1_BUF.&n; */
DECL|struct|xfs_buf_log_format_v1
r_typedef
r_struct
id|xfs_buf_log_format_v1
(brace
DECL|member|blf_type
r_int
r_int
id|blf_type
suffix:semicolon
multiline_comment|/* buf log item type indicator */
DECL|member|blf_size
r_int
r_int
id|blf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|blf_blkno
id|__int32_t
id|blf_blkno
suffix:semicolon
multiline_comment|/* starting blkno of this buf */
DECL|member|blf_flags
id|ushort
id|blf_flags
suffix:semicolon
multiline_comment|/* misc state */
DECL|member|blf_len
id|ushort
id|blf_len
suffix:semicolon
multiline_comment|/* number of blocks in this buf */
DECL|member|blf_map_size
r_int
r_int
id|blf_map_size
suffix:semicolon
multiline_comment|/* size of data bitmap in words */
DECL|member|blf_data_map
r_int
r_int
id|blf_data_map
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* variable size bitmap of */
multiline_comment|/*   regions of buffer in this item */
DECL|typedef|xfs_buf_log_format_v1_t
)brace
id|xfs_buf_log_format_v1_t
suffix:semicolon
multiline_comment|/*&n; * This is a form of the above structure with a 64 bit blkno field.&n; * For 6.2 and beyond, this is XFS_LI_BUF.  We use this to log everything.&n; */
DECL|struct|xfs_buf_log_format_t
r_typedef
r_struct
id|xfs_buf_log_format_t
(brace
DECL|member|blf_type
r_int
r_int
id|blf_type
suffix:semicolon
multiline_comment|/* buf log item type indicator */
DECL|member|blf_size
r_int
r_int
id|blf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|blf_flags
id|ushort
id|blf_flags
suffix:semicolon
multiline_comment|/* misc state */
DECL|member|blf_len
id|ushort
id|blf_len
suffix:semicolon
multiline_comment|/* number of blocks in this buf */
DECL|member|blf_blkno
id|__int64_t
id|blf_blkno
suffix:semicolon
multiline_comment|/* starting blkno of this buf */
DECL|member|blf_map_size
r_int
r_int
id|blf_map_size
suffix:semicolon
multiline_comment|/* size of data bitmap in words */
DECL|member|blf_data_map
r_int
r_int
id|blf_data_map
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* variable size bitmap of */
multiline_comment|/*   regions of buffer in this item */
DECL|typedef|xfs_buf_log_format_t
)brace
id|xfs_buf_log_format_t
suffix:semicolon
multiline_comment|/*&n; * This flag indicates that the buffer contains on disk inodes&n; * and requires special recovery handling.&n; */
DECL|macro|XFS_BLI_INODE_BUF
mdefine_line|#define XFS_BLI_INODE_BUF&t;0x1
multiline_comment|/*&n; * This flag indicates that the buffer should not be replayed&n; * during recovery because its blocks are being freed.&n; */
DECL|macro|XFS_BLI_CANCEL
mdefine_line|#define XFS_BLI_CANCEL&t;&t;0x2
multiline_comment|/*&n; * This flag indicates that the buffer contains on disk&n; * user or group dquots and may require special recovery handling.&n; */
DECL|macro|XFS_BLI_UDQUOT_BUF
mdefine_line|#define XFS_BLI_UDQUOT_BUF&t;0x4
multiline_comment|/* #define XFS_BLI_PDQUOT_BUF&t;0x8 */
DECL|macro|XFS_BLI_GDQUOT_BUF
mdefine_line|#define XFS_BLI_GDQUOT_BUF&t;0x10
DECL|macro|XFS_BLI_CHUNK
mdefine_line|#define XFS_BLI_CHUNK&t;&t;128
DECL|macro|XFS_BLI_SHIFT
mdefine_line|#define XFS_BLI_SHIFT&t;&t;7
DECL|macro|BIT_TO_WORD_SHIFT
mdefine_line|#define BIT_TO_WORD_SHIFT&t;5
DECL|macro|NBWORD
mdefine_line|#define NBWORD&t;&t;&t;(NBBY * sizeof(unsigned int))
multiline_comment|/*&n; * buf log item flags&n; */
DECL|macro|XFS_BLI_HOLD
mdefine_line|#define XFS_BLI_HOLD&t;&t;0x01
DECL|macro|XFS_BLI_DIRTY
mdefine_line|#define XFS_BLI_DIRTY&t;&t;0x02
DECL|macro|XFS_BLI_STALE
mdefine_line|#define XFS_BLI_STALE&t;&t;0x04
DECL|macro|XFS_BLI_LOGGED
mdefine_line|#define XFS_BLI_LOGGED&t;&t;0x08
DECL|macro|XFS_BLI_INODE_ALLOC_BUF
mdefine_line|#define XFS_BLI_INODE_ALLOC_BUF 0x10
macro_line|#ifdef __KERNEL__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|ktrace
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
multiline_comment|/*&n; * This is the in core log item structure used to track information&n; * needed to log buffers.  It tracks how many times the lock has been&n; * locked, and which 128 byte chunks of the buffer are dirty.&n; */
DECL|struct|xfs_buf_log_item
r_typedef
r_struct
id|xfs_buf_log_item
(brace
DECL|member|bli_item
id|xfs_log_item_t
id|bli_item
suffix:semicolon
multiline_comment|/* common item structure */
DECL|member|bli_buf
r_struct
id|xfs_buf
op_star
id|bli_buf
suffix:semicolon
multiline_comment|/* real buffer pointer */
DECL|member|bli_flags
r_int
r_int
id|bli_flags
suffix:semicolon
multiline_comment|/* misc flags */
DECL|member|bli_recur
r_int
r_int
id|bli_recur
suffix:semicolon
multiline_comment|/* lock recursion count */
DECL|member|bli_refcount
id|atomic_t
id|bli_refcount
suffix:semicolon
multiline_comment|/* cnt of tp refs */
macro_line|#ifdef DEBUG
DECL|member|bli_trace
r_struct
id|ktrace
op_star
id|bli_trace
suffix:semicolon
multiline_comment|/* event trace buf */
macro_line|#endif
macro_line|#ifdef XFS_TRANS_DEBUG
DECL|member|bli_orig
r_char
op_star
id|bli_orig
suffix:semicolon
multiline_comment|/* original buffer copy */
DECL|member|bli_logged
r_char
op_star
id|bli_logged
suffix:semicolon
multiline_comment|/* bytes logged (bitmap) */
macro_line|#endif
DECL|member|bli_format
id|xfs_buf_log_format_t
id|bli_format
suffix:semicolon
multiline_comment|/* in-log header */
DECL|typedef|xfs_buf_log_item_t
)brace
id|xfs_buf_log_item_t
suffix:semicolon
multiline_comment|/*&n; * This structure is used during recovery to record the buf log&n; * items which have been canceled and should not be replayed.&n; */
DECL|struct|xfs_buf_cancel
r_typedef
r_struct
id|xfs_buf_cancel
(brace
DECL|member|bc_blkno
id|xfs_daddr_t
id|bc_blkno
suffix:semicolon
DECL|member|bc_len
id|uint
id|bc_len
suffix:semicolon
DECL|member|bc_refcount
r_int
id|bc_refcount
suffix:semicolon
DECL|member|bc_next
r_struct
id|xfs_buf_cancel
op_star
id|bc_next
suffix:semicolon
DECL|typedef|xfs_buf_cancel_t
)brace
id|xfs_buf_cancel_t
suffix:semicolon
DECL|macro|XFS_BLI_TRACE_SIZE
mdefine_line|#define XFS_BLI_TRACE_SIZE&t;32
macro_line|#if defined(XFS_ALL_TRACE)
DECL|macro|XFS_BLI_TRACE
mdefine_line|#define XFS_BLI_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_BLI_TRACE
macro_line|#undef XFS_BLI_TRACE
macro_line|#endif
macro_line|#if defined(XFS_BLI_TRACE)
r_void
id|xfs_buf_item_trace
c_func
(paren
r_char
op_star
comma
id|xfs_buf_log_item_t
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_buf_item_trace
mdefine_line|#define xfs_buf_item_trace(id, bip)
macro_line|#endif
r_void
id|xfs_buf_item_init
c_func
(paren
r_struct
id|xfs_buf
op_star
comma
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_void
id|xfs_buf_item_relse
c_func
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_buf_item_log
c_func
(paren
id|xfs_buf_log_item_t
op_star
comma
id|uint
comma
id|uint
)paren
suffix:semicolon
id|uint
id|xfs_buf_item_dirty
c_func
(paren
id|xfs_buf_log_item_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_buf_attach_iodone
c_func
(paren
r_struct
id|xfs_buf
op_star
comma
r_void
(paren
op_star
)paren
(paren
r_struct
id|xfs_buf
op_star
comma
id|xfs_log_item_t
op_star
)paren
comma
id|xfs_log_item_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_buf_iodone_callbacks
c_func
(paren
r_struct
id|xfs_buf
op_star
)paren
suffix:semicolon
r_void
id|xfs_buf_iodone
c_func
(paren
r_struct
id|xfs_buf
op_star
comma
id|xfs_buf_log_item_t
op_star
)paren
suffix:semicolon
macro_line|#ifdef XFS_TRANS_DEBUG
r_void
id|xfs_buf_item_flush_log_debug
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
comma
id|uint
id|first
comma
id|uint
id|last
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_buf_item_flush_log_debug
mdefine_line|#define xfs_buf_item_flush_log_debug(bp, first, last)
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_BUF_ITEM_H__ */
eof
