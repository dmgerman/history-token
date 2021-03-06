multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR2_BLOCK_H__
DECL|macro|__XFS_DIR2_BLOCK_H__
mdefine_line|#define&t;__XFS_DIR2_BLOCK_H__
multiline_comment|/*&n; * xfs_dir2_block.h&n; * Directory version 2, single block format structures&n; */
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
id|xfs_dir2_data_hdr
suffix:semicolon
r_struct
id|xfs_dir2_leaf_entry
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * The single block format is as follows:&n; * xfs_dir2_data_hdr_t structure&n; * xfs_dir2_data_entry_t and xfs_dir2_data_unused_t structures&n; * xfs_dir2_leaf_entry_t structures&n; * xfs_dir2_block_tail_t structure&n; */
DECL|macro|XFS_DIR2_BLOCK_MAGIC
mdefine_line|#define&t;XFS_DIR2_BLOCK_MAGIC&t;0x58443242&t;/* XD2B: for one block dirs */
DECL|struct|xfs_dir2_block_tail
r_typedef
r_struct
id|xfs_dir2_block_tail
(brace
DECL|member|count
id|__uint32_t
id|count
suffix:semicolon
multiline_comment|/* count of leaf entries */
DECL|member|stale
id|__uint32_t
id|stale
suffix:semicolon
multiline_comment|/* count of stale lf entries */
DECL|typedef|xfs_dir2_block_tail_t
)brace
id|xfs_dir2_block_tail_t
suffix:semicolon
multiline_comment|/*&n; * Generic single-block structure, for xfs_db.&n; */
DECL|struct|xfs_dir2_block
r_typedef
r_struct
id|xfs_dir2_block
(brace
DECL|member|hdr
id|xfs_dir2_data_hdr_t
id|hdr
suffix:semicolon
multiline_comment|/* magic XFS_DIR2_BLOCK_MAGIC */
DECL|member|u
id|xfs_dir2_data_union_t
id|u
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|leaf
id|xfs_dir2_leaf_entry_t
id|leaf
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|tail
id|xfs_dir2_block_tail_t
id|tail
suffix:semicolon
DECL|typedef|xfs_dir2_block_t
)brace
id|xfs_dir2_block_t
suffix:semicolon
multiline_comment|/*&n; * Pointer to the leaf header embedded in a data block (1-block format)&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_BLOCK_TAIL_P)
id|xfs_dir2_block_tail_t
op_star
id|xfs_dir2_block_tail_p
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_block_t
op_star
id|block
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_BLOCK_TAIL_P
mdefine_line|#define&t;XFS_DIR2_BLOCK_TAIL_P(mp,block)&t;xfs_dir2_block_tail_p(mp,block)
macro_line|#else
DECL|macro|XFS_DIR2_BLOCK_TAIL_P
mdefine_line|#define&t;XFS_DIR2_BLOCK_TAIL_P(mp,block)&t;&bslash;&n;&t;(((xfs_dir2_block_tail_t *)((char *)(block) + (mp)-&gt;m_dirblksize)) - 1)
macro_line|#endif
multiline_comment|/*&n; * Pointer to the leaf entries embedded in a data block (1-block format)&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_BLOCK_LEAF_P)
r_struct
id|xfs_dir2_leaf_entry
op_star
id|xfs_dir2_block_leaf_p
c_func
(paren
id|xfs_dir2_block_tail_t
op_star
id|btp
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_BLOCK_LEAF_P
mdefine_line|#define&t;XFS_DIR2_BLOCK_LEAF_P(btp) &bslash;&n;&t;xfs_dir2_block_leaf_p(btp)
macro_line|#else
DECL|macro|XFS_DIR2_BLOCK_LEAF_P
mdefine_line|#define&t;XFS_DIR2_BLOCK_LEAF_P(btp)&t;&bslash;&n;&t;(((struct xfs_dir2_leaf_entry *)(btp)) - INT_GET((btp)-&gt;count, ARCH_CONVERT))
macro_line|#endif
multiline_comment|/*&n; * Function declarations.&n; */
r_extern
r_int
id|xfs_dir2_block_addname
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_block_getdents
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
r_struct
id|uio
op_star
id|uio
comma
r_int
op_star
id|eofp
comma
r_struct
id|xfs_dirent
op_star
id|dbp
comma
id|xfs_dir2_put_t
id|put
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_block_lookup
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_block_removename
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_block_replace
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leaf_to_block
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
r_struct
id|xfs_dabuf
op_star
id|lbp
comma
r_struct
id|xfs_dabuf
op_star
id|dbp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_sf_to_block
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_DIR2_BLOCK_H__ */
eof
