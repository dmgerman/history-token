multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_INODE_ITEM_H__
DECL|macro|__XFS_INODE_ITEM_H__
mdefine_line|#define __XFS_INODE_ITEM_H__
multiline_comment|/*&n; * This is the structure used to lay out an inode log item in the&n; * log.&t; The size of the inline data/extents/b-tree root to be logged&n; * (if any) is indicated in the ilf_dsize field.  Changes to this structure&n; * must be added on to the end.&n; *&n; * Convention for naming inode log item versions :  The current version&n; * is always named XFS_LI_INODE.  When an inode log item gets superseded,&n; * add the latest version of IRIX that will generate logs with that item&n; * to the version name.&n; *&n; * -Version 1 of this structure (XFS_LI_5_3_INODE) included up to the first&n; *&t;union (ilf_u) field.  This was released with IRIX 5.3-XFS.&n; * -Version 2 of this structure (XFS_LI_6_1_INODE) is currently the entire&n; *&t;structure.  This was released with IRIX 6.0.1-XFS and IRIX 6.1.&n; * -Version 3 of this structure (XFS_LI_INODE) is the same as version 2&n; *&t;so a new structure definition wasn&squot;t necessary.&t; However, we had&n; *&t;to add a new type because the inode cluster size changed from 4K&n; *&t;to 8K and the version number had to be rev&squot;ved to keep older kernels&n; *&t;from trying to recover logs with the 8K buffers in them.  The logging&n; *&t;code can handle recovery on different-sized clusters now so hopefully&n; *&t;this&squot;ll be the last time we need to change the inode log item just&n; *&t;for a change in the inode cluster size.&t; This new version was&n; *&t;released with IRIX 6.2.&n; */
DECL|struct|xfs_inode_log_format
r_typedef
r_struct
id|xfs_inode_log_format
(brace
DECL|member|ilf_type
r_int
r_int
id|ilf_type
suffix:semicolon
multiline_comment|/* inode log item type */
DECL|member|ilf_size
r_int
r_int
id|ilf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|ilf_fields
id|uint
id|ilf_fields
suffix:semicolon
multiline_comment|/* flags for fields logged */
DECL|member|ilf_asize
id|ushort
id|ilf_asize
suffix:semicolon
multiline_comment|/* size of attr d/ext/root */
DECL|member|ilf_dsize
id|ushort
id|ilf_dsize
suffix:semicolon
multiline_comment|/* size of data/ext/root */
DECL|member|ilf_ino
id|xfs_ino_t
id|ilf_ino
suffix:semicolon
multiline_comment|/* inode number */
r_union
(brace
DECL|member|ilfu_rdev
id|xfs_dev_t
id|ilfu_rdev
suffix:semicolon
multiline_comment|/* rdev value for dev inode*/
DECL|member|ilfu_uuid
id|uuid_t
id|ilfu_uuid
suffix:semicolon
multiline_comment|/* mount point value */
DECL|member|ilf_u
)brace
id|ilf_u
suffix:semicolon
DECL|member|ilf_blkno
id|__int64_t
id|ilf_blkno
suffix:semicolon
multiline_comment|/* blkno of inode buffer */
DECL|member|ilf_len
r_int
id|ilf_len
suffix:semicolon
multiline_comment|/* len of inode buffer */
DECL|member|ilf_boffset
r_int
id|ilf_boffset
suffix:semicolon
multiline_comment|/* off of inode in buffer */
DECL|typedef|xfs_inode_log_format_t
)brace
id|xfs_inode_log_format_t
suffix:semicolon
multiline_comment|/* Initial version shipped with IRIX 5.3-XFS */
DECL|struct|xfs_inode_log_format_v1
r_typedef
r_struct
id|xfs_inode_log_format_v1
(brace
DECL|member|ilf_type
r_int
r_int
id|ilf_type
suffix:semicolon
multiline_comment|/* inode log item type */
DECL|member|ilf_size
r_int
r_int
id|ilf_size
suffix:semicolon
multiline_comment|/* size of this item */
DECL|member|ilf_fields
id|uint
id|ilf_fields
suffix:semicolon
multiline_comment|/* flags for fields logged */
DECL|member|ilf_dsize
id|uint
id|ilf_dsize
suffix:semicolon
multiline_comment|/* size of data/ext/root */
DECL|member|ilf_ino
id|xfs_ino_t
id|ilf_ino
suffix:semicolon
multiline_comment|/* inode number */
r_union
(brace
DECL|member|ilfu_rdev
id|xfs_dev_t
id|ilfu_rdev
suffix:semicolon
multiline_comment|/* rdev value for dev inode*/
DECL|member|ilfu_uuid
id|uuid_t
id|ilfu_uuid
suffix:semicolon
multiline_comment|/* mount point value */
DECL|member|ilf_u
)brace
id|ilf_u
suffix:semicolon
DECL|typedef|xfs_inode_log_format_t_v1
)brace
id|xfs_inode_log_format_t_v1
suffix:semicolon
multiline_comment|/*&n; * Flags for xfs_trans_log_inode flags field.&n; */
DECL|macro|XFS_ILOG_CORE
mdefine_line|#define XFS_ILOG_CORE&t;0x001&t;/* log standard inode fields */
DECL|macro|XFS_ILOG_DDATA
mdefine_line|#define XFS_ILOG_DDATA&t;0x002&t;/* log i_df.if_data */
DECL|macro|XFS_ILOG_DEXT
mdefine_line|#define XFS_ILOG_DEXT&t;0x004&t;/* log i_df.if_extents */
DECL|macro|XFS_ILOG_DBROOT
mdefine_line|#define XFS_ILOG_DBROOT 0x008&t;/* log i_df.i_broot */
DECL|macro|XFS_ILOG_DEV
mdefine_line|#define XFS_ILOG_DEV&t;0x010&t;/* log the dev field */
DECL|macro|XFS_ILOG_UUID
mdefine_line|#define XFS_ILOG_UUID&t;0x020&t;/* log the uuid field */
DECL|macro|XFS_ILOG_ADATA
mdefine_line|#define XFS_ILOG_ADATA&t;0x040&t;/* log i_af.if_data */
DECL|macro|XFS_ILOG_AEXT
mdefine_line|#define XFS_ILOG_AEXT&t;0x080&t;/* log i_af.if_extents */
DECL|macro|XFS_ILOG_ABROOT
mdefine_line|#define XFS_ILOG_ABROOT 0x100&t;/* log i_af.i_broot */
DECL|macro|XFS_ILOG_NONCORE
mdefine_line|#define XFS_ILOG_NONCORE&t;(XFS_ILOG_DDATA | XFS_ILOG_DEXT | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_DBROOT | XFS_ILOG_DEV | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_UUID | XFS_ILOG_ADATA | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_AEXT | XFS_ILOG_ABROOT)
DECL|macro|XFS_ILOG_DFORK
mdefine_line|#define XFS_ILOG_DFORK&t;&t;(XFS_ILOG_DDATA | XFS_ILOG_DEXT | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_DBROOT)
DECL|macro|XFS_ILOG_AFORK
mdefine_line|#define XFS_ILOG_AFORK&t;&t;(XFS_ILOG_ADATA | XFS_ILOG_AEXT | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_ABROOT)
DECL|macro|XFS_ILOG_ALL
mdefine_line|#define XFS_ILOG_ALL&t;&t;(XFS_ILOG_CORE | XFS_ILOG_DDATA | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_DEXT | XFS_ILOG_DBROOT | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_DEV | XFS_ILOG_UUID | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_ADATA | XFS_ILOG_AEXT | &bslash;&n;&t;&t;&t;&t; XFS_ILOG_ABROOT)
DECL|macro|XFS_ILI_HOLD
mdefine_line|#define XFS_ILI_HOLD&t;&t;0x1
DECL|macro|XFS_ILI_IOLOCKED_EXCL
mdefine_line|#define XFS_ILI_IOLOCKED_EXCL&t;0x2
DECL|macro|XFS_ILI_IOLOCKED_SHARED
mdefine_line|#define XFS_ILI_IOLOCKED_SHARED 0x4
DECL|macro|XFS_ILI_IOLOCKED_ANY
mdefine_line|#define XFS_ILI_IOLOCKED_ANY   (XFS_ILI_IOLOCKED_EXCL | XFS_ILI_IOLOCKED_SHARED)
macro_line|#ifdef __KERNEL__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_bmbt_rec_32
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
DECL|struct|xfs_inode_log_item
r_typedef
r_struct
id|xfs_inode_log_item
(brace
DECL|member|ili_item
id|xfs_log_item_t
id|ili_item
suffix:semicolon
multiline_comment|/* common portion */
DECL|member|ili_inode
r_struct
id|xfs_inode
op_star
id|ili_inode
suffix:semicolon
multiline_comment|/* inode ptr */
DECL|member|ili_flush_lsn
id|xfs_lsn_t
id|ili_flush_lsn
suffix:semicolon
multiline_comment|/* lsn at last flush */
DECL|member|ili_last_lsn
id|xfs_lsn_t
id|ili_last_lsn
suffix:semicolon
multiline_comment|/* lsn at last transaction */
DECL|member|ili_ilock_recur
r_int
r_int
id|ili_ilock_recur
suffix:semicolon
multiline_comment|/* lock recursion count */
DECL|member|ili_iolock_recur
r_int
r_int
id|ili_iolock_recur
suffix:semicolon
multiline_comment|/* lock recursion count */
DECL|member|ili_flags
r_int
r_int
id|ili_flags
suffix:semicolon
multiline_comment|/* misc flags */
DECL|member|ili_logged
r_int
r_int
id|ili_logged
suffix:semicolon
multiline_comment|/* flushed logged data */
DECL|member|ili_last_fields
r_int
r_int
id|ili_last_fields
suffix:semicolon
multiline_comment|/* fields when flushed */
DECL|member|ili_extents_buf
r_struct
id|xfs_bmbt_rec_32
op_star
id|ili_extents_buf
suffix:semicolon
multiline_comment|/* array of logged exts */
DECL|member|ili_pushbuf_flag
r_int
r_int
id|ili_pushbuf_flag
suffix:semicolon
multiline_comment|/* one bit used in push_ail */
macro_line|#ifdef DEBUG
DECL|member|ili_push_owner
r_uint64
id|ili_push_owner
suffix:semicolon
multiline_comment|/* one who sets pushbuf_flag&n;&t;&t;&t;&t;&t;&t;      above gets to push the buf */
macro_line|#endif
macro_line|#ifdef XFS_TRANS_DEBUG
DECL|member|ili_root_size
r_int
id|ili_root_size
suffix:semicolon
DECL|member|ili_orig_root
r_char
op_star
id|ili_orig_root
suffix:semicolon
macro_line|#endif
DECL|member|ili_format
id|xfs_inode_log_format_t
id|ili_format
suffix:semicolon
multiline_comment|/* logged structure */
DECL|typedef|xfs_inode_log_item_t
)brace
id|xfs_inode_log_item_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ILOG_FDATA)
r_int
id|xfs_ilog_fdata
c_func
(paren
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_ILOG_FDATA
mdefine_line|#define XFS_ILOG_FDATA(w)&t;xfs_ilog_fdata(w)
macro_line|#else
DECL|macro|XFS_ILOG_FDATA
mdefine_line|#define XFS_ILOG_FDATA(w)&t;&bslash;&n;&t;((w) == XFS_DATA_FORK ? XFS_ILOG_DDATA : XFS_ILOG_ADATA)
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ILOG_FBROOT)
r_int
id|xfs_ilog_fbroot
c_func
(paren
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_ILOG_FBROOT
mdefine_line|#define XFS_ILOG_FBROOT(w)&t;xfs_ilog_fbroot(w)
macro_line|#else
DECL|macro|XFS_ILOG_FBROOT
mdefine_line|#define XFS_ILOG_FBROOT(w)&t;&bslash;&n;&t;((w) == XFS_DATA_FORK ? XFS_ILOG_DBROOT : XFS_ILOG_ABROOT)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ILOG_FEXT)
r_int
id|xfs_ilog_fext
c_func
(paren
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_ILOG_FEXT
mdefine_line|#define XFS_ILOG_FEXT(w)&t;xfs_ilog_fext(w)
macro_line|#else
DECL|macro|XFS_ILOG_FEXT
mdefine_line|#define XFS_ILOG_FEXT(w)&t;&bslash;&n;&t;((w) == XFS_DATA_FORK ? XFS_ILOG_DEXT : XFS_ILOG_AEXT)
macro_line|#endif
macro_line|#ifdef __KERNEL__
r_void
id|xfs_inode_item_init
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
r_struct
id|xfs_mount
op_star
)paren
suffix:semicolon
r_void
id|xfs_inode_item_destroy
c_func
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
r_void
id|xfs_iflush_done
c_func
(paren
r_struct
id|xfs_buf
op_star
comma
id|xfs_inode_log_item_t
op_star
)paren
suffix:semicolon
r_void
id|xfs_iflush_abort
c_func
(paren
r_struct
id|xfs_inode
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_INODE_ITEM_H__ */
eof
