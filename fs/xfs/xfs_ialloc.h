multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_IALLOC_H__
DECL|macro|__XFS_IALLOC_H__
mdefine_line|#define __XFS_IALLOC_H__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_dinode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * Allocation parameters for inode allocation.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IALLOC_INODES)
r_int
id|xfs_ialloc_inodes
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_IALLOC_INODES
mdefine_line|#define XFS_IALLOC_INODES(mp)&t;xfs_ialloc_inodes(mp)
macro_line|#else
DECL|macro|XFS_IALLOC_INODES
mdefine_line|#define XFS_IALLOC_INODES(mp)&t;((mp)-&gt;m_ialloc_inos)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IALLOC_BLOCKS)
id|xfs_extlen_t
id|xfs_ialloc_blocks
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_IALLOC_BLOCKS
mdefine_line|#define XFS_IALLOC_BLOCKS(mp)&t;xfs_ialloc_blocks(mp)
macro_line|#else
DECL|macro|XFS_IALLOC_BLOCKS
mdefine_line|#define XFS_IALLOC_BLOCKS(mp)&t;((mp)-&gt;m_ialloc_blks)
macro_line|#endif
multiline_comment|/*&n; * For small block file systems, move inodes in clusters of this size.&n; * When we don&squot;t have a lot of memory, however, we go a bit smaller&n; * to reduce the number of AGI and ialloc btree blocks we need to keep&n; * around for xfs_dilocate().  We choose which one to use in&n; * xfs_mount_int().&n; */
DECL|macro|XFS_INODE_BIG_CLUSTER_SIZE
mdefine_line|#define XFS_INODE_BIG_CLUSTER_SIZE&t;8192
DECL|macro|XFS_INODE_SMALL_CLUSTER_SIZE
mdefine_line|#define XFS_INODE_SMALL_CLUSTER_SIZE&t;4096
DECL|macro|XFS_INODE_CLUSTER_SIZE
mdefine_line|#define XFS_INODE_CLUSTER_SIZE(mp)&t;(mp)-&gt;m_inode_cluster_size
multiline_comment|/*&n; * Make an inode pointer out of the buffer/offset.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_MAKE_IPTR)
r_struct
id|xfs_dinode
op_star
id|xfs_make_iptr
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
r_struct
id|xfs_buf
op_star
id|b
comma
r_int
id|o
)paren
suffix:semicolon
DECL|macro|XFS_MAKE_IPTR
mdefine_line|#define XFS_MAKE_IPTR(mp,b,o)&t;&t;xfs_make_iptr(mp,b,o)
macro_line|#else
DECL|macro|XFS_MAKE_IPTR
mdefine_line|#define XFS_MAKE_IPTR(mp,b,o) &bslash;&n;&t;((xfs_dinode_t *)(xfs_buf_offset(b, (o) &lt;&lt; (mp)-&gt;m_sb.sb_inodelog)))
macro_line|#endif
multiline_comment|/*&n; * Find a free (set) bit in the inode bitmask.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_IALLOC_FIND_FREE)
r_int
id|xfs_ialloc_find_free
c_func
(paren
id|xfs_inofree_t
op_star
id|fp
)paren
suffix:semicolon
DECL|macro|XFS_IALLOC_FIND_FREE
mdefine_line|#define XFS_IALLOC_FIND_FREE(fp)&t;xfs_ialloc_find_free(fp)
macro_line|#else
DECL|macro|XFS_IALLOC_FIND_FREE
mdefine_line|#define XFS_IALLOC_FIND_FREE(fp)&t;xfs_lowbit64(*(fp))
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Prototypes for visible xfs_ialloc.c routines.&n; */
multiline_comment|/*&n; * Allocate an inode on disk.&n; * Mode is used to tell whether the new inode will need space, and whether&n; * it is a directory.&n; *&n; * To work within the constraint of one allocation per transaction,&n; * xfs_dialloc() is designed to be called twice if it has to do an&n; * allocation to make more free inodes.&t; If an inode is&n; * available without an allocation, agbp would be set to the current&n; * agbp and alloc_done set to false.&n; * If an allocation needed to be done, agbp would be set to the&n; * inode header of the allocation group and alloc_done set to true.&n; * The caller should then commit the current transaction and allocate a new&n; * transaction.&t; xfs_dialloc() should then be called again with&n; * the agbp value returned from the previous call.&n; *&n; * Once we successfully pick an inode its number is returned and the&n; * on-disk data structures are updated.&t; The inode itself is not read&n; * in, since doing so would break ordering constraints with xfs_reclaim.&n; *&n; * *agbp should be set to NULL on the first call, *alloc_done set to FALSE.&n; */
r_int
multiline_comment|/* error */
id|xfs_dialloc
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_ino_t
id|parent
comma
multiline_comment|/* parent inode (directory) */
id|mode_t
id|mode
comma
multiline_comment|/* mode bits for new inode */
r_int
id|okalloc
comma
multiline_comment|/* ok to allocate more space */
r_struct
id|xfs_buf
op_star
op_star
id|agbp
comma
multiline_comment|/* buf for a.g. inode header */
id|boolean_t
op_star
id|alloc_done
comma
multiline_comment|/* an allocation was done to replenish&n;&t;&t;&t;&t;&t;   the free inodes */
id|xfs_ino_t
op_star
id|inop
)paren
suffix:semicolon
multiline_comment|/* inode number allocated */
multiline_comment|/*&n; * Free disk inode.  Carefully avoids touching the incore inode, all&n; * manipulations incore are the caller&squot;s responsibility.&n; * The on-disk inode is not changed by this operation, only the&n; * btree (free inode mask) is changed.&n; */
r_int
multiline_comment|/* error */
id|xfs_difree
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
id|xfs_ino_t
id|inode
)paren
suffix:semicolon
multiline_comment|/* inode to be freed */
multiline_comment|/*&n; * Return the location of the inode in bno/len/off,&n; * for mapping it into a buffer.&n; */
r_int
id|xfs_dilocate
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
id|xfs_ino_t
id|ino
comma
multiline_comment|/* inode to locate */
id|xfs_fsblock_t
op_star
id|bno
comma
multiline_comment|/* output: block containing inode */
r_int
op_star
id|len
comma
multiline_comment|/* output: num blocks in cluster*/
r_int
op_star
id|off
comma
multiline_comment|/* output: index in block of inode */
id|uint
id|flags
)paren
suffix:semicolon
multiline_comment|/* flags for inode btree lookup */
multiline_comment|/*&n; * Compute and fill in value of m_in_maxlevels.&n; */
r_void
id|xfs_ialloc_compute_maxlevels
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
multiline_comment|/* file system mount structure */
multiline_comment|/*&n; * Log specified fields for the ag hdr (inode section)&n; */
r_void
id|xfs_ialloc_log_agi
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_buf
op_star
id|bp
comma
multiline_comment|/* allocation group header buffer */
r_int
id|fields
)paren
suffix:semicolon
multiline_comment|/* bitmask of fields to log */
multiline_comment|/*&n; * Read in the allocation group header (inode allocation section)&n; */
r_int
multiline_comment|/* error */
id|xfs_ialloc_read_agi
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
id|xfs_agnumber_t
id|agno
comma
multiline_comment|/* allocation group number */
r_struct
id|xfs_buf
op_star
op_star
id|bpp
)paren
suffix:semicolon
multiline_comment|/* allocation group hdr buf */
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_IALLOC_H__ */
eof
