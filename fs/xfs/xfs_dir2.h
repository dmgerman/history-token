multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR2_H__
DECL|macro|__XFS_DIR2_H__
mdefine_line|#define __XFS_DIR2_H__
r_struct
id|dirent
suffix:semicolon
r_struct
id|uio
suffix:semicolon
r_struct
id|xfs_dabuf
suffix:semicolon
r_struct
id|xfs_da_args
suffix:semicolon
r_struct
id|xfs_dir2_put_args
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * Directory version 2.&n; * There are 4 possible formats:&n; *&t;shortform&n; *&t;single block - data with embedded leaf at the end&n; *&t;multiple data blocks, single leaf+freeindex block&n; *&t;data blocks, node&amp;leaf blocks (btree), freeindex blocks&n; *&n; *&t;The shortform format is in xfs_dir2_sf.h.&n; *&t;The single block format is in xfs_dir2_block.h.&n; *&t;The data block format is in xfs_dir2_data.h.&n; *&t;The leaf and freeindex block formats are in xfs_dir2_leaf.h.&n; *&t;Node blocks are the same as the other version, in xfs_da_btree.h.&n; */
multiline_comment|/*&n; * Byte offset in data block and shortform entry.&n; */
DECL|typedef|xfs_dir2_data_off_t
r_typedef
id|__uint16_t
id|xfs_dir2_data_off_t
suffix:semicolon
DECL|macro|NULLDATAOFF
mdefine_line|#define NULLDATAOFF&t;0xffffU
DECL|typedef|xfs_dir2_data_aoff_t
r_typedef
id|uint
id|xfs_dir2_data_aoff_t
suffix:semicolon
multiline_comment|/* argument form */
multiline_comment|/*&n; * Directory block number (logical dirblk in file)&n; */
DECL|typedef|xfs_dir2_db_t
r_typedef
id|__uint32_t
id|xfs_dir2_db_t
suffix:semicolon
multiline_comment|/*&n; * Byte offset in a directory.&n; */
DECL|typedef|xfs_dir2_off_t
r_typedef
id|xfs_off_t
id|xfs_dir2_off_t
suffix:semicolon
multiline_comment|/*&n; * For getdents, argument struct for put routines.&n; */
DECL|typedef|xfs_dir2_put_t
r_typedef
r_int
(paren
op_star
id|xfs_dir2_put_t
)paren
(paren
r_struct
id|xfs_dir2_put_args
op_star
id|pa
)paren
suffix:semicolon
DECL|struct|xfs_dir2_put_args
r_typedef
r_struct
id|xfs_dir2_put_args
(brace
DECL|member|cook
id|xfs_off_t
id|cook
suffix:semicolon
multiline_comment|/* cookie of (next) entry */
DECL|member|ino
id|xfs_intino_t
id|ino
suffix:semicolon
multiline_comment|/* inode number */
DECL|member|dbp
r_struct
id|xfs_dirent
op_star
id|dbp
suffix:semicolon
multiline_comment|/* buffer pointer */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* directory entry name */
DECL|member|namelen
r_int
id|namelen
suffix:semicolon
multiline_comment|/* length of name */
DECL|member|done
r_int
id|done
suffix:semicolon
multiline_comment|/* output: set if value was stored */
DECL|member|put
id|xfs_dir2_put_t
id|put
suffix:semicolon
multiline_comment|/* put function ptr (i/o) */
DECL|member|uio
r_struct
id|uio
op_star
id|uio
suffix:semicolon
multiline_comment|/* uio control structure */
DECL|typedef|xfs_dir2_put_args_t
)brace
id|xfs_dir2_put_args_t
suffix:semicolon
DECL|macro|XFS_DIR_IS_V2
mdefine_line|#define XFS_DIR_IS_V2(mp)&t;((mp)-&gt;m_dirversion == 2)
r_extern
id|xfs_dirops_t
id|xfsv2_dirops
suffix:semicolon
multiline_comment|/*&n; * Other interfaces used by the rest of the dir v2 code.&n; */
r_extern
r_int
id|xfs_dir2_grow_inode
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
r_int
id|space
comma
id|xfs_dir2_db_t
op_star
id|dbp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_isblock
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_int
op_star
id|vp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_isleaf
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
r_int
op_star
id|vp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_shrink_inode
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_dir2_db_t
id|db
comma
r_struct
id|xfs_dabuf
op_star
id|bp
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_DIR2_H__ */
eof
