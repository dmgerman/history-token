multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_IALLOC_BTREE_H__
DECL|macro|__XFS_IALLOC_BTREE_H__
mdefine_line|#define __XFS_IALLOC_BTREE_H__
multiline_comment|/*&n; * Inode map on-disk structures&n; */
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_btree_cur
suffix:semicolon
r_struct
id|xfs_btree_sblock
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
multiline_comment|/*&n; * There is a btree for the inode map per allocation group.&n; */
DECL|macro|XFS_IBT_MAGIC
mdefine_line|#define XFS_IBT_MAGIC&t;0x49414254&t;/* &squot;IABT&squot; */
DECL|typedef|xfs_inofree_t
r_typedef
id|__uint64_t
id|xfs_inofree_t
suffix:semicolon
DECL|macro|XFS_INODES_PER_CHUNK
mdefine_line|#define XFS_INODES_PER_CHUNK&t;(NBBY * sizeof(xfs_inofree_t))
DECL|macro|XFS_INODES_PER_CHUNK_LOG
mdefine_line|#define XFS_INODES_PER_CHUNK_LOG&t;(XFS_NBBYLOG + 3)
DECL|macro|XFS_INOBT_ALL_FREE
mdefine_line|#define XFS_INOBT_ALL_FREE&t;((xfs_inofree_t)-1)
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_MASKN)
id|xfs_inofree_t
id|xfs_inobt_maskn
c_func
(paren
r_int
id|i
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_MASKN
mdefine_line|#define XFS_INOBT_MASKN(i,n)&t;&t;xfs_inobt_maskn(i,n)
macro_line|#else
DECL|macro|XFS_INOBT_MASKN
mdefine_line|#define XFS_INOBT_MASKN(i,n)&t;&bslash;&n;&t;((((n) &gt;= XFS_INODES_PER_CHUNK ? &bslash;&n;&t;&t;(xfs_inofree_t)0 : ((xfs_inofree_t)1 &lt;&lt; (n))) - 1) &lt;&lt; (i))
macro_line|#endif
multiline_comment|/*&n; * Data record structure&n; */
DECL|struct|xfs_inobt_rec
r_typedef
r_struct
id|xfs_inobt_rec
(brace
DECL|member|ir_startino
id|xfs_agino_t
id|ir_startino
suffix:semicolon
multiline_comment|/* starting inode number */
DECL|member|ir_freecount
id|__int32_t
id|ir_freecount
suffix:semicolon
multiline_comment|/* count of free inodes (set bits) */
DECL|member|ir_free
id|xfs_inofree_t
id|ir_free
suffix:semicolon
multiline_comment|/* free inode mask */
DECL|typedef|xfs_inobt_rec_t
)brace
id|xfs_inobt_rec_t
suffix:semicolon
multiline_comment|/*&n; * Key structure&n; */
DECL|struct|xfs_inobt_key
r_typedef
r_struct
id|xfs_inobt_key
(brace
DECL|member|ir_startino
id|xfs_agino_t
id|ir_startino
suffix:semicolon
multiline_comment|/* starting inode number */
DECL|typedef|xfs_inobt_key_t
)brace
id|xfs_inobt_key_t
suffix:semicolon
DECL|typedef|xfs_inobt_ptr_t
r_typedef
id|xfs_agblock_t
id|xfs_inobt_ptr_t
suffix:semicolon
multiline_comment|/* btree pointer type */
multiline_comment|/* btree block header type */
DECL|typedef|xfs_inobt_block_t
r_typedef
r_struct
id|xfs_btree_sblock
id|xfs_inobt_block_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_INOBT_BLOCK)
id|xfs_inobt_block_t
op_star
id|xfs_buf_to_inobt_block
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_INOBT_BLOCK
mdefine_line|#define XFS_BUF_TO_INOBT_BLOCK(bp)&t;xfs_buf_to_inobt_block(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_INOBT_BLOCK
mdefine_line|#define XFS_BUF_TO_INOBT_BLOCK(bp) ((xfs_inobt_block_t *)(XFS_BUF_PTR(bp)))
macro_line|#endif
multiline_comment|/*&n; * Bit manipulations for ir_free.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_MASK)
id|xfs_inofree_t
id|xfs_inobt_mask
c_func
(paren
r_int
id|i
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_MASK
mdefine_line|#define XFS_INOBT_MASK(i)&t;&t;xfs_inobt_mask(i)
macro_line|#else
DECL|macro|XFS_INOBT_MASK
mdefine_line|#define XFS_INOBT_MASK(i)&t;&t;((xfs_inofree_t)1 &lt;&lt; (i))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_IS_FREE)
r_int
id|xfs_inobt_is_free
c_func
(paren
id|xfs_inobt_rec_t
op_star
id|rp
comma
r_int
id|i
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_IS_FREE
mdefine_line|#define XFS_INOBT_IS_FREE(rp,i,arch)&t;xfs_inobt_is_free(rp,i,arch)
macro_line|#else
DECL|macro|XFS_INOBT_IS_FREE
mdefine_line|#define XFS_INOBT_IS_FREE(rp,i,arch)&t;((INT_GET((rp)-&gt;ir_free, arch) &bslash;&n;&t;&t;&t;&t;&t; &amp; XFS_INOBT_MASK(i)) != 0)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_SET_FREE)
r_void
id|xfs_inobt_set_free
c_func
(paren
id|xfs_inobt_rec_t
op_star
id|rp
comma
r_int
id|i
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_SET_FREE
mdefine_line|#define XFS_INOBT_SET_FREE(rp,i,arch)&t;xfs_inobt_set_free(rp,i,arch)
macro_line|#else
DECL|macro|XFS_INOBT_SET_FREE
mdefine_line|#define XFS_INOBT_SET_FREE(rp,i,arch)&t;(INT_MOD_EXPR((rp)-&gt;ir_free, arch, |= XFS_INOBT_MASK(i)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_CLR_FREE)
r_void
id|xfs_inobt_clr_free
c_func
(paren
id|xfs_inobt_rec_t
op_star
id|rp
comma
r_int
id|i
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_CLR_FREE
mdefine_line|#define XFS_INOBT_CLR_FREE(rp,i,arch)&t;xfs_inobt_clr_free(rp,i,arch)
macro_line|#else
DECL|macro|XFS_INOBT_CLR_FREE
mdefine_line|#define XFS_INOBT_CLR_FREE(rp,i,arch)&t;(INT_MOD_EXPR((rp)-&gt;ir_free, arch, &amp;= ~XFS_INOBT_MASK(i)))
macro_line|#endif
multiline_comment|/*&n; * Real block structures have a size equal to the disk block size.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_BLOCK_SIZE)
r_int
id|xfs_inobt_block_size
c_func
(paren
r_int
id|lev
comma
r_struct
id|xfs_btree_cur
op_star
id|cur
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_BLOCK_SIZE
mdefine_line|#define XFS_INOBT_BLOCK_SIZE(lev,cur)&t;xfs_inobt_block_size(lev,cur)
macro_line|#else
DECL|macro|XFS_INOBT_BLOCK_SIZE
mdefine_line|#define XFS_INOBT_BLOCK_SIZE(lev,cur)&t;(1 &lt;&lt; (cur)-&gt;bc_blocklog)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_BLOCK_MAXRECS)
r_int
id|xfs_inobt_block_maxrecs
c_func
(paren
r_int
id|lev
comma
r_struct
id|xfs_btree_cur
op_star
id|cur
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_BLOCK_MAXRECS
mdefine_line|#define XFS_INOBT_BLOCK_MAXRECS(lev,cur)&t;xfs_inobt_block_maxrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_INOBT_BLOCK_MAXRECS
mdefine_line|#define XFS_INOBT_BLOCK_MAXRECS(lev,cur)&t;&bslash;&n;&t;((cur)-&gt;bc_mp-&gt;m_inobt_mxr[lev != 0])
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_BLOCK_MINRECS)
r_int
id|xfs_inobt_block_minrecs
c_func
(paren
r_int
id|lev
comma
r_struct
id|xfs_btree_cur
op_star
id|cur
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_BLOCK_MINRECS
mdefine_line|#define XFS_INOBT_BLOCK_MINRECS(lev,cur)&t;xfs_inobt_block_minrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_INOBT_BLOCK_MINRECS
mdefine_line|#define XFS_INOBT_BLOCK_MINRECS(lev,cur)&t;&bslash;&n;&t;((cur)-&gt;bc_mp-&gt;m_inobt_mnr[lev != 0])
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_IS_LAST_REC)
r_int
id|xfs_inobt_is_last_rec
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_IS_LAST_REC
mdefine_line|#define XFS_INOBT_IS_LAST_REC(cur)&t;xfs_inobt_is_last_rec(cur)
macro_line|#else
DECL|macro|XFS_INOBT_IS_LAST_REC
mdefine_line|#define XFS_INOBT_IS_LAST_REC(cur)&t;&bslash;&n;&t;((cur)-&gt;bc_ptrs[0] == &bslash;&n;&t;&t;INT_GET(XFS_BUF_TO_INOBT_BLOCK((cur)-&gt;bc_bufs[0])-&gt;bb_numrecs, ARCH_CONVERT))
macro_line|#endif
multiline_comment|/*&n; * Maximum number of inode btree levels.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IN_MAXLEVELS)
r_int
id|xfs_in_maxlevels
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_IN_MAXLEVELS
mdefine_line|#define XFS_IN_MAXLEVELS(mp)&t;&t;xfs_in_maxlevels(mp)
macro_line|#else
DECL|macro|XFS_IN_MAXLEVELS
mdefine_line|#define XFS_IN_MAXLEVELS(mp)&t;&t;((mp)-&gt;m_in_maxlevels)
macro_line|#endif
multiline_comment|/*&n; * block numbers in the AG.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IBT_BLOCK)
id|xfs_agblock_t
id|xfs_ibt_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_IBT_BLOCK
mdefine_line|#define XFS_IBT_BLOCK(mp)&t;&t;xfs_ibt_block(mp)
macro_line|#else
DECL|macro|XFS_IBT_BLOCK
mdefine_line|#define XFS_IBT_BLOCK(mp)&t;((xfs_agblock_t)(XFS_CNT_BLOCK(mp) + 1))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_PREALLOC_BLOCKS)
id|xfs_agblock_t
id|xfs_prealloc_blocks
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_PREALLOC_BLOCKS
mdefine_line|#define XFS_PREALLOC_BLOCKS(mp)&t;&t;xfs_prealloc_blocks(mp)
macro_line|#else
DECL|macro|XFS_PREALLOC_BLOCKS
mdefine_line|#define XFS_PREALLOC_BLOCKS(mp) ((xfs_agblock_t)(XFS_IBT_BLOCK(mp) + 1))
macro_line|#endif
multiline_comment|/*&n; * Record, key, and pointer address macros for btree blocks.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_REC_ADDR)
id|xfs_inobt_rec_t
op_star
id|xfs_inobt_rec_addr
c_func
(paren
id|xfs_inobt_block_t
op_star
id|bb
comma
r_int
id|i
comma
r_struct
id|xfs_btree_cur
op_star
id|cur
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_REC_ADDR
mdefine_line|#define XFS_INOBT_REC_ADDR(bb,i,cur)&t;xfs_inobt_rec_addr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_INOBT_REC_ADDR
mdefine_line|#define XFS_INOBT_REC_ADDR(bb,i,cur)&t;&bslash;&n;&t;XFS_BTREE_REC_ADDR(XFS_INOBT_BLOCK_SIZE(0,cur), xfs_inobt, bb, i, &bslash;&n;&t;&t;XFS_INOBT_BLOCK_MAXRECS(0, cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_KEY_ADDR)
id|xfs_inobt_key_t
op_star
id|xfs_inobt_key_addr
c_func
(paren
id|xfs_inobt_block_t
op_star
id|bb
comma
r_int
id|i
comma
r_struct
id|xfs_btree_cur
op_star
id|cur
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_KEY_ADDR
mdefine_line|#define XFS_INOBT_KEY_ADDR(bb,i,cur)&t;xfs_inobt_key_addr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_INOBT_KEY_ADDR
mdefine_line|#define XFS_INOBT_KEY_ADDR(bb,i,cur)&t;&bslash;&n;&t;XFS_BTREE_KEY_ADDR(XFS_INOBT_BLOCK_SIZE(1,cur), xfs_inobt, bb, i, &bslash;&n;&t;&t;XFS_INOBT_BLOCK_MAXRECS(1, cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_INOBT_PTR_ADDR)
id|xfs_inobt_ptr_t
op_star
id|xfs_inobt_ptr_addr
c_func
(paren
id|xfs_inobt_block_t
op_star
id|bb
comma
r_int
id|i
comma
r_struct
id|xfs_btree_cur
op_star
id|cur
)paren
suffix:semicolon
DECL|macro|XFS_INOBT_PTR_ADDR
mdefine_line|#define XFS_INOBT_PTR_ADDR(bb,i,cur)&t;xfs_inobt_ptr_addr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_INOBT_PTR_ADDR
mdefine_line|#define XFS_INOBT_PTR_ADDR(bb,i,cur)&t;&bslash;&n;&t;XFS_BTREE_PTR_ADDR(XFS_INOBT_BLOCK_SIZE(1,cur), xfs_inobt, bb, i, &bslash;&n;&t;&t;XFS_INOBT_BLOCK_MAXRECS(1, cur))
macro_line|#endif
multiline_comment|/*&n; * Prototypes for externally visible routines.&n; */
multiline_comment|/*&n; * Decrement cursor by one record at the level.&n; * For nonzero levels the leaf-ward information is untouched.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_decrement
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|level
comma
multiline_comment|/* level in btree, 0 is leaf */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
macro_line|#ifdef _NOTYET_
multiline_comment|/*&n; * Delete the record pointed to by cur.&n; * The cursor refers to the place where the record was (could be inserted)&n; * when the operation returns.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_delete
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
macro_line|#endif&t;/* _NOTYET_ */
multiline_comment|/*&n; * Get the data from the pointed-to record.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_get_rec
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agino_t
op_star
id|ino
comma
multiline_comment|/* output: starting inode of chunk */
id|__int32_t
op_star
id|fcnt
comma
multiline_comment|/* output: number of free inodes */
id|xfs_inofree_t
op_star
id|free
comma
multiline_comment|/* output: free inode mask */
r_int
op_star
id|stat
comma
multiline_comment|/* output: success/failure */
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
multiline_comment|/* output: architecture */
multiline_comment|/*&n; * Increment cursor by one record at the level.&n; * For nonzero levels the leaf-ward information is untouched.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_increment
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|level
comma
multiline_comment|/* level in btree, 0 is leaf */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Insert the current record at the point referenced by cur.&n; * The cursor may be inconsistent on return if splits have been done.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_insert
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Lookup the record equal to ino in the btree given by cur.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_lookup_eq
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agino_t
id|ino
comma
multiline_comment|/* starting inode of chunk */
id|__int32_t
id|fcnt
comma
multiline_comment|/* free inode count */
id|xfs_inofree_t
id|free
comma
multiline_comment|/* free inode mask */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Lookup the first record greater than or equal to ino&n; * in the btree given by cur.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_lookup_ge
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agino_t
id|ino
comma
multiline_comment|/* starting inode of chunk */
id|__int32_t
id|fcnt
comma
multiline_comment|/* free inode count */
id|xfs_inofree_t
id|free
comma
multiline_comment|/* free inode mask */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Lookup the first record less than or equal to ino&n; * in the btree given by cur.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_lookup_le
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agino_t
id|ino
comma
multiline_comment|/* starting inode of chunk */
id|__int32_t
id|fcnt
comma
multiline_comment|/* free inode count */
id|xfs_inofree_t
id|free
comma
multiline_comment|/* free inode mask */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Update the record referred to by cur, to the value given&n; * by [ino, fcnt, free].&n; * This either works (return 0) or gets an EFSCORRUPTED error.&n; */
r_int
multiline_comment|/* error */
id|xfs_inobt_update
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agino_t
id|ino
comma
multiline_comment|/* starting inode of chunk */
id|__int32_t
id|fcnt
comma
multiline_comment|/* free inode count */
id|xfs_inofree_t
id|free
)paren
suffix:semicolon
multiline_comment|/* free inode mask */
macro_line|#endif&t;/* __XFS_IALLOC_BTREE_H__ */
eof
