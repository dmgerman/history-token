multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_BMAP_BTREE_H__
DECL|macro|__XFS_BMAP_BTREE_H__
mdefine_line|#define __XFS_BMAP_BTREE_H__
DECL|macro|XFS_BMAP_MAGIC
mdefine_line|#define XFS_BMAP_MAGIC&t;0x424d4150&t;/* &squot;BMAP&squot; */
r_struct
id|xfs_btree_cur
suffix:semicolon
r_struct
id|xfs_btree_lblock
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
multiline_comment|/*&n; * Bmap root header, on-disk form only.&n; */
DECL|struct|xfs_bmdr_block
r_typedef
r_struct
id|xfs_bmdr_block
(brace
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
DECL|typedef|xfs_bmdr_block_t
)brace
id|xfs_bmdr_block_t
suffix:semicolon
multiline_comment|/*&n; * Bmap btree record and extent descriptor.&n; * For 32-bit kernels,&n; *  l0:31 is an extent flag (value 1 indicates non-normal).&n; *  l0:0-30 and l1:9-31 are startoff.&n; *  l1:0-8, l2:0-31, and l3:21-31 are startblock.&n; *  l3:0-20 are blockcount.&n; * For 64-bit kernels,&n; *  l0:63 is an extent flag (value 1 indicates non-normal).&n; *  l0:9-62 are startoff.&n; *  l0:0-8 and l1:21-63 are startblock.&n; *  l1:0-20 are blockcount.&n; */
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|BMBT_TOTAL_BITLEN
mdefine_line|#define BMBT_TOTAL_BITLEN&t;128&t;/* 128 bits, 16 bytes */
DECL|macro|BMBT_EXNTFLAG_BITOFF
mdefine_line|#define BMBT_EXNTFLAG_BITOFF&t;0
DECL|macro|BMBT_EXNTFLAG_BITLEN
mdefine_line|#define BMBT_EXNTFLAG_BITLEN&t;1
DECL|macro|BMBT_STARTOFF_BITOFF
mdefine_line|#define BMBT_STARTOFF_BITOFF&t;(BMBT_EXNTFLAG_BITOFF + BMBT_EXNTFLAG_BITLEN)
DECL|macro|BMBT_STARTOFF_BITLEN
mdefine_line|#define BMBT_STARTOFF_BITLEN&t;54
DECL|macro|BMBT_STARTBLOCK_BITOFF
mdefine_line|#define BMBT_STARTBLOCK_BITOFF&t;(BMBT_STARTOFF_BITOFF + BMBT_STARTOFF_BITLEN)
DECL|macro|BMBT_STARTBLOCK_BITLEN
mdefine_line|#define BMBT_STARTBLOCK_BITLEN&t;52
DECL|macro|BMBT_BLOCKCOUNT_BITOFF
mdefine_line|#define BMBT_BLOCKCOUNT_BITOFF&t;&bslash;&n;&t;(BMBT_STARTBLOCK_BITOFF + BMBT_STARTBLOCK_BITLEN)
DECL|macro|BMBT_BLOCKCOUNT_BITLEN
mdefine_line|#define BMBT_BLOCKCOUNT_BITLEN&t;(BMBT_TOTAL_BITLEN - BMBT_BLOCKCOUNT_BITOFF)
macro_line|#else
DECL|macro|BMBT_TOTAL_BITLEN
mdefine_line|#define BMBT_TOTAL_BITLEN&t;128&t;/* 128 bits, 16 bytes */
DECL|macro|BMBT_EXNTFLAG_BITOFF
mdefine_line|#define BMBT_EXNTFLAG_BITOFF&t;63
DECL|macro|BMBT_EXNTFLAG_BITLEN
mdefine_line|#define BMBT_EXNTFLAG_BITLEN&t;1
DECL|macro|BMBT_STARTOFF_BITOFF
mdefine_line|#define BMBT_STARTOFF_BITOFF&t;(BMBT_EXNTFLAG_BITOFF - BMBT_STARTOFF_BITLEN)
DECL|macro|BMBT_STARTOFF_BITLEN
mdefine_line|#define BMBT_STARTOFF_BITLEN&t;54
DECL|macro|BMBT_STARTBLOCK_BITOFF
mdefine_line|#define BMBT_STARTBLOCK_BITOFF&t;85 /* 128 - 43 (other 9 is in first word) */
DECL|macro|BMBT_STARTBLOCK_BITLEN
mdefine_line|#define BMBT_STARTBLOCK_BITLEN&t;52
DECL|macro|BMBT_BLOCKCOUNT_BITOFF
mdefine_line|#define BMBT_BLOCKCOUNT_BITOFF&t;64 /* Start of second 64 bit container */
DECL|macro|BMBT_BLOCKCOUNT_BITLEN
mdefine_line|#define BMBT_BLOCKCOUNT_BITLEN&t;21
macro_line|#endif
DECL|macro|BMBT_USE_64
mdefine_line|#define BMBT_USE_64&t;1
DECL|struct|xfs_bmbt_rec_32
r_typedef
r_struct
id|xfs_bmbt_rec_32
(brace
DECL|member|l0
DECL|member|l1
DECL|member|l2
DECL|member|l3
id|__uint32_t
id|l0
comma
id|l1
comma
id|l2
comma
id|l3
suffix:semicolon
DECL|typedef|xfs_bmbt_rec_32_t
)brace
id|xfs_bmbt_rec_32_t
suffix:semicolon
DECL|struct|xfs_bmbt_rec_64
r_typedef
r_struct
id|xfs_bmbt_rec_64
(brace
DECL|member|l0
DECL|member|l1
id|__uint64_t
id|l0
comma
id|l1
suffix:semicolon
DECL|typedef|xfs_bmbt_rec_64_t
)brace
id|xfs_bmbt_rec_64_t
suffix:semicolon
DECL|typedef|xfs_bmbt_rec_base_t
r_typedef
id|__uint64_t
id|xfs_bmbt_rec_base_t
suffix:semicolon
multiline_comment|/* use this for casts */
DECL|typedef|xfs_bmbt_rec_t
DECL|typedef|xfs_bmdr_rec_t
r_typedef
id|xfs_bmbt_rec_64_t
id|xfs_bmbt_rec_t
comma
id|xfs_bmdr_rec_t
suffix:semicolon
multiline_comment|/*&n; * Values and macros for delayed-allocation startblock fields.&n; */
DECL|macro|STARTBLOCKVALBITS
mdefine_line|#define STARTBLOCKVALBITS&t;17
DECL|macro|STARTBLOCKMASKBITS
mdefine_line|#define STARTBLOCKMASKBITS&t;(15 + XFS_BIG_FILESYSTEMS * 20)
DECL|macro|DSTARTBLOCKMASKBITS
mdefine_line|#define DSTARTBLOCKMASKBITS&t;(15 + 20)
DECL|macro|STARTBLOCKMASK
mdefine_line|#define STARTBLOCKMASK&t;&t;&bslash;&n;&t;(((((xfs_fsblock_t)1) &lt;&lt; STARTBLOCKMASKBITS) - 1) &lt;&lt; STARTBLOCKVALBITS)
DECL|macro|DSTARTBLOCKMASK
mdefine_line|#define DSTARTBLOCKMASK&t;&t;&bslash;&n;&t;(((((xfs_dfsbno_t)1) &lt;&lt; DSTARTBLOCKMASKBITS) - 1) &lt;&lt; STARTBLOCKVALBITS)
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_ISNULLSTARTBLOCK)
r_int
id|isnullstartblock
c_func
(paren
id|xfs_fsblock_t
id|x
)paren
suffix:semicolon
DECL|macro|ISNULLSTARTBLOCK
mdefine_line|#define ISNULLSTARTBLOCK(x)&t;isnullstartblock(x)
macro_line|#else
DECL|macro|ISNULLSTARTBLOCK
mdefine_line|#define ISNULLSTARTBLOCK(x)&t;(((x) &amp; STARTBLOCKMASK) == STARTBLOCKMASK)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_ISNULLDSTARTBLOCK)
r_int
id|isnulldstartblock
c_func
(paren
id|xfs_dfsbno_t
id|x
)paren
suffix:semicolon
DECL|macro|ISNULLDSTARTBLOCK
mdefine_line|#define ISNULLDSTARTBLOCK(x)&t;isnulldstartblock(x)
macro_line|#else
DECL|macro|ISNULLDSTARTBLOCK
mdefine_line|#define ISNULLDSTARTBLOCK(x)&t;(((x) &amp; DSTARTBLOCKMASK) == DSTARTBLOCKMASK)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_NULLSTARTBLOCK)
id|xfs_fsblock_t
id|nullstartblock
c_func
(paren
r_int
id|k
)paren
suffix:semicolon
DECL|macro|NULLSTARTBLOCK
mdefine_line|#define NULLSTARTBLOCK(k)&t;nullstartblock(k)
macro_line|#else
DECL|macro|NULLSTARTBLOCK
mdefine_line|#define NULLSTARTBLOCK(k)&t;&bslash;&n;&t;((ASSERT(k &lt; (1 &lt;&lt; STARTBLOCKVALBITS))), (STARTBLOCKMASK | (k)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_STARTBLOCKVAL)
id|xfs_filblks_t
id|startblockval
c_func
(paren
id|xfs_fsblock_t
id|x
)paren
suffix:semicolon
DECL|macro|STARTBLOCKVAL
mdefine_line|#define STARTBLOCKVAL(x)&t;startblockval(x)
macro_line|#else
DECL|macro|STARTBLOCKVAL
mdefine_line|#define STARTBLOCKVAL(x)&t;((xfs_filblks_t)((x) &amp; ~STARTBLOCKMASK))
macro_line|#endif
multiline_comment|/*&n; * Possible extent formats.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|XFS_EXTFMT_NOSTATE
id|XFS_EXTFMT_NOSTATE
op_assign
l_int|0
comma
DECL|enumerator|XFS_EXTFMT_HASSTATE
id|XFS_EXTFMT_HASSTATE
DECL|typedef|xfs_exntfmt_t
)brace
id|xfs_exntfmt_t
suffix:semicolon
multiline_comment|/*&n; * Possible extent states.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|XFS_EXT_NORM
DECL|enumerator|XFS_EXT_UNWRITTEN
id|XFS_EXT_NORM
comma
id|XFS_EXT_UNWRITTEN
comma
DECL|enumerator|XFS_EXT_DMAPI_OFFLINE
id|XFS_EXT_DMAPI_OFFLINE
DECL|typedef|xfs_exntst_t
)brace
id|xfs_exntst_t
suffix:semicolon
multiline_comment|/*&n; * Extent state and extent format macros.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_EXTFMT_INODE )
id|xfs_exntfmt_t
id|xfs_extfmt_inode
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
)paren
suffix:semicolon
DECL|macro|XFS_EXTFMT_INODE
mdefine_line|#define XFS_EXTFMT_INODE(x)&t;xfs_extfmt_inode(x)
macro_line|#else
DECL|macro|XFS_EXTFMT_INODE
mdefine_line|#define XFS_EXTFMT_INODE(x) &bslash;&n;  (XFS_SB_VERSION_HASEXTFLGBIT(&amp;((x)-&gt;i_mount-&gt;m_sb)) ? &bslash;&n;&t;XFS_EXTFMT_HASSTATE : XFS_EXTFMT_NOSTATE)
macro_line|#endif
DECL|macro|ISUNWRITTEN
mdefine_line|#define ISUNWRITTEN(x)&t;((x)-&gt;br_state == XFS_EXT_UNWRITTEN)
multiline_comment|/*&n; * Incore version of above.&n; */
DECL|struct|xfs_bmbt_irec
r_typedef
r_struct
id|xfs_bmbt_irec
(brace
DECL|member|br_startoff
id|xfs_fileoff_t
id|br_startoff
suffix:semicolon
multiline_comment|/* starting file offset */
DECL|member|br_startblock
id|xfs_fsblock_t
id|br_startblock
suffix:semicolon
multiline_comment|/* starting block number */
DECL|member|br_blockcount
id|xfs_filblks_t
id|br_blockcount
suffix:semicolon
multiline_comment|/* number of blocks */
DECL|member|br_state
id|xfs_exntst_t
id|br_state
suffix:semicolon
multiline_comment|/* extent state */
DECL|typedef|xfs_bmbt_irec_t
)brace
id|xfs_bmbt_irec_t
suffix:semicolon
multiline_comment|/*&n; * Key structure for non-leaf levels of the tree.&n; */
DECL|struct|xfs_bmbt_key
r_typedef
r_struct
id|xfs_bmbt_key
(brace
DECL|member|br_startoff
id|xfs_dfiloff_t
id|br_startoff
suffix:semicolon
multiline_comment|/* starting file offset */
DECL|typedef|xfs_bmbt_key_t
DECL|typedef|xfs_bmdr_key_t
)brace
id|xfs_bmbt_key_t
comma
id|xfs_bmdr_key_t
suffix:semicolon
DECL|typedef|xfs_bmbt_ptr_t
DECL|typedef|xfs_bmdr_ptr_t
r_typedef
id|xfs_dfsbno_t
id|xfs_bmbt_ptr_t
comma
id|xfs_bmdr_ptr_t
suffix:semicolon
multiline_comment|/* btree pointer type */
multiline_comment|/* btree block header type */
DECL|typedef|xfs_bmbt_block_t
r_typedef
r_struct
id|xfs_btree_lblock
id|xfs_bmbt_block_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_BMBT_BLOCK)
id|xfs_bmbt_block_t
op_star
id|xfs_buf_to_bmbt_block
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_BMBT_BLOCK
mdefine_line|#define XFS_BUF_TO_BMBT_BLOCK(bp)&t;&t;xfs_buf_to_bmbt_block(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_BMBT_BLOCK
mdefine_line|#define XFS_BUF_TO_BMBT_BLOCK(bp) ((xfs_bmbt_block_t *)(XFS_BUF_PTR(bp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_RBLOCK_DSIZE)
r_int
id|xfs_bmap_rblock_dsize
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
DECL|macro|XFS_BMAP_RBLOCK_DSIZE
mdefine_line|#define XFS_BMAP_RBLOCK_DSIZE(lev,cur)&t;&t;xfs_bmap_rblock_dsize(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_RBLOCK_DSIZE
mdefine_line|#define XFS_BMAP_RBLOCK_DSIZE(lev,cur) ((cur)-&gt;bc_private.b.forksize)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_RBLOCK_ISIZE)
r_int
id|xfs_bmap_rblock_isize
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
DECL|macro|XFS_BMAP_RBLOCK_ISIZE
mdefine_line|#define XFS_BMAP_RBLOCK_ISIZE(lev,cur)&t;&t;xfs_bmap_rblock_isize(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_RBLOCK_ISIZE
mdefine_line|#define XFS_BMAP_RBLOCK_ISIZE(lev,cur) &bslash;&n;&t;((int)XFS_IFORK_PTR((cur)-&gt;bc_private.b.ip, &bslash;&n;&t;&t;&t;    (cur)-&gt;bc_private.b.whichfork)-&gt;if_broot_bytes)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_IBLOCK_SIZE)
r_int
id|xfs_bmap_iblock_size
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
DECL|macro|XFS_BMAP_IBLOCK_SIZE
mdefine_line|#define XFS_BMAP_IBLOCK_SIZE(lev,cur)&t;&t;xfs_bmap_iblock_size(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_IBLOCK_SIZE
mdefine_line|#define XFS_BMAP_IBLOCK_SIZE(lev,cur) (1 &lt;&lt; (cur)-&gt;bc_blocklog)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BLOCK_DSIZE)
r_int
id|xfs_bmap_block_dsize
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
DECL|macro|XFS_BMAP_BLOCK_DSIZE
mdefine_line|#define XFS_BMAP_BLOCK_DSIZE(lev,cur)&t;&t;xfs_bmap_block_dsize(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_BLOCK_DSIZE
mdefine_line|#define XFS_BMAP_BLOCK_DSIZE(lev,cur) &bslash;&n;&t;((lev) == (cur)-&gt;bc_nlevels - 1 ? &bslash;&n;&t;&t;XFS_BMAP_RBLOCK_DSIZE(lev,cur) : &bslash;&n;&t;&t;XFS_BMAP_IBLOCK_SIZE(lev,cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BLOCK_ISIZE)
r_int
id|xfs_bmap_block_isize
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
DECL|macro|XFS_BMAP_BLOCK_ISIZE
mdefine_line|#define XFS_BMAP_BLOCK_ISIZE(lev,cur)&t;&t;xfs_bmap_block_isize(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_BLOCK_ISIZE
mdefine_line|#define XFS_BMAP_BLOCK_ISIZE(lev,cur) &bslash;&n;&t;((lev) == (cur)-&gt;bc_nlevels - 1 ? &bslash;&n;&t;&t;XFS_BMAP_RBLOCK_ISIZE(lev,cur) : &bslash;&n;&t;&t;XFS_BMAP_IBLOCK_SIZE(lev,cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BLOCK_DMAXRECS)
r_int
id|xfs_bmap_block_dmaxrecs
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
DECL|macro|XFS_BMAP_BLOCK_DMAXRECS
mdefine_line|#define XFS_BMAP_BLOCK_DMAXRECS(lev,cur)&t;xfs_bmap_block_dmaxrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_BLOCK_DMAXRECS
mdefine_line|#define XFS_BMAP_BLOCK_DMAXRECS(lev,cur) &bslash;&n;&t;((lev) == (cur)-&gt;bc_nlevels - 1 ? &bslash;&n;&t;&t;XFS_BTREE_BLOCK_MAXRECS(XFS_BMAP_RBLOCK_DSIZE(lev,cur), &bslash;&n;&t;&t;&t;xfs_bmdr, (lev) == 0) : &bslash;&n;&t;&t;((cur)-&gt;bc_mp-&gt;m_bmap_dmxr[(lev) != 0]))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BLOCK_IMAXRECS)
r_int
id|xfs_bmap_block_imaxrecs
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
DECL|macro|XFS_BMAP_BLOCK_IMAXRECS
mdefine_line|#define XFS_BMAP_BLOCK_IMAXRECS(lev,cur)&t;xfs_bmap_block_imaxrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_BLOCK_IMAXRECS
mdefine_line|#define XFS_BMAP_BLOCK_IMAXRECS(lev,cur) &bslash;&n;&t;((lev) == (cur)-&gt;bc_nlevels - 1 ? &bslash;&n;&t;&t;XFS_BTREE_BLOCK_MAXRECS(XFS_BMAP_RBLOCK_ISIZE(lev,cur), &bslash;&n;&t;&t;&t;xfs_bmbt, (lev) == 0) : &bslash;&n;&t;&t;((cur)-&gt;bc_mp-&gt;m_bmap_dmxr[(lev) != 0]))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BLOCK_DMINRECS)
r_int
id|xfs_bmap_block_dminrecs
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
DECL|macro|XFS_BMAP_BLOCK_DMINRECS
mdefine_line|#define XFS_BMAP_BLOCK_DMINRECS(lev,cur)&t;xfs_bmap_block_dminrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_BLOCK_DMINRECS
mdefine_line|#define XFS_BMAP_BLOCK_DMINRECS(lev,cur) &bslash;&n;&t;((lev) == (cur)-&gt;bc_nlevels - 1 ? &bslash;&n;&t;&t;XFS_BTREE_BLOCK_MINRECS(XFS_BMAP_RBLOCK_DSIZE(lev,cur), &bslash;&n;&t;&t;&t;xfs_bmdr, (lev) == 0) : &bslash;&n;&t;&t;((cur)-&gt;bc_mp-&gt;m_bmap_dmnr[(lev) != 0]))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BLOCK_IMINRECS)
r_int
id|xfs_bmap_block_iminrecs
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
DECL|macro|XFS_BMAP_BLOCK_IMINRECS
mdefine_line|#define XFS_BMAP_BLOCK_IMINRECS(lev,cur)&t;xfs_bmap_block_iminrecs(lev,cur)
macro_line|#else
DECL|macro|XFS_BMAP_BLOCK_IMINRECS
mdefine_line|#define XFS_BMAP_BLOCK_IMINRECS(lev,cur) &bslash;&n;&t;((lev) == (cur)-&gt;bc_nlevels - 1 ? &bslash;&n;&t;&t;XFS_BTREE_BLOCK_MINRECS(XFS_BMAP_RBLOCK_ISIZE(lev,cur), &bslash;&n;&t;&t;&t;xfs_bmbt, (lev) == 0) : &bslash;&n;&t;&t;((cur)-&gt;bc_mp-&gt;m_bmap_dmnr[(lev) != 0]))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_REC_DADDR)
id|xfs_bmbt_rec_t
op_star
id|xfs_bmap_rec_daddr
c_func
(paren
id|xfs_bmbt_block_t
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
DECL|macro|XFS_BMAP_REC_DADDR
mdefine_line|#define XFS_BMAP_REC_DADDR(bb,i,cur)&t;&t;xfs_bmap_rec_daddr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_BMAP_REC_DADDR
mdefine_line|#define XFS_BMAP_REC_DADDR(bb,i,cur) &bslash;&n;&t;XFS_BTREE_REC_ADDR(XFS_BMAP_BLOCK_DSIZE(&t;&t;&bslash;&n;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur),&t;&bslash;&n;&t;&t;xfs_bmbt, bb, i, XFS_BMAP_BLOCK_DMAXRECS(&t;&bslash;&n;&t;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_REC_IADDR)
id|xfs_bmbt_rec_t
op_star
id|xfs_bmap_rec_iaddr
c_func
(paren
id|xfs_bmbt_block_t
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
DECL|macro|XFS_BMAP_REC_IADDR
mdefine_line|#define XFS_BMAP_REC_IADDR(bb,i,cur)&t;&t;xfs_bmap_rec_iaddr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_BMAP_REC_IADDR
mdefine_line|#define XFS_BMAP_REC_IADDR(bb,i,cur) &bslash;&n;&t;XFS_BTREE_REC_ADDR(XFS_BMAP_BLOCK_ISIZE(&t;&t;&bslash;&n;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur),&t;&bslash;&n;&t;&t;xfs_bmbt, bb, i, XFS_BMAP_BLOCK_IMAXRECS(&t;&bslash;&n;&t;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_KEY_DADDR)
id|xfs_bmbt_key_t
op_star
id|xfs_bmap_key_daddr
c_func
(paren
id|xfs_bmbt_block_t
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
DECL|macro|XFS_BMAP_KEY_DADDR
mdefine_line|#define XFS_BMAP_KEY_DADDR(bb,i,cur)&t;&t;xfs_bmap_key_daddr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_BMAP_KEY_DADDR
mdefine_line|#define XFS_BMAP_KEY_DADDR(bb,i,cur) &bslash;&n;&t;XFS_BTREE_KEY_ADDR(XFS_BMAP_BLOCK_DSIZE(&t;&t;&bslash;&n;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur),&t;&bslash;&n;&t;&t;xfs_bmbt, bb, i, XFS_BMAP_BLOCK_DMAXRECS(&t;&bslash;&n;&t;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_KEY_IADDR)
id|xfs_bmbt_key_t
op_star
id|xfs_bmap_key_iaddr
c_func
(paren
id|xfs_bmbt_block_t
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
DECL|macro|XFS_BMAP_KEY_IADDR
mdefine_line|#define XFS_BMAP_KEY_IADDR(bb,i,cur)&t;&t;xfs_bmap_key_iaddr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_BMAP_KEY_IADDR
mdefine_line|#define XFS_BMAP_KEY_IADDR(bb,i,cur) &bslash;&n;&t;XFS_BTREE_KEY_ADDR(XFS_BMAP_BLOCK_ISIZE(&t;&t;&bslash;&n;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur),&t;&bslash;&n;&t;&t;xfs_bmbt, bb, i, XFS_BMAP_BLOCK_IMAXRECS(&t;&bslash;&n;&t;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_PTR_DADDR)
id|xfs_bmbt_ptr_t
op_star
id|xfs_bmap_ptr_daddr
c_func
(paren
id|xfs_bmbt_block_t
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
DECL|macro|XFS_BMAP_PTR_DADDR
mdefine_line|#define XFS_BMAP_PTR_DADDR(bb,i,cur)&t;&t;xfs_bmap_ptr_daddr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_BMAP_PTR_DADDR
mdefine_line|#define XFS_BMAP_PTR_DADDR(bb,i,cur) &bslash;&n;&t;XFS_BTREE_PTR_ADDR(XFS_BMAP_BLOCK_DSIZE(&t;&t;&bslash;&n;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur),&t;&bslash;&n;&t;&t;xfs_bmbt, bb, i, XFS_BMAP_BLOCK_DMAXRECS(&t;&bslash;&n;&t;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_PTR_IADDR)
id|xfs_bmbt_ptr_t
op_star
id|xfs_bmap_ptr_iaddr
c_func
(paren
id|xfs_bmbt_block_t
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
DECL|macro|XFS_BMAP_PTR_IADDR
mdefine_line|#define XFS_BMAP_PTR_IADDR(bb,i,cur)&t;&t;xfs_bmap_ptr_iaddr(bb,i,cur)
macro_line|#else
DECL|macro|XFS_BMAP_PTR_IADDR
mdefine_line|#define XFS_BMAP_PTR_IADDR(bb,i,cur) &bslash;&n;&t;XFS_BTREE_PTR_ADDR(XFS_BMAP_BLOCK_ISIZE(&t;&t;&bslash;&n;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur),&t;&bslash;&n;&t;&t;xfs_bmbt, bb, i, XFS_BMAP_BLOCK_IMAXRECS(&t;&bslash;&n;&t;&t;&t;INT_GET((bb)-&gt;bb_level, ARCH_CONVERT), cur))
macro_line|#endif
multiline_comment|/*&n; * These are to be used when we know the size of the block and&n; * we don&squot;t have a cursor.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BROOT_REC_ADDR)
id|xfs_bmbt_rec_t
op_star
id|xfs_bmap_broot_rec_addr
c_func
(paren
id|xfs_bmbt_block_t
op_star
id|bb
comma
r_int
id|i
comma
r_int
id|sz
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_BROOT_REC_ADDR
mdefine_line|#define XFS_BMAP_BROOT_REC_ADDR(bb,i,sz)&t;xfs_bmap_broot_rec_addr(bb,i,sz)
macro_line|#else
DECL|macro|XFS_BMAP_BROOT_REC_ADDR
mdefine_line|#define XFS_BMAP_BROOT_REC_ADDR(bb,i,sz) &bslash;&n;&t;XFS_BTREE_REC_ADDR(sz,xfs_bmbt,bb,i,XFS_BMAP_BROOT_MAXRECS(sz))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BROOT_KEY_ADDR)
id|xfs_bmbt_key_t
op_star
id|xfs_bmap_broot_key_addr
c_func
(paren
id|xfs_bmbt_block_t
op_star
id|bb
comma
r_int
id|i
comma
r_int
id|sz
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_BROOT_KEY_ADDR
mdefine_line|#define XFS_BMAP_BROOT_KEY_ADDR(bb,i,sz)&t;xfs_bmap_broot_key_addr(bb,i,sz)
macro_line|#else
DECL|macro|XFS_BMAP_BROOT_KEY_ADDR
mdefine_line|#define XFS_BMAP_BROOT_KEY_ADDR(bb,i,sz) &bslash;&n;&t;XFS_BTREE_KEY_ADDR(sz,xfs_bmbt,bb,i,XFS_BMAP_BROOT_MAXRECS(sz))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BROOT_PTR_ADDR)
id|xfs_bmbt_ptr_t
op_star
id|xfs_bmap_broot_ptr_addr
c_func
(paren
id|xfs_bmbt_block_t
op_star
id|bb
comma
r_int
id|i
comma
r_int
id|sz
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_BROOT_PTR_ADDR
mdefine_line|#define XFS_BMAP_BROOT_PTR_ADDR(bb,i,sz)&t;xfs_bmap_broot_ptr_addr(bb,i,sz)
macro_line|#else
DECL|macro|XFS_BMAP_BROOT_PTR_ADDR
mdefine_line|#define XFS_BMAP_BROOT_PTR_ADDR(bb,i,sz) &bslash;&n;&t;XFS_BTREE_PTR_ADDR(sz,xfs_bmbt,bb,i,XFS_BMAP_BROOT_MAXRECS(sz))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BROOT_NUMRECS)
r_int
id|xfs_bmap_broot_numrecs
c_func
(paren
id|xfs_bmdr_block_t
op_star
id|bb
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_BROOT_NUMRECS
mdefine_line|#define XFS_BMAP_BROOT_NUMRECS(bb)&t;&t;xfs_bmap_broot_numrecs(bb)
macro_line|#else
DECL|macro|XFS_BMAP_BROOT_NUMRECS
mdefine_line|#define XFS_BMAP_BROOT_NUMRECS(bb) (INT_GET((bb)-&gt;bb_numrecs, ARCH_CONVERT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BROOT_MAXRECS)
r_int
id|xfs_bmap_broot_maxrecs
c_func
(paren
r_int
id|sz
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_BROOT_MAXRECS
mdefine_line|#define XFS_BMAP_BROOT_MAXRECS(sz)&t;&t;xfs_bmap_broot_maxrecs(sz)
macro_line|#else
DECL|macro|XFS_BMAP_BROOT_MAXRECS
mdefine_line|#define XFS_BMAP_BROOT_MAXRECS(sz) XFS_BTREE_BLOCK_MAXRECS(sz,xfs_bmbt,0)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BROOT_SPACE_CALC)
r_int
id|xfs_bmap_broot_space_calc
c_func
(paren
r_int
id|nrecs
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_BROOT_SPACE_CALC
mdefine_line|#define XFS_BMAP_BROOT_SPACE_CALC(nrecs)&t;xfs_bmap_broot_space_calc(nrecs)
macro_line|#else
DECL|macro|XFS_BMAP_BROOT_SPACE_CALC
mdefine_line|#define XFS_BMAP_BROOT_SPACE_CALC(nrecs) &bslash;&n;&t;((int)(sizeof(xfs_bmbt_block_t) + &bslash;&n;&t;       ((nrecs) * (sizeof(xfs_bmbt_key_t) + sizeof(xfs_bmbt_ptr_t)))))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_BROOT_SPACE)
r_int
id|xfs_bmap_broot_space
c_func
(paren
id|xfs_bmdr_block_t
op_star
id|bb
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_BROOT_SPACE
mdefine_line|#define XFS_BMAP_BROOT_SPACE(bb)&t;&t;xfs_bmap_broot_space(bb)
macro_line|#else
DECL|macro|XFS_BMAP_BROOT_SPACE
mdefine_line|#define XFS_BMAP_BROOT_SPACE(bb) &bslash;&n;&t;XFS_BMAP_BROOT_SPACE_CALC(INT_GET((bb)-&gt;bb_numrecs, ARCH_CONVERT))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMDR_SPACE_CALC)
r_int
id|xfs_bmdr_space_calc
c_func
(paren
r_int
id|nrecs
)paren
suffix:semicolon
DECL|macro|XFS_BMDR_SPACE_CALC
mdefine_line|#define XFS_BMDR_SPACE_CALC(nrecs)&t;&t;xfs_bmdr_space_calc(nrecs)
macro_line|#else
DECL|macro|XFS_BMDR_SPACE_CALC
mdefine_line|#define XFS_BMDR_SPACE_CALC(nrecs)&t;&bslash;&n;&t;((int)(sizeof(xfs_bmdr_block_t) + &bslash;&n;&t;       ((nrecs) * (sizeof(xfs_bmbt_key_t) + sizeof(xfs_bmbt_ptr_t)))))
macro_line|#endif
multiline_comment|/*&n; * Maximum number of bmap btree levels.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BM_MAXLEVELS)
r_int
id|xfs_bm_maxlevels
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_BM_MAXLEVELS
mdefine_line|#define XFS_BM_MAXLEVELS(mp,w)&t;&t;&t;xfs_bm_maxlevels(mp,w)
macro_line|#else
DECL|macro|XFS_BM_MAXLEVELS
mdefine_line|#define XFS_BM_MAXLEVELS(mp,w)&t;&t;((mp)-&gt;m_bm_maxlevels[w])
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_SANITY_CHECK)
r_int
id|xfs_bmap_sanity_check
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_bmbt_block_t
op_star
id|bb
comma
r_int
id|level
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_SANITY_CHECK
mdefine_line|#define XFS_BMAP_SANITY_CHECK(mp,bb,level)&t;&bslash;&n;&t;xfs_bmap_sanity_check(mp,bb,level)
macro_line|#else
DECL|macro|XFS_BMAP_SANITY_CHECK
mdefine_line|#define XFS_BMAP_SANITY_CHECK(mp,bb,level)&t;&bslash;&n;&t;(INT_GET((bb)-&gt;bb_magic, ARCH_CONVERT) == XFS_BMAP_MAGIC &amp;&amp; &bslash;&n;&t; INT_GET((bb)-&gt;bb_level, ARCH_CONVERT) == level &amp;&amp; &bslash;&n;&t; INT_GET((bb)-&gt;bb_numrecs, ARCH_CONVERT) &gt; 0 &amp;&amp; &bslash;&n;&t; INT_GET((bb)-&gt;bb_numrecs, ARCH_CONVERT) &lt;= (mp)-&gt;m_bmap_dmxr[(level) != 0])
macro_line|#endif
multiline_comment|/*&n; * Trace buffer entry types.&n; */
DECL|macro|XFS_BMBT_KTRACE_ARGBI
mdefine_line|#define XFS_BMBT_KTRACE_ARGBI&t;1
DECL|macro|XFS_BMBT_KTRACE_ARGBII
mdefine_line|#define XFS_BMBT_KTRACE_ARGBII&t;2
DECL|macro|XFS_BMBT_KTRACE_ARGFFFI
mdefine_line|#define XFS_BMBT_KTRACE_ARGFFFI 3
DECL|macro|XFS_BMBT_KTRACE_ARGI
mdefine_line|#define XFS_BMBT_KTRACE_ARGI&t;4
DECL|macro|XFS_BMBT_KTRACE_ARGIFK
mdefine_line|#define XFS_BMBT_KTRACE_ARGIFK&t;5
DECL|macro|XFS_BMBT_KTRACE_ARGIFR
mdefine_line|#define XFS_BMBT_KTRACE_ARGIFR&t;6
DECL|macro|XFS_BMBT_KTRACE_ARGIK
mdefine_line|#define XFS_BMBT_KTRACE_ARGIK&t;7
DECL|macro|XFS_BMBT_KTRACE_CUR
mdefine_line|#define XFS_BMBT_KTRACE_CUR&t;8
DECL|macro|XFS_BMBT_TRACE_SIZE
mdefine_line|#define XFS_BMBT_TRACE_SIZE&t;4096&t;/* size of global trace buffer */
DECL|macro|XFS_BMBT_KTRACE_SIZE
mdefine_line|#define XFS_BMBT_KTRACE_SIZE&t;32&t;/* size of per-inode trace buffer */
macro_line|#if defined(XFS_ALL_TRACE)
DECL|macro|XFS_BMBT_TRACE
mdefine_line|#define XFS_BMBT_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_BMBT_TRACE
macro_line|#undef XFS_BMBT_TRACE
macro_line|#endif
multiline_comment|/*&n; * Prototypes for xfs_bmap.c to call.&n; */
r_void
id|xfs_bmdr_to_bmbt
c_func
(paren
id|xfs_bmdr_block_t
op_star
comma
r_int
comma
id|xfs_bmbt_block_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_bmbt_decrement
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|xfs_bmbt_delete
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_void
id|xfs_bmbt_get_all
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_bmbt_irec_t
op_star
id|s
)paren
suffix:semicolon
id|xfs_bmbt_block_t
op_star
id|xfs_bmbt_get_block
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
id|cur
comma
r_int
id|level
comma
r_struct
id|xfs_buf
op_star
op_star
id|bpp
)paren
suffix:semicolon
id|xfs_filblks_t
id|xfs_bmbt_get_blockcount
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
id|xfs_fsblock_t
id|xfs_bmbt_get_startblock
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
id|xfs_fileoff_t
id|xfs_bmbt_get_startoff
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
id|xfs_exntst_t
id|xfs_bmbt_get_state
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
macro_line|#if ARCH_CONVERT != ARCH_NOCONVERT
r_void
id|xfs_bmbt_disk_get_all
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_bmbt_irec_t
op_star
id|s
)paren
suffix:semicolon
id|xfs_exntst_t
id|xfs_bmbt_disk_get_state
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
id|xfs_filblks_t
id|xfs_bmbt_disk_get_blockcount
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
id|xfs_fsblock_t
id|xfs_bmbt_disk_get_startblock
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
id|xfs_fileoff_t
id|xfs_bmbt_disk_get_startoff
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_bmbt_disk_get_all
mdefine_line|#define xfs_bmbt_disk_get_all(r, s) &bslash;&n;&t;xfs_bmbt_get_all(r, s)
DECL|macro|xfs_bmbt_disk_get_state
mdefine_line|#define xfs_bmbt_disk_get_state(r) &bslash;&n;&t;xfs_bmbt_get_state(r)
DECL|macro|xfs_bmbt_disk_get_blockcount
mdefine_line|#define xfs_bmbt_disk_get_blockcount(r) &bslash;&n;&t;xfs_bmbt_get_blockcount(r)
DECL|macro|xfs_bmbt_disk_get_startblock
mdefine_line|#define xfs_bmbt_disk_get_startblock(r) &bslash;&n;&t;xfs_bmbt_get_blockcount(r)
DECL|macro|xfs_bmbt_disk_get_startoff
mdefine_line|#define xfs_bmbt_disk_get_startoff(r) &bslash;&n;&t;xfs_bmbt_get_startoff(r)
macro_line|#endif
r_int
id|xfs_bmbt_increment
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|xfs_bmbt_insert
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|xfs_bmbt_insert_many
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
r_int
comma
id|xfs_bmbt_rec_t
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_void
id|xfs_bmbt_log_block
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
r_struct
id|xfs_buf
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|xfs_bmbt_log_recs
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
r_struct
id|xfs_buf
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_bmbt_lookup_eq
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
id|xfs_fileoff_t
comma
id|xfs_fsblock_t
comma
id|xfs_filblks_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|xfs_bmbt_lookup_ge
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
id|xfs_fileoff_t
comma
id|xfs_fsblock_t
comma
id|xfs_filblks_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|xfs_bmbt_lookup_le
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
id|xfs_fileoff_t
comma
id|xfs_fsblock_t
comma
id|xfs_filblks_t
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Give the bmap btree a new root block.  Copy the old broot contents&n; * down into a real block and make the broot point to it.&n; */
r_int
multiline_comment|/* error */
id|xfs_bmbt_newroot
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
id|logflags
comma
multiline_comment|/* logging flags for inode */
r_int
op_star
id|stat
)paren
suffix:semicolon
multiline_comment|/* return status - 0 fail */
r_void
id|xfs_bmbt_set_all
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_bmbt_irec_t
op_star
id|s
)paren
suffix:semicolon
r_void
id|xfs_bmbt_set_allf
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_fileoff_t
id|o
comma
id|xfs_fsblock_t
id|b
comma
id|xfs_filblks_t
id|c
comma
id|xfs_exntst_t
id|v
)paren
suffix:semicolon
r_void
id|xfs_bmbt_set_blockcount
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_filblks_t
id|v
)paren
suffix:semicolon
r_void
id|xfs_bmbt_set_startblock
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_fsblock_t
id|v
)paren
suffix:semicolon
r_void
id|xfs_bmbt_set_startoff
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_fileoff_t
id|v
)paren
suffix:semicolon
r_void
id|xfs_bmbt_set_state
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_exntst_t
id|v
)paren
suffix:semicolon
macro_line|#if ARCH_CONVERT != ARCH_NOCONVERT
r_void
id|xfs_bmbt_disk_set_all
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_bmbt_irec_t
op_star
id|s
)paren
suffix:semicolon
r_void
id|xfs_bmbt_disk_set_allf
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|r
comma
id|xfs_fileoff_t
id|o
comma
id|xfs_fsblock_t
id|b
comma
id|xfs_filblks_t
id|c
comma
id|xfs_exntst_t
id|v
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_bmbt_disk_set_all
mdefine_line|#define xfs_bmbt_disk_set_all(r, s) &bslash;&n;&t;xfs_bmbt_set_all(r, s)
DECL|macro|xfs_bmbt_disk_set_allf
mdefine_line|#define xfs_bmbt_disk_set_allf(r, o, b, c, v) &bslash;&n;&t;xfs_bmbt_set_allf(r, o, b, c, v)
macro_line|#endif
r_void
id|xfs_bmbt_to_bmdr
c_func
(paren
id|xfs_bmbt_block_t
op_star
comma
r_int
comma
id|xfs_bmdr_block_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|xfs_bmbt_update
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
id|xfs_fileoff_t
comma
id|xfs_fsblock_t
comma
id|xfs_filblks_t
comma
id|xfs_exntst_t
)paren
suffix:semicolon
macro_line|#ifdef XFSDEBUG
multiline_comment|/*&n; * Get the data from the pointed-to record.&n; */
r_int
id|xfs_bmbt_get_rec
c_func
(paren
r_struct
id|xfs_btree_cur
op_star
comma
id|xfs_fileoff_t
op_star
comma
id|xfs_fsblock_t
op_star
comma
id|xfs_filblks_t
op_star
comma
id|xfs_exntst_t
op_star
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Search an extent list for the extent which includes block&n; * bno.&n; */
id|xfs_bmbt_rec_t
op_star
id|xfs_bmap_do_search_extents
c_func
(paren
id|xfs_bmbt_rec_t
op_star
comma
id|xfs_extnum_t
comma
id|xfs_extnum_t
comma
id|xfs_fileoff_t
comma
r_int
op_star
comma
id|xfs_extnum_t
op_star
comma
id|xfs_bmbt_irec_t
op_star
comma
id|xfs_bmbt_irec_t
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_BMAP_BTREE_H__ */
eof
