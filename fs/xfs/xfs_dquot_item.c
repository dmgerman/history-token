multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;xfs.h&gt;
macro_line|#include &lt;xfs_quota_priv.h&gt;
multiline_comment|/*&n; * returns the number of iovecs needed to log the given dquot item.&n; */
multiline_comment|/* ARGSUSED */
id|STATIC
id|uint
DECL|function|xfs_qm_dquot_logitem_size
id|xfs_qm_dquot_logitem_size
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|logitem
)paren
(brace
multiline_comment|/*&n;&t; * we need only two iovecs, one for the format, one for the real thing&n;&t; */
r_return
(paren
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fills in the vector of log iovecs for the given dquot log item.&n; */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_format
id|xfs_qm_dquot_logitem_format
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|logitem
comma
id|xfs_log_iovec_t
op_star
id|logvec
)paren
(brace
id|ASSERT
c_func
(paren
id|logitem
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|logitem-&gt;qli_dquot
)paren
suffix:semicolon
id|logvec-&gt;i_addr
op_assign
(paren
id|xfs_caddr_t
)paren
op_amp
id|logitem-&gt;qli_format
suffix:semicolon
id|logvec-&gt;i_len
op_assign
r_sizeof
(paren
id|xfs_dq_logformat_t
)paren
suffix:semicolon
id|logvec
op_increment
suffix:semicolon
id|logvec-&gt;i_addr
op_assign
(paren
id|xfs_caddr_t
)paren
op_amp
id|logitem-&gt;qli_dquot-&gt;q_core
suffix:semicolon
id|logvec-&gt;i_len
op_assign
r_sizeof
(paren
id|xfs_disk_dquot_t
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
l_int|2
op_eq
id|logitem-&gt;qli_item.li_desc-&gt;lid_size
)paren
suffix:semicolon
id|logitem-&gt;qli_format.qlf_size
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n; * Increment the pin count of the given dquot.&n; * This value is protected by pinlock spinlock in the xQM structure.&n; */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_pin
id|xfs_qm_dquot_logitem_pin
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|logitem
)paren
(brace
r_int
r_int
id|s
suffix:semicolon
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|dqp
op_assign
id|logitem-&gt;qli_dquot
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
id|s
op_assign
id|XFS_DQ_PINLOCK
c_func
(paren
id|dqp
)paren
suffix:semicolon
id|dqp-&gt;q_pincount
op_increment
suffix:semicolon
id|XFS_DQ_PINUNLOCK
c_func
(paren
id|dqp
comma
id|s
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Decrement the pin count of the given dquot, and wake up&n; * anyone in xfs_dqwait_unpin() if the count goes to 0.&t; The&n; * dquot must have been previously pinned with a call to xfs_dqpin().&n; */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_unpin
id|xfs_qm_dquot_logitem_unpin
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|logitem
)paren
(brace
r_int
r_int
id|s
suffix:semicolon
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|dqp
op_assign
id|logitem-&gt;qli_dquot
suffix:semicolon
id|ASSERT
c_func
(paren
id|dqp-&gt;q_pincount
OG
l_int|0
)paren
suffix:semicolon
id|s
op_assign
id|XFS_DQ_PINLOCK
c_func
(paren
id|dqp
)paren
suffix:semicolon
id|dqp-&gt;q_pincount
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|dqp-&gt;q_pincount
op_eq
l_int|0
)paren
(brace
id|sv_broadcast
c_func
(paren
op_amp
id|dqp-&gt;q_pinwait
)paren
suffix:semicolon
)brace
id|XFS_DQ_PINUNLOCK
c_func
(paren
id|dqp
comma
id|s
)paren
suffix:semicolon
)brace
multiline_comment|/* ARGSUSED */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_unpin_remove
id|xfs_qm_dquot_logitem_unpin_remove
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|logitem
comma
id|xfs_trans_t
op_star
id|tp
)paren
(brace
id|xfs_qm_dquot_logitem_unpin
c_func
(paren
id|logitem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given the logitem, this writes the corresponding dquot entry to disk&n; * asynchronously. This is called with the dquot entry securely locked;&n; * we simply get xfs_qm_dqflush() to do the work, and unlock the dquot&n; * at the end.&n; */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_push
id|xfs_qm_dquot_logitem_push
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|logitem
)paren
(brace
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|dqp
op_assign
id|logitem-&gt;qli_dquot
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_FLUSH_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Since we were able to lock the dquot&squot;s flush lock and&n;&t; * we found it on the AIL, the dquot must be dirty.  This&n;&t; * is because the dquot is removed from the AIL while still&n;&t; * holding the flush lock in xfs_dqflush_done().  Thus, if&n;&t; * we found it in the AIL and were able to obtain the flush&n;&t; * lock without sleeping, then there must not have been&n;&t; * anyone in the process of flushing the dquot.&n;&t; */
id|xfs_qm_dqflush
c_func
(paren
id|dqp
comma
id|XFS_B_DELWRI
)paren
suffix:semicolon
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
id|STATIC
id|xfs_lsn_t
DECL|function|xfs_qm_dquot_logitem_committed
id|xfs_qm_dquot_logitem_committed
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|l
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
multiline_comment|/*&n;&t; * We always re-log the entire dquot when it becomes dirty,&n;&t; * so, the latest copy _is_ the only one that matters.&n;&t; */
r_return
(paren
id|lsn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to wait for the given dquot to be unpinned.&n; * Most of these pin/unpin routines are plagiarized from inode code.&n; */
r_void
DECL|function|xfs_qm_dqunpin_wait
id|xfs_qm_dqunpin_wait
c_func
(paren
id|xfs_dquot_t
op_star
id|dqp
)paren
(brace
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dqp-&gt;q_pincount
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Give the log a push so we don&squot;t wait here too long.&n;&t; */
id|xfs_log_force
c_func
(paren
id|dqp-&gt;q_mount
comma
(paren
id|xfs_lsn_t
)paren
l_int|0
comma
id|XFS_LOG_FORCE
)paren
suffix:semicolon
id|s
op_assign
id|XFS_DQ_PINLOCK
c_func
(paren
id|dqp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dqp-&gt;q_pincount
op_eq
l_int|0
)paren
(brace
id|XFS_DQ_PINUNLOCK
c_func
(paren
id|dqp
comma
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sv_wait
c_func
(paren
op_amp
(paren
id|dqp-&gt;q_pinwait
)paren
comma
id|PINOD
comma
op_amp
(paren
id|XFS_DQ_TO_QINF
c_func
(paren
id|dqp
)paren
op_member_access_from_pointer
id|qi_pinlock
)paren
comma
id|s
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called when IOP_TRYLOCK returns XFS_ITEM_PUSHBUF to indicate that&n; * the dquot is locked by us, but the flush lock isn&squot;t. So, here we are&n; * going to see if the relevant dquot buffer is incore, waiting on DELWRI.&n; * If so, we want to push it out to help us take this item off the AIL as soon&n; * as possible.&n; *&n; * We must not be holding the AIL_LOCK at this point. Calling incore() to&n; * search the buffercache can be a time consuming thing, and AIL_LOCK is a&n; * spinlock.&n; */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_pushbuf
id|xfs_qm_dquot_logitem_pushbuf
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|qip
)paren
(brace
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
id|xfs_buf_t
op_star
id|bp
suffix:semicolon
id|uint
id|dopush
suffix:semicolon
id|dqp
op_assign
id|qip-&gt;qli_dquot
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The qli_pushbuf_flag keeps others from&n;&t; * trying to duplicate our effort.&n;&t; */
id|ASSERT
c_func
(paren
id|qip-&gt;qli_pushbuf_flag
op_ne
l_int|0
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|qip-&gt;qli_push_owner
op_eq
id|get_thread_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If flushlock isn&squot;t locked anymore, chances are that the&n;&t; * inode flush completed and the inode was taken off the AIL.&n;&t; * So, just get out.&n;&t; */
r_if
c_cond
(paren
(paren
id|valusema
c_func
(paren
op_amp
(paren
id|dqp-&gt;q_flock
)paren
)paren
OG
l_int|0
)paren
op_logical_or
(paren
(paren
id|qip-&gt;qli_item.li_flags
op_amp
id|XFS_LI_IN_AIL
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|qip-&gt;qli_pushbuf_flag
op_assign
l_int|0
suffix:semicolon
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mp
op_assign
id|dqp-&gt;q_mount
suffix:semicolon
id|bp
op_assign
id|xfs_incore
c_func
(paren
id|mp-&gt;m_ddev_targp
comma
id|qip-&gt;qli_format.qlf_blkno
comma
id|XFS_QI_DQCHUNKLEN
c_func
(paren
id|mp
)paren
comma
id|XFS_INCORE_TRYLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|XFS_BUF_ISDELAYWRITE
c_func
(paren
id|bp
)paren
)paren
(brace
id|dopush
op_assign
(paren
(paren
id|qip-&gt;qli_item.li_flags
op_amp
id|XFS_LI_IN_AIL
)paren
op_logical_and
(paren
id|valusema
c_func
(paren
op_amp
(paren
id|dqp-&gt;q_flock
)paren
)paren
op_le
l_int|0
)paren
)paren
suffix:semicolon
id|qip-&gt;qli_pushbuf_flag
op_assign
l_int|0
suffix:semicolon
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|XFS_BUF_ISPINNED
c_func
(paren
id|bp
)paren
)paren
(brace
id|xfs_log_force
c_func
(paren
id|mp
comma
(paren
id|xfs_lsn_t
)paren
l_int|0
comma
id|XFS_LOG_FORCE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dopush
)paren
(brace
macro_line|#ifdef XFSRACEDEBUG
id|delay_for_intr
c_func
(paren
)paren
suffix:semicolon
id|delay
c_func
(paren
l_int|300
)paren
suffix:semicolon
macro_line|#endif
id|xfs_bawrite
c_func
(paren
id|mp
comma
id|bp
)paren
suffix:semicolon
)brace
r_else
(brace
id|xfs_buf_relse
c_func
(paren
id|bp
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|qip-&gt;qli_pushbuf_flag
op_assign
l_int|0
suffix:semicolon
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
id|xfs_buf_relse
c_func
(paren
id|bp
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|qip-&gt;qli_pushbuf_flag
op_assign
l_int|0
suffix:semicolon
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to attempt to lock the dquot associated with this&n; * dquot log item.  Don&squot;t sleep on the dquot lock or the flush lock.&n; * If the flush lock is already held, indicating that the dquot has&n; * been or is in the process of being flushed, then see if we can&n; * find the dquot&squot;s buffer in the buffer cache without sleeping.  If&n; * we can and it is marked delayed write, then we want to send it out.&n; * We delay doing so until the push routine, though, to avoid sleeping&n; * in any device strategy routines.&n; */
id|STATIC
id|uint
DECL|function|xfs_qm_dquot_logitem_trylock
id|xfs_qm_dquot_logitem_trylock
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|qip
)paren
(brace
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|uint
id|retval
suffix:semicolon
id|dqp
op_assign
id|qip-&gt;qli_dquot
suffix:semicolon
r_if
c_cond
(paren
id|dqp-&gt;q_pincount
OG
l_int|0
)paren
r_return
(paren
id|XFS_ITEM_PINNED
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xfs_qm_dqlock_nowait
c_func
(paren
id|dqp
)paren
)paren
r_return
(paren
id|XFS_ITEM_LOCKED
)paren
suffix:semicolon
id|retval
op_assign
id|XFS_ITEM_SUCCESS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xfs_qm_dqflock_nowait
c_func
(paren
id|dqp
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * The dquot is already being flushed.&t;It may have been&n;&t;&t; * flushed delayed write, however, and we don&squot;t want to&n;&t;&t; * get stuck waiting for that to complete.  So, we want to check&n;&t;&t; * to see if we can lock the dquot&squot;s buffer without sleeping.&n;&t;&t; * If we can and it is marked for delayed write, then we&n;&t;&t; * hold it and send it out from the push routine.  We don&squot;t&n;&t;&t; * want to do that now since we might sleep in the device&n;&t;&t; * strategy routine.  We also don&squot;t want to grab the buffer lock&n;&t;&t; * here because we&squot;d like not to call into the buffer cache&n;&t;&t; * while holding the AIL_LOCK.&n;&t;&t; * Make sure to only return PUSHBUF if we set pushbuf_flag&n;&t;&t; * ourselves.  If someone else is doing it then we don&squot;t&n;&t;&t; * want to go to the push routine and duplicate their efforts.&n;&t;&t; */
r_if
c_cond
(paren
id|qip-&gt;qli_pushbuf_flag
op_eq
l_int|0
)paren
(brace
id|qip-&gt;qli_pushbuf_flag
op_assign
l_int|1
suffix:semicolon
id|ASSERT
c_func
(paren
id|qip-&gt;qli_format.qlf_blkno
op_eq
id|dqp-&gt;q_blkno
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|qip-&gt;qli_push_owner
op_assign
id|get_thread_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t; * The dquot is left locked.&n;&t;&t;&t; */
id|retval
op_assign
id|XFS_ITEM_PUSHBUF
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
id|XFS_ITEM_FLUSHING
suffix:semicolon
id|xfs_dqunlock_nonotify
c_func
(paren
id|dqp
)paren
suffix:semicolon
)brace
)brace
id|ASSERT
c_func
(paren
id|qip-&gt;qli_item.li_flags
op_amp
id|XFS_LI_IN_AIL
)paren
suffix:semicolon
r_return
(paren
id|retval
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unlock the dquot associated with the log item.&n; * Clear the fields of the dquot and dquot log item that&n; * are specific to the current transaction.  If the&n; * hold flags is set, do not unlock the dquot.&n; */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_unlock
id|xfs_qm_dquot_logitem_unlock
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|ql
)paren
(brace
id|xfs_dquot_t
op_star
id|dqp
suffix:semicolon
id|ASSERT
c_func
(paren
id|ql
op_ne
l_int|NULL
)paren
suffix:semicolon
id|dqp
op_assign
id|ql-&gt;qli_dquot
suffix:semicolon
id|ASSERT
c_func
(paren
id|XFS_DQ_IS_LOCKED
c_func
(paren
id|dqp
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear the transaction pointer in the dquot&n;&t; */
id|dqp-&gt;q_transp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * dquots are never &squot;held&squot; from getting unlocked at the end of&n;&t; * a transaction.  Their locking and unlocking is hidden inside the&n;&t; * transaction layer, within trans_commit. Hence, no LI_HOLD flag&n;&t; * for the logitem.&n;&t; */
id|xfs_dqunlock
c_func
(paren
id|dqp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The transaction with the dquot locked has aborted.  The dquot&n; * must not be dirty within the transaction.  We simply unlock just&n; * as if the transaction had been cancelled.&n; */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_abort
id|xfs_qm_dquot_logitem_abort
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|ql
)paren
(brace
id|xfs_qm_dquot_logitem_unlock
c_func
(paren
id|ql
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this needs to stamp an lsn into the dquot, I think.&n; * rpc&squot;s that look at user dquot&squot;s would then have to&n; * push on the dependency recorded in the dquot&n; */
multiline_comment|/* ARGSUSED */
id|STATIC
r_void
DECL|function|xfs_qm_dquot_logitem_committing
id|xfs_qm_dquot_logitem_committing
c_func
(paren
id|xfs_dq_logitem_t
op_star
id|l
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the ops vector for dquots&n; */
DECL|variable|xfs_dquot_item_ops
r_struct
id|xfs_item_ops
id|xfs_dquot_item_ops
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
id|xfs_qm_dquot_logitem_size
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
id|xfs_qm_dquot_logitem_format
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
id|xfs_qm_dquot_logitem_pin
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
id|xfs_qm_dquot_logitem_unpin
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
id|xfs_qm_dquot_logitem_unpin_remove
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
id|xfs_qm_dquot_logitem_trylock
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
id|xfs_qm_dquot_logitem_unlock
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
id|xfs_qm_dquot_logitem_committed
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
id|xfs_qm_dquot_logitem_push
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
id|xfs_qm_dquot_logitem_abort
comma
dot
id|iop_pushbuf
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
id|xfs_qm_dquot_logitem_pushbuf
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
id|xfs_qm_dquot_logitem_committing
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize the dquot log item for a newly allocated dquot.&n; * The dquot isn&squot;t locked at this point, but it isn&squot;t on any of the lists&n; * either, so we don&squot;t care.&n; */
r_void
DECL|function|xfs_qm_dquot_logitem_init
id|xfs_qm_dquot_logitem_init
c_func
(paren
r_struct
id|xfs_dquot
op_star
id|dqp
)paren
(brace
id|xfs_dq_logitem_t
op_star
id|lp
suffix:semicolon
id|lp
op_assign
op_amp
id|dqp-&gt;q_logitem
suffix:semicolon
id|lp-&gt;qli_item.li_type
op_assign
id|XFS_LI_DQUOT
suffix:semicolon
id|lp-&gt;qli_item.li_ops
op_assign
op_amp
id|xfs_dquot_item_ops
suffix:semicolon
id|lp-&gt;qli_item.li_mountp
op_assign
id|dqp-&gt;q_mount
suffix:semicolon
id|lp-&gt;qli_dquot
op_assign
id|dqp
suffix:semicolon
id|lp-&gt;qli_format.qlf_type
op_assign
id|XFS_LI_DQUOT
suffix:semicolon
id|lp-&gt;qli_format.qlf_id
op_assign
id|INT_GET
c_func
(paren
id|dqp-&gt;q_core.d_id
comma
id|ARCH_CONVERT
)paren
suffix:semicolon
id|lp-&gt;qli_format.qlf_blkno
op_assign
id|dqp-&gt;q_blkno
suffix:semicolon
id|lp-&gt;qli_format.qlf_len
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * This is just the offset of this dquot within its buffer&n;&t; * (which is currently 1 FSB and probably won&squot;t change).&n;&t; * Hence 32 bits for this offset should be just fine.&n;&t; * Alternatively, we can store (bufoffset / sizeof(xfs_dqblk_t))&n;&t; * here, and recompute it at recovery time.&n;&t; */
id|lp-&gt;qli_format.qlf_boffset
op_assign
(paren
id|__uint32_t
)paren
id|dqp-&gt;q_bufoffset
suffix:semicolon
)brace
multiline_comment|/*------------------  QUOTAOFF LOG ITEMS  -------------------*/
multiline_comment|/*&n; * This returns the number of iovecs needed to log the given quotaoff item.&n; * We only need 1 iovec for an quotaoff item.  It just logs the&n; * quotaoff_log_format structure.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|uint
DECL|function|xfs_qm_qoff_logitem_size
id|xfs_qm_qoff_logitem_size
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
)paren
(brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called to fill in the vector of log iovecs for the&n; * given quotaoff log item. We use only 1 iovec, and we point that&n; * at the quotaoff_log_format structure embedded in the quotaoff item.&n; * It is at this point that we assert that all of the extent&n; * slots in the quotaoff item have been filled.&n; */
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_format
id|xfs_qm_qoff_logitem_format
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
comma
id|xfs_log_iovec_t
op_star
id|log_vector
)paren
(brace
id|ASSERT
c_func
(paren
id|qf-&gt;qql_format.qf_type
op_eq
id|XFS_LI_QUOTAOFF
)paren
suffix:semicolon
id|log_vector-&gt;i_addr
op_assign
(paren
id|xfs_caddr_t
)paren
op_amp
(paren
id|qf-&gt;qql_format
)paren
suffix:semicolon
id|log_vector-&gt;i_len
op_assign
r_sizeof
(paren
id|xfs_qoff_logitem_t
)paren
suffix:semicolon
id|qf-&gt;qql_format.qf_size
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Pinning has no meaning for an quotaoff item, so just return.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_pin
id|xfs_qm_qoff_logitem_pin
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Since pinning has no meaning for an quotaoff item, unpinning does&n; * not either.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_unpin
id|xfs_qm_qoff_logitem_unpin
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_unpin_remove
id|xfs_qm_qoff_logitem_unpin_remove
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
comma
id|xfs_trans_t
op_star
id|tp
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Quotaoff items have no locking, so just return success.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|uint
DECL|function|xfs_qm_qoff_logitem_trylock
id|xfs_qm_qoff_logitem_trylock
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
)paren
(brace
r_return
id|XFS_ITEM_LOCKED
suffix:semicolon
)brace
multiline_comment|/*&n; * Quotaoff items have no locking or pushing, so return failure&n; * so that the caller doesn&squot;t bother with us.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_unlock
id|xfs_qm_qoff_logitem_unlock
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * The quotaoff-start-item is logged only once and cannot be moved in the log,&n; * so simply return the lsn at which it&squot;s been logged.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
id|xfs_lsn_t
DECL|function|xfs_qm_qoff_logitem_committed
id|xfs_qm_qoff_logitem_committed
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
r_return
(paren
id|lsn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The transaction of which this QUOTAOFF is a part has been aborted.&n; * Just clean up after ourselves.&n; * Shouldn&squot;t this never happen in the case of qoffend logitems? XXX&n; */
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_abort
id|xfs_qm_qoff_logitem_abort
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
)paren
(brace
id|kmem_free
c_func
(paren
id|qf
comma
r_sizeof
(paren
id|xfs_qoff_logitem_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * There isn&squot;t much you can do to push on an quotaoff item.  It is simply&n; * stuck waiting for the log to be flushed to disk.&n; */
multiline_comment|/*ARGSUSED*/
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_push
id|xfs_qm_qoff_logitem_push
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qf
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
id|STATIC
id|xfs_lsn_t
DECL|function|xfs_qm_qoffend_logitem_committed
id|xfs_qm_qoffend_logitem_committed
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qfe
comma
id|xfs_lsn_t
id|lsn
)paren
(brace
id|xfs_qoff_logitem_t
op_star
id|qfs
suffix:semicolon
id|SPLDECL
c_func
(paren
id|s
)paren
suffix:semicolon
id|qfs
op_assign
id|qfe-&gt;qql_start_lip
suffix:semicolon
id|AIL_LOCK
c_func
(paren
id|qfs-&gt;qql_item.li_mountp
comma
id|s
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Delete the qoff-start logitem from the AIL.&n;&t; * xfs_trans_delete_ail() drops the AIL lock.&n;&t; */
id|xfs_trans_delete_ail
c_func
(paren
id|qfs-&gt;qql_item.li_mountp
comma
(paren
id|xfs_log_item_t
op_star
)paren
id|qfs
comma
id|s
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|qfs
comma
r_sizeof
(paren
id|xfs_qoff_logitem_t
)paren
)paren
suffix:semicolon
id|kmem_free
c_func
(paren
id|qfe
comma
r_sizeof
(paren
id|xfs_qoff_logitem_t
)paren
)paren
suffix:semicolon
r_return
(paren
id|xfs_lsn_t
)paren
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX rcc - don&squot;t know quite what to do with this.  I think we can&n; * just ignore it.  The only time that isn&squot;t the case is if we allow&n; * the client to somehow see that quotas have been turned off in which&n; * we can&squot;t allow that to get back until the quotaoff hits the disk.&n; * So how would that happen?  Also, do we need different routines for&n; * quotaoff start and quotaoff end?  I suspect the answer is yes but&n; * to be sure, I need to look at the recovery code and see how quota off&n; * recovery is handled (do we roll forward or back or do something else).&n; * If we roll forwards or backwards, then we need two separate routines,&n; * one that does nothing and one that stamps in the lsn that matters&n; * (truly makes the quotaoff irrevocable).  If we do something else,&n; * then maybe we don&squot;t need two.&n; */
multiline_comment|/* ARGSUSED */
id|STATIC
r_void
DECL|function|xfs_qm_qoff_logitem_committing
id|xfs_qm_qoff_logitem_committing
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qip
comma
id|xfs_lsn_t
id|commit_lsn
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* ARGSUSED */
id|STATIC
r_void
DECL|function|xfs_qm_qoffend_logitem_committing
id|xfs_qm_qoffend_logitem_committing
c_func
(paren
id|xfs_qoff_logitem_t
op_star
id|qip
comma
id|xfs_lsn_t
id|commit_lsn
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|variable|xfs_qm_qoffend_logitem_ops
r_struct
id|xfs_item_ops
id|xfs_qm_qoffend_logitem_ops
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
id|xfs_qm_qoff_logitem_size
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
id|xfs_qm_qoff_logitem_format
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
id|xfs_qm_qoff_logitem_pin
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
id|xfs_qm_qoff_logitem_unpin
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
id|xfs_qm_qoff_logitem_unpin_remove
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
id|xfs_qm_qoff_logitem_trylock
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
id|xfs_qm_qoff_logitem_unlock
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
id|xfs_qm_qoffend_logitem_committed
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
id|xfs_qm_qoff_logitem_push
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
id|xfs_qm_qoff_logitem_abort
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
id|xfs_qm_qoffend_logitem_committing
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the ops vector shared by all quotaoff-start log items.&n; */
DECL|variable|xfs_qm_qoff_logitem_ops
r_struct
id|xfs_item_ops
id|xfs_qm_qoff_logitem_ops
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
id|xfs_qm_qoff_logitem_size
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
id|xfs_qm_qoff_logitem_format
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
id|xfs_qm_qoff_logitem_pin
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
id|xfs_qm_qoff_logitem_unpin
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
id|xfs_qm_qoff_logitem_unpin_remove
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
id|xfs_qm_qoff_logitem_trylock
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
id|xfs_qm_qoff_logitem_unlock
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
id|xfs_qm_qoff_logitem_committed
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
id|xfs_qm_qoff_logitem_push
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
id|xfs_qm_qoff_logitem_abort
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
id|xfs_qm_qoff_logitem_committing
)brace
suffix:semicolon
multiline_comment|/*&n; * Allocate and initialize an quotaoff item of the correct quota type(s).&n; */
id|xfs_qoff_logitem_t
op_star
DECL|function|xfs_qm_qoff_logitem_init
id|xfs_qm_qoff_logitem_init
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_qoff_logitem_t
op_star
id|start
comma
id|uint
id|flags
)paren
(brace
id|xfs_qoff_logitem_t
op_star
id|qf
suffix:semicolon
id|qf
op_assign
(paren
id|xfs_qoff_logitem_t
op_star
)paren
id|kmem_zalloc
c_func
(paren
r_sizeof
(paren
id|xfs_qoff_logitem_t
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|qf-&gt;qql_item.li_type
op_assign
id|XFS_LI_QUOTAOFF
suffix:semicolon
r_if
c_cond
(paren
id|start
)paren
id|qf-&gt;qql_item.li_ops
op_assign
op_amp
id|xfs_qm_qoffend_logitem_ops
suffix:semicolon
r_else
id|qf-&gt;qql_item.li_ops
op_assign
op_amp
id|xfs_qm_qoff_logitem_ops
suffix:semicolon
id|qf-&gt;qql_item.li_mountp
op_assign
id|mp
suffix:semicolon
id|qf-&gt;qql_format.qf_type
op_assign
id|XFS_LI_QUOTAOFF
suffix:semicolon
id|qf-&gt;qql_format.qf_flags
op_assign
id|flags
suffix:semicolon
id|qf-&gt;qql_start_lip
op_assign
id|start
suffix:semicolon
r_return
(paren
id|qf
)paren
suffix:semicolon
)brace
eof
