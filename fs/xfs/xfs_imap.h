multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_IMAP_H__
DECL|macro|__XFS_IMAP_H__
mdefine_line|#define __XFS_IMAP_H__
multiline_comment|/*&n; * This is the structure passed to xfs_imap() to map&n; * an inode number to its on disk location.&n; */
DECL|struct|xfs_imap
r_typedef
r_struct
id|xfs_imap
(brace
DECL|member|im_blkno
id|xfs_daddr_t
id|im_blkno
suffix:semicolon
multiline_comment|/* starting BB of inode chunk */
DECL|member|im_len
id|uint
id|im_len
suffix:semicolon
multiline_comment|/* length in BBs of inode chunk */
DECL|member|im_agblkno
id|xfs_agblock_t
id|im_agblkno
suffix:semicolon
multiline_comment|/* logical block of inode chunk in ag */
DECL|member|im_ioffset
id|ushort
id|im_ioffset
suffix:semicolon
multiline_comment|/* inode offset in block in &quot;inodes&quot; */
DECL|member|im_boffset
id|ushort
id|im_boffset
suffix:semicolon
multiline_comment|/* inode offset in block in bytes */
DECL|typedef|xfs_imap_t
)brace
id|xfs_imap_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
r_int
id|xfs_imap
c_func
(paren
r_struct
id|xfs_mount
op_star
comma
r_struct
id|xfs_trans
op_star
comma
id|xfs_ino_t
comma
id|xfs_imap_t
op_star
comma
id|uint
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* __XFS_IMAP_H__ */
eof
