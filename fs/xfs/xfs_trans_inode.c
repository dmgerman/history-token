multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_macros.h&quot;
macro_line|#include &quot;xfs_types.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_ag.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_trans_priv.h&quot;
macro_line|#include &quot;xfs_alloc_btree.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_ialloc_btree.h&quot;
macro_line|#include &quot;xfs_btree.h&quot;
macro_line|#include &quot;xfs_ialloc.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode_item.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#ifdef XFS_TRANS_DEBUG
id|STATIC
r_void
id|xfs_trans_inode_broot_debug
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
suffix:semicolon
macro_line|#else
DECL|macro|xfs_trans_inode_broot_debug
mdefine_line|#define&t;xfs_trans_inode_broot_debug(ip)
macro_line|#endif
multiline_comment|/*&n; * Get and lock the inode for the caller if it is not already&n; * locked within the given transaction.  If it is already locked&n; * within the transaction, just increment its lock recursion count&n; * and return a pointer to it.&n; *&n; * For an inode to be locked in a transaction, the inode lock, as&n; * opposed to the io lock, must be taken exclusively.  This ensures&n; * that the inode can be involved in only 1 transaction at a time.&n; * Lock recursion is handled on the io lock, but only for lock modes&n; * of equal or lesser strength.  That is, you can recur on the io lock&n; * held EXCL with a SHARED request but not vice versa.  Also, if&n; * the inode is already a part of the transaction then you cannot&n; * go from not holding the io lock to having it EXCL or SHARED.&n; *&n; * Use the inode cache routine xfs_inode_incore() to find the inode&n; * if it is already owned by this transaction.&n; *&n; * If we don&squot;t already own the inode, use xfs_iget() to get it.&n; * Since the inode log item structure is embedded in the incore&n; * inode structure and is initialized when the inode is brought&n; * into memory, there is nothing to do with it here.&n; *&n; * If the given transaction pointer is NULL, just call xfs_iget().&n; * This simplifies code which must handle both cases.&n; */
r_int
DECL|function|xfs_trans_iget
id|xfs_trans_iget
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_ino_t
id|ino
comma
id|uint
id|lock_flags
comma
id|xfs_inode_t
op_star
op_star
id|ipp
)paren
(brace
r_int
id|error
suffix:semicolon
id|xfs_inode_t
op_star
id|ip
suffix:semicolon
id|xfs_inode_log_item_t
op_star
id|iip
suffix:semicolon
multiline_comment|/*&n;&t; * If the transaction pointer is NULL, just call the normal&n;&t; * xfs_iget().&n;&t; */
r_if
c_cond
(paren
id|tp
op_eq
l_int|NULL
)paren
(brace
r_return
(paren
id|xfs_iget
c_func
(paren
id|mp
comma
l_int|NULL
comma
id|ino
comma
id|lock_flags
comma
id|ipp
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we find the inode in core with this transaction&n;&t; * pointer in its i_transp field, then we know we already&n;&t; * have it locked.  In this case we just increment the lock&n;&t; * recursion count and return the inode to the caller.&n;&t; * Assert that the inode is already locked in the mode requested&n;&t; * by the caller.  We cannot do lock promotions yet, so&n;&t; * die if someone gets this wrong.&n;&t; */
r_if
c_cond
(paren
(paren
id|ip
op_assign
id|xfs_inode_incore
c_func
(paren
id|tp-&gt;t_mountp
comma
id|ino
comma
id|tp
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Make sure that the inode lock is held EXCL and&n;&t;&t; * that the io lock is never upgraded when the inode&n;&t;&t; * is already a part of the transaction.&n;&t;&t; */
id|ASSERT
c_func
(paren
id|ip-&gt;i_itemp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|lock_flags
op_amp
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_lock
comma
id|MR_UPDATE
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
op_logical_neg
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_EXCL
)paren
)paren
op_logical_or
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_iolock
comma
id|MR_UPDATE
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
op_logical_neg
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_EXCL
)paren
)paren
op_logical_or
(paren
id|ip-&gt;i_itemp-&gt;ili_flags
op_amp
id|XFS_ILI_IOLOCKED_EXCL
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
op_logical_neg
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_SHARED
)paren
)paren
op_logical_or
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_iolock
comma
(paren
id|MR_UPDATE
op_or
id|MR_ACCESS
)paren
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
op_logical_neg
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_SHARED
)paren
)paren
op_logical_or
(paren
id|ip-&gt;i_itemp-&gt;ili_flags
op_amp
id|XFS_ILI_IOLOCKED_ANY
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_flags
op_amp
(paren
id|XFS_IOLOCK_SHARED
op_or
id|XFS_IOLOCK_EXCL
)paren
)paren
(brace
id|ip-&gt;i_itemp-&gt;ili_iolock_recur
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lock_flags
op_amp
id|XFS_ILOCK_EXCL
)paren
(brace
id|ip-&gt;i_itemp-&gt;ili_ilock_recur
op_increment
suffix:semicolon
)brace
op_star
id|ipp
op_assign
id|ip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|lock_flags
op_amp
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
id|error
op_assign
id|xfs_iget
c_func
(paren
id|tp-&gt;t_mountp
comma
id|tp
comma
id|ino
comma
id|lock_flags
comma
op_amp
id|ip
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_return
id|error
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|ip
op_ne
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get a log_item_desc to point at the new item.&n;&t; */
r_if
c_cond
(paren
id|ip-&gt;i_itemp
op_eq
l_int|NULL
)paren
id|xfs_inode_item_init
c_func
(paren
id|ip
comma
id|mp
)paren
suffix:semicolon
id|iip
op_assign
id|ip-&gt;i_itemp
suffix:semicolon
(paren
r_void
)paren
id|xfs_trans_add_item
c_func
(paren
id|tp
comma
(paren
id|xfs_log_item_t
op_star
)paren
(paren
id|iip
)paren
)paren
suffix:semicolon
id|xfs_trans_inode_broot_debug
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the IO lock has been acquired, mark that in&n;&t; * the inode log item so we&squot;ll know to unlock it&n;&t; * when the transaction commits.&n;&t; */
id|ASSERT
c_func
(paren
id|iip-&gt;ili_flags
op_eq
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_EXCL
)paren
(brace
id|iip-&gt;ili_flags
op_or_assign
id|XFS_ILI_IOLOCKED_EXCL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_SHARED
)paren
(brace
id|iip-&gt;ili_flags
op_or_assign
id|XFS_ILI_IOLOCKED_SHARED
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize i_transp so we can find it with xfs_inode_incore()&n;&t; * above.&n;&t; */
id|ip-&gt;i_transp
op_assign
id|tp
suffix:semicolon
op_star
id|ipp
op_assign
id|ip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Add the locked inode to the transaction.&n; * The inode must be locked, and it cannot be associated with any&n; * transaction.  The caller must specify the locks already held&n; * on the inode.&n; */
r_void
DECL|function|xfs_trans_ijoin
id|xfs_trans_ijoin
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_inode_t
op_star
id|ip
comma
id|uint
id|lock_flags
)paren
(brace
id|xfs_inode_log_item_t
op_star
id|iip
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_transp
op_eq
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_lock
comma
id|MR_UPDATE
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|lock_flags
op_amp
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip-&gt;i_itemp
op_eq
l_int|NULL
)paren
id|xfs_inode_item_init
c_func
(paren
id|ip
comma
id|ip-&gt;i_mount
)paren
suffix:semicolon
id|iip
op_assign
id|ip-&gt;i_itemp
suffix:semicolon
id|ASSERT
c_func
(paren
id|iip-&gt;ili_flags
op_eq
l_int|0
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|iip-&gt;ili_ilock_recur
op_eq
l_int|0
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|iip-&gt;ili_iolock_recur
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get a log_item_desc to point at the new item.&n;&t; */
(paren
r_void
)paren
id|xfs_trans_add_item
c_func
(paren
id|tp
comma
(paren
id|xfs_log_item_t
op_star
)paren
(paren
id|iip
)paren
)paren
suffix:semicolon
id|xfs_trans_inode_broot_debug
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the IO lock is already held, mark that in the inode log item.&n;&t; */
r_if
c_cond
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_EXCL
)paren
(brace
id|iip-&gt;ili_flags
op_or_assign
id|XFS_ILI_IOLOCKED_EXCL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lock_flags
op_amp
id|XFS_IOLOCK_SHARED
)paren
(brace
id|iip-&gt;ili_flags
op_or_assign
id|XFS_ILI_IOLOCKED_SHARED
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize i_transp so we can find it with xfs_inode_incore()&n;&t; * in xfs_trans_iget() above.&n;&t; */
id|ip-&gt;i_transp
op_assign
id|tp
suffix:semicolon
)brace
multiline_comment|/*&n; * Mark the inode as not needing to be unlocked when the inode item&squot;s&n; * IOP_UNLOCK() routine is called.  The inode must already be locked&n; * and associated with the given transaction.&n; */
multiline_comment|/*ARGSUSED*/
r_void
DECL|function|xfs_trans_ihold
id|xfs_trans_ihold
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|ASSERT
c_func
(paren
id|ip-&gt;i_transp
op_eq
id|tp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_itemp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_lock
comma
id|MR_UPDATE
)paren
)paren
suffix:semicolon
id|ip-&gt;i_itemp-&gt;ili_flags
op_or_assign
id|XFS_ILI_HOLD
suffix:semicolon
)brace
multiline_comment|/*&n; * Cancel the previous inode hold request made on this inode&n; * for this transaction.&n; */
multiline_comment|/*ARGSUSED*/
r_void
DECL|function|xfs_trans_ihold_release
id|xfs_trans_ihold_release
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|ASSERT
c_func
(paren
id|ip-&gt;i_transp
op_eq
id|tp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_itemp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_lock
comma
id|MR_UPDATE
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_itemp-&gt;ili_flags
op_amp
id|XFS_ILI_HOLD
)paren
suffix:semicolon
id|ip-&gt;i_itemp-&gt;ili_flags
op_and_assign
op_complement
id|XFS_ILI_HOLD
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to mark the fields indicated in fieldmask as needing&n; * to be logged when the transaction is committed.  The inode must&n; * already be associated with the given transaction.&n; *&n; * The values for fieldmask are defined in xfs_inode_item.h.  We always&n; * log all of the core inode if any of it has changed, and we always log&n; * all of the inline data/extents/b-tree root if any of them has changed.&n; */
r_void
DECL|function|xfs_trans_log_inode
id|xfs_trans_log_inode
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_inode_t
op_star
id|ip
comma
id|uint
id|flags
)paren
(brace
id|xfs_log_item_desc_t
op_star
id|lidp
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_transp
op_eq
id|tp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_itemp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|ismrlocked
c_func
(paren
op_amp
id|ip-&gt;i_lock
comma
id|MR_UPDATE
)paren
)paren
suffix:semicolon
id|lidp
op_assign
id|xfs_trans_find_item
c_func
(paren
id|tp
comma
(paren
id|xfs_log_item_t
op_star
)paren
(paren
id|ip-&gt;i_itemp
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|lidp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|tp-&gt;t_flags
op_or_assign
id|XFS_TRANS_DIRTY
suffix:semicolon
id|lidp-&gt;lid_flags
op_or_assign
id|XFS_LID_DIRTY
suffix:semicolon
multiline_comment|/*&n;&t; * Always OR in the bits from the ili_last_fields field.&n;&t; * This is to coordinate with the xfs_iflush() and xfs_iflush_done()&n;&t; * routines in the eventual clearing of the ilf_fields bits.&n;&t; * See the big comment in xfs_iflush() for an explanation of&n;&t; * this coorination mechanism.&n;&t; */
id|flags
op_or_assign
id|ip-&gt;i_itemp-&gt;ili_last_fields
suffix:semicolon
id|ip-&gt;i_itemp-&gt;ili_format.ilf_fields
op_or_assign
id|flags
suffix:semicolon
)brace
macro_line|#ifdef XFS_TRANS_DEBUG
multiline_comment|/*&n; * Keep track of the state of the inode btree root to make sure we&n; * log it properly.&n; */
id|STATIC
r_void
DECL|function|xfs_trans_inode_broot_debug
id|xfs_trans_inode_broot_debug
c_func
(paren
id|xfs_inode_t
op_star
id|ip
)paren
(brace
id|xfs_inode_log_item_t
op_star
id|iip
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip-&gt;i_itemp
op_ne
l_int|NULL
)paren
suffix:semicolon
id|iip
op_assign
id|ip-&gt;i_itemp
suffix:semicolon
r_if
c_cond
(paren
id|iip-&gt;ili_root_size
op_ne
l_int|0
)paren
(brace
id|ASSERT
c_func
(paren
id|iip-&gt;ili_orig_root
op_ne
l_int|NULL
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|iip-&gt;ili_orig_root
comma
id|iip-&gt;ili_root_size
)paren
suffix:semicolon
id|iip-&gt;ili_root_size
op_assign
l_int|0
suffix:semicolon
id|iip-&gt;ili_orig_root
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ip-&gt;i_d.di_format
op_eq
id|XFS_DINODE_FMT_BTREE
)paren
(brace
id|ASSERT
c_func
(paren
(paren
id|ip-&gt;i_df.if_broot
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|ip-&gt;i_df.if_broot_bytes
OG
l_int|0
)paren
)paren
suffix:semicolon
id|iip-&gt;ili_root_size
op_assign
id|ip-&gt;i_df.if_broot_bytes
suffix:semicolon
id|iip-&gt;ili_orig_root
op_assign
(paren
r_char
op_star
)paren
id|kmem_alloc
c_func
(paren
id|iip-&gt;ili_root_size
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|iip-&gt;ili_orig_root
comma
(paren
r_char
op_star
)paren
(paren
id|ip-&gt;i_df.if_broot
)paren
comma
id|iip-&gt;ili_root_size
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
