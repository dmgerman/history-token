multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ITABLE_H__
DECL|macro|__XFS_ITABLE_H__
mdefine_line|#define __XFS_ITABLE_H__
multiline_comment|/*&n; * xfs_bulkstat() is used to fill in xfs_bstat structures as well as dm_stat&n; * structures (by the dmi library). This is a pointer to a formatter function&n; * that will iget the inode and fill in the appropriate structure.&n; * see xfs_bulkstat_one() and dm_bulkstat_one() in dmi_xfs.c&n; */
DECL|typedef|bulkstat_one_pf
r_typedef
r_int
(paren
op_star
id|bulkstat_one_pf
)paren
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_struct
id|xfs_trans
op_star
id|tp
comma
id|xfs_ino_t
id|ino
comma
r_void
op_star
id|buffer
comma
id|xfs_daddr_t
id|bno
comma
r_void
op_star
id|dip
comma
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n; * Values for stat return value.&n; */
DECL|macro|BULKSTAT_RV_NOTHING
mdefine_line|#define BULKSTAT_RV_NOTHING&t;0
DECL|macro|BULKSTAT_RV_DIDONE
mdefine_line|#define BULKSTAT_RV_DIDONE&t;1
DECL|macro|BULKSTAT_RV_GIVEUP
mdefine_line|#define BULKSTAT_RV_GIVEUP&t;2
multiline_comment|/*&n; * Values for bulkstat flag argument.&n; */
DECL|macro|BULKSTAT_FG_IGET
mdefine_line|#define BULKSTAT_FG_IGET&t;0x1&t;/* Go through the buffer cache */
DECL|macro|BULKSTAT_FG_QUICK
mdefine_line|#define BULKSTAT_FG_QUICK&t;0x2&t;/* No iget, walk the dinode cluster */
DECL|macro|BULKSTAT_FG_VFSLOCKED
mdefine_line|#define BULKSTAT_FG_VFSLOCKED&t;0x4&t;/* Already have vfs lock */
multiline_comment|/*&n; * Return stat information in bulk (by-inode) for the filesystem.&n; */
r_int
multiline_comment|/* error status */
id|xfs_bulkstat
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
multiline_comment|/* mount point for filesystem */
id|xfs_trans_t
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_ino_t
op_star
id|lastino
comma
multiline_comment|/* last inode returned */
r_int
op_star
id|count
comma
multiline_comment|/* size of buffer/count returned */
id|bulkstat_one_pf
id|formatter
comma
multiline_comment|/* func that&squot;d fill a single buf */
r_int
id|statstruct_size
comma
multiline_comment|/* sizeof struct that we&squot;re filling */
id|xfs_caddr_t
id|ubuffer
comma
multiline_comment|/* buffer with inode stats */
r_int
id|flags
comma
multiline_comment|/* flag to control access method */
r_int
op_star
id|done
)paren
suffix:semicolon
multiline_comment|/* 1 if there&squot;re more stats to get */
r_int
id|xfs_bulkstat_single
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_ino_t
op_star
id|lastinop
comma
id|xfs_caddr_t
id|buffer
comma
r_int
op_star
id|done
)paren
suffix:semicolon
r_int
id|xfs_bulkstat_one
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_ino_t
id|ino
comma
r_void
op_star
id|buffer
comma
id|xfs_daddr_t
id|bno
comma
r_void
op_star
id|dibuff
comma
r_int
op_star
id|stat
)paren
suffix:semicolon
r_int
multiline_comment|/* error status */
id|xfs_inumbers
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
multiline_comment|/* mount point for filesystem */
id|xfs_trans_t
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_ino_t
op_star
id|last
comma
multiline_comment|/* last inode returned */
r_int
op_star
id|count
comma
multiline_comment|/* size of buffer/count returned */
id|xfs_caddr_t
id|buffer
)paren
suffix:semicolon
multiline_comment|/* buffer with inode descriptions */
macro_line|#endif&t;/* __XFS_ITABLE_H__ */
eof
