multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_AG_H__
DECL|macro|__XFS_AG_H__
mdefine_line|#define __XFS_AG_H__
multiline_comment|/*&n; * Allocation group header&n; * This is divided into three structures, placed in sequential 512-byte&n; * buffers after a copy of the superblock (also in a 512-byte buffer).&n; */
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
DECL|macro|XFS_AGF_MAGIC
mdefine_line|#define XFS_AGF_MAGIC&t;0x58414746&t;/* &squot;XAGF&squot; */
DECL|macro|XFS_AGI_MAGIC
mdefine_line|#define XFS_AGI_MAGIC&t;0x58414749&t;/* &squot;XAGI&squot; */
DECL|macro|XFS_AGF_VERSION
mdefine_line|#define XFS_AGF_VERSION 1
DECL|macro|XFS_AGI_VERSION
mdefine_line|#define XFS_AGI_VERSION 1
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGF_GOOD_VERSION)
r_int
id|xfs_agf_good_version
c_func
(paren
r_int
id|v
)paren
suffix:semicolon
DECL|macro|XFS_AGF_GOOD_VERSION
mdefine_line|#define XFS_AGF_GOOD_VERSION(v) xfs_agf_good_version(v)
macro_line|#else
DECL|macro|XFS_AGF_GOOD_VERSION
mdefine_line|#define XFS_AGF_GOOD_VERSION(v)&t;&t;((v) == XFS_AGF_VERSION)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGI_GOOD_VERSION)
r_int
id|xfs_agi_good_version
c_func
(paren
r_int
id|v
)paren
suffix:semicolon
DECL|macro|XFS_AGI_GOOD_VERSION
mdefine_line|#define XFS_AGI_GOOD_VERSION(v) xfs_agi_good_version(v)
macro_line|#else
DECL|macro|XFS_AGI_GOOD_VERSION
mdefine_line|#define XFS_AGI_GOOD_VERSION(v)&t;&t;((v) == XFS_AGI_VERSION)
macro_line|#endif
multiline_comment|/*&n; * Btree number 0 is bno, 1 is cnt.  This value gives the size of the&n; * arrays below.&n; */
DECL|macro|XFS_BTNUM_AGF
mdefine_line|#define XFS_BTNUM_AGF&t;((int)XFS_BTNUM_CNTi + 1)
multiline_comment|/*&n; * The second word of agf_levels in the first a.g. overlaps the EFS&n; * superblock&squot;s magic number.  Since the magic numbers valid for EFS&n; * are &gt; 64k, our value cannot be confused for an EFS superblock&squot;s.&n; */
DECL|struct|xfs_agf
r_typedef
r_struct
id|xfs_agf
(brace
multiline_comment|/*&n;&t; * Common allocation group header information&n;&t; */
DECL|member|agf_magicnum
id|__uint32_t
id|agf_magicnum
suffix:semicolon
multiline_comment|/* magic number == XFS_AGF_MAGIC */
DECL|member|agf_versionnum
id|__uint32_t
id|agf_versionnum
suffix:semicolon
multiline_comment|/* header version == XFS_AGF_VERSION */
DECL|member|agf_seqno
id|xfs_agnumber_t
id|agf_seqno
suffix:semicolon
multiline_comment|/* sequence # starting from 0 */
DECL|member|agf_length
id|xfs_agblock_t
id|agf_length
suffix:semicolon
multiline_comment|/* size in blocks of a.g. */
multiline_comment|/*&n;&t; * Freespace information&n;&t; */
DECL|member|agf_roots
id|xfs_agblock_t
id|agf_roots
(braket
id|XFS_BTNUM_AGF
)braket
suffix:semicolon
multiline_comment|/* root blocks */
DECL|member|agf_spare0
id|__uint32_t
id|agf_spare0
suffix:semicolon
multiline_comment|/* spare field */
DECL|member|agf_levels
id|__uint32_t
id|agf_levels
(braket
id|XFS_BTNUM_AGF
)braket
suffix:semicolon
multiline_comment|/* btree levels */
DECL|member|agf_spare1
id|__uint32_t
id|agf_spare1
suffix:semicolon
multiline_comment|/* spare field */
DECL|member|agf_flfirst
id|__uint32_t
id|agf_flfirst
suffix:semicolon
multiline_comment|/* first freelist block&squot;s index */
DECL|member|agf_fllast
id|__uint32_t
id|agf_fllast
suffix:semicolon
multiline_comment|/* last freelist block&squot;s index */
DECL|member|agf_flcount
id|__uint32_t
id|agf_flcount
suffix:semicolon
multiline_comment|/* count of blocks in freelist */
DECL|member|agf_freeblks
id|xfs_extlen_t
id|agf_freeblks
suffix:semicolon
multiline_comment|/* total free blocks */
DECL|member|agf_longest
id|xfs_extlen_t
id|agf_longest
suffix:semicolon
multiline_comment|/* longest free space */
DECL|typedef|xfs_agf_t
)brace
id|xfs_agf_t
suffix:semicolon
DECL|macro|XFS_AGF_MAGICNUM
mdefine_line|#define XFS_AGF_MAGICNUM&t;0x00000001
DECL|macro|XFS_AGF_VERSIONNUM
mdefine_line|#define XFS_AGF_VERSIONNUM&t;0x00000002
DECL|macro|XFS_AGF_SEQNO
mdefine_line|#define XFS_AGF_SEQNO&t;&t;0x00000004
DECL|macro|XFS_AGF_LENGTH
mdefine_line|#define XFS_AGF_LENGTH&t;&t;0x00000008
DECL|macro|XFS_AGF_ROOTS
mdefine_line|#define XFS_AGF_ROOTS&t;&t;0x00000010
DECL|macro|XFS_AGF_LEVELS
mdefine_line|#define XFS_AGF_LEVELS&t;&t;0x00000020
DECL|macro|XFS_AGF_FLFIRST
mdefine_line|#define XFS_AGF_FLFIRST&t;&t;0x00000040
DECL|macro|XFS_AGF_FLLAST
mdefine_line|#define XFS_AGF_FLLAST&t;&t;0x00000080
DECL|macro|XFS_AGF_FLCOUNT
mdefine_line|#define XFS_AGF_FLCOUNT&t;&t;0x00000100
DECL|macro|XFS_AGF_FREEBLKS
mdefine_line|#define XFS_AGF_FREEBLKS&t;0x00000200
DECL|macro|XFS_AGF_LONGEST
mdefine_line|#define XFS_AGF_LONGEST&t;&t;0x00000400
DECL|macro|XFS_AGF_NUM_BITS
mdefine_line|#define XFS_AGF_NUM_BITS&t;11
DECL|macro|XFS_AGF_ALL_BITS
mdefine_line|#define XFS_AGF_ALL_BITS&t;((1 &lt;&lt; XFS_AGF_NUM_BITS) - 1)
multiline_comment|/* disk block (xfs_daddr_t) in the AG */
DECL|macro|XFS_AGF_DADDR
mdefine_line|#define XFS_AGF_DADDR&t;&t;((xfs_daddr_t)1)
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGF_BLOCK)
id|xfs_agblock_t
id|xfs_agf_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_AGF_BLOCK
mdefine_line|#define XFS_AGF_BLOCK(mp)&t;xfs_agf_block(mp)
macro_line|#else
DECL|macro|XFS_AGF_BLOCK
mdefine_line|#define XFS_AGF_BLOCK(mp)&t;XFS_HDR_BLOCK(mp, XFS_AGF_DADDR)
macro_line|#endif
multiline_comment|/*&n; * Size of the unlinked inode hash table in the agi.&n; */
DECL|macro|XFS_AGI_UNLINKED_BUCKETS
mdefine_line|#define XFS_AGI_UNLINKED_BUCKETS&t;64
DECL|struct|xfs_agi
r_typedef
r_struct
id|xfs_agi
(brace
multiline_comment|/*&n;&t; * Common allocation group header information&n;&t; */
DECL|member|agi_magicnum
id|__uint32_t
id|agi_magicnum
suffix:semicolon
multiline_comment|/* magic number == XFS_AGI_MAGIC */
DECL|member|agi_versionnum
id|__uint32_t
id|agi_versionnum
suffix:semicolon
multiline_comment|/* header version == XFS_AGI_VERSION */
DECL|member|agi_seqno
id|xfs_agnumber_t
id|agi_seqno
suffix:semicolon
multiline_comment|/* sequence # starting from 0 */
DECL|member|agi_length
id|xfs_agblock_t
id|agi_length
suffix:semicolon
multiline_comment|/* size in blocks of a.g. */
multiline_comment|/*&n;&t; * Inode information&n;&t; * Inodes are mapped by interpreting the inode number, so no&n;&t; * mapping data is needed here.&n;&t; */
DECL|member|agi_count
id|xfs_agino_t
id|agi_count
suffix:semicolon
multiline_comment|/* count of allocated inodes */
DECL|member|agi_root
id|xfs_agblock_t
id|agi_root
suffix:semicolon
multiline_comment|/* root of inode btree */
DECL|member|agi_level
id|__uint32_t
id|agi_level
suffix:semicolon
multiline_comment|/* levels in inode btree */
DECL|member|agi_freecount
id|xfs_agino_t
id|agi_freecount
suffix:semicolon
multiline_comment|/* number of free inodes */
DECL|member|agi_newino
id|xfs_agino_t
id|agi_newino
suffix:semicolon
multiline_comment|/* new inode just allocated */
DECL|member|agi_dirino
id|xfs_agino_t
id|agi_dirino
suffix:semicolon
multiline_comment|/* last directory inode chunk */
multiline_comment|/*&n;&t; * Hash table of inodes which have been unlinked but are&n;&t; * still being referenced.&n;&t; */
DECL|member|agi_unlinked
id|xfs_agino_t
id|agi_unlinked
(braket
id|XFS_AGI_UNLINKED_BUCKETS
)braket
suffix:semicolon
DECL|typedef|xfs_agi_t
)brace
id|xfs_agi_t
suffix:semicolon
DECL|macro|XFS_AGI_MAGICNUM
mdefine_line|#define XFS_AGI_MAGICNUM&t;0x00000001
DECL|macro|XFS_AGI_VERSIONNUM
mdefine_line|#define XFS_AGI_VERSIONNUM&t;0x00000002
DECL|macro|XFS_AGI_SEQNO
mdefine_line|#define XFS_AGI_SEQNO&t;&t;0x00000004
DECL|macro|XFS_AGI_LENGTH
mdefine_line|#define XFS_AGI_LENGTH&t;&t;0x00000008
DECL|macro|XFS_AGI_COUNT
mdefine_line|#define XFS_AGI_COUNT&t;&t;0x00000010
DECL|macro|XFS_AGI_ROOT
mdefine_line|#define XFS_AGI_ROOT&t;&t;0x00000020
DECL|macro|XFS_AGI_LEVEL
mdefine_line|#define XFS_AGI_LEVEL&t;&t;0x00000040
DECL|macro|XFS_AGI_FREECOUNT
mdefine_line|#define XFS_AGI_FREECOUNT&t;0x00000080
DECL|macro|XFS_AGI_NEWINO
mdefine_line|#define XFS_AGI_NEWINO&t;&t;0x00000100
DECL|macro|XFS_AGI_DIRINO
mdefine_line|#define XFS_AGI_DIRINO&t;&t;0x00000200
DECL|macro|XFS_AGI_UNLINKED
mdefine_line|#define XFS_AGI_UNLINKED&t;0x00000400
DECL|macro|XFS_AGI_NUM_BITS
mdefine_line|#define XFS_AGI_NUM_BITS&t;11
DECL|macro|XFS_AGI_ALL_BITS
mdefine_line|#define XFS_AGI_ALL_BITS&t;((1 &lt;&lt; XFS_AGI_NUM_BITS) - 1)
multiline_comment|/* disk block (xfs_daddr_t) in the AG */
DECL|macro|XFS_AGI_DADDR
mdefine_line|#define XFS_AGI_DADDR&t;&t;((xfs_daddr_t)2)
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGI_BLOCK)
id|xfs_agblock_t
id|xfs_agi_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_AGI_BLOCK
mdefine_line|#define XFS_AGI_BLOCK(mp)&t;xfs_agi_block(mp)
macro_line|#else
DECL|macro|XFS_AGI_BLOCK
mdefine_line|#define XFS_AGI_BLOCK(mp)&t;XFS_HDR_BLOCK(mp, XFS_AGI_DADDR)
macro_line|#endif
multiline_comment|/*&n; * The third a.g. block contains the a.g. freelist, an array&n; * of block pointers to blocks owned by the allocation btree code.&n; */
DECL|macro|XFS_AGFL_DADDR
mdefine_line|#define XFS_AGFL_DADDR&t;&t;((xfs_daddr_t)3)
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGFL_BLOCK)
id|xfs_agblock_t
id|xfs_agfl_block
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_AGFL_BLOCK
mdefine_line|#define XFS_AGFL_BLOCK(mp)&t;xfs_agfl_block(mp)
macro_line|#else
DECL|macro|XFS_AGFL_BLOCK
mdefine_line|#define XFS_AGFL_BLOCK(mp)&t;XFS_HDR_BLOCK(mp, XFS_AGFL_DADDR)
macro_line|#endif
DECL|macro|XFS_AGFL_SIZE
mdefine_line|#define XFS_AGFL_SIZE&t;&t;(BBSIZE / sizeof(xfs_agblock_t))
DECL|struct|xfs_agfl
r_typedef
r_struct
id|xfs_agfl
(brace
DECL|member|agfl_bno
id|xfs_agblock_t
id|agfl_bno
(braket
id|XFS_AGFL_SIZE
)braket
suffix:semicolon
DECL|typedef|xfs_agfl_t
)brace
id|xfs_agfl_t
suffix:semicolon
multiline_comment|/*&n; * Busy block/extent entry.  Used in perag to mark blocks that have been freed&n; * but whose transactions aren&squot;t committed to disk yet.&n; */
DECL|struct|xfs_perag_busy
r_typedef
r_struct
id|xfs_perag_busy
(brace
DECL|member|busy_start
id|xfs_agblock_t
id|busy_start
suffix:semicolon
DECL|member|busy_length
id|xfs_extlen_t
id|busy_length
suffix:semicolon
DECL|member|busy_tp
r_struct
id|xfs_trans
op_star
id|busy_tp
suffix:semicolon
multiline_comment|/* transaction that did the free */
DECL|typedef|xfs_perag_busy_t
)brace
id|xfs_perag_busy_t
suffix:semicolon
multiline_comment|/*&n; * Per-ag incore structure, copies of information in agf and agi,&n; * to improve the performance of allocation group selection.&n; *&n; * pick sizes which fit in allocation buckets well&n; */
macro_line|#if (BITS_PER_LONG == 32)
DECL|macro|XFS_PAGB_NUM_SLOTS
mdefine_line|#define XFS_PAGB_NUM_SLOTS&t;84
macro_line|#elif (BITS_PER_LONG == 64)
DECL|macro|XFS_PAGB_NUM_SLOTS
mdefine_line|#define XFS_PAGB_NUM_SLOTS&t;128
macro_line|#endif
DECL|struct|xfs_perag
r_typedef
r_struct
id|xfs_perag
(brace
DECL|member|pagf_init
r_char
id|pagf_init
suffix:semicolon
multiline_comment|/* this agf&squot;s entry is initialized */
DECL|member|pagi_init
r_char
id|pagi_init
suffix:semicolon
multiline_comment|/* this agi&squot;s entry is initialized */
DECL|member|pagf_metadata
r_char
id|pagf_metadata
suffix:semicolon
multiline_comment|/* the agf is prefered to be metadata */
DECL|member|pagi_inodeok
r_char
id|pagi_inodeok
suffix:semicolon
multiline_comment|/* The agi is ok for inodes */
DECL|member|pagf_levels
id|__uint8_t
id|pagf_levels
(braket
id|XFS_BTNUM_AGF
)braket
suffix:semicolon
multiline_comment|/* # of levels in bno &amp; cnt btree */
DECL|member|pagf_flcount
id|__uint32_t
id|pagf_flcount
suffix:semicolon
multiline_comment|/* count of blocks in freelist */
DECL|member|pagf_freeblks
id|xfs_extlen_t
id|pagf_freeblks
suffix:semicolon
multiline_comment|/* total free blocks */
DECL|member|pagf_longest
id|xfs_extlen_t
id|pagf_longest
suffix:semicolon
multiline_comment|/* longest free space */
DECL|member|pagi_freecount
id|xfs_agino_t
id|pagi_freecount
suffix:semicolon
multiline_comment|/* number of free inodes */
macro_line|#ifdef __KERNEL__
DECL|member|pagb_lock
id|lock_t
id|pagb_lock
suffix:semicolon
multiline_comment|/* lock for pagb_list */
macro_line|#endif
DECL|member|pagb_count
r_int
id|pagb_count
suffix:semicolon
multiline_comment|/* pagb slots in use */
DECL|member|pagb_list
id|xfs_perag_busy_t
op_star
id|pagb_list
suffix:semicolon
multiline_comment|/* unstable blocks */
DECL|typedef|xfs_perag_t
)brace
id|xfs_perag_t
suffix:semicolon
DECL|macro|XFS_AG_MIN_BYTES
mdefine_line|#define XFS_AG_MIN_BYTES&t;(1LL &lt;&lt; 24)&t;/* 16 MB */
DECL|macro|XFS_AG_BEST_BYTES
mdefine_line|#define XFS_AG_BEST_BYTES&t;(1LL &lt;&lt; 30)&t;/*  1 GB */
DECL|macro|XFS_AG_MAX_BYTES
mdefine_line|#define XFS_AG_MAX_BYTES&t;(1LL &lt;&lt; 32)&t;/*  4 GB */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AG_MIN_BLOCKS)
id|xfs_extlen_t
id|xfs_ag_min_blocks
c_func
(paren
r_int
id|bl
)paren
suffix:semicolon
DECL|macro|XFS_AG_MIN_BLOCKS
mdefine_line|#define XFS_AG_MIN_BLOCKS(bl)&t;&t;xfs_ag_min_blocks(bl)
macro_line|#else
DECL|macro|XFS_AG_MIN_BLOCKS
mdefine_line|#define XFS_AG_MIN_BLOCKS(bl)&t;((xfs_extlen_t)(XFS_AG_MIN_BYTES &gt;&gt; bl))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AG_BEST_BLOCKS)
id|xfs_extlen_t
id|xfs_ag_best_blocks
c_func
(paren
r_int
id|bl
comma
id|xfs_drfsbno_t
id|blks
)paren
suffix:semicolon
DECL|macro|XFS_AG_BEST_BLOCKS
mdefine_line|#define XFS_AG_BEST_BLOCKS(bl,blks)&t;xfs_ag_best_blocks(bl,blks)
macro_line|#else
multiline_comment|/*--#define&t;XFS_AG_BEST_BLOCKS(bl)&t;((xfs_extlen_t)(XFS_AG_BEST_BYTES &gt;&gt; bl))*/
multiline_comment|/*&n; * Best is XFS_AG_BEST_BLOCKS at and below 64 Gigabyte filesystems, and&n; * XFS_AG_MAX_BLOCKS above 64 Gigabytes.&n; */
DECL|macro|XFS_AG_BEST_BLOCKS
mdefine_line|#define XFS_AG_BEST_BLOCKS(bl,blks)&t;((xfs_extlen_t)((1LL &lt;&lt; (36 - bl)) &gt;= &bslash;&n;&t;&t;&t;&t;&t;&t;&t;blks) ? &bslash;&n;&t;&t;&t;&t;&t;&t;&t;((xfs_extlen_t)(XFS_AG_BEST_BYTES &gt;&gt; bl)) : &bslash;&n;&t;&t;&t;&t;&t;&t;&t;XFS_AG_MAX_BLOCKS(bl))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AG_MAX_BLOCKS)
id|xfs_extlen_t
id|xfs_ag_max_blocks
c_func
(paren
r_int
id|bl
)paren
suffix:semicolon
DECL|macro|XFS_AG_MAX_BLOCKS
mdefine_line|#define XFS_AG_MAX_BLOCKS(bl)&t;&t;xfs_ag_max_blocks(bl)
macro_line|#else
DECL|macro|XFS_AG_MAX_BLOCKS
mdefine_line|#define XFS_AG_MAX_BLOCKS(bl)&t;((xfs_extlen_t)(XFS_AG_MAX_BYTES &gt;&gt; bl))
macro_line|#endif
DECL|macro|XFS_MAX_AGNUMBER
mdefine_line|#define XFS_MAX_AGNUMBER&t;((xfs_agnumber_t)(NULLAGNUMBER - 1))
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AG_MAXLEVELS)
r_int
id|xfs_ag_maxlevels
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_AG_MAXLEVELS
mdefine_line|#define XFS_AG_MAXLEVELS(mp)&t;&t;xfs_ag_maxlevels(mp)
macro_line|#else
DECL|macro|XFS_AG_MAXLEVELS
mdefine_line|#define XFS_AG_MAXLEVELS(mp)&t;((mp)-&gt;m_ag_maxlevels)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MIN_FREELIST)
r_int
id|xfs_min_freelist
c_func
(paren
id|xfs_agf_t
op_star
id|a
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_MIN_FREELIST
mdefine_line|#define XFS_MIN_FREELIST(a,mp)&t;&t;xfs_min_freelist(a,mp)
macro_line|#else
DECL|macro|XFS_MIN_FREELIST
mdefine_line|#define XFS_MIN_FREELIST(a,mp)&t;&bslash;&n;&t;XFS_MIN_FREELIST_RAW(&t;&bslash;&n;&t;&t;INT_GET((a)-&gt;agf_levels[XFS_BTNUM_BNOi], ARCH_CONVERT), &bslash;&n;&t;&t;INT_GET((a)-&gt;agf_levels[XFS_BTNUM_CNTi], ARCH_CONVERT), mp)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MIN_FREELIST_PAG)
r_int
id|xfs_min_freelist_pag
c_func
(paren
id|xfs_perag_t
op_star
id|pag
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_MIN_FREELIST_PAG
mdefine_line|#define XFS_MIN_FREELIST_PAG(pag,mp)&t;xfs_min_freelist_pag(pag,mp)
macro_line|#else
DECL|macro|XFS_MIN_FREELIST_PAG
mdefine_line|#define XFS_MIN_FREELIST_PAG(pag,mp)&t;&bslash;&n;&t;XFS_MIN_FREELIST_RAW((uint_t)(pag)-&gt;pagf_levels[XFS_BTNUM_BNOi], &bslash;&n;&t;&t;&t;     (uint_t)(pag)-&gt;pagf_levels[XFS_BTNUM_CNTi], mp)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MIN_FREELIST_RAW)
r_int
id|xfs_min_freelist_raw
c_func
(paren
r_int
id|bl
comma
r_int
id|cl
comma
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_MIN_FREELIST_RAW
mdefine_line|#define XFS_MIN_FREELIST_RAW(bl,cl,mp)&t;xfs_min_freelist_raw(bl,cl,mp)
macro_line|#else
DECL|macro|XFS_MIN_FREELIST_RAW
mdefine_line|#define XFS_MIN_FREELIST_RAW(bl,cl,mp)&t;&bslash;&n;&t;(MIN(bl + 1, XFS_AG_MAXLEVELS(mp)) + &bslash;&n;&t; MIN(cl + 1, XFS_AG_MAXLEVELS(mp)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGB_TO_FSB)
id|xfs_fsblock_t
id|xfs_agb_to_fsb
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_agnumber_t
id|agno
comma
id|xfs_agblock_t
id|agbno
)paren
suffix:semicolon
DECL|macro|XFS_AGB_TO_FSB
mdefine_line|#define XFS_AGB_TO_FSB(mp,agno,agbno)&t;xfs_agb_to_fsb(mp,agno,agbno)
macro_line|#else
DECL|macro|XFS_AGB_TO_FSB
mdefine_line|#define XFS_AGB_TO_FSB(mp,agno,agbno) &bslash;&n;&t;(((xfs_fsblock_t)(agno) &lt;&lt; (mp)-&gt;m_sb.sb_agblklog) | (agbno))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FSB_TO_AGNO)
id|xfs_agnumber_t
id|xfs_fsb_to_agno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_fsblock_t
id|fsbno
)paren
suffix:semicolon
DECL|macro|XFS_FSB_TO_AGNO
mdefine_line|#define XFS_FSB_TO_AGNO(mp,fsbno)&t;xfs_fsb_to_agno(mp,fsbno)
macro_line|#else
DECL|macro|XFS_FSB_TO_AGNO
mdefine_line|#define XFS_FSB_TO_AGNO(mp,fsbno) &bslash;&n;&t;((xfs_agnumber_t)((fsbno) &gt;&gt; (mp)-&gt;m_sb.sb_agblklog))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_FSB_TO_AGBNO)
id|xfs_agblock_t
id|xfs_fsb_to_agbno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_fsblock_t
id|fsbno
)paren
suffix:semicolon
DECL|macro|XFS_FSB_TO_AGBNO
mdefine_line|#define XFS_FSB_TO_AGBNO(mp,fsbno)&t;xfs_fsb_to_agbno(mp,fsbno)
macro_line|#else
DECL|macro|XFS_FSB_TO_AGBNO
mdefine_line|#define XFS_FSB_TO_AGBNO(mp,fsbno) &bslash;&n;&t;((xfs_agblock_t)((fsbno) &amp; XFS_MASK32LO((mp)-&gt;m_sb.sb_agblklog)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AGB_TO_DADDR)
id|xfs_daddr_t
id|xfs_agb_to_daddr
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_agnumber_t
id|agno
comma
id|xfs_agblock_t
id|agbno
)paren
suffix:semicolon
DECL|macro|XFS_AGB_TO_DADDR
mdefine_line|#define XFS_AGB_TO_DADDR(mp,agno,agbno) xfs_agb_to_daddr(mp,agno,agbno)
macro_line|#else
DECL|macro|XFS_AGB_TO_DADDR
mdefine_line|#define XFS_AGB_TO_DADDR(mp,agno,agbno) &bslash;&n;&t;((xfs_daddr_t)(XFS_FSB_TO_BB(mp, &bslash;&n;&t;&t;(xfs_fsblock_t)(agno) * (mp)-&gt;m_sb.sb_agblocks + (agbno))))
macro_line|#endif
multiline_comment|/*&n; * XFS_DADDR_TO_AGNO and XFS_DADDR_TO_AGBNO moved to xfs_mount.h&n; * to avoid header file ordering change&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AG_DADDR)
id|xfs_daddr_t
id|xfs_ag_daddr
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_agnumber_t
id|agno
comma
id|xfs_daddr_t
id|d
)paren
suffix:semicolon
DECL|macro|XFS_AG_DADDR
mdefine_line|#define XFS_AG_DADDR(mp,agno,d)&t;&t;xfs_ag_daddr(mp,agno,d)
macro_line|#else
DECL|macro|XFS_AG_DADDR
mdefine_line|#define XFS_AG_DADDR(mp,agno,d) (XFS_AGB_TO_DADDR(mp, agno, 0) + (d))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_AGF)
id|xfs_agf_t
op_star
id|xfs_buf_to_agf
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_AGF
mdefine_line|#define XFS_BUF_TO_AGF(bp)&t;&t;xfs_buf_to_agf(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_AGF
mdefine_line|#define XFS_BUF_TO_AGF(bp)&t;((xfs_agf_t *)XFS_BUF_PTR(bp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_AGI)
id|xfs_agi_t
op_star
id|xfs_buf_to_agi
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_AGI
mdefine_line|#define XFS_BUF_TO_AGI(bp)&t;&t;xfs_buf_to_agi(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_AGI
mdefine_line|#define XFS_BUF_TO_AGI(bp)&t;((xfs_agi_t *)XFS_BUF_PTR(bp))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BUF_TO_AGFL)
id|xfs_agfl_t
op_star
id|xfs_buf_to_agfl
c_func
(paren
r_struct
id|xfs_buf
op_star
id|bp
)paren
suffix:semicolon
DECL|macro|XFS_BUF_TO_AGFL
mdefine_line|#define XFS_BUF_TO_AGFL(bp)&t;&t;xfs_buf_to_agfl(bp)
macro_line|#else
DECL|macro|XFS_BUF_TO_AGFL
mdefine_line|#define XFS_BUF_TO_AGFL(bp)&t;((xfs_agfl_t *)XFS_BUF_PTR(bp))
macro_line|#endif
multiline_comment|/*&n; * For checking for bad ranges of xfs_daddr_t&squot;s, covering multiple&n; * allocation groups or a single xfs_daddr_t that&squot;s a superblock copy.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_AG_CHECK_DADDR)
r_void
id|xfs_ag_check_daddr
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_daddr_t
id|d
comma
id|xfs_extlen_t
id|len
)paren
suffix:semicolon
DECL|macro|XFS_AG_CHECK_DADDR
mdefine_line|#define XFS_AG_CHECK_DADDR(mp,d,len)&t;xfs_ag_check_daddr(mp,d,len)
macro_line|#else
DECL|macro|XFS_AG_CHECK_DADDR
mdefine_line|#define XFS_AG_CHECK_DADDR(mp,d,len)&t;&bslash;&n;&t;((len) == 1 ? &bslash;&n;&t;    ASSERT((d) == XFS_SB_DADDR || &bslash;&n;&t;&t;   XFS_DADDR_TO_AGBNO(mp, d) != XFS_SB_DADDR) : &bslash;&n;&t;    ASSERT(XFS_DADDR_TO_AGNO(mp, d) == &bslash;&n;&t;&t;   XFS_DADDR_TO_AGNO(mp, (d) + (len) - 1)))
macro_line|#endif
macro_line|#endif&t;/* __XFS_AG_H__ */
eof
