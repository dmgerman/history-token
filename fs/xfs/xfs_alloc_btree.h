multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ALLOC_BTREE_H__
DECL|macro|__XFS_ALLOC_BTREE_H__
mdefine_line|#define __XFS_ALLOC_BTREE_H__
multiline_comment|/*&n; * Freespace on-disk structures&n; */
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
multiline_comment|/*&n; * There are two on-disk btrees, one sorted by blockno and one sorted&n; * by blockcount and blockno.  All blocks look the same to make the code&n; * simpler; if we have time later, we&squot;ll make the optimizations.&n; */
DECL|macro|XFS_ABTB_MAGIC
mdefine_line|#define XFS_ABTB_MAGIC&t;0x41425442&t;/* &squot;ABTB&squot; for bno tree */
DECL|macro|XFS_ABTC_MAGIC
mdefine_line|#define XFS_ABTC_MAGIC&t;0x41425443&t;/* &squot;ABTC&squot; for cnt tree */
multiline_comment|/*&n; * Data record/key structure&n; */
DECL|struct|xfs_alloc_rec
r_typedef
r_struct
id|xfs_alloc_rec
(brace
DECL|member|ar_startblock
id|xfs_agblock_t
id|ar_startblock
suffix:semicolon
multiline_comment|/* starting block number */
DECL|member|ar_blockcount
id|xfs_extlen_t
id|ar_blockcount
suffix:semicolon
multiline_comment|/* count of free blocks */
DECL|typedef|xfs_alloc_rec_t
DECL|typedef|xfs_alloc_key_t
)brace
id|xfs_alloc_rec_t
comma
id|xfs_alloc_key_t
suffix:semicolon
DECL|typedef|xfs_alloc_ptr_t
r_typedef
id|xfs_agblock_t
id|xfs_alloc_ptr_t
suffix:semicolon
multiline_comment|/* btree pointer type */
multiline_comment|/* btree block header type */
DECL|typedef|xfs_alloc_block_t
r_typedef
r_struct
id|xfs_btree_sblock
id|xfs_alloc_block_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_ALLOC_BLOCK)
id|xfs_alloc_block_t
op_star
id|xfs_buf_to_alloc_block
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_ALLOC_BLOCK
mdefine_line|#define XFS_BUF_TO_ALLOC_BLOCK(bp)&t;xfs_buf_to_alloc_block(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_ALLOC_BLOCK
mdefine_line|#define XFS_BUF_TO_ALLOC_BLOCK(bp) ((xfs_alloc_block_t *)(XFS_BUF_PTR(bp)))
macro_line|#endif
multiline_comment|/*&n; * Real block structures have a size equal to the disk block size.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ALLOC_BLOCK_SIZE)
r_int
id|xfs_alloc_block_size
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
DECL|macro|XFS_ALLOC_BLOCK_SIZE
mdefine_line|#define XFS_ALLOC_BLOCK_SIZE(lev,cur)&t;xfs_alloc_block_size(lev,cur)
macro_line|#else
DECL|macro|XFS_ALLOC_BLOCK_SIZE
mdefine_line|#define XFS_ALLOC_BLOCK_SIZE(lev,cur)&t;(1 &lt;&lt; (cur)-&gt;bc_blocklog)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ALLOC_BLOCK_MAXRECS)
r_int
id|xfs_alloc_block_maxrecs
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
DECL|macro|XFS_ALLOC_BLOCK_MAXRECS
mdefine_line|#define XFS_ALLOC_BLOCK_MAXRECS(lev,cur)&t;xfs_alloc_block_maxrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_ALLOC_BLOCK_MAXRECS
mdefine_line|#define XFS_ALLOC_BLOCK_MAXRECS(lev,cur)&t;&bslash;&n;&t;((cur)-&gt;bc_mp-&gt;m_alloc_mxr[lev != 0])
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ALLOC_BLOCK_MINRECS)
r_int
id|xfs_alloc_block_minrecs
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
DECL|macro|XFS_ALLOC_BLOCK_MINRECS
mdefine_line|#define XFS_ALLOC_BLOCK_MINRECS(lev,cur)&t;xfs_alloc_block_minrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_ALLOC_BLOCK_MINRECS
mdefine_line|#define XFS_ALLOC_BLOCK_MINRECS(lev,cur)&t;&bslash;&n;&t;((cur)-&gt;bc_mp-&gt;m_alloc_mnr[lev != 0])
macro_line|#endif
multiline_comment|/*&n; * Minimum and maximum blocksize.&n; * The blocksize upper limit is pretty much arbitrary.&n; */
DECL|macro|XFS_MIN_BLOCKSIZE_LOG
mdefine_line|#define XFS_MIN_BLOCKSIZE_LOG&t;9&t;/* i.e. 512 bytes */
DECL|macro|XFS_MAX_BLOCKSIZE_LOG
mdefine_line|#define XFS_MAX_BLOCKSIZE_LOG&t;16&t;/* i.e. 65536 bytes */
DECL|macro|XFS_MIN_BLOCKSIZE
mdefine_line|#define XFS_MIN_BLOCKSIZE&t;(1 &lt;&lt; XFS_MIN_BLOCKSIZE_LOG)
DECL|macro|XFS_MAX_BLOCKSIZE
mdefine_line|#define XFS_MAX_BLOCKSIZE&t;(1 &lt;&lt; XFS_MAX_BLOCKSIZE_LOG)
multiline_comment|/*&n; * block numbers in the AG; SB is BB 0, AGF is BB 1, AGI is BB 2, AGFL is BB 3&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BNO_BLOCK)
id|xfs_agblock_t
id|xfs_bno_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_BNO_BLOCK
mdefine_line|#define XFS_BNO_BLOCK(mp)&t;xfs_bno_block(mp)
macro_line|#else
DECL|macro|XFS_BNO_BLOCK
mdefine_line|#define XFS_BNO_BLOCK(mp)&t;((xfs_agblock_t)(XFS_AGFL_BLOCK(mp) + 1))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_CNT_BLOCK)
id|xfs_agblock_t
id|xfs_cnt_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_CNT_BLOCK
mdefine_line|#define XFS_CNT_BLOCK(mp)&t;xfs_cnt_block(mp)
macro_line|#else
DECL|macro|XFS_CNT_BLOCK
mdefine_line|#define XFS_CNT_BLOCK(mp)&t;((xfs_agblock_t)(XFS_BNO_BLOCK(mp) + 1))
macro_line|#endif
multiline_comment|/*&n; * Record, key, and pointer address macros for btree blocks.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ALLOC_REC_ADDR)
id|xfs_alloc_rec_t
op_star
id|xfs_alloc_rec_addr
c_func
(paren
id|xfs_alloc_block_t
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
DECL|macro|XFS_ALLOC_REC_ADDR
mdefine_line|#define XFS_ALLOC_REC_ADDR(bb,i,cur)&t;xfs_alloc_rec_addr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_ALLOC_REC_ADDR
mdefine_line|#define XFS_ALLOC_REC_ADDR(bb,i,cur)&t;&bslash;&n;&t;XFS_BTREE_REC_ADDR(XFS_ALLOC_BLOCK_SIZE(0,cur), xfs_alloc, bb, i, &bslash;&n;&t;&t;XFS_ALLOC_BLOCK_MAXRECS(0, cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ALLOC_KEY_ADDR)
id|xfs_alloc_key_t
op_star
id|xfs_alloc_key_addr
c_func
(paren
id|xfs_alloc_block_t
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
DECL|macro|XFS_ALLOC_KEY_ADDR
mdefine_line|#define XFS_ALLOC_KEY_ADDR(bb,i,cur)&t;xfs_alloc_key_addr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_ALLOC_KEY_ADDR
mdefine_line|#define XFS_ALLOC_KEY_ADDR(bb,i,cur)&t;&bslash;&n;&t;XFS_BTREE_KEY_ADDR(XFS_ALLOC_BLOCK_SIZE(1,cur), xfs_alloc, bb, i, &bslash;&n;&t;&t;XFS_ALLOC_BLOCK_MAXRECS(1, cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_ALLOC_PTR_ADDR)
id|xfs_alloc_ptr_t
op_star
id|xfs_alloc_ptr_addr
c_func
(paren
id|xfs_alloc_block_t
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
DECL|macro|XFS_ALLOC_PTR_ADDR
mdefine_line|#define XFS_ALLOC_PTR_ADDR(bb,i,cur)&t;xfs_alloc_ptr_addr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_ALLOC_PTR_ADDR
mdefine_line|#define XFS_ALLOC_PTR_ADDR(bb,i,cur)&t;&bslash;&n;&t;XFS_BTREE_PTR_ADDR(XFS_ALLOC_BLOCK_SIZE(1,cur), xfs_alloc, bb, i, &bslash;&n;&t;&t;XFS_ALLOC_BLOCK_MAXRECS(1, cur))
macro_line|#endif
multiline_comment|/*&n; * Prototypes for externally visible routines.&n; */
multiline_comment|/*&n; * Decrement cursor by one record at the level.&n; * For nonzero levels the leaf-ward information is untouched.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_decrement
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
multiline_comment|/*&n; * Delete the record pointed to by cur.&n; * The cursor refers to the place where the record was (could be inserted)&n; * when the operation returns.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_delete
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
multiline_comment|/*&n; * Get the data from the pointed-to record.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_get_rec
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agblock_t
op_star
id|bno
comma
multiline_comment|/* output: starting block of extent */
id|xfs_extlen_t
op_star
id|len
comma
multiline_comment|/* output: length of extent */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* output: success/failure */
multiline_comment|/*&n; * Increment cursor by one record at the level.&n; * For nonzero levels the leaf-ward information is untouched.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_increment
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
id|xfs_alloc_insert
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
multiline_comment|/*&n; * Lookup the record equal to [bno, len] in the btree given by cur.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_lookup_eq
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agblock_t
id|bno
comma
multiline_comment|/* starting block of extent */
id|xfs_extlen_t
id|len
comma
multiline_comment|/* length of extent */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Lookup the first record greater than or equal to [bno, len]&n; * in the btree given by cur.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_lookup_ge
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agblock_t
id|bno
comma
multiline_comment|/* starting block of extent */
id|xfs_extlen_t
id|len
comma
multiline_comment|/* length of extent */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Lookup the first record less than or equal to [bno, len]&n; * in the btree given by cur.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_lookup_le
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agblock_t
id|bno
comma
multiline_comment|/* starting block of extent */
id|xfs_extlen_t
id|len
comma
multiline_comment|/* length of extent */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* success/failure */
multiline_comment|/*&n; * Update the record referred to by cur, to the value given by [bno, len].&n; * This either works (return 0) or gets an EFSCORRUPTED error.&n; */
r_int
multiline_comment|/* error */
id|xfs_alloc_update
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agblock_t
id|bno
comma
multiline_comment|/* starting block of extent */
id|xfs_extlen_t
id|len
)paren
suffix:semicolon
multiline_comment|/* length of extent */
macro_line|#endif&t;/* __XFS_ALLOC_BTREE_H__ */
eof
