multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * This file contains the implementation of the xfs_efi_log_item&n; * and xfs_efd_log_item items.&n; */
macro_line|#include &lt;xfs.h&gt;
DECL|variable|xfs_efi_zone
id|kmem_zone_t
op_star
id|xfs_efi_zone
suffix:semicolon
DECL|variable|xfs_efd_zone
id|kmem_zone_t
op_star
id|xfs_efd_zone
suffix:semicolon
id|STATIC
r_void
id|xfs_efi_item_unlock
c_func
(paren
id|xfs_efi_log_item_t
op_star
)paren
suffix:semicolon
id|STATIC
r_void
id|xfs_efi_item_abort
c_func
(paren
id|xfs_efi_log_item_t
op_star
)paren
suffix:semicolon
id|STATIC
r_void
id|xfs_efd_item_abort
c_func
(paren
id|xfs_efd_log_item_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This returns the number of iovecs needed to log the given efi item.&n; * We only need 1 iovec for an efi item.  It just logs the efi_log_format&n; * structure.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|uint
DECL|function|xfs_efi_item_size
id|xfs_efi_item_size
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to fill in the vector of log iovecs for the&n; * given efi log item. We use only 1 iovec, and we point that&n; * at the efi_log_format structure embedded in the efi item.&n; * It is at this point that we assert that all of the extent&n; * slots in the efi item have been filled.&n; */
id|STATIC
r_void
DECL|function|xfs_efi_item_format
id|xfs_efi_item_format
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
comma
id|xfs_log_iovec_t
op_star
id|log_vector
)paren
(brace
id|uint
id|size
suffix:semicolon
id|ASSERT
c_func
(paren
id|efip-&gt;efi_next_extent
op_eq
id|efip-&gt;efi_format.efi_nextents
)paren
suffix:semicolon
id|efip-&gt;efi_format.efi_type
op_assign
id|XFS_LI_EFI
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|xfs_efi_log_format_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|efip-&gt;efi_format.efi_nextents
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|efip-&gt;efi_format.efi_size
op_assign
l_int|1
suffix:semicolon
id|log_vector-&gt;i_addr
op_assign
(paren
id|xfs_caddr_t
)paren
op_amp
(paren
id|efip-&gt;efi_format
)paren
suffix:semicolon
id|log_vector-&gt;i_len
op_assign
id|size
suffix:semicolon
id|ASSERT
c_func
(paren
id|size
op_ge
r_sizeof
(paren
id|xfs_efi_log_format_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pinning has no meaning for an efi item, so just return.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efi_item_pin
id|xfs_efi_item_pin
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * While EFIs cannot really be pinned, the unpin operation is the&n; * last place at which the EFI is manipulated during a transaction.&n; * Here we coordinate with xfs_efi_cancel() to determine who gets to&n; * free the EFI.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efi_item_unpin
id|xfs_efi_item_unpin
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_int
id|nexts
suffix:semicolon
r_int
id|size
suffix:semicolon
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
id|mp
op_assign
id|efip-&gt;efi_item.li_mountp
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efip-&gt;efi_flags
op_amp
id|XFS_EFI_CANCELED
)paren
(brace
multiline_comment|/*&n;&t;&t; * xfs_trans_delete_ail() drops the AIL lock.&n;&t;&t; */
id|xfs_trans_delete_ail
c_func
(paren
id|mp
comma
(paren
id|xfs_log_item_t
op_star
)paren
id|efip
comma
id|s
)paren
suffix:semicolon
id|nexts
op_assign
id|efip-&gt;efi_format.efi_nextents
suffix:semicolon
r_if
c_cond
(paren
id|nexts
OG
id|XFS_EFI_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
r_sizeof
(paren
id|xfs_efi_log_item_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|nexts
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|efip
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_efi_zone
comma
id|efip
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|efip-&gt;efi_flags
op_or_assign
id|XFS_EFI_COMMITTED
suffix:semicolon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * like unpin only we have to also clear the xaction descriptor&n; * pointing the log item if we free the item.  This routine duplicates&n; * unpin because efi_flags is protected by the AIL lock.  Freeing&n; * the descriptor and then calling unpin would force us to drop the AIL&n; * lock which would open up a race condition.&n; */
id|STATIC
r_void
DECL|function|xfs_efi_item_unpin_remove
id|xfs_efi_item_unpin_remove
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
comma
id|xfs_trans_t
op_star
id|tp
)paren
(brace
r_int
id|nexts
suffix:semicolon
r_int
id|size
suffix:semicolon
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
id|xfs_log_item_desc_t
op_star
id|lidp
suffix:semicolon
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
id|mp
op_assign
id|efip-&gt;efi_item.li_mountp
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efip-&gt;efi_flags
op_amp
id|XFS_EFI_CANCELED
)paren
(brace
multiline_comment|/*&n;&t;&t; * free the xaction descriptor pointing to this item&n;&t;&t; */
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
id|efip
)paren
suffix:semicolon
id|xfs_trans_free_item
c_func
(paren
id|tp
comma
id|lidp
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * pull the item off the AIL.&n;&t;&t; * xfs_trans_delete_ail() drops the AIL lock.&n;&t;&t; */
id|xfs_trans_delete_ail
c_func
(paren
id|mp
comma
(paren
id|xfs_log_item_t
op_star
)paren
id|efip
comma
id|s
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * now free the item itself&n;&t;&t; */
id|nexts
op_assign
id|efip-&gt;efi_format.efi_nextents
suffix:semicolon
r_if
c_cond
(paren
id|nexts
OG
id|XFS_EFI_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
r_sizeof
(paren
id|xfs_efi_log_item_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|nexts
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|efip
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_efi_zone
comma
id|efip
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|efip-&gt;efi_flags
op_or_assign
id|XFS_EFI_COMMITTED
suffix:semicolon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Efi items have no locking or pushing.  However, since EFIs are&n; * pulled from the AIL when their corresponding EFDs are committed&n; * to disk, their situation is very similar to being pinned.  Return&n; * XFS_ITEM_PINNED so that the caller will eventually flush the log.&n; * This should help in getting the EFI out of the AIL.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|uint
DECL|function|xfs_efi_item_trylock
id|xfs_efi_item_trylock
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_return
id|XFS_ITEM_PINNED
suffix:semicolon
)brace
multiline_comment|/*&n; * Efi items have no locking, so just return.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efi_item_unlock
id|xfs_efi_item_unlock
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_if
c_cond
(paren
id|efip-&gt;efi_item.li_flags
op_amp
id|XFS_LI_ABORTED
)paren
id|xfs_efi_item_abort
c_func
(paren
id|efip
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * The EFI is logged only once and cannot be moved in the log, so&n; * simply return the lsn at which it&squot;s been logged.  The canceled&n; * flag is not paid any attention here.&t; Checking for that is delayed&n; * until the EFI is unpinned.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|xfs_lsn_t
DECL|function|xfs_efi_item_committed
id|xfs_efi_item_committed
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
r_return
id|lsn
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called when the transaction logging the EFI is aborted.&n; * Free up the EFI and return.&t;No need to clean up the slot for&n; * the item in the transaction.&t; That was done by the unpin code&n; * which is called prior to this routine in the abort/fs-shutdown path.&n; */
id|STATIC
r_void
DECL|function|xfs_efi_item_abort
id|xfs_efi_item_abort
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_int
id|nexts
suffix:semicolon
r_int
id|size
suffix:semicolon
id|nexts
op_assign
id|efip-&gt;efi_format.efi_nextents
suffix:semicolon
r_if
c_cond
(paren
id|nexts
OG
id|XFS_EFI_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
r_sizeof
(paren
id|xfs_efi_log_item_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|nexts
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|efip
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_efi_zone
comma
id|efip
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * There isn&squot;t much you can do to push on an efi item.&t;It is simply&n; * stuck waiting for all of its corresponding efd items to be&n; * committed to disk.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efi_item_push
id|xfs_efi_item_push
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * The EFI dependency tracking op doesn&squot;t do squat.  It can&squot;t because&n; * it doesn&squot;t know where the free extent is coming from.  The dependency&n; * tracking has to be handled by the &quot;enclosing&quot; metadata object.  For&n; * example, for inodes, the inode is locked throughout the extent freeing&n; * so the dependency should be recorded there.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efi_item_committing
id|xfs_efi_item_committing
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the ops vector shared by all efi log items.&n; */
DECL|variable|xfs_efi_item_ops
r_struct
id|xfs_item_ops
id|xfs_efi_item_ops
op_assign
(brace
dot
id|iop_size
op_assign
(paren
id|uint
c_func
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efi_item_size
comma
dot
id|iop_format
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_log_iovec_t
op_star
)paren
)paren
id|xfs_efi_item_format
comma
dot
id|iop_pin
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efi_item_pin
comma
dot
id|iop_unpin
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efi_item_unpin
comma
dot
id|iop_unpin_remove
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_trans_t
op_star
)paren
)paren
id|xfs_efi_item_unpin_remove
comma
dot
id|iop_trylock
op_assign
(paren
id|uint
c_func
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efi_item_trylock
comma
dot
id|iop_unlock
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efi_item_unlock
comma
dot
id|iop_committed
op_assign
(paren
id|xfs_lsn_t
c_func
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_lsn_t
)paren
)paren
id|xfs_efi_item_committed
comma
dot
id|iop_push
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efi_item_push
comma
dot
id|iop_abort
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efi_item_abort
comma
dot
id|iop_pushbuf
op_assign
l_int|NULL
comma
dot
id|iop_committing
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_lsn_t
)paren
)paren
id|xfs_efi_item_committing
)brace
suffix:semicolon
multiline_comment|/*&n; * Allocate and initialize an efi item with the given number of extents.&n; */
id|xfs_efi_log_item_t
op_star
DECL|function|xfs_efi_init
id|xfs_efi_init
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|uint
id|nextents
)paren
(brace
id|xfs_efi_log_item_t
op_star
id|efip
suffix:semicolon
id|uint
id|size
suffix:semicolon
id|ASSERT
c_func
(paren
id|nextents
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nextents
OG
id|XFS_EFI_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
(paren
id|uint
)paren
(paren
r_sizeof
(paren
id|xfs_efi_log_item_t
)paren
op_plus
(paren
(paren
id|nextents
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
)paren
)paren
suffix:semicolon
id|efip
op_assign
(paren
id|xfs_efi_log_item_t
op_star
)paren
id|kmem_zalloc
c_func
(paren
id|size
comma
id|KM_SLEEP
)paren
suffix:semicolon
)brace
r_else
(brace
id|efip
op_assign
(paren
id|xfs_efi_log_item_t
op_star
)paren
id|kmem_zone_zalloc
c_func
(paren
id|xfs_efi_zone
comma
id|KM_SLEEP
)paren
suffix:semicolon
)brace
id|efip-&gt;efi_item.li_type
op_assign
id|XFS_LI_EFI
suffix:semicolon
id|efip-&gt;efi_item.li_ops
op_assign
op_amp
id|xfs_efi_item_ops
suffix:semicolon
id|efip-&gt;efi_item.li_mountp
op_assign
id|mp
suffix:semicolon
id|efip-&gt;efi_format.efi_nextents
op_assign
id|nextents
suffix:semicolon
id|efip-&gt;efi_format.efi_id
op_assign
(paren
id|__psint_t
)paren
(paren
r_void
op_star
)paren
id|efip
suffix:semicolon
r_return
(paren
id|efip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called by the efd item code below to release references to&n; * the given efi item.&t;Each efd calls this with the number of&n; * extents that it has logged, and when the sum of these reaches&n; * the total number of extents logged by this efi item we can free&n; * the efi item.&n; *&n; * Freeing the efi item requires that we remove it from the AIL.&n; * We&squot;ll use the AIL lock to protect our counters as well as&n; * the removal from the AIL.&n; */
r_void
DECL|function|xfs_efi_release
id|xfs_efi_release
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
comma
id|uint
id|nextents
)paren
(brace
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
r_int
id|extents_left
suffix:semicolon
id|uint
id|size
suffix:semicolon
r_int
id|nexts
suffix:semicolon
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
id|mp
op_assign
id|efip-&gt;efi_item.li_mountp
suffix:semicolon
id|ASSERT
c_func
(paren
id|efip-&gt;efi_next_extent
OG
l_int|0
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|efip-&gt;efi_flags
op_amp
id|XFS_EFI_COMMITTED
)paren
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|efip-&gt;efi_next_extent
op_ge
id|nextents
)paren
suffix:semicolon
id|efip-&gt;efi_next_extent
op_sub_assign
id|nextents
suffix:semicolon
id|extents_left
op_assign
id|efip-&gt;efi_next_extent
suffix:semicolon
r_if
c_cond
(paren
id|extents_left
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * xfs_trans_delete_ail() drops the AIL lock.&n;&t;&t; */
id|xfs_trans_delete_ail
c_func
(paren
id|mp
comma
(paren
id|xfs_log_item_t
op_star
)paren
id|efip
comma
id|s
)paren
suffix:semicolon
)brace
r_else
(brace
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|extents_left
op_eq
l_int|0
)paren
(brace
id|nexts
op_assign
id|efip-&gt;efi_format.efi_nextents
suffix:semicolon
r_if
c_cond
(paren
id|nexts
OG
id|XFS_EFI_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
r_sizeof
(paren
id|xfs_efi_log_item_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|nexts
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|efip
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_efi_zone
comma
id|efip
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * This is called when the transaction that should be committing the&n; * EFD corresponding to the given EFI is aborted.  The committed and&n; * canceled flags are used to coordinate the freeing of the EFI and&n; * the references by the transaction that committed it.&n; */
id|STATIC
r_void
DECL|function|xfs_efi_cancel
id|xfs_efi_cancel
c_func
(paren
id|xfs_efi_log_item_t
op_star
id|efip
)paren
(brace
r_int
id|nexts
suffix:semicolon
r_int
id|size
suffix:semicolon
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
id|mp
op_assign
id|efip-&gt;efi_item.li_mountp
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efip-&gt;efi_flags
op_amp
id|XFS_EFI_COMMITTED
)paren
(brace
multiline_comment|/*&n;&t;&t; * xfs_trans_delete_ail() drops the AIL lock.&n;&t;&t; */
id|xfs_trans_delete_ail
c_func
(paren
id|mp
comma
(paren
id|xfs_log_item_t
op_star
)paren
id|efip
comma
id|s
)paren
suffix:semicolon
id|nexts
op_assign
id|efip-&gt;efi_format.efi_nextents
suffix:semicolon
r_if
c_cond
(paren
id|nexts
OG
id|XFS_EFI_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
r_sizeof
(paren
id|xfs_efi_log_item_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|nexts
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|efip
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_efi_zone
comma
id|efip
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|efip-&gt;efi_flags
op_or_assign
id|XFS_EFI_CANCELED
suffix:semicolon
id|AIL_UNLOCK
c_func
(paren
id|mp
comma
id|s
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This returns the number of iovecs needed to log the given efd item.&n; * We only need 1 iovec for an efd item.  It just logs the efd_log_format&n; * structure.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|uint
DECL|function|xfs_efd_item_size
id|xfs_efd_item_size
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to fill in the vector of log iovecs for the&n; * given efd log item. We use only 1 iovec, and we point that&n; * at the efd_log_format structure embedded in the efd item.&n; * It is at this point that we assert that all of the extent&n; * slots in the efd item have been filled.&n; */
id|STATIC
r_void
DECL|function|xfs_efd_item_format
id|xfs_efd_item_format
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
comma
id|xfs_log_iovec_t
op_star
id|log_vector
)paren
(brace
id|uint
id|size
suffix:semicolon
id|ASSERT
c_func
(paren
id|efdp-&gt;efd_next_extent
op_eq
id|efdp-&gt;efd_format.efd_nextents
)paren
suffix:semicolon
id|efdp-&gt;efd_format.efd_type
op_assign
id|XFS_LI_EFD
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|xfs_efd_log_format_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|efdp-&gt;efd_format.efd_nextents
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|efdp-&gt;efd_format.efd_size
op_assign
l_int|1
suffix:semicolon
id|log_vector-&gt;i_addr
op_assign
(paren
id|xfs_caddr_t
)paren
op_amp
(paren
id|efdp-&gt;efd_format
)paren
suffix:semicolon
id|log_vector-&gt;i_len
op_assign
id|size
suffix:semicolon
id|ASSERT
c_func
(paren
id|size
op_ge
r_sizeof
(paren
id|xfs_efd_log_format_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pinning has no meaning for an efd item, so just return.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efd_item_pin
id|xfs_efd_item_pin
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Since pinning has no meaning for an efd item, unpinning does&n; * not either.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efd_item_unpin
id|xfs_efd_item_unpin
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efd_item_unpin_remove
id|xfs_efd_item_unpin_remove
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
comma
id|xfs_trans_t
op_star
id|tp
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Efd items have no locking, so just return success.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|uint
DECL|function|xfs_efd_item_trylock
id|xfs_efd_item_trylock
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
)paren
(brace
r_return
id|XFS_ITEM_LOCKED
suffix:semicolon
)brace
multiline_comment|/*&n; * Efd items have no locking or pushing, so return failure&n; * so that the caller doesn&squot;t bother with us.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efd_item_unlock
id|xfs_efd_item_unlock
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
)paren
(brace
r_if
c_cond
(paren
id|efdp-&gt;efd_item.li_flags
op_amp
id|XFS_LI_ABORTED
)paren
id|xfs_efd_item_abort
c_func
(paren
id|efdp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * When the efd item is committed to disk, all we need to do&n; * is delete our reference to our partner efi item and then&n; * free ourselves.  Since we&squot;re freeing ourselves we must&n; * return -1 to keep the transaction code from further referencing&n; * this item.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|xfs_lsn_t
DECL|function|xfs_efd_item_committed
id|xfs_efd_item_committed
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
id|uint
id|size
suffix:semicolon
r_int
id|nexts
suffix:semicolon
multiline_comment|/*&n;&t; * If we got a log I/O error, it&squot;s always the case that the LR with the&n;&t; * EFI got unpinned and freed before the EFD got aborted.&n;&t; */
r_if
c_cond
(paren
(paren
id|efdp-&gt;efd_item.li_flags
op_amp
id|XFS_LI_ABORTED
)paren
op_eq
l_int|0
)paren
id|xfs_efi_release
c_func
(paren
id|efdp-&gt;efd_efip
comma
id|efdp-&gt;efd_format.efd_nextents
)paren
suffix:semicolon
id|nexts
op_assign
id|efdp-&gt;efd_format.efd_nextents
suffix:semicolon
r_if
c_cond
(paren
id|nexts
OG
id|XFS_EFD_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
r_sizeof
(paren
id|xfs_efd_log_item_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|nexts
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|efdp
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_efd_zone
comma
id|efdp
)paren
suffix:semicolon
)brace
r_return
(paren
id|xfs_lsn_t
)paren
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The transaction of which this EFD is a part has been aborted.&n; * Inform its companion EFI of this fact and then clean up after&n; * ourselves.  No need to clean up the slot for the item in the&n; * transaction.&t; That was done by the unpin code which is called&n; * prior to this routine in the abort/fs-shutdown path.&n; */
id|STATIC
r_void
DECL|function|xfs_efd_item_abort
id|xfs_efd_item_abort
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
)paren
(brace
r_int
id|nexts
suffix:semicolon
r_int
id|size
suffix:semicolon
multiline_comment|/*&n;&t; * If we got a log I/O error, it&squot;s always the case that the LR with the&n;&t; * EFI got unpinned and freed before the EFD got aborted. So don&squot;t&n;&t; * reference the EFI at all in that case.&n;&t; */
r_if
c_cond
(paren
(paren
id|efdp-&gt;efd_item.li_flags
op_amp
id|XFS_LI_ABORTED
)paren
op_eq
l_int|0
)paren
id|xfs_efi_cancel
c_func
(paren
id|efdp-&gt;efd_efip
)paren
suffix:semicolon
id|nexts
op_assign
id|efdp-&gt;efd_format.efd_nextents
suffix:semicolon
r_if
c_cond
(paren
id|nexts
OG
id|XFS_EFD_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
r_sizeof
(paren
id|xfs_efd_log_item_t
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|nexts
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|efdp
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|kmem_zone_free
c_func
(paren
id|xfs_efd_zone
comma
id|efdp
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * There isn&squot;t much you can do to push on an efd item.&t;It is simply&n; * stuck waiting for the log to be flushed to disk.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efd_item_push
id|xfs_efd_item_push
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efdp
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * The EFD dependency tracking op doesn&squot;t do squat.  It can&squot;t because&n; * it doesn&squot;t know where the free extent is coming from.  The dependency&n; * tracking has to be handled by the &quot;enclosing&quot; metadata object.  For&n; * example, for inodes, the inode is locked throughout the extent freeing&n; * so the dependency should be recorded there.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_efd_item_committing
id|xfs_efd_item_committing
c_func
(paren
id|xfs_efd_log_item_t
op_star
id|efip
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the ops vector shared by all efd log items.&n; */
DECL|variable|xfs_efd_item_ops
r_struct
id|xfs_item_ops
id|xfs_efd_item_ops
op_assign
(brace
dot
id|iop_size
op_assign
(paren
id|uint
c_func
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efd_item_size
comma
dot
id|iop_format
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_log_iovec_t
op_star
)paren
)paren
id|xfs_efd_item_format
comma
dot
id|iop_pin
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efd_item_pin
comma
dot
id|iop_unpin
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efd_item_unpin
comma
dot
id|iop_unpin_remove
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_trans_t
op_star
)paren
)paren
id|xfs_efd_item_unpin_remove
comma
dot
id|iop_trylock
op_assign
(paren
id|uint
c_func
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efd_item_trylock
comma
dot
id|iop_unlock
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efd_item_unlock
comma
dot
id|iop_committed
op_assign
(paren
id|xfs_lsn_t
c_func
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_lsn_t
)paren
)paren
id|xfs_efd_item_committed
comma
dot
id|iop_push
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efd_item_push
comma
dot
id|iop_abort
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
)paren
)paren
id|xfs_efd_item_abort
comma
dot
id|iop_pushbuf
op_assign
l_int|NULL
comma
dot
id|iop_committing
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
id|xfs_log_item_t
op_star
comma
id|xfs_lsn_t
)paren
)paren
id|xfs_efd_item_committing
)brace
suffix:semicolon
multiline_comment|/*&n; * Allocate and initialize an efd item with the given number of extents.&n; */
id|xfs_efd_log_item_t
op_star
DECL|function|xfs_efd_init
id|xfs_efd_init
c_func
(paren
id|xfs_mount_t
op_star
id|mp
comma
id|xfs_efi_log_item_t
op_star
id|efip
comma
id|uint
id|nextents
)paren
(brace
id|xfs_efd_log_item_t
op_star
id|efdp
suffix:semicolon
id|uint
id|size
suffix:semicolon
id|ASSERT
c_func
(paren
id|nextents
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nextents
OG
id|XFS_EFD_MAX_FAST_EXTENTS
)paren
(brace
id|size
op_assign
(paren
id|uint
)paren
(paren
r_sizeof
(paren
id|xfs_efd_log_item_t
)paren
op_plus
(paren
(paren
id|nextents
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|xfs_extent_t
)paren
)paren
)paren
suffix:semicolon
id|efdp
op_assign
(paren
id|xfs_efd_log_item_t
op_star
)paren
id|kmem_zalloc
c_func
(paren
id|size
comma
id|KM_SLEEP
)paren
suffix:semicolon
)brace
r_else
(brace
id|efdp
op_assign
(paren
id|xfs_efd_log_item_t
op_star
)paren
id|kmem_zone_zalloc
c_func
(paren
id|xfs_efd_zone
comma
id|KM_SLEEP
)paren
suffix:semicolon
)brace
id|efdp-&gt;efd_item.li_type
op_assign
id|XFS_LI_EFD
suffix:semicolon
id|efdp-&gt;efd_item.li_ops
op_assign
op_amp
id|xfs_efd_item_ops
suffix:semicolon
id|efdp-&gt;efd_item.li_mountp
op_assign
id|mp
suffix:semicolon
id|efdp-&gt;efd_efip
op_assign
id|efip
suffix:semicolon
id|efdp-&gt;efd_format.efd_nextents
op_assign
id|nextents
suffix:semicolon
id|efdp-&gt;efd_format.efd_efi_id
op_assign
id|efip-&gt;efi_format.efi_id
suffix:semicolon
r_return
(paren
id|efdp
)paren
suffix:semicolon
)brace
eof
