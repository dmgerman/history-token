multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_RTALLOC_H__
DECL|macro|__XFS_RTALLOC_H__
mdefine_line|#define __XFS_RTALLOC_H__
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/* Min and max rt extent sizes, specified in bytes */
DECL|macro|XFS_MAX_RTEXTSIZE
mdefine_line|#define XFS_MAX_RTEXTSIZE&t;(1024 * 1024 * 1024)&t;/* 1GB */
DECL|macro|XFS_DFL_RTEXTSIZE
mdefine_line|#define XFS_DFL_RTEXTSIZE&t;(64 * 1024)&t;&t;/* 64KB */
DECL|macro|XFS_MIN_RTEXTSIZE
mdefine_line|#define XFS_MIN_RTEXTSIZE&t;(4 * 1024)&t;&t;/* 4KB */
multiline_comment|/*&n; * Constants for bit manipulations.&n; */
DECL|macro|XFS_NBBYLOG
mdefine_line|#define XFS_NBBYLOG&t;3&t;&t;/* log2(NBBY) */
DECL|macro|XFS_WORDLOG
mdefine_line|#define XFS_WORDLOG&t;2&t;&t;/* log2(sizeof(xfs_rtword_t)) */
DECL|macro|XFS_NBWORDLOG
mdefine_line|#define XFS_NBWORDLOG&t;(XFS_NBBYLOG + XFS_WORDLOG)
DECL|macro|XFS_NBWORD
mdefine_line|#define XFS_NBWORD&t;(1 &lt;&lt; XFS_NBWORDLOG)
DECL|macro|XFS_WORDMASK
mdefine_line|#define XFS_WORDMASK&t;((1 &lt;&lt; XFS_WORDLOG) - 1)
DECL|macro|XFS_BLOCKSIZE
mdefine_line|#define XFS_BLOCKSIZE(mp)&t;((mp)-&gt;m_sb.sb_blocksize)
DECL|macro|XFS_BLOCKMASK
mdefine_line|#define XFS_BLOCKMASK(mp)&t;((mp)-&gt;m_blockmask)
DECL|macro|XFS_BLOCKWSIZE
mdefine_line|#define XFS_BLOCKWSIZE(mp)&t;((mp)-&gt;m_blockwsize)
DECL|macro|XFS_BLOCKWMASK
mdefine_line|#define XFS_BLOCKWMASK(mp)&t;((mp)-&gt;m_blockwmask)
multiline_comment|/*&n; * Summary and bit manipulation macros.&n; */
DECL|macro|XFS_SUMOFFS
mdefine_line|#define XFS_SUMOFFS(mp,ls,bb)&t;((int)((ls) * (mp)-&gt;m_sb.sb_rbmblocks + (bb)))
DECL|macro|XFS_SUMOFFSTOBLOCK
mdefine_line|#define XFS_SUMOFFSTOBLOCK(mp,s)&t;&bslash;&n;&t;(((s) * (uint)sizeof(xfs_suminfo_t)) &gt;&gt; (mp)-&gt;m_sb.sb_blocklog)
DECL|macro|XFS_SUMPTR
mdefine_line|#define XFS_SUMPTR(mp,bp,so)&t;&bslash;&n;&t;((xfs_suminfo_t *)((char *)XFS_BUF_PTR(bp) + &bslash;&n;&t;&t;(((so) * (uint)sizeof(xfs_suminfo_t)) &amp; XFS_BLOCKMASK(mp))))
DECL|macro|XFS_BITTOBLOCK
mdefine_line|#define XFS_BITTOBLOCK(mp,bi)&t;((bi) &gt;&gt; (mp)-&gt;m_blkbit_log)
DECL|macro|XFS_BLOCKTOBIT
mdefine_line|#define XFS_BLOCKTOBIT(mp,bb)&t;((bb) &lt;&lt; (mp)-&gt;m_blkbit_log)
DECL|macro|XFS_BITTOWORD
mdefine_line|#define XFS_BITTOWORD(mp,bi)&t;&bslash;&n;&t;((int)(((bi) &gt;&gt; XFS_NBWORDLOG) &amp; XFS_BLOCKWMASK(mp)))
DECL|macro|XFS_RTMIN
mdefine_line|#define XFS_RTMIN(a,b)&t;((a) &lt; (b) ? (a) : (b))
DECL|macro|XFS_RTMAX
mdefine_line|#define XFS_RTMAX(a,b)&t;((a) &gt; (b) ? (a) : (b))
DECL|macro|XFS_RTLOBIT
mdefine_line|#define XFS_RTLOBIT(w)&t;xfs_lowbit32(w)
DECL|macro|XFS_RTHIBIT
mdefine_line|#define XFS_RTHIBIT(w)&t;xfs_highbit32(w)
macro_line|#if XFS_BIG_FILESYSTEMS
DECL|macro|XFS_RTBLOCKLOG
mdefine_line|#define XFS_RTBLOCKLOG(b)&t;xfs_highbit64(b)
macro_line|#else
DECL|macro|XFS_RTBLOCKLOG
mdefine_line|#define XFS_RTBLOCKLOG(b)&t;xfs_highbit32(b)
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_XFS_RT
multiline_comment|/*&n; * Function prototypes for exported functions.&n; */
multiline_comment|/*&n; * Allocate an extent in the realtime subvolume, with the usual allocation&n; * parameters.&t;The length units are all in realtime extents, as is the&n; * result block number.&n; */
r_int
multiline_comment|/* error */
id|xfs_rtallocate_extent
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_rtblock_t
id|bno
comma
multiline_comment|/* starting block number to allocate */
id|xfs_extlen_t
id|minlen
comma
multiline_comment|/* minimum length to allocate */
id|xfs_extlen_t
id|maxlen
comma
multiline_comment|/* maximum length to allocate */
id|xfs_extlen_t
op_star
id|len
comma
multiline_comment|/* out: actual length allocated */
id|xfs_alloctype_t
id|type
comma
multiline_comment|/* allocation type XFS_ALLOCTYPE... */
r_int
id|wasdel
comma
multiline_comment|/* was a delayed allocation extent */
id|xfs_extlen_t
id|prod
comma
multiline_comment|/* extent product factor */
id|xfs_rtblock_t
op_star
id|rtblock
)paren
suffix:semicolon
multiline_comment|/* out: start block allocated */
multiline_comment|/*&n; * Free an extent in the realtime subvolume.  Length is expressed in&n; * realtime extents, as is the block number.&n; */
r_int
multiline_comment|/* error */
id|xfs_rtfree_extent
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_rtblock_t
id|bno
comma
multiline_comment|/* starting block number to free */
id|xfs_extlen_t
id|len
)paren
suffix:semicolon
multiline_comment|/* length of extent freed */
multiline_comment|/*&n; * Initialize realtime fields in the mount structure.&n; */
r_int
multiline_comment|/* error */
id|xfs_rtmount_init
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
multiline_comment|/* file system mount structure */
multiline_comment|/*&n; * Get the bitmap and summary inodes into the mount structure&n; * at mount time.&n; */
r_int
multiline_comment|/* error */
id|xfs_rtmount_inodes
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
multiline_comment|/* file system mount structure */
multiline_comment|/*&n; * Pick an extent for allocation at the start of a new realtime file.&n; * Use the sequence number stored in the atime field of the bitmap inode.&n; * Translate this to a fraction of the rtextents, and return the product&n; * of rtextents and the fraction.&n; * The fraction sequence is 0, 1/2, 1/4, 3/4, 1/8, ..., 7/8, 1/16, ...&n; */
r_int
multiline_comment|/* error */
id|xfs_rtpick_extent
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
id|xfs_extlen_t
id|len
comma
multiline_comment|/* allocation length (rtextents) */
id|xfs_rtblock_t
op_star
id|pick
)paren
suffix:semicolon
multiline_comment|/* result rt extent */
multiline_comment|/*&n; * Debug code: print out the value of a range in the bitmap.&n; */
r_void
id|xfs_rtprint_range
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount structure */
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_rtblock_t
id|start
comma
multiline_comment|/* starting block to print */
id|xfs_extlen_t
id|len
)paren
suffix:semicolon
multiline_comment|/* length to print */
multiline_comment|/*&n; * Debug code: print the summary file.&n; */
r_void
id|xfs_rtprint_summary
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount structure */
r_struct
id|xfs_trans
op_star
id|tp
)paren
suffix:semicolon
multiline_comment|/* transaction pointer */
multiline_comment|/*&n; * Grow the realtime area of the filesystem.&n; */
r_int
id|xfs_growfs_rt
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount structure */
id|xfs_growfs_rt_t
op_star
id|in
)paren
suffix:semicolon
multiline_comment|/* user supplied growfs struct */
macro_line|#else
DECL|macro|xfs_rtallocate_extent
macro_line|# define xfs_rtallocate_extent(t,b,min,max,l,a,f,p,rb)&t;(ENOSYS)
DECL|macro|xfs_rtfree_extent
macro_line|# define xfs_rtfree_extent(t,b,l)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_rtpick_extent
macro_line|# define xfs_rtpick_extent(m,t,l,rb)&t;&t;&t;(ENOSYS)
DECL|macro|xfs_growfs_rt
macro_line|# define xfs_growfs_rt(mp,in)&t;&t;&t;&t;(ENOSYS)
DECL|macro|xfs_rtmount_init
macro_line|# define xfs_rtmount_init(m)&t;(((mp)-&gt;m_sb.sb_rblocks == 0)? 0 : (ENOSYS))
DECL|macro|xfs_rtmount_inodes
macro_line|# define xfs_rtmount_inodes(m)&t;(((mp)-&gt;m_sb.sb_rblocks == 0)? 0 : (ENOSYS))
macro_line|#endif&t;/* CONFIG_XFS_RT */
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_RTALLOC_H__ */
eof
