multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR2_NODE_H__
DECL|macro|__XFS_DIR2_NODE_H__
mdefine_line|#define __XFS_DIR2_NODE_H__
multiline_comment|/*&n; * Directory version 2, btree node format structures&n; */
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
id|xfs_da_state
suffix:semicolon
r_struct
id|xfs_da_state_blk
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * Constants.&n; */
multiline_comment|/*&n; * Offset of the freespace index.&n; */
DECL|macro|XFS_DIR2_FREE_SPACE
mdefine_line|#define XFS_DIR2_FREE_SPACE&t;2
DECL|macro|XFS_DIR2_FREE_OFFSET
mdefine_line|#define XFS_DIR2_FREE_OFFSET&t;(XFS_DIR2_FREE_SPACE * XFS_DIR2_SPACE_SIZE)
DECL|macro|XFS_DIR2_FREE_FIRSTDB
mdefine_line|#define XFS_DIR2_FREE_FIRSTDB(mp)&t;&bslash;&n;&t;XFS_DIR2_BYTE_TO_DB(mp, XFS_DIR2_FREE_OFFSET)
DECL|macro|XFS_DIR2_FREE_MAGIC
mdefine_line|#define XFS_DIR2_FREE_MAGIC&t;0x58443246&t;/* XD2F */
multiline_comment|/*&n; * Structures.&n; */
DECL|struct|xfs_dir2_free_hdr
r_typedef
r_struct
id|xfs_dir2_free_hdr
(brace
DECL|member|magic
id|__uint32_t
id|magic
suffix:semicolon
multiline_comment|/* XFS_DIR2_FREE_MAGIC */
DECL|member|firstdb
id|__int32_t
id|firstdb
suffix:semicolon
multiline_comment|/* db of first entry */
DECL|member|nvalid
id|__int32_t
id|nvalid
suffix:semicolon
multiline_comment|/* count of valid entries */
DECL|member|nused
id|__int32_t
id|nused
suffix:semicolon
multiline_comment|/* count of used entries */
DECL|typedef|xfs_dir2_free_hdr_t
)brace
id|xfs_dir2_free_hdr_t
suffix:semicolon
DECL|struct|xfs_dir2_free
r_typedef
r_struct
id|xfs_dir2_free
(brace
DECL|member|hdr
id|xfs_dir2_free_hdr_t
id|hdr
suffix:semicolon
multiline_comment|/* block header */
DECL|member|bests
id|xfs_dir2_data_off_t
id|bests
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* best free counts */
multiline_comment|/* unused entries are -1 */
DECL|typedef|xfs_dir2_free_t
)brace
id|xfs_dir2_free_t
suffix:semicolon
DECL|macro|XFS_DIR2_MAX_FREE_BESTS
mdefine_line|#define XFS_DIR2_MAX_FREE_BESTS(mp)&t;&bslash;&n;&t;(((mp)-&gt;m_dirblksize - (uint)sizeof(xfs_dir2_free_hdr_t)) / &bslash;&n;&t; (uint)sizeof(xfs_dir2_data_off_t))
multiline_comment|/*&n; * Macros.&n; */
multiline_comment|/*&n; * Convert data space db to the corresponding free db.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DB_TO_FDB)
id|xfs_dir2_db_t
id|xfs_dir2_db_to_fdb
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_db_t
id|db
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DB_TO_FDB
mdefine_line|#define XFS_DIR2_DB_TO_FDB(mp,db)&t;xfs_dir2_db_to_fdb(mp, db)
macro_line|#else
DECL|macro|XFS_DIR2_DB_TO_FDB
mdefine_line|#define XFS_DIR2_DB_TO_FDB(mp,db)&t;&bslash;&n;&t;(XFS_DIR2_FREE_FIRSTDB(mp) + (db) / XFS_DIR2_MAX_FREE_BESTS(mp))
macro_line|#endif
multiline_comment|/*&n; * Convert data space db to the corresponding index in a free db.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DB_TO_FDINDEX)
r_int
id|xfs_dir2_db_to_fdindex
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_db_t
id|db
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DB_TO_FDINDEX
mdefine_line|#define XFS_DIR2_DB_TO_FDINDEX(mp,db)&t;xfs_dir2_db_to_fdindex(mp, db)
macro_line|#else
DECL|macro|XFS_DIR2_DB_TO_FDINDEX
mdefine_line|#define XFS_DIR2_DB_TO_FDINDEX(mp,db)&t;((db) % XFS_DIR2_MAX_FREE_BESTS(mp))
macro_line|#endif
multiline_comment|/*&n; * Functions.&n; */
r_extern
r_void
id|xfs_dir2_free_log_bests
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
r_struct
id|xfs_dabuf
op_star
id|bp
comma
r_int
id|first
comma
r_int
id|last
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leaf_to_node
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
)paren
suffix:semicolon
r_extern
id|xfs_dahash_t
id|xfs_dir2_leafn_lasthash
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|bp
comma
r_int
op_star
id|count
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leafn_lookup_int
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|bp
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_int
op_star
id|indexp
comma
r_struct
id|xfs_da_state
op_star
id|state
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leafn_order
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|leaf1_bp
comma
r_struct
id|xfs_dabuf
op_star
id|leaf2_bp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leafn_split
c_func
(paren
r_struct
id|xfs_da_state
op_star
id|state
comma
r_struct
id|xfs_da_state_blk
op_star
id|oldblk
comma
r_struct
id|xfs_da_state_blk
op_star
id|newblk
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leafn_toosmall
c_func
(paren
r_struct
id|xfs_da_state
op_star
id|state
comma
r_int
op_star
id|action
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_leafn_unbalance
c_func
(paren
r_struct
id|xfs_da_state
op_star
id|state
comma
r_struct
id|xfs_da_state_blk
op_star
id|drop_blk
comma
r_struct
id|xfs_da_state_blk
op_star
id|save_blk
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_node_addname
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
id|xfs_dir2_node_lookup
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
id|xfs_dir2_node_removename
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
id|xfs_dir2_node_replace
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
id|xfs_dir2_node_trim_free
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_fileoff_t
id|fo
comma
r_int
op_star
id|rvalp
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_DIR2_NODE_H__ */
eof
