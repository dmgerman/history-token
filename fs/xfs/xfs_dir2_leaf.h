multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR2_LEAF_H__
DECL|macro|__XFS_DIR2_LEAF_H__
mdefine_line|#define&t;__XFS_DIR2_LEAF_H__
multiline_comment|/*&n; * Directory version 2, leaf block structures.&n; */
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
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * Constants.&n; */
multiline_comment|/*&n; * Offset of the leaf/node space.  First block in this space&n; * is the btree root.&n; */
DECL|macro|XFS_DIR2_LEAF_SPACE
mdefine_line|#define&t;XFS_DIR2_LEAF_SPACE&t;1
DECL|macro|XFS_DIR2_LEAF_OFFSET
mdefine_line|#define&t;XFS_DIR2_LEAF_OFFSET&t;(XFS_DIR2_LEAF_SPACE * XFS_DIR2_SPACE_SIZE)
DECL|macro|XFS_DIR2_LEAF_FIRSTDB
mdefine_line|#define&t;XFS_DIR2_LEAF_FIRSTDB(mp)&t;&bslash;&n;&t;XFS_DIR2_BYTE_TO_DB(mp, XFS_DIR2_LEAF_OFFSET)
multiline_comment|/*&n; * Types.&n; */
multiline_comment|/*&n; * Offset in data space of a data entry.&n; */
DECL|typedef|xfs_dir2_dataptr_t
r_typedef
id|__uint32_t
id|xfs_dir2_dataptr_t
suffix:semicolon
DECL|macro|XFS_DIR2_MAX_DATAPTR
mdefine_line|#define&t;XFS_DIR2_MAX_DATAPTR&t;((xfs_dir2_dataptr_t)0xffffffff)
DECL|macro|XFS_DIR2_NULL_DATAPTR
mdefine_line|#define&t;XFS_DIR2_NULL_DATAPTR&t;((xfs_dir2_dataptr_t)0)
multiline_comment|/*&n; * Structures.&n; */
multiline_comment|/*&n; * Leaf block header.&n; */
DECL|struct|xfs_dir2_leaf_hdr
r_typedef
r_struct
id|xfs_dir2_leaf_hdr
(brace
DECL|member|info
id|xfs_da_blkinfo_t
id|info
suffix:semicolon
multiline_comment|/* header for da routines */
DECL|member|count
id|__uint16_t
id|count
suffix:semicolon
multiline_comment|/* count of entries */
DECL|member|stale
id|__uint16_t
id|stale
suffix:semicolon
multiline_comment|/* count of stale entries */
DECL|typedef|xfs_dir2_leaf_hdr_t
)brace
id|xfs_dir2_leaf_hdr_t
suffix:semicolon
multiline_comment|/*&n; * Leaf block entry.&n; */
DECL|struct|xfs_dir2_leaf_entry
r_typedef
r_struct
id|xfs_dir2_leaf_entry
(brace
DECL|member|hashval
id|xfs_dahash_t
id|hashval
suffix:semicolon
multiline_comment|/* hash value of name */
DECL|member|address
id|xfs_dir2_dataptr_t
id|address
suffix:semicolon
multiline_comment|/* address of data entry */
DECL|typedef|xfs_dir2_leaf_entry_t
)brace
id|xfs_dir2_leaf_entry_t
suffix:semicolon
multiline_comment|/*&n; * Leaf block tail.&n; */
DECL|struct|xfs_dir2_leaf_tail
r_typedef
r_struct
id|xfs_dir2_leaf_tail
(brace
DECL|member|bestcount
id|__uint32_t
id|bestcount
suffix:semicolon
DECL|typedef|xfs_dir2_leaf_tail_t
)brace
id|xfs_dir2_leaf_tail_t
suffix:semicolon
multiline_comment|/*&n; * Leaf block.&n; * bests and tail are at the end of the block for single-leaf only&n; * (magic = XFS_DIR2_LEAF1_MAGIC not XFS_DIR2_LEAFN_MAGIC).&n; */
DECL|struct|xfs_dir2_leaf
r_typedef
r_struct
id|xfs_dir2_leaf
(brace
DECL|member|hdr
id|xfs_dir2_leaf_hdr_t
id|hdr
suffix:semicolon
multiline_comment|/* leaf header */
DECL|member|ents
id|xfs_dir2_leaf_entry_t
id|ents
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* entries */
multiline_comment|/* ... */
DECL|member|bests
id|xfs_dir2_data_off_t
id|bests
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* best free counts */
DECL|member|tail
id|xfs_dir2_leaf_tail_t
id|tail
suffix:semicolon
multiline_comment|/* leaf tail */
DECL|typedef|xfs_dir2_leaf_t
)brace
id|xfs_dir2_leaf_t
suffix:semicolon
multiline_comment|/*&n; * Macros.&n; * The DB blocks are logical directory block numbers, not filesystem blocks.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_MAX_LEAF_ENTS)
r_int
id|xfs_dir2_max_leaf_ents
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_MAX_LEAF_ENTS
mdefine_line|#define&t;XFS_DIR2_MAX_LEAF_ENTS(mp)&t;&bslash;&n;&t;xfs_dir2_max_leaf_ents(mp)
macro_line|#else
DECL|macro|XFS_DIR2_MAX_LEAF_ENTS
mdefine_line|#define&t;XFS_DIR2_MAX_LEAF_ENTS(mp)&t;&bslash;&n;&t;((int)(((mp)-&gt;m_dirblksize - (uint)sizeof(xfs_dir2_leaf_hdr_t)) / &bslash;&n;&t;       (uint)sizeof(xfs_dir2_leaf_entry_t)))
macro_line|#endif
multiline_comment|/*&n; * Get address of the bestcount field in the single-leaf block.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_LEAF_TAIL_P)
id|xfs_dir2_leaf_tail_t
op_star
id|xfs_dir2_leaf_tail_p
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_leaf_t
op_star
id|lp
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_LEAF_TAIL_P
mdefine_line|#define&t;XFS_DIR2_LEAF_TAIL_P(mp,lp)&t;&bslash;&n;&t;xfs_dir2_leaf_tail_p(mp, lp)
macro_line|#else
DECL|macro|XFS_DIR2_LEAF_TAIL_P
mdefine_line|#define&t;XFS_DIR2_LEAF_TAIL_P(mp,lp)&t;&bslash;&n;&t;((xfs_dir2_leaf_tail_t *)&bslash;&n;&t; ((char *)(lp) + (mp)-&gt;m_dirblksize - &bslash;&n;&t;  (uint)sizeof(xfs_dir2_leaf_tail_t)))
macro_line|#endif
multiline_comment|/*&n; * Get address of the bests array in the single-leaf block.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_LEAF_BESTS_P)
id|xfs_dir2_data_off_t
op_star
id|xfs_dir2_leaf_bests_p_arch
c_func
(paren
id|xfs_dir2_leaf_tail_t
op_star
id|ltp
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_LEAF_BESTS_P_ARCH
mdefine_line|#define&t;XFS_DIR2_LEAF_BESTS_P_ARCH(ltp,arch)&t;xfs_dir2_leaf_bests_p_arch(ltp,arch)
macro_line|#else
DECL|macro|XFS_DIR2_LEAF_BESTS_P_ARCH
mdefine_line|#define&t;XFS_DIR2_LEAF_BESTS_P_ARCH(ltp,arch)&t;&bslash;&n;&t;((xfs_dir2_data_off_t *)(ltp) - INT_GET((ltp)-&gt;bestcount, arch))
macro_line|#endif
multiline_comment|/*&n; * Convert dataptr to byte in file space&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DATAPTR_TO_BYTE)
id|xfs_dir2_off_t
id|xfs_dir2_dataptr_to_byte
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_dataptr_t
id|dp
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DATAPTR_TO_BYTE
mdefine_line|#define&t;XFS_DIR2_DATAPTR_TO_BYTE(mp,dp)&t;xfs_dir2_dataptr_to_byte(mp, dp)
macro_line|#else
DECL|macro|XFS_DIR2_DATAPTR_TO_BYTE
mdefine_line|#define&t;XFS_DIR2_DATAPTR_TO_BYTE(mp,dp)&t;&bslash;&n;&t;((xfs_dir2_off_t)(dp) &lt;&lt; XFS_DIR2_DATA_ALIGN_LOG)
macro_line|#endif
multiline_comment|/*&n; * Convert byte in file space to dataptr.  It had better be aligned.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_BYTE_TO_DATAPTR)
id|xfs_dir2_dataptr_t
id|xfs_dir2_byte_to_dataptr
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_off_t
id|by
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_BYTE_TO_DATAPTR
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_DATAPTR(mp,by)&t;xfs_dir2_byte_to_dataptr(mp,by)
macro_line|#else
DECL|macro|XFS_DIR2_BYTE_TO_DATAPTR
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_DATAPTR(mp,by)&t;&bslash;&n;&t;((xfs_dir2_dataptr_t)((by) &gt;&gt; XFS_DIR2_DATA_ALIGN_LOG))
macro_line|#endif
multiline_comment|/*&n; * Convert dataptr to a block number&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DATAPTR_TO_DB)
id|xfs_dir2_db_t
id|xfs_dir2_dataptr_to_db
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_dataptr_t
id|dp
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DATAPTR_TO_DB
mdefine_line|#define&t;XFS_DIR2_DATAPTR_TO_DB(mp,dp)&t;xfs_dir2_dataptr_to_db(mp, dp)
macro_line|#else
DECL|macro|XFS_DIR2_DATAPTR_TO_DB
mdefine_line|#define&t;XFS_DIR2_DATAPTR_TO_DB(mp,dp)&t;&bslash;&n;&t;XFS_DIR2_BYTE_TO_DB(mp, XFS_DIR2_DATAPTR_TO_BYTE(mp, dp))
macro_line|#endif
multiline_comment|/*&n; * Convert dataptr to a byte offset in a block&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DATAPTR_TO_OFF)
id|xfs_dir2_data_aoff_t
id|xfs_dir2_dataptr_to_off
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_dataptr_t
id|dp
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DATAPTR_TO_OFF
mdefine_line|#define&t;XFS_DIR2_DATAPTR_TO_OFF(mp,dp)&t;xfs_dir2_dataptr_to_off(mp, dp)
macro_line|#else
DECL|macro|XFS_DIR2_DATAPTR_TO_OFF
mdefine_line|#define&t;XFS_DIR2_DATAPTR_TO_OFF(mp,dp)&t;&bslash;&n;&t;XFS_DIR2_BYTE_TO_OFF(mp, XFS_DIR2_DATAPTR_TO_BYTE(mp, dp))
macro_line|#endif
multiline_comment|/*&n; * Convert block and offset to byte in space&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DB_OFF_TO_BYTE)
id|xfs_dir2_off_t
id|xfs_dir2_db_off_to_byte
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_db_t
id|db
comma
id|xfs_dir2_data_aoff_t
id|o
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DB_OFF_TO_BYTE
mdefine_line|#define&t;XFS_DIR2_DB_OFF_TO_BYTE(mp,db,o)&t;&bslash;&n;&t;xfs_dir2_db_off_to_byte(mp, db, o)
macro_line|#else
DECL|macro|XFS_DIR2_DB_OFF_TO_BYTE
mdefine_line|#define&t;XFS_DIR2_DB_OFF_TO_BYTE(mp,db,o)&t;&bslash;&n;&t;(((xfs_dir2_off_t)(db) &lt;&lt; &bslash;&n;&t; ((mp)-&gt;m_sb.sb_blocklog + (mp)-&gt;m_sb.sb_dirblklog)) + (o))
macro_line|#endif
multiline_comment|/*&n; * Convert byte in space to (DB) block&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_BYTE_TO_DB)
id|xfs_dir2_db_t
id|xfs_dir2_byte_to_db
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_off_t
id|by
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_BYTE_TO_DB
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_DB(mp,by)&t;xfs_dir2_byte_to_db(mp, by)
macro_line|#else
DECL|macro|XFS_DIR2_BYTE_TO_DB
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_DB(mp,by)&t;&bslash;&n;&t;((xfs_dir2_db_t)((by) &gt;&gt; &bslash;&n;&t;&t;&t; ((mp)-&gt;m_sb.sb_blocklog + (mp)-&gt;m_sb.sb_dirblklog)))
macro_line|#endif
multiline_comment|/*&n; * Convert byte in space to (DA) block&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_BYTE_TO_DA)
id|xfs_dablk_t
id|xfs_dir2_byte_to_da
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_off_t
id|by
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_BYTE_TO_DA
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_DA(mp,by)&t;xfs_dir2_byte_to_da(mp, by)
macro_line|#else
DECL|macro|XFS_DIR2_BYTE_TO_DA
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_DA(mp,by)&t;&bslash;&n;&t;XFS_DIR2_DB_TO_DA(mp, XFS_DIR2_BYTE_TO_DB(mp, by))
macro_line|#endif
multiline_comment|/*&n; * Convert byte in space to offset in a block&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_BYTE_TO_OFF)
id|xfs_dir2_data_aoff_t
id|xfs_dir2_byte_to_off
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_off_t
id|by
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_BYTE_TO_OFF
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_OFF(mp,by)&t;xfs_dir2_byte_to_off(mp, by)
macro_line|#else
DECL|macro|XFS_DIR2_BYTE_TO_OFF
mdefine_line|#define&t;XFS_DIR2_BYTE_TO_OFF(mp,by)&t;&bslash;&n;&t;((xfs_dir2_data_aoff_t)((by) &amp; &bslash;&n;&t;&t;&t;&t;((1 &lt;&lt; ((mp)-&gt;m_sb.sb_blocklog + &bslash;&n;&t;&t;&t;&t;&t;(mp)-&gt;m_sb.sb_dirblklog)) - 1)))
macro_line|#endif
multiline_comment|/*&n; * Convert block and offset to dataptr&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DB_OFF_TO_DATAPTR)
id|xfs_dir2_dataptr_t
id|xfs_dir2_db_off_to_dataptr
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dir2_db_t
id|db
comma
id|xfs_dir2_data_aoff_t
id|o
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DB_OFF_TO_DATAPTR
mdefine_line|#define&t;XFS_DIR2_DB_OFF_TO_DATAPTR(mp,db,o)&t;&bslash;&n;&t;xfs_dir2_db_off_to_dataptr(mp, db, o)
macro_line|#else
DECL|macro|XFS_DIR2_DB_OFF_TO_DATAPTR
mdefine_line|#define&t;XFS_DIR2_DB_OFF_TO_DATAPTR(mp,db,o)&t;&bslash;&n;&t;XFS_DIR2_BYTE_TO_DATAPTR(mp, XFS_DIR2_DB_OFF_TO_BYTE(mp, db, o))
macro_line|#endif
multiline_comment|/*&n; * Convert block (DB) to block (dablk)&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DB_TO_DA)
id|xfs_dablk_t
id|xfs_dir2_db_to_da
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
DECL|macro|XFS_DIR2_DB_TO_DA
mdefine_line|#define&t;XFS_DIR2_DB_TO_DA(mp,db)&t;xfs_dir2_db_to_da(mp, db)
macro_line|#else
DECL|macro|XFS_DIR2_DB_TO_DA
mdefine_line|#define&t;XFS_DIR2_DB_TO_DA(mp,db)&t;&bslash;&n;&t;((xfs_dablk_t)((db) &lt;&lt; (mp)-&gt;m_sb.sb_dirblklog))
macro_line|#endif
multiline_comment|/*&n; * Convert block (dablk) to block (DB)&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DA_TO_DB)
id|xfs_dir2_db_t
id|xfs_dir2_da_to_db
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dablk_t
id|da
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DA_TO_DB
mdefine_line|#define&t;XFS_DIR2_DA_TO_DB(mp,da)&t;xfs_dir2_da_to_db(mp, da)
macro_line|#else
DECL|macro|XFS_DIR2_DA_TO_DB
mdefine_line|#define&t;XFS_DIR2_DA_TO_DB(mp,da)&t;&bslash;&n;&t;((xfs_dir2_db_t)((da) &gt;&gt; (mp)-&gt;m_sb.sb_dirblklog))
macro_line|#endif
multiline_comment|/*&n; * Convert block (dablk) to byte offset in space&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_DA_TO_BYTE)
id|xfs_dir2_off_t
id|xfs_dir2_da_to_byte
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dablk_t
id|da
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_DA_TO_BYTE
mdefine_line|#define XFS_DIR2_DA_TO_BYTE(mp,da)&t;xfs_dir2_da_to_byte(mp, da)
macro_line|#else
DECL|macro|XFS_DIR2_DA_TO_BYTE
mdefine_line|#define&t;XFS_DIR2_DA_TO_BYTE(mp,da)&t;&bslash;&n;&t;XFS_DIR2_DB_OFF_TO_BYTE(mp, XFS_DIR2_DA_TO_DB(mp, da), 0)
macro_line|#endif
multiline_comment|/*&n; * Function declarations.&n; */
r_extern
r_int
id|xfs_dir2_block_to_leaf
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
id|dbp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leaf_addname
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_leaf_compact
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
id|bp
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_leaf_compact_x1
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|bp
comma
r_int
op_star
id|indexp
comma
r_int
op_star
id|lowstalep
comma
r_int
op_star
id|highstalep
comma
r_int
op_star
id|lowlogp
comma
r_int
op_star
id|highlogp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leaf_getdents
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
id|xfs_dir2_leaf_init
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_dir2_db_t
id|bno
comma
r_struct
id|xfs_dabuf
op_star
op_star
id|bpp
comma
r_int
id|magic
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_leaf_log_ents
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
r_void
id|xfs_dir2_leaf_log_bests
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
r_void
id|xfs_dir2_leaf_log_header
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
)paren
suffix:semicolon
r_extern
r_void
id|xfs_dir2_leaf_log_tail
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
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_leaf_lookup
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
id|xfs_dir2_leaf_removename
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
id|xfs_dir2_leaf_replace
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
id|xfs_dir2_leaf_search_hash
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
r_int
id|xfs_dir2_leaf_trim_data
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
id|xfs_dir2_db_t
id|db
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_node_to_leaf
c_func
(paren
r_struct
id|xfs_da_state
op_star
id|state
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_DIR2_LEAF_H__ */
eof
