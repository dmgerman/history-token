multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_BTREE_H__
DECL|macro|__XFS_BTREE_H__
mdefine_line|#define __XFS_BTREE_H__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_bmap_free
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
multiline_comment|/*&n; * This nonsense is to make -wlint happy.&n; */
DECL|macro|XFS_LOOKUP_EQ
mdefine_line|#define XFS_LOOKUP_EQ&t;((xfs_lookup_t)XFS_LOOKUP_EQi)
DECL|macro|XFS_LOOKUP_LE
mdefine_line|#define XFS_LOOKUP_LE&t;((xfs_lookup_t)XFS_LOOKUP_LEi)
DECL|macro|XFS_LOOKUP_GE
mdefine_line|#define XFS_LOOKUP_GE&t;((xfs_lookup_t)XFS_LOOKUP_GEi)
DECL|macro|XFS_BTNUM_BNO
mdefine_line|#define XFS_BTNUM_BNO&t;((xfs_btnum_t)XFS_BTNUM_BNOi)
DECL|macro|XFS_BTNUM_CNT
mdefine_line|#define XFS_BTNUM_CNT&t;((xfs_btnum_t)XFS_BTNUM_CNTi)
DECL|macro|XFS_BTNUM_BMAP
mdefine_line|#define XFS_BTNUM_BMAP&t;((xfs_btnum_t)XFS_BTNUM_BMAPi)
DECL|macro|XFS_BTNUM_INO
mdefine_line|#define XFS_BTNUM_INO&t;((xfs_btnum_t)XFS_BTNUM_INOi)
multiline_comment|/*&n; * Short form header: space allocation btrees.&n; */
DECL|struct|xfs_btree_sblock
r_typedef
r_struct
id|xfs_btree_sblock
(brace
DECL|member|bb_magic
id|__uint32_t
id|bb_magic
suffix:semicolon
multiline_comment|/* magic number for block type */
DECL|member|bb_level
id|__uint16_t
id|bb_level
suffix:semicolon
multiline_comment|/* 0 is a leaf */
DECL|member|bb_numrecs
id|__uint16_t
id|bb_numrecs
suffix:semicolon
multiline_comment|/* current # of data records */
DECL|member|bb_leftsib
id|xfs_agblock_t
id|bb_leftsib
suffix:semicolon
multiline_comment|/* left sibling block or NULLAGBLOCK */
DECL|member|bb_rightsib
id|xfs_agblock_t
id|bb_rightsib
suffix:semicolon
multiline_comment|/* right sibling block or NULLAGBLOCK */
DECL|typedef|xfs_btree_sblock_t
)brace
id|xfs_btree_sblock_t
suffix:semicolon
multiline_comment|/*&n; * Long form header: bmap btrees.&n; */
DECL|struct|xfs_btree_lblock
r_typedef
r_struct
id|xfs_btree_lblock
(brace
DECL|member|bb_magic
id|__uint32_t
id|bb_magic
suffix:semicolon
multiline_comment|/* magic number for block type */
DECL|member|bb_level
id|__uint16_t
id|bb_level
suffix:semicolon
multiline_comment|/* 0 is a leaf */
DECL|member|bb_numrecs
id|__uint16_t
id|bb_numrecs
suffix:semicolon
multiline_comment|/* current # of data records */
DECL|member|bb_leftsib
id|xfs_dfsbno_t
id|bb_leftsib
suffix:semicolon
multiline_comment|/* left sibling block or NULLDFSBNO */
DECL|member|bb_rightsib
id|xfs_dfsbno_t
id|bb_rightsib
suffix:semicolon
multiline_comment|/* right sibling block or NULLDFSBNO */
DECL|typedef|xfs_btree_lblock_t
)brace
id|xfs_btree_lblock_t
suffix:semicolon
multiline_comment|/*&n; * Combined header and structure, used by common code.&n; */
DECL|struct|xfs_btree_hdr
r_typedef
r_struct
id|xfs_btree_hdr
(brace
DECL|member|bb_magic
id|__uint32_t
id|bb_magic
suffix:semicolon
multiline_comment|/* magic number for block type */
DECL|member|bb_level
id|__uint16_t
id|bb_level
suffix:semicolon
multiline_comment|/* 0 is a leaf */
DECL|member|bb_numrecs
id|__uint16_t
id|bb_numrecs
suffix:semicolon
multiline_comment|/* current # of data records */
DECL|typedef|xfs_btree_hdr_t
)brace
id|xfs_btree_hdr_t
suffix:semicolon
DECL|struct|xfs_btree_block
r_typedef
r_struct
id|xfs_btree_block
(brace
DECL|member|bb_h
id|xfs_btree_hdr_t
id|bb_h
suffix:semicolon
multiline_comment|/* header */
r_union
(brace
r_struct
(brace
DECL|member|bb_leftsib
id|xfs_agblock_t
id|bb_leftsib
suffix:semicolon
DECL|member|bb_rightsib
id|xfs_agblock_t
id|bb_rightsib
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
multiline_comment|/* short form pointers */
r_struct
(brace
DECL|member|bb_leftsib
id|xfs_dfsbno_t
id|bb_leftsib
suffix:semicolon
DECL|member|bb_rightsib
id|xfs_dfsbno_t
id|bb_rightsib
suffix:semicolon
DECL|member|l
)brace
id|l
suffix:semicolon
multiline_comment|/* long form pointers */
DECL|member|bb_u
)brace
id|bb_u
suffix:semicolon
multiline_comment|/* rest */
DECL|typedef|xfs_btree_block_t
)brace
id|xfs_btree_block_t
suffix:semicolon
multiline_comment|/*&n; * For logging record fields.&n; */
DECL|macro|XFS_BB_MAGIC
mdefine_line|#define XFS_BB_MAGIC&t;&t;0x01
DECL|macro|XFS_BB_LEVEL
mdefine_line|#define XFS_BB_LEVEL&t;&t;0x02
DECL|macro|XFS_BB_NUMRECS
mdefine_line|#define XFS_BB_NUMRECS&t;&t;0x04
DECL|macro|XFS_BB_LEFTSIB
mdefine_line|#define XFS_BB_LEFTSIB&t;&t;0x08
DECL|macro|XFS_BB_RIGHTSIB
mdefine_line|#define XFS_BB_RIGHTSIB&t;&t;0x10
DECL|macro|XFS_BB_NUM_BITS
mdefine_line|#define XFS_BB_NUM_BITS&t;&t;5
DECL|macro|XFS_BB_ALL_BITS
mdefine_line|#define XFS_BB_ALL_BITS&t;&t;((1 &lt;&lt; XFS_BB_NUM_BITS) - 1)
multiline_comment|/*&n; * Boolean to select which form of xfs_btree_block_t.bb_u to use.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BTREE_LONG_PTRS)
r_int
id|xfs_btree_long_ptrs
c_func
(paren
id|xfs_btnum_t
id|btnum
)paren
suffix:semicolon
DECL|macro|XFS_BTREE_LONG_PTRS
mdefine_line|#define XFS_BTREE_LONG_PTRS(btnum)&t;((btnum) == XFS_BTNUM_BMAP)
macro_line|#else
DECL|macro|XFS_BTREE_LONG_PTRS
mdefine_line|#define XFS_BTREE_LONG_PTRS(btnum)&t;((btnum) == XFS_BTNUM_BMAP)
macro_line|#endif
multiline_comment|/*&n; * Magic numbers for btree blocks.&n; */
r_extern
r_const
id|__uint32_t
id|xfs_magics
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Maximum and minimum records in a btree block.&n; * Given block size, type prefix, and leaf flag (0 or 1).&n; * The divisor below is equivalent to lf ? (e1) : (e2) but that produces&n; * compiler warnings.&n; */
DECL|macro|XFS_BTREE_BLOCK_MAXRECS
mdefine_line|#define XFS_BTREE_BLOCK_MAXRECS(bsz,t,lf)&t;&bslash;&n;&t;((int)(((bsz) - (uint)sizeof(t ## _block_t)) / &bslash;&n;&t; (((lf) * (uint)sizeof(t ## _rec_t)) + &bslash;&n;&t;  ((1 - (lf)) * &bslash;&n;&t;   ((uint)sizeof(t ## _key_t) + (uint)sizeof(t ## _ptr_t))))))
DECL|macro|XFS_BTREE_BLOCK_MINRECS
mdefine_line|#define XFS_BTREE_BLOCK_MINRECS(bsz,t,lf)&t;&bslash;&n;&t;(XFS_BTREE_BLOCK_MAXRECS(bsz,t,lf) / 2)
multiline_comment|/*&n; * Record, key, and pointer address calculation macros.&n; * Given block size, type prefix, block pointer, and index of requested entry&n; * (first entry numbered 1).&n; */
DECL|macro|XFS_BTREE_REC_ADDR
mdefine_line|#define XFS_BTREE_REC_ADDR(bsz,t,bb,i,mxr)&t;&bslash;&n;&t;((t ## _rec_t *)((char *)(bb) + sizeof(t ## _block_t) + &bslash;&n;&t; ((i) - 1) * sizeof(t ## _rec_t)))
DECL|macro|XFS_BTREE_KEY_ADDR
mdefine_line|#define XFS_BTREE_KEY_ADDR(bsz,t,bb,i,mxr)&t;&bslash;&n;&t;((t ## _key_t *)((char *)(bb) + sizeof(t ## _block_t) + &bslash;&n;&t; ((i) - 1) * sizeof(t ## _key_t)))
DECL|macro|XFS_BTREE_PTR_ADDR
mdefine_line|#define XFS_BTREE_PTR_ADDR(bsz,t,bb,i,mxr)&t;&bslash;&n;&t;((t ## _ptr_t *)((char *)(bb) + sizeof(t ## _block_t) + &bslash;&n;&t; (mxr) * sizeof(t ## _key_t) + ((i) - 1) * sizeof(t ## _ptr_t)))
DECL|macro|XFS_BTREE_MAXLEVELS
mdefine_line|#define XFS_BTREE_MAXLEVELS&t;8&t;/* max of all btrees */
multiline_comment|/*&n; * Btree cursor structure.&n; * This collects all information needed by the btree code in one place.&n; */
DECL|struct|xfs_btree_cur
r_typedef
r_struct
id|xfs_btree_cur
(brace
DECL|member|bc_tp
r_struct
id|xfs_trans
op_star
id|bc_tp
suffix:semicolon
multiline_comment|/* transaction we&squot;re in, if any */
DECL|member|bc_mp
r_struct
id|xfs_mount
op_star
id|bc_mp
suffix:semicolon
multiline_comment|/* file system mount struct */
r_union
(brace
DECL|member|a
id|xfs_alloc_rec_t
id|a
suffix:semicolon
DECL|member|b
id|xfs_bmbt_irec_t
id|b
suffix:semicolon
DECL|member|i
id|xfs_inobt_rec_t
id|i
suffix:semicolon
DECL|member|bc_rec
)brace
id|bc_rec
suffix:semicolon
multiline_comment|/* current insert/search record value */
DECL|member|bc_bufs
r_struct
id|xfs_buf
op_star
id|bc_bufs
(braket
id|XFS_BTREE_MAXLEVELS
)braket
suffix:semicolon
multiline_comment|/* buf ptr per level */
DECL|member|bc_ptrs
r_int
id|bc_ptrs
(braket
id|XFS_BTREE_MAXLEVELS
)braket
suffix:semicolon
multiline_comment|/* key/record # */
DECL|member|bc_ra
id|__uint8_t
id|bc_ra
(braket
id|XFS_BTREE_MAXLEVELS
)braket
suffix:semicolon
multiline_comment|/* readahead bits */
DECL|macro|XFS_BTCUR_LEFTRA
mdefine_line|#define XFS_BTCUR_LEFTRA&t;1&t;/* left sibling has been read-ahead */
DECL|macro|XFS_BTCUR_RIGHTRA
mdefine_line|#define XFS_BTCUR_RIGHTRA&t;2&t;/* right sibling has been read-ahead */
DECL|member|bc_nlevels
id|__uint8_t
id|bc_nlevels
suffix:semicolon
multiline_comment|/* number of levels in the tree */
DECL|member|bc_blocklog
id|__uint8_t
id|bc_blocklog
suffix:semicolon
multiline_comment|/* log2(blocksize) of btree blocks */
DECL|member|bc_btnum
id|xfs_btnum_t
id|bc_btnum
suffix:semicolon
multiline_comment|/* identifies which btree type */
r_union
(brace
r_struct
(brace
multiline_comment|/* needed for BNO, CNT */
DECL|member|agbp
r_struct
id|xfs_buf
op_star
id|agbp
suffix:semicolon
multiline_comment|/* agf buffer pointer */
DECL|member|agno
id|xfs_agnumber_t
id|agno
suffix:semicolon
multiline_comment|/* ag number */
DECL|member|a
)brace
id|a
suffix:semicolon
r_struct
(brace
multiline_comment|/* needed for BMAP */
DECL|member|ip
r_struct
id|xfs_inode
op_star
id|ip
suffix:semicolon
multiline_comment|/* pointer to our inode */
DECL|member|flist
r_struct
id|xfs_bmap_free
op_star
id|flist
suffix:semicolon
multiline_comment|/* list to free after */
DECL|member|firstblock
id|xfs_fsblock_t
id|firstblock
suffix:semicolon
multiline_comment|/* 1st blk allocated */
DECL|member|allocated
r_int
id|allocated
suffix:semicolon
multiline_comment|/* count of alloced */
DECL|member|forksize
r_int
id|forksize
suffix:semicolon
multiline_comment|/* fork&squot;s inode space */
DECL|member|whichfork
r_char
id|whichfork
suffix:semicolon
multiline_comment|/* data or attr fork */
DECL|member|flags
r_char
id|flags
suffix:semicolon
multiline_comment|/* flags */
DECL|macro|XFS_BTCUR_BPRV_WASDEL
mdefine_line|#define XFS_BTCUR_BPRV_WASDEL&t;1&t;&t;&t;/* was delayed */
DECL|member|b
)brace
id|b
suffix:semicolon
r_struct
(brace
multiline_comment|/* needed for INO */
DECL|member|agbp
r_struct
id|xfs_buf
op_star
id|agbp
suffix:semicolon
multiline_comment|/* agi buffer pointer */
DECL|member|agno
id|xfs_agnumber_t
id|agno
suffix:semicolon
multiline_comment|/* ag number */
DECL|member|i
)brace
id|i
suffix:semicolon
DECL|member|bc_private
)brace
id|bc_private
suffix:semicolon
multiline_comment|/* per-btree type data */
DECL|typedef|xfs_btree_cur_t
)brace
id|xfs_btree_cur_t
suffix:semicolon
DECL|macro|XFS_BTREE_NOERROR
mdefine_line|#define XFS_BTREE_NOERROR&t;0
DECL|macro|XFS_BTREE_ERROR
mdefine_line|#define XFS_BTREE_ERROR&t;&t;1
multiline_comment|/*&n; * Convert from buffer to btree block header.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_BLOCK)
id|xfs_btree_block_t
op_star
id|xfs_buf_to_block
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_BLOCK
mdefine_line|#define XFS_BUF_TO_BLOCK(bp)&t;xfs_buf_to_block(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_BLOCK
mdefine_line|#define XFS_BUF_TO_BLOCK(bp)&t;((xfs_btree_block_t *)(XFS_BUF_PTR(bp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_LBLOCK)
id|xfs_btree_lblock_t
op_star
id|xfs_buf_to_lblock
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_LBLOCK
mdefine_line|#define XFS_BUF_TO_LBLOCK(bp)&t;xfs_buf_to_lblock(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_LBLOCK
mdefine_line|#define XFS_BUF_TO_LBLOCK(bp)&t;((xfs_btree_lblock_t *)(XFS_BUF_PTR(bp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_SBLOCK)
id|xfs_btree_sblock_t
op_star
id|xfs_buf_to_sblock
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_SBLOCK
mdefine_line|#define XFS_BUF_TO_SBLOCK(bp)&t;xfs_buf_to_sblock(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_SBLOCK
mdefine_line|#define XFS_BUF_TO_SBLOCK(bp)&t;((xfs_btree_sblock_t *)(XFS_BUF_PTR(bp)))
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#ifdef DEBUG
multiline_comment|/*&n; * Debug routine: check that block header is ok.&n; */
r_void
id|xfs_btree_check_block
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_btree_block_t
op_star
id|block
comma
multiline_comment|/* generic btree block pointer */
r_int
id|level
comma
multiline_comment|/* level of the btree block */
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
multiline_comment|/* buffer containing block, if any */
multiline_comment|/*&n; * Debug routine: check that keys are in the right order.&n; */
r_void
id|xfs_btree_check_key
c_func
(paren
id|xfs_btnum_t
id|btnum
comma
multiline_comment|/* btree identifier */
r_void
op_star
id|ak1
comma
multiline_comment|/* pointer to left (lower) key */
r_void
op_star
id|ak2
)paren
suffix:semicolon
multiline_comment|/* pointer to right (higher) key */
multiline_comment|/*&n; * Debug routine: check that records are in the right order.&n; */
r_void
id|xfs_btree_check_rec
c_func
(paren
id|xfs_btnum_t
id|btnum
comma
multiline_comment|/* btree identifier */
r_void
op_star
id|ar1
comma
multiline_comment|/* pointer to left (lower) record */
r_void
op_star
id|ar2
)paren
suffix:semicolon
multiline_comment|/* pointer to right (higher) record */
macro_line|#else
DECL|macro|xfs_btree_check_block
mdefine_line|#define xfs_btree_check_block(a,b,c,d)
DECL|macro|xfs_btree_check_key
mdefine_line|#define xfs_btree_check_key(a,b,c)
DECL|macro|xfs_btree_check_rec
mdefine_line|#define xfs_btree_check_rec(a,b,c)
macro_line|#endif&t;/* DEBUG */
multiline_comment|/*&n; * Checking routine: check that long form block header is ok.&n; */
r_int
multiline_comment|/* error (0 or EFSCORRUPTED) */
id|xfs_btree_check_lblock
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_btree_lblock_t
op_star
id|block
comma
multiline_comment|/* btree long form block pointer */
r_int
id|level
comma
multiline_comment|/* level of the btree block */
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
multiline_comment|/* buffer containing block, if any */
multiline_comment|/*&n; * Checking routine: check that (long) pointer is ok.&n; */
r_int
multiline_comment|/* error (0 or EFSCORRUPTED) */
id|xfs_btree_check_lptr
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_dfsbno_t
id|ptr
comma
multiline_comment|/* btree block disk address */
r_int
id|level
)paren
suffix:semicolon
multiline_comment|/* btree block level */
multiline_comment|/*&n; * Checking routine: check that short form block header is ok.&n; */
r_int
multiline_comment|/* error (0 or EFSCORRUPTED) */
id|xfs_btree_check_sblock
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_btree_sblock_t
op_star
id|block
comma
multiline_comment|/* btree short form block pointer */
r_int
id|level
comma
multiline_comment|/* level of the btree block */
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
multiline_comment|/* buffer containing block */
multiline_comment|/*&n; * Checking routine: check that (short) pointer is ok.&n; */
r_int
multiline_comment|/* error (0 or EFSCORRUPTED) */
id|xfs_btree_check_sptr
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
id|xfs_agblock_t
id|ptr
comma
multiline_comment|/* btree block disk address */
r_int
id|level
)paren
suffix:semicolon
multiline_comment|/* btree block level */
multiline_comment|/*&n; * Delete the btree cursor.&n; */
r_void
id|xfs_btree_del_cursor
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|error
)paren
suffix:semicolon
multiline_comment|/* del because of error */
multiline_comment|/*&n; * Duplicate the btree cursor.&n; * Allocate a new one, copy the record, re-get the buffers.&n; */
r_int
multiline_comment|/* error */
id|xfs_btree_dup_cursor
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* input cursor */
id|xfs_btree_cur_t
op_star
op_star
id|ncur
)paren
suffix:semicolon
multiline_comment|/* output cursor */
multiline_comment|/*&n; * Change the cursor to point to the first record in the current block&n; * at the given level.&t;Other levels are unaffected.&n; */
r_int
multiline_comment|/* success=1, failure=0 */
id|xfs_btree_firstrec
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|level
)paren
suffix:semicolon
multiline_comment|/* level to change */
multiline_comment|/*&n; * Retrieve the block pointer from the cursor at the given level.&n; * This may be a bmap btree root or from a buffer.&n; */
id|xfs_btree_block_t
op_star
multiline_comment|/* generic btree block pointer */
id|xfs_btree_get_block
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|level
comma
multiline_comment|/* level in btree */
r_struct
id|xfs_buf
op_star
op_star
id|bpp
)paren
suffix:semicolon
multiline_comment|/* buffer containing the block */
multiline_comment|/*&n; * Get a buffer for the block, return it with no data read.&n; * Long-form addressing.&n; */
r_struct
id|xfs_buf
op_star
multiline_comment|/* buffer for fsbno */
id|xfs_btree_get_bufl
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount point */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_fsblock_t
id|fsbno
comma
multiline_comment|/* file system block number */
id|uint
id|lock
)paren
suffix:semicolon
multiline_comment|/* lock flags for get_buf */
multiline_comment|/*&n; * Get a buffer for the block, return it with no data read.&n; * Short-form addressing.&n; */
r_struct
id|xfs_buf
op_star
multiline_comment|/* buffer for agno/agbno */
id|xfs_btree_get_bufs
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount point */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_agnumber_t
id|agno
comma
multiline_comment|/* allocation group number */
id|xfs_agblock_t
id|agbno
comma
multiline_comment|/* allocation group block number */
id|uint
id|lock
)paren
suffix:semicolon
multiline_comment|/* lock flags for get_buf */
multiline_comment|/*&n; * Allocate a new btree cursor.&n; * The cursor is either for allocation (A) or bmap (B).&n; */
id|xfs_btree_cur_t
op_star
multiline_comment|/* new btree cursor */
id|xfs_btree_init_cursor
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount point */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_buf
op_star
id|agbp
comma
multiline_comment|/* (A only) buffer for agf structure */
id|xfs_agnumber_t
id|agno
comma
multiline_comment|/* (A only) allocation group number */
id|xfs_btnum_t
id|btnum
comma
multiline_comment|/* btree identifier */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* (B only) inode owning the btree */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* (B only) data/attr fork */
multiline_comment|/*&n; * Check for the cursor referring to the last block at the given level.&n; */
r_int
multiline_comment|/* 1=is last block, 0=not last block */
id|xfs_btree_islastblock
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|level
)paren
suffix:semicolon
multiline_comment|/* level to check */
multiline_comment|/*&n; * Change the cursor to point to the last record in the current block&n; * at the given level.&t;Other levels are unaffected.&n; */
r_int
multiline_comment|/* success=1, failure=0 */
id|xfs_btree_lastrec
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|level
)paren
suffix:semicolon
multiline_comment|/* level to change */
multiline_comment|/*&n; * Compute first and last byte offsets for the fields given.&n; * Interprets the offsets table, which contains struct field offsets.&n; */
r_void
id|xfs_btree_offsets
c_func
(paren
id|__int64_t
id|fields
comma
multiline_comment|/* bitmask of fields */
r_const
r_int
op_star
id|offsets
comma
multiline_comment|/* table of field offsets */
r_int
id|nbits
comma
multiline_comment|/* number of bits to inspect */
r_int
op_star
id|first
comma
multiline_comment|/* output: first byte offset */
r_int
op_star
id|last
)paren
suffix:semicolon
multiline_comment|/* output: last byte offset */
multiline_comment|/*&n; * Get a buffer for the block, return it read in.&n; * Long-form addressing.&n; */
r_int
multiline_comment|/* error */
id|xfs_btree_read_bufl
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount point */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_fsblock_t
id|fsbno
comma
multiline_comment|/* file system block number */
id|uint
id|lock
comma
multiline_comment|/* lock flags for read_buf */
r_struct
id|xfs_buf
op_star
op_star
id|bpp
comma
multiline_comment|/* buffer for fsbno */
r_int
id|refval
)paren
suffix:semicolon
multiline_comment|/* ref count value for buffer */
multiline_comment|/*&n; * Get a buffer for the block, return it read in.&n; * Short-form addressing.&n; */
r_int
multiline_comment|/* error */
id|xfs_btree_read_bufs
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount point */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_agnumber_t
id|agno
comma
multiline_comment|/* allocation group number */
id|xfs_agblock_t
id|agbno
comma
multiline_comment|/* allocation group block number */
id|uint
id|lock
comma
multiline_comment|/* lock flags for read_buf */
r_struct
id|xfs_buf
op_star
op_star
id|bpp
comma
multiline_comment|/* buffer for agno/agbno */
r_int
id|refval
)paren
suffix:semicolon
multiline_comment|/* ref count value for buffer */
multiline_comment|/*&n; * Read-ahead the block, don&squot;t wait for it, don&squot;t return a buffer.&n; * Long-form addressing.&n; */
r_void
multiline_comment|/* error */
id|xfs_btree_reada_bufl
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount point */
id|xfs_fsblock_t
id|fsbno
comma
multiline_comment|/* file system block number */
id|xfs_extlen_t
id|count
)paren
suffix:semicolon
multiline_comment|/* count of filesystem blocks */
multiline_comment|/*&n; * Read-ahead the block, don&squot;t wait for it, don&squot;t return a buffer.&n; * Short-form addressing.&n; */
r_void
multiline_comment|/* error */
id|xfs_btree_reada_bufs
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount point */
id|xfs_agnumber_t
id|agno
comma
multiline_comment|/* allocation group number */
id|xfs_agblock_t
id|agbno
comma
multiline_comment|/* allocation group block number */
id|xfs_extlen_t
id|count
)paren
suffix:semicolon
multiline_comment|/* count of filesystem blocks */
multiline_comment|/*&n; * Read-ahead btree blocks, at the given level.&n; * Bits in lr are set from XFS_BTCUR_{LEFT,RIGHT}RA.&n; */
r_int
multiline_comment|/* readahead block count */
id|xfs_btree_readahead_core
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|lev
comma
multiline_comment|/* level in btree */
r_int
id|lr
)paren
suffix:semicolon
multiline_comment|/* left/right bits */
r_static
r_inline
r_int
multiline_comment|/* readahead block count */
DECL|function|xfs_btree_readahead
id|xfs_btree_readahead
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|lev
comma
multiline_comment|/* level in btree */
r_int
id|lr
)paren
multiline_comment|/* left/right bits */
(brace
r_if
c_cond
(paren
(paren
id|cur-&gt;bc_ra
(braket
id|lev
)braket
op_or
id|lr
)paren
op_eq
id|cur-&gt;bc_ra
(braket
id|lev
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xfs_btree_readahead_core
c_func
(paren
id|cur
comma
id|lev
comma
id|lr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the buffer for level &quot;lev&quot; in the cursor to bp, releasing&n; * any previous buffer.&n; */
r_void
id|xfs_btree_setbuf
c_func
(paren
id|xfs_btree_cur_t
op_star
id|cur
comma
multiline_comment|/* btree cursor */
r_int
id|lev
comma
multiline_comment|/* level in btree */
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
multiline_comment|/* new buffer to set */
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * Min and max functions for extlen, agblock, fileoff, and filblks types.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_EXTLEN_MIN)
id|xfs_extlen_t
id|xfs_extlen_min
c_func
(paren
id|xfs_extlen_t
id|a
comma
id|xfs_extlen_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_EXTLEN_MIN
mdefine_line|#define XFS_EXTLEN_MIN(a,b)&t;xfs_extlen_min(a,b)
macro_line|#else
DECL|macro|XFS_EXTLEN_MIN
mdefine_line|#define XFS_EXTLEN_MIN(a,b)&t;&bslash;&n;&t;((xfs_extlen_t)(a) &lt; (xfs_extlen_t)(b) ? &bslash;&n;&t; (xfs_extlen_t)(a) : (xfs_extlen_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_EXTLEN_MAX)
id|xfs_extlen_t
id|xfs_extlen_max
c_func
(paren
id|xfs_extlen_t
id|a
comma
id|xfs_extlen_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_EXTLEN_MAX
mdefine_line|#define XFS_EXTLEN_MAX(a,b)&t;xfs_extlen_max(a,b)
macro_line|#else
DECL|macro|XFS_EXTLEN_MAX
mdefine_line|#define XFS_EXTLEN_MAX(a,b)&t;&bslash;&n;&t;((xfs_extlen_t)(a) &gt; (xfs_extlen_t)(b) ? &bslash;&n;&t; (xfs_extlen_t)(a) : (xfs_extlen_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGBLOCK_MIN)
id|xfs_agblock_t
id|xfs_agblock_min
c_func
(paren
id|xfs_agblock_t
id|a
comma
id|xfs_agblock_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_AGBLOCK_MIN
mdefine_line|#define XFS_AGBLOCK_MIN(a,b)&t;xfs_agblock_min(a,b)
macro_line|#else
DECL|macro|XFS_AGBLOCK_MIN
mdefine_line|#define XFS_AGBLOCK_MIN(a,b)&t;&bslash;&n;&t;((xfs_agblock_t)(a) &lt; (xfs_agblock_t)(b) ? &bslash;&n;&t; (xfs_agblock_t)(a) : (xfs_agblock_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGBLOCK_MAX)
id|xfs_agblock_t
id|xfs_agblock_max
c_func
(paren
id|xfs_agblock_t
id|a
comma
id|xfs_agblock_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_AGBLOCK_MAX
mdefine_line|#define XFS_AGBLOCK_MAX(a,b)&t;xfs_agblock_max(a,b)
macro_line|#else
DECL|macro|XFS_AGBLOCK_MAX
mdefine_line|#define XFS_AGBLOCK_MAX(a,b)&t;&bslash;&n;&t;((xfs_agblock_t)(a) &gt; (xfs_agblock_t)(b) ? &bslash;&n;&t; (xfs_agblock_t)(a) : (xfs_agblock_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FILEOFF_MIN)
id|xfs_fileoff_t
id|xfs_fileoff_min
c_func
(paren
id|xfs_fileoff_t
id|a
comma
id|xfs_fileoff_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_FILEOFF_MIN
mdefine_line|#define XFS_FILEOFF_MIN(a,b)&t;xfs_fileoff_min(a,b)
macro_line|#else
DECL|macro|XFS_FILEOFF_MIN
mdefine_line|#define XFS_FILEOFF_MIN(a,b)&t;&bslash;&n;&t;((xfs_fileoff_t)(a) &lt; (xfs_fileoff_t)(b) ? &bslash;&n;&t; (xfs_fileoff_t)(a) : (xfs_fileoff_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FILEOFF_MAX)
id|xfs_fileoff_t
id|xfs_fileoff_max
c_func
(paren
id|xfs_fileoff_t
id|a
comma
id|xfs_fileoff_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_FILEOFF_MAX
mdefine_line|#define XFS_FILEOFF_MAX(a,b)&t;xfs_fileoff_max(a,b)
macro_line|#else
DECL|macro|XFS_FILEOFF_MAX
mdefine_line|#define XFS_FILEOFF_MAX(a,b)&t;&bslash;&n;&t;((xfs_fileoff_t)(a) &gt; (xfs_fileoff_t)(b) ? &bslash;&n;&t; (xfs_fileoff_t)(a) : (xfs_fileoff_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FILBLKS_MIN)
id|xfs_filblks_t
id|xfs_filblks_min
c_func
(paren
id|xfs_filblks_t
id|a
comma
id|xfs_filblks_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_FILBLKS_MIN
mdefine_line|#define XFS_FILBLKS_MIN(a,b)&t;xfs_filblks_min(a,b)
macro_line|#else
DECL|macro|XFS_FILBLKS_MIN
mdefine_line|#define XFS_FILBLKS_MIN(a,b)&t;&bslash;&n;&t;((xfs_filblks_t)(a) &lt; (xfs_filblks_t)(b) ? &bslash;&n;&t; (xfs_filblks_t)(a) : (xfs_filblks_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FILBLKS_MAX)
id|xfs_filblks_t
id|xfs_filblks_max
c_func
(paren
id|xfs_filblks_t
id|a
comma
id|xfs_filblks_t
id|b
)paren
suffix:semicolon
DECL|macro|XFS_FILBLKS_MAX
mdefine_line|#define XFS_FILBLKS_MAX(a,b)&t;xfs_filblks_max(a,b)
macro_line|#else
DECL|macro|XFS_FILBLKS_MAX
mdefine_line|#define XFS_FILBLKS_MAX(a,b)&t;&bslash;&n;&t;((xfs_filblks_t)(a) &gt; (xfs_filblks_t)(b) ? &bslash;&n;&t; (xfs_filblks_t)(a) : (xfs_filblks_t)(b))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FSB_SANITY_CHECK)
r_int
id|xfs_fsb_sanity_check
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_fsblock_t
id|fsb
)paren
suffix:semicolon
DECL|macro|XFS_FSB_SANITY_CHECK
mdefine_line|#define XFS_FSB_SANITY_CHECK(mp,fsb)&t;xfs_fsb_sanity_check(mp,fsb)
macro_line|#else
DECL|macro|XFS_FSB_SANITY_CHECK
mdefine_line|#define XFS_FSB_SANITY_CHECK(mp,fsb)&t;&bslash;&n;&t;(XFS_FSB_TO_AGNO(mp, fsb) &lt; mp-&gt;m_sb.sb_agcount &amp;&amp; &bslash;&n;&t; XFS_FSB_TO_AGBNO(mp, fsb) &lt; mp-&gt;m_sb.sb_agblocks)
macro_line|#endif
multiline_comment|/*&n; * Macros to set EFSCORRUPTED &amp; return/branch.&n; */
DECL|macro|XFS_WANT_CORRUPTED_GOTO
mdefine_line|#define XFS_WANT_CORRUPTED_GOTO(x,l)&t;&bslash;&n;&t;{ &bslash;&n;&t;&t;int fs_is_ok = (x); &bslash;&n;&t;&t;ASSERT(fs_is_ok); &bslash;&n;&t;&t;if (unlikely(!fs_is_ok)) { &bslash;&n;&t;&t;&t;XFS_ERROR_REPORT(&quot;XFS_WANT_CORRUPTED_GOTO&quot;, &bslash;&n;&t;&t;&t;&t;&t; XFS_ERRLEVEL_LOW, NULL); &bslash;&n;&t;&t;&t;error = XFS_ERROR(EFSCORRUPTED); &bslash;&n;&t;&t;&t;goto l; &bslash;&n;&t;&t;} &bslash;&n;&t;}
DECL|macro|XFS_WANT_CORRUPTED_RETURN
mdefine_line|#define XFS_WANT_CORRUPTED_RETURN(x)&t;&bslash;&n;&t;{ &bslash;&n;&t;&t;int fs_is_ok = (x); &bslash;&n;&t;&t;ASSERT(fs_is_ok); &bslash;&n;&t;&t;if (unlikely(!fs_is_ok)) { &bslash;&n;&t;&t;&t;XFS_ERROR_REPORT(&quot;XFS_WANT_CORRUPTED_RETURN&quot;, &bslash;&n;&t;&t;&t;&t;&t; XFS_ERRLEVEL_LOW, NULL); &bslash;&n;&t;&t;&t;return XFS_ERROR(EFSCORRUPTED); &bslash;&n;&t;&t;} &bslash;&n;&t;}
macro_line|#endif&t;/* __XFS_BTREE_H__ */
eof
