multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_UTILS_H__
DECL|macro|__XFS_UTILS_H__
mdefine_line|#define __XFS_UTILS_H__
DECL|macro|IRELE
mdefine_line|#define IRELE(ip)&t;VN_RELE(XFS_ITOV(ip))
DECL|macro|IHOLD
mdefine_line|#define IHOLD(ip)&t;VN_HOLD(XFS_ITOV(ip))
DECL|macro|ITRACE
mdefine_line|#define&t;ITRACE(ip)&t;vn_trace_ref(XFS_ITOV(ip), __FILE__, __LINE__, &bslash;&n;&t;&t;&t;&t;(inst_t *)__return_address)
r_extern
r_int
id|xfs_rename
(paren
id|bhv_desc_t
op_star
comma
id|vname_t
op_star
comma
id|vnode_t
op_star
comma
id|vname_t
op_star
comma
id|cred_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_get_dir_entry
(paren
id|vname_t
op_star
comma
id|xfs_inode_t
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir_lookup_int
(paren
id|bhv_desc_t
op_star
comma
id|uint
comma
id|vname_t
op_star
comma
id|xfs_ino_t
op_star
comma
id|xfs_inode_t
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_truncate_file
(paren
id|xfs_mount_t
op_star
comma
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir_ialloc
(paren
id|xfs_trans_t
op_star
op_star
comma
id|xfs_inode_t
op_star
comma
id|mode_t
comma
id|nlink_t
comma
id|xfs_dev_t
comma
id|cred_t
op_star
comma
id|prid_t
comma
r_int
comma
id|xfs_inode_t
op_star
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_droplink
(paren
id|xfs_trans_t
op_star
comma
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_bumplink
(paren
id|xfs_trans_t
op_star
comma
id|xfs_inode_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xfs_bump_ino_vers2
(paren
id|xfs_trans_t
op_star
comma
id|xfs_inode_t
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_UTILS_H__ */
eof
